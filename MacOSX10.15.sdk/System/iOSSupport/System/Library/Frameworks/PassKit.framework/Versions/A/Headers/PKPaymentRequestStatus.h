//
//  PKPaymentRequestStatus.h
//
//  Copyright © 2016 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PassKit/PKConstants.h>

NS_ASSUME_NONNULL_BEGIN

@class PKShippingMethod;
@class PKPaymentSummaryItem;

API_AVAILABLE(ios(11.0), watchos(4.0))
@interface PKPaymentAuthorizationResult : NSObject

- (instancetype)initWithStatus:(PKPaymentAuthorizationStatus)status
                        errors:(nullable NSArray<NSError *> *)errors NS_DESIGNATED_INITIALIZER;

// The status of the payment
@property (nonatomic, assign) PKPaymentAuthorizationStatus status;

// Any errors that applied. These errors will be displayed to the user to correct.
// Errors should be ordered from most to least serious.
// See PKError for specific NSError keys to use to enable rich error handling.
@property (null_resettable, nonatomic, copy) NSArray<NSError *> *errors;

@end

API_AVAILABLE(ios(11.0), watchos(4.0))
@interface PKPaymentRequestUpdate : NSObject

- (instancetype)initWithPaymentSummaryItems:(NSArray<PKPaymentSummaryItem *> *)paymentSummaryItems NS_DESIGNATED_INITIALIZER;

// The status of the payment request update. Set PKPaymentAuthorizationStatusSuccess for a successful update,
// and PKPaymentAuthorizationStatusFailure if you were unable to process the required changes.
// PKPaymentAuthorizationStatusSuccess by default
@property (nonatomic, assign) PKPaymentAuthorizationStatus status;

// The new payment summary items to update the payment request with
@property (nonatomic, copy) NSArray<PKPaymentSummaryItem *> *paymentSummaryItems;

@end

API_AVAILABLE(ios(11.0), watchos(4.0))
@interface PKPaymentRequestShippingContactUpdate : PKPaymentRequestUpdate

// You may optionally supply errors here. 
// See PKError for specific NSError keys to use.
- (instancetype)initWithErrors:(nullable NSArray<NSError *> *)errors
           paymentSummaryItems:(NSArray<PKPaymentSummaryItem *> *)paymentSummaryItems
               shippingMethods:(NSArray<PKShippingMethod *> *)shippingMethods NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy) NSArray<PKShippingMethod *> *shippingMethods;
@property (null_resettable, nonatomic, copy) NSArray<NSError *> *errors;

@end

API_AVAILABLE(ios(11.0), watchos(4.0))
@interface PKPaymentRequestShippingMethodUpdate : PKPaymentRequestUpdate

@end

API_AVAILABLE(ios(11.0), watchos(4.0))
@interface PKPaymentRequestPaymentMethodUpdate : PKPaymentRequestUpdate

// You may optionally supply errors here.
// See PKError for specific NSError keys to use.
- (instancetype)initWithErrors:(nullable NSArray<NSError *> *)errors
           paymentSummaryItems:(NSArray<PKPaymentSummaryItem *> *)paymentSummaryItems NS_DESIGNATED_INITIALIZER;

@property (null_resettable, nonatomic, copy) NSArray<NSError *> *errors;
@end

NS_ASSUME_NONNULL_END
