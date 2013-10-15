# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/x'

module Jabber
  module MUC
    class IqQueryMUCOwner < IqQuery
      name_xmlns 'query', 'http://jabber.org/protocol/muc#owner'

      include XParent
    end
  end
end
