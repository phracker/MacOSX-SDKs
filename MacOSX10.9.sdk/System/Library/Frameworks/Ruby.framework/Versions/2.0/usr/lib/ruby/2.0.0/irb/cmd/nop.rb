#
#   nop.rb -
#   	$Release Version: 0.9.6$
#   	$Revision: 38358 $
#   	by Keiju ISHITSUKA(keiju@ruby-lang.org)
#
# --
#
#
#
# :stopdoc:
module IRB
  module ExtendCommand
    class Nop

      @RCS_ID='-$Id: nop.rb 38358 2012-12-13 05:22:30Z zzak $-'

      def self.execute(conf, *opts)
	command = new(conf)
	command.execute(*opts)
      end

      def initialize(conf)
	@irb_context = conf
      end

      attr_reader :irb_context

      def irb
	@irb_context.irb
      end

      def execute(*opts)
	#nop
      end
    end
  end
end
# :startdoc:
