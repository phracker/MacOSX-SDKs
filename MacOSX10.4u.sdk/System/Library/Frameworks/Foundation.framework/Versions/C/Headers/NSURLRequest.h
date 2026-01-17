/*	
    NSURLRequest.h
    Copyright (C) 2003-2005, Apple Computer, Inc. All rights reserved.    
    
    Public header file.
*/

// Note: To use the APIs described in these headers, you must perform
// a runtime check for Foundation-462.1 or later.
#import <AvailabilityMacros.h>
#if defined(MAC_OS_X_VERSION_10_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2)

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

@class NSData;
@class NSDictionary;
@class NSInputStream;
@class NSString;
@class NSURL;
@class NSURLRequestInternal;

/*!
    @header NSURLRequest.h

    This header file describes the constructs used to represent URL
    load requests in a manner independent of protocol and URL scheme.
    Immutable and mutable variants of this URL load request concept
    are described, named NSURLRequest and NSMutableURLRequest,
    respectively. A collection of constants is also declared to
    exercise control over URL content caching policy.

    <p>NSURLRequest and NSMutableURLRequest are designed to be
    customized to support protocol-specific requests. Protocol
    implementors who need to extend the capabilities of NSURLRequest
    and NSMutableURLRequest are encouraged to provide categories on
    these classes as appropriate to support protocol-specific data. To
    store and retrieve data, category methods can use the
    <tt>+propertyForKey:inRequest:</tt> and
    <tt>+setProperty:forKey:inRequest:</tt> class methods on
    NSURLProtocol. See the NSHTTPURLRequest on NSURLRequest and
    NSMutableHTTPURLRequest on NSMutableURLRequest for examples of
    such extensions.

    <p>The main advantage of this design is that a client of the URL
    loading library can implement request policies in a standard way
    without type checking of requests or protocol checks on URLs. Any
    protocol-specific details that have been set on a URL request will
    be used if they apply to the particular URL being loaded, and will
    be ignored if they do not apply.
*/

/*!
    @enum NSURLRequestCachePolicy
    
    @discussion The NSURLRequestCachePolicy enum defines constants that
    can be used to specify the type of interactions that take place with
    the caching system when the URL loading system processes a request.
    Specifically, these constants cover interactions that have to do
    with whether already-existing cache data is returned to satisfy a
    URL load request.
    
    @constant NSURLRequestUseProtocolCachePolicy Specifies that the
    caching logic defined in the protocol implementation, if any, is
    used for a particular URL load request. This is the default policy
    for URL load requests.
              
    @constant NSURLRequestReloadIgnoringCacheData Specifies that the
    data for the URL load should be loaded from the origin source. No
    existing cache data, regardless of its freshness or validity,
    should be used to satisfy a URL load request.
              
    @constant NSURLRequestReturnCacheDataElseLoad Specifies that the
    existing cache data should be used to satisfy a URL load request,
    regardless of its age or expiration date. However, if there is no
    existing data in the cache corresponding to a URL load request,
    the URL is loaded from the origin source.
              
    @constant NSURLRequestReturnCacheDataDontLoad Specifies that the
    existing cache data should be used to satisfy a URL load request,
    regardless of its age or expiration date. However, if there is no
    existing data in the cache corresponding to a URL load request, no
    attempt is made to load the URL from the origin source, and the
    load is considered to have failed. This constant specifies a
    behavior that is similar to an "offline" mode.
*/
typedef enum
{
    NSURLRequestUseProtocolCachePolicy,
    NSURLRequestReloadIgnoringCacheData,
    NSURLRequestReturnCacheDataElseLoad,
    NSURLRequestReturnCacheDataDontLoad,
} NSURLRequestCachePolicy;


/*!
    @class NSURLRequest
    
    @abstract An NSURLRequest object represents a URL load request in a
    manner independent of protocol and URL scheme.
    
    @discussion NSURLRequest encapsulates two basic data elements about
    a URL load request:
    <ul>
    <li>The URL to load.
    <li>The policy to use when consulting the URL content cache made
    available by the implementation.
    </ul>
    In addition, NSURLRequest is designed to be extended to support
    protocol-specific data by adding categories to access a property
    object provided in an interface targeted at protocol implementors.
    <ul>
    <li>Protocol implementors should direct their attention to the
    NSURLRequestExtensibility category on NSURLRequest for more
    information on how to provide extensions on NSURLRequest to
    support protocol-specific request information.
    <li>Clients of this API who wish to create NSURLRequest objects to
    load URL content should consult the protocol-specific NSURLRequest
    categories that are available. The NSHTTPURLRequest category on
    NSURLRequest is an example.
    </ul>
    <p>
    Objects of this class are used to create NSURLConnection instances,
    which can are used to perform the load of a URL, or as input to the
    NSURLConnection class method which performs synchronous loads.
*/
@interface NSURLRequest : NSObject <NSCoding, NSCopying, NSMutableCopying>
{
    @private
    NSURLRequestInternal *_internal;
}

