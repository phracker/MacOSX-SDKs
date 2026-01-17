/*
 * NEVPNProtocol.h
 *
 * Copyright (c) 2013-2015, 2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEProxySettings.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @interface NEVPNProtocol
 * @discussion The NEVPNProtocol class declares the programmatic interface of an object that manages the protocol-specific portion of a VPN configuration.
 *
 * NEVPNProtocol is an abstract base class from which other protocol-specific classes are derived.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface NEVPNProtocol : NSObject <NSCopying,NSSecureCoding>

/*!
 * @property serverAddress
 * @discussion The VPN server. Depending on the protocol, may be an IP address, host name, or URL.
 */
@property (copy, nullable) NSString *serverAddress API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property username
 * @discussion The username component of the VPN authentication credential.
 */
@property (copy, nullable) NSString *username API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property passwordReference
 * @discussion The password component of the VPN authentication credential. The value is a persistent reference to a keychain item with the kSecClassGenericPassword class.
 */
@property (copy, nullable) NSData *passwordReference API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property identityReference
 * @discussion The certificate and private key component of the VPN authentication credential. The value is a persistent reference to a keychain item with the kSecClassIdentity class.
 */
@property (copy, nullable) NSData *identityReference API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property identityData
 * @discussion The PKCS12 data for the VPN authentication identity. The value is a NSData in PKCS12 format.
 */
@property (copy, nullable) NSData *identityData API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property identityDataPassword 
 * @discussion The password to be used to decrypt the PKCS12 identity data.
 */
@property (copy, nullable) NSString *identityDataPassword API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property disconnectOnSleep
 * @discussion If YES, the VPN connection will be disconnected when the device goes to sleep. The default is NO.
 */
@property BOOL disconnectOnSleep API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property proxySettings
 * @discussion An NEProxySettings object containing the proxy settings to use for connections routed through the tunnel.
 */
@property (copy, nullable) NEProxySettings *proxySettings API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property includeAllNetworks
 * @discussion If YES, all traffic will be sent over the tunnel, and all traffic will be dropped if the tunnel is down. The default is NO.
 */
@property BOOL includeAllNetworks API_AVAILABLE(macos(10.15), ios(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property excludeLocalNetworks
 * @discussion If YES, all traffic destined for local networks will be excluded from the tunnel. The default is NO on macOS and YES on iOS.
 */
@property BOOL excludeLocalNetworks API_AVAILABLE(macos(10.15), ios(14.2)) API_UNAVAILABLE(tvos, watchos) __WATCHOS_PROHIBITED;

/*!
 * @property enforceRoutes
 * @discussion If YES, route rules for this tunnel will take precendence over any locally-defined routes. The default is NO.
 */
@property BOOL enforceRoutes API_AVAILABLE(macos(11.0), ios(14.2)) API_UNAVAILABLE(tvos, watchos) __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END

