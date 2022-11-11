//
//  NWTCPConnection.h
//  Network
//
//  Copyright (c) 2014-2016, 2018 Apple Inc. All rights reserved.
//

#ifndef __NE_TAPI__

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif // __NE_INDIRECT__

#ifndef __NWTCPConnection_h_
#define __NWTCPConnection_h_

#import <Security/Security.h>


NS_ASSUME_NONNULL_BEGIN

/*!
 * @typedef NWTCPConnectionState
 * @abstract Defined connection states. New types may be defined in the future.
 */
typedef NS_ENUM(NSInteger, NWTCPConnectionState) {
	/*! @constant NWTCPConnectionStateInvalid The connection is in an invalid or uninitialized state */
	NWTCPConnectionStateInvalid			= 0,

	/*! @constant NWTCPConnectionStateConnecting The connection is attempting */
	NWTCPConnectionStateConnecting		= 1,

	/*! @constant NWTCPConnectionStateWaiting The connection has attempted but failed. It is now
	 *		waiting for better condition(s) before trying again.
	 */
	NWTCPConnectionStateWaiting			= 2,

	/*! @constant NWTCPConnectionStateConnected The connection is established. It is now possible
	 *		to transfer data. If TLS is in use, the TLS handshake would have finished when the connection
	 *		is in this state.
	 */
	NWTCPConnectionStateConnected		= 3,

	/*! @constant NWTCPConnectionStateDisconnected The connection is disconnected. It is no longer
	 *		possible to transfer data. The application should call cancellation method to clean up resources
	 *		when the connection is in this state.
	 */
	NWTCPConnectionStateDisconnected	= 4,

	/*! @constant NWTCPConnectionStateCancelled The connection is cancelled. This is triggered by
	 *		the cancellation method.
	 */
	NWTCPConnectionStateCancelled		= 5,
} API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @interface NWTCPConnection
 * @discussion Establish TCP connections to an endpoint, and send and receive data on the TCP connection.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface NWTCPConnection : NSObject

/*!
 * @method initWithUpgradeForConnection:
 * @discussion This convenience initializer can be used to create a new connection that would only
 * 		be connected if there exists a better path (as determined by the system) to the destination
 * 		endpoint of the original connection. It will be initialized using the same destination endpoint
 * 		and set of parameters from the original connection.
 *
 * 		If the original connection becomes disconnected or cancelled, the new "upgrade" connection
 * 		would automatically be considered better.
 *
 *		The caller should create an NWTCPConnection and watch for the hasBetterPath property.
 *		When this property is YES, the caller should attempt to create a new upgrade
 *		connection, with the goal to start transferring data on the new better path as soon as
 *		possible to reduce power and potentially monetary cost. When the new upgrade connection
 *		becomes connected and when the caller wraps up the previous caller session on
 *		the original connection, the caller can start using the new upgrade connection and
 *		tear down the original one.
 *
 * @param connection The original connection from which the caller will upgrade
 * @return An initialized NWTCPConnection
 */
- (instancetype)initWithUpgradeForConnection:(NWTCPConnection *)connection API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property state
 * @discussion The status of the connection. Use KVO to watch this property to get updates.
 */
@property (nonatomic, readonly) NWTCPConnectionState state API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property viable
 * @discussion YES if the connection can read and write data, NO otherwise. Use KVO to watch this property.
 */
@property (nonatomic, readonly, getter=isViable) BOOL viable API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property hasBetterPath
 * @discussion YES if the system determines there is a better path the destination can be reached if
 *		the caller creates a new connection using the same endpoint and parameters. This can
 *		be done using the convenience upgrade initializer method.
 *		Use KVO to watch this property to get updates.
 */
@property (nonatomic, readonly) BOOL hasBetterPath API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property endpoint
 * @discussion The destination endpoint with which this connection was created.
 */
@property (nonatomic, readonly) NWEndpoint *endpoint API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property connectedPath
 * @discussion The network path over which the connection was established. The caller can query
 *		additional properties from the NWPath object for more information.
 *
 * 		Note that this contains a snapshot of information at the time of connection establishment
 * 		for this connection only. As a result, some underlying properties might change in time and
 * 		might not reflect the path for other connections that might be established at different times.
 */
@property (nonatomic, readonly, nullable) NWPath *connectedPath API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property localAddress
 * @discussion The IP address endpoint from which the connection was connected.
 */
@property (nonatomic, readonly, nullable) NWEndpoint *localAddress API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property remoteAddress
 * @discussion The IP address endpoint to which the connection was connected.
 */
@property (nonatomic, readonly, nullable) NWEndpoint *remoteAddress API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property txtRecord
 * @discussion When the connection is connected to a Bonjour service endpoint, the TXT record associated
 * 		with the Bonjour service is available via this property. Beware that the value comes from
 * 		the network. Care must be taken when parsing this potentially malicious value.
 */
@property (nonatomic, readonly, nullable) NSData *txtRecord API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property error
 * @discussion The connection-wide error property indicates any fatal error that occurred while
 * 		processing the connection or performing data reading or writing.
 */
@property (nonatomic, readonly, nullable) NSError *error API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @method cancel:
 * @discussion Cancel the connection. This will clean up the resources associated with this object
 * 		and transition this object to NWTCPConnectionStateCancelled state.
 */
- (void)cancel API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @method readLength:completionHandler:
 * @discussion Read "length" number of bytes. See readMinimumLength:maximumLength:completionHandler:
 * 		for a complete discussion of the callback behavior.
 * @param length The exact number of bytes the application wants to read
 * @param completion The completion handler to be invoked when there is data to read or an error occurred
 */
