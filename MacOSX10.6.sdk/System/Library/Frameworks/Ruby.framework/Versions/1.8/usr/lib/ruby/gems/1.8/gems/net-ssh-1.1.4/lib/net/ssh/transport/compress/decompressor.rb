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

      module Compress

        # The ancestor class of all decompression implementations.
        class Decompressor

          # Return a new instance just like the current instance, but
          # reconfigured with the given options.
          def new( options={} )
            obj = dup
            obj.configure( options )
            return obj
          end

          # Reconfigure the current instance with the given options (which
          # should be a Hash-like). Subclasses may override this method to
          # implement the desired functionality.
          def configure( options )
          end

          # Raises NotImplementedError. Subclasses must override this
          # method to implement the desired decompression functionality.
          def decompress( text )
            raise NotImplementedError,
              "subclasses must implement the 'decompress' method"
          end

        end

      end

    end
  end
end
