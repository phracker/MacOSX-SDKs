require File.expand_path(File.join(File.dirname(__FILE__), 'helper'))
require 'webrick'
class ::WEBrick::HTTPServer ; def access_log(config, req, res) ; end ; end
class ::WEBrick::BasicLog ; def log(level, data) ; end ; end

class BugTestInstancePostDiffersFromClassPost < Test::Unit::TestCase
  def test_bug
    server = WEBrick::HTTPServer.new( :Port => 9999 )
    server.mount_proc("/test") do|req,res|
      sleep 0.5
      res.body = "hi"
      res['Content-Type'] = "text/html"
    end

    thread = Thread.new(server) do|srv|
      srv.start
    end

    threads = []
    timer = Time.now

    5.times do |i|
      t = Thread.new do
        c = Curl::Easy.perform('http://localhost:9999/test')
        c.header_str
      end
      threads << t
    end

    multi_responses = threads.collect do|t|
      t.value
    end

    multi_time = (Time.now - timer)
    puts "requested in #{multi_time}"

    timer = Time.now
    single_responses = []
    5.times do |i|
      c = Curl::Easy.perform('http://localhost:9999/test')
      single_responses << c.header_str
    end
    
    single_time = (Time.now - timer)
    puts "requested in #{single_time}"

    assert single_time > multi_time

    server.shutdown
    thread.join
  end
end
