#!/usr/bin/ruby

$:.unshift '../../../../../lib'
require 'xmpp4r'


# Argument checking
if ARGV.size < 2
  puts("Usage: #{$0} <desired jid> <password> [field1=value1] [fieldN=valueN]")
  exit
end


# The usual procedure
cl = Jabber::Client.new(Jabber::JID.new(ARGV[0]))
puts "Connecting"
cl.connect

# Registration of the new user account
puts "Registering..."
begin
  fields = {}
  ARGV[2..-1].each { |a|
    k, v = a.split('=', 2)
    fields[k] = v
  }
  cl.register(ARGV[1], fields)
  puts "Successful"
rescue Jabber::ServerError => e
  puts "Error: #{e.error.text}"
  if e.error.type == :modify
    puts "Accepted registration information:"
    instructions, fields = cl.register_info
    fields.each { |info|
      puts "* #{info}"
    }
    puts "(#{instructions})"
  end
end

# Shutdown
cl.close
