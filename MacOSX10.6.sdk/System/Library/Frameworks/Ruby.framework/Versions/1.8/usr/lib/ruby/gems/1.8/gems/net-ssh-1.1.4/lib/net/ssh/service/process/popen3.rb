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
      
        # A delegate class for managing popen3 requests for remote processes.
        class POpen3Manager

          # Create a new POpen3Manager instance on the given connection.
          def initialize( connection, log )
            @connection = connection
            @log = log
          end

          # Invokes the given command synchronously on the current connection.
          # (This means that parallel commands and operations cannot be
          # executed when this method is used.) This will return +nil+ if the
          # method could not be executed. If the command is successfully
          # invoked, and a block is given, the block is then invoked with the
          # input, output, and error streams of the command as parameters, and
          # the channel is closed as soon as the block terminates. If a block
          # is not given, the input, output, and error channels are returned
          # and the process *might* not terminate until the session itself
          # terminates.
          def popen3( command )
            @connection.open_channel( "session" ) do |chan|

              chan.on_success do |ch|
                input  = SSHStdinPipe.new( ch )
                output = SSHStdoutPipe.new( ch )
                error  = SSHStderrPipe.new( ch )

                if block_given?
                  yield input, output, error
                  chan.close
                else
                  return [ input, output, error ]
                end
              end

              chan.on_failure do |ch|
                chan.close
              end

              chan.exec command, true
            end

            @connection.loop
            return nil
          end

          # A specialized class for use by the Net::SSH "popen3" service.
          # An instance of this class represents a means of writing data to an
          # SSH channel. This class should never be instantiated directly; use
          # the popen3 method instead.
          class SSHStdinPipe
          
            # The channel used by this pipe.
            attr_reader :channel

            # Create a new +stdin+ pipe on the given channel.
            def initialize( channel )
              @channel = channel
            end

            # Write the given data as channel data to the underlying channel.
            def write( data )
              @channel.send_data data
              @channel.connection.process true
            end

            # Write the given data as channel data to the underlying channel,
            # appending a newline character (if one isn't already appended).
            def puts( data )
              write data.chomp + "\n"
            end

          end

          # An abstract class representing a writable stream on a channel. This
          # is subclassed by SSHStdoutPipe and SSHStderrPipe.
          class SSHOutputPipe
            
            # The channel used by this pipe.
            attr_reader :channel
            
            # Create a new output pipe on the given channel.
            def initialize( channel )
              @channel = channel
              @data = ""
            end

            # Returns true if there are any bytes available on this pipe. This
            # will do a non-blocking read on the connection to determine if
            # there
            def data_available?
              if @data.length == 0
                connection = @channel.connection
                connection.process while connection.reader_ready?
              end
              @data.length > 0
            end

            # Read all available bytes from the pipe. If there are no available
            # bytes, then this will block until data becomes available.
            def read
              if @data.length < 1
                @channel.connection.process while @data.length < 1
              end

              data, @data = @data, ""
              return data
            end

          end

          # A specialization of SSHOutputPipe that represents specifically the 
          # +stdout+ stream of a process. It should only be used by popen3.
          class SSHStdoutPipe < SSHOutputPipe

            # Create a new +stdout+ stream on the given channel. Only one such
            # pipe should ever be associated with a channel.
            def initialize( channel )
              super( channel )
              channel.on_data(&method(:do_data))
            end

            # Invoked when data is recieved from the channel. It simply
            # accumulates all data until a +read+ is invoked.
            def do_data( channel, data )
              @data << data
            end

          end

          # A specialization of SSHOutputPipe that represents specifically the
          # +stderr+ stream of a process. It should only be used by popen3.
          class SSHStderrPipe < SSHOutputPipe

            # Create a new +stderr+ stream on the given channel. Only one such
            # pipe should ever be associated with a channel.
            def initialize( channel )
              super( channel )
              channel.on_extended_data(&method(:do_data))
            end

            # Invoked when data is recieved from the channel. It simply
            # accumulates all data until a +read+ is invoked.
            def do_data( channel, type, data )
              @data << data if type == 1
            end

          end

        end

      end # module Process
    end # module Service
  end # module SSH
end # module Net
