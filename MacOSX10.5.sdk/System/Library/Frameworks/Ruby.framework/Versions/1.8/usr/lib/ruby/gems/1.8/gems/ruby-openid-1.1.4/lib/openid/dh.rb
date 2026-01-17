require "openid/util"

module OpenID

  # Encapsulates a Diffie-Hellman key exchange.  This class is used
  # internally by both the consumer and server objects.
  #
  # Read more about Diffie-Hellman on wikipedia:
  # http://en.wikipedia.org/wiki/Diffie-Hellman
  class DiffieHellman

    @@DEFAULT_MOD = 155172898181473697471232257763715539915724801966915404479707795314057629378541917580651227423698188993727816152646631438561595825688188889951272158842675419950341258706556549803580104870537681476726513255747040765857479291291572334510643245094715007229621094194349783925984760375594985848253359305585439638443
    @@DEFAULT_GEN = 2

    attr_reader :p, :g, :public
    
    def DiffieHellman.from_base64(p=nil, g=nil)
      unless p.nil?
        p = OpenID::Util.base64_to_num(p)
      end
      unless g.nil?
        g = OpenID::Util.base64_to_num(g)
      end
      DiffieHellman.new(p, g)
    end

    def initialize(p=nil, g=nil)
      @p = p.nil? ? @@DEFAULT_MOD : p
      @g = g.nil? ? @@DEFAULT_GEN : g
      
      @private = OpenID::Util.rand(@p-2) + 1
      @public = OpenID::Util.powermod(@g, @private, @p)
    end

    def get_shared_secret(composite)
      OpenID::Util.powermod(composite, @private, @p)
    end

    def xor_secrect(composite, secret)
      dh_shared = get_shared_secret(composite)
      sha1_dh_shared = OpenID::Util.sha1( \
                          OpenID::Util.num_to_str(dh_shared))
      return OpenID::Util.strxor(secret, sha1_dh_shared)
    end

  end

end
