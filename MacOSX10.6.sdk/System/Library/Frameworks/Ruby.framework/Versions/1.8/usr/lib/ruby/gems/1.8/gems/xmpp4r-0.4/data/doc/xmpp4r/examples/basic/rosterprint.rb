#!/usr/bin/ruby

$:.unshift '../../../../../lib/'

require 'xmpp4r'
require 'xmpp4r/roster/helper/roster'

# Command line argument checking

if ARGV.size != 2
  puts("Usage: ./rosterprint.rb <jid> <password>")
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

mainthread = Thread.current

roster.add_query_callback { |iq|
  mainthread.wakeup
}

Thread.stop

roster.groups.each { |group|
  if group.nil?
    puts "*** Ungrouped ***"
  else
    puts "*** #{group} ***"
  end

  roster.find_by_group(group).each { |item|
    puts "- #{item.iname} (#{item.jid})"
  }

  print "\n"
}

cl.close
