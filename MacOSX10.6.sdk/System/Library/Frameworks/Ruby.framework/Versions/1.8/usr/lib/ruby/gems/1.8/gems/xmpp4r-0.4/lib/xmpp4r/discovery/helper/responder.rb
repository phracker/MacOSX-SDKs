# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/iq'
require 'xmpp4r/discovery/iq/discoinfo'
require 'xmpp4r/discovery/iq/discoitems'
require 'xmpp4r/caps/helper/generator'

module Jabber
  module Discovery
    ##
    # Responds to Service Discovery queries on a given node
    #
    # Modify returned elements by these attributes:
    # * Responder#identities
    # * Responder#features (Responder#add_features is a short-cut accepting an Array of Strings, too)
    # * Responder#forms
    # * Responder#items
    class Responder
      ##
      # Service Discovery node this Responder is responsible for
      # (will not answer queries for other nodes)
      attr_reader :node

      ##
      # Identities returned on Discovery Info query
      #
      # Array of [Discovery::Identity]
      attr_accessor :identities
      ##
      # Features returned on Discovery Info query,
      #
      # Array of [Discovery::Feature]
      attr_accessor :features
      ##
      # Forms returned on Discovery Info query
      # (such as Software Information)
      #
      # Array of [Dataforms::XData]
      attr_accessor :forms

      ##
      # Children returned on Discovery Item query
      #
      # May contain other Discovery::Responder instances
      # which will generate an item dynamically from their
      # first identity
      #
      # Array of [Discovery::Item] or [Discovery::Responder] (mixed)
      attr_accessor :items

      ##
      # Set the JID this helper feels responsible for
      # (default: nil, responsible for any JID)
      attr_accessor :my_jid

      CALLBACK_PRIORITY = 180

      ##
      # Initialize responder for a specific node
      # stream:: [Jabber::Stream]
      # node:: [nil] or [String]
      def initialize(stream, node=nil, identities=[], features=[], items=[])
        @stream = stream
        @my_jid = nil
        @node = node
        @identities = identities
        @features = []
        add_features(features)
        @forms = []
        @items = items

        @stream.add_iq_callback(CALLBACK_PRIORITY, self) do |iq|
          my_nodes = [@node, "#{@node}##{generate_ver}"]

          if iq.type == :get and
             iq.query.kind_of? IqQueryDiscoInfo and
             my_nodes.include?(iq.query.node)

            answer = iq.answer(false)
            answer.type = :result
            query = answer.add(IqQueryDiscoInfo.new)
            query.node = iq.query.node
            (@identities + @features + @forms).each do |element|
              query.add(element)
            end
            @stream.send(answer)

            true  # handled

          elsif iq.type == :get and
                iq.query.kind_of? IqQueryDiscoItems and
                my_nodes.include?(iq.query.node)

            answer = iq.answer(false)
            answer.type = :result
            query = answer.add(IqQueryDiscoItems.new)
            query.node = iq.query.node
            @items.each do |item|
              if item.kind_of? Responder
                query.add(item.generate_item)
              else
                query.add(item)
              end
            end
            @stream.send(answer)

            true  # handled

          else
            false # not handled
          end
        end
      end

      ##
      # Add a feature
      # feature:: [Jabber::Discovery::Feature] or [String]
      def add_feature(feature)
        if feature.kind_of? Feature
          @features << feature
        else
          @features << Feature.new(feature.to_s)
        end
      end

      ##
      # Add a series of features
      # features:: Array of [Jabber::Discovery::Feature] or [String]
      def add_features(features)
        features.each { |feature|
          add_feature(feature)
        }
      end

      ##
      # Generate a XEP-0115: Entity Capabilities <c/> element
      # for inclusion in Presence stanzas. This enables efficient
      # caching of Service Discovery information.
      def generate_caps
        Caps::C.new(@node, generate_ver)
      end

      ##
      # Generate an item for inclusion in items discovery in other
      # responders
      # return:: [Discovery::Item] or nil
      def generate_item
        i = @identities.first
        if i
          Item.new(@my_jid || @stream.jid, i.iname, @node)
        else
          nil
        end
      end

      private

      def generate_ver
        Caps::generate_ver(@identities, @features, @forms)
      end
    end
  end
end
