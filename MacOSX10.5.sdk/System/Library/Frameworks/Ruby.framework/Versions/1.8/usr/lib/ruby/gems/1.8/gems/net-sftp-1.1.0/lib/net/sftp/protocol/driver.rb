#--
# =============================================================================
# Copyright (c) 2004, Jamis Buck (jamis@37signals.com)
# All rights reserved.
#
# This source file is distributed as part of the Net::SFTP Secure FTP Client
# library for Ruby. This file (and the library as a whole) may be used only as
# allowed by either the BSD license, or the Ruby license (or, by association
# with the Ruby license, the GPL). See the "doc" subdirectory of the Net::SFTP
# distribution for the texts of these licenses.
# -----------------------------------------------------------------------------
# net-sftp website: http://net-ssh.rubyforge.org/sftp
# project website : http://rubyforge.org/projects/net-ssh
# =============================================================================
#++

require 'thread'
require 'net/sftp/errors'
require 'net/sftp/protocol/constants'

module Net ; module SFTP ; module Protocol

  # This is the driver object for the SFTP protocol. It manages the SSH channel
  # used to communicate with the server, as well as the negotiation of the
  # protocol. The operations themselves are specific to the protocol version
  # in use, and are handled by protocol-version-specific dispatcher objects.
  class Driver
    include Constants

    # The current state of the driver. This will be one of +unconfirmed+,
    # +init+, +version+, +open+, or +closed+.
    attr_reader :state
    
    # The underlying SSH channel supporting this SFTP connection.
    attr_reader :channel

    # Create a new SFTP protocol driver object on the given SSH connection.
    # +buffers+ is a reference to a buffer factory, +version+ is the highest
    # supported SFTP protocol version, +dispatchers+ is a Proc object that
    # returns a dispatcher instance for a specific protocol version, and +log+
    # is a logger instance.
    #
    # The new protocol driver will be in an +unconfirmed+ state, initially.
    # When the server validates the requested channel, the driver goes to the
    # +init+ state, and requests the SFTP subsystem. When the subsystem has
    # been accepted, the driver sends its supported protocol version to the
    # server, and goes to the +version+ state. Lastly, when the server
    # responds with its supported protocol version and the version to use has
    # been successfully negotiated, the driver will go to the +open+ state,
    # after which SFTP operations may be successfully performed on the driver.
    def initialize( connection, buffers, version, dispatchers, log )
      @buffers = buffers
      @version = version
      @dispatchers = dispatchers
      @log = log

      @next_request_id = 0
      @next_request_mutex = Mutex.new
      @parsed_data = nil
      @on_open = nil

      @state = :unconfirmed

      @log.debug "opening channel for sftp" if @log.debug?
      @channel = connection.open_channel( "session", &method( :do_confirm ) )
    end

    # Closes the underlying SSH channel that the SFTP session uses to
    # communicate with the server. This moves the driver to the +closed+
    # state. If the driver is already closed, this does nothing.
    def close
      if @state != :closed
        @log.debug "closing sftp channel" if @log.debug?
        @channel.close
        @state = :closed
      end
    end

    # Returns the next available request id in a thread-safe manner. The
    # request-id is used to identify packets associated with request sequences.
    def next_request_id
      @next_request_mutex.synchronize do
        request_id = @next_request_id
        @next_request_id += 1
        return request_id
      end
    end

    # Specify the callback to invoke when the session has been successfully
    # opened (i.e., once the driver's state has moved to +open+). The callback
    # should accept a single parameter--the driver itself.
    def on_open( &block )
      @on_open = block
    end

    # The callback used internally to indicate that the requested channel has
    # been confirmed. This will request the SFTP subsystem, register some
    # request callbacks, and move the driver's state to +init+. This may only
    # be called when the driver's state is +unconfirmed+.
    def do_confirm( channel )
      assert_state :unconfirmed
      @log.debug "requesting sftp subsystem" if @log.debug?

      channel.subsystem  "sftp"
      channel.on_success &method( :do_success )
      channel.on_data    &method( :do_data )

      @state = :init
    end

    # The callback used internally to indicate that the SFTP subsystem was
    # successfully requested. This may only be called when the driver's state
    # is +init+. It sends an INIT packet containing the highest supported
    # SFTP protocol version to the server, and moves the driver's state to
    # +version+.
    def do_success( channel )
      assert_state :init
      @log.debug "initializing sftp subsystem" if @log.debug?

      packet = @buffers.writer
      packet.write_long @version
      send_data FXP_INIT, packet

      @state = :version
    end

    # This is used internally to indicate that a VERSION packet was received
    # from the server. This may only be called when the driver's state is
    # +version+. It determines the highest possible protocol version supported
    # by both the client and the server, selects the dispatcher that handles
    # that protocol version, moves the state to +open+, and then invokes the
    # +on_open+ callback (if one was registered).
    def do_version( content )
      assert_state :version
      @log.debug "negotiating sftp protocol version" if @log.debug?
      @log.debug "my sftp version is #{@version}" if @log.debug?

      server_version = content.read_long
      @log.debug "server reports sftp version #{server_version}" if @log.debug?

      negotiated_version = [ @version, server_version ].min 
      @log.info "negotiated version is #{negotiated_version}" if @log.info?

      extensions = Hash.new
      until content.eof?
        ext_name = content.read_string
        ext_data = content.read_string
        extensions[ ext_name ] = ext_data
      end

      @dispatcher = @dispatchers[ negotiated_version, extensions ]

      @state = :open

      @on_open.call( self ) if @on_open
    end

    # This is called internally when a data packet is received from the server.
    # All SFTP packets are transfered as SSH data packets, so this parses the
    # data packet to determine the SFTP packet type, and then sends the contents
    # on to the active dispatcher for further processing. This routine correctly
    # handles SFTP packets that span multiple SSH data packets.
    def do_data( channel, data )
      if @parsed_data
        @parsed_data[:content].append data
        return if @parsed_data[:length] > @parsed_data[:content].length

        type = @parsed_data[:type]
        content = @parsed_data[:content]
        @parsed_data = nil
      else
        reader = @buffers.reader( data )
        length = reader.read_long-1
        type = reader.read_byte
        content = reader.remainder_as_buffer

        if length > content.length
          @parsed_data = { :length => length,
                           :type => type,
                           :content => content }
          return
        end
      end

      if type == FXP_VERSION
        do_version content
      else
        assert_state :open
        @dispatcher.dispatch channel, type, content
      end
    end

    # Delegates missing methods to the current dispatcher (if the state is
    # +open+). This allows clients to register callbacks for the supported
    # operations of the negotiated protocol version.
    def method_missing( sym, *args, &block )
      if @state == :open && @dispatcher.respond_to?( sym )
        assert_state :open
        @dispatcher.__send__( sym, *args, &block )
      else
        super
      end
    end

    # Returns true if the driver responds to the given message, or if the
    # state is +open+ and the active dispatcher responds to the given
    # message.
    def respond_to?( sym )
      super || @state == :open && @dispatcher.respond_to?( sym )
    end

    # A convenience method for sending an SFTP packet of the given type,
    # with the given payload. This repackages the data as an SSH data packet
    # and sends it across the channel.
    def send_data( type, data )
      data = data.to_s

      msg = @buffers.writer
      msg.write_long data.length + 1
      msg.write_byte type
      msg.write data

      @channel.send_data msg
    end

    # A sanity checker, to ensure that an operation is invoked only when the
    # appropriate state is active.
    def assert_state( state )
      raise Net::SFTP::Bug, "invalid state `#{state}'" if state != @state
    end
    private :assert_state

  end

end ; end ; end
