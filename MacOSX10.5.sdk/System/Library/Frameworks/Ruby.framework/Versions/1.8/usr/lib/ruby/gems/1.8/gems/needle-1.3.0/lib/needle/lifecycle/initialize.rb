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

    # The instantiation pipeline element that implements calling a separate
    # initialization method on the instantiated service. This should always be
    # placed in the pipeline as close to the service implementation as possible
    # (hence, the low default priority).
    class Initialize < Needle::Pipeline::Element

      set_default_priority( -100 )

      # Initialize the element. Looks at the options hash to determine the
      # name of the initialization method to call, defaulting to
      # <tt>:initialize_service</tt>.
      def initialize_element
        @init_method = options[:init_method] || :initialize_service
      end

      # Invokes the next element of the chain. If the result responds to the
      # requested initialization method, that method is invoked on the
      # result, and the result is returned.
      def call( *args )
        service = succ.call( *args )
        service.send @init_method if service.respond_to?( @init_method )
        service
      end

    end

  end
end
