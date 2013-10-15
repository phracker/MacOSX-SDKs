#--
# =============================================================================
# Copyright (c) 2004,2005 Jamis Buck (jamis@37signals.com)
# All rights reserved.
#
# This source file is distributed as part of the Net::SSH Secure Shell Client
# library for Ruby. This file (and the library as a whole) may be used only as
# allowed by either the BSD license, or the Ruby license (or, by association
# with the Ruby license, the GPL). See the "doc" subdirectory of the Net::SSH
# distribution for the texts of these licenses.
# -----------------------------------------------------------------------------
# net-ssh website : http://net-ssh.rubyforge.org
# project website: http://rubyforge.org/projects/net-ssh
# =============================================================================
#++

require 'net/ssh/connection/constants'
require 'net/ssh/connection/term'

module Net
  module SSH
    module Connection

      class Channel
        include Constants

        #--
        # ====================================================================
        # ATTRIBUTES
        # ====================================================================
        #++

        # The channel's local id (assigned by the connection)
        attr_reader :local_id

        # The channel's remote id (assigned by the remote server)
        attr_reader :remote_id

        # The connection driver instance that owns this channel
        attr_reader :connection

        # The type of this channel
        attr_reader :type
        
        # The maximum packet size that may be sent over this channel
        attr_reader :maximum_packet_size

        # The maximum data window size for this channel
        attr_reader :window_size

        # The maximum packet size that may be sent over this channel
        attr_reader :local_maximum_packet_size

        # The maximum data window size for this channel
        attr_reader :local_window_size

        #--
        # ====================================================================
        # FACTORY METHODS
        # ====================================================================
        #++

        # Requests that a new channel be opened on the remote host.
        # This will return immediately, but the +on_confirm_open+ callback
        # will be invoked when the remote host confirms that the channel has
        # been successfully opened.
        def self.open( connection, log, buffers, type, data=nil )
          channel = new( connection, log, buffers, type )

          msg = buffers.writer

          msg.write_byte CHANNEL_OPEN
          msg.write_string type
          msg.write_long channel.local_id
          msg.write_long channel.local_window_size
          msg.write_long channel.local_maximum_packet_size
          msg.write data.to_s if data

          connection.send_message msg

          channel
        end

        # Creates a new channel object with the given internal
        # information. The channel is assumed to already be
        # connected to a remote host.
        def self.create( connection, log, buffers, type, remote_id,
          window_size, packet_size )
        # begin
          channel = new( connection, log, buffers, type )
          channel.do_confirm_open remote_id, window_size, packet_size
          channel
        end

        private_class_method :new

        #--
        # ====================================================================
        # CONSTRUCTOR
        # ====================================================================
        #++

        # Create a new channel object on the given connection, and of the given
        # type.
        def initialize( connection, log, buffers, type )
          @connection = connection
          @log = log
          @buffers = buffers
          @type = type
          @local_id = @connection.allocate_channel_id
          @local_window_size = 0x20000
          @local_maximum_packet_size = 0x10000
        end

        #--
        # ====================================================================
        # CALLBACK HOOKS
        # ====================================================================
        #++

        # Set the callback to use when the channel has been confirmed
        # to be open.
        def on_confirm_open( &block )
          @on_confirm_open = block
        end

        # Set the callback to use when the channel could not be opened
        # for some reason.
        def on_confirm_failed( &block )
          @on_confirm_failed = block
        end

        # Set the callback to be invoked when the server requests
        # that the window size be adjusted.
        def on_window_adjust( &block )
          @on_window_adjust = block
        end

        # Set the callback to be invoked when the server sends a
        # data packet over the channel.
        def on_data( &block )
          @on_data = block
        end

        # Set the callback to be invoked when the server sends an
        # extended data packet over the channel.
        def on_extended_data( &block )
          @on_extended_data = block
        end

        # Set the callback to be invoked when the server sends an EOF
        # packet.
        def on_eof( &block )
          @on_eof = block
        end

        # Set the callback to be invoked when the server sends a
        # request packet.
        def on_request( &block )
          @on_request = block
        end

        # Set the callback to invoked when the server sends
        # confirmation of a successful operation.
        def on_success( &block )
          @on_success = block
        end

        # Set the callback to invoked when the server sends
        # notification of a failed operation.
        def on_failure( &block )
          @on_failure = block
        end

        # Set the callback to be invoked when the channel is closed.
        def on_close( &block )
          @on_close = block
        end

        #--
        # ====================================================================
        # CHANNEL STATE ACCESSORS
        # ====================================================================
        #++

        def valid?
          not @local_id.nil?
        end

        # Retrieved a named property of the channel.
        def property( name )
          ( @properties ||= Hash.new )[ name ]
        end

        # Set a named property on the channel.
        def set_property( name, value )
          ( @properties ||= Hash.new )[ name ] = value
        end

        alias :[]  :property
        alias :[]= :set_property

        #--
        # ====================================================================
        # CHANNEL AFFECTORS
        # ====================================================================
        #++

        # Closes the channel.
        def close( client_initiated=true )
          unless defined?(@already_closed) && @already_closed
            msg = @buffers.writer
            msg.write_byte CHANNEL_CLOSE
            msg.write_long @remote_id
            @connection.send_message msg
            @already_closed = true
          end

          unless client_initiated
            @connection.remove_channel( self )
            callback :close, self
          end

          self
        end

        # Send an EOF across the channel. No data should be sent from the client
        # to the server over this channel after this, although packets may still
        # be received from the server.
        def send_eof
          msg = @buffers.writer
          msg.write_byte CHANNEL_EOF
          msg.write_long @remote_id
          @connection.send_message msg
          self
        end

        # Send the given signal to process on the other side of the channel. The
        # parameter should be one of the Channel::SIGxxx constants.
        def send_signal( sig, want_reply=false )
          send_request_string "signal", sig, want_reply
          self
        end

        # Send a channel request with the given name. It will have one data
        # item, which will be interpreted as a string.
        def send_request_string( request_name, data, want_reply=false )
          msg = @buffers.writer
          msg.write_string data.to_s
          send_request request_name, msg, want_reply
        end

        # Send a generic channel request with the given name. The data item will
        # be written directly into the request (after converting it to a string,
        # as necessary).
        def send_request( request_name, data, want_reply=false )
          msg = @buffers.writer
          msg.write_byte CHANNEL_REQUEST
          msg.write_long @remote_id
          msg.write_string request_name
          msg.write_bool want_reply
          msg.write data.to_s
          @connection.send_message msg
          self
        end

        # Send a "window adjust" message to the server for this channel,
        # informing it that it may send this many more bytes over the
        # channel.
        def send_window_adjust( size )
          msg = @buffers.writer
          msg.write_byte CHANNEL_WINDOW_ADJUST
          msg.write_long @remote_id
          msg.write_long size
          @connection.send_message msg
        end

        # Send a data packet to the server, over the channel.
        def send_data( data )
          @connection.register_data_request( self, data )
        end

        # Send an extended data packet to the server, over the channel.
        # Extended data always has a numeric type associated with it. The
        # only predefined type is 1, whic corresponds to +stderr+ data.
        def send_extended_data( type, data )
          @connection.register_data_request( self, data, type )
        end

        # Splits the given data so that it will fit in a data packet, taking
        # into consideration the current window size and maximum packet size.
        # The +overhead+ parameter is the number of additional bytes added by
        # the packet itself.
        #
        # This returns a tuple, <tt>[data,data_to_return]</tt>, where the first
        # element is the data to include in the packet, and the second element
        # is the data remaining that would not fit in the packet.
        def split_data_for_packet( data, overhead )
          data_to_return = nil

          if data.length > window_size 
            data_to_return = data[window_size..-1]
            data = data[0,window_size]
          end

          max_size_less_overhead = maximum_packet_size - overhead
          if data.length > max_size_less_overhead
            data_to_return = data[max_size_less_overhead..-1] + ( data_to_return || "" )
            data = data[0,max_size_less_overhead]
          end

          [ data, data_to_return ]
        end
        private :split_data_for_packet

        # Send a data packet to the server, over the channel. Only sends as
        # much of that data as the channel is currently capable of sending
        # (based on window size and maximum packet size), and returns any
        # data that could not be sent. Returns +nil+ if all the data that
        # was requested to be sent, was sent.
        def send_data_packet( data )
          # overhead is ( byte.length + id.length + strlen.length ) = 9
          data, data_to_return = split_data_for_packet( data.to_s, 9 )
          @window_size -= data.length

          msg = @buffers.writer
          msg.write_byte CHANNEL_DATA
          msg.write_long @remote_id
          msg.write_string data
          @connection.send_message msg

          data_to_return
        end

        # Send an extended data packet to the server, over the channel.
        # Extended data always has a numeric type associated with it. The
        # only predefined type is 1, whic corresponds to +stderr+ data.
        def send_extended_data_packet( type, data )
          # overhead is
          #   ( byte.length + id.length + type.length + strlen.length ) = 13
          data, data_to_return = split_data_for_packet( data.to_s, 13 )
          @window_size -= data.length

          msg = @buffers.writer
          msg.write_byte CHANNEL_EXTENDED_DATA
          msg.write_long @remote_id
          msg.write_long type
          msg.write_string data
          @connection.send_message msg

          data_to_return
        end

        VALID_PTY_OPTIONS = { :term=>"xterm",
                              :chars_wide=>80,
                              :chars_high=>24,
                              :pixels_wide=>640,
                              :pixels_high=>480,
                              :modes=>{},
                              :want_reply=>false }

        # Request that a pty be opened for this channel. Valid options are
        # :term, :chars_wide, :chars_high, :pixels_wide, :pixels_high, :modes,
        # and :want_reply. :modes is a Hash, where the keys are constants from
        # Net::SSH::Service::Term, and values are integers describing the
        # corresponding key.
        def request_pty( opts = {} )
          invalid_opts = opts.keys - VALID_PTY_OPTIONS.keys
          unless invalid_opts.empty?
            raise ArgumentError,
              "invalid option(s) to request_pty: #{invalid_opts.inspect}"
          end

          opts = VALID_PTY_OPTIONS.merge( opts )

          msg = @buffers.writer
          msg.write_string opts[ :term ]
          msg.write_long opts[ :chars_wide ]
          msg.write_long opts[ :chars_high ]
          msg.write_long opts[ :pixels_wide ]
          msg.write_long opts[ :pixels_high ]

          modes = @buffers.writer
          opts[ :modes ].each do |mode, data|
            modes.write_byte mode
            modes.write_long data
          end
          modes.write_byte Term::TTY_OP_END

          msg.write_string modes.to_s

          send_request "pty-req", msg, opts[:want_reply]
        end

        # Execute the given remote command over the channel. This should be
        # invoked in the "on_confirm" callback of a channel. This method will
        # return immediately.
        def exec( command, want_reply=false )
          send_request_string "exec", command, want_reply
        end

        # Request the given subsystem. This method will return immediately.
        def subsystem( subsystem, want_reply=true )
          send_request_string "subsystem", subsystem, want_reply
        end

        #--
        # ====================================================================
        # CHANNEL EVENTS
        # ====================================================================
        #++

        # A convenience method for defining new event callbacks.
        def self.event( event, *parameters )
          define_method "do_#{event}" do |*args|
            callback event, self, *args
            self
          end
        end

        # Invoked when the server confirms the opening of a channel.
        def do_confirm_open( remote_id, window_size, packet_size )
          @remote_id = remote_id
          @window_size = window_size
          @maximum_packet_size = packet_size
          callback :confirm_open, self
        end

        # Invoked when the server failed to confirm the opening of a channel.
        def do_confirm_failed( reason_code, description, language )
          @local_id = nil
          @connection = nil
          callback :confirm_failed, self, reason_code, description, language
        end

        # Invoked when the server asks to adjust the window size. This in turn
        # calls the "on_window_adjust" callback.
        def do_window_adjust( bytes_to_add )
          @window_size += bytes_to_add
          callback :window_adjust, self, bytes_to_add
        end

        # Invoked when the server sends a data packet. This in turn calls the
        # "on_data" callback.
        def do_data( data )
          update_local_window_size data
          callback :data, self, data
        end

        # Invoked when the server sends an extended data packet. This in turn
        # calls the "on_extended_data" callback.
        def do_extended_data( type, data )
          update_local_window_size data
          callback :extended_data, self, type, data
        end

        # Invoked when the server sends an EOF packet. This in turn calls the
        # "on_eof" callback.
        event :eof

        # Invoked when the server sends a request packet. This in turn calls
        # the "on_request" callback.
        event :request, :type, :want_reply, :data

        # Invoked when the server sends confirmation of a successful operation.
        # This in turn invokes the "on_success" callback, if set.
        event :success

        # Invoked when the server sends notification of a failed operation.
        # This in turn invokes the "on_failure" callback, if set.
        event :failure

        #--
        # ====================================================================
        # PRIVATE UTILITIES
        # ====================================================================
        #++

        # Updates the window size for this channel based on the size of the
        # data that was receieved. If no more space in the window is left,
        # a message is sent to the server indicating that the window size
        # is increased.
        def update_local_window_size( data )
          @local_window_size -= data.length
          if @local_window_size < 4096
            @local_window_size += 0x20000
            send_window_adjust 0x20000
          end
        end
        private :update_local_window_size

        # A convenience utility method for invoking a named callback with a
        # set of arguments.
        def callback( which, *args )
          block = instance_variable_get( "@on_#{which.to_s}" )
          block.call( *args ) if block
        end
        private :callback

      end

    end
  end
end
