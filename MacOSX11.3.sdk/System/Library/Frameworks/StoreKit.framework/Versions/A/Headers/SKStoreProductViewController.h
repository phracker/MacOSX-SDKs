//
//  SKStoreProductViewController.h
//  StoreKit
//
//  Copyright (c) 2012 Apple, Inc. All rights reserved.
//

#import <StoreKit/StoreKitDefines.h>
#import <TargetConditionals.h>

#if TARGET_OS_OSX
#import <AppKit/AppKit.h>
#else
#import <UIKit/UIKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@protocol SKStoreProductViewControllerDelegate;

/* View controller to display iTunes Store product information */
#if TARGET_OS_OSX
SK_EXTERN_CLASS API_AVAILABLE(ios(6.0), macCatalyst(13.0), macos(11.0)) __TVOS_PROHIBITED @interface SKStoreProductViewController : NSViewController
#else
SK_EXTERN_CLASS API_AVAILABLE(ios(6.0), macCatalyst(13.0), macos(11.0)) __TVOS_PROHIBITED @interface SKStoreProductViewController : UIViewController
#endif

// Delegate for product page events
@property(nonatomic, weak, nullable) id <SKStoreProductViewControllerDelegate> delegate API_AVAILABLE(ios(6.0), macCatalyst(13.0), macos(11.0)) __TVOS_PROHIBITED;

// Load product view for the product with the given parameters.  See below for parameters (SKStoreProductParameter*).
// Block is invoked when the load finishes.
- (void)loadProductWithParameters:(NSDictionary<NSString *, id> *)parameters completionBlock:(nullable void(^)(BOOL result, NSError * __nullable error))block API_AVAILABLE(ios(6.0), macCatalyst(13.0), macos(11.0)) __TVOS_PROHIBITED;

@end


@protocol SKStoreProductViewControllerDelegate <NSObject>

@optional

// Sent after the page is dismissed
- (void)productViewControllerDidFinish:(SKStoreProductViewController *)viewController API_AVAILABLE(ios(6.0), macCatalyst(13.0), macos(11.0)) __TVOS_PROHIBITED;

@end


// iTunes Store item identifier (NSNumber) of the product
SK_EXTERN NSString * const SKStoreProductParameterITunesItemIdentifier API_AVAILABLE(ios(6.0), macCatalyst(13.0), macos(11.0));

// SKU for the In-App Purchase product (NSString) to render at the top of the product page
SK_EXTERN NSString * const SKStoreProductParameterProductIdentifier API_AVAILABLE(ios(11.0), macCatalyst(13.0), macos(11.0));

// iTunes Store affiliate token (NSString)
SK_EXTERN NSString * const SKStoreProductParameterAffiliateToken API_AVAILABLE(ios(8.0), macCatalyst(13.0), macos(11.0));

// iTunes Store affiliate campaign token (NSString)
SK_EXTERN NSString * const SKStoreProductParameterCampaignToken API_AVAILABLE(ios(8.0), macCatalyst(13.0), macos(11.0));

// Analytics provider token (NSString)
SK_EXTERN NSString * const SKStoreProductParameterProviderToken API_AVAILABLE(ios(8.3), macCatalyst(13.0), macos(11.0));

// Advertising partner token (NSString)
SK_EXTERN NSString * const SKStoreProductParameterAdvertisingPartnerToken API_AVAILABLE(ios(9.3), macCatalyst(13.0), macos(11.0));
NS_ASSUME_NONNULL_END
