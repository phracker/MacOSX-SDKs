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
require 'net/ssh/errors'

module Net
  module SSH
    module Service
      module Shell

        class OpenFailed < Net::SSH::Exception; end

        # A service class for interacting with a user's shell on a remote
        # machine. The shell may be interacted with either with or without a
        # pty.
        class Shell

          # Create a new shell over the given connection. The +pty_opts+
          # parameter must be either a Hash of the allowed values for the
          # Net::SSH::Connection::Channel#request_pty method, or a boolean
          # value (indicating whether a pty should be allocated or not). This
          # will block until the shell is open and ready to receive input.
          def initialize( connection, log, pty_opts )
            @connection = connection
            @log = log

            @pty_opts = pty_opts

            @stdout = ""
            @stderr = ""

            @state = :opening
            @connection.open_channel( "session", &method( :on_confirm ) )

            @connection.loop { @state != :open && @state != :closed }
            raise "could not open shell" if @state != :open
          end

          # Returns +true+ if the shell is open.
          def open?
            @state == :open
          end

          # Return the stdout output (if any) that the shell has generated
          # since the last time this method was invoked.
          def stdout
            string, @stdout = @stdout, ""
            string
          end

          # Returns +true+ if there is any data from the shell on stdout,
          # consuming input on the connection in a non-blocking manner to make
          # sure that any available data is considered.
          def stdout?
            exists = @stdout.length > 0
            unless exists
              consume_connection
              exists = @stdout.length > 0
            end
            exists
          end

          # Return the stderr output (if any) that the shell has generated
          # since the last time this method was invoked.
          def stderr
            string, @stderr = @stderr, ""
            string
          end

          # Returns +true+ if there is any data from the shell on stderr,
          # consuming input on the connection in a non-blocking manner to make
          # sure that any available data is considered.
          def stderr?
            exists = @stderr.length > 0
            unless exists
              consume_connection
              exists = @stderr.length > 0
            end
            exists
          end

          # Sends the given data to the shell on the shell's stdin stream.
          def send_data( data )
            raise "channel not open" unless @state == :open
            @channel.send_data data
          end

          # Sends the given data to the shell on the stream indicated by the
          # +type+ parameter.
          def send_extended_data( type, data )
            raise "channel not open" unless @state == :open
            @channel.send_extended_data type, data
          end

          # Reinterprets method invocations as requests to send data to the
          # shell. The method name and the arguments are concatenated together
          # with spaces and a newline appended. The resulting string is sent
          # to the shell via #send_data.
          def method_missing( sym, *args )
            cmd = sym.to_s
            cmd << " " << args.join( " " ) unless args.empty?
            send_data cmd + "\n"
          end

          undef_method :exit

          private

            # Consumes all available input on the connection.
            def consume_connection
              return unless @channel
              connection = @channel.connection
              connection.process while connection.reader_ready?
            end

            # Invoked when the channel has been confirmed.
            def on_confirm( channel )
              @channel = channel

              @channel.on_confirm_failed( &method( :on_confirm_failed ) )
              @channel.on_close( &method( :on_close ) )
              @channel.on_data( &method( :on_data ) )
              @channel.on_eof( &method( :on_eof ) )
              @channel.on_extended_data( &method( :on_extended_data ) )
              @channel.on_request( &method( :on_request ) )
              @channel.on_failure( &method( :on_failure ) )
              @channel.on_success( &method( :on_success ) )

              @pty_opts ? request_pty : request_shell
            end

            # Request a pty from the server for this channel, using the
            # parameters given when the service was started.
            def request_pty
              @state = :pty
              pty_opts = { :want_reply=>true }
              pty_opts = @pty_opts.merge( pty_opts ) if @pty_opts.is_a?( Hash )
              @channel.request_pty pty_opts
            end

            # Request that the user's shell be started on this channel. All
            # subsequent input to the channel is interpreted as input to the
            # shell.
            def request_shell
              @state = :shell
              @channel.send_request "shell", nil, true
            end

            # Called when the channel could not be opened for some reason.
            def on_confirm_failed( channel, reason, description, *args )
              raise OpenFailed, "#{reason} (#{description})"
            end

            # Invoked when the channel closes. Changes the shell's state to
            # closed.
            def on_close( channel )
              @state = :closed
            end

            # Invoked when data is received over the channel. It is written
            # to the stdout stream.
            def on_data( channel, data )
              @stdout << data if @state == :open
            end

            # Invoked when the channel receives an eof notification. (Not
            # currently used.)
            def on_eof( channel )
            end

            # Invoked when extended data (stderr) is recieved. If type == 1,
            # this data is written to the stderr stream; otherwise, it is
            # ignored.
            def on_extended_data( channel, type, data )
              @stderr << data if @state == :open && type == 1
            end

            # Invoked when a request is received over the channel. (Not
            # currently used.)
            def on_request( channel, request, want_reply, data )
            end

            # Invoked when a request fails. Currently, this is only used in
            # response to the pty or shell request, and will close the shell
            # in reponse.
            def on_failure( channel )
              if @state == :pty || @state == :shell
                @state = :closed
              end
            end

            # Invoked when a request succeeds. Currently used only to manage
            # the state machine and make sure that the shell gets opened after
            # a successful pty request.
            def on_success( channel )
              if @state == :pty
                request_shell
              elsif @state == :shell
                @state = :open
              end
            end

        end

      end # Shell
    end # Service
  end # SSH
end # Net
