#!/usr/bin/ruby

$:.unshift '../../../../../lib'

require 'xmpp4r'
require 'xmpp4r/iq/query/discoinfo'
require 'xmpp4r/iq/query/discoitems'
require 'xmpp4r/x/muc'


#Jabber::debug = true

class Room
  class RoomException < Exception
    attr_reader :error
    def initialize(error, msg)
      @error = Jabber::ErrorResponse.new(error, msg)
    end
  end

  def initialize(stream, name)
    @users = {}   # nick => jid
    @stream = stream
    @name = name
  end

  def num_users
    @users.size
  end

  def each_user(&block)
    @users.each { |n,j| yield(n, j) }
  end

  def handle_message(msg)
    origin = msg.from
    msg.from = nil
    @users.each { |nick,jid|
      if jid == origin
        msg.from = Jabber::JID.new(@name.node, @name.domain, nick)
      end
    }
    unless msg.from.nil?
      broadcast(msg)
    end

    true
  end

  def handle_presence(pres)
    reason = nil

    # Check if nick already registered
    @users.each { |nick,jid|
      if pres.from != jid && pres.to.resource == nick
        puts "#{pres.from} tried to use already active #{pres.to}"
        raise RoomException.new('conflict', "Nick already used")
      end
    }
    # New user?
    unless @users.has_key?(pres.to.resource)
      # Check nick length
      if pres.to.resource.size < 1
        puts "#{pres.from} tried to use empty nick"
        raise RoomException.new('not-acceptable', "Nick must contain characters")
      end

      # Push user-list
      userinfo = Jabber::Presence.import(pres)
      userinfo.to = pres.from
      userinfo.add(Jabber::XMUCUser.new).add(Jabber::XMUCUserItem.new(:none, :participant))
      print "Sending all users for #{pres.to} to #{pres.from}:"
      @users.each { |nick,jid|
        userinfo.from = Jabber::JID.new(@name.node, @name.domain, nick)
        print " #{nick} (#{jid})"
        @stream.send(userinfo)
      }
      puts " Ok"

      # Add the new user
      puts "Adding #{pres.from} as #{pres.to}"
      @users[pres.to.resource] = pres.from

      send_message("#{pres.to.resource} joins #{@name.node}")
      reason = "#{pres.to.resource} joins #{@name.node}"
    end

    # Remove dead rats
    if pres.type == :error || pres.type == :unavailable
      was_nick = nil
      @users.delete_if { |nick,jid|
        was_nick = nick
        jid == pres.from
      }
      unless was_nick.nil?
        send_message("#{was_nick} has left #{@name.node}")
        reason = "#{was_nick} has left #{@name.node}"
      end
    end

    # Advertise users presence to all
    puts "Advertising user to all"
    x = Jabber::XMUCUserItem.new(:none, :participant, pres.from)
    x.reason = reason
    pres.add(Jabber::XMUCUser.new).add(x)
    pres.from = pres.to
    broadcast(pres)
  end

  def send_message(body)
    msg = Jabber::Message.new
    msg.from = Jabber::JID.new(@name.node, @name.domain, "")
    msg.type = :groupchat
    msg.body = body
    broadcast(msg)
  end

  def broadcast(stanza)
    x = stanza.class::import(stanza)
    @users.each { |nick,jid|
      x.to = jid
      @stream.send(x)
    }
  end
end

