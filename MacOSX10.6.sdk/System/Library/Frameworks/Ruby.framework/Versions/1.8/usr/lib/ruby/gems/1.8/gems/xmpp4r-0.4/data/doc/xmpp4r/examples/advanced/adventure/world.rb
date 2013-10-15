require 'rexml/document'

class World < REXML::Element
  def initialize(muc)
    super('world')

    @muc = muc
  end

  def send(resource, stanza)
    # Avoid sending to things without JID
    if stanza.to != nil
      @muc.send(node, resource, stanza)
    end
  end

  def World.new_from_file(muc, filename)
    file = File.new(filename)
    world = World.new(muc)
    world.import(REXML::Document.new(file).root)
    file.close
    world
  end

  def add(xmlelement)
    if xmlelement.kind_of?(REXML::Element) && (xmlelement.name == 'place')
      super(Place.new.import(xmlelement))
    elsif xmlelement.kind_of?(REXML::Element) && (xmlelement.name == 'thing') && !xmlelement.kind_of?(Player)
      super(Thing.new(self).import(xmlelement))
    else
      super(xmlelement)
    end
  end

  def node
    attributes['node']
  end

  def iname
    attributes['name']
  end

  def place(placename)
    pl = nil
    each_element('place') { |place|
      if place.iname == placename
        pl = place
      end
    }
    pl
  end

  def each_thing_by_place(place, &block)
    each_element('thing') { |t|
      if t.place == place
        yield(t)
      end
    }
  end

  def move_thing(thing, newplace)
    each_thing_by_place(thing.place) { |t|
      # Call leave hooks
      t.on_leave(thing, newplace)

      # Broadcast unavailability presence to leaver
      unless t.presence.nil?
        pres = Jabber::Presence.import(t.presence)
        pres.type = :unavailable
        pres.to = thing.jid
        send(t.iname, pres) unless t.jid == thing.jid
      end

      # Broadcast unavailability presence to all who are here
      unless thing.presence.nil?
        pres = Jabber::Presence.import(thing.presence)
        pres.type = :unavailable
        pres.to = t.jid
        send(thing.iname, pres) unless thing.jid == t.jid
      end
    }

    # Enter new place
    oldplace = thing.place
    thing.place = newplace

    each_thing_by_place(thing.place) { |t|
      # Broadcast availability presence to enterer
      unless t.presence.nil?
        pres = Jabber::Presence.import(t.presence)
        pres.to = thing.jid
        send(t.iname, pres)
      end

      # Broadcast availability presence to all who are here
      unless thing.presence.nil?
        pres = Jabber::Presence.import(thing.presence)
        pres.to = t.jid
        send(thing.iname, pres)
      end
    }

    thing.send_message(nil, " ")
    subject = newplace.nil? ? " " : newplace.dup
    subject[0] = subject[0,1].upcase
    thing.send_message(nil, "Entering #{newplace}", subject)
    thing.send_message(nil, " ")
    thing.see(place(newplace))

    each_thing_by_place(thing.place) { |t|
      # Call enter hooks
      t.on_enter(thing, oldplace)
    }
  end

  def handle_presence(pres)
    # A help for the irritated first:
    if pres.type == :subscribe
      msg = Jabber::Message.new(pres.from)
      msg.type = :normal
      msg.subject = "Adventure component help"
      msg.body = "You don't need to subscribe to my presence. Simply use your Jabber client to join the MUC or conference at #{pres.to.strip}"
      send(nil, msg)
      return(true)
    end

    # Look if player is already known
    player = nil
    each_element('thing') { |thing|
      if thing.kind_of?(Player) && pres.to.resource == thing.iname
        player = thing
      end

      # Disallow nick changes
      if thing.kind_of?(Player) && (pres.from == thing.jid) && (player != thing)
        answer = pres.answer(false)
        answer.type = :error
        answer.add(Jabber::ErrorResponse.new('not-acceptable', 'Nickchange not allowed'))
        send(thing.iname, answer)
        return(true)
      end
    }

    # Either nick-collission or empty nick
    unless (player.nil? || pres.from == player.jid) && (pres.to.resource.to_s.size > 1)
      answer = pres.answer
      answer.type = :error
      if (pres.to.resource.to_s.size > 1)
        answer.add(Jabber::ErrorResponse.new('conflict', 'Nickname already used'))
      else
        answer.add(Jabber::ErrorResponse.new('not-acceptable', 'Please use a nickname'))
      end
      send(nil, answer)
      return(true)
    end

    # Add the valid player
    if player.nil?
      player = add(Player.new(self, pres.to.resource, pres.from))
      player.presence = pres
      move_thing(player, attributes['start'])
      player.send_message('Help!', 'Send "?" to get a list of available commands any time.')
    # Or broadcast updated presence
    else
      player.presence = pres

      each_thing_by_place(player.place) { |t|
        # Broadcast presence to all who are here
        pres = Jabber::Presence.import(player.presence)
        pres.to = t.jid
        send(player.iname, pres)
      }
    end

    # Remove the player instantly
    if pres.type == :error || pres.type == :unavailable
      move_thing(player, nil)
      delete_element(player)
    end
  end

  def handle_message(msg)
    player = nil
    each_element('thing') { |thing|
      if thing.kind_of?(Player) && msg.to.resource == nil && msg.from == thing.jid
        player = thing
      end
    }

    if player.nil?
      answer = msg.answer
      answer.type = :error
      answer.add(Jabber::ErrorResponse.new('forbidden'))
      send(msg.to.resource, answer)
      return(true)
    end

    unless command(player, msg.body)
      each_thing_by_place(player.place) { |thing|
        thing.send_message(player.iname, msg.body)
      }
    end
  end

  def command(player, text)
    if text == '?'
      player.send_message(nil, "(Command) who")
      place(player.place).each_element('go') { |go|
        player.send_message(nil, "(Command) go #{go.attributes['spec']}")
      }
      each_thing_by_place(player.place) { |thing|
        thing.each_element('on-command') { |c|
          player.send_message(nil, "(Command) #{c.attributes['command']} #{thing.command_name}")
        }
      }
      return(true)
    else
      words = text.split(/ /)
      cmd = words.shift
      what = words.shift || ""
      if cmd == 'go'
        oldplace = place(player.place)
        newplace = nil

        oldplace.each_element('go') { |go|
          if go.attributes['spec'] == what
            newplace = go.attributes['place']
          end
        }

        if newplace.nil?
          player.send_message(nil, 'You cannot go there')
        else
          move_thing(player, newplace)
        end
        return(true)
      elsif cmd == 'who'
        player.send_message(nil, "Players in \"#{iname}\":")
        each_element('thing') { |thing|
          if thing.kind_of?(Player)
            player.send_message(nil, "#{thing.iname} is at/in #{thing.place}")
          end
        }
        return(true)
      else
        handled = false
        each_thing_by_place(player.place) { |thing|
          if what.downcase == thing.command_name.downcase
            thing.each_element('on-command') { |c|
              if c.attributes['command'] == cmd
                thing.command(player, c, words)
                handled = true
              end
            }
          end
        }
        return(true) if handled
      end
    end
    false
  end
