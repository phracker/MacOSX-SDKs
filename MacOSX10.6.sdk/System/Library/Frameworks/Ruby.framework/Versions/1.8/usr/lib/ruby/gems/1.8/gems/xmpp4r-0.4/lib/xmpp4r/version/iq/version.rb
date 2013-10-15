# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/query'

module Jabber
  module Version
    ##
    # Class for handling queries for 'Software Version'
    # (JEP 0092)
    #
    # Notice that according to JEP 0092 only the <os/> element can be omitted,
    # <name/> (iname) and <version/> must be present
    class IqQueryVersion < IqQuery
      name_xmlns 'query', 'jabber:iq:version'

      ##
      # Create a new <query xmlns='jabber:iq:version'/> element
      def initialize(iname=nil, version=nil, os=nil)
        super()
        set_iname(iname) if iname
        set_version(version) if version
        set_os(os) if os
      end

      ##
      # Get the name of the software
      #
      # This has been renamed to 'iname' here to keep
      # REXML::Element#name accessible
      def iname
        first_element_text('name')
      end

      ##
      # Set the name of the software
      #
      # The element won't be deleted if text is nil as
      # it must occur in a version query, but its text will
      # be empty.
      def iname=(text)
        replace_element_text('name', text.nil? ? '' : text)
      end

      ##
      # Set the name of the software (chaining-friendly)
      # result:: [String] or nil
      def set_iname(text)
        self.iname = text
        self
      end

      ##
      # Get the version of the software
      # result:: [String] or nil
      def version
        first_element_text('version')
      end

      ##
      # Set the version of the software
      #
      # The element won't be deleted if text is nil as
      # it must occur in a version query
      def version=(text)
        replace_element_text('version', text.nil? ? '' : text)
      end

      ##
      # Set the version of the software (chaining-friendly)
      # text:: [String]
      def set_version(text)
        self.version = text
        self
      end

      ##
      # Get the operating system or nil
      # (os is not mandatory for Version Query)
      def os
        first_element_text('os')
      end

      ##
      # Set the os of the software
      # text:: [String] or nil
      def os=(text)
        if text
          replace_element_text('os', text)
        else
          delete_elements('os')
        end
      end

      ##
      # Set the os of the software (chaining-friendly)
      # text:: [String] or nil
      def set_os(text)
        self.os = text
        self
      end
    end
  end
end
