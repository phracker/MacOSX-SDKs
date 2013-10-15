/*	
    NSURLConnection.h
    Copyright (c) 2003-2011, Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/NSObject.h>

@class NSCachedURLResponse;
@class NSData;
@class NSError;
@class NSURLAuthenticationChallenge;
@class NSURLConnectionInternal;
@class NSURLRequest;
@class NSURLResponse;
@class NSRunLoop;
@class NSInputStream;
@class NSURLProtectionSpace;
@protocol NSURLConnectionDelegate;
@class NSOperationQueue;

/*!
    @class NSURLConnection
    
    @abstract An NSURLConnection object provides support to perform
    asynchronous loads of a URL request.
    
    @discussion The interface for NSURLConnection is very sparse,
    providing only the controls to start and cancel asynchronous loads
    of a URL request. Many times, as is the case in the
    NSURLConnectionDelegate protocol, NSURLConnection instances are used
    as tokens that uniquely identifies a particular load of a request
    that have the same request and delegate, but actually are different.
    <p>To load a URL request synchronously, see the
    NSURLConnectionSynchronousLoading category on NSURLConnection.
*/
@interface NSURLConnection : NSObject
{
    @private
    NSURLConnectionInternal *_internal;
}

/*! 
    @method canHandleRequest:
    @abstract Performs a "preflight" operation that performs some
    speculative checks to see if a connection can be initialized, and
    the associated I/O that is started in the initializer methods can
    begin.
    @discussion The result of this method is valid only as long as no
    protocols are registered or unregistered, and as long as the request
    is not mutated (if the request is mutable). Hence, clients should be
    prepared to handle failures even if they have performed request
    preflighting by caling this method.
    @param request The request to preflight.
    @result YES if it is likely that the given request can be used to
    initialize a connection and the associated I/O can be started, NO
    otherwise.
*/
+ (BOOL)canHandleRequest:(NSURLRequest *)request;

/*! 
    @method connectionWithRequest:delegate:
    @abstract Allocates and initializes an NSURLConnection with the
    given request and delegate. The asynchronous URL load process is
    started as part of this method.
    @discussion It is important to note that the delegate callbacks
    defined by the NSURLConnectionDelegate protocol will be
    sent on the thread which calls this method. For this to work
    properly, the calling thread must be running its run loop and must
    be running the default run loop mode.
    @param request The request to load. Note that the request is
    deep-copied as part of the initialization process. Changes made to
    the request argument after this method returns do not affect the
    request that is used for the loading process.
    @param delegate an object to which the NSURLConnection will send
    asynchronous callbacks to convey information about the progress of
    the asynchronous URL load. See the NSURLConnectionDelegate
    protocol for the list of available delegate methods.
    @result A newly-created and autoreleased NSURLConnection instance.
*/
+ (NSURLConnection *)connectionWithRequest:(NSURLRequest *)request delegate:(id)delegate;

/*! 
    @method initWithRequest:delegate:
    @abstract Initializes an NSURLConnection with the given request
    and delegate. The asynchronous URL load process is started as part
    of this method.
    @discussion It is important to note that the delegate callbacks
    defined by the NSURLConnectionDelegate protocol will be
    sent on the thread which calls this method. For this to work
    properly, the calling thread must be running its run loop and must
    be running the default run loop mode.
    <p>This is the designated initializer for the NSURLConnection
    class.
    @param request The request to load. Note that the request is
    deep-copied as part of the initialization process. Changes made to
    the request argument after this method returns do not affect the
    request that is used for the loading process.
    @param delegate an object to which the NSURLConnection will send
    asynchronous callbacks to convey information about the progress of
    the asynchronous URL load. See the NSURLConnectionDelegate protocol
    for the list of available delegate methods.
    @result An initialized NSURLConnection instance. 
*/
- (id)initWithRequest:(NSURLRequest *)request delegate:(id)delegate;

/*!
    @method initWithRequest:delegate:startImmediately:
    @abstract Designated initializer for NSURLConnection; initializes an
        NSURLConnection with the given request and delegate and optionally 
        starts the connection.
    @discussion This method extends the older initWithRequest:delegate: by allowing
        the caller to delay the start of the connection.  This allows the caller
        to customize where the delegate will receive its NSURLConnectionDelegate
        messages via -scheduleWithRunLoop:forMode: or -setDelegateQueue: before the
	connection starts its work.  If startImmediately is NO, the connection
        needs to be started by calling -start before any work to process the request wil be done.
    @param request The request to load.
    @param delegate The object which will receive the delegation messages for the connection
    @param startImmediately Whether the connection should start processing request immediately
        or should delay processing until it receives the -start message.
    @result The initialized NSURLConnection instance
*/
- (id)initWithRequest:(NSURLRequest *)request delegate:(id)delegate startImmediately:(BOOL)startImmediately NS_AVAILABLE(10_5, 2_0);

