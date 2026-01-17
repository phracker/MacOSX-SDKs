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
    module UserAuth
      module Methods

        def register_services( container )
          container.namespace_define :methods do |b|

            b.password do |c,p|
              require 'net/ssh/userauth/methods/password'
              method = Password.new( c[:transport][:buffers] )
              method.messenger = c[:userauth][:driver]
              method
            end

            b.keyboard_interactive do |c,p|
              require 'net/ssh/userauth/methods/keyboard-interactive'
              method = KeyboardInteractive.new( c[:transport][:buffers],
                c[:keyboard_interactive_callback] )
              method.messenger = c[:userauth][:driver]
              method
            end

            b.keyboard_interactive_prompter do
              require 'net/ssh/util/prompter'
              Net::SSH::Util::Prompter.new
            end

            b.keyboard_interactive_callback do |c,p|
              proc do |req|
                if req.password
                  [ req.password ] * req.prompts.length
                else
                  responses = []
                  puts req.name unless req.name.empty?
                  puts req.instruction unless req.instruction.empty?
                  req.prompts.each do |prompt|
                    response = prompt.echo ?
                      gets.chomp :
                      c[:keyboard_interactive_prompter].
                        password( prompt.prompt )
                    responses << response
                  end
                  responses
                end
              end
            end

            b.publickey do |c,p|
              require 'net/ssh/userauth/methods/publickey'
              method = PublicKey.new( c[:transport][:buffers] )
              method.messenger = c[:userauth][:driver]
              method.session_id = c[:transport][:session].session_id
              method
            end

            b.hostbased do |c,p|
              require 'net/ssh/userauth/methods/hostbased'
              method = HostBased.new( c[:transport][:buffers] )
              session = c[:transport][:session]
              method.messenger = c[:userauth][:driver]
              method.hostname = session.client_name
              method.session_id = session.session_id
              method
            end
            
          end
        end
        module_function :register_services

      end
    end
  end
end
