/*	NSURLHandle.h
	Copyright (c) 1997-2007, Apple Inc. All rights reserved.
*/
 
#import <Foundation/NSObject.h>

/* NSURLHandle has been deprecated; please use NSURLConnection instead. */

@class NSURLHandle, NSMutableArray, NSMutableData, NSData, NSURL;

	// HTTP Specific Property Keys
FOUNDATION_EXPORT NSString *NSHTTPPropertyStatusCodeKey DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
FOUNDATION_EXPORT NSString *NSHTTPPropertyStatusReasonKey DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
FOUNDATION_EXPORT NSString *NSHTTPPropertyServerHTTPVersionKey DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
FOUNDATION_EXPORT NSString *NSHTTPPropertyRedirectionHeadersKey DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
FOUNDATION_EXPORT NSString *NSHTTPPropertyErrorPageDataKey DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
FOUNDATION_EXPORT NSString *NSHTTPPropertyHTTPProxy DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER; // NSDictionary containing proxy information to use in place of proxy identified in SystemConfiguration.framework
													// To avoid any proxy use, pass an empty dictionary
#endif

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED

// FTP Specific Property Keys
	// All keys are optional.  The default configuration allows an
	// anonymous, passive-mode, one-off transfer of the specified URL.
FOUNDATION_EXPORT NSString *NSFTPPropertyUserLoginKey DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER; // NSString - default "anonymous"
FOUNDATION_EXPORT NSString *NSFTPPropertyUserPasswordKey DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER; // NSString - default "NSURLHandle@apple.com"
FOUNDATION_EXPORT NSString *NSFTPPropertyActiveTransferModeKey DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER; // NSNumber BOOL - default NO (i.e. passive mode)
FOUNDATION_EXPORT NSString *NSFTPPropertyFileOffsetKey DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER; // NSNumber - default 0

#endif

#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED

// NSDictionary containing proxy information to use in place of proxy identified in SystemConfiguration.framework
// To avoid any proxy use, pass an empty dictionary
FOUNDATION_EXPORT NSString *NSFTPPropertyFTPProxy DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;

#endif


enum {
    NSURLHandleNotLoaded = 0,
    NSURLHandleLoadSucceeded,
    NSURLHandleLoadInProgress,
    NSURLHandleLoadFailed
};
typedef NSUInteger NSURLHandleStatus;

@protocol NSURLHandleClient
- (void)URLHandle:(NSURLHandle *)sender resourceDataDidBecomeAvailable:(NSData *)newBytes DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)URLHandleResourceDidBeginLoading:(NSURLHandle *)sender DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)URLHandleResourceDidFinishLoading:(NSURLHandle *)sender DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)URLHandleResourceDidCancelLoading:(NSURLHandle *)sender DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)URLHandle:(NSURLHandle *)sender resourceDidFailLoadingWithReason:(NSString *)reason DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
@end

@interface NSURLHandle:NSObject
{
    NSMutableArray *_clients;
    id _data; 
    NSURLHandleStatus _status;
    NSInteger _reserved;
}

+ (void)registerURLHandleClass:(Class)anURLHandleSubclass DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER; // Call this to register a new subclass of NSURLHandle
+ (Class)URLHandleClassForURL:(NSURL *)anURL DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSURLHandleStatus)status DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (NSString *)failureReason DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER; // if status is NSURLHandleLoadFailed, then failureReason returns the reason for failure; otherwise, it returns nil

- (void)addClient:(id <NSURLHandleClient>)client DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)removeClient:(id <NSURLHandleClient>)client DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;

- (void)loadInBackground DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)cancelLoadInBackground DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;

- (NSData *)resourceData DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER; // Blocks until all data is available
- (NSData *)availableResourceData DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;  // Immediately returns whatever data is available

#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (long long) expectedResourceDataSize DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;	// Length of all of the resource data (can be queried before all data has arrived; negative if unknown)
#endif

- (void)flushCachedData DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;

// As a background load progresses, subclasses should call these methods
- (void)backgroundLoadDidFailWithReason:(NSString *)reason DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER; // Sends the failure message to clients
- (void)didLoadBytes:(NSData *)newBytes loadComplete:(BOOL)yorn DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;

// The primitives; these must be overridden by subclasses.
+ (BOOL)canInitWithURL:(NSURL *)anURL DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
+ (NSURLHandle *)cachedHandleForURL:(NSURL *)anURL DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- initWithURL:(NSURL *)anURL cached:(BOOL)willCache DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;

- (id)propertyForKey:(NSString *)propertyKey DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;  // Must be overridden by subclasses
- (id)propertyForKeyIfAvailable:(NSString *)propertyKey DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (BOOL)writeProperty:(id)propertyValue forKey:(NSString *)propertyKey DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (BOOL)writeData:(NSData *)data DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER; // Must be overridden by subclasses; returns success or failure

- (NSData *)loadInForeground DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;   // Called from resourceData, above.
- (void)beginLoadInBackground DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;  // Called from -loadInBackground, above.
- (void)endLoadInBackground DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;    // Called from -cancelLoadInBackground, above.

@end

