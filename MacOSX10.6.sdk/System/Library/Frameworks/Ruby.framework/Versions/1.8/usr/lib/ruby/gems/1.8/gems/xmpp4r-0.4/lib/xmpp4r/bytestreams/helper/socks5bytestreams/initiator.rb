# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

module Jabber
  module Bytestreams
    ##
    # SOCKS5Bytestreams implementation for the initiator side
    class SOCKS5BytestreamsInitiator < SOCKS5Bytestreams
      attr_reader :streamhosts

      def initialize(stream, session_id, initiator_jid, target_jid)
        super
        @streamhosts = []
      end

      ##
      # Add a streamhost which will be offered to the target
      #
      # streamhost:: can be:
      # * [StreamHost] if already got all information (host/port)
      # * [SOCKS5BytestreamsServer] if this is the local streamhost
      # * [String] or [JID] if information should be automatically resolved by SOCKS5Bytestreams::query_streamhost
      def add_streamhost(streamhost)
        if streamhost.kind_of?(StreamHost)
          @streamhosts << streamhost
        elsif streamhost.kind_of?(SOCKS5BytestreamsServer)
          streamhost.each_streamhost(@initiator_jid) { |sh|
            @streamhosts << sh
          }
        elsif streamhost.kind_of?(String) or streamhost.kind_of?(JID)
          @streamhosts << SOCKS5Bytestreams::query_streamhost(@stream, streamhost, @initiator_jid)
        else
          raise "Unknwon streamhost type: #{streamhost.class}"
        end
      end

      ##
      # Send the configured streamhosts to the target,
      # wait for an answer and
      # connect to the host the target chose.
      def open
        iq1 = Iq.new(:set, @target_jid)
        iq1.from = @initiator_jid
        bs = iq1.add IqQueryBytestreams.new(@session_id)
        @streamhosts.each { |se|
          bs.add(se)
        }

        peer_used = nil
        @stream.send_with_id(iq1) { |response|
          if response.query.kind_of?(IqQueryBytestreams)
            peer_used = response.query.streamhost_used
            raise "No streamhost-used" unless peer_used
            raise "Invalid streamhost-used" unless peer_used.jid
          end
        }

        @streamhost_used = nil
        @streamhosts.each { |sh|
          if peer_used.jid == sh.jid
            @streamhost_used = sh
            break
          end
        }
        if @streamhost_used.jid == @initiator_jid
          # This is our own JID, so the target chose SOCKS5BytestreamsServer
          @socks = @streamhost_used.server.peer_sock(stream_address)
          raise "Target didn't connect" unless @socks
          @streamhost_cbs.process(@streamhost_used, :success, nil)
        else
          begin
            @socks = connect_socks(@streamhost_used)
          rescue Exception => e
            Jabber::debuglog("SOCKS5 Bytestreams: #{e.class}: #{e}\n#{e.backtrace.join("\n")}")
            @streamhost_cbs.process(@streamhost_used, :failure, e)
            raise e
          end
          iq2 = Iq.new(:set, @streamhost_used.jid)
          iq2.add(IqQueryBytestreams.new(@session_id)).activate = @target_jid.to_s
          @stream.send_with_id(iq2)
        end
      end
    end
  end
end
