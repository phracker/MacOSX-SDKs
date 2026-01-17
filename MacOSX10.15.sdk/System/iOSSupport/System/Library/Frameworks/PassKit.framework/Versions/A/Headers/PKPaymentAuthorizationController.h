//
//  PKPaymentAuthorizationController.h
//  PassKit
//
//  Copyright © 2015 Apple, Inc. All rights reserved.
//
#if TARGET_OS_IPHONE

#import <PassKit/PKConstants.h>
#import <PassKit/PKPaymentRequest.h>

NS_ASSUME_NONNULL_BEGIN

@class PKPayment;
@class PKContact;
@class PKPaymentMethod;
@class PKShippingMethod;
@class PKPaymentSummaryItem;
@class PKPaymentAuthorizationResult;
@class PKPaymentAuthorizationController;
@class PKPaymentRequestPaymentMethodUpdate;
@class PKPaymentRequestShippingMethodUpdate;
@class PKPaymentRequestShippingContactUpdate;

@protocol PKPaymentAuthorizationControllerDelegate <NSObject>

@required

// Sent to the delegate when payment authorization is finished.  This may occur when
// the user cancels the request, or after the PKPaymentAuthorizationStatus parameter of the
// paymentAuthorizationController:didAuthorizePayment:completion: has been shown to the user.
//
// The delegate is responsible for dismissing and releasing the controller in this method.
- (void)paymentAuthorizationControllerDidFinish:(PKPaymentAuthorizationController *)controller;

@optional

// Sent to the delegate after the user has acted on the payment request.  The application
// should inspect the payment to determine whether the payment request was authorized.
//
// If the application requested a shipping contact then the full contact is now part of the payment.
//
// The delegate must call completion with an appropriate authorization status, as may be determined
// by submitting the payment credential to a processing gateway for payment authorization.
- (void)paymentAuthorizationController:(PKPaymentAuthorizationController *)controller
                   didAuthorizePayment:(PKPayment *)payment
                               handler:(void (^)(PKPaymentAuthorizationResult *result))completion API_AVAILABLE(ios(11.0), watchos(4.0));

- (void)paymentAuthorizationController:(PKPaymentAuthorizationController *)controller
                   didAuthorizePayment:(PKPayment *)payment
                            completion:(void (^)(PKPaymentAuthorizationStatus status))completion API_DEPRECATED("Use paymentAuthorizationController:didAuthorizePayment:handler: instead to provide more granular errors", ios(10.0, 11.0), watchos(3.0, 4.0));

// Sent to the delegate before the payment is authorized, but after the user has authenticated using
// the side button. Optional.
- (void)paymentAuthorizationControllerWillAuthorizePayment:(PKPaymentAuthorizationController *)controller;


// Sent when the user has selected a new shipping method.  The delegate should determine
// shipping costs based on the shipping method and either the shipping address contact in the original
// PKPaymentRequest or the contact provided by the last call to paymentAuthorizationController:
// didSelectShippingContact:completion:.
//
// The delegate must invoke the completion block with an updated array of PKPaymentSummaryItem objects.
//
// The delegate will receive no further callbacks except paymentAuthorizationControllerDidFinish:
// until it has invoked the completion block.
- (void)paymentAuthorizationController:(PKPaymentAuthorizationController *)controller
               didSelectShippingMethod:(PKShippingMethod *)shippingMethod
                               handler:(void (^)(PKPaymentRequestShippingMethodUpdate *requestUpdate))completion API_AVAILABLE(ios(11.0), watchos(4.0));

- (void)paymentAuthorizationController:(PKPaymentAuthorizationController *)controller
              didSelectShippingContact:(PKContact *)contact
                               handler:(void (^)(PKPaymentRequestShippingContactUpdate *requestUpdate))completion API_AVAILABLE(ios(11.0), watchos(4.0));


// Sent when the user has selected a new payment card.  Use this delegate callback if you need to
// update the summary items in response to the card type changing (for example, applying credit card surcharges)
//
// The delegate will receive no further callbacks except paymentAuthorizationControllerDidFinish:
// until it has invoked the completion block.

