require "uri"

require "openid/util"
require "openid/dh"
require "openid/fetchers"
require "openid/association"
require "openid/discovery"


# Everything in this library exists within the OpenID Module.  Users of
# the library should look at OpenID::Consumer and/or OpenID::Server
module OpenID

  # ==Overview
  #
  # Brief terminology:
  #
  # [+Consumer+]
  #   The website wanting to verify an OpenID identity URL.  Sometimes
  #   called a "relying party".  If you want people to log into your site
  #   using OpenID, then you are the consumer.
  # 
  # [+Server+]
  #   The website which makes assertions as to whether or not the user
  #   at the end of the browser owns the URL they say they do.
  #
  # [+Redirect+]
  #   An HTTP 302 (Temporarily Moved) redirect.  When issued as an HTTP
  #   response from the server, the browser changes it's location to the
  #   value specified.
  #
  # The OpenID authentication process requires the following steps,
  # as visible to the user of this library:
  #
  # 1. The user enters their OpenID into a field on the consumer's
  #    site, and hits a login button.
  #
  # 2. The consumer site discovers the user's OpenID server information using
  #    the Yadis protocol (Potentially falling back to OpenID 1.0 "linkrel"
  #    discovery).
  #
  # 3. The consumer site prepares a URL to be sent to the  server
  #    which contains the OpenID autentication information, and 
  #    issues a redirect user's browser.
  #
  # 4. The server then verifies that the user owns the URL
  #    provided, and sends the browser a redirect
  #    back to the consumer.  This redirect contains the
  #    server's response to the authentication request.
  #
  # The most important part of the flow to note is the consumer's site
  # must handle two separate HTTP requests in order to perform the
  # full identity check.  These two HTTP requests are described in
  # steps 1 and 4 above, and are handled by Consumer.begin and
  # Consumer.complete respectively.
  #
  #
  # ==Consumer Library Design
  #
  # The library is designed with the above flow in mind.  The
  # goal is to make it as easy as possible to perform the above steps
  # securely.
  #
  # At a high level, there are two important parts in the consumer
  # library.  The first important part is the OpenID::Consumer class,
  # which contains the public interface to the consumer logic.
  # The second is the OpenID::Store class, which defines the
  # interface needed to store the state the consumer needs to maintain
  # between requests.
  #
  # In general, the second part is less important for users of the
  # library to know about, as several concrete store implementations are
  # provided.  The user simply needs to choose the store which best fits
  # their environment and requirements.
  #
  #
  # ==Stores and Dumb Mode
  #
  # OpenID is a protocol that works best when the consumer site is
  # able to store some state.  This is the normal mode of operation
  # for the protocol, and is sometimes referred to as smart mode.
  # There is also a fallback mode, known as dumb mode, which is
  # available when the consumer site is not able to store state.  This
  # mode should be avoided when possible, as it leaves the
  # implementation more vulnerable to replay attacks.
  #
  # The mode the library works in for normal operation is determined
  # by the store that it is given.  The store is an abstraction that
  # handles the data that the consumer needs to manage between HTTP
  # requests in order to operate efficiently and securely.
  #
  # Several store implementation are provided, and the interface is
  # fully documented so that custom stores can be used as well. The
  # implementations that are provided allow the consumer site to store
  # data in a couple of different ways: in the filesystem,
  # or in an SQL database.
  #
  # There is an additional concrete store provided that puts the
  # consumer in dumb mode.  This is not recommended, as it removes the
  # library's ability to stop replay attacks reliably.  It still uses
  # time-based checking to make replay attacks only possible within a
  # small window, but they remain possible within that window.  This
  # store should only be used if the consumer site has no way to
  # retain data between requests at all. See DumbStore for more info.
  #
  # If your ennvironment permits, use of the FilesystemStore
  # is recommended.
  #
  #
  # ==Immediate Mode
  #
  # If you are new to OpenID, it is suggested that you skip this section
  # and refer to it later.  Immediate mode is an advanced consumer topic.
  #
  # In the flow described in the overview, the user may need to confirm to the
  # identity server that it's ok to authorize his or her identity.
  # The server may draw pages asking for information from the user
  # before it redirects the browser back to the consumer's site.  This
  # is generally transparent to the consumer site, so it is typically
  # ignored as an implementation detail.
  #
  # There can be times, however, where the consumer site wants to get
  # a response immediately.  When this is the case, the consumer can
  # put the library in immediate mode.  In immediate mode, there is an
  # extra response possible from the server, which is essentially the
  # server reporting that it doesn't have enough information to answer
  # the question yet.  In addition to saying that, the identity server
  # provides a URL to which the user can be sent to provide the needed
  # information and let the server finish handling the original
  # request.
  #
  # You may invoke immediate mode when building the redirect URL to the
  # OpenID server in the SuccessRequest.redirect_url method.  Pass true
  # for the +immediate+ paramter.  Read the interface for Consumer.complete
  # for information about handling the additional response.
  #
  # ==Using the Library
  #
  # Integrating this library into an application is a
  # relatively straightforward process.  The process usually follows this plan:
  #
  # Add an OpenID login field somewhere on your site.  When an OpenID
  # is entered in that field and the form is submitted, it should make
  # a request to the site which includes that OpenID URL.
  #
  # When your site receives that request, it should create an
  # OpenID::Consumer instance, and call
  # OpenID::Consumer.begin.  If begin completes successfully,
  # it will return a SuccessRequest object.  Otherwise it will subclass
  # of OpenIDStatus which contains additional information about the
  # the failure.
  #
  # If successful, build a redirect URL to the server by calling
  # SuccessRequest.redirect_url and send back an HTTP 302 redirect
  # of that URL to the user's browser. The redirect_url accepts a 
  # return_to parameter, which is the URL to which they will return
  # to fininsh the OpenID transaction.  This URL is supplied by you,
  # and should be able to handle step 4 of the flow described in the
  # overview.
  #
  # That's the first half of the authentication process.  The second
  # half of the process is done after the OpenID server sends the
  # user's browser a redirect back to your site with the
  # authentication response.
  #
  # When that happens, the browser will make a request to the return_to
  # URL you provided to the SuccessRequest.redirect_url
  # method.  The request will have several query parameters added
  # to the URL by the identity server as the information necessary to
  # finish the request.
  #
  # Your job here is to make sure that the action performed at the return_to
  # URL creates an instnce of OpenID::Consumer, and calls the Consumer.complete
  # method. This call will
  # return a SuccessResponse object, or a subclass of OpenIDStatus explaining,
  # the failure.  See the documentation for Consumer.complete
  # for a full explanation of the possible responses.
  #
  # If you received a SuccessResponse, you may access the identity URL
  # of the user though it's +identity_url+ method.
  class Consumer
    
    @@service_key = '_openid_consumer_service'
    @@disco_suffix = 'xopenid_services'
    attr_accessor :consumer, :session, :fetcher

    # Creates a new OpenID::Consumer instance.  You should create a new
    # instance of the Consumer object with every HTTP request that handles
    # OpenID transactions.  Do not store the instance of it in a
    # global variable somewhere.
    #
    # [+session+]
    #   A hash-like object representing the user's session data.  This is
    #   used for keeping state of the OpenID transaction when the user is
    #   redirected to the server.  In a rails application, the controller's
    #   @session instance variable should be used.
    #
    # [+store+] 
    #   This must be an object that implements the OpenID::Store interface.
    #   Several concrete implementations are provided, to cover
    #   most common use cases.  We recommend using the simple file based
    #   store bundled with the library: OpenID::FilesystemStore.
    # 
    # [+fetcher+]
    #   Optional.  If provided, this must be an instance that implements
    #   OpenID::Fetcher interface.  If no fetcher is provided,
    #   an OpenID::StandardFetcher instance will be created
    #   for you automatically.  If you need custom fetcher behavior, it
    #   is probably best to subclass StandardFetcher, and pass your instance
    #   in here.
    # 
    # This object keeps an internal instance of OpenID::GenericConsumer
    # for low level OpenID calls, called +consumer+. You may use a custom    
    # certificate authority PEM file for veryifying HTTPS server certs
    # by calling the GenericConsumer.ca_path= method of the +consumer+
    # instance variable.
    def initialize(session, store, fetcher=nil)
      @session = session
      @consumer = GenericConsumer.new(store, fetcher)
    end

    # +begin+ is called to start the OpenID verification process.  See steps
    # 1-2 in the overview at the top of this file.
    #
    # ==Parameters
    #
    # [+user_url+]
    #   Identity URL given by the user. +begin+ performs a textual
    #   transformation of the URL to try and make sure it is "normalized",
    #   for example, a user_url of example.com will be normalized to
    #   http://example.com/ normalizing and resolving any redirects
    #   the server might issue.
    #
    # ==Return Value
    #
    # +begin+ returns a subclass of OpenIDStatus, which is an object
    # that has a +status+ method.  The status methodfor this object will either
    # return OpenID::SUCCESS, or OpenID::FAILURE.  Generally +begin+ will fail
    # if the users' OpenID page cannot be retrieved or OpenID server
    # information cannot be determined.
    # 
    # ===Success
    #
    # In the case that request.status equals OpenID::SUCCESS, the response
    # will be of type OpenID::SuccessRequest.  The SuccessRequest object
    # may the be used to add simple registration extension arguments,
    # using SuccessRequest.add_extension_arg, and build the redirect
    # url to the server using SuccessRequest.redirect_url as described
    # in step 3 of the overview.
    #
    # The next step in the success case is to actually build the redirect
    # URL to the server.  Please see the documentation for
    # SuccessRequest.redirect_url for details.  Once the redirect url
    # is created, you should issue an HTTP 302 temporary redirect to the
    # user's browser, sending her to the OpenID server.  Once the user
    # finishes the operations on the server, she will be redirected back to
    # the return_to URL you passed to redirect_url, which should invoke
    # the Consumer.complete method.
    #
    # ===Failure
    # 
    # If the library is unable to fetch the +user_url+, or no server
    # information can be determined, or if the server information is malformed,
    # +begin+ will return a FailureRequest object.  The status method of this
    # object will return OpenID::FAILURE.  FailureRequest objects have a
    # +msg+ method which provides more detailed information as to why
    # the request failed.
    def begin(user_url)
      discovery = self.get_discovery(user_url)

      unless discovery
        return FailureRequest.new("Don't know how to find services for that identifier")
      end

      service = discovery.next_service

      unless service
        return FailureRequest.new('No service endpoints found.')
      end
      
      return self.begin_without_discovery(service)
    end

    # Start the OpenID transaction without doing OpenID server
    # discovery. This method is used internally by Consumer.begin after
    # discovery is performed, and exists to provide an interface for library
    # users needing to perform their own discovery.
    #
    # ==Parameters
    #
    # +service+ must be an OpenID::OpenIDServiceEnpoint object, or an object
    # that implements it's interface.  You may produce these objects
    # and perform discovery manually using OpenID::OpenIDDiscovery.
    #
    # ==Return Value
    # 
    # +begin_without_discovery+ always returns an OpenID::SuccessRequest
    # object.  Please see the success documentation for OpenID::Consumer.begin
    # for more information.
    def begin_without_discovery(service)
      request = @consumer.begin(service)
      @session[@@service_key] = service
      return request
    end
    
    # Called to interpret the server's response to an OpenID request. It
    # is called in step 4 of the flow described in the consumer overview.
    #
    # ==Parameters
    # [+query+]
    #   A hash of the query paramters for this HTTP request.
    #
    # ==Return Value
    # Return value is a subclass of OpenIDStatus, and may have a status
    # of OpenID::SUCCESS, OpenID::CANCEL, OpenID::FAILURE,
    # or OpenID::SETUP_NEEDED.  The status may be accessed through the
    # +status+ method of the response object.
    #
    # When OpenID::SUCCESS is returned, the response object will be of 
    # type SuccessResponse, which has several useful attributes including
    # +identity_url+, +service+, and a method +extension_response+ for
    # extracting potential signed extension reponses from the server.  See
    # the documentation for OpenID::SuccessResponse for more information
    # about it's interface and methods.
    #
    # In the case of response.status being OpenID::CANCEL, the user cancelled
    # the OpenID transaction on the server. The response will be an instance
    # of OpenID::CancelResponse, and you may access the originally submitted
    # identity URL and service information through that object.
    #
    # When status is OpenID::FAILURE, the object will be an instance of
    # OpenID::FailureResponse. If the identity which failed can be determined
    # it will be available by accessing the +identity_url+ attribute of the
    # response.  FailureResponse objects also have a +msg+ attribute
    # which may be useful in debugging.  If no msg is specified, msg will be
    # nil.
    #
    # When OpenID::SETUP_NEEDED is returned, the response object is an 
    # instance of OpenID::SetupNeededResponse. The useful piece of information
    # contained in this response is the +setup_url+ method, which
    # should be used to send the user to the server and log in.
    # This response is only generated by immediate
    # mode requests (openid.mode=immediate).  The user should be redirected
    # in to the +setup_url+, either in the current window or in a 
    # new browser window.
    def complete(query)
      service = @session[@@service_key]
      
      if service.nil?
        resp = FailureResponse.new(nil, 'No session state found.')
      else
        resp = @consumer.complete(query, service)
      end

      # If the response has an non-nil identity_url attribute,
      # then we can get te discovery object and finalize the request.
      # Otherwise it is a failure or replay, and we set the response
      # servce to nil.
      if resp.identity_url
        disco = self.get_discovery(resp.identity_url)
        if [SUCCESS, CANCEL].member?(resp.status)
          if resp.identity_url
            resp.service = disco.finish
          end
        else
          resp.service = disco.current
        end
      else
        resp.service = nil
      end


      # want to delete service unless status is SETUP_NEEDED,
      # because we still need the service info when the user returns from
      # the server
      unless resp.status == SETUP_NEEDED
        @session[@@service_key] = nil
      end

      return resp
    end

    protected
    
    # Used internally to create an instnace of the OpenIDDiscovery object.
    def get_discovery(url)
      if XRI::identifier_scheme(url) == :xri
        XRIDiscovery.new(@session, url, @@disco_suffix)
      else
        url = OpenID::Util.normalize_url(url)
        if url
          user_url = user_url.to_s
          OpenIDDiscovery.new(@session, url, @consumer.fetcher, @@disco_suffix)
        else
          nil
        end
      end
    end
  end

  # This class implements the common logic for OpenID consumers.  It
  # is used by the higher level OpenID::Consumer class.  Only advanced
  # users with special needs should ever have to look at this class.
  #
  # The only part of the library which has to be used and isn't
  # documented in full here is the store required to create an
  # OpenID::Consumer instance.  More on the abstract store type and
  # concrete implementations of it that are provided in the documentation
  # of OpenID::Consumer.new 
  class GenericConsumer

    # Number of characters to be used in generated nonces
    @@NONCE_LEN = 8
    
    # Nonce character set
    @@NONCE_CHRS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
    @@D_SUFFIX = 'openid_disco'

    attr_reader :fetcher

    public
        
    # Creates a new Consumer instance.  You should create a new
    # instance of the Consumer object with every HTTP request.  Do not
    # store the instance of it in a global variable somewhere.
    #
    # [+store+] 
    #   This must be an object that implements the OpenID::Store interface.
    #   Several concrete implementations are provided, to cover
    #   most common use cases.  We recommend using the simple file based
    #   store bundled with the library: OpenID::FilesystemStore.
    # 
    # [+fetcher+]
    #   Optional.  If provided, this must be an instance that implements
    #   Fetcher interface.  If no fetcher is provided,
    #   an instance of OpenID::StandardFetcher will be created for
    #   you automatically.
    def initialize(store, fetcher=nil)
      if fetcher.nil?
        fetcher = StandardFetcher.new
      end
      @store = store
      @fetcher = fetcher
      @ca_path = nil
    end
    
    # Set the path to a pem certificate authority file for verifying
    # server certificates during HTTPS.  If you are interested in verifying
    # certs like the mozilla web browser, have a look at the files here:
    #
    # http://curl.haxx.se/docs/caextract.html
    def ca_path=(ca_path)
      ca_path = ca_path.to_s
      if File.exists?(ca_path)
        @ca_path = ca_path
        @fetcher.ca_path = ca_path
      else
        raise ArgumentError, "#{ca_path} is not a valid file path"
      end
    end

    # See the interface documentation for Consumer.begin_without_discovery
    # for arugumnets and return values of this method.
    # begin_without_discovery is a light wrapper around this method, and the
    # has the same interface.
    def begin(service)
      nonce = self.create_nonce
      assoc = self.get_association(service.server_url)
      return SuccessRequest.new(assoc, nonce, service)
    end

    # Please see the interface docs for Consumer.complete.  This method accpets
    # a +service+ paramter which is provided though the SuccessRequest object
    # generated in the +begin+ call.  The +service+ should be stored somewhere
    # in the user's session or environment and passed into this method
    # along with the full query string Hash.  Consumer.complete has the
    # full list of return values for this method.
    def complete(query, service_endpoint)
      return FailureResponse.new(nil, msg='no session state found') unless service_endpoint

      consumer_id = service_endpoint.consumer_id
      server_id = service_endpoint.server_id
      server_url = service_endpoint.server_url

      # get the nonce out of the query
      nonce = query['nonce']
      if nonce.nil?
        return FailureResponse.new(consumer_id, 'could not extract nonce')
      end

      mode = query["openid.mode"]

      case mode
      when "cancel"        
        return CancelResponse.new(consumer_id)

      when "error"
        error = query["openid.error"]
        unless error.nil?
          OpenID::Util.log('Error: '+error)
        end
        return FailureResponse.new(nil, msg=error)

      when "id_res"        
        return self.do_id_res(nonce, consumer_id, server_id, server_url, query)

      else
        return FailureResponse.new(nil, msg="unknown mode #{mode}")
      end

    end

    # Low level method for handling the OpenID server response.
    def do_id_res(nonce, consumer_id, server_id, server_url, query)
      user_setup_url = query["openid.user_setup_url"]
      if user_setup_url
        return SetupNeededResponse.new(user_setup_url)
      end
      
      return_to = query["openid.return_to"]
      server_id2 = query["openid.identity"]
      assoc_handle = query["openid.assoc_handle"]
      
      if return_to.nil?
        return FailureResponse.new(consumer_id, msg='openid.return_to was nil')
      elsif server_id2.nil?
        return FailureResponse.new(consumer_id, msg='openid.identity was nil')
      elsif assoc_handle.nil?
        return FailureResponse.new(consumer_id, msg='openid.assoc_handle was nil')
      end
      
      if server_id != server_id2
        return FailureResponse.new(consumer_id, msg='server ids do not match')
      end
      
      assoc = @store.get_association(server_url, assoc_handle)
    
      if assoc.nil?
        # It's not an association we know about. Dumb mode is our
        # only possible path for recovery.
        code, msg = self.check_auth(nonce, query, server_url)
        if code == SUCCESS
          return SuccessResponse.new(consumer_id, query)
        else
          return FailureResponse.new(consumer_id, "check_auth failed: #{msg}")
        end
      end

      if assoc.expires_in <= 0
        OpenID::Util.log("Association with #{server_url} expired")
        return FailureResponse.new(consumer_id, 'assoc expired')
      end

      # Check the signature
      sig = query["openid.sig"]
      return FailureResponse.new(consumer_id, 'no sig') if sig.nil?
      signed = query["openid.signed"]
      return FailureResponse.new(consumer_id, 'no signed') if signed.nil?
      
      args = OpenID::Util.get_openid_params(query)
      signed_list = signed.split(",")
      _signed, v_sig = OpenID::Util.sign_reply(args, assoc.secret, signed_list)

      if v_sig != sig
        return FailureResponse.new(consumer_id, 'sig mismatch')
      end

      unless @store.use_nonce(nonce)
        return FailureResponse.new(consumer_id, 'nonce already used')
      end

      return SuccessResponse.new(consumer_id, query)
    end

    # Low level method for performing OpenID check_authenticaion requests
    def check_auth(nonce, query, server_url)
      check_args = OpenID::Util.get_openid_params(query)
      check_args["openid.mode"] = "check_authentication"
      post_data = OpenID::Util.urlencode(check_args)

      ret = @fetcher.post(server_url, post_data)
      if ret.nil?
        return FAILURE, "unable to post to #{server_url}"
      else
        url, body = ret
      end
    
      results = OpenID::Util.parsekv(body)
      is_valid = results.fetch("is_valid", "false")
    
      if is_valid == "true"

        # we started this request with a bad association,
        # falling back to dumb mode, the invalidate_handle tells
        # us to handle of the assoc to remove from our store.
        invalidate_handle = results["invalidate_handle"]
        if invalidate_handle
          @store.remove_association(server_url, invalidate_handle)
        end

        # make sure response is not getting replayed by checking the nonce
        unless @store.use_nonce(nonce)
          return FAILURE, "#{server_url}, nonce #{nonce} already used"
        end

        # is_valid = true, and we successfully used the nonce.
        return SUCCESS, nil
      end
    
      error = results["error"]
      if error
        msg = "error from server: #{error}"
      else
        msg = "is_valid was false"
      end
      return FAILURE, msg
    end

    # Create a nonce and store it for preventing replace attacks.
    def create_nonce
      # build the nonce and store it
      nonce = OpenID::Util.random_string(@@NONCE_LEN, @@NONCE_CHRS)
      @store.store_nonce(nonce)
      return nonce
    end

    # Get existing or create a new association (shared secret) with the
    # server at +server_url+.
    def get_association(server_url)
      return nil if @store.dumb?
      assoc = @store.get_association(server_url)
      return assoc unless assoc.nil?
      return self.associate(server_url)    
    end
    
    # Make the openid.associate call to the server.
    def associate(server_url)
      dh = OpenID::DiffieHellman.new
      cpub = OpenID::Util.to_base64(OpenID::Util.num_to_str(dh.public))
      args = {
        'openid.mode' => 'associate',
        'openid.assoc_type' =>'HMAC-SHA1',
        'openid.session_type' =>'DH-SHA1',
        'openid.dh_modulus' => OpenID::Util.to_base64(OpenID::Util.num_to_str(dh.p)),
        'openid.dh_gen' => OpenID::Util.to_base64(OpenID::Util.num_to_str(dh.g)),
        'openid.dh_consumer_public' => cpub
      }
      body = OpenID::Util.urlencode(args)
      
      ret = @fetcher.post(server_url, body)
      return nil if ret.nil?
      url, data = ret
      results = OpenID::Util.parsekv(data)
      
      assoc_type = results["assoc_type"]
      return nil if assoc_type.nil? or assoc_type != "HMAC-SHA1"
      
      assoc_handle = results["assoc_handle"]
      return nil if assoc_handle.nil?    
      
      expires_in = results.fetch("expires_in", "0").to_i

      session_type = results["session_type"]
      if session_type.nil?
        secret = OpenID::Util.from_base64(results["mac_key"])
      else
        return nil if session_type != "DH-SHA1"
        
        dh_server_public = results["dh_server_public"]
        return nil if dh_server_public.nil?
        
        spub = OpenID::Util.str_to_num(OpenID::Util.from_base64(dh_server_public))
        dh_shared = dh.get_shared_secret(spub)
        enc_mac_key = results["enc_mac_key"]
        secret = OpenID::Util.strxor(OpenID::Util.from_base64(enc_mac_key),
                                     OpenID::Util.sha1(OpenID::Util.num_to_str(dh_shared)))
      end
   
      assoc = OpenID::Association.from_expires_in(expires_in, assoc_handle,
                                                  secret, 'HMAC-SHA1')
      @store.store_association(server_url, assoc)
      return assoc
    end

  end

  # Base class for objects returned from Consumer.begin and Consumer.complete
  class OpenIDStatus

    attr_reader :status

    def initialize(status)
      @status = status
    end

  end

  # Returned by Consumer.begin when server information cannot be determined
  # from the provided identity URL.  The +msg+ method may return a useful
  # string for debugging the request.
  class FailureRequest < OpenIDStatus

    attr_reader :msg

    def initialize(msg='')
      super(FAILURE)
      @msg = msg
    end

  end

  # Encapsulates the information the library retrieves and uses during
  # Consumer.begin.
  class SuccessRequest < OpenIDStatus
    
    attr_reader :server_id, :server_url, :nonce, :identity_url, \
                :service, :return_to_args
    
    # Creates a new SuccessRequest object.  This just stores each
    # argument in an appropriately named field.
    #
    # Users of this library should not create instances of this
    # class.  Instances of this class are created by Consumer
    # during begin.
    def initialize(assoc, nonce, service)
      super(SUCCESS)
      @service = service
      @server_id = service.server_id
      @server_url = service.server_url
      @identity_url = service.consumer_id
      @extra_args = {}
      @return_to_args = {'nonce' => nonce}

      @assoc = assoc
      @nonce = nonce
    end

    # Called to construct the redirect URL sent to
    # the browser to ask the server to verify its identity.  This is
    # called in step 3 of the flow described in the overview.
    # Please note that you don't need to call this method directly
    # unless you need to create a custom redirect, as it is called
    # directly during begin. The generated redirect should be
    # sent to the browser which initiated the authorization request.
    #
    # ==Parameters
    # [+trust_root+]
    #   This is a URL that will be sent to the
    #   server to identify this site.  The OpenID spec (
    #   http://www.openid.net/specs.bml#mode-checkid_immediate )
    #   has more information on what the trust_root value is for
    #   and what its form can be.  While the trust root is
    #   officially optional in the OpenID specification, this
    #   implementation requires that it be set.  Nothing is
    #   actually gained by leaving out the trust root, as you can
    #   get identical behavior by specifying the return_to URL as
    #   the trust root.
    #
    # [+return_to+]
    #   This is the URL that will be included in the
    #   generated redirect as the URL the OpenID server will send
    #   its response to.  The URL passed in must handle OpenID
    #   authentication responses.
    #
    # [+immediate+]
    #   Optional.  If +immediate+ is true, the request will be made using
    #   openid.mode=checkid_immediate instead of the standard
    #   openid.mode=checkid_setup. 
    #
    # ==Return Value
    # Return a string which is the URL to which you should redirect the user.
    def redirect_url(trust_root, return_to, immediate=false)
      # add the nonce into the return_to url
      return_to = OpenID::Util.append_args(return_to, @return_to_args)

      redir_args = {
        "openid.identity" => @server_id,
        "openid.return_to" => return_to,
        "openid.trust_root" => trust_root,
        "openid.mode" => immediate ? 'checkid_immediate' : 'checkid_setup'
      }

      redir_args["openid.assoc_handle"] = @assoc.handle if @assoc
      redir_args.update(@extra_args)
     
      return OpenID::Util.append_args(server_url, redir_args).to_s
    end

    # get the return_to URL
    def return_to(return_to)
      OpenID::Util.append_args(return_to, @return_to_args)
    end

    # Add an openid extension argument to the request. A simple resitration
    # request may look something like:
    #
    #  req.add_extension_arg('sreg','required','email')
    #  req.add_extension_arg('sreg','optional','nickname,gender')
    #  req.add_extension_arg('sreg','policy_url','http://example.com/policy')
    def add_extension_arg(namespace, key, value)
      @extra_args['openid.'+namespace+'.'+key] = value
    end

    def add_arg(key, value)
      @extra_args[key] = value
    end

    # Checks to see if the user's OpenID server additionally supports
    # the extensions service type url provided.
    def uses_extension?(extension_url)
      return false unless extension_url

      @service.service_types.each do |url|
        if OpenID::Util.urls_equal?(url, extension_url)
          return true
        end
      end

      return false
    end

  end

  # Encapsulates the information that is useful after a successful
  # Consumer.complete call.  Verified identity URL and
  # signed extension response values are available through this object.
  class SuccessResponse < OpenIDStatus
    
    attr_reader :identity_url
    attr_accessor :service

    # Instances of this object will be created for you automatically
    # by OpenID::Consumer.  You should never have to construct this
    # object yourself.
    def initialize(identity_url, query)
      super(SUCCESS)
      @identity_url = identity_url
      @query = query
      @service = nil
    end

    # Returns all the arguments from an extension's namespace.  For example
    # 
    #   response.extension_response('sreg')
    # 
    # may return something like:
    #
    #  {'email' => 'mayor@example.com', 'nickname' => 'MayorMcCheese'}
    #
    # The extension namespace is not included in the keys of the returned
    # hash.  Values returned from this method are guaranteed to be signed.
    # Calling this method should be the *only* way you access extension
    # response data!
    def extension_response(extension_name)      
      prefix = extension_name
      
      signed = @query['openid.signed']
      return nil if signed.nil?
      
      signed = signed.split(',')
      extension_args = {}
      extension_prefix = prefix + '.'
      
      signed.each do |arg|
        if arg.index(extension_prefix) == 0
          query_key = 'openid.'+arg
          extension_args[arg[(1+prefix.length..-1)]] = @query[query_key]
        end
      end
      
      return extension_args
    end

  end

  # Object returned from Consumer.complete when the auth request failed.
  # The +identity_url+, +msg+, and +service+ methods may contain useful
  # information about the failure if it is available.  These methods will
  # return nil if no useful info can be determined.
  class FailureResponse < OpenIDStatus
    
    attr_accessor :identity_url, :msg, :service

    def initialize(identity_url=nil, msg=nil)
      super(FAILURE)
      @identity_url = identity_url
      @msg = msg
    end

  end
  
  # Returned by Consumer.begin in immediate mode when the user needs to
  # log into the OpenID server.  User should be redirected to the value
  # returned from the +setup_url+ method.
  class SetupNeededResponse < OpenIDStatus
    
    attr_reader :setup_url
    attr_accessor :identity_url, :service

    def initialize(setup_url)
      super(SETUP_NEEDED)
      @setup_url = setup_url
    end

  end

  # Response returned from Consumer.complete when the user cancels the
  # OpenID transaction.
  class CancelResponse < OpenIDStatus
    attr_accessor :identity_url, :service
    def initialize(identity_url)
      super(CANCEL)
      @identity_url = identity_url
    end
  end

end
