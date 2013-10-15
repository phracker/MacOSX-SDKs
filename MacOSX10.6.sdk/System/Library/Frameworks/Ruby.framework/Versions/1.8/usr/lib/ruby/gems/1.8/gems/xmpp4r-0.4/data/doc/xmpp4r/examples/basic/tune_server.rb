#!/usr/bin/env ruby

$:.unshift '../../../../../lib'

require 'xmpp4r'
require 'xmpp4r/roster'
require 'xmpp4r/tune'
require 'rbosa'

#
# Send XEP-0118 User Tune events...
#
# See Jabber::UserTune::Helper for the gory details...
#
# NB needs rbosa library to access iTunes - only on MacOSX
#

if ARGV.length != 2:
  puts "Usage: ruby tune_server.rb <jid> <pw>"
  exit 1
end

jid=ARGV[0]
pw=ARGV[1]

Jabber::debug=true

cl = Jabber::Client.new(jid)
cl.connect
cl.auth(pw)

# Following XEP-0163 PEP we need to
# ensure we have a 'both' subscription to the Tune client
roster = Jabber::Roster::Helper.new(cl)
roster.add_subscription_request_callback do |item,pres|
  roster.accept_subscription(pres.from)

  reply = pres.answer
  reply.type = :subscribe
  cl.send(reply)
end

cl.send(Jabber::Presence.new.set_show(:chat))

t=Jabber::UserTune::Helper.new(cl, nil)

itunes=OSA.app('iTunes')

loop do
  track = itunes.current_track

  if track
    puts "Now playing: #{track.name} by #{track.artist}"
    t.now_playing(Jabber::UserTune::Tune.new(track.artist, track.name))
  end

  sleep 5
end
