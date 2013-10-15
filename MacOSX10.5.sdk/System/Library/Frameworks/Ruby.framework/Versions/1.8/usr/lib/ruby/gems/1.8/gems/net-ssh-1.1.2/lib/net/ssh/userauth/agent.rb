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
require 'net/ssh/transport/session'

module Net
  module SSH
    module UserAuth

      # A trivial exception class for representing agent-specific errors.
      class AgentError < Net::SSH::Exception; end

      # This class implements a simple client for the ssh-agent protocol. It
      # does not implement any specific protocol, but instead copies the
      # behavior of the ssh-agent functions in the OpenSSH library (3.8).
      #
      # This means that although it behaves like a SSH1 client, it also has
      # some SSH2 functionality (like signing data).
      class Agent
        SSH2_AGENT_REQUEST_VERSION    = 1
        SSH2_AGENT_REQUEST_IDENTITIES = 11
        SSH2_AGENT_IDENTITIES_ANSWER  = 12
        SSH2_AGENT_SIGN_REQUEST       = 13
        SSH2_AGENT_SIGN_RESPONSE      = 14
        SSH2_AGENT_FAILURE            = 30
        SSH2_AGENT_VERSION_RESPONSE   = 103

        SSH_COM_AGENT2_FAILURE        = 102

        SSH_AGENT_REQUEST_RSA_IDENTITIES = 1
        SSH_AGENT_RSA_IDENTITIES_ANSWER  = 2
        SSH_AGENT_FAILURE                = 5

        # The socket factory used to connect to the agent process. It must
        # respond to #open, and accept a single parameter (the name of the
        # socket to open).
        attr_writer :socket_factory

        # The name of the socket to open.
        attr_writer :socket_name

        # The version of the SSH protocol version to report.
        attr_writer :version

        # The buffer factory to use to obtain buffer instances.
        attr_writer :buffers

        # The key factory to use to obtain key instances.
        attr_writer :keys

        # Connect to the agent process using the socket factory and socket name
        # given by the attribute writers. If the agent on the other end of the
        # socket reports that it is an SSH2-compatible agent, this will fail
        # (it only supports the ssh-agent distributed by OpenSSH).
        def connect!
          @socket = @socket_factory.open( @socket_name )

          # determine what type of agent we're communicating with
          buffer = @buffers.writer
          buffer.write_string Net::SSH::Transport::Session.version
          type, body = send_with_reply SSH2_AGENT_REQUEST_VERSION, buffer

          if type == SSH2_AGENT_VERSION_RESPONSE
            raise NotImplementedError, "SSH2 agents are not yet supported"
          elsif type != SSH_AGENT_RSA_IDENTITIES_ANSWER
            raise AgentError,
              "unknown response from agent: #{type}, #{body.to_s.inspect}"
          end
        end

        # Return an array of all identities (public keys) known to the agent.
        # Each key returned is augmented with a +comment+ property which is set
        # to the comment returned by the agent for that key.
        def identities
          case @version
            when 1
              code1 = SSH_AGENT_REQUEST_RSA_IDENTITIES
              code2 = SSH_AGENT_RSA_IDENTITIES_ANSWER
            when 2
              code1 = SSH2_AGENT_REQUEST_IDENTITIES
              code2 = SSH2_AGENT_IDENTITIES_ANSWER
            else
              raise NotImplementedError, "SSH version #{@version}"
          end

          type, body = send_with_reply code1
          raise AgentError,
            "could not get identity count" if agent_failed( type )
          raise AgentError, "bad authentication reply: #{type}" if type != code2

          identities = []
          body.read_long.times do
            case @version
              when 1
                key = @keys.get( "rsa" )
                bits = body.read_long
                key.e = body.read_bignum
                key.n = body.read_bignum
              when 2
                blob = @buffers.reader( body.read_string )
                key = blob.read_key
            end

            unless key.respond_to?( :comment= )
              key.instance_eval <<-EVAL
                def comment=(cmt)
                  @comment = cmt
                end
              EVAL
            end

            unless key.respond_to?( :comment )
              key.instance_eval <<-EVAL
                def comment
                  @comment
                end
              EVAL
            end

            key.comment = body.read_string
            identities.push key
          end

          return identities
        end

        # Closes this socket. This agent reference is no longer able to
        # query the agent.
        def close
          @socket.close
        end

        # Using the agent and the given public key, sign the given data. The
        # signature is returned in SSH2 format.
        def sign( key, data )
          blob = @buffers.writer
          blob.write_key key

          packet_data = @buffers.writer
          packet_data.write_string blob.to_s
          packet_data.write_string data.to_s
          packet_data.write_long 0

          type, reply = send_with_reply SSH2_AGENT_SIGN_REQUEST, packet_data
          if agent_failed( type )
            raise AgentError,
              "agent could not sign data with requested identity"
          elsif type != SSH2_AGENT_SIGN_RESPONSE
            raise AgentError, "bad authentication response #{type}"
          end

          return reply.read_string
        end

        # Send a new packet of the given type, with the associated data.
        def send_packet( type, data=nil )
          buffer = @buffers.writer
          buffer.write_long( ( data ? data.length : 0 ) + 1 )
          buffer.write_byte type.to_i
          buffer.write data.to_s if data
          @socket.send buffer.to_s, 0
        end
        private :send_packet

        # Read the next packet from the agent. This will return a two-part
        # tuple consisting of the packet type, and the packet's body (which
        # is returned as a Net::SSH::Util::ReaderBuffer).
        def read_packet
          length = @socket.read( 4 ).unpack( "N" ).first - 1
          type = @socket.read( 1 ).unpack( "C" ).first
          reader = @buffers.reader( @socket.read( length ) )
          return type, reader
        end
        private :read_packet

        # Send the given packet and return the subsequent reply from the agent.
        # (See #send_packet and #read_packet).
        def send_with_reply( type, data=nil )
          send_packet type, data
          read_packet
        end
        private :send_with_reply

        # Returns +true+ if the parameter indicates a "failure" response from
        # the agent, and +false+ otherwise.
        def agent_failed( type )
          type == SSH_AGENT_FAILURE ||
          type == SSH2_AGENT_FAILURE ||
          type == SSH_COM_AGENT2_FAILURE
        end
        private :agent_failed

        def send_raw_packet( data )
          @socket.send data, 0
        end
        
        def read_raw_packet
          buffer = @socket.read( 4 )
          length = buffer.unpack( "N" ).first
          buffer = buffer + @socket.read( length )
          buffer
        end

      end

    end
  end
end
