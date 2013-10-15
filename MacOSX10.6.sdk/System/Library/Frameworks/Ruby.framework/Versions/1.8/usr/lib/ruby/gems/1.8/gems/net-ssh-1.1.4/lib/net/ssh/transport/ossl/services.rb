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

module Net
  module SSH
    module Transport
      module OSSL

        # Register all OpenSSL-related services.
        def register_services( container )
          # make sure the user has a valid Ruby and OpenSSL installed.
          version_check

          # Register all OpenSSL services in the :ossl namespace.
          container.namespace_define :ossl do |b|

            # The list of known sources of HMAC algorithm implementations.
            b.hmac_algorithm_sources { Array.new }
            b.require 'net/ssh/transport/ossl/hmac/services', "#{self}::HMAC"

            # The hash mapping SSH2 cipher names to OpenSSL cipher names.
            b.cipher_names do
              Hash[ "3des-cbc"     => "des-ede3-cbc",
                    "blowfish-cbc" => "bf-cbc",
                    "aes256-cbc"   => "aes-256-cbc",
                    "aes192-cbc"   => "aes-192-cbc",
                    "aes128-cbc"   => "aes-128-cbc",
                    "idea-cbc"     => "idea-cbc",
                    "none"         => "none" ]
            end

            # The hash mapping key names to OpenSSL key implementations.
            b.key_names do
              Hash[ "dh"  => OpenSSL::PKey::DH,
                    "rsa" => OpenSSL::PKey::RSA,
                    "dsa" => OpenSSL::PKey::DSA ]
            end

            # The hash mapping digest names to OpenSSL digest implementations.
            b.digest_names do
              Hash[ "sha1" => OpenSSL::Digest::SHA1,
                    "md5"  => OpenSSL::Digest::MD5 ]
            end

            # The factory for converting cipher names to cipher implementations.
            b.cipher_factory( :model => :singleton_deferred ) do |c,p|
              require 'net/ssh/transport/ossl/cipher-factory'
              svc = CipherFactory.new( c.cipher_names )
              svc.identity_cipher = c.identity_cipher
              svc
            end

            # The factory for converting HMAC names to HMAC implementations.
            b.hmac_factory( :model => :singleton_deferred ) do |c,p|
              require 'net/ssh/transport/ossl/hmac-factory'
              HMACFactory.new( c.hmac_algorithm_sources )
            end

            # The factory for obtaining OpenSSL-specific buffer implementations.
            b.buffer_factory do
              require 'net/ssh/transport/ossl/buffer-factory'
              BufferFactory.new
            end

            # The factory for converting key names to key implementations.
            b.key_factory( :model => :singleton_deferred ) do |c,p|
              require 'net/ssh/transport/ossl/key-factory'
              svc = KeyFactory.new( c.key_names )
              svc.buffers = c.buffer_factory
              svc.prompter = c.prompter if c.knows_key?( :prompter )
              svc
            end

            # The factory for creating OpenSSL::BN (big number) instances.
            b.bn_factory { OpenSSL::BN }

            # The factory for converting digest names to digest implementations.
            b.digest_factory do |c,p|
              require 'net/ssh/transport/ossl/digest-factory'
              DigestFactory.new( c.digest_names )
            end

          end

          # Register each of the factories defined above in the corresponding
          # factory map, under the :ossl key.
          container.define do |b|
            b.cipher_factories[:ossl] = b.ossl.cipher_factory
            b.hmac_factories[:ossl]   = b.ossl.hmac_factory
            b.key_factories[:ossl]    = b.ossl.key_factory
            b.buffer_factories[:ossl] = b.ossl.buffer_factory
            b.bn_factories[:ossl]     = b.ossl.bn_factory
            b.digest_factories[:ossl] = b.ossl.digest_factory
          end
        end
        module_function :register_services

        # Tries to make sure that the correct minimum versions of libraries are
        # installed.
        def version_check
          if RUBY_VERSION < "1.8.2"
            unless OpenSSL::PKey::DH.instance_methods.include? "p"
              warn "Your OpenSSL module (the Ruby module, not the library)\n" +
                   "is too old. Please go to the Net::SSH downloads page\n" +
                   "and install the most recent snapshot of the OpenSSL\n" +
                   "module.\n\n" +
                   "  http://rubyforge.org/projects/net-ssh"
              abort
            end
          end

          # make sure that the OpenSSL library itself is at least version 0.9.7
          match = OpenSSL::OPENSSL_VERSION.match(
            /OpenSSL (\d+)\.(\d+)\.(\d+)(.*?) / )
          major = match[1].to_i
          minor = match[2].to_i
          tiny = match[3].to_i
          patch = match[4]

          if major < 1 && ( minor < 9 || minor == 9 && tiny < 7 )
            ver = "#{major}.#{minor}.#{tiny}#{patch}"
            warn "Your OpenSSL library (the library itself, not the Ruby\n" +
                 "module) is version #{ver}, too old to use with Net::SSH.\n" +
                 "Please upgrade to at least version 0.9.7 and then rebuild\n" +
                 "your Ruby OpenSSL module."
            abort
          end
        end
        module_function :version_check

      end
    end
  end
end
