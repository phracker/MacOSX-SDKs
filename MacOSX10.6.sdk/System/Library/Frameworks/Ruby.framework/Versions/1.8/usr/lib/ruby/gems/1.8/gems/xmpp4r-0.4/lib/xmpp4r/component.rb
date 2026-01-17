# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/connection'

module Jabber
  ##
  # The component class provides everything needed to build a XMPP Component.
  #
  # Components are more flexible as they are only restricted in the use of a
  # fixed domain. node and resource of JIDs are freely choosable for all stanzas.
  class Component  < Connection

    # The component's JID
    attr_reader :jid

    # The server's address
    attr_reader :server_address

    # The server's port
    attr_reader :server_port

    # Create a new Component
    # jid:: [JID]
    def initialize(jid, server_address=nil, server_port=5347)
      super()
      @jid = (jid.kind_of?(JID) ? jid : JID.new(jid.to_s))

      if server_address
        $stderr.puts "Passing server and port to Jabber::Component.new is " +
                     "obsolete and will vanish in some later XMPP4R release. " +
                     "Please use these arguments when calling " +
                     "Jabber::Client#connect"
        @server_address = server_address
        @server_port = server_port
      end
    end

    # Connect to the server
    # (chaining-friendly)
    # server:: [String] Hostname
    # port:: [Integer] TCP port (5347)
    # return:: self
    def connect(server=nil, port=5347)
      if server
        super(server, port)
      else
        super(@server_address, @server_port)
      end
      self
    end

    ##
    # Close the connection,
    # sends <tt></stream:stream></tt> tag first
    def close
      send("</stream:stream>")
      super
    end

    def generate_stream_start(to=nil, from=nil, id=nil, xml_lang="en", xmlns="jabber:component:accept", version="1.0")
      super
    end
    private :generate_stream_start

    ##
    # Start the stream-parser and send the component-specific stream opening element
    def start
      super
      send(generate_stream_start(@jid)) { |e|
        if e.name == 'stream'
          true
        else
          false
        end
      }
    end

    ##
    # Send auth with given secret and wait for result
    #
    # Throws ComponentAuthenticationFailure
    # secret:: [String] the shared secret
    def auth(secret)
      hash = Digest::SHA1::hexdigest(@streamid.to_s + secret)
      authenticated = false
      send("<handshake>#{hash}</handshake>") { |r|
        if r.prefix == 'stream' and r.name == 'error'
          true
        elsif r.name == 'handshake'
          authenticated = true
          true
        else
          false
        end
      }
      unless authenticated
        raise ComponentAuthenticationFailure.new, "Component authentication failed"
      end
    end
  end
end
