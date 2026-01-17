require 'openid/util'

module OpenID

  # Represents an "association" between a consumer and server, and
  # is also used for storage of the information exchanged
  # during the openid.mode='associate' transaction.
  # This class is used by the both the server and consumer.
  class Association
    @@version = '2'
    @@assoc_keys = [
                    'version',
                    'handle',
                    'secret',
                    'issued',
                    'lifetime',
                    'assoc_type'
                   ]

    attr_reader :handle, :secret, :issued, :lifetime, :assoc_type

    def Association.from_expires_in(expires_in, handle, secret, assoc_type)
      issued = Time.now.to_i
      lifetime = expires_in
      new(handle, secret, issued, lifetime, assoc_type) 
    end

    def Association.serialize(assoc)
      data = [
              '2',
              assoc.handle,
              OpenID::Util.to_base64(assoc.secret),
              assoc.issued.to_i.to_s,
              assoc.lifetime.to_i.to_s,
              assoc.assoc_type              
             ]
  
      lines = ""
      (0...@@assoc_keys.length).collect do |i| 
        lines += "#{@@assoc_keys[i]}: #{data[i]}\n"
      end
    
      lines
    end

    def Association.deserialize(assoc_s)
      keys = []
      values = []
      assoc_s.split("\n").each do |line|
        k, v = line.split(":", 2)
        keys << k.strip
        values << v.strip
      end
  
      version, handle, secret, issued, lifetime, assoc_type = values
      raise 'VersionError' if version != @@version
  
      secret = OpenID::Util.from_base64(secret)
      issued = issued.to_i
      lifetime = lifetime.to_i
      Association.new(handle, secret, issued, lifetime, assoc_type)
    end

    def initialize(handle, secret, issued, lifetime, assoc_type)
      if assoc_type != 'HMAC-SHA1'
        raise ArgumentError, "HMAC-SHA1 is the only supported assoc_type, got #{assoc_type}"
      end
      
      @handle = handle
      @secret = secret
      @issued = issued
      @lifetime = lifetime
      @assoc_type = assoc_type
    end

    def expires_in
      [0, @issued + @lifetime - Time.now.to_i].max
    end

    def expired?
      return expires_in == 0
    end

    def sign(pairs)
      kv = ''
      pairs.each {|k,v| kv << "#{k}:#{v}\n"}
      return OpenID::Util.hmac_sha1(@secret, kv)
    end

    def sign_hash(fields, hash, prefix='openid.')
      pairs = []
      fields.each { |f| pairs << [f, hash[prefix+f]] }
      return OpenID::Util.to_base64(sign(pairs))
    end

    def add_signature(fields, hash, prefix='openid.')
      sig = sign_hash(fields, hash, prefix)
      signed = fields.join(',')
      hash[prefix+'sig'] = sig
      hash[prefix+'signed'] = signed
    end

    def ==(other)
      self.instance_variable_hash == other.instance_variable_hash
    end

  end

end