/*! 
    @method requestWithURL:
    @abstract Allocates and initializes an NSURLRequest with the given
    URL.
    @discussion Default values are used for cache policy
    (NSURLRequestUseProtocolCachePolicy) and timeout interval (60
    seconds).
    @param URL The URL for the request.
    @result A newly-created and autoreleased NSURLRequest instance.
*/
+ (id)requestWithURL:(NSURL *)URL;

/*! 
    @method requestWithURL:cachePolicy:properties:
    @abstract Allocates and initializes a NSURLRequest with the given
    URL and cache policy.
    @param URL The URL for the request. 
    @param cachePolicy The cache policy for the request. 
    @param timeoutInterval The timeout interval for the request. See the
    commentary for the <tt>timeoutInterval</tt> for more information on
    timeout intervals.
    @result A newly-created and autoreleased NSURLRequest instance. 
*/
+ (id)requestWithURL:(NSURL *)URL cachePolicy:(NSURLRequestCachePolicy)cachePolicy timeoutInterval:(NSTimeInterval)timeoutInterval;

/*! 
    @method initWithURL:
    @abstract Initializes an NSURLRequest with the given URL. 
    @discussion Default values are used for cache policy
    (NSURLRequestUseProtocolCachePolicy) and timeout interval (60
    seconds).
    @param URL The URL for the request. 
    @result An initialized NSURLRequest. 
*/
- (id)initWithURL:(NSURL *)URL;

/*! 
    @method initWithURL:
    @abstract Initializes an NSURLRequest with the given URL and
    cache policy.
    @discussion This is the designated initializer for the 
    NSURLRequest class.
    @param URL The URL for the request. 
    @param cachePolicy The cache policy for the request. 
    @param timeoutInterval The timeout interval for the request. See the
    commentary for the <tt>timeoutInterval</tt> for more information on
    timeout intervals.
    @result An initialized NSURLRequest. 
*/
- (id)initWithURL:(NSURL *)URL cachePolicy:(NSURLRequestCachePolicy)cachePolicy timeoutInterval:(NSTimeInterval)timeoutInterval;

/*! 
    @method URL
    @abstract Returns the URL of the receiver. 
    @result The URL of the receiver. 
*/
- (NSURL *)URL;

/*! 
    @method cachePolicy
    @abstract Returns the cache policy of the receiver. 
    @result The cache policy of the receiver. 
*/
- (NSURLRequestCachePolicy)cachePolicy;

/*! 
    @method timeoutInterval
    @abstract Returns the timeout interval of the receiver.
    @discussion The timeout interval specifies the limit on the idle
    interval alloted to a request in the process of loading. The "idle
    interval" is defined as the period of time that has passed since the
    last instance of load activity occurred for a request that is in the
    process of loading. Hence, when an instance of load activity occurs
    (e.g. bytes are received from the network for a request), the idle
    interval for a request is reset to 0. If the idle interval ever
    becomes greater than or equal to the timeout interval, the request
    is considered to have timed out. This timeout interval is measured
    in seconds.
    @result The timeout interval of the receiver. 
*/
- (NSTimeInterval)timeoutInterval;

/*!
    @method mainDocumentURL
    @abstract The main document URL associated with this load.
    @discussion This URL is used for the cookie "same domain as main
    document" policy. There may also be other future uses.
    See setMainDocumentURL:
    NOTE: In the current implementation, this value is unused by the
    framework. A fully functional version of this method will be available 
    in the future. 
    @result The main document URL.
*/
- (NSURL *)mainDocumentURL;

@end



