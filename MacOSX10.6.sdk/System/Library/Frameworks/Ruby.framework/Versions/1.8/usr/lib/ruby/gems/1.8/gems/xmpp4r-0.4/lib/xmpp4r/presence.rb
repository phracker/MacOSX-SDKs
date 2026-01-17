# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/xmppstanza'
require 'xmpp4r/x'

module Jabber
  ##
  # The presence class is used to construct presence messages to
  # send to the Jabber service.
  class Presence < XMPPStanza
    name_xmlns 'presence', 'jabber:client'
    force_xmlns true

    include Comparable
    include XParent

    ##
    # Create presence stanza
    # show:: [String] Initial Availability Status
    # status:: [String] Initial status message
    # priority:: [Fixnum] Initial priority value
    def initialize(show=nil, status=nil, priority=nil)
      super()
      set_show(show) if show
      set_status(status) if status
      set_priority(priority) if priority
    end

    ##
    # Get type of presence
    #
    # result:: [Symbol] or [Nil] Possible values are:
    # * :error
    # * :probe (Servers send this to request presence information)
    # * :subscribe (Subscription request)
    # * :subscribed (Subscription approval)
    # * :unavailable (User has gone offline)
    # * :unsubscribe (Unsubscription request)
    # * :unsubscribed (Unsubscription approval)
    # * [nil] (available)
    # See RFC3921 - 2.2.1. for explanation.
    def type
      case super
        when 'error' then :error
        when 'probe' then :probe
        when 'subscribe' then :subscribe
        when 'subscribed' then :subscribed
        when 'unavailable' then :unavailable
        when 'unsubscribe' then :unsubscribe
        when 'unsubscribed' then :unsubscribed
        else nil
      end
    end

    ##
    # Set type of presence
    # val:: [Symbol] See type for possible subscription types
    def type=(val)
      case val
        when :error then super('error')
        when :probe then super('probe')
        when :subscribe then super('subscribe')
        when :subscribed then super('subscribed')
        when :unavailable then super('unavailable')
        when :unsubscribe then super('unsubscribe')
        when :unsubscribed then super('unsubscribed')
        else super(nil)
      end
    end

    ##
    # Set type of presence (chaining-friendly)
    # val:: [Symbol] See type for possible subscription types
    def set_type(val)
      self.type = val
      self
    end

    ##
    # Get Availability Status (RFC3921 - 5.2)
    # result:: [Symbol] or [Nil] Valid values according to RFC3921:
    # * nil (Available, no <show/> element)
    # * :away
    # * :chat (Free for chat)
    # * :dnd (Do not disturb)
    # * :xa (Extended away)
    def show
      e = first_element('show')
      text = e ? e.text : nil
      case text
        when 'away' then :away
        when 'chat' then :chat
        when 'dnd' then :dnd
        when 'xa' then :xa
        else nil
      end
    end

    ##
    # Set Availability Status
    # val:: [Symbol] or [Nil] See show for explanation
    def show=(val)
      xe = first_element('show')
      if xe.nil?
        xe = add_element('show')
      end
      case val
        when String then raise "Invalid value for show."
        when :away then text = 'away'
        when :chat then text = 'chat'
        when :dnd then text = 'dnd'
        when :xa then text = 'xa'
        when nil then text = nil
        else raise "Invalid value for show."
      end

      if text.nil?
        delete_element(xe)
      else
        xe.text = text
      end
    end

    ##
    # Set Availability Status (chaining-friendly)
    # val:: [Symbol] or [Nil] See show for explanation
    def set_show(val)
      self.show = val
      self
    end

    ##
    # Get status message
    # result:: [String] or nil
    def status
      first_element_text('status')
    end

    ##
    # Set status message
    # val:: [String] or nil
    def status=(val)
      if val.nil?
        delete_element('status')
      else
        replace_element_text('status', val)
      end
    end

    ##
    # Set status message (chaining-friendly)
    # val:: [String] or nil
    def set_status(val)
      self.status = val
      self
    end

    ##
    # Get presence priority, or nil if absent
    # result:: [Integer]
    def priority
       e = first_element_text('priority')
      if e
        return e.to_i
      else
        return nil
      end
    end

    ##
    # Set presence priority
    # val:: [Integer] Priority value between -128 and +127
    #
    # *Warning:* negative values make you receive no subscription requests etc.
    # (RFC3921 - 2.2.2.3.)
    def priority=(val)
      if val.nil?
        delete_element('priority')
      else
        replace_element_text('priority', val)
      end
    end

    ##
    # Set presence priority (chaining-friendly)
    # val:: [Integer] Priority value between -128 and +127
    def set_priority(val)
      self.priority = val
      self
    end

    ##
    # Compare two presences using priority
    # (with cmp_interest as fall-back).
    def <=>(o)
      if priority.to_i == o.priority.to_i
        cmp_interest(o)
      else
        priority.to_i <=> o.priority.to_i
      end
    end

    ##
    # Compare two presences. The most suitable to talk with is the
    # biggest.
    PRESENCE_STATUS = { :chat => 4,
                        nil => 3,
                        :dnd => 2,
                        :away => 1,
                        :xa => 0,
                        :unavailable => -1,
                        :error => -2 }
    def cmp_interest(o)
      if type.nil?
        if o.type.nil?
          # both available.
          PRESENCE_STATUS[show] <=> PRESENCE_STATUS[o.show]
        else
          return -1
        end
      elsif o.type.nil?
        return 1
      else
        # both are non-nil. We consider this is equal.
        return 0
      end
    end

  end
end
