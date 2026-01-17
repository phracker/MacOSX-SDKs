#if !__has_include(<PassKitCore/PKDeferredPaymentSummaryItem.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKDeferredPaymentSummaryItem.h
//    PassKit
//  Copyright © 2021 Apple, Inc. All rights reserved.
//

#import <PassKit/PKPaymentSummaryItem.h>

#ifndef __PKDEFERREDPAYMENTSUMMARYITEM_H__
#define __PKDEFERREDPAYMENTSUMMARYITEM_H__

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(15.0), watchos(8.0))
@interface PKDeferredPaymentSummaryItem : PKPaymentSummaryItem

// The timestamp to which the payment is deferred.
@property (nonatomic, copy) NSDate *deferredDate;

@end

NS_ASSUME_NONNULL_END

#endif // __PKDEFERREDPAYMENTSUMMARYITEM_H__

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKDeferredPaymentSummaryItem.h>
#endif