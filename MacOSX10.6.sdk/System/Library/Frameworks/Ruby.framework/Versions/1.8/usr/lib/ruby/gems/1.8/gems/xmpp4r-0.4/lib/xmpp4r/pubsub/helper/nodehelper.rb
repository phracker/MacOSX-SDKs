# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/
#
# For documentation of the return values please see [Jabber::PubSub::ServiceHelper]
# This class is only a wrapper around [Jabber::PubSub::ServiceHelper]
#


require 'xmpp4r/pubsub/helper/servicehelper'
require 'xmpp4r/pubsub/helper/nodebrowser'

module Jabber
  module PubSub
    class NodeHelper < ServiceHelper

      attr_reader :nodename
      attr_reader :name
      attr_reader :jid
      attr_reader :my_subscriptions
      ##
      # creates a new node
      # new(client,service,nodename)
      # stream:: [Jabber::Stream]
      # jid:: [String] (jid of the pubsub service)
      # nodename:: [String]
      def initialize(stream, jid, nodename = nil, create_if_not_exist = true)
        super(stream,jid)
        @nodename = nodename
        @jid = jid
        @stream = stream

        if create_if_not_exist and not node_exist?
          # if no nodename is given a instant node will created
          # (if the service supports instant nodes)
          @nodename = create_node
        else
          get_subscriptions
        end
      end

      ##
      # creates the node
      # create(configuration=nil)
      # configuration:: [Jabber::XData]
      def create_node(configuration = Jabber::PubSub::NodeConfig.new)
        unless node_exist?
          super(@nodename,configuration)
        else
          false
        end
      end

      ##
      # get the configuration of the node
      # get_configuration(configuration=nil)
      # configuration:: [Jabber::XData]
      def get_configuration(subid = nil)
        get_options(@nodename, subid)
      end

      ##
      # set the configuration of the node
      # set_configuration(configuration=nil)
      # configuration:: [Jabber::XData]
      # subid:: [String] default is nil
      def set_configuration(configuration,subid = nil)
        set_options(@nodename, configuration, subid)
      end

      ##
      # deletes the node
      # delete
      def delete_node
        delete(@nodename)
      end

      ##
      # publishing content on this node
      # publish_content(items)
      # items:: [REXML::Element]
      def publish_content(items)
        publish_item_to(@nodename,items)
      end

      ##
      # gets all items from the node
      # get_all_items
      def get_all_items
        items(@nodename)
      end

      ##
      # get a count of items
      # get_items(count)
      # count:: [Fixnum]
      def get_items(count)
        items(@nodename,count)
      end

      ##
      # get all node affiliations
      # get_affiliations
      def get_affiliations
        affiliations
      end

      ##
      # get all subscriptions on this node
      # get_subscriptions
      def get_subscriptions
        get_subscriptions_from(@nodename)
      end

      ##
      # get all subscribers subscribed on this node
      # get_subscribers
      def get_subscribers
        @subscriptions = subscribers(@nodename)
      end

      ##
      # subscribe to this node
      # do_subscribe
      def do_subscribe
        subscribe_to(@nodename)
        get_subscriptions
      end

      ##
      # unsubscribe from this node
      # do_unsubscribe(subid = nil)
      # subid:: [String]
      def do_unsubscribe(subid)
        unsubscribe(@nodename,subid)
      end

      ##
      # purge all items from this node
      # purge_items
      def purge_items
        purge(@nodename)
      end

    private

      def node_exist?
        nodebrowser = PubSub::NodeBrowser.new(@stream)
        nodebrowser.nodes(@jid).include?(@nodename)
      end
      def disco_info
      end

    end #class
  end #module
end #module