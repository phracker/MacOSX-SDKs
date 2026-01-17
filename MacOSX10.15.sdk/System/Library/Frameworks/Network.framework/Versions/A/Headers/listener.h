//
//  listener.h
//  Network
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_LISTENER_H__
#define __NW_LISTENER_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/connection.h>
#include <Network/advertise_descriptor.h>
#include <Network/error.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @typedef nw_listener_t
 * @abstract
 *		A Network Listener is an object that is able to receive incoming nw_connection_t
 *		objects by binding to a local endpoint. A listener will accept connections based
 *		on the protocols defined in its stack. For transport listeners (such as TCP and UDP),
 *		accepted connections will represent new local and remote address and port tuples.
 *		For listeners that include higher-level protocols that support multiplexing,
 *		accepted connections will represent multiplexed streams on a new or existing transport
 *		binding.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_LISTENER_IMPL
NW_OBJECT_DECL(nw_listener);
#endif // NW_LISTENER_IMPL

/*!
 * @typedef nw_listener_state_t
 * @abstract
 *		Listener states sent by nw_listener_set_state_changed_handler.
 *		States progress forward and do not move backwards.
 */
typedef enum {
	/*!
	 *	@const nw_listener_state_invalid The state of the listener is not valid. This state
	 *		will never be delivered in the listener's state update handler, and can be treated as
	 *		an unexpected value.
	 */
	nw_listener_state_invalid = 0,
	/*! @const nw_listener_state_waiting The listener is waiting for a usable network before being able to receive connections */
	nw_listener_state_waiting = 1,
	/*! @const nw_listener_state_ready The listener is ready and able to accept incoming connections */
	nw_listener_state_ready = 2,
	/*! @const nw_listener_state_failed The listener has irrecoverably closed or failed */
	nw_listener_state_failed = 3,
	/*! @const nw_listener_state_cancelled The listener has been cancelled by the caller */
	nw_listener_state_cancelled = 4,
} nw_listener_state_t;

/*!
 * @function nw_listener_create_with_port
 *
 * @abstract
 *		Creates a networking listener bound to a specified local port.
 *
 * @param port
 *		A port number as a C string, such as "443", or a service
 *		name, such as "https".
 *
 * @param parameters
 *		The parameters to use for the listener. These include the protocols to be
 *		used for the listener.
 *
 * @result
 *		Returns an allocated nw_listener_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED _Nullable nw_listener_t
nw_listener_create_with_port(const char *port, nw_parameters_t parameters);

/*!
 * @function nw_listener_create
 *
 * @abstract
 *		Creates a networking listener. The listener will be assigned a random
 *		port upon which to listen unless otherwise specified by the parameters.
 *
 * @param parameters
 *		The parameters to use for the listener. These include the protocols to be
 *		used for the listener.
 *
 * @result
 *		Returns an allocated nw_listener_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED _Nullable nw_listener_t
nw_listener_create(nw_parameters_t parameters);

/*!
 * @function nw_listener_create_with_connection
 *
 * @abstract
 *		Creates a networking listener based on an existing
 *		multiplexing connection. If there are multiple protocols
 *		in the connection that support listening for incoming flows,
 *		the listener will be hooked up the highest in the stack
 *		(the closest to the reading and writing of the client data).
 *
 * @param connection
 *		An existing connection that has a multiplexing protocol
 *		that supports receiving new connections.
 *
 * @param parameters
 *		The parameters to use for the listener. The protocol stack
 *		defined in the parameters must be able to join a protocol
 *		in the connection that supports listening protocols.
 *
 * @result
 *		Returns an allocated nw_listener_t object on success. Use nw_release() to deallocate.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED _Nullable nw_listener_t
nw_listener_create_with_connection(nw_connection_t connection,
								   nw_parameters_t parameters);

/*!
 * @function nw_listener_set_queue
 *
 * @abstract
 *		Sets the client callback queue, on which blocks for events will
 *		be scheduled. This must be done before calling nw_listener_start().
 *
 * @param listener
 *		The listener object.
 *
 * @param queue
 *		The client's dispatch queue.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_listener_set_queue(nw_listener_t listener,
					  dispatch_queue_t queue);

#ifdef __BLOCKS__

typedef void (^nw_listener_state_changed_handler_t)(nw_listener_state_t state, _Nullable nw_error_t error);

/*!
 * @function nw_listener_set_state_changed_handler
 *
 * @abstract
 *		Sets the state change handler. For clients that need to perform cleanup when the
 *		connection has been cancelled, the nw_listener_state_cancelled state will
 *		be delivered last.
 *
 * @param listener
 *		The listener object.
 *
 * @param handler
 *		The state changed handler to call when the listener state changes.
 *		Pass NULL to remove the event handler.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_listener_set_state_changed_handler(nw_listener_t listener,
									  _Nullable nw_listener_state_changed_handler_t handler);

/*!
 * @typedef nw_listener_new_connection_handler_t
 *
 * @abstract
 *		The block called to notify client of a new connection.
 *
 * @param connection
 *		The new connection object. This connection is not yet started. Set the
 *		event handler and other settings on the connection before calling start.
 */
typedef void (^nw_listener_new_connection_handler_t)(nw_connection_t connection);

