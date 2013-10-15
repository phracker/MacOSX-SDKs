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
require 'needle/lifecycle/proxy'

module Needle
  module Lifecycle

    # The instantiation pipeline element that implements deferred
    # instantiation.
    class Deferred < Needle::Pipeline::Element

      set_default_priority 50

      # Returns a new proxy instance that wraps the next element of the
      # instantiation pipeline.
      def call( *args )
        Proxy.new( succ, *args )
      end

    end

  end
end
