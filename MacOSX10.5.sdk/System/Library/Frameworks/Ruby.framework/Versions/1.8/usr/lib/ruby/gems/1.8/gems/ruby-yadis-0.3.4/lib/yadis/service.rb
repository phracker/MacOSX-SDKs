# Class representing an XRD Service element.  
class ServiceEndpoint

  attr_accessor :service_types, :uri, :yadis_uri, :element, :yadis, :canonical_id

  def initialize
    @service_types = []
    @uri = nil
    @yadis_uri = nil
    @element = nil
    @canonical_id = nil
  end

  def match_type_uris(type_uris)
    type_uris.find_all {|t| @service_types.member?(t)}
  end

  def ==(other)
    return self.instance_variables == other.instance_variables
  end

end
