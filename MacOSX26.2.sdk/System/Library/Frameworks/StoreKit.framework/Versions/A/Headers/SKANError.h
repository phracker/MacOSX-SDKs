//
//  SKANError.h
//  StoreKit
//
//  Created by Nikhil R Varma on 1/10/22.
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN NSString * const SKANErrorDomain API_AVAILABLE(ios(15.4), visionos(1.0)) API_UNAVAILABLE(macos,watchos) __TVOS_PROHIBITED;

typedef NS_ERROR_ENUM(SKANErrorDomain, SKANError) {
    SKANErrorImpressionMissingRequiredValue = 0,
    SKANErrorUnsupported                    = 1,
    SKANErrorAdNetworkIdMissing             = 2,
    SKANErrorMismatchedSourceAppId          = 3,
    SKANErrorImpressionNotFound             = 4,
    SKANErrorInvalidCampaignId              = 5,
    SKANErrorInvalidConversionValue         = 6,
    SKANErrorInvalidSourceAppId             = 7,
    SKANErrorInvalidAdvertisedAppId         = 8,
    SKANErrorInvalidVersion                 = 9,
    SKANErrorUnknown                        = 10,
    SKANErrorImpressionTooShort             = 11,
} API_AVAILABLE(ios(15.4), visionos(1.0)) API_UNAVAILABLE(macos,watchos) __TVOS_PROHIBITED;

NS_ASSUME_NONNULL_END
