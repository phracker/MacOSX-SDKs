//
//  connection.h
//  Network
//
//  Copyright (c) 2015-2018 Apple Inc. All rights reserved.
//

#ifndef __NW_CONNECTION_H__
#define __NW_CONNECTION_H__

#include <Network/endpoint.h>
#include <Network/parameters.h>
#include <Network/path.h>
#include <Network/content_context.h>
#include <Network/error.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @typedef nw_connection_t
 * @abstract
 *		A Network Connection is an object that represents a bi-directional data pipe between
 *		a local endpoint and a remote endpoint. A connection handles establishment of any
 *		transport, security, or application-level protocols required to transmit and receive
 *		user data. Multiple protocol instances may be attempted during the establishment phase
 *		of the connection. Multiple connections may be multiplexed over a single transport
 *		if they make use of a protocol that supports multiplexing.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_CONNECTION_IMPL
NW_OBJECT_DECL(nw_connection);
#endif // NW_CONNECTION_IMPL

/*!
 * @typedef nw_connection_state_t
 * @abstract
 *		Connection states sent by nw_connection_set_state_changed_handler.
 *		States generally progress forward and do not move backwards, with the
 *		exception of preparing and waiting, which may alternate before the connection
 *		becomes ready or failed.
 */
typedef enum {
	/*!
	 *	@const nw_connection_state_invalid The state of the connection is not valid. This state
	 *		will never be delivered in the connection's state update handler, and can be treated as
	 *		an unexpected value.
	 */
	nw_connection_state_invalid = 0,
	/*! @const nw_connection_state_waiting The connection is waiting for a usable network before re-attempting */
	nw_connection_state_waiting = 1,
	/*! @const nw_connection_state_preparing The connection is in the process of establishing */
	nw_connection_state_preparing = 2,
	/*! @const nw_connection_state_ready The connection is established and ready to send and receive data upon */
	nw_connection_state_ready = 3,
	/*! @const nw_connection_state_failed The connection has irrecoverably closed or failed */
	nw_connection_state_failed = 4,
	/*! @const nw_connection_state_cancelled The connection has been cancelled by the caller */
	nw_connection_state_cancelled = 5,
} nw_connection_state_t;

