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
require 'needle/thread'

module Needle
  module Lifecycle

    # The instantiation pipeline element that enforces the singleton
    # multiplicity.
    class Singleton < Needle::Pipeline::Element
      set_default_priority 100

      # Creates the mutex to use and sets the cached reference to +nil+.
      def initialize_element
        @mutex = QueryableMutex.new
        @cached = nil
        @is_cached = false
      end

      # Returns the cached reference, if it has been previously cached.
      # Otherwise, invokes the next element in the pipeline and caches the
      # result. The cached reference is returned.
      def call( container, point )
        unless @is_cached
          @mutex.synchronize do
            unless @is_cached
              @cached = succ.call( container, point )
              @is_cached = true
            end
          end
        end

        @cached
      end

      # Resets the cached singleton instance, so that the next time it is
      # requested it is re-constructed.
      def reset!
        @mutex.synchronize do
          @cached = nil
          @is_cached = false
        end
      end

    end

  end
end
