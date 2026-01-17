# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/x'
require 'xmpp4r/jid'
require 'time'

module Jabber
  module Delay
    ##
    # Implementation of JEP 0091
    # for <x xmlns='jabber:x:delay' stamp='...' .../>
    # applied on <message/> and <presence/> stanzas
    #
    # One may also use XDelay#text for a descriptive reason
    # for the delay.
    #
    # Please note that you must require 'xmpp4r/xdelay' to use
    # this class as it's not required by a basic XMPP implementation.
    # <x/> elements with the specific namespace will then be
    # converted to XDelay automatically.
    class XDelay < X
      name_xmlns 'x', 'jabber:x:delay'

      ##
      # Initialize a new XDelay element
      #
      # insertnow:: [Boolean] Set the stamp to [Time::now]
      def initialize(insertnow=true)
        super()

        if insertnow
          set_stamp(Time.now)
        end
      end

      ##
      # Get the timestamp
      # result:: [Time] or nil
      def stamp
        if attributes['stamp']
          begin
            # Actually this should be Time.xmlschema,
            # but "unfortunately, the 'jabber:x:delay' namespace predates" JEP 0082
            Time.parse(attributes['stamp'])
          rescue ArgumentError
            nil
          end
        else
          nil
        end
      end

      ##
      # Set the timestamp
      # t:: [Time] or nil
      def stamp=(t)
        if t.nil?
          attributes['stamp'] = nil
        else
          attributes['stamp'] = t.strftime("%Y%m%dT%H:%M:%S")
        end
      end

      ##
      # Set the timestamp (chaining-friendly)
      def set_stamp(t)
        self.stamp = t
        self
      end

      ##
      # Get the timestamp's origin
      # result:: [JID]
      def from
        if attributes['from']
          JID.new(attributes['from'])
        else
          nil
        end
      end

      ##
      # Set the timestamp's origin
      # jid:: [JID]
      def from=(jid)
        attributes['from'] = jid.nil? ? nil : jid.to_s
      end

      ##
      # Set the timestamp's origin (chaining-friendly)
      def set_from(jid)
        self.from = jid
        self
      end
    end
  end
end
