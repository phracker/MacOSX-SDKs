#--
# =============================================================================
# Copyright (c) 2004,2005 Jamis Buck (jamis@37signals.com)
# All rights reserved.
#
# This source file is distributed as part of the Net::SSH Secure Shell Client
# library for Ruby. This file (and the library as a whole) may be used only as
# allowed by either the BSD license, or the Ruby license (or, by association
# with the Ruby license, the GPL). See the "doc" subdirectory of the Net::SSH
# distribution for the texts of these licenses.
# -----------------------------------------------------------------------------
# net-ssh website : http://net-ssh.rubyforge.org
# project website: http://rubyforge.org/projects/net-ssh
# =============================================================================
#++

module Net
  module SSH
    module Transport

      module Constants

        # Transport layer generic messages

        DISCONNECT                = 1
        IGNORE                    = 2
        UNIMPLEMENTED             = 3
        DEBUG                     = 4
        SERVICE_REQUEST           = 5
        SERVICE_ACCEPT            = 6

        # Algorithm negotiation messages

        KEXINIT                   = 20
        NEWKEYS                   = 21

        # Key exchange method specific messages

        KEXDH_INIT                = 30
        KEXDH_REPLY               = 31

      end

      module DisconnectReasons

        HOST_NOT_ALLOWED_TO_CONNECT    =  1
        PROTOCOL_ERROR                 =  2
        KEY_EXCHANGE_FAILED            =  3
        RESERVED                       =  4
        MAC_ERROR                      =  5
        COMPRESSION_ERROR              =  6
        SERVICE_NOT_AVAILABLE          =  7
        PROTOCOL_VERSION_NOT_SUPPORTED =  8
        HOST_KEY_NOT_VERIFIABLE        =  9
        CONNECTION_LOST                = 10
        BY_APPLICATION                 = 11
        TOO_MANY_CONNECTIONS           = 12
        AUTH_CANCELLED_BY_USER         = 13
        NO_MORE_AUTH_METHODS_AVAILABLE = 14
        ILLEGAL_USER_NAME              = 15

      end

    end
  end
end
