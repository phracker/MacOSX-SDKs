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
}
API_DEPRECATED("Use MusicAuthorization.Status from MusicKit.", ios(9.3, 18.0), tvos(9.3, 18.0), watchos(7.0, 11.0), macos(11.0, 15.0), macCatalyst(13.0, 18.0))
API_UNAVAILABLE(visionos);

typedef NS_OPTIONS(NSUInteger, SKCloudServiceCapability) {
    SKCloudServiceCapabilityNone                           = 0,
    SKCloudServiceCapabilityMusicCatalogPlayback           = 1 << 0,
    SKCloudServiceCapabilityMusicCatalogSubscriptionEligible API_DEPRECATED("Use the canBecomeSubscriber property of MusicSubscription from MusicKit.", ios(10.1, 18.0), tvos(10.1, 18.0), watchos(7.0, 11.0), macos(11.0, 15.0), macCatalyst(13.0, 18.0)) = 1 << 1,
    SKCloudServiceCapabilityAddToCloudMusicLibrary         = 1 << 8,
}
API_DEPRECATED("Use MusicSubscription from MusicKit.", ios(9.3, 18.0), tvos(9.3, 18.0), watchos(7.0, 11.0), macos(11.0, 15.0), macCatalyst(13.0, 18.0))
API_UNAVAILABLE(visionos);

SK_EXTERN_CLASS
API_DEPRECATED("Use MusicKit.", ios(9.3, 18.0), tvos(9.3, 18.0), watchos(7.0, 11.0), macos(11.0, 15.0), macCatalyst(13.0, 18.0))
API_UNAVAILABLE(visionos)
@interface SKCloudServiceController : NSObject

+ (SKCloudServiceAuthorizationStatus)authorizationStatus API_DEPRECATED("Use MusicAuthorization.currentStatus from MusicKit.", ios(9.3, 18.0), tvos(9.3, 18.0), watchos(7.0, 11.0), macos(11.0, 15.0), macCatalyst(13.0, 18.0));
+ (void)requestAuthorization:(void (^) (SKCloudServiceAuthorizationStatus authorizationStatus))completionHandler API_DEPRECATED("Use MusicAuthorization.request() from MusicKit.", ios(9.3, 18.0), tvos(9.3, 18.0), watchos(7.0, 11.0), macos(11.0, 15.0), macCatalyst(13.0, 18.0));

- (void)requestCapabilitiesWithCompletionHandler:(void (^) (SKCloudServiceCapability capabilities, NSError * _Nullable error))completionHandler API_DEPRECATED("Use MusicSubscription.current from MusicKit.", ios(9.3, 18.0), tvos(9.3, 18.0), watchos(7.0, 11.0), macos(11.0, 15.0), macCatalyst(13.0, 18.0));

- (void)requestStorefrontCountryCodeWithCompletionHandler:(void (^) (NSString * _Nullable storefrontCountryCode, NSError * _Nullable error))completionHandler API_DEPRECATED("Use MusicDataRequest.currentCountryCode from MusicKit.", ios(11.0, 18.0), macos(11.0, 15.0), macCatalyst(13.1, 18.0), tvos(11.0, 18.0), watchos(7.0, 11.0));
- (void)requestStorefrontIdentifierWithCompletionHandler:(void (^) (NSString * _Nullable storefrontIdentifier, NSError * _Nullable error))completionHandler API_DEPRECATED("Use Storefront.current.id.", ios(9.3, 18.0), tvos(9.3, 18.0), watchos(7.0, 11.0), macos(11.0, 15.0), macCatalyst(13.0, 18.0));

- (void)requestUserTokenForDeveloperToken:(NSString *)developerToken completionHandler:(void (^) (NSString * _Nullable userToken, NSError * _Nullable error))completionHandler API_DEPRECATED("Use MusicKit.", ios(11.0, 18.0), tvos(11.0, 18.0), watchos(7.0, 11.0), macos(11.0, 15.0), macCatalyst(13.0, 18.0));
- (void)requestPersonalizationTokenForClientToken:(NSString *)clientToken withCompletionHandler:(void (^) (NSString * _Nullable personalizationToken, NSError * _Nullable error))completionHandler API_DEPRECATED_WITH_REPLACEMENT("requestUserTokenForDeveloperToken:completionHandler:", ios(10.3, 11.0), tvos(10.3, 11.0)) API_UNAVAILABLE(watchos, macos, macCatalyst);

@end

SK_EXTERN NSNotificationName const SKCloudServiceCapabilitiesDidChangeNotification API_DEPRECATED("Use MusicSubscription.subscriptionUpdates from MusicKit.", ios(9.3, 18.0), tvos(9.3, 18.0), watchos(7.0, 11.0), macos(11.0, 15.0), macCatalyst(13.0, 18.0)) API_UNAVAILABLE(visionos);
SK_EXTERN NSNotificationName const SKStorefrontCountryCodeDidChangeNotification API_DEPRECATED("Use Storefront.updates.", ios(11.0, 18.0), tvos(11.0, 18.0), watchos(7.0, 11.0), macos(11.0, 15.0), macCatalyst(13.0, 18.0)) API_UNAVAILABLE(visionos);
SK_EXTERN NSNotificationName const SKStorefrontIdentifierDidChangeNotification API_DEPRECATED("Use Storefront.updates.", ios(9.3, 18.0), tvos(9.3, 18.0), watchos(7.0, 11.0), macos(11.0, 15.0), macCatalyst(13.0, 18.0)) API_UNAVAILABLE(visionos);

NS_ASSUME_NONNULL_END
