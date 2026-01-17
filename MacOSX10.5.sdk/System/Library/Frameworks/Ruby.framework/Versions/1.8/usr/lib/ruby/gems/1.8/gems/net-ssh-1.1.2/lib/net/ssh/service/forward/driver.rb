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

require 'net/ssh/errors'

module Net
  module SSH
    module Service
      module Forward

        # The Forward::Driver class manages ports that have been forwarded.
        # It will open a socket on each local port and listen for local
        # connections, forwarding those connections over an SSH channel to
        # the other end.
        class Driver
          
          # The number of direct (local-to-remote) channels that have been
          # opened.
          attr_reader :direct_channel_count

          # The number of direct (local-to-remote) channels that are currently
          # open.
          attr_reader :open_direct_channel_count

          # Create a new Driver instance.
          def initialize( connection, buffers, log, handlers )
            @connection = connection
            @buffers = buffers
            @log = log
            @handlers = handlers

            @local_forwards = Hash.new
            @remote_forwards = Hash.new
            @direct_channel_count = 0
            @open_direct_channel_count = 0

            @connection.add_channel_open_handler(
              "forwarded-tcpip", &method(:do_open_channel) )
          end

          # Open a direct "tcpip" channel to the remote machine, which will then
          # forward the connection to the given remote-host and remote-port. The
          # connection will appear to have come from the given port on the local
          # machine.
          #
          # The handler object may respond to the following messages, in order
          # to respond to requests over the channel:
          #
          # * on_receive( channel, data ): when data is received over the
          #   channel (from the remote machine), this method will be invoked.
          # * on_eof( channel ): when the remote machine will no longer send
          #   data, this method will be invoked. The client may continue to send
          #   data over the channel, however.
          # * on_close( channel ): when the channel has been closed and is no
          #   longer valid for passing data, this method will be invoked.
          # * confirm( channel, local_port, remote_host, remote_port, *data ):
          #   when the channel has been opened and the remote machine has
          #   confirmed it, this method will be invoked. The +data+ parameters
          #   are the same parameters as were passed to the direct_channel
          #   method.
          # * process( channel ): invoked after the channel is confirmed, to
          #   process the channel. It is invoked in a new Thread.
          #
          # Only the +process+ method is required--the others will only be
          # invoked if the handler responds to them.
          def direct_channel( local_port, remote_host, remote_port,
            handler, *data )
          # begin
            writer = @buffers.writer
            writer.write_string remote_host
            writer.write_long remote_port.to_i
            writer.write_string "127.0.0.1"
            writer.write_long local_port.to_i

            @direct_channel_count += 1
            @open_direct_channel_count += 1

            if @log.debug?
              @log.debug "opening direct channel for " +
                "#{local_port}:#{remote_host}:#{remote_port}"
            end

            c = @connection.open_channel( 'direct-tcpip', writer ) do |channel|
              if @log.debug?
                @log.debug "direct channel confirmed for " +
                  "#{local_port}:#{remote_host}:#{remote_port}"
              end

              if handler.respond_to?( :on_receive )
                channel.on_data( &handler.method(:on_receive) )
              end

              if handler.respond_to?( :on_eof )
                channel.on_eof( &handler.method(:on_eof) )
              end

              channel.on_close do |ch|
                @open_direct_channel_count -= 1
                handler.on_close( ch ) if handler.respond_to?( :on_close )
              end

              if handler.respond_to?( :confirm )
                handler.confirm( channel, local_port, remote_host,
                  remote_port, *data )
              end

              if handler.respond_to?( :process )
                Thread.new { handler.process( channel ) }
              end
            end

            c.on_confirm_failed do |channel, code,desc,lang|
              raise Net::SSH::Exception, "could not open direct channel for " +
                "#{local_port}:#{remote_host}:#{remote_port} (#{code}, #{desc})"
            end

            nil
          end
          
          # Forward connections on the given local port, to the given remote
          # host and remote port. 
          #
          # This method will return immediately, forwarding the connections
          # asynchronously.
          def local( *args )
            if args.length < 3 || args.length > 4
              raise ArgumentError,
                "expected 3 or 4 parameters, got #{args.length+1}"
            end

            bind_address = "127.0.0.1"
            bind_address = args.shift if args.first.is_a? String

            local_port = args.shift.to_i
            remote_host = args.shift
            remote_port = args.shift

            key = [ local_port.to_i, bind_address ]

            if @log.debug?
              @log.debug "starting local forwarding server on " +
                key.inspect
            end

            socket = TCPServer.new( bind_address, local_port )

            Thread.new do
              begin
                @local_forwards[ key ] = { :thread => Thread.current,
                                           :socket => socket }

                if @log.debug?
                  @log.debug "listening for connections on #{key.inspect}"
                end

                while ( client = socket.accept )
                  @log.debug "#{key.inspect} received connection" if @log.debug?

                  direct_channel( local_port,
                                  remote_host,
                                  remote_port,
                                  @handlers[:local].call( client ) )
                end

              rescue Exception => e
                @log.error "error forwarding local connection: " +
                  "#{e.class} (#{e.message})\n   " +
                  e.backtrace.join( "\n  " )
              end
            end
          end

          # Initiate forwarding of the given remote port on the connected host.
          # Forwarded packets will be passed to the given block as they are
          # recieved. The remote-host represents the address that should be
          # bound on the remote host, and defaults to '127.0.0.1'.
          def remote( handler, remote_port, remote_host="127.0.0.1" )
            if @remote_forwards[ remote_port ]
              raise Net::SSH::Exception, "#{remote_port} is already forwarded"
            end

            writer = @buffers.writer
            writer.write_string remote_host
            writer.write_long remote_port.to_i

            @connection.global_request( "tcpip-forward", writer
            ) do |success, response|
              if success
                remote_port = response.read_long if remote_port == 0
                @remote_forwards[ remote_port ] = { :port => remote_port,
                                                    :handler => handler }
                handler.setup( remote_port ) if handler.respond_to?( :setup )
              else
                msg = "remote port #{remote_port} could not be forwarded " +
                      "to local host"
                if handler.respond_to?( :error )
                  handler.error( msg )
                else
                  raise Net::SSH::Exception, msg
                end
              end
            end
          end

          # A convenience method for setting up a forwarded connection from the
          # given port on the remote host, to the given host and port (local).
          def remote_to( port, host, remote_port, remote_host="127.0.0.1" )
          # begin
            remote( @handlers[:remote].call( port, host ), remote_port,
              remote_host )
          end

          # Return an array of the active forwarded local connections. Each
          # element of the array is another array containing the local port, and
          # the remote host and port of the connection.
          def active_locals
            @local_forwards.keys
          end

          # Return an array of the active forwarded remote connections. Each
          # element of the array is an integer representing the port number of
          # the remote host that is being forwarded to the local client.
          def active_remotes
            @remote_forwards.keys
          end

          # Cease forwarding connections from the given local port (and
          # interface). The parameters must match those given to a prior call to
          # #local. Existing forwarded connections are not affected by
          # this call, but no more connections will be accepted on the local
          # port.
          def cancel_local( local_port, bind_address="127.0.0.1" )
            key = [ local_port.to_i, bind_address ]

            forward = @local_forwards[ key ]
            @local_forwards.delete key

            forward[ :socket ].shutdown
            forward[ :thread ].terminate

            true
          end

          # Cease forwarding connections from the given remote port. The
          # +remote_host+ parameter must match the corresponding parameter that
          # was passed to #remote. Existing forwarded connections are
          # not affected by this call, but no more connections will be
          # forwarded from the remote host to the local host via that port.
          def cancel_remote( remote_port, remote_host="127.0.0.1" )
            writer = @buffers.writer
            writer.write_string remote_host
            writer.write_long remote_port.to_i

            @connection.global_request( "cancel-tcpip-forward", writer
            ) do |success, response|
              if success
                @remote_forwards.delete remote_port
              else
                raise Net::SSH::Exception,
                  "could not cancel remote forward request on " +
                  "(#{remote_port},#{remote_host})"
              end
            end
          end

          # open a new channel as requested by the server
          def do_open_channel( connection, channel, data )
            connected_address = data.read_string
            connected_port = data.read_long
            originator_address = data.read_string
            originator_port = data.read_long

            forward_data = @remote_forwards[ connected_port ]
            unless forward_data
              raise Net::SSH::Exception,
                "recieved invalid channel-open command for a port forward " +
                "that was never requested"
            end

            handler = forward_data[:handler]

            forward_data[:channel] = channel

            if handler.respond_to?( :on_open )
              handler.on_open( channel,
                               connected_address, connected_port,
                               originator_address, originator_port )
            end

            channel.on_data( &handler.method(:on_receive) )

            if handler.respond_to?( :on_close )
              channel.on_close( &handler.method(:on_close) )
            end

            if handler.respond_to?( :on_eof )
              channel.on_eof( &handler.method(:on_eof) )
            end
          end

        end

      end # Forward
    end # Service
  end # SSH
end # Net
