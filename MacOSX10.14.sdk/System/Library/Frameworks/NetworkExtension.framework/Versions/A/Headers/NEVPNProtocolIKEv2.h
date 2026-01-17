/*
 * Copyright (c) 2014-2015, 2018 Apple Inc.
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
	NEVPNIKEv2EncryptionAlgorithmDES = 1,
	/*! @const NEVPNIKEv2EncryptionAlgorithm3DES Triple Data Encryption Algorithm (aka 3DES) */
	NEVPNIKEv2EncryptionAlgorithm3DES = 2,
	/*! @const NEVPNIKEv2EncryptionAlgorithmAES128 Advanced Encryption Standard 128 bit (AES128) */
	NEVPNIKEv2EncryptionAlgorithmAES128 = 3,
	/*! @const NEVPNIKEv2EncryptionAlgorithmAES256 Advanced Encryption Standard 256 bit (AES256) */
	NEVPNIKEv2EncryptionAlgorithmAES256 = 4,
	/*! @const NEVPNIKEv2EncryptionAlgorithmAES128GCM Advanced Encryption Standard 128 bit (AES128GCM) */
	NEVPNIKEv2EncryptionAlgorithmAES128GCM API_AVAILABLE(macos(10.11), ios(8.3)) API_UNAVAILABLE(watchos, tvos) = 5,
	/*! @const NEVPNIKEv2EncryptionAlgorithmAES256GCM Advanced Encryption Standard 256 bit (AES256GCM) */
	NEVPNIKEv2EncryptionAlgorithmAES256GCM API_AVAILABLE(macos(10.11), ios(8.3)) API_UNAVAILABLE(watchos, tvos) = 6,
} API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @typedef NEVPNIKEv2IntegrityAlgorithm
 * @abstract IKEv2 Integrity Algorithms
 */
typedef NS_ENUM(NSInteger, NEVPNIKEv2IntegrityAlgorithm) {
	/*! @const NEVPNIKEv2IntegrityAlgorithmSHA96 SHA-1 96 bit */
	NEVPNIKEv2IntegrityAlgorithmSHA96 = 1,
	/*! @const NEVPNIKEv2IntegrityAlgorithmSHA160 SHA-1 160 bit */
	NEVPNIKEv2IntegrityAlgorithmSHA160 = 2,
	/*! @const NEVPNIKEv2IntegrityAlgorithmSHA256 SHA-2 256 bit */
	NEVPNIKEv2IntegrityAlgorithmSHA256 = 3,
	/*! @const NEVPNIKEv2IntegrityAlgorithmSHA384 SHA-2 384 bit */
	NEVPNIKEv2IntegrityAlgorithmSHA384 = 4,
	/*! @const NEVPNIKEv2IntegrityAlgorithmSHA512 SHA-2 512 bit */
	NEVPNIKEv2IntegrityAlgorithmSHA512 = 5,
} API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

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
} API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @typedef NEVPNIKEv2DiffieHellmanGroup
 * @abstract IKEv2 Diffie Hellman groups
 */
