#!/usr/bin/env ruby
$:.unshift '../../../../../lib/'
require 'xmpp4r'
require 'xmpp4r/muc/helper/simplemucclient'


if ARGV.size != 3
  puts "Usage: #{$0} <jid> <password> <room@conference/nick>"
  exit
end

# Print a line formatted depending on time.nil?
def print_line(time, line)
  if time.nil?
    puts line
  else
    puts "#{time.strftime('%I:%M')} #{line}"
  end
end


#Jabber::debug = true
cl = Jabber::Client.new(Jabber::JID.new(ARGV[0]))
cl.connect
cl.auth(ARGV[1])

# For waking up...
mainthread = Thread.current

# This is the SimpleMUCClient helper!
m = Jabber::MUC::SimpleMUCClient.new(cl)

# SimpleMUCClient callback-blocks

m.on_join { |time,nick|
  print_line time, "#{nick} has joined!"
  puts "Users: " + m.roster.keys.join(', ')
}
m.on_leave { |time,nick|
  print_line time, "#{nick} has left!"
}

m.on_message { |time,nick,text|
  print_line time, "<#{nick}> #{text}"

  # Avoid reacting on messaged delivered as room history
  unless time
    # Bot: invite astro@spaceboyz.net
    if text.strip =~ /^(.+?): invite (.+)$/
      jid = $2
      if $1.downcase == m.jid.resource.downcase
        m.invite(jid => "Inviting you on behalf of #{nick}")
        m.say("Inviting #{jid}...")
      end
    # Bot: subject This is room is powered by XMPP4R
    elsif text.strip =~ /^(.+?): subject (.+)$/
      if $1.downcase == m.jid.resource.downcase
        m.subject = $2
      end
    # Bot: exit please
    elsif text.strip =~ /^(.+?): exit please$/
      if $1.downcase == m.jid.resource.downcase
        puts "exiting"
        m.exit "Exiting on behalf of #{nick}"
        mainthread.wakeup
      end
    end
  end
}
m.on_room_message { |time,text|
  print_line time, "- #{text}"
}
m.on_subject { |time,nick,subject|
  print_line time, "*** (#{nick}) #{subject}"
}

m.join(ARGV[2])

# Wait for being waken up by m.on_message
Thread.stop

cl.close