class MUC
  def initialize(jid, secret, addr, port=5347)
    @rooms = {}

    @component = Jabber::Component.new(jid, addr, port)
    @component.connect
    @component.auth(secret)

    @component.add_iq_callback { |iq|
      handle_iq(iq)
    }
    @component.add_presence_callback { |pres|
      handle_presence(pres)
    }
    @component.add_message_callback { |msg|
      handle_message(msg)
    }
  end

  def handle_iq(iq)
    puts "#{iq.from} #{iq.queryns} to #{iq.to}"
    if iq.query.kind_of?(Jabber::IqQueryDiscoInfo)
      handle_disco_info(iq)
      true
    elsif iq.query.kind_of?(Jabber::IqQueryDiscoItems)
      handle_disco_items(iq)
      true
    else
      false
    end
  end

  def handle_presence(pres)
    room = nil
    @rooms.each { |name,r|
      room = r if name == pres.to.strip
    }

    if room.nil? && pres.type.nil? && (pres.to.node.to_s != '')
      room = Room.new(@component, pres.to.strip)
      @rooms[pres.to.strip] = room
    elsif room.nil? && pres.type != :error
      pres.to, pres.from = pres.from, pres.to
      pres.type = :error
      pres.add(Jabber::ErrorResponse.new('item-not-found'))
      @component.send(pres)
      return(true)
    end

    begin
      room.handle_presence(pres)
    rescue Room::RoomException => e
      pres.to, pres.from = pres.from, pres.to
      pres.type = :error
      pres.add(e.error)
      @component.send(pres)
      return(true)
    end
    return(false)
  end

  def handle_message(msg)
    puts "Message from #{msg.from} to #{msg.to} (#{msg.type}): #{msg.body.inspect}"
    return if msg.type == :error

    room = @rooms[msg.to]
    unless room.nil?
      room.handle_message(msg)
    else
      msg.to, msg.from = msg.from, msg.to
      msg.type = :error
      msg.add(Jabber::ErrorResponse.new('item-not-found', 'The chatroom you are trying to reach is currently not available.'))
      @component.send(msg)
    end
  end

  def handle_disco_info(iq)
    if (iq.type == :get)
      iq.type = :result
      iq.query = Jabber::IqQueryDiscoInfo.new
      if iq.to.node == nil
        iq.query.add(Jabber::DiscoIdentity.new('conference', 'Minimal Multi-User Chat', 'text'))
      else
        room = @rooms[iq.to]
        if room.nil?
          iq.type = :error
          iq.add_element(Jabber::ErrorResponse.new('item-not-found'))
        else
          iq.query.add(Jabber::DiscoIdentity.new('conference', "#{iq.to.node} (#{room.num_users})", 'text'))
        end
      end
      [Jabber::IqQueryDiscoInfo.new.namespace,
       Jabber::IqQueryDiscoItems.new.namespace,
       Jabber::XMUC.new.namespace,
       Jabber::XMUCUser.new.namespace].each { |ns|
          iq.query.add(Jabber::DiscoFeature.new(ns))
      }
    else
      iq.type = :error
      iq.add_element(Jabber::ErrorResponse.new('bad-request'))
    end
    iq.to, iq.from = iq.from, iq.to
    @component.send(iq)
  end

  def handle_disco_items(iq)
    if (iq.type == :get)
      iq.type = :result
      if iq.to.node == nil
        @rooms.each { |name,room|
          iq.query.add(Jabber::DiscoItem.new(Jabber::JID.new(name, @component.jid.domain), name))
        }
      elsif iq.to.resource == nil
        room = @rooms[iq.to.strip]
        unless room.nil?
          room.each_user { |nick,jid|
            iq.query.add(Jabber::DiscoItem.new(jid, nick))
          }
        else
          iq.type = :error
          iq.add_element(Jabber::ErrorResponse.new('item-not-found'))
        end
      end
    else
      iq.type = :error
      iq.add_element(Jabber::ErrorResponse.new('bad-request'))
    end
    iq.to, iq.from = iq.from, iq.to
    @component.send(iq)
  end
end

if ARGV.size != 3
  puts "Syntax: ./minimuc.rb <JID> <Password> <Host>"
  puts "Example: ./minimuc.rb conference.xmpp4r.mil minimuc localhost"
  exit
end

muc = MUC.new(Jabber::JID.new(ARGV[0]), ARGV[1], ARGV[2])
Thread.stop
