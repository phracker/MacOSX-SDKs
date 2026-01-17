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

require 'net/ssh/transport/ossl/hmac/sha1'
require 'openssl'

module Net
  module SSH
    module Transport
      module OSSL

        module HMAC

          # The SHA1-96 HMAC algorithm. This returns only the first 12 bytes of
          # the digest.
          class SHA1_96 < SHA1

            # Create a new instance of the SHA1-96 algorithm.
            def initialize
              super
              @mac_length = 12
            end

          end

        end

      end
    end
  end
end
