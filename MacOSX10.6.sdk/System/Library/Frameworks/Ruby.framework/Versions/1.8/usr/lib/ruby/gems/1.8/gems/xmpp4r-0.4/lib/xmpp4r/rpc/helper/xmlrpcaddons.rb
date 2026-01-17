require "xmlrpc/parser"
require "xmlrpc/create"
require "xmlrpc/config"
require "xmlrpc/utils"     # ParserWriterChooseMixin


module XMLRPC
  class Create

    # Avoids warnings
    remove_method(:methodCall)
    remove_method(:methodResponse)

    ##
    # create a Method Call
    # name:: [String] name of the method
    # params:: [Array] params of the method as a array
    def methodCall(name, *params)
      name = name.to_s

      if name !~ /[a-zA-Z0-9_.:\/]+/
        raise ArgumentError, "Wrong XML-RPC method-name"
      end

      parameter = params.collect { |param|
        @writer.ele("param", conv2value(param))
      }

      tree = @writer.document(
               @writer.ele("methodCall",
                 @writer.tag("methodName", name),
                 @writer.ele("params", *parameter)
               )
             )

      @writer.document_to_str(tree) + "\n"
    end
    ##
    # create a response to a method call
    # is_ret:: [TrueClass] is this a return (true)  or a error (false)
    # params:: [Array] a array of params

    def methodResponse(is_ret, *params)

      if is_ret
        begin
          resp = params.collect do |param|
            @writer.ele("param", conv2value(param))
          end

          resp = [@writer.ele("params", *resp)]
        rescue Exception => e
          error = XMLRPC::FaultException.new(XMLRPC::BasicServer::ERR_UNCAUGHT_EXCEPTION, "Uncaught exception '#{e.message}' serialising params into response")
          resp = @writer.ele("fault", conv2value(error.to_h))
        end
      else
        if params.size != 1 or params[0] === XMLRPC::FaultException
          raise ArgumentError, "no valid fault-structure given"
        end
        resp = @writer.ele("fault", conv2value(params[0].to_h))
      end

      tree = @writer.document(@writer.ele("methodResponse", resp))
      @writer.document_to_str(tree) + "\n"
    end
  end
end
