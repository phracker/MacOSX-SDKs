//
//  SKOverlayAppConfiguration.h
//  StoreKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>
#import <StoreKit/SKAdImpression.h>
#import <StoreKit/SKOverlay.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, SKOverlayPosition) {
    SKOverlayPositionBottom = 0,
    SKOverlayPositionBottomRaised = 1,
} API_AVAILABLE(ios(14.0), visionos(1.0)) API_UNAVAILABLE(macos, watchos) __TVOS_PROHIBITED NS_SWIFT_NAME(SKOverlay.Position);

SK_EXTERN_CLASS
API_AVAILABLE(ios(14.0), visionos(1.0)) API_UNAVAILABLE(macos, watchos) __TVOS_PROHIBITED
NS_SWIFT_NAME(SKOverlay.Configuration) NS_SWIFT_NONSENDABLE
@interface SKOverlayConfiguration : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

SK_EXTERN_CLASS
SK_CLASS_FINAL
API_AVAILABLE(ios(14.0), visionos(1.0)) API_UNAVAILABLE(macos, watchos) __TVOS_PROHIBITED
NS_SWIFT_NAME(SKOverlay.AppConfiguration) NS_SWIFT_NONSENDABLE
/// An overlay configuration that can be used to show any app from the App Store.
@interface SKOverlayAppConfiguration : SKOverlayConfiguration

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Creates a new app overlay configuration that will show an app from the App Store.
/// @param appIdentifier the app identifier of the app to show.
/// @param position the desired position of the overlay.
- (instancetype)initWithAppIdentifier:(NSString *)appIdentifier position:(SKOverlayPosition)position NS_SWIFT_NAME(init(appIdentifier:position:)) NS_DESIGNATED_INITIALIZER;

/// The identifier of the app that will be shown.
@property (nonatomic, retain) NSString *appIdentifier;

/// A token representing an App Analytics campaign.
@property (nonatomic, retain, nullable) NSString *campaignToken;

/// The provider token for the developer that created the app being presented.
@property (nonatomic, retain, nullable) NSString *providerToken;

/// An optional identifier for an app's custom product page.
@property (nonatomic, retain, nullable) NSString *customProductPageIdentifier API_AVAILABLE(ios(15.0), visionos(1.0)) API_UNAVAILABLE(macos, watchos) __TVOS_PROHIBITED;

/// An optional extra parameter for specifying the version of your app that will be shown to the user.
@property (nonatomic, retain, nullable) NSString *latestReleaseID API_AVAILABLE(ios(15.0), visionos(1.0)) API_UNAVAILABLE(macos, watchos) __TVOS_PROHIBITED;

/// The position an overlay will show at on screen.
@property (nonatomic) SKOverlayPosition position;

/// Allows the user to interactively dismiss an overlay.
@property (nonatomic) BOOL userDismissible;

- (void)setAdditionalValue:(nullable id)value forKey:(NSString *)key;

- (nullable id)additionalValueForKey:(NSString *)key NS_WARN_UNUSED_RESULT;

- (void)setAdImpression:(SKAdImpression *)impression API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, watchos, visionos) __TVOS_PROHIBITED;

@end

SK_EXTERN_CLASS
SK_CLASS_FINAL
API_AVAILABLE(ios(14.0), visionos(1.0)) API_UNAVAILABLE(macos, watchos) __TVOS_PROHIBITED
NS_SWIFT_NAME(SKOverlay.AppClipConfiguration) NS_SWIFT_NONSENDABLE
/// An overlay configuration that can be used to show an app clip's full app.
@interface SKOverlayAppClipConfiguration : SKOverlayConfiguration

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Creates a new app overlay configuration that will show an app clip's full app.
/// @param position the desired position of the overlay.
- (instancetype)initWithPosition:(SKOverlayPosition)position NS_SWIFT_NAME(init(position:)) NS_DESIGNATED_INITIALIZER;

/// A token representing an App Analytics campaign.
@property (nonatomic, retain, nullable) NSString *campaignToken;

/// The provider token for the developer that created the app being presented.
@property (nonatomic, retain, nullable) NSString *providerToken;

/// An optional identifier for a parent app's custom product page.
@property (nonatomic, retain, nullable) NSString *customProductPageIdentifier API_AVAILABLE(ios(15.0), visionos(1.0)) API_UNAVAILABLE(macos, watchos) __TVOS_PROHIBITED;

/// An optional extra parameter for specifying the version of your app that will be shown to the user.
@property (nonatomic, retain, nullable) NSString *latestReleaseID API_AVAILABLE(ios(15.0), visionos(1.0)) API_UNAVAILABLE(macos, watchos) __TVOS_PROHIBITED;

/// The position an overlay will show at on screen.
@property (nonatomic) SKOverlayPosition position;

- (void)setAdditionalValue:(nullable id)value forKey:(NSString *)key;

- (nullable id)additionalValueForKey:(NSString *)key NS_WARN_UNUSED_RESULT;

@end

NS_ASSUME_NONNULL_END
