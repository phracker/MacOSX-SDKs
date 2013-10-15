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

require 'needle/errors'
require 'needle/service-point'

module Needle

  # This class is used by the Container#define! and Container#namespace!
  # methods to allow an +instance_eval+'d block to create new service points
  # simply by invoking imaginary methods. It is basically an empty shell, with
  # almost all of the builtin methods removed from it. (This allows services
  # like "hash" and "print" to be defined, where they would normally conflict
  # with the Kernel methods of the same name.)
  class DefinitionContext
    ( private_instance_methods +
      protected_instance_methods +
      public_instance_methods -
      [ "instance_eval", "object_id", "__id__", "__send__", "initialize",
        "remove_const", "method_missing", "method", "class", "inspect", "to_s",
        "instance_variables", "block_given?" ]
    ).
    each { |m| undef_method m }

    # Create a new DefinitionContext that wraps the given container. All
    # operations performed on this context will be delegated to the
    # container.
    def initialize( container )
      @container = container
    end

    # A way to access the container reference being operated on from within
    # the context.
    def this_container
      @container
    end

    # Delegate to Container#intercept.
    def intercept( name )
      @container.intercept( name )
    end

    # Delegate to Container#namespace.
    def namespace( *parms, &block )
      @container.namespace( *parms, &block )
    end

    # Delegate to Container#namespace_define!.
    def namespace_define!( *parms, &block )
      @container.namespace_define!( *parms, &block )
    end

    alias :namespace! :namespace_define!

    # Delegate to Container#define on the new namespace.
    def namespace_define( *parms, &block )
      @container.namespace( *parms ) { |ns| ns.define( &block ) }
    end

    # Delegate to Container#require on the current container.
    def require( *parms )
      # this is necessary to work around an rdoc bug...rdoc doesn't like
      # calling require with a variable number of arguments.
      @container.__send__( :require, *parms )
    end

    # Delegate to Container#use on the current container, but yields the
    # definition context instead of the container.
    def use( opts, &block )
      use! @container.defaults.merge( opts ), &block
    end

    # Delegate to Container#use! on the current container, but yields the
    # definition context instead of the container.
    def use!( opts )
      original = @container.use!( opts )

      if block_given?
        begin
          yield self
        ensure
          @container.use! original
        end
      end

      original
    end

    # Delegates to Container#has_key?.
    def has_key?( name )
      @container.has_key?( name )
    end

    # Delegates to Container#knows_key?.
    def knows_key?( name )
      @container.knows_key?( name )
    end

    # Any method invocation with no block and no parameters is interpreted to
    # be a service reference on the wrapped container, and delegates to
    # Container#[]. If the block is not given but the args are not empty, a
    # NoMethodError will be raised.
    #
    # If a block is given, this delegates to Container#register, leaving
    # all parameters in place.
    def method_missing( sym, *args, &block )
      if block.nil?
        @container.get( sym, *args )
      else
        @container.register( sym, *args, &block )
      end
    end

  end

end
