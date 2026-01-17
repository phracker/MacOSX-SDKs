module LibXML
  module XML
    class Reader
      def reset_error_handler
        warn('reset_error_handler is deprecated.  Use Error.reset_handler instead')
        Error.reset_handler
      end

      def set_error_handler(&block)
        warn('set_error_handler is deprecated.  Use Error.set_handler instead')
        Error.set_handler(&block)
      end
    end
  end
end