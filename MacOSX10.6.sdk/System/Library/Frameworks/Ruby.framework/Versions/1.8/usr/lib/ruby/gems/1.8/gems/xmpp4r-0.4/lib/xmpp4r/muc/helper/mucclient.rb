# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/muc/x/muc'
require 'xmpp4r/muc/iq/mucowner'
require 'xmpp4r/muc/iq/mucadmin'
require 'xmpp4r/dataforms'

module Jabber
  module MUC
    ##
    # The MUCClient Helper handles low-level stuff of the
    # Multi-User Chat (JEP 0045).
    #
    # Use one instance per room.
    #
    # Note that one client cannot join a single room multiple
    # times. At least the clients' resources must be different.
    # This is a protocol design issue. But don't consider it as
    # a bug, it is just a clone-preventing feature.
    class MUCClient
      ##
      # Sender JID, set this to use MUCClient from Components
      # my_jid:: [JID] Defaults to nil
      attr_accessor :my_jid

      ##
      # MUC room roster
      # roster:: [Hash] of [String] Nick => [Presence]
      attr_reader :roster

      ##
      # MUC JID
      # jid:: [JID] room@component/nick
      attr_reader :jid

      ##
      # Initialize a MUCClient
      #
      # Call MUCClient#join *after* you have registered your
      # callbacks to avoid reception of stanzas after joining
      # and before registration of callbacks.
      # stream:: [Stream] to operate on
      def initialize(stream)
        # Attributes initialization
        @stream = stream
        @my_jid = nil
        @jid = nil
        @roster = {}
        @roster_lock = Mutex.new

        @active = false

        @join_cbs = CallbackList.new
        @leave_cbs = CallbackList.new
        @presence_cbs = CallbackList.new
        @message_cbs = CallbackList.new
        @private_message_cbs = CallbackList.new
      end

      ##
      # Join a room
      #
      # This registers its own callbacks on the stream
      # provided to initialize and sends initial presence
      # to the room. May throw ServerError if joining
      # fails.
      # jid:: [JID] room@component/nick
      # password:: [String] Optional password
      # return:: [MUCClient] self (chain-able)
      def join(jid, password=nil)
        if active?
          raise "MUCClient already active"
        end

        @jid = (jid.kind_of?(JID) ? jid : JID.new(jid))
        activate

        # Joining
        pres = Presence.new
        pres.to = @jid
        pres.from = @my_jid
        xmuc = XMUC.new
        xmuc.password = password
        pres.add(xmuc)

        # We don't use Stream#send_with_id here as it's unknown
        # if the MUC component *always* uses our stanza id.
        error = nil
        @stream.send(pres) { |r|
          if from_room?(r.from) and r.kind_of?(Presence) and r.type == :error
            # Error from room
            error = r.error
            true
          # type='unavailable' may occur when the MUC kills our previous instance,
          # but all join-failures should be type='error'
          elsif r.from == jid and r.kind_of?(Presence) and r.type != :unavailable
            # Our own presence reflected back - success
            if r.x(XMUCUser) and (i = r.x(XMUCUser).items.first)
              @affiliation = i.affiliation  # we're interested in if it's :owner
              @role = i.role                # :moderator ?
            end

            handle_presence(r, false)
            true
          else
            # Everything else
            false
          end
        }

        if error
          deactivate
          raise ServerError.new(error)
        end

        self
      end

      ##
      # Exit the room
      #
      # * Sends presence with type='unavailable' with an optional
      #   reason in <tt><status/></tt>,
      # * then waits for a reply from the MUC component (will be
      #   processed by leave-callbacks),
      # * then deletes callbacks from the stream.
      # reason:: [String] Optional custom exit message
      def exit(reason=nil)
        unless active?
          raise "MUCClient hasn't yet joined"
        end

        pres = Presence.new
        pres.type = :unavailable
        pres.to = jid
        pres.from = @my_jid
        pres.status = reason if reason
        @stream.send(pres) { |r|
          Jabber::debuglog "exit: #{r.to_s.inspect}"
          if r.kind_of?(Presence) and r.type == :unavailable and r.from == jid
            @leave_cbs.process(r)
            true
          else
            false
          end
        }

        deactivate

        self
      end

      ##
      # Is the MUC client active?
      #
      # This is false after initialization,
      # true after joining and
      # false after exit/kick
      def active?
        @active
      end

      ##
      # The MUCClient's own nick
      # (= resource)
      # result:: [String] Nickname
      def nick
        @jid ? @jid.resource : nil
      end

      ##
      # Change nick
      #
      # Threading is, again, suggested. This method waits for two
      # <presence/> stanzas, one indicating unavailabilty of the old
      # transient JID, one indicating availability of the new
      # transient JID.
      #
      # If the service denies nick-change, ServerError will be raised.
      def nick=(new_nick)
        unless active?
          raise "MUCClient not active"
        end

        new_jid = JID.new(@jid.node, @jid.domain, new_nick)

        # Joining
        pres = Presence.new
        pres.to = new_jid
        pres.from = @my_jid

        error = nil
        # Keeping track of the two stanzas enables us to process stanzas
        # which don't arrive in the order specified by JEP-0045
        presence_unavailable = false
        presence_available = false
        # We don't use Stream#send_with_id here as it's unknown
        # if the MUC component *always* uses our stanza id.
        @stream.send(pres) { |r|
          if from_room?(r.from) and r.kind_of?(Presence) and r.type == :error
            # Error from room
            error = r.error
          elsif r.from == @jid and r.kind_of?(Presence) and r.type == :unavailable and
                r.x and r.x.kind_of?(XMUCUser) and r.x.status_code == 303
            # Old JID is offline, but wait for the new JID and let stanza be handled
            # by the standard callback
            presence_unavailable = true
            handle_presence(r)
          elsif r.from == new_jid and r.kind_of?(Presence) and r.type != :unavailable
            # Our own presence reflected back - success
            presence_available = true
            handle_presence(r)
          end

          if error or (presence_available and presence_unavailable)
            true
          else
            false
          end
        }

        if error
          raise ServerError.new(error)
        end

        # Apply new JID
        @jid = new_jid
      end

      ##
      # The room name
      # (= node)
      # result:: [String] Room name
      def room
        @jid ? @jid.node : nil
      end

      ##
      # Send a stanza to the room
      #
      # If stanza is a Jabber::Message, <tt>stanza.type</tt> will be
      # automatically set to :groupchat if directed to room or :chat
      # if directed to participant.
      # stanza:: [XMPPStanza] to send
      # to:: [String] Stanza destination recipient, or room if +nil+
      def send(stanza, to=nil)
        if stanza.kind_of? Message
          stanza.type = to ? :chat : :groupchat
        end
        stanza.from = @my_jid
        stanza.to = JID.new(jid.node, jid.domain, to)
        @stream.send(stanza)
      end

      ##
      # Add a callback for <presence/> stanzas indicating availability
      # of a MUC participant
      #
      # This callback will *not* be called for initial presences when
      # a client joins a room, but only for the presences afterwards.
      #
      # The callback will be called from MUCClient#handle_presence with
      # one argument: the <presence/> stanza.
      # Note that this stanza will have been already inserted into
      # MUCClient#roster.
      def add_join_callback(prio = 0, ref = nil, &block)
        @join_cbs.add(prio, ref, block)
      end

      ##
      # Add a callback for <presence/> stanzas indicating unavailability
      # of a MUC participant
      #
      # The callback will be called with one argument: the <presence/> stanza.
      #
      # Note that this is called just *before* the stanza is removed from
      # MUCClient#roster, so it is still possible to see the last presence
      # in the given block.
      #
      # If the presence's origin is your MUC JID, the MUCClient will be
      # deactivated *afterwards*.
      def add_leave_callback(prio = 0, ref = nil, &block)
        @leave_cbs.add(prio, ref, block)
      end

      ##
      # Add a callback for a <presence/> stanza which is neither a join
      # nor a leave. This will be called when a room participant simply
      # changes his status.
      def add_presence_callback(prio = 0, ref = nil, &block)
        @presence_cbs.add(prio, ref, block)
      end

      ##
      # Add a callback for <message/> stanza directed to the whole room.
      #
      # See MUCClient#add_private_message_callback for private messages
      # between MUC participants.
      def add_message_callback(prio = 0, ref = nil, &block)
        @message_cbs.add(prio, ref, block)
      end

      ##
      # Add a callback for <message/> stanza with type='chat'.
      #
      # These stanza are normally not broadcasted to all room occupants
      # but are some sort of private messaging.
      def add_private_message_callback(prio = 0, ref = nil, &block)
        @private_message_cbs.add(prio, ref, block)
      end

      ##
      # Does this JID belong to that room?
      # jid:: [JID]
      # result:: [true] or [false]
      def from_room?(jid)
        @jid.strip == jid.strip
      end

      private

      ##
      # call_join_cbs:: [Bool] Do not call them if we receive initial presences from room
      def handle_presence(pres, call_join_cbs=true) # :nodoc:
        if pres.type == :unavailable or pres.type == :error
          @leave_cbs.process(pres)
          @roster_lock.synchronize {
            @roster.delete(pres.from.resource)
          }

          if pres.from == jid and !(pres.x and pres.x.kind_of?(XMUCUser) and pres.x.status_code == 303)
            deactivate
          end
        else
          is_join = ! @roster.has_key?(pres.from.resource)
          @roster_lock.synchronize {
            @roster[pres.from.resource] = pres
          }
          if is_join
            @join_cbs.process(pres) if call_join_cbs
          else
            @presence_cbs.process(pres)
          end
        end
      end

      def handle_message(msg) # :nodoc:
        if msg.type == :chat
          @private_message_cbs.process(msg)
        else  # type == :groupchat or anything else
          @message_cbs.process(msg)
        end
      end

      def activate  # :nodoc:
        @active = true

        # Callbacks
        @stream.add_presence_callback(150, self) { |presence|
          if from_room?(presence.from)
            handle_presence(presence)
            true
          else
            false
          end
        }

        @stream.add_message_callback(150, self) { |message|
          if from_room?(message.from)
            handle_message(message)
            true
          else
            false
          end
        }
      end

      def deactivate  # :nodoc:
        @active = false
        @jid = nil

        # Callbacks
        @stream.delete_presence_callback(self)
        @stream.delete_message_callback(self)
      end

    public
      def owner?
        @affiliation == :owner
      end

      ##
      # Use this method to configure a MUC room of which you are the owner.
      #
      # options:: [Hash] where keys are the features of the room you wish
      # to configure. See http://www.xmpp.org/extensions/xep-0045.html#registrar-formtype-owner
      def configure(options={})
        get_room_configuration
        submit_room_configuration(options)
      end

      def get_room_configuration
        raise 'You are not the owner' unless owner?

        iq = Iq.new(:get, jid.strip)
        iq.from = my_jid
        iq.add(IqQueryMUCOwner.new)

        fields = []

        @stream.send_with_id(iq) do |answer|
          raise "Configuration not possible for this room" unless answer.query && answer.query.x(Dataforms::XData)

          answer.query.x(Dataforms::XData).fields.each do |field|
            if (var = field.attributes['var'])
              fields << var
            end
          end
        end

        fields
      end

      def submit_room_configuration(options)
        # fill out the reply form
        iq = Iq.new(:set, jid.strip)
        iq.from = my_jid
        query = IqQueryMUCOwner.new
        form = Dataforms::XData.new
        form.type = :submit
        options.each do |var, values|
          field = Dataforms::XDataField.new
          values = [values] unless values.is_a?(Array)
          field.var, field.values = var, values
          form.add(field)
        end
        query.add(form)
        iq.add(query)

        @stream.send_with_id(iq)
      end

      ##
      # Push a list of new affiliations to the room
      # items:: [Array] of, or single [IqQueryMUCAdminItem]
      def send_affiliations(items)
        iq = Iq.new(:set, jid.strip)
        iq.from = my_jid
        iq.add(IqQueryMUCAdmin.new)

        items = [item] unless items.kind_of? Array
        items.each { |item|
          iq.query.add(item)
        }

        @stream.send_with_id(iq)
      end
    end
  end
end
