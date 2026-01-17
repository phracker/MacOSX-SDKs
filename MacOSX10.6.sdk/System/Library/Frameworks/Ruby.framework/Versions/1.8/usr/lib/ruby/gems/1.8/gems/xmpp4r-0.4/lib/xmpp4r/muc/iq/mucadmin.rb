# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/x'

module Jabber
  module MUC
    class IqQueryMUCAdmin < IqQuery
      name_xmlns 'query', 'http://jabber.org/protocol/muc#admin'

      include XParent

      def items
        r = []
        each_element('item') { |item|
          r << item if item.kind_of? IqQueryMUCAdminItem
        }
        r
      end
    end
  end
end
