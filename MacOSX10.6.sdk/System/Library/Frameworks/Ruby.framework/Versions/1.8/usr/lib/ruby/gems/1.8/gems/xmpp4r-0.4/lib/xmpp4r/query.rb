# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/xmppelement'

module Jabber
  ##
  # A class used to build/parse IQ Query requests/responses
  #
  class IqQuery < XMPPElement
    name_xmlns 'query'
    force_xmlns true
  end
end
