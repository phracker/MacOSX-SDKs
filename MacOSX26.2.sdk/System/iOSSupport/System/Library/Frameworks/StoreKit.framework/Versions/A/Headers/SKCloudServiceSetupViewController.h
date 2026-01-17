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
SK_EXTERN_CLASS
API_DEPRECATED("Use the musicSubscriptionOffer(isPresented:options:onLoadCompletion:) SwiftUI View Modifier from MusicKit.", ios(10.1, 18.0))
API_UNAVAILABLE(visionos)
API_UNAVAILABLE(macos)
__TVOS_PROHIBITED
#if TARGET_OS_OSX
@interface SKCloudServiceSetupViewController : NSViewController
#else
@interface SKCloudServiceSetupViewController : UIViewController
#endif

/// Optional delegate.
@property (nonatomic, nullable, weak) id <SKCloudServiceSetupViewControllerDelegate> delegate;

/// Load cloud service setup view with the given options.
/// Block is invoked on the main thread when the load finishes.
- (void)loadWithOptions:(NSDictionary<SKCloudServiceSetupOptionsKey, id> *)options completionHandler:(nullable void (^)(BOOL result, NSError * _Nullable error))completionHandler;

@end


API_DEPRECATED("Use the musicSubscriptionOffer(isPresented:options:onLoadCompletion:) SwiftUI View Modifier from MusicKit.", ios(10.1, 18.0))
API_UNAVAILABLE(visionos)
API_UNAVAILABLE(macos)
__TVOS_PROHIBITED
@protocol SKCloudServiceSetupViewControllerDelegate <NSObject>

@optional

/// Sent when the view controller was dismissed.
- (void)cloudServiceSetupViewControllerDidDismiss:(SKCloudServiceSetupViewController *)cloudServiceSetupViewController;

@end


/// Action for setup entry point (of type SKCloudServiceSetupAction).
SK_EXTERN SKCloudServiceSetupOptionsKey const SKCloudServiceSetupOptionsActionKey
NS_SWIFT_NAME(action)
API_DEPRECATED("Use the action property of MusicSubscriptionOffer.Options from MusicKit.", ios(10.1, 18.0))
API_UNAVAILABLE(visionos)
API_UNAVAILABLE(macos);

/// Identifier of the iTunes Store item the user is trying to access which requires cloud service setup (NSNumber).
SK_EXTERN SKCloudServiceSetupOptionsKey const SKCloudServiceSetupOptionsITunesItemIdentifierKey
NS_SWIFT_NAME(iTunesItemIdentifier)
API_DEPRECATED("Use the itemID property of MusicSubscriptionOffer.Options from MusicKit.", ios(10.1, 18.0))
API_UNAVAILABLE(visionos)
API_UNAVAILABLE(macos);

/// iTunes Store affiliate token (NSString).
SK_EXTERN SKCloudServiceSetupOptionsKey const SKCloudServiceSetupOptionsAffiliateTokenKey
NS_SWIFT_NAME(affiliateToken)
API_DEPRECATED("Use the affiliateToken property of MusicSubscriptionOffer.Options from MusicKit.", ios(10.3, 18.0))
API_UNAVAILABLE(visionos)
API_UNAVAILABLE(macos);

/// iTunes Store affiliate campaign token (NSString).
SK_EXTERN SKCloudServiceSetupOptionsKey const SKCloudServiceSetupOptionsCampaignTokenKey
NS_SWIFT_NAME(campaignToken)
API_DEPRECATED("Use the campaignToken property of MusicSubscriptionOffer.Options from MusicKit.", ios(10.3, 18.0))
API_UNAVAILABLE(visionos)
API_UNAVAILABLE(macos);

/// Identifier used to select the main message presented to the user for this setup view (SKCloudServiceSetupMessageIdentifier).
/// When missing, the setup view will be configured in a way that is equivalent to using SKCloudServiceSetupMessageIdentifierJoin.
SK_EXTERN SKCloudServiceSetupOptionsKey const SKCloudServiceSetupOptionsMessageIdentifierKey
NS_SWIFT_NAME(messageIdentifier)
API_DEPRECATED("Use the messageIdentifier property of MusicSubscriptionOffer.Options from MusicKit.", ios(11.0, 18.0))
API_UNAVAILABLE(visionos)
API_UNAVAILABLE(macos);

// Supported actions for setup entry point.
SK_EXTERN SKCloudServiceSetupAction const SKCloudServiceSetupActionSubscribe
API_DEPRECATED("Use MusicSubscriptionOffer.Action.subscribe from MusicKit.", ios(10.1, 18.0))
API_UNAVAILABLE(visionos)
API_UNAVAILABLE(macos);

// Supported message identifiers.
SK_EXTERN SKCloudServiceSetupMessageIdentifier const SKCloudServiceSetupMessageIdentifierJoin
API_DEPRECATED("Use MusicSubscriptionOffer.MessageIdentifier.join from MusicKit.", ios(11.0, 18.0))
API_UNAVAILABLE(visionos)
API_UNAVAILABLE(macos);

SK_EXTERN SKCloudServiceSetupMessageIdentifier const SKCloudServiceSetupMessageIdentifierConnect
API_DEPRECATED("No longer supported.", ios(11.0, 18.0))
API_UNAVAILABLE(visionos)
API_UNAVAILABLE(macos);

SK_EXTERN SKCloudServiceSetupMessageIdentifier const SKCloudServiceSetupMessageIdentifierAddMusic
API_DEPRECATED("Use MusicSubscriptionOffer.MessageIdentifier.addMusic from MusicKit.", ios(11.0, 18.0))
API_UNAVAILABLE(visionos)
API_UNAVAILABLE(macos);

SK_EXTERN SKCloudServiceSetupMessageIdentifier const SKCloudServiceSetupMessageIdentifierPlayMusic
API_DEPRECATED("Use MusicSubscriptionOffer.MessageIdentifier.playMusic from MusicKit.", ios(11.0, 18.0))
API_UNAVAILABLE(visionos)
API_UNAVAILABLE(macos);

NS_ASSUME_NONNULL_END
