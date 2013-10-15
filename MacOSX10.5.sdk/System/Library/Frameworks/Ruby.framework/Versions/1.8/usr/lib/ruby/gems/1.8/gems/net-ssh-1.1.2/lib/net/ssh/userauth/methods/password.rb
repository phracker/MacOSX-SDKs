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

        # Implements the "password" SSH authentication method.
        class Password
          include Net::SSH::UserAuth::Constants

          # The messenger to use when communicating.
          attr_writer :messenger

          # Create a new Password authenticator. It will use the given buffers
          # factory to create new buffer instances.
          def initialize( buffers )
            @buffers = buffers
          end

          # Attempt to authenticate the given user for the given service. The
          # data hash must specify a <tt>:password</tt> value, otherwise this
          # will always return false.
          def authenticate( next_service, username, data={} )
            return false unless data[:password]

            msg = @buffers.writer
            msg.write_byte USERAUTH_REQUEST
            msg.write_string username
            msg.write_string next_service
            msg.write_string "password"
            msg.write_bool false
            msg.write_string data[:password]
            @messenger.send_message msg

            message = @messenger.wait_for_message

            case message.message_type
              when USERAUTH_SUCCESS
                return true
              when USERAUTH_FAILURE, USERAUTH_PASSWD_CHANGEREQ
                return false
              else
                raise Net::SSH::Exception,
                  "unexpected reply to USERAUTH_REQUEST: #{message.inspect}"
            end
          end
        end

      end
    end
  end
end
