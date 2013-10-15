#--
# =============================================================================
# Copyright (c) 2007, Chris Andrews (chris@nodnol.org),
#   Jamis Buck (jgb3@email.byu.edu)
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
      module AgentForward

        def register_services( container )

          container.namespace_define :agentforward do |ns|
            ns.driver :model => :singleton_deferred do |c,p|
              require 'net/ssh/service/agentforward/driver'
              Driver.new( c[:connection][:driver],
                          c[:transport][:buffers],
                          c[:log_for, p],
                          c[:userauth].agent)
            end
          end

        end
        module_function :register_services

      end
    end
  end
end
