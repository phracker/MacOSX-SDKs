//
//  SKCloudServiceController.h
//  StoreKit
//
//  Copyright © 2015-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, SKCloudServiceAuthorizationStatus) {
    SKCloudServiceAuthorizationStatusNotDetermined,
    SKCloudServiceAuthorizationStatusDenied,
    SKCloudServiceAuthorizationStatusRestricted,
    SKCloudServiceAuthorizationStatusAuthorized,
} API_AVAILABLE(ios(9.3), tvos(9.3), watchos(7.0), macos(11.0), macCatalyst(13.0));

typedef NS_OPTIONS(NSUInteger, SKCloudServiceCapability) {
    SKCloudServiceCapabilityNone                           = 0,
    SKCloudServiceCapabilityMusicCatalogPlayback           = 1 << 0,
    SKCloudServiceCapabilityMusicCatalogSubscriptionEligible API_AVAILABLE(ios(10.1), tvos(10.1), watchos(7.0), macos(11.0), macCatalyst(13.0)) = 1 << 1,
    SKCloudServiceCapabilityAddToCloudMusicLibrary         = 1 << 8,
} API_AVAILABLE(ios(9.3), tvos(9.3), watchos(7.0), macos(11.0), macCatalyst(13.0));

SK_EXTERN_CLASS API_AVAILABLE(ios(9.3), tvos(9.3), watchos(7.0), macos(11.0), macCatalyst(13.0))
@interface SKCloudServiceController : NSObject

+ (SKCloudServiceAuthorizationStatus)authorizationStatus API_AVAILABLE(ios(9.3), tvos(9.3), watchos(7.0), macos(11.0), macCatalyst(13.0));
+ (void)requestAuthorization:(void (^) (SKCloudServiceAuthorizationStatus authorizationStatus))completionHandler API_AVAILABLE(ios(9.3), tvos(9.3), watchos(7.0), macos(11.0), macCatalyst(13.0));

- (void)requestCapabilitiesWithCompletionHandler:(void (^) (SKCloudServiceCapability capabilities, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(9.3), tvos(9.3), watchos(7.0), macos(11.0), macCatalyst(13.0));

- (void)requestStorefrontCountryCodeWithCompletionHandler:(void (^) (NSString * _Nullable storefrontCountryCode, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0));
- (void)requestStorefrontIdentifierWithCompletionHandler:(void (^) (NSString * _Nullable storefrontIdentifier, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(9.3), tvos(9.3), watchos(7.0), macos(11.0), macCatalyst(13.0));

- (void)requestUserTokenForDeveloperToken:(NSString *)developerToken completionHandler:(void (^) (NSString * _Nullable userToken, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0), tvos(11.0), watchos(7.0), macos(11.0), macCatalyst(13.0));
- (void)requestPersonalizationTokenForClientToken:(NSString *)clientToken withCompletionHandler:(void (^) (NSString * _Nullable personalizationToken, NSError * _Nullable error))completionHandler API_DEPRECATED_WITH_REPLACEMENT("requestUserTokenForDeveloperToken:completionHandler:", ios(10.3, 11.0), tvos(10.3, 11.0)) API_UNAVAILABLE(watchos, macos, macCatalyst);

@end

SK_EXTERN NSNotificationName const SKCloudServiceCapabilitiesDidChangeNotification API_AVAILABLE(ios(9.3), tvos(9.3), watchos(7.0), macos(11.0), macCatalyst(13.0));
SK_EXTERN NSNotificationName const SKStorefrontCountryCodeDidChangeNotification API_AVAILABLE(ios(11.0), tvos(11.0), watchos(7.0), macos(11.0), macCatalyst(13.0));
SK_EXTERN NSNotificationName const SKStorefrontIdentifierDidChangeNotification API_AVAILABLE(ios(9.3), tvos(9.3), watchos(7.0), macos(11.0), macCatalyst(13.0));

NS_ASSUME_NONNULL_END
