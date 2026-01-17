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

    # The ancestor class of all exceptions raised in the Net::SSH module.
    class Exception < StandardError; end

    # Raised when user authentication failed.
    class AuthenticationFailed < Exception; end

    # Raised when the cached key for a particular host does not match the
    # key given by the host, which can be indicative of a man-in-the-middle
    # attack. When rescuing this exception, you can inspect the key fingerprint
    # and, if you want to proceed anyway, simply call the remember_host!
    # method on the exception, and then retry.
    class HostKeyMismatch < Exception
      attr_writer :callback, :data

      def [](key)
        @data[key]
      end

      def fingerprint
        @data[:fingerprint]
      end

      def host
        @data[:peer][:host]
      end

      def port
        @data[:peer][:port]
      end

      def ip
        @data[:peer][:ip]
      end

      def key
        @data[:key]
      end

      def remember_host!
        @callback.call
      end
    end
  end
end