/*!
 * @function nw_connection_create
 *
 * @abstract
 *		Creates a networking connection to an endpoint.
 *
 * @param endpoint
 *		The remote endpoint to connect to.
 *
 * @param parameters
 *		The parameters to use for the connection. The data mode,
 *		either datagram or stream, must be set.
 *
 * @result
 *		Returns an allocated nw_connection_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_connection_t
nw_connection_create(nw_endpoint_t endpoint,
					 nw_parameters_t parameters);

/*!
 * @function nw_connection_copy_endpoint
 *
 * @abstract
 *		Retrieves the remote endpoint for a connection.
 *
 * @param connection
 *		The connection object.
 *
 * @result
 *		Returns an nw_endpoint_t object on success.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_endpoint_t
nw_connection_copy_endpoint(nw_connection_t connection);

/*!
 * @function nw_connection_copy_parameters
 *
 * @abstract
 *		Retrieves the parameters for a connection.
 *
 * @param connection
 *		The connection object.
 *
 * @result
 *		Returns an nw_parameters_t object on success.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_parameters_t
nw_connection_copy_parameters(nw_connection_t connection);

#ifdef __BLOCKS__

typedef void (^nw_connection_state_changed_handler_t)(nw_connection_state_t state,
													  _Nullable nw_error_t error);

/*!
 * @function nw_connection_set_state_changed_handler
 *
 * @abstract
 *		Sets the state change handler. For clients that need to perform cleanup when the
 *		connection has been cancelled, the nw_connection_state_cancelled state will
 *		be delivered last.
 *
 * @param connection
 *		The connection object.
 *
 * @param handler
 *		The state changed handler to call when the connection state changes.
 *		Pass NULL to remove the state changed handler.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_set_state_changed_handler(nw_connection_t connection,
								_Nullable nw_connection_state_changed_handler_t handler);

typedef void (^nw_connection_boolean_event_handler_t)(bool value);

/*!
 * @function nw_connection_set_viability_changed_handler
 *
 * @abstract
 *		Define a callback to be fired when the viability of the connection changes.
 *		This indicates whether or not read and write calls will succeed on a ready
 *		connection.
 *
 * @param connection
 *		The connection object.
 *
 * @param handler
 *		The event handler to call when the connection viability changes. The value will
 *		be true when the connection is viable, and false otherwise.
 *		Pass NULL to remove the event handler.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_set_viability_changed_handler(nw_connection_t connection,
											_Nullable nw_connection_boolean_event_handler_t handler);

/*!
 * @function nw_connection_set_better_path_available_handler
 *
 * @abstract
 *		Define a callback to be fired when a better path is available or not.
 *		This indicates whether or not a preferred path is available for the
 *		connection.
 *
 * @param connection
 *		The connection object.
 *
 * @param handler
 *		The event handler to call when the better path availability changes. The value
 *		will be true when a better path is available, and false otherwise.
 *		Pass NULL to remove the event handler.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_set_better_path_available_handler(nw_connection_t connection,
												_Nullable nw_connection_boolean_event_handler_t handler);

typedef void (^nw_connection_path_event_handler_t)(nw_path_t path);

/*!
 * @function nw_connection_set_path_changed_handler
 *
 * @abstract
 *		Define a callback to be fired when the connection's path changes.
 *
 * @param connection
 *		The connection object.
 *
 * @param handler
 *		The event handler to call when the connection's path changes.
 *		Pass NULL to remove the event handler.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_set_path_changed_handler(nw_connection_t connection,
									   _Nullable nw_connection_path_event_handler_t handler);
#endif // __BLOCKS__

/*!
 * @function nw_connection_set_queue
 *
 * @abstract
 *		Sets the client callback queue, on which blocks for events will
 *		be scheduled. This must be done before calling nw_connection_start().
 *
 * @param connection
 *		The connection object.
 *
 * @param queue
 *		The client's dispatch queue.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_set_queue(nw_connection_t connection,
						dispatch_queue_t queue);

/*!
 * @function nw_connection_start
 *
 * @abstract
 *		Starts the connection, which will cause the connection
 *		to evaluate its path, do resolution, and try to become
 *		readable and writable.
 *
 * @param connection
 *		The connection object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_start(nw_connection_t connection);

/*!
 * @function nw_connection_restart
 *
 * @abstract
 *		Connections in the waiting state will normally re-attempt
 *		on network changes. Call nw_connection_restart() to force
 *		a connection in the waiting state to retry connection
 *		establishment even without a network change. Calls to restart
 *		for connections that are not in the waiting state will be
 *		ignored.
 *
 * @param connection
 *		The connection object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_restart(nw_connection_t connection);

/*!
 * @function nw_connection_cancel
 *
 * @abstract
 *		Cancel the connection. This will close the connection, and negotiate over the network
 *		if applicable for the protocol. The process of cancellation will be completed
 *		asynchronously, and the final callback event delivered to the caller will be a state
 *		update with a value of nw_listener_state_cancelled. Once this update is delivered, the
 *		caller may clean up any associated memory or objects.
 *
 *		Outstanding sends and receives will receive errors before the state changes to cancelled.
 *		There is no guarantee that any outstanding sends that have not yet send completion handlers
 *		will send data before the connection is closed.
 *
 * @param connection
 *		The connection object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_cancel(nw_connection_t connection);

/*!
 * @function nw_connection_force_cancel
 *
 * @abstract
 *		A variant of nw_connection_cancel() that indicates that the protocol stack should
 *		not close gracefully, but close as quickly as possible without negotiation. For example,
 *		a force close would lead to TCP RST packets being sent, as opposed to negotiating with
 *		FIN packets.
 *
 * @param connection
 *		The connection object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_force_cancel(nw_connection_t connection);

/*!
 * @function nw_connection_cancel_current_endpoint
 *
 * @abstract
 *		Cancel the currently connected endpoint, causing the connection
 *		to fall through to the next endpoint if available, or fail if no
 *		more endpoints are available. This is primarily useful for connections
 *		which do not have reliable handshakes, such as UDP. If data is sent
 *		on the connection with no response, canceling the current endpoint
 *		will allow another address or interface to be attempted.
 *
 * @param connection
 *		The connection object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_cancel_current_endpoint(nw_connection_t connection);

#ifdef __BLOCKS__

/*!
 * @typedef nw_connection_receive_completion_t
 * @abstract
 *		A receive completion is invoked exactly once for a call to nw_connection_receive().
 *		The completion indicates that the requested content has been received (in which case
 *		the content is delivered), or else an error has occurred.
 *
 * @param content
 *		The received content, which has a length constrained by the call to nw_connection_receive().
 *		The content may be NULL in two cases: (1) the receieve context (logical message) is now complete,
 *		and the callback is only delivering the completed event; or, (2) the connection encountered
 *		an error and there is no data to deliver. Note that the content may be non-NULL even in the
 *		case of an error if there was some data received before the error was encountered. The caller
 *		should process all content it receives, and not necessarily ignore data in case of errors.
 *
 * @param context
 *		The context (logical message) associated with the received content. This includes protocol metadata
 *		that lets the caller introspect information about the received content (such as flags on an IP packet).
 *		When the message has been completely received, the context will be delivered along with the
 *		is_complete flag.
 *
 *		For datagram protocols such as UDP, the context represents the properties of a single received
 *		datagram.
 *
 *		For protocols that only have a single context for the entire connection, such as stream protocols
 *		like TCP, the context will be marked as "final", which can be accessed with
 *		nw_content_context_get_is_final(). Once a final context is marked as complete, the recipient
 *		may assume that the connection has been closed in the receiving direction (a "read close"). For
 *		TCP, this represents receiving a FIN.
 *
 * @param is_complete
 *		An indication that this context (logical message) is now complete. Until this flag is
 *		set, the recipient should assume that there may be more bytes to read for this context.
 *		Note that even when reading datagrams, as from UDP, the context may be read in multiple
 *		chunks if the maximum_length was smaller than the full length of the message.
 *
 *		If is_complete is marked and the received context is the final context for connection,
 *		the caller may assume that the connection has been closed in the receiving direction.
 *
 * @param error
 *		An error will be sent if an error was encountered while trying to receive on the connection.
 *		There may still be content delivered along with the error, but this content may be shorter
 *		than the requested ranges. An error will be sent for any outstanding receive calls when the
 *		connection is cancelled.
 */