/*! 
    @class NSMutableURLRequest
    
    @abstract An NSMutableURLRequest object represents a mutable URL load
    request in a manner independent of protocol and URL scheme.
    
    @discussion This specialization of NSURLRequest is provided to aid
    developers who may find it more convenient to mutate a single request
    object for a series of URL loads instead of creating an immutable
    NSURLRequest for each load. This programming model is supported by
    the following contract stipulation between NSMutableURLRequest and 
    NSURLConnection: NSURLConnection makes a deep copy of each 
    NSMutableURLRequest object passed to one of its initializers.    
    <p>NSMutableURLRequest is designed to be extended to support
    protocol-specific data by adding categories to access a property
    object provided in an interface targeted at protocol implementors.
    <ul>
    <li>Protocol implementors should direct their attention to the
    NSMutableURLRequestExtensibility category on
    NSMutableURLRequest for more information on how to provide
    extensions on NSMutableURLRequest to support protocol-specific
    request information.
    <li>Clients of this API who wish to create NSMutableURLRequest
    objects to load URL content should consult the protocol-specific
    NSMutableURLRequest categories that are available. The
    NSMutableHTTPURLRequest category on NSMutableURLRequest is an
    example.
    </ul>
*/
@interface NSMutableURLRequest : NSURLRequest

/*! 
    @method setURL
    @abstract Sets the URL of the receiver. 
    @param URL The new URL for the receiver. 
*/
- (void)setURL:(NSURL *)URL;

/*! 
    @method setCachePolicy:
    @abstract Sets the cache policy of the receiver. 
    @param policy The new NSURLRequestCachePolicy for the receiver. 
*/
- (void)setCachePolicy:(NSURLRequestCachePolicy)policy;

/*! 
    @method setTimeoutInterval:
    @abstract Sets the timeout interval of the receiver.
    @discussion The timeout interval specifies the limit on the idle
    interval allotted to a request in the process of loading. The "idle
    interval" is defined as the period of time that has passed since the
    last instance of load activity occurred for a request that is in the
    process of loading. Hence, when an instance of load activity occurs
    (e.g. bytes are received from the network for a request), the idle
    interval for a request is reset to 0. If the idle interval ever
    becomes greater than or equal to the timeout interval, the request
    is considered to have timed out. This timeout interval is measured
    in seconds.
    @param seconds The new timeout interval of the receiver. 
*/
- (void)setTimeoutInterval:(NSTimeInterval)seconds;

/*!
    @method setMainDocumentURL:
    @abstract Sets the main document URL
    @param URL The main document URL.
    @discussion The caller should pass the URL for an appropriate main
    document, if known. For example, when loading a web page, the URL
    of the main html document for the top-level frame should be
    passed.  This main document will be used to implement the cookie
    "only from same domain as main document" policy, and possibly
    other things in the future.
    NOTE: In the current implementation, the passed-in value is unused by the
    framework. A fully functional version of this method will be available 
    in the future. 
*/
- (void)setMainDocumentURL:(NSURL *)URL;

@end



/*!
    @category NSURLRequest(NSHTTPURLRequest) 
    The NSHTTPURLRequest on NSURLRequest provides methods for accessing
    information specific to HTTP protocol requests.
*/
@interface NSURLRequest (NSHTTPURLRequest) 

/*! 
    @method HTTPMethod
    @abstract Returns the HTTP request method of the receiver. 
    @result the HTTP request method of the receiver. 
*/
- (NSString *)HTTPMethod;

/*! 
    @method allHTTPHeaderFields
    @abstract Returns a dictionary containing all the HTTP header fields
    of the receiver.
    @result a dictionary containing all the HTTP header fields of the
    receiver.
*/
- (NSDictionary *)allHTTPHeaderFields;

/*! 
    @method valueForHTTPHeaderField:
    @abstract Returns the value which corresponds to the given header
    field. Note that, in keeping with the HTTP RFC, HTTP header field
    names are case-insensitive.
    @param field the header field name to use for the lookup
    (case-insensitive).
    @result the value associated with the given header field, or nil if
    there is no value associated with the given header field.
*/
- (NSString *)valueForHTTPHeaderField:(NSString *)field;

/*! 
    @method HTTPBody
    @abstract Returns the request body data of the receiver. 
    @discussion This data is sent as the message body of the request, as
    in done in an HTTP POST request.
    @result The request body data of the receiver. 
*/
- (NSData *)HTTPBody;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/*!
    @method HTTPBodyStream
    @abstract Returns the request body stream of the receiver
    if any has been set
    @discussion The stream is returned for examination only; it is
    not safe for the caller to manipulate the stream in any way.  Also
    note that the HTTPBodyStream and HTTPBody are mutually exclusive - only
    one can be set on a given request.  Also note that the body stream is
    preserved across copies, but is LOST when the request is coded via the 
    NSCoding protocol
    @result The request body stream of the receiver.
*/
- (NSInputStream *)HTTPBodyStream;
#endif

