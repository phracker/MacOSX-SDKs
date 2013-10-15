# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/xmppelement'

module Jabber
  ##
  # A class used to build/parse <x/> elements
  #
  # These elements may occur as "attachments"
  # in [Message] and [Presence] stanzas
  class X < XMPPElement
    name_xmlns 'x'
    force_xmlns true
  end

  module XParent
    ##
    # Get the first <x/> element in this stanza, or nil if none found.
    # wanted_xmlns:: [String] Optional, find the first <x/> element having this xmlns,
    # wanted_xmlns can also be a derivate of XMPPElement from which the namespace will be taken
    # result:: [REXML::Element] or nil
    def x(wanted_xmlns=nil)
      if wanted_xmlns.kind_of? Class and wanted_xmlns.ancestors.include? XMPPElement
        wanted_xmlns = wanted_xmlns.new.namespace
      end

        each_element('x') { |x|
        if wanted_xmlns.nil? or wanted_xmlns == x.namespace
          return x
        end
      }
      nil
    end
  end
end
