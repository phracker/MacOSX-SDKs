#!/usr/bin/env ruby

$:.unshift '../../../../../lib'
require 'xmpp4r'
include Jabber

if ARGV.size != 2
  puts "Warning! This example UNREGISTERS user accounts!"
  puts "Usage: #{$0} <jid> <password>"
  exit
end

cl = Client.new(JID.new(ARGV[0]))
cl.connect
cl.auth(ARGV[1])
cl.remove_registration

cl.close
