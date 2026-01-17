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

require 'needle/interceptor-chain'
require 'needle/pipeline/element'

module Needle
  module Pipeline

    # The pipeline element that implements adding interceptors to a service.
    class InterceptorElement < Element

      set_default_priority 0

      # The array of interceptors to be proxied onto the object.
      attr_reader :interceptors

      # Initializes the array of interceptors. It is initially empty.
      def initialize_element
        @interceptors = []
      end

      # Invokes the next element in the chain and adds the interceptors to
      # the result, returning a proxy object wrapped by the interceptors.
      def call( container, point, *args )
        service = succ.call( container, point, *args )
        InterceptorChainBuilder.build( point, service, @interceptors )
      end

    end

  end
end
