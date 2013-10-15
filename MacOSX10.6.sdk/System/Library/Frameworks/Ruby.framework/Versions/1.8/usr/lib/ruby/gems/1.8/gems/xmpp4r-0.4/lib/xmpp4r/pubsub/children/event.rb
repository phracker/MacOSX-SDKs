# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/iq'

module Jabber
  module PubSub

    ##
    # Event
    # a publishing event
    class Event < XMPPElement
      name_xmlns 'event', NS_PUBSUB + '#event'
      force_xmlns true

      ##
      # return payload
      def payload
        elements
      end

      ##
      # add payload
      # payload:: [REXML::Element]
      def payload=(pl)
        add_element = pl
      end

      ##
      # return the payload type
      def event_type?
        # each child of event
        # this should iterate only one time
        each_element('./event/*') { |plelement|
          case plelement.name
            when 'collection' 	   then return :collection
            when 'configuration'   then	return :configuration
            when 'delete'	   then return :delete
            when 'items'	   then return :items
            when 'purge'	   then return :purge
            when 'subscription'	   then return :subscription
            else return nil
          end
        }
      end
    end
  end
end
