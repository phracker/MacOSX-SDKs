# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

module Jabber
  module MUC
    class XMUCUserInvite < XMPPElement
      name_xmlns 'invite', 'http://jabber.org/protocol/muc#user'

      def initialize(to=nil, reason=nil)
        super()
        set_to(to)
        set_reason(reason)
      end

      def to
        attributes['to'].nil? ? nil : JID.new(attributes['to'])
      end

      def to=(j)
        attributes['to'] = j.nil? ? nil : j.to_s
      end

      def set_to(j)
        self.to = j
        self
      end

      def from
        attributes['from'].nil? ? nil : JID.new(attributes['from'])
      end

      def from=(j)
        attributes['from'] = (j.nil? ? nil : j.to_s)
      end

      def set_from(j)
        self.from = j
        self
      end

      def reason
        first_element_text('reason')
      end

      def reason=(s)
        if s
          replace_element_text('reason', s)
        else
          delete_elements('reason')
        end
      end

      def set_reason(s)
        self.reason = s
        self
      end
    end
  end
end
