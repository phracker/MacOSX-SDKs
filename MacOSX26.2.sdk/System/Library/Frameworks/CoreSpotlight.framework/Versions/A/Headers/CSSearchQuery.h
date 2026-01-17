//
//  CSSearchQuery.h
//  CoreSpotlight
//
//  Copyright © 2015–2022 Apple Inc. All rights reserved.
//

#import <CoreSpotlight/CSBase.h>

NS_ASSUME_NONNULL_BEGIN

CORESPOTLIGHT_EXPORT NSErrorDomain const CSSearchQueryErrorDomain API_AVAILABLE(macos(10.13), ios(10.0)) CS_TVOS_UNAVAILABLE;

typedef NS_ENUM(NSInteger, CSSearchQueryErrorCode) {
    CSSearchQueryErrorCodeUnknown = -2000,
    CSSearchQueryErrorCodeIndexUnreachable = -2001,
    CSSearchQueryErrorCodeInvalidQuery = -2002,
    CSSearchQueryErrorCodeCancelled = -2003,
} API_AVAILABLE(macos(10.13), ios(10.0)) CS_TVOS_UNAVAILABLE;

typedef NS_OPTIONS(NSUInteger, CSSearchQuerySourceOptions) {
    CSSearchQuerySourceOptionDefault = 0,
    CSSearchQuerySourceOptionAllowMail = 1 << 0,  // com.apple.corespotlight.search.allow.mail entitlement
} NS_SWIFT_NAME(CSSearchQueryContext.SourceOptions) API_AVAILABLE(macos(13));

@class CSSearchableItem;

API_AVAILABLE(macos(10.13), ios(10.0)) CS_TVOS_UNAVAILABLE
@interface CSSearchQueryContext : NSObject<NSSecureCoding, NSCopying>

@property (nonatomic, strong) NSArray<NSString *> *fetchAttributes;
@property (nonatomic, copy) NSArray<NSString *> *filterQueries;
@property (nullable, nonatomic, strong) NSString *keyboardLanguage;

@property (nonatomic, assign) CSSearchQuerySourceOptions sourceOptions API_AVAILABLE(macos(13));
@end

API_AVAILABLE(macos(10.13), ios(10.0)) CS_TVOS_UNAVAILABLE
@interface CSSearchQuery : NSObject

- (instancetype)init NS_UNAVAILABLE;

// queryString: The query string (e.g., 'contentType == "public.email-message" && subject != "Re:*"')
- (instancetype)initWithQueryString:(NSString * _Nonnull)queryString queryContext:(CSSearchQueryContext * _Nullable)queryContext NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(13.0), ios(16.0)) CS_TVOS_UNAVAILABLE;

// queryString: The query string (e.g., 'contentType == "public.email-message" && subject != "Re:*"')
// attributes: The attributes to be fetched for the searchable items
- (instancetype)initWithQueryString:(NSString *)queryString attributes:(NSArray<NSString *> * _Nullable)attributes NS_DEPRECATED(10_13, 13_0, 10_0, 16_0, "Use initWithQueryString:queryContext instead");

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
