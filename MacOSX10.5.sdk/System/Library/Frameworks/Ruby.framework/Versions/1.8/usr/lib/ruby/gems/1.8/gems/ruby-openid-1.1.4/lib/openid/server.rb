require 'openid/util'
require 'openid/association'
require 'openid/dh'
require 'openid/trustroot'

module OpenID

  # This module contains classes specific to implemeting an OpenID
  # server.
  #
  # ==Overview
  #
  # An OpenID server must perform three tasks:
  #
  #   1. Examine the incoming request to determine its nature and validity.
  #
  #   2. Make a decision about how to respond to this request.
  #
  #   3. Format the response according to the protocol.
  #
  # The first and last of these tasks may performed by
  # the Server.decode_request and Server.encode_response methods of the
  # OpenID::Server::Server object.  Who gets to do the intermediate task --
  # deciding how to respond to the request -- will depend on what type of
  # request it is.
  #
  # If it's a request to authenticate a user (a checkid_setup or
  # checkid_immediate request), you need to decide if you will assert
  # that this user may claim the identity in question.  Exactly how you do
  # that is a matter of application policy, but it generally involves making
  # sure the user has an account with your system and is logged in, checking
  # to see if that identity is hers to claim, and verifying with the user that
  # she does consent to releasing that information to the party making the
  # request.  Do this by examining the properties of the CheckIDRequest
  # object, and when you've come to a decision, form a response by calling
  # CheckIDRequest.answer.
  #
  # Other types of requests relate to establishing associations between client
  # and server and verifing the authenticity of previous communications.
  # Server contains all the logic and data necessary to respond to
  # such requests; just pass it to Server.handle_request.
  #
  #
  # ==OpenID Extensions
  # 
  # Do you want to provide other information for your users
  # in addition to authentication?  Version 1.2 of the OpenID
  # protocol allows consumers to add extensions to their requests.
  # For example, with sites using the Simple Registration Extension
  # http://www.openidenabled.com/openid/simple-registration-extension/,
  # a user can agree to have their nickname and e-mail address sent to a
  # site when they sign up.
  #
  # Since extensions do not change the way OpenID authentication works,
  # code to handle extension requests may be completely separate from the
  # OpenIDRequest class here.  But you'll likely want data sent back by
  # your extension to be signed.  OpenIDResponse provides methods with
  # which you can add data to it which can be signed with the other data in
  # the OpenID signature.
  #
  # For example when request is a checkid_* request:
  #   
  #   response = request.answer(true)
  #   # this will add a signed 'openid.sreg.timezone' parameter to the response
  #   response.add_field('sreg', 'timezone', 'America/Los_Angeles')
  #
  #
  # ==Stores
  #
  # The OpenID server needs to maintain state between requests in order
  # to function.  Its mechanism for doing this is called a store.  The
  # store interface is defined in OpenID::Store.
  # Additionally, several concrete store implementations are provided, so that
  # most sites won't need to implement a custom store.  For a store backed
  # by flat files on disk, see OpenID::FilesystemStore.
  # 
  # ==Upgrading
  #
  # The keys by which a server looks up associations in its store have changed
  # in version 1.2 of this library.  If your store has entries created from
  # version 1.0 code, you should empty it.
  module Server
       
    HTTP_REDIRECT = 302
    HTTP_OK = 200
    HTTP_ERROR = 400
    
    BROWSER_REQUEST_MODES = ['checkid_setup', 'checkid_immediate']
    OPENID_PREFIX = 'openid.'

    ENCODE_KVFORM = ['kvform'].freeze
    ENCODE_URL = ['URL/redirect'].freeze

    # Represents an incoming OpenID request.
    class OpenIDRequest
      
      attr_reader :mode

      # +mode+ is the corresponsing "openid.mode" value of the request,
      # and is available through the +mode+ method.
      def initialize(mode)
        @mode = mode
      end

    end

    # A request to verify the validity of a previous response.
    class CheckAuthRequest < OpenIDRequest
      
      attr_accessor :assoc_handle, :sig, :signed, :invalidate_handle

      # Create a new CheckAuthRequest. Please see the
      # CheckAuthRequest.from_query class method, as it is the preferred
      # way to produce this object.
      #
      # ==Parameters
      #
      # [+assoc_handle+]
      #   String value of the "openid.assoc_handle" from the incoming request
      #
      # [+sig+]
      #   String signature for the request. This is "openid.sig"
      #
      # [+signed+]
      #   An array of pairs of [key, value], where key is the signed paramter
      #   name without the "openid." prefix.  Value is the String value of 
      #   of the paramter.
      #
      # [+invalidate_handle+]
      #   Optional. The association handle that the consumer is asking about
      #   the validity of.  May be nil.
      def initialize(assoc_handle, sig, signed, invalidate_handle=nil)
        super('check_authentication')
        @assoc_handle = assoc_handle
        @sig = sig
        @signed = signed
        @invalidate_handle = invalidate_handle
      end

      # Produce a CheckAuthRequest instance from the request query.  Raises
      # a ProtocolError if the request is malformed, and returns an instance
      # CheckAuthRequest on success.
      def CheckAuthRequest.from_query(query)       
        assoc_handle = query['openid.assoc_handle']
        sig = query['openid.sig']
        signed = query['openid.signed']
        invalidate_handle = query['openid.invalidate_handle']

        unless assoc_handle and sig and signed
          raise ProtocolError.new(query,
                                  "#{@mode} request missing required paramter")
        end

        signed = signed.split(',')
        signed_pairs = []

        signed.each do |field|
          if field == 'mode'
            value = 'id_res'
          else
            value = query['openid.'+field]
            if value.nil?
              raise ProtocolError.new(query, "Couldn't find signed field #{field}")
            end
          end
          signed_pairs << [field, value]
        end
        
        return new(assoc_handle, sig, signed_pairs, invalidate_handle)
      end

      # Respond to this request.  Given an OpenID::Server::Signatory instance
      # the validity of the signature and invalidate_handle can be checked.
      # 
      # Returns an OpenIDResponse object with an appropriate "is_valid" field
      # and an "invalidate_handle" field if appropriate.
      def answer(signatory)
        is_valid = signatory.verify(@assoc_handle, @sig, @signed)
        signatory.invalidate(assoc_handle, true)

        response = OpenIDResponse.new(self)
        response.fields['is_valid'] = is_valid ? 'true' : 'false'
        
        if @invalidate_handle
          assoc = signatory.get_association(@invalidate_handle, false)
          unless assoc
            response.fields['invalidate_handle'] = @invalidate_handle
          end          
        end

        return response
      end

    end
    
    # An object that knows how to handle association requests with no
    # session type.
    class PlainTextServerSession

      attr_reader :session_type

      def initialize
        @session_type = 'plaintext'
      end

      def PlainTextServerSession.from_query(query)
        new
      end
      
      def answer(secret)
        return {'mac_key' => OpenID::Util.to_base64(secret)}
      end

    end

    # An object that knows how to handle Diffie Hellman (DH-SHA1) association
    # requests.
    class DiffieHellmanServerSession

      attr_reader :session_type, :dh, :consumer_pubkey
      
      # In general you should create instances of DiffieHellmanServerSession
      # with the from_query class method.
      # 
      # ==Parameters
      #
      # [+dh+]
      #   OpenID::DiffieHellman instance
      #
      # [+consumer_pubkey+]
      #   Decoded "openid.dh_consumer_public".
      def initialize(dh, consumer_pubkey)
        @dh = dh
        @consumer_pubkey = consumer_pubkey
        @session_type = 'DH-SHA1'
      end      

      # Creates a new DiffieHellmanServerSession from the incoming request.
      # Raises a ProtocolError for malformed requests, and returns a 
      # DiffieHellmanServerSession instnace on success.
      def DiffieHellmanServerSession.from_query(query)
        dh_modulus = query['openid.dh_modulus']
        dh_gen = query['openid.dh_gen']
        dh = OpenID::DiffieHellman.from_base64(dh_modulus, dh_gen)

        consumer_pubkey = query['openid.dh_consumer_public']
        unless consumer_pubkey
          msg = 'No openid.dh_consumer_public found for DH-SHA1 session'
          raise ProtocolError.new(query, msg)
        end

        consumer_pubkey = OpenID::Util.base64_to_num(consumer_pubkey)
        return new(dh, consumer_pubkey)
      end

      # Generate the arguments to be added to the response using +secret+.
      def answer(secret)
        mac_key = @dh.xor_secrect(@consumer_pubkey, secret)
        return {
          'dh_server_public' => OpenID::Util.num_to_base64(@dh.public),
          'enc_mac_key' => OpenID::Util.to_base64(mac_key)
        }
      end

    end

    # A request to establish an OpenID association.  This object contains the
    # logic for handling "openid.mode=associate" requests.
    class AssociateRequest < OpenIDRequest

      attr_accessor :assoc_type, :session

      # +session+ is an instance of PlainTextServerSession or 
      # DiffieHellmanServerSession
      def initialize(session)
        super('associate')
        @assoc_type = 'HMAC-SHA1'
        @session = session
      end

      # Generate an AssociateRequest instance from the incoming query.
      # Raises a ProtocolError on malformed requests.
      def AssociateRequest.from_query(query)
        session_type = query['openid.session_type']
        if session_type == 'DH-SHA1'
          session = DiffieHellmanServerSession.from_query(query)
        elsif session_type.nil?
          session = PlainTextServerSession.from_query(query)
        else
          raise ProtocolError.new(query,
                                  "Unknown session_type #{session_type}")
        end
        
        return new(session)
      end

      # Respond to this request with an association.  +assoc+ is an
      # OpenID::Association instance that represents the association to
      # respond with.
      def answer(assoc)
        response = OpenIDResponse.new(self)

        fields = {
          'expires_in' => assoc.expires_in.to_s,
          'assoc_type' => 'HMAC-SHA1',
          'assoc_handle' => assoc.handle
        }

        # add the session specific arguments to the response fields
        response.fields.update(fields)        
        response.fields.update(@session.answer(assoc.secret))
        
        if @session.session_type != 'plaintext'
          response.fields['session_type'] = @session.session_type
        end

        return response
      end

    end

    # Object representing a request to confirm the identity of a
    # user. This object handles requests for openid.mode checkid_immediate, and
    # checkid_setup.
    class CheckIDRequest < OpenIDRequest
      
      attr_accessor :identity, :return_to, :trust_root, :immediate, \
                    :assoc_handle, :mode, :query
      
      # Create a new CheckIDRequest instance.  Most likely you'll want to
      # use CheckIDRequest.from_query to create this object.
      def initialize(mode, identity, return_to,
                     trust_root=nil, assoc_handle=nil)
        
        unless ['checkid_immediate', 'checkid_setup'].include?(mode)
          raise ProtocolError, "Can't create CheckIDRequest for mode #{mode}"
        end

        super(mode)
        @identity = identity
        @return_to = return_to
        @trust_root = trust_root
        @immediate = mode == 'checkid_immediate' ? true : false
        @assoc_handle = assoc_handle
        @query = {}
      end
       
      
      # Create a CheckIDRequest object from a web query.  May raise a
      # ProtocolError if request is a malformed checkid_* reuquest.
      def CheckIDRequest.from_query(query)
        mode = query['openid.mode']

        identity = query['openid.identity']
        raise ProtocolError.new(query, 'openid.identity missing') unless identity
        return_to = query['openid.return_to']
        raise ProtocolError.new(query, 'openid.return_to missing') unless return_to

        trust_root = query['openid.trust_root']
        trust_root = nil if trust_root and trust_root.empty?

        unless OpenID::TrustRoot.parse(return_to)
          raise MalformedReturnURL.new(query, return_to)
        end

        if trust_root and not OpenID::TrustRoot.parse(trust_root)
          raise MalformedTrustRoot.new(query, trust_root)
        end
       
        assoc_handle = query['openid.assoc_handle']
        
        req = new(mode, identity, return_to, trust_root, assoc_handle)        
        req.query = query
        
        unless req.trust_root_valid
          raise UntrustedReturnURL.new(query, return_to, trust_root)
        end

        return req
      end

      # Returns +true+ or +false+ according to whether the return_to
      # is under the supplied trust_root.
      def trust_root_valid
        return true unless @trust_root
        tr = OpenID::TrustRoot.parse(@trust_root)
        raise MalformedTrustRoot.new(nil, @trust_root) if tr.nil?
        return tr.validate_url(@return_to)
      end

      # Generate a response to this checkid_* request.
      #
      # ==Paramters
      #
      # [+allow+]
      #   Boolean value stating whether or not to allow this user to "claim"
      #   supplied identity and let the consumer have the information. The
      #   value of allow should be follow the following algorithm:
      #
      #   The identity URL provided (openid.identity) and available
      #   through the +identity_url+ method of this object is owned by
      #   the logged in user, and they have approved the consumer receive
      #   the identity assertion.
      #
      # [+server_url+]
      #   When an immeditate mode request does not succeed, it gets back a URL
      #   where the request may be continued in a not-so-immediate fashion.
      #   The URL returned is generated using the supplied +server_url+ here.
      #   +server_url+ should be the full URL of you openid server endpoint.
      def answer(allow, server_url=nil)
        if allow or @immediate
          mode = 'id_res'
        else
          mode = 'cancel'
        end

        response = OpenIDResponse.new(self)

        if allow
          response.add_fields(nil, {
                                'mode' => mode,
                                'identity' => @identity,
                                'return_to' => @return_to
                              })
        else
          response.add_field(nil, 'mode', mode, false)
          response.signed.clear
          if @immediate
            unless server_url
              raise ArgumentError, "setup_url is required for allow=false in immediate mode"
            end
            # make a request just like this one, but immediate mode
            setup_request = self.class.new('checkid_immediate',
                                           @identity,
                                           @return_to,
                                           @trust_root)
            setup_url = setup_request.encode_to_url(server_url)
            response.add_field(nil, 'user_setup_url', setup_url, false)
          end

        end
        
        return response
      end

      # Encode this request as a GET URL, returning the URL.
      def encode_to_url(server_url)
        q = {
          'openid.mode' => @mode,
          'openid.identity' => @identity,
          'openid.return_to' => @return_to
        }

        q['openid.trust_root'] = @trust_root if @trust_root
        q['openid.assoc_handle'] = @assoc_handle if @assoc_handle

        # add other openid stuff into the query (extensions)
        @query.each do |k,v|
          if k.starts_with?('openid.') and not q.has_key?(k)
            q[k] = v
          end
        end

        return OpenID::Util.append_args(server_url, q)
      end

      # Create the URL to cancel this request.  Useful for creating a "Cancel"
      # button on your "approve this openid transaction" form.
      def cancel_url
        if @immediate
          raise ProtocolError.new(nil, 'cancel is not an appropriate reponse to immediate mode requests')
        end
        return OpenID::Util.append_args(@return_to,{'openid.mode' => 'cancel'})
      end

      # The identity_url which was requested to be verified.  Your server
      # should provide a page at identity_url, and be able to assert
      # that the logged in user does or does not "own" that URL.
      # "Owning" an identity_url is in the details of the
      # server account name to URL mapping.
      def identity_url
        @identity
      end

    end
    
    # Object representing a response to an OpenIDRequest
    class OpenIDResponse

      attr_accessor :request, :fields, :signed

      # +request+ is a subclass of OpenIDRequest that this object
      # should respond to.
      def initialize(request)
        @request = request
        @fields = {}
        @signed = []
      end

      # Add an extra field to this response.
      #
      # [+namespace+]
      #   Extension namespace the field is in with no leading "openid.". For
      #   example, if you are adding a simple registration argument, you would
      #   pass 'sreg' as the namespace.
      def add_field(namespace, key, value, signed=true)
        if namespace and namespace != ''
          key = namespace + '.' + key
        end
        @fields[key] = value
        if signed and not @signed.member?(key)
          @signed << key
        end
      end

      # Same as OpenIDResponse.add_field, except that it accepts a Hash
      # fields to be added as the +fields+ argument.
      def add_fields(namespace, fields, signed=true)
        fields.each {|k,v| self.add_field(namespace, k, v, signed)}
      end

      # Update the fields of this request with another OpenIDResponse, +other+.
      def update(namespace, other)
        if namespace and namespace != ''
          namespaced_fields = {}
          other.fields.each {|k,v| namespaced_fields[namespace+'.'+k] = v}
          namespaced_signed = other.signed.collect {|k| namespace+'.'+k}
        else
          namespaced_fields = other.fields.dup
          namespaced_signed = other.signed.dup
        end
        
        @fields.update(namespaced_fields)
        @signed |= namespaced_signed
      end

      # Returns a boolean saying whether or not this response requires
      # signing.
      def needs_signing?
        ['checkid_immediate','checkid_setup'].member?(@request.mode) and \
           @signed.length > 0
      end

      # OpenID responses can be sent back as a URL redirect or as a kvform
      # reponse to a POST. This method returns a code describing how the
      # response should be encoded, and return either
      # OpenID::Server::ENCODE_URL or OpenID::Server::ENCODE_KVFORM.
      def which_encoding?
        if BROWSER_REQUEST_MODES.member?(@request.mode)
          return ENCODE_URL
        else
          return ENCODE_KVFORM
        end
      end

      # Encode the response to a URL, suitable to be send via 302 redirect.
      def encode_to_url
        fields = {}
        @fields.each {|k,v| fields['openid.'+k] = v}
        return OpenID::Util.append_args(@request.return_to, fields)
      end

      # Encode the response to kvform format.
      def encode_to_kvform
        return OpenID::Util.kvform(@fields)
      end
      
    end

    # Object responsible for signing responses, and checking signatures.
    class Signatory
      @@secret_lifetime = 14 * 24 * 60 * 6
      @@normal_key = 'http://localhost/|normal'
      @@dumb_key = 'http://localhost/|dumb'
      
      attr_reader :dumb_key

      # Accepts an object that implements the OpenID::Store interface.  See
      # OpenID::FilesystemStore for a simple file based store.
      def initialize(store)
        @store = store
      end

      # Verify that the signature for some data is valid.
      #
      # ==Paramters
      #
      # [+assoc_handle+]
      #   The association handle used to get the secret out of the store, and
      #   passed in via openid.assoc_handle.
      #
      # [+sig+]
      #   Value of openid.sig
      #
      # [+signed_pairs+]
      #   Array of Array pairs of key, value signed data.
      #
      # [+dumb+]
      #   boolean representing whether this is a dumb mode request      
      def verify(assoc_handle, sig, signed_pairs, dumb=true)
        assoc = self.get_association(assoc_handle, dumb)
        unless assoc
          OpenID::Util.log("failed to get assoc with handle #{assoc_handle} to verify sig #{sig}")
          return false
        end
        
        expected_sig = OpenID::Util.to_base64(assoc.sign(signed_pairs))

        if sig == expected_sig
          return true
        else
          OpenID::Util.log("signture mismatch: expected #{expected_sig}, got #{sig}")
          return false
        end
      end

      # Sign a response, creating a signature based on everything in it's
      # +signed+ array.  Returns a new response object with sig and signed
      # values in its field set.
      def sign(response)
        # get a deep copy of the response
        signed_response = Marshal.load(Marshal.dump(response))
        assoc_handle = response.request.assoc_handle

        if assoc_handle
          assoc = self.get_association(assoc_handle, false)
          unless assoc
            # no assoc for handle, fall back to dumb mode
            signed_response.fields['invalidate_handle'] = assoc_handle
            assoc = self.create_association(true)
          end
        else
          # dumb mode
          assoc = self.create_association(true)
        end
        
        signed_response.fields['assoc_handle'] = assoc.handle
        assoc.add_signature(signed_response.signed,
                            signed_response.fields, '')
        return signed_response
      end

      # Make a new assocation.
      def create_association(dumb=true, assoc_type='HMAC-SHA1')
        secret = OpenID::Util.get_random_bytes(20)
        uniq = OpenID::Util.to_base64(OpenID::Util.get_random_bytes(4))
        handle = "{%s}{%x}{%s}" % [assoc_type, Time.now.to_i, uniq]
        assoc = Association.from_expires_in(@@secret_lifetime,
                                            handle,
                                            secret,
                                            assoc_type)

        key = dumb ? @@dumb_key : @@normal_key
        @store.store_association(key, assoc)
        return assoc
      end

      # Get an association by assoc_handle and mode
      def get_association(assoc_handle, dumb)
        if assoc_handle.nil?
          raise ArgumentError, 'assoc_handle must not be nil'
        end
        
        key = dumb ? @@dumb_key : @@normal_key
        
        assoc = @store.get_association(key, assoc_handle)
        if assoc and assoc.expired?
          @store.remove_association(key, assoc_handle)
          assoc = nil
        end
        
        return assoc
      end

      # Invalidate an association by assoc_handle and mode
      def invalidate(assoc_handle, dumb)
        key = dumb ? @@dumb_key : @@normal_key
        @store.remove_association(key, assoc_handle)
      end

    end

    # Response to an OpenID request that a web server can understand. Proper
    # responses can be issued to your framework by examining the +code+
    # method and associated methods.
    class WebResponse
      
      attr_accessor :code, :headers, :body

      def initialize
        @code = HTTP_OK
        @headers = {}
        @body = ''
      end

      def set_redirect(url)
        @code = HTTP_REDIRECT
        @headers['location'] = url
      end

      # If this method returns true, a redirect should be issued by the
      # webserver to the value returned by the redirect_url method.
      #
      # If this method returns false, the value returned by the +body+
      # method should be returned to ther server as-is without modification.
      def is_redirect?
        @code == HTTP_REDIRECT
      end

      def redirect_url
        @headers['location']
      end

    end

    # Object that encodes OpenIDResponse objects into WebResponse objects.
    class Encoder
      
      def encode(response)
        webresponse = WebResponse.new

        case response.which_encoding?
        when ENCODE_KVFORM
          webresponse.code = HTTP_ERROR if response.kind_of?(Exception)
          webresponse.body = response.encode_to_kvform

        when ENCODE_URL
          webresponse.set_redirect(response.encode_to_url)

        else
          # don't know how to encode response
          raise EncodingError.new(response)
        end
        
        return webresponse
      end

    end

    # Object that encodes OpenIDResponse objects into WebResponse objects,
    # potentially adding a signature along the way.
    class SigningEncoder < Encoder
      
      def initialize(signatory)
        if signatory.nil?
          raise ArgumentError, "signatory must not be nil"
        end
        @signatory = signatory
      end

      def encode(response)
        if (not response.kind_of?(Exception)) and response.needs_signing?
          if response.fields.has_key?('sig')
            raise AlreadySigned
          end
          response = @signatory.sign(response)
        end
        return super(response)
      end

    end

    # Decode incoming web requests into an OpenIDRequest object.
    class Decoder

      def decode(query)
        return nil if query.length == 0
        
        mode = query['openid.mode']
        return nil if mode.nil?

        if mode.class == Array
          raise ArgumentError, 'query hash must have one value for each key'
        end

        case mode
        when 'checkid_setup', 'checkid_immediate'
          return CheckIDRequest.from_query(query)

        when 'check_authentication'
          return CheckAuthRequest.from_query(query)

        when 'associate'
          return AssociateRequest.from_query(query)
          
        else
          raise ProtocolError.new(query, "Unknown mode #{mode}")
        end
        
      end

    end

    # Top level object that handles incoming requests for an OpenID server.
    # 
    # Some types of requests (those which are not CheckIDRequest objects) may
    # be handed to the handle_request method, and an appropriate response
    # will be returned.
    #
    # For convenienve, decode and encode methods are exposed which should be
    # used as the entry and exit points of the OpenID server logic.  The first
    # step when handling an OpenID server action should be to call
    # Server.decode_request with the query arguments.
    #
    # This object needs an instance of OpenID::Store to store state between
    # sessions and associations.  See OpenID::FilesystemStore for a simple
    # file based solution.
    #
    # ==Pseudo Code
    # 
    # Below is some pseudo code for using this object to handle OpenID server
    # requests. The +params+ variable represents a Hash of the incoming
    # arguments.  is_authorized and show_decide_page are methods you provide.
    # At the end you have a WebResponse object suitable for examining and
    # issuing a response to your web server.
    #   
    #   include OpenID
    #   store = FilesystemStore.new('/var/openid/store')
    #   server = Server::Server.new(store)
    #   request = server.decode_request(params)
    #   if request.kind_of?(CheckIDRequest)
    #     if is_authorized(request.identity, request.trust_root)
    #       response = request.answer(true)
    #     elsif request.immediate
    #       response = request.answer(false,'http://example.com/openid-server')
    #     else
    #       show_decide_page(request)
    #       return
    #     end
    #   else
    #     response = server.handle_request(request)
    #   end
    #
    #   web_response = server.encode_response(response)
    #
    # For an actual working example, please see the rails_server
    # directory inside of the examples directory.  Have a look at the
    # app/controllers/server_controller.rb and the +index+ method of the
    # ServerController object.
    class Server
      
      # +store+ is a kind of OpenID::Store
      def initialize(store)
        @store = store
        @signatory = Signatory.new(store)
        @encoder = SigningEncoder.new(@signatory)
        @decoder = Decoder.new
      end

      # Decode an incoming web request into a kind of OpenIDRequest object.
      # +query+ should be a hash of request arguments. Rails users will want to
      # pass in the @params instance variable of the ActionController.
      def decode_request(query)
        return @decoder.decode(query)
      end

      # Handle all non checkid_* OpenID requests.
      def handle_request(request)
        return self.send('openid_'+request.mode, request)
      end
      
      # Return a WebResponse object given an OpenIDResponse object
      def encode_response(response)
        return @encoder.encode(response)
      end
      
      # called by handle_request to perform check auth calls
      def openid_check_authentication(request)
        return request.answer(@signatory)
      end

      # called by handle_request to perform openid.mode=associate calls.
      def openid_associate(request)
        assoc = @signatory.create_association(false)
        return request.answer(assoc)
      end

    end

    # Raised when an OpenID request encounters some kind of protocol error.
    class ProtocolError < Exception
      
      attr_reader :query

      def initialize(query, text=nil)
        super(text)
        @query = query
      end

      def has_return_to?
        @query.has_key?('openid.return_to')
      end

      def encode_to_url
        return_to = @query['openid.return_to']
        unless return_to
          raise ArgumentError, 'No return_to in query'
        end
        
        args = {
          'openid.mode' => 'error',
          'openid.error' => self.to_s
        }
        
        return OpenID::Util.append_args(return_to, args)
      end

      def encode_to_kvform
        args = {
          'mode' => 'error',
          'error' => self.to_s
        }        
        return OpenID::Util.kvform(args)        
      end

      def which_encoding?
        if self.has_return_to?
          return ENCODE_URL
        end

        mode = @query['openid.mode']
        if mode and not BROWSER_REQUEST_MODES.member?(mode)
          return ENCODE_KVFORM          
        end
        
        return nil
      end

    end

    class EncodingError < Exception; end    
    class AlreadySigned < EncodingError; end
    
    class MalformedReturnURL < ProtocolError
      
      attr_reader :return_to

      def initialize(query, return_to)
        super(query)
        @return_to = return_to
      end

    end

    class MalformedTrustRoot < ProtocolError; end

    class UntrustedReturnURL < ProtocolError

      attr_reader :return_to, :trust_root

      def initialize(query, return_to, trust_root)
        super(query)
        @return_to = return_to
        @trust_root = trust_root        
      end
    end

  end

end
