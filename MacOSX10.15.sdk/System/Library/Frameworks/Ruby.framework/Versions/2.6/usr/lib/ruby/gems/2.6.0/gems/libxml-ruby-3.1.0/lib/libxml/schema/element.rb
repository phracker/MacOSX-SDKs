# encoding: UTF-8

module LibXML
  module XML
    class Schema::Element
      def required?
        !min_occurs.zero?
      end

      def array?
        max_occurs > 1
      end

      def elements
        type.elements
      end
    end
  end
end
