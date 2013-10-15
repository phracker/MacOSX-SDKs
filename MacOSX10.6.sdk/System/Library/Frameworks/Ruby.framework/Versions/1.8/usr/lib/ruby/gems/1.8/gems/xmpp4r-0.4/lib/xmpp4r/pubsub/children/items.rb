# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/iq'

module Jabber
  module PubSub
    ##
    # Items
    # a collection of Items
    class Items < XMPPElement
      name_xmlns 'items', NS_PUBSUB

      def node
        attributes['node']
      end
      def node=(mynodename)
        attributes['node'] = mynodename
      end
      def subid
        attributes['subid']
      end
      def subid=(mysubid)
        attributes['subid'] = mysubid
      end
      def max_items
        attributes['max_items']
      end
      def max_items=(mymaxitems)
        attributes['max_items'] = mymaxitems
      end
    end

    ##
    # Items wrapped in a Pubsub Event.
    #
    # See example 2 in http://www.xmpp.org/extensions/xep-0060.html#intro-howitworks
    # and http://www.xmpp.org/extensions/xep-0060.html#schemas-event
    class EventItems < Items
      name_xmlns 'items', NS_PUBSUB + "#event"
    end
  end
end
