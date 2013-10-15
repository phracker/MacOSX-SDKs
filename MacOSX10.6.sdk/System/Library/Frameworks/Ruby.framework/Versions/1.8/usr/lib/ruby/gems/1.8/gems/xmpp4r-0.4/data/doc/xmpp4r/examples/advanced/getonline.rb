#!/usr/bin/ruby

# This script can get all roster entries

require 'optparse'
require 'xmpp4r'
include Jabber

get = true
jid = JID.new('lucastest@linux.ensimag.fr/rosterget')
password = 'lucastest'
domains = []

OptionParser.new do |opts|
  opts.banner = 'Usage: roster.rb -j jid -p password -d domain'
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
exit = false
nb = 0
cl.add_iq_callback { |i|
  fjid = JID.new(i.from)
  if i.type == :result and fjid.resource == "admin"
    domain = fjid.domain
    items = nil
    i.each_element('item') { |e| items = e }
    raise "items nil" if items.nil?
    puts "--- Online users for #{domain} (seconds, sent, received)"
    c = 0
    items.each_element('user') do |e|
      puts "#{e.attribute('jid')} #{e.attribute('name')}"
      c += 1
    end
    puts "--- #{domain} : #{c} online users"
    nb -= 1
  end
}
for d in domains do
  cl.send(Iq.new_browseget.set_to("#{d}/admin"))
  nb += 1
end
while nb > 0
  cl.process(1)
end
cl.close
