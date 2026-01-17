# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/


require 'xmpp4r/client'
require 'net/http'

module Jabber
  module HTTPBinding
    ##
    # This class implements an alternative Client
    # using HTTP Binding (JEP0124).
    #
    # This class is designed to be a drop-in replacement
    # for Jabber::Client, except for the
    # Jabber::HTTP::Client#connect method which takes an URI
    # as argument.
    #
    # HTTP requests are buffered to not exceed the negotiated
    # 'polling' and 'requests' parameters.
    #
    # Stanzas in HTTP resonses may be delayed to arrive in the
    # order defined by 'rid' parameters.
    #
    # =Debugging
    # Turning Jabber::debug to true will make debug output
    # not only spit out stanzas but HTTP request/response
    # bodies, too.
    class Client < Jabber::Client

      # Content-Type to be used for communication
      # (you can set this to "text/html")
      attr_accessor :http_content_type
      # The server should wait this value seconds if
      # there is no stanza to be received
      attr_accessor :http_wait
      # The server may hold this amount of stanzas
      # to reduce number of HTTP requests
      attr_accessor :http_hold

      ##
      # Initialize
      # jid:: [JID or String]
      def initialize(jid)
        super

        @lock = Mutex.new
        @pending_requests = 0
        @last_send = Time.at(0)
        @send_buffer = ''

        @http_wait = 20
        @http_hold = 1
        @http_content_type = 'text/xml; charset=utf-8'
      end

      ##
      # Set up the stream using uri as the HTTP Binding URI
      #
      # You may optionally pass host and port parameters
      # to make use of the JEP0124 'route' feature.
      #
      # uri:: [URI::Generic or String]
      # host:: [String] Optional host to route to
      # port:: [Fixnum] Port for route feature
      def connect(uri, host=nil, port=5222)
        uri = URI::parse(uri) unless uri.kind_of? URI::Generic
        @uri = uri

        @allow_tls = false  # Shall be done at HTTP level
        @stream_mechanisms = []
        @stream_features = {}
        @http_rid = IdGenerator.generate_id.to_i
        @pending_rid = @http_rid
        @pending_rid_lock = Mutex.new

        req_body = REXML::Element.new('body')
        req_body.attributes['rid'] = @http_rid
        req_body.attributes['content'] = @http_content_type
        req_body.attributes['hold'] = @http_hold.to_s
        req_body.attributes['wait'] = @http_wait.to_s
        req_body.attributes['to'] = @jid.domain
        if host
          req_body.attributes['route'] = 'xmpp:#{host}:#{port}'
        end
        req_body.attributes['secure'] = 'true'
        req_body.attributes['xmlns'] = 'http://jabber.org/protocol/httpbind'
        res_body = post(req_body)
        unless res_body.name == 'body'
          raise 'Response body is no <body/> element'
        end

        @streamid = res_body.attributes['authid']
        @status = CONNECTED
        @http_sid = res_body.attributes['sid']
        @http_wait = res_body.attributes['wait'].to_i if res_body.attributes['wait']
        @http_hold = res_body.attributes['hold'].to_i if res_body.attributes['hold']
        @http_inactivity = res_body.attributes['inactivity'].to_i
        @http_polling = res_body.attributes['polling'].to_i
        @http_polling = 5 if @http_polling == 0
        @http_requests = res_body.attributes['requests'].to_i
        @http_requests = 1 if @http_requests == 0

        receive_elements_with_rid(@http_rid, res_body.children)

        @features_sem.run
      end

      ##
      # Send a stanza, additionally with block
      #
      # This method ensures a 'jabber:client' namespace for
      # the stanza
      def send(xml, &block)
        if xml.kind_of? REXML::Element
          xml.add_namespace('jabber:client')
        end

        super
      end

      ##
      # Ensure that there is one pending request
      #
      # Will be automatically called if you've sent
      # a stanza.
      def ensure_one_pending_request
        return if is_disconnected?

        if @lock.synchronize { @pending_requests } < 1
          send_data('')
        end
      end

      ##
      # Close the session by sending
      # <presence type='unavailable'/>
      def close
        @status = DISCONNECTED
        send(Jabber::Presence.new.set_type(:unavailable))
      end

      private

      ##
      # Receive stanzas ensuring that the 'rid' order is kept
      # result:: [REXML::Element]
      def receive_elements_with_rid(rid, elements)
        while rid > @pending_rid
          @pending_rid_lock.lock
        end
        @pending_rid = rid + 1

        elements.each { |e|
          receive(e)
        }

        @pending_rid_lock.unlock
      end

      ##
      # Do a POST request
      def post(body)
        body = body.to_s
        request = Net::HTTP::Post.new(@uri.path)
        request.content_length = body.size
        request.body = body
        request['Content-Type'] = @http_content_type
        Jabber::debuglog("HTTP REQUEST (#{@pending_requests}/#{@http_requests}):\n#{request.body}")
        response = Net::HTTP.start(@uri.host, @uri.port) { |http|
          http.use_ssl = true if @uri.kind_of? URI::HTTPS
          http.request(request)
        }
        Jabber::debuglog("HTTP RESPONSE (#{@pending_requests}/#{@http_requests}):\n#{response.body}")

        unless response.kind_of? Net::HTTPSuccess
          # Unfortunately, HTTPResponses aren't exceptions
          # TODO: rescue'ing code should be able to distinguish
          raise Net::HTTPBadResponse, "#{response.class}"
        end

        body = REXML::Document.new(response.body).root
        if body.name != 'body' and body.namespace != 'http://jabber.org/protocol/httpbind'
          raise REXML::ParseException.new('Malformed body')
        end
        body
      end

      ##
      # Prepare data to POST and
      # handle the result
      def post_data(data)
        req_body = nil
        current_rid = nil

        begin
          begin
            @lock.synchronize {
              # Do not send unneeded requests
              if data.size < 1 and @pending_requests > 0
                return
              end

              req_body = "<body"
              req_body += " rid='#{@http_rid += 1}'"
              req_body += " sid='#{@http_sid}'"
              req_body += " xmlns='http://jabber.org/protocol/httpbind'"
              req_body += ">"
              req_body += data
              req_body += "</body>"
              current_rid = @http_rid

              @pending_requests += 1
              @last_send = Time.now
            }

            res_body = post(req_body)

          ensure
            @lock.synchronize { @pending_requests -= 1 }
          end

          receive_elements_with_rid(current_rid, res_body.children)
          ensure_one_pending_request

        rescue REXML::ParseException
          if @exception_block
            Thread.new do
              Thread.current.abort_on_exception = true
              close; @exception_block.call(e, self, :parser)
            end
          else
            Jabber::debuglog "Exception caught when parsing HTTP response!"
            close
            raise
          end

        rescue StandardError => e
          Jabber::debuglog("POST error (will retry): #{e.class}: #{e}")
          receive_elements_with_rid(current_rid, [])
          # It's not good to resend on *any* exception,
          # but there are too many cases (Timeout, 404, 502)
          # where resending is appropriate
          # TODO: recognize these conditions and act appropriate
          send_data(data)
        end
      end

      ##
      # Send data,
      # buffered and obeying 'polling' and 'requests' limits
      def send_data(data)
        @lock.synchronize do

          @send_buffer += data
          limited_by_polling = (@last_send + @http_polling >= Time.now)
          limited_by_requests = (@pending_requests + 1 > @http_requests)

          # Can we send?
          if !limited_by_polling and !limited_by_requests
            data = @send_buffer
            @send_buffer = ''

            Thread.new do
              Thread.current.abort_on_exception = true
              post_data(data)
            end

          elsif !limited_by_requests
            Thread.new do
              Thread.current.abort_on_exception = true
              # Defer until @http_polling has expired
              wait = @last_send + @http_polling - Time.now
              sleep(wait) if wait > 0
              # Ignore locking, it's already threaded ;-)
              send_data('')
            end
          end

        end
      end
    end
  end
end
