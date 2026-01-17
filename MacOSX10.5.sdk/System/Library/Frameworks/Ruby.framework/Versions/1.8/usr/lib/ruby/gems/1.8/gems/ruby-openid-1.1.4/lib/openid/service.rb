 require 'rexml/document'

begin
  require 'yadis'
rescue LoadError
  require 'rubygems'
  require_gem 'ruby-yadis'
end

module OpenID

  # OpenIDService is an object representation of an OpenID server,
  # and the services it provides.  It contains a useful information such
  # as the server URL, and information about the OpenID identity bound
  # to the server.  OpenIDService object should be produced using the
  # OpenIDService.from_service class method with a Yadis Service object.
  # See the ruby Yadis library for more information:
  #
  # http://www.openidenabled.com/yadis/libraries/ruby
  #
  # Unless you choose to do your own discovery and interface with
  # OpenIDConsumer through the OpenIDConsumer.begin_without_discovery
  # method, you won't need to ever use this object directly.  It is used
  # internally by the OpenIDConsumer object.
  class OpenIDServiceEndpoint < ServiceEndpoint
    
    @@namespace = {
      'xrdsns' => 'xri://$xrds',
      'xrdns' => 'xri://$xrd*($v*2.0)',
      'openidns' => 'http://openid.net/xmlns/1.0'
    }
    attr_accessor :service_types, :uri, :yadis_url, :delegate_url, :xrds_uri, :canonical_id

    # Class method to produce OpenIDService objects. Call with a Yadis Service
    # object.  Will return nil if the Service object does not represent an
    # an OpenID server.
    def OpenIDServiceEndpoint.from_endpoint(service, versions=nil)
      return nil unless OpenIDServiceEndpoint.is_type?(service, versions)

      s = new
      s.service_types = service.service_types
      s.uri = service.uri
      s.yadis_url = service.yadis.uri if service.yadis
      s.xrds_uri = service.yadis.xrds_uri if service.yadis
      s.canonical_id = service.canonical_id

      s.delegate_url = nil
      REXML::XPath.each(service.element, 'openidns:Delegate',
                        @@namespace) do |e|
        s.delegate_url = e.text.strip
      end

      return s
    end

    # Class method to determine if a Yadis service object is an OpenID server.
    # +versions+ is a list of Strings representing the versions of the OpenID
    # protocol you support.  Only service that match one of the versions will
    # return a value that evaluates to true.  If no +versions+ list is
    # specified, all versions will be accepted.
    def OpenIDServiceEndpoint.is_type?(service, versions=nil)
      # escape the period in the version numbers
      versions.collect! {|v| v.gsub('.', '\.')} if versions
      
      base_url = 'http://openid\.net/signon/'
      base_url += '(' + versions.join('|') + '){1}' if versions
      
      service.service_types.each do |st|
        return true if st.match(base_url)
      end

      return false
    end

    # Alias for +supports?+
    def uses_extension?(extension_url)
      return supports?(extension_url)
    end
    
    # Same as uses_extension? Checks to see if the provided URL is
    # in the list of service types. Example that checks for support
    # of the simple registratino protocol:
    #
    #   service.supports?('http://openid.net/sreg/1.0')
    #
    def supports?(url)
      return @service_types.member?(url)
    end

    # Returns the OpenID delegate URL.  This is the URL on the OpenID server,
    # For example if example.com delegates to example-server.com/user, then
    # this will return example-server.com/user
    def delegate
      @delegate_url or self.consumer_id
    end

    # Returns the OpenID server endpoint URL.
    def server_url
      @uri
    end
    
    # Returns user's URL which resides on the OpenID server.  For
    # example if http://example.com/ delegates to http://example.myopenid.com/,
    # then http://example.myopenid.com/ will be returned by this method.
    def server_id
      self.delegate
    end

    # The URL the user entered to authenticate.  For example, if
    # http://example.com/ delegates to http://example.myopenid.com/, this
    # method will return http://example.com/
    def consumer_id
      @yadis_url
    end

    def canonical_id
      @canonical_id or self.consumer_id
    end
  end


  # Used for providing an OpenIDService like object
  # to the OpenID library for 1.X link rel discovery.
  # See the documentation for OpenID::OpenIDService for more information
  # on what this object does.
  class FakeOpenIDServiceEndpoint < OpenIDServiceEndpoint
    
    def initialize(consumer_id, server_id, server_url)
      @uri = server_url
      @delegate = server_id
      @yadis_url = consumer_id     
      @service_types = ['http://openid.net/signon/1.0']
      @yadis = nil
      @xrds_uri = nil
    end

    def delegate
      @delegate
    end

    def supports?(url)
      false
    end

  end

end
