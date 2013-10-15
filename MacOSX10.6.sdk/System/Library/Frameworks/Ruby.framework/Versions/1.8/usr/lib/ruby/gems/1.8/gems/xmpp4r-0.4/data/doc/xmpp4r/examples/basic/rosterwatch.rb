#!/usr/bin/ruby
#
# XMPP4R - XMPP Library for Ruby
# Copyright (C) 2005 Stephan Maka <stephan@spaceboyz.net>
# Released under Ruby's license (see the LICENSE file) or GPL, at your option
#
#
# Roster-Watch example
#
#
# Learn how a roster looks like
#       how presences are received
#       about subscription requests and answers
#       what vCards contain
#
# It's recommended to insert 'p' commands in this script. :-)
#
# This script does:
#
# * Listing roster changes
#
# * Subscribe to roster items which have a subscription of "none" or "from"
#   WARNING: Chances are that you don't want that :-)
#
# * Requesting vCards for unnamed items in your roster and renaming them
#   to the <NICKNAME/> or <FN/> field in the vCard
#
# * Listing presence changes
#
# * Listing subscription and unsubscription requests and answers

$:.unshift '../../../../../lib/'

require 'xmpp4r'
require 'xmpp4r/roster/helper/roster'
require 'xmpp4r/vcard/helper/vcard'

# Command line argument checking

if ARGV.size != 2
  puts("Usage: ./rosterwatch.rb <jid> <password>")
  exit
end

# Building up the connection

#Jabber::debug = true

jid = Jabber::JID.new(ARGV[0])

cl = Jabber::Client.new(jid)
cl.connect
cl.auth(ARGV[1])

# The roster instance
roster = Jabber::Roster::Helper.new(cl)

# Callback to handle updated roster items
roster.add_update_callback { |olditem,item|
  if [:from, :none].include?(item.subscription) && item.ask != :subscribe
    puts("Subscribing to #{item.jid}")
    item.subscribe
  end

  # Print the item
  if olditem.nil?
    # We didn't knew before:
    puts("#{item.iname} (#{item.jid}, #{item.subscription}) #{item.groups.join(', ')}")
  else
    # Showing whats different:
    puts("#{olditem.iname} (#{olditem.jid}, #{olditem.subscription}) #{olditem.groups.join(', ')} -> #{item.iname} (#{item.jid}, #{item.subscription}) #{item.groups.join(', ')}")
  end

  # If the item has no name associated...
  unless item.iname
    Thread.new do
      puts("#{item.jid} has no nickname... getting vCard")
      begin
        # ...get a vCard
        vcard = Jabber::Vcard::Helper.new(cl).get(item.jid.strip)

        unless vcard.nil?
          # Rename him to vCard's <NICKNAME/> field
          if vcard['NICKNAME']
            item.iname = vcard['NICKNAME']
            puts("Renaming #{item.jid} to #{vcard['NICKNAME']}")
            item.send
          # Rename him to vCard's <FN/> field
          elsif vcard['FN']
            item.iname = vcard['FN']
            puts("Renaming #{item.jid} to #{vcard['FN']}")
            item.send
          # We've got a lazy one
          else
            puts("#{item.jid} provided no details in vCard")
          end
        end

      rescue Exception => e
        # This will be (mostly) thrown by Jabber::Vcard::Helper#get
        puts("Error getting vCard for #{item.jid}: #{e.to_s}")
      end
    end
  end
}

# Presence updates:
roster.add_presence_callback { |item,oldpres,pres|
  # Can't look for something that just does not exist...
  if pres.nil?
    # ...so create it:
    pres = Jabber::Presence.new
  end
  if oldpres.nil?
    # ...so create it:
    oldpres = Jabber::Presence.new
  end

  # Print name and jid:
  name = "#{pres.from}"
  if item.iname
    name = "#{item.iname} (#{pres.from})"
  end
  puts(name)

  # Print type changes:
  unless oldpres.type.nil? && pres.type.nil?
    puts("  Type: #{oldpres.type.inspect} -> #{pres.type.inspect}")
  end
  # Print show changes:
  unless oldpres.show.nil? && pres.show.nil?
    puts("  Show:     #{oldpres.show.to_s.inspect} -> #{pres.show.to_s.inspect}")
  end
  # Print status changes:
  unless oldpres.status.nil? && pres.status.nil?
    puts("  Status:   #{oldpres.status.to_s.inspect} -> #{pres.status.to_s.inspect}")
  end
  # Print priority changes:
  unless oldpres.priority.nil? && pres.priority.nil?
    puts("  Priority: #{oldpres.priority.inspect} -> #{pres.priority.inspect}")
  end

  # Note: presences with type='error' will reflect our own show/status/priority
  # as it is mostly just a reply from a server. This is *not* a bug.
}

# Subscription requests and responses:
subscription_callback = lambda { |item,pres|
  name = pres.from
  if item != nil && item.iname != nil
    name = "#{item.iname} (#{pres.from})"
  end
  case pres.type
    when :subscribe then puts("Subscription request from #{name}")
    when :subscribed then puts("Subscribed to #{name}")
    when :unsubscribe then puts("Unsubscription request from #{name}")
    when :unsubscribed then puts("Unsubscribed from #{name}")
    else raise "The Roster Helper is buggy!!! subscription callback with type=#{pres.type}"
  end
}
roster.add_subscription_callback(0, nil, &subscription_callback)
roster.add_subscription_request_callback(0, nil, &subscription_callback)

# Send initial presence
# this is important for receiving presence of subscribed users
cl.send(Jabber::Presence.new.set_show(:dnd).set_status('Watching my roster change...'))

# Main loop:
Thread.stop

cl.close
