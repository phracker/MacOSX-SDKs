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
    module Connection

      module Constants

        # Connection protocol generic messages

        GLOBAL_REQUEST            = 80
        REQUEST_SUCCESS           = 81
        REQUEST_FAILURE           = 82

        # Channel related messages

        CHANNEL_OPEN              = 90
        CHANNEL_OPEN_CONFIRMATION = 91
        CHANNEL_OPEN_FAILURE      = 92
        CHANNEL_WINDOW_ADJUST     = 93
        CHANNEL_DATA              = 94
        CHANNEL_EXTENDED_DATA     = 95
        CHANNEL_EOF               = 96
        CHANNEL_CLOSE             = 97
        CHANNEL_REQUEST           = 98
        CHANNEL_SUCCESS           = 99
        CHANNEL_FAILURE           = 100

      end

    end
  end
end
