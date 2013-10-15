require 'xmpp4r/xmppelement'

module Jabber
  module XHTML
    NS_XHTML_IM = 'http://jabber.org/protocol/xhtml-im'
    NS_XHTML = 'http://www.w3.org/1999/xhtml'

    ##
    # XHTML-IM (XEP-0071) container
    #
    # The important methods are:
    # * HTML#contents=
    # * HTML#to_text
    class HTML < XMPPElement
      name_xmlns 'html', NS_XHTML_IM
      force_xmlns true

      ##
      # Initialize element with HTML contents (see HTML#contents=)
      def initialize(contents=[])
        super()
        self.contents = contents
      end

      ##
      # Get first XHTML::Body child
      def body
        first_element('body') || add(Body.new)
      end

      ##
      # Replace first XHTML::Body child
      def body=(body)
        delete_elements('body')
        add(body)
      end

      ##
      # Replace first XHTML::Body child (chainable)
      def set_body(body)
        self.body = body
        self
      end

      ##
      # Set contents of this HTML document. The "contents" parameter can be:
      # * An Array of REXML::Element and Strings which will replace the current children of the body
      # * A single REXML::Element which will replace all other children of the body
      # * An instance of XHTML::Body which will replace the current body
      # * A String comprising an HTML fragment. This will be parsed, which could raise an Exception.
      #   We must never send invalid XML over an XMPP stream. If you intend to put variable data in
      #   your HTML, use something like Rails' Builder::XmlMarkup or Ramaze::Gestalt
      def contents=(contents)
        if contents.kind_of? String
          self.body = REXML::Document.new("<body xmlns='#{NS_XHTML}'>#{contents}</body>").root
        elsif contents.kind_of? Body
          self.body = contents
        elsif contents.kind_of? Array
          self.body = Body.new
          contents.each do |element|
            if element.kind_of? String
              body.add_text(element)
            else
              body.add(element)
            end
          end
        else
          self.body = Body.new
          body.add(contents)
        end
      end

      ##
      # HTML#contents= chainable
      def set_contents(contents)
        self.contents = contents
        self
      end

      ##
      # Convert contents of this XHTML container to plain text
      # for easy usage with an additional fall-back <body/> in message stanzas
      #
      # The resulting string is recursively composed of the text nodes of
      # all children.
      # This works because of the design criteria of HTML/XHTML:
      # readable content is not being put into attributes but as text children.
      #
      # If you require clickable links and proper information representation
      # then compose the text yourself!
      def to_text
        text_getter = nil # Create binding so that the following lambda can work recursively

        text_getter = lambda do |element|
          if element.kind_of? REXML::Text
            element.value
          elsif element.kind_of? REXML::Element
            element.children.collect { |child|
              text_getter.call(child)
            }.join
          end
        end

        text_getter.call(self) # Finally, execute and return results
      end
    end

    ##
    # HTML Body element, must be the only child of XHTML::HTML
    class Body < XMPPElement
      name_xmlns 'body', NS_XHTML
      force_xmlns true
    end
  end
end
