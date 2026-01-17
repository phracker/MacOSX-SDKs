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

/**
 * DEPRECATION NOTICE
 *
 * NW object wrappers are hidden in Swift 6. To continue accessing them, you
 * can prepend double underscores to the symbol name.
 */

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("Use `sec_protocol_options_t` in Security framework instead, see deprecation notice in <NetworkExtension/NWTLSParameters.h>", macos(10.11, 15.0), ios(9.0, 18.0), tvos(17.0, 18.0), visionos(1.0, 2.0))
API_UNAVAILABLE(watchos)
@interface NWTLSParameters : NSObject

/*!
 * @property TLSSessionID
 * @discussion The session ID for the associated connection, used for TLS session resumption.
 *		This property is optional when using TLS.
 */
@property (nullable, copy) NSData *TLSSessionID
API_DEPRECATED("Use `sec_protocol_options_set_tls_resumption_enabled` in Security framework instead, see deprecation notice in <NetworkExtension/NWTLSParameters.h>", macos(10.11, 15.0), ios(9.0, 18.0), tvos(17.0, 18.0), visionos(1.0, 2.0))
API_UNAVAILABLE(watchos);

/*!
 * @property SSLCipherSuites
 * @discussion The set of allowed cipher suites, as defined in <Security/CipherSuite.h>.
 *		If set to nil, the default cipher suites will be used.
 */
@property (nullable, copy) NSSet<NSNumber *> *SSLCipherSuites
API_DEPRECATED("Use `sec_protocol_options_append_tls_ciphersuite` in Security framework instead, see deprecation notice in <NetworkExtension/NWTLSParameters.h>", macos(10.11, 15.0), ios(9.0, 18.0), tvos(17.0, 18.0), visionos(1.0, 2.0))
API_UNAVAILABLE(watchos);

/*!
 * @property minimumSSLProtocolVersion
 * @discussion The minimum allowed SSLProtocol value. as defined in <Security/SecureTransport.h>.
 *		If set, the SSL handshake will not accept any protocol version older than the minimum.
 */
@property (assign) NSUInteger minimumSSLProtocolVersion
API_DEPRECATED("Use `sec_protocol_options_set_min_tls_protocol_version` in Security framework instead, see deprecation notice in <NetworkExtension/NWTLSParameters.h>", macos(10.11, 15.0), ios(9.0, 18.0), tvos(17.0, 18.0), visionos(1.0, 2.0))
API_UNAVAILABLE(watchos);

/*!
 * @property maximumSSLProtocolVersion
 * @discussion The maximum allowed SSLProtocol value. as defined in <Security/SecureTransport.h>.
 *		If set, the SSL handshake will not accept any protocol version newer than the maximum.
 *		This property should be used with caution, since it may limit the use of preferred
 *		SSL protocols.
 */
@property (assign) NSUInteger maximumSSLProtocolVersion
API_DEPRECATED("Use `sec_protocol_options_set_max_tls_protocol_version` in Security framework instead, see deprecation notice in <NetworkExtension/NWTLSParameters.h>", macos(10.11, 15.0), ios(9.0, 18.0), tvos(17.0, 18.0), visionos(1.0, 2.0))
API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

#endif // __NWTLSParameters_h_
