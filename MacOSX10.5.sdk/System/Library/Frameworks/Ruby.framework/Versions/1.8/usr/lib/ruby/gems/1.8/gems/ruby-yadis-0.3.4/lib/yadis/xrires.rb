require "cgi"
require "yadis/xri"
require "yadis/xrds"
require "yadis/fetcher"

module XRI

  class XRIHTTPError < StandardError; end
  
  class ProxyResolver

    DEFAULT_PROXY = 'http://proxy.xri.net/'
    
    def initialize(proxy_url=nil)
      if proxy_url
        @proxy_url = proxy_url
      else
        @proxy_url = DEFAULT_PROXY
      end

      @proxy_url += '/' unless @proxy_url.match('/$')
    end

    def query_url(xri, service_type=nil)
      # URI normal form has a leading xri://, but we need to strip
      # that off again for the QXRI.  This is under discussion for
      # XRI Resolution WD 11.
      # 
      qxri = XRI.to_uri_normal(xri)[6..-1]
      hxri = @proxy_url + qxri
      args = {'_xrd_r' => 'application/xrds+xml'}
      if service_type
        args['_xrd_t'] = service_type
      else
        # don't perform service endpoint selection 
        args['_xrd_r'] += ';sep=false'
      end

      return XRI.append_args(hxri, args)
    end

    def query(xri, service_types)
      # these can be query args or http headers, needn't be both.
      # headers = {'Accept' => 'application/xrds+xml;sep=true'}
      fetcher = NetHTTPFetcher.new
      services = service_types.collect { |service_type|
        url = self.query_url(xri, service_type)
        response = fetcher.get(url)
        raise XRIHTTPError, "Could not fetch #{xri}" if response.nil?
        xrds = XRDS.new(response[1].body)
        return xrds.services unless xrds.nil?
      }
      # TODO:
      #  * If we do get hits for multiple service_types, we're almost 
      #    certainly going to have duplicated service entries and 
      #    broken priority ordering.
      services = services.inject([]) { |flatter, some_services|
        flatter.concat(some_services) unless some_services.nil?
      }
    end
  end

  def XRI.urlencode(args)
    a = []
    args.each do |key, val|
      a << (CGI::escape(key) + "=" + CGI::escape(val))
    end
    a.join("&")
  end

  def XRI.append_args(url, args)
    return url if args.length == 0
    
    # rstrip question marks
    rstripped = url.dup
    while rstripped[-1].chr == '?'
      rstripped = rstripped[0...rstripped.length-1]
    end
    
    if rstripped.index('?')
      sep = '&'
    else
      sep = '?'
    end
    
    return url + sep + XRI.urlencode(args)
  end

end

# Example:
#  r = XRI::ProxyResolver.new('http://proxy.xri.net/')
#  j = r.query('=keturn', ['xri://+i-service*(+forwarding)*($v*1.0)'])
#  Stderr.puts("the answer is #{j}")
