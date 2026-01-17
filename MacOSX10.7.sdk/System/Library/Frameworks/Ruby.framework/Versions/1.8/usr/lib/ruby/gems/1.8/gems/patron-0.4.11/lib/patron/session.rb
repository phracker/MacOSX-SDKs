## -------------------------------------------------------------------
##
## Patron HTTP Client: Session class
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
require 'patron/error'
require 'patron/request'
require 'patron/response'
require 'patron/session_ext'


module Patron

  # This class represents multiple request/response transactions with an HTTP
  # server. This is the primary API for Patron.
  class Session

    # HTTP connection timeout in seconds. Defaults to 1 second.
    attr_accessor :connect_timeout

    # HTTP transaction timeout in seconds. Defaults to 5 seconds.
    attr_accessor :timeout

    # Maximum number of times to follow redirects.
    # Set to 0 to disable and -1 to follow all redirects. Defaults to 5.
    attr_accessor :max_redirects

    # Prepended to the URL in all requests.
    attr_accessor :base_url

    # Username and password for http authentication
    attr_accessor :username, :password

    # Proxy URL in cURL format ('hostname:8080')
    attr_accessor :proxy

    # Proxy type (default is HTTP), see constants under ProxyType for supported types.
    attr_accessor :proxy_type

    # Standard set of headers that are used in all requests.
    attr_reader :headers

    # Set the authentication type for the request.
    # @see Patron::Request#auth_type
    attr_accessor :auth_type

    # Does this session stricly verify SSL certificates?
    attr_accessor :insecure

    # Set the buffer size for this request. This option will
    # only be set if buffer_size is non-nil
    attr_accessor :buffer_size

    private :ext_initialize, :handle_request, :enable_cookie_session, :set_debug_file

    # Create a new Session object.
    def initialize
      ext_initialize
      @headers = {}
      @timeout = 5
      @connect_timeout = 1
      @max_redirects = 5
      @auth_type = :basic
    end

    # Turn on cookie handling for this session, storing them in memory by
    # default or in +file+ if specified. The +file+ must be readable and
    # writable. Calling multiple times will add more files.
    def handle_cookies(file = nil)
      if file
        path = Pathname(file).expand_path
        unless File.exists?(file) and File.writable?(path.dirname)
          raise ArgumentError, "Can't create file #{path} (permission error)"
        end
        unless File.readable?(file) or File.writable?(path)
          raise ArgumentError, "Can't read or write file #{path} (permission error)"
        end
      end
      enable_cookie_session(path.to_s)
      self
    end

    # Enable debug output to stderr or to specified +file+.
    def enable_debug(file = nil)
      set_debug_file(file.to_s)
    end

    ###################################################################
    ### Standard HTTP methods
    ###

    # Retrieve the contents of the specified +url+ optionally sending the
    # specified headers. If the +base_url+ varaible is set then it is prepended
    # to the +url+ parameter. Any custom headers are merged with the contents
    # of the +headers+ instance variable. The results are returned in a
    # Response object.
    def get(url, headers = {})
      request(:get, url, headers)
    end

    # Retrieve the contents of the specified +url+ as with #get, but the
    # content at the URL is downloaded directly into the specified file.
    def get_file(url, filename, headers = {})
      request(:get, url, headers, :file => filename)
    end

    # As #get but sends an HTTP HEAD request.
    def head(url, headers = {})
      request(:head, url, headers)
    end

    # As #get but sends an HTTP DELETE request.
    def delete(url, headers = {})
      request(:delete, url, headers)
    end

    # Uploads the passed +data+ to the specified +url+ using HTTP PUT. +data+
    # must be a string.
    def put(url, data, headers = {})
      request(:put, url, headers, :data => data)
    end

    # Uploads the contents of a file to the specified +url+ using HTTP PUT.
    def put_file(url, filename, headers = {})
      request(:put, url, headers, :file => filename)
    end

    # Uploads the passed +data+ to the specified +url+ using HTTP POST. +data+
    # must be a string.
    def post(url, data, headers = {})
      request(:post, url, headers, :data => data)
    end

    # Uploads the contents of a file to the specified +url+ using HTTP POST.
    def post_file(url, filename, headers = {})
      request(:post, url, headers, :file => filename)
    end

    # Uploads the contents of a file and data to the specified +url+ using HTTP POST.
    def post_multipart(url, data, filename, headers = {})
      request(:post, url, headers, {:data => data, :file => filename, :multipart => true})
    end

    ###################################################################
    ### WebDAV methods
    ###

    # Sends a WebDAV COPY request to the specified +url+.
    def copy(url, dest, headers = {})
      headers['Destination'] = dest
      request(:copy, url, headers)
    end

    ###################################################################
    ### Basic API methods
    ###

    # Send an HTTP request to the specified +url+.
    def request(action, url, headers, options = {})
      # If the Expect header isn't set uploads are really slow
      headers['Expect'] ||= ''

      req = Request.new
      req.action = action
      req.timeout = self.timeout
      req.connect_timeout = self.connect_timeout
      req.max_redirects = self.max_redirects
      req.headers = self.headers.merge(headers)
      req.username = self.username
      req.password = self.password
      req.multipart = options[:multipart]
      req.upload_data = options[:data]
      req.file_name = options[:file]
      req.proxy = proxy
      req.proxy_type = proxy_type
      req.auth_type = auth_type
      req.insecure = insecure
      req.buffer_size = buffer_size

      req.url = self.base_url.to_s + url.to_s
      raise ArgumentError, "Empty URL" if req.url.empty?

      handle_request(req)
    end
  end
end
