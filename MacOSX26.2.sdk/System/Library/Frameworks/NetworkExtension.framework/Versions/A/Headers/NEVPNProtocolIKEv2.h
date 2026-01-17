/*
 * Copyright (c) 2014-2015, 2018-2019 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEVPNProtocolIPSec.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @typedef NEVPNIKEv2EncryptionAlgorithm
 * @abstract IKEv2 Encryption Algorithms
 */
typedef NS_ENUM(NSInteger, NEVPNIKEv2EncryptionAlgorithm) {
	/*! @const NEVPNIKEv2EncryptionAlgorithmDES Data Encryption Standard (DES) */
	NEVPNIKEv2EncryptionAlgorithmDES API_OBSOLETED("DES is not supported", macos(10.11, 14.0, 26.0), ios(8.0, 17.0, 26.0), visionos(1.0, 1.0, 26.0)) API_UNAVAILABLE(watchos, tvos) = 1,
	/*! @const NEVPNIKEv2EncryptionAlgorithm3DES Triple Data Encryption Algorithm (aka 3DES) */
	NEVPNIKEv2EncryptionAlgorithm3DES API_OBSOLETED("3DES is not supported", macos(10.11, 14.0, 26.0), ios(8.0, 17.0, 26.0), visionos(1.0, 1.0, 26.0)) API_UNAVAILABLE(watchos, tvos) = 2,
	/*! @const NEVPNIKEv2EncryptionAlgorithmAES128 Advanced Encryption Standard 128 bit (AES128) */
	NEVPNIKEv2EncryptionAlgorithmAES128 API_DEPRECATED("Use an encryption algorithm with 256-bit keys instead", macos(10.11, 14.0), ios(8.0, 17.0), tvos(17.0, 17.0)) = 3,
	/*! @const NEVPNIKEv2EncryptionAlgorithmAES256 Advanced Encryption Standard 256 bit (AES256) */
	NEVPNIKEv2EncryptionAlgorithmAES256 = 4,
	/*! @const NEVPNIKEv2EncryptionAlgorithmAES128GCM Advanced Encryption Standard 128 bit (AES128GCM) */
	NEVPNIKEv2EncryptionAlgorithmAES128GCM API_DEPRECATED("Use an encryption algorithm with 256-bit keys instead", macos(10.11, 14.0), ios(8.3, 17.0), tvos(17.0, 17.0)) API_UNAVAILABLE(watchos) = 5,
	/*! @const NEVPNIKEv2EncryptionAlgorithmAES256GCM Advanced Encryption Standard 256 bit (AES256GCM) */
	NEVPNIKEv2EncryptionAlgorithmAES256GCM API_AVAILABLE(macos(10.11), ios(8.3), tvos(17.0)) API_UNAVAILABLE(watchos) = 6,
	/*! @const NEVPNIKEv2EncryptionAlgorithmChaCha20Poly1305 ChaCha20 and Poly1305 (ChaCha20Poly1305) */
	NEVPNIKEv2EncryptionAlgorithmChaCha20Poly1305 API_AVAILABLE(macos(10.15), ios(13.0), tvos(17.0)) API_UNAVAILABLE(watchos) = 7,
} API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @typedef NEVPNIKEv2IntegrityAlgorithm
 * @abstract IKEv2 Integrity Algorithms
 */
typedef NS_ENUM(NSInteger, NEVPNIKEv2IntegrityAlgorithm) {
	/*! @const NEVPNIKEv2IntegrityAlgorithmSHA96 SHA-1 96 bit */
	NEVPNIKEv2IntegrityAlgorithmSHA96 API_OBSOLETED("SHA-1 is not supported", macos(10.11, 14.0, 26.0), ios(8.0, 17.0, 26.0), visionos(1.0, 1.0, 26.0)) API_UNAVAILABLE(watchos, tvos) = 1,
	/*! @const NEVPNIKEv2IntegrityAlgorithmSHA160 SHA-1 160 bit */
	NEVPNIKEv2IntegrityAlgorithmSHA160 API_OBSOLETED("SHA-1 is not supported", macos(10.11, 14.0, 26.0), ios(8.0, 17.0, 26.0), visionos(1.0, 1.0, 26.0)) API_UNAVAILABLE(watchos, tvos) = 2,
	/*! @const NEVPNIKEv2IntegrityAlgorithmSHA256 SHA-2 256 bit */
	NEVPNIKEv2IntegrityAlgorithmSHA256 = 3,
	/*! @const NEVPNIKEv2IntegrityAlgorithmSHA384 SHA-2 384 bit */
	NEVPNIKEv2IntegrityAlgorithmSHA384 = 4,
	/*! @const NEVPNIKEv2IntegrityAlgorithmSHA512 SHA-2 512 bit */
	NEVPNIKEv2IntegrityAlgorithmSHA512 = 5,
} API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @typedef NEVPNIKEv2DeadPeerDetectionRate
 * @abstract IKEv2 Dead Peer Detection Rates
 */
