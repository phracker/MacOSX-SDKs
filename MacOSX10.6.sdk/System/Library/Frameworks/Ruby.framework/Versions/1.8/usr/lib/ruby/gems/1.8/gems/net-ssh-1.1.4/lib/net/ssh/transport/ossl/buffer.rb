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
require 'net/ssh/util/buffer'

module Net
  module SSH
    module Transport

      module OSSL

        # The implementation of a reader buffer that can read bignums and keys.
        module ReaderBufferImpl

          # Read a bignum (OpenSSL::BN) from the buffer, in SSH2 format. It is
          # essentially just a string, which is reinterpreted to be a bignum in
          # binary format.
          def read_bignum
            data = read_string
            return unless data
            OpenSSL::BN.new( data, 2 )
          end

          # Read a key from the buffer. The key will start with a string
          # describing its type. The remainder of the key is defined by the
          # type that was read.
          def read_key
            type = read_string
            return ( type ? read_keyblob( type ) : nil )
          end

          # Read a keyblob of the given type from the buffer, and return it as
          # a key. Only RSA and DSA keys are supported.
          def read_keyblob( type )
            case type
              when "ssh-dss"
                key = OpenSSL::PKey::DSA.new
                key.p = read_bignum
                key.q = read_bignum
                key.g = read_bignum
                key.pub_key = read_bignum

              when "ssh-rsa"
                key = OpenSSL::PKey::RSA.new
                key.e = read_bignum
                key.n = read_bignum

              else
                raise NotImplementedError, "unsupported key type '#{type}'"
            end

            return key
          end

        end

        # An extension of the standard ReaderBuffer implementation that also
        # includes the ReaderBufferImpl module.
        class ReaderBuffer < Net::SSH::Util::ReaderBuffer
          include ReaderBufferImpl
        end

        # An extension of the standard general Buffer implementation that also
        # includes the ReaderBufferImpl module.
        class Buffer < Net::SSH::Util::Buffer
          include ReaderBufferImpl
        end

      end

    end
  end
end
