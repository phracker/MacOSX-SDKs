#!/usr/bin/ruby -w

$:.unshift '../../lib'
require 'shellmgr'
require 'xmpp4r'
include Jabber

if ARGV.length != 3
  puts "usage: ./shellmgr_jabber.rb jid_to_use password jid_to_authorize"
  exit(1)
end

myjid = JID.new(ARGV[0])
mypassword = ARGV[1]
authjid = JID.new(ARGV[2])

myjid = JID.new(myjid.node, myjid.domain, 'RSM')
cl = Client.new(myjid)
cl.connect
cl.auth(mypassword)
mainthread = Thread.current
sh = Shell.new { |str|
  puts "-----RECEIVING-----\n#{str}"
  cl.send(Message.new(authjid, str)) }
cl.add_message_callback do |m|
  if JID.new(m.from).strip.to_s != authjid.strip.to_s
    puts "Received message from non-authorized user #{m.from}"
  else
    if m.body == "killshell"
      cl.send(Message.new(authjid, "Exiting..."))
      mainthread.wakeup
    else
      puts "-----EXECUTING-----\n#{m.body}"
      sh.puts(m.body)
    end
  end
end
cl.send(Presence.new)
puts "Connected ! Ask #{authjid.to_s} to send commands to #{myjid.to_s}"
cl.send(Message.new(authjid, "I'm ready to receive commands from you."))
Thread.stop
cl.close
sh.kill