/*! 
    @method HTTPShouldHandleCookies
    @abstract Determine whether default cookie handling will happen for 
    this request.
    @discussion NOTE: In the current implementation, this value is unused by the
    framework. A fully functional version of this method will be available 
    in the future. 
    @result YES if cookies will be sent with and set for this request; 
    otherwise NO.
*/
- (BOOL)HTTPShouldHandleCookies;

@end



/*!
    @category NSMutableURLRequest(NSMutableHTTPURLRequest) 
    The NSMutableHTTPURLRequest on NSMutableURLRequest provides methods
    for configuring information specific to HTTP protocol requests.
*/
@interface NSMutableURLRequest (NSMutableHTTPURLRequest) 

/*! 
    @method setHTTPMethod:
    @abstract Sets the HTTP request method of the receiver. 
    @param method the new HTTP request method for the receiver.
*/
- (void)setHTTPMethod:(NSString *)method;

/*! 
    @method setAllHTTPHeaderFields:
    @abstract Sets the HTTP header fields of the receiver to the given
    dictionary.
    @discussion This method replaces all header fields that may have
    existed before this method call. 
    <p>Since HTTP header fields must be string values, each object and
    key in the dictionary passed to this method must answer YES when
    sent an <tt>-isKindOfClass:[NSString class]</tt> message. If either
    the key or value for a key-value pair answers NO when sent this
    message, the key-value pair is skipped.
    @param headerFields a dictionary containing HTTP header fields.
*/
- (void)setAllHTTPHeaderFields:(NSDictionary *)headerFields;

/*! 
    @method setValue:forHTTPHeaderField:
    @abstract Sets the value of the given HTTP header field.
    @discussion If a value was previously set for the given header
    field, that value is replaced with the given value. Note that, in
    keeping with the HTTP RFC, HTTP header field names are
    case-insensitive.
    @param value the header field value. 
    @param field the header field name (case-insensitive). 
*/
- (void)setValue:(NSString *)value forHTTPHeaderField:(NSString *)field;

/*! 
    @method addValue:forHTTPHeaderField:
    @abstract Adds an HTTP header field in the current header
    dictionary.
    @discussion This method provides a way to add values to header
    fields incrementally. If a value was previously set for the given
    header field, the given value is appended to the previously-existing
    value. The appropriate field delimiter, a comma in the case of HTTP,
    is added by the implementation, and should not be added to the given
    value by the caller. Note that, in keeping with the HTTP RFC, HTTP
    header field names are case-insensitive.
    @param value the header field value. 
    @param field the header field name (case-insensitive). 
*/
- (void)addValue:(NSString *)value forHTTPHeaderField:(NSString *)field;

/*! 
    @method setHTTPBody:
    @abstract Sets the request body data of the receiver.
    @discussion This data is sent as the message body of the request, as
    in done in an HTTP POST request.
    @param data the new request body data for the receiver.
*/
- (void)setHTTPBody:(NSData *)data;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/*!
    @method setHTTPBodyStream:
    @abstract Sets the request body to be the contents of the given stream. 
    @discussion The provided stream should be unopened; the request will take
    over the stream's delegate.  The entire stream's contents will be 
    transmitted as the HTTP body of the request.  Note that the body stream
    and the body data (set by setHTTPBody:, above) are mutually exclusive 
    - setting one will clear the other. 
    @param inputStream the new input stream for use by the receiver
*/
- (void)setHTTPBodyStream:(NSInputStream *)inputStream;
#endif

/*! 
    @method setHTTPShouldHandleCookies
    @abstract Decide whether default cookie handling will happen for 
    this request.
    @param should YES if cookies should be sent with and set for this request; 
    otherwise NO.
    @discussion The default is YES - in other words, cookies are sent from and 
    stored to the cookie manager by default.
    NOTE: In the current implementation, the passed-in value is unused by the
    framework. A fully functional version of this method will be available 
    in the future. 
*/
- (void)setHTTPShouldHandleCookies:(BOOL)should;

@end

#endif
