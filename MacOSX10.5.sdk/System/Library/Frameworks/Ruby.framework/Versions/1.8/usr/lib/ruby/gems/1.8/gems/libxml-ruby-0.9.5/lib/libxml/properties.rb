# $Id: libxml.rb 374 2008-07-11 04:51:41Z cfis $ 
# Please see the LICENSE file for copyright and distribution information 


# This is for backwards compatibility and is DEPRECATED
module LibXML
  module XML
    class Node
      def property(name)
        warn('Node#properties is deprecated.  Use Node#[] instead.')
        self[name]
      end

      def properties
        warn('Node#properties is deprecated.  Use Node#attributes instead.')
        self.attributes
      end

      def properties?
        warn('Node#properties? is deprecated.  Use Node#attributes? instead.')
        self.attributes?
      end
    end

  end
end