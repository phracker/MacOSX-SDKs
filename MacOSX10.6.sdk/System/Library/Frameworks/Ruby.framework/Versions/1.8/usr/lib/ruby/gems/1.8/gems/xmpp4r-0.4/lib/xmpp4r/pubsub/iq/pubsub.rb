# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/iq'

module Jabber
  module PubSub
    NS_PUBSUB = 'http://jabber.org/protocol/pubsub'
    class IqPubSub < XMPPElement
      name_xmlns 'pubsub', NS_PUBSUB
      force_xmlns true
    end
    class IqPubSubOwner < XMPPElement
      name_xmlns 'pubsub', NS_PUBSUB + '#owner'
      force_xmlns true
    end
  end
end
