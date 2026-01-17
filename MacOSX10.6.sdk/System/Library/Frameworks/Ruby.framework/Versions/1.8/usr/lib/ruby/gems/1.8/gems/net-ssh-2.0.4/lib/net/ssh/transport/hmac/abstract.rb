require 'openssl'

module Net; module SSH; module Transport; module HMAC

  # The base class of all OpenSSL-based HMAC algorithm wrappers.
  class Abstract

    class <<self
      %w(key_length mac_length digest_class).each do |attribute|
        define_method(attribute) do |*v|
          # satisfy ruby -w
          if !instance_variables.include?("@#{attribute}")
            instance_variable_set("@#{attribute}", nil)
          end

          if v.empty?
            v = instance_variable_get("@#{attribute}")
            if v.nil? && superclass.respond_to?(attribute)
              v = superclass.send(attribute)
              instance_variable_set("@#{attribute}", v)
            end
            v
          else
            instance_variable_set("@#{attribute}", v.first)
          end
        end
      end
    end

    %w(key_length mac_length digest_class).each do |attribute|
      define_method(attribute) { self.class.send(attribute) }
    end

    # The key in use for this instance.
    attr_reader :key

    def initialize(key=nil)
      self.key = key
    end

    # Sets the key to the given value, truncating it so that it is the correct
    # length.
    def key=(value)
      @key = value ? value.to_s[0,key_length] : nil
    end

    # Compute the HMAC digest for the given data string.
    def digest(data)
      OpenSSL::HMAC.digest(digest_class.new, key, data)[0,mac_length]
    end

  end

end; end; end; end
