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

require 'thread'

module Needle

  # A subclass of Mutex that allows clients to discover which thread has the
  # mutex locked. This is necessary for (among other things) discovering
  # cycles in the dependency graph of services.
  class QueryableMutex < Mutex

    # Create a new unlocked QueryableMutex.
    def initialize
      super
      @locking_thread = nil
    end

    # Checks to see if the current thread has the mutex locked, and if it
    # does, raises an exception. Otherwise, locks the mutex and sets the
    # locking thread to Thread.current.
    def lock
      if @locking_thread == Thread.current
        raise ThreadError,
          "an attempt was made to reacquire an existing lock " +
          "(this could happen if you have a circular dependency on a service)"
      end

      while (Thread.critical = true; @locked)
        @waiting.push Thread.current
        Thread.stop
      end
      @locked = true
      @locking_thread = Thread.current
      Thread.critical = false
      self
    end

    # Attempts to acquire the lock. Returns +true+ if the lock was acquired,
    # and +false+ if the mutex was already locked.
    def try_lock
      result = false
      Thread.critical = true
      unless @locked
        @locked = true
        result = true
        @locking_thread = Thread.current
      end
      Thread.critical = false
      result
    end
    
    # Unlocks the mutex and sets the locking thread to +nil+.
    def unlock
      return unless @locked
      Thread.critical = true
      @locked = false
      begin
        t = @waiting.shift
        t.wakeup if t
      rescue ThreadError
        retry
      end
      @locking_thread = nil
      Thread.critical = false
      begin
        t.run if t
      rescue ThreadError
      end
      self
    end

    # Return +true+ if the current thread has locked this mutex.
    def self_locked?
      @locking_thread == Thread.current
    end

  end

end
