#!/usr/bin/ruby

$:.unshift '../../../../../lib'

require 'xmpp4r'
require 'xmpp4r/version/iq/version'
require 'xmpp4r/version/helper/simpleresponder'


# A Hash containing all Version Query answers with their JIDs as keys:
versions = {}

# Command line argument checking

if ARGV.size != 2
  puts("Usage: ./versionbot.rb <jid> <password>")
  exit
end

# Building up the connection

#Jabber::debug = true

jid = Jabber::JID.new(ARGV[0])

cl = Jabber::Client.new(jid)
cl.connect
cl.auth(ARGV[1])

cl.on_exception { |*a|
  p a[0].backtrace
  exit!
}

# I'm not sure about the portability of 'uname -sr' here ;-)
# but that's all needed to answer version queries:
Jabber::Version::SimpleResponder.new(cl, 'xmpp4r Versionbot example', Jabber::XMPP4R_VERSION, IO.popen('uname -sr').readlines.to_s.strip)


cl.add_iq_callback { |iq|
  # Filter for version query results
  if (iq.type == :result) && iq.query.kind_of?(Jabber::Version::IqQueryVersion)
    puts "Version query result from #{iq.from}"
    # Keep track of results per JID
    versions[iq.from] = iq.query
    # Print details
    puts "  Name: #{iq.query.iname.inspect}"
    puts "  Version: #{iq.query.version.inspect}"
    puts "  OS: #{iq.query.os.inspect}"
  end
}

cl.add_presence_callback { |pres|
  # Already fingerprinted or offline?
  unless versions.has_key?(pres.from) || (pres.type == :unavailable) || (pres.type == :error)
    # Construct a new query
    iq = Jabber::Iq.new(:get, pres.from)
    # and ask for the version
    iq.query = Jabber::Version::IqQueryVersion.new
    puts "Asking #{iq.to} for his/her/its version"
    versions[pres.from] = :asking
    cl.send(iq)
  end
}

# Send initial presence
cl.send(Jabber::Presence.new.set_show(:xa).set_status('I am the evil fingerprinting robot'))

# Main loop:
loop do
  cl.process
  sleep(1)
end

cl.close
