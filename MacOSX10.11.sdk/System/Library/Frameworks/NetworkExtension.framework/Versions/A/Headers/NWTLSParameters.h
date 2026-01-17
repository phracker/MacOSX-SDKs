//
//  NWUDPSession.h
//  Network
//
//  Copyright (c) 2015 Apple. All rights reserved.
//

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

@interface NWTLSParameters : NSObject

/*!
 * @property TLSSessionID
 * @discussion The session ID for the associated connection, used for TLS session resumption.
 *		This property is optional when using TLS.
 */
@property (nullable, copy) NSData *TLSSessionID NS_AVAILABLE(10_11, 9_0);

/*!
 * @property SSLCipherSuites
 * @discussion The set of allowed cipher suites, as defined in <Security/CipherSuite.h>.
 *		If set to nil, the default cipher suites will be used.
 */
@property (nullable, copy) NSSet<NSNumber *> *SSLCipherSuites NS_AVAILABLE(10_11, 9_0);

/*!
 * @property minimumSSLProtocolVersion
 * @discussion The minimum allowed SSLProtocol value. as defined in <Security/SecureTransport.h>.
 *		If set, the SSL handshake will not accept any protocol version older than the minimum.
 */
@property (assign) NSUInteger minimumSSLProtocolVersion NS_AVAILABLE(10_11, 9_0);

/*!
 * @property maximumSSLProtocolVersion
 * @discussion The maximum allowed SSLProtocol value. as defined in <Security/SecureTransport.h>.
 *		If set, the SSL handshake will not accept any protocol version newer than the maximum.
 *		This property should be used with caution, since it may limit the use of preferred
 *		SSL protocols.
 */
@property (assign) NSUInteger maximumSSLProtocolVersion NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END
