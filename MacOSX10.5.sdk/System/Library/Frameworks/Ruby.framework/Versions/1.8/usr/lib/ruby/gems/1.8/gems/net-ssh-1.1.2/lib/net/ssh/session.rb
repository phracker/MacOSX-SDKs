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

require 'needle'
require 'net/ssh/errors'

module Net
  module SSH

    # Encapsulates a single session (connection) to a server via SSH.
    class Session

      # The dependency-injection registry used by this session.
      attr_reader :registry

      # The name of the host that this session is connected to.
      attr_reader :host

      # The hash of options that were used to establish this session.
      attr_reader :options

      # The underlying connection
      attr_reader :connection

      # Create a new SSH session. This method polymorphically accepts a
      # variable number of parameters, as follows:
      #
      # * 1 parameter: must be the hostname to connect to.
      # * 2 parameters: must be the hostname, and either the port (as an
      #   integer) or the username to connect as.
      # * 3 parameters: must be the hostname, and either the port (as an
      #   integer) and username, or the username and the password.
      # * 4 parameters: must be the hostname, port, username, and password.
      #
      # Any scenario above that omits the username assumes that the USER
      # environment variable is set to the user's name. Any scenario above that
      # omits the password assumes that the user will log in without a password
      # (ie, using a public key). Any scenario above that omits the port number
      # assumes a port number of 22 (the default for SSH).
      #
      # Any of the above scenarios may also accept a Hash as the last
      # parameter, specifying a list of additional options to be used to
      # initialize the session. (See Net::SSH::Session.add_options).
      #
      # Alternatively, named parameters may be used, in which case the first
      # parameter is positional and is always the host to connect to, following
      # which you may specify any of the following named parameters (as
      # symbols):
      #
      # * :port
      # * :username
      # * :password
      #
      # Any additional parameters are treated as options that configure how the
      # connection behaves.
      #
      # Allowed options are:
      #
      # * :keys (the list of filenames identifying the user's keys)
      # * :host_keys (the list of filenames identifying the host's keys)
      # * :auth_methods (a list of authentication methods to use)
      # * :crypto_backend (defaults to :ossl, and specifies the cryptography
      #   backend to use)
      # * :registry_options (a hash of options to use when creating the
      #   registry)
      # * :container (the registry to use. If not specified, a new registry
      #   will be created)
      # * :verbose (how verbose the logging output should be. Defaults to
      #   :warn).
      # * :log (the name of the file, or the IO object, to which messages will
      #   be logged. Defaults to STDERR.)
      # * :forward_agent (true or false, whether or not to forward requests
      #   for the authentication agent. Defaults to false.)
      # * :paranoid (either false, in which case server fingerprints are not
      #   verified, true, in which case they are verified and mismatches result
      #   in a warning and a prompt, or an object responding to :allow?, which
      #   will be invoked and should return true or false for whether or not
      #   to allow the connection. Defaults to true.)
      #
      # Also, any options recognized by Net::SSH::Transport::Session may be
      # given, and will be passed through to initialize the transport session.
      #
      # If a block is given to this method, then it is called with the new
      # session object. The session object is then closed when the block
      # terminates. If a block is not given, then the session object is
      # returned (and must be closed explicitly).
      def initialize( *args )
        @open = false
        @agent_forwarded = false

        process_arguments( *args )

        @registry.define do |b|
          b.crypto_backend { @crypto_backend }
          b.transport_host { @host }
          b.transport_options { @options }

          b.userauth_keys { @keys }
          b.userauth_host_keys { @host_keys }
          b.userauth_method_order { @auth_methods }

          b.host_key_verifier { @host_key_verifier }

          # Register myself with the registry, so that other services may
          # access me.
          b.session( :pipeline => [] ) { self }

          b.prompter do
            require 'net/ssh/util/prompter'
            Net::SSH::Util::Prompter.new
          end

          b.require 'net/ssh/transport/services', "Net::SSH::Transport"
          b.require 'net/ssh/connection/services', "Net::SSH::Connection"
          b.require 'net/ssh/userauth/services', "Net::SSH::UserAuth"

          b.require 'net/ssh/service/services', "Net::SSH::Service"
        end

        userauth = @registry[:userauth][:driver]
        if userauth.authenticate( "ssh-connection", @username, @password )
          @open = true
          @connection = @registry[:connection][:driver]
          if block_given?
            yield self
            close
          end
        else
          @registry[:transport][:session].close
          raise AuthenticationFailed, @username
        end
      end

      # Closes the session, if it is open. If it is not open, this does
      # nothing.
      def close
        @registry[:transport][:session].close if @open
        @open = false
      end

      # Returns +true+ if the session is currently open.
      def open?
        @open
      end

      # Opens a new communication channel over the current connection. This
      # returns immediately. The block will be invoked when then the channel
      # has been opened. (See Net::SSH::Connection::Driver#open_channel).
      def open_channel( type="session", data=nil, &block )
        sanity_check
        channel = @connection.open_channel( type, data )
        channel.on_confirm_open(&block)

        # If we have an agent, and agent-forwarding is enabled, set up
        # the forwarding. Do this once only, after the first channel
        # is opened.
        if @forward_agent && @registry[:userauth].agent
          unless @agent_forwarded
            agentforward.request
            @agent_forwarded = true
          end
        end

        channel
      end

      # Enters the main communication loop. This processes events occuring over
      # the channel. If a block is given, the loop will continue for as long
      # as the block returns +true+. Otherwise, the loop continues until there
      # are no more open channels. (See Net::SSH::Connection::Driver#loop).
      def loop( &block )
        sanity_check
        @connection.loop(&block)
      end

      # Provides convenient access to services that have been registered with
      # the session, such as "process" and "forward".
      #
      # Usage:
      #
      #   session.forward.local(...)
      def method_missing( sym, *args, &block )
        if args.empty? && block.nil? && @registry[:services].has_key?( sym )
          return @registry[:services][ sym ]
        else
          super
        end
      end

      # Processes the argument list, determining the meaning of each argument
      # and allowing polymorphic argument lists. (See #initialize).
      def process_arguments( *args )
        @options = {}
        @username = ENV['USER'] || ENV['USERNAME']

        raise ArgumentError,
          "you must specify the host to connect to" if args.length < 1

        @host = args.shift

        # support for both named arguments, and positional arguments...
        if args.length == 1 && args[0].is_a?( Hash ) &&
           ( args[0][:username] || args[0][:password] ||
             args[0][:port] || args[0][:options] )
        # then
          @username = args[0][:username] || @username
          @password = args[0][:password]

          @options.update args.shift
        else
          @options[ :port ] = args.shift if args.first.is_a? Numeric
          if args.first.nil? || args.first.is_a?( String )
            @username = args.shift || @username
          end
          if args.first.nil? || args.first.is_a?( String )
            @password = args.shift
          end
          @options.update args.shift if args.first.is_a?( Hash )
        end

        if !args.empty?
          raise ArgumentError, "extra parameters detected: #{args.inspect}"
        elsif @username.nil?
          raise ArgumentError, "no username was given and none could be inferred from the environment"
        end

        @keys = @options[ :keys ]
        @host_keys = @options[ :host_keys ]
        @auth_methods = @options[ :auth_methods ]
        @forward_agent = @options[ :forward_agent ] || false
        @crypto_backend = @options.fetch( :crypto_backend, :ossl )
        @host_key_verifier = host_key_verifier_from(@options.fetch(:paranoid, true))

        verbose = @options.fetch( :verbose, :warn )
        log = @options.fetch( :log, STDERR )

        @registry_options = @options.fetch( :registry_options, {} )

        @registry_options[ :logs ] ||= {}
        @registry_options[ :logs ][ :default_level ] = verbose

        if log.is_a? IO
          @registry_options[ :logs ][ :device ] ||= log
        else
          @registry_options[ :logs ][ :filename ] ||= log
        end

        @registry = @options[ :container ] ||
          Needle::Registry.new( @registry_options )

        [ :keys, :host_keys, :auth_methods, :username, :password,
          :crypto_backend, :registry_options, :container, :log, :verbose,
          :forward_agent, :paranoid
        ].each do |i|
          @options.delete i
        end

        @options.freeze
      end
      private :process_arguments

      def host_key_verifier_from(paranoia)
        case paranoia
        when true then
          require 'net/ssh/lenient-host-key-verifier'
          Net::SSH::LenientHostKeyVerifier.new
        when false then
          require 'net/ssh/null-host-key-verifier'
          Net::SSH::NullHostKeyVerifier.new
        when :very then
          require 'net/ssh/host-key-verifier'
          Net::SSH::HostKeyVerifier.new
        else
          if paranoia.respond_to?(:verify)
            paranoia
          else
            raise ArgumentError, "argument to :paranoid is not valid: #{paranoia.inspect}"
          end
        end
      end
      private :host_key_verifier_from

      # Make sure we're in an acceptible state.
      def sanity_check
        raise Net::SSH::Exception, "session not open" unless @open
      end
      private :sanity_check

    end

  end
end
