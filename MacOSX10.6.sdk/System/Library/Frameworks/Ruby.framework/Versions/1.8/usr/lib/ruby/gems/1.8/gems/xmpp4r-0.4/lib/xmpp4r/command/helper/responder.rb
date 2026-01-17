module Jabber

  module Command

    ##
    # The Responder Helper handles the low-level stuff of the
    # Ad-hoc commands (JEP 0050).
    class Responder

      ##
      # Initialize a Responder
      def initialize(stream)
        @stream = stream
        @commandsdiscocbs = CallbackList.new
        @commandexeccbs = CallbackList.new

        stream.add_iq_callback(180, self) { |iq|
          iq_callback(iq)
        }
      end

      ##
      # Add a callback for <query> stanzas asking for the list
      # of ad-hoc commands
      def add_commands_disco_callback(priority = 0, ref = nil, &block)
        @commandsdiscocbs.add(priority, ref, block)
      end

      ##
      # Add a callback for <command> stanzas asking for the execution
      # of an ad-hoc command
      def add_commands_exec_callback(priority = 0, ref = nil, &block)
        @commandexeccbs.add(priority, ref, block)
      end

      ##
      # Handles <iq> stanzas and execute callbacks
      def iq_callback(iq)
        if iq.type == :get
          if iq.query.kind_of?(Jabber::Discovery::IqQueryDiscoItems) &&
             iq.query.node == "http://jabber.org/protocol/commands"
            @commandsdiscocbs.process(iq)
          end
        elsif iq.type == :set && iq.command
          @commandexeccbs.process(iq)
        end
      end

    end

  end

end
