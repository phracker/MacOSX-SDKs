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
require 'net/ssh/userauth/constants'

module Net
  module SSH
    module UserAuth
      module Methods

        # Implements the "publickey" SSH authentication method.
        class PublicKey
          include Net::SSH::UserAuth::Constants

          # The messenger instance to use to send and receive messages
          attr_writer :messenger

          # The session id of the current SSH session
          attr_writer :session_id

          # Create a new PublicKey instance that uses the given buffer
          # factory to produce new buffer instances.
          def initialize( buffers )
            @buffers = buffers
          end

          # Attempts to perform public-key authentication for the given
          # username, trying each identity known to the key manager. If any of
          # them succeed, returns +true+, otherwise returns +false+. The data
          # hash must contain a UserKeyManager instance under the
          # <tt>:key_manager</tt> key.
          def authenticate( next_service, username, data={} )
            key_manager = data[:key_manager]
            return false unless key_manager

            key_manager.identities.each do |identity|
              return true if authenticate_with( identity, next_service,
                username, key_manager )
            end

            return false

          ensure
            key_manager.finish if key_manager
          end

          # Builds a Net::SSH::Util::WriterBuffer that contains the request
          # formatted for sending a public-key request to the server.
          def build_request( pub_key, username, next_service, has_sig,
                buffer=nil )
          # begin
            buffer ||= @buffers.writer

            buffer.write_byte USERAUTH_REQUEST
            buffer.write_string username
            buffer.write_string next_service
            buffer.write_string "publickey"
            buffer.write_bool has_sig
            buffer.write_string pub_key.ssh_type

            blob = @buffers.writer
            blob.write_key pub_key
            buffer.write_string blob.to_s

            return buffer
          end
          private :build_request

          # Builds and sends a request formatted for a public-key
          # authentication request.
          def send_request( pub_key, username, next_service, signature=nil )
            msg = build_request( pub_key, username, next_service, signature )
            msg.write_string signature if signature
            @messenger.send_message msg
          end
          private :send_request

          # Attempts to perform public-key authentication for the given
          # username, with the given identity (public key). Returns +true+ if
          # successful, or +false+ otherwise.
          def authenticate_with( identity, next_service, username, key_manager )
            send_request identity, username, next_service

            message = @messenger.wait_for_message

            case message.message_type
              when USERAUTH_PK_OK
                sig_data = @buffers.writer
                sig_data.write_string @session_id
                build_request identity, username, next_service, true, sig_data

                sig_blob = key_manager.sign( identity, sig_data )

                send_request identity, username, next_service, sig_blob.to_s
                message = @messenger.wait_for_message

                case message.message_type
                  when USERAUTH_SUCCESS
                    return true
                  when USERAUTH_FAILURE
                    return false
                  else
                    raise Net::SSH::Exception,
                      "unexpected server response to USERAUTH_REQUEST: " +
                      message.inspect
                end

              when USERAUTH_FAILURE
                return false

              else
                raise Net::SSH::Exception,
                  "unexpected reply to USERAUTH_REQUEST: #{message.inspect}"
            end
          end
          private :authenticate_with

        end

      end
    end
  end
end
