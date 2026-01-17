# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/base64'

module Jabber
  module Bytestreams
    ##
    # In-Band Bytestreams (JEP-0047) implementation
    #
    # Don't use directly, use IBBInitiator and IBBTarget
    #
    # In-Band Bytestreams should only be used when transferring
    # very small amounts of binary data, because it is slow and
    # increases server load drastically.
    #
    # Note that the constructor takes a lot of arguments. In-Band
    # Bytestreams do not specify a way to initiate the stream,
    # this should be done via Stream Initiation.
    class IBB
      NS_IBB = 'http://jabber.org/protocol/ibb'

      ##
      # Create a new bytestream
      #
      # Will register a <message/> callback to intercept data
      # of this stream. This data will be buffered, you can retrieve
      # it with receive
      def initialize(stream, session_id, my_jid, peer_jid)
        @stream = stream
        @session_id = session_id
        @my_jid = (my_jid.kind_of?(String) ? JID.new(my_jid) : my_jid)
        @peer_jid = (peer_jid.kind_of?(String) ? JID.new(peer_jid) : peer_jid)

        @active = false
        @seq_send = 0
        @seq_recv = 0
        @queue = []
        @queue_lock = Mutex.new
        @pending = Semaphore.new
        @sendbuf = ''
        @sendbuf_lock = Mutex.new

        @block_size = 4096  # Recommended by JEP0047
      end

      def active?
        @active
      end

      ##
      # Send data
      #
      # Data is buffered to match block_size in each packet.
      # If you need the data to be sent immediately, use
      # flush afterwards.
      # buf:: [String]
      def write(buf)
        @sendbuf_lock.synchronize {
          @sendbuf += buf

          while @sendbuf.size >= @block_size
            send_data(@sendbuf[0..@block_size-1])
            @sendbuf = @sendbuf[@block_size..-1].to_s
          end
        }
      end

      ##
      # Empty the send-buffer by sending remaining data
      def flush
        @sendbuf_lock.synchronize {
          while @sendbuf.size > 0
            send_data(@sendbuf[0..@block_size-1])
            @sendbuf = @sendbuf[@block_size..-1].to_s
          end
        }
      end

      ##
      # Receive data
      #
      # Will wait until the Message with the next sequence number
      # is in the stanza queue.
      def read
        if active?
          res = nil

          while res.nil?
            @queue_lock.synchronize {
              @queue.each { |item|
                # Find next data
                if item.type == :data and item.seq == @seq_recv.to_s
                  res = item
                  break
                # No data? Find close
                elsif item.type == :close and res.nil?
                  res = item
                end
              }

              @queue.delete_if { |item| item == res }
            }

            # No data? Wait for next to arrive...
            @pending.wait unless res
          end

          if res.type == :data
            @seq_recv += 1
            @seq_recv = 0 if @seq_recv > 65535
            res.data
          elsif res.type == :close
            deactivate
            nil # Closed
          end
        else
          nil
        end
      end

      ##
      # Close the stream
      #
      # Waits for acknowledge from peer,
      # may throw ServerError
      def close
        if active?
          flush
          deactivate

          iq = Iq.new(:set, @peer_jid)
          close = iq.add REXML::Element.new('close')
          close.add_namespace IBB::NS_IBB
          close.attributes['sid'] = @session_id

          @stream.send_with_id(iq)
        end
      end

      private

      ##
      # Send data directly
      # data:: [String]
      def send_data(databuf)
        if active?
          msg = Message.new
          msg.from = @my_jid
          msg.to = @peer_jid

          data = msg.add REXML::Element.new('data')
          data.add_namespace NS_IBB
          data.attributes['sid'] = @session_id
          data.attributes['seq'] = @seq_send.to_s
          data.text = Base64::encode64(databuf)

          # TODO: Implement AMP correctly
          amp = msg.add REXML::Element.new('amp')
          amp.add_namespace 'http://jabber.org/protocol/amp'
          deliver_at = amp.add REXML::Element.new('rule')
          deliver_at.attributes['condition'] = 'deliver-at'
          deliver_at.attributes['value'] = 'stored'
          deliver_at.attributes['action'] = 'error'
          match_resource = amp.add REXML::Element.new('rule')
          match_resource.attributes['condition'] = 'match-resource'
          match_resource.attributes['value'] = 'exact'
          match_resource.attributes['action'] = 'error'

          @stream.send(msg)

          @seq_send += 1
          @seq_send = 0 if @seq_send > 65535
        else
          raise 'Attempt to send data when not activated'
        end
      end

      def activate
        unless active?
          @stream.add_message_callback(200, self) { |msg|
            data = msg.first_element('data')
            if msg.from == @peer_jid and msg.to == @my_jid and data and data.attributes['sid'] == @session_id
              if msg.type == nil
                @queue_lock.synchronize {
                  @queue.push IBBQueueItem.new(:data, data.attributes['seq'], data.text.to_s)
                  @pending.run
                }
              elsif msg.type == :error
                @queue_lock.synchronize {
                  @queue << IBBQueueItem.new(:close)
                  @pending.run
                }
              end
              true
            else
              false
            end
          }

          @stream.add_iq_callback(200, self) { |iq|
            close = iq.first_element('close')
            if iq.type == :set and close and close.attributes['sid'] == @session_id
              answer = iq.answer(false)
              answer.type = :result
              @stream.send(answer)

              @queue_lock.synchronize {
                @queue << IBBQueueItem.new(:close)
                @pending.run
              }
              true
            else
              false
            end
          }

          @active = true
        end
      end

      def deactivate
        if active?
          @stream.delete_message_callback(self)
          @stream.delete_iq_callback(self)

          @active = false
        end
      end
    end

    ##
    # Represents an item in the internal data queue
    class IBBQueueItem
      attr_reader :type, :seq
      def initialize(type, seq=nil, data_text='')
        unless [:data, :close].include? type
          raise "Unknown IBBQueueItem type: #{type}"
        end

        @type = type
        @seq = seq
        @data = data_text
      end

      ##
      # Return the Base64-*decoded* data
      #
      # There's no need to catch Exceptions here,
      # as none are thrown.
      def data
        Base64::decode64(@data)
      end
    end
  end
end
