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

require 'stringio'

module Net
  module SSH
    module Service
      module Shell

        # A version of Shell::Shell that acts synchronously, allowing clients
        # to execute a command via a shell, wait for it to finish, and then
        # inspect both the stdout and stderr from the command, as well as the
        # exit status.
        class SyncShell

          # A struct representing the result of executing a command.
          CommandOutput = Struct.new( :stdout, :stderr, :status )

          # The unique confirmation string that is used to recognize the
          # end of a command's execution.
          CONFIRMATION = "2357foobarbazzabraboof7532"

          # Create a new SyncShell that uses the given +shell+ factory to obtain
          # a shell to wrap. The other parameters are used
          def initialize( shell, log, pty_opts )
            @log = log
            @shell = shell.call( pty_opts )
          end

          # Delegates to Shell::Shell.open?
          def open?
            @shell.open?
          end

          # Attempts to invoke the given command, which must not be
          # terminated with a newline. If +stdin+ is not nil, it will be sent
          # to the shell immediately after sending the request to execute the
          # command. It is expected that this will be used by the program that
          # was just executed somehow, but this is not (cannot) be enforced.
          def send_command( cmd, stdin=nil )
            @log.debug "executing #{cmd.inspect}" if @log.debug?
            send_data "#{cmd}; printf '%s %d' #{CONFIRMATION} $?\n"
            send_data stdin if stdin

            out = ""
            err = ""

            @log.debug "waiting for #{cmd.inspect}" if @log.debug?
            loop do
              sleep 0.01
              out << @shell.stdout while @shell.open? && @shell.stdout?
              err << @shell.stderr while @shell.open? && @shell.stderr?

              break if !@shell.open? || out.index( CONFIRMATION + " " )
            end

            if @log.debug?
              @log.debug "#{cmd.inspect} finished"
              @log.debug " stdout --> #{out.inspect}"
              @log.debug " stderr --> #{err.inspect}"
            end

            if @shell.open?
              match = out.match( /#{CONFIRMATION} /o )
              out = match.pre_match
              status = match.post_match.strip.to_i
            else
              status = 0
            end

            CommandOutput.new( out, ( err.empty? ? nil : err ), status )
          end

          # Sends the given string directly to the shell, without waiting for
          # any response.
          def send_data( data )
            @shell.send_data data
          end

          # Dends the given string directly to the shell as the given type of
          # data, without waiting for any response.
          def send_extended_data( type, data )
            @shell.send_extended_data type, data
          end

          # Reinterprets missing methods as requests to execute commands. The
          # parameters to the method are concatenated together with spaces
          # and sent to the shell via #send_command.
          def method_missing( sym, *args )
            cmd = sym.to_s
            cmd << " " << args.join( " " ) unless args.empty?
            send_command cmd
          end

        end

      end # SyncShell
    end # Service
  end # SSH
end # Net
