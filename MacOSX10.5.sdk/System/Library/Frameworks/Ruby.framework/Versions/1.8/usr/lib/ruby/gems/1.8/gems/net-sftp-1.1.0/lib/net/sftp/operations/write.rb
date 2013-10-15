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

  # Implements the +write+ operation. Handles, automatically, the looping
  # necessary to write a large data set.
  class Write < Abstract

    # The maximum size of data that will be written at one time.
    CHUNK_SIZE = 32 * 1024

    # Perform the operation. Only CHUNK_SIZE portions of the +data+ parameter
    # will be written at a time, with subsequent chunks being writteni
    # automatically when prior chunks complete.
    def perform( handle, data, offset=0 )
      @handle = handle
      @offset = offset
      @data = data
      @pos = 0

      @driver.write( nil, handle, offset, data[0,CHUNK_SIZE] )
    end

    # Invoked when the server sends a status packet. If the status is FX_OK,
    # then the callback is invoked (if all data has been written), or the
    # next chunk is written to the server (if more data remains). Other
    # status codes are handled by the superclass.
    def do_status( code, message, language )
      if code == FX_OK
        @log.debug "[#{@id}] chunk written" if @log.debug?
        @pos += CHUNK_SIZE

        if @pos > @data.length
          @callback[ OK ]
          return
        end

        @driver.write @id, @handle, @offset + @pos, @data[@pos,CHUNK_SIZE]
        @session.register @id, self
      else
        super
      end
    end

  end

end ; end ; end
