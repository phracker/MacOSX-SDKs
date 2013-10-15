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

        # Implements the host-based SSH authentication method.
        class HostBased
          include Net::SSH::UserAuth::Constants

          # The messenger to use to send and receive messages.
          attr_writer :messenger

          # The session-id of the current SSH session.
          attr_writer :session_id

          # The hostname to report to the server.
          attr_writer :hostname

          # Create a new 
          def initialize( buffers )
            @buffers = buffers
          end

          # Attempts to perform host-based authorization of the user. The data
          # hash must contain a <tt>:key_manager</tt> key or the call will
          # fail.
          def authenticate( next_service, username, data={} )
            key_manager = data[:key_manager] or return false

            key_manager.host_identities.each do |identity|
              return true if authenticate_with( identity, next_service,
                username, key_manager )
            end

            return false

          ensure
            key_manager.finish if key_manager
          end

          # Attempts to perform host-based authentication of the user, using
          # the given host identity (key).
          def authenticate_with( identity, next_service, username, key_manager )
            client_username = ENV['USER'] || username

            req = build_request identity, next_service, username,
              @hostname+".", client_username

            sig_data = @buffers.writer
            sig_data.write_string @session_id
            sig_data.write req

            sig = key_manager.sign( identity, sig_data.to_s )

            message = @buffers.writer
            message.write req
            message.write_string sig

            @messenger.send_message message
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
          end
          private :authenticate_with

          # Build the "core" hostbased request string.
          def build_request( identity, next_service, username, hostname,
               client_username )
          # begin
            buf = @buffers.writer
            buf.write_byte USERAUTH_REQUEST
            buf.write_string username
            buf.write_string next_service
            buf.write_string "hostbased"

            buf.write_string identity.ssh_type
            blob = @buffers.writer
            blob.write_key identity
            buf.write_string blob.to_s

            buf.write_string hostname
            buf.write_string client_username
            return buf.to_s
          end

        end

      end
    end
  end
end
