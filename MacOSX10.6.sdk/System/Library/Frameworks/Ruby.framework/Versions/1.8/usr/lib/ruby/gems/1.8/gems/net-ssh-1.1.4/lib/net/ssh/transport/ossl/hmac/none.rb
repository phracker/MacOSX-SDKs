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

require 'net/ssh/transport/ossl/hmac/hmac'

module Net
  module SSH
    module Transport
      module OSSL

        module HMAC

          # The "none" algorithm. This has a key and mac length of 0.
          class None < Abstract

            # Create a new instance of the None HMAC algorithm.
            def initialize
              @key_length = @mac_length = 0
            end

            # Always returns the empty string.
            def digest( data )
              ""
            end

          end

        end

      end
    end
  end
end
