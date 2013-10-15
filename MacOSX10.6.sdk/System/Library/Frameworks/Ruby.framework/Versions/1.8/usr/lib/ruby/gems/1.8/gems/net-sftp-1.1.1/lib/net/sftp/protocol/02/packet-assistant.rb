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

require 'net/sftp/protocol/01/packet-assistant'

module Net ; module SFTP ; module Protocol ; module V_02

  # The packet assistant, used to format packets for version 2 of the SFTP
  # protocol. This simply adds support for the RENAME packet:
  #
  # * rename( id, old, new )
  class PacketAssistant < V_01::PacketAssistant

    packet :rename,   :string, # old name
                      :string  # new name

  end

end ; end ; end ; end
