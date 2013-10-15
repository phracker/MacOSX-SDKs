require 'xmlrpc/server'
require 'xmlrpc/parser'
require 'xmlrpc/create'
require 'xmlrpc/config'
require 'xmlrpc/utils'         # ParserWriterChooseMixin

require 'xmpp4r/dataforms/x/data'
require 'xmpp4r/rpc/iq/rpc'
require 'xmpp4r/rpc/helper/xmlrpcaddons'

module Jabber
  module RPC

    ##
    # XMLRPC Server
    class Server < XMLRPC::BasicServer

      include XMLRPC::ParserWriterChooseMixin
      include XMLRPC::ParseContentType

      ##
      # new - creates a new server
      #
      def initialize(stream,class_delim=".")
        super(class_delim)
        @stream = stream
        @stream.add_iq_callback(120,"Helpers::RPCServer") { |iq|
          if iq.type == :set and iq.type != :result
            handle_iq(iq)
            true
          else
            false
          end
        }
      end

      ##
      # handles incoming iqs
      # iq:: [Jabber::IQ] - the jabber iq
      def handle_iq(iq)
        if iq.type == :set
          if iq.query.kind_of?(IqQueryRPC)
            data = iq.query
            response = IqQueryRPC.new
            data.elements.each { |rpc|
              if rpc
                response.typed_add(handle_rpc_requests(rpc))
              end
            }

            respiq = iq.answer(false)
            respiq.type = :result
            respiq.add(response)
            @stream.send(respiq)
          end
        end
      end

      private

      ##
      # handles the rpc requests
      # takes rpcdata:: [String]
      def handle_rpc_requests(rpcdata)
        resp = process(rpcdata.to_s)
        if resp == nil or resp.size <= 0
          raise Jabber::ErrorResponse.new(:forbidden)
        else
          return resp
        end
      end
    end # RPCServer
  end  # Helpers
end   # Jabber
