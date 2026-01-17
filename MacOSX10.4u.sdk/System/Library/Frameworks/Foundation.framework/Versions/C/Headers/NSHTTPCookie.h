/*	
    NSHTTPCookie.h
    Copyright (C) 2003-2005, Apple Computer, Inc. All rights reserved.    
    
    Public header file.
*/

// Note: To use the APIs described in these headers, you must perform
// a runtime check for Foundation-462.1 or later.
#import <AvailabilityMacros.h>
#if defined(MAC_OS_X_VERSION_10_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2)

#import <Foundation/NSObject.h>

@class NSArray;
@class NSDate;
@class NSDictionary;
@class NSString;
@class NSURL;

/*!
    @const NSHTTPCookieName
    @discussion Key for cookie name
*/
extern NSString * const NSHTTPCookieName;

/*!
    @const NSHTTPCookieValue
    @discussion Key for cookie value
*/
extern NSString * const NSHTTPCookieValue;

/*!
    @const NSHTTPCookieOriginURL
    @discussion Key for cookie origin URL
*/
extern NSString * const NSHTTPCookieOriginURL;

/*!
    @const NSHTTPCookieVersion
    @discussion Key for cookie version
*/
extern NSString * const NSHTTPCookieVersion;

/*!
    @const NSHTTPCookieDomain
    @discussion Key for cookie domain
*/
extern NSString * const NSHTTPCookieDomain;

/*!
    @const NSHTTPCookiePath
    @discussion Key for cookie path
*/
extern NSString * const NSHTTPCookiePath;

/*!
    @const NSHTTPCookieSecure
    @discussion Key for cookie secure flag
*/
extern NSString * const NSHTTPCookieSecure;

/*!
    @const NSHTTPCookieExpires
    @discussion Key for cookie expiration date
*/
extern NSString * const NSHTTPCookieExpires;

/*!
    @const NSHTTPCookieComment
    @discussion Key for cookie comment text
*/
extern NSString * const NSHTTPCookieComment;

/*!
    @const NSHTTPCookieCommentURL
    @discussion Key for cookie comment URL
*/
extern NSString * const NSHTTPCookieCommentURL;

/*!
    @const NSHTTPCookieDiscard
    @discussion Key for cookie discard (session-only) flag
*/
extern NSString * const NSHTTPCookieDiscard;

/*!
    @const NSHTTPCookieMaximumAge
    @discussion Key for cookie maximum age (an alternate way of specifying the expiration)
*/
extern NSString * const NSHTTPCookieMaximumAge;

/*!
    @const NSHTTPCookiePort
    @discussion Key for cookie ports
*/
extern NSString * const NSHTTPCookiePort;


@class NSHTTPCookieInternal;

/*!
    @class NSHTTPCookie
    @abstract NSHTTPCookie represents an http cookie.
    @discussion A NSHTTPCookie instance represents a single http cookie. It is
    an immutable object initialized from a dictionary that contains
    the various cookie attributes. It has accessors to get the various
    attributes of a cookie.
*/

@interface NSHTTPCookie : NSObject
{
@private
    NSHTTPCookieInternal * _cookiePrivate;
}

