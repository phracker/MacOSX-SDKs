# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/callbacks'
require 'xmpp4r/version/iq/version'

module Jabber
  module Version
    ##
    # A class to answer version requests using IqQueryVersion
    #
    # If you don't need the flexibility of dynamic responses with
    # the callback you can register with add_version_callback,
    # take a look at SimpleResponder
    class Responder
      ##
      # Initialize a new version responder
      #
      # Registers it's callback (prio = 180, ref = self)
      # stream:: [Stream] Where to register callback handlers
      def initialize(stream)
        @stream = stream
        @versioncbs = CallbackList.new

        stream.add_iq_callback(180, self) { |iq|
          iq_callback(iq)
        }
      end

      ##
      # Add a callback for Iq stanzas with IqQueryVersion
      #
      # First argument passed to block is the Iq stanza,
      # second argument is a block, which can be called with
      # software name, version and os
      #
      # Example:
      #   my_version_helper.add_version_callback { |iq,block|
      #     block.call('Cool client', '6.0', 'Cool OS')
      #   }
      def add_version_callback(priority = 0, ref = nil, &block)
        @versioncbs.add(priority, ref, block)
      end

      ##
      # <iq/> callback handler to answer Software Version queries
      # (registered by constructor and used internally only)
      #
      # Used internally
      def iq_callback(iq)
        if iq.type == :get
          if iq.query.kind_of?(IqQueryVersion)
            replyblock = lambda { |name,version,os|
              answer = iq.answer
              answer.type = :result
              answer.query.set_iname(name).set_version(version).set_os(os)

              @stream.send(answer)
              true
            }
            @versioncbs.process(iq, replyblock)
          else
            false
          end
        else
          false
        end
      end
    end
  end
end
