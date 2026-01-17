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
require 'base64'
require 'net/ssh/proxy/errors'

module Net
  module SSH
    module Proxy

      # An implementation of a socket factory that returns a socket which
      # will tunnel the connection through an HTTP proxy. It allows explicit
      # specification of the user and password, but if none are given it
      # will look in the HTTP_PROXY_USER/HTTP_PROXY_PASSWORD and
      # CONNECT_USER/CONNECT_PASSWORD environment variables as well.
      class HTTP

        # Create a new socket factory that tunnels via the given host and
        # port.
        def initialize( proxy_host, proxy_port=80, options={} )
          @proxy_host = proxy_host
          @proxy_port = proxy_port
          @options = options
        end

        # Return a new socket connected to the given host and port via the
        # proxy that was requested when the socket factory was instantiated.
        def open( host, port )
          connect_string = "CONNECT #{host}:#{port} HTTP/1.0"

          socket = TCPSocket.new( @proxy_host, @proxy_port )
          socket.puts connect_string
          socket.puts

          resp = parse_response( socket )

          return socket if resp[:code] == 200

          socket.shutdown
          raise ConnectError, resp.inspect unless resp[:code] == 407

          user = proxy_user
          passwd = proxy_password

          raise UnauthorizedError, "no proxy user given" unless user

          auth = resp[:headers]["Proxy-Authenticate"]
          scheme, parms = auth.split( / /, 2 )

          case scheme
            when "Basic"
              credentials =
                Base64.encode64( "#{user}:#{passwd}" ).gsub( /\n/, "" )
            else
              raise NotImplementedError,
                "authorization scheme #{scheme.inspect} is not supported"
          end

          socket = TCPSocket.new( @proxy_host, @proxy_port )
          socket.puts connect_string
          socket.puts "Proxy-Authorization: #{scheme} #{credentials}"
          socket.puts

          resp = parse_response( socket )

          raise ConnectError, resp.inspect if resp[:code] != 200

          return socket
        end

        def parse_response( socket )
          version, code, reason = socket.gets.chomp.split( / /, 3 )
          headers = {}

          while ( line = socket.gets.chomp ) != ""
            name, value = line.split( /:/, 2 ).map { |v| v.strip }
            headers[ name ] = value
          end

          if headers[ "Content-Length" ]
            body = socket.read( headers[ "Content-Length" ].to_i )
          end

          return { :version => version,
                   :code => code.to_i,
                   :reason => reason,
                   :headers => headers,
                   :body => body }
        end
        private :parse_response

        def proxy_user
          return @options[ :user ] if @options[ :user ]
          return ENV['HTTP_PROXY_USER'] if ENV['HTTP_PROXY_USER']
          return ENV['CONNECT_USER'] if ENV['CONNECT_USER']
          return nil
        end
        private :proxy_user

        def proxy_password
          return @options[ :password ] if @options[ :password ]
          return ENV['HTTP_PROXY_PASSWORD'] if ENV['HTTP_PROXY_PASSWORD']
          return ENV['CONNECT_PASSWORD'] if ENV['CONNECT_PASSWORD']
          return ""
        end
        private :proxy_password

      end

    end
  end
end
