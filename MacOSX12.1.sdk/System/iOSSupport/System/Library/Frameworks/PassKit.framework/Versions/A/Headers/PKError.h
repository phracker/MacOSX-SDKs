//
//  PKError.h
//  PassKit
//
//  Copyright (c) 2011 Apple, Inc. All rights reserved.
//

#ifndef __PKERROR_H
#define __PKERROR_H

#import <PassKit/PKConstants.h>

NS_ASSUME_NONNULL_BEGIN

// PKPassKitErrorDomain is used for generic errors with PassKit, such as
// adding or removing passes from the user's pass library. PassKit returns these errors to you.
extern NSString * const PKPassKitErrorDomain API_AVAILABLE(ios(6.0), watchos(3.0));


typedef NS_ERROR_ENUM(PKPassKitErrorDomain, PKPassKitErrorCode) {
    PKUnknownError = -1,
    PKInvalidDataError = 1,
    PKUnsupportedVersionError,
    PKInvalidSignature,
    PKNotEntitledError
} API_AVAILABLE(ios(6.0), watchos(3.0));


// PKPaymentErrorDomain is used for errors with in-app or web payments.
// You create your own PKPaymentErrors and return them to indicate problems with a purchase
extern NSString * const PKPaymentErrorDomain API_AVAILABLE(ios(11.0), watchos(4.0));

typedef NS_ERROR_ENUM(PKPaymentErrorDomain, PKPaymentErrorCode) {
    PKPaymentUnknownError = -1,                        // there was an unknown error processing the payment. The user should try again.
    PKPaymentShippingContactInvalidError = 1,          // the user's contact information has an error. Use the PKPaymentErrorKeys in the userInfo to detail the problem.
    PKPaymentBillingContactInvalidError,               // the user's billing contact information has an error. Use the PKPaymentErrorKeys in the userInfo to detail the problem.
    PKPaymentShippingAddressUnserviceableError,         // the user's shipping address is otherwise valid but not serviceable. For example, the address is in Canada and you only ship to the United States, or you don't deliver to PO Boxes.
    PKPaymentCouponCodeInvalidError API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos), // The coupon code entered by the user is invalid.
    PKPaymentCouponCodeExpiredError API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos), // The coupon code entered by the user has expired.
} API_AVAILABLE(ios(11.0), watchos(4.0));

typedef NSString * PKPaymentErrorKey NS_STRING_ENUM;
extern PKPaymentErrorKey const PKPaymentErrorContactFieldUserInfoKey  API_AVAILABLE(ios(11.0), watchos(4.0)); // a PKContactField the error relates to. Use with PKPaymentShippingContactInvalidError
extern PKPaymentErrorKey const PKPaymentErrorPostalAddressUserInfoKey API_AVAILABLE(ios(11.0), watchos(4.0)); // if the error relates to PKContactFieldPostalAddress you may set the specific key here

typedef NS_ENUM(NSInteger, PKAddPaymentPassError) {
    PKAddPaymentPassErrorUnsupported,
    PKAddPaymentPassErrorUserCancelled,
    PKAddPaymentPassErrorSystemCancelled
} API_AVAILABLE(ios(9.0), watchos(6.0));

extern NSString * const PKAddSecureElementPassErrorDomain API_AVAILABLE(ios(13.4));

typedef NS_ERROR_ENUM(PKAddSecureElementPassErrorDomain, PKAddSecureElementPassErrorCode) {
    PKAddSecureElementPassUnknownError,
    PKAddSecureElementPassUserCanceledError,
    PKAddSecureElementPassUnavailableError,
    PKAddSecureElementPassInvalidConfigurationError,
    PKAddSecureElementPassDeviceNotSupportedError,
    PKAddSecureElementPassDeviceNotReadyError,
} API_AVAILABLE(ios(13.4));

NS_ASSUME_NONNULL_END
#endif // __PKERROR_H
