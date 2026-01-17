# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'rexml/document'
require 'rexml/parsers/xpathparser'
require 'rexml/source'

# Turn $VERBOSE off to suppress warnings about redefinition
oldverbose = $VERBOSE
$VERBOSE = false

# REXML : Adds custom helper methods to the REXML module.
#
module REXML

  # this class adds a few helper methods to REXML::Element
  class Element

    ##
    # Replaces or adds a child element of name <tt>e</tt> with text <tt>t</tt>.
    def replace_element_text(e, t)
      el = first_element(e)
      if el.nil?
        el = REXML::Element.new(e)
        add_element(el)
      end
      if t
        el.text = t
      end
      self
    end

    ##
    # Returns first element of name <tt>e</tt>
    def first_element(e)
      each_element(e) { |el| return el }
      return nil
    end

    ##
    # Returns text of first element of name <tt>e</tt>
    def first_element_text(e)
      el = first_element(e)
      if el
        return el.text
      else
        return nil
      end
    end

    # This method does exactly the same thing as add(), but it can be
    # overriden by subclasses to provide on-the-fly object creations.
    # For example, if you import a REXML::Element of name 'plop', and you
    # have a Plop class that subclasses REXML::Element, with typed_add you
    # can get your REXML::Element to be "magically" converted to Plop.
    def typed_add(e)
      add(e)
    end

    ##
    # import this element's children and attributes
    def import(xmlelement)
      if @name and @name != xmlelement.name
        raise "Trying to import an #{xmlelement.name} to a #{@name} !"
      end
      add_attributes(xmlelement.attributes.clone)
      @context = xmlelement.context
      xmlelement.each do |e|
        if e.kind_of? REXML::Element
          typed_add(e.deep_clone)
        elsif e.kind_of? REXML::Text
          add_text(e.value)
        else
          add(e.clone)
        end
      end
      self
    end

    def self.import(xmlelement)
      self.new(xmlelement.name).import(xmlelement)
    end

    ##
    # Deletes one or more children elements,
    # not just one like REXML::Element#delete_element
    def delete_elements(element)
      while(delete_element(element)) do end
    end

    ##
    # Test for equality of two elements, useful for assert_equal in
    # test cases. Tries to parse String o as XML.
    #
    # See Test::Unit::Assertions
    def ==(o)
      return false unless self.kind_of? REXML::Element
      if o.kind_of? REXML::Element
        # Ok
      elsif o.kind_of? String
        # Parse o
        begin
          o = REXML::Document.new(o).root
        rescue REXML::ParseException
          return false
        end
      else
        # Cannot compare with anything other than Elements or Strings
        return false
      end

      return false unless name == o.name

      attributes.each_attribute do |attr|
        return false unless attr.value == o.attributes[attr.name]
      end

      o.attributes.each_attribute do |attr|
        return false unless attributes[attr.name] == attr.value
      end

      children.each_with_index do |child,i|
        return false unless child == o.children[i]
      end

      return true
    end

  end # class Element

  # FIXME : Is this still needed now that we're a bit past Ruby 1.8.3??
  # Very dirty fix for the :progress problem in REXML from Ruby 1.8.3
  # http://www.germane-software.com/projects/rexml/ticket/34
  # the fix proposed in REXML changeset 1145 only fixes this for pipes, not for
  # TCP sockets, so we have to keep this.
  class IOSource
    def position
      0
    end

    def current_line
      [0, 0, ""]
    end
  end # class IOSource

end # module REXML

# Restore the old $VERBOSE setting
$VERBOSE = oldverbose

