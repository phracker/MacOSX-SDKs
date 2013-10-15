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

require 'net/sftp/protocol/02/packet-assistant'

module Net ; module SFTP ; module Protocol ; module V_03

  # The packet assistant which formats packets for version 3 of the SFTP
  # protocol. This adds support for the readlink and symlink packets:
  #
  # * readlink( id, path )
  # * symlink( id, link, target )
  class PacketAssistant < V_02::PacketAssistant

    packet :readlink, :string  # path

    packet :symlink,  :string, # link-path
                      :string  # target-path

  end

end ; end ; end ; end
