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

        # Implements the "keyboard-interactive" SSH authentication method.
        class KeyboardInteractive
          include Net::SSH::UserAuth::Constants

          # Represents an information request from the server
          InfoRequest = Struct.new( :name, :instruction, :password, :prompts )

          # Represents a single prompt in an InfoRequest.
          Prompt = Struct.new( :prompt, :echo )

          USERAUTH_INFO_REQUEST  = 60
          USERAUTH_INFO_RESPONSE = 61

          # The messenger to use when communicating.
          attr_writer :messenger

          # Create a new Password authenticator. It will use the given buffers
          # factory to create new buffer instances. The +callback+ should be
          # a proc object to use to specialize the behavior of this
          # authentication method.
          def initialize( buffers, callback )
            @buffers = buffers
            @callback = callback
          end

          # Attempt to authenticate the given user for the given service. The
          # data hash must specify a <tt>:password</tt> value, otherwise this
          # will always return false.
          def authenticate( next_service, username, data={} )
            password = data[:password]

            msg = @buffers.writer
            msg.write_byte USERAUTH_REQUEST
            msg.write_string username
            msg.write_string next_service
            msg.write_string "keyboard-interactive"
            msg.write_string ""
            msg.write_string ""
            @messenger.send_message msg

            loop do
              message = @messenger.wait_for_message

              case message.message_type
                when USERAUTH_SUCCESS
                  return true
                when USERAUTH_FAILURE
                  return false
                when USERAUTH_INFO_REQUEST
                  name = message.buffer.read_string
                  instruction = message.buffer.read_string
                  req = InfoRequest.new( name, instruction, password, [] )
                  password = nil # only use the given password once

                  lang_tag = message.buffer.read_string
                  message.buffer.read_long.times do
                    prompt = message.buffer.read_string
                    echo = message.buffer.read_bool
                    req.prompts << Prompt.new( prompt, echo )
                  end

                  responses = @callback.call( req )
                  msg = @buffers.writer
                  msg.write_byte USERAUTH_INFO_RESPONSE
                  msg.write_long responses.length
                  msg.write_string(*responses)
                  @messenger.send_message msg
                else
                  raise Net::SSH::Exception,
                    "unexpected reply in keyboard interactive: " +
                      message.inspect
              end
            end
          end
        end

      end
    end
  end
end
