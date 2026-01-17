# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r'
require 'xmpp4r/pubsub'
require 'xmpp4r/tune/tune'

module Jabber
  module UserTune
    ##
    # A Helper for XEP-0118 User Tune
    #
    # Use this helper to send user tunes, or receive them from a
    # specified jid. Described at http://www.xmpp.org/extensions/xep-0118.html
    #
    # For example:
    # <pre>
    # h = UserTune::Helper( @client, 'radio1@hug.hellomatty.com' )
    # h.add_usertune_callback do |tune|
    #   puts "Now playing: #{tune.title} by #{tune.artist}"
    # end
    # </pre>
    #
    # Also see the examples provided.
    class Helper < PubSub::ServiceHelper
      ##
      # Send out the tune currently playing.
      #
      # track:: [Jabber::UserTune::Tune] the tune currently playing
      def now_playing(track)
        item = Jabber::PubSub::Item.new()
        item.add(track)

        publish_item_to(NS_USERTUNE, item)
      end

      ##
      # Use this method to indicate that you have stopped playing
      # a tune.
      def stop_playing
        now_playing(Jabber::UserTune::Tune.new())
      end

      ##
      # Add a callback that will be invoked when a tune is received
      # from the jid specified when you constructed the Helper.
      def add_usertune_callback(prio = 200, ref = nil, &block)
        add_event_callback(prio, ref) do |event|
          tune = event.first_element('items/item/tune')
          if tune
            block.call(tune)
          end
        end
      end
    end
  end
end
