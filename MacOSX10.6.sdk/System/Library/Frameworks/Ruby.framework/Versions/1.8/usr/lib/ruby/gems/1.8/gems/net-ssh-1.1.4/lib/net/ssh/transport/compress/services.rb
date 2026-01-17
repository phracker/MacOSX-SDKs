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

        # Register all services that manage the compression and decompression
        # of data.
        def register_services( parent )

          # These services all go in their own namespace.
          parent.namespace_define :compress do |b|
            b.zlib_compressor do
              require 'net/ssh/transport/compress/zlib-compressor'
              ZLibCompressor.new
            end

            b.none_compressor do
              require 'net/ssh/transport/compress/none-compressor'
              NoneCompressor.new
            end

            b.zlib_decompressor do
              require 'net/ssh/transport/compress/zlib-decompressor'
              ZLibDecompressor.new
            end

            b.none_decompressor do
              require 'net/ssh/transport/compress/none-decompressor'
              NoneDecompressor.new
            end

            # Add the compressor services to the hash of available
            # compression algorithms.
            b.compression_algorithms.update(
              "zlib" => b.zlib_compressor,
              "none" => b.none_compressor
            )

            # Add the decompressor services to the hash of available
            # decompression algorithms.
            b.decompression_algorithms.update(
              "zlib" => b.zlib_decompressor,
              "none" => b.none_decompressor
            )
          end
        end
        module_function :register_services

      end
    end
  end
end
