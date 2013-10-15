# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'rexml/parsers/sax2parser'
require 'rexml/source'
require 'xmpp4r/rexmladdons'

module Jabber

  ##
  # The StreamParser uses REXML to parse the incoming XML stream
  # of the Jabber protocol and fires XMPPStanza at the Connection
  # instance.
  #
  class StreamParser
    # status if the parser is started
    attr_reader :started

    ##
    # Constructs a parser for the supplied stream (socket input)
    #
    # stream:: [IO] Socket input stream
    # listener:: [Object.receive(XMPPStanza)] The listener (usually a Jabber::Protocol::Connection instance)
    #
    def initialize(stream, listener)
      @stream = stream
      @listener = listener
      @current = nil
    end

    ##
    # Begins parsing the XML stream and does not return until
    # the stream closes.
    #
    def parse
      @started = false
      begin
        parser = REXML::Parsers::SAX2Parser.new @stream

        parser.listen( :start_element ) do |uri, localname, qname, attributes|
          e = REXML::Element.new(qname)
          e.add_attributes attributes
          @current = @current.nil? ? e : @current.add_element(e)

          if @current.name == 'stream' and !@started
            @started = true
            @listener.receive(@current)
            @current = nil
          end
        end

        parser.listen( :end_element ) do  |uri, localname, qname|
          if qname == 'stream:stream' and @current.nil?
            @started = false
            @listener.parser_end
          else
            @listener.receive(@current) unless @current.parent
            @current = @current.parent
          end
        end

        parser.listen( :characters ) do | text |
          @current.add(REXML::Text.new(text.to_s, @current.whitespace, nil, true)) if @current
        end

        parser.listen( :cdata ) do | text |
          @current.add(REXML::CData.new(text)) if @current
        end

        parser.parse
      rescue REXML::ParseException => e
        @listener.parse_failure(e)
      end
    end
  end
end
