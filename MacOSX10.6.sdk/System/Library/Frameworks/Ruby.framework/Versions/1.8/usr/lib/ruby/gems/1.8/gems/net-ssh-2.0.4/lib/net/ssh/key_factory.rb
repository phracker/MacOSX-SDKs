require 'net/ssh/transport/openssl'
require 'net/ssh/prompt'

module Net; module SSH

  # A factory class for returning new Key classes. It is used for obtaining
  # OpenSSL key instances via their SSH names, and for loading both public and
  # private keys. It used used primarily by Net::SSH itself, internally, and
  # will rarely (if ever) be directly used by consumers of the library.
  #
  #   klass = Net::SSH::KeyFactory.get("rsa")
  #   assert klass.is_a?(OpenSSL::PKey::RSA)
  #
  #   key = Net::SSH::KeyFacory.load_public_key("~/.ssh/id_dsa.pub")
  class KeyFactory
    # Specifies the mapping of SSH names to OpenSSL key classes.
    MAP = {
      "dh"  => OpenSSL::PKey::DH,
      "rsa" => OpenSSL::PKey::RSA,
      "dsa" => OpenSSL::PKey::DSA
    }

    class <<self
      include Prompt

      # Fetch an OpenSSL key instance by its SSH name. It will be a new,
      # empty key of the given type.
      def get(name)
        MAP.fetch(name).new
      end

      # Loads a private key from a file. It will correctly determine
      # whether the file describes an RSA or DSA key, and will load it
      # appropriately. The new key is returned. If the key itself is
      # encrypted (requiring a passphrase to use), the user will be
      # prompted to enter their password unless passphrase works. 
      def load_private_key(filename, passphrase=nil)
        file = File.read(File.expand_path(filename))

        if file.match(/-----BEGIN DSA PRIVATE KEY-----/)
          key_type = OpenSSL::PKey::DSA
        elsif file.match(/-----BEGIN RSA PRIVATE KEY-----/)
          key_type = OpenSSL::PKey::RSA
        elsif file.match(/-----BEGIN (.*) PRIVATE KEY-----/)
          raise OpenSSL::PKey::PKeyError, "not a supported key type '#{$1}'"
        else
          raise OpenSSL::PKey::PKeyError, "not a private key (#{filename})"
        end

        encrypted_key = file.match(/ENCRYPTED/)
        tries = 0

        begin
          return key_type.new(file, passphrase || 'invalid')
        rescue OpenSSL::PKey::RSAError, OpenSSL::PKey::DSAError => e
          if encrypted_key
            tries += 1
            if tries <= 3
              passphrase = prompt("Enter passphrase for #{filename}:", false)
              retry
            else
              raise
            end
          else
            raise
          end
        end
      end

      # Loads a public key from a file. It will correctly determine whether
      # the file describes an RSA or DSA key, and will load it
      # appropriately. The new public key is returned.
      def load_public_key(filename)
        data = File.read(File.expand_path(filename))
        type, blob = data.split(/ /)

        raise Net::SSH::Exception, "public key at #{filename} is not valid" if blob.nil?

        blob = blob.unpack("m*").first
        reader = Net::SSH::Buffer.new(blob)
        reader.read_key or raise OpenSSL::PKey::PKeyError, "not a public key #{filename.inspect}"
      end
    end

  end

end; end
