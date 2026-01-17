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

require 'net/sftp/protocol/03/packet-assistant'

module Net ; module SFTP ; module Protocol ; module V_04

  # Version 4 of the SFTP protocol changed the number of parameters to several
  # different packet types:
  #
  # * rename( id, old, new, flags )
  # * stat( id, path, flags )
  # * lstat( id, path, flags )
  # * fstat( id, handle, flags )
  class PacketAssistant < V_03::PacketAssistant

    packet :rename,   :string, # old name
                      :string, # new name
                      :long    # flags

    packet :stat,     :string, # path
                      :long    # flags

    packet :lstat,    :string, # path
                      :long    # flags

    packet :fstat,    :string, # handle
                      :long    # flags

  end

end ; end ; end ; end
