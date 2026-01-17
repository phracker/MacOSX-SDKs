#if !__has_include(<PassKitCore/PKError.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKError.h
//    PassKit
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

// PKDisbursementErrorDomain is used for errors with in-app disbursements.
// You create your own PKDisbursementErrors and return them to indicate problems with a transfer.
extern NSString * const PKDisbursementErrorDomain API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos, tvos);

typedef NS_ERROR_ENUM(PKDisbursementErrorDomain, PKDisbursementErrorCode) {
    PKDisbursementUnknownError = -1,               // there was an unknown error processing the disbursement. The user should try again.
    PKDisbursementUnsupportedCardError = 1,        // the selected card does not support receiving funds in.
    PKDisbursementRecipientContactInvalidError,    // the recipient contact information has an error. Use the PKDisbursementErrorKeys in the userInfo to detail the problem.
} API_AVAILABLE(macos(15.0),ios(17.0)) API_UNAVAILABLE(watchos, tvos);

typedef NSString * PKDisbursementErrorKey NS_STRING_ENUM;
extern PKDisbursementErrorKey const PKDisbursementErrorContactFieldUserInfoKey  API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos, tvos); // a PKContactField the error relates to. Use with PKDisbursementRecipientContactInvalidError

typedef NS_ENUM(NSInteger, PKAddPaymentPassError) {
    PKAddPaymentPassErrorUnsupported,
    PKAddPaymentPassErrorUserCancelled,
    PKAddPaymentPassErrorSystemCancelled
} API_AVAILABLE(ios(9.0), watchos(6.0));

extern NSString * const PKAddSecureElementPassErrorDomain API_AVAILABLE(ios(13.4));

typedef NS_ERROR_ENUM(PKAddSecureElementPassErrorDomain, PKAddSecureElementPassErrorCode) {
    PKAddSecureElementPassGenericError API_AVAILABLE(ios(18.0)) = 0,
    PKAddSecureElementPassUnknownError API_DEPRECATED("Use PKAddSecureElementPassGenericError instead.", ios(13.4, 18.0)) = PKAddSecureElementPassGenericError,
    PKAddSecureElementPassUserCanceledError,
    PKAddSecureElementPassUnavailableError,
    PKAddSecureElementPassInvalidConfigurationError,
    PKAddSecureElementPassDeviceNotSupportedError,
    PKAddSecureElementPassDeviceNotReadyError,
    PKAddSecureElementPassOSVersionNotSupportedError,
} API_AVAILABLE(ios(13.4));

extern NSString * const PKShareSecureElementPassErrorDomain API_AVAILABLE(ios(16.0));

typedef NS_ERROR_ENUM(PKShareSecureElementPassErrorDomain, PKShareSecureElementPassErrorCode) {
    PKShareSecureElementPassUnknownError,
    // Unable to present share pass UI. This generally occurs when your app isn't entitled to the pass
    // or the pass isn't shareable.
    PKShareSecureElementPassSetupError,

} API_AVAILABLE(ios(16.0));

NS_ASSUME_NONNULL_END
#endif // __PKERROR_H

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKError.h>
#endif