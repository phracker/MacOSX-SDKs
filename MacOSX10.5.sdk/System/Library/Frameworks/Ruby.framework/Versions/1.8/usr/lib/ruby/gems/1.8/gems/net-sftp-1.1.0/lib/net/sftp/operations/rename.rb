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

  # Implements the +rename+ operation.
  class Rename < Abstract

    # Perform the operation. The flags parameter is ignored under earlier
    # versions of the SFTP protocol (3 and under).
    def perform( filename, new_name, flags=0 )
      @driver.rename( nil, filename, new_name, flags )
    end

  end

end ; end ; end
