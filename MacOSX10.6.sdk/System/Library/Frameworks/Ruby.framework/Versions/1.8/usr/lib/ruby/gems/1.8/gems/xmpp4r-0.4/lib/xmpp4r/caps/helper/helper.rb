# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r'
require 'xmpp4r/discovery'
require 'xmpp4r/caps/c'
require 'xmpp4r/caps/helper/generator'

module Jabber
  module Caps
    ##
    # A Helper to manage advertising and discovery of entity capabilities.
    #
    # Following XEP-0115 (ver 1.4 http://www.xmpp.org/extensions/xep-0115.html).
    # you can use this Helper to, for example, advertise that your client
    # wishes to receive XEP-0118 User Tune notifications, eg:
    #
    # caps_helper=Jabber::Caps::Helper(cl,
    #   [Jabber::Discovery::Identity.new('client',nil,'bot')],
    #   [Jabber::Discovery::Feature.new('http://jabber.org/protocol/tune+notify')]
    # )
    class Helper
      attr_accessor :identities, :features, :node

      ##
      # Construct a new Caps Helper.
      #
      # This will send a <presence> message containing
      # a <c/> (Jabber::Caps::C) stanza to your server.
      # client:: [Jabber::Stream]
      # i:: [Array] of [Jabber::Discovery::Identity] objects that this entity  will advertise
      # f:: [Array] of [Jabber::Discovery::Feature] objects that this entity will advertise
      # n:: [String] an identifier representing the software underlying this entity
      def initialize(client,i=[],f=[],n="http://home.gna.org/xmpp4r/##{Jabber::XMPP4R_VERSION}")
        @stream = client
        @identities = i
        @features = f
        @node = n

        @stream.add_iq_callback(250) do |iq|
          if iq.type == :get and iq.query.kind_of? Jabber::Discovery::IqQueryDiscoInfo
            Thread.new do
              Thread.abort_on_exception = true
              handle_discoinfo_query(iq)
            end
            true
          else
            false
          end
        end

        p = Jabber::Presence.new()
        p.add(c)
        @stream.send(p)
      end

      ##
      # Return a <c/> element for inclusion in your own <presence>
      # stanzas.
      def c
        Jabber::Caps::C.new(node, ver)
      end

      ##
      # Send actual identities/ features back to a requesting entity
      def handle_discoinfo_query(iq)
        caps_reply = Jabber::XMPPStanza.answer(iq)
        caps_reply.type = :result
        caps_reply.query = Jabber::Discovery::IqQueryDiscoInfo.new
        @identities.each { |i| caps_reply.query.add(i) }
        @features.each { |f| caps_reply.query.add(f) }

        @stream.send(caps_reply)
      end

      ##
      # Generate 'ver', an opaque hash used to represent this entity's
      # capabilities
      #
      # See http://www.xmpp.org/extensions/xep-0115.html#ver
      def ver
        Caps::generate_ver(@identities, @features)
      end
    end
  end
end
