/*	NSURLHandle.h
	Copyright (c) 1997-2005, Apple, Inc. All rights reserved.
*/
 
#import <Foundation/NSObject.h>

@class NSURLHandle, NSMutableArray, NSMutableData, NSData, NSURL;

	// HTTP Specific Property Keys
FOUNDATION_EXPORT NSString *NSHTTPPropertyStatusCodeKey;
FOUNDATION_EXPORT NSString *NSHTTPPropertyStatusReasonKey;
FOUNDATION_EXPORT NSString *NSHTTPPropertyServerHTTPVersionKey;
FOUNDATION_EXPORT NSString *NSHTTPPropertyRedirectionHeadersKey;
FOUNDATION_EXPORT NSString *NSHTTPPropertyErrorPageDataKey;
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
FOUNDATION_EXPORT NSString *NSHTTPPropertyHTTPProxy; // NSDictionary containing proxy information to use in place of proxy identified in SystemConfiguration.framework
													// To avoid any proxy use, pass an empty dictionary
#endif

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED

// FTP Specific Property Keys
	// All keys are optional.  The default configuration allows an
	// anonymous, passive-mode, one-off transfer of the specified URL.
FOUNDATION_EXPORT NSString *NSFTPPropertyUserLoginKey; // NSString - default "anonymous"
FOUNDATION_EXPORT NSString *NSFTPPropertyUserPasswordKey; // NSString - default "NSURLHandle@apple.com"
FOUNDATION_EXPORT NSString *NSFTPPropertyActiveTransferModeKey; // NSNumber BOOL - default NO (i.e. passive mode)
FOUNDATION_EXPORT NSString *NSFTPPropertyFileOffsetKey; // NSNumber - default 0

#endif

#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED

// NSDictionary containing proxy information to use in place of proxy identified in SystemConfiguration.framework
// To avoid any proxy use, pass an empty dictionary
FOUNDATION_EXPORT NSString *NSFTPPropertyFTPProxy;

#endif


typedef enum {
    NSURLHandleNotLoaded = 0,
    NSURLHandleLoadSucceeded,
    NSURLHandleLoadInProgress,
    NSURLHandleLoadFailed
} NSURLHandleStatus;

@protocol NSURLHandleClient
- (void)URLHandle:(NSURLHandle *)sender resourceDataDidBecomeAvailable:(NSData *)newBytes;
- (void)URLHandleResourceDidBeginLoading:(NSURLHandle *)sender;
- (void)URLHandleResourceDidFinishLoading:(NSURLHandle *)sender;
- (void)URLHandleResourceDidCancelLoading:(NSURLHandle *)sender;
- (void)URLHandle:(NSURLHandle *)sender resourceDidFailLoadingWithReason:(NSString *)reason;
@end

@interface NSURLHandle:NSObject
{
    NSMutableArray *_clients;
    id _data; 
    NSURLHandleStatus _status;
    int _reserved;
}

+ (void)registerURLHandleClass:(Class)anURLHandleSubclass; // Call this to register a new subclass of NSURLHandle
+ (Class)URLHandleClassForURL:(NSURL *)anURL;

- (NSURLHandleStatus)status;
- (NSString *)failureReason; // if status is NSURLHandleLoadFailed, then failureReason returns the reason for failure; otherwise, it returns nil

- (void)addClient:(id <NSURLHandleClient>)client;
- (void)removeClient:(id <NSURLHandleClient>)client;

- (void)loadInBackground;
- (void)cancelLoadInBackground;

- (NSData *)resourceData; // Blocks until all data is available
- (NSData *)availableResourceData;  // Immediately returns whatever data is available

#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (long long) expectedResourceDataSize;	// Length of all of the resource data (can be queried before all data has arrived; negative if unknown)
#endif

- (void)flushCachedData;

// As a background load progresses, subclasses should call these methods
- (void)backgroundLoadDidFailWithReason:(NSString *)reason; // Sends the failure message to clients
- (void)didLoadBytes:(NSData *)newBytes loadComplete:(BOOL)yorn;

// The primitives; these must be overridden by subclasses.
+ (BOOL)canInitWithURL:(NSURL *)anURL;
+ (NSURLHandle *)cachedHandleForURL:(NSURL *)anURL;
- initWithURL:(NSURL *)anURL cached:(BOOL)willCache;

- (id)propertyForKey:(NSString *)propertyKey;  // Must be overridden by subclasses
- (id)propertyForKeyIfAvailable:(NSString *)propertyKey;
- (BOOL)writeProperty:(id)propertyValue forKey:(NSString *)propertyKey;
- (BOOL)writeData:(NSData *)data; // Must be overridden by subclasses; returns success or failure

- (NSData *)loadInForeground;   // Called from resourceData, above.
- (void)beginLoadInBackground;  // Called from -loadInBackground, above.
- (void)endLoadInBackground;    // Called from -cancelLoadInBackground, above.

@end

