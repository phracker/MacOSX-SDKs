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

require 'thread'
require 'net/ssh/connection/constants'
require 'net/ssh/errors'

module Net
  module SSH
    module Connection

      class Driver
        include Constants

        # A structure for representing global requests, as registered by the
        # #global_request method.
        Request = Struct.new( :type, :data, :callback )

        # A structure for representing a data buffer that must be sent
        # across a channel.
        DataRequest = Struct.new( :channel, :data, :type )

        #--
        # ====================================================================
        # CONSTRUCTOR
        # ====================================================================
        #++

        # Create a new connection driver that communicates over the given
        # transport session. +log+ is the logger instance to write log messages
        # to, buffers is a buffer factory, and channels is a factory that can
        # return new channel instances.
        def initialize( session, log, buffers, factories )
          @session = session
          @log = log
          @buffers = buffers
          @factories = factories

          @channel_id_mutex = Mutex.new
          @next_channel_id = 0

          @channel_map = Hash.new
          @request_queue = Array.new
          @channel_open_handlers = Hash.new

          @data_requests = Array.new
          @data_requests_mutex = Mutex.new
        end

        #--
        # ====================================================================
        # CHANNEL MANAGEMENT
        # ====================================================================
        #++

        # Open and return a new channel. This returns immediately, before the
        # server confirms that the channel was opened. When the server sends
        # the confirmation, the +on_confirm+ callback will be invoked.
        def open_channel( type, extra_data=nil, &on_confirm )
          channel = @factories[:open].call( type, extra_data )
          channel.on_confirm_open(&on_confirm)
          @channel_map[ channel.local_id ] = channel
        end

        # Remove the given channel from the connection.
        def remove_channel( channel )
          @channel_map.delete channel.local_id
        end

        # Returns an array of active channels.
        def channels
          @channel_map.values
        end

        # Add a callback to be invoked when a channel-open request is recieved
        # for a channel of the given type. The handler-id is returned.
        def add_channel_open_handler( type, &block )
          ( @channel_open_handlers[ type ] ||= Array.new ).push block
          @channel_open_handlers.length
        end

        # Remove a callback with the given id for channel-open requests of the
        # given type.
        def remove_channel_open_handler( type, id )
          @channel_open_handlers[ type ][ id-1 ] = nil
        end

        # Return the next available channel id for this connection. This
        # method is thread-safe.
        def allocate_channel_id
          @channel_id_mutex.synchronize do
            @next_channel_id += 1
            return @next_channel_id
          end
        end

        # Register a data buffer (of an optional type) to be sent across the
        # given channel at the next available opportunity.
        #
        # This is used internally by channels to hide the window size and
        # maximum packet size from the client. Clients should not call this
        # method directly.
        def register_data_request( channel, data, type=nil )
          @data_requests_mutex.synchronize do
            @data_requests << DataRequest.new( channel, data, type )
          end

          # make sure the new data request has a chance to be sent to the
          # server... Otherwise, it cannot be sent until the next time #process
          # is invoked, which can be unexpected in synchronous situations.
          process_data_requests
        end

        #--
        # ====================================================================
        # CONNECTION PROCESSING
        # ====================================================================
        #++

        # Repeated call #process for as long as the given block returns
        # +true+. If no block is given, then the loop continues until there
        # are no more open channels on this connection.
        def loop( &block )
          block ||= proc do 
            channels = @channel_map.reject {|k,v| v.type == 'auth-agent@openssh.com' }
            not channels.empty?
          end
          process while block.call
        end

        # Wait for and dispatch a single event. If +nonblock+ is false (the
        # default) this will block until a message has been received. Otherwise,
        # it will return immediately.
        def process( nonblock=false )
          process_data_requests

          if !nonblock || reader_ready?
            type, response = @session.wait_for_message

            unless ( dispatcher = MESSAGES[ type ] )
              raise Net::SSH::Exception,
                "Unexpected response type '#{type}', (#{response.inspect})"
            end

            dispatcher[:method].bind( self ).call( response )
          end

          self
        end

        #--
        # ====================================================================
        # COMMUNICATION
        # ====================================================================
        #++

        # Send a global request packet to the server. This returns immediately.
        # The given block will be invoked when the server responds.
        def global_request( type, data=nil, &block )
          writer = @buffers.writer
          writer.write_byte GLOBAL_REQUEST
          writer.write_string type.to_s
          writer.write_bool true
          writer.write data.to_s if data
          @session.send_message writer

          @request_queue.push Request.new( type, data, block )
          self
        end

        # Send a channel request packet to the server.
        def channel_request( type )
          writer = @buffers.writer
          writer.write_byte CHANNEL_REQUEST
          writer.write_long 0 # channel id
          writer.write_string type
          writer.write_byte 0 # want_confirm
          
          @session.send_message writer
        end

        # A convenience method for sending messages.
        def send_message( msg )
          @session.send_message msg
          self
        end

        # Delegates to the #reader_ready method of the transport session.
        def reader_ready?
          @session.reader_ready?
        end

        # Sends an innocuous packet to the server to test the connection. Can
        # be used to defeat timeouts on long-running commands.
        def ping!
          @session.ping!
        end

        #--
        # ====================================================================
        # MESSAGE HANDLERS
        # ====================================================================
        #++

        def do_global_request( response )
          name = response.read_string
          want_reply = response.read_bool
          request_data = response.remainder_as_buffer

          @log.debug "GLOBAL_REQUEST received (#{name})" if @log.debug?

          if want_reply
            writer = @buffers.writer
            writer.write_byte REQUEST_SUCCESS
            @session.send_message writer
          end
        end

        def do_request_success( response )
          @log.debug "REQUEST_SUCCESS received" if @log.debug?
          process_request response, true
        end

        def do_request_failure( response )
          @log.debug "REQUEST_FAILURE received" if @log.debug?
          process_request response, false
        end

        def do_channel_open( response )
          ch_type = response.read_string
          @log.debug "CHANNEL_OPEN recieved (#{ch_type})" if @log.debug?
          handled = false

          sender_channel = response.read_long
          window_size = response.read_long
          packet_size = response.read_long

          channel = @factories[:create].call( ch_type, sender_channel,
                        window_size, packet_size )

          ( @channel_open_handlers[ ch_type ] || [] ).each do |handler|
            next unless handler
            handled = true
            handler.call( self, channel, response )
          end

          unless handled
            raise Net::SSH::Exception,
              "cannot handle request to open a channel of type '#{ch_type}'"
          end

          @channel_map[channel.local_id] = channel

          writer = @buffers.writer
          writer.write_byte CHANNEL_OPEN_CONFIRMATION
          writer.write_long channel.remote_id
          writer.write_long channel.local_id
          writer.write_long 0x7FFFFFFF
          writer.write_long 0x7FFFFFFF
          @session.send_message writer
        end

        def do_channel_open_failure( response )
          local_id = response.read_long
          reason_code = response.read_long
          reason = response.read_string
          language = response.read_string

          @log.debug "CHANNEL_OPEN_FAILURE recieved (#{reason})" if @log.debug?

          channel = @channel_map[ local_id ]
          @channel_map.delete local_id
          channel.do_confirm_failed reason_code, reason, language
        end

        def do_channel_open_confirmation( response )
          local_id = response.read_long
          remote_id = response.read_long
          window_size = response.read_long
          packet_size = response.read_long

          if @log.debug?
            @log.debug "CHANNEL_OPEN_CONFIRMATION recieved (#{local_id})"
          end

          channel = @channel_map[ local_id ]
          channel.do_confirm_open remote_id, window_size, packet_size
        end

        def do_channel_window_adjust( response )
          local_id = response.read_long
          bytes_to_add = response.read_long

          if @log.debug?
            @log.debug "CHANNEL_WINDOW_ADJUST recieved " +
              "(#{local_id}:#{bytes_to_add})"
          end

          @channel_map[ local_id ].do_window_adjust( bytes_to_add )
        end

        def do_channel_data( response )
          local_id = response.read_long
          data = response.read_string

          if @log.debug?
            @log.debug "CHANNEL_DATA recieved (#{local_id}:#{data.inspect})"
          end

          @channel_map[ local_id ].do_data data
        end

        def do_channel_extended_data( response )
          local_id = response.read_long
          data_type = response.read_long
          data = response.read_string

          if @log.debug?
            @log.debug "CHANNEL_EXTENDED_DATA recieved " +
              "(#{local_id}:#{data_type}:#{data.inspect})"
          end

          @channel_map[ local_id ].do_extended_data data_type, data
        end

        def do_channel_eof( response )
          local_id = response.read_long
          @log.debug "CHANNEL_EOF recieved (#{local_id})" if @log.debug?
          @channel_map[ local_id ].do_eof
        end

        def do_channel_close( response )
          local_id = response.read_long
          @log.debug "CHANNEL_CLOSE recieved (#{local_id})" if @log.debug?
          @channel_map[ local_id ].close false
        end

        def do_channel_request( response )
          local_id = response.read_long
          request = response.read_string
          want_reply = response.read_bool
          request_data = response.remainder_as_buffer

          if @log.debug?
            @log.debug "CHANNEL_REQUEST recieved (#{local_id}:#{request})"
          end

          @channel_map[ local_id ].do_request request, want_reply, request_data
        end

        def do_channel_success( response )
          local_id = response.read_long
          @log.debug "CHANNEL_SUCCESS recieved (#{local_id})" if @log.debug?
          @channel_map[ local_id ].do_success
        end

        def do_channel_failure( response )
          local_id = response.read_long
          @log.debug "CHANNEL_FAILURE recieved (#{local_id})" if @log.debug?
          @channel_map[ local_id ].do_failure
        end

        #--
        # ====================================================================
        # INTERNAL STATE MANAGEMENT
        # ====================================================================
        private
        #++

        # Process a response recived from a "global_request".
        def process_request( response, success )
          request = @request_queue.shift
          request.callback.call( success, response ) if request.callback
        end

        # Process all pending data requests.
        def process_data_requests
          # guard against recursive calls
          return if @processing_data_requests

          # guard against simultaneous calls
          @data_requests_mutex.synchronize do
            begin
              @processing_data_requests = true
              @data_requests.map! do |req|
                while req && req.channel.window_size > 0
                  remaining = if req.type
                      req.channel.send_extended_data_packet( req.type, req.data )
                    else
                      req.channel.send_data_packet( req.data )
                    end
                  if remaining
                    req.data = remaining
                  else
                    req = nil
                  end
                end

                req
              end
              @data_requests.compact!
            ensure
              @processing_data_requests = false
            end
          end
        end

        #--
        # ====================================================================
        # MESSAGE DISPATCHER SETUP
        # ====================================================================
        #++

        MESSAGES = %w(
          global_request
          request_success request_failure channel_open channel_open_failure
          channel_open_confirmation channel_window_adjust channel_data
          channel_extended_data channel_eof channel_close channel_request
          channel_success channel_failure
        ).inject({}) do |map, event|
          constant = Constants.const_get event.upcase.to_sym
          map[constant] = {
            :name => event.to_sym,
            :method => instance_method( "do_#{event}".to_sym )
          }
          map
        end

      end

    end
  end
end
