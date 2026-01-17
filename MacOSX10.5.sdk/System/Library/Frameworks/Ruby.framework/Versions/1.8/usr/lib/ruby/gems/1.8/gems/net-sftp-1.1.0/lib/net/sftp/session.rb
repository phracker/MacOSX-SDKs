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

require 'net/sftp/errors'
require 'net/sftp/protocol/constants'

module Net ; module SFTP

  # Represents a single SFTP session, running atop an SSH session.
  class Session
    include Protocol::Constants

    # remove this, inherited from Kernel, so that sftp.open will go via
    # method_missing
    undef :open

    # The status of the last synchronously executed operation. This is either
    # +nil+, or an object that responds to <tt>:code</tt>, <tt>:message</tt>,
    # and <tt>:language</tt>.
    attr_accessor :status

    # Create a new SFTP session on top of the given SSH session.
    def initialize( session )
      @session = session
      @log = @session.registry.log_for( "sftp.session" )

      @session.registry.namespace_define :sftp do |ns|
        ns.require "net/sftp/protocol/services", "Net::SFTP::Protocol"
        ns.require "net/sftp/operations/services", "Net::SFTP::Operations"

        # register a reference to myself for other services to be able to
        # access me.
        ns.session( :pipeline => [] ) { self }

        @driver = ns.protocol.driver
        @driver.on_open do |d|
          d.on_attrs( &method( :do_attrs  ))
          d.on_data(  &method( :do_data   ))
          d.on_handle(&method( :do_handle ))
          d.on_name(  &method( :do_name   ))
          d.on_status(&method( :do_status ))

          if block_given?
            begin
              yield self
            ensure
              d.close
            end
          end
        end

        @operations = ns.operations
      end

      @requests = Hash.new

      @session.loop if block_given?
    end

    #--
    # ====================================================================
    # QUERIES/GETTERS/SETTERS/ACTIONS
    # ====================================================================
    #++

    # Return the state of the SFTP connection. (See
    # Net::SFTP::Protocol::Driver#state.)
    def state
      @driver.state
    end

    # Return the underlying SSH channel that supports this SFTP connection.
    # Useful for adding custom callbacks for some events, or for accessing
    # the underlying connection beneath the channel.
    def channel
      @driver.channel
    end

    # Closes the SFTP connection, but leaves the SSH connection open.
    def close_channel
      @driver.close
    end

    # Closes the underlying SSH connection.
    def close
      @session.close
    end

    # Registers the given handler with the given request id. This is used
    # internally by the operations, so that the session knows who to delegate
    # a response to that has been received from the server.
    def register( id, handler )
      @requests[ id ] = handler
    end

    # Delegates to Net::SSH::Session#loop. Causes the underlying SSH
    # connection to process events as long as the given block returns +true+,
    # or (if no block is given) until there are no more open channels.
    def loop( &block )
      @session.loop( &block )
    end

    # Waits for the underlying driver to reach a state of :open (or :closed).
    # This makes it easier to use the SFTP routines synchronously without using
    # the block form:
    #
    #   sftp = Net::SFTP::Session.new( ssh_session )
    #   sftp.connect
    #   puts sftp.realpath( "." )
    #
    # Without the call to #connect, the call to #realpath would fail because
    # the SFTP protocol has not yet been negotiated and no underlying driver has
    # been selected.
    #
    # If no block is given, it returns +self+, so it can be chained easily to
    # other method calls. If a block _is_ given, the session is yielded to the
    # block as soon as the driver successfully reports it's state as +open+,
    # with the session's channel being closed automatically when the block
    # finishes.
    #
    #   require 'net/ssh'
    #   require 'net/sftp'
    #
    #   Net::SSH.start( 'localhost' ) do |session|
    #     session.sftp.connect do |sftp|
    #       puts sftp.realpath( "." )
    #     end
    #   end
    def connect
      @session.loop do
        @driver.state != :open &&
        @driver.state != :closed
      end
      if @driver.state == :open && block_given?
        begin
          yield self
        ensure
          close_channel
        end
      else
        self
      end
    end

    # Opens the given remote file and returns a handle to it, which may be used
    # with other operations (read, write, etc.). If a block is given, the handle
    # will be yielded to it and closed when the block finishes, otherwise the
    # handle will be returned. If the flags parameter is a numeric value, it
    # must be a combination of IO constants, otherwise, it should be a string
    # such as given to File.open.
    def open_handle( path, flags=IO::RDONLY, mode=0660 )
      if String === flags
        flags = case flags
          when "r" then IO::RDONLY
          when "r+" then IO:RDWR
          when "w" then IO::WRONLY | IO::CREAT | IO::TRUNC
          when "w+" then IO::RDWR | IO::CREAT | IO::TRUNC
          when "a" then IO::APPEND | IO::CREAT
          when "a+" then IO::APPEND | IO::CREAT
          else IO::RDONLY
        end
      end

      handle = self.open( path, flags, mode )
      if block_given?
        begin
          yield handle
        ensure
          close_handle( handle )
        end
      else
        return handle
      end
    end

    # Retrieves the given remote file to the given local path. This will
    # overwrite any file at the local path name. The remote file must
    # exist.
    def get_file( remote_path, local_path )
      open_handle( remote_path ) do |handle|
        contents = read( handle )
        File.open( local_path, "wb" ) { |f| f.write contents }
      end
    end

    # This stores the given local file at the given remote path. This will
    # overwrite any file at the remote path name. The local file must exist.
    def put_file( local_path, remote_path )
      contents = File.open( local_path, "rb" ) { |f| f.read }
      open_handle( remote_path, "w" ) { |handle| write( handle, contents ) }
    end
    
    #--
    # ====================================================================
    # CALLBACKS
    # ====================================================================
    #++

    # Invoked by the underlying SFTP protocol layer when a SFTP data packet
    # is received.
    def do_data( driver, id, data )
      @requests.delete( id ).do_data( data )
    end

    # Invoked by the underlying SFTP protocol layer when a SFTP status packet
    # is received.
    def do_status( driver, id, code, message, language )
      @requests.delete( id ).do_status( code, message, language )
    end

    # Invoked by the underlying SFTP protocol layer when a SFTP handle packet
    # is received.
    def do_handle( driver, id, handle )
      @requests.delete( id ).do_handle( handle )
    end

    # Invoked by the underlying SFTP protocol layer when a SFTP name packet
    # is received.
    def do_name( driver, id, items )
      @requests.delete( id ).do_name( items )
    end

    # Invoked by the underlying SFTP protocol layer when a SFTP attrs packet
    # is received.
    def do_attrs( driver, id, attributes )
      @requests.delete( id ).do_attrs( attributes )
    end

    #--
    # ====================================================================
    # DELEGATION
    # ====================================================================
    #++

    # Delegates the message to the operation that has been registered with
    # the given name. If no such operation exists, control is passed to the
    # superclass' implementation of #method_missing.
    def method_missing( sym, *args, &block )
      if @operations.has_key?( sym )
        @operations[ sym ].execute( *args, &block )
      else
        super
      end
    end

    # Returns +true+ if the object responds to the given symbol, or if there is
    # an operation registered under the given symbol.
    def respond_to?( sym )
      super || @operations.has_key?( sym )
    end

    # Returns +true+ if the underlying driver responds to the given symbol. This
    # can be used by clients to determine whether the SFTP protocol version in
    # use supports a particular operation.
    def support?( sym )
      @driver.respond_to?( sym )
    end

  end

end ; end
