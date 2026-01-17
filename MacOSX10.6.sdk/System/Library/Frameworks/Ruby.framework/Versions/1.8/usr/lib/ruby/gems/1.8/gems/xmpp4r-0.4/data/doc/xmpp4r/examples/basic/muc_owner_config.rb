require 'xmpp4r'
require 'xmpp4r/muc'

client = Jabber::Client.new('admin@myserver.co.uk/ruby')
muc = Jabber::MUC::MUCClient.new(client)
client.connect
client.auth('admin')
muc.join('room@conference.myserver.co.uk/admin')
muc.configure(
      'muc#roomconfig_roomname' => 'roomname',
      'muc#roomconfig_persistentroom' => 1
)
