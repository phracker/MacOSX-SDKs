//
//  PKDisbursementRequest.h
//
//  Copyright © 2019 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class PKPaymentSummaryItem;

typedef NS_ENUM(NSInteger, PKDisbursementRequestSchedule) {
    PKDisbursementRequestScheduleOneTime,
    PKDisbursementRequestScheduleFuture,
} NS_SWIFT_NAME(PKDisbursementRequest.Schedule);

// PKDisbursementRequest defines an application's request to disburse an amount
@interface PKDisbursementRequest : NSObject

// An amount is always required. If the disbursement amount is pending, the amount should be zero
@property (nonatomic, copy) NSDecimalNumber *amount API_AVAILABLE(ios(12.2)) API_UNAVAILABLE(tvos, watchos, macos);

// Currency code for this disbursement. The currency code is required unless the requestType is future
@property (nonatomic, copy, nullable) NSString *currencyCode API_AVAILABLE(ios(12.2)) API_UNAVAILABLE(tvos, watchos, macos);

// The merchant's ISO country code.
@property (nonatomic, copy) NSString *countryCode API_AVAILABLE(ios(12.2)) API_UNAVAILABLE(tvos, watchos, macos);

// Specifies if the disbursement is a one time request or a future request
@property (nonatomic, assign) PKDisbursementRequestSchedule requestSchedule API_AVAILABLE(ios(12.2)) API_UNAVAILABLE(tvos, watchos, macos);

// The summary items are optional. The final amount summary item will be prepopulated by the amount specified above.
@property (nonatomic, copy, nullable) NSArray<PKPaymentSummaryItem *> *summaryItems API_AVAILABLE(ios(12.2)) API_UNAVAILABLE(tvos, watchos, macos);

@end

NS_ASSUME_NONNULL_END
