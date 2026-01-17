# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/callbacks'
require 'thread'
require 'xmpp4r/roster/iq/roster'

module Jabber
  module Roster
    ##
    # The Roster helper intercepts <tt><iq/></tt> stanzas with Jabber::IqQueryRoster
    # and <tt><presence/></tt> stanzas, but provides cbs which allow the programmer
    # to keep track of updates.
    #
    # A thread for any received stanza is spawned, so the user can invoke
    # accept_subscription et al in the callback blocks, without stopping
    # the current (= parser) thread when waiting for a reply.
    class Helper
      ##
      # All items in your roster
      # items:: [Hash] ([JID] => [Roster::Helper::RosterItem])
      attr_reader :items

      ##
      # Initialize a new Roster helper
      #
      # Registers its cbs (prio = 120, ref = self)
      #
      # Request a roster
      # (Remember to send initial presence afterwards!)
      #
      # The initialization will not wait for the roster being received,
      # use wait_for_roster.
      #
      # <b>Attention:</b> If you send presence and receive presences
      # before the roster has arrived, the Roster helper will let them
      # pass through and does *not* keep them!
      def initialize(stream)
        @stream = stream
        @items = {}
        @items_lock = Mutex.new
        @roster_wait = Semaphore.new
        @query_cbs = CallbackList.new
        @update_cbs = CallbackList.new
        @presence_cbs = CallbackList.new
        @subscription_cbs = CallbackList.new
        @subscription_request_cbs = CallbackList.new

        # Register cbs
        stream.add_iq_callback(120, self) { |iq|
          if iq.query.kind_of?(IqQueryRoster)
            Thread.new do
              Thread.current.abort_on_exception = true
              handle_iq_query_roster(iq)
            end

            true
          else
            false
          end
        }
        stream.add_presence_callback(120, self) { |pres|
          Thread.new do
            Thread.current.abort_on_exception = true
            handle_presence(pres)
          end
        }

        # Request the roster
        rosterget = Iq.new_rosterget
        stream.send(rosterget)
      end

      ##
      # Wait for first roster query result to arrive
      def wait_for_roster
        @roster_wait.wait
        @roster_wait.run
      end

      ##
      # Add a callback to be called when a query has been processed
      #
      # Because update callbacks are called for each roster item,
      # this may be appropriate to notify that *anything* has updated.
      #
      # Arguments for callback block: The received <tt><iq/></tt> stanza
      def add_query_callback(prio = 0, ref = nil, &block)
        @query_cbs.add(prio, ref, block)
      end

      ##
      # Add a callback for Jabber::Roster::Helper::RosterItem updates
      #
      # Note that this will be called much after initialization
      # for the answer of the initial roster request
      #
      # The block receives two objects:
      # * the old Jabber::Roster::Helper::RosterItem
      # * the new Jabber::Roster::Helper::RosterItem
      def add_update_callback(prio = 0, ref = nil, &block)
        @update_cbs.add(prio, ref, block)
      end

      ##
      # Add a callback for Jabber::Presence updates
      #
      # This will be called for <tt><presence/></tt> stanzas for known RosterItems.
      # Unknown JIDs may still pass and can be caught via Jabber::Stream#add_presence_callback.
      #
      # The block receives three objects:
      # * the Jabber::Roster::Helper::RosterItem
      # * the old Jabber::Presence (or nil)
      # * the new Jabber::Presence (or nil)
      def add_presence_callback(prio = 0, ref = nil, &block)
        @presence_cbs.add(prio, ref, block)
      end

      ##
      # Add a callback for subscription updates,
      # which will be called upon receiving a <tt><presence/></tt> stanza
      # with type:
      # * :subscribed
      # * :unsubscribe
      # * :unsubscribed
      #
      # The block receives two objects:
      # * the Jabber::Roster::Helper::RosterItem (or nil)
      # * the <tt><presence/></tt> stanza
      def add_subscription_callback(prio = 0, ref = nil, &block)
        @subscription_cbs.add(prio, ref, block)
      end

      ##
      # Add a callback for subscription requests,
      # which will be called upon receiving a <tt><presence type='subscribe'/></tt> stanza
      #
      # The block receives two objects:
      # * the Jabber::Roster::Helper::RosterItem (or nil)
      # * the <tt><presence/></tt> stanza
      #
      # Response to this event can be taken with accept_subscription
      # and decline_subscription.
      #
      # Example usage:
      #  my_roster.add_subscription_request_callback do |item,presence|
      #    if accept_subscription_requests
      #      my_roster.accept_subscription(presence.from)
      #    else
      #      my_roster.decline_subscription(presence.from)
      #    end
      #  end
      def add_subscription_request_callback(prio = 0, ref = nil, &block)
        @subscription_request_cbs.add(prio, ref, block)
      end

      private

      ##
      # Handle received <tt><iq/></tt> stanzas,
      # used internally
      def handle_iq_query_roster(iq)
        # If the <iq/> contains <error/> we just ignore that
        # and assume an empty roster
        iq.query.each_element('item') do |item|
          olditem, newitem = nil, nil

          @items_lock.synchronize {
            olditem = @items[item.jid]

            # Handle deletion of item
            if item.subscription == :remove
              @items.delete(item.jid)
            else
              newitem = @items[item.jid] = RosterItem.new(@stream).import(item)
            end
          }
          @update_cbs.process(olditem, newitem)
        end

        @roster_wait.run
        @query_cbs.process(iq)
      end

      ##
      # Handle received <tt><presence/></tt> stanzas,
      # used internally
      def handle_presence(pres)
        item = self[pres.from]

        if [:subscribed, :unsubscribe, :unsubscribed].include?(pres.type)
          @subscription_cbs.process(item, pres)
          true

        elsif pres.type == :subscribe
          @subscription_request_cbs.process(item, pres)
          true

        else
          unless item.nil?
            update_presence(item, pres)
            true  # Callback consumed stanza
          else
            false # Callback did not consume stanza
          end
        end
      end

      ##
      # Update the presence of an item,
      # used internally
      #
      # Callbacks are called here
      def update_presence(item, pres)

        # This requires special handling, to announce all resources offline
        if pres.from.resource.nil? and pres.type == :error
          oldpresences = []
          item.each_presence do |oldpres|
            oldpresences << oldpres
          end

          item.add_presence(pres)
          oldpresences.each { |oldpres|
            @presence_cbs.process(item, oldpres, pres)
          }
        else
          oldpres = item.presence(pres.from).nil? ?
            nil :
            Presence.new.import(item.presence(pres.from))

          item.add_presence(pres)
          @presence_cbs.process(item, oldpres, pres)
        end
      end

      public

      ##
      # Get an item by jid
      #
      # If not available tries to look for it with the resource stripped
      def [](jid)
        jid = JID.new(jid) unless jid.kind_of? JID

        @items_lock.synchronize {
          if @items.has_key?(jid)
            @items[jid]
          elsif @items.has_key?(jid.strip)
            @items[jid.strip]
          else
            nil
          end
        }
      end

      ##
      # Returns the list of RosterItems which, stripped, are equal to the
      # one you are looking for.
      def find(jid)
        jid = JID.new(jid) unless jid.kind_of? JID

        j = jid.strip
        l = {}
        @items_lock.synchronize {
          @items.each_pair do |k, v|
            l[k] = v if k.strip == j
          end
        }
        l
      end

      ##
      # Groups in this Roster,
      # sorted by name
      #
      # Contains +nil+ if there are ungrouped items
      # result:: [Array] containing group names (String)
      def groups
        res = []
        @items_lock.synchronize {
          @items.each_pair do |jid,item|
            res += item.groups
            res += [nil] if item.groups == []
          end
        }
        res.uniq.sort { |a,b| a.to_s <=> b.to_s }
      end

      ##
      # Get items in a group
      #
      # When group is nil, return ungrouped items
      # group:: [String] Group name
      # result:: Array of [RosterItem]
      def find_by_group(group)
        res = []
        @items_lock.synchronize {
          @items.each_pair do |jid,item|
            res.push(item) if item.groups.include?(group)
            res.push(item) if item.groups == [] and group.nil?
          end
        }
        res
      end

      ##
      # Add a user to your roster
      #
      # Threading is encouraged as the function waits for
      # a result. ServerError is thrown upon error.
      #
      # See Jabber::Roster::Helper::RosterItem#subscribe for details
      # about subscribing. (This method isn't used here but the
      # same functionality applies.)
      #
      # If the item is already in the local roster
      # it will simply send itself
      # jid:: [JID] to add
      # iname:: [String] Optional item name
      # subscribe:: [Boolean] Whether to subscribe to this jid
      def add(jid, iname=nil, subscribe=false)
        if self[jid]
          self[jid].send
        else
          request = Iq.new_rosterset
          request.query.add(Jabber::Roster::RosterItem.new(jid, iname))
          @stream.send_with_id(request)
          # Adding to list is handled by handle_iq_query_roster
        end

        if subscribe
          # Actually the item *should* already be known now,
          # but we do it manually to exclude conditions.
          pres = Presence.new.set_type(:subscribe).set_to(jid.strip)
          @stream.send(pres)
        end
      end

      ##
      # Accept a subscription request
      # * Sends a <presence type='subscribed'/> stanza
      # * Adds the contact to your roster
      # jid:: [JID] of contact
      # iname:: [String] Optional roster item name
      def accept_subscription(jid, iname=nil)
        pres = Presence.new.set_type(:subscribed).set_to(jid.strip)
        @stream.send(pres)

        unless self[jid.strip]
          request = Iq.new_rosterset
          request.query.add(Jabber::Roster::RosterItem.new(jid.strip, iname))
          @stream.send_with_id(request)
        end
      end

      ##
      # Decline a subscription request
      # * Sends a <presence type='unsubscribed'/> stanza
      def decline_subscription(jid)
        pres = Presence.new.set_type(:unsubscribed).set_to(jid.strip)
        @stream.send(pres)
      end

      ##
      # These are extensions to RosterItem to carry presence information.
      # This information is *not* stored in XML!
      class RosterItem < Jabber::Roster::RosterItem
        ##
        # Tracked (online) presences of this RosterItem
        attr_reader :presences

        ##
        # Initialize an empty RosterItem
        def initialize(stream)
          super()
          @stream = stream
          @presences = []
          @presences_lock = Mutex.new
        end

        ##
        # Send the updated RosterItem to the server,
        # i.e. if you modified iname, groups, ...
        def send
          request = Iq.new_rosterset
          request.query.add(self)
          @stream.send(request)
        end

        ##
        # Remove item
        #
        # This cancels both subscription *from* the contact to you
        # and from you *to* the contact.
        #
        # The methods waits for a roster push from the server (success)
        # or throws ServerError upon failure.
        def remove
          request = Iq.new_rosterset
          request.query.add(Jabber::Roster::RosterItem.new(jid, nil, :remove))
          @stream.send_with_id(request)
          # Removing from list is handled by Roster#handle_iq_query_roster
        end

        ##
        # Is any presence of this person on-line?
        #
        # (Or is there any presence? Unavailable presences are
        # deleted.)
        def online?
          @presences_lock.synchronize {
            @presences.select { |pres|
              pres.type.nil?
            }.size > 0
          }
        end

        ##
        # Iterate through all received <tt><presence/></tt> stanzas
        def each_presence(&block)
          # Don't lock here, we don't know what block does...
          @presences.each { |pres|
            yield(pres)
          }
        end

        ##
        # Get specific presence
        # jid:: [JID] Full JID
        def presence(jid)
          @presences_lock.synchronize {
            @presences.each { |pres|
              return(pres) if pres.from == jid
            }
          }
          nil
        end

        ##
        # Add presence and sort presences
        # (unless type is :unavailable or :error)
        #
        # This overwrites previous stanzas with the same destination
        # JID to keep track of resources. Presence stanzas with
        # <tt>type == :unavailable</tt> or <tt>type == :error</tt> will
        # be deleted as this indicates that this resource has gone
        # offline.
        #
        # If <tt>type == :error</tt> and the presence's origin has no
        # specific resource the contact is treated completely offline.
        def add_presence(newpres)
          @presences_lock.synchronize {
            # Delete old presences with the same JID
            @presences.delete_if do |pres|
              pres.from == newpres.from or pres.from.resource.nil?
            end

            if newpres.type == :error and newpres.from.resource.nil?
              # Replace by single error presence
              @presences = [newpres]
            else
              # Add new presence
              @presences.push(newpres)
            end

            @presences.sort!
          }
        end

        ##
        # Send subscription request to the user
        #
        # The block given to Jabber::Roster::Roster#add_update_callback will
        # be called, carrying the RosterItem with ask="subscribe"
        #
        # This function returns immediately after sending the subscription
        # request and will not wait of approval or declination as it may
        # take months for the contact to decide. ;-)
        def subscribe
          pres = Presence.new.set_type(:subscribe).set_to(jid.strip)
          @stream.send(pres)
        end

        ##
        # Unsubscribe from a contact's presence
        #
        # This method waits for a presence with type='unsubscribed'
        # from the contact. It may throw ServerError upon failure.
        #
        # subscription attribute of the item is *from* or *none*
        # afterwards. As long as you don't remove that item and
        # subscription='from' the contact is subscribed to your
        # presence.
        def unsubscribe
          pres = Presence.new.set_type(:unsubscribe).set_to(jid.strip)
          @stream.send(pres) { |answer|
            answer.type == :unsubscribed and
            answer.from.strip == pres.to
          }
        end

        ##
        # Deny the contact to see your presence.
        #
        # This method will not wait and returns immediately
        # as you will need no confirmation for this action.
        #
        # Though, you will get a roster update for that item,
        # carrying either subscription='to' or 'none'.
        def cancel_subscription
          pres = Presence.new.set_type(:unsubscribed).set_to(jid)
          @stream.send(pres)
        end
      end
    end #Class Roster
  end #Module Roster
end #Module Jabber
