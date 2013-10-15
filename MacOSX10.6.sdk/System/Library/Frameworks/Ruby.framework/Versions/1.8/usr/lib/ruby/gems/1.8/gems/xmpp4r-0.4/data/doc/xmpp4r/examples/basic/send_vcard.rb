#!/usr/bin/ruby

# Demonstration of the Vcard helper class
#
# * Retrieves your own vCard
# * Modify fields given on the command line
# * Dumps the vCard
# * Send your vCard to the server

$:.unshift('../../../../../lib')

require 'xmpp4r'
require 'xmpp4r/vcard/helper/vcard'
include Jabber


# settings
if ARGV.length < 2
  puts "Usage:\t./send_vcard.rb <jid> <password> [<field1>=<value1> [... <fieldN>=<valueN>] ]"
  puts "Example:\t./send_vcard.rb user@server/resource password NICKNAME=User \"FN=A user\""
  exit 1
end

# Do the client stuff...
myJID = JID.new(ARGV.shift)
myPassword = ARGV.shift
cl = Client.new(myJID)
cl.connect
cl.auth(myPassword)

# The Vcard helper
vcard_helper = Vcard::Helper.new(cl)

begin
  puts "Retrieving vCard information for #{cl.jid.strip}"
  vcard = vcard_helper.get


  # Inspect the command line for vCard fields to be changed
  ARGV.each { |arg|
    arg.scan(/^(.+?)=(.*)$/) { |field,text|
      puts "field #{field}: #{vcard[field].inspect} => #{text.inspect}"
      vcard[field] = text
    }
  }

  # Dump the vCard
  vcard.fields.each { |field|
    if field.split(/\//).pop == 'BINVAL'
      puts "#{field}:\tBINVAL"
    else
      puts "#{field}:\t#{vcard[field].inspect}"
    end
  }

  begin
    puts "Sending vCard information for #{cl.jid.strip}"
    vcard_helper.set(vcard)
  rescue Exception => e
    puts "Sorry, we stumbled upon the following when sending the vCard of #{cl.jid.strip}: #{e.to_s.inspect}"
  end

rescue Exception => e
  puts "Sorry, we stumbled upon the following when requesting the vCard of #{cl.jid.strip}: #{e.to_s.inspect}"
end

cl.close
