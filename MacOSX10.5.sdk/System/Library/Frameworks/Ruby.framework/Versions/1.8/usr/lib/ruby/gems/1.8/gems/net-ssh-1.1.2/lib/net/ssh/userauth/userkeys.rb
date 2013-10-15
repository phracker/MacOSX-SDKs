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
    module UserAuth

      # A trivial exception class used to report errors in the key manager.
      class UserKeyManagerError < Net::SSH::Exception; end

      # This class encapsulates all operations done by clients on a user's
      # private keys. In practice, the client should never need a reference
      # to a private key; instead, they grab a list of "identities" (public 
      # keys) that are available from the UserKeyManager, and then use
      # the UserKeyManager to do various private key operations using those
      # identities.
      #
      # The UserKeyManager also uses the Agent class to encapsulate the
      # ssh-agent. Thus, from a client's perspective it is completely
      # hidden whether an identity comes from the ssh-agent or from a file
      # on disk.
      class UserKeyManager

        # The agent factory to use when a new agent instance is needed.
        attr_writer :agent_factory

        # The key manager instance to use for managing keys
        attr_writer :keys

        # The logger instance to use for logging messages
        attr_writer :log

        # The buffer manager to use for providing new buffer instances.
        attr_writer :buffers

        # The object that will be used to test whether a given key file is
        # readable. This object must only respond to "readable?" with one
        # parameter, the file to test the readability of.
        attr_writer :key_existence_tester

        # The list of user key files that will be examined
        attr_reader :key_files

        # The list of host key files that will be examined
        attr_reader :host_key_files

        # Create a new UserKeyManager. By default, the manager will
        # use the ssh-agent (if it is running).
        def initialize
          @key_files = []
          @host_key_files = []
          @use_agent = true
          @agent = nil
        end

        # Clear all knowledge of any loaded user keys. This also clears the list
        # of default identity files that are to be loaded, thus making it
        # appropriate to use if a client wishes to NOT use the default identity
        # files.
        def clear!
          @key_files = []
          @known_identities = nil
          self
        end

        # Clear all knowledge of any loaded host keys. This also clears the list
        # of default identity files that are to be loaded, thus making it
        # appropriate to use if a client wishes to NOT use the default identity
        # files.
        def clear_host!
          @host_key_files = []
          @known_host_identities = nil
          self
        end

        # Add the given key_file to the list of key files that will be used.
        def add( key_file )
          @key_files.push( key_file ).uniq!
          self
        end

        alias :<< :add

        # Add the given key_file to the list of host key files that will be
        # used.
        def add_host_key( key_file )
          @host_key_files.push( key_file ).uniq!
          self
        end

        # This is used as a hint to the UserKeyManager indicating that the agent
        # connection is no longer needed. Any other open resources may be closed
        # at this time.
        #
        # Calling this does NOT indicate that the UserKeyManager will no longer
        # be used. Identities may still be requested and operations done on
        # loaded identities, in which case, the agent will be automatically
        # reconnected. This method simply allows the client connection to be
        # closed when it will not be used in the immediate future.
        def finish
          close_agent
        end

        # Returns an array of identities (public keys) known to this manager.
        # The origin of the identities may be from files on disk or from an
        # ssh-agent. Note that identities from an ssh-agent are always listed
        # first in the array, with other identities coming after.
        def identities
          identities = []
          @known_identities = Hash.new

          ensure_agent
          if @agent
            @agent.identities.each do |key|
              identities.push key
              @known_identities[ key ] = { :from => :agent }
            end
          end

          @key_files.each do |file|
            if @key_existence_tester.readable?( file )
              begin
                key = @keys.load_public_key( file + ".pub" )
                identities.push key
                @known_identities[ key ] = { :from => :file, :file => file }
              rescue Exception => e
                @log.warn "could not load public key file " +
                  "'#{file}.pub' (#{e.message} [#{e.class}])" if @log.warn?
              end
            end
          end

          identities
        end

        # Returns an array of host identities (public keys) known to this
        # manager. Host identities are those that identify the current host,
        # and are used (typically) for hostbased authentication.
        def host_identities
          identities = []
          @known_host_identities = Hash.new

          @host_key_files.each do |file|
            if @key_existence_tester.readable?( file )
              begin
                key = @keys.load_public_key( file + ".pub" )
                identities.push key
                @known_host_identities[ key ] =
                  { :from => :file, :file => file }
              rescue Exception => e
                @log.warn "could not load public host key file " +
                  "'#{file}.pub' (#{e.message} [#{e.class}])" if @log.warn?
              end
            end
          end

          identities
        end

        # Sign the given data, using the corresponding private key of the given
        # identity. If the identity was originally obtained from an ssh-agent,
        # then the ssh-agent will be used to sign the data, otherwise the
        # private key for the identity will be loaded from disk (if it hasn't
        # been loaded already) and will then be used to sign the data.
        #
        # Regardless of the identity's origin or who does the signing, this
        # will always return the signature in an SSH2-specified "signature
        # blob" format.
        def sign( identity, data )
          info = find_identity( identity )

          if info[:key].nil? && info[:from] == :file
            begin
              info[:key] = @keys.load_private_key( info[:file] )
            rescue Exception => e 
              raise UserKeyManagerError,
                    "the given identity is known, " +
                    "but the private key could not be loaded " +
                    "(#{e.message} [#{e.class}])"
            end
          end

          if info[:key]
            sig_blob = @buffers.writer
            sig_blob.write_string identity.ssh_type
            sig_blob.write_string info[:key].ssh_do_sign( data.to_s )
            return sig_blob.to_s
          end

          if info[:from] == :agent
            raise UserKeyManagerError,
              "the agent is no longer available" unless @agent
            return @agent.sign( identity, data.to_s )
          end

          raise UserKeyManagerError,
            "[BUG] can't determine identity origin (#{info.inspect})"
        end

        # Identifies whether the ssh-agent will be used or not.
        def use_agent?
          @use_agent
        end

        # Toggles whether the ssh-agent will be used or not. If true, an
        # attempt will be made to use the ssh-agent. If false, any existing
        # connection to an agent is closed and the agent will not be used.
        def use_agent=( use_agent )
          close_agent if !use_agent
          @use_agent = use_agent
        end

        # Ensures that a connection to the agent has been made, if an agent is
        # to be used.
        def ensure_agent
          return if @agent || !@use_agent
          @agent = @agent_factory.open
        end
        private :ensure_agent

        # Closes any open connection to an ssh-agent.
        def close_agent
          @agent.close if @agent
          @agent = nil
        end
        private :close_agent

        def find_identity( identity )
          info = @known_identities[ identity ] if @known_identities
          if !info && @known_host_identities[ identity ]
            info = @known_host_identities[ identity ]
          end
          raise UserKeyManagerError,
            "the given identity is unknown to the key manager" unless info
          return info
        end
        private :find_identity

      end

    end
  end
end
