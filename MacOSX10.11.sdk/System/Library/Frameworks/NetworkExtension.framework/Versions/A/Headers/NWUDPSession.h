//
//  NWUDPSession.h
//  Network
//
//  Copyright (c) 2014, 2015 Apple. All rights reserved.
//

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

@class NWEndpoint;
@class NWPath;

/*!
 * @typedef NWUDPSessionState
 * @abstract UDP session state values
 */
typedef NS_ENUM(NSInteger, NWUDPSessionState) {
	/*! @constant NWUDPSessionStateInvalid The session is in an invalid or uninitialized state. */
	NWUDPSessionStateInvalid = 0,
	/*! @constant NWUDPSessionStateWaiting The session is waiting for better conditions before
	 *		attempting to make the session ready.
	 */
	NWUDPSessionStateWaiting = 1,
	/*! @constant NWUDPSessionStatePreparing The endpoint is being resolved */
	NWUDPSessionStatePreparing = 2,
	/*! @constant NWUDPSessionStateReady The session is ready for reading and writing data */
	NWUDPSessionStateReady = 3,
	/*! @constant NWUDPSessionStateFailed None of the currently resolved endpoints can be used
	 *		at this time, either due to problems with the path or the client rejecting the
	 *		endpoints.
	 */
	NWUDPSessionStateFailed = 4,
	/*! @constant NWUDPSessionStateCancelled The session has been cancelled by the client */
	NWUDPSessionStateCancelled = 5,
} NS_AVAILABLE(10_11, 9_0);

/*!
 * @interface NWUDPSession
 * @discussion Open UDP datagram sessions to an endpoint, and send and receive datagrams.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NWUDPSession : NSObject

/*!
 * @method initWithUpgradeForSession:
 * @discussion This convenience initializer can be used to create a new session based on the
 *		original session's endpoint and parameters.
 *
 *		The application should create an NWUDPSession and watch the "hasBetterPath" property. 
 *		When this property is YES, it should call initWithUpgradeForSession: to create a new
 *		session, with the goal to start transferring data on the new better path as soon as
 *		possible to reduce power and potentially monetary cost. When the new "upgrade" session
 *		becomes ready and when the application wraps up the previous application session on
 *		the original session, the application can start using the new "upgrade" session and
 *		tear down the original one.
 *
 * @param session The original session from which the application will upgrade
 * @return An initialized NWUDPSession object.
 */
- (instancetype)initWithUpgradeForSession:(NWUDPSession *)session NS_AVAILABLE(10_11, 9_0);

/*!
 * @property state
 * @discussion The current state of the UDP session. If the state is NWUDPSessionStateReady, 
 *		then the connection is eligible for reading and writing. The state will be
 *		NWUDPSessionStateFailed if the endpoint could not be resolved, or all endpoints have been 
 *		rejected. Use KVO to watch for changes.
 */
@property (readonly) NWUDPSessionState state NS_AVAILABLE(10_11, 9_0);

/*!
 * @property endpoint
 * @discussion The provided endpoint.
 */
@property (readonly) NWEndpoint *endpoint NS_AVAILABLE(10_11, 9_0);

/*!
 * @property resolvedEndpoint
 * @discussion The currently targeted remote endpoint. Use KVO to watch for changes.
 */
@property (readonly, nullable) NWEndpoint *resolvedEndpoint NS_AVAILABLE(10_11, 9_0);

/*!
 * @property viable
 * @discussion YES if the connection can read and write data, NO otherwise. 
 *		Use KVO to watch this property.
 */
@property (readonly, getter=isViable) BOOL viable NS_AVAILABLE(10_11, 9_0);

/*!
 * @property hasBetterPath
 * @discussion YES if there is another path available that is preferred over the currentPath. 
 *		To take advantage of this path, create a new UDPSession. Use KVO to watch for changes.
 */
@property (readonly) BOOL hasBetterPath NS_AVAILABLE(10_11, 9_0);

/*!
 * @property currentPath
 * @discussion The current evaluated path for the resolvedEndpoint. Use KVO to watch for changes.
 */
@property (readonly, nullable) NWPath *currentPath NS_AVAILABLE(10_11, 9_0);

/*!
 * @method tryNextResolvedEndpoint
 * @discussion Mark the current value of resolvedEndpoint as unusable, and try to switch to the 
 *		next available endpoint. This should be used when the caller has attempted to communicate
 *		with the current resolvedEndpoint, and the caller has determined that it is unusable. If
 *		there are no other resolved endpoints, the session will move to the failed state.
 */
- (void)tryNextResolvedEndpoint NS_AVAILABLE(10_11, 9_0);

/*!
 * @property maximumDatagramLength
 * @discussion The maximum size of a datagram to be written currently. If a datagram is written
 *		with a longer length, the datagram may be fragmented or encounter an error. Note that this
 *		value is not guaranteed to be the maximum datagram length for end-to-end communication 
 *		across the network. Use KVO to watch for changes.
 */
@property (readonly) NSUInteger maximumDatagramLength NS_AVAILABLE(10_11, 9_0);

/*!
 * @method setReadHandler:maxDatagrams
 * @discussion Set a read handler for datagrams. Reads will be scheduled by the system, so this
 *		method only needs to be called once for a session.
 * @param handler A handler called when datagrams have been read, or when an error has occurred.
 * @param minDatagrams The maximum number of datagrams to send to the handler.
 */
- (void)setReadHandler:(void (^)(NSArray<NSData *> * __nullable datagrams, NSError * __nullable error))handler
		  maxDatagrams:(NSUInteger)maxDatagrams NS_AVAILABLE(10_11, 9_0);

/*!
 * @method writeMultipleDatagrams:completionHandler
 * @discussion Write multiple datagrams. Callers should wait until the completionHandler is executed
 *		before issuing another write.
 * @param datagram An NSArray of NSData objects, containing the ordered list datagrams to write.
 * @param completionHandler A handler called when the write request has either succeeded or failed.
 */
- (void)writeMultipleDatagrams:(NSArray<NSData *> *)datagramArray
			 completionHandler:(void (^)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 * @method writeDatagram:completionHandler
 * @discussion Write a single datagram. Callers should wait until the completionHandler is executed
 *		before issuing another write.
 * @param datagram An NSData containing the datagram to write.
 * @param completionHandler A handler called when the write request has either succeeded or failed.
 */
- (void)writeDatagram:(NSData *)datagram
	completionHandler:(void (^)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 * @method cancel
 * @discussion Move into the NWUDPSessionStateCancelled state. The connection will be terminated,
 *		and all handlers will be cancelled.
 */
- (void)cancel NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END
