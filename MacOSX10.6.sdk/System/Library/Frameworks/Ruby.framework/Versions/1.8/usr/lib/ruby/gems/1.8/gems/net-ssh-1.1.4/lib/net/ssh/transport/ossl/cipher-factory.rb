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

        # Implements a factory of OpenSSL cipher algorithms.
        class CipherFactory
        
          # The accessor for setting the identity cipher implementation to use.
          attr_writer :identity_cipher

          # Create a new CipherFactory instance that uses the given Hash-like
          # to convert SSH2 cipher algorithm names to OpenSSL cipher algorithm
          # names.
          def initialize( cipher_map )
            @cipher_map = cipher_map
          end

          # Retrieves a new instance of the named algorithm. The new instance
          # will be initialized using an iv and key generated from the given
          # iv, key, shared, hash and digester values. Additionally, the
          # cipher will be put into encryption or decryption mode, based on the
          # value of the +encrypt+ parameter.
          def get( name,
                   iv=nil, key=nil,
                   shared=nil, hash=nil,
                   digester=nil,
                   encrypt=false )
          # begin
            ossl_name = @cipher_map.fetch( name ) do
              raise CipherNotFound, name
            end

            return @identity_cipher if ossl_name == "none"

            cipher = OpenSSL::Cipher::Cipher.new( ossl_name )
            cipher.send( encrypt ? :encrypt : :decrypt )

            cipher.padding = 0
            cipher.iv = make_key( cipher.iv_len, iv, shared, hash, digester )
            cipher.key = make_key( cipher.key_len, key, shared, hash, digester )

            return cipher
          end

          # Returns a two-element array containing the [ key-length,
          # block-size ] for the named cipher algorithm. If the cipher
          # algorithm is unknown, or is "none", 0 is returned for both elements
          # of the tuple.
          def get_lengths( name )
            ossl_name = @cipher_map[ name ]
            return [ 0, 0 ] if ossl_name.nil? || ossl_name == "none"

            cipher = OpenSSL::Cipher::Cipher.new( ossl_name )
            return [ cipher.key_len, cipher.block_size ]
          end

          # Generate a key value in accordance with the SSH2 specification.
          def make_key( bytes, key, shared, hash, digester )
            k = key[ 0, bytes ]

            while k.length < bytes
              step = digester.digest( shared + hash + k )
              bytes_needed = bytes - k.length
              k << step[ 0, bytes_needed ]
            end

            return k
          end
          private :make_key

        end

      end

    end
  end
end
