/*	
    NSHTTPCookieStorage.h
    Copyright (c) 2003-2014, Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/NSObject.h>

@class NSArray;
@class NSHTTPCookie;
@class NSURL;
@class NSDate;
@class NSURLSessionTask;

/*!
    @enum NSHTTPCookieAcceptPolicy
    @abstract Values for the different cookie accept policies
    @constant NSHTTPCookieAcceptPolicyAlways Accept all cookies
    @constant NSHTTPCookieAcceptPolicyNever Reject all cookies
    @constant NSHTTPCookieAcceptPolicyOnlyFromMainDocumentDomain Accept cookies
    only from the main document domain
*/
typedef NS_ENUM(NSUInteger, NSHTTPCookieAcceptPolicy) {
    NSHTTPCookieAcceptPolicyAlways,
    NSHTTPCookieAcceptPolicyNever,
    NSHTTPCookieAcceptPolicyOnlyFromMainDocumentDomain
};


@class NSHTTPCookieStorageInternal;

/*!
    @class NSHTTPCookieStorage 
    @discussion NSHTTPCookieStorage implements a singleton object (shared
    instance) which manages the shared cookie store.  It has methods
    to allow clients to set and remove cookies, and get the current
    set of cookies.  It also has convenience methods to parse and
    generate cookie-related HTTP header fields.
*/

@interface NSHTTPCookieStorage : NSObject
{
    @private
    NSHTTPCookieStorageInternal *_internal;
}

/*!
    @method sharedHTTPCookieStorage
    @abstract Get the shared cookie storage in the default location.
    @result The shared cookie storage
*/
+ (NSHTTPCookieStorage *)sharedHTTPCookieStorage;

/*!
    @method cookies
    @abstract Get all the cookies
    @result An NSArray of NSHTTPCookies
*/
@property (readonly, copy) NSArray *cookies;

/*!
    @method setCookie:
    @abstract Set a cookie
    @discussion The cookie will override an existing cookie with the
    same name, domain and path, if any.
*/
- (void)setCookie:(NSHTTPCookie *)cookie;

/*!
    @method deleteCookie:
    @abstract Delete the specified cookie
*/
- (void)deleteCookie:(NSHTTPCookie *)cookie;

/*!
 @method removeCookiesSince:
 @abstract Delete all cookies from the cookie storage since the provided date.
 */
- (void)removeCookiesSinceDate:(NSDate *)date NS_AVAILABLE(10_10, 8_0);

/*!
    @method cookiesForURL:
    @abstract Returns an array of cookies to send to the given URL.
    @param URL The URL for which to get cookies.
    @result an NSArray of NSHTTPCookie objects.
    @discussion The cookie manager examines the cookies it stores and
    includes those which should be sent to the given URL. You can use
    <tt>+[NSCookie requestHeaderFieldsWithCookies:]</tt> to turn this array
    into a set of header fields to add to a request.
*/
- (NSArray *)cookiesForURL:(NSURL *)URL;

/*!
    @method setCookies:forURL:mainDocumentURL:
    @abstract Adds an array cookies to the cookie store, following the
    cookie accept policy.
    @param cookies The cookies to set.
    @param URL The URL from which the cookies were sent.
    @param mainDocumentURL The main document URL to be used as a base for the "same
    domain as main document" policy.
    @discussion For mainDocumentURL, the caller should pass the URL for
    an appropriate main document, if known. For example, when loading
    a web page, the URL of the main html document for the top-level
    frame should be passed. To save cookies based on a set of response
    headers, you can use <tt>+[NSCookie
    cookiesWithResponseHeaderFields:forURL:]</tt> on a header field
    dictionary and then use this method to store the resulting cookies
    in accordance with policy settings.
*/
- (void)setCookies:(NSArray *)cookies forURL:(NSURL *)URL mainDocumentURL:(NSURL *)mainDocumentURL;

/*!
    @method cookieAcceptPolicy
    @abstract The cookie accept policy preference of the
    receiver.
*/
@property NSHTTPCookieAcceptPolicy cookieAcceptPolicy;

/*!
  @method sortedCookiesUsingDescriptors:
  @abstract Returns an array of all cookies in the store, sorted according to the key value and sorting direction of the NSSortDescriptors specified in the parameter.
  @param sortOrder an array of NSSortDescriptors which represent the preferred sort order of the resulting array.
  @discussion proper sorting of cookies may require extensive string conversion, which can be avoided by allowing the system to perform the sorting.  This API is to be preferred over the more generic -[NSHTTPCookieStorage cookies] API, if sorting is going to be performed.
*/
- (NSArray*)sortedCookiesUsingDescriptors:(NSArray*) sortOrder NS_AVAILABLE(10_7, 5_0);

@end

@interface NSHTTPCookieStorage (NSURLSessionTaskAdditions)
- (void)storeCookies:(NSArray *)cookies forTask:(NSURLSessionTask *)task NS_AVAILABLE(10_10, 8_0);
- (void)getCookiesForTask:(NSURLSessionTask *)task completionHandler:(void (^) (NSArray *cookies))completionHandler NS_AVAILABLE(10_10, 8_0);
@end

/*!
    @const NSHTTPCookieManagerAcceptPolicyChangedNotification
    @discussion Name of notification that should be posted to the
    distributed notification center whenever the accept cookies
    preference is changed
*/
FOUNDATION_EXPORT NSString * const NSHTTPCookieManagerAcceptPolicyChangedNotification;

/*!
    @const NSHTTPCookieManagerCookiesChangedNotification
    @abstract Notification sent when the set of cookies changes
*/
FOUNDATION_EXPORT NSString * const NSHTTPCookieManagerCookiesChangedNotification;

