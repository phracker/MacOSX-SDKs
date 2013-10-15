#!/usr/bin/ruby
#
# A tool to change the password of a Jabber account
#


$:.unshift('../../../../../lib')

require 'xmpp4r'
include Jabber

def with_status(str, &block)
  print "#{str}..."
  $stdout.flush
  begin
    yield
    puts " Ok"
  rescue Exception => e
    puts " Exception: #{e.to_s}"
    raise e
  end
end


# settings
if ARGV.length != 3
  puts "Run with ./change_password.rb user@server/resource oldpassword newpassword"
  exit 1
end
my_jid = JID.new(ARGV[0])
my_jid.resource = 'change_password' if my_jid.resource.nil?
old_password = ARGV[1]
new_password = ARGV[2]

cl = Client.new(my_jid)

with_status('Connecting') { cl.connect }
with_status('Authenticating') { cl.auth(old_password) }
with_status('Changing password') { cl.password = new_password }

cl.close
