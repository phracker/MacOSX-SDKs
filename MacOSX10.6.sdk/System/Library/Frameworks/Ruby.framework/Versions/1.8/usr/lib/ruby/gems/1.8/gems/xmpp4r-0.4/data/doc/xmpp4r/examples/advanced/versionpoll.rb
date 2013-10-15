#!/usr/bin/ruby

# This script will request the version information of a list of JID given
# on stdin.

$:.unshift '../../../../../lib'

require 'optparse'
require 'xmpp4r/client'
require 'xmpp4r/version/iq/version'
include Jabber
#Jabber::debug = true

# settings
jid = JID.new('bot@localhost/Bot')
password = 'bot'
domains = []
OptionParser.new do |opts|
  opts.banner = 'Usage: versionpoll.rb -j jid -p password -d DOMAINS'
  opts.separator ''
  opts.on('-j', '--jid JID', 'sets the jid') { |j| jid = JID.new(j) }
  opts.on('-p', '--password PASSWORD', 'sets the password') { |p| password = p }
  opts.on('-d', '--domain DOMAIN', 'sets the domain') { |d| domains << d }
  opts.on_tail('-h', '--help', 'Show this message') {
    puts opts
    exit
  }
  opts.parse!(ARGV)
end

cl = Client.new(jid)
cl.connect
cl.auth(password)
sent = []
queried = []
activity = false
cl.add_iq_callback do |i|
  fjid = JID.new(i.from)
  if i.type == :result and fjid.resource == "admin"
    domain = fjid.domain
    items = i.first_element('item')
    raise "items nil" if items.nil?
    items.each_element('user') do |e|
      j = e.attribute('jid')
      if not queried.include?(j)
        activity = true
        queried << j
        cl.send(Iq.new_browseget.set_to(j))
      end
    end
  end
end

cl.add_iq_callback do |i|
  if i.type == :result
    u = i.first_element('user')
    if u
      u.each_element('user') do |e|
        if (a = e.attribute('type'))
          if a.value == 'client'
            activity = true
            iq = Iq.new(:get)
            iq.query = Version::IqQueryVersion.new
            iq.set_to(JID.new(e.attribute('jid').to_s))
            cl.send(iq)
          end
        end
      end
    end
  end
end
cl.add_iq_callback do |iq|
  if iq.type == :result and iq.query.class == Version::IqQueryVersion
    activity = true
    r = [ iq.from.to_s, iq.query.iname, iq.query.version, iq.query.os ]
    puts r.inspect
  end
end
cl.send(Presence.new)
for d in domains do
  cl.send(Iq.new_browseget.set_to("#{d}/admin"))
end

activity = true
while activity
  activity = false
  # other threads might set activity to true
  sleep 10
end
cl.close
