//
//  PassKit.h
//  PassKit
//
//  Copyright (c) 2011 Apple, Inc. All rights reserved.
//

#import <PassKit/PKConstants.h>
#import <PassKit/PKObject.h>
#import <PassKit/PKPass.h>
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
#endif // TARGET_OS_IPHONE || TARGET_OS_OSX
