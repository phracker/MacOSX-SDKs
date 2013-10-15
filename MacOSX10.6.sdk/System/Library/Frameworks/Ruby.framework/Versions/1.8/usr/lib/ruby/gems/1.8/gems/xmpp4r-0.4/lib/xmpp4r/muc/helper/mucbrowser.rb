# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/discovery'

module Jabber
  module MUC
    ##
    # The MUCBrowser helper can be used to discover
    # Multi-User-Chat components via Service Discovery
    #
    # See JEP 0045 sections 6.1. and 6.2.
    #
    # Usage of its functions should be threaded as
    # responses can take a while
    class MUCBrowser
      ##
      # Initialize a new MUCBrowser helper
      def initialize(stream)
        @stream = stream
      end

      ##
      # Retrieve the name of a MUC component,
      # depending upon whether the target entity supports
      # the MUC protocol.
      #
      # A return-value of nil does *not* mean that the entity
      # does not exist or does not support Service Discovery!
      # nil just means that this is not a MUC-compliant service.
      #
      # Throws an ServerError when receiving
      # <tt><iq type='error'/></tt>
      # jid:: [JID] Target entity (set only domain!)
      # return:: [String] or [nil]
      def muc_name(jid)
        iq = Iq.new(:get, jid)
        iq.from = @stream.jid  # Enable components to use this
        iq.add(Discovery::IqQueryDiscoInfo.new)

        res = nil

        @stream.send_with_id(iq) do |answer|
          if answer.type == :result
            answer.query.each_element('feature') { |feature|
              # Look if the component has a MUC or Groupchat feature
              if feature.var == 'http://jabber.org/protocol/muc' or feature.var == 'gc-1.0'
                # If so, get the identity
                if answer.query.first_element('identity')
                  res = answer.query.first_element('identity').iname
                end
              end
            }
            true
          else
            false
          end
        end

        res
      end

      ##
      # Retrieve the existing rooms of a MUC component
      #
      # The resulting Hash contains pairs of room JID and room name
      #
      # Usage:
      #  my_mucbrowse_helper.muc_rooms('conference.jabber.org').each { |jid,name| ... }
      #
      # Throws an exception when receiving <tt><iq type='error'/></tt>
      # jid:: [JID] Target entity (set only domain!)
      # return:: [Hash]
      def muc_rooms(jid)
        iq = Iq.new(:get, jid)
        iq.from = @stream.jid  # Enable components to use this
        iq.add(Discovery::IqQueryDiscoItems.new)

        rooms = {}

        @stream.send_with_id(iq) do |answer|
          answer.query.each_element('item') { |item|
            rooms[item.jid] = item.iname
          }
        end

        rooms
      end
    end
  end
end
