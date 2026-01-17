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

require 'base64'
require 'net/ssh/transport/errors'
require 'net/ssh/util/openssl'

module Net
  module SSH
    module Transport

      module OSSL

        # A factory class for returning new Key algorithm factories (actually
        # classes).
        class KeyFactory

          # The setter for the buffer factory to use.
          attr_writer :buffers

          # The setter for describing which prompter service to use when
          # prompting the user for a key passphrase.
          attr_writer :prompter

          # Create a new instance of the KeyFactory that uses the given
          # Hash-like to map SSH2 key algorithm names to names of
          # factories (classes) that can instantiate those algorithms.
          def initialize( algorithms )
            @factories = algorithms
          end

          # Return a new instance of the key factory for the given name.
          # If no such algorithm exists, a KeyTypeNotFound error will be raised.
          def get( name )
            klass_name = @factories.fetch( name ) do
              raise KeyTypeNotFound, name
            end

            return klass_name.new
          end

          # Loads a private key from a file. It will correctly determine
          # whether the file describes an RSA or DSA key, and will load it
          # appropriately. The new key is returned. If the key itself is
          # encrypted (requiring a passphrase to use), the user will be
          # prompted to enter their password. 
          def load_private_key( filename )
            file = File.read( filename )

            if file.match( /-----BEGIN DSA PRIVATE KEY-----/ )
              key_type = OpenSSL::PKey::DSA
            elsif file.match( /-----BEGIN RSA PRIVATE KEY-----/ )
              key_type = OpenSSL::PKey::RSA
            elsif file.match( /-----BEGIN (.*) PRIVATE KEY-----/ )
              raise OpenSSL::PKey::PKeyError, "not a supported key type '#{$1}'"
            else
              raise OpenSSL::PKey::PKeyError, "not a private key (#{filename})"
            end

            encrypted_key = file.match( /ENCRYPTED/ )
            password = encrypted_key ? 'nil' : nil
            tries = 0

            begin
              return key_type.new( file, password )
            rescue OpenSSL::PKey::RSAError, OpenSSL::PKey::DSAError => e
              if encrypted_key && @prompter
                tries += 1
                if tries <= 3
                  password = @prompter.password(
                    "Enter password for #{filename}: " )
                  retry
                else
                  raise
                end
              else
                raise
              end
            end
          end

          # Loads a public key from a file. It will correctly determine whether
          # the file describes an RSA or DSA key, and will load it
          # appropriately. The new public key is returned.
          def load_public_key( filename )
            data = File.open( filename ) { |file| file.read }
            type, blob = data.split( / / )

            blob = Base64.decode64( blob )
            reader = @buffers.reader( blob )
            key = reader.read_key or
              raise OpenSSL::PKey::PKeyError,
                "not a public key #{filename.inspect}"
            return key
          end

        end

      end

    end
  end
end
