# encoding: UTF-8

module LibXML
  module XML
    class Schema::Attribute
      REQUIRED = 1
      OPTIONAL = 2

      def default
        node['default']
      end

      def required?
        occurs == REQUIRED
      end

    end
  end
end
