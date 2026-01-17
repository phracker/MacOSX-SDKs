# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

module Jabber
  module Bytestreams
    ##
    # Implementation of IBB at the initiator side
    class IBBInitiator < IBB
      # You may set the block-size before open
      attr_accessor :block_size

      ##
      # Open the stream to the peer,
      # waits for successful result
      #
      # May throw ServerError
      def open
        iq = Iq.new(:set, @peer_jid)
        open = iq.add REXML::Element.new('open')
        open.add_namespace IBB::NS_IBB
        open.attributes['sid'] = @session_id
        open.attributes['block-size'] = @block_size.to_s

        @stream.send_with_id(iq)

        activate
      end
    end
  end
end
