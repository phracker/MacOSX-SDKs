/*
 * Copyright (c) 2013-2015 Apple Inc.
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
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*!
 * @interface NEVPNProtocolIPSec
 * @discussion The NEVPNProtocolIPSec class declares the programmatic interface of an object that manages the IPSec-specific portion of a VPN configuration.
 *
 * Instances of this class use IKE version 1 for key negotiation.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NEVPNProtocolIPSec : NEVPNProtocol

/*!
 * @property authenticationMethod
 * @discussion The method used to authenticate with the IPSec server. Note that if this property is set to NEVPNIKEAuthenticationMethodNone, extended authentication will still be negotiated if useExtendedAuthentication is set to YES.
 */
@property NEVPNIKEAuthenticationMethod authenticationMethod NS_AVAILABLE(10_10, 8_0);

/*!
 * @property useExtendedAuthentication
 * @discussion A flag indicating if extended authentication will be negotiated. This authentication is in addition to the IKE authentication used to authenticate the endpoints of the IKE session.
 *   For IKE version 1, when this flag is set X-Auth authentication will be negotiated as part of the IKE session, using the username and password properties as the credential.
 *   For IKE version 2, when this flag is set EAP authentication will be negotiated as part of the IKE session, using the username, password, and/or identity properties as the credential depending on which EAP method the server requires.
 */
@property BOOL useExtendedAuthentication NS_AVAILABLE(10_10, 8_0);

/*!
 * @property sharedSecretReference
 * @discussion A persistent reference to a keychain item of class kSecClassGenericPassword containing the IKE shared secret.
 */
@property (copy, nullable) NSData *sharedSecretReference NS_AVAILABLE(10_10, 8_0);

/*!
 * @property localIdentifier
 * @discussion A string identifying the local IPSec endpoint for authentication purposes.
 */
@property (copy, nullable) NSString *localIdentifier NS_AVAILABLE(10_10, 8_0);

/*!
 * @property remoteIdentifier
 * @discussion A string identifying the remote IPSec endpoint for authentication purposes.
 */
@property (copy, nullable) NSString *remoteIdentifier NS_AVAILABLE(10_10, 8_0);

@end

NS_ASSUME_NONNULL_END

