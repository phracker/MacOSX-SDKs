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

require 'net/ssh/errors'
require 'net/ssh/transport/constants'
require 'net/ssh/transport/kex/dh.rb'

module Net
  module SSH
    module Transport
      module Kex

        # A key-exchange service implementing the
        # "diffie-hellman-group-exchange-sha1" key-exchange algorithm.
        class DiffieHellmanGroupExchangeSHA1 < DiffieHellmanGroup1SHA1

          MINIMUM_BITS      = 1024
          MAXIMUM_BITS      = 8192

          KEXDH_GEX_GROUP   = 31
          KEXDH_GEX_INIT    = 32
          KEXDH_GEX_REPLY   = 33
          KEXDH_GEX_REQUEST = 34

          # Compute the number of bits needed for the given number of bytes.
          def compute_need_bits( data )
            need_bits = data[:need_bytes] * 8
            if need_bits < MINIMUM_BITS
              need_bits = MINIMUM_BITS
            elsif need_bits > MAXIMUM_BITS
              need_bits = MAXIMUM_BITS
            end

            data[:need_bits] = need_bits
            data[:need_bytes] = need_bits / 8
          end
          private :compute_need_bits

          # Returns the DH key parameters for the given session.
          def get_parms( session, data )
            compute_need_bits( data )

            # request the DH key parameters for the given number of bits.
            buffer = @buffers.writer
            buffer.write_byte KEXDH_GEX_REQUEST
            buffer.write_long MINIMUM_BITS
            buffer.write_long data[:need_bits]
            buffer.write_long MAXIMUM_BITS
            session.send_message buffer

            type, buffer = session.wait_for_message
            unless type == KEXDH_GEX_GROUP
              raise Net::SSH::Exception, "expected KEXDH_GEX_GROUP, got #{type}"
            end

            p = buffer.read_bignum
            g = buffer.read_bignum
            
            [ p, g ]
          end
          private :get_parms

          # Returns the INIT/REPLY constants used by this algorithm.
          def get_init_reply
            [ KEXDH_GEX_INIT, KEXDH_GEX_REPLY ]
          end
          private :get_init_reply

          # Build the signature buffer to use when verifying a signature from
          # the server.
          def build_signature_buffer( dh, data, result )
            response = @buffers.writer
            response.write_string data[:client_version_string],
                                  data[:server_version_string],
                                  data[:client_algorithm_packet],
                                  data[:server_algorithm_packet],
                                  result[:key_blob]
            response.write_long MINIMUM_BITS,
                                data[:need_bits],
                                MAXIMUM_BITS
            response.write_bignum dh.p, dh.g, dh.pub_key,
                                  result[:server_dh_pubkey],
                                  result[:shared_secret]
            response
          end
          private :build_signature_buffer

        end

      end
    end
  end
end
