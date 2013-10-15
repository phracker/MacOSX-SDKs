# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/query'

module Jabber
  module RPC
    class IqQueryRPC < IqQuery
      NS_RPC = 'jabber:iq:rpc'
      name_xmlns 'query', NS_RPC

      # TODO: Is typed_add with a String right here?
      def typed_add(e)
        if e.kind_of? String
          typed_add(REXML::Document.new(e).root)
        else
          super
        end
      end
    end
  end
end
