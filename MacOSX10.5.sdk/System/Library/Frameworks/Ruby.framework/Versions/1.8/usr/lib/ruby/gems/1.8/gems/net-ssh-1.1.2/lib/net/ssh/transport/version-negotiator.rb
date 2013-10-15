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

      # Manages the negotiation of the version strings between client and
      # server.
      class VersionNegotiator

        # For processing the version header. The version reported by the server
        # must match this pattern.
        VERSION_LINE = /^SSH-/

        # Only versions matching this pattern are supported by Net::SSH.
        REQUIRED_VERSION_PATTERN = /^SSH-(1.99|2.0)-/

        # An array of lines returned by the server prior to reporting the
        # version.
        attr_reader :header_lines

        # Creates a new VersionNegotiator object that logs to the given logger
        # instance.
        def initialize( logger )
          @logger = logger
        end

        # Negotiate version information over the given socket. This will
        # return the version reported by the server.
        def negotiate( socket, version )
          server_version = ""
          @header_lines = []

          loop do
            server_version = socket.readline
            break if server_version.nil? || VERSION_LINE.match( server_version )
            @header_lines << server_version
          end

          if !REQUIRED_VERSION_PATTERN.match( server_version )
            raise Net::SSH::Exception,
              "incompatible ssh version #{server_version.inspect}"
          end

          if @logger.debug?
            @logger.debug "remote server is #{server_version.chomp.inspect}"
          end
          socket.print "#{version}\r\n"

          return server_version.chomp
        end

      end

    end
  end
end
