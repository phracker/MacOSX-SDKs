module LibXML
  module XML
    class Schema::Type
      def kind_name
        Schema::Types.constants.find { |k| Schema::Types.const_get(k) == kind }
      end

      def annotation
        return if node.nil?
        annotations = node.children.select { |n| n.name == 'annotation' }
        annotations.map do |annotation|
          annotation.children.map(&:content).join("\n")
        end.join("\n")
      end

      def annonymus_subtypes
        elements.select { |_, e| e.type.name.nil? }
      end

      def annonymus_subtypes_recursively(parent=nil)
        annonymus_subtypes.map do |element_name, e|
          [{[parent, element_name].compact.join('::') => e.type},
           e.type.annonymus_subtypes_recursively(element_name)]
        end.flatten
      end

    end
  end
end
