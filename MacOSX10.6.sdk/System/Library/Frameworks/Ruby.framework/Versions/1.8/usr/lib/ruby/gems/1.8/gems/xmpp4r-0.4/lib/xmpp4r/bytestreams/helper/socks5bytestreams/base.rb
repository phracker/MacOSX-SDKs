# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'socket'
require 'thread'
require 'timeout'
require 'digest/sha1'

require 'xmpp4r/callbacks'

module Jabber
  module Bytestreams
    ##
    # SOCKS5 Bytestreams (JEP-0065) implementation
    #
    # Don't use directly, use SOCKS5BytestreamsInitiator
    # and SOCKS5BytestreamsTarget
    class SOCKS5Bytestreams
      ##
      # [StreamHost] the SOCKS connection is using
      attr_reader :streamhost_used

      ##
      # SOCKS connection timeout (for trying multiple streamhosts)
      #
      # default: nil, use the OS' default timeout
      attr_accessor :connect_timeout

      def initialize(stream, session_id, initiator_jid, target_jid)
        @stream = stream
        @session_id = session_id
        @initiator_jid = (initiator_jid.kind_of?(String) ? JID.new(initiator_jid) : initiator_jid)
        @target_jid = (target_jid.kind_of?(String) ? JID.new(target_jid) : target_jid)
        @socks = nil
        @connect_timeout = nil
        @streamhost_used = nil
        @streamhost_cbs = CallbackList.new
      end

      ##
      # Add a callback that will be called when there is action regarding
      # SOCKS stream-hosts
      #
      # Usage of this callback is optional and serves informational purposes only.
      #
      # block takes three arguments:
      # * The StreamHost instance that is currently being tried
      # * State information (is either :connecting, :authenticating, :success or :failure)
      # * The exception value for the state :failure, else nil
      def add_streamhost_callback(priority = 0, ref = nil, &block)
        @streamhost_cbs.add(priority, ref, block)
      end

      ##
      # Receive from the stream-host
      # length:: [Fixnum] Amount of bytes (Will be passed to TCPSocket#read for the underlying SOCKS5 connection)
      # result:: [String] (or [nil] if finished)
      def read(length=nil)
        @socks.read(length)
      end

      ##
      # Flush the SOCKS5 socket
      def flush
        @socks.flush
      end

      ##
      # Send to the stream-host
      # buf:: [String] Data
      # result:: [Fixnum] Amount of bytes sent
      def write(buf)
        @socks.write(buf)
        # FIXME: On FreeBSD this throws Errno::EPERM after it has already written a few
        # kilobytes, and when there are multiple sockets. ktrace told, that this originates
        # from the syscall, not ruby.
      end

      ##
      # Close the stream-host connection
      def close
        @socks.close
      end

      ##
      # Query a JID for its stream-host information
      #
      # SOCKS5BytestreamsInitiator#add_streamhost can do this for you.
      # Use this method if you plan to do multiple transfers, so
      # you can cache the result.
      # stream:: [Stream] to operate on
      # streamhost:: [JID] of the proxy
      # my_jid:: [JID] Optional sender JID for Component operation
      def self.query_streamhost(stream, streamhost, my_jid=nil)
        res = nil

        iq = Iq.new(:get, streamhost)
        iq.from = my_jid
        iq.add(IqQueryBytestreams.new)
        stream.send_with_id(iq) { |reply|
          reply.query.each_element { |e|
            if e.kind_of?(StreamHost)
              e.jid = reply.from  # Help misconfigured proxys
              res = e
            end
          }
        }

        if res and res.jid and res.host and res.port
          res
        else
          nil
        end
      end

      private

      ##
      # The address the stream-host expects from us.
      # According to JEP-0096 this is the SHA1 hash
      # of the concatenation of session_id,
      # initiator_jid and target_jid.
      # result:: [String] SHA1 hash
      def stream_address
        Digest::SHA1.hexdigest("#{@session_id}#{@initiator_jid}#{@target_jid}")
      end

      ##
      # Try a streamhost
      # result:: [SOCKS5Socket]
      def connect_socks(streamhost)
        Timeout::timeout(@connect_timeout, Errno::ETIMEDOUT) {
          Jabber::debuglog("SOCKS5 Bytestreams: connecting to proxy #{streamhost.jid} (#{streamhost.host}:#{streamhost.port})")
          @streamhost_cbs.process(streamhost, :connecting, nil)
          socks = SOCKS5Socket.new(streamhost.host, streamhost.port)

          Jabber::debuglog("SOCKS5 Bytestreams: connected, authenticating")
          @streamhost_cbs.process(streamhost, :authenticating, nil)
          socks.auth

          socks.connect_domain(stream_address, 0)

          Jabber::debuglog("SOCKS5 Bytestreams: connected")
          @streamhost_cbs.process(streamhost, :success, nil)

          socks
        }
      end
    end
  end
end
