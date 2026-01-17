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

require 'net/ssh/session'

#--
# Documentation Roadmap:
#
#   1. Start with net/ssh/session.rb (Net::SSH::Session). This creates a new
#      Needle registry and registers all the services.
#
#   2. Look at net/ssh/transport/services.rb to see how the transport services
#      are defined, and what classes implement each of them.
#
#   3. Look at net/ssh/transport/session.rb (Net::SSH::Transport::Session). This
#      implements the driver for the transport layer.
#
#   4. Look at net/ssh/userauth/services.rb to see how the services for the
#      user authentication layer are defined, and implemented.
#
#   5. Look at net/ssh/connection/services.rb to see how the services for the
#      connection layer are defined and implemented.
#
#   6. Look at net/ssh/service/services.rb to see how the auxiliary services
#      (process and forward) are defined.
#++

module Net
  module SSH

    # A convenience method for starting a new SSH session. See
    # Net::SSH::Session.
    def start( *args, &block )
      Net::SSH::Session.new( *args, &block )
    end
    module_function :start

    # A registry of external (i.e., third-party) services that should be made
    # available to any SSH session.
    EXTERNAL_SERVICES = Hash.new

    # Used by third-parties to register a service that should be made available
    # to any SSH session when the session is constructed. The block should take
    # a two parameters--the dependency injection container that should contain
    # the services, and the service-point for the service being registered.
    #
    # The +name+ parameter should be a symbol.
    def register_service( name, &block )
      EXTERNAL_SERVICES[ name ] = block
    end
    module_function :register_service

  end
end
