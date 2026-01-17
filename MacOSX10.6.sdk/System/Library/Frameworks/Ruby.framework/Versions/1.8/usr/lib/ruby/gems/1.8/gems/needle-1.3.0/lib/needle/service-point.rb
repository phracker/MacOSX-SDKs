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

require 'needle/pipeline/collection'
require 'needle/thread'

module Needle

  # A "service point" is a definition of a service. Just as a class defines the
  # behavior of an object, so does a service point describe a service. In
  # particular, a service point also knows how to instantiate a service.
  #
  # A ServicePoint should never be directly instantiated. Instead, define
  # services via the interfaces provided by Container.
  class ServicePoint

    # The name of this service point, as it is known to the container that it
    # was registered in.
    attr_reader :name

    # A reference to the container that contains this service point.
    attr_reader :container

    # The reference to the instantiation pipeline used by this service point.
    attr_reader :pipeline

    # Create a new service point that references the given container and has
    # the given name. The associated callback will be used to instantiate the
    # service on demand.
    #
    # The <tt>:model</tt> option is used to tell Needle which style of
    # life-cycle management should be used for the service. It defaults to
    # <tt>:singleton</tt>. The model must be a symbol that refers to a service
    # model that has been registered in the root <tt>:service_models</tt>
    # service.
    #
    # The <tt>:pipeline</tt> option is mutually exclusive with <tt>:model</tt>.
    # It must be an array of symbols (or strings) that define the instantiation
    # pipeline to use for this service. Each element must correspond to an entry
    # in the <tt>:pipeline_elements</tt> service.
    def initialize( container, name, opts={}, &callback )
      @name = name
      @container = container
      @callback = callback
      @pipeline = Needle::Pipeline::Collection.new self
      @chain = nil

      @chain_mutex = QueryableMutex.new
      @element_mutex = QueryableMutex.new

      if opts[:pipeline]
        elements = opts[:pipeline]
      else
        model = opts[:model] || :singleton
        elements = @container[:service_models][model]
      end

      elements.concat [ *opts[:include] ] if opts[:include]
      elements.each { |element| @pipeline.add element, opts }
    end

    # Returns the fully-qualified name of the service point, with the point's
    # name, its container's name, and all of its container's ancestors' names
    # concatenated together with dot characters, i.e. "one.two.three".
    def fullname
      container_name = @container.fullname
      if container_name
        "#{container_name}.#{@name}"
      else
        @name.to_s
      end
    end

    # Adds the given interceptor definition to this service point. The
    # parameter should act like an instance of Interceptor.
    def interceptor( interceptor )
      @element_mutex.synchronize do
        element = @pipeline.get( :interceptor )
        unless element
          @pipeline.add( :interceptor )
          element = @pipeline.get( :interceptor )
        end
        element.interceptors << interceptor
        @pipeline.reset!
        @chain = nil
      end
    end

    # Return the service instance represented by this service point. Depending
    # on the style of lifecycle management chosen for this service point, this
    # may or may not be a new instance for every invocation of this method.
    #
    # The first argument is the container that should be used to resolve this
    # service point. Assuming the container to be used is this service point's
    # own container would mean that any nested service points couldn't override
    # service points their parents' service points used.
    #
    # Any extra arguments to this method will be passed through to the chain,
    # which may cause an error if there is an element in the pipeline that does
    # not accept additional arguments. Regardless, the first two parameters to
    # the chain will always be the container and the service point.
    def instance( actual_container, *args )
      unless @chain
        @chain_mutex.synchronize do
          @chain = @pipeline.chain_to( @callback ) unless @chain
        end
      end

      @chain.call( actual_container, self, *args )
    end

  end

end
