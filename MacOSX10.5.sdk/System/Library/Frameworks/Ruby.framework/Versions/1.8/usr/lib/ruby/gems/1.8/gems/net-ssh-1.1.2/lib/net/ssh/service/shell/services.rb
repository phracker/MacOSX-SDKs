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
      module Shell

        def register_services( container )

          container.namespace_define :shell do |ns|

            ns.shell do |c,p|
              require 'net/ssh/service/shell/shell'
              connection = c[:connection][:driver]
              log = c[:log_for, p]
              lambda { |pty| Shell.new( connection, log, pty ) }
            end

            ns.sync do |c,p|
              require 'net/ssh/service/shell/sync'
              connection = c[:connection][:driver]
              log = c[:log_for, p]
              shell = c[:shell]
              lambda { |pty| SyncShell.new( shell, log, pty ) }
            end

            ns.driver do |c,p|
              require 'net/ssh/service/shell/driver'
              Driver.new( c[:log_for, p], c[:shell], c[:sync] )
            end

          end

        end
        module_function :register_services

      end
    end
  end
end