- (void)readLength:(NSUInteger)length completionHandler:(void (^)(NSData * _Nullable data, NSError * _Nullable error))completion NS_SWIFT_DISABLE_ASYNC API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @method readMinimumLength:maximumLength:completionHandler:
 *
 * @discussion Read the requested range of bytes. The completion handler will be invoked when:
 * 		- Exactly "length" number of bytes have been read. 'data' will be non-nil.
 *
 * 		- Fewer than "length" number of bytes, including 0 bytes, have been read, and the connection's
 * 		read side has been closed. 'data' might be nil, depending on whether there was any data to be
 * 		read when the connection's read side was closed.
 *
 * 		- Some fatal error has occurred, and 'data' will be nil.
 *
 * 		To know when to schedule a read again, check for the condition whether an error has occurred.
 *
 *		For better performance, the caller should pick the effective minimum and maximum lengths.
 *		For example, if the caller absolutely needs a specific number of bytes before it can
 *		make any progress, use that value as the minimum. The maximum bytes can be the upperbound
 *		that the caller wants to read. Typically, the minimum length can be the caller
 *		protocol fixed-size header and the maximum length can be the maximum size of the payload or
 *		the size of the current read buffer.
 *
 * @param minimum The minimum number of bytes the caller wants to read
 * @param maximum The maximum number of bytes the caller wants to read
 * @param completion The completion handler to be invoked when there is data to read or an error occurred
 */
- (void)readMinimumLength:(NSUInteger)minimum maximumLength:(NSUInteger)maximum completionHandler:(void (^)(NSData * _Nullable data, NSError * _Nullable error))completion NS_SWIFT_DISABLE_ASYNC API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @method write:completionHandler:
 * @discussion Write the given data object content. Callers should wait until the completionHandler is executed
 *		before issuing another write.
 * @param data The data object whose content will be written
 * @param completion The completion handler to be invoked when the data content has been written or an error has occurred.
 * 		If the error is nil, the write succeeded and the caller can write more data.
 */
- (void)write:(NSData *)data completionHandler:(void (^)(NSError * _Nullable error))completion NS_SWIFT_DISABLE_ASYNC API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @method writeClose:
 * @discussion Close this connection's write side such that further write requests won't succeed.
 * 		Note that this has the effect of closing the read side of the peer connection.
 * 		When the connection's read side and write side are closed, the connection is considered
 * 		disconnected and will transition to the appropriate state.
 */
- (void)writeClose API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

@end

/*!
 * @protocol NWTCPConnectionAuthenticationDelegate
 * @discussion Allows the caller to take custom actions on some connection events.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@protocol NWTCPConnectionAuthenticationDelegate <NSObject>
@optional

/*!
 * @method shouldProvideIdentityForConnection:
 * @discussion The caller can implement this optional protocol method to decide whether it
 *		wants to provide the identity for this connection for authentication. If this delegate
 *		method is not implemented, the return value will default to YES if
 *		provideIdentityForConnection:completionHandler: is implemented.
 * @param connection The connection sending this message
 * @return YES to provide the identity for this connection, in which case, the delegate method
 *		provideIdentityForConnection:completionHandler: will be called.
 */
- (BOOL)shouldProvideIdentityForConnection:(NWTCPConnection *)connection API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @method provideIdentityForConnection:completionHandler:
 * @discussion The caller can implement this optional protocol method to provide the identity
 *		and an optional certificate chain to be used for authentication.
 * @param connection The connection sending this message
 * @param completion The completion handler for passing identity and certificate chain to the connection.
 *		The "identity" argument is required and must not be nil. The "certificateChain" argument is optional,
 *		and is an array of one or more SecCertificateRef objects. The certificate chain must contain objects
 *		of type SecCertificateRef only. If the certificate chain is set, it will be used. Otherwise, the leaf
 *		certificate will be extracted from the SecIdentityRef object and will be used for authentication.
 *
 *		The caller is responsible for keeping the argument object(s) alive for the duration of the
 *		completion handler invocation.
 */
- (void)provideIdentityForConnection:(NWTCPConnection *)connection
				   completionHandler:(void (^)(SecIdentityRef identity, NSArray<id> *certificateChain))completion NS_SWIFT_DISABLE_ASYNC API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @method shouldEvaluateTrustForConnection:
 * @discussion The caller can implement this optional protocol method to decide whether it
 *		wants to take over the default trust evaluation for this connection. If this delegate method
 *		is not implemented, the return value will default to YES if
 *		provideIdentityForConnection:completionHandler: is implemented.
 * @param connection The connection sending this message
 * @return YES to take over the default trust evaluation, in which case, the delegate method
 *		evaluateTrustForConnection:peerCertificateChain:completionHandler: will be called.
 */
- (BOOL)shouldEvaluateTrustForConnection:(NWTCPConnection *)connection API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @method evaluateTrustForConnection:peerCertificateChain:completionHandler:
 * @discussion The caller can implement this optional protocol method to set up custom policies
 *		for peer certificate trust evaluation. If the delegate method is implemented, the caller
 *		is responsible for creating and setting up the SecTrustRef object and passing it to the
 *		completion handler. Otherwise, the default trust evaluation policy is used for the connection.
 * @param connection The connection sending this message
 * @param peerCertificateChain The peer certificate chain
 * @param completion The completion handler for passing the SecTrustRef object to the connection.
 *		The SecTrustRef object "trust" is required and must not be nil. It will be evaluated using
 *		SecTrustEvaluate() if necessary. The caller is responsible for keeping the argument object
 *		alive for the duration of the completion handler invocation.
 */
- (void)evaluateTrustForConnection:(NWTCPConnection *)connection
			  peerCertificateChain:(NSArray<id> *)peerCertificateChain
				 completionHandler:(void (^)(SecTrustRef trust))completion NS_SWIFT_DISABLE_ASYNC API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END

#endif // __NWTCPConnection_h_

#endif // __NE_TAPI__