/*!
    @method start
    @abstract Causes the NSURLConnection to start processing its request, if it has not already.
*/
- (void)start NS_AVAILABLE(10_5, 2_0);

/*! 
    @method cancel
    @abstract Cancels an asynchronous load of a URL.
    @discussion Once this method is called, the asynchronous load is
    stopped, and the NSURLConnectionDelegate associated with the
    receiver will no longer receive any asynchronous callbacks for
    this NSURLConnection.
*/
- (void)cancel;

/* Scheduling APIs
    NSURLConnection sends its delegate messages via the run loop; these methods
    determine which runloops and which modes the messages will be sent on.  At creation,
    a connection is scheduled on the current thread (the one where the creation takes place)
    in the default mode.  That can be changed to add or remove runloop + mode pairs
    using the following methods.  It is permissible to be scheduled on multiple run loops and modes,
    or on the same run loop in multiple modes, so scheduling in one place does not cause unscheduling
    in another.
*/
- (void)scheduleInRunLoop:(NSRunLoop *)aRunLoop forMode:(NSString *)mode NS_AVAILABLE(10_5, 2_0);
- (void)unscheduleFromRunLoop:(NSRunLoop *)aRunLoop forMode:(NSString *)mode NS_AVAILABLE(10_5, 2_0);

/*
    In Mac OS X 10.7, it is now possible to specify an NSOperationQueue upon which
    connection delegate messages will be dispatched.  It is an error to schedule
    with both an NSRunLoop and an NSOperationQueue.
 */
- (void)setDelegateQueue:(NSOperationQueue*) queue NS_AVAILABLE(10_7, 5_0);

@end



/*!
    @protocol NSURLConnectionDelegate <NSObject>

    The NSURLConnectionDelegate formal protocol defines
    NSURLConnection delegate methods that can be implemented by
    objects to receive informational callbacks about the asynchronous
    load of a URL request. Other delegate methods provide hooks that
    allow the delegate to customize the process of performing an
    asynchronous URL load.

    <p>Note that all these will be called on the thread that started
    the asynchronous load operation on the associated NSURLConnection
    object.
    <p>The following contract governs the delivery of the callbacks
    defined in this interface:
    <ul>
    <li>Zero or more <tt>-connection:willSendRequest:redirectResponse:</tt> 
    messages will be sent to the delegate before any other messages in this
    list are sent.
    <li>Before receiving a response or processing a redirect,
    <tt>connection:didReceiveAuthenticationChallenge:</tt> may be
    received if authentication is required.
    <li>Zero or more <tt>connection:didReceiveResponse:</tt> messages
    will be sent to the delegate before receiving a
    <tt>-connection:didReceiveData:</tt> message. In rare cases, as will
    occur in an HTTP load where the content type of the load data is
    multipart/x-mixed-replace, the delegate will receive more than one
    <tt>connection:didReceiveResponse:</tt> message. In the event this
    occurs, delegates should discard all data previously delivered by
    way of the <tt>-connection:didReceiveData:</tt>, and should be
    prepared to handle the, potentially different, MIME type reported by
    the NSURLResponse. Note that the only case where a response is not
    sent to a delegate is when the protocol implemenation encounters an
    error before a response could be created.
    <li>Zero or more <tt>connection:didReceiveData:</tt> messages will
    be sent before and of the following messages are sent to the
    delegate:
        <ul>
        <li><tt>connection:willCacheResponse:</tt>
        <li><tt>-connectionDidFinishLoading:</tt>
        <li><tt>-connection:didFailWithError:</tt>
        </ul>
    <li>Zero or one <tt>connection:willCacheResponse:</tt> messages will
    be sent to the delegate after <tt>connection:didReceiveData:</tt>
    are sent but before a <tt>-connectionDidFinishLoading:</tt> message
    is sent.
    <li>Unless a NSURLConnection receives a <tt>-cancel</tt> message,
    the delegate will receive one and only one of
    <tt>-connectionDidFinishLoading:</tt>, or
    <tt>-connection:didFailWithError:</tt> message, but never
    both. In addition, once either of these callbacks is sent, the
    delegate will receive no further callbacks of any kind for the
    given NSURLConnection. 
    </ul>
*/
@protocol NSURLConnectionDelegate <NSObject>

