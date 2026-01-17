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

require 'net/ssh'

module Net
  module SSH
    module Service

      # Register all standard SSH services.
      def register_services( container )

        # Define the hash that will be used to record the registered services.
        # If the hash already exists, don't redefine it.
        unless container.knows_key?( :services )
          container.define.services { Hash.new }
        end

        # Register the services in their own namespace.
        container.namespace_define :service do |ns|
          ns.require "net/ssh/service/forward/services", "#{self}::Forward"
          ns.require "net/ssh/service/process/services", "#{self}::Process"
          ns.require "net/ssh/service/shell/services", "#{self}::Shell"
          ns.require "net/ssh/service/agentforward/services", "#{self}::AgentForward"
        end

        # Add the services to the services hash.
        container.services[ :forward ] = container.service.forward.driver
        container.services[ :process ] = container.service.process.driver
        container.services[ :shell ] = container.service.shell.driver
        container.services[ :agentforward ] = container.service.agentforward.driver

        # Register the external services and add them to the collection of
        # known services.
        EXTERNAL_SERVICES.each do |name, block|
          container.service.register( name,
            :model => :singleton_deferred,
            &block )
          container.services[ name ] = container.service[ name ]
        end

      end
      module_function :register_services

    end
  end
end
