require 'yadis/yadis'

class YadisServiceManager

  attr_reader :starting_url, :yadis_url, :services, :session_key, :current

  def initialize(starting_url, yadis_url, services)
    @starting_url = starting_url
    @yadis_url = yadis_url
    @services = services
    @current = nil
  end

  def next
    @current = @services.shift
  end

  def for_url?(url)
    url == @starting_url or url == @yadis_url
  end

  def started?
    not @current.nil?
  end

  def length
    @services.length
  end

end

class Discovery

  @@default_suffix = 'auth'
  @@prefix = '_yadis_services_'

  # expects a normalized url
  def initialize(session, url, session_key_suffix=nil)
    @session = session
    @url = url
    @session_key = @@prefix + (session_key_suffix or @@default_suffix)
  end

  def next_service
    manager = self.get_manager
    if manager and manager.length <= 0
      self.destroy_manager
      manager = nil
    end

    unless manager
      begin
        yadis_url, services = self.discover
      rescue YADISParseError, YADISHTTPError
        manager = nil
      else
        manager = self.create_manager(services, yadis_url)   
      end     
    end

    if manager
      service = manager.next
      self.store_manager(manager)
    else
      service = nil
    end
    
    return service
  end

  def finish
    manager = self.get_manager
    return nil unless manager

    service = manager.current
    self.destroy_manager
    return service
  end

  def current
    manager = self.get_manager
    return nil unless manager
    return manager.current
  end

  def get_manager
    manager = @session[@session_key]

    # make sure we've got the right manager here
    if manager and manager.for_url?(@url)
      return manager
    end

    return nil
  end

  def create_manager(services, yadis_url=nil)
    if self.get_manager
      raise ArgumentError, "There is already a manager for #{@url}"
    end

    if services.length > 0
      manager = YadisServiceManager.new(@url, yadis_url, services)
      self.store_manager(manager)
    else
      manager = nil
    end

    return manager
  end

  def destroy_manager
    if self.get_manager
      begin
        @session.delete(@session_key)
      rescue
        # sometimes Hash like session objects don't have a delete
        # method.  We handle that case by assigning nil to the session[key]
        @session[@session_key] = nil
      end
    end
  end

  def store_manager(manager)
    @session[@session_key] = manager
  end

  # The filter argument is a Proc that will be used to call
  # YADIS.filter_services.  See the documentation for YADIS.filter_services
  # for more information about writing filters.
  def discover(filter=nil)
    y = YADIS.new(@url)
    
    # a default filter which sends through everything.  you should
    # probably consider writing a custom filter and passing it in.
    unless filter
      filter = lambda {|s| s}
    end

    return [y.uri, y.filter_services(filter)]    
  end

end


