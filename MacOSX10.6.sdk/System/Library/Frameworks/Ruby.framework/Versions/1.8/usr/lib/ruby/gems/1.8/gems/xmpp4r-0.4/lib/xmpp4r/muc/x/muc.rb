# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/muc/x/mucuseritem'
require 'xmpp4r/muc/x/mucuserinvite'

module Jabber
  module MUC
    ##
    # Class for <x/> elements
    # with namespace http://jabber.org/protocol/muc
    #
    # See JEP-0045 for details
    class XMUC < X
      name_xmlns 'x', 'http://jabber.org/protocol/muc'

      ##
      # Text content of the <tt><password/></tt> element
      def password
        first_element_text('password')
      end

      ##
      # Set the password for joining a room
      # (text content of the <tt><password/></tt> element)
      def password=(s)
        if s
          replace_element_text('password', s)
        else
          delete_elements('password')
        end
      end
    end

    ##
    # Class for <x/> elements
    # with namespace http://jabber.org/protocol/muc#user
    #
    # See JEP-0058 for details
    class XMUCUser < X
      name_xmlns 'x', 'http://jabber.org/protocol/muc#user'

      ##
      # Retrieve the three-digit code in
      # <tt><x xmlns='http://jabber.org/protocol/muc#user'><status code='...'/></x></tt>
      # result:: [Fixnum] or nil
      def status_code
        e = nil
        each_element('status') { |xe| e = xe }
        if e and e.attributes['code'].size == 3 and e.attributes['code'].to_i != 0
          e.attributes['code'].to_i
        else
          nil
        end
      end

      ##
      # Get all <item/> elements
      # result:: [Array] of [XMUCUserItem]
      def items
        res = []
        each_element('item') { |item|
          res << item
        }
        res
      end
    end
  end
end
