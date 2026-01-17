/*	NSURL.h
	Copyright (c) 1997-2007, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSURLHandle.h>
#import <Foundation/NSString.h>

@class NSNumber, NSData, NSDictionary;

// As more schemes are used and understood, strong constants for them will be added here
FOUNDATION_EXPORT NSString *NSURLFileScheme;

@interface NSURL: NSObject <NSCoding, NSCopying, NSURLHandleClient>
{
    NSString *_urlString;
    NSURL *_baseURL;
    void *_clients;
    __strong void *_reserved;
}
        
// Convenience initializers
- initWithScheme:(NSString *)scheme host:(NSString *)host path:(NSString *)path;
- initFileURLWithPath:(NSString *)path isDirectory:(BOOL)isDir AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- initFileURLWithPath:(NSString *)path;  // Better to use initFileURLWithPath:isDirectory: if you know if the path is a file vs directory, as it saves an i/o.

+ (id)fileURLWithPath:(NSString *)path isDirectory:(BOOL) isDir AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
+ (id)fileURLWithPath:(NSString *)path; // Better to use fileURLWithPath:isDirectory: if you know if the path is a file vs directory, as it saves an i/o.

// These methods expect their string arguments to contain any percent escape codes that are necessary
- initWithString:(NSString *)URLString;
- initWithString:(NSString *)URLString relativeToURL:(NSURL *)baseURL; // It is an error for URLString to be nil
+ (id)URLWithString:(NSString *)URLString;
+ (id)URLWithString:(NSString *)URLString relativeToURL:(NSURL *)baseURL;

- (NSString *)absoluteString;
- (NSString *)relativeString; // The relative portion of a URL.  If baseURL is nil, or if the receiver is itself absolute, this is the same as absoluteString
- (NSURL *)baseURL; // may be nil.
- (NSURL *)absoluteURL; // if the receiver is itself absolute, this will return self.

// Any URL is composed of these two basic pieces.  The full URL would be the concatenation of [myURL scheme], ':', [myURL resourceSpecifier]
- (NSString *)scheme;
- (NSString *)resourceSpecifier;

/* If the URL conforms to rfc 1808 (the most common form of URL), the following accessors will return the various components; otherwise they return nil.  The litmus test for conformance is as recommended in RFC 1808 - whether the first two characters of resourceSpecifier is @"//".  In all cases, they return the component's value after resolving the receiver against its base URL. */
- (NSString *)host;
- (NSNumber *)port;
- (NSString *)user;
- (NSString *)password;
- (NSString *)path;
- (NSString *)fragment;
- (NSString *)parameterString;
- (NSString *)query;
- (NSString *)relativePath; // The same as path if baseURL is nil

- (BOOL)isFileURL; // Whether the scheme is file:; if [myURL isFileURL] is YES, then [myURL path] is suitable for input into NSFileManager or NSPathUtilities.

- (NSURL *)standardizedURL;
@end

#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED
@interface NSString (NSURLUtilities)

/* Adds all percent escapes necessary to convert the receiver in to a legal URL string.  Uses the given encoding to determine the correct percent escapes (returning nil if the given encoding cannot encode a particular character).  See CFURLCreateStringByAddingPercentEscapes in CFURL.h for more complex transformations */
- (NSString *)stringByAddingPercentEscapesUsingEncoding:(NSStringEncoding)enc;

/* Replaces all percent escapes with the matching characters as determined by the given encoding.  Returns nil if the transformation is not possible (i.e. the percent escapes give a byte sequence not legal in the given encoding).  See CFURLCreateStringByReplacingPercentEscapes in CFURL.h for more complex transformations */
- (NSString *)stringByReplacingPercentEscapesUsingEncoding:(NSStringEncoding)enc;

@end
#endif

// Client informal protocol for use with the deprecated loadResourceDataNotifyingClient: below.  
@interface NSObject(NSURLClient)
- (void)URL:(NSURL *)sender resourceDataDidBecomeAvailable:(NSData *)newBytes DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)URLResourceDidFinishLoading:(NSURL *)sender DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)URLResourceDidCancelLoading:(NSURL *)sender DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)URL:(NSURL *)sender resourceDidFailLoadingWithReason:(NSString *)reason DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
@end

//  This entire protocol is deprecated; use NSURLConnection instead.
@interface NSURL (NSURLLoading)
- (NSData *)resourceDataUsingCache:(BOOL)shouldUseCache DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER; // Blocks to load the data if necessary.  If shouldUseCache is YES, then if an equivalent URL has already been loaded and cached, its resource data will be returned immediately.  If shouldUseCache is NO, a new load will be started
- (void)loadResourceDataNotifyingClient:(id)client usingCache:(BOOL)shouldUseCache DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER; // Starts an asynchronous load of the data, registering delegate to receive notification.  Only one such background load can proceed at a time.
- (id)propertyForKey:(NSString *)propertyKey DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;

    // These attempt to write the given arguments for the resource specified by the URL; they return success or failure
- (BOOL)setResourceData:(NSData *)data DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (BOOL)setProperty:(id)property forKey:(NSString *)propertyKey DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSURLHandle *)URLHandleUsingCache:(BOOL)shouldUseCache DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER; // Sophisticated clients will want to ask for this, then message the handle directly.  If shouldUseCache is NO, a newly instantiated handle is returned, even if an equivalent URL has been loaded

@end

