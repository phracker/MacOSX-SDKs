# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/iq'
require 'xmpp4r/base64'

module Jabber
  module Vcard
    ##
    # vCard container for User Information
    # (can be specified by users themselves, mostly kept on servers)
    # (JEP 0054)
    class IqVcard < XMPPElement
      name_xmlns 'vCard', 'vcard-temp'
      force_xmlns true

      ##
      # Initialize a <vCard/> element
      # fields:: [Hash] Initialize with keys as XPath element names and values for element texts
      def initialize(fields=nil)
        super()

        unless fields.nil?
          fields.each { |name,value|
            self[name] = value
          }
        end
      end

      ##
      # Get an elements/fields text
      #
      # vCards have too much possible children, so ask for them here
      # and extract the result with iqvcard.element('...').text
      # name:: [String] XPath
      def [](name)
        text = nil
        each_element(name) { |child| text = child.text }
        text
      end

      ##
      # Set an elements/fields text
      # name:: [String] XPath
      # text:: [String] Value
      def []=(name, text)
        xe = self
        name.split(/\//).each do |elementname|
          # Does the children already exist?
          newxe = nil
          xe.each_element(elementname) { |child| newxe = child }

          if newxe.nil?
            # Create a new
            xe = xe.add_element(elementname)
          else
            # Or take existing
            xe = newxe
          end
        end
        xe.text = text
      end

      ##
      # Get vCard field names
      #
      # Example:
      #  ["NICKNAME", "BDAY", "ORG/ORGUNIT", "PHOTO/TYPE", "PHOTO/BINVAL"]
      #
      # result:: [Array] of [String]
      def fields
        element_names(self).uniq
      end

      ##
      # Get the PHOTO/BINVAL (Avatar picture) field decoded from Base64
      # result:: [String] or [nil]
      def photo_binval
        if (binval = self['PHOTO/BINVAL'])
          Base64::decode64(binval)
        else
          nil
        end
      end

      private

      ##
      # Recursive helper function,
      # returns all element names in an array, concatenated
      # to their parent's name with a slash
      def element_names(xe, prefix='')  # :nodoc:
        res = []
        xe.each_element { |child|
          if child.kind_of?(REXML::Element)
            children = element_names(child, "#{prefix}#{child.name}/")
            if children == []
              res.push("#{prefix}#{child.name}")
            else
              res += children
            end
          end
        }
        res
      end
    end
  end
end
