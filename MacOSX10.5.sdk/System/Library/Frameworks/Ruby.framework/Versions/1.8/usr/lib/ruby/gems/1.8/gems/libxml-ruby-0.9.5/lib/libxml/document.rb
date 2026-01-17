module LibXML
  module XML
    class Document
      def self.file(value)
        Parser.file(value).parse
      end

      def self.string(value)
        Parser.string(value).parse
      end

      def self.document(value)
        Parser.document(value).parse
      end

      def self.io(value)
        Parser.io(value).parse
      end

      # Return the nodes matching the specified xpath expression, 
      # optionally using the specified namespace.  For more 
      # information about working with namespaces, please refer
      # to the XML::XPath documentation.
      # 
      # Parameters:
      # * xpath - The xpath expression as a string
      # * namespaces - An optional list of namespaces (see XML::XPath for information).
      # * Returns - XML::XPath::Object
      #
      #  document.find('/foo', 'xlink:http://www.w3.org/1999/xlink')
      #
      # IMPORTANT - The returned XML::Node::Set must be freed before
      # its associated document.  In a running Ruby program this will
      # happen automatically via Ruby's mark and sweep garbage collector.
      # However, if the program exits, Ruby does not guarantee the order
      # in which objects are freed
      # (see http://blade.nagaokaut.ac.jp/cgi-bin/scat.rb/ruby/ruby-core/17700).
      # As a result, the associated document may be freed before the node
      # list, which will cause a segmentation fault.
      # To avoid this, use the following (non-ruby like) coding style:
      #
      #  nodes = doc.find('/header')
      #  nodes.each do |node|
      #    ... do stuff ...
      #  end
      #
      #  nodes = nil
      #  GC.start
      def find(xpath, nslist = nil)
        context = XPath::Context.new(self)
        context.node = self.root  
        context.register_namespaces_from_node(self.root)
        context.register_namespaces(nslist) if nslist

        context.find(xpath)
      end
    
      # Return the first node matching the specified xpath expression.
      # For more information, please refer to the documentation
      # for XML::Document#find.
      def find_first(xpath, nslist = nil)
        find(xpath, nslist).first
      end
    end
  end
end  