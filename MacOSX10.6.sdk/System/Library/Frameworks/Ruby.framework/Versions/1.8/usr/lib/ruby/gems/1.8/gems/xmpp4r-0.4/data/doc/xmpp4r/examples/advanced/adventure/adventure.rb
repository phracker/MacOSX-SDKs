#!/usr/bin/ruby

$:.unshift '../../lib'

require 'xmpp4r'
require 'xmpp4r/discovery'
require 'xmpp4r/muc/x/muc'

require 'adventuremuc'


#Jabber::debug = true

if ARGV.size != 3
  puts "Syntax: ./adventure.rb <JID> <Password> <Host>"
  puts "See README for further help"
  exit
end

muc = AdventureMUC.new(Jabber::JID.new(ARGV[0]), ARGV[1], ARGV[2])
muc.add_world('tower.xml')
muc.add_world('cube.xml')
Thread.stop
