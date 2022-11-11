//
//  PKIssuerProvisioningExtensionPaymentPassEntry.h
//  PassKit
//
//  Copyright © 2020 Apple, Inc. All rights reserved.
//
#import <PassKit/PKIssuerProvisioningExtensionPassEntry.h>

NS_ASSUME_NONNULL_BEGIN

@class PKAddPaymentPassRequestConfiguration;

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos)
@interface PKIssuerProvisioningExtensionPaymentPassEntry : PKIssuerProvisioningExtensionPassEntry

- (nullable instancetype)initWithIdentifier:(NSString *)identifier
                                      title:(NSString *)title
                                        art:(CGImageRef)art
                    addRequestConfiguration:(PKAddPaymentPassRequestConfiguration *)configuration NS_DESIGNATED_INITIALIZER
  NS_SWIFT_NAME(init(identifier:title:art:addRequestConfiguration:));

@property (nonatomic, readonly) PKAddPaymentPassRequestConfiguration *addRequestConfiguration;

@end

NS_ASSUME_NONNULL_END
