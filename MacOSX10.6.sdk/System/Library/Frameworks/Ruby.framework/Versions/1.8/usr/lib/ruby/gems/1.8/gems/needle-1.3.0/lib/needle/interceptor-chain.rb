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

  # This module encapsulates the functionality for building interceptor chains.
  module InterceptorChainBuilder

    # The context of a method invocation.  This is used in an interceptor chain
    # to encapsulate the elements of the current invocation.
    # sym:   the name of the method being invoked
    # args:  the argument list being passed to the method
    # block: the reference to the block attached to the method invocation
    # data:  a hash that may be used by clients for storing arbitrary data in
    #        the context.
    InvocationContext = Struct.new( :sym, :args, :block, :data )

    # A single element in an interceptor chain.  Each interceptor object is
    # wrapped in an instance of one of these.  Calling #process_next on a given
    # chain element, invokes the #process method on the corresponding
    # interceptor, with the next element in the chain being passed in.
    class InterceptorChainElement

      # Create a new InterceptorChainElement that wraps the given interceptor.
      def initialize( interceptor )
        @interceptor = interceptor
      end

      # Set the next element in the interceptor chain to the given object.  This
      # must be either an InterceptorChainElement instance of a
      # ProxyObjectChainElement instance.
      def next=( next_obj )
        @next_obj = next_obj
      end

      # Invokes the #process method of the interceptor encapsulated by this
      # object, with the _next_ element in the chain being passed to it.
      def process_next( context )
        if @next_obj.nil?
          raise Bug,
            "[BUG] interceptor chain should always terminate with proxy"
        end
        @interceptor.process( @next_obj, context )
      end

    end

    # Encapsulates the end of an interceptor chain, which is the actual object
    # being affected.
    class ProxyObjectChainElement

      # Create a new ProxyObjectChainElement that wraps the given object.
      def initialize( obj )
        @obj = obj
      end

      # Invoke the method represented by the context on the wrapped object.
      def process_next( context )
        @obj.__send__( context.sym, *context.args, &context.block )
      end

    end

    # This is just a trivial proxy class that is used to wrap a service
    # before the interceptors are applied to it. This additional level of
    # abstraction prevents the need for mangling the names of the service's
    # methods, and also offers those applications that need it the ability
    # to invoke methods of the service without going through the interceptors.
    #
    # The proxy will be decorated with dynamically appended methods by the
    # InterceptorChainBuilder#build method.
    class InterceptedServiceProxy

      # Create a new InterceptedServiceProxy that wraps the given interceptor
      # chain.
      def initialize( chain )
        @chain = chain
      end

    end

    # This will apply the given interceptors to the given service by first
    # ordering the interceptors based on their relative priorities,
    # and then dynamically modifying the service's methods so that the chain
    # of interceptors sits in front of each of them.
    #
    # The modified service is returned.
    def build( point, service, interceptors )
      return service if interceptors.nil? || interceptors.empty?

      ordered_list =
        interceptors.sort { |a,b|
          a.options[:priority] <=> b.options[:priority] }

      chain = ProxyObjectChainElement.new( service )

      ordered_list.reverse.each do |interceptor|
        factory = interceptor.action.call( point.container )
        instance = factory.new( point, interceptor.options )
        element = InterceptorChainElement.new( instance )
        element.next = chain
        chain = element
      end

      # FIXME: should inherited methods of "Object" be interceptable?
      methods_to_intercept = ( service.class.instance_methods( true ) -
                               Object.instance_methods +
                               service.class.instance_methods( false ) ).uniq

      service = InterceptedServiceProxy.new( chain )
      singleton = class << service; self; end

      methods_to_intercept.each do |method|
        next if method =~ /^__/

        if singleton.instance_methods(false).include? method
          singleton.send( :remove_method, method )
        end

        singleton.class_eval <<-EOF
          def #{method}( *args, &block )
            context = InvocationContext.new( :#{method}, args, block, Hash.new )
            @chain.process_next( context )
          end
        EOF
      end

      # allow the interceptor to intercept methods not explicitly
      # declared on the reciever.
      if singleton.instance_methods(false).include? "method_missing"
        singleton.send( :remove_method, :method_missing )
      end

      singleton.class_eval <<-EOF
        def method_missing( sym, *args, &block )
          context = InvocationContext.new( sym, args, block, Hash.new )
          @chain.process_next( context )
        end
      EOF

      return service
    end
    module_function :build

  end

end
