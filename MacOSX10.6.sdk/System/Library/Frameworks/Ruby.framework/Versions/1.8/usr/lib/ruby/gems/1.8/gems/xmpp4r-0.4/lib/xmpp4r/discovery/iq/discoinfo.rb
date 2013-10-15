# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/query'

module Jabber
  module Discovery
    NS_DISCO_INFO = 'http://jabber.org/protocol/disco#info'

    ##
    # Class for handling Service Discovery queries,
    # info
    # (JEP 0030)
    #
    # This <query/> may contain multiple Identity and Feature
    # elements, describing the type and the supported namespaces of
    # the service.
    class IqQueryDiscoInfo < IqQuery
      name_xmlns 'query', NS_DISCO_INFO

      ##
      # Get the queried Service Discovery node or nil
      #
      # See IqQueryDiscoItems#node for a
      # small explanation of this.
      def node
        attributes['node']
      end

      ##
      # Get the queried Service Discovery node or nil
      # val:: [String]
      def node=(val)
        attributes['node'] = val
      end

      ##
      # Get the queried Service Discovery node or nil
      # (chaining-friendly)
      # val:: [String]
      def set_node(val)
        self.node = val
        self
      end

      ##
      # Get the first identity child
      # result:: [Identity]
      def identity
        first_element('identity')
      end

      ##
      # Get list of identities
      # result:: [Array] of [Identity]
      def identities
        get_elements('identity')
      end

      ##
      # Get list of features
      # result:: [Array] of [String]
      def features
        res = []
        each_element('feature') { |feature|
          res.push(feature.var)
        }
        res
      end
    end


    ##
    # Service Discovery identity to add() to IqQueryDiscoInfo
    #
    # Please note that XEP 0030 requires both category and type to occur,
    # for a reference see: http://www.xmpp.org/registrar/disco-categories.html
    class Identity < XMPPElement
      name_xmlns 'identity', NS_DISCO_INFO

      ##
      # Initialize a new Identity
      # category:: [String] Initial category or nil
      # iname:: [String] Initial identity name or nil
      # type:: [String] Initial type or nil
      def initialize(category=nil, iname=nil, type=nil)
        super()
        set_category(category)
        set_iname(iname)
        set_type(type)
      end

      ##
      # Get the identity's category or nil
      # result:: [String]
      def category
        attributes['category']
      end

      ##
      # Set the identity's category
      #
      # Service Discovery categories should be somewhat
      # standardized by some registry, so clients may
      # represent specific categories by specific icons...
      # (see http://www.jabber.org/registrar/disco-categories.html)
      # val:: [String]
      def category=(val)
        attributes['category'] = val
      end

      ##
      # Set the identity's category (chaining-friendly)
      # val:: [String]
      def set_category(val)
        self.category = val
        self
      end

      ##
      # Get the identity's name or nil
      #
      # This has been renamed from <name/> to "iname" here
      # to keep REXML::Element#name accessible
      # result:: [String]
      def iname
        attributes['name']
      end

      ##
      # Set the identity's name
      # val:: [String]
      def iname=(val)
        attributes['name'] = val
      end

      ##
      # Set the identity's name (chaining-friendly)
      # val:: [String]
      def set_iname(val)
        self.iname = val
        self
      end

      ##
      # Get the identity's type or nil
      # result:: [String]
      def type
        attributes['type']
      end

      ##
      # Set the identity's type
      # (see http://www.jabber.org/registrar/disco-categories.html)
      # val:: [String]
      def type=(val)
        attributes['type'] = val
      end

      ##
      # Set the identity's type (chaining-friendly)
      # val:: [String]
      def set_type(val)
        self.type = val
        self
      end
    end

    ##
    # Service Discovery feature to add() to IqQueryDiscoInfo
    #
    # Please note that JEP 0030 requires var to be set,
    # for a reference see: http://www.xmpp.org/registrar/disco-features.html
    class Feature < XMPPElement
      name_xmlns 'feature', NS_DISCO_INFO

      ##
      # Create a new <feature/> element
      # var:: [String] New var
      def initialize(var=nil)
        super()
        set_var(var)
      end

      ##
      # Get the feature's var or nil
      # result:: [String]
      def var
        attributes['var']
      end

      ##
      # Set the feature's var
      #
      # This is a namespace the identity supports.
      # val:: [String]
      def var=(val)
        attributes['var'] = val
      end

      ##
      # Set the feature's var (chaining-friendly)
      # val:: [String]
      def set_var(val)
        self.var = val
        self
      end
    end
  end
end
