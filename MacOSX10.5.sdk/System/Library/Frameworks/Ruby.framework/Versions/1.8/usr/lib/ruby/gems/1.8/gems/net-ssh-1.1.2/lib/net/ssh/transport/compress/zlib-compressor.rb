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
require 'net/ssh/transport/compress/compressor'

module Net
  module SSH
    module Transport

      module Compress

        # The "zlib" compression algorithm.
        class ZLibCompressor < Compressor

          # Creates a new ZLibCompressor instance using the default
          # configuration options.
          def initialize
            init_deflater( Zlib::DEFAULT_COMPRESSION )
          end

          # Reconfigures this instance with the given Hash of options. The only
          # supported option is <tt>:level</tt>, which must be one of the Zlib
          # constants.
          def configure( options )
            init_deflater( options[:level] ) if options.has_key?(:level)
          end

          # Deflates the text using the Zlib deflate interface.
          def compress( text )
            @deflater.deflate( text, Zlib::SYNC_FLUSH )
          end

          # Reinitializes the internal deflater, using the given compression
          # level.
          def init_deflater( level )
            @deflater = Zlib::Deflate.new( level )
          end
          private :init_deflater

        end

      end

    end
  end
end
