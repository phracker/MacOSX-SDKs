//
//  SKStorefront.h
//  StoreKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS API_AVAILABLE(ios(13.0), macos(10.15), watchos(6.2)) @interface SKStorefront : NSObject

/* The three letter country code for the current storefront */
@property(NS_NONATOMIC_IOSONLY, copy, readonly) NSString *countryCode API_AVAILABLE(ios(13.0), macos(10.15), watchos(6.2));

/* The App Store storefront identifier */
@property(NS_NONATOMIC_IOSONLY, copy, readonly) NSString *identifier API_AVAILABLE(ios(13.0), macos(10.15), watchos(6.2));

@end

NS_ASSUME_NONNULL_END
