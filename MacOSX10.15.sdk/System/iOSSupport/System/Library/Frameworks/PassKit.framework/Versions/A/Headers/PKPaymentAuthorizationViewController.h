//
//  PKPaymentAuthorizationViewController.h
//  PassKit
//
//  Copyright (c) 2014 Apple, Inc. All rights reserved.
//
#if !TARGET_OS_WATCH && !TARGET_OS_TV

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#if !TARGET_OS_MACCATALYST
#import <AddressBook/ABRecord.h>
#endif
#else
#import <AppKit/AppKit.h>
#import <AddressBook/ABAddressBookC.h>
#endif

#import <PassKit/PKConstants.h>
#import <PassKit/PKPaymentRequest.h>

NS_ASSUME_NONNULL_BEGIN

@class PKPayment;
@class PKContact;
@class PKPaymentMethod;
@class PKShippingMethod;
@class PKPaymentSummaryItem;
@class PKPaymentAuthorizationResult;
@class PKPaymentRequestPaymentMethodUpdate;
@class PKPaymentAuthorizationViewController;
@class PKPaymentRequestShippingMethodUpdate;
@class PKPaymentRequestShippingContactUpdate;

@protocol PKPaymentAuthorizationViewControllerDelegate <NSObject>

@required

// Sent to the delegate when payment authorization is finished.  This may occur when
// the user cancels the request, or after the PKPaymentAuthorizationStatus parameter of the
// paymentAuthorizationViewController:didAuthorizePayment:completion: has been shown to the user.
//
// The delegate is responsible for dismissing the view controller in this method.
- (void)paymentAuthorizationViewControllerDidFinish:(PKPaymentAuthorizationViewController *)controller;

@optional

// Sent to the delegate after the user has acted on the payment request.  The application
// should inspect the payment to determine whether the payment request was authorized.
//
// If the application requested a shipping address then the full addresses is now part of the payment.
//
// The delegate must call completion with an appropriate authorization status, as may be determined
// by submitting the payment credential to a processing gateway for payment authorization.
- (void)paymentAuthorizationViewController:(PKPaymentAuthorizationViewController *)controller
                       didAuthorizePayment:(PKPayment *)payment
                                   handler:(void (^)(PKPaymentAuthorizationResult *result))completion API_AVAILABLE(ios(11.0), watchos(4.0));

// Sent to the delegate before the payment is authorized, but after the user has authenticated using
// passcode or Touch ID. Optional.
- (void)paymentAuthorizationViewControllerWillAuthorizePayment:(PKPaymentAuthorizationViewController *)controller API_AVAILABLE(ios(8.3), watchos(3.0));


// Sent when the user has selected a new shipping method.  The delegate should determine
// shipping costs based on the shipping method and either the shipping address supplied in the original
// PKPaymentRequest or the address fragment provided by the last call to paymentAuthorizationViewController:
// didSelectShippingAddress:completion:.
//
// The delegate must invoke the completion block with an updated array of PKPaymentSummaryItem objects.
//
// The delegate will receive no further callbacks except paymentAuthorizationViewControllerDidFinish:
// until it has invoked the completion block.
- (void)paymentAuthorizationViewController:(PKPaymentAuthorizationViewController *)controller
                   didSelectShippingMethod:(PKShippingMethod *)shippingMethod
                                   handler:(void (^)(PKPaymentRequestShippingMethodUpdate *update))completion API_AVAILABLE(ios(11.0), watchos(4.0));

// Sent when the user has selected a new shipping address.  The delegate should inspect the
// address and must invoke the completion block with an updated array of PKPaymentSummaryItem objects.
//
// The delegate will receive no further callbacks except paymentAuthorizationViewControllerDidFinish:
// until it has invoked the completion block.

- (void)paymentAuthorizationViewController:(PKPaymentAuthorizationViewController *)controller
                  didSelectShippingContact:(PKContact *)contact
                                   handler:(void (^)(PKPaymentRequestShippingContactUpdate *update))completion API_AVAILABLE(ios(11.0), watchos(4.0));

