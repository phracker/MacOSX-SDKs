//
//  PKAddPaymentPassViewController.h
//  PassKit
//
//  Copyright © 2015 Apple, Inc. All rights reserved.
//

#if TARGET_OS_IPHONE

#import <UIKit/UIKit.h>
#import <PassKit/PKAddPaymentPassRequest.h>
#import <PassKit/PKConstants.h>
#import <PassKit/PKError.h>

NS_ASSUME_NONNULL_BEGIN

@class PKAddPaymentPassViewController, PKPaymentPass;

@protocol PKAddPaymentPassViewControllerDelegate<NSObject>

/* Certificates is an array of NSData, each a DER encoded X.509 certificate, with the leaf first and root last.
 * The continuation handler must be called within 20 seconds or an error will be displayed. 
 * Subsequent to timeout, the continuation handler is invalid and invocations will be ignored.
 */
- (void)addPaymentPassViewController:(PKAddPaymentPassViewController *)controller
 generateRequestWithCertificateChain:(NSArray<NSData *> *)certificates
                               nonce:(NSData *)nonce
                      nonceSignature:(NSData *)nonceSignature
                   completionHandler:(void(^)(PKAddPaymentPassRequest *request))handler;

/* Error parameter will use codes from the PKAddPaymentPassError enumeration, using the PKPassKitErrorDomain domain.
 */
- (void)addPaymentPassViewController:(PKAddPaymentPassViewController *)controller didFinishAddingPaymentPass:(nullable PKPaymentPass *)pass error:(nullable NSError *)error;

@end

API_AVAILABLE(ios(9.0))
@interface PKAddPaymentPassViewController : UIViewController

+ (BOOL)canAddPaymentPass;

/* This controller should be presented with -[UIViewController presentViewController:animated:completion:].
 */
- (nullable instancetype)initWithRequestConfiguration:(PKAddPaymentPassRequestConfiguration *)configuration
                                             delegate:(nullable id<PKAddPaymentPassViewControllerDelegate>)delegate NS_DESIGNATED_INITIALIZER;

@property (nonatomic, weak, nullable) id<PKAddPaymentPassViewControllerDelegate> delegate;

@end

NS_ASSUME_NONNULL_END

#endif
