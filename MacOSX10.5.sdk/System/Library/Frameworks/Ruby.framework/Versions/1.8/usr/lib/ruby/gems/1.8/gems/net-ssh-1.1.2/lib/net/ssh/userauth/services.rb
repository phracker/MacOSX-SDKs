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

      def register_services( container )
        container.namespace_define :userauth do |b|

          b.require 'net/ssh/userauth/methods/services', "#{self}::Methods"

          b.agent_socket_factory do
            if File::ALT_SEPARATOR
              require 'net/ssh/userauth/pageant'
              Pageant::Socket
            else
              require 'socket'
              defined?( UNIXSocket ) ? UNIXSocket : nil
            end
          end

          b.default_agent_socket_name { ENV['SSH_AUTH_SOCK'] }

          b.default_agent_version { 2 }
          
          b.agent( :model => :prototype ) do |c,p|
            socket_factory = c[:agent_socket_factory]
            socket_name = c[:default_agent_socket_name]

            if (File::ALT_SEPARATOR || socket_name) && socket_factory
              require 'net/ssh/userauth/agent'
              require 'net/ssh/transport/services'

              agent = Agent.new
              agent.socket_factory = socket_factory
              agent.socket_name = socket_name
              agent.version = c[:default_agent_version]
              agent.buffers = c[:transport][:buffers]
              agent.keys = c[:transport][:keys]
              
              begin
                agent.connect!
              rescue Net::SSH::Exception
                # if there was an error connecting to the agent, swallow the
                # error and move on, without the agent
                agent = nil
              end
            end

            agent
          end

          b.agent_factory do |c,p|
            factory = Object.new
            klass = class << factory; self; end
            klass.send( :define_method, :open ) { c[:agent] }
            factory
          end

          b.default_user_key_locations do
            [ "#{ENV['HOME']}/.ssh/id_dsa",
              "#{ENV['HOME']}/.ssh2/id_dsa",
              "#{ENV['HOME']}/.ssh/id_rsa",
              "#{ENV['HOME']}/.ssh2/id_rsa" ]
          end

          b.default_host_key_locations do
            [ "/etc/ssh/ssh_host_dsa_key",
              "/etc/ssh/ssh_host_rsa_key" ]
          end

          b.key_existence_tester { File }

          b.user_keys do |c,p|
            require 'net/ssh/userauth/userkeys'

            userkeys = UserKeyManager.new
            userkeys.agent_factory = c[:agent_factory]
            userkeys.keys = c[:transport][:keys]
            userkeys.buffers = c[:transport][:buffers]
            userkeys.log = c[:log_for, p]
            userkeys.key_existence_tester = b.key_existence_tester

            b.default_user_key_locations.each { |f| userkeys.add f }
            b.default_host_key_locations.each { |f| userkeys.add_host_key f }

            userkeys
          end

          b.authentication_method_order do
            [ "publickey",
              "hostbased",
              "password",
              "keyboard-interactive" ]
          end

          b.driver do |c,p|
            require 'net/ssh/userauth/driver'

            driver = Driver.new( c[:log_for, p],
                                 c[:transport][:buffers],
                                 c[:methods],
                                 c[:authentication_method_order] )

            driver.key_manager = c[:user_keys]
            driver.session = c[:transport][:session]

            if c.knows_key?(:userauth_keys) && c[:userauth_keys]
              driver.set_key_files c[:userauth_keys]
            end
            if c.knows_key?(:userauth_host_keys) && c[:userauth_host_keys]
              driver.set_host_key_files c[:userauth_host_keys]
            end
            if c.knows_key?(:userauth_method_order) && c[:userauth_method_order]
              driver.set_auth_method_order(*c[:userauth_method_order])
            end

            driver
          end

        end
      end
      module_function :register_services

    end
  end
end
