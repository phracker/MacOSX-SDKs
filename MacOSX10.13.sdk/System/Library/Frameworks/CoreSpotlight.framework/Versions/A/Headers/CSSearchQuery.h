//
//  CSSearchQuery.h
//  CoreSpotlight
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CoreSpotlight/CSBase.h>

NS_ASSUME_NONNULL_BEGIN

CORESPOTLIGHT_EXPORT NSString * const CSSearchQueryErrorDomain CS_AVAILABLE(10_12, 10_0) CS_TVOS_UNAVAILABLE;

typedef NS_ENUM(NSInteger, CSSearchQueryErrorCode) {
    CSSearchQueryErrorCodeUnknown = -2000,
    CSSearchQueryErrorCodeIndexUnreachable = -2001,
    CSSearchQueryErrorCodeInvalidQuery = -2002,
    CSSearchQueryErrorCodeCancelled = -2003,
} CS_AVAILABLE(10_12, 10_0) CS_TVOS_UNAVAILABLE;

@class CSSearchableItem;

CS_CLASS_AVAILABLE(10_12, 10_0) CS_TVOS_UNAVAILABLE
@interface CSSearchQuery : NSObject

- (instancetype)init NS_UNAVAILABLE;

// queryString: The query string (e.g., 'contentType == "public.email-message" && subject != "Re:*"')
// attributes: The attributes to be fetched for the searchable items
- (instancetype)initWithQueryString:(NSString *)queryString attributes:(NSArray<NSString *> * _Nullable)attributes;

@property (readonly, getter=isCancelled) BOOL cancelled;

// The query will update the count before each foundItemsHandler invocation to reflect
// the number of items found so far; if foundItemsHandler is nil then the count will
// contain the total number of found items when the query completes.
@property (readonly) NSUInteger foundItemCount;

// The foundItemsHandler will be invoked repeatedly with a new batch of searchable items.
// The query serializes all the foundItemsHandler invocations.
@property (nullable, copy) void (^foundItemsHandler)(NSArray<CSSearchableItem *> *items);

@property (nullable, copy) void (^completionHandler)(NSError * _Nullable error);

// An array of NSFileProtectionComplete, NSFileProtectionCompleteUnlessOpen,
// or NSFileProtectionCompleteUntilFirstUserAuthentication.
// By default the data protection will be read from the "com.apple.developer.default-data-protection"
// entitlement if any or NSFileProtectionCompleteUntilFirstUserAuthentication will be used otherwise.
@property (copy) NSArray<NSFileProtectionType> *protectionClasses;

- (void)start;
- (void)cancel;

@end

NS_ASSUME_NONNULL_END
