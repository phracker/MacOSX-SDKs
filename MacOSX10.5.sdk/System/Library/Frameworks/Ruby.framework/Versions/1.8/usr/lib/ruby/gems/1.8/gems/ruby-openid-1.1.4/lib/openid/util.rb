require "base64"
require "cgi"
require "digest/sha1"
require "hmac-sha1"
require "uri"

require "openid/urinorm"

srand(Time.now.to_f)

class Object

  def instance_variable_hash
    h = {}
    self.instance_variables.each { |k| h[k] = self.instance_variable_get(k) }
    return h
  end

end

class String

  def starts_with?(other)
    other = other.to_str
    head = self[0, other.length]
    head == other
  end

end


module OpenID

  # Code returned when either the of the
  # OpenID::OpenIDConsumer.begin_auth or OpenID::OpenIDConsumer.complete_auth
  # methods return successfully.
  SUCCESS = 'success'

  # Code OpenID::OpenIDConsumer.complete_auth
  # returns when the value it received indicated an invalid login.
  FAILURE = 'failure'

  # Code returned by OpenIDConsumer.complete_auth when the user
  # cancels the operation from the server.
  CANCEL = 'cancel'

  # Code returned by OpenID::OpenIDConsumer.complete_auth when the
  # OpenIDConsumer instance is in immediate mode and ther server sends back a
  # URL for the user to login with.
  SETUP_NEEDED = 'setup needed'  

  # Code returned by OpenID::OpenIDConsumer.begin_auth when it is unable
  # to fetch the URL given by the user.
  HTTP_FAILURE = 'http failure'

  # Code returned by OpenID::OpenIDConsumer.begin_auth when the page fetched
  # from the OpenID URL doesn't contain the necessary link tags to function
  # as an identity page.
  PARSE_ERROR = 'parse error'

  module Util

    HAS_URANDOM = File.chardev? '/dev/urandom'

    def Util.get_openid_params(query)
      params = {}
      query.each do |k,v|
        params[k] = v if k.index("openid.") == 0
      end
      params
    end

    def Util.hmac_sha1(key, text)
      HMAC::SHA1.digest(key, text)
    end

    def Util.sha1(s)
      Digest::SHA1.digest(s)
    end
   
    def Util.to_base64(s)
      Base64.encode64(s).gsub("\n", "")
    end

    def Util.from_base64(s)
      Base64.decode64(s)
    end
 
    def Util.kvform(hash)
      form = ""
      hash.each do |k,v|
        form << "#{k}:#{v}\n"
      end
      form
    end

    def Util.parsekv(s)
      s.strip!
      form = {}
      s.split("\n").each do |line|
        pair = line.split(":", 2)
        if pair.length == 2
          k, v = pair
          form[k.strip] = v.strip
        end
      end
      form
    end

    def Util.num_to_str(n)
      bits = n.to_s(2)
      prepend = (8 - bits.length % 8)
      bits = ('0' * prepend) + bits
      [bits].pack('B*')
    end

    def Util.str_to_num(s)
      # taken from openid-ruby 0.0.1
      s = "\000" * (4 - (s.length % 4)) + s
      num = 0
      s.unpack('N*').each do |x|
        num <<= 32
        num |= x
      end
      num    
    end

    def Util.num_to_base64(l)
      return to_base64(num_to_str(l))
    end

    def Util.base64_to_num(s)
      return str_to_num(from_base64(s))
    end

    def Util.random_string(length, chars=nil)
      s = ""

      unless chars.nil?
        length.times { s << chars[Util.rand(chars.length)] }
      else
        length.times { s << Util.rand(256).chr }
      end
      s
    end

    def Util.urlencode(args)
      a = []
      args.each do |key, val|
        val = '' unless val
        a << (CGI::escape(key) + "=" + CGI::escape(val))
      end
      a.join("&")
    end
    
    def Util.parse_query(qs)
      query = {}
      CGI::parse(qs).each {|k,v| query[k] = v[0]}
      return query
    end
    
    def Util.append_args(url, args)
      url = url.dup
      url if args.length == 0
      url << (url.include?("?") ? "&" : "?")
      url << Util.urlencode(args)
    end
    
    def Util.strxor(s1, s2)
      raise ArgumentError if s1.length != s2.length
      length = [s1.length, s2.length].min - 1
      a = (0..length).collect {|i| (s1[i]^s2[i]).chr}
      a.join("")
    end
    
    # Sign the given fields from the reply with the specified key.
    # Return [signed, sig]
    def Util.sign_reply(reply, key, signed_fields, prefix="openid.")
      token = []
      signed_fields.each do |sf|
        token << [sf+":"+reply[prefix+sf].to_s+"\n"]
      end
      text = token.join("")
      signed = Util.to_base64(Util.hmac_sha1(key, text))
      return [signed_fields.join(","), signed]
    end

    # This code is taken from this post[http://blade.nagaokaut.ac.jp/cgi-bin/scat.\rb/ruby/ruby-talk/19098]
    # by Eric Lee Green.
    # This implementation is much faster than x ** n % q
    def Util.powermod(x, n, q)
      counter=0
      n_p=n
      y_p=1
      z_p=x
      while n_p != 0
        if n_p[0]==1
          y_p=(y_p*z_p) % q
        end
        n_p = n_p >> 1
        z_p = (z_p * z_p) % q
        counter += 1
      end
      return y_p
    end

    # Generate a random number less than max.  Uses urandom if available.
    def Util.rand(max)
      unless Util::HAS_URANDOM
        return Kernel::rand(max)
      end

      start = 0
      stop = max
      step = 1
      r = ((stop-start)/step).to_i

      # figure out how many bytes we need
      rbytes = Util::num_to_str(r)
      nbytes = rbytes.length
      nbytes -= 1 if rbytes[0].chr == "\000"
            
      bytes = "\000" + Util::get_random_bytes(nbytes)
      n = Util::str_to_num(bytes)
      
      return start + (n % r) * step
    end

    # change the message below to do whatever you like for logging
    def Util.log(message)
      STDERR.puts('OpenID Log: ' + message)
    end


    def Util.get_random_bytes(n)
      bytes = ""

      if Util::HAS_URANDOM
        f = File.open("/dev/urandom")
        while n != 0
          _bytes = f.read(n)
          n -= _bytes.length
          bytes << _bytes
        end
      else
        bytes = Util.random_string(n)
      end

      return bytes
    end

    def Util.normalize_url(url)
      url = url.strip

      unless url.starts_with?('http://') or url.starts_with?('https://')
        url = 'http://' + url
      end

      begin
        return Util.urinorm(url)
      rescue URI::InvalidURIError
        return nil
      end
    end

    def Util.urls_equal?(url1, url2)
      url1 = Util.normalize_url(url1)
      return false if url1.nil?
      return url1 == Util.normalize_url(url2)
    end

  end

end
