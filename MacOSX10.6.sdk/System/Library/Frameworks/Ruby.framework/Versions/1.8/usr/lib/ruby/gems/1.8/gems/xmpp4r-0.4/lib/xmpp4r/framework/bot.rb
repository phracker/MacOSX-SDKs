require 'xmpp4r/framework/base'

require 'xmpp4r'
require 'xmpp4r/roster'
require 'xmpp4r/caps/c'
require 'xmpp4r/discovery'
require 'xmpp4r/xhtml'

module Jabber
  module Framework
    ##
    # Abstract handler methods that *may* be implemented by a deriving class:
    # * on_message(text)
    # * on_message_xhtml(html_body, text)
    class Bot < Base
      helper :roster, Roster::Helper
      helper(:disco_default) { |cl|
        Discovery::Responder.new(cl,
                                 nil,
                                 [Jabber::Discovery::Identity.new('client', 'XMPP4R Bot', 'bot')]
                                 )
      }
      helper(:disco_caps) { |cl|
        Discovery::Responder.new(cl,
                                 "http://home.gna.org/xmpp4r/#{Jabber::XMPP4R_VERSION}",
                                 [Jabber::Discovery::Identity.new('client', 'XMPP4R Bot', 'bot')]
                                 )
      }

      def initialize(jid, password)
        cl = Jabber::Client.new(jid)
        cl.connect
        cl.auth(password)

        super(cl)

        roster.add_subscription_request_callback do |item,presence|
          if accept_subscription_from?(presence.from.strip)
            roster.accept_subscription(presence.from.strip)
          else
            roster.decline_subscription(presence.from.strip)
          end
        end

        @pep_notifications = []
        cl.add_message_callback do |msg|
          if msg.type != :error and msg.body
            if (html = msg.first_element('html')) and respond_to? :on_message_xhtml
              on_message_xhtml(html.body, msg.body)
            elsif respond_to? :on_message
              on_message(msg.body)
            end
          elsif msg.type != :error and (event = msg.first_element('event'))
            event.each_element('items') do |items|
              node = items.attributes['node']
              items.each_element('item') do |item|
                @pep_notifications.each { |notification_node,callback|
                  if node == notification_node
                    callback.call(msg.from, item)
                  end
                }
              end
            end
          else
            false
          end
        end

        add_cap('presence')
        add_cap(Caps::NS_CAPS)
        add_cap('message') if respond_to? :on_message
        add_cap(XHTML::NS_XHTML_IM) if respond_to? :on_message_xhtml

        @presence_show = nil
        @presence_status = nil
      end

      ##
      # Add feature namespace to Capabilities Discovery
      def add_cap(capability)
        disco_default.add_feature(capability)
        disco_caps.add_feature(capability)
      end

      ##
      # Front-end for Roster::Helper#add_subscription_request_callback
      #
      # Can be overwritten, must return true or false
      def accept_subscription_from?(jid)
        true
      end

      ##
      # Send a simple text chat message
      def send_message(to, text)
        msg = Message.new
        msg.type = :chat
        msg.to = to
        msg.body = text
        @stream.send(msg)
      end

      ##
      # Send an XHTML chat message
      # text:: [String] alternate plain text body, generated from xhtml_contents if nil
      def send_message_xhtml(to, xhtml_contents, text=nil)
        msg = Message.new
        msg.type = :chat
        msg.to = to
        html = msg.add(XHTML::HTML.new(xhtml_contents))
        msg.body = text ? text : html.to_text
        @stream.send(msg)
      end

      ##
      # Set and send a Presence
      def set_presence(show=nil, status=nil)
        @presence_show = show
        @presence_status = status
        send_presence
      end

      private

      def send_presence
        roster.wait_for_roster

        # TODO: vcard photo hash
        if @presence_show == :unavailable
          presence = Presence.new(nil, @presence_status)
          presence.type = :unavailable
        else
          presence = Presence.new(@presence_show, @presence_status)
        end
        presence.add(disco_caps.generate_caps)
        @stream.send(presence)
      end

      public

      def add_pep_notification(node, &callback)
        add_cap("#{node}+notify")
        @pep_notifications << [node, callback]
      end
    end

  end
end
