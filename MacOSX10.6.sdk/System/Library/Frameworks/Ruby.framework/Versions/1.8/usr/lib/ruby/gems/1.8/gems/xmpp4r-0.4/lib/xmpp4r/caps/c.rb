# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/xmppelement'

module Jabber
  module Caps
    NS_CAPS='http://jabber.org/protocol/caps'

    ##
    # The <c/> XMPP element, used to advertise entity capabilities.
    #
    # See http://www.xmpp.org/extensions/xep-0115.html#protocol.
    #
    # You should not need to construct this element directly, see
    # Jabber::Caps::Helper.
    class C < XMPPElement
      name_xmlns 'c', NS_CAPS
      force_xmlns true

      def initialize(node = nil, ver = nil)
        super()
        add_attribute('node', node) if node
        if ver
          add_attribute('ver', ver)
          add_attribute('hash', 'sha-1')
        end
      end

      ##
      # Get the value of this element's 'ver' attribute,
      # an opaque hash representing this entity's capabilities.
      def ver
        attributes['ver']
      end

      ##
      # Get the value of this element's 'node' attribute,
      # a 'unique identifier for the software underlying the entity'
      def node
        attributes['node']
      end

      ##
      # Get the value of this element's 'hash' attribute,
      # the algorithm used in generating the 'ver' attribute
      def hash
        attributes['hash']
      end
    end
  end
end
