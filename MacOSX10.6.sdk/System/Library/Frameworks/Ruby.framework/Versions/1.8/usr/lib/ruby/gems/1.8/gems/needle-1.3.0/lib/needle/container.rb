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

  # The container is the heart of Needle's model. Every Container instance is
  # a miniature registry, and is really a namespace separate from every other
  # Container instance. Service lookups inside of a container always look in
  # +self+ first, and if not found, they then look in their parent container,
  # recursively.
  #
  # You will rarely need to instantiate a Container directly. Instead, use the
  # Container#namespace method to create new containers.
  class Container

    # The container that contains this container. This will be +nil+ for
    # the root of a hierarchy (see Registry).
    attr_reader :parent

    # The name of this container. May be +nil+.
    attr_reader :name

    # A hash of default options to use when registering services. These
    # defaults also apply to namespaces, so when specifying a new default
    # service model (for instance) there may be unexpected side-effects with
    # the namespaces that are created.
    attr_reader :defaults

    # Create a new empty container with the given parent and name. If a parent
    # is given, this container will inherit the defaults of the parent at the
    # time the container was created.
    def initialize( parent=nil, name=nil )
      @root = nil
      @builder = nil

      @name = name
      @parent = parent
      @service_points = Hash.new

      @defaults = ( parent.nil? ? Hash.new : parent.defaults.dup )
    end

    # Returns the root of the current hierarchy. If the container is the
    # root, returns self, otherwise calls Container#root on its parent.
    # The value is cached for future reference.
    def root
      return @root if @root
      return self if parent.nil?
      @root = parent.root
    end

    # Returns +true+ if this container either is the given container or is
    # descended from the given container, and +false+ otherwise.
    def descended_from?( container )
      return true if self == container
      return false unless parent
      parent.descended_from? container
    end

    # Return the fully qualified name of this container, which is the
    # container's name and all parent's names up to the root container,
    # catenated together with dot characters, i.e., "one.two.three".
    def fullname
      parent_name = ( parent ? parent.fullname : nil )
      return @name.to_s unless parent_name
      "#{parent_name}.#{@name}"
    end

    # Returns the DefinitionContext instance that can be used to "build"
    # this container.
    def builder
      @builder ||= self[ :definition_context_factory ].new( self )
    end

    # If a block is given, yields the container's builder instance to the
    # block. Otherwise, simply returns the builder instance.
    #
    # Usage:
    #
    #   container.define do |b|
    #     b.foo { Bar.new }
    #     b.baz { Baz.new }
    #     ...
    #   end
    #
    # Or:
    #
    #   container.define.foo { Bar.new }
    #   container.define.baz { Baz.new }
    def define
      yield builder if block_given?
      builder
    end

    # Create a new DefinitionContext around the container, and then evaluate
    # the block within the new context instance (via +instance_eval+).
    #
    # Usage:
    #
    #   container.define! do
    #     calc( :model => :prototype ) { Calc.new( operations ) }
    #   end
    def define!( &block )
      raise ArgumentError, "block expected" unless block
      builder.instance_eval( &block )
      self
    end

    # Register the named service with the container. When the service is
    # requested (with Container#[]), the associated callback will be used
    # to construct it.
    #
    # This returns the registry that was used to register the service.
    #
    # Usage:
    #
    #   container.register( :calc, :model=>:prototype ) do |c|
    #     Calc.new( c.operations )
    #   end
    def register( name, opts={}, &callback )
      raise ArgumentError, "expect block" unless callback

      name = name.to_s.intern unless name.is_a?( Symbol )
      @service_points[ name ] =
        ServicePoint.new( self, name, @defaults.merge( opts ), &callback )

      self
    end

    # Create a new namespace within the container, with the given name. If a
    # block is provided, it will be invoked when the namespace is created,
    # with the new namespace passed to it.
    #
    # For the curious, namespaces are simply services that are implemented
    # by Container.  The two statements are conceptually identical:
    #
    #   container.namespace( :calc )
    #   container.register( :calc ) { |c,p| Needle::Container.new( c, p.name ) }
    #
    # Note that this means that namespaces may be singletons or prototypes, or
    # have immediate or deferred instantiation, and so forth. (The default of
    # immediate, singleton instantiation is sufficient for 99% of the things
    # you'll use namespaces for.)
    #
    # Usage:
    #
    #   container.namespace( :operations ) do |op|
    #     op.register( :add ) { Adder.new }
    #     ...
    #   end
    #
    #   adder = container.calc.operations.add
    #
    # *Note*: the block is not invoked until the namespace is created, which
    # is not until it is first referenced. If you need the namespace to be
    # created immediately, either use #namespace_define or reference the
    # namespace as soon as you've created it.
    def namespace( name, opts={}, &block )
      register( name, opts ) do |c,p|
        ns = self[ :namespace_impl_factory ].new( c, name )
        block.call ns if block
        ns
      end
    end

    # Create a new namespace within the container, with the given name.
    # The block (which is required) will be passed to Container#define! on
    # the new namespace.
    #
    # For the curious, namespaces are simply services that are implemented
    # by Container.  The two statements are really identical:
    #
    #   container.namespace( :calc )
    #   container.register( :calc ) { |c,p| Needle::Container.new( c, p.name ) }
    #
    # Note that this means that namespaces may be singletons or prototypes, or
    # have immediate or deferred instantiation, and so forth. (The default of
    # immediate, singleton instantiation is sufficient for 99% of the things
    # you'll use namespaces for.)
    #
    # Usage:
    #
    #   container.namespace_define!( :operations ) do
    #     add { Adder.new }
    #     ...
    #   end
    #
    #   adder = container.calc.operations.add
    #
    # *Note*: this method will immediately instantiate the new namespace,
    # unlike #namespace. If you want instantiation of the namespace to be
    # deferred, either use a deferring service model
    # (like <tt>:singleton_deferred</tt>) or create the namespace via
    # #namespace.
    def namespace_define!( name, opts={}, &block )
      raise ArgumentError, "block expected" unless block
      namespace( name, opts ) { |ns| ns.define!( &block ) }
      self[name]
    end

    alias :namespace! :namespace_define!

    # Create a new namespace within the container, with the given name.
    # The block (which is required) will be passed to Container#define on
    # the new namespace.
    #
    # For the curious, namespaces are simply services that are implemented
    # by Container.  The two statements are really identical:
    #
    #   container.namespace( :calc )
    #   container.register( :calc ) { |c,p| Needle::Container.new( c, p.name ) }
    #
    # Note that this means that namespaces may be singletons or prototypes, or
    # have immediate or deferred instantiation, and so forth. (The default of
    # immediate, singleton instantiation is sufficient for 99% of the things
    # you'll use namespaces for.)
    #
    # Usage:
    #
    #   container.namespace_define( :operations ) do |b|
    #     b.add { Adder.new }
    #     ...
    #   end
    #
    #   adder = container.calc.operations.add
    #
    # *Note*: this method will immediately instantiate the new namespace,
    # unlike #namespace. If you want instantiation of the namespace to be
    # deferred, either use a deferring service model
    # (like <tt>:singleton_deferred</tt>) or create the namespace via
    # #namespace.
    def namespace_define( name, opts={}, &block )
      raise ArgumentError, "block expected" unless block
      namespace( name, opts ) { |ns| ns.define( &block ) }
      self[name]
    end

    # Describe a new interceptor to use that will intercept method calls
    # on the named service. This method returns a new Interceptor instance,
    # which can be used directly to configure the behavior of the interceptor.
    #
    # Usage:
    #
    #   container.intercept( :calc ).with { |c| c.logging_interceptor }
    def intercept( name )
      point = find_definition( name )
      raise ServiceNotFound, "#{fullname}.#{name}" unless point

      interceptor = self[ :interceptor_impl_factory ].new
      point.interceptor interceptor

      interceptor
    end

    # Returns the pipeline object for the named service, which allows clients
    # to explicitly manipulate the service's instantiation pipeline.
    #
    # Usage:
    #
    #   container.pipeline( :calc ).
    #     add( :initialize ).
    #     add( :custom ) { |me,*args| me.succ.call( *args ) }
    def pipeline( name )
      point = find_definition( name )
      raise ServiceNotFound, "#{fullname}.#{name}" unless point

      point.pipeline
    end

    # Searches the current container and its ancestors for the named service.
    # If found, the service point (the definition of that service) is returned,
    # otherwise +nil+ is returned.
    def find_definition( name )
      point = @service_points[ name ]
      point = parent.find_definition( name ) if parent unless point
      point
    end

    # Retrieves the named service, if it exists. Ancestors are searched if the
    # service is not defined by the current container (see #find_definition).
    # If the named service does not exist, ServiceNotFound is raised.
    #
    # Note that this returns the instantiated service, not the service point.
    #
    # Also, if any pipeline element in the instantiation pipeline does not
    # support extra parameters when extra parameters have been given, then an
    # error will be raised.
    def get( name, *args )
      point = find_definition( name )
      raise ServiceNotFound, "#{fullname}.#{name}" unless point

      point.instance( self, *args )
    end

    alias :[] :get

    # Returns +true+ if this container includes a service point with the given
    # name. Returns +false+ otherwise.
    def has_key?( name )
      @service_points.has_key?( name )
    end

    # Returns +true+ if this container <em>or any ancestor</em> includes a
    # service point with the given name. Returns +false+ otherwise.
    def knows_key?( name )
      return true if has_key?( name )
      return parent.knows_key?( name ) if parent
      false
    end

    # Return an array of the names of all service points in this container.
    def keys
      @service_points.keys
    end

    # Require the given file, and then invoke the given registration method on
    # the target module. The container will be passed as the sole parameter to
    # the registration method. This allows you to easily decentralize the
    # definition of services.
    #
    # Usage:
    #
    #   container.require( "app/services", "App::Services" )
    #
    #   # in app/services.rb:
    #
    #   module App
    #     module Services
    #
    #       def register_services( container )
    #         ...
    #       end
    #       module_function :register_services
    #
    #     end
    #   end
    def require( file, target_name, registration_method=:register_services )
      Kernel.require file

      if target_name.is_a?( Module )
        target = target_name
      else
        target = Object
        target_name.to_s.split( /::/ ).each do |element|
          target = target.const_get( element )
        end
      end

      target.__send__( registration_method, self )
    end

    # As a convenience for accessing services, this delegates any message
    # sent to the container (which has no parameters and no block) to
    # Container#[]. Note that this incurs slightly more overhead than simply
    # calling Container#[] directly, so if performance is an issue, you should
    # avoid this approach.
    #
    # Usage:
    #
    #   container.register( :add ) { Adder.new }
    #   p container.add == container[:add] # => true
    def method_missing( sym, *args )
      if knows_key?( sym )
        get( sym, *args )
      else
        super
      end
    end

    # Returns true if this container responds to the given message, or if it
    # explicitly contains a service with the given name (see #has_key?). In
    # this case, #has_key? is used instead of #knows_key? so that subcontainers
    # may be used as proper hashes by their parents.
    def respond_to?( sym )
      has_key?( sym ) || super
    end

    # Specifies a set of default options to use temporarily. The options are
    # merged with the current set of defaults for the container. The original
    # options are returned, and may be restored by invoking #use again with
    # the hash that is returned. If a block is given, the registry will be
    # yielded to it and the options automatically restored when the block
    # returns.
    def use( opts, &block ) # :yield: self
      use! @defaults.merge( opts ), &block
    end

    # Specifies a set of default options to use temporarily. The original
    # options are returned. This differs from #use in that it will completely
    # replace the original options, instead of merging the parameters with
    # the originals.
    def use!( opts )
      original = @defaults
      @defaults = opts

      if block_given?
        begin
          yield self
        ensure
          use! original
        end
      end

      return original
    end

  end

end