- (void)paymentAuthorizationController:(PKPaymentAuthorizationController *)controller
                didSelectPaymentMethod:(PKPaymentMethod *)paymentMethod
                               handler:(void (^)(PKPaymentRequestPaymentMethodUpdate *requestUpdate))completion API_AVAILABLE(ios(11.0), watchos(4.0));

// These delegate methods are deprecated and have been replaced with new callbacks that allow more granular
// and comprehensive errors to be surfaced to users
- (void)paymentAuthorizationController:(PKPaymentAuthorizationController *)controller
               didSelectShippingMethod:(PKShippingMethod *)shippingMethod
                            completion:(void (^)(PKPaymentAuthorizationStatus status, NSArray<PKPaymentSummaryItem *> *summaryItems))completion API_DEPRECATED("Use paymentAuthorizationController:didSelectShippingMethod:handler: instead to provide more granular errors", ios(10.0, 11.0), watchos(3.0, 4.0));

- (void)paymentAuthorizationController:(PKPaymentAuthorizationController *)controller
              didSelectShippingContact:(PKContact *)contact
                            completion:(void (^)(PKPaymentAuthorizationStatus status, NSArray<PKShippingMethod *> *shippingMethods,
                                                 NSArray<PKPaymentSummaryItem *> *summaryItems))completion API_DEPRECATED("Use paymentAuthorizationController:didSelectShippingContact:handler: instead to provide more granular errors", ios(10.0, 11.0), watchos(3.0, 4.0));

- (void)paymentAuthorizationController:(PKPaymentAuthorizationController *)controller
                didSelectPaymentMethod:(PKPaymentMethod *)paymentMethod
                            completion:(void (^)(NSArray<PKPaymentSummaryItem *> *summaryItems))completion API_DEPRECATED("Use paymentAuthorizationController:didSelectPaymentMethod:handler: instead to provide more granular errors", ios(10.0, 11.0), watchos(3.0, 4.0));

@end

// PKPaymentAuthorizationController prompts the user to authorize a PKPaymentRequest, funding the
// payment amount with a valid payment card.
API_AVAILABLE(ios(10.0), watchos(3.0))
@interface PKPaymentAuthorizationController : NSObject

// Determine whether this device can process payment requests.
// YES if the device is generally capable of making in-app payments.
// NO if the device cannot make in-app payments or if the user is restricted from authorizing payments.
+ (BOOL)canMakePayments;

// Determine whether this device can process payment requests using specific payment network brands.
// Your application should confirm that the user can make payments before attempting to authorize a payment.
// Your application may also want to alter its appearance or behavior when the user is not allowed
// to make payments.
// YES if the user can authorize payments on this device using one of the payment networks supported
// by the merchant.
// NO if the user cannot authorize payments on these networks or if the user is restricted from
// authorizing payments.
+ (BOOL)canMakePaymentsUsingNetworks:(NSArray<PKPaymentNetwork> *)supportedNetworks;

// Determine whether this device can process payments using the specified networks and capabilities bitmask
// See +canMakePaymentsUsingNetworks:
+ (BOOL)canMakePaymentsUsingNetworks:(NSArray<PKPaymentNetwork> *)supportedNetworks capabilities:(PKMerchantCapability)capabilties;

// The controller's delegate.
@property (nonatomic, weak, nullable) id<PKPaymentAuthorizationControllerDelegate> delegate;

// Initialize the controller with a payment request.
- (instancetype)initWithPaymentRequest:(PKPaymentRequest *)request NS_DESIGNATED_INITIALIZER;

// Presents the Apple Pay UI modally over your app. You are responsible for dismissal
- (void)presentWithCompletion:(nullable void(^)(BOOL success))completion;

// Dismisses the Apple Pay UI. Call this when you receive the paymentAuthorizationControllerDidFinish delegate
// callback, or otherwise wish a dismissal to occur
- (void)dismissWithCompletion:(nullable void(^)(void))completion;

@end

NS_ASSUME_NONNULL_END

#endif
