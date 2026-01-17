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

require 'socket'
require 'timeout'
require 'net/ssh/transport/constants'
require 'net/ssh/transport/errors'
require 'net/ssh/version'

module Net
  module SSH
    module Transport

      # Represents a low-level SSH session, at the transport protocol level.
      # This handles the algorithm negotiation and key exchange for any SSH
      # connection.
      class Session
        include Constants
        
        # the unique session identifier
        attr_reader :session_id

        # the collection of algorithms currently being used
        attr_reader :algorithms

        # the hostname that was requested
        attr_reader :host

        # the port that was requested
        attr_reader :port

        attr_writer :logger
        attr_writer :default_port
        attr_writer :version_negotiator
        attr_writer :algorithm_negotiator
        attr_writer :socket_factory
        attr_writer :packet_sender
        attr_writer :packet_receiver
        attr_writer :ciphers
        attr_writer :hmacs
        attr_writer :kexs
        attr_writer :compressors
        attr_writer :decompressors

        # The name that Net::SSH reports for itself
        NAME = "Ruby/Net::SSH"

        # The SSH protocol supported by Net::SSH.
        PROTOCOL = "SSH-2.0"

        # Returns the version string of this client.
        def self.version
          "#{PROTOCOL}-#{NAME}_#{Net::SSH::Version::STRING}"
        end

        VALID_OPTIONS = [ :port, :host_key, :kex, :encryption, :hmac,
                          :compression, :languages, :compression_level, :proxy,
                          :timeout ]

        # Create a new connection to the given host. This will negotiate the
        # algorithms to use and exchange the keys. A block must be given. The
        # uninitialized +self+ will be passed to the block, so that dependencies
        # may be injected.
        def initialize( host, options={} )
          @saved_message = nil
          @session_id = nil
          @host = host

          yield self

          invalid_options = options.keys - VALID_OPTIONS

          unless invalid_options.empty?
            raise ArgumentError,
              "invalid option(s) to #{self.class}: #{invalid_options.inspect}"
          end

          @logger.debug "connecting" if @logger.debug?

          @port = options[ :port ] || @default_port
          @socket = timeout( options[:timeout] || 0 ) do
            ( options[:proxy] || @socket_factory ).open( host, @port )
          end

          @packet_sender.socket = @socket
          @packet_receiver.socket = @socket

          @kex_info = {
            :client_version_string => self.class.version,
            :server_version_string =>
              @version_negotiator.negotiate( @socket, self.class.version ) }

          @options = options
          kexinit
        end

        # Returns info about the remote peer
        def peer
          @peer ||= begin
            addr = @socket.getpeername
            ip_address = Socket.getnameinfo(addr, Socket::NI_NUMERICHOST | Socket::NI_NUMERICSERV).first
            { :ip => ip_address, :port => @port.to_i, :host => @host }
          end
        end

        # Returns the name of the client's host, as reported by the socket.
        def client_name
          return @hostname if defined? @hostname

          sockaddr = @socket.getsockname
          begin
            @hostname =
              Socket.getnameinfo( sockaddr, Socket::NI_NAMEREQD ).first
          rescue
            begin
              @hostname = Socket.getnameinfo( sockaddr ).first
            rescue
              begin
                @hostname = Socket.gethostbyname( Socket.gethostname ).first
              rescue
                @logger.error "the client ipaddr/name could not be determined"
              end
            end
          end

          return @hostname
        end

        def kexinit
          @doing_kexinit = true
          @algorithms = @algorithm_negotiator.negotiate( self, @options )

          @kex_info[ :server_algorithm_packet ] = @algorithms.server_packet
          @kex_info[ :client_algorithm_packet ] = @algorithms.client_packet

          exchange_keys
          @doing_kexinit = false
        end
        private :kexinit

        # Closes the connection.
        def close
          # TODO: send a DISCONNECT message to the server to close gracefully
          @socket.close
        end

        def get_kex_byte_requirement
          need = 0

          [ @algorithms.encryption_s2c,
            @algorithms.encryption_c2s
          ].each do |alg|
            key_len, block_size = @ciphers.get_lengths( alg )
            need = key_len if need < key_len
            need = block_size if need < block_size
          end

          [ @algorithms.mac_c2s, @algorithms.mac_s2c ].each do |alg|
            key_len = @hmacs.get_key_length( alg )
            need = key_len if need < key_len
          end

          return need
        end
        private :get_kex_byte_requirement
        
        # Exchanges keys with the server, using the kex algorithm negotiated
        # during the algorithm negotiation phase. After finishing this phase,
        # further packets sent to or from the server will be encrypted and
        # (possibly) compressed.
        def exchange_keys
          @kex_info[ :need_bytes ] = get_kex_byte_requirement

          kex = @kexs.fetch( @algorithms.kex )
          result = kex.exchange_keys( self, @kex_info )

          @shared_secret = result[ :shared_secret ]
          hash = result[ :session_id ]
          @session_id = hash unless @session_id
          @server_key = result[ :server_key ]
          @hashing_algorithm = result[ :hashing_algorithm ]

          # prepare the ciphers, et. al.
          secret_bin = @shared_secret.to_ssh

          iv_c2s = @hashing_algorithm.digest( secret_bin +
                                              hash +
                                              "A" +
                                              @session_id )
          iv_s2c = @hashing_algorithm.digest( secret_bin +
                                              hash +
                                              "B" +
                                              @session_id )
          key_c2s = @hashing_algorithm.digest( secret_bin +
                                               hash +
                                               "C" +
                                               @session_id )
          key_s2c = @hashing_algorithm.digest( secret_bin +
                                               hash +
                                               "D" +
                                               @session_id )
          mac_key_c2s = @hashing_algorithm.digest( secret_bin +
                                                   hash +
                                                   "E" +
                                                   @session_id )
          mac_key_s2c = @hashing_algorithm.digest( secret_bin +
                                                   hash +
                                                   "F" +
                                                   @session_id )

          cipher_c2s = @ciphers.get( 
                            @algorithms.encryption_c2s, iv_c2s, key_c2s,
                            secret_bin, hash, @hashing_algorithm,
                            true )

          cipher_s2c = @ciphers.get( 
                            @algorithms.encryption_s2c, iv_s2c, key_s2c,
                            secret_bin, hash, @hashing_algorithm,
                            false )

          mac_c2s = @hmacs.get( @algorithms.mac_c2s, mac_key_c2s );
          mac_s2c = @hmacs.get( @algorithms.mac_s2c, mac_key_s2c );

          compression_c2s = @compressors[ @algorithms.compression_c2s ].new(
              :level => @algorithms.compression_level )
          compression_s2c = @decompressors[ @algorithms.compression_s2c ].new

          @packet_sender.set_algorithms cipher_c2s, mac_c2s, compression_c2s
          @packet_receiver.set_algorithms cipher_s2c, mac_s2c, compression_s2c
        end
        private :exchange_keys

        # Waits for the next message from the server, handling common requests
        # like DISCONNECT, IGNORE, DEBUG, and KEXINIT in the background. The
        # next message is returned as a [ type, buffer ] tuple, where the buffer
        # is a Net::SSH::Util::ReaderBuffer.
        def wait_for_message
          buffer = type = nil

          if @saved_message
            type, buffer = @saved_message
            @logger.debug "returning saved message: #{type}" if @logger.debug?
            @saved_message = nil
          else
            loop do
              if @logger.debug?
                @logger.debug "waiting for packet from server..."
              end

              buffer = @packet_receiver.get
              next unless buffer

              type = buffer.read_byte
              @logger.debug "got packet of type #{type}" if @logger.debug?

              case type
                when DISCONNECT
                  reason_code = buffer.read_long
                  description = buffer.read_string
                  language = buffer.read_string
                  raise Net::SSH::Transport::Disconnect,
                    "disconnected: #{description} (#{reason_code})"

                when IGNORE
                  # do nothing
                  @logger.info "received IGNORE message " +
                    "(#{buffer.read_string.inspect})" if @logger.debug?

                when DEBUG
                  # do nothing
                  @logger.info "received DEBUG message" if @logger.debug?
                  always_display = buffer.read_bool
                  message = buffer.read_string
                  language = buffer.read_string
                  if always_display
                    @logger.warn "#{message} (#{language})" if @logger.warn?
                  else
                    @logger.debug "#{message} (#{language})" if @logger.debug?
                  end

                when KEXINIT
                  # unless we're already doing a key-exchange, do key
                  # re-exchange
                  if !@doing_kexinit
                    @logger.info "re-key requested" if @logger.info?
                    @saved_message = [ type, buffer ]
                    kexinit
                  else
                    break
                  end

                else
                  break
              end
            end
          end

          return type, buffer
        end

        # Sends the given payload, using the currently configured
        # OutgoingPacketStream.
        def send_message( message )
          if @logger.debug?
            @logger.debug "sending message >>#{message.to_s.inspect}<<"
          end

          @packet_sender.send message
        end

        # Returns true if there are bytes to be read on the socket. Note that
        # this only means there is an encrypted packet ready to be read, not
        # that there is data available to any particular SSH channel.
        def reader_ready?
          IO.select([@socket],nil,nil,0) != nil
        end

        # Sends an IGNORE packet to the server, as a way to ping the connection
        # and make sure the server knows the client is still active.
        def ping!
          send_message [IGNORE, 4, "ping"].pack("cNA4")
        end
      end

    end
  end
end
