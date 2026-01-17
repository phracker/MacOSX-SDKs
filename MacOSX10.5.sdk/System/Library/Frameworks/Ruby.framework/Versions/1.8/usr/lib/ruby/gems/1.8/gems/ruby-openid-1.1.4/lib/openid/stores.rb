require "openid/util"

module OpenID

  # Interface for the abstract Store
  class Store

    @@AUTH_KEY_LEN = 20

    # Put a Association object into storage
    def store_association(server_url, association)
      raise NotImplementedError
    end

    # Returns a Association object from storage that matches
    # the server_url.  Returns nil if no such association is found or if
    # the one matching association is expired. (Is allowed to GC expired
    # associations when found.)
    def get_association(server_url, handle=nil)
      raise NotImplementedError
    end

    # If there is a matching association, remove it from the store and
    # return true, otherwise return false.
    def remove_association(server_url, handle)
      raise NotImplementedError
    end

    # Stores a nonce (which is passed in as a string).
    def store_nonce(nonce)
      raise NotImplementedError
    end

    # If the nonce is in the store, remove it and return true. Otherwise
    # return false.
    def use_nonce(nonce)
      raise NotImplementedError
    end

    # Returns a 20-byte auth key used to sign the tokens, to ensure
    # that they haven't been tampered with in transit. It must return
    # the same key every time it is called.   
    def get_auth_key
      raise NotImplementedError
    end

    # Method return true if the store is dumb-mode-style store.
    def dumb?
      false
    end

  end


  class DumbStore < Store
    
    def initialize(secret_phrase)
      require "digest/sha1"
      @auth_key = Digest::SHA1.hexdigest(secret_phrase)
    end

    def store_association(server_url, assoc)
      nil
    end

    def get_association(server_url, handle=nil)
      nil
    end
  
    def remove_association(server_url, handle)
      false
    end

    def store_nonce(nonce)
      nil
    end

    def use_nonce(nonce)
      true
    end

    def get_auth_key
      @auth_key
    end

    def dumb?
      true
    end

  end

  class ServerAssocs
    def initialize
      @assocs = {}
    end

    def set(assoc)
      @assocs[assoc.handle] = assoc
    end

    def get(handle)
      @assocs[handle]
    end

    def remove(handle)
      return @assocs.delete(handle)
    end

    def best
      best = nil
      @assocs.each do |k, assoc|
        if best.nil? or best.issued < assoc.issued
          best = assoc
        end
      end
      return best
    end
  end

  # An in-memory implementation of Store.  This class is mainly used
  # for testing, though it may be useful for long-running single process apps.
  #
  # You should probably be looking at OpenID::FilesystemStore
  class MemoryStore < Store

    def initialize
      @server_assocs = {}
      @nonces = {}
      @auth_key = OpenID::Util.random_string(@@AUTH_KEY_LEN)
    end

    def dumb?
      false
    end

    def store_association(server_url, assoc)
      assocs = _get_server_assocs(server_url)
      assocs.set(self.deepcopy(assoc))
    end
    
    def get_association(server_url, handle=nil)
      assocs = _get_server_assocs(server_url)
      return assocs.best if handle.nil?
      return assocs.get(handle)
    end
    
    def remove_association(server_url, handle)
      assocs = _get_server_assocs(server_url)
      return assocs.remove(handle)
    end

    def use_nonce(nonce)
      return true if @nonces.delete(nonce)
      return false
    end

    def store_nonce(nonce)
      @nonces[nonce] = true
    end

    def get_auth_key
      @auth_key
    end

    def _get_server_assocs(server_url)
      unless @server_assocs.has_key?(server_url)
        @server_assocs[server_url] = ServerAssocs.new
      end
      return @server_assocs[server_url]
    end

    def deepcopy(o)
      Marshal.load(Marshal.dump(o))
    end

  end

end
