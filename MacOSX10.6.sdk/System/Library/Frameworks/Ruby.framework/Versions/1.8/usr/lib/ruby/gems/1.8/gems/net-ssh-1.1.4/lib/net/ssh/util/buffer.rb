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

    module Util

      # The abstract ancestor module of both ReaderBufferImpl and
      # WriterBufferImpl. It defines the common interface for both submodules.
      module BufferBase

        # exposes the content of the buffer
        attr_reader :content

        # the length of the buffer's content.
        def length
          @content.length
        end

        # returns a copy of the buffer's content.
        def to_s
          ( @content || "" ).dup
        end

        # Compares the contents of the two buffers.
        def ==( buffer )
          to_s == buffer.to_s
        end

        # Resets the buffer, making it empty.
        def clear!
          @content = ""
        end

        def init_BufferBase( content="" )
          @content = content
        end
        private :init_BufferBase

      end

      # A convenience module for representing a string of encoded data. It
      # provides an interface for easily reading and decoding the buffer.
      module ReaderBufferImpl

        # the current position of the pointer in the buffer
        attr_reader :position

        # used by derived modules and classes to perform any
        # reader-buffer-specific initialization.
        def init_ReaderBufferImpl
          @position = 0
        end
        private :init_ReaderBufferImpl

        # Appends the given text to the end of the buffer.
        def append( text )
          @content << text
        end

        # Returns all text from the current pointer to the end of the buffer as
        # a new buffer as the same class as the receiver.
        def remainder_as_buffer
          self.class.new( @content[ @position..-1 ] )
        end

        # Reads +count+ bytes from the buffer. If +count+ is +nil+, this will
        # return all remaining text in the buffer. This method will increment
        # the pointer.
        def read( count = nil )
          count = length - @position unless count
          return nil if @position + count > length

          @position += count
          @content[ @position-count, count ]
        end

        # Return the next 8 bytes as a 64-bit integer (in network byte order).
        def read_int64
          hi = read_long
          lo = read_long
          return ( hi << 32 ) + lo
        end

        # Return the next four bytes as a long integer (in network byte order).
        def read_long
          b = read( 4 ) or return nil
          b.unpack( "N" ).first
        end

        # Read the next two bytes as a short integer (in network byte order).
        def read_short
          b = read( 2 ) or return nil
          b.unpack( "n" ).first
        end

        # Read and return the next byte in the buffer.
        def read_byte
          b = read( 1 ) or return nil
          b[0]
        end

        # Read and return an SSH2-encoded string. The string starts with a long
        # integer that describes the number of bytes remaining in the string.
        def read_string
          length = read_long or return nil
          read( length )
        end

        # Read a single byte and convert it into a boolean, using 'C' rules
        # (i.e., zero is false, non-zero is true).
        def read_bool
          b = read( 1 ) or return nil
          b[0] != 0
        end

        # Resets the pointer to the start of the buffer.
        def reset!
          @position = 0
        end

        # Returns true if the pointer is at the end of the buffer.
        def eof?
          @position >= length
        end

        # Resets the buffer, making it empty.
        def clear!
          @content = ""
          @position = 0
        end

      end # ReaderBufferImpl

      # A convenience module for writing a string of encoded data. It provides
      # an interface for easily writing and encoding data.
      module WriterBufferImpl

        def init_WriterBufferImpl
          # nothing
        end
        private :init_WriterBufferImpl

        # Writes the given data literally into the string.
        def write( *data )
          @content << data.join
        end

        # Writes each argument to the buffer as a network-byte-order-encoded
        # 64-bit integer (8 bytes).
        def write_int64( *n )
          n.each do |i|
            hi = ( i >> 32 ) & 0xFFFFFFFF
            lo = i & 0xFFFFFFFF
            @content << [ hi, lo ].pack( "N2" )
          end
        end

        # Writes each argument to the buffer as a network-byte-order-encoded
        # long (4-byte) integer.
        def write_long( *n )
          @content << n.pack( "N*" )
        end

        # Writes each argument to the buffer as a network-byte-order-encoded
        # short (2-byte) integer.
        def write_short( *n )
          @content << n.pack( "n*" )
        end

        # Writes each argument to the buffer as a byte.
        def write_byte( *n )
          @content << n.map { |c| c.chr }.join
        end

        # Writes each argument to the buffer as an SSH2-encoded string. Each
        # string is prefixed by its length, encoded as a 4-byte long integer.
        def write_string( *text )
          text.each do |string|
            write_long( string.length )
            write( string )
          end
        end

        # Writes each argument to the buffer as a (C-style) boolean, with 1
        # meaning true, and 0 meaning false.
        def write_bool( *b )
          @content << b.map { |v| ( v ? 1 : 0 ).chr }.join
        end

        # Writes each argument to the buffer as a bignum (SSH2-style). No
        # checking is done to ensure that the arguments are, in fact, bignums.
        def write_bignum( *n )
          @content << n.map { |b| b.to_ssh }.join
        end

        # Writes the given arguments to the buffer as SSH2-encoded keys.
        def write_key( *key )
          key.each do |k|
            write_string( k.ssh_type )

            case k.ssh_type
              when "ssh-dss"
                write_bignum( k.p )
                write_bignum( k.q )
                write_bignum( k.g )
                write_bignum( k.pub_key )

              when "ssh-rsa"
                write_bignum( k.e )
                write_bignum( k.n )

              else
                raise NotImplementedError,
                  "unsupported key type '#{k.ssh_type}'"
            end
          end
        end

      end # class WriterBufferImpl

      # A convenience class for a read-only buffer.
      class ReaderBuffer
        include BufferBase
        include ReaderBufferImpl

        def initialize( content )
          init_BufferBase( content )
          init_ReaderBufferImpl
        end
      end

      # A convenience class for a write-only buffer.
      class WriterBuffer
        include BufferBase
        include WriterBufferImpl

        def initialize( content="" )
          init_BufferBase( content )
          init_WriterBufferImpl
        end
      end

      # A convenience class for a read/write buffer.
      class Buffer
        include BufferBase
        include ReaderBufferImpl
        include WriterBufferImpl

        def initialize( content="" )
          init_BufferBase( content )
          init_ReaderBufferImpl
          init_WriterBufferImpl
        end
      end

    end # module Util

  end # module SSH
end # module Net
