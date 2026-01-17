# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/rexmladdons'

module Jabber

  ##
  # This class represents an XML element and provides functionality
  # for automatic casting of XML element classes according to their
  # element name and namespace.
  #
  # Deriving classes must met these criteria:
  # * The element name and namespace must be specified by calling
  #   the name_xmlns class method
  # * The class constructor must be callable with no mandatory parameter
  class XMPPElement < REXML::Element
    @@name_xmlns_classes = {}
    @@force_xmlns = false

    ##
    # Specify XML element name and xmlns for a deriving class,
    # this pair and the class will be added to a global pool
    #
    # If the namespace is nil the class is a "wildcard class"
    # matching elements with any xmlns if no other class with
    # that namespace was defined
    def self.name_xmlns(name, xmlns=nil)
      @@name_xmlns_classes[[name, xmlns]] = self
    end

    ##
    # Set whether this element is always built with an xmlns attribute
    def self.force_xmlns(force)
      @@force_xmlns = force
    end

    ##
    # Whether this element is always built with an xmlns attribute
    def self.force_xmlns?
      @@force_xmlns
    end

    ##
    # Find the name and namespace for a given class.
    # This class must have registered these two values
    # by calling name_xmlns at definition time.
    #
    # Raises an exception if none was found
    # klass:: [Class]
    # result:: [String, String] name and namespace
    def self.name_xmlns_for_class(klass)
      klass.ancestors.each do |klass1|
        @@name_xmlns_classes.each do |name_xmlns,k|
          if klass1 == k
            return name_xmlns
          end
        end
      end

      raise NoNameXmlnsRegistered.new(klass)
    end

    ##
    # Find a class for given name and namespace
    # name:: [String]
    # xmlns:: [String]
    # result:: A descendant of XMPPElement or REXML::Element
    def self.class_for_name_xmlns(name, xmlns)
      if @@name_xmlns_classes.has_key? [name, xmlns]
        @@name_xmlns_classes[[name, xmlns]]
      elsif @@name_xmlns_classes.has_key? [name, nil]
        @@name_xmlns_classes[[name, nil]]
      else
        REXML::Element
      end
    end

    ##
    # Import another REXML::Element descendant to:
    # * Either an element class that registered with
    #   name and xmlns before
    # * Or if none was found to the class itself
    #   (you may call this class method on a deriving class)
    def self.import(element)
      klass = class_for_name_xmlns(element.name, element.namespace)
      if klass != self and klass.ancestors.include?(self)
        klass.new.import(element)
      else
        self.new.import(element)
      end
    end

    ##
    # Initialize this element, which will then be initialized
    # with the name registered with name_xmlns.
    def initialize(*arg)
      if arg.empty?
        name, xmlns = self.class::name_xmlns_for_class(self.class)
        super(name)
        if self.class::force_xmlns?
          add_namespace(xmlns)
        end
      else
        super
      end
    end

    ##
    # Add a child element which will be imported according to the
    # child's name and xmlns
    # element:: [REXML::Element] Child
    # result:: [REXML::Element or descendant of XMPPElement] New child
    def typed_add(element)
      if element.kind_of? REXML::Element
        element_ns = (element.namespace.to_s == '') ? namespace : element.namespace

        klass = XMPPElement::class_for_name_xmlns(element.name, element_ns)
        if klass != element.class
          element = klass.import(element)
        end
      end

      super(element)
    end

    def parent=(new_parent)
      if parent and parent.namespace('') == namespace('') and attributes['xmlns'].nil?
        add_namespace parent.namespace('')
      end

      super

      if new_parent and new_parent.namespace('') == namespace('')
        delete_namespace
      end
    end

    def clone
      cloned = self.class.new
      cloned.add_attributes self.attributes.clone
      cloned.context = @context
      cloned
    end

    ##
    # Generic XML attribute 'xml:lang'
    # (REXML provides no shortcut)
    def xml_lang
      attributes['xml:lang']
    end

    ##
    # Set XML language attribute
    def xml_lang=(l)
      attributes['xml:lang'] = l
    end

    ##
    # Set XML language attribute (chainable)
    def set_xml_lang(l)
      self.xml_lang = l
      self
    end

  end
end
