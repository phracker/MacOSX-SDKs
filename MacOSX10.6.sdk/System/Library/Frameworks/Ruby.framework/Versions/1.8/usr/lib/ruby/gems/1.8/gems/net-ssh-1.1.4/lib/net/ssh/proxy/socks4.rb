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
require 'resolv'
require 'ipaddr'
require 'net/ssh/proxy/errors'

module Net
  module SSH
    module Proxy

      # An implementation of a socket factory that returns a socket which
      # will tunnel the connection through a SOCKS4 proxy. It allows explicit
      # specification of the user, but if it is not given it will look in the
      # SOCKS_USER and CONNECT_USER environment variables as well.
      class SOCKS4

        SOCKS_VERSION = 4

        SOCKS_CMD_CONNECT    = 1

        SOCKS_GRANTED        = 90
        SOCKS_REJECTED       = 91
        SOCKS_IDENTD_REJECT  = 92
        SOCKS_IDENTD_BAD     = 93

        # Create a new proxy connection to the given proxy host and port.
        # Optionally, a @:user@ option may be given to identify the username
        # with which to authenticate.
        def initialize( proxy_host, proxy_port=1080, options={} )
          @proxy_host = proxy_host
          @proxy_port = proxy_port
          @options = options
        end

        # Return a new socket connected to the given host and port via the
        # proxy that was requested when the socket factory was instantiated.
        def open( host, port )
          sock = TCPSocket.new( @proxy_host, @proxy_port )

          ip_addr = IPAddr.new( Resolv.getaddress( host ) )
          
          packet = [ SOCKS_VERSION, SOCKS_CMD_CONNECT,
                     port.to_i, ip_addr.to_i,
                     proxy_user, 0 ].pack( "CCnNA*C" )
          sock.send packet, 0

          version, status, port, ip = sock.recv( 8 ).unpack( "CCnN" )
          if status != SOCKS_GRANTED
            sock.close
            raise ConnectError, "error connecting to proxy (#{status})"
          end

          return sock
        end

        def proxy_user
          return @options[ :user ] if @options[ :user ]
          return ENV['SOCKS_USER'] if ENV['SOCKS_USER']
          return ENV['CONNECT_USER'] if ENV['CONNECT_USER']
          return nil
        end
        private :proxy_user

      end

    end
  end
end
