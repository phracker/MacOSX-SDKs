# encoding: UTF-8

module LibXML
  module XML
    class SaxParser
      # call-seq:
      #    XML::SaxParser.file(path) -> XML::SaxParser
      #
      # Creates a new parser by parsing the specified file or uri.
      def self.file(path)
        context = XML::Parser::Context.file(path)
        self.new(context)
      end

      # call-seq:
      #    XML::SaxParser.io(io) -> XML::SaxParser
      #    XML::SaxParser.io(io, :encoding => XML::Encoding::UTF_8) -> XML::SaxParser
      #
      # Creates a new reader by parsing the specified io object.
      #
      # Parameters:
      #
      #  encoding - The document encoding, defaults to nil. Valid values
      #             are the encoding constants defined on XML::Encoding.
      def self.io(io, options = {})
        context = XML::Parser::Context.io(io)
        context.encoding = options[:encoding] if options[:encoding]
        self.new(context)
      end

      # call-seq:
      #    XML::SaxParser.string(string)
      #
      # Creates a new parser by parsing the specified string.
      def self.string(string)
        context = XML::Parser::Context.string(string)
        self.new(context)
      end
    end
  end
end