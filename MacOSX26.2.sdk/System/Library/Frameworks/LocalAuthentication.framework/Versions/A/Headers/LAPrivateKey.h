//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Security/SecKey.h>

NS_ASSUME_NONNULL_BEGIN

@class LAPublicKey;

/// @brief Managed Private Key.
API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(watchos, tvos)
@interface LAPrivateKey: NSObject

/// @brief Offers the public key counterpart of a @c LAPrivateKey instance
@property (nonatomic, readonly) LAPublicKey *publicKey;

/// @brief Generates a digital signature for the given data.
/// @param data The data to be signed, typically the digest of the actual data.
/// @param algorithm A  @c SecKeyAlgorithm suitable for generating signatures with this key – e.g: @c kSecKeyAlgorithmECDSASignatureMessageX962SHA256
/// @param handler Completion handler with the signature of given data or an error on failure.
- (void)signData:(NSData *)data secKeyAlgorithm:(SecKeyAlgorithm)algorithm completion:(void (NS_SWIFT_SENDABLE ^)(NSData *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(sign(_:algorithm:completion:));

/// @brief Checks if the the provided algorithm can be used for signing data
/// @param algorithm Cryptographic algorithm
/// @return @c YES in case the key supports the provided algorithm with the specified operation.
- (BOOL)canSignUsingSecKeyAlgorithm:(SecKeyAlgorithm)algorithm NS_SWIFT_NAME(canSign(using:));

/// @brief Decrypts the given ciphertext
/// @param data The data to decrypt. The length and format of the data must conform to chosen algorithm,
/// typically be less or equal to the value returned by SecKeyGetBlockSize().
/// @param algorithm A @c SecKeyAlgorithm suitable for decrypting data with this key –e.g: @c kSecKeyAlgorithmECIESEncryptionStandardVariableIVX963SHA256AESGCM
/// @param handler Completion handler with plaintext or an error on failure.
- (void)decryptData:(NSData *)data secKeyAlgorithm:(SecKeyAlgorithm)algorithm completion:(void (NS_SWIFT_SENDABLE ^)(NSData *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(decrypt(_:algorithm:completion:));

/// @brief Checks if the the provided algorithm can be used for decryption
/// @param algorithm Cryptographic algorithm
/// @return @c YES in case the key supports the provided algorithm with the specified operation.
- (BOOL)canDecryptUsingSecKeyAlgorithm:(SecKeyAlgorithm)algorithm NS_SWIFT_NAME(canDecrypt(using:));

/// @brief Performs a Diffie-Hellman style key exchange operation
/// @param publicKey Remote party's public key.
/// @param algorithm A @c SecKeyAlgorithm suitable for performing a key exchange with this key –e.g: @c kSecKeyAlgorithmECDHKeyExchangeCofactorX963SHA256
/// @param parameters Dictionary with parameters, see @c SecKeyKeyExchangeParameter constants.  Used algorithm determines the set of required and optional parameters to be used.
/// @param handler Completion handler with the result of the key exchange or an error on failure.
- (void)exchangeKeysWithPublicKey:(NSData *)publicKey secKeyAlgorithm:(SecKeyAlgorithm)algorithm secKeyParameters:(NSDictionary *)parameters completion:(void (NS_SWIFT_SENDABLE ^)(NSData *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(exchangeKeys(publicKey:algorithm:parameters:completion:));

/// @brief Checks if the the provided algorithm can be used for performing key exchanges
/// @param algorithm Cryptographic algorithm
/// @return @c YES in case the key supports the provided algorithm with the specified operation.
- (BOOL)canExchangeKeysUsingSecKeyAlgorithm:(SecKeyAlgorithm)algorithm NS_SWIFT_NAME(canExchangeKeys(using:));

/// @brief Clients cannot create @c LAPrivateKey instances directly. They typically obtain them from a @c LAPersistedRight instance.
+ (instancetype)new NS_UNAVAILABLE;

/// @brief Clients cannot create @c LAPrivateKey instances directly. They typically obtain them from a @c LAPersistedRight instance.
- (instancetype)init NS_UNAVAILABLE;
@end

NS_ASSUME_NONNULL_END
