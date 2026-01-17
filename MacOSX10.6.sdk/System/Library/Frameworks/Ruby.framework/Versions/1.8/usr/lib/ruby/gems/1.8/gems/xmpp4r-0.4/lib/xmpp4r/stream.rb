# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/callbacks'
require 'socket'
require 'thread'
require 'xmpp4r/semaphore'
require 'xmpp4r/streamparser'
require 'xmpp4r/presence'
require 'xmpp4r/message'
require 'xmpp4r/iq'
require 'xmpp4r/debuglog'
require 'xmpp4r/idgenerator'

module Jabber
  ##
  # The stream class manages a connection stream (a file descriptor using which
  # XML messages are read and sent)
  #
  # You may register callbacks for the three Jabber stanzas
  # (message, presence and iq) and use the send and send_with_id
  # methods.
  #
  # To ensure the order of received stanzas, callback blocks are
  # launched in the parser thread. If further blocking operations
  # are intended in those callbacks, run your own thread there.
  class Stream
    DISCONNECTED = 1
    CONNECTED = 2

    # file descriptor used
    attr_reader :fd

    # connection status
    attr_reader :status

    ##
    # Initialize a new stream
    def initialize
      @fd = nil
      @status = DISCONNECTED
      @xmlcbs = CallbackList.new
      @stanzacbs = CallbackList.new
      @messagecbs = CallbackList.new
      @iqcbs = CallbackList.new
      @presencecbs = CallbackList.new
      @send_lock = Mutex.new
      @last_send = Time.now
      @exception_block = nil
      @threadblocks = []
      @wakeup_thread = nil
      @streamid = nil
      @streamns = 'jabber:client'
      @features_sem = Semaphore.new
      @parser_thread = nil
    end

    ##
    # Start the XML parser on the fd
    def start(fd)
      @stream_mechanisms = []
      @stream_features = {}

      @fd = fd
      @parser = StreamParser.new(@fd, self)
      @parser_thread = Thread.new do
        Thread.current.abort_on_exception = true
        begin
          @parser.parse
          Jabber::debuglog("DISCONNECTED\n")

          if @exception_block
            Thread.new { close!; @exception_block.call(nil, self, :disconnected) }
          else
            close!
          end
        rescue Exception => e
          Jabber::debuglog("EXCEPTION:\n#{e.class}\n#{e.message}\n#{e.backtrace.join("\n")}")

          if @exception_block
            Thread.new do
              Thread.current.abort_on_exception = true
              close
              @exception_block.call(e, self, :start)
            end
          else
            Jabber::debuglog "Exception caught in Parser thread! (#{e.class})\n#{e.backtrace.join("\n")}"
            close!
            raise
          end
        end
      end

      @status = CONNECTED
    end

    def stop
      @parser_thread.kill
      @parser = nil
    end

    ##
    # Mounts a block to handle exceptions if they occur during the
    # poll send.  This will likely be the first indication that
    # the socket dropped in a Jabber Session.
    #
    # The block has to take three arguments:
    # * the Exception
    # * the Jabber::Stream object (self)
    # * a symbol where it happened, namely :start, :parser, :sending and :end
    def on_exception(&block)
      @exception_block = block
    end

    ##
    # This method is called by the parser when a failure occurs
    def parse_failure(e)
      Jabber::debuglog("EXCEPTION:\n#{e.class}\n#{e.message}\n#{e.backtrace.join("\n")}")

      # A new thread has to be created because close will cause the thread
      # to commit suicide(???)
      if @exception_block
        # New thread, because close will kill the current thread
        Thread.new do
          Thread.current.abort_on_exception = true
          close
          @exception_block.call(e, self, :parser)
        end
      else
        Jabber::debuglog "Stream#parse_failure was called by XML parser. Dumping " +
          "backtrace...\n" + e.exception + "\n#{e.backtrace.join("\n")}"
        close
        raise
      end
    end

    ##
    # This method is called by the parser upon receiving <tt></stream:stream></tt>
    def parser_end
      if @exception_block
        Thread.new do
          Thread.current.abort_on_exception = true
          close
          @exception_block.call(nil, self, :close)
        end
      else
        close
      end
    end

    ##
    # Returns if this connection is connected to a Jabber service
    # return:: [Boolean] Connection status
    def is_connected?
      return @status == CONNECTED
    end

    ##
    # Returns if this connection is NOT connected to a Jabber service
    #
    # return:: [Boolean] Connection status
    def is_disconnected?
      return @status == DISCONNECTED
    end

    ##
    # Processes a received REXML::Element and executes
    # registered thread blocks and filters against it.
    #
    # element:: [REXML::Element] The received element
    def receive(element)
      Jabber::debuglog("RECEIVED:\n#{element.to_s}")

      if element.namespace('').to_s == '' # REXML namespaces are always strings
        element.add_namespace(@streamns)
      end

      case element.prefix
      when 'stream'
        case element.name
          when 'stream'
            stanza = element
            @streamid = element.attributes['id']
            @streamns = element.namespace('') if element.namespace('')

            # Hack: component streams are basically client streams.
            # Someday we may want to create special stanza classes
            # for components/s2s deriving from normal stanzas but
            # posessing these namespaces
            @streamns = 'jabber:client' if @streamns == 'jabber:component:accept'

            unless element.attributes['version']  # isn't XMPP compliant, so
              Jabber::debuglog("FEATURES: server not XMPP compliant, will not wait for features")
              @features_sem.run                   # don't wait for <stream:features/>
            end
          when 'features'
            stanza = element
            element.each { |e|
              if e.name == 'mechanisms' and e.namespace == 'urn:ietf:params:xml:ns:xmpp-sasl'
                e.each_element('mechanism') { |mech|
                  @stream_mechanisms.push(mech.text)
                }
              else
                @stream_features[e.name] = e.namespace
              end
            }
            Jabber::debuglog("FEATURES: received")
            @features_sem.run
          else
            stanza = element
        end
      else
        # Any stanza, classes are registered by XMPPElement::name_xmlns
        begin
          stanza = XMPPStanza::import(element)
        rescue NoNameXmlnsRegistered
          stanza = element
        end
      end

      # Iterate through blocked threads (= waiting for an answer)
      #
      # We're dup'ping the @threadblocks here, so that we won't end up in an
      # endless loop if Stream#send is being nested. That means, the nested
      # threadblock won't receive the stanza currently processed, but the next
      # one.
      threadblocks = @threadblocks.dup
      threadblocks.each { |threadblock|
        exception = nil
        r = false
        begin
          r = threadblock.call(stanza)
        rescue Exception => e
          exception = e
        end

        if r == true
          @threadblocks.delete(threadblock)
          threadblock.wakeup
          return
        elsif exception
          @threadblocks.delete(threadblock)
          threadblock.raise(exception)
        end
      }

      Jabber::debuglog("PROCESSING:\n#{stanza.to_s} (#{stanza.class})")
      return true if @xmlcbs.process(stanza)
      return true if @stanzacbs.process(stanza)
      case stanza
      when Message
        return true if @messagecbs.process(stanza)
      when Iq
        return true if @iqcbs.process(stanza)
      when Presence
        return true if @presencecbs.process(stanza)
      end
    end

    ##
    # This is used by Jabber::Stream internally to
    # keep track of any blocks which were passed to
    # Stream#send.
    class ThreadBlock
      def initialize(block)
        @block = block
        @waiter = Semaphore.new
        @exception = nil
      end
      def call(*args)
        @block.call(*args)
      end
      def wait
        @waiter.wait
        raise @exception if @exception
      end
      def wakeup
        # TODO: Handle threadblock removal if !alive?
        @waiter.run
      end
      def raise(exception)
        @exception = exception
        @waiter.run
      end
    end

    def send_data(data)
      @send_lock.synchronize do
        @last_send = Time.now
        @fd << data
        @fd.flush
      end
    end

    ##
    # Sends XML data to the socket and (optionally) waits
    # to process received data.
    #
    # Do not invoke this in a callback but in a seperate thread
    # because we may not suspend the parser-thread (in whose
    # context callbacks are executed).
    #
    # xml:: [String] The xml data to send
    # &block:: [Block] The optional block
    def send(xml, &block)
      Jabber::debuglog("SENDING:\n#{xml}")
      @threadblocks.unshift(threadblock = ThreadBlock.new(block)) if block
      begin
        # Temporarily remove stanza's namespace to
        # reduce bandwidth consumption
        if xml.kind_of? XMPPStanza and xml.namespace == 'jabber:client'
          xml.delete_namespace
          send_data(xml.to_s)
          xml.add_namespace(@streamns)
        else
          send_data(xml.to_s)
        end
      rescue Exception => e
        Jabber::debuglog("EXCEPTION:\n#{e.class}\n#{e.message}\n#{e.backtrace.join("\n")}")

        if @exception_block
          Thread.new do
            Thread.current.abort_on_exception = true
            close!
            @exception_block.call(e, self, :sending)
          end
        else
          Jabber::debuglog "Exception caught while sending! (#{e.class})\n#{e.backtrace.join("\n")}"
          close!
          raise
        end
      end
      # The parser thread might be running this (think of a callback running send())
      # If this is the case, we mustn't stop (or we would cause a deadlock)
      if block and Thread.current != @parser_thread
        threadblock.wait
      elsif block
        Jabber::debuglog("WARNING:\nCannot stop current thread in Jabber::Stream#send because it is the parser thread!")
      end
    end

    ##
    # Send an XMMP stanza with an Jabber::XMPPStanza#id. The id will be
    # generated by Jabber::IdGenerator if not already set.
    #
    # The block will be called once: when receiving a stanza with the
    # same Jabber::XMPPStanza#id. There is no need to return true to
    # complete this! Instead the return value of the block will be
    # returned. This is a direct result of unique request/response
    # stanza identification via the id attribute.
    #
    # The block may be omitted. Then, the result will be the response
    # stanza.
    #
    # Be aware that if a stanza with <tt>type='error'</tt> is received
    # the function does not yield but raises an ServerError with
    # the corresponding error element.
    #
    # Please see Stream#send for some implementational details.
    #
    # Please read the note about nesting at Stream#send
    # xml:: [XMPPStanza]
    def send_with_id(xml, &block)
      if xml.id.nil?
        xml.id = Jabber::IdGenerator.instance.generate_id
      end

      res = nil
      error = nil
      send(xml) do |received|
        if received.kind_of? XMPPStanza and received.id == xml.id
          if received.type == :error
            error = (received.error ? received.error : ErrorResponse.new)
            true
          elsif block_given?
            res = yield(received)
            true
          else
            res = received
            true
          end
        else
          false
        end
      end

      unless error.nil?
        raise ServerError.new(error)
      end

      res
    end

    ##
    # Adds a callback block to process received XML messages
    #
    # priority:: [Integer] The callback's priority, the higher, the sooner
    # ref:: [String] The callback's reference
    # &block:: [Block] The optional block
    def add_xml_callback(priority = 0, ref = nil, &block)
      @xmlcbs.add(priority, ref, block)
    end

    ##
    # Delete an XML-messages callback
    #
    # ref:: [String] The reference of the callback to delete
    def delete_xml_callback(ref)
      @xmlcbs.delete(ref)
    end

    ##
    # Adds a callback block to process received Messages
    #
    # priority:: [Integer] The callback's priority, the higher, the sooner
    # ref:: [String] The callback's reference
    # &block:: [Block] The optional block
    def add_message_callback(priority = 0, ref = nil, &block)
      @messagecbs.add(priority, ref, block)
    end

    ##
    # Delete an Message callback
    #
    # ref:: [String] The reference of the callback to delete
    def delete_message_callback(ref)
      @messagecbs.delete(ref)
    end

    ##
    # Adds a callback block to process received Stanzas
    #
    # priority:: [Integer] The callback's priority, the higher, the sooner
    # ref:: [String] The callback's reference
    # &block:: [Block] The optional block
    def add_stanza_callback(priority = 0, ref = nil, &block)
      @stanzacbs.add(priority, ref, block)
    end

    ##
    # Delete a Stanza callback
    #
    # ref:: [String] The reference of the callback to delete
    def delete_stanza_callback(ref)
      @stanzacbs.delete(ref)
    end

    ##
    # Adds a callback block to process received Presences
    #
    # priority:: [Integer] The callback's priority, the higher, the sooner
    # ref:: [String] The callback's reference
    # &block:: [Block] The optional block
    def add_presence_callback(priority = 0, ref = nil, &block)
      @presencecbs.add(priority, ref, block)
    end

    ##
    # Delete a Presence callback
    #
    # ref:: [String] The reference of the callback to delete
    def delete_presence_callback(ref)
      @presencecbs.delete(ref)
    end

    ##
    # Adds a callback block to process received Iqs
    #
    # priority:: [Integer] The callback's priority, the higher, the sooner
    # ref:: [String] The callback's reference
    # &block:: [Block] The optional block
    def add_iq_callback(priority = 0, ref = nil, &block)
      @iqcbs.add(priority, ref, block)
    end

    ##
    # Delete an Iq callback
    #
    # ref:: [String] The reference of the callback to delete
    #
    def delete_iq_callback(ref)
      @iqcbs.delete(ref)
    end
    ##
    # Closes the connection to the Jabber service
    def close
      close!
    end

    def close!
      @parser_thread.kill if @parser_thread
      @fd.close if @fd and !@fd.closed?
      @status = DISCONNECTED
    end
  end
end
