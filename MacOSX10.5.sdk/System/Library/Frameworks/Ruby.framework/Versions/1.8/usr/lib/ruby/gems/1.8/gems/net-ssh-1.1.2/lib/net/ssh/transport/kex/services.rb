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

require 'openssl'

module Net
  module SSH
    module Transport
      module Kex

        # Register the services that perform key-exchanges.
        def register_services( container )
          container.namespace_define :kex do |b|

            # The :dh service is a standard Diffie-Hellman key exchange
            # algorithm using Group-1 and SHA-1.
            b.dh :model => :singleton_deferred do
              require 'net/ssh/transport/kex/dh'
              dh = DiffieHellmanGroup1SHA1.new( b.bns, b.digesters )
              dh.keys = b.keys
              dh.buffers = b.buffers
              dh.host_key_verifier = b.host_key_verifier
              dh
            end

            # The :dh_gex service is a standard Diffie-Hellman key exchange
            # algorithm using SHA-1 and a negotiated group.
            b.dh_gex :model => :singleton_deferred do
              require 'net/ssh/transport/kex/dh-gex'
              dh = DiffieHellmanGroupExchangeSHA1.new( b.bns, b.digesters )
              dh.keys = b.keys
              dh.buffers = b.buffers
              dh.host_key_verifier = b.host_key_verifier
              dh
            end

            # Add these services to the hash of available kex algorithms.
            b.kex_names.update(
              "diffie-hellman-group-exchange-sha1" => b.dh_gex,
              "diffie-hellman-group1-sha1" => b.dh
            )
          end
        end
        module_function :register_services

      end
    end
  end
end
