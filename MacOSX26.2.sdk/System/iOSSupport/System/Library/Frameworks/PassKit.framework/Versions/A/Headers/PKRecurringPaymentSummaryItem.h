#if !__has_include(<PassKitCore/PKRecurringPaymentSummaryItem.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKRecurringPaymentSummaryItem.h
//    PassKit
//  Copyright © 2021 Apple, Inc. All rights reserved.
//

#import <PassKit/PKPaymentSummaryItem.h>

#ifndef __PKRECURRINGPAYMENTSUMMARYITEM_H__
#define __PKRECURRINGPAYMENTSUMMARYITEM_H__

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(15.0), watchos(8.0))
@interface PKRecurringPaymentSummaryItem : PKPaymentSummaryItem

// The timestamp at which the first payment will be taken; nil indicates immediately. The default value is nil.
@property (nonatomic, copy, nullable) NSDate *startDate;

// The interval at which payments will be taken (daily, weekly, monthly, yearly, etc.). The default value is NSCalendarUnitMonth.
@property (nonatomic, assign) NSCalendarUnit intervalUnit;

// The number of intervals between payments. Default is 1.
@property (nonatomic, assign) NSInteger intervalCount;

// If set, the date at which the recurring payments will end. Default is nil.
@property (nonatomic, copy, nullable) NSDate *endDate;

@end

NS_ASSUME_NONNULL_END

#endif // __PKRECURRINGPAYMENTSUMMARYITEM_H__

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKRecurringPaymentSummaryItem.h>
#endif