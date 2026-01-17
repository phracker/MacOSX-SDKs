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

module Net
  module SSH
    module Transport
      module Kex

        # A key-exchange service implementing the "diffie-hellman-group1-sha1"
        # key-exchange algorithm.
        class DiffieHellmanGroup1SHA1
          include Constants

          # The value of 'P', as a string, in hexadecimal
          P_s = "FFFFFFFF" "FFFFFFFF" "C90FDAA2" "2168C234" +
                "C4C6628B" "80DC1CD1" "29024E08" "8A67CC74" +
                "020BBEA6" "3B139B22" "514A0879" "8E3404DD" +
                "EF9519B3" "CD3A431B" "302B0A6D" "F25F1437" +
                "4FE1356D" "6D51C245" "E485B576" "625E7EC6" +
                "F44C42E9" "A637ED6B" "0BFF5CB6" "F406B7ED" +
                "EE386BFB" "5A899FA5" "AE9F2411" "7C4B1FE6" +
                "49286651" "ECE65381" "FFFFFFFF" "FFFFFFFF"

          # The radix in which P_s represents the value of P
          P_r = 16

          # The group constant
          G = 2

          # The reference to the key factory to use.
          attr_writer :keys

          # The reference to the buffer factory to use.
          attr_writer :buffers

          # The reference to the host key verifier to use to verify host keys.
          attr_writer :host_key_verifier

          # Create a new instance of the DiffieHellmanGroup1SHA1 algorithm.
          # The parameters are, respectively, a factory for creating new
          # Bignum instances, and a factory for obtaining digester objects.
          def initialize( bn, digests )
            @bn = bn

            @p = @bn.new( P_s, P_r )
            @g = G

            @digester = digests.get( "sha1" )
          end

          # Returns the DH key parameters for the given session.
          def get_parms( session, data )
            [ @p, @g ]
          end
          private :get_parms

          # Returns the INIT/REPLY constants used by this algorithm.
          def get_init_reply
            [ KEXDH_INIT, KEXDH_REPLY ]
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
            response.write_bignum dh.pub_key,
                                  result[:server_dh_pubkey],
                                  result[:shared_secret]
            response
          end
          private :build_signature_buffer

          # Generate a DH key with a private key consisting of the given
          # number of bytes.
          def generate_key( session, data ) #:nodoc:
            dh = @keys.get( "dh" )
            dh.p, dh.g = get_parms( session, data )

            dh.priv_key = @bn.rand( data[:need_bytes] * 8 )

            loop do
              dh.generate_key!
              break if dh.valid?
            end

            dh
          end

          # Send the KEXDH_INIT message, and expect the KEXDH_REPLY. Return the
          # resulting buffer.
          def send_kexinit( dh, session ) #:nodoc:
            init, reply = get_init_reply

            # send the KEXINIT message
            buffer = @buffers.writer
            buffer.write_byte init
            buffer.write_bignum dh.pub_key
            session.send_message buffer

            # expect the KEXDH_REPLY message
            type, buffer = session.wait_for_message
            raise Net::SSH::Exception,
              "expected REPLY" unless type == reply

            return buffer
          end

          # Parse the buffer from a KEXDH_REPLY message, returning a hash of
          # the extracted values.
          def parse_kex_reply( dh, buffer, session ) #:nodoc:
            result = Hash.new

            result[:key_blob] = buffer.read_string
            result[:server_key] = @buffers.reader( result[:key_blob] ).read_key
            result[:server_dh_pubkey] = buffer.read_bignum
            result[:shared_secret] =
              @bn.new( dh.compute_key( result[:server_dh_pubkey] ), 2 )

            sig_buffer = @buffers.reader( buffer.read_string )
            sig_type = sig_buffer.read_string
            if sig_type != session.algorithms.host_key
              raise Net::SSH::Exception,
                "host key algorithm mismatch for signature " +
                "'#{sig_type}' != '#{session.algorithms.host_key}'"
            end
            result[:server_sig] = sig_buffer.read_string

            return result
          end

          # Verify that the given key is of the expected type, and that it
          # really is the key for the session's host. Raise Net::SSH::Exception
          # if it is not.
          def verify_server_key( key, session ) #:nodoc:
            if key.ssh_type != session.algorithms.host_key
              raise Net::SSH::Exception,
                "host key algorithm mismatch " +
                "'#{key.ssh_type}' != '#{session.algorithms.host_key}'"
            end

            blob, fingerprint = generate_key_fingerprint(key)

            unless @host_key_verifier.verify(:key => key, :key_blob => blob, :fingerprint => fingerprint, :peer => session.peer)
              raise Net::SSH::Exception, "host key verification failed"
            end
          end

          def generate_key_fingerprint(key)
            writer = @buffers.writer
            writer.write_key(key)

            blob = writer.to_s
            fingerprint = OpenSSL::Digest::MD5.hexdigest(blob).scan(/../).join(":")

            [blob, fingerprint]
          rescue ::Exception => e
            [nil, "(could not generate fingerprint: #{e.message})"]
          end

          # Verify the signature that was received. Raise Net::SSH::Exception
          # if the signature could not be verified. Otherwise, return the new
          # session-id.
          def verify_signature( dh, data, result ) #:nodoc:
            response = build_signature_buffer( dh, data, result )

            hash = @digester.digest( response.to_s )

            unless result[:server_key].ssh_do_verify(
              result[:server_sig], hash )
                raise Net::SSH::Exception, "could not verify server signature"
            end

            return hash
          end

          # Send the NEWKEYS message, and expect the NEWKEYS message in
          # reply.
          def confirm_newkeys( session ) #:nodoc:
            # send own NEWKEYS message first (the wodSSHServer won't send first)
            response = @buffers.writer
            response.write_byte NEWKEYS
            session.send_message response

            # wait for the server's NEWKEYS message
            type, buffer = session.wait_for_message
            raise Net::SSH::Exception, "expected NEWKEYS" unless type == NEWKEYS
          end

          # Perform the key-exchange for the given session, with the given
          # data. The data is a Hash of symbols representing information
          # required by this algorithm, which was acquired during earlier
          # processing. This method will return an object consisting of the
          # following fields:
          #
          # * :session_id
          # * :server_key
          # * :shared_secret
          # * :hashing_algorithm
          #
          # The caller is expected to be able to understand how to use these
          # deliverables.
          def exchange_keys( session, data )
            data = data.dup
            dh = generate_key( session, data )

            buffer = send_kexinit( dh, session )

            result = parse_kex_reply( dh, buffer, session )

            verify_server_key( result[:server_key], session )

            session_id = verify_signature( dh, data, result )

            confirm_newkeys( session )

            return Struct.new( :session_id,
              :server_key, :shared_secret, :hashing_algorithm ).new(
                session_id, result[:server_key], result[:shared_secret],
                @digester )
          end

        end

      end
    end
  end
end
