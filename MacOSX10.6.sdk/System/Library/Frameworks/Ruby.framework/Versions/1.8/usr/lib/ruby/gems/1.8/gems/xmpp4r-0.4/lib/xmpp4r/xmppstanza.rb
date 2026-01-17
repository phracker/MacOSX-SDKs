# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/xmppelement'
require 'xmpp4r/errors'
require 'xmpp4r/jid'

module Jabber
  ##
  # root class of all Jabber XML elements
  class XMPPStanza < XMPPElement
    ##
    # Compose a response by doing the following:
    # * Create a new XMPPStanza of the same subclass
    #   with the same element-name
    # * Import xmppstanza if import is true
    # * Swap 'to' and 'from'
    # * Copy 'id'
    # * Does not take care about the type
    #
    # *Attention*: Be careful when answering to stanzas with
    # <tt>type == :error</tt> - answering to an error may generate
    # another error on the other side, which could be leading to a
    # ping-pong effect quickly!
    #
    # xmppstanza:: [XMPPStanza] source
    # import:: [true or false] Copy attributes and children of source
    # result:: [XMPPStanza] answer stanza
    def XMPPStanza.answer(xmppstanza, import=true)
      x = xmppstanza.class.new
      if import
        x.import(xmppstanza)
      end
      x.from = xmppstanza.to
      x.to = xmppstanza.from
      x.id = xmppstanza.id
      x
    end

    ##
    # Return the first <tt><error/></tt> child
    def error
      first_element('error')
    end

    ##
    # Compose a response of this XMPPStanza
    # (see XMPPStanza.answer)
    # result:: [XMPPStanza] New constructed stanza
    def answer(import=true)
      XMPPStanza.answer(self, import)
    end

    ##
    # Makes some changes to the structure of an XML element to help
    # it respect the specification. For example, in a message, we should
    # have <subject/> < <body/> < { rest of tags }
    def normalize
    end

    ##
    # get the to attribute
    #
    # return:: [String] the element's to attribute
    def to
      (a = attribute('to')).nil? ? a : JID.new(a.value)
    end

    ##
    # set the to attribute
    #
    # v:: [String] the value to set
    def to= (v)
      add_attribute('to', v ? v.to_s : nil)
    end

    ##
    # set the to attribute (chaining-friendly)
    #
    # v:: [String] the value to set
    def set_to(v)
      self.to = v
      self
    end

    ##
    # get the from attribute
    #
    # return:: [String] the element's from attribute
    def from
      (a = attribute('from')).nil? ? a : JID.new(a.value)
    end

    ##
    # set the from attribute
    #
    # v:: [String] the value from set
    def from= (v)
      add_attribute('from', v ? v.to_s : nil)
    end

    ##
    # set the from attribute (chaining-friendly)
    #
    # v:: [String] the value from set
    def set_from(v)
      add_attribute('from', v ? v.to_s : nil)
      self
    end

    ##
    # get the id attribute
    #
    # return:: [String] the element's id attribute
    def id
      (a = attribute('id')).nil? ? a : a.value
    end

    ##
    # set the id attribute
    #
    # v:: [String] the value id set
    def id= (v)
      add_attribute('id', v.to_s)
    end

    ##
    # set the id attribute (chaining-friendly)
    #
    # v:: [String] the value id set
    def set_id(v)
      add_attribute('id', v.to_s)
      self
    end

    ##
    # get the type attribute
    #
    # return:: [String] the element's type attribute
    def type
      (a = attribute('type')).nil? ? a : a.value
    end

    ##
    # set the type attribute
    #
    # v:: [String] the value type set
    def type= (v)
      add_attribute('type', v)
    end

    ##
    # set the type attribute (chaining-friendly)
    #
    # v:: [String] the value type set
    def set_type(v)
      add_attribute('type', v)
      self
    end
  end
end
