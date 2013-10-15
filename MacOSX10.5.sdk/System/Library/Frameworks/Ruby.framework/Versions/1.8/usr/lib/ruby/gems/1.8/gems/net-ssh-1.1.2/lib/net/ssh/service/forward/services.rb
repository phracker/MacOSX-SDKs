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
      module Forward

        # Register the services pertaining to port forwarding.
        def register_services( container )

          # All port forwarding services go in the :forward namespace.
          container.namespace_define :forward do |ns|

            # The :driver service manages all port forwarding. It is declared
            # as deferred so that it is not actually instantiated until it is
            # used--otherwise, it would be instantiated as soon as it was added
            # to the list of available services, whether it was ever used or
            # not.
            ns.driver :model => :singleton_deferred do |c,p|
              require 'net/ssh/service/forward/driver'
              Driver.new( c[:connection][:driver],
                          c[:transport][:buffers],
                          c[:log_for, p],
                          :local => c[:local_network_handler],
                          :remote => c[:remote_network_handler] )
            end

            # A constant service, used to indicate the maximum block size to be
            # passed over a forwarded connection.
            ns.read_block_size { 64 * 1024 }

            # The :local_network_handler service returns a proc object that
            # creates new LocalNetworkHandler instances for a given client
            # connection. This is used for forwarding ports on the local host.
            ns.local_network_handler :model => :singleton_deferred do |c,p|
              require 'net/ssh/service/forward/local-network-handler'
              log = c[:log_for, p]
              block_size = c[:read_block_size]
              lambda do |client|
                LocalNetworkHandler.new( log, block_size, client )
              end
            end

            # The :remote_network_handler service returns a proc object that
            # creates new RemoteNetworkHandler instances for a given port and
            # host. This is used for forwarding ports on a remote host.
            ns.remote_network_handler :model => :singleton_deferred do |c,p|
              require 'net/ssh/service/forward/remote-network-handler'
              log = c[:log_for, p]
              block_size = c[:read_block_size]
              lambda do |port, host|
                RemoteNetworkHandler.new( log, block_size, port, host )
              end
            end
          end
        end
        module_function :register_services

      end
    end
  end
end
