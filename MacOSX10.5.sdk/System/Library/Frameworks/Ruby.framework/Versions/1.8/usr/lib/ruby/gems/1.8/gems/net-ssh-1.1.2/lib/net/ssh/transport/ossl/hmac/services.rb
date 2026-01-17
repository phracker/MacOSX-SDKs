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
    module Transport
      module OSSL
        module HMAC

          # Register all services that implement the various support
          # HMAC algorithms.
          def register_services( container )
            container.namespace_define :hmac do |space|

              # Register each supported HMAC algorithm.
              %w{sha1 sha1-96 md5 md5-96}.each do |name|
                space.__send__( name.sub(/-/, "_").intern ) do
                  require "net/ssh/transport/ossl/hmac/#{name}"
                  const_get( name.upcase.sub(/-/, "_").intern ).new
                end
              end

              # The :none service is trivial--simply doing as much of nothing
              # as possible. This is for consistency in how HMAC's are handled,
              # since it is possible to not have an HMAC for part of the
              # communication cycle.
              space.none do
                require "net/ssh/transport/ossl/hmac/none"
                None.new
              end

              # Add the implementations to a hash, naming them according to the
              # SSH2 specification.
              space.collection do |c,|
                Hash[ "hmac-sha1"    => c.sha1,
                      "hmac-sha1-96" => c.sha1_96,
                      "hmac-md5"     => c.md5,
                      "hmac-md5-96"  => c.md5_96,
                      "none"         => c.none ]
              end

              # Add the collection of algorithms to the list of known HMAC
              # algorithm sources.
              if space.knows_key?( :hmac_algorithm_sources )
                space.hmac_algorithm_sources << space.collection
              end
            end
          end
          module_function :register_services

        end
      end
    end
  end
end