typedef void (^nw_connection_receive_completion_t)(_Nullable dispatch_data_t content,
												   _Nullable nw_content_context_t context,
												   bool is_complete,
												   _Nullable nw_error_t error);
/*!
 * @function nw_connection_receive
 *
 * @abstract
 *		Receive data from a connection. This may be called before the connection
 *		is ready, in which case the receive request will be queued until the
 *		connection is ready. The completion handler will be invoked exactly
 *		once for each call, so the client must call this function multiple
 *		times to receive multiple chunks of data. For protocols that
 *		support flow control, such as TCP, calling receive opens the receive
 *		window. If the client stops calling receive, the receive window will
 *		fill up and the remote peer will stop sending.
 *
 * @param connection
 *		The connection object on which to receive data. The connection should
 *		be in the ready state.
 *
 * @param minimum_incomplete_length
 *		The minimum length to receive from the connection, until the content
 *		is complete. Content will be delivered when at least the minimum is available,
 *		or the content is complete, whichever comes first.
 *
 * @param maximum_length
 *		The maximum length to receive from the connection.
 *
 * @param completion
 *		A callback to be called when content has been received.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_receive(nw_connection_t connection,
					  uint32_t minimum_incomplete_length,
					  uint32_t maximum_length,
					  nw_connection_receive_completion_t completion);

/*!
 * @function nw_connection_receive_message
 *
 * @abstract
 *		Receive a single atomic message from a connection. The completion
 *		handler will be invoked exactly once for each call, so the client
 *		must call this function multiple times to receive multiple messages.
 *
 * @param connection
 *		The connection object on which to receive the message. The connection
 *		should be in the ready state.
 *
 * @param completion
 *		A callback to be called when the message has been received, or an error
 *		has occurred.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_receive_message(nw_connection_t connection,
							  nw_connection_receive_completion_t completion);

/*!
 * @typedef nw_connection_send_completion_t
 * @abstract
 *		A send completion is invoked exactly once for a call to nw_connection_send().
 *		The completion indicates that the sent content has been processed by the stack
 *		(not necessarily that it has left the host), or else an error has occurred during
 *		sending.
 *
 * @param error
 *		An error will be sent if the associated content could not be fully sent before an
 *		error occurred. An error will be sent for any outstanding sends when the connection
 *		is cancelled.
 */
