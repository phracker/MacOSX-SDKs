module LibXML
  module XML
    class Node
      # Register the prefix (i.e., name) of the default namespace to
      # make xpath searches easier
      def register_default_namespace(prefix)
        ns = self.namespace.find do |ns|
          ns.prefix.nil?
        end

        if ns
          NS.new(self, ns.href, prefix)
        else
          raise(ArgumentError, "No default namespace was found")
        end
      end

      # Determines whether this node has attributes
      def attributes?
        attributes.length > 0
      end
      
      # Create a shallow copy of the node.  To create
      # a deep copy call Node#copy(true)
      def clone
        copy(false)
      end
      
      # Create a shallow copy of the node.  To create
      # a deep copy call Node#copy(true)
      def dup
        copy(false)
      end
    
      # Return nodes matching the specified xpath expression.
      # For more information, please refer to the documentation
      # for XML::Document#find.
      def find(xpath, nslist = nil)
        if not self.doc
          raise(TypeError, "A node must belong to a document before " +
                           "it can be searched with XPath.")
        end
      
        context = XPath::Context.new(self)
        context.node = self  
        context.register_namespaces_from_node(self)
        context.register_namespaces_from_node(self.doc.root)
        context.register_namespaces(nslist) if nslist

        context.find(xpath)
      end
    
      # Return the first node matching the specified xpath expression.
      # For more information, please refer to the documentation
      # for XML::Node#find.
      def find_first(xpath, nslist = nil)
        find(xpath, nslist).first
      end
    
      # -------  Traversal  ----------------
      # Iterates over this node's attributes.
      #
      #  doc = XML::Document.new('model/books.xml')
      #  doc.root.each_attr {|attr| puts attr}
      def each_attr
        attributes.each do |attr|
          yield(attr)
        end
      end
      
      # Iterates over this node's child elements (nodes
      # that have a node_type == ELEMENT_NODE).
      #
      #  doc = XML::Document.new('model/books.xml')
      #  doc.root.each_element {|element| puts element}
      def each_element
        each do |node|
          yield(node) if node.node_type == ELEMENT_NODE
        end
      end
      
      # Determines whether this node has a parent node
      def parent?
        not parent.nil?
      end
    
      # Determines whether this node has a first node
      def first?
        not first.nil?
      end
    
      # Returns this node's children as an array.
      def children
        entries
      end
    
      # Determines whether this node has a next node
      def next?
        not self.next.nil?
      end
    
      # Determines whether this node has a previous node
      def prev?
        not prev.nil?
      end
    
      # Determines whether this node has a last node
      def last?
        not last.nil?
      end


      # -------  Node Types  ----------------
      
      # Returns this node's type name    
      def node_type_name
        case node_type
          # Most common choices first
          when ATTRIBUTE_NODE
            'attribute'
          when DOCUMENT_NODE
            'document_xml'
          when ELEMENT_NODE
            'element'
          when TEXT_NODE
            'text'
          
          # Now the rest  
          when ATTRIBUTE_DECL
            'attribute_decl'
          when CDATA_SECTION_NODE
            'cdata'
          when COMMENT_NODE
            'comment'
          when DOCB_DOCUMENT_NODE
            'document_docbook'
          when DOCUMENT_FRAG_NODE
            'fragment'
          when DOCUMENT_TYPE_NODE
            'doctype'
          when DTD_NODE
            'dtd'
          when ELEMENT_DECL
            'elem_decl'
          when ENTITY_DECL
            'entity_decl'
          when ENTITY_NODE
            'entity'
          when ENTITY_REF_NODE
            'entity_ref'
          when HTML_DOCUMENT_NODE
            'document_html'
          when NAMESPACE_DECL
            'namespace'
          when NOTATION_NODE
            'notation'
          when PI_NODE
            'pi'
          when XINCLUDE_START
            'xinclude_start'
          when XINCLUDE_END
            'xinclude_end'
          else
            raise(UnknownType, "Unknown node type: %n", node.node_type);
        end
      end
      
      # Specifies if this is an attribute node
      def attribute?
        node_type == ATTRIBUTE_NODE
      end
      
      # Specifies if this is an attribute declaration node
      def attribute_decl?
        node_type == ATTRIBUTE_DECL
      end

      # Specifies if this is an CDATA node
      def cdata?
        node_type == CDATA_SECTION_NODE
      end

      # Specifies if this is an comment node
      def comment?
        node_type == COMMENT_NODE
      end

      # Specifies if this is an docbook node
      def docbook_doc?
        node_type == DOCB_DOCUMENT_NODE
      end

      # Specifies if this is an docbook node
      def doctype?
        node_type == DOCUMENT_TYPE_NODE
      end

      # Specifies if this is an DOCTYPE node
      def document?
        node_type == DOCUMENT_NODE
      end

      # Specifies if this is an DTD node
      def dtd?
        node_type == DTD_NODE
      end

      # Specifies if this is an element node
      def element?
        node_type == ELEMENT_NODE
      end

      # Specifies if this is an entity node
      def entity?
        node_type == ENTITY_NODE
      end

      # Specifies if this is an element declaration node
      def element_decl?
        node_type == ELEMENT_DECL
      end

      # Specifies if this is an entity reference node
      def entity_ref?
        node_type == ENTITY_REF_NODE
      end

      # Specifies if this is a fragment node
      def fragment?
        node_type == DOCUMENT_FRAG_NODE
      end

      # Specifies if this is a html document node
      def html_doc?
        node_type == HTML_DOCUMENT_NODE
      end

      # Specifies if this is a namespace node (not if it
      # has a namepsace)
      def namespace?
        node_type == NAMESPACE_DECL
      end

      # Specifies if this is a notation node
      def notation?
        node_type == NOTATION_NODE
      end

      # Specifies if this is a processiong instruction node
      def pi?
        node_type == PI_NODE
      end

      # Specifies if this is a text node
      def text?
        node_type == TEXT_NODE
      end
      
      # Specifies if this is an xinclude end node
      def xinclude_end?
        node_type == XINCLUDE_END
      end
      
      # Specifies if this is an xinclude start node
      def xinclude_start?
        node_type == XINCLUDE_START
      end

      alias :child? :first?  
      alias :children? :first?  
      alias :child :first
      alias :each_child :each
    end
  end
end
