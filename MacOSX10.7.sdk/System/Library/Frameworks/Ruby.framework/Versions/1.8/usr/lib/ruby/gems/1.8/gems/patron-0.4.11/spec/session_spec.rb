## -------------------------------------------------------------------
##
## Copyright (c) 2008 The Hive http://www.thehive.com/
##
## Permission is hereby granted, free of charge, to any person obtaining a copy
## of this software and associated documentation files (the "Software"), to deal
## in the Software without restriction, including without limitation the rights
## to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
## copies of the Software, and to permit persons to whom the Software is
## furnished to do so, subject to the following conditions:
##
## The above copyright notice and this permission notice shall be included in
## all copies or substantial portions of the Software.
##
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
## IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
## FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
## AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
## LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
## OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
## THE SOFTWARE.
##
## -------------------------------------------------------------------
require File.expand_path("./spec") + '/spec_helper.rb'
require 'webrick'
require 'base64'
require 'fileutils'

describe Patron::Session do

  before(:each) do
    @session = Patron::Session.new
    @session.base_url = "http://localhost:9001"
  end

  it "should escape and unescape strings symetrically" do
    string = "foo~bar baz/"
    escaped = @session.escape(string)
    unescaped = @session.unescape(escaped)
    unescaped.should == string
  end

  it "should raise an error when passed an invalid action" do
    lambda { @session.request(:bogus, "/test", {}) }.should raise_error(ArgumentError)
  end

  it "should raise an error when no URL is provided" do
    @session.base_url = nil
    lambda {@session.get(nil)}.should raise_error(ArgumentError)
  end

  it "should retrieve a url with :get" do
    response = @session.get("/test")
    body = YAML::load(response.body)
    body.request_method.should == "GET"
  end

  it "should download content with :get and a file path" do
    tmpfile = "/tmp/patron_test.yaml"
    response = @session.get_file "/test", tmpfile
    response.body.should be_nil
    body = YAML::load_file(tmpfile)
    body.request_method.should == "GET"
    FileUtils.rm tmpfile
  end

  it "should include custom headers in a request" do
    response = @session.get("/test", {"User-Agent" => "PatronTest"})
    body = YAML::load(response.body)
    body.header["user-agent"].should == ["PatronTest"]
  end

  it "should merge custom headers with session headers" do
    @session.headers["X-Test"] = "Testing"
    response = @session.get("/test", {"User-Agent" => "PatronTest"})
    body = YAML::load(response.body)
    body.header["user-agent"].should == ["PatronTest"]
    body.header["x-test"].should == ["Testing"]
  end

  it "should raise an exception on timeout" do
    @session.timeout = 1
    lambda {@session.get("/timeout")}.should raise_error(Patron::TimeoutError)
  end

  it "should follow redirects by default" do
    @session.max_redirects = 1
    response = @session.get("/redirect")
    body = YAML::load(response.body)
    response.status.should == 200
    body.path.should == "/test"
  end

  it "should include redirect count in response" do
    @session.max_redirects = 1
    response = @session.get("/redirect")
    response.redirect_count.should == 1
  end

  it "should not follow redirects when configured to do so" do
    @session.max_redirects = 0
    response = @session.get("/redirect")
    response.status.should == 301
    response.body.should be_empty
  end

  it "should retrieve URL metadata with :head" do
    response = @session.head("/test")
    response.status.should == 200
    response.body.should be_empty
    response.headers.should_not be_empty
  end

  it "should send a delete request with :delete" do
    response = @session.delete("/test")
    body = YAML::load(response.body)
    body.request_method.should == "DELETE"
  end

  it "should send a COPY request with :copy" do
    response = @session.copy("/test", "/test2")
    body = YAML::load(response.body)
    body.request_method.should == "COPY"
  end

  it "should include a Destination header in COPY requests" do
    response = @session.copy("/test", "/test2")
    body = YAML::load(response.body)
    body.header['destination'].first.should == "/test2"
  end

  it "should upload data with :put" do
    data = "upload data"
    response = @session.put("/test", data)
    body = YAML::load(response.body)
    body.request_method.should == "PUT"
    body.header['content-length'].should == [data.size.to_s]
  end

  it "should raise when no data is provided to :put" do
    lambda { @session.put("/test", nil) }.should raise_error(ArgumentError)
  end

  it "should upload a file with :put" do
    response = @session.put_file("/test", "LICENSE")
    body = YAML::load(response.body)
    body.request_method.should == "PUT"
  end

  it "should raise when no file is provided to :put" do
    lambda { @session.put_file("/test", nil) }.should raise_error(ArgumentError)
  end

  it "should use chunked encoding when uploading a file with :put" do
    response = @session.put_file("/test", "LICENSE")
    body = YAML::load(response.body)
    body.header['transfer-encoding'].first.should == "chunked"
  end

  it "should upload data with :post" do
    data = "upload data"
    response = @session.post("/test", data)
    body = YAML::load(response.body)
    body.request_method.should == "POST"
    body.header['content-length'].should == [data.size.to_s]
  end

  it "should raise when no data is provided to :post" do
    lambda { @session.post("/test", nil) }.should raise_error(ArgumentError)
  end

  it "should upload a file with :post" do
    response = @session.post_file("/test", "LICENSE")
    body = YAML::load(response.body)
    body.request_method.should == "POST"
  end

  it "should upload a multipart with :post" do
    response = @session.post_multipart("/test", { :test_data => "123" }, { :test_file => "LICENSE" } )
    body = YAML::load(response.body)
    body.request_method.should == "POST"
  end

  it "should raise when no file is provided to :post" do
    lambda { @session.post_file("/test", nil) }.should raise_error(ArgumentError)
  end

  it "should use chunked encoding when uploading a file with :post" do
    response = @session.post_file("/test", "LICENSE")
    body = YAML::load(response.body)
    body.header['transfer-encoding'].first.should == "chunked"
  end

  it "should pass credentials as http basic auth" do
    @session.username = "foo"
    @session.password = "bar"
    response = @session.get("/test")
    body = YAML::load(response.body)
    body.header['authorization'].should == [encode_authz("foo", "bar")]
  end

  it "should handle cookies if set" do
    @session.handle_cookies
    response = @session.get("/setcookie").body
    YAML::load(response).header['cookie'].first.should == "session_id=foo123"
  end

  it "should not handle cookies by default" do
    response = @session.get("/setcookie").body
    YAML::load(response).header.should_not include('cookie')
  end

  it "should raise exception if cookie store is not writable or readable" do
    lambda { @session.handle_cookies("/trash/clash/foo") }.should raise_error(ArgumentError)
  end

  it "should work with multiple threads" do
    threads = []
    3.times do
      threads << Thread.new do
        session = Patron::Session.new
        session.base_url = "http://localhost:9001"
        session.post_file("/test", "LICENSE")
      end
    end
    threads.each {|t| t.join }
  end

  it "should limit the buffer_size" do
    # Buffer size is tricky to test, as it only affects the buffer size for each
    # read and it's not really visible at this, higher level. It's also only a
    # suggestion rather than a command so it may not even take affect. Currently
    # we just test that the response completes without any issues, it would be nice
    # to have a more robust test here.
    @session.buffer_size = 1

    body = nil

    lambda {
      response = @session.get("/test")
      body = YAML::load(response.body)
    }.should_not raise_error

    body.request_method.should == "GET"
  end

  def encode_authz(user, passwd)
    "Basic " + Base64.encode64("#{user}:#{passwd}").strip
  end

end
