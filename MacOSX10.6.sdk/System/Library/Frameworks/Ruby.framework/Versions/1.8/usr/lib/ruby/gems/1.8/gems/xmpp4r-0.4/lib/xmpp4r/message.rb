# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/xmppstanza'
require 'xmpp4r/x'

module Jabber
  ##
  # The Message class manages the <message/> stanzas,
  # which is used for all messaging communication.
  class Message < XMPPStanza

    name_xmlns 'message', 'jabber:client'
    force_xmlns true

    include XParent

    ##
    # Create a new message
    # >to:: a JID or a String object to send the message to.
    # >body:: the message's body
    def initialize(to = nil, body = nil)
      super()
      if not to.nil?
        set_to(to)
      end
      if !body.nil?
        add_element(REXML::Element.new("body").add_text(body))
      end
    end

    ##
    # Get the type of the Message stanza
    #
    # The following Symbols are allowed:
    # * :chat
    # * :error
    # * :groupchat
    # * :headline
    # * :normal
    # result:: [Symbol] or nil
    def type
      case super
        when 'chat' then :chat
        when 'error' then :error
        when 'groupchat' then :groupchat
        when 'headline' then :headline
        when 'normal' then :normal
        else nil
      end
    end

    ##
    # Set the type of the Message stanza (see Message#type for details)
    # v:: [Symbol] or nil
    def type=(v)
      case v
        when :chat then super('chat')
        when :error then super('error')
        when :groupchat then super('groupchat')
        when :headline then super('headline')
        when :normal then super('normal')
        else super(nil)
      end
    end

    ##
    # Set the type of the Message stanza (chaining-friendly)
    # v:: [Symbol] or nil
    def set_type(v)
      self.type = v
      self
    end

    ##
    # Returns the message's body, or nil.
    # This is the message's plain-text content.
    def body
      first_element_text('body')
    end

    ##
    # Sets the message's body
    #
    # b:: [String] body to set
    def body=(b)
      replace_element_text('body', b)
    end

    ##
    # Sets the message's body
    #
    # b:: [String] body to set
    # return:: [REXML::Element] self for chaining
    def set_body(b)
      self.body = b
      self
    end

    ##
    # sets the message's subject
    #
    # s:: [String] subject to set
    def subject=(s)
      replace_element_text('subject', s)
    end

    ##
    # sets the message's subject
    #
    # s:: [String] subject to set
    # return:: [REXML::Element] self for chaining
    def set_subject(s)
      self.subject = s
      self
    end

    ##
    # Returns the message's subject, or nil
    def subject
      first_element_text('subject')
    end

    ##
    # sets the message's thread
    # s:: [String] thread to set
    def thread=(s)
      delete_elements('thread')
      replace_element_text('thread', s) unless s.nil?
    end

    ##
    # gets the message's thread (chaining-friendly)
    # Please note that this are not [Thread] but a [String]-Identifier to track conversations
    # s:: [String] thread to set
    def set_thread(s)
      self.thread = s
      self
    end

    ##
    # Returns the message's thread, or nil
    def thread
      first_element_text('thread')
    end
  end
end
