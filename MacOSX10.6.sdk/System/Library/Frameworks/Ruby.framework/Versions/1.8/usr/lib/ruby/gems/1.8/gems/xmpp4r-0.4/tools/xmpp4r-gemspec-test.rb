#!/usr/bin/env ruby

# Since GitHub doesn't allow unsafe commands in a gemspec this script
# will simulate running in their environment.

require 'rubygems/specification'
data = File.read('../xmpp4r.gemspec')
spec = nil
Thread.new { spec = eval("$SAFE = 3\n#{data}") }.join
puts spec

