# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/xmppstanza'
require 'xmpp4r/jid'
require 'digest/sha1'

require 'xmpp4r/query'
require 'xmpp4r/vcard/iq/vcard'

module Jabber
  ##
  # IQ: Information/Query
  # (see RFC3920 - 9.2.3
  #
  # A class used to build/parse IQ requests/responses
  class Iq < XMPPStanza
    name_xmlns 'iq', 'jabber:client'
    force_xmlns true

    @@element_classes = {}

    ##
    # Build a new <iq/> stanza
    # type:: [Symbol] or nil, see Iq#type
    # to:: [JID] Recipient
    def initialize(type = nil, to = nil)
      super()

      if not to.nil?
        set_to(to)
      end
      if not type.nil?
        set_type(type)
      end
    end

    ##
    # Get the type of the Iq stanza
    #
    # The following values are allowed:
    # * :get
    # * :set
    # * :result
    # * :error
    # result:: [Symbol] or nil
    def type
      case super
        when 'get' then :get
        when 'set' then :set
        when 'result' then :result
        when 'error' then :error
        else nil
      end
    end

    ##
    # Set the type of the Iq stanza (see Iq#type)
    # v:: [Symbol] or nil
    def type=(v)
      case v
        when :get then super('get')
        when :set then super('set')
        when :result then super('result')
        when :error then super('error')
        else super(nil)
      end
    end

    ##
    # Set the type of the Iq stanza (chaining-friendly)
    # v:: [Symbol] or nil
    def set_type(v)
      self.type = v
      self
    end

    ##
    # Returns the iq's query child, or nil
    # result:: [IqQuery]
    def query
      first_element('query')
    end

    ##
    # Delete old elements named newquery.name
    #
    # newquery:: [REXML::Element] will be added
    def query=(newquery)
      delete_elements(newquery.name)
      add(newquery)
    end

    ##
    # Returns the iq's query's namespace, or nil
    # result:: [String]
    def queryns
      e = first_element('query')
      if e
        return e.namespace
      else
        return nil
      end
    end

    ##
    # Returns the iq's <vCard/> child, or nil
    # result:: [IqVcard]
    def vcard
      first_element('vCard')
    end

    ##
    # Returns the iq's <pubsub/> child, or nil
    # result:: [IqVcard]
    def pubsub
      first_element('pubsub')
    end

    ##
    # Returns the iq's <command/> child, or nil
    # resulte:: [IqCommand]
    def command
      first_element("command")
    end

    ##
    # Create a new Iq stanza with an unspecified query child
    # (<query/> has no namespace)
    def Iq.new_query(type = nil, to = nil)
      iq = Iq.new(type, to)
      query = IqQuery.new
      iq.add(query)
      iq
    end

    ##
    # Create a new jabber:iq:auth set Stanza.
    def Iq.new_authset(jid, password)
      iq = Iq.new(:set)
      query = IqQuery.new
      query.add_namespace('jabber:iq:auth')
      query.add(REXML::Element.new('username').add_text(jid.node))
      query.add(REXML::Element.new('password').add_text(password))
      query.add(REXML::Element.new('resource').add_text(jid.resource)) if not jid.resource.nil?
      iq.add(query)
      iq
    end

    ##
    # Create a new jabber:iq:auth set Stanza for Digest authentication
    def Iq.new_authset_digest(jid, session_id, password)
      iq = Iq.new(:set)
      query = IqQuery.new
      query.add_namespace('jabber:iq:auth')
      query.add(REXML::Element.new('username').add_text(jid.node))
      query.add(REXML::Element.new('digest').add_text(Digest::SHA1.hexdigest(session_id + password)))
      query.add(REXML::Element.new('resource').add_text(jid.resource)) if not jid.resource.nil?
      iq.add(query)
      iq
    end

    ##
    # Create a new jabber:iq:register set stanza for service/server registration
    # username:: [String] (Element will be ommited if unset)
    # password:: [String] (Element will be ommited if unset)
    def Iq.new_register(username=nil, password=nil)
      iq = Iq.new(:set)
      query = IqQuery.new
      query.add_namespace('jabber:iq:register')
      query.add(REXML::Element.new('username').add_text(username)) if username
      query.add(REXML::Element.new('password').add_text(password)) if password
      iq.add(query)
      iq
    end

    ##
    # Create a new jabber:iq:register get stanza for retrieval
    # of accepted registration information
    def Iq.new_registerget
      iq = Iq.new(:get)
      query = IqQuery.new
      query.add_namespace('jabber:iq:register')
      iq.add(query)
      iq
    end

    ##
    # Create a new jabber:iq:roster get Stanza.
    #
    # IqQueryRoster is unused here because possibly not require'd
    def Iq.new_rosterget
      iq = Iq.new(:get)
      query = IqQuery.new
      query.add_namespace('jabber:iq:roster')
      iq.add(query)
      iq
    end

    ##
    # Create a new jabber:iq:roster get Stanza.
    def Iq.new_browseget
      iq = Iq.new(:get)
      query = IqQuery.new
      query.add_namespace('jabber:iq:browse')
      iq.add(query)
      iq
    end

    ##
    # Create a new jabber:iq:roster set Stanza.
    def Iq.new_rosterset
      iq = Iq.new(:set)
      query = IqQuery.new
      query.add_namespace('jabber:iq:roster')
      iq.add(query)
      iq
    end
  end
end
