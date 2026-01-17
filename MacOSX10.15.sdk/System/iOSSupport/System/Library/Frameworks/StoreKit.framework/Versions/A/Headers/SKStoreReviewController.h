//
//  SKStoreReviewController.h
//  StoreKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

/** Controller class to request a review from the current user */
SK_EXTERN_CLASS API_AVAILABLE(ios(10.3), macos(10.14)) __TVOS_PROHIBITED @interface SKStoreReviewController : NSObject

/** Request StoreKit to ask the user for an app review. This may or may not show any UI.
 *
 *  Given this may not successfully present an alert to the user, it is not appropriate for use
 *  from a button or any other user action. For presenting a write review form, a deep link is 
 *  available to the App Store by appending the query params "action=write-review" to a product URL.
 */
+ (void)requestReview API_AVAILABLE(ios(10.3), macos(10.14)) __TVOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
