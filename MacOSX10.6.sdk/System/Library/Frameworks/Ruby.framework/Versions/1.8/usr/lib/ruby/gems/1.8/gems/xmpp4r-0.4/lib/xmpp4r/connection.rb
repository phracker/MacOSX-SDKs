# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

begin
  require 'openssl'
rescue LoadError
end
require 'xmpp4r/stream'

module Jabber
  ##
  # The connection class manages the TCP connection to the Jabber server
  #
  class Connection  < Stream
    attr_reader :host, :port

    # How many seconds to wait for <stream:features/>
    # before proceeding
    attr_accessor :features_timeout

    # Keep-alive interval in seconds, defaults to 60
    # (see private method keepalive_loop for implementation details)
    attr_accessor :keepalive_interval

    # Allow TLS negotiation? Defaults to true
    attr_accessor :allow_tls

    # Optional CA-Path for TLS-handshake
    attr_accessor :ssl_capath

    # Optional callback for verification of SSL peer
    attr_accessor :ssl_verifycb

    #whether to use the old and deprecated SSL protocol
    #Defaults to false
    attr_accessor :use_ssl

    ##
    # Create a new connection to the given host and port
    def initialize
      super()
      @host = nil
      @port = nil
      @allow_tls = defined? OpenSSL
      @tls = false
      @ssl_capath = nil
      @ssl_verifycb = nil
      @features_timeout = 10
      @keepalive_interval = 60
      @use_ssl = false
    end

    ##
    # Connect to the Jabber server through a TCP Socket,
    # start the Jabber parser,
    # invoke to accept_features to wait for TLS,
    # start the keep-alive thread
    def connect(host, port)
      @host = host
      @port = port
      # Reset is_tls?, so that it works when reconnecting
      @tls = false

      Jabber::debuglog("CONNECTING:\n#{@host}:#{@port}")
      @socket = TCPSocket.new(@host, @port)

      # We want to use the old and deprecated SSL protocol (usually on port 5223)
      if @use_ssl
        ssl = OpenSSL::SSL::SSLSocket.new(@socket)
        ssl.connect # start SSL session
        ssl.sync_close = true
        Jabber::debuglog("SSL connection established.")
        @socket = ssl
      end

      start

      accept_features

      @keepaliveThread = Thread.new do
        Thread.current.abort_on_exception = true
        keepalive_loop
      end
    end

    ##
    # Closing connection:
    # first kill keepaliveThread, then call Stream#close!
    def close!
      @keepaliveThread.kill if @keepaliveThread and @keepaliveThread.alive?
      super
    end

    def accept_features
      begin
        Timeout::timeout(@features_timeout) {
          Jabber::debuglog("FEATURES: waiting...")
          @features_sem.wait
          Jabber::debuglog("FEATURES: waiting finished")
        }
      rescue Timeout::Error
        Jabber::debuglog("FEATURES: timed out when waiting, stream peer seems not XMPP compliant")
      end

      if @allow_tls and not is_tls? and @stream_features['starttls'] == 'urn:ietf:params:xml:ns:xmpp-tls'
        begin
          starttls
        rescue
          Jabber::debuglog("STARTTLS:\nFailure: #{$!}")
        end
      end
    end

    ##
    # Start the parser on the previously connected socket
    def start
      super(@socket)
    end

    ##
    # Do a <starttls/>
    # (will be automatically done by connect if stream peer supports this)
    def starttls
      stls = REXML::Element.new('starttls')
      stls.add_namespace('urn:ietf:params:xml:ns:xmpp-tls')

      reply = nil
      send(stls) { |r|
        reply = r
        true
      }
      if reply.name != 'proceed'
        raise ServerError(reply.first_element('error'))
      end
      # Don't be interrupted
      stop

      begin
        error = nil

        # Context/user set-able stuff
        ctx = OpenSSL::SSL::SSLContext.new
        if @ssl_capath
          ctx.verify_mode = OpenSSL::SSL::VERIFY_PEER
          ctx.ca_path = @ssl_capath
        else
          ctx.verify_mode = OpenSSL::SSL::VERIFY_NONE
        end
        ctx.verify_callback = @ssl_verifycb

        # SSL connection establishing
        sslsocket = OpenSSL::SSL::SSLSocket.new(@socket, ctx)
        sslsocket.sync_close = true
        Jabber::debuglog("TLSv1: OpenSSL handshake in progress")
        sslsocket.connect

        # Make REXML believe it's a real socket
        class << sslsocket
          def kind_of?(o)
            o == IO ? true : super
          end
        end

        # We're done and will use it
        @tls = true
        @socket = sslsocket
      rescue
        error = $!
      ensure
        Jabber::debuglog("TLSv1: restarting parser")
        start
        accept_features
        raise error if error
      end
    end

    ##
    # Have we gone to TLS mode?
    # result:: [true] or [false]
    def is_tls?
      @tls
    end

    def generate_stream_start(to=nil, from=nil, id=nil, xml_lang="en", xmlns="jabber:client", version="1.0")
      stream_start_string = "<stream:stream xmlns:stream='http://etherx.jabber.org/streams' "
      stream_start_string += "xmlns='#{xmlns}' " unless xmlns.nil?
      stream_start_string += "to='#{to}' " unless to.nil?
      stream_start_string += "from='#{from}' " unless from.nil?
      stream_start_string += "id='#{id}' " unless id.nil?
      stream_start_string += "xml:lang='#{xml_lang}' " unless xml_lang.nil?
      stream_start_string += "version='#{version}' " unless version.nil?
      stream_start_string += ">"
      stream_start_string
    end
    private :generate_stream_start

    ##
    # A loop to send "keep alive" data to prevent
    # the Jabber connection from closing for inactivity.
    #
    # This loop sends a single white-space character if
    # no other data has been sent in the last @keepalive_interval
    # seconds.
    def keepalive_loop
      loop do
        difference = @last_send + @keepalive_interval - Time.now
        if difference <= 0
          send(' ')
          sleep @keepalive_interval
        else
          sleep(difference)
        end
      end
    end
    private :keepalive_loop

  end
end
