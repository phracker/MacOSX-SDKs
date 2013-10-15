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

module Net
  module SSH
    module Service
      module Forward

        # This is a utility class used internally by Forward::Driver. It
        # manages the network server instance for each locally forwarded port,
        # and is passed as the handler to Driver#direct_channel by
        # Forward::Driver#forward_local. Other clients may desire to extend
        # this class and pass the modified class to
        # Forward::Driver#direct_channel for their own purposes, but in general
        # this class will rarely be used outside of Forward::Driver.
        class LocalNetworkHandler

          # Create a new LocalNetworkHandler for the given client connection.
          def initialize( log, block_size, client )
            @log = log
            @block_size = block_size
            @client = client
          end

          # Invoked when data is recieved from the channel. This method just
          # sends the data to the client connection.
          def on_receive( channel, data )
            @client.send data, 0
          end

          # Invoked when the remote end of the channel will no longer be
          # sending data. It may still receive data, however.
          def on_eof( channel )
            channel[:eof] = true
          end

          # Called to process the channel in a loop. It will repeatedly read
          # from the client and send the results across the channel.
          def process( channel )
            loop do
              break if channel[:eof]
              data = @client.recv(@block_size) or break
              channel.send_data data unless data.empty?
            end

            channel.close
          rescue StandardError, Exception => e
            @log.error "error processing connection: " +
              "#{e.class} (#{e.message})\n  " +
              e.backtrace.join("\n  ")
          end

        end

      end # Forward
    end # Service
  end # SSH
end # Net
