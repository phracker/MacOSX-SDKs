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
  module Lifecycle

    # The instantiation pipeline element that enforces the singleton
    # multiplicity, on a per-thread basis.
    class Threaded < Needle::Pipeline::Element
      set_default_priority 100

      # Returns a Hash of threaded services that are cached by the current
      # thread.
      def service_cache
        Thread.current[ :threaded_services ] ||= Hash.new
      end

      # Returns the cached reference, if it has been previously cached for
      # the current thread. Otherwise, invokes the next element in the pipeline
      # and caches the result. The cached reference is returned.
      def call( container, point )
        cache = service_cache
        name = service_point.fullname

        unless cache.has_key?( name )
          service = succ.call( container, point )
          cache[ name ] = service
        end

        cache[ name ]
      end

      # Resets the cached singleton instance, so that the next time it is
      # requested it is re-constructed. Only the cache for the current thread
      # and service point is reset.
      def reset!
        cache = service_cache
        cache.delete service_point.fullname
      end

    end

  end
end
