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
$:.unshift(File.expand_path(File.join(File.dirname(__FILE__), '..', 'ext')))
$:.unshift(File.expand_path(File.join(File.dirname(__FILE__), '..', 'lib')))
require 'curb'
require 'uri'
 
url = 'https://www.google.com/accounts/ServiceLoginAuth'
 
c = Curl::Easy.http_post('https://www.google.com/accounts/ServiceLoginAuth',
                         Curl:: PostField.content('ltmpl','m_blanco')) #do
#                         end

puts "success"

