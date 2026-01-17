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
    # XMLRPC Client
    class Client

      include XMLRPC::ParserWriterChooseMixin
      include XMLRPC::ParseContentType

      attr_accessor :my_jid

      ##
      # xmppstream
      # stream:: [Stream]
      # jid where you want to send the rpc requests to
      # jid:: [JID] rpcserver@jabberserver/ressource
      def initialize(stream,jid)
        @jid    = JID.new(jid)
        @my_jid = stream.jid
        @stream =  stream
        @parser = nil
        @create = XMLRPC::Create.new
      end

      ##
      # automatically trys to find a method
      # thanx to eric cestari  :)
      def method_missing(methodname, *args)
        send("call", methodname,*args)
      end


      def call(method, *args)
        ok, param = call2(method, *args)
        if ok
          param
        else
          raise param
        end
      end

      def call2(method, *args)
        request = @create.methodCall(method, *args)
        data = do_rpc(request)
        parser().parseMethodResponse(data)
      end

      ##
      # adds multi rpcalls to the query
      # methods:: [Array]
      def multicall(*methods)
        ok, params = multicall2(*methods)
        if ok
          params
        else
          raise params
        end
      end

      ##
      # generate a multicall
      # methods:: [Array]
      def multicall2(*methods)
        gen_multicall(methods)
      end

      def do_rpc(xmlrpc)
        iq = Iq.new(:set, @jid)
        iq.from = @my_jid
        iq.id = IdGenerator::generate_id
        rpcquery = iq.add(IqQueryRPC.new)
        rpcquery.typed_add(xmlrpc)

        result = nil
        @stream.send_with_id(iq) do |iqreply|
          if iqreply.query.kind_of?(IqQueryRPC)
            result = iqreply.query.to_s
          end
        end

        result
      end

      private

      def gen_multicall(methods=[])
        ok, params = call2("system.multicall",
          methods.collect { |m|
            {
              'methodName' => m[0],
              'params' => m[1..-1]
            }
          }
        )

        if ok
          params = params.collect{ |param|
            if param.is_a? Array
              param[0]
            elsif param.is_a? Hash
              XMLRPC::FaultException.new(param["faultCode"], param["faultString"])
            else
              raise "Wrong multicall return value"
            end
          }
        end

        return ok, params
      end
    end
  end  # Helpers
end   # Jabber
