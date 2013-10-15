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
    module Service
      module Process
      
        # Represents a process executing on the remote machine. It also provides
        # a simple interface for interacting with such a remote process.
        #
        # It may be used in either of two ways. The first allows multiple
        # processes to be invoked on the remote machine and run in parallel
        # over the same session. Because of this, it is a bit complicated to
        # set up:
        #
        #   require 'net/ssh'
        #
        #   Net::SSH.start( 'host', 'user', 'passwd' ) do |session|
        #     process = session.process.open( "bc" )
        #     dialog = [ "5+5", "7*12", "1+2*5/(7+3)" ]
        #
        #     process.on_success do |p|
        #       puts "requesting computation of '#{dialog.first}'"
        #       p.puts dialog.shift
        #     end
        #
        #     process.on_failure do |p, status|
        #       puts "process failed to start (#{status})"
        #     end
        #
        #     process.on_stdout do |p, data|
        #       puts "--> #{data}"
        #       if dialog.empty?
        #         p.close_input
        #       else
        #         puts "requesting computation of '#{dialog.first}'"
        #         p.puts dialog.shift
        #       end
        #     end
        #
        #     process.on_stderr do |p, data|
        #       puts "[stderr]--> #{data}"
        #     end
        #
        #     process.on_exit do |p, status|
        #       puts "process finished with exit status: #{status}"
        #     end
        #
        #     session.loop
        #   end
        #
        # Naturally, not all of the callbacks used above are required. If you
        # omit any of them, they will simply not be called. However, you
        # *should* do something when the process is successfully started
        # (+on_success+), and you *should* do something when data is recieved
        # over stdout (+on_stdout+). Lastly, you *must* execute
        # <tt>session.loop</tt> in order to process the connection.
        #
        # The simpler way to use this service is only available when you
        # are not handling multiple parallel processes--you can only use it
        # when the process you are executing is the only task you are using the
        # SSH connection for. It is reminiscent of the popen interface: you
        # invoke a command and get three pseudo-IO objects back--one for the
        # command's "stdin" stream, one for it's "stdout" stream, and one for
        # it's "stderr" stream. You may then write to the "stdin" stream, and
        # read from the "stdout" and "stderr" streams.
        #
        # For example:
        #
        #   require 'net/ssh'
        #
        #   Net::SSH.start( 'host', 'user', 'passwd' ) do |session|
        #     input, output, error = session.process.popen3( "bc" )
        #     input.puts "5+5"
        #     puts "5+5=#{output.read}"
        #     input.puts "7*12"
        #     puts "7*12=#{output.read}"
        #     input.puts "1+2*5/(7+3)"
        #     puts "1+2*5/(7+3)=#{output.read}"
        #     input.puts "quit"
        #   end
        #
        # One caveat with this format: the process cannot be explicitly
        # terminated from the client side--the process must terminate on its
        # own (for example, by recieving a "quit" command, as used above). If
        # the command does not support any means of gracefully aborting it,
        # then the only way to kill the command is to terminate the connection.
        #
        # A slightly cleaner approach uses blocks to denote the lifespan of the
        # process. When the block terminates, the process is killed (if it is
        # still running):
        #
        #   require 'net/ssh'
        #
        #   Net::SSH.start( 'host', 'user', 'passwd' ) do |session|
        #     session.process.popen3( "cat" ) do |input, output, error|
        #       input.puts "hello"
        #       puts "echo: #{output.read}"
        #       input.puts "world"
        #       puts "echo: #{output.read}"
        #     end
        #   end
        class Driver

          # Create a new Driver instance, using the given log and handlers
          # hash.
          def initialize( connection, log, handlers )
            @connection = connection
            @log = log
            @handlers = handlers
          end

          def open( command )
            @log.debug "opening '#{command}'" if @log.debug?
            process = @handlers[ :open ].call( command )

            if block_given?
              yield process
              @connection.loop
              return nil
            end

            process
          end

          def popen3( command, &block )
            @log.debug "popen3 '#{command}'" if @log.debug?
            mgr = @handlers[ :popen3 ]
            mgr.popen3( command, &block )
          end

        end

      end # module Process
    end # module Service
  end # module SSH
end # module Net
