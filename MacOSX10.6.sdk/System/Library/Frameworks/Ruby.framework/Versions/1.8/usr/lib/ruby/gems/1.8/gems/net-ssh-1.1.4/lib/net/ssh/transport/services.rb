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

      # Register the services that together implement the SSH transport layer.
      def register_services( container )
        container.namespace_define :transport do |b|
          b.kex_names { Hash.new }
          b.compression_algorithms { Hash.new }
          b.decompression_algorithms { Hash.new }

          b.cipher_factories { Hash.new }
          b.hmac_factories { Hash.new }
          b.key_factories { Hash.new }
          b.buffer_factories { Hash.new }
          b.bn_factories { Hash.new }
          b.digest_factories { Hash.new }

          b.ciphers( :model => :prototype ) { |c,|
            c.cipher_factories.fetch( c.crypto_backend ) }

          b.hmacs( :model => :prototype ) { |c,|
            c.hmac_factories.fetch( c.crypto_backend ) }

          b.keys( :model => :prototype ) { |c,|
            c.key_factories.fetch( c.crypto_backend ) }

          b.buffers( :model => :prototype ) { |c,|
            c.buffer_factories.fetch( c.crypto_backend ) }

          b.bns( :model => :prototype ) { |c,|
            c.bn_factories.fetch( c.crypto_backend ) }

          b.digesters( :model => :prototype ) { |c,|
            c.digest_factories.fetch( c.crypto_backend ) }

          b.identity_cipher do
            require 'net/ssh/transport/identity-cipher'
            IdentityCipher.new
          end

          b.outgoing_packet_stream :model => :prototype_deferred do |c,|
            require 'net/ssh/transport/packet-stream'
            OutgoingPacketStream.new(
              c.ciphers, c.hmacs, c.compression_algorithms )
          end

          b.incoming_packet_stream :model => :prototype_deferred do |c,point|
            require 'net/ssh/transport/packet-stream'
            stream = IncomingPacketStream.new(
              c.ciphers, c.hmacs, c.decompression_algorithms )
            stream.buffers = c.buffers
            stream.log = c.log_for( point )
            stream
          end

          b.algorithms do
            Hash[
              :host_key => [ "ssh-dss", "ssh-rsa" ],
              :kex => [ "diffie-hellman-group-exchange-sha1",
                        "diffie-hellman-group1-sha1" ],
              :encryption => [ "3des-cbc",
                               "aes128-cbc", 
                               "blowfish-cbc",
                               "aes256-cbc",
                               "aes192-cbc",
                               "idea-cbc",
                               "none" ],
              :hmac => [ "hmac-md5",
                         "hmac-sha1",
                         "hmac-md5-96",
                         "hmac-sha1-96",
                         "none" ],
              :compression => [ "none", "zlib" ],
              :languages => []
            ]
          end

          b.default_ssh_port { 22 }

          b.socket_factory do
            require 'socket'
            TCPSocket
          end

          b.version_negotiator do |c,point|
            require 'net/ssh/transport/version-negotiator'
            VersionNegotiator.new( c.log_for( point ) )
          end

          b.algorithm_negotiator do |c,point|
            require 'net/ssh/transport/algorithm-negotiator'
            AlgorithmNegotiator.new(
              c.log_for( point ),
              c.algorithms,
              c.buffers )
          end

          b.session do |c,point|
            require 'net/ssh/transport/session'

            args = [ c[:transport_host] ]
            args << c[:transport_options] if c.knows_key?(:transport_options)

            Session.new( *args ) do |s|
              s.logger               = c[:log_for, point]
              s.default_port         = c[:default_ssh_port]
              s.version_negotiator   = c[:version_negotiator]
              s.algorithm_negotiator = c[:algorithm_negotiator]
              s.socket_factory       = c[:socket_factory]
              s.packet_sender        = c[:outgoing_packet_stream]
              s.packet_receiver      = c[:incoming_packet_stream]
              s.ciphers              = c[:ciphers]
              s.hmacs                = c[:hmacs]
              s.kexs                 = c[:kex_names]
              s.compressors          = c[:compression_algorithms]
              s.decompressors        = c[:decompression_algorithms]
            end
          end

          b.require 'net/ssh/transport/ossl/services', "#{self}::OSSL"
          b.require 'net/ssh/transport/compress/services', "#{self}::Compress"
          b.require 'net/ssh/transport/kex/services', "#{self}::Kex"
        end
      end
      module_function :register_services

    end
  end
end
