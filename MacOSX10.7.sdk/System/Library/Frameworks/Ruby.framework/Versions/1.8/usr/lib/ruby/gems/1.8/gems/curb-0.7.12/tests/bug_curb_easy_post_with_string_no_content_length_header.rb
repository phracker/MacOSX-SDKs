=begin
From jwhitmire
Todd, I'm trying to use curb to post data to a REST url. We're using it to post support questions from our iphone app directly to tender. The post looks good to me, but curl is not adding the content-length header so I get a 411 length required response from the server.

Here's my post block, do you see anything obvious? Do I need to manually add the Content-Length header?

c = Curl::Easy.http_post(url) do |curl|
  curl.headers["User-Agent"] = "Curl/Ruby"
  if user
    curl.headers["X-Multipass"] = user.multipass
  else
    curl.headers["X-Tender-Auth"] = TOKEN
  end
  curl.headers["Accept"] = "application/vnd.tender-v1+json"

  curl.post_body = params.map{|f,k| "#{curl.escape(f)}=#{curl.escape(k)}"}.join('&')

  curl.verbose = true
  curl.follow_location = true
  curl.enable_cookies = true
end
Any insight you care to share would be helpful. Thanks.
=end
require File.expand_path(File.join(File.dirname(__FILE__), 'helper'))
require 'webrick'
class ::WEBrick::HTTPServer ; def access_log(config, req, res) ; end ; end
class ::WEBrick::BasicLog ; def log(level, data) ; end ; end

class BugCurbEasyPostWithStringNoContentLengthHeader < Test::Unit::TestCase
  def test_bug_workaround
    server = WEBrick::HTTPServer.new( :Port => 9999 )
    server.mount_proc("/test") do|req,res|
      assert_equal '15', req['Content-Length']
      res.body = "hi"
      res['Content-Type'] = "text/html"
    end

    thread = Thread.new(server) do|srv|
      srv.start
    end
    params = {:cat => "hat", :foo => "bar"}

    post_body = params.map{|f,k| "#{Curl::Easy.new.escape(f)}=#{Curl::Easy.new.escape(k)}"}.join('&')
    c = Curl::Easy.http_post("http://127.0.0.1:9999/test",post_body) do |curl|
      curl.headers["User-Agent"] = "Curl/Ruby"
      curl.headers["X-Tender-Auth"] = "A Token"
      curl.headers["Accept"] = "application/vnd.tender-v1+json"

      curl.follow_location = true
      curl.enable_cookies = true
    end

    server.shutdown
    thread.join
  end
  def test_bug
    server = WEBrick::HTTPServer.new( :Port => 9999 )
    server.mount_proc("/test") do|req,res|
      assert_equal '15', req['Content-Length']
      res.body = "hi"
      res['Content-Type'] = "text/html"
    end

    thread = Thread.new(server) do|srv|
      srv.start
    end
    params = {:cat => "hat", :foo => "bar"}

    c = Curl::Easy.http_post("http://127.0.0.1:9999/test") do |curl|
      curl.headers["User-Agent"] = "Curl/Ruby"
      curl.headers["X-Tender-Auth"] = "A Token"
      curl.headers["Accept"] = "application/vnd.tender-v1+json"

      curl.post_body = params.map{|f,k| "#{curl.escape(f)}=#{curl.escape(k)}"}.join('&')

      curl.follow_location = true
      curl.enable_cookies = true
    end

    server.shutdown
    thread.join
  end
end
