## -------------------------------------------------------------------
##
## Patron HTTP Client: Response class
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

module Patron

  # Represents the response from the HTTP server.
  class Response

    def initialize
      @headers = {}
    end

    attr_reader :url, :status, :status_line, :redirect_count, :body, :headers

    def inspect
      # Avoid spamming the console with the header and body data
      "#<Patron::Response @status_line='#{@status_line}'>"
    end

  private

    # Called by the C code to parse and set the headers
    def parse_headers(header_data)
      header_data.split(/\r\n/).each do |header|
        if header =~ %r|^HTTP/1.[01]|
          @status_line = header.strip
        else
          parts = header.split(':', 2)
          unless parts.empty?
            parts[1].strip! unless parts[1].nil?
            if @headers.has_key?(parts[0])
              @headers[parts[0]] = [@headers[parts[0]]] unless @headers[parts[0]].kind_of? Array
              @headers[parts[0]] << parts[1]
            else
              @headers[parts[0]] = parts[1]
            end
          end
        end
      end
    end

  end
end