end

class Place < REXML::Element
  def initialize
    super('place')
  end

  def iname
    attributes['name']
  end
end

class Thing < REXML::Element
  def initialize(world)
    super('thing')
    @world = world
  end

  def add(xmlelement)
    if xmlelement.kind_of?(REXML::Element) && (xmlelement.name == 'presence')
      super(Jabber::Presence.import(xmlelement))
    else
      super(xmlelement)
    end
  end

  def iname
    attributes['name']
  end

  def command_name
    attributes['command-name'].nil? ? iname : attributes['command-name']
  end

  def place
    attributes['place']
  end

  def place=(p)
    attributes['place'] = p
  end

  def jid
    nil
  end

  def presence
    xe = nil
    each_element('presence') { |pres|
      xe = Jabber::Presence.import(pres)
    }
    if self.kind_of?(Player)
      xe.add(Jabber::MUC::XMUCUser.new).add(Jabber::MUC::XMUCUserItem.new(:none, :participant))
    else
      xe.add(Jabber::MUC::XMUCUser.new).add(Jabber::MUC::XMUCUserItem.new(:owner, :moderator))
    end
    xe
  end

  def presence=(pres)
    delete_elements('presence')
    add(pres)
  end

  def see(place)
  end

  def send_message(fromresource, text, subject=nil)
  end

  def send_message_to_place(fromresource, text)
    @world.each_element('thing') { |thing|
      if thing.place == place
        thing.send_message(fromresource, text)
      end
    }
  end

  def on_enter(thing, from)
    each_element('on-enter') { |c|
      command(thing, c, [from])
    }
  end

  def on_leave(thing, to)
    each_element('on-leave') { |c|
      command(thing, c, [to])
    }
  end

  def command(source, command, arguments)
    command.each_element { |action|
      text = action.text.nil? ? "" : action.text.dup
      text.gsub!('%self%', iname)
      text.gsub!('%actor%', source.iname)
      text.gsub!('%place%', place)
      if action.name == 'say' || action.name == 'tell'
        sender = nil
        sender = iname if action.name == 'say'
        if action.attributes['to'] == 'all'
          send_message_to_place(sender, text)
        else
          source.send_message(sender, text)
        end
      end
    }
  end
end

class Player < Thing
  def initialize(world, iname, jid)
    super(world)
    attributes['name'] = iname
    attributes['jid'] = jid.to_s
  end

  def jid
    attributes['jid'].nil? ? nil : Jabber::JID.new(attributes['jid'])
  end

  def see(place)
    return if place.nil?

    place.text.strip.split(/\n/).each do |line|
      send_message(nil, line.strip)
    end

    send_message(nil, " ")

    directions = []
    place.each_element('go') { |go|
      directions.push(go.attributes['spec'])
    }
    send_message(nil, "You can go #{directions.join(', ')}")
  end

  def send_message(fromresource, text, subject=nil)
    msg = Jabber::Message.new(jid, text)
    msg.type = :groupchat
    msg.subject = subject unless subject.nil?
    @world.send(fromresource, msg)
  end

  def on_enter(thing, from)
    if thing != self
      if from.nil?
        send_message(nil, "#{thing.iname} spawns")
      else
        send_message(nil, "#{thing.iname} enters #{place} coming from #{from}")
      end
    end
  end

  def on_leave(thing, to)
    if thing != self
      if to.nil?
        send_message(nil, "#{thing.iname} disintegrates")
      else
        send_message(nil, "#{thing.iname} leaves #{place} going to #{to}")
      end
    end
  end
end
