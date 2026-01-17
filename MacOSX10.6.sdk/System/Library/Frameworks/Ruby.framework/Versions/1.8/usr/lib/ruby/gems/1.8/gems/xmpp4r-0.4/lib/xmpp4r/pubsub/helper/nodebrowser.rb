# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/discovery'

module Jabber
  module PubSub
    class NodeBrowser
      ##
      # Initialize a new NodeBrowser
      # new(stream,pubsubservice)
      # stream:: [Jabber::Stream]
      def initialize(stream)
        @stream = stream
      end

      ##
      # Retrieve the nodes
      # Throws an ServerError when receiving
      # <tt><iq type='error'/></tt>
      # jid:: [JID] Target entity (set only domain!)
      # return:: [Array] of [String] or [nil]
      def nodes(jid)
        iq = Iq.new(:get,jid)
        iq.from = @stream.jid
        iq.add(Discovery::IqQueryDiscoItems.new)
        nodes = []
        @stream.send_with_id(iq) do |answer|
          answer.query.each_element('item') { |item|
            nodes.push(item.node)
          }
        end
        nodes
      end

      ##
      # Retrieve the nodes with names
      # Throws a ServerError when receiving
      # <tt><iq type='error'/></tt>
      # jid:: [Jabber::JID] Target entity (set only domain!)
      # return:: [Array] of [Hash] with keys 'node' => [String] and 'name' => [String] or [nil]
      def nodes_names(jid)
        iq = Iq.new(:get,jid)
        iq.from = @stream.jid
        iq.add(Discovery::IqQueryDiscoItems.new)
        nodes = []
        @stream.send_with_id(iq) { |answer|
          answer.query.each_element('item') do |item|
            nodes.push( {'node' => item.node,'name' => item.iname } )
          }
        end
        nodes
      end


      ##
      # Retrieve the items from a node
      # Throws an ServerError when receiving
      # <tt><iq type='error'/></tt>
      # jid:: [Jabber::JID] Target entity (set only domain!)
      # node:: [String]
      # return:: [Array] of [Hash] with keys 'name' => [String] and 'jid' => [Jabber::JID]
      def items(jid,node)
        iq = Iq.new(:get,jid)
        iq.from = @stream.jid
        discoitems = Discovery::IqQueryDiscoItems.new
        discoitems.node = node
        iq.add(discoitems)
        items = []
        err = nil
        @stream.send_with_id(iq) do |answer|
          answer.query.each_element('item') { |item|
            items.push( {'jid' => item.jid,'name' => item.iname } )
          }
        end
        items
      end

      ##
      # get disco info for a node
      # jid:: [Jabber::JID]
      # node:: [String]
      # return:: [Hash] with possible keys type:: [String] ,category:: [String],features:: [Array] of feature, nodeinformation:: [Jabber::XData]
      # check http://www.xmpp.org/extensions/xep-0060.html#entity for more infos
      def get_info(jid,node)
        iq = Iq.new(:get,jid)
        iq.from = @stream.jid
        discoinfo = Discovery::IqQueryDiscoInfo.new
        discoinfo.node = node
        iq.add(discoinfo)
        info = {}
        @stream.send_with_id(iq) do |answer|
          identity = answer.query.identity
          info['type'] = identity.type
          info['category'] = identity.category
          info['features'] = answer.query.features
          
          answer.query.each_element('x') { |x|
            info['nodeinformation'] = x
          }
        end
        info
      end
      # this is only for a xep <-> nodebrowser.rb understanding
      alias get_metadata get_info

      ##
      # get type of node
      # jid:: [Jabber::JID]
      # node:: [String]
      #
      def type(jid,node)
        info = get_info(jid,node)
        return info['type']
      end

      ##
      # get category of node
      # jid:: [Jabber::JID]
      # node:: [String]
      #
      def category(jid,node)
        info = get_info(jid,node)
        return info['category']
      end

    end #class
  end #module
end #module
