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

require 'openssl'
require 'net/ssh/util/buffer'
require 'net/ssh/transport/ossl/buffer'

module Net
  module SSH
    module Transport

      module OSSL

        # A factory class for returning new buffer instances that have been
        # decorated to also handle OpenSSL specific information.
        class BufferFactory

          # Return a new reader buffer that can also read bignums and keys.
          def reader( text )
            Net::SSH::Transport::OSSL::ReaderBuffer.new( text )
          end

          # Return a new writer buffer, initialized with the parameter.
          def writer( text="" )
            Net::SSH::Util::WriterBuffer.new( text )
          end

          # Return a new general buffer that can also read bignums and keys.
          def buffer( text="" )
            Net::SSH::Transport::OSSL::Buffer.new( text )
          end

        end

      end

    end
  end
end
