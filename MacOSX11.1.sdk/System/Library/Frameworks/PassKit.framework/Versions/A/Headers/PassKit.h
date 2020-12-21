//
//  PassKit.h
//  PassKit
//
//  Copyright (c) 2011 Apple, Inc. All rights reserved.
//

#import <PassKit/PKConstants.h>
#import <PassKit/PKObject.h>
#import <PassKit/PKPass.h>
#import <PassKit/PKSecureElementPass.h>
#import <PassKit/PKPaymentPass.h>
#import <PassKit/PKError.h>
#import <PassKit/PKPassLibrary.h>
#if __has_include(<PassKit/PKLabeledValue.h>)
#import <PassKit/PKLabeledValue.h>
#endif
#import <PassKit/PKContact.h>
#if __has_include(<PassKit/PKTransitPassProperties.h>)
#import <PassKit/PKTransitPassProperties.h>
#endif
#if __has_include(<PassKit/PKSuicaPassProperties.h>)
#import <PassKit/PKSuicaPassProperties.h>
#endif
#if __has_include(<PassKit/PKPaymentRequest.h>)
#import <PassKit/PKPaymentRequest.h>
#endif
#if __has_include(<PassKit/PKPaymentRequestStatus.h>)
#import <PassKit/PKPaymentRequestStatus.h>
#endif
#if __has_include(<PassKit/PKPayment.h>)
#import <PassKit/PKPayment.h>
#endif
#if __has_include(<PassKit/PKPaymentMethod.h>)
#import <PassKit/PKPaymentMethod.h>
#endif
#if __has_include(<PassKit/PKPaymentToken.h>)
#import <PassKit/PKPaymentToken.h>
#endif
#if TARGET_OS_IPHONE || TARGET_OS_OSX
#if __has_include(<PassKit/PKPaymentAuthorizationViewController.h>)
#import <PassKit/PKPaymentAuthorizationViewController.h>
#endif
#if __has_include(<PassKit/PKPaymentAuthorizationController.h>)
#import <PassKit/PKPaymentAuthorizationController.h>
#endif
#if __has_include(<PassKit/PKAddPassButton.h>)
#import <PassKit/PKAddPassButton.h>
#endif
#if __has_include(<PassKit/PKPaymentButton.h>)
#import <PassKit/PKPaymentButton.h>
#endif
#if __has_include(<PassKit/PKAddPassesViewController.h>)
#import <PassKit/PKAddPassesViewController.h>
#endif
#if __has_include(<PassKit/PKAddPaymentPassRequest.h>)
#import <PassKit/PKAddPaymentPassRequest.h>
#endif
#if __has_include(<PassKit/PKAddPaymentPassViewController.h>)
#import <PassKit/PKAddPaymentPassViewController.h>
#endif
#if __has_include(<PassKit/PKDisbursementVoucher.h>)
#import <PassKit/PKDisbursementVoucher.h>
#endif
#if __has_include(<PassKit/PKDisbursementRequest.h>)
#import <PassKit/PKDisbursementRequest.h>
#endif
#if __has_include(<PassKit/PKDisbursementAuthorizationController.h>)
#import <PassKit/PKDisbursementAuthorizationController.h>
#endif
#if __has_include(<PassKit/PKPaymentInformationEventExtension.h>)
#import <PassKit/PKPaymentInformationEventExtension.h>
#endif
#if __has_include(<PassKit/PKBarcodeEventMetadataRequest.h>)
#import <PassKit/PKBarcodeEventMetadataRequest.h>
#endif
#if __has_include(<PassKit/PKAddSecureElementPassViewController.h>)
#import <PassKit/PKAddSecureElementPassViewController.h>
#endif
#if __has_include(<PassKit/PKAddSecureElementPassConfiguration.h>)
#import <PassKit/PKAddSecureElementPassConfiguration.h>
#endif
#if __has_include(<PassKit/PKAddCarKeyPassConfiguration.h>)
#import <PassKit/PKAddCarKeyPassConfiguration.h>
#endif
#if __has_include(<PassKit/PKPaymentMerchantSession.h>)
#import <PassKit/PKPaymentMerchantSession.h>
#endif
#if __has_include(<PassKit/PKAddShareablePassConfiguration.h>)
#import <PassKit/PKAddShareablePassConfiguration.h>
#endif
#if __has_include(<PassKit/PKIssuerProvisioningExtensionAuthorizationProviding.h>)
#import <PassKit/PKIssuerProvisioningExtensionAuthorizationProviding.h>
#endif
#if __has_include(<PassKit/PKIssuerProvisioningExtensionHandler.h>)
#import <PassKit/PKIssuerProvisioningExtensionHandler.h>
#endif
#if __has_include(<PassKit/PKIssuerProvisioningExtensionStatus.h>)
#import <PassKit/PKIssuerProvisioningExtensionStatus.h>
#endif
#if __has_include(<PassKit/PKIssuerProvisioningExtensionPassEntry.h>)
#import <PassKit/PKIssuerProvisioningExtensionPassEntry.h>
#endif
#if __has_include(<PassKit/PKIssuerProvisioningExtensionPaymentPassEntry.h>)
#import <PassKit/PKIssuerProvisioningExtensionPaymentPassEntry.h>
#endif
#endif // TARGET_OS_IPHONE || TARGET_OS_OSX
