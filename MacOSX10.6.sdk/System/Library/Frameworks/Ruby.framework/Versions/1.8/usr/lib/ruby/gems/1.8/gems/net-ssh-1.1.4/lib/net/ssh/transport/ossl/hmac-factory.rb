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
require 'net/ssh/transport/errors'

module Net
  module SSH
    module Transport

      module OSSL

        # A factory class for returning new HMAC algorithm instances.
        class HMACFactory

          # Create a new instance of the HMACFactory that uses the given
          # Hash-like to map SSH2 HMAC algorithm names to instances of
          # factories that can instantiate those algorithms.
          def initialize( algorithms )
            @algorithms = algorithms
          end

          # Return a new instance of the HMAC algorithm for the given
          # name. If no such algorithm exists, a HMACAlgorithmNotFound error
          # will be raised.
          def get( name, key="" )
            algo = find_algorithm( name ) or
              raise HMACAlgorithmNotFound, name
              
            return algo.new( key )
          end

          # Return the key length of the named HMAC algorithm. If no such
          # algorithm exists, raise HMACAlgorithmNotFound.
          def get_key_length( name )
            algo = find_algorithm( name ) or
              raise HMACAlgorithmNotFound, name

            return algo.key_length
          end

          # Searches all registered algorithm sets for the one with the
          # given name. Returns +nil+ if no such algorithm exists.
          def find_algorithm( name )
            @algorithms.each do |set|
              return set[name] if set.has_key?( name )
            end

            nil
          end

        end

      end

    end
  end
end
