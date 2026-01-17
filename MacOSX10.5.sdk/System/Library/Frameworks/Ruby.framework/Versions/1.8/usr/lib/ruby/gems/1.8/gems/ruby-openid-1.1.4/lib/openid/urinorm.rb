require 'uri'

UNRESERVED = [false]*256
('A'[0]..'Z'[0]).each {|i| UNRESERVED[i] = true}
('a'[0]..'z'[0]).each {|i| UNRESERVED[i] = true}
('0'[0]..'9'[0]).each {|i| UNRESERVED[i] = true}
%W(- . _ ~).each {|i| UNRESERVED[i[0]] = true}

module OpenID

  module Util
    
    def Util._remove_dot_segments(path)
      result_segments = []

      while path.length > 0
        if path.starts_with?('../')
          path = path[3..-1]
        elsif path.starts_with?('./')
          path = path[2..-1]
        elsif path.starts_with?('/./')
          path = path[2..-1]
        elsif path == '/.'
          path = '/'
        elsif path.starts_with?('/../')
          path = path[3..-1]
          result_segments.pop if result_segments.length > 0
        elsif path == '/..'
          path = '/'
          result_segments.pop if result_segments.length > 0
        elsif path == '..' or path == '.'
          path = ''
        else
          i = 0
          i = 1 if path[0].chr == '/'
          i = path.index('/', i)
          i = path.length if i.nil?
          result_segments << path[0...i]
          path = path[i..-1]
        end
      end
      
      return result_segments.join('')
    end

    def Util.urinorm(uri)
      uri = URI.parse(uri)
      
      raise URI::InvalidURIError.new('no scheme') unless uri.scheme
      uri.scheme = uri.scheme.downcase
      unless ['http','https'].member?(uri.scheme)
        raise URI::InvalidURIError.new('Not an HTTP or HTTPS URI')
      end

      raise URI::InvalidURIError.new('no host') unless uri.host
      uri.host = uri.host.downcase

      uri.path = _remove_dot_segments(uri.path)
      uri.path = '/' if uri.path.length == 0
      
      uri = uri.normalize.to_s
      uri = uri.gsub(/%[0-9a-zA-Z]{2}/) {
        i = $&[1..2].upcase.to_i(16)
        UNRESERVED[i] ? i.chr : $&.upcase
      }

      return uri
    end

  end

end