/*!
    @method initWithProperties:
    @abstract Initialize a NSHTTPCookie object with a dictionary of
    parameters
    @param properties The dictionary of properties to be used to
    initialize this cookie.
    @discussion Supported dictionary keys and value types for the
    given dictionary are as follows.

    All properties can handle an NSString value, but some can also
    handle other types.

    <table border=1 cellspacing=2 cellpadding=4>
    <tr>
        <th>Property key constant</th>
        <th>Type of value</th>
        <th>Required</th>
        <th>Description</th>
    </tr>
    <tr>
        <td>NSHTTPCookieComment</td>
        <td>NSString</td>
        <td>NO</td>
        <td>Comment for the cookie. Only valid for version 1 cookies and
        later. Default is nil.</td>
    </tr>
    <tr>
        <td>NSHTTPCookieCommentURL</td>
        <td>NSURL or NSString</td>
        <td>NO</td>
        <td>Comment URL for the cookie. Only valid for version 1 cookies
        and later. Default is nil.</td>
    </tr>
    <tr>
        <td>NSHTTPCookieDomain</td>
        <td>NSString</td>
        <td>Special, a value for either NSHTTPCookieOriginURL or
        NSHTTPCookieDomain must be specified.</td>
        <td>Domain for the cookie. Inferred from the value for
        NSHTTPCookieOriginURL if not provided.</td>
    </tr>
    <tr>
        <td>NSHTTPCookieDiscard</td>
        <td>NSString</td>
        <td>NO</td>
        <td>A string stating whether the cookie should be discarded at
        the end of the session. String value must be either "TRUE" or
        "FALSE". Default is "FALSE", unless this is cookie is version
        1 or greater and a value for NSHTTPCookieMaximumAge is not
        specified, in which case it is assumed "TRUE".</td>
    </tr>
    <tr>
        <td>NSHTTPCookieExpires</td>
        <td>NSDate or NSString</td>
        <td>NO</td>
        <td>Expiration date for the cookie. Used only for version 0
        cookies. Ignored for version 1 or greater.</td>
    </tr>
    <tr>
        <td>NSHTTPCookieMaximumAge</td>
        <td>NSString</td>
        <td>NO</td>
        <td>A string containing an integer value stating how long in
        seconds the cookie should be kept, at most. Only valid for
        version 1 cookies and later. Default is "0".</td>
    </tr>
    <tr>
        <td>NSHTTPCookieName</td>
        <td>NSString</td>
        <td>YES</td>
        <td>Name of the cookie</td>
    </tr>
    <tr>
        <td>NSHTTPCookieOriginURL</td>
        <td>NSURL or NSString</td>
        <td>Special, a value for either NSHTTPCookieOriginURL or
        NSHTTPCookieDomain must be specified.</td>
        <td>URL that set this cookie. Used as default for other fields
        as noted.</td>
    </tr>
    <tr>
        <td>NSHTTPCookiePath</td>
        <td>NSString</td>
        <td>NO</td>
        <td>Path for the cookie. Inferred from the value for
        NSHTTPCookieOriginURL if not provided. Default is "/".</td>
    </tr>
    <tr>
        <td>NSHTTPCookiePort</td>
        <td>NSString</td>
        <td>NO</td>
        <td>comma-separated integer values specifying the ports for the
        cookie. Only valid for version 1 cookies and later. Default is
        empty string ("").</td>
    </tr>
    <tr>
        <td>NSHTTPCookieSecure</td>
        <td>NSString</td>
        <td>NO</td>
        <td>A string stating whether the cookie should be transmitted
        only over secure channels. String value must be either "TRUE"
        or "FALSE". Default is "FALSE".</td>
    </tr>
    <tr>
        <td>NSHTTPCookieValue</td>
        <td>NSString</td>
        <td>YES</td>
        <td>Value of the cookie</td>
    </tr>
    <tr>
        <td>NSHTTPCookieVersion</td>
        <td>NSString</td>
        <td>NO</td>
        <td>Specifies the version of the cookie. Must be either "0" or
        "1". Default is "0".</td>
    </tr>
    </table>
    <p>
    All other keys are ignored.
    @result An initialized NSHTTPCookie, or nil if the set of
    dictionary keys is invalid, for example because a required key is
    missing, or a recognized key maps to an illegal value.
*/
- (id)initWithProperties:(NSDictionary *)properties;

/*!
    @method cookieWithProperties:
    @abstract Allocates and initializes an NSHTTPCookie with the given
    dictionary.
    @discussion See the NSHTTPCookie <tt>-initWithProperties:</tt>
    method for more information on the constraints imposed on the
    dictionary, and for descriptions of the supported keys and values.
    @param properties The dictionary to use to initialize this cookie.
    @result A newly-created and autoreleased NSHTTPCookie instance, or
    nil if the set of dictionary keys is invalid, for example because
    a required key is missing, or a recognized key maps to an illegal
    value.
*/
+ (id)cookieWithProperties:(NSDictionary *)properties;

/*!
    @method requestHeaderFieldsWithCookies:
    @abstract Return a dictionary of header fields that can be used to add the
    specified cookies to the request.
    @param cookies The cookies to turn into request headers.
    @result An NSDictionary where the keys are header field names, and the values
    are the corresponding header field values.
*/
+ (NSDictionary *)requestHeaderFieldsWithCookies:(NSArray *)cookies;

