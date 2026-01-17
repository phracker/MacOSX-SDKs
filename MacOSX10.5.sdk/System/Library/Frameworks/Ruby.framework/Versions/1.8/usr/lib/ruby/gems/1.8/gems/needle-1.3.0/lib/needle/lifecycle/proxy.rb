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

require 'needle/thread'

module Needle
  module Lifecycle

    # A proxy class to aid in deferred instantiation of service points. This is
    # used primarily by the "deferred" service models.
    class Proxy

      # Create a new proxy object that wraps the object returned by either the
      # +proc_obj+ or +callback+. (Only one of +proc_obj+ or +callback+ should
      # be specified.)
      def initialize( proc_obj=nil, *args, &callback )
        if proc_obj && callback
          raise ArgumentError, "only specify argument OR block, not both"
        end

        @callback = proc_obj || callback or
          raise ArgumentError, "callback required"

        @args = args
        @mutex = QueryableMutex.new
        @instantiation_failed = false
        @instance = nil
      end

      # Attempts to invoke the given message on the service. If the service has
      # not yet been instantiated, it will be instantiated and stored.
      def method_missing( sym, *args, &block )
        unless @instance || @instantiation_failed
          @mutex.synchronize do
            unless @instance || @instantiation_failed
              begin
                @instance = @callback.call( *@args )
              rescue Exception
                @instantiation_failed = true
                raise
              end
            end
          end
        end

        unless @instantiation_failed
          @instance.__send__ sym, *args, &block
        else
          # just return nil... this way, a failed instantiation won't barf
          # more than once... I hope...
        end
      end

      # Override some "standard" methods so that they are routed to the
      # service instead of to the proxy.
      [ "is_a?", "respond_to?", "to_s", "to_str",
        "to_i", "to_int", "to_io", "===", "==", "=~",
        "send" ].each do |method|
      #begin
        class_eval <<-EOF
          def #{method}( *args, &block )
            unless @instantiation_failed
              method_missing '#{method}', *args, &block
            else
              super
            end
          end
        EOF
      end

      def inspect
        "#<#{self.class.name}:#{"0x%08x"%self.object_id}:" +
        "instantiated=>#{@instance ? true : false}>"
      end

    end

  end
end
