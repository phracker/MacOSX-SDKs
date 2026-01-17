#if !__has_include(<PassKitCore/PKAutomaticReloadPaymentSummaryItem.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKAutomaticReloadPaymentSummaryItem.h
//    PassKit
//
//  Copyright © 2021 Apple, Inc. All rights reserved.
//

#import <PassKit/PKPaymentSummaryItem.h>

#ifndef PKAutomaticReloadPaymentSummaryItem_h
#define PKAutomaticReloadPaymentSummaryItem_h

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos)
@interface PKAutomaticReloadPaymentSummaryItem : PKPaymentSummaryItem

// The threshold at which the reload amount will be applied.
@property (nonatomic, strong) NSDecimalNumber *thresholdAmount;

@end

NS_ASSUME_NONNULL_END

#endif // PKAutomaticReloadPaymentSummaryItem_h

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKAutomaticReloadPaymentSummaryItem.h>
#endif