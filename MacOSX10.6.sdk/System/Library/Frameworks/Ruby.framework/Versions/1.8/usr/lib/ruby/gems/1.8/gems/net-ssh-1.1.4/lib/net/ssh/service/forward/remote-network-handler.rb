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

require 'socket'

module Net
  module SSH
    module Service
      module Forward

        # A helper class for managing ports forwarded from a remote host to
        # the local host.
        class RemoteNetworkHandler

          # Instantiate a new RemoteNetworkHandler instance that will forward
          # data to the given local port and host address.
          def initialize( log, block_size, local_port, local_host='127.0.0.1' )
            @log = log
            @block_size = block_size
            @local_port = local_port
            @local_host = local_host
          end

          # Opens a new socket to the local host and port given when the
          # handler was created, and forwards data from the channel to that
          # connection.
          def on_open( channel, c_addr, c_port, o_addr, o_port )
            @client = TCPSocket.new( @local_host, @local_port )

            Thread.new do
              begin
                loop do
                  break if channel[:eof]
                  data = ""
                  while IO.select([@client],nil,nil,0.01)
                    data << @client.recv(@block_size)
                  end
                  channel.send_data data unless data.empty?
                end
              rescue Exception => e
                @log.error "error while forwarding remote port: " +
                  "#{e.class}: #{e.message}\n  " +
                  e.backtrace.join( "\n  " )
              ensure
                channel.close
              end
            end
          end

          # Invoked when the channel indicates that the end is near.
          def on_eof( channel )
            channel[:eof] = true
          end

          # Invoked when the channel is closed.
          def on_close( channel )
            @client.shutdown
          end

          # Invoked when data is received over the channel.
          def on_receive( channel, data )
            @client.send data, 0
          end

        end

      end
    end
  end
end
