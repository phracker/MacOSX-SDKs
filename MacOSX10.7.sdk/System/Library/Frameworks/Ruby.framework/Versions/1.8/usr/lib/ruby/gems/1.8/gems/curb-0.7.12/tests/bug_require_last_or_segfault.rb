# From Vlad Jebelev:
# 
# - if I have a require statement after "require 'curb'" and there is a 
# POST with at least 1 field, the script will fail with a segmentation 
# fault, e.g. the following sequence fails every time for me (Ruby 1.8.5):
# -----------------------------------------------------------------
# require 'curb'
# require 'uri'
#  
#  url = 'https://www.google.com/accounts/ServiceLoginAuth'
#   
#  c = Curl::Easy.http_post(
#         'https://www.google.com/accounts/ServiceLoginAuth',
#               [Curl:: PostField.content('ltmpl','m_blanco')] ) do |curl|
#  end
#  ------------------------------------------------------------------
#  :..dev/util$ ruby seg.rb
#  seg.rb:6: [BUG] Segmentation fault
#  ruby 1.8.5 (2006-08-25) [i686-linux]
#                
#  Aborted
#  ------------------------------------------------------------------
#
require 'test/unit'
require 'rbconfig'

$rubycmd = Config::CONFIG['RUBY_INSTALL_NAME'] || 'ruby'

class BugTestRequireLastOrSegfault < Test::Unit::TestCase
  def test_bug
    5.times do |i|
      puts "Test ##{i}"

      # will be empty string if it segfaults...
      assert_equal 'success', `#$rubycmd #{File.dirname(__FILE__)}/require_last_or_segfault_script.rb`.chomp
      sleep 5
    end
  end
end

