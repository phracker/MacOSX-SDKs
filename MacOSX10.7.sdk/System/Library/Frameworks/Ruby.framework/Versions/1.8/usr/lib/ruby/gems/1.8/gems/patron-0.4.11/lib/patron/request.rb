## -------------------------------------------------------------------
##
## Patron HTTP Client: Request class
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

require 'cgi'

module Patron

  # Represents the information necessary for an HTTP request.
  # This is basically a data object with validation. Not all fields will be
  # used in every request.
  class Request

    VALID_ACTIONS = [:get, :put, :post, :delete, :head, :copy]

    def initialize
      @action = :get
      @headers = {}
      @timeout = 0
      @connect_timeout = 0
      @max_redirects = -1
    end

    attr_accessor :url, :username, :password, :file_name, :proxy, :proxy_type, :auth_type, :insecure, :multipart
    attr_reader :action, :timeout, :connect_timeout, :max_redirects, :headers, :buffer_size
    attr_reader :auth_type

    # Set the type of authentication to use for this request.
    #
    # @param [String, Symbol] type - The type of authentication to use for this request, can be one of
    #   :basic, :digest, or :any
    #
    # @example
    #   sess.username = "foo"
    #   sess.password = "sekrit"
    #   sess.auth_type = :digest
    def auth_type=(type=:basic)
      @auth_type = case type
      when :basic, "basic"
        Request::AuthBasic
      when :digest, "digest"
        Request::AuthDigest
      when :any, "any"
        Request::AuthAny
      else
        raise "#{type.inspect} is an unknown authentication type"
      end
    end

    def upload_data=(data)
      @upload_data = case data
      when Hash
        self.multipart ? data : hash_to_string(data)
      else
        data
      end
    end

    def upload_data
      @upload_data
    end

    def action=(new_action)
      if !VALID_ACTIONS.include?(new_action)
        raise ArgumentError, "Action must be one of #{VALID_ACTIONS.join(', ')}"
      end

      @action = new_action
    end

    def timeout=(new_timeout)
      if new_timeout && new_timeout.to_i < 1
        raise ArgumentError, "Timeout must be a positive integer greater than 0"
      end

      @timeout = new_timeout.to_i
    end

    def connect_timeout=(new_timeout)
      if new_timeout && new_timeout.to_i < 1
        raise ArgumentError, "Timeout must be a positive integer greater than 0"
      end

      @connect_timeout = new_timeout.to_i
    end

    def max_redirects=(new_max_redirects)
      if new_max_redirects.to_i < -1
        raise ArgumentError, "Max redirects must be a positive integer, 0 or -1"
      end

      @max_redirects = new_max_redirects.to_i
    end

    def headers=(new_headers)
      if !new_headers.kind_of?(Hash)
        raise ArgumentError, "Headers must be a hash"
      end

      @headers = new_headers
    end

    def buffer_size=(buffer_size)
      if buffer_size != nil && buffer_size.to_i < 1
        raise ArgumentError, "Buffer size must be a positive integer greater than 0 or nil"
      end

      @buffer_size = buffer_size != nil ? buffer_size.to_i : nil
    end

    def action_name
      @action.to_s.upcase
    end

    def credentials
      return nil if username.nil? || password.nil?
      "#{username}:#{password}"
    end

  private

    # serialize hash for Rails-style params
    def hash_to_string(hash)
      pairs = []
      recursive = Proc.new do |h, prefix|
        h.each_pair do |k,v|
          key = prefix == '' ? k : "#{prefix}[#{k}]"
                                    @action == :post ? v = CGI::escape(v.to_s) : v
          v.is_a?(Hash) ? recursive.call(v, key) : pairs << "#{key}=#{v}"
        end
      end
      recursive.call(hash, '')
      return pairs.join('&')
    end
  end
end
