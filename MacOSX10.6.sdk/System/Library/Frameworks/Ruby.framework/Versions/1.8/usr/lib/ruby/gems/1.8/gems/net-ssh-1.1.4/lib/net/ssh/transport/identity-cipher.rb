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

      # A cipher that does nothing but pass the data through, unchanged. This
      # keeps things in the code nice and clean when a cipher has not yet been
      # determined (i.e., during key exchange).
      class IdentityCipher
        
        # A default block size of 8 is required by the SSH2 protocol.
        def block_size
          8
        end

        # Does nothing. Returns self.
        def encrypt
          self
        end

        # Does nothing. Returns self.
        def decrypt
          self
        end

        # Passes its single argument through unchanged.
        def update( text )
          text
        end

        # Returns the empty string.
        def final
          ""
        end

        # The name of this cipher, which is "identity".
        def name
          "identity"
        end
      end

    end

  end
end
