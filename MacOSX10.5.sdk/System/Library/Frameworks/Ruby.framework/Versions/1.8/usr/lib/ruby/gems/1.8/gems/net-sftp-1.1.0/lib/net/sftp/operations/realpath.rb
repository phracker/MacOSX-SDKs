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

  # Implements the +realpath+ operation.
  class Realpath < Abstract

    # Perform the operation.
    def perform( path )
      @driver.realpath( nil, path )
    end

    # A convenience--returns the first (and only) element of the array of items
    # that is returned, instead of returning the array itself.
    def do_name( items )
      @callback[ OK, items.first ]
    end

  end

end ; end ; end
