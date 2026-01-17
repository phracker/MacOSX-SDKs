/*
 * Copyright (c) 2013-2015, 2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEVPNProtocol.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @typedef NEVPNIKEAuthenticationMethod
 * @abstract Internet Key Exchange (IKE) authentication methods used to authenticate with the IPSec server.
 */
typedef NS_ENUM(NSInteger, NEVPNIKEAuthenticationMethod) {
	/*! @const NEVPNIKEAuthenticationMethodNone Do not authenticate with the IPSec server */
	NEVPNIKEAuthenticationMethodNone = 0,
	/*! @const NEVPNIKEAuthenticationMethodCertificate Use a certificate and private key as the authentication credential */
	NEVPNIKEAuthenticationMethodCertificate = 1,
	/*! @const NEVPNIKEAuthenticationMethodSharedSecret Use a shared secret as the authentication credential */
	NEVPNIKEAuthenticationMethodSharedSecret = 2,
} API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @interface NEVPNProtocolIPSec
 * @discussion The NEVPNProtocolIPSec class declares the programmatic interface of an object that manages the IPSec-specific portion of a VPN configuration.
 *
 * Instances of this class use IKE version 1 for key negotiation.
 */
API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface NEVPNProtocolIPSec : NEVPNProtocol

/*!
 * @property authenticationMethod
 * @discussion The method used to authenticate with the IPSec server. Note that if this property is set to NEVPNIKEAuthenticationMethodNone, extended authentication will still be negotiated if useExtendedAuthentication is set to YES.
 */
@property NEVPNIKEAuthenticationMethod authenticationMethod API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property useExtendedAuthentication
 * @discussion A flag indicating if extended authentication will be negotiated. This authentication is in addition to the IKE authentication used to authenticate the endpoints of the IKE session.
 *   For IKE version 1, when this flag is set X-Auth authentication will be negotiated as part of the IKE session, using the username and password properties as the credential.
 *   For IKE version 2, when this flag is set EAP authentication will be negotiated as part of the IKE session, using the username, password, and/or identity properties as the credential depending on which EAP method the server requires.
 */
@property BOOL useExtendedAuthentication API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property sharedSecretReference
 * @discussion A persistent reference to a keychain item of class kSecClassGenericPassword containing the IKE shared secret.
 */
@property (copy, nullable) NSData *sharedSecretReference API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property localIdentifier
 * @discussion A string identifying the local IPSec endpoint for authentication purposes.
 */
@property (copy, nullable) NSString *localIdentifier API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property remoteIdentifier
 * @discussion A string identifying the remote IPSec endpoint for authentication purposes.
 */
@property (copy, nullable) NSString *remoteIdentifier API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

