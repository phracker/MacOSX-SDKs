//
//  SKStorefront.h
//  StoreKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS
API_DEPRECATED("Use Storefront.", ios(13.0, 18.0), macos(10.15, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0))
NS_SWIFT_SENDABLE
@interface SKStorefront : NSObject

/* The three letter country code for the current storefront */
@property(NS_NONATOMIC_IOSONLY, copy, readonly) NSString *countryCode API_DEPRECATED("Use 'Storefront.countryCode'.", ios(13.0, 18.0), macos(10.15, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

/* The App Store storefront identifier */
@property(NS_NONATOMIC_IOSONLY, copy, readonly) NSString *identifier API_DEPRECATED("Use 'Storefront.id'.", ios(13.0, 18.0), macos(10.15, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));

@end

NS_ASSUME_NONNULL_END
