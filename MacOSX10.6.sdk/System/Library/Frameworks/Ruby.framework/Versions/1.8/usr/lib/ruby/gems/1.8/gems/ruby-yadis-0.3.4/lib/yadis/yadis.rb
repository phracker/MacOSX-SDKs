require 'yadis/xrds'
require 'yadis/fetcher'
require 'yadis/parsehtml'

class YADISParseError < StandardError; end
class YADISHTTPError < StandardError; end


# High level class for performing the Yadis protocol on a given URL. The
# YADIS.discover class method is a good place to get started in determining
# which services a URL supports.
class YADIS

  @@ca_path = nil
  attr_accessor :uri, :xrds_uri, :xrds

  # Discover services for a given URI.  Please note that no normalization 
  # will be done to the passed in URI, it should be a textually
  # valid URI string before calling discover.
  #
  # Returns nil if no XRDS was found, or a YADIS object on success.  This
  # method is essentially the same as YADIS.new, but does not raise any
  # exceptions.
  def YADIS.discover(uri)
    return nil unless uri
    begin
      return YADIS.new(uri)
    rescue
      return nil
    end
  end

  # Set the path to a certificate authority pem file, for verifying
  # server certificates of HTTPS pages.  If you are interested in verifying
  # certs like the mozilla web browser, have a look at the files here:
  #
  # http://curl.haxx.se/docs/caextract.html
  def YADIS.ca_path=(ca_path)
    ca_path = ca_path.to_s
    if File.exists?(ca_path)
      @@ca_path = ca_path
    else
      raise ArgumentError, "#{ca_path} is not a valid file path"
    end
  end

  # Discover services for a URI using the Yadis protocol.  +uri+ should
  # be a valid URI represented as a string.  This method may raise
  # YADISParseError in the case of an invalid or unparsable XRDS file,
  # or YADISHTTPError is the URI cannot be fetched.
  def initialize(uri)
    http = NetHTTPFetcher.new
    http.ca_path = @@ca_path if @@ca_path    
    headers = {'Accept' => 'application/xrds+xml'}

    response = http.get(uri, headers)
    raise YADISHTTPError, "Could not fetch #{uri}" if response.nil?

    uri, resp_payload = response
    xrds_uri = uri

    header = resp_payload['x-xrds-location']
    header = resp_payload['x-yadis-location'] if header.nil?

    if header
      xrds_uri = header
      response = http.get(xrds_uri)
      raise YADISHTTPError, "Could not fetch XRDS #{xrds_uri}" if response.nil?
      resp_payload = response[1]
    end

    unless resp_payload['content-type'] == 'application/xrds+xml'
      loc = html_yadis_location(resp_payload.body)
      unless loc.nil?
        xrds_uri, resp_payload = http.get(loc)
      end
    end

    xrds = XRDS.parse(resp_payload.body)
    raise YADISParseError, "Bad XRDS" if xrds.nil?

    @uri = uri
    @xrds_uri = xrds_uri
    @xrds = xrds
  end

  # Returns an Array Service objects sorted by priority.
  def services
    @xrds.services.each {|s| s.yadis = self}
    @xrds.services
  end

  # Returns a list of services, ordered by priority,
  # that match the filter. filter is a Proc object that produces
  # ServiceEnpoint objects, subclasses of ServiceEnpoint or nil.
  # This method is useful for extracting several types of services while
  # maintaining priority, for example you may write a filter Proc to extract
  # OpenID and LID ServiceEnpoint objects.
  def filter_services(filter)
    # product a list of filtered ServiceEndpoint objects.  filtered
    # will contain a list of nil or ServiceEnpoint (subclasses) objects.
    filtered = self.services.collect {|s| filter.call(s)}
    
    # return all object in filtered that are not nil
    return filtered.find_all {|s| s}
  end

end
