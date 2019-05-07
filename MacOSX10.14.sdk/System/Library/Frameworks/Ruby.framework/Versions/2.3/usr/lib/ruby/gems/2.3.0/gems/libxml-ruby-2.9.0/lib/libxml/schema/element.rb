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

      def annotation
        return if node.nil?
        annotations = node.children.select { |n| n.name == 'annotation' }
        annotations.map do |annotation|
          annotation.children.map(&:content).join("\n")
        end.join("\n")
      end
    end
  end
end
