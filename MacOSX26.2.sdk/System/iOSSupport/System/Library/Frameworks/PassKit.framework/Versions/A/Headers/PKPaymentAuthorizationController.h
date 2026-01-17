#if (!__has_include(<PassKitUI/PKPaymentAuthorizationController.h>) && !__has_include(<PassKitMacHelperTemp/PKPaymentAuthorizationController.h>)) || PK_USE_PUBLIC_PASSKIT
//
//  PKPaymentAuthorizationController.h
//    PassKit
//
//  Copyright © 2015 Apple, Inc. All rights reserved.
//

#ifndef __PKPAYMENTAUTHORIZATIONCONTROLLER_H
#define __PKPAYMENTAUTHORIZATIONCONTROLLER_H

#import <TargetConditionals.h>

#if TARGET_OS_OSX || TARGET_OS_IPHONE

#import <PassKit/PKConstants.h>
#import <PassKit/PKPaymentRequest.h>

#if TARGET_OS_IPHONE
@class UIWindow;
#else // TARGET_OS_OSX
@class NSWindow;
#endif

NS_ASSUME_NONNULL_BEGIN

@class PKPayment;
@class PKContact;
@class PKPaymentMethod;
@class PKShippingMethod;
@class PKPaymentSummaryItem;
@class PKPaymentAuthorizationResult;
@class PKPaymentAuthorizationController;
@class PKPaymentRequestPaymentMethodUpdate;
@class PKPaymentRequestCouponCodeUpdate;
@class PKPaymentRequestShippingMethodUpdate;
@class PKPaymentRequestShippingContactUpdate;
@class PKPaymentRequestMerchantSessionUpdate;

@class PKDisbursementRequest;

@protocol PKPaymentAuthorizationControllerDelegate <NSObject>

@required

// Sent to the delegate when payment authorization is finished.  This may occur when
// the user cancels the request, or after the PKPaymentAuthorizationStatus parameter of the
// paymentAuthorizationController:didAuthorizePayment:completion: has been shown to the user.
//
// The delegate is responsible for dismissing and releasing the controller in this method.
- (void)paymentAuthorizationControllerDidFinish:(PKPaymentAuthorizationController *)controller NS_SWIFT_UI_ACTOR;

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
                               handler:(void (^)(PKPaymentAuthorizationResult *result))completion API_AVAILABLE(macos(11.0), ios(11.0), watchos(4.0)) NS_SWIFT_UI_ACTOR;

- (void)paymentAuthorizationController:(PKPaymentAuthorizationController *)controller
                   didAuthorizePayment:(PKPayment *)payment
                            completion:(void (^)(PKPaymentAuthorizationStatus status))completion API_DEPRECATED("Use paymentAuthorizationController:didAuthorizePayment:handler: instead to provide more granular errors", ios(10.0, 11.0), watchos(3.0, 4.0));

// Sent to the delegate before the payment is authorized, but after the user has authenticated using
// the side button. Optional.
- (void)paymentAuthorizationControllerWillAuthorizePayment:(PKPaymentAuthorizationController *)controller NS_SWIFT_UI_ACTOR;

- (void)paymentAuthorizationController:(PKPaymentAuthorizationController *)controller
       didRequestMerchantSessionUpdate:(void (^)(PKPaymentRequestMerchantSessionUpdate *update))handler API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0)) NS_SWIFT_ASYNC_NAME(paymentAuthorizationControllerDidRequestMerchantSessionUpdate(controller:)) NS_SWIFT_UI_ACTOR;

- (void)paymentAuthorizationController:(PKPaymentAuthorizationController *)controller
                   didChangeCouponCode:(NSString *)couponCode
                               handler:(void (^)(PKPaymentRequestCouponCodeUpdate *update))completion API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR;

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
                               handler:(void (^)(PKPaymentRequestShippingMethodUpdate *requestUpdate))completion API_AVAILABLE(macos(11.0), ios(11.0), watchos(4.0)) NS_SWIFT_UI_ACTOR;


- (void)paymentAuthorizationController:(PKPaymentAuthorizationController *)controller
              didSelectShippingContact:(PKContact *)contact
                               handler:(void (^)(PKPaymentRequestShippingContactUpdate *requestUpdate))completion API_AVAILABLE(macos(11.0), ios(11.0), watchos(4.0)) NS_SWIFT_UI_ACTOR;


// Sent when the user has selected a new payment card.  Use this delegate callback if you need to
// update the summary items in response to the card type changing (for example, applying credit card surcharges)
//
// The delegate will receive no further callbacks except paymentAuthorizationControllerDidFinish:
// until it has invoked the completion block.

- (void)paymentAuthorizationController:(PKPaymentAuthorizationController *)controller
                didSelectPaymentMethod:(PKPaymentMethod *)paymentMethod
                               handler:(void (^)(PKPaymentRequestPaymentMethodUpdate *requestUpdate))completion API_AVAILABLE(macos(11.0), ios(11.0), watchos(4.0)) NS_SWIFT_UI_ACTOR;

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

#if TARGET_OS_OSX || TARGET_OS_MACCATALYST
@required
#elif defined(TARGET_OS_VISION) && TARGET_OS_VISION
@required
#endif

#if TARGET_OS_OSX

- (nullable NSWindow *)presentationWindowForPaymentAuthorizationController:(PKPaymentAuthorizationController *)controller API_AVAILABLE(macos(11.0));

#else

- (nullable UIWindow *)presentationWindowForPaymentAuthorizationController:(PKPaymentAuthorizationController *)controller API_AVAILABLE(ios(14.0), watchos(7.0));

#endif

@end

// PKPaymentAuthorizationController prompts the user to authorize a PKPaymentRequest, funding the
// payment amount with a valid payment card.
API_AVAILABLE(macos(11.0), ios(10.0), watchos(3.0)) API_UNAVAILABLE(tvos)
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

// Determine whether this device can process disbursement requests.
+ (BOOL)supportsDisbursements API_AVAILABLE(ios(17.0), macos(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

// Determine whether this device can process disbursement requests using specific payment network brands.
+ (BOOL)supportsDisbursementsUsingNetworks:(NSArray<PKPaymentNetwork> *)supportedNetworks NS_SWIFT_NAME(supportsDisbursements(using:)) API_AVAILABLE(ios(17.0), macos(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

// Determine whether this device can process disbursements to cards issued in any of the indicated regions using the specified networks and capabilities bitmask.
// supportedRegions is a list of ISO 3166 country codes. Duplicates are ignored.
+ (BOOL)supportsDisbursementsUsingNetworks:(NSArray<PKPaymentNetwork> *)supportedNetworks
                              capabilities:(PKMerchantCapability)capabilties NS_SWIFT_NAME(supportsDisbursements(using:capabilities:)) API_AVAILABLE(ios(17.0), macos(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

// Initialize the controller with a request to send money to a user.
- (instancetype)initWithDisbursementRequest:(PKDisbursementRequest *)request API_AVAILABLE(ios(17.0), macos(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

#endif // TARGET_OS_IPHONE
#endif

#else
#import <TargetConditionals.h>
#if TARGET_OS_OSX 
#import <PassKitMacHelperTemp/PKPaymentAuthorizationController.h> 
#else 
#import <PassKitUI/PKPaymentAuthorizationController.h> 
#endif
#endif