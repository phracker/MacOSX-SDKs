# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/muc/item'

module Jabber
  module MUC
    class IqQueryMUCAdminItem < MUC::UserItem
      name_xmlns 'item', 'http://jabber.org/protocol/muc#admin'

      def initialize(affiliation=nil, role=nil, jid=nil)
        super()
        set_affiliation(affiliation)
        set_role(role)
        set_jid(jid)
      end
    end
  end
end