@optional

/*! 
    @method connection:willSendRequest:redirectResponse:   
    @abstract This method is called whenever an NSURLConnection
    determines that it must change URLs in order to continue loading a
    request.
    @discussion This method gives the delegate an opportunity to
    inspect the request that will be used to continue loading the
    request, and modify it if necessary. The URL-change determinations
    mentioned above can occur as a result of transforming a request
    URL to its canonical form, or can happen for protocol-specific
    reasons, such as an HTTP redirect. 
    <p>If the delegate wishes to reject the redirect, it can call
    <tt>[connection cancel]</tt>, or it can return nil from this
    method. There is one subtle difference which results from this
    choice. If <tt>[connection cancel]</tt> is called in the delegate
    method, all processing for the connection stops, and no futher
    delegate callbacks will be sent. If the delegate returns nil, the
    connection will continue to process, and this has special
    relevance in the case where the redirectResponse argument is
    non-nil. In this case, any data that is loaded for the connection
    will be sent to the delegate, and the delegate will receive a
    finshed or failure delegate callback as appropiate.
    @param connection an NSURLConnection that has determined that it
    must change URLs in order to continue loading a request.
    @param request The NSURLRequest object that will be used to
    continue loading. The delegate should copy and modify this request
    as necessary to change the attributes of the request, or can
    simply return the given request if the delegate determines that no
    changes need to be made.
    @param redirectResponse The NSURLResponse that caused this
    callback to be sent. This argument is nil in cases where this
    callback is not being sent as a result of involving the delegate
    in redirect processing.
    @result The request that the URL loading system will use to
    continue.
*/
- (NSURLRequest *)connection:(NSURLConnection *)connection willSendRequest:(NSURLRequest *)request redirectResponse:(NSURLResponse *)response;

/*! 
    @method connection:needNewBodyStream:  
    @abstract This method is called whenever an NSURLConnection
    determines that it the client needs to provide a new, unopened
    body stream.  This can occur if the request had a body stream
    set on it and requires retransmission.
    @discussion This method gives the delegate an opportunity to
    attach a new, unopened body stream to the connection to handle
    situations where the stream data needs to be retransmitted.  In the
    past on Mac OS X the stream data was spooled to disk in case retransmission
    was required, which may not be desirable for large data sets.  By
    implementing this delegate method the client is opting in to no longer
    having the data spooled to disk - for each retransmission a new stream
    needs to be provided.  Returning NULL from this delegate method will cause
    the connection to fail.
    @param connection an NSURLConnection that has determined that it
    required a new body stream to continue.
    @param request The current NSURLRequest object associated with the connection.
    @result The new unopened body stream to use (see setHTTPBodyStream).
*/
- (NSInputStream *)connection:(NSURLConnection *)connection needNewBodyStream:(NSURLRequest *)request NS_AVAILABLE(10_6, 3_0);

/*!
    @method connection:canAuthenticateAgainstProtectionSpace:
    @abstract This method gives the delegate an opportunity to inspect an NSURLProtectionSpace before an authentication attempt is made.
    @discussion If implemented, will be called before connection:didReceiveAuthenticationChallenge 
    to give the delegate a chance to inspect the protection space that will be authenticated against.  Delegates should determine
    if they are prepared to respond to the authentication method of the protection space and if so, return YES, or NO to
    allow default processing to handle the authentication.  If this delegate is not implemented, then default 
    processing will occur (typically, consulting
    the user's keychain and/or failing the connection attempt.
    @param connection an NSURLConnection that has an NSURLProtectionSpace ready for inspection
    @param protectionSpace an NSURLProtectionSpace that will be used to generate an authentication challenge
    @result a boolean value that indicates the willingness of the delegate to handle the authentication
 */
- (BOOL)connection:(NSURLConnection *)connection canAuthenticateAgainstProtectionSpace:(NSURLProtectionSpace *)protectionSpace NS_AVAILABLE(10_6, 3_0);

/*!
    @method connection:didReceiveAuthenticationChallenge:
    @abstract Start authentication for a given challenge
    @discussion Call useCredential:forAuthenticationChallenge:,
    continueWithoutCredentialForAuthenticationChallenge: or cancelAuthenticationChallenge: on
    the challenge sender when done.
    @param connection the connection for which authentication is needed
    @param challenge The NSURLAuthenticationChallenge to start authentication for
*/
- (void)connection:(NSURLConnection *)connection didReceiveAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

