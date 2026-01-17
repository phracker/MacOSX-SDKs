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

    # The instantiation pipeline element that enforces the multiton
    # multiplicity. "Multiton" multiplicity is like singleton multiplicity,
    # except that the guarded instance is unique for each unique set of
    # arguments passed to the multiton.
    class Multiton < Needle::Pipeline::Element
      set_default_priority 100

      # Creates the mutex to use and initializes the cache.
      def initialize_element
        @mutex = QueryableMutex.new
        @cached = Hash.new
        @is_cached = Hash.new( false )
      end

      # Returns the cached reference for the given arguments, if it has been
      # previously cached. Otherwise, invokes the next element in the pipeline
      # and caches the result. The cached reference is returned.
      def call( container, point, *args )
        unless @is_cached[ args ]
          @mutex.synchronize do
            unless @is_cached[ args ]
              @cached[ args ] = succ.call( container, point, *args )
              @is_cached[ args ] = true
            end
          end
        end

        @cached[ args ]
      end

      # Resets the caches for this multiton object.
      def reset!
        @mutex.synchronize do
          @cached = Hash.new
          @is_cached = Hash.new( false )
        end
      end

    end

  end
end
