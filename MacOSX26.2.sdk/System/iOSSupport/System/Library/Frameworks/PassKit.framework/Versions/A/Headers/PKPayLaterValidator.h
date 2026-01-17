#if !__has_include(<PassKitCore/PKPayLaterValidator.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKPayLaterValidator.h
//    PassKit
//
//  Copyright © 2023 Apple, Inc. All rights reserved.
//

#ifndef __PKPAYLATERVALIDATOR_H
#define __PKPAYLATERVALIDATOR_H

#import <TargetConditionals.h>
#import <Foundation/Foundation.h>

#if TARGET_OS_IOS && !TARGET_OS_MACCATALYST

typedef NS_ENUM(NSInteger, PKPayLaterDisplayStyle) {
    PKPayLaterDisplayStyleStandard = 0, /// The Standard Merchandising Widget
    PKPayLaterDisplayStyleBadge, /// Displays a simple Pay badge with the pay later info graphic
    PKPayLaterDisplayStyleCheckout, /// To be displayed inside of a toggleable checkout view
    PKPayLaterDisplayStylePrice, /// To be shown beneath a products price
} API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(macos, watchos, tvos);

typedef NS_ENUM(NSInteger, PKPayLaterAction) {
    PKPayLaterActionLearnMore = 0, /// Displays a simple info sheet on the learn more details of pay later
    PKPayLaterActionCalculator, /// The Standard Price breakdown calculator for pay later, that features an interactive calculator
} API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(macos, watchos, tvos);

/// Checks if a Pay Later Merchandising information can be displayed for the given values
/// - Parameters:
///   - amount: The users bag price or item pricing
///   - currencyCode: The ISO 4217 code for the country or region of the merchant’s principle place of business.
///   - completion: The block that is called when the eligibility result is calculated
API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(macos, watchos, tvos)
extern void PKPayLaterValidateAmount(NSDecimalNumber *amount, NSString *currencyCode, void(^completion)(BOOL eligible)) NS_REFINED_FOR_SWIFT;

#endif // TARGET_OS_IOS && !TARGET_OS_MACCATALYST

#endif // __PKPAYLATERVIEW_H

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKPayLaterValidator.h>
#endif