typedef NS_ENUM(NSInteger, NEVPNIKEv2DeadPeerDetectionRate) {
	/*! @const NEVPNIKEv2DeadPeerDetectionRateNone Do not perform dead peer detection */
	NEVPNIKEv2DeadPeerDetectionRateNone = 0,
	/*! @const NEVPNIKEv2DeadPeerDetectionRateLow Run dead peer detection once every 30 minutes. If the peer does not respond, retry 5 times at 1 second intervals before declaring the peer dead */
	NEVPNIKEv2DeadPeerDetectionRateLow = 1,
	/*! @const NEVPNIKEv2DeadPeerDetectionRateMedium Run dead peer detection once every 10 minutes. If the peer does not respond, retry 5 times at 1 second intervals before declaring the peer dead */
	NEVPNIKEv2DeadPeerDetectionRateMedium = 2,
	/*! @const NEVPNIKEv2DeadPeerDetectionRateHigh Run dead peer detection once every 1 minute. If the peer does not respond, retry 5 times at 1 second intervals before declaring the peer dead */
	NEVPNIKEv2DeadPeerDetectionRateHigh = 3,
} API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @typedef NEVPNIKEv2DiffieHellmanGroup
 * @abstract IKEv2 Diffie Hellman groups
 */
typedef NS_ENUM(NSInteger, NEVPNIKEv2DiffieHellmanGroup) {
	/*! @const NEVPNIKEv2DiffieHellmanGroupInvalid Diffie Hellman group 0 is not a valid DH group*/
	NEVPNIKEv2DiffieHellmanGroupInvalid = 0,
	/*! @const NEVPNIKEv2DiffieHellmanGroup1 Diffie Hellman group 1 (768-bit MODP) */
	NEVPNIKEv2DiffieHellmanGroup1 API_OBSOLETED("Diffie Hellman groups less than 14 are not supported", macos(10.11, 14.0, 26.0), ios(8.0, 17.0, 26.0), visionos(1.0, 1.0, 26.0)) API_UNAVAILABLE(watchos, tvos) = 1,
	/*! @const NEVPNIKEv2DiffieHellmanGroup2 Diffie Hellman group 2 (1024-bit MODP) */
	NEVPNIKEv2DiffieHellmanGroup2 API_OBSOLETED("Diffie Hellman groups less than 14 are not supported", macos(10.11, 14.0, 26.0), ios(8.0, 17.0, 26.0), visionos(1.0, 1.0, 26.0)) API_UNAVAILABLE(watchos, tvos) = 2,
	/*! @const NEVPNIKEv2DiffieHellmanGroup5 Diffie Hellman group 5 (1536-bit MODP) */
	NEVPNIKEv2DiffieHellmanGroup5 API_OBSOLETED("Diffie Hellman groups less than 14 are not supported", macos(10.11, 14.0, 26.0), ios(8.0, 17.0, 26.0), visionos(1.0, 1.0, 26.0)) API_UNAVAILABLE(watchos, tvos) = 5,
	/*! @const NEVPNIKEv2DiffieHellmanGroup14 Diffie Hellman group 14 (2048-bit MODP) */
	NEVPNIKEv2DiffieHellmanGroup14 = 14,
	/*! @const NEVPNIKEv2DiffieHellmanGroup15 Diffie Hellman group 15 (3072-bit MODP) */
	NEVPNIKEv2DiffieHellmanGroup15 = 15,
	/*! @const NEVPNIKEv2DiffieHellmanGroup16 Diffie Hellman group 16 (4096-bit MODP) */
	NEVPNIKEv2DiffieHellmanGroup16 = 16,
	/*! @const NEVPNIKEv2DiffieHellmanGroup17 Diffie Hellman group 17 (6144-bit MODP) */
	NEVPNIKEv2DiffieHellmanGroup17 = 17,
	/*! @const NEVPNIKEv2DiffieHellmanGroup18 Diffie Hellman group 18 (8192-bit MODP) */
	NEVPNIKEv2DiffieHellmanGroup18 = 18,
	/*! @const NEVPNIKEv2DiffieHellmanGroup19 Diffie Hellman group 19 (256-bit random ECP) */
	NEVPNIKEv2DiffieHellmanGroup19 = 19,
	/*! @const NEVPNIKEv2DiffieHellmanGroup20 Diffie Hellman group 20 (384-bit random ECP) */
	NEVPNIKEv2DiffieHellmanGroup20 = 20,
	/*! @const NEVPNIKEv2DiffieHellmanGroup21 Diffie Hellman group 21 (521-bit random ECP) */
	NEVPNIKEv2DiffieHellmanGroup21 = 21,
	/*! @const NEVPNIKEv2DiffieHellmanGroup31 Diffie Hellman group 31 (Curve25519) */
	NEVPNIKEv2DiffieHellmanGroup31 API_AVAILABLE(macos(10.15), ios(13.0), tvos(17.0)) API_UNAVAILABLE(watchos) = 31,
	/*! @const NEVPNIKEv2DiffieHellmanGroup32 Diffie Hellman group 32 (Curve448) */
	NEVPNIKEv2DiffieHellmanGroup32 API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos) = 32,
} API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @typedef NEVPNIKEv2PostQuantumKeyExchangeMethod
 * @abstract IKEv2 post-quantum key exchange methods
 */
