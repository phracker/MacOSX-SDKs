# This Sinatra application must be run with mongrel
# or possibly with unicorn for the serve action to work properly.
# See http://efreedom.com/Question/1-3669674/Streaming-Data-Sinatra-Rack-Application

require 'sinatra'

get '/wait/:time' do |time|
  time = time.to_i
  sleep(time)
  "Slept #{time} at #{Time.now}"
end

# http://efreedom.com/Question/1-3027435/Way-Flush-Html-Wire-Sinatra
class Streamer
  def initialize(time, chunks)
    @time = time
    @chunks = chunks
  end
  
  def each
    @chunks.each do |chunk|
      sleep(@time)
      yield chunk
    end
  end
end

get '/serve/:chunk_size/every/:time/for/:count' do |chunk_size, time, count|
  chunk_size, time, count = chunk_size.to_i, time.to_i, count.to_i
  chunk = 'x' * chunk_size
  chunks = [chunk] * count
  Streamer.new(time, chunks)
end
