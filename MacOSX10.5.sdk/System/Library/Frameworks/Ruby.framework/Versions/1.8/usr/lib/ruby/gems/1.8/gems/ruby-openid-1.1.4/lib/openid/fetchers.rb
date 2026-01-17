require "uri"
require "openid/util"

# Try to use net/https, falling back to no SSL support if it is not available
begin
  require 'net/https'
rescue LoadError
  OpenID::Util.log('WARNING: no SSL support found.  Will not be able to fetch HTTPS URLs!')
  HAS_OPENSSL = false
  require 'net/http'  
else
  HAS_OPENSSL = true
end

# Not all versions of Ruby 1.8.4 have the version of post_connection_check
# that properly handles wildcard hostnames.  This version of
# post_connection_check is copied from post April 2006 release of 1.8.4.
module Net
  class HTTP
    def post_connection_check(hostname)
      check_common_name = true
      cert = @socket.io.peer_cert
      cert.extensions.each { |ext|
        next if ext.oid != "subjectAltName"
        ext.value.split(/,\s+/).each{ |general_name|
          if /\ADNS:(.*)/ =~ general_name
            check_common_name = false
            reg = Regexp.escape($1).gsub(/\\\*/, "[^.]+")
            return true if /\A#{reg}\z/i =~ hostname
          elsif /\AIP Address:(.*)/ =~ general_name
            check_common_name = false
            return true if $1 == hostname
          end
        }
      }
      if check_common_name
        cert.subject.to_a.each{ |oid, value|
          if oid == "CN"
            reg = Regexp.escape(value).gsub(/\\\*/, "[^.]+")
            return true if /\A#{reg}\z/i =~ hostname
          end
        }
      end
      raise OpenSSL::SSL::SSLError, "hostname does not match"
    end
  end
end

module OpenID

  # Base Object used by consumer to send http messages
  class Fetcher

    # Fetch the content of url, following redirects, and return the
    # final url and page data.  Return nil on failure.    
    def get(url)
      raise NotImplementedError
    end
    
    # Post the body string to url. Return the resulting url and page data.
    # Return nil on failure    
    def post(url, body)
      raise NotImplementedError
    end
    
  end
  
  # Implemetation of OpenID::Fetcher that uses ruby's Net::HTTP
  class StandardFetcher < Fetcher
    
    attr_accessor :ca_path

    def initialize(read_timeout=20, open_timeout=20)
      @read_timeout = read_timeout
      @open_timeout = open_timeout
      @ca_path = nil
    end
    
    def get(url)    
      resp, final_url = do_get(url)
      if resp.nil?
        nil
      else
        [final_url, resp.body]
      end
    end
  
    def post(url, body)
      begin
        uri = URI.parse(url)
        http = get_http_obj(uri)
        resp = http.post(uri.request_uri, body,
                         {"Content-type"=>"application/x-www-form-urlencoded"})
      rescue
        nil
      else
        [uri.to_s, resp.body]
      end
    end

    protected
    
    # return a Net::HTTP object ready for use    
    def get_http_obj(uri)
      http = Net::HTTP.new(uri.host, uri.port)
      http.read_timeout = @read_timeout
      http.open_timeout = @open_timeout

      if uri.scheme == 'https'

        if HAS_OPENSSL
          http.use_ssl = true

          if @ca_path
            http.verify_mode = OpenSSL::SSL::VERIFY_PEER
            http.ca_file = @ca_path
          else
            OpenID::Util.log('WARNING: making https request without verifying server certificate.')
            http.verify_mode = OpenSSL::SSL::VERIFY_NONE
          end
          
        end

      end

      return http
    end
    
    # do a GET following redirects limit deep
    
    def do_get(url, limit=5)
      if limit == 0
        return nil
      end
      begin
        u = URI.parse(url)
        http = get_http_obj(u)
        http.start {
          if HAS_OPENSSL and u.is_a?(URI::HTTPS) and @ca_path
            # do the post_connection_check, which verifies that
            # the host matches the cert
            http.post_connection_check(u.host)
          end
        }
        resp = http.get(u.request_uri)
      rescue
        nil
      else
        case resp
        when Net::HTTPSuccess then [resp, URI.parse(url).to_s]
        when Net::HTTPRedirection then do_get(resp["location"], limit-1)
        else
          nil
        end
      end
    end
    
  end
  
end
