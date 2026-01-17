#if !__has_include(<PassKitCore/PKPaymentRequestStatus.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKPaymentRequestStatus.h
//    PassKit
//  Copyright © 2016 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PassKit/PKConstants.h>

NS_ASSUME_NONNULL_BEGIN

@class PKShippingMethod;
@class PKPaymentSummaryItem;
@class PKPaymentMerchantSession;
@class PKPaymentTokenContext;
@class PKAutomaticReloadPaymentRequest;
@class PKRecurringPaymentRequest;
@class PKDeferredPaymentRequest;
@class PKPaymentOrderDetails;

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

// Optional metadata for an order that was placed by this payment. The device will attempt to fetch
// the order in the background. Ignored unless the status is `PKPaymentAuthorizationStatusSuccess`.
@property (nonatomic, strong, nullable) PKPaymentOrderDetails *orderDetails API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(watchos);


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

// The new array of payment token contexts to update the payment request with.
// The default value is `nil`, which indicates no update is needed.
//
// This property cannot be used simultaneously with recurring or automatic reload payment requests.
@property (nonatomic, copy, nullable) NSArray<PKPaymentTokenContext *> *multiTokenContexts API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(watchos);

// The new recurring payment request to update the payment request with.
// The default value is `nil`, which indicates no update is needed.
//
// The billing agreement cannot be changed.
//
// This property cannot be used simultaneously with multi token contexts or automatic reload payment requests.
@property (nonatomic, strong, nullable) PKRecurringPaymentRequest *recurringPaymentRequest API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(watchos);

// The new automatic reload payment request to update the payment request with.
// The default value is `nil`, which indicates no update is needed.
//
// The billing agreement cannot be changed.
//
// This property cannot be used simultaneously with multi token contexts or recurring payment requests.
@property (nonatomic, strong, nullable) PKAutomaticReloadPaymentRequest *automaticReloadPaymentRequest API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(watchos);

// The new deferred payment request to update the payment request with.
// The default value is `nil`, which indicates no update is needed.
//
// The billing agreeement cannot be changed.
//
// This property cannot be used simultaneously with: multi token contexts, recurring payment requests or automatic reload payment requests.
@property (nonatomic, strong, nullable) PKDeferredPaymentRequest *deferredPaymentRequest API_AVAILABLE(macos(13.3), ios(16.4)) API_UNAVAILABLE(watchos);

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

API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(watchos)
@interface PKPaymentOrderDetails : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithOrderTypeIdentifier:(NSString *)orderTypeIdentifier
                            orderIdentifier:(NSString *)orderIdentifier
                              webServiceURL:(NSURL *)webServiceURL
                        authenticationToken:(NSString *)authenticationToken NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy) NSString *orderTypeIdentifier;
@property (nonatomic, copy) NSString *orderIdentifier;
@property (nonatomic, copy) NSURL *webServiceURL;
@property (nonatomic, copy) NSString *authenticationToken;

@end

NS_ASSUME_NONNULL_END

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKPaymentRequestStatus.h>
#endif