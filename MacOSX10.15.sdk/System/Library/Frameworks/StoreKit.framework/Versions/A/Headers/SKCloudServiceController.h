//
//  SKCloudServiceController.h
//  StoreKit
//
//  Copyright © 2015-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, SKCloudServiceAuthorizationStatus) {
    SKCloudServiceAuthorizationStatusNotDetermined,
    SKCloudServiceAuthorizationStatusDenied,
    SKCloudServiceAuthorizationStatusRestricted,
    SKCloudServiceAuthorizationStatusAuthorized,
} API_AVAILABLE(ios(9.3)) API_UNAVAILABLE(macos);

typedef NS_OPTIONS(NSUInteger, SKCloudServiceCapability) {
    SKCloudServiceCapabilityNone                           = 0,
    SKCloudServiceCapabilityMusicCatalogPlayback           = 1 << 0,
    SKCloudServiceCapabilityMusicCatalogSubscriptionEligible API_AVAILABLE(ios(10.1)) API_UNAVAILABLE(macos)  = 1 << 1,
    SKCloudServiceCapabilityAddToCloudMusicLibrary         = 1 << 8,
} API_AVAILABLE(ios(9.3)) API_UNAVAILABLE(macos);

SK_EXTERN_CLASS API_AVAILABLE(ios(9.3)) API_UNAVAILABLE(macos) @interface SKCloudServiceController : NSObject

+ (SKCloudServiceAuthorizationStatus)authorizationStatus API_AVAILABLE(ios(9.3)) API_UNAVAILABLE(macos);
+ (void)requestAuthorization:(void(^)(SKCloudServiceAuthorizationStatus status))handler API_AVAILABLE(ios(9.3)) API_UNAVAILABLE(macos);

- (void)requestCapabilitiesWithCompletionHandler:(void(^)(SKCloudServiceCapability capabilities, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(9.3)) API_UNAVAILABLE(macos);

- (void)requestStorefrontCountryCodeWithCompletionHandler:(void(^)(NSString * _Nullable storefrontCountryCode, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos);
- (void)requestStorefrontIdentifierWithCompletionHandler:(void(^)(NSString * _Nullable storefrontIdentifier, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(9.3)) API_UNAVAILABLE(macos);

- (void)requestUserTokenForDeveloperToken:(NSString *)developerToken completionHandler:(void(^)(NSString * _Nullable userToken, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos);
- (void)requestPersonalizationTokenForClientToken:(NSString *)clientToken withCompletionHandler:(void(^)(NSString * _Nullable personalizationToken, NSError * _Nullable error))completionHandler API_DEPRECATED_WITH_REPLACEMENT("requestUserTokenForDeveloperToken:completionHandler:", ios(10.3, 11.0)) API_UNAVAILABLE(macos, macCatalyst);

@end

SK_EXTERN NSNotificationName const SKCloudServiceCapabilitiesDidChangeNotification API_AVAILABLE(ios(9.3)) API_UNAVAILABLE(macos);
SK_EXTERN NSNotificationName const SKStorefrontCountryCodeDidChangeNotification API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos);
SK_EXTERN NSNotificationName const SKStorefrontIdentifierDidChangeNotification API_AVAILABLE(ios(9.3)) API_UNAVAILABLE(macos);

NS_ASSUME_NONNULL_END
