#!/usr/bin/env ruby

$:.unshift '../../../../../lib'

require 'xmpp4r'
require 'xmpp4r/roster'
require 'xmpp4r/discovery'
require 'xmpp4r/caps'
require 'xmpp4r/tune'


#
# Echo tunes received via XEP-0118 User Tune notifications
#
# See Jabber::UserTune::Helper for the gory details
#

if ARGV.length != 3
  puts "Usage: ruby tune_client.rb <jid> <pw> <tune-playing-jid>"
  exit 1
end

jid = ARGV[0]
pw = ARGV[1]
dj_jid = ARGV[2]

#Jabber::debug=true
cl = Jabber::Client.new(Jabber::JID.new(jid))
cl.connect
cl.auth(pw)

# PEP (XEP-0163 says we need:
# - a 'both' subscription to the dj
# - told the server that we support the '...tune+notify' feature
# before we can receive events
roster = Jabber::Roster::Helper.new(cl)
roster.add_subscription_request_callback(0, nil) do |item,pres|
  roster.accept_subscription(pres.from)
end

caps = Jabber::Caps::Helper.new(cl,
  [Jabber::Discovery::Identity.new('client', nil, 'pc')],
  [Jabber::Discovery::Feature.new('http://jabber.org/protocol/tune+notify')]
)

t = Jabber::UserTune::Helper.new(cl, dj_jid)
t.add_usertune_callback do |tune|
  puts "from:#{dj_jid} tune:#{tune.artist} plays #{tune.title}"
end

p = Jabber::Presence.new()
p.type = :subscribe
p.to = dj_jid
cl.send p

Thread.stop
