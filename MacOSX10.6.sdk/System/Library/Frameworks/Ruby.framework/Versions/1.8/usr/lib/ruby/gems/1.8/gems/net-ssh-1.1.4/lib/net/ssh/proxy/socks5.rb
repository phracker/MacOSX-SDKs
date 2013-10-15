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

require 'socket'
require 'net/ssh/proxy/errors'

module Net
  module SSH
    module Proxy

      # An implementation of a socket factory that returns a socket which
      # will tunnel the connection through a SOCKS5 proxy. It allows explicit
      # specification of the user and password, but if none are given it
      # will look in the SOCKS_USER/SOCKS_PASSWORD and
      # CONNECT_USER/CONNECT_PASSWORD environment variables as well.
      class SOCKS5

        SOCKS_VERSION = 5

        SOCKS_METHOD_NO_AUTH = 0
        SOCKS_METHOD_GSSAPI  = 1
        SOCKS_METHOD_PASSWD  = 2

        SOCKS_METHOD_NONE    = 0xFF
        
        SOCKS_CMD_CONNECT    = 1

        SOCKS_ATYP_IPV4      = 1
        SOCKS_ATYP_DOMAIN    = 3
        SOCKS_ATYP_IPV6      = 4

        SOCKS_SUCCESS        = 0
        SOCKS_FAILURE        = 1
        SOCKS_NOT_ALLOWED    = 2
        SOCKS_NETWORK_UNREACHABLE = 3
        SOCKS_HOST_UNREACHABLE = 4
        SOCKS_REFUSED        = 5
        SOCKS_TTL_EXPIRED    = 6
        SOCKS_CMD_NOT_SUPPORTED = 7
        SOCKS_ADDR_NOT_SUPPORTED = 8

        # Create a new proxy connection to the given proxy host and port.
        # Optionally, @:user@ and @:password@ options may be given to
        # identify the username and password with which to authenticate.
        def initialize( proxy_host, proxy_port=1080, options={} )
          @proxy_host = proxy_host
          @proxy_port = proxy_port
          @options = options
        end

        # Return a new socket connected to the given host and port via the
        # proxy that was requested when the socket factory was instantiated.
        def open( host, port )
          sock = TCPSocket.new( @proxy_host, @proxy_port )

          methods = [ SOCKS_METHOD_NO_AUTH ]
          methods << SOCKS_METHOD_PASSWD if proxy_user

          packet = [ SOCKS_VERSION, methods.size, *methods ].pack( "C*" )
          sock.send packet, 0

          version, method = sock.recv( 2 ).unpack( "CC" )
          if version != 5
            sock.close
            raise Net::SSH::Proxy::Error,
              "invalid SOCKS version (#{version})"
          end

          if method == SOCKS_METHOD_NONE
            sock.close
            raise Net::SSH::Proxy::Error,
              "no supported authorization methods"
          end

          case method
            when SOCKS_METHOD_NO_AUTH
              # no method-dependent subnegotiation required

            when SOCKS_METHOD_PASSWD
              negotiate_password( sock )
          end

          packet = [ SOCKS_VERSION, SOCKS_CMD_CONNECT, 0 ].pack( "C*" )

          if host =~ /^(\d+)\.(\d+)\.(\d+)\.(\d+)$/
            packet << [ SOCKS_ATYP_IPV4, $1.to_i, $2.to_i,
                        $3.to_i, $4.to_i ].pack( "C*" )
          else
            packet << [ SOCKS_ATYP_DOMAIN, host.length, host ].pack( "CCA*" )
          end

          packet << [ port ].pack( "n" )
          sock.send packet, 0

          version, reply, = sock.recv( 4 ).unpack( "C*" )
          len = sock.recv( 1 )[0]
          sock.recv( len + 2 )

          unless reply == SOCKS_SUCCESS
            sock.close
            raise ConnectError, "#{reply}"
          end

          return sock
        end

        # Simple username/password negotiation with the SOCKS5 server.
        def negotiate_password( socket )
          user = proxy_user
          passwd = proxy_password

          packet = [ 0x01,
                     user.length, user,
                     passwd.length, passwd ].pack( "CCA*CA*" )

          socket.send packet, 0

          version, status = socket.recv( 2 ).unpack( "CC" )

          if status != SOCKS_SUCCESS
            socket.close
            raise UnauthorizedError, "could not authorize user"
          end
        end
        private :negotiate_password

        def proxy_user
          return @options[ :user ] if @options[ :user ]
          return ENV['SOCKS_USER'] if ENV['SOCKS_USER']
          return ENV['CONNECT_USER'] if ENV['CONNECT_USER']
          return nil
        end
        private :proxy_user

        def proxy_password
          return @options[ :password ] if @options[ :password ]
          return ENV['SOCKS_PASSWORD'] if ENV['SOCKS_PASSWORD']
          return ENV['CONNECT_PASSWORD'] if ENV['CONNECT_PASSWORD']
          return ""
        end
        private :proxy_password

      end

    end
  end
end
