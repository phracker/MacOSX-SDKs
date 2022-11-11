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
@class PKPaymentMerchantSession;

API_AVAILABLE(macos(11.0), ios(11.0), watchos(4.0))
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

API_AVAILABLE(macos(11.0), ios(11.0), watchos(4.0))
@interface PKPaymentRequestUpdate : NSObject

- (instancetype)initWithPaymentSummaryItems:(NSArray<PKPaymentSummaryItem *> *)paymentSummaryItems NS_DESIGNATED_INITIALIZER;

// The status of the payment request update. Set PKPaymentAuthorizationStatusSuccess for a successful update,
// and PKPaymentAuthorizationStatusFailure if you were unable to process the required changes.
// PKPaymentAuthorizationStatusSuccess by default
@property (nonatomic, assign) PKPaymentAuthorizationStatus status;

// The new payment summary items to update the payment request with
@property (nonatomic, copy) NSArray<PKPaymentSummaryItem *> *paymentSummaryItems;

// The new shipping methods to update the payment request with. An empty array, the default value,
// indicates that the shipping methods don't need updating.
@property (nonatomic, copy) NSArray<PKShippingMethod *> *shippingMethods API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0));



@end

API_AVAILABLE(macos(11.0), ios(11.0), watchos(4.0))
@interface PKPaymentRequestShippingContactUpdate : PKPaymentRequestUpdate

// You may optionally supply errors here. 
// See PKError for specific NSError keys to use.
- (instancetype)initWithErrors:(nullable NSArray<NSError *> *)errors
           paymentSummaryItems:(NSArray<PKPaymentSummaryItem *> *)paymentSummaryItems
               shippingMethods:(NSArray<PKShippingMethod *> *)shippingMethods NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy) NSArray<PKShippingMethod *> *shippingMethods;
@property (null_resettable, nonatomic, copy) NSArray<NSError *> *errors;

@end

API_AVAILABLE(macos(11.0), ios(11.0), watchos(4.0))
@interface PKPaymentRequestShippingMethodUpdate : PKPaymentRequestUpdate

@end

API_AVAILABLE(macos(11.0), ios(11.0), watchos(4.0))
@interface PKPaymentRequestPaymentMethodUpdate : PKPaymentRequestUpdate

// You may optionally supply errors here.
// See PKError for specific NSError keys to use.
- (instancetype)initWithErrors:(nullable NSArray<NSError *> *)errors
           paymentSummaryItems:(NSArray<PKPaymentSummaryItem *> *)paymentSummaryItems NS_DESIGNATED_INITIALIZER;

@property (null_resettable, nonatomic, copy) NSArray<NSError *> *errors;
@end

API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0))
@interface PKPaymentRequestMerchantSessionUpdate : NSObject

- (instancetype)initWithStatus:(PKPaymentAuthorizationStatus)status
               merchantSession:(nullable PKPaymentMerchantSession *)session;

@property (nonatomic, assign) PKPaymentAuthorizationStatus status;
@property (nullable, nonatomic, strong) PKPaymentMerchantSession *session;

@end

API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos)
@interface PKPaymentRequestCouponCodeUpdate : PKPaymentRequestUpdate

// You may optionally supply errors here.
// See PKError for specific NSError keys to use.
- (instancetype)initWithErrors:(nullable NSArray<NSError *> *)errors
           paymentSummaryItems:(NSArray<PKPaymentSummaryItem *> *)paymentSummaryItems
               shippingMethods:(NSArray<PKShippingMethod *> *)shippingMethods NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy, null_resettable) NSArray<NSError *> *errors;

@end

NS_ASSUME_NONNULL_END
