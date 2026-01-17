#if !__has_include(<PassKitCore/PKIssuerProvisioningExtensionHandler.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKIssuerProvisioningExtensionHandler.h
//    PassKit
//
//  Copyright © 2020 Apple, Inc. All rights reserved.
//
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class PKIssuerProvisioningExtensionStatus, PKIssuerProvisioningExtensionPassEntry, PKAddPaymentPassRequestConfiguration, PKAddPaymentPassRequest;

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos, macos)
@interface PKIssuerProvisioningExtensionHandler : NSObject

- (void)statusWithCompletion:(void(^)(PKIssuerProvisioningExtensionStatus *status))completion;

- (void)passEntriesWithCompletion:(void(^)(NSArray<PKIssuerProvisioningExtensionPassEntry *> *entries))completion;
- (void)remotePassEntriesWithCompletion:(void(^)(NSArray<PKIssuerProvisioningExtensionPassEntry *> *entries))completion;

/* Certificates is an array of NSData, each a DER encoded X.509 certificate, with the leaf first and root last.
 * The continuation handler must be called within 20 seconds or an error will be displayed. 
 * Subsequent to timeout, the continuation handler is invalid and invocations will be ignored.
 */
- (void)generateAddPaymentPassRequestForPassEntryWithIdentifier:(NSString *)identifier
                                                  configuration:(PKAddPaymentPassRequestConfiguration *)configuration
                                               certificateChain:(NSArray<NSData *> *)certificates
                                                          nonce:(NSData *)nonce
                                                 nonceSignature:(NSData *)nonceSignature
                                              completionHandler:(void(^)(PKAddPaymentPassRequest * _Nullable request))completion
  NS_SWIFT_NAME(generateAddPaymentPassRequestForPassEntryWithIdentifier(_:configuration:certificateChain:nonce:nonceSignature:completionHandler:));

@end

NS_ASSUME_NONNULL_END

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKIssuerProvisioningExtensionHandler.h>
#endif