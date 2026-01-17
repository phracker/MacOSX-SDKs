//
//  SKAdNetwork.h
//  StoreKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) __TVOS_PROHIBITED @interface SKAdNetwork : NSObject

// Participating apps should call this on launch to complete the install+open action associated with a product view
+ (void)registerAppForAdNetworkAttribution API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) __TVOS_PROHIBITED;

@end

// Constants for use with SKStoreProductViewController to associate a product view with an install+open

// Advertising network's cryptographic signature for the atribution params (NSString)
SK_EXTERN NSString * const SKStoreProductParameterAdNetworkAttributionSignature API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos);

// Advertising network campaign identifier (NSNumber)
SK_EXTERN NSString * const SKStoreProductParameterAdNetworkCampaignIdentifier API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos);

// Advertising network identifier (NSString)
SK_EXTERN NSString * const SKStoreProductParameterAdNetworkIdentifier API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos);

// Random entropy value for security (NSUUID)
SK_EXTERN NSString * const SKStoreProductParameterAdNetworkNonce API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos);

// Timestamp for this ad impression (NSNumber)
SK_EXTERN NSString * const SKStoreProductParameterAdNetworkTimestamp API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos);

NS_ASSUME_NONNULL_END
