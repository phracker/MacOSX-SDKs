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

require 'net/sftp/protocol/02/impl'

module Net ; module SFTP ; module Protocol ; module V_03

  # The implementation of the operations for version 3 of the SFTP protocol.
  # This adds support for the readlink and symlink operations.
  class Impl < V_02::Impl

    operation :readlink,
              :symlink

    # The #status message changed in this version. It adds +message+ and
    # +language+ fields, so the callback now receives +driver+, +id+, +code+,
    # +message+, and +language+ as parameters.
    def do_status( channel, content )
      return unless has_on_status?
      id = content.read_long
      code = content.read_long
      message = content.read_string
      language = content.read_string
      call_on_status( driver, id, code, message, language )
    end
    
  end

end ; end ; end ; end
