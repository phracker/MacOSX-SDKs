require "openid/util"
require "openid/service"
require "openid/parse"

# try and use the yadis gem, falling back to system yadis
begin
  require 'rubygems'
  require_gem 'ruby-yadis', ">=0.3.3"  
rescue LoadError
  require "yadis"
end

module OpenID

  OPENID_IDP_2_0_TYPE = 'http://openid.net/server/2.0'
  OPENID_2_0_TYPE = 'http://openid.net/signon/2.0'
  OPENID_1_2_TYPE = 'http://openid.net/signon/1.2'
  OPENID_1_1_TYPE = 'http://openid.net/signon/1.1'
  OPENID_1_0_TYPE = 'http://openid.net/signon/1.0'
  OPENID_TYPE_URIS = [OPENID_2_0_TYPE,OPENID_1_2_TYPE,
                     OPENID_1_1_TYPE,OPENID_1_0_TYPE]

  # OpenID::Discovery encapsulates the logic for doing Yadis and OpenID 1.0
  # style server discovery.  This class uses a session object to manage 
  # a list of tried OpenID servers for implemeting server fallback.  This is
  # useful the case when a user's primary server(s) is not available, and
  # will allow then to try again with one of their alternates.
  class OpenIDDiscovery < Discovery

    def initialize(session, url, fetcher, suffix=nil)
      super(session, url, suffix)
      @fetcher = fetcher
    end

    # Pass in a custom filter here if you like.  Otherwise you'll get all
    # OpenID sso services. filter should produce objects or subclasses of
    # OpenIDServiceEndpoint.
    def discover(filter=nil)
      unless filter
        filter = lambda {|s| OpenIDServiceEndpoint.from_endpoint(s)}
      end
      
      begin
        # do yadis discover, filtering out OpenID services
        return super(filter)
      rescue YADISParseError, YADISHTTPError

        # Couldn't do Yadis discovery, fall back on OpenID 1.0 disco
        status, service = self.openid_discovery(@url)
        if status == SUCCESS
          return [service.consumer_id, [service]]
        end
      end

      return [nil, []]
    end

    # Perform OpenID 1.0 style link rel discovery.  No string normalization
    # will be done on +url+.  See Util.normalize_url for information on
    # textual URL transformations.
    def openid_discovery(url)
      ret = @fetcher.get(url)
      return [HTTP_FAILURE, nil] if ret.nil?
      
      consumer_id, data = ret
      server = nil
      delegate = nil
      parse_link_attrs(data) do |attrs|
        rel = attrs["rel"]
        if rel == "openid.server" and server.nil?
          href = attrs["href"]
          server = href unless href.nil?
        end
        
        if rel == "openid.delegate" and delegate.nil?
          href = attrs["href"]
          delegate = href unless href.nil?
        end
      end

      return [PARSE_ERROR, nil] if server.nil?
    
      server_id = delegate.nil? ? consumer_id : delegate

      consumer_id = OpenID::Util.normalize_url(consumer_id)
      server_id = OpenID::Util.normalize_url(server_id)
      server_url = OpenID::Util.normalize_url(server)
                  
      service = OpenID::FakeOpenIDServiceEndpoint.new(consumer_id,
                                                      server_id,
                                                      server_url)
      return [SUCCESS, service]
    end    

  end

  class XRIDiscovery < Discovery
    def initialize(session, iname, suffix=nil)
      super(session, iname, suffix)
    end

    def discover(filter=nil)
      begin
        services = XRI::ProxyResolver.new.query(@url, OPENID_TYPE_URIS)
      rescue XRI::XRIHTTPError, ArgumentError
        return [nil, []]
      end
      endpoints = []
      services.each {|s|
        se = OpenIDServiceEndpoint.from_endpoint(s)
        if se
          se.delegate_url = @url
          se.yadis_url = @url
          endpoints << se
        end
      }
      return [@url, endpoints]      
    end

  end

end
