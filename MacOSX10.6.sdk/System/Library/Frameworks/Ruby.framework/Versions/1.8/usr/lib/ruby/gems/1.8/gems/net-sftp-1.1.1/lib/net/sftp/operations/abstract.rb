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

require 'net/sftp/operations/errors'

module Net ; module SFTP ; module Operations

  # The base class for all SFTP operations. Subclasses must implement a
  # +perform+ method, which accepts the arguments expected by the corresponding
  # method of the driver. Subclasses _may_ also override the default
  # implementations of +do_status+, +do_data+, +do_name+, +do_handle+, and
  # +do_attrs+, as necessary.
  class Abstract
    include Constants

    # A structure for reporting status information.
    Status = Struct.new( :code, :message, :language )

    # A constant for representing the commonly-used FX_OK status.
    OK = Status.new( FX_OK, "Success", "" )

    # Create a new operation with the given logger instance, which will
    # operate atop the given session, using the given driver to format and 
    # send the requests to the server.
    def initialize( log, session, driver )
      @log = log
      @session = session
      @driver = driver
    end

    # Execute the operation. If a callback is given, the operation will be
    # performed asynchronously with the callback being invoked when the
    # operation completes. If a callback is not given, the operation will
    # be performed synchronously, with the expected value being returned.
    def execute( *args, &callback )
      @log.debug "executing" if @log.debug?

      unless block_given?
        status = result = nil
        callback = Proc.new do |status, *pargs|
          status = status
          result = case
            when pargs.empty? then @session.status
            when pargs.length == 1 then pargs.first
            else pargs
          end
        end
      end

      @callback = callback
      @id = perform *args
      @log.debug "received request id #{@id}"
      @session.register( @id, self )

      unless block_given?
        @session.loop { status.nil? }
        @session.status = status
        return result
      end
    end

    # A callback for SFTP status packets. By default, raises an exception unless
    # the status is FX_OK, in which case the registered callback is invoked.
    def do_status( code, message, language )
      raise StatusException.new( code, message, language ) unless code == FX_OK
      @callback[ Status.new( code, message, language ) ]
    end

    # A callback for SFTP handle packets. By default, invokes the registered
    # callback, passing an OK status and the handle.
    def do_handle( handle )
      @callback[ OK, handle ]
    end

    # A callback for SFTP data packets. By default, invokes the registered
    # callback, passing an OK status and the data.
    def do_data( data )
      @callback[ OK, data ]
    end

    # A callback for SFTP name packets. By default, invokes the registered
    # callback, passing an OK status and the list of items.
    def do_name( items )
      @callback[ OK, items ]
    end

    # A callback for SFTP attrs packets. By default, invokes the registered
    # callback, passing an OK status and the attributes object.
    def do_attrs( attributes )
      @callback[ OK, attributes ]
    end

  end

end ; end ; end
