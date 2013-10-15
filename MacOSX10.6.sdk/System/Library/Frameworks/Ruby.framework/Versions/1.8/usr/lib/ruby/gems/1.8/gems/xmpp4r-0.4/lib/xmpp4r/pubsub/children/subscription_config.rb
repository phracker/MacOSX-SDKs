# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/xmppelement'
require 'xmpp4r/pubsub/children/configuration'
require 'xmpp4r/pubsub/iq/pubsub'

module Jabber
  module PubSub
    ##
    # SubscriptionConfig
    #
    # An <options> XMPP element, see example 57 in
    # http://www.xmpp.org/extensions/xep-0060.html#subscriber-configure-success
    class SubscriptionConfig < Configuration
      name_xmlns 'options', NS_PUBSUB

      ##
      # Construct a new Options stanza
      # node:: [String] the node to which this subscription applies
      # jid:: [String] or [Jabber::JID] the jid that holds the subscription
      # options:: [Hash] the configuration for this subscription
      # subid:: [String] (optional) subscription id
      def initialize(node = nil, jid = nil, options = nil, subid = nil)
        super()

        self.node = node
        self.jid = jid
        self.options = options
        self.subid = subid
      end

      ##
      # set the 'jid' attribute of this stanza
      # jid:: [Jabber::JID] or [String] the jid owning the subscription
      def jid=(jid)
        attributes['jid'] = jid.to_s
      end

      ##
      # get the 'jid' attribute for this stanza
      def jid
        attributes['jid'] ? Jabber::JID.new(attributes['jid']) : nil
      end

      ##
      # set the 'subid' attribute
      # subid:: [String] the subscription id
      def subid=(subid)
        attributes['subid'] = subid
      end

      ##
      # get the 'subid' attribute
      def subid
        attributes['subid']
      end

      private

      def form_type
        'http://jabber.org/protocol/pubsub#subscribe_options'
      end
    end
  end
end
