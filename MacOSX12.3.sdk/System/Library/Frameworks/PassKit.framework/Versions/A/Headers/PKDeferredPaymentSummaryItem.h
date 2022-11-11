//
//  PKDeferredPaymentSummaryItem.h
//
//  Copyright © 2021 Apple, Inc. All rights reserved.
//

#import <PassKit/PKPaymentSummaryItem.h>

#ifndef __PKDEFERREDPAYMENTSUMMARYITEM_H__
#define __PKDEFERREDPAYMENTSUMMARYITEM_H__

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0))
@interface PKDeferredPaymentSummaryItem : PKPaymentSummaryItem

// The timestamp to which the payment is deferred.
@property (nonatomic, copy) NSDate *deferredDate;

@end

NS_ASSUME_NONNULL_END

#endif // __PKDEFERREDPAYMENTSUMMARYITEM_H__
