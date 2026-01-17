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
require 'net/ssh/userauth/constants'
require 'net/ssh/transport/constants'
require 'ostruct'

module Net
  module SSH
    module UserAuth

      # A wrapper around the transport layer that represents the functionality
      # of user authentication.
      class Driver

        include Net::SSH::UserAuth::Constants
        include Net::SSH::Transport::Constants

        # The UserKeyManager instance used by the auth service.
        attr_writer :key_manager

        # The SSH (transport) session to use for communication.
        attr_writer :session

        # The array of auth-method names (as strings), giving the order in
        # which each auth-method will be tried.
        attr_reader :order

        # Create a new user-auth service on top of the given session.
        def initialize( log, buffers, methods, order )
          @log = log
          @buffers = buffers
          @methods = methods
          @on_banner = proc { |msg,lang| }
          @order = order.dup
          @allowed_auth_methods = nil
        end

        # Causes the set of on-disk key files to be used to be set to the
        # given array. Any key files that were specified previously are
        # lost.
        def set_key_files( files )
          @key_manager.clear!
          files.each { |file| @key_manager << file }
        end

        # Causes the set of on-disk host key files to be used to be set to the
        # given array. Any host key files that were specified previously are
        # lost.
        def set_host_key_files( files )
          @key_manager.clear_host!
          files.each { |file| @key_manager.add_host_key file }
        end

        # Changes the set of authentication methods to try to the given array.
        # Methods are tried in the order in which they are listed in the
        # array.
        def set_auth_method_order( *methods )
          @order = methods.flatten
        end

        # Specify the callback to use when the server sends a banner message
        # at login time.
        def on_banner( &block )
          @on_banner = block
        end

        # Sends the message by delegating to the session's #send_message
        # method. (This is a convenience method for the authentication
        # implementations.)
        def send_message( message )
          @session.send_message message
        end

        # Wraps the Net::SSH::Transport::Session#wait_for_message method,
        # doing special checking for authentication-related messages.
        def wait_for_message
          loop do
            type, buffer = @session.wait_for_message

            case type
              when USERAUTH_BANNER
                message = buffer.read_string
                language = buffer.read_string

                if @log.debug?
                  @log.debug "got USERAUTH_BANNER (#{message}:#{language})"
                end

                @on_banner.call( message, language )

              when USERAUTH_FAILURE
                authentications = buffer.read_string
                @allowed_auth_methods = authentications.split(/,/)
                partial_success = buffer.read_bool
                return OpenStruct.new( :message_type    => type,
                                       :authentications => authentications,
                                       :partial_success => partial_success )

              when USERAUTH_SUCCESS
                return OpenStruct.new( :message_type => type )

              when SERVICE_ACCEPT
                return OpenStruct.new( :message_type => type,
                                       :service_name => buffer.read_string )
              
              # authmethod-specific codes
              when 60..79
                return OpenStruct.new( :message_type => type,
                                       :buffer       => buffer )

              else
                raise Net::SSH::Exception,
                      "unexpected message type '#{type}' (#{buffer.to_s})"
            end
          end
        end

        # Processes the authentication of the given username. The
        # 'next_service' parameter should be set to the SSH service that will
        # be requested once the authentication succeeds (usually
        # 'ssh-connection').
        #
        # This will return +true+ if the user is accepted by the server, and
        # +false+ otherwise.
        def authenticate( next_service, username, password=nil )
          msg = @buffers.writer
          msg.write_byte SERVICE_REQUEST
          msg.write_string "ssh-userauth"
          send_message msg

          message = wait_for_message
          unless message.message_type == SERVICE_ACCEPT
            raise Net::SSH::Exception,
              "expected SERVICE_ACCEPT, got #{message.inspect}"
          end

          data = { :password => password,
                   :key_manager => @key_manager }

          @order.each do |auth_method|
            # if the server has reported a list of auth methods that are
            # allowed to continue, only consider those auth methods.
            next if @allowed_auth_methods &&
              !@allowed_auth_methods.include?( auth_method )

            @log.debug "trying #{auth_method.inspect}" if @log.debug?

            impl = @methods[ auth_method.downcase.gsub(/-/,"_").intern ]
            if impl.nil?
              raise NotImplementedError,
                "`#{auth_method}' authentication is not implemented"
            end

            return true if impl.authenticate( next_service, username, data )
          end

          @log.debug "all authorization methods failed" if @log.debug?
          return false

        ensure
          @key_manager.finish
        end

      end

    end
  end
end
