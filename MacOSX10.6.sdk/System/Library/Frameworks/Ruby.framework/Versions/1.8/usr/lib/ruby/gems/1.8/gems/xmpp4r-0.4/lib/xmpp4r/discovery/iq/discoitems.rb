# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/query'

module Jabber
  module Discovery
    NS_DISCO_ITEMS = 'http://jabber.org/protocol/disco#items'

    ##
    # Class for handling Service Discovery queries,
    # items
    # (JEP 0030)
    #
    # This <query/> may contain multiple Item elements,
    # describing multiple services to be browsed by Jabber clients.
    # These may then get further information about these items by
    # querying IqQueryDiscoInfo and further sub-items by querying
    # IqQueryDiscoItems.
    class IqQueryDiscoItems < IqQuery
      name_xmlns 'query', NS_DISCO_ITEMS

      ##
      # Get the queried Service Discovery node or nil
      #
      # A Service Discovery node is _not_ a JID node,
      # this may be a bit confusing. It's just to make
      # Service Discovery browsing a bit more structured.
      def node
        attributes['node']
      end

      ##
      # Get the queried Service Discovery node or nil
      def node=(val)
        attributes['node'] = val
      end

      ##
      # Get the queried Service Discovery node or nil
      # (chaining-friendly)
      def set_node(val)
        self.node = val
        self
      end

      ##
      # Get all item children
      # result:: Array of [Discovery::Item]
      def items
        get_elements('item')
      end
    end


    ##
    # Service Discovery item to add() to IqQueryDiscoItems
    #
    # Please note that JEP 0030 requires the jid to occur
    class Item < XMPPElement
      name_xmlns 'item', NS_DISCO_ITEMS

      ##
      # Initialize a new Service Discovery <item/>
      # to be added to IqQueryDiscoItems
      # jid:: [JID]
      # iname:: [String] Item name
      # node:: [String] Service Discovery node (_not_ JID#node)
      def initialize(jid=nil, iname=nil, node=nil)
        super()
        set_jid(jid)
        set_iname(iname)
        set_node(node)
      end

      ##
      # Get the item's jid or nil
      # result:: [String]
      def jid
        JID.new(attributes['jid'])
      end

      ##
      # Set the item's jid
      # val:: [JID]
      def jid=(val)
        attributes['jid'] = val.to_s
      end

      ##
      # Set the item's jid (chaining-friendly)
      # val:: [JID]
      def set_jid(val)
        self.jid = val
        self
      end

      ##
      # Get the item's name or nil
      #
      # This has been renamed from <name/> to "iname" here
      # to keep REXML::Element#name accessible
      # result:: [String]
      def iname
        attributes['name']
      end

      ##
      # Set the item's name
      # val:: [String]
      def iname=(val)
        attributes['name'] = val
      end

      ##
      # Set the item's name (chaining-friendly)
      # val:: [String]
      def set_iname(val)
        self.iname = val
        self
      end

      ##
      # Get the item's Service Discovery node or nil
      # result:: [String]
      def node
        attributes['node']
      end

      ##
      # Set the item's Service Discovery node
      # val:: [String]
      def node=(val)
        attributes['node'] = val
      end

      ##
      # Set the item's Service Discovery node (chaining-friendly)
      # val:: [String]
      def set_node(val)
        self.node = val
        self
      end
    end
  end
end
