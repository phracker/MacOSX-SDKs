#!/usr/bin/ruby

# Basic console client that does nothing, but easy to modify to test things.
# to test, start, then type :
# connect login@server/resource password
# auth

$:.unshift '../../../../../lib'

require 'xmpp4r/client'
include Jabber

Jabber::debug = true

class BasicClient
  def initialize
    puts "Welcome to this Basic Console Jabber Client!"
    quit = false
    # main loop
    while not quit do
      print "> "
      $defout.flush
      line = gets
      quit = true if line.nil?
      if not quit
        command, args = line.split(' ', 2)
        args = args.to_s.chomp
        # main case
        case command
        when 'exit'
          quit = true
        when 'connect'
          do_connect(args)
        when 'help'
          do_help
        when 'auth'
          do_auth
        else
          puts "Command \"#{command}\" unknown"
        end
      end
    end
    puts "Goodbye!"
  end

  def do_help
    puts <<-EOF
# exit - exits
# connect user@server/resource password - connects
# auth - sends authentification
    EOF
  end

  ##
  # connect <jid> <password>
  def do_connect(args)
    @jid, @password = args.split(' ', 2)
    @jid = JID.new(@jid)
    @cl = Client.new(@jid)
    @cl.connect
  end

  ##
  # auth
  def do_auth
    @cl.auth(@password, false)
  end
end

BasicClient.new