/*!
 * @function nw_listener_set_new_connection_handler
 *
 * @abstract
 *		Sets the client new connection handler. Must be called before
 *		nw_listener_start.
 *
 * @param listener
 *		The listener object.
 *
 * @param handler
 *		The event handler to call when the listener receives a new connection.
 *		Pass NULL to remove the new connection handler.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_listener_set_new_connection_handler(nw_listener_t listener,
									   _Nullable nw_listener_new_connection_handler_t handler);

#endif // __BLOCKS__

/*!
 * @define NW_LISTENER_INFINITE_CONNECTION_LIMIT
 * @discussion This value indicates that a listener should not limit incoming connections
 */
#define NW_LISTENER_INFINITE_CONNECTION_LIMIT UINT32_MAX

/*!
 * @function nw_listener_get_new_connection_limit
 *
 * @abstract
 *		Gets the listener new connection limit. The default value is
 *      NW_LISTENER_INFINITE_CONNECTION_LIMIT which indicates that
 *      the listener should not limit incoming connections. If the value
 *      is not NW_LISTENER_INFINITE_CONNECTION_LIMIT, it will be decremented
 *      by 1 every time a new connection is created. When the value becomes
 *      0, new connection handlers will no longer be invoked until
 *      nw_listener_set_new_connection_limit() is invoked with a value
 *      that is greater than 0. Incoming connections will eventually be rejected
 *      if nw_listener_set_new_connection_limit() is not called after the connection
 *      limit reaches 0.
 *
 * @param listener
 *		The listener object.
 *
 * @result
 *		Returns current new connection limit
 */
API_AVAILABLE(macos(10.15), ios(12.0), watchos(5.0), tvos(12.0))
uint32_t
nw_listener_get_new_connection_limit(nw_listener_t listener);

/*!
 * @function nw_listener_set_new_connection_limit
 *
 * @abstract
 *		Sets the listener new connection limit. Use the value NW_LISTENER_INFINITE_CONNECTION_LIMIT
 *      to disable connection limits. If the value is not NW_LISTENER_INFINITE_CONNECTION_LIMIT,
 *      it will be decremented by 1 every time a new connection is created. When the value becomes
 *      0, new connection handlers will no longer be invoked until
 *      nw_listener_set_new_connection_limit() is invoked with a value
 *      that is greater than 0. Incoming connections will eventually be rejected
 *      if nw_listener_set_new_connection_limit() is not called after the connection
 *      limit reaches 0.
 *
 * @param listener
 *		The listener object.
 *
 * @param new_connection_limit
 *		The new connection limit. Pass NW_LISTENER_INFINITE_CONNECTION_LIMIT
 *      to disable new connection limiting.
 */
API_AVAILABLE(macos(10.15), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_listener_set_new_connection_limit(nw_listener_t listener,
									 uint32_t new_connection_limit);

/*!
 * @function nw_listener_set_advertise_descriptor
 *
 * @abstract
 *		Describes the bonjour service the listener should register. Setting the
 *		advertise descriptor more than once may be used to update the TXT record.
 *
 * @param listener
 *		The listener object.
 *
 * @param advertise_descriptor
 *		The advertise_descriptor or NULL to prevent or remove registration of a service.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_listener_set_advertise_descriptor(nw_listener_t listener,
									 _Nullable nw_advertise_descriptor_t advertise_descriptor);

#ifdef __BLOCKS__

/*!
 * @typedef nw_listener_advertised_endpoint_changed_handler_t
 *
 * @abstract
 *		A block called to notify client of a change in advertised endpoints.
 *
 * @param advertised_endpoint
 *		An endpoint that is has been added or removed from the list of advertised
 *		endpoints for the listener.
 *
 * @param added
 *		A boolean indicating if the endpoint is being added or removed. If added,
 *		the value with be true; if removed, the value will be false.
 */
typedef void (^nw_listener_advertised_endpoint_changed_handler_t)(nw_endpoint_t advertised_endpoint,
																  bool added);

/*!
 * @function nw_listener_set_advertised_endpoint_changed_handler
 *
 * @abstract
 *		Sets the client advertised endpoint changed handler. The handler will be
 *		invoked for listeners which have called nw_listener_set_advertise_descriptor().
 *
 * @param listener
 *		The listener object.
 *
 * @param handler
 *		The event handler to call when the listener adds or removes an advertised endpoint.
 *		Pass NULL to remove the handler.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_listener_set_advertised_endpoint_changed_handler(nw_listener_t listener,
													_Nullable nw_listener_advertised_endpoint_changed_handler_t handler);

#endif // __BLOCKS__

/*!
 * @function nw_listener_get_port
 *
 * @abstract
 *		Gets the local port as a number in host byte order. If the listener was created with a
 *		port of 0 (let the system assign a port), nw_listener_get_port will return 0 until the
 *		listener is in the ready state.
 *
 * @param listener
 *		The listener to get the local port of.
 *
 * @result
 *		Returns a port in host byte order.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
uint16_t
nw_listener_get_port(nw_listener_t listener);

/*!
 * @function nw_listener_start
 *
 * @abstract
 *		Starts the listener, which will cause the listener
 *		to start listening for inbound connections.
 *
 * @param listener
 *		The listener object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_listener_start(nw_listener_t listener);

/*!
 * @function nw_listener_cancel
 *
 * @abstract
 *		Cancel the listener. This will de-register the listener from the system. The process
 *		of cancellation will be completed asynchronously, and the final callback event
 *		delivered to the caller will be a state update with a value of nw_listener_state_cancelled.
 *		Once this update is delivered, the caller may clean up any associated memory or objects.
 *
 * @param listener
 *		The listener object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_listener_cancel(nw_listener_t listener);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif /* __NW_LISTENER_H__ */
