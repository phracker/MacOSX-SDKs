#--
# =============================================================================
# Copyright (c) 2004, Jamis Buck (jamis@37signals.com)
# All rights reserved.
#
# This source file is distributed as part of the Net::SFTP Secure FTP Client
# library for Ruby. This file (and the library as a whole) may be used only as
# allowed by either the BSD license, or the Ruby license (or, by association
# with the Ruby license, the GPL). See the "doc" subdirectory of the Net::SFTP
# distribution for the texts of these licenses.
# -----------------------------------------------------------------------------
# net-sftp website: http://net-ssh.rubyforge.org/sftp
# project website : http://rubyforge.org/projects/net-ssh
# =============================================================================
#++

require 'net/sftp/operations/abstract'

module Net ; module SFTP ; module Operations

  # Implements the +read+ operation, which reads data from an open file handle.
  # This also implements the common case of reading to the end of the file. In
  # that case, the callback is guaranteed to receive the contents of the entire
  # file in one chunk.
  class Read < Abstract

    # The default maximum amount of data to read at once when reading an entire
    # file.
    DEFAULT_CHUNK_SIZE = 64 * 1024

    # Perform the operation. If length is less than 0 (the default), then the
    # entire file (from the given offset) will be read and returned in "one
    # fell swoop". Otherwise, the given length of data will be requested.
    def perform( handle, options={} )
      @length = options[:length] || -1
      @handle = handle
      @offset = options[:offset] || 0
      @chunk_size = options[:chunk_size] || DEFAULT_CHUNK_SIZE
      @progress_callback = options[:progress_callback]
      @data = ""

      real_length = ( @length >= 0 && @length < @chunk_size ?
                          @length : @chunk_size )
      @driver.read( nil, @handle, @offset, real_length )
    end

    # Invoked when a data packet is received from the server. If the original
    # request was for an entire file, this will send another read request,
    # offset to the end of the data that has been read so far. Otherwise, the
    # callback will be invoked directly.
    def do_data( data )
      @log.debug "[#{@id}] got #{data.length} bytes" if @log.debug?

      @data << data
      @progress_callback[@data] if @progress_callback

      if @length < 0 || @data.length < @length
        if @length < 0
          length = @chunk_size
        else
          length = @length - @data.length
          length = length > @chunk_size ? @chunk_size : length
        end

        @log.debug "[#{@id}] requesting #{length} more bytes" if @log.debug?
        @driver.read @id, @handle, @offset + @data.length, length
        @session.register( @id, self )
      else
        @callback[ OK, @data ]
      end
    end

    # Invoked when a status code is received from the server. If the code is
    # FX_EOF, then no data could be read because the end of the file was
    # reached. In this case, the callback is invoked with the data that has been
    # read so far. Other status codes are handled by the superclass.
    def do_status( code, message, language )
      if code == FX_EOF
        @log.debug "[#{@id}] got EOF" if @log.debug?
        @callback[ OK, @data ]
      else
        super
      end
    end

  end

end ; end ; end
