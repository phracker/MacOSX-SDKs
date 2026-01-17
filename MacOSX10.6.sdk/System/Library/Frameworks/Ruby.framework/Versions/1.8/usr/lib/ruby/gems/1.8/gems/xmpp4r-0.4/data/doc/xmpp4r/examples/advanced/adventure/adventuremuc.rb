require 'world'

class AdventureMUC
  def initialize(jid, secret, addr, port=5347)
    @worlds = {}

    @component = Jabber::Component.new(jid)
    @component.connect(addr, port)
    @component.auth(secret)
    @component.on_exception { |e,|
      puts "#{e.class}: #{e}\n#{e.backtrace.join("\n")}"
    }

    @component.add_iq_callback { |iq|
      handle_iq(iq)
    }
    @component.add_presence_callback { |pres|
      handle_presence(pres)
    }
    @component.add_message_callback { |msg|
      handle_message(msg)
    }

    puts "Adventure component up and running"
  end

  def add_world(file)
    print "Adding world from #{file}..."
    begin
      world = World.new_from_file(self, file)
    rescue Exception => e
      puts " #{e.to_s}"
      exit
    end
    @worlds[world.node] = world
    puts " #{world.iname}"
  end

  def send(worldnode, worldresource, stanza)
    stanza.from = Jabber::JID.new(worldnode, @component.jid.domain, worldresource)
    @component.send(stanza)
  end

  def handle_iq(iq)
    puts "iq: from #{iq.from} type #{iq.type} to #{iq.to}: #{iq.queryns}"

    if iq.query.kind_of?(Jabber::Discovery::IqQueryDiscoInfo)
      handle_disco_info(iq)
      true
    elsif iq.query.kind_of?(Jabber::Discovery::IqQueryDiscoItems)
      handle_disco_items(iq)
      true
    else
      false
    end
  end

  def handle_disco_info(iq)
    if iq.type != :get
      answer = iq.answer
      answer.type = :error
      answer.add(Jabber::ErrorResponse.new('bad-request'))
      @component.send(answer) if iq.type != :error
      return
    end
    answer = iq.answer
    answer.type = :result
    if iq.to.node == nil
      answer.query.add(Jabber::Discovery::Identity.new('conference', 'Adventure component', 'text'))
      answer.query.add(Jabber::Discovery::Feature.new(Jabber::Discovery::IqQueryDiscoInfo.new.namespace))
      answer.query.add(Jabber::Discovery::Feature.new(Jabber::Discovery::IqQueryDiscoItems.new.namespace))
    else
      world = @worlds[iq.to.node]
      if world.nil?
        answer.type = :error
        answer.query.add(Jabber::ErrorResponse.new('item-not-found', 'The world you are trying to reach is currently unavailable.'))
      else
        answer.query.add(Jabber::Discovery::Identity.new('conference', world.iname, 'text'))
        answer.query.add(Jabber::Discovery::Feature.new(Jabber::Discovery::IqQueryDiscoInfo.new.namespace))
        answer.query.add(Jabber::Discovery::Feature.new(Jabber::Discovery::IqQueryDiscoItems.new.namespace))
        answer.query.add(Jabber::Discovery::Feature.new(Jabber::MUC::XMUC.new.namespace))
        answer.query.add(Jabber::Discovery::Feature.new(Jabber::MUC::XMUCUser.new.namespace))
      end
    end
    @component.send(answer)
  end

  def handle_disco_items(iq)
    if iq.type != :get
      answer = iq.answer
      answer.add(Jabber::ErrorResponse.new('bad-request'))
      @component.send(answer)
      return
    end
    answer = iq.answer
    answer.type = :result
    if iq.to.node == nil
      @worlds.each { |node,world|
        answer.query.add(Jabber::Discovery::Item.new(Jabber::JID.new(node, @component.jid.domain), world.iname))
      }
    end
    @component.send(answer)
  end

  def handle_presence(pres)
    puts "presence: from #{pres.from} type #{pres.type} to #{pres.to}"

    world = @worlds[pres.to.node]
    if world.nil?
      answer = pres.answer
      answer.type = :error
      answer.add(Jabber::ErrorResponse.new('item-not-found', 'The world you are trying to reach is currently unavailable.'))
      @component.send(answer)
    else
      world.handle_presence(pres)
    end

    true
  end

  def handle_message(msg)
    puts "message: from #{msg.from} type #{msg.type} to #{msg.to}: #{msg.body.inspect}"

    world = @worlds[msg.to.node]
    if world.nil?
      answer = msg.answer
      answer.type = :error
      answer.add(Jabber::ErrorResponse.new('item-not-found', 'The world you are trying to reach is currently unavailable.'))
      @component.send(answer)
    else
      world.handle_message(msg)
    end

    true
  end
end
