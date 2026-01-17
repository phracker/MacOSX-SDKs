//
//  NWTLSParameters.h
//  NetworkExtension
//
//  Copyright (c) 2015-2016, 2018 Apple. All rights reserved.
//

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif // __NE_INDIRECT__

#ifndef __NWTLSParameters_h_
#define __NWTLSParameters_h_


NS_ASSUME_NONNULL_BEGIN

@interface NWTLSParameters : NSObject

/*!
 * @property TLSSessionID
 * @discussion The session ID for the associated connection, used for TLS session resumption.
 *		This property is optional when using TLS.
 */
@property (nullable, copy) NSData *TLSSessionID API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property SSLCipherSuites
 * @discussion The set of allowed cipher suites, as defined in <Security/CipherSuite.h>.
 *		If set to nil, the default cipher suites will be used.
 */
@property (nullable, copy) NSSet<NSNumber *> *SSLCipherSuites API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property minimumSSLProtocolVersion
 * @discussion The minimum allowed SSLProtocol value. as defined in <Security/SecureTransport.h>.
 *		If set, the SSL handshake will not accept any protocol version older than the minimum.
 */
@property (assign) NSUInteger minimumSSLProtocolVersion API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property maximumSSLProtocolVersion
 * @discussion The maximum allowed SSLProtocol value. as defined in <Security/SecureTransport.h>.
 *		If set, the SSL handshake will not accept any protocol version newer than the maximum.
 *		This property should be used with caution, since it may limit the use of preferred
 *		SSL protocols.
 */
@property (assign) NSUInteger maximumSSLProtocolVersion API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END

#endif // __NWTLSParameters_h_