/*!
    @method connection:willSendRequestForAuthenticationChallenge:
    @abstract Start authentication for a given challenge.
    @discussion Call useCredential:forAuthenticationChallenge:,
    continueWithoutCredentialForAuthenticationChallenge:, cancelAuthenticationChallenge:, 
    performDefaultHandlingForAuthenticationChallenge:, or rejectProtectionSpaceAndContinueWithChallenge on
    the challenge sender when done.  All information for making an authentication 
    decision is provided in this callback.  If this callback is implemented, the delegate will not
    receive callbacks to didReceiveAuthenticationChallenge, canAuthenticateAgainstProtectionSpace, or 
    connectionShouldUseCredentialStorage. All the work of those three callbacks can be done in 
    willSendRequestForAuthenticationChallenge:.
    @param connection the connection for which authentication is needed
    @param challenge The NSURLAuthenticationChallenge to start authentication for
 */

- (void)connection:(NSURLConnection *)connection willSendRequestForAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

/*!
    @method connection:didCancelAuthenticationChallenge:
    @abstract Cancel authentication for a given request
    @param connection the connection for which authentication was cancelled
    @param challenge The NSURLAuthenticationChallenge for which to cancel authentication
*/
- (void)connection:(NSURLConnection *)connection didCancelAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

/*! 
    @method connectionShouldUseCredentialStorage   
    @abstract This method allows the delegate to inform the url loader that it
				should not consult the credential storage for the connection.
    @discussion This method will be called before any attempt to authenticate is
		attempted on a connection.  By returning NO the delegate is telling the
		connection to not consult the credential storage and taking responsiblity
		for providing any credentials for authentication challenges.  Not implementing
		this method is the same as returing YES.  The delegate is free to consult the
		credential storage itself when it receives a didReceiveAuthenticationChallenge
		message.
    @param connection  the NSURLConnection object asking if it should consult the credential storage.
    @result NO if the connection should not consult the credential storage, Yes if it should.
*/
- (BOOL)connectionShouldUseCredentialStorage:(NSURLConnection *)connection NS_AVAILABLE(10_6, 3_0);

/*! 
    @method connection:didReceiveResponse:   
    @abstract This method is called when the URL loading system has
    received sufficient load data to construct a NSURLResponse object.
    @discussion The given NSURLResponse is immutable and
    will not be modified by the URL loading system once it is
    presented to the NSURLConnectionDelegate by this method.
    <p>See the protocol description for information regarding
    the contract associated with the delivery of this delegate 
    callback.
    @param connection an NSURLConnection instance for which the
    NSURLResponse is now available.
    @param response the NSURLResponse object for the given
    NSURLConnection.
*/
- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response;

/*! 
    @method connection:didReceiveData:   
    @abstract This method is called to deliver the content of a URL
    load.
    @discussion Load data is delivered incrementally. Clients can
    concatenate each successive NSData object delivered through this
    method over the course of an asynchronous load to build up the
    complete data for a URL load. It is also important to note that this
    method provides the only way for an ansynchronous delegate to find
    out about load data. In other words, it is the responsibility of the
    delegate to retain or copy this data as it is delivered through this
    method.
    <p>See the protocol description for information regarding
    the contract associated with the delivery of this delegate 
    callback.
    @param connection  NSURLConnection that has received data.
    @param data A chunk of URL load data.
*/
- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data;

/*! 
    @method connection:didSendBodyData:   
    @abstract This method is called to deliver progress information
	    for a url upload.  The bytes refer to bytes of the body
	    associated with the url request.
    @discussion This method is called as the body (message data) of a request 
    is transmitted (as during an http POST).  It provides the number of bytes 
    written for the latest write, the total number of bytes written and the 
    total number of bytes the connection expects to write (for HTTP this is 
    based on the content length). The total number of expected bytes may change
    if the request needs to be retransmitted (underlying connection lost, authentication
    challenge from the server, etc.).
    @param connection  NSURLConnection that has written data.
    @param bytesWritten number of bytes written 
    @param totalBytesWritten total number of bytes written for this connection
    @param totalBytesExpectedToWrite the number of bytes the connection expects to write (can change due to retransmission of body content)
*/
- (void)connection:(NSURLConnection *)connection didSendBodyData:(NSInteger)bytesWritten totalBytesWritten:(NSInteger)totalBytesWritten totalBytesExpectedToWrite:(NSInteger)totalBytesExpectedToWrite NS_AVAILABLE(10_6, 3_0);

