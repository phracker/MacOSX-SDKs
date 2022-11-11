//
//  PKPaymentInformationEventExtension.h
//  PassKit
//
//  Copyright © 2020 Apple, Inc. All rights reserved.
//

#import <PassKit/PKBarcodeEventMetadataRequest.h>

NS_ASSUME_NONNULL_BEGIN

typedef void (^PKInformationRequestCompletionBlock)(PKBarcodeEventMetadataResponse *);
typedef void (^PKSignatureRequestCompletionBlock)(PKBarcodeEventSignatureResponse *);

API_AVAILABLE(ios(14.0), watchos(7.0))
@interface PKPaymentInformationEventExtension : NSObject

@end

@protocol PKPaymentInformationRequestHandling
@required

- (void)handleInformationRequest:(PKBarcodeEventMetadataRequest *)infoRequest
                      completion:(PKInformationRequestCompletionBlock)completion;

- (void)handleSignatureRequest:(PKBarcodeEventSignatureRequest *)signatureRequest
                    completion:(PKSignatureRequestCompletionBlock)completion;

- (void)handleConfigurationRequest:(PKBarcodeEventConfigurationRequest *)configurationRequest
                        completion:(void (^)(void))completion;

@end

NS_ASSUME_NONNULL_END

