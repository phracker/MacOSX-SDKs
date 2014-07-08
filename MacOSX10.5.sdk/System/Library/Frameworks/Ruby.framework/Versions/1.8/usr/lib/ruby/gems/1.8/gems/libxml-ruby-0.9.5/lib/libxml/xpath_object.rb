module LibXML
  module XML
    module XPath
      class Object
        def set
          warn("XPath::Object#set is deprecated.  Simply use the XPath::Object API instead")
          self
        end
      end
    end
  end
end