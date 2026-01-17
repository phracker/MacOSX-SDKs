/*	NSURLHandle.h
	Copyright 1997-2001, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSURLHandle, NSMutableArray, NSMutableData, NSData, NSURL;

FOUNDATION_EXPORT NSString *NSHTTPPropertyStatusCodeKey;
FOUNDATION_EXPORT NSString *NSHTTPPropertyStatusReasonKey;
FOUNDATION_EXPORT NSString *NSHTTPPropertyServerHTTPVersionKey;
FOUNDATION_EXPORT NSString *NSHTTPPropertyRedirectionHeadersKey;
FOUNDATION_EXPORT NSString *NSHTTPPropertyErrorPageDataKey;

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

