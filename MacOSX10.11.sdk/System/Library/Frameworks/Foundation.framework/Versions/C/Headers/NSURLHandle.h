/*	NSURLHandle.h
	Copyright (c) 1997-2015, Apple Inc. All rights reserved.
*/
 
#import <Foundation/NSObject.h>

/* NSURLHandle has been deprecated; please use NSURLConnection instead. */

@class NSURLHandle, NSMutableArray, NSMutableData, NSData, NSURL;

	// HTTP Specific Property Keys
FOUNDATION_EXPORT NSString *NSHTTPPropertyStatusCodeKey NS_DEPRECATED(10_0, 10_4, NA, NA);
FOUNDATION_EXPORT NSString *NSHTTPPropertyStatusReasonKey NS_DEPRECATED(10_0, 10_4, NA, NA);
FOUNDATION_EXPORT NSString *NSHTTPPropertyServerHTTPVersionKey NS_DEPRECATED(10_0, 10_4, NA, NA);
FOUNDATION_EXPORT NSString *NSHTTPPropertyRedirectionHeadersKey NS_DEPRECATED(10_0, 10_4, NA, NA);
FOUNDATION_EXPORT NSString *NSHTTPPropertyErrorPageDataKey NS_DEPRECATED(10_0, 10_4, NA, NA);
FOUNDATION_EXPORT NSString *NSHTTPPropertyHTTPProxy NS_DEPRECATED(10_2, 10_4, NA, NA); // NSDictionary containing proxy information to use in place of proxy identified in SystemConfiguration.framework
													// To avoid any proxy use, pass an empty dictionary

// FTP Specific Property Keys
	// All keys are optional.  The default configuration allows an
	// anonymous, passive-mode, one-off transfer of the specified URL.
FOUNDATION_EXPORT NSString *NSFTPPropertyUserLoginKey NS_DEPRECATED(10_2, 10_4, NA, NA); // NSString - default "anonymous"
FOUNDATION_EXPORT NSString *NSFTPPropertyUserPasswordKey NS_DEPRECATED(10_2, 10_4, NA, NA); // NSString - default "NSURLHandle@apple.com"
FOUNDATION_EXPORT NSString *NSFTPPropertyActiveTransferModeKey NS_DEPRECATED(10_2, 10_4, NA, NA); // NSNumber BOOL - default NO (i.e. passive mode)
FOUNDATION_EXPORT NSString *NSFTPPropertyFileOffsetKey NS_DEPRECATED(10_2, 10_4, NA, NA); // NSNumber - default 0

// NSDictionary containing proxy information to use in place of proxy identified in SystemConfiguration.framework
// To avoid any proxy use, pass an empty dictionary
FOUNDATION_EXPORT NSString *NSFTPPropertyFTPProxy NS_DEPRECATED(10_3, 10_4, NA, NA);



typedef NS_ENUM(NSUInteger, NSURLHandleStatus) {
    NSURLHandleNotLoaded = 0,
    NSURLHandleLoadSucceeded,
    NSURLHandleLoadInProgress,
    NSURLHandleLoadFailed
};

@protocol NSURLHandleClient
- (void)URLHandle:(NSURLHandle *)sender resourceDataDidBecomeAvailable:(NSData *)newBytes NS_DEPRECATED(10_0, 10_4, NA, NA);
- (void)URLHandleResourceDidBeginLoading:(NSURLHandle *)sender NS_DEPRECATED(10_0, 10_4, NA, NA);
- (void)URLHandleResourceDidFinishLoading:(NSURLHandle *)sender NS_DEPRECATED(10_0, 10_4, NA, NA);
- (void)URLHandleResourceDidCancelLoading:(NSURLHandle *)sender NS_DEPRECATED(10_0, 10_4, NA, NA);
- (void)URLHandle:(NSURLHandle *)sender resourceDidFailLoadingWithReason:(NSString *)reason NS_DEPRECATED(10_0, 10_4, NA, NA);
@end

@interface NSURLHandle:NSObject
{
    NSMutableArray *_clients;
    id _data; 
    NSURLHandleStatus _status;
    NSInteger _reserved;
}

+ (void)registerURLHandleClass:(Class)anURLHandleSubclass NS_DEPRECATED(10_0, 10_4, NA, NA); // Call this to register a new subclass of NSURLHandle
+ (Class)URLHandleClassForURL:(NSURL *)anURL NS_DEPRECATED(10_0, 10_4, NA, NA);

- (NSURLHandleStatus)status NS_DEPRECATED(10_0, 10_4, NA, NA);
- (NSString *)failureReason NS_DEPRECATED(10_0, 10_4, NA, NA); // if status is NSURLHandleLoadFailed, then failureReason returns the reason for failure; otherwise, it returns nil

- (void)addClient:(id <NSURLHandleClient>)client NS_DEPRECATED(10_0, 10_4, NA, NA);
- (void)removeClient:(id <NSURLHandleClient>)client NS_DEPRECATED(10_0, 10_4, NA, NA);

- (void)loadInBackground NS_DEPRECATED(10_0, 10_4, NA, NA);
- (void)cancelLoadInBackground NS_DEPRECATED(10_0, 10_4, NA, NA);

- (NSData *)resourceData NS_DEPRECATED(10_0, 10_4, NA, NA); // Blocks until all data is available
- (NSData *)availableResourceData NS_DEPRECATED(10_0, 10_4, NA, NA);  // Immediately returns whatever data is available

- (long long) expectedResourceDataSize NS_DEPRECATED(10_3, 10_4, NA, NA);	// Length of all of the resource data (can be queried before all data has arrived; negative if unknown)

- (void)flushCachedData NS_DEPRECATED(10_0, 10_4, NA, NA);

// As a background load progresses, subclasses should call these methods
- (void)backgroundLoadDidFailWithReason:(NSString *)reason NS_DEPRECATED(10_0, 10_4, NA, NA); // Sends the failure message to clients
- (void)didLoadBytes:(NSData *)newBytes loadComplete:(BOOL)yorn NS_DEPRECATED(10_0, 10_4, NA, NA);

// The primitives; these must be overridden by subclasses.
+ (BOOL)canInitWithURL:(NSURL *)anURL NS_DEPRECATED(10_0, 10_4, NA, NA);
+ (NSURLHandle *)cachedHandleForURL:(NSURL *)anURL NS_DEPRECATED(10_0, 10_4, NA, NA);
- initWithURL:(NSURL *)anURL cached:(BOOL)willCache NS_DEPRECATED(10_0, 10_4, NA, NA);

- (id)propertyForKey:(NSString *)propertyKey NS_DEPRECATED(10_0, 10_4, NA, NA);  // Must be overridden by subclasses
- (id)propertyForKeyIfAvailable:(NSString *)propertyKey NS_DEPRECATED(10_0, 10_4, NA, NA);
- (BOOL)writeProperty:(id)propertyValue forKey:(NSString *)propertyKey NS_DEPRECATED(10_0, 10_4, NA, NA);
- (BOOL)writeData:(NSData *)data NS_DEPRECATED(10_0, 10_4, NA, NA); // Must be overridden by subclasses; returns success or failure

- (NSData *)loadInForeground NS_DEPRECATED(10_0, 10_4, NA, NA);   // Called from resourceData, above.
- (void)beginLoadInBackground NS_DEPRECATED(10_0, 10_4, NA, NA);  // Called from -loadInBackground, above.
- (void)endLoadInBackground NS_DEPRECATED(10_0, 10_4, NA, NA);    // Called from -cancelLoadInBackground, above.

@end

