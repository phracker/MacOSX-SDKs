# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

module Jabber
  module Bytestreams
    ##
    # Implementation of IBB at the target side
    class IBBTarget < IBB
      # You may read the block-size after accept
      attr_reader :block_size

      def initialize(stream, session_id, initiator_jid, target_jid)
        # Target and Initiator are swapped here, because we're the target
        super(stream, session_id, target_jid, initiator_jid)
      end

      ##
      # Wait for the initiator side to start
      # the stream.
      def accept
        connect_sem = Semaphore.new

        @stream.add_iq_callback(200, self) { |iq|
          open = iq.first_element('open')
          if iq.type == :set and iq.from == @peer_jid and iq.to == @my_jid and open and open.attributes['sid'] == @session_id
            @stream.delete_iq_callback(self)
            activate
            @block_size = (open.attributes['block-size'] || 4096).to_i

            reply = iq.answer(false)
            reply.type = :result
            @stream.send(reply)

            connect_sem.run
            true
          else
            false
          end
        }

        connect_sem.wait
        true
      end
    end
  end
end
