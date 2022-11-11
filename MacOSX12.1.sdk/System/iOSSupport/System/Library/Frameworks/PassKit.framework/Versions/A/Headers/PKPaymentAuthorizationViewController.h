//
//  PKPaymentAuthorizationViewController.h
//  PassKit
//
//  Copyright (c) 2014 Apple, Inc. All rights reserved.
//

#ifndef __PKPAYMENTAUTHORIZATIONVIEWCONTROLLER_H
#define __PKPAYMENTAUTHORIZATIONVIEWCONTROLLER_H

#import <TargetConditionals.h>

#if !TARGET_OS_WATCH && !TARGET_OS_TV

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#if !TARGET_OS_MACCATALYST
#import <AddressBook/ABRecord.h>
#endif
#else
#import <AppKit/AppKit.h>
#endif

#import <PassKit/PKConstants.h>
#import <PassKit/PKPaymentRequest.h>
#import <PassKit/PKPaymentAuthorizationViewControllerDelegate.h>

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
+ (BOOL)canMakePaymentsUsingNetworks:(NSArray<PKPaymentNetwork> *)supportedNetworks capabilities:(PKMerchantCapability)capabilties API_AVAILABLE(macos(11.0), ios(9.0));

// The view controller's delegate.
@property (nonatomic, weak, nullable) id<PKPaymentAuthorizationViewControllerDelegate> delegate;

// Initializes and returns a newly created view controller for the supplied payment.
// It is your responsibility to present and dismiss the view controller using the
// appropriate means for the given device idiom.
- (nullable instancetype)initWithPaymentRequest:(PKPaymentRequest *)request NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

#endif
#endif
