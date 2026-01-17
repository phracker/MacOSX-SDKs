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

require 'net/sftp/errors'

module Net ; module SFTP ; module Operations

  module Constants
    FX_OK                     = 0
    FX_EOF                    = 1
    FX_NO_SUCH_FILE           = 2
    FX_PERMISSION_DENIED      = 3
    FX_FAILURE                = 4
    FX_BAD_MESSAGE            = 5
    FX_NO_CONNECTION          = 6
    FX_CONNECTION_LOST        = 7
    FX_OP_UNSUPPORTED         = 8
    FX_INVALID_HANDLE         = 9
    FX_NO_SUCH_PATH           = 10
    FX_FILE_ALREADY_EXISTS    = 11
    FX_WRITE_PROTECT          = 12
    FX_NO_MEDIA               = 13
    FX_NO_SPACE_ON_FILESYSTEM = 14
    FX_QUOTA_EXCEEDED         = 15
    FX_UNKNOWN_PRINCIPLE      = 16
    FX_LOCK_CONFlICT          = 17
    FX_DIR_NOT_EMPTY          = 18
    FX_NOT_A_DIRECTORY        = 19
    FX_INVALID_FILENAME       = 20
    FX_LINK_LOOP              = 21
  end

  # A exception class for reporting a non-success result of an operation.
  class StatusException < Net::SFTP::Exception

    # The error code (numeric)
    attr_reader :code

    # The description of the error
    attr_reader :description

    # The language in which the description is being reported (usually the
    # empty string)
    attr_reader :language

    # Create a new status exception that reports the given code and
    # description.
    def initialize( code, description, language )
      @code = code
      @description = description
      @language = language
    end

    # Override the default message format, to include the code and
    # description.
    def message
      m = super
      m << " (#{code}, #{description.inspect})"
    end

  end

end ; end ; end
