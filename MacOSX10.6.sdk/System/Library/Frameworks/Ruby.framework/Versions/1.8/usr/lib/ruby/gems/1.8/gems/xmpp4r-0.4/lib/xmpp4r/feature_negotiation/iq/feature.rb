# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/iq'
require 'xmpp4r/dataforms/x/data'

module Jabber
  module FeatureNegotiation
    ##
    # Feature negotiation,
    # can appear as direct child to Iq
    # or as child of IqSi
    class IqFeature < XMPPElement
      name_xmlns 'feature', 'http://jabber.org/protocol/feature-neg'

      ##
      # First <x/> child with xmlns='jabber:x:data'
      def x
        res = nil
        each_element('x') { |e|
          res = e if e.namespace == 'jabber:x:data'
        }
        res
      end
    end
  end
end
