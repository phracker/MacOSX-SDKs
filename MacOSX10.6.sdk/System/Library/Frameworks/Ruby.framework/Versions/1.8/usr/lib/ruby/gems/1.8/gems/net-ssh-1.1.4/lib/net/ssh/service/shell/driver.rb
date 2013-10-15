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
    module Service
      module Shell

        # The service driver for the Shell service. It manages the creation of
        # new Shell::Shell and Shell::SyncShell subservices.
        #
        # Usage:
        #
        #   Net::SSH.start( host ) do |session|
        #     shell = session.shell.open
        #
        #     shell.cd "/home/foo"
        #     shell.mkdir "-p some/long/dir"
        #     shell.cd "some/long/dir"
        #     shell.touch "foo.txt"
        #     shell.exit
        #
        #     session.loop
        #   end
        #
        # Or:
        #
        #   Net::SSH.start( host ) do |session|
        #     shell = session.shell.sync
        #
        #     shell.cd "/home/foo"
        #
        #     out = shell.test "-e some/file.txt"
        #     if out.status == 0
        #       out = shell.cat "some/file.txt"
        #       puts out.stdout
        #     else
        #       puts "no such file 'some/file.txt'"
        #     end
        #
        #   end
        class Driver

          # Create a new driver with the given logger and shell and
          # sync factories.
          def initialize( log, shell_factory, sync_factory )
            @log = log
            @shell_factory = shell_factory
            @sync_factory = sync_factory
          end

          # Open a new shell, using the Shell::Shell subservice and
          # the given options.
          def open( options={} )
            pty_opts = options[:pty]

            @shell_factory.call( pty_opts )
          end
          
          # Open a new shell, using the Shell::SyncShell subservice and
          # the given options.
          def sync( options={} )
            pty_opts = options[:pty]

            @sync_factory.call( pty_opts )
          end
          
        end

      end # Shell
    end # Service
  end # SSH
end # Net
