#!/usr/bin/ruby -w

require 'shellmgr'

sh = Shell.new { |s| puts s }

while true do
  l = gets
  sh.puts l
end
