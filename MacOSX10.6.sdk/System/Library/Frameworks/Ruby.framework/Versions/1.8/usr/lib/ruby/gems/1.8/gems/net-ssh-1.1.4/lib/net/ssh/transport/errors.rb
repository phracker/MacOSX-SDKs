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

require 'net/ssh/errors'

module Net
  module SSH
    module Transport

      # The parent class of all exceptions raised in the transport layer of
      # the Net::SSH module.
      class Exception < Net::SSH::Exception; end

      # Raised when the implementation for a requested cipher algorithm could
      # not be found.
      class CipherNotFound < Exception; end

      # Raised when the implementation for a requested HMAC algorithm could not
      # be found.
      class HMACAlgorithmNotFound < Exception; end

      # Raised when the implementation for a requested Key could not be found.
      class KeyTypeNotFound < Exception; end

      # Raised when the implementation for a requested Digest could not be
      # found.
      class DigestTypeNotFound < Exception; end

      # Raised when the server unexpectedly disconnects.
      class Disconnect < Exception; end

    end
  end
end
