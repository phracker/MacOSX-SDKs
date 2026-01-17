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

require 'net/sftp/protocol/01/impl'

module Net ; module SFTP ; module Protocol ; module V_02

  # The implementation of the operations defined by version 2 of the SFTP
  # protocol. This simply adds support for the RENAME operation, otherwise
  # extending the version 1 implementation, unaltered.
  class Impl < V_01::Impl

    operation :rename

    alias :rename_raw :rename

    # This operation is special since a later version of the protocol adds
    # support for flags. In this version, the flags parameter is ignored,
    # but it exists for compatibility with later versions.
    def rename( id, name, new_name, flags=nil )
      rename_raw id, name, new_name
    end

  end

end ; end ; end ; end
