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
require 'net/ssh/known-hosts'

module Net
  module SSH
    module Transport

      # The AlgorithmNegotiator is used for negotiating the algorithms to be
      # employed for a specific SSH session.
      class AlgorithmNegotiator
        include Constants

        Algorithms = Struct.new( :server_packet,
                                 :client_packet,
                                 :kex,
                                 :host_key,
                                 :encryption_c2s,
                                 :encryption_s2c,
                                 :mac_c2s,
                                 :mac_s2c,
                                 :compression_c2s,
                                 :compression_s2c,
                                 :language_c2s,
                                 :language_s2c,
                                 :compression_level )

        # Create a new AlgorithmNegotiator instance, using the given logger,
        # set of default algorithms, and buffer factory.
        def initialize( logger, algorithms, buffers )
          @default_algorithms = algorithms
          @buffers = buffers
          @logger = logger
        end

        # Adds the algorithms of the specified type from +options+ to the
        # @algorithms hash. Also verifies that the specified algorithms are
        # supported.
        def prepare_preferred_algorithm( options, algorithm )
          @algorithms[ algorithm ] = @default_algorithms[ algorithm ].dup
          if options[algorithm]
            algos = [ *options[algorithm] ]
            algos.each do |algo|
              unless @algorithms[algorithm].include?(algo)
                raise NotImplementedError,
                  "unsupported algorithm for #{algorithm.inspect}: #{algo}"
              end
            end
            @algorithms[ algorithm ].unshift( *algos ).uniq!
          end
        end
        private :prepare_preferred_algorithm

        # Builds the @algorithms hash from the values specified in the
        # +options+ hash.
        def prepare_preferred_algorithms( session, options )
          @algorithms = Hash.new

          if !options.key?(:host_key)
            keys = Net::SSH::KnownHosts.search_for(Net::SSH::KnownHosts.canonize(session.host, session.port))
            preferred_order = []
            preferred_order << keys.first.ssh_type if keys.any?
            options = options.merge(:host_key => preferred_order)
          end

          prepare_preferred_algorithm options, :host_key
          prepare_preferred_algorithm options, :kex
          prepare_preferred_algorithm options, :encryption
          prepare_preferred_algorithm options, :hmac
          prepare_preferred_algorithm options, :compression
          prepare_preferred_algorithm options, :languages

          @compression_level = options[ :compression_level ]
        end
        private :prepare_preferred_algorithms

        # looks for the first element in list1 that is also in list2
        def first_matching_element( list1, list2 )
          list1 = list1.split( /,/ ) if String === list1
          list2 = list2.split( /,/ ) if String === list2

          list1.each do |item|
            return item if list2.include? item
          end

          return nil
        end
        private :first_matching_element

        # Negotiate the supported algorithms with the server. If a compromise
        # cannot be reached between what the client wants and what the server
        # can provide, this will fail.
        def negotiate( session, options )
          prepare_preferred_algorithms session, options

          # first, discover what the server can do
          type, buffer = session.wait_for_message
          raise Net::SSH::Exception, "expected KEXINIT" unless type == KEXINIT

          server_algorithm_packet = buffer.content

          cookie = buffer.read( 16 )
          kex_algorithms = buffer.read_string
          server_host_key_algorithms = buffer.read_string
          encryption_algorithms_client_to_server = buffer.read_string
          encryption_algorithms_server_to_client = buffer.read_string
          mac_algorithms_client_to_server = buffer.read_string
          mac_algorithms_server_to_client = buffer.read_string
          compression_algorithms_client_to_server = buffer.read_string
          compression_algorithms_server_to_client = buffer.read_string
          languages_client_to_server = buffer.read_string
          languages_server_to_client = buffer.read_string
          first_kex_packet_follows = buffer.read_bool
          zero = buffer.read_long

          # TODO: if first_kex_packet_follows, we need to try to skip the
          # actual kexinit stuff and try to guess what the server is doing...
          # need to read more about this scenario.

          # next, tell the server what we can do

          my_kex = @algorithms[ :kex ].join( "," )
          my_server_host_key_algorithms = @algorithms[ :host_key ].join( "," )
          my_encryption_algorithms = @algorithms[ :encryption ].join( "," )
          my_mac_algorithms = @algorithms[ :hmac ].join( "," )
          my_compression_algorithms = @algorithms[ :compression ].join( "," )
          my_languages = @algorithms[ :languages ].join( "," )

          msg = @buffers.writer
          msg.write_byte KEXINIT
          msg.write_long rand(0xFFFFFFFF), rand(0xFFFFFFFF), rand(0xFFFFFFFF),
            rand(0xFFFFFFFF)
          msg.write_string my_kex, my_server_host_key_algorithms
          msg.write_string my_encryption_algorithms, my_encryption_algorithms
          msg.write_string my_mac_algorithms, my_mac_algorithms
          msg.write_string my_compression_algorithms, my_compression_algorithms
          msg.write_string my_languages, my_languages
          msg.write_bool false
          msg.write_long 0

          client_algorithm_packet = msg.to_s
          session.send_message msg

          # negotiate algorithms

          kex_algorithm = first_matching_element( @algorithms[ :kex ],
            kex_algorithms )
          raise Net::SSH::Exception,
            "could not settle on kex algorithm" unless kex_algorithm
          @logger.debug "kex algorithm: #{kex_algorithm}" if @logger.debug?

          host_key_algorithm = first_matching_element(
            @algorithms[ :host_key ], server_host_key_algorithms )
          raise Net::SSH::Exception,
            "could not settle on host key algorithm" unless host_key_algorithm
          if @logger.debug?
            @logger.debug "host key algorithm: #{host_key_algorithm}"
          end

          encryption_algorithm_c2s = first_matching_element(
            @algorithms[ :encryption ], encryption_algorithms_client_to_server )
          unless encryption_algorithm_c2s
            raise Net::SSH::Exception,
              "could not settle on client-to-server encryption algorithm"
          end
          if @logger.debug?
            @logger.debug "encryption algorithm (client-to-server): " +
              encryption_algorithm_c2s
          end

          encryption_algorithm_s2c = first_matching_element(
            @algorithms[ :encryption ], encryption_algorithms_server_to_client )
          unless encryption_algorithm_s2c
            raise Net::SSH::Exception,
              "could not settle on server-to-client encryption algorithm"
          end
          if @logger.debug?
            @logger.debug "encryption algorithm (server-to-client): " +
              encryption_algorithm_s2c
          end

          mac_algorithm_c2s = first_matching_element(
            @algorithms[ :hmac ], mac_algorithms_client_to_server )
          unless mac_algorithm_c2s
            raise Net::SSH::Exception,
              "could not settle on client-to-server HMAC algorithm"
          end
          if @logger.debug?
            @logger.debug "hmac algorithm (client-to-server): " +
              mac_algorithm_c2s
          end

          mac_algorithm_s2c = first_matching_element( @algorithms[ :hmac ],
            mac_algorithms_server_to_client )
          unless mac_algorithm_s2c
            raise Net::SSH::Exception,
              "could not settle on server-to-client HMAC algorithm"
          end
          if @logger.debug?
            @logger.debug "hmac algorithm (server-to-client): " +
              mac_algorithm_s2c
          end

          compression_algorithm_c2s = first_matching_element(
            @algorithms[ :compression ],
            compression_algorithms_client_to_server )
          unless compression_algorithm_c2s
            raise Net::SSH::Exception,
              "could not settle on client-to-server compression algorithm"
          end
          if @logger.debug?
            @logger.debug "compression algorithm (client-to-server): " +
              compression_algorithm_c2s
          end

          compression_algorithm_s2c = first_matching_element(
            @algorithms[ :compression ],
            compression_algorithms_server_to_client )
          unless compression_algorithm_s2c
            raise Net::SSH::Exception,
              "could not settle on server-to-client compression algorithm"
          end
          if @logger.debug?
            @logger.debug "compression algorithm (server-to-client): " +
              compression_algorithm_s2c
          end

          language_c2s = first_matching_element( @algorithms[ :languages ],
            languages_client_to_server ) || ""
          if @logger.debug?
            @logger.debug "language (client-to-server): #{language_c2s}"
          end

          language_s2c = first_matching_element( @algorithms[ :languages ],
            languages_server_to_client ) || ""
          if @logger.debug?
            @logger.debug "language (server-to-client): #{language_s2c}"
          end

          return Algorithms.new( server_algorithm_packet,
                                 client_algorithm_packet,
                                 kex_algorithm,
                                 host_key_algorithm,
                                 encryption_algorithm_c2s,
                                 encryption_algorithm_s2c,
                                 mac_algorithm_c2s,
                                 mac_algorithm_s2c,
                                 compression_algorithm_c2s,
                                 compression_algorithm_s2c,
                                 language_c2s,
                                 language_s2c,
                                 @compression_level )
        end

      end

    end
  end
end
