//
//  TKTokenKeychainItem.h
//  Copyright © 2015-2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CryptoTokenKit/TKToken.h>

NS_ASSUME_NONNULL_BEGIN

@class TKTokenKeychainItem;
@class TKTokenKeychainCertificate;
@class TKTokenKeychainKey;
@class TKTokenKeychainState;

/*!
 @interface TKTokenKeychainItem
 @brief Base interface for propagation token's items into the keychain.
 */
API_AVAILABLE(macos(10.12), ios(10.0), tvos(11.0), watchos(4.0))
@interface TKTokenKeychainItem : NSObject

/*! @brief Initializes item with objectID. */
- (instancetype)initWithObjectID:(TKTokenObjectID)objectID NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

/*! @brief object ID for item identification */
@property (readonly, copy) TKTokenObjectID objectID;

/*!
 @discussion Contains the user-visible label for this item.  This property is an equivalent of kSecAttrLabel in SecItem.h
 */
@property (nullable, copy) NSString *label;

/*!
 @discussion Contains access constraints for this object keyed by TKTOpenOperation wrapped in NSNumber.
 */
@property (nullable, copy) NSDictionary<NSNumber *, TKTokenOperationConstraint> *constraints;

@end

/*!
 @interface TKTokenKeychainCertificate
 @brief Interface for propagation token's certificates into the keychain.
 */
API_AVAILABLE(macos(10.12), ios(10.0), tvos(11.0), watchos(4.0))
@interface TKTokenKeychainCertificate : TKTokenKeychainItem

/*!
 @discussion initialize TKTokenKeychainCertificate with data from SecCertificateRef.  Use SecCertificateCreateWithData to obtain SecCertificateRef.  @c constraints property is initialized indicating that reading of certificate is always allowed, all other operations are disallowed.
 */
- (nullable instancetype)initWithCertificate:(SecCertificateRef)certificateRef objectID:(TKTokenObjectID)objectID NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithObjectID:(TKTokenObjectID)objectID NS_UNAVAILABLE;

/*!
 @discussion Contains DER-encoded representation of an X.509 certificate.
 */
@property (copy, readonly) NSData *data;

@end

/*!
 @interface TKTokenKeychainKey
 @brief Interface for propagation token's keys into the keychain.
 */
API_AVAILABLE(macos(10.12), ios(10.0), tvos(11.0), watchos(4.0))
@interface TKTokenKeychainKey : TKTokenKeychainItem

/*!
 @discussion Initialize TKTokenKeychainKey with informations from SecCertificateRef associated with the key.  Use SecCertificateCreateWithData to obtain SecCertificateRef.  If NULL is passed instead of certificate, all properties of created instance must be initialized manually.
 */
- (nullable instancetype)initWithCertificate:(nullable SecCertificateRef)certificateRef objectID:(TKTokenObjectID)objectID NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithObjectID:(TKTokenObjectID)objectID NS_UNAVAILABLE;

/*!
 @discussion Type of the key, currently kSecAttrKeyTypeRSA and kSecAttrKeyTypeECSECPrimeRandom is supported).  The property is an equivalent to kSecAttrKeyType in SecItem.h
 */
@property (copy) NSString *keyType;

/*!
 @discussion Represents private tag data.  The property is an equivalent to kSecAttrApplicationTag in SecItem.h
 */
@property (copy, nullable) NSData *applicationTag;

/*!
 @discussion Indicates the number of bits in this key.  The property is an equivalent to kSecAttrKeySizeInBits in SecItem.h
 */
@property NSInteger keySizeInBits;

/*!
 @discussion Contains raw public key data for this private key.
 */
@property (copy, nullable) NSData *publicKeyData;

/*!
 @discussion SHA1 hash of the raw public key.  The property is an equivalent to kSecAttrApplicationLabel in SecItem.h
 */
@property (copy, nullable) NSData *publicKeyHash;

/*!
 @discussion Indicates whether this key can be used to decrypt data.  The property is an equivalent to kSecAttrCanDecrypt in SecItem.h
 */
@property BOOL canDecrypt;

/*!
 @discussion Indicates whether this key can be used to create a digital signature.  The property is an equivalent to kSecAttrCanSign in SecItem.h
 */
@property BOOL canSign;

/*!
 @discussion Indicates whether this key can be used to perform Diffie-Hellman style cryptographic key exchange.
 */
@property BOOL canPerformKeyExchange;

/*!
 @discussion Indicates whether this key can be used for login in to the system.
 */
@property (getter=isSuitableForLogin) BOOL suitableForLogin;

@end

/*!
 @discussion Contains TKTokenKeychainItem instances (keys and certificates) which represent keychain state (i.e. set of items) of specific token.
 */
API_AVAILABLE(macos(10.12), ios(10.0), tvos(11.0), watchos(4.0))
@interface TKTokenKeychainContents : NSObject

/*!
 @discussion Fills keychain with the set of specified items.  All items belonging to token are first removed from the keychain and then the keychain is populated with new items.
 @param items New items to be stored into the keychain.
 */
- (void)fillWithItems:(NSArray<TKTokenKeychainItem *> *)items;

/*! @brief All items related to this token in the keychain. */
@property (readonly, copy) NSArray<TKTokenKeychainItem *> *items;

/*!
 @discussion Returns key with specified objectID.  Fills error with TKTokenErrorCodeObjectNotFound if no such key exists.
 */
- (nullable TKTokenKeychainKey *)keyForObjectID:(TKTokenObjectID)objectID error:(NSError **)error;

/*!
 @discussion Returns certificate with specified objectID.  Fills error with TKTokenErrorCodeObjectNotFound if no such certificate exists.
 */
- (nullable TKTokenKeychainCertificate *)certificateForObjectID:(TKTokenObjectID)objectID error:(NSError **)error;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
