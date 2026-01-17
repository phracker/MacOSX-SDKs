# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

module Jabber
  module Bytestreams
    ##
    # The SOCKS5BytestreamsServer is an implementation of a SOCKS5 server.
    #
    # You can use it if you're reachable by your SOCKS5Bytestreams peers,
    # thus avoiding use of an external proxy.
    #
    # ==Usage:
    # * Instantiate with an unfirewalled port
    # * Add your external IP addresses with SOCKS5BytestreamsServer#add_address
    # * Once you've got an *outgoing* SOCKS5BytestreamsInitiator, do
    #   <tt>SOCKS5BytestreamsInitiator#add_streamhost(my_socks5bytestreamsserver)</tt>
    #   *before* you do <tt>SOCKS5BytestreamsInitiator#open</tt>
    class SOCKS5BytestreamsServer
      ##
      # Start a local SOCKS5BytestreamsServer
      #
      # Will start to listen on the given TCP port and
      # accept new peers
      # port:: [Fixnum] TCP port to listen on
      # listen_on:: [String] Optional address for the server socket to listen on (i.e. '0.0.0.0' or '::')
      def initialize(port, listen_on=nil)
        @port = port
        @addresses = []
        @peers = []
        @peers_lock = Mutex.new
        if listen_on
          socket = TCPServer.new(listen_on, port)
        else
          socket = TCPServer.new(port)
        end

        Thread.new do
          Thread.current.abort_on_exception = true
          loop do
            peer = SOCKS5BytestreamsPeer.new(socket.accept)
            Thread.new do
              Thread.current.abort_on_exception = true
              begin
                peer.start
              rescue
                Jabber::debuglog("SOCKS5 BytestreamsServer: Error accepting peer: #{$!}")
              end
            end
            @peers_lock.synchronize do
              @peers << peer
            end
          end
        end
      end

      ##
      # Find the socket a peer is associated to
      #
      # This method also performs some housekeeping, ie. removing
      # peers with closed sockets.
      # addr:: [String] Address like SOCKS5Bytestreams#stream_address
      # result:: [TCPSocker] or [nil]
      def peer_sock(addr)
        res = nil
        @peers_lock.synchronize {
          removes = []

          @peers.each { |peer|
            if peer.socket and peer.socket.closed?
              # Queue peers with closed socket for removal
              removes << peer
            elsif peer.address == addr and res.nil?
              res = peer.socket
            end

            # If we sent multiple addresses of our own, clients may
            # connect multiple times. DO NOT close any other connections
            # here. These may belong to other concurrent bytestreams,
            # believe that the peer will close any unneeded sockets
            # which will then be picked up by the next call to peer_sock.
          }

          # If we sent multiple addresses of our own, clients may
          # connect multiple times. Close these connections here.
          @peers.delete_if { |peer|
            if removes.include? peer
              peer.socket.close rescue IOError
              true
            else
              false
            end
          }
        }

        res
      end

      ##
      # Add an external IP address
      #
      # This is a must-have, as SOCKS5BytestreamsInitiator must inform
      # the target where to connect
      def add_address(address)
        @addresses << address
      end

      ##
      # Iterate through all configured addresses,
      # yielding SOCKS5BytestreamsServerStreamHost
      # instances, which should be passed to
      # SOCKS5BytestreamsInitiator#add_streamhost
      #
      # This will be automatically invoked if you pass an instance
      # of SOCKS5BytestreamsServer to
      # SOCKS5BytestreamsInitiator#add_streamhost
      # my_jid:: [JID] My Jabber-ID
      def each_streamhost(my_jid, &block)
        @addresses.each { |address|
          yield SOCKS5BytestreamsServerStreamHost.new(self, my_jid, address, @port)
        }
      end
    end

    ##
    # A subclass of StreamHost which possesses a
    # server attribute, to let SOCKS5BytestreamsInitiator
    # know this is the local SOCKS5BytestreamsServer
    class SOCKS5BytestreamsServerStreamHost < StreamHost
      attr_reader :server
      def initialize(server, jid=nil, host=nil, port=nil)
        super(jid, host, port)
        @server = server
      end
    end

    ##
    # This class will be instantiated by SOCKS5BytestreamsServer
    # upon accepting a new connection
    class SOCKS5BytestreamsPeer
      attr_reader :address, :socket

      ##
      # Initialize a new peer
      # socket:: [TCPSocket]
      def initialize(socket)
        @socket = socket
        Jabber::debuglog("SOCKS5 BytestreamsServer: accepted peer #{@socket.peeraddr[2]}:#{@socket.peeraddr[1]}")
      end

      ##
      # Start handshake process
      def start
        if !@socket.respond_to? :getbyte
          class << @socket; alias getbyte getc; end
        end

        auth_ver = @socket.getbyte
        if auth_ver != 5
          # Unsupported version
          @socket.close
          return
        end

        auth_nmethods = @socket.getbyte
        auth_methods = @socket.read(auth_nmethods)
        unless auth_methods.index("\x00")
          # Client won't accept no authentication
          @socket.write("\x05\xff")
          @socket.close
          return
        end
        @socket.write("\x05\x00")
        Jabber::debuglog("SOCKS5 BytestreamsServer: peer #{@socket.peeraddr[2]}:#{@socket.peeraddr[1]} authenticated")

        req = @socket.read(4)
        if req != "\x05\x01\x00\x03"
          # Unknown version, command, reserved, address-type
          @socket.close
          return
        end
        req_addrlen = @socket.getbyte
        req_addr = @socket.read(req_addrlen)
        req_port = @socket.read(2)
        if req_port != "\x00\x00"
          # Port is not 0
          @socket.write("\x05\x01")
          @socket.close
          return
        end
        @socket.write("\x05\x00\x00\x03#{req_addrlen.chr}#{req_addr}\x00\x00")
        Jabber::debuglog("SOCKS5 BytestreamsServer: peer #{@socket.peeraddr[2]}:#{@socket.peeraddr[1]} connected for #{req_addr}")

        @address = req_addr
      end
    end
  end
end
