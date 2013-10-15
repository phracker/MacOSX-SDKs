#!/usr/bin/ruby

$:.unshift '../../../../../lib'

require 'xmpp4r'
include Jabber

c = Component.new('tada', 'localhost', 60001)
c.connect
c.auth('jabber-rocks')
Thread.stop