typedef void (^nw_connection_send_completion_t)(_Nullable nw_error_t error);

#define NW_CONNECTION_SEND_TYPE_DECL(name) \
	extern const nw_connection_send_completion_t _nw_connection_send_##name

/*!
 * @const NW_CONNECTION_SEND_IDEMPOTENT_CONTENT
 * @discussion A send callback override that causes the write call to
 *		be treated as idempotent. Idempotent content is allowed to be sent
 *		before the connection is ready, and may be replayed across parallel connection
 *		attempts. This content can be sent as part of fast-open protocols, which allows
 *		the data to be sent out sooner than if it were required to wait for
 *		connection establishment.
 *
 *		This override intentionally disallows the client from receiving callbacks
 *		for the write calls, since the content may be sent multiple times internally.
 *		For any large content, or content that need to be sensitive to sending backpressure,
 *		an explicit callback should be used.
 */
#define NW_CONNECTION_SEND_IDEMPOTENT_CONTENT (_nw_connection_send_idempotent_content)
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_CONNECTION_SEND_TYPE_DECL(idempotent_content);

#define NW_CONTENT_CONTEXT_TYPE_DECL(name) \
	extern const nw_content_context_t _nw_content_context_##name

/*!
 * @const NW_CONNECTION_DEFAULT_MESSAGE_CONTEXT
 * @discussion Use the default message context to send content with all default properties:
 *		default priority, no expiration, and not the final message. Marking this context
 *		as complete with a send indicates that the message content is now complete and any
 *		other messages that were blocked may be scheduled, but will not close the underlying
 *		connection. Use this context for any lightweight sends of datagrams or messages on
 *		top of a stream that do not require special properties.
 *
 *		This context does not support overriding any properties.
 */
#define NW_CONNECTION_DEFAULT_MESSAGE_CONTEXT (_nw_content_context_default_message)
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_CONTENT_CONTEXT_TYPE_DECL(default_message);

/*!
 * @const NW_CONNECTION_FINAL_MESSAGE_CONTEXT
 * @discussion Use the final message context to indicate that no more sends are expected
 *		once this context is complete. Like NW_CONNECTION_DEFAULT_MESSAGE_CONTEXT, all
 *		properties are default. Marking a send as complete when using this context will close
 *		the sending side of the underlying connection. This is the equivalent of sending a FIN
 *		on a TCP stream.
 *
 *		This context does not support overriding any properties.
 */
#define NW_CONNECTION_FINAL_MESSAGE_CONTEXT (_nw_content_context_final_send)
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_CONTENT_CONTEXT_TYPE_DECL(final_send);

