#if !__has_include(<PassKitCore/PKInstantFundsOutFeeSummaryItem.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKInstantFundsOutFeeSummaryItem.h
//    PassKit
//  Copyright © 2023 Apple, Inc. All rights reserved.
//

#import <PassKit/PKPaymentSummaryItem.h>

#ifndef __PKINSTANTFUNDSOUTFEESUMMARYITEM_H__
#define __PKINSTANTFUNDSOUTFEESUMMARYITEM_H__

NS_ASSUME_NONNULL_BEGIN

// A summary item representing a fee for an Instant Funds Out transfer.
API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos, tvos)
@interface PKInstantFundsOutFeeSummaryItem : PKPaymentSummaryItem

@end

NS_ASSUME_NONNULL_END

#endif // __PKINSTANTFUNDSOUTFEESUMMARYITEM_H__

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKInstantFundsOutFeeSummaryItem.h>
#endif