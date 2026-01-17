#if (!__has_include(<PassKitUI/PKPaymentAuthorizationViewController.h>) && !__has_include(<PassKitMacHelperTemp/PKPaymentAuthorizationViewController.h>)) || PK_USE_PUBLIC_PASSKIT
//
//  PKPaymentAuthorizationViewController.h
//    PassKit
//
//  Copyright (c) 2014 Apple, Inc. All rights reserved.
//

#ifndef __PKPAYMENTAUTHORIZATIONVIEWCONTROLLER_H
#define __PKPAYMENTAUTHORIZATIONVIEWCONTROLLER_H

#import <TargetConditionals.h>

#if !TARGET_OS_WATCH

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

#import <PassKit/PKConstants.h>
#import <PassKit/PKPaymentRequest.h>
#if TARGET_OS_OSX
#import <PassKit/PKPaymentAuthorizationViewControllerDelegate.h>
#else
#import <PassKit/PKPaymentAuthorizationViewControllerDelegate.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@class PKPayment;
@class PKContact;
@class PKPaymentMethod;
@class PKShippingMethod;
@class PKPaymentSummaryItem;
@class PKPaymentAuthorizationResult;
@class PKPaymentRequestPaymentMethodUpdate;
@class PKPaymentRequestShippingMethodUpdate;
@class PKPaymentRequestShippingContactUpdate;

@class PKDisbursementRequest;

// PKPaymentAuthorizationViewController prompts the user to authorize a PKPaymentRequest, funding the
// payment amount with a valid payment card.
#if TARGET_OS_IPHONE
API_AVAILABLE(ios(8.0))
@interface PKPaymentAuthorizationViewController : UIViewController
#else
NS_CLASS_AVAILABLE_MAC(11_0)
@interface PKPaymentAuthorizationViewController : NSViewController
#endif

// Determine whether this device can process payment requests.
// YES if the device is generally capable of making in-app payments.
// NO if the device cannot make in-app payments or if the user is restricted from authorizing payments.
+ (BOOL)canMakePayments NS_SWIFT_NONISOLATED;

// Determine whether this device can process payment requests using specific payment network brands.
// Your application should confirm that the user can make payments before attempting to authorize a payment.
// Your application may also want to alter its appearance or behavior when the user is not allowed
// to make payments.
// YES if the user can authorize payments on this device using one of the payment networks supported
// by the merchant.
// NO if the user cannot authorize payments on these networks or if the user is restricted from
// authorizing payments.
+ (BOOL)canMakePaymentsUsingNetworks:(NSArray<PKPaymentNetwork> *)supportedNetworks NS_SWIFT_NONISOLATED;

// Determine whether this device can process payments using the specified networks and capabilities bitmask
// See -canMakePaymentsUsingNetworks:
+ (BOOL)canMakePaymentsUsingNetworks:(NSArray<PKPaymentNetwork> *)supportedNetworks capabilities:(PKMerchantCapability)capabilties API_AVAILABLE(macos(11.0), ios(9.0)) NS_SWIFT_NONISOLATED;

// The view controller's delegate.
@property (nonatomic, weak, nullable) id<PKPaymentAuthorizationViewControllerDelegate> delegate;

// Initializes and returns a newly created view controller for the supplied payment.
// It is your responsibility to present and dismiss the view controller using the
// appropriate means for the given device idiom.
- (nullable instancetype)initWithPaymentRequest:(PKPaymentRequest *)request NS_DESIGNATED_INITIALIZER;

// Determine whether this device can process disbursement requests.
+ (BOOL)supportsDisbursements API_AVAILABLE(ios(17.0), macos(15.0))  NS_SWIFT_NONISOLATED API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

// Determine whether this device can process disbursement requests using specific payment network brands.
+ (BOOL)supportsDisbursementsUsingNetworks:(NSArray<PKPaymentNetwork> *)supportedNetworks  NS_SWIFT_NONISOLATED NS_SWIFT_NAME(supportsDisbursements(using:)) API_AVAILABLE(ios(17.0), macos(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

// Determine whether this device can process disbursements to cards using the specified networks and capabilities bitmask.
+ (BOOL)supportsDisbursementsUsingNetworks:(NSArray<PKPaymentNetwork> *)supportedNetworks
                              capabilities:(PKMerchantCapability)capabilities  NS_SWIFT_NONISOLATED NS_SWIFT_NAME(supportsDisbursements(using:capabilities:)) API_AVAILABLE(ios(17.0), macos(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

// Initialize the controller with a request to send money to a user.
- (instancetype)initWithDisbursementRequest:(PKDisbursementRequest *)request API_AVAILABLE(ios(17.0), macos(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

#endif
#endif

#else
#import <TargetConditionals.h>
#if TARGET_OS_OSX 
#import <PassKitMacHelperTemp/PKPaymentAuthorizationViewController.h> 
#else 
#import <PassKitUI/PKPaymentAuthorizationViewController.h> 
#endif
#endif