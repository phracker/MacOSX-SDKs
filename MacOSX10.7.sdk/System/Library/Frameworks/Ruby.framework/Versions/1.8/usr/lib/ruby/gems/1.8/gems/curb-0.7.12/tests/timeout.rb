require File.expand_path(File.join(File.dirname(__FILE__), 'helper'))

# Run server with: ruby -rubygems timeout_server.rb -p 9128

# Note that curl requires all timeouts to be integers -
# curl_easy_setopt does not have a provision for floating-point values

class TestCurbTimeouts < Test::Unit::TestCase
  def test_no_timeout_by_default
    curl = Curl::Easy.new(wait_url(2))
    start = Time.now
    assert_equal true, curl.http_get
    elapsed = Time.now - start
    assert elapsed > 2
  end
  
  def test_overall_timeout_on_dead_transfer
    curl = Curl::Easy.new(wait_url(2))
    curl.timeout = 1
    assert_raise(Curl::Err::TimeoutError) do
      curl.http_get
    end
  end
  
  def test_clearing_timeout
    curl = Curl::Easy.new(wait_url(2))
    curl.timeout = 1
    curl.timeout = nil
    start = Time.now
    assert_equal true, curl.http_get
    elapsed = Time.now - start
    assert elapsed > 2
  end
  
  def test_overall_timeout_on_slow_transfer
    curl = Curl::Easy.new(serve_url(100, 2, 3))
    curl.timeout = 1
    # transfer is aborted despite data being exchanged
    assert_raise(Curl::Err::TimeoutError) do
      curl.http_get
    end
  end
  
  def test_low_speed_time_on_slow_transfer
    curl = Curl::Easy.new(serve_url(100, 1, 3))
    curl.low_speed_time = 2
    # use default low_speed_limit of 1
    assert true, curl.http_get
  end
  
  def test_low_speed_time_on_very_slow_transfer
    # send data slower than required
    curl = Curl::Easy.new(serve_url(10, 2, 3))
    curl.low_speed_time = 1
    # XXX for some reason this test fails if low speed limit is not specified
    curl.low_speed_limit = 1
    # use default low_speed_limit of 1
    assert_raise(Curl::Err::TimeoutError) do
      curl.http_get
    end
  end
  
  def test_low_speed_limit_on_slow_transfer
    curl = Curl::Easy.new(serve_url(10, 1, 3))
    curl.low_speed_time = 2
    curl.low_speed_limit = 1000
    assert_raise(Curl::Err::TimeoutError) do
      curl.http_get
    end
  end
  
  def test_clearing_low_speed_time
    curl = Curl::Easy.new(serve_url(100, 2, 3))
    curl.low_speed_time = 1
    curl.low_speed_time = nil
    assert_equal true, curl.http_get
  end
  
  def test_clearing_low_speed_limit
    curl = Curl::Easy.new(serve_url(10, 1, 3))
    curl.low_speed_time = 2
    curl.low_speed_limit = 1000
    curl.low_speed_limit = nil
    assert_equal true, curl.http_get
  end
  
  private
  
  def wait_url(time)
    "#{server_base}/wait/#{time}"
  end
  
  def serve_url(chunk_size, time, count)
    "#{server_base}/serve/#{chunk_size}/every/#{time}/for/#{count}"
  end
  
  def server_base
    'http://127.0.0.1:9128'
  end
end
