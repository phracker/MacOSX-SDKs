//
//  SKStoreReviewController.h
//  StoreKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>
#if TARGET_OS_IOS
#import <UIKit/UIKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

/** Controller class to request a review from the current user */
SK_EXTERN_CLASS
API_DEPRECATED("Use AppStore.requestReview(in:).", ios(10.3, 18.0), macos(10.14, 15.0), visionos(1.0, 2.0))
API_UNAVAILABLE(watchos)
__TVOS_PROHIBITED
NS_SWIFT_SENDABLE
@interface SKStoreReviewController : NSObject

/** Request StoreKit to ask the user for an app review. Uses the keyWindow's UIWindowScene which may or may not be the scene a user is interacting with.
 *
 *  This may or may not show any UI.
 *
 *  Given this may not successfully present an alert to the user, it is not appropriate for use
 *  from a button or any other user action. For presenting a write review form, a deep link is 
 *  available to the App Store by appending the query params "action=write-review" to a product URL.
 */
+ (void)requestReview
API_DEPRECATED("Use -[SKStoreReviewController requestReviewInScene:].", ios(10.3, 14.0))
API_DEPRECATED("Use AppStore.requestReview(in:).", macos(10.14, 15.0))
API_UNAVAILABLE(visionos)
API_UNAVAILABLE(watchos)
__TVOS_PROHIBITED;

#if TARGET_OS_IOS
/** Request StoreKit to ask the user for an app review in a given UIWindowScene.
 *
 *  This may or may not show any UI.
 *
 *  Given this may not successfully present an alert to the user, it is not appropriate for use
 *  from a button or any other user action. For presenting a write review form, a deep link is
 *  available to the App Store by appending the query params "action=write-review" to a product URL.
 */
+ (void)requestReviewInScene:(UIWindowScene *)windowScene
API_DEPRECATED("Use AppStore.requestReview(in:).", ios(14.0, 18.0), visionos(1.0, 2.0))
API_UNAVAILABLE(watchos)
__TVOS_PROHIBITED
NS_SWIFT_UI_ACTOR;
#endif
@end

NS_ASSUME_NONNULL_END
