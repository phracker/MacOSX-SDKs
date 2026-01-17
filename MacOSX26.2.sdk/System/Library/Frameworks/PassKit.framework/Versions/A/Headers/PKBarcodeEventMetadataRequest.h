#if !__has_include(<PassKitCore/PKBarcodeEventMetadataRequest.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKBarcodeEventMetadataRequest.h
//    PassKit
//
//  Copyright © 2020 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0), watchos(7.0))
@interface PKBarcodeEventMetadataRequest : NSObject

@property (nonatomic, readonly, copy) NSString *deviceAccountIdentifier;
@property (nonatomic, readonly, copy) NSString *lastUsedBarcodeIdentifier;

@end

API_AVAILABLE(ios(14.0), watchos(7.0))
@interface PKBarcodeEventMetadataResponse : NSObject

- (instancetype)initWithPaymentInformation:(NSData *)paymentInformation;

@property (nonatomic, copy) NSData *paymentInformation;

@end

API_AVAILABLE(ios(14.0), watchos(7.0))
@interface PKBarcodeEventSignatureRequest : NSObject

@property (nonatomic, readonly, copy) NSString *deviceAccountIdentifier;
@property (nonatomic, readonly, copy) NSString *transactionIdentifier;
@property (nonatomic, readonly, copy) NSString *barcodeIdentifier;
@property (nonatomic, readonly, copy) NSString *rawMerchantName;
@property (nonatomic, readonly, copy) NSString *merchantName;
@property (nonatomic, readonly, strong) NSDate *transactionDate;
@property (nonatomic, readonly, copy) NSString *currencyCode;
@property (nonatomic, readonly, strong) NSNumber *amount;
@property (nonatomic, readonly, copy) NSString *transactionStatus;
@property (nonatomic, readonly, copy) NSData *partialSignature;

@end

API_AVAILABLE(ios(14.0), watchos(7.0))
@interface PKBarcodeEventSignatureResponse : NSObject

- (instancetype)initWithSignedData:(NSData *)signedData;

@property (nonatomic, copy) NSData *signedData;

@end

typedef NS_ENUM(NSInteger, PKBarcodeEventConfigurationDataType) {
    PKBarcodeEventConfigurationDataTypeUnknown,
    PKBarcodeEventConfigurationDataTypeSigningKeyMaterial,
    PKBarcodeEventConfigurationDataTypeSigningCertificate
} API_AVAILABLE(ios(14.0), watchos(7.0));

API_AVAILABLE(ios(14.0), watchos(7.0))
@interface PKBarcodeEventConfigurationRequest : NSObject

@property (nonatomic, readonly) NSString *deviceAccountIdentifier;
@property (nonatomic, readonly) NSData *configurationData;
@property (nonatomic, readonly) PKBarcodeEventConfigurationDataType configurationDataType;

@end

NS_ASSUME_NONNULL_END


#else
#import <TargetConditionals.h>
#import <PassKitCore/PKBarcodeEventMetadataRequest.h>
#endif