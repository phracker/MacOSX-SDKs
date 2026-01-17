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

require 'zlib'
require 'net/ssh/transport/compress/decompressor'

module Net
  module SSH
    module Transport

      module Compress

        # The "zlib" decompression algorithm.
        class ZLibDecompressor < Decompressor

          # Creates a new ZLibDecompressor.
          def initialize
            init_inflater
          end

          # Decompresses the text using the "inflate" Zlib algorithm.
          def decompress( text )
            @inflater.inflate( text )
          end

          # Reinitializes the internal inflater using the default number of
          # window bits.
          def init_inflater
            @inflater = Zlib::Inflate.new( nil )
          end
          private :init_inflater

        end

      end

    end
  end
end
