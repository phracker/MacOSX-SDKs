//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Security/SecKey.h>

NS_ASSUME_NONNULL_BEGIN

/// @brief The public part of an asymmetric key pair
API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(watchos, tvos)
@interface LAPublicKey: NSObject

/// @brief Exports public key bytes.
/// @param handler Completion handler with the raw bytes of the public key or an error on failure
- (void)exportBytesWithCompletion:(void (NS_SWIFT_SENDABLE ^)(NSData *_Nullable, NSError *_Nullable))handler NS_SWIFT_ASYNC_NAME(getter:bytes());

/// @brief Encrypts the given data
/// @param data The data to encrypt.
/// @param algorithm A @c SecKeyAlgorithm suitable for encrypting with this key –e.g: @c kSecKeyAlgorithmECIESEncryptionStandardVariableIVX963SHA256AESGCM .
/// @param handler Completion handler with the cipher text or an error on failure.
- (void)encryptData:(NSData *)data secKeyAlgorithm:(SecKeyAlgorithm)algorithm completion:(void (NS_SWIFT_SENDABLE ^)(NSData *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(encrypt(_:algorithm:completion:));

/// @brief Checks if the the provided algorithm can be used for encryption with the key.
/// @param algorithm Cryptographic algorithm
/// @return @c YES in case the key supports the provided algorithm with the specified operation.
- (BOOL)canEncryptUsingSecKeyAlgorithm:(SecKeyAlgorithm)algorithm NS_SWIFT_NAME(canEncrypt(using:));

/// @brief Verifies a digital signature for the given data.
/// @param signedData The signed data.
/// @param signature The signature of the given data.
/// @param algorithm One of @c SecKeyAlgorithm suitable for verifying signatures with this key –e.g: @c kSecKeyAlgorithmECDSASignatureMessageX962SHA256
/// @param handler Completion handler with the signature of given data or an error on failure.
- (void)verifyData:(NSData *)signedData signature:(NSData *)signature secKeyAlgorithm:(SecKeyAlgorithm)algorithm completion:(void (NS_SWIFT_SENDABLE ^)(NSError *_Nullable))handler
#pragma push_macro("verify")
#undef verify
NS_SWIFT_NAME(verify(_:signature:algorithm:completion:));
#pragma pop_macro("verify")

/// @brief Checks if the the provided algorithm can be used for verifying signatures with the key.
/// @param algorithm Cryptographic algorithm
/// @return @c YES in case the key supports the provided algorithm with the specified operation.
- (BOOL)canVerifyUsingSecKeyAlgorithm:(SecKeyAlgorithm)algorithm NS_SWIFT_NAME(canVerify(using:));

/// @brief Clients cannot create @c LAPublicKey instances directly. They can only obtain them from a related @c LAPrivateKey instance
+ (instancetype)new NS_UNAVAILABLE;

/// @brief Clients cannot create @c LAPublicKey instances directly. They can only obtain them from a related @c LAPrivateKey instance
- (instancetype)init NS_UNAVAILABLE;
@end

NS_ASSUME_NONNULL_END
