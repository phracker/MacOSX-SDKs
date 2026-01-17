# From Vlad Jebelev:
#
# - Second thing - I think you just probably didn't have the time to update 
# instance methods yet but when I POST with a reusal of a previous curl 
# instance, it doesnt' work for me, e.g. when I create a curl previously and 
# then issue:
#  
#   c.http_post(login_url, *fields)
#   
# instead of:
#  
#   c = Curl::Easy.http_post(login_url, *fields) do |curl|
#     ...  
#   end
#    
# then the result I am getting is quite different.
#
# ================
#
# Update:
#
#   It seems that class httpost is incorrectly passing arguments down to 
#   instance httppost. This bug is intermittent, but results in an
#   exception from the first post when it occurs.
#   
require File.expand_path(File.join(File.dirname(__FILE__), 'helper'))

class BugTestInstancePostDiffersFromClassPost < Test::Unit::TestCase
  def test_bug
    5.times do |i|
      puts "Test ##{i}"
      do_test
      sleep 2
    end
  end

  def do_test
    c = Curl::Easy.http_post('https://www.google.com/accounts/ServiceLoginAuth',
                Curl::PostField.content('ltmpl','m_blanco'))
    body_c, header_c = c.body_str, c.header_str
   
    sleep 2

    c.http_post('https://www.google.com/accounts/ServiceLoginAuth',
                Curl::PostField.content('ltmpl','m_blanco'))
    body_i, header_i = c.body_str, c.header_str

    # timestamps will differ, just check first bit. We wont get here if
    # the bug bites anyway...
    assert_equal header_c[0..50], header_i[0..50]
  end
end

