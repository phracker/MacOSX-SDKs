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
      module Process

        # Register all services pertaining to the management of remote
        # processes.
        def register_services( container )

          # All process management services are registered in their own
          # namespace.
          container.namespace_define :process do |ns|

            # The :open_manager service returns a proc object that can be used
            # to create new OpenManager instances for a given command.
            ns.open_manager do |c,p|
              require 'net/ssh/service/process/open'
              connection = c[:connection][:driver]
              log = c[:log_for, p]
              lambda { |cmd| OpenManager.new( connection, log, cmd ) }
            end

            # The :popen3_manager service returns a new POpen3Manager instance
            # for managing the execution of commands with a popen3-type
            # interface.
            ns.popen3_manager do |c,p|
              require 'net/ssh/service/process/popen3'
              connection = c[:connection][:driver]
              log = c[:log_for, p]
              POpen3Manager.new( connection, log )
            end

            # The :driver controls access to all remote process management
            # services.
            ns.driver do |c,p|
              require 'net/ssh/service/process/driver'
              Driver.new( c[:connection][:driver],
                          c[:log_for, p],
                          :open => c[:open_manager],
                          :popen3 => c[:popen3_manager] )
            end

          end
        end
        module_function :register_services

      end
    end
  end
end
