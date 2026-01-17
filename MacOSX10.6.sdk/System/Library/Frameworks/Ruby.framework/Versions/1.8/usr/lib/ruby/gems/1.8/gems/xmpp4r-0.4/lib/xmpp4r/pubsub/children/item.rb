# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/iq'

module Jabber
  module PubSub
    ##
    # Item
    # One PubSub Item
    class Item < XMPPElement
      name_xmlns 'item', NS_PUBSUB
      def initialize(id=nil)
        super()
        attributes['id'] = id
      end
      def id
        attributes['id']
      end
      def id=(myid)
        attributes['id'] = myid
      end
    end

    ##
    # An Item wrapped in a Pubsub Event.
    #
    # See example 2 in http://www.xmpp.org/extensions/xep-0060.html#intro-howitworks
    # and http://www.xmpp.org/extensions/xep-0060.html#schemas-event
    class EventItem < Item
      name_xmlns 'item', NS_PUBSUB + "#event"
    end
  end
end
