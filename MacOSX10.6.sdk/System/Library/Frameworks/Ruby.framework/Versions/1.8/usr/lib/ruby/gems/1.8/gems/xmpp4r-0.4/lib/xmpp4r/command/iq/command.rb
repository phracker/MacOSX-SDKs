require 'xmpp4r/iq'

module Jabber

  module Command

    ##
    # Class for handling ad-hoc commands
    # (JEP 0050)
    #
    # A command is uniquely identified by its node attribute.
    class IqCommand < Iq
      name_xmlns 'command', 'http://jabber.org/protocol/commands'

      def initialize(node=nil, action=nil)
        super()
        set_node(node)
        set_action(action)
      end

      ##
      # Get the node of the Command stanza
      # result:: [String] or nil
      def node
        attributes['node']
      end

      ##
      # Set the node of the Command stanza
      # v:: [String] or nil
      def node=(v)
        attributes['node'] = v
      end

      ##
      # Set the node of the Command stanza (chaining-friendly)
      # v:: [String] or nil
      def set_node(v)
        self.node = v
        self
      end

      ##
      # Get the sessionid of the Command stanza
      # result:: [String] or nil
      def sessionid
        attributes['sessionid']
      end

      ##
      # Set the sessionid of the Command stanza
      # v:: [String] or nil
      def sessionid=(v)
        attributes['sessionid'] = v
      end

      ##
      # Set the sessionid of the Command stanza (chaining-friendly)
      # v:: [String] or nil
      def set_sessionid(v)
        self.sessionid = v
        self
      end

      ##
      # Get the action of the Command stanza
      #
      # The following Symbols are allowed:
      # * :execute
      # * :cancel
      # * :prev
      # * :next
      # * :complete
      # return:: [Symbol] or nil
      def action
        case attributes['action']
          when 'execute' then :execute
          when 'cancel' then :cancel
          when 'prev' then :prev
          when 'next' then :next
          when 'complete' then :complete
          else nil
        end
      end

      ##
      # Set the action of the Command stanza (see IqCommand#action for details)
      # v:: [Symbol] or nil
      def action=(v)
        attributes['action'] = case v
          when :execute then 'execute'
          when :cancel then 'cancel'
          when :prev then 'prev'
          when :next then 'next'
          when :complete then 'complete'
          else nil
        end
      end

      ##
      # Set the action of the Command stanza (chaining-friendly)
      # v:: [Symbol] or nil
      def set_action(v)
        self.action = v
        self
      end

      ##
      # Get the status of the Command stanza
      #
      # The following Symbols are allowed:
      # * :executing
      # * :completed
      # * :canceled
      # return:: [Symbol] or nil
      def status
        case attributes['status']
          when 'executing' then :executing
          when 'completed' then :completed
          when 'canceled' then :canceled
          else nil
        end
      end

      ##
      # Set the status of the Command stanza (see IqCommand#status for details)
      # v:: [Symbol] or nil
      def status=(v)
        attributes['status'] = case v
          when :executing then 'executing'
          when :completed then 'completed'
          when :canceled then 'canceled'
          else nil
        end
      end

      ##
      # Set the status of the Command stanza (chaining-friendly)
      # v:: [Symbol] or nil
      def set_status(v)
        self.status = v
        self
      end

      ##
      # Get the actions allowed
      # return:: [REXML::Element] or nil
      def actions
        first_element('actions')
      end

    end
  end
end
