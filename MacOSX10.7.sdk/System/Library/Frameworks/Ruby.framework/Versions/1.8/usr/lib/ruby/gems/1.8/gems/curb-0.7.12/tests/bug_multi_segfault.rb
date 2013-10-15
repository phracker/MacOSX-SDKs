# From safis  http://github.com/taf2/curb/issues#issue/5
# irb: require 'curb'
# irb: multi = Curl::Multi.new
# irb: exit
# <main>:47140: [BUG] Bus Error
$:.unshift File.expand_path(File.join(File.dirname(__FILE__),'..','ext'))
$:.unshift File.expand_path(File.join(File.dirname(__FILE__),'..','lib'))
require 'curb'

class BugMultiSegfault < Test::Unit::TestCase
  def test_bug
    multi = Curl::Multi.new
  end
end
