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

require 'needle/pipeline/element'

module Needle
  module Pipeline

    # Represents a collection of pipeline elements. Elements may be added to
    # the pipeline, and then returned as a single object representing the chain
    # of pipeline elements.
    class Collection

      # Wraps a block as a new pipeline element. When the element is invoked,
      # control is delegated to the block.
      class BlockElement < Element
        
        set_default_priority 0

        # Create a new pipeline element around the given block.
        def initialize( point, name, priority, options, block )
          super( point, name, priority, options )
          @block = block
        end

        # Invoke the block. The block must accept as many parameters as the
        # pipeline expects, plus 1 (the first parameter is always this
        # BlockElement instance).
        def call( *args )
          @block.call( self, *args )
        end

      end

      # Create a new pipeline element collection, initially empty.
      def initialize( service_point )
        @elements = []
        @service_point = service_point
      end

      # Add a new pipeline element to this collection. If the first parameter
      # is a symbol or a string, it is taken to be the name of the element to
      # add. If no explicit implementation is given, then the implementation is
      # looked up in the <tt>:pipeline_elements</tt> service, using the given
      # name.
      #
      # After the first parameter, if the next parameter is numeric, it is taken
      # to mean the priority of the element. This overrides whatever default
      # priority is given for the selected element.
      #
      # If the next parameter responds to the <tt>:new</tt> message, it is taken
      # to be an explicit implementation of the element. This is only valid if
      # a block is not given. If a block is given, then it is always taken to be
      # the implementation of the element.
      #
      # If the last parameter is a Hash, it is taken to be a map of options that
      # should be passed to the element when it is instantiated.
      #
      # This returns +self+, so that #add calls may be chained.
      def add( *args, &block )
        name = priority = nil
        options = {}
        klass = nil
        element = nil

        if [ Symbol, String ].any? { |i| args.first.is_a?( i ) }
          name = args.shift.to_s.intern
        end
        priority = args.shift if args.first.is_a?( Numeric )
        klass = args.shift if args.first.respond_to?( :new ) && block.nil?
        options = args.shift if args.first.is_a?( Hash )

        raise ArgumentError,
          "bad argument list #{args.inspect}" unless args.empty?

        if block
          element = BlockElement.new( @service_point, name, priority,
            options, block )
        else
          klass ||= @service_point.container[:pipeline_elements].fetch( name )
          element = klass.new( @service_point, name, priority, options )
        end

        @elements << element
        self
      end

      # Returns the first pipeline element with the given name, or +nil+ if no
      # such element exists.
      def get( name )
        name = name.to_s.intern
        @elements.find { |el| name == el.name }
      end

      # Clears the state for each named element. If no elements are named, all
      # elements are cleared.
      def reset!( *args )
        @elements.each do |element|
          element.reset! if args.empty? || args.include?( element.name )
        end
        self
      end

      # Builds a linked list of the elements, with the last element being the
      # block (or block-like) object given by the parameter. Higher-priority
      # elements will be closer to the head of the list.
      def chain_to( block )
        head = tail = nil
        @elements.sort.reverse.each do |el|
          if head
            tail.succ = el
            tail = el
          else # first time through...
            head = tail = el
          end
        end

        if tail
          tail.succ = block
          return head
        else
          return block
        end
      end

    end

  end
end
