//
//  SKCloudServiceSetupViewController.h
//  StoreKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <StoreKit/StoreKitDefines.h>

#if TARGET_OS_OSX
#import <AppKit/AppKit.h>
#else
#import <UIKit/UIKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

typedef NSString * SKCloudServiceSetupOptionsKey NS_STRING_ENUM;
typedef NSString * SKCloudServiceSetupAction NS_STRING_ENUM;
typedef NSString * SKCloudServiceSetupMessageIdentifier NS_STRING_ENUM;

@protocol SKCloudServiceSetupViewControllerDelegate;

/// View controller to allow user to setup iTunes Store account for cloud service, such as Apple Music subscription.
#if TARGET_OS_OSX
SK_EXTERN_CLASS API_AVAILABLE(ios(10.1)) API_UNAVAILABLE(macos) __TVOS_PROHIBITED @interface SKCloudServiceSetupViewController : NSViewController
#else
SK_EXTERN_CLASS API_AVAILABLE(ios(10.1)) API_UNAVAILABLE(macos) __TVOS_PROHIBITED @interface SKCloudServiceSetupViewController : UIViewController
#endif

/// Optional delegate.
@property (nonatomic, nullable, weak) id <SKCloudServiceSetupViewControllerDelegate> delegate API_AVAILABLE(ios(10.1)) API_UNAVAILABLE(macos) __TVOS_PROHIBITED;

/// Load cloud service setup view with the given options.
/// Block is invoked on the main thread when the load finishes.
- (void)loadWithOptions:(NSDictionary<SKCloudServiceSetupOptionsKey, id> *)options completionHandler:(nullable void (^)(BOOL result, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(10.1)) API_UNAVAILABLE(macos) __TVOS_PROHIBITED;

@end


@protocol SKCloudServiceSetupViewControllerDelegate <NSObject>

@optional

/// Sent when the view controller was dismissed.
- (void)cloudServiceSetupViewControllerDidDismiss:(SKCloudServiceSetupViewController *)cloudServiceSetupViewController API_AVAILABLE(ios(10.1)) API_UNAVAILABLE(macos) __TVOS_PROHIBITED;

@end


/// Action for setup entry point (of type SKCloudServiceSetupAction).
SK_EXTERN SKCloudServiceSetupOptionsKey const SKCloudServiceSetupOptionsActionKey NS_SWIFT_NAME(action) API_AVAILABLE(ios(10.1)) API_UNAVAILABLE(macos);

/// Identifier of the iTunes Store item the user is trying to access which requires cloud service setup (NSNumber).
SK_EXTERN SKCloudServiceSetupOptionsKey const SKCloudServiceSetupOptionsITunesItemIdentifierKey NS_SWIFT_NAME(iTunesItemIdentifier) API_AVAILABLE(ios(10.1)) API_UNAVAILABLE(macos);

/// iTunes Store affiliate token (NSString).
SK_EXTERN SKCloudServiceSetupOptionsKey const SKCloudServiceSetupOptionsAffiliateTokenKey NS_SWIFT_NAME(affiliateToken) API_AVAILABLE(ios(10.3)) API_UNAVAILABLE(macos);

/// iTunes Store affiliate campaign token (NSString).
SK_EXTERN SKCloudServiceSetupOptionsKey const SKCloudServiceSetupOptionsCampaignTokenKey NS_SWIFT_NAME(campaignToken) API_AVAILABLE(ios(10.3)) API_UNAVAILABLE(macos);

/// Identifier used to select the main message presented to the user for this setup view (SKCloudServiceSetupMessageIdentifier).
/// When missing, the setup view will be configured in a way that is equivalent to using SKCloudServiceSetupMessageIdentifierJoin.
SK_EXTERN SKCloudServiceSetupOptionsKey const SKCloudServiceSetupOptionsMessageIdentifierKey NS_SWIFT_NAME(messageIdentifier) API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos);

// Supported actions for setup entry point.

SK_EXTERN SKCloudServiceSetupAction const SKCloudServiceSetupActionSubscribe API_AVAILABLE(ios(10.1)) API_UNAVAILABLE(macos);

// Supported message identifiers.

SK_EXTERN SKCloudServiceSetupMessageIdentifier const SKCloudServiceSetupMessageIdentifierJoin API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos);
SK_EXTERN SKCloudServiceSetupMessageIdentifier const SKCloudServiceSetupMessageIdentifierConnect API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos);
SK_EXTERN SKCloudServiceSetupMessageIdentifier const SKCloudServiceSetupMessageIdentifierAddMusic API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos);
SK_EXTERN SKCloudServiceSetupMessageIdentifier const SKCloudServiceSetupMessageIdentifierPlayMusic API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos);

NS_ASSUME_NONNULL_END
