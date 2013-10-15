#--
# =============================================================================
# Copyright (c) 2007, Chris Andrews (chris@nodnol.org),
#   Jamis Buck (jgb3@email.byu.edu)
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
      module AgentForward

        class Driver

          def initialize( connection, buffers, log, agent )
            @connection = connection
            @buffers = buffers
            @log = log
            @agent = agent
            @data = ''

            @connection.add_channel_open_handler(
              "auth-agent@openssh.com", &method(:do_open_channel) )
          end

          def request
            @connection.channel_request( 'auth-agent-req@openssh.com' )
          end

          def do_open_channel( connection, channel, data )
            channel.on_data(&method(:do_data))
          end

          # handle CHANNEL_DATA packets received on the agent-forward
          # channel - pass complete received packets to the agent.
          def do_data( channel, data )
            @data = @data + data
            reply = call_agent
            if reply
              channel.send_data reply
              @data = ''
            end
          end
          
          # Called if we have any data to forward to the
          # agent. Examines the accumulated data to see if we have a
          # complete packet, based on the length field (the first four
          # bytes as a network long).
          def call_agent
            # if we have enough data to check the length of this packet
            if @data.length >= 4
              packet_length = @data[0..3].unpack('N').first
              # send the complete packet to the agent and read the
              # response
              if @data.length == (4 + packet_length)
                @agent.send_raw_packet @data
                buffer = @agent.read_raw_packet
              end
            end
            buffer
          end

        end

      end # AgentForward
    end # Service
  end # SSH
end # Net
