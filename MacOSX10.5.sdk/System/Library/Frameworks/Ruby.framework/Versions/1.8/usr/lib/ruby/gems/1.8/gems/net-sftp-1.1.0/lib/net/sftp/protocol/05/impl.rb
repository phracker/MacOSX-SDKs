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

require 'net/sftp/protocol/04/impl'

module Net ; module SFTP ; module Protocol ; module V_05

  # The implementation of the operations available to version 5 of the SFTP
  # protocol.
  class Impl < V_04::Impl

    F_CREATE_NEW         = 0x00000000
    F_CREATE_TRUNCATE    = 0x00000001
    F_OPEN_EXISTING      = 0x00000002
    F_OPEN_OR_CREATE     = 0x00000003
    F_TRUNCATE_EXISTING  = 0x00000004

    F_APPEND_DATA        = 0x00000008
    F_APPEND_DATA_ATOMIC = 0x00000010
    F_TEXT_MODE          = 0x00000020
    F_READ_LOCK          = 0x00000040
    F_WRITE_LOCK         = 0x00000080
    F_DELETE_LOCK        = 0x00000100

    module ACE
      F_READ_DATA         = 0x00000001
      F_LIST_DIRECTORY    = 0x00000001
      F_WRITE_DATA        = 0x00000002
      F_ADD_FILE          = 0x00000002
      F_APPEND_DATA       = 0x00000004
      F_ADD_SUBDIRECTORY  = 0x00000004
      F_READ_NAMED_ATTRS  = 0x00000008
      F_WRITE_NAMED_ATTRS = 0x00000010
      F_EXECUTE           = 0x00000020
      F_DELETE_CHILD      = 0x00000040
      F_READ_ATTRIBUTES   = 0x00000080
      F_WRITE_ATTRIBUTES  = 0x00000100
      F_DELETE            = 0x00010000
      F_READ_ACL          = 0x00020000
      F_WRITE_ACL         = 0x00040000
      F_WRITE_OWNER       = 0x00080000
      F_SYNCHRONIZE       = 0x00100000
    end

    # The open operation changed in version 4. This method keeps the same
    # interface as previous versions, but changes how the parameters are
    # interpreted and converted into a packet.
    def open( id, path, flags, mode=0660 )
      sftp_flags, desired_access = case
        when flags & IO::WRONLY != 0 then
          [ F_CREATE_TRUNCATE,
            ACE::F_WRITE_DATA | ACE::F_WRITE_ATTRIBUTES ]
        when flags & IO::RDWR   != 0 then
          [ F_OPEN_OR_CREATE,
            ACE::F_READ_DATA | ACE::F_READ_ATTRIBUTES |
            ACE::F_WRITE_DATA | ACE::F_WRITE_ATTRIBUTES ]
        when flags & IO::APPEND != 0 then
          [ F_OPEN_OR_CREATE | F_APPEND_DATA,
            ACE::F_WRITE_DATA | ACE::F_WRITE_ATTRIBUTES |
            ACE::F_APPEND_DATA ]
        else
          [ F_OPEN_EXISTING,
            ACE::F_READ_DATA | ACE::F_READ_ATTRIBUTES ]
      end

      sftp_flags |= F_OPEN_OR_CREATE if flags & IO::CREAT != 0
      sftp_flags |= F_TRUNCATE_EXISTING if flags & IO::TRUNC != 0

      attributes = @attr_factory.empty
      attributes.permissions = mode

      open_raw id, path, desired_access, sftp_flags, attributes
    end

  end

end ; end ; end ; end
