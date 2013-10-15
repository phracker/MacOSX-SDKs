# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

module Jabber
  ##
  # This class implements semaphore for threads synchronization.
  class Semaphore

    ##
    # Initialize new semaphore
    #
    # val:: [Integer] number of threads, that can enter to section
    def initialize(val=0)
      @tickets = val
      @lock = Mutex.new
      @cond = ConditionVariable.new
    end

    ##
    # Waits until are available some free tickets
    def wait
      @lock.synchronize {
        @cond.wait(@lock) while !(@tickets > 0)
        @tickets -= 1
      }
    end

    ##
    # Unlocks guarded section, increments number of free tickets
    def run
      @lock.synchronize {
        @tickets += 1
        @cond.signal
      }
    end
  end
end
