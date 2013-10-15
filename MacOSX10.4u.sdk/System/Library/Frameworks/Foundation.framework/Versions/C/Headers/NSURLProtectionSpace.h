/*	
    NSURLProtectionSpace.h
    Copyright (C) 2003-2005, Apple Computer, Inc. All rights reserved.    
    
    Public header file.
*/

// Note: To use the APIs described in these headers, you must perform
// a runtime check for Foundation-462.1 or later.
#import <AvailabilityMacros.h>
#if defined(MAC_OS_X_VERSION_10_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2)

#import <Foundation/NSObject.h>

@class NSString;

/*!
    @const NSURLProtectionSpaceHTTPProxy
    @abstract The proxy type for http proxies
*/
extern NSString * const NSURLProtectionSpaceHTTPProxy;

/*!
    @const NSURLProtectionSpaceHTTPSProxy
    @abstract The proxy type for https proxies
*/
extern NSString * const NSURLProtectionSpaceHTTPSProxy;

/*!
    @const NSURLProtectionSpaceFTPProxy
    @abstract The proxy type for ftp proxies
*/
extern NSString * const NSURLProtectionSpaceFTPProxy;

/*!
    @const NSURLProtectionSpaceSOCKProxy
    @abstract The proxy type for SOCKS proxies
*/
extern NSString * const NSURLProtectionSpaceSOCKSProxy;

/*!
    @const NSURLAuthenticationMethodDefault
    @abstract The default authentication method for a protocol
*/
extern NSString * const NSURLAuthenticationMethodDefault;

/*!
    @const NSURLAuthenticationMethodHTTPBasic
    @abstract HTTP basic authentication. Equivalent to
    NSURLAuthenticationMethodDefault for http.
*/
extern NSString * const NSURLAuthenticationMethodHTTPBasic;

/*!
    @const NSURLAuthenticationMethodHTTPDigest
    @abstract HTTP digest authentication.
*/
extern NSString * const NSURLAuthenticationMethodHTTPDigest;

/*!
    @const NSURLAuthenticationMethodHTMLForm
    @abstract HTML form authentication. Applies to any protocol.
*/
extern NSString * const NSURLAuthenticationMethodHTMLForm;


@class NSURLProtectionSpaceInternal;

/*!
    @class NSURLProtectionSpace
    @discussion This class represents a protection space requiring authentication.
*/

@interface NSURLProtectionSpace : NSObject <NSCopying>
{
@private
    NSURLProtectionSpaceInternal *_internal;
}

/*!
    @method initWithHost:port:protocol:realm:authenticationMethod:
    @abstract Initialize a protection space representing an origin server, or a realm on one
    @param host The hostname of the server
    @param port The port for the server
    @param protocol The sprotocol for this server - e.g. "http", "ftp", "https"
    @param realm A string indicating a protocol-specific subdivision
    of a single host. For http and https, this maps to the realm
    string in http authentication challenges. For many other protocols
    it is unused.
    @param authenticationMethod The authentication method to use to access this protection space -
    valid values include nil (default method), @"digest" and @"form".
    @result The initialized object.
*/
- (id)initWithHost:(NSString *)host port:(int)port protocol:(NSString *)protocol realm:(NSString *)realm authenticationMethod:(NSString *)authenticationMethod;

/*!
    @method initWithProxyHost:port:type:realm:authenticationMethod:
    @abstract Initialize a protection space representing a proxy server, or a realm on one
    @param host The hostname of the proxy server
    @param port The port for the proxy server
    @param type The type of proxy - e.g. "http", "ftp", "SOCKS"
    @param realm A string indicating a protocol-specific subdivision
    of a single host. For http and https, this maps to the realm
    string in http authentication challenges. For many other protocols
    it is unused.
    @param authenticationMethod The authentication method to use to access this protection space -
    valid values include nil (default method) and @"digest"
    @result The initialized object.
*/
- (id)initWithProxyHost:(NSString *)host port:(int)port type:(NSString *)type realm:(NSString *)realm  authenticationMethod:(NSString *)authenticationMethod;

/*!
    @method realm
    @abstract Get the authentication realm for which the protection space that
    needs authentication
    @discussion This is generally only available for http
    authentication, and may be nil otherwise.
    @result The realm string
*/
- (NSString *)realm;

/*!
    @method receivesCredentialSecurely
    @abstract Determine if the password for this protection space can be sent securely
    @result YES if a secure authentication method or protocol will be used, NO otherwise
*/
- (BOOL)receivesCredentialSecurely;

/*!
    @method isProxy
    @abstract Determine if this authenticating protection space is a proxy server
    @result YES if a proxy, NO otherwise
*/
- (BOOL)isProxy;

/*!
    @method host
    @abstract Get the proxy host if this is a proxy authentication, or the host from the URL.
    @result The host for this protection space.
*/
- (NSString *)host;

/*!
    @method port
    @abstract Get the proxy port if this is a proxy authentication, or the port from the URL.
    @result The port for this protection space, or 0 if not set.
*/
- (int)port;

/*!
    @method proxyType
    @abstract Get the type of this protection space, if a proxy
    @result The type string, or nil if not a proxy.
 */
- (NSString *)proxyType;

/*!
    @method protocol
    @abstract Get the protocol of this protection space, if not a proxy
    @result The type string, or nil if a proxy.
*/
- (NSString *)protocol;

/*!
    @method authenticationMethod
    @abstract Get the authentication method to be used for this protection space
    @result The authentication method
*/
- (NSString *)authenticationMethod;

@end

#endif
