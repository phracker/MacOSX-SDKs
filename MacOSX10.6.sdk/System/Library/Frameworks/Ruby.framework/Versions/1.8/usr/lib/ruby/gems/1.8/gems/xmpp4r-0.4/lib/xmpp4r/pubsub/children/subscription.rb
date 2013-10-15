# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/iq'

module Jabber
  module PubSub
    ##
    # Subscription
    class Subscription < XMPPElement
      name_xmlns 'subscription', NS_PUBSUB
      def initialize(myjid=nil,mynode=nil,mysubid=nil,mysubscription=nil)
        super()
        jid = myjid
        node =  mynode
        subid =  mysubid
        state = mysubscription
      end
      def jid
        (a = attribute('jid')).nil? ? a : JID.new(a.value)
      end
      def jid=(myjid)
        add_attribute('jid', myjid ? myjid.to_s : nil)
      end

      def node
        attributes['node']
      end
      def node=(mynode)
        attributes['node'] = mynode
      end

      def subid
        attributes['subid']
      end
      def subid=(mysubid)
        attributes['subid'] = mysubid
      end

      def state
          # each child of event
          # this should interate only one time
          case attributes['subscription']
              when 'none'      		then return :none
              when 'pending'   		then return :pending
              when 'subscribed'         then return :subscribed
              when 'unconfigured'       then return :unconfigured
              else return nil
          end
      end
      def state=(mystate)
        attributes['subscription'] = mystate
      end
      alias subscription state

      def need_approval?
        state == :pending
      end
    end
  end
end
