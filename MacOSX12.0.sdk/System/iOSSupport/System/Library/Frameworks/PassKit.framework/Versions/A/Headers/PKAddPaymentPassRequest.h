//
//  PKAddPaymentPassRequest.h
//  PassKit
//
//  Copyright © 2018 Apple, Inc. All rights reserved.
//

#ifndef __PKADDPAYMENTPASSREQUEST_H
#define __PKADDPAYMENTPASSREQUEST_H

#import <Foundation/Foundation.h>
#import <PassKit/PKConstants.h>

NS_ASSUME_NONNULL_BEGIN

@class PKLabeledValue;

typedef NS_ENUM(NSInteger, PKAddPaymentPassStyle) {
    PKAddPaymentPassStylePayment,
    PKAddPaymentPassStyleAccess
} API_AVAILABLE(ios(12.0), watchos(5.0));

API_AVAILABLE(ios(9.0), watchos(2.0))
@interface PKAddPaymentPassRequestConfiguration : NSObject

/* Schemes defined in PKConstants.h.
 * Supported Schemes:
 *  PKEncryptionSchemeECC_V2:
 *      ephemeralPublicKey
 *  PKEncryptionSchemeRSA_V2:
 *      wrappedKey
 */
- (nullable instancetype)initWithEncryptionScheme:(PKEncryptionScheme)encryptionScheme NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy, readonly) PKEncryptionScheme encryptionScheme;

/* Display Properties:
 *  At least one of cardholder name or primary account suffix must be supplied.
 */
@property (nonatomic, assign) PKAddPaymentPassStyle style API_AVAILABLE(ios(12.0), watchos(5.0));
@property (nonatomic, copy, nullable) NSString *cardholderName;
@property (nonatomic, copy, nullable) NSString *primaryAccountSuffix;

@property (nonatomic, copy) NSArray<PKLabeledValue *> *cardDetails API_AVAILABLE(ios(10.1), watchos(3.1));

@property (nonatomic, copy, nullable) NSString *localizedDescription;

/* Pass Library Filters:
 *  If the filtered set is empty, then all filter will be ignored.
 */
@property (nonatomic, copy, nullable) NSString *primaryAccountIdentifier;

/* Filters introduction page to a specific network - does not function as a restriction.
 */
@property (nonatomic, copy, nullable) PKPaymentNetwork paymentNetwork;

/* Filters introduction page to a specific set of images - does not function as a restriction.
 */
@property (nonatomic, copy) NSSet<NSString *> *productIdentifiers API_AVAILABLE(ios(12.3), watchos(5.3));

@property (nonatomic, assign) BOOL requiresFelicaSecureElement API_AVAILABLE(ios(10.1), watchos(3.1));

@end

API_AVAILABLE(ios(9.0), watchos(2.0))
@interface PKAddPaymentPassRequest : NSObject

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy, nullable) NSData *encryptedPassData;
@property (nonatomic, copy, nullable) NSData *activationData;

/* Scheme dependent properties:
 */
@property (nonatomic, copy, nullable) NSData *ephemeralPublicKey;
@property (nonatomic, copy, nullable) NSData *wrappedKey;

@end

NS_ASSUME_NONNULL_END

#endif