// Sent when the user has selected a new payment card.  Use this delegate callback if you need to
// update the summary items in response to the card type changing (for example, applying credit card surcharges)
//
// The delegate will receive no further callbacks except paymentAuthorizationViewControllerDidFinish:
// until it has invoked the completion block.

- (void)paymentAuthorizationViewController:(PKPaymentAuthorizationViewController *)controller
                    didSelectPaymentMethod:(PKPaymentMethod *)paymentMethod
                                   handler:(void (^)(PKPaymentRequestPaymentMethodUpdate *update))completion API_AVAILABLE(ios(11.0), watchos(4.0));

// Deprecated delegate methods
// These methods are deprecated. Please migrate away from them to their replacements.
- (void)paymentAuthorizationViewController:(PKPaymentAuthorizationViewController *)controller
                       didAuthorizePayment:(PKPayment *)payment
                                completion:(void (^)(PKPaymentAuthorizationStatus status))completion API_DEPRECATED("Use paymentAuthorizationViewController:didAuthorizePayment:handler: instead to provide more granular errors", ios(8.0, 11.0));

- (void)paymentAuthorizationViewController:(PKPaymentAuthorizationViewController *)controller
                   didSelectShippingMethod:(PKShippingMethod *)shippingMethod
                                completion:(void (^)(PKPaymentAuthorizationStatus status, NSArray<PKPaymentSummaryItem *> *summaryItems))completion API_DEPRECATED("Use paymentAuthorizationViewController:didSelectShippingMethod:handler: instead to provide more granular errors", ios(8.0, 11.0));

#if !TARGET_OS_MACCATALYST
- (void)paymentAuthorizationViewController:(PKPaymentAuthorizationViewController *)controller
                  didSelectShippingAddress:(ABRecordRef)address
                                completion:(void (^)(PKPaymentAuthorizationStatus status, NSArray<PKShippingMethod *> *shippingMethods,
                                                     NSArray<PKPaymentSummaryItem *> *summaryItems))completion API_DEPRECATED("ABRecordRef has been deprecated. Please migrate away from this delegate callback as soon as possible.", ios(8.0, 9.0));
#endif

- (void)paymentAuthorizationViewController:(PKPaymentAuthorizationViewController *)controller
                  didSelectShippingContact:(PKContact *)contact
                                completion:(void (^)(PKPaymentAuthorizationStatus status, NSArray<PKShippingMethod *> *shippingMethods,
                                                     NSArray<PKPaymentSummaryItem *> *summaryItems))completion API_DEPRECATED("Use paymentAuthorizationViewController:didSelectShippingContact:handler: instead to provide more granular errors", ios(9.0, 11.0));

- (void)paymentAuthorizationViewController:(PKPaymentAuthorizationViewController *)controller
                    didSelectPaymentMethod:(PKPaymentMethod *)paymentMethod
                                completion:(void (^)(NSArray<PKPaymentSummaryItem *> *summaryItems))completion API_DEPRECATED("Use paymentAuthorizationViewController:didSelectPaymentMethod:handler: instead to provide more granular errors", ios(9.0, 11.0));

@end

// PKPaymentAuthorizationViewController prompts the user to authorize a PKPaymentRequest, funding the
// payment amount with a valid payment card.
#if TARGET_OS_IPHONE
API_AVAILABLE(ios(8.0))
@interface PKPaymentAuthorizationViewController : UIViewController
#else
NS_CLASS_AVAILABLE_MAC(10_12)
@interface PKPaymentAuthorizationViewController : NSViewController
#endif

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
// See -canMakePaymentsUsingNetworks:
+ (BOOL)canMakePaymentsUsingNetworks:(NSArray<PKPaymentNetwork> *)supportedNetworks capabilities:(PKMerchantCapability)capabilties API_AVAILABLE(ios(9.0));

// The view controller's delegate.
@property (nonatomic, weak, nullable) id<PKPaymentAuthorizationViewControllerDelegate> delegate;

// Initializes and returns a newly created view controller for the supplied payment.
// It is your responsibility to present and dismiss the view controller using the
// appropriate means for the given device idiom.
- (nullable instancetype)initWithPaymentRequest:(PKPaymentRequest *)request NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

#endif
