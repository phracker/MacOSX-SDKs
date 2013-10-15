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

module Needle

  # This represents the definition of an interceptor as it is attached to a
  # service point. Instances of Interceptor are also used for configuring
  # themselves programmatically.
  #
  # You will almost never instantiate an Interceptor object directly. Instead,
  # use the Container#intercept method. You can then configure the new
  # interceptor by chaining methods of the new object together, quite
  # readably:
  #
  #   container.intercept( :foo ).with! { some_interceptor }.
  #     with_options( :arg => :value )
  #
  # You can also create new interceptors on the fly via the Interceptor#doing
  # method.
  class Interceptor

    # This is the wrapper for on-the-fly interceptors that have been created
    # via Interceptor#doing. The callback registered with Interceptor#doing
    # gets wrapped by an instance of this class, to comply with the interface
    # required by InterceptorChainBuilder.
    #
    # This class should rarely (if ever) be instantiated directly. Instead,
    # using the Interceptor#doing method to create dynamic interceptors.
    class DynamicInterceptor

      # Create a new DynamicInterceptor instance that wraps the given
      # callback.
      def initialize( callback )
        @callback = callback
      end

      # This method is a concession to the required interceptor factory
      # interface. It should return the new interceptor, configured to be
      # attached to the given service point, and with the given options.
      # It will always return +self+.
      def new( point, opts )
        @point = point
        @options = opts
        self
      end

      # Process this link in the interceptor chain. This will invoke the
      # wrapped callback, passing in the chain and context parameters.
      # Before invoking the callback, the options and service point
      # references that were given in #new are assigned to context
      # data members (so they can be referenced inside the callback).
      def process( chain, context )
        context.data[:options] = @options
        context.data[:point] = @point
        @callback.call( chain, context )
      end

    end

    # The set of options that were given to this interceptor via the
    # #with_options method.
    attr_reader :options

    # Create a new Interceptor definition. By default, it has no
    # implementation and a priority of 0.
    def initialize
      @options = { :priority => 0 }
      @doing = @with = nil
    end

    # Returns the action that was specified for this interceptor as a proc
    # instance. This will either be the block passed to #with, or a proc
    # that wraps the instantiation of a DynamicInterceptor (when #doing
    # was used).
    #
    # If neither #with nor #doing were specified, an
    # InterceptorConfigurationError is raised.
    def action
      return @with if @with
      raise InterceptorConfigurationError,
        "You must specify either 'with' or 'doing'" unless @doing

      return proc { |c| DynamicInterceptor.new( @doing ) }
    end

    # Sets the action for this interceptor to be that defined by the
    # interceptor returned when the block is executed. You can only
    # invoke #with once, and never after previously invoking #doing on the
    # same interceptor instance.
    #
    # Usage:
    #
    #   container.intercept( :foo ).
    #     with { |c| c.logging_interceptor }
    def with( &block )
      if @with
        raise InterceptorConfigurationError,
          "you cannot redefine 'with' behavior"
      end

      if @doing
        raise InterceptorConfigurationError,
          "cannot specify 'with' after specifying 'doing'"
      end

      if block.nil?
        raise InterceptorConfigurationError,
          "you must specify a block to 'with'"
      end

      @with = block
      self
    end

    # This is identical to #with, but it wraps the block in another proc that
    # calls +instance_eval+ on the container, with the block.
    #
    # Usage:
    #
    #   container.intercept( :foo ).
    #     with! { logging_interceptor }
    def with!( &block )
      with { |c| c.instance_eval( &block ) }
    end

    # This allows new interceptors to be defined "on-the-fly". The associated
    # block must accept two parameters--an object representing the chain of
    # interceptors, and the context of the current method invocation. The block
    # should then invoke #process_next on the chain (passing the context as
    # the lone parameter) when the next element of the chain should be invoked.
    #
    # You should only call #doing once per interceptor, and never after
    # invoking #with on the same interceptor.
    def doing( &block )
      if @doing
        raise InterceptorConfigurationError,
          "you cannot redefine 'doing' behavior"
      end

      if @with
        raise InterceptorConfigurationError,
          "cannot specify 'doing' after specifying 'with'"
      end

      if block.nil?
        raise InterceptorConfigurationError,
          "you must specify a block to 'doing'"
      end

      @doing = block
      self
    end

    # Merge the given +opts+ hash into the interceptors options hash.
    def with_options( opts={} )
      @options.update opts
      self
    end

    # A convenience method for querying the options on an interceptor
    # definition.
    def []( name )
      @options[ name ]
    end

    # A convenience method for setting the options on an interceptor
    # definition.
    def []=( name, value )
      @options[ name ] = value
    end

  end

end
