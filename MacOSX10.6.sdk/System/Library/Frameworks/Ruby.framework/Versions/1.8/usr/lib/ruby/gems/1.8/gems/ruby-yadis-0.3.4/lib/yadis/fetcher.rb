require "uri"

begin
  require "net/https"
rescue LoadError
  HAS_OPENSSL_ = false
  require 'net/http'
else  
  HAS_OPENSSL_ = true
end

class NetHTTPFetcher
    
  attr_accessor :ca_path
  
  def initialize(read_timeout=20, open_timeout=20)
    @read_timeout = read_timeout
    @open_timeout = open_timeout
    @ca_path = nil
  end
    
  def get(url, params = nil)    
    resp, final_url = do_get(url, params)
    if resp.nil?
      nil
    else
      [final_url, resp]
    end
  end
  
  protected
    
    # return a Net::HTTP object ready for use    
    def get_http_obj(uri)
      http = Net::HTTP.new(uri.host, uri.port)
      http.read_timeout = @read_timeout
      http.open_timeout = @open_timeout

      if uri.scheme == 'https'        
        if HAS_OPENSSL_
          http.use_ssl = true
          if @ca_path
            http.ca_file = @ca_path
            http.verify_mode = OpenSSL::SSL::VERIFY_PEER
          else
            http.verify_mode = OpenSSL::SSL::VERIFY_NONE
            STDERR.puts("Warning: fetching over https without verifying server certificate")
          end
        else
          STDERR.puts('Warning: trying to fetch HTTPS URL without OpenSSL support')
        end
      end

      return http
    end
    
    # do a GET following redirects limit deep    
    def do_get(url, params, limit=5)
      if limit == 0
        return nil
      end
      begin
        uri = URI.parse(url)
        http = get_http_obj(uri)
        resp = http.request_get(uri.request_uri, params)
      rescue
        nil
      else
        case resp
        when Net::HTTPSuccess
          return [resp, URI.parse(url).to_s]
        when Net::HTTPRedirection
          return do_get(resp["location"], params, limit-1)
        else
          return nil
        end
      end
    end

end
