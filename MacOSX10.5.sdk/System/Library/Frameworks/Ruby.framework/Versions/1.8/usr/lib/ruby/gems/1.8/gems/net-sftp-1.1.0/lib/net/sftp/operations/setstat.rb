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

  # Implements the +setstat+ operation.
  class Setstat < Abstract

    # Perform the operation. The +hash+ parameter is a hash of attributes that
    # should be set on the file or directory indicated by the +path+.
    def perform( path, hash )
      attrs = @driver.attr_factory.from_hash( hash )
      @driver.setstat( nil, path, attrs )
    end

  end

end ; end ; end
