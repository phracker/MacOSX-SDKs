#if !__has_include(<PassKitCore/PKPass_Types.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKPass_Types.h
//    PassKit
//
//  Copyright (c) 2023 Apple, Inc. All rights reserved.
//

#ifndef __PKPASS_TYPES_H
#define __PKPASS_TYPES_H

typedef NS_ENUM(NSUInteger, PKPassType) {
    PKPassTypeBarcode,
    PKPassTypeSecureElement API_AVAILABLE(ios(13.4), watchos(6.2)),
    PKPassTypePayment API_DEPRECATED("Use PKPassTypeSecureElement instead", macos(10.12, API_TO_BE_DEPRECATED), ios(8.0, API_TO_BE_DEPRECATED), watchos(3.0, API_TO_BE_DEPRECATED)) = PKPassTypeSecureElement,

    PKPassTypeAny = ~(NSUInteger)0
} API_AVAILABLE(ios(8.0), watchos(3.0));

#endif /* __PKPASS_TYPES_H */

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKPass_Types.h>
#endif