typedef NS_ENUM(NSInteger, NEVPNIKEv2PostQuantumKeyExchangeMethod) {
	/*! @const NEVPNIKEv2PostQuantumKeyExchangeMethodNone Do not perform a post-quantum key exchange */
	NEVPNIKEv2PostQuantumKeyExchangeMethodNone = 0,
	/*! @const NEVPNIKEv2PostQuantumKeyExchangeMethod36 Post-Quantum Key Exchange method 36 (ML-KEM-768) */
	NEVPNIKEv2PostQuantumKeyExchangeMethod36 = 36,
	/*! @const NEVPNIKEv2PostQuantumKeyExchangeMethod37 Post-Quantum Key Exchange method 37 (ML-KEM-1024) */
	NEVPNIKEv2PostQuantumKeyExchangeMethod37 = 37,
} API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

/*!
 * @typedef NEVPNIKEv2CertificateType
 * @abstract IKEv2 Certificate types
 */
typedef NS_ENUM(NSInteger, NEVPNIKEv2CertificateType) {
	/*! @const NEVPNIKEv2CertificateType RSA */
	NEVPNIKEv2CertificateTypeRSA = 1,
	/*! @const NEVPNIKEv2CertificateTypeECDSA256 ECDSA with p-256 curve */
	NEVPNIKEv2CertificateTypeECDSA256 = 2,
	/*! @const NEVPNIKEv2CertificateTypeECDSA384 ECDSA with p-384 curve */
	NEVPNIKEv2CertificateTypeECDSA384 = 3,
	/*! @const NEVPNIKEv2CertificateTypeECDSA521 ECDSA with p-521 curve */
	NEVPNIKEv2CertificateTypeECDSA521 = 4,
	/*! @const NEVPNIKEv2CertificateTypeEd25519 EdDSA with Edwards Curve25519 */
	NEVPNIKEv2CertificateTypeEd25519 API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(watchos, tvos) = 5,
	/*! @const NEVPNIKEv2CertificateTypeRSAPSS RSA-PSS */
	NEVPNIKEv2CertificateTypeRSAPSS API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos) = 6,
} API_AVAILABLE(macos(10.11), ios(8.3), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @typedef NEVPNIKEv2TLSVersion
 * @abstract TLS Versions for use in EAP-TLS
 */
typedef NS_ENUM(NSInteger, NEVPNIKEv2TLSVersion) {
	/*! @const NEVPNIKEv2TLSVersionDefault Use the default TLS configuration */
	NEVPNIKEv2TLSVersionDefault = 0,
	/*! @const NEVPNIKEv2TLSVersion1_0 TLS 1.0 */
	NEVPNIKEv2TLSVersion1_0 = 1,
	/*! @const NEVPNIKEv2TLSVersion1_0 TLS 1.1 */
	NEVPNIKEv2TLSVersion1_1 = 2,
	/*! @const NEVPNIKEv2TLSVersion1_0 TLS 1.2 */
	NEVPNIKEv2TLSVersion1_2 = 3,
} API_AVAILABLE(macos(10.13), ios(11.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @class NEVPNIKEv2SecurityAssociationParameters
 * @discussion The NEVPNIKEv2SecurityAssociationParameters class declares the programmatic interface of an object that manages parameters for an IPSec Security Association
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface NEVPNIKEv2SecurityAssociationParameters : NSObject <NSSecureCoding,NSCopying>

/*!
 * @property encryptionAlgorithm
 * @discussion The algorithm used by the Security Association to encrypt and decrypt data. On macOS and iOS, the default is NEVPNIKEv2EncryptionAlgorithmAES256 starting in macOS 11 and iOS 14.
 * Prior to that the default was NEVPNIKEv2EncryptionAlgorithm3DES. On tvOS, the default is NEVPNIKEv2EncryptionAlgorithmAES256GCM.
 */
@property NEVPNIKEv2EncryptionAlgorithm encryptionAlgorithm API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property integrityAlgorithm
 * @discussion The algorithm used by the Security Association to verify the integrity of data.  The IKE psedo-random function algorithm will be inferred based on the integrity algorithm.
 * Default is NEVPNIKEv2IntegrityAlgorithmSHA256 starting in macOS 11, iOS 14, and tvOS 17.  Prior to that the default was NEVPNIKEv2IntegrityAlgorithmSHA96.
 */
@property NEVPNIKEv2IntegrityAlgorithm integrityAlgorithm API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property diffieHellmanGroup
 * @discussion The Diffie Hellman group used by the Security Association. Default is NEVPNIKEv2DiffieHellmanGroup14 starting in macOS 11, iOS 14, and tvOS 17. Prior to that the default was NEVPNIKEv2DiffieHellmanGroup2.
 */
@property NEVPNIKEv2DiffieHellmanGroup diffieHellmanGroup API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property postQuantumKeyExchangeMethods
 * @discussion The post-quantum key exchange method(s) used by the Security Association, if any. Values are taken from NEVPNIKEv2PostQuantumKeyExchangeMethod. Up to 7 methods may be specified, mapping to ADDKE1 - ADDKE7 from RFC 9370.
 */
@property (copy) NSArray<NSNumber *> *postQuantumKeyExchangeMethods API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

/*!
 * @property lifetimeMinutes
 * @discussion The life time of the Security Association, in minutes. Default is 60 for IKE Security Associations, and 30 for Child Security Associations. Before the lifetime is reached, IKEv2 will attempt to rekey the Security Association to maintain the connection.
 */
@property int32_t lifetimeMinutes API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

@end

/*!
 * @interface NEVPNIKEv2PPKConfiguration
 * @discussion The NEVPNIKEv2PPKConfiguration class declares the programmatic interface of an object that manages parameters for a Post-quantum Pre-shared Key (PPK)
 *
 * Instances of this class conform to RFC 8784.
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos)
@interface NEVPNIKEv2PPKConfiguration : NSObject<NSCopying>

/*!
 * @method initWithIdentifier:keychainReference:
 * @discussion Initialize a newly-allocated NEVPNIKEv2PPKConfiguration object.
 * @param identifier The identifier for the PPK.
 * @param keychainReference A persistent reference to a keychain item of class kSecClassGenericPassword containing the PPK.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier keychainReference:(NSData *)keychainReference;

/*!
 * @property identifier
 * @discussion The identifer for the PPK.
 */
@property (readonly, copy) NSString *identifier;

/*!
 * @property keychainReference
 * @discussion A persistent reference to a keychain item of class kSecClassGenericPassword containing the PPK.
 */
@property (readonly, copy) NSData *keychainReference;

/*!
 * @property isMandatory
 * @discussion Boolean indicating whether use of the PPK is mandatory or not. Default is YES.
 */
@property BOOL isMandatory;

@end

/*!
 * @interface NEVPNProtocolIKEv2
 * @discussion The NEVPNProtocolIKEv2 class declares the programmatic interface of an object that manages the IKEv2-specific portion of a VPN configuration.
 *
 * Instances of this class use IKE version 2 for key negotiation.
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface NEVPNProtocolIKEv2 : NEVPNProtocolIPSec

/*!
 * @property deadPeerDetectionRate
 * @discussion How frequently the IKEv2 client will run the dead peer detection algorithm.  Default is NEVPNIKEv2DeadPeerDetectionRateMedium.
 */
@property NEVPNIKEv2DeadPeerDetectionRate deadPeerDetectionRate API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property serverCertificateIssuerCommonName
 * @discussion A string containing the Subject Common Name field of the Certificate Authority certificate that issued the IKEv2 server's certificate.
 */
@property (copy, nullable) NSString *serverCertificateIssuerCommonName API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property serverCertificateCommonName
 * @discussion A string containing the value to verify in the IKEv2 server certificate's Subject Common Name field.
 */
@property (copy, nullable) NSString *serverCertificateCommonName API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property certificateType
 * @discussion contains the type of certificate if an certificate is configured.  Default is RSA.
 */
@property NEVPNIKEv2CertificateType certificateType API_AVAILABLE(macos(10.11), ios(8.3), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property useConfigurationAttributeInternalIPSubnet
 * @discussion Boolean indicating if client should use INTERNAL_IP4_SUBNET / INTERNAL_IP6_SUBNET attributes.  Default is False.
 */
@property BOOL useConfigurationAttributeInternalIPSubnet API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property IKESecurityAssociationParameters
 * @discussion Parameters for the IKE SA
 */
@property (readonly) NEVPNIKEv2SecurityAssociationParameters *IKESecurityAssociationParameters API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property childSecurityAssociationParameters
 * @discussion Parameters for the child SA
 */
@property (readonly) NEVPNIKEv2SecurityAssociationParameters *childSecurityAssociationParameters API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property disableMOBIKE
 * @discussion Disable MOBIKE negotiation. Default is NO.
 */
@property BOOL disableMOBIKE API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property disableRedirect
 * @discussion Disable Server Redirect. Default is NO.
 */
@property BOOL disableRedirect API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property enablePFS
 * @discussion Enable Perfect Forward Secrecy. Default is NO.
 */
@property BOOL enablePFS API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property allowPostQuantumKeyExchangeFallback
 * @discussion Allow servers that do not support post-quantum key exchanges to skip them. This property has no effect if no post-quantum key exchange methods
 *     are configured for the IKE SA or Child SA (see NEVPNIKEv2SecurityAssociationParameters.postQuantumKeyExchangeMethods). Default is NO.
 */
@property BOOL allowPostQuantumKeyExchangeFallback API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

/*!
 * @property enableRevocationCheck
 * @discussion Enable certificate revocation check. Default is NO.
 */
@property BOOL enableRevocationCheck API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property strictRevocationCheck
 * @discussion Require positive certificate revocation check response for peer certificate validation to pass. Default is NO.
 */
@property BOOL strictRevocationCheck API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property minimumTLSVersion
 * @discussion Sets a minimum TLS version to allow for EAP-TLS authentication. Default is NEVPNIKEv2TLSVersionDefault.
 */
@property NEVPNIKEv2TLSVersion minimumTLSVersion API_AVAILABLE(macos(10.13), ios(11.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property maximumTLSVersion
 * @discussion Sets a maximum TLS version to allow for EAP-TLS authentication. Default is NEVPNIKEv2TLSVersionDefault.
 */
@property NEVPNIKEv2TLSVersion maximumTLSVersion API_AVAILABLE(macos(10.13), ios(11.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property enableFallback
 * @discussion Enable Fallback is used to support Wi-Fi Assist. Wi-Fi Assist allows connections for foreground apps to switch over
 *     to Cellular Data when WiFi connectivity is poor. By setting the EnableFallback key, the device will bring up a tunnel over
 *     Cellular Data to carry traffic that is eligible for Wi-Fi Assist and also requires VPN. Enabling fallback requires that the
 *     server support multiple tunnels for a single user. Default is NO.
 */
@property BOOL enableFallback API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property mtu
 * @discussion Maximum Transmission Unit (MTU) size in bytes to assign to the tunnel interface.
 */
@property NSUInteger mtu API_AVAILABLE(macos(11.0), ios(14.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property ppkConfiguration
 * @discussion Configuration for the use of a Post-quantum Pre-shared Key (PPK).
 */
@property (copy, nullable) NEVPNIKEv2PPKConfiguration *ppkConfiguration API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

