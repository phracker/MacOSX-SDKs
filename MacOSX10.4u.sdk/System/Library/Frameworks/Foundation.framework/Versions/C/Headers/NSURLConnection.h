/*	
    NSURLConnection.h
    Copyright (C) 2003-2005, Apple Computer, Inc. All rights reserved.    
    
    Public header file.
*/

// Note: To use the APIs described in these headers, you must perform
// a runtime check for Foundation-462.1 or later.
#import <AvailabilityMacros.h>
#if defined(MAC_OS_X_VERSION_10_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2)

#import <Foundation/NSObject.h>

@class NSCachedURLResponse;
@class NSData;
@class NSError;
@class NSURLAuthenticationChallenge;
@class NSURLConnectionInternal;
@class NSURLRequest;
@class NSURLResponse;

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
    defined by the NSURLConnectionDelegate informal protocol will be
    sent on the thread which calls this method. For this to work
    properly, the calling thread must be running its run loop and must
    be running the default run loop mode.
    @param request The request to load. Note that the request is
    deep-copied as part of the initialization process. Changes made to
    the request argument after this method returns do not affect the
    request that is used for the loading process.
    @param delegate an object to which the NSURLConnection will send
    asynchronous callbacks to convey information about the progress of
    the asynchronous URL load. See the NSURLConnectionDelegate informal 
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
    defined by the NSURLConnectionDelegate informal protocol will be
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
    the asynchronous URL load. See the NSURLConnectionDelegate informal 
    protocol for the list of available delegate methods.
    @result An initialized NSURLConnection instance. 
*/
- (id)initWithRequest:(NSURLRequest *)request delegate:(id)delegate;


/*! 
    @method cancel
    @abstract Cancels an asynchronous load of a URL.
    @discussion Once this method is called, the asynchronous load is
    stopped, and the NSURLConnectionDelegate associated with the
    receiver will no longer receive any asynchronous callbacks for
    this NSURLConnection.
*/
- (void)cancel;

@end



/*!
    @category NSObject(NSURLConnectionDelegate)

    The NSURLConnectionDelegate category on NSObject defines
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
@interface NSObject (NSURLConnectionDelegate)

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
    @method connection:didCancelAuthenticationChallenge:
    @abstract Cancel authentication for a given request
    @param connection the connection for which authentication was cancelled
    @param challenge The NSURLAuthenticationChallenge for which to cancel authentication
*/
- (void)connection:(NSURLConnection *)connection didCancelAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

/*! 
    @method connection:didReceiveResponse:   
    @abstract This method is called when the URL loading system has
    received sufficient load data to construct a NSURLResponse object.
    @discussion The given NSURLResponse is immutable and
    will not be modified by the URL loading system once it is
    presented to the NSURLConnectionDelegate by this method.
    <p>See the category description for information regarding
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
    <p>See the category description for information regarding
    the contract associated with the delivery of this delegate 
    callback.
    @param connection  NSURLConnection that has received data.
    @param data A chunk of URL load data.
*/
- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data;

/*! 
    @method connectionDidFinishLoading:   
    @abstract This method is called when an NSURLConnection has
    finished loading successfully.
    @discussion See the category description for information regarding
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
    @discussion See the category description for information regarding
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
    @discussion See the category description for information regarding
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
    @param error An out parameter which is filled in with the
    error generated by performing the load. If no error occurred
    the load, this will be nil.
    @result The content of the URL resulting from performing the load,
    or nil if the load failed.
*/
+ (NSData *)sendSynchronousRequest:(NSURLRequest *)request returningResponse:(NSURLResponse **)response error:(NSError **)error;

@end

#endif
