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
      
        # A delegate class to manage the processing for a single executed
        # process on the remote host. It opens a channel, executes the process
        # on it, and manages the various callbacks.
        #
        # This service is typically used like this:
        #
        #   Net::SSH.start( 'host', 'user' ) do |session|
        #     session.process.open( "bc" ) do |process|
        #       ...
        #     end
        #   end
        class OpenManager

          # Create a new OpenManager instance on the given connection. It will
          # attempt to execute the given command. If a block is given, the
          # manager will be yielded to the block, and the constructor will not
          # return until all channels are closed.
          def initialize( connection, log, command )
            @log = log
            @command = command
            @channel = connection.open_channel(
              "session", &method( :do_confirm ) )

            if block_given?
              yield self
              connection.loop
            end
          end

          # Register the given block to be invoked when the command has been
          # confirmed to have been successfully started. The block should
          # accept a single parameter, the process instance that was created
          # (+self+).
          def on_success( &block )
            @on_success = block
          end

          # Register the given block to be invoked when the command could not
          # be started. The block should accept two parameters: the process
          # instance (+self+) and a status string. (The status string is
          # currently always +nil+, since SSH itself does not indicate why the
          # program failed to start.)
          def on_failure( &block )
            @on_failure = block
          end

          # Register the given block to be invoked when data is recieved from
          # the invoked command's +stdout+ stream. The block should accept two
          # parameters: the process instance (+self+) and the data string. Note
          # that if the process sends large amounts of data, this method may be
          # invoked multiple times, each time with a portion of the command's
          # output.
          def on_stdout( &block )
            @on_stdout = block
          end

          # Register the given block to be invoked when data is recieved from
          # the invoked command's +stderr+ stream. The block should accept two
          # parameters: the process instance (+self+) and the data string. Note
          # that if the process sends large amounts of data, this method may be
          # invoked multiple times, each time with a portion of the command's
          # error output.
          def on_stderr( &block )
            @on_stderr = block
          end

          # Register the given block to be invoked when the process terminates
          # normally. The block should accept two parameters: the process
          # instance (+self+) and the exit status of the process.
          def on_exit( &block )
            @on_exit = block
          end

          # Send the given data to the process. It will be sent via the
          # process's +stdin+ stream. This method returns immediately.
          def write( data )
            @channel.send_data data
          end

          # Send the given data to the process, appending a newline. As with
          # Kernel::puts, this will not append a newline if the string already
          # has one. See #write.
          def puts( data )
            @channel.send_data data.chomp + "\n"
          end

          # Indicate that no more data will be sent to the process (sends an
          # EOF to the process). The process may continue to send data, but
          # the +stdin+ stream is effectively closed. This will return
          # immediately.
          def close_input
            @channel.send_eof
          end

          # Close the process. All streams (+stdin+, +stdout+, +stderr+) will
          # be closed. Any output that the process had already produced will
          # still be sent, but it will be shut down as soon as possible. This
          # will return immediately.
          def close
            @channel.close
          end

          # Invoked when the channel's opening has been confirmed by the
          # server. This is where the command to execute will be sent to the
          # server.
          def do_confirm( channel )
            channel.on_success(&method(:do_exec_success))
            channel.on_failure(&method(:do_exec_failure))
            channel.exec @command, true
          end

          # Invoked when the invocation of the command has been successful.
          # This registers various callbacks, and then calls the +on_success+
          # callback (if registered).
          def do_exec_success( channel )
            channel.on_data(&method(:do_data))
            channel.on_extended_data(&method(:do_extended_data))
            channel.on_close(&method(:do_close))
            channel.on_request(&method(:do_request))
            @on_success.call( self ) if @on_success
          end

          # Invoked when the invocation of the command failed. This will call
          # the +on_failure+ callback, if registered, or will otherwise raise
          # an exception.
          def do_exec_failure( channel )
            if @on_failure
              @on_failure.call( self, nil )
            else
              raise Net::SSH::Exception,
                "could not execute process (#{@command})"
            end
          end

          # Invoked when data arrives over the channel. This simply delegates to
          # the +on_stdout+ callback, if registered.
          def do_data( channel, data )
            @on_stdout.call( self, data ) if @on_stdout
          end

          # Invoked when extended data arrives over the channel. This simply
          # delegates to the +on_stderr+ callback, if registered, if the type
          # is 1; otherwise it does nothing.
          def do_extended_data( channel, type, data )
            case type
              when 1
                @on_stderr.call( self, data ) if @on_stderr
            end
          end

          # Invoked when the channel is closed. This simply delegates to
          # the +on_exit+ callback, if registered.
          def do_close( channel )
            @on_exit.call( self, @exit_status ) if @on_exit
          end

          # Invoked when a channel request is received.
          def do_request( channel, type, want_reply, data )
            case type
              when "exit-status"
                @exit_status = data.read_long
            end
          end

        end

      end # module Process
    end # module Service
  end # module SSH
end # module Net
