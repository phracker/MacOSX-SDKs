//
//  SKError.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN NSString * const SKErrorDomain API_AVAILABLE(ios(3.0), macos(10.7));

// error codes for the SKErrorDomain
typedef NS_ENUM(NSInteger,SKErrorCode) {
    SKErrorUnknown,
    SKErrorClientInvalid,                                                                         // client is not allowed to issue the request, etc.
    SKErrorPaymentCancelled,                                                                      // user cancelled the request, etc.
    SKErrorPaymentInvalid,                                                                        // purchase identifier was invalid, etc.
    SKErrorPaymentNotAllowed,                                                                     // this device is not allowed to make the payment
    SKErrorStoreProductNotAvailable API_AVAILABLE(ios(3.0), macos(10.15)),                        // Product is not available in the current storefront
    SKErrorCloudServicePermissionDenied API_AVAILABLE(ios(9.3)) API_UNAVAILABLE(macos),           // user has not allowed access to cloud service information
    SKErrorCloudServiceNetworkConnectionFailed API_AVAILABLE(ios(9.3)) API_UNAVAILABLE(macos),    // the device could not connect to the nework
    SKErrorCloudServiceRevoked API_AVAILABLE(ios(10.3)) API_UNAVAILABLE(macos),                   // user has revoked permission to use this cloud service
    SKErrorPrivacyAcknowledgementRequired API_AVAILABLE(ios(12.2), macos(10.14.4)),               // The user needs to acknowledge Apple's privacy policy
    SKErrorUnauthorizedRequestData API_AVAILABLE(ios(12.2), macos(10.14.4)),                      // The app is attempting to use SKPayment's requestData property, but does not have the appropriate entitlement
    SKErrorInvalidOfferIdentifier API_AVAILABLE(ios(12.2), macos(10.14.4)),                       // The specified subscription offer identifier is not valid
    SKErrorInvalidSignature API_AVAILABLE(ios(12.2), macos(10.14.4)),                             // The cryptographic signature provided is not valid
    SKErrorMissingOfferParams API_AVAILABLE(ios(12.2), macos(10.14.4)),                           // One or more parameters from SKPaymentDiscount is missing
    SKErrorInvalidOfferPrice API_AVAILABLE(ios(12.2), macos(10.14.4))                             // The price of the selected offer is not valid (e.g. lower than the current base subscription price)
} API_AVAILABLE(ios(3.0), macos(10.7));

NS_ASSUME_NONNULL_END
