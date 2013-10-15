# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/xmppelement'

module Jabber
  module PubSub

    ##
    # Publish
    #
    # A <publish> XMPP element, see example 1 in
    # http://www.xmpp.org/extensions/xep-0060.html#intro-howitworks
    class Publish < XMPPElement
      name_xmlns 'publish', NS_PUBSUB
      ##
      # return the node for this publication
      def node
        attributes['node']
      end
    end
  end
end
