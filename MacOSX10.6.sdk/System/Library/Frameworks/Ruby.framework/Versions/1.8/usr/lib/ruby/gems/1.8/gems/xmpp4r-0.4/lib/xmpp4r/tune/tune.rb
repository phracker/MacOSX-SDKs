# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/xmppelement'
require 'rexml/element'

module Jabber
  module UserTune
    NS_USERTUNE = 'http://jabber.org/protocol/tune'

    ##
    # The <tune> XMPP element, as defined in XEP-0118 User Tune
    #
    # See http://www.xmpp.org/extensions/xep-0118.html - this element
    # encapsulates metadata (artist, track etc) about a tune the user
    # is currently playing. These are expressed as child elements
    # such as <artist>, <title> etc which are also managed by this class.
    #
    # If the element has no children then it indicates that the user
    # has stopped playing a tune. Use the Tune#playing? method to discover
    # this?
    class Tune < XMPPElement
      name_xmlns 'tune', NS_USERTUNE
      force_xmlns true

      ##
      # Construct a new <tune> element.
      #
      # Supply no arguments to make an
      # empty element to indicate that tune playing has stopped.
      #
      # artist:: [String] the artist or performer of the song or piece
      # title:: [String] the title of the song or piece
      # length:: [Fixnum] the duration of the song or piece in seconds
      # track:: [String] a unique identifier for the tune; e.g., the track number within a collection or the specific URI for the object (e.g., a stream or audio file)
      # source:: [String] the collection (e.g., album) or other source (e.g., a band website that hosts streams or audio files)
      # uri:: [String] a URI or URL pointing to information about the song, collection, or artist
      # rating:: [Numeric] a number indicating how much you like this song - will be clamped into an integer 0 <= x <= 10
      def initialize(artist = nil, title = nil, length = nil, track = nil, source = nil, uri = nil, rating = nil)
        super()

        add_element(REXML::Element.new('artist')).text = artist if artist

        add_element(REXML::Element.new('title')).text = title if title

        add_element(REXML::Element.new('length')).text = length.to_s if length

        add_element(REXML::Element.new('track')).text = track if track

        add_element(REXML::Element.new('source')).text = source if source

        add_element(REXML::Element.new('uri')).text = uri if uri

        if rating and rating.kind_of?(Numeric)
          r = rating.to_i
          r = 0 if r < 0
          r = 10 if r > 10
          add_element(REXML::Element.new('rating')).text = r.to_s
        end
      end


      ##
      # Returns true if a tune is currently playing, otherwise false.
      def playing?
        (elements.size > 0)
      end

      ##
      # Get the artist for this tune.
      def artist
        first_element('artist').text if first_element('artist')
      end

      ##
      # Get the title of this tune.
      def title
        first_element('title').text  if first_element('title')
      end

      ##
      # Get the length of this tune, in seconds.
      def length
        first_element('length').text.to_i if first_element('length')
      end

      ##
      # Get an identitier for this tune.
      def track
        first_element('track').text if first_element('track')
      end

      ##
      # Get the source of this tune, such as an album.
      def source
        first_element('source').text if first_element('source')
      end

      ##
      # Get a URI that represents this tune.
      def uri
        first_element('uri').text if first_element('uri')
      end

      ##
      # Get the rating for this track
      def rating
        first_element('rating').text.to_i if first_element('rating')
      end
    end
  end
end