/*! 
    @method connectionDidFinishLoading:   
    @abstract This method is called when an NSURLConnection has
    finished loading successfully.
    @discussion See the protocol description for information regarding
    the contract associated with the delivery of this delegate
    callback.
    @param connection an NSURLConnection that has finished loading
    successfully.
*/
- (void)connectionDidFinishLoading:(NSURLConnection *)connection;

/*! 
    @method connection:didFailWithError:   
    @abstract This method is called when an NSURLConnection has
    failed to load successfully.
    @discussion See the protocol description for information regarding
    the contract associated with the delivery of this delegate
    callback.
    @param connection an NSURLConnection that has failed to load.
    @param error The error that encapsulates information about what
    caused the load to fail.
*/
- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error;

/*!
    @method connection:willCacheResponse:
    @abstract This method gives the delegate an opportunity to inspect
    the NSCachedURLResponse that will be stored in the cache, and modify
    it if necessary.
    @discussion See the protocol description for information regarding
    the contract associated with the delivery of this delegate
    callback.
    @param connection an NSURLConnection that has a NSCachedURLResponse
    ready for inspection.
    @result a NSCachedURLResponse that will be written to the cache. The
    delegate need not perform any customization and may return the
    NSCachedURLResponse passed to it. The delegate may replace the
    NSCachedURLResponse with a completely new one. The delegate may also
    return nil to indicate that no NSCachedURLResponse should be stored
    for this connection.
*/
- (NSCachedURLResponse *)connection:(NSURLConnection *)connection willCacheResponse:(NSCachedURLResponse *)cachedResponse;

@end



/*!
    @category NSURLConnection(NSURLConnectionSynchronousLoading)
    The NSURLConnectionSynchronousLoading category on NSURLConnection
    provides the interface to perform synchronous loading of URL
    requests.
*/
@interface NSURLConnection (NSURLConnectionSynchronousLoading)

/*! 
    @method sendSynchronousRequest:returningResponse:error:
    @abstract Performs a synchronous load of the given request,
    returning an NSURLResponse in the given out parameter.
    @discussion A synchronous load for the given request is built on
    top of the asynchronous loading code made available by the class.
    The calling thread is blocked while the asynchronous loading
    system performs the URL load on a thread spawned specifically for
    this load request. No special threading or run loop configuration
    is necessary in the calling thread in order to perform a
    synchronous load. For instance, the calling thread need not be
    running its run loop.
    @param request The request to load. Note that the request is
    deep-copied as part of the initialization process. Changes made to
    the request argument after this method returns do not affect the
    request that is used for the loading process.
    @param response An out parameter which is filled in with the
    response generated by performing the load.
    @param error Out parameter (may be NULL) used if an error occurs
    while processing the request. Will not be modified if the load
    succeeds.
    @result The content of the URL resulting from performing the load,
    or nil if the load failed.
*/
+ (NSData *)sendSynchronousRequest:(NSURLRequest *)request returningResponse:(NSURLResponse **)response error:(NSError **)error;

@end

#if NS_BLOCKS_AVAILABLE

/*!
    @category NSURLConnection(NSURLConnectionQueuedLoading)

    The NSURLConnectionQueuedLoading category on NSURLConnection
    provides the interface to perform asynchronous loading of URL
    requests where the results of the request are delivered to a
    block via an NSOperationQueue.

    Note that there is no guarantee of load ordering implied by this
    method.
 */
@interface NSURLConnection (NSURLConnectionQueuedLoading)

/*!
    @method sendAsynchronousRequest:queue:completionHandler:
    @abstract Performs an asynchronous load of the given request. When
    the request has completed or failed, the block will be executed
    from the context of the specified NSOperationQueue.
    @discussion This is a convenience routine that allows for
    asynchronous loading of an url based resource.  If the resource load
    is successful, the data parameter to the callback will contain the
    resource data and the error parameter will be nil.  If the
    resource load fails, the data parameter will be nil and the error
    will contain information about the failure.
    @param request The request to load. Note that the request is
    deep-copied as part of the initialization process. Changes made to
    the request argument after this method returns do not affect the
    request that is used for the loading process.
    @param queue An NSOperationQueue upon which	the handler block will
    be dispatched.
    @param handler A block which receives the results of the resource
    load.
 */
+ (void)sendAsynchronousRequest:(NSURLRequest *)request
			  queue:(NSOperationQueue*) queue
	      completionHandler:(void (^)(NSURLResponse*, NSData*, NSError*)) handler NS_AVAILABLE(10_7, 5_0);
		   
@end
				   
#endif

		   
