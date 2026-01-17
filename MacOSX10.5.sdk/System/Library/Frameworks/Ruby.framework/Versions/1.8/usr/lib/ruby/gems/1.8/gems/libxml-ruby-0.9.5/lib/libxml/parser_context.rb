# $Id: libxml.rb 374 2008-07-11 04:51:41Z cfis $

module LibXML
  module XML
    class Parser
      class Context
        def options
          warn("ParserContext#options has been removed from the bindings")
        end

        def options=(value)
          warn("ParserContext#options has been removed from the bindings")
        end
      end
    end
  end
end