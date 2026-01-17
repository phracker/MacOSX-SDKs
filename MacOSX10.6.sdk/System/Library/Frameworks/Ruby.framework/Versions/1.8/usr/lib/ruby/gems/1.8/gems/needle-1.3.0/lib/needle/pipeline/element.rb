#--
# =============================================================================
# Copyright (c) 2004, Jamis Buck (jamis@37signals.com)
# All rights reserved.
#
# This source file is distributed as part of the Needle dependency injection
# library for Ruby. This file (and the library as a whole) may be used only as
# allowed by either the BSD license, or the Ruby license (or, by association
# with the Ruby license, the GPL). See the "doc" subdirectory of the Needle
# distribution for the texts of these licenses.
# -----------------------------------------------------------------------------
# needle website : http://needle.rubyforge.org
# project website: http://rubyforge.org/projects/needle
# =============================================================================
#++

module Needle
  module Pipeline

    # The base class of instantiation pipeline elements. All subclasses
    # MUST implement is the #call method, to define the logic that instances of
    # that pipeline element should perform when invoked.
    class Element
      include Comparable

      # The service definition that this element belongs to.
      attr_reader :service_point
      
      # The name of this element (may be +nil+).
      attr_reader :name
      
      # The priority of this element, used to determine ordering. Higher ordered
      # elements are invoked before lower-ordered elements.
      attr_reader :priority

      # The hash of options that were given to this element.
      attr_reader :options

      # The next element in the chain. This value is only valid during pipeline
      # execution--its value should not be relied upon at any other time.
      attr_accessor :succ

      class << self
        # The default priority to use for elements of this type.
        attr_reader :default_priority

        # Set the default priority for elements of this type. Subclasses may
        # use this method to set their default priority.
        def set_default_priority( priority )
          @default_priority = priority
        end
      end

      set_default_priority 0

      # Create a new element instance with the given name and priority. This
      # will call #initialize_element, so that subclasses only need to
      # implement that method if they have any initialization logic to perform.
      def initialize( point, name=nil, priority=nil, options={} )
        @service_point = point
        @name, @priority = name, ( priority || self.class.default_priority )
        @options = options
        initialize_element
      end

      # Invoked by the constructor to perform any subclass-specific
      # initialization logic.
      def initialize_element
      end

      # Orders elements by their priority.
      def <=>( element )
        priority <=> element.priority
      end

      # Invoke this element's logic.
      def call( *args )
        raise NotImplementedError
      end

      # Invoked by Pipeline::Collection#reset!. Subclasses of Element that
      # save any kind of state should override this method to clear that
      # state on demand.
      def reset!
      end

      alias :[] :call
    end

  end
end