typedef NS_ENUM(NSInteger, NEVPNIKEv2DiffieHellmanGroup) {
	/*! @const NEVPNIKEv2DiffieHellmanGroupInvalid Diffie Hellman group 0 is not a valid DH group*/
	NEVPNIKEv2DiffieHellmanGroupInvalid = 0,
	/*! @const NEVPNIKEv2DiffieHellmanGroup1 Diffie Hellman group 1 (768-bit MODP) */
	NEVPNIKEv2DiffieHellmanGroup1 = 1,
	/*! @const NEVPNIKEv2DiffieHellmanGroup2 Diffie Hellman group 2 (1024-bit MODP) */
	NEVPNIKEv2DiffieHellmanGroup2 = 2,
	/*! @const NEVPNIKEv2DiffieHellmanGroup5 Diffie Hellman group 5 (1536-bit MODP) */
	NEVPNIKEv2DiffieHellmanGroup5 = 5,
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
} API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

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
} API_AVAILABLE(macos(10.11), ios(8.3)) API_UNAVAILABLE(watchos, tvos);

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
} API_AVAILABLE(macos(10.13), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @class NEVPNIKEv2SecurityAssociationParameters
 * @discussion The NEVPNIKEv2SecurityAssociationParameters class declares the programmatic interface of an object that manages parameters for an IPSec Security Association
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEVPNIKEv2SecurityAssociationParameters : NSObject <NSSecureCoding,NSCopying>

/*!
 * @property encryptionAlgorithm
 * @discussion The algorithm used by the Security Association to encrypt and decrypt data. Default is NEVPNIKEv2EncryptionAlgorithm3DES.
 */
@property NEVPNIKEv2EncryptionAlgorithm encryptionAlgorithm API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property integrityAlgorithm
 * @discussion The algorithm used by the Security Association to verify the integrity of data. Default is NEVPNIKEv2IntegrityAlgorithmSHA96. The IKE psedo-random function algorithm will be inferred based on the integrity algorithm.
 */
@property NEVPNIKEv2IntegrityAlgorithm integrityAlgorithm API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property diffieHellmanGroup
 * @discussion The Diffie Hellman group used by the Security Association. Default is NEVPNIKEv2DiffieHellmanGroup2.
 */
@property NEVPNIKEv2DiffieHellmanGroup diffieHellmanGroup API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property lifetimeMinutes
 * @discussion The life time of the Security Association, in minutes. Default is 60 for IKE Security Associations, and 30 for Child Security Associations. Before the lifetime is reached, IKEv2 will attempt to rekey the Security Association to maintain the connection.
 */
@property int32_t lifetimeMinutes API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

@end

/*!
 * @interface NEVPNProtocolIKEv2
 * @discussion The NEVPNProtocolIKEv2 class declares the programmatic interface of an object that manages the IKEv2-specific portion of a VPN configuration.
 *
 * Instances of this class use IKE version 2 for key negotiation.
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEVPNProtocolIKEv2 : NEVPNProtocolIPSec

/*!
 * @property deadPeerDetectionRate
 * @discussion How frequently the IKEv2 client will run the dead peer detection algorithm.  Default is NEVPNIKEv2DeadPeerDetectionRateMedium.
 */
@property NEVPNIKEv2DeadPeerDetectionRate deadPeerDetectionRate API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property serverCertificateIssuerCommonName
 * @discussion A string containing the Subject Common Name field of the Certificate Authority certificate that issued the IKEv2 server's certificate.
 */
@property (copy, nullable) NSString *serverCertificateIssuerCommonName API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property serverCertificateCommonName
 * @discussion A string containing the value to verify in the IKEv2 server certificate's Subject Common Name field.
 */
@property (copy, nullable) NSString *serverCertificateCommonName API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property certificateType
 * @discussion contains the type of certificate if an certificate is configured.  Default is RSA.
 */
@property NEVPNIKEv2CertificateType certificateType API_AVAILABLE(macos(10.11), ios(8.3)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property useConfigurationAttributeInternalIPSubnet
 * @discussion Boolean indicating if client should use INTERNAL_IP4_SUBNET / INTERNAL_IP6_SUBNET attributes.  Default is False.
 */
@property BOOL useConfigurationAttributeInternalIPSubnet API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property IKESecurityAssociationParameters
 * @discussion Parameters for the IKE SA
 */
@property (readonly) NEVPNIKEv2SecurityAssociationParameters *IKESecurityAssociationParameters API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property childSecurityAssociationParameters
 * @discussion Parameters for the child SA
 */
@property (readonly) NEVPNIKEv2SecurityAssociationParameters *childSecurityAssociationParameters API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property disableMOBIKE
 * @discussion Disable MOBIKE negotiation. Default is NO.
 */
@property BOOL disableMOBIKE API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property disableRedirect
 * @discussion Disable Server Redirect. Default is NO.
 */
@property BOOL disableRedirect API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property enablePFS
 * @discussion Enable Perfect Forward Secrecy. Default is NO.
 */
@property BOOL enablePFS API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property enableRevocationCheck
 * @discussion Enable certificate revocation check. Default is NO.
 */
@property BOOL enableRevocationCheck API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property strictRevocationCheck
 * @discussion Require positive certificate revocation check response for peer certificate validation to pass. Default is NO.
 */
@property BOOL strictRevocationCheck API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property minimumTLSVersion
 * @discussion Sets a minimum TLS version to allow for EAP-TLS authentication. Default is NEVPNIKEv2TLSVersionDefault.
 */
@property NEVPNIKEv2TLSVersion minimumTLSVersion API_AVAILABLE(macos(10.13), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property maximumTLSVersion
 * @discussion Sets a maximum TLS version to allow for EAP-TLS authentication. Default is NEVPNIKEv2TLSVersionDefault.
 */
@property NEVPNIKEv2TLSVersion maximumTLSVersion API_AVAILABLE(macos(10.13), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

