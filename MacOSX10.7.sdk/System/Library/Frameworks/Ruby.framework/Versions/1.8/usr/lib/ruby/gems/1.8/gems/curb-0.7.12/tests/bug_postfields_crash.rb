# From GICodeWarrior:
#
# $ ruby crash_curb.rb 
# crash_curb.rb:7: [BUG] Segmentation fault
# ruby 1.8.7 (2009-06-12 patchlevel 174) [x86_64-linux]
# 
# Aborted
# crash_curb.rb:
# #!/usr/bin/ruby
# require 'rubygems'
# require 'curb'
# 
# curl = Curl::Easy.new('http://example.com/')
# curl.multipart_form_post = true
# curl.http_post(Curl::PostField.file('test', 'test.xml'){'example data'})
# Ubuntu 9.10
# curb gem version 0.6.2.1
require File.expand_path(File.join(File.dirname(__FILE__), 'helper'))

class BugPostFieldsCrash < Test::Unit::TestCase
  def test_crash
    curl = Curl::Easy.new('http://example.com/')
    curl.multipart_form_post = true
    curl.http_post(Curl::PostField.file('test', 'test.xml'){'example data'})
  end
end
