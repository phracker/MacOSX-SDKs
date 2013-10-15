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

require 'net/ssh/transport/errors'

module Net
  module SSH
    module Transport

      module OSSL

        # Implements a factory of OpenSSL digest algorithms.
        class DigestFactory
        
          # Create a new DigestFactory instance that uses the given Hash-like
          # to convert SSH2 digest algorithm names to OpenSSL digest algorithm
          # names.
          def initialize( digest_map )
            @digest_map = digest_map
          end

          # Return a factory that can implement the requested SSH2 digest
          # algorithm.
          def get( name )
            klass = @digest_map.fetch( name ) do
              raise DigestTypeNotFound, name
            end

            return klass
          end

        end

      end

    end
  end
end
