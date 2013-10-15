require 'thread'

module Jabber
  module Framework
    class Base

      def self.helper(name, klass=nil, &factory)
        if klass.nil? and factory.nil?
          raise "helper #{name} needs a class or factory"
        end

        define_method(name) do
          @helpers_lock.synchronize do
            if @helpers[name]
              @helpers[name]
            else
              if factory
                @helpers[name] = instance_eval { factory.call(@stream) }
              elsif klass
                @helpers[name] = klass.new(@stream)
              else
                raise
                end
            end
          end
        end
      end

      attr_accessor :stream

      def initialize(stream)
        @stream = stream
        @helpers = {}
        @helpers_lock = Mutex.new

        # Catch all unhandled iq stanzas (lowest priority)
        @stream.add_iq_callback(-1000, self, &method(:on_unhandled_iq))
      end

      def on_unhandled_iq(iq)
        if iq.type == :get or iq.type == :set
          answer = iq.answer(true)
          answer.type = :error
          answer.add(ErrorResponse.new('feature-not-implemented'))
          @stream.send(answer)

          true
        else
          false
        end
      end

    end
  end
end
