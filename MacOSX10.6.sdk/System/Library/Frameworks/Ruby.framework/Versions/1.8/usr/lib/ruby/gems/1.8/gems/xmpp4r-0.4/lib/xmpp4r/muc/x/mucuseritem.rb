# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/muc/item'

module Jabber
  module MUC
    class XMUCUserItem < MUC::UserItem
      name_xmlns 'item', 'http://jabber.org/protocol/muc#user'

      def initialize(affiliation=nil, role=nil, jid=nil)
        super()
        set_affiliation(affiliation)
        set_role(role)
        set_jid(jid)
      end

      def continue
        c = nil
        each_element('continue') { |xe| c = xe }
        c.nil?
      end

      def continue=(c)
        delete_elements('continue')
        add_element('continue') if c
      end

      def set_continue(c)
        self.continue = c
        self
      end
    end
  end
end
