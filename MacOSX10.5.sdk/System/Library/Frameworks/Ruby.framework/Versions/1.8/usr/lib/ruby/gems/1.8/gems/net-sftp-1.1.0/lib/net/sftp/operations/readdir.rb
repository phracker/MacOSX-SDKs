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

  # Implements the +readdir+ operation. This will handle the continuous calls
  # to +readdir+ until the entire contents of the directory have been read,
  # returning them in a single array.
  class Readdir < Abstract

    # Performs the operation.
    def perform( handle )
      @items = []
      @handle = handle
      @driver.readdir nil, @handle
    end

    # Invoked when the server returns a list of "names". Requests +readdir+
    # again, automatically.
    def do_name( items )
      @log.debug "[#{@id}] got #{items.length} items" if @log.debug?
      @items.concat items
      @driver.readdir @id, @handle
      @session.register @id, self
    end

    # Invoked when a status code is received from the server. If the code is
    # FX_OK or FX_EOF then there is nothing left to read and the callback is
    # invoked. Other status codes are handled by the superclass.
    def do_status( code, message, language )
      if code == FX_OK || code == FX_EOF
        @callback[ OK, @items ]
      else
        super
      end
    end

  end

end ; end ; end
