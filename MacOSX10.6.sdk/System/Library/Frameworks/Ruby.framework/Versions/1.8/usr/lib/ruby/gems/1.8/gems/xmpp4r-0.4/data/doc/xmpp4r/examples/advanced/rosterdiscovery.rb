#!/usr/bin/ruby
#
# XMPP4R - XMPP Library for Ruby
# Copyright (C) 2005 Stephan Maka <stephan@spaceboyz.net>
# Released under Ruby's license (see the LICENSE file) or GPL, at your option
#
#
# Roster-Discovery example
#
# If you don't understand this code read JEP-0030 (Service Discovery) first:
# http://www.jabber.org/jeps/jep-0030.html
#
# This examples exposes your roster to Service Discovery and can be browsed
# by anyone. Please use with care if you want to keep your roster private!
#
# The Psi client has a very pretty Service Discovery dialog. But be sure
# to turn off "Auto-browse into objects" for big rosters.
#

$:.unshift '../../../../../lib'

require 'thread'

require 'xmpp4r'
require 'xmpp4r/helpers/roster'
require 'xmpp4r/iq/query/discoinfo'
require 'xmpp4r/iq/query/discoitems'

# Command line argument checking

if ARGV.size != 2
  puts("Usage: ./rosterdiscovery.rb <jid> <password>")
  exit
end

# Building up the connection

#Jabber::debug = true

jid = Jabber::JID.new(ARGV[0])

cl = Jabber::Client.new(jid)
cl.connect
cl.auth(ARGV[1])


# The roster instance
roster = Jabber::Helpers::Roster.new(cl)


cl.add_iq_callback { |iq|
  if iq.query.kind_of?(Jabber::IqQueryDiscoInfo) || iq.query.kind_of?(Jabber::IqQueryDiscoItems)

    # Prepare the <iq/> stanza for result
    iq.from, iq.to = iq.to, iq.from
    iq.type = :result


    if iq.query.kind_of?(Jabber::IqQueryDiscoInfo)
      # iq.to and iq.from are already switched here:
      puts("#{iq.to} requests info of #{iq.from} node #{iq.query.node.inspect}")

      if iq.query.node.nil?
        iq.query.add(Jabber::DiscoIdentity.new('directory', 'Roster discovery', 'user'))
      else
        # Count contacts in group
        in_group = 0
        roster.items.each { |jid,item|
          if item.groups.include?(iq.query.node)
            in_group += 1
          end
        }

        iq.query.add(Jabber::DiscoIdentity.new('directory', "#{iq.query.node} (#{in_group})", 'group'))
      end

      iq.query.add(Jabber::DiscoFeature.new(Jabber::IqQueryDiscoInfo.new.namespace))
      iq.query.add(Jabber::DiscoFeature.new(Jabber::IqQueryDiscoItems.new.namespace))

    elsif iq.query.kind_of?(Jabber::IqQueryDiscoItems)
      # iq.to and iq.from are already switched here:
      puts("#{iq.to} requests items of #{iq.from} node #{iq.query.node.inspect}")

      if iq.query.node.nil?
        # Make items from group names
        groups = []

        roster.items.each { |jid,item|
          groups += item.groups
        }

        groups.uniq.each { |group|
          iq.query.add(Jabber::DiscoItem.new(cl.jid, group, group))
        }

        # Collect all ungrouped roster items
        roster.items.each { |jid,item|
          if item.groups == []
            iq.query.add(Jabber::DiscoItem.new(item.jid, item.iname.to_s == '' ? item.jid : item.iname))
          end
        }
      else
        # Add a discovery item for each roster item in that group
        roster.items.each { |jid,item|
          if item.groups.include?(iq.query.node)
            iq.query.add(Jabber::DiscoItem.new(item.jid, item.iname.to_s == '' ? item.jid : item.iname))
          end
        }
      end

    end

    cl.send(iq)

    true
  end
}

# Initial presence
cl.send(Jabber::Presence.new.set_status("Discover my roster at #{jid}"))

# Main loop:

loop do
  cl.process
  Thread.stop
end

cl.close