/*!
 * @const NW_CONNECTION_DEFAULT_STREAM_CONTEXT
 * @discussion Use the default stream context to indicate that this sending context is
 *		the one that represents the entire connection. All context properties are default.
 *		This context behaves in the same way as NW_CONNECTION_FINAL_MESSAGE_CONTEXT, such
 *		that marking the context complete by sending is_complete will close the sending
 *		side of the underlying connection (a FIN for a TCP stream).
 *
 *		Note that this context is a convenience for sending a single, final context.
 *		If the protocol used by the connection is a stream (such as TCP), the caller
 *		may still use NW_CONNECTION_DEFAULT_MESSAGE_CONTEXT, NW_CONNECTION_FINAL_MESSAGE_CONTEXT,
 *		or a custom context with priorities and metadata to set properties of a particular
 *		chunk of stream data relative to other data on the stream.
 *
 *		This context does not support overriding any properties.
 */
#define NW_CONNECTION_DEFAULT_STREAM_CONTEXT (_nw_content_context_default_stream)
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_CONTENT_CONTEXT_TYPE_DECL(default_stream);

/*!
 * @function nw_connection_send
 *
 * @abstract
 *		Send data on a connection. This may be called before the connection is ready,
 *		in which case the send will be enqueued until the connection is ready to send.
 *		This is an asynchronous send and the completion block can be used to
 *		determine when the send is complete. There is nothing preventing a client
 *		from issuing an excessive number of outstanding sends. To minmize memory
 *		footprint and excessive latency as a consequence of buffer bloat, it is
 *		advisable to keep a low number of outstanding sends. The completion block
 *		can be used to pace subsequent sends.
 *
 * @param connection
 *		The connection object on which to send data.
 *
 * @param content
 *		A data object to send. This may be NULL only if this send is marking a context
 *		(a message or complete connection) as complete in the sending direction.
 *
 * @param context
 *		The context associated with the content, which represents a logical message
 *		to be sent on the connection. All content sent within a single context will
 *		be sent as an in-order unit, up until the point that the context is marked
 *		complete (see is_complete). Once a context is marked complete, it may be re-used
 *		as a new logical message. Protocols like TCP that cannot send multiple
 *		independent messages at once (serial streams) will only start processing a new
 *		context once the prior context has been marked complete.
 *
 *		The context can hold protocol metadata to define how to send content, such
 *		as flags for IP packets.
 *
 *		The context also can define properties that allow a message to ordered relative
 *		to other messages if multiple messages are queued. These properties include
 *		relative priority, expiration, and antecedent relationships. Some protocols
 *		support re-ordering messages within a single connection. For other protocols
 *		that do not, like TCP, these properties still take effect when enqueuing data
 *		into the stream's send buffer. The ordering of messages applies to the first
 *		calls to send on a given context.
 *
 *		In order to close a connection on the sending side (a "write close"), send
 *		a context that is marked as "final" and mark is_complete. The convenience definition
 *		NW_CONNECTION_FINAL_MESSAGE_CONTEXT may be used to define the default final context
 *		for a connection. If the caller wants to treat the entire connection as a single
 *		stream, with only one context, set NW_CONNECTION_FINAL_MESSAGE_CONTEXT for all
 *		sends; marking is_complete on the final send call will send a "write close".
 *		Using NW_CONNECTION_DEFAULT_STREAM_CONTEXT has the same behavior as sending
 *		NW_CONNECTION_FINAL_MESSAGE_CONTEXT.
 *
 *		To send basic datagrams on a connection, use NW_CONNECTION_DEFAULT_MESSAGE_CONTEXT
 *		and pass is_complete as true for each datagram.
 *
 *		To send data as a single stream on a connection, use NW_CONNECTION_DEFAULT_STREAM_CONTEXT
 *		and pass is_complete as true only to mark the end of the stream.
 *
 * @param is_complete
 *		A flag indicating if the caller's sending context (logical message) is now complete.
 *
 *		Until a context is marked complete, content sent for other contexts may not
 *		be sent immediately (if the protocol requires sending bytes serially, like TCP).
 *
 *		For datagram protocols, like UDP, is_complete indicates that the content represents
 *		a complete datagram.
 *
 *		When sending directly on streaming protocols like TCP, is_complete can be used to
 *		indicate that the connection should send a "write close" (a TCP FIN) if the sending
 *		context is the final context on the connection. Specifically, to send a "write close",
 *		pass NW_CONNECTION_FINAL_MESSAGE_CONTEXT or NW_CONNECTION_DEFAULT_STREAM_CONTEXT for the
 *		context (or create a custom context and set nw_content_context_set_is_final()), and pass
 *		true for is_complete.
 *
 * @param completion
 *		A callback to be called when the data has been sent, or an error has occurred.
 *		This callback does not indicate that the remote side has acknowledged the data.
 *		This callback does indicate that the data has either been sent or it has been
 *		enqueued to be sent.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_send(nw_connection_t connection,
				   _Nullable dispatch_data_t content,
				   nw_content_context_t context,
				   bool is_complete,
				   nw_connection_send_completion_t completion);

/*!
 * @function nw_connection_batch
 *
 * @abstract
 *		Batch several send and/or receive operations together, to hint to
 *		the connection that multiple send or recieve operations are expected
 *		in quick succession.
 *
 * @param connection
 *		The connection object.
 *
 * @param batch_block
 *		The batch block will be invoked immediately upon calling this function.
 *		The client may call nw_connection_send() or nw_connection_receive()
 *		multiple times within the block, and the connection will attempt to
 *		batch these operations when the block returns.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_connection_batch(nw_connection_t connection,
					NW_NOESCAPE dispatch_block_t batch_block);

#endif // __BLOCKS__

/*!
 * @function nw_connection_copy_description
 *
 * @abstract
 *		Copy a human-readable description of the connection.
 *
 * @param connection
 *		The connection object.
 *
 * @result
 *		Returns a human-readable string description of the connection.
 *		The caller must call free() on the string.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
char *
nw_connection_copy_description(nw_connection_t connection);

/*!
 * @function nw_connection_copy_current_path
 *
 * @abstract
 *		Copy the current path for a connection. If a connection is
 *		established, this will reflect the connected path.
 *
 * @param connection
 *		The connection object.
 *
 * @result
 *		Returns a retained path object, or NULL if the connection
 *		has not been started or has been cancelled.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED _Nullable nw_path_t
nw_connection_copy_current_path(nw_connection_t connection);

/*!
 * @function nw_connection_copy_protocol_metadata
 *
 * @abstract
 *		Copy the connection-wide metadata for a specific protocol.
 *		This allows the caller to introspect per-protocol state,
 *		only once the connection has been established. This
 *		metadata is also available when receiving data through
 *		the content context.
 *
 * @param connection
 *		The connection object.
 *
 * @param definition
 *		The protocol definition for which metadata will be returned.
 *
 * @result
 *		Returns a retained protocol metadata object, or NULL if the connection
 *		has not been established yet, or is cancelled.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED _Nullable nw_protocol_metadata_t
nw_connection_copy_protocol_metadata(nw_connection_t connection,
									 nw_protocol_definition_t definition);

/*!
 * @function nw_connection_get_maximum_datagram_size
 *
 * @abstract
 *		Check for the maximum datagram size that can be written
 *		on the connection. Any datagrams written should be less
 *		than or equal to this size.
 *
 * @param connection
 *		The connection object.
 *
 * @result
 *		Returns a datagram size based on the current MTU and the
 *		overhead of the protocols being used.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
uint32_t
nw_connection_get_maximum_datagram_size(nw_connection_t connection);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif /* __NW_CONNECTION_H__ */
