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

require 'needle/container'
require 'needle/definition-context'
require 'needle/errors'
require 'needle/interceptor'
require 'needle/lifecycle/deferred'
require 'needle/lifecycle/initialize'
require 'needle/lifecycle/multiton'
require 'needle/lifecycle/singleton'
require 'needle/lifecycle/threaded'
require 'needle/log-factory'
require 'needle/logging-interceptor'
require 'needle/pipeline/interceptor'

module Needle

  # Registry is a specialization of Container, with additional functionality
  # for bootstrapping basic services into a new registry. It also supports a
  # #define! method for easily registering new services.
  #
  # Usage:
  #
  #   require 'needle'
  #
  #   registry = Needle::Registry.new
  #   registry.register( :foo ) { Foo.new }
  #   registry.register( :bar ) { |c| Bar.new( c.foo ) }
  #
  #   bar = registry.bar
  class Registry < Container

    # Instantiate a new Registry (via #new) and immediately invoke #define!
    # using the given block.
    #
    # Usage:
    #
    #   registry = Needle::Registry.define! do
    #     add { Adder.new }
    #     ...
    #   end
    #
    #   adder = registry.add
    def self.define!( *parms, &block )
      raise NeedleError, "needs a block" if block.nil?
      new( *parms ) { |reg| reg.define!( &block ) }
    end

    # Instantiate a new Registry (via #new) and immediately invoke #define
    # using the given block.
    #
    # Usage:
    #
    #   registry = Needle::Registry.define do |b|
    #     b.add { Adder.new }
    #     ...
    #   end
    #
    #   adder = registry.add
    def self.define( *parms, &block )
      raise NeedleError, "needs a block" if block.nil?
      new( *parms ) { |reg| reg.define( &block ) }
    end

    # Instantiate a new Registry. The options hash may include the following
    # keys:
    #
    # <tt>:logs</tt>:: options used to initialize the logger factory. The
    #                  value to this key should be another hash.
    # <tt>:parent</tt>:: The parent container of this registry.
    # <tt>:name</tt>:: The name of this registry.
    #
    # If a block is given, the constructed registry instance is yielded to it.
    #
    # Usage:
    #
    #   registry = Needle::Registry.new
    #
    # or
    #
    #   registry = Needle::Registry.new do |reg|
    #     reg.register( :add ) { Adder.new }
    #   end
    #
    # or
    #
    #   registry = Needle::Registry.new(
    #     :logs => { :filename => "/dev/null" }
    #   )
    def initialize( opts={} )
      super( opts[:parent], opts[:name] )
      bootstrap( opts ) if parent.nil?
      yield( self ) if block_given?
    end

    # Returns +nil+, unless the registry has a parent, in which case it acts
    # like Container#fullname. Registries are usually unnamed containers.
    def fullname
      parent ? super : nil
    end

    # Bootstraps the pipeline elements, service models, logger factory, and
    # logging interceptor services into the current registry. This is only
    # called when a new, root (parentless) registry is created.
    def bootstrap( opts )
      register( :pipeline_elements, :pipeline=>[] ) { Hash.new }
      pipeline( :pipeline_elements ).add( :singleton,
        Needle::Lifecycle::Singleton )

      self[:pipeline_elements].update(
        :singleton   => Needle::Lifecycle::Singleton,
        :initialize  => Needle::Lifecycle::Initialize,
        :deferred    => Needle::Lifecycle::Deferred,
        :interceptor => Needle::Pipeline::InterceptorElement,
        :multiton    => Needle::Lifecycle::Multiton,
        :threaded    => Needle::Lifecycle::Threaded
      )

      register( :service_models, :pipeline=>[:singleton] ) { Hash.new }
      self[:service_models].update(
        :multiton                      => [ :multiton ],
        :multiton_initialize           => [ :multiton, :initialize ],
        :multiton_deferred             => [ :multiton, :deferred ],
        :multiton_deferred_initialize  => [ :multiton, :deferred, :initialize ],
        :prototype                     => [],
        :prototype_initialize          => [ :initialize ],
        :prototype_deferred            => [ :deferred ],
        :prototype_deferred_initialize => [ :deferred, :initialize ],
        :singleton                     => [ :singleton ],
        :singleton_initialize          => [ :singleton, :initialize ],
        :singleton_deferred            => [ :singleton, :deferred ],
        :singleton_deferred_initialize => [ :singleton, :deferred, :initialize],
        :threaded                      => [ :threaded ],
        :threaded_initialize           => [ :threaded, :initialize ],
        :threaded_deferred             => [ :threaded, :deferred ],
        :threaded_deferred_initialize  => [ :threaded, :deferred, :initialize ]
      )

      register( :definition_context_factory ) { DefinitionContext }

      define do |b|
        b.namespace_impl_factory   { Container }
        b.interceptor_impl_factory { Interceptor }

        b.logs { LogFactory.new( opts[:logs] || {} ) }

        # a parameterized version of c[:logs] for easier access
        b.log_for( :model => :prototype ) { |c,p,name| c[:logs].get(name) }

        b.logging_interceptor { LoggingInterceptor }
      end
    end
    private :bootstrap

  end

end
