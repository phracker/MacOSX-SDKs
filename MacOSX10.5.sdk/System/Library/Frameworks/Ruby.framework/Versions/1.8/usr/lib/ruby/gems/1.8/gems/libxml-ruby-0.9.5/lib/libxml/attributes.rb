# $Id: libxml.rb 374 2008-07-11 04:51:41Z cfis $ 
# Please see the LICENSE file for copyright and distribution information 

module LibXML
  module XML
    class Attributes
      def to_h
        inject({}) do |hash, attr|
          hash[attr.name] = attr.value
          hash
        end
      end
    end
  end
end