/*!
    @method cookiesWithResponseHeaderFields:forURL:
    @abstract Return an array of cookies parsed from the specified response header fields and URL.
    @param headerFields The response header fields to check for cookies.
    @param URL The URL that the cookies came from - relevant to how the cookies are interpeted.
    @result An NSArray of NSHTTPCookie objects
    @discussion This method will ignore irrelevant header fields so
    you can pass a dictionary containing data other than cookie data.
*/
+ (NSArray *)cookiesWithResponseHeaderFields:(NSDictionary *)headerFields forURL:(NSURL *)URL;

/*!
    @method properties
    @abstract Returns a dictionary representation of the receiver.
    @discussion This method returns a dictionary representation of the
    NSHTTPCookie which can be saved and passed to
    <tt>-initWithProperties:</tt> or <tt>+cookieWithProperties:</tt>
    later to reconstitute an equivalent cookie.
    <p>See the NSHTTPCookie <tt>-initWithProperties:</tt> method for
    more information on the constraints imposed on the dictionary, and
    for descriptions of the supported keys and values.
    @result The dictionary representation of the receiver.
*/
- (NSDictionary *)properties;

/*!
    @method version
    @abstract Returns the version of the receiver.
    @discussion Version 0 maps to "old-style" Netscape cookies.
    Version 1 maps to RFC2965 cookies. There may be future versions.
    @result the version of the receiver.
*/
- (unsigned)version;

/*!
    @method name
    @abstract Returns the name of the receiver.
    @result the name of the receiver.
*/
- (NSString *)name;

/*!
    @method value
    @abstract Returns the value of the receiver.
    @result the value of the receiver.
*/
- (NSString *)value;

/*!
    @method expiresDate
    @abstract Returns the expires date of the receiver.
    @result the expires date of the receiver.
    @discussion The expires date is the date when the cookie should be
    deleted. The result will be nil if there is no specific expires
    date. This will be the case only for "session-only" cookies.
    @result The expires date of the receiver.
*/
- (NSDate *)expiresDate;

/*!
    @method isSessionOnly
    @abstract Returns whether the receiver is session-only.
    @result YES if this receiver should be discarded at the end of the
    session (regardless of expiration date), NO if receiver need not
    be discarded at the end of the session.
*/
- (BOOL)isSessionOnly;

/*!
    @method domain
    @abstract Returns the domain of the receiver.
    @discussion This value specifies URL domain to which the cookie
    should be sent. A domain with a leading dot means the cookie
    should be sent to subdomains as well, assuming certain other
    restrictions are valid. See RFC 2965 for more detail.
    @result The domain of the receiver.
*/
- (NSString *)domain;

/*!
    @method path
    @abstract Returns the path of the receiver.
    @discussion This value specifies the URL path under the cookie's
    domain for which this cookie should be sent. The cookie will also
    be sent for children of that path, so "/" is the most general.
    @result The path of the receiver.
*/
- (NSString *)path;

/*!
    @method isSecure
    @abstract Returns whether the receiver should be sent only over
    secure channels
    @result YES if this cookie should be sent only over secure channels,
    NO otherwise.
*/
- (BOOL)isSecure;

/*!
    @method comment
    @abstract Returns the comment of the receiver.
    @discussion This value specifies a string which is suitable for
    presentation to the user explaining the contents and purpose of this
    cookie. It may be nil.
    @result The comment of the receiver, or nil if the receiver has no
    comment.
*/
- (NSString *)comment;

/*!
    @method commentURL
    @abstract Returns the comment URL of the receiver.
    @discussion This value specifies a URL which is suitable for
    presentation to the user as a link for further information about
    this cookie. It may be nil.
    @result The comment URL of the receiver, or nil if the receiver
    has no comment URL.
*/
- (NSURL *)commentURL;

/*!
    @method portList
    @abstract Returns the list ports to which the receiver should be
    sent.
    @discussion This value specifies an NSArray of NSNumbers
    (containing integers) which specify the only ports to which this
    cookie should be sent.
    @result The list ports to which the receiver should be sent. The
    array may be nil, in which case this cookie can be sent to any
    port.
*/
- (NSArray *)portList;

@end

#endif
