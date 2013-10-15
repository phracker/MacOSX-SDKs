#!/usr/bin/ruby

# This script will send a jabber message to the specified JID. The subject can be
# specified using the '-s' option, and the message will be taken from stdin.

$:.unshift '../../../../../lib'

require 'optparse'
require 'xmpp4r'
include Jabber

# settings
myJID = JID.new('bot@localhost/Bot')
myPassword = 'bot'

to = nil
subject = ''
OptionParser.new do |opts|
  opts.banner = 'Usage: jabbersend.rb -s \'subject\' -t dest@domain'
  opts.separator ''
  opts.on('-s', '--subject SUBJECT', 'sets the message\'s subject') { |s| subject = s }
  opts.on('-t', '--to DESTJID', 'sets the receiver') { |t| to = JID.new(t) }
  opts.on_tail('-h', '--help', 'Show this message') {
    puts opts
    exit
  }
  opts.parse!(ARGV)
end

if to.nil?
  puts "No receiver specified. See jabbersend -h"
end

cl = Client.new(myJID)
cl.connect
cl.auth(myPassword)
body = STDIN.readlines.join
m = Message.new(to, body).set_type(:normal).set_id('1').set_subject(subject)
puts m.to_s
cl.send(m)
cl.close
