# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

module Jabber
  ##
  # This class manages a list of callbacks.
  #
  # ==Callbacks management and priority
  #
  # Callbacks are managed by the class CallbackList. When they are added, a
  # priority (just a number or anything Comparable with other priorities) is
  # specified. The biggest the priority is, the earliest the callback will be
  # considered.
  #
  # Callbacks are processed for a given set of objects as long as they return
  # false. If you want to stop processing, you must return true. Example :
  #  cbl = CallbackList.new
  #  c1 = false
  #  c2 = false
  #  c3 = false
  #  cbl.add(10) { c1 = true; 1 }
  #  cbl.add(5) { c2 = true; true }
  #  cbl.add(0) { c3 = true }
  #  cbl.process('aa')
  #  puts "#{c1} #{c2} #{c3}"
  # This example would display "true true false" as callbacks processing was
  # stopped after the second callback returned true.
  #
  # In XMPP4R, callbacks' priorities are quite normalized since we want to be
  # able to "cascade" callbacks in a clean way. Here are values your code should
  # take into account :
  #
  # >= 200::  logging & debugging callbacks. Those callbacks should not consume
  #           elements.
  # 100-199:: Where Helpers register their callbacks. The normal value is 100,
  #           and Helpers shouldn't register something else unless there's a
  #           very good reason to.
  # < 100::   all those numbers are normally available for your application.
  #           That's enough, don't you think ?
  class CallbackList

    # Create a new list of callbacks
    def initialize
      @list = []
    end

    ##
    # Add a callback to the list
    #
    # List will be sorted afterwards
    #
    # prio:: [Integer] the callback's priority, the higher, the sooner.
    # ref:: [String] the callback's reference
    # block:: [Block] a block to execute
    # return:: [Jabber::CallbackList] The list, for chaining
    def add(prio = 0, ref = nil, proc = nil, &block)
      block = proc if proc
      @list.push(Callback.new(prio, ref, block))
      @list.sort! { |a, b| b.priority <=> a.priority }
      self
    end

    ##
    # Delete a callback by reference
    # ref:: [String] the reference of the callback to delete
    # return:: [CallBackList] The list, for chaining
    def delete(ref)
      @list.delete_if { |item| item.ref == ref }
      self
    end

    ##
    # Number of elements in the list
    # return:: [Integer] The number of elements
    def length
      @list.length
    end

    ##
    # Process an element through all my callbacks. returns e.consumed?
    # e:: [Object] The elements to pass to the callback. You can pass
    # several, but of course, you block must know how to handle them.
    # return:: [Boolean] true if the element has been consumed
    def process(*e)
      # If somebody adds a new callback the list will get modified
      # and sorted(!) while still iterating through it. So we use a
      # local copy of @list. Any freshly added callback will receive
      # the next stanzas, not the current.
      list = @list.dup

      # process through callbacks
      list.each do |item|
        return true if item.block.call(*e) == true
      end
      false
    end
  end

  # This class is used to store callbacks inside CallbackList. See the
  # CallbackList class for more detailed explanations.
  class Callback

    # The Callback's priority
    attr_reader :priority

    # The Callback's reference, using for deleting purposes
    attr_reader :ref

    # The Callback's block to execute
    attr_reader :block

    ##
    # Create a new callback
    # priority:: [Integer] the callback's priority. The higher, the sooner it
    # will be executed
    # ref:: [String] The callback's reference
    def initialize(priority = 0, ref = nil, block = Proc.new {})
      @priority = priority
      @ref = ref
      @block = block
    end
  end
end
