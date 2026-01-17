require 'rexml/document'
require 'yadis/service'

# Class that handles XRDS parsing and XRD Service element extraction.

module XRDSUtil
  
  @@namespaces = {
    'xrdsns' => 'xri://$xrds',
    'xrdns' => 'xri://$xrd*($v*2.0)'
  }

  def last_xrd(root_element)
    REXML::XPath.match(root_element, '/xrdsns:XRDS/xrdns:XRD',
                       @@namespaces)[-1]
  end
  
end

class XRDS

  include XRDSUtil
  attr_reader :xml

  # Method for producing a valid XRDS object.  Accepts an XML
  # String. Returns an XRDS object on success, or nil on failure.
  # Same as calling XRDS.new, but does not raise ArgumentErrors.
  def XRDS.parse(xml)
    begin
      return new(xml)
    rescue
      return nil
    end
  end

  # Create a new XRDS object.  Raises ArgumentError if xml_text is
  # malformed or invalid XRDS.
  def initialize(xml_text)
    @xml_text = xml_text
    parse_xml(xml_text)
  end

  def _dump(depth)
    return @xml_text
  end

  def XRDS._load(s)
    XRDS.new(s)
  end

  def parse_xml(xml_text)   
    begin
      xml = @xml = REXML::Document.new(xml_text)
    rescue
      raise ArgumentError, "Can't parse XRDS"
    end
    
    if xml.root.nil?
      raise ArgumentError, "No document root"
    end

    xrd = self.last_xrd(xml.root)
    raise ArgumentError, "No XRD Elements found" if xrd.nil?
   
    @services = {}  # keyed by [service_priority, uri_priority]
    REXML::XPath.each(xrd, 'xrdns:Service', @@namespaces) do |s|
      _create_services(s)
    end
    
    REXML::XPath.each(xrd, 'xrdns:CanonicalID', @@namespaces) do |c|
      canonical_id = c.text.strip
      if canonical_id.length > 0
        self.services.each {|s| s.canonical_id = canonical_id}
      end
    end

  end


  # Returns an Array of ServiceEndpoint objects, sorted by priority.  Highest
  # priority is at element 0.
  def services
    s = []

    @services.keys.sort.each do |key|
      services_list = @services[key].dup

      # randomize services with the same priority
      while services_list.length > 0
        s << services_list.delete_at((rand * services_list.length).to_i)
      end

    end
    
    return s
  end

  private

  # create services objects
  def _create_services(service_element)
    service = ServiceEndpoint.new
    service.element = service_element
    service.uri = nil
    service.service_types = []

    REXML::XPath.each(service_element, 'xrdns:Type', @@namespaces) do |t|
      # XXX: If the Type element is empty, should we add an empty element
      # to our list, or none at all?
      service.service_types << t.text.strip unless t.text.nil?
    end

    sp = service_element.attributes['priority']
    service_priority = sp ? sp.to_i : -1
    has_uri = false

    REXML::XPath.each(service.element, 'xrdns:URI', @@namespaces) do |uri|
      has_uri = true
      _service = service.dup
      _service.uri = uri.text.strip
      
      up = uri.attributes['priority']
      uri_priority = up ? up.to_i : -1
      priority = [service_priority, uri_priority]
      
      _add_service(priority, _service)
    end
      
    unless has_uri
      priority = [service_priority, -1]
      _add_service(priority, service)
    end

  end

  def _add_service(priority, service)
    unless @services.has_key?(priority)
      @services[priority] = []
    end

    # services with the same priority are appended to the list
    @services[priority] << service
  end

end

