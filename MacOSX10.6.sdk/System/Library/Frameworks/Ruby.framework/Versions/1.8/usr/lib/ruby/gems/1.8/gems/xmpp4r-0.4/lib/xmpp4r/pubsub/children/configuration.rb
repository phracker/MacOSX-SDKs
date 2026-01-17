# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/xmppelement'
require 'xmpp4r/pubsub/iq/pubsub'

module Jabber
  module PubSub

    class Configuration < XMPPElement
      ##
      # get the underlying XData form element
      def form
        children.each do |c|
          return c if c.kind_of?(Jabber::Dataforms::XData)
        end

        nil
      end

      def form=(form)
        children.each do |c|
          delete_element(c)
          if c.kind_of?(Jabber::Dataforms::XData)
            delete(c)
          end
        end
        add(form)
      end

      # Implemented by NodeConfig and SubscriptionConfig
      def form_type
        ''
      end

      def options=(options)
        if options
          self.form = form_for_options( form_type, options )
        end
      end

      ##
      # get a list of the configured options represented by this stanza
      # return:: [Hash] the options and their values
      def options
        configured_options = {}

        if !form.nil?
          form.fields.each do |f|
            f.values.size == 1 ? configured_options[f.var] = f.values.first : configured_options[f.var] = f.values
          end
        end

        configured_options
      end

      def node=(node)
        attributes['node'] = node
      end

      def node
        attributes['node']
      end

      private

      ##
      # creates a Dataform for configuration
      # config:: [Hash] the desired configuration options
      def form_for_options(type, options)
        form = Jabber::Dataforms::XData.new(:submit)
        pubsub_config = Jabber::Dataforms::XDataField.new('FORM_TYPE', :hidden)
        pubsub_config.values = [type]
        form.add(pubsub_config)
        options.each_pair do |key, value|
          f = Jabber::Dataforms::XDataField.new(key)
          f.values = [value]
          form.add(f)
        end

        form
      end
    end
  end
end
