#!/usr/bin/env ruby

$:.unshift '../../../../../lib'

require 'xmpp4r'
require 'xmpp4r/muc/helper/mucbrowser'

if ARGV.size != 3
  puts "Usage: #{$0} <jid> <password> <muc-jid>"
  exit
end

jid, password, muc_jid = Jabber::JID.new(ARGV.shift), ARGV.shift, Jabber::JID.new(ARGV.shift)

cl = Jabber::Client.new(jid)
cl.connect
cl.auth(password)

browser = Jabber::MUC::MUCBrowser.new(cl)

print "Querying #{muc_jid} for identity..."; $stdout.flush
name = browser.muc_name(muc_jid)

if name.nil?
  puts " Sorry, but the queried MUC component doesn't seem to support MUC or Groupchat."
else
  puts " #{name}"

  print "Querying #{muc_jid} for its rooms..."; $stdout.flush
  rooms = browser.muc_rooms(muc_jid)
  puts " #{rooms.size} rooms found"

  max_room_length = 0
  rooms.each_key { |jid| max_room_length = jid.to_s.size if jid.to_s.size > max_room_length }

  rooms.each { |jid,name|
    puts "#{jid.to_s.ljust(max_room_length)} #{name}"
  }
end

cl.close
