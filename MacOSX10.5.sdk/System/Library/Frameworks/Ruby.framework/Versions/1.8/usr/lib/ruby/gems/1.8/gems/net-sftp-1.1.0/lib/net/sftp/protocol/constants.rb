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

module Net ; module SFTP ; module Protocol

  module Constants

    FXP_INIT             = 1
    FXP_VERSION          = 2
    FXP_OPEN             = 3
    FXP_CLOSE            = 4
    FXP_READ             = 5
    FXP_WRITE            = 6
    FXP_LSTAT            = 7
    FXP_FSTAT            = 8
    FXP_SETSTAT          = 9
    FXP_FSETSTAT         = 10
    FXP_OPENDIR          = 11
    FXP_READDIR          = 12
    FXP_REMOVE           = 13
    FXP_MKDIR            = 14
    FXP_RMDIR            = 15
    FXP_REALPATH         = 16
    FXP_STAT             = 17
    FXP_RENAME           = 18
    FXP_READLINK         = 19
    FXP_SYMLINK          = 20

    FXP_STATUS           = 101
    FXP_HANDLE           = 102
    FXP_DATA             = 103
    FXP_NAME             = 104
    FXP_ATTRS            = 105

    FXP_EXTENDED         = 106
    FXP_EXTENDED_REPLY   = 107

    FXP_RENAME_OVERWRITE = 0x00000001
    FXP_RENAME_ATOMIC    = 0x00000002
    FXP_RENAME_NATIVE    = 0x00000004

    FX_OK                = 0
    FX_EOF               = 1

  end

end ; end ; end
