//
//  PKPaymentSummaryItem.h
//
//  Copyright © 2021 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PassKit/PKConstants.h>

#ifndef __PKPAYMENTSUMMARYITEM_H__
#define __PKPAYMENTSUMMARYITEM_H__

@class PKDateComponentsRange;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, PKPaymentSummaryItemType) {
    PKPaymentSummaryItemTypeFinal,      // The payment summary item's amount is known to be correct
    PKPaymentSummaryItemTypePending     // The payment summary item's amount is estimated or unknown - e.g, a taxi fare
}  API_AVAILABLE(ios(9.0), watchos(3.0));

// PKPaymentSummaryItem Defines a line-item for a payment such as tax, shipping, or discount.
API_AVAILABLE(ios(8.0), watchos(3.0))
@interface PKPaymentSummaryItem : NSObject

+ (instancetype)summaryItemWithLabel:(NSString *)label amount:(NSDecimalNumber *)amount;
+ (instancetype)summaryItemWithLabel:(NSString *)label amount:(NSDecimalNumber *)amount type:(PKPaymentSummaryItemType)type API_AVAILABLE(ios(9.0), watchos(3.0));

// A short localized description of the item, e.g. "Tax" or "Gift Card".
@property (nonatomic, copy) NSString *label;

// Same currency as the enclosing PKPaymentRequest.  Negative values are permitted, for example when
// redeeming a coupon. An amount is always required unless the summary item's type is set to pending
@property (nonatomic, copy) NSDecimalNumber *amount;

// Defaults to PKPaymentSummaryItemTypeFinal
// Set to PKPaymentSummaryItemTypePending if the amount of the item is not known at this time
@property (nonatomic, assign) PKPaymentSummaryItemType type API_AVAILABLE(ios(9.0), watchos(3.0));

@end

NS_ASSUME_NONNULL_END

#endif // __PKPAYMENTSUMMARYITEM_H__
