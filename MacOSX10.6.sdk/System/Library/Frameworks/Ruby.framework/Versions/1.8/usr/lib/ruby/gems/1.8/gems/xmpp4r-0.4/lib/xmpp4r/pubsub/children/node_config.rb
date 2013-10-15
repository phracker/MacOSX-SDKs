# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/xmppelement'
require 'xmpp4r/pubsub/children/configuration'

module Jabber
  module PubSub
    ##
    # NodeConfig
    #
    # A <configure> XMPP element for pubsub nodes, see example 123 in
    # http://www.xmpp.org/extensions/xep-0060.html#owner-create-and-configure
    class NodeConfig < Configuration
      name_xmlns 'configure', NS_PUBSUB

      ##
      # Construct a <configure> element.
      # node:: [String] the node to configure
      # options:: [Hash] the configuration to apply
      def initialize(node = nil, options = nil)
        super()

        self.node = node
        self.options = options
      end

      private

      def form_type
        'http://jabber.org/protocol/pubsub#node_config'
      end
    end

    ##
    #
    # OwnerNodeConfig
    #
    # A <configure> stanza for 'Owner' use cases
    #
    # see example 125 in
    # http://www.xmpp.org/extensions/xep-0060.html#owner-configure-request
    class OwnerNodeConfig < NodeConfig
      name_xmlns 'configure', NS_PUBSUB + '#owner'
    end
  end
end
