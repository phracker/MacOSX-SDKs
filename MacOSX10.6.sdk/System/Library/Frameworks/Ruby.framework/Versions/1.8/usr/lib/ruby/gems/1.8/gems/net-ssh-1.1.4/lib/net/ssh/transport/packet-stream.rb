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

require 'thread'

require 'net/ssh/errors'
require 'net/ssh/transport/errors'

module Net
  module SSH
    module Transport

      # The abstract parent of IncomingPacketStream and OutgoingPacketStream. It
      # represents the common interface of its subclasses.
      class PacketStream
        
        # the sequence number of the next packet to be processed.
        attr_reader :sequence_number

        # the setter for setting the socket to use for IO communication
        attr_writer :socket

        # Create a new packet stream. The given ciphers and hmacs are factories
        # that are used to initialize the cipher and mac attributes.
        def initialize( ciphers, hmacs )
          @sequence_number = 0

          @cipher = ciphers.get( "none" )
          @hmac = hmacs.get( "none" )
        end

        # Set the cipher and mac algorithms to the given arguments.
        def set_algorithms( cipher, mac )
          @cipher, @hmac = cipher, mac
        end

        # Compute the mac for the given payload.
        def compute_hmac( payload )
          @hmac.digest( [ @sequence_number, payload ].pack( "NA*" ) )
        end

        # Increment the sequence number. This handles the (rare) case of a
        # sequence number overflowing a long integer, and resets it safely to 0
        # (as required by the SSH2 protocol).
        def increment_sequence_number
          @sequence_number += 1
          @sequence_number = 0 if @sequence_number > 0xFFFFFFFF
        end
        private :increment_sequence_number

      end

      # Handles the compression and encryption of outgoing packets.
      class OutgoingPacketStream < PacketStream

        # Create a new OutgoingPacketStream.
        def initialize( ciphers, hmacs, compressors )
          super( ciphers, hmacs )
          @compressor = compressors.fetch( "none" )
          @mutex = Mutex.new
        end

        # Set the cipher, mac, and compressor to the given values.
        def set_algorithms( cipher, hmac, compressor )
          super( cipher, hmac )
          @compressor = compressor
        end

        # Send the given payload over the socket, after (possibly) compressing
        # and encrypting it. The payload is converted to a string (using #to_s)
        # before being manipulated.
        def send( payload )
          @mutex.synchronize do
            # force the payload into a string
            payload = @compressor.compress( payload.to_s )

            # the length of the packet, minus the padding
            actual_length = 4 + payload.length + 1

            # compute the padding length
            padding_length = @cipher.block_size -
              ( actual_length % @cipher.block_size )
            padding_length += @cipher.block_size if padding_length < 4

            # compute the packet length (sans the length field itself)
            packet_length = payload.length + padding_length + 1

            if packet_length < 16
              padding_length += @cipher.block_size
              packet_length = payload.length + padding_length + 1
            end

            padding = Array.new( padding_length ) { rand(256) }.pack("C*")

            unencrypted_data = [ packet_length, padding_length, payload,
              padding ].pack( "NCA*A*" )
            mac = compute_hmac( unencrypted_data )

            encrypted_data = @cipher.update( unencrypted_data ) << @cipher.final
            message = encrypted_data + mac
            
            # send package, in case package was only partially transferred, retry
            counter = message.size
            while counter > 0
              begin
                counter -= @socket.send message[(message.size-counter)..message.size], 0
              rescue Errno::EINTR
                retry
              end
            end

            increment_sequence_number
          end
        end

      end

      # Handles the decompression and dencryption of incoming packets.
      class IncomingPacketStream < PacketStream

        # A handle to the buffer factory to use when creating buffers
        attr_writer :buffers

        # A handle to the logger instance to use for writing log messages
        attr_writer :log

        # Create a new IncomingPacketStream.
        def initialize( ciphers, hmacs, decompressors )
          super( ciphers, hmacs )
          @decompressor = decompressors.fetch( "none" )
          @mutex = Mutex.new
        end

        # Set the cipher, mac, and decompressor algorithms to the given values.
        def set_algorithms( cipher, mac, decompressor )
          super( cipher, mac )
          @decompressor = decompressor
        end

        # Retrieve the next packet from the string, after (possibly) decrypting
        # and decompressing it. The packet is returned as a reader buffer.
        def get
          @mutex.synchronize do
            # get the first block of data
            if @log.debug?
              @log.debug "reading #{@cipher.block_size} bytes from socket..."
            end

            data = read( @cipher.block_size )

            # decipher it
            reader = @buffers.reader( @cipher.update( data ) )

            # determine the packet length and how many bytes remain to be read
            packet_length = reader.read_long
            remaining_to_read = packet_length + 4 - @cipher.block_size
            if @log.debug?
              @log.debug "packet length(#{packet_length}) " +
                "remaining(#{remaining_to_read})"
            end

            # read the remainder of the packet and decrypt it.
            data = read( remaining_to_read )

            # get the hmac from the tail of the packet (if one exists), and
            # then validate it.
            hmac = @hmac.mac_length > 0 ? read( @hmac.mac_length ) : ""

            reader.append @cipher.update( data ) unless data.empty?
            reader.append @cipher.final

            padding_length = reader.read_byte

            payload = reader.read( packet_length - padding_length - 1 )
            padding = reader.read( padding_length ) if padding_length > 0

            my_computed_hmac = compute_hmac( reader.content )
            raise Net::SSH::Exception, "corrupted mac detected" if hmac != my_computed_hmac

            # decompress the payload
            payload = @decompressor.decompress( payload )

            increment_sequence_number

            buffer = @buffers.reader( payload )
            @log.debug "received: #{buffer.content.inspect}" if @log.debug?

            return buffer
          end
        end

        def read( length )
          if IO === @socket
          data = ""
            begin
              while data.length < length
                break if @socket.closed?
                if ( IO.select([@socket],nil,nil,0.01) rescue nil )
                  data << @socket.read(length-data.length)
                end
              end
            rescue Errno::EINTR
              retry
            end
          else
            data = @socket.recv(length)
          end

          # if the data is less than expected, the socket was closed
          if data.nil? || data.length < length
            raise Net::SSH::Transport::Disconnect,
              "connection closed by remote host"
          end

          data
        end
        private :read

      end

    end
  end
end
