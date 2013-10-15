# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

module Jabber
  ##
  # The JID class represents a Jabber Identifier as described by
  # RFC3920 section 3.1.
  #
  # Note that you can use JIDs also for Sorting, Hash keys, ...
  class JID
    include Comparable

    PATTERN = /^(?:([^@]*)@)??([^@\/]*)(?:\/(.*?))?$/

    begin
      require 'idn'
      USE_STRINGPREP = true
    rescue LoadError
      USE_STRINGPREP = false
    end

    ##
    # Create a new JID. If called as new('a@b/c'), parse the string and
    # split (node, domain, resource)
    def initialize(node = "", domain = nil, resource = nil)
      @resource = resource
      @domain = domain
      @node = node
      if @domain.nil? and @resource.nil? and @node
        @node, @domain, @resource = @node.to_s.scan(PATTERN).first
      end

      if USE_STRINGPREP
        @node = IDN::Stringprep.nodeprep(@node) if @node
        @domain = IDN::Stringprep.nameprep(@domain) if @domain
        @resource = IDN::Stringprep.resourceprep(@resource) if @resource
      else
        @node.downcase! if @node
        @domain.downcase! if @domain
      end

      raise ArgumentError, 'Node too long' if (@node || '').length > 1023
      raise ArgumentError, 'Domain too long' if (@domain || '').length > 1023
      raise ArgumentError, 'Resource too long' if (@resource || '').length > 1023
    end

    ##
    # Returns a string representation of the JID
    # * ""
    # * "domain"
    # * "node@domain"
    # * "domain/resource"
    # * "node@domain/resource"
    def to_s
      s = @domain
      s = "#{@node}@#{s}" if @node
      s += "/#{@resource}" if @resource
      return s
    end

    ##
    # Returns a new JID with resource removed.
    # return:: [JID]
    def strip
      JID.new(@node, @domain)
    end
    alias_method :bare, :strip

    ##
    # Removes the resource (sets it to nil)
    # return:: [JID] self
    def strip!
      @resource = nil
      self
    end
    alias_method :bare!, :strip!

    ##
    # Returns a hash value of the String representation
    # (see JID#to_s)
    def hash
      return to_s.hash
    end

    ##
    # Ccompare to another JID
    #
    # String representations are compared, see JID#to_s
    def eql?(o)
      to_s.eql?(o.to_s)
    end

    ##
    # Ccompare to another JID
    #
    # String representations are compared, see JID#to_s
    def ==(o)
      to_s == o.to_s
    end

    ##
    # Compare two JIDs,
    # helpful for sorting etc.
    #
    # String representations are compared, see JID#to_s
    def <=>(o)
      to_s <=> o.to_s
    end

    # Get the JID's node
    def node
      @node
    end

    # Set the JID's node
    def node=(v)
      @node = v.to_s
      if USE_STRINGPREP
        @node = IDN::Stringprep.nodeprep(@node) if @node
      end
    end

    # Get the JID's domain
    def domain
      return nil if @domain.empty?
      @domain
    end

    # Set the JID's domain
    def domain=(v)
      @domain = v.to_s
      if USE_STRINGPREP
        @domain = IDN::Stringprep.nodeprep(@domain)
      end
    end

    # Get the JID's resource
    def resource
      @resource
    end

    # Set the JID's resource
    def resource=(v)
      @resource = v.to_s
      if USE_STRINGPREP
        @resource = IDN::Stringprep.nodeprep(@resource)
      end
    end

    # Escape JID
    def JID::escape(jid)
      return jid.to_s.gsub('@', '%')
    end

    # Test if jid is empty
    def empty?
      to_s.empty?
    end

    # Test id jid is strepped
    def stripped?
      @resource.nil?
    end
    alias_method :bared?, :stripped?
  end
end
