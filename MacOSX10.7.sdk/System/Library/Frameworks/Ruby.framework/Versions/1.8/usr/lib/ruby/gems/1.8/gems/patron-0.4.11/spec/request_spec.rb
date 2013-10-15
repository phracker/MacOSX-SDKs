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


describe Patron::Request do

  before(:each) do
    @request = Patron::Request.new
  end

  describe :action do

    it "should accept :get, :put, :post, :delete and :head" do
      [:get, :put, :post, :delete, :head, :copy].each do |action|
        lambda {@request.action = action}.should_not raise_error
      end
    end

    it "should raise an exception when assigned a bad value" do
      lambda {@request.action = :foo}.should raise_error(ArgumentError)
    end

  end

  describe :timeout do

    it "should raise an exception when assigned a negative number" do
      lambda {@request.timeout = -1}.should raise_error(ArgumentError)
    end

    it "should raise an exception when assigned 0" do
      lambda {@request.timeout = 0}.should raise_error(ArgumentError)
    end

  end

  describe :max_redirects do

    it "should raise an error when assigned an integer smaller than -1" do
      lambda {@request.max_redirects = -2}.should raise_error(ArgumentError)
    end

  end

  describe :headers do

    it "should raise an error when assigned something other than a hash" do
      lambda {@request.headers = :foo}.should raise_error(ArgumentError)
    end

  end

  describe :buffer_size do

    it "should raise an exception when assigned a negative number" do
      lambda {@request.buffer_size = -1}.should raise_error(ArgumentError)
    end

    it "should raise an exception when assigned 0" do
      lambda {@request.buffer_size = 0}.should raise_error(ArgumentError)
    end

  end
end
