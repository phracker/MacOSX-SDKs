#!/usr/bin/ruby

# This script can be used to migrate from one jabber account to another

$:.unshift '../../../../../lib'

require 'optparse'
require 'xmpp4r'
include Jabber

jidfrom = JID.new('lucas@linux.ensimag.fr/JabberMigrate')
pwfrom = 'z'
jidto = JID.new('lucas@nussbaum.fr/JabberMigrate')
pwto = 'z'

BOTHOLD = "Hi, you are subscribed to my presence. I just changed my JID. The new one is #{jidto.strip}. You might want to update your roster. Thank you, and sorry for the inconvenience !"
BOTHNEW = "Hi, you are subscribed to the presence of my previous JID : #{jidfrom.strip}. I just changed my JID, and this is the new one. You might want to update your roster. Thank you, and sorry for the inconvenience !"

clfrom = Client.new(jidfrom)
clfrom.connect
clfrom.auth(pwfrom)
clto = Client.new(jidto)
clto.connect
clto.auth(pwto)
#clfrom.send(Presence.new)
#clto.send(Presence.new)
clfrom.send(Iq.new_rosterget)
exit = false
clfrom.add_iq_callback { |i|
  if i.type == :result and i.queryns == 'jabber:iq:roster'
    i.query.each_element do |e|
      e.text = ''
      jid = e.attribute('jid')
      name = e.attribute('name')
      subscription = e.attribute('subscription')
      ask = e.attribute('ask')
      jid &&= jid.value
      next if jid =~ /@(icq|msn|aim|yahoo).blop.info/
#      next if jid !~ /lucas@im.apinc.org/
      puts "Processing #{e.to_s}"
#      Jabber::debug = true
      name &&= name.value
      subscription &&= subscription.value
      ask &&= ask.value
      puts subscription
      case subscription
      when 'from'
        # il veut me voir, je veux pas le voir.
        # envoi unsubscribed
        clfrom.send(Presence.new.set_to(jid).set_type(:unsubscribed))
        # envoi message d'info OLD & NEW
        clfrom.send(Message.new(jid, BOTHOLD).set_type(:chat))
        clto.send(Message.new(jid, BOTHNEW).set_type(:chat))
      when 'to'
        # je veux le voir, il veut pas me voir
        # envoi unsubscribe
        clfrom.send(Presence.new.set_to(jid).set_type(:unsubscribe))
        # envoi subscribe avec message
        pres = Presence.new.set_to(jid).set_type(:subscribe)
        pres.add(Element.new('status').add_text("Hi, I was previously subscribed to your presence with my JID #{jidfrom.strip}. Can I re-subscribe to your presence ? Thank you."))
        clto.send(pres)
      when 'both'
        # envoi unsubscribed
        clfrom.send(Presence.new.set_to(jid).set_type(:unsubscribed))
        # envoi unsubscribe
        clfrom.send(Presence.new.set_to(jid).set_type(:unsubscribe))
        # update roster
        iq = Iq.new_rosterset
        e.delete_attribute('ask')
        e.delete_attribute('subscription')
        iq.query.add_element(e)
        clto.send(iq)
        # envoi message d'info OLD & NEW
        clfrom.send(Message.new(jid, BOTHOLD).set_type(:chat))
        pres = Presence.new.set_to(jid).set_type(:subscribe)
        pres.add(Element.new('status').add_text("Hi, I was previously subscribed to your presence with my JID #{jidfrom.strip}. Can I re-subscribe to your presence ? Thank you."))
        clto.send(pres)
        clto.send(Message.new(jid, BOTHNEW).set_type(:chat))
      end
    end
  end
}
while not exit
  clfrom.process
  clto.process
end
clfrom.close
clto.close
