//
//  connection_group.h
//  Network
//
//  Copyright (c) 2019-2021 Apple Inc. All rights reserved.
//

#ifndef __NW_CONNECTION_GROUP_H__
#define __NW_CONNECTION_GROUP_H__

#ifndef __NW_INDIRECT__
#error "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/connection.h>
#include <Network/error.h>
#include <Network/group_descriptor.h>
#include <Network/parameters.h>

NW_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 * @typedef nw_connection_group_t
 * @abstract
 *		A Network Connection Group may be used to listen for, process, and reply to
 *		incoming messages on a network that are associated with a particular group.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_CONNECTION_GROUP_IMPL
NW_OBJECT_DECL(nw_connection_group);
#endif // NW_CONNECTION_GROUP_IMPL

/*!
 * @typedef nw_connection_group_state_t
 * @abstract
 *		Connection Group states sent by nw_connection_group_set_state_changed_handler.
 *		States progress forward and do not move backwards.
 */
typedef enum {
	/*!
	 *	@const nw_connection_group_state_invalid The state of the connection group is not valid.
	 *		This state will never be delivered in the connection group's state update
	 *		handler and can be treated as an unexpected value.
	 */
	nw_connection_group_state_invalid = 0,

	/*!
	 *	@const nw_connection_group_state_waiting The connection group is waiting for a usable network
	 *		before being able to receive and process incoming messages.
	 */
	nw_connection_group_state_waiting = 1,

	/*!
	 *	@const nw_connection_group_state_ready The connection group is ready and able to receive and
	 *		process incoming messages.
	 */
	nw_connection_group_state_ready = 2,

	/*!
	 *	@const nw_connection_group_state_failed The connection group has irrecoverably failed.
	 *		You should cancel the connection group and create a new connection group object
	 *		if you wish to continue processing incoming messages.
	 */
	nw_connection_group_state_failed = 3,

	/*!
	 *	@const nw_connection_group_state_cancelled The connection group has been cancelled by
	 *		the user. You should create a new connection group object if you wish to continue
	 *		processing incoming messages.
	 */
	nw_connection_group_state_cancelled = 4,
} nw_connection_group_state_t;

/*!
 * @function nw_connection_group_create
 *
 * @abstract
 *		Creates a new connection group object to use for communication with
 *		a group descriptor using protocols described by parameters.
 *
 * @param group_descriptor
 * 		A group descriptor. For example, a descriptor of type nw_group_type_multicast
 * 		defines one or more multicast groups to automatically join.
 *
 * @param parameters
 *		Parameters to use for the new connection group. This includes the protocols that
 *		will be used to delineate complete messages for processing. For multicast
 *		joining, all available interfaces will be joined as prohibited or required.
 *
 * @result
 *		Returns an allocated nw_connection_group_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0))
NW_RETURNS_RETAINED nw_connection_group_t
nw_connection_group_create(nw_group_descriptor_t group_descriptor,
						   nw_parameters_t parameters);

/*!
 * @function nw_connection_group_copy_descriptor
 *
 * @abstract
 *		Gets the group descriptor with which the connection group was created.
 *
 * @param group
 *		The connection group to check.
 *
 * @result
 *		Returns the descriptor with which the connection group was created.
 */
API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0))
NW_RETURNS_RETAINED
nw_group_descriptor_t
nw_connection_group_copy_descriptor(nw_connection_group_t group);

/*!
 * @function nw_connection_group_copy_parameters
 *
 * @abstract
 *		Returns a copy of the parameters passed to nw_connection_group_create.
 *
 * @param group
 *		The connection group object.
 *
 * @result
 *		Returns an nw_parameters_t object.
 */
API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0))
NW_RETURNS_RETAINED nw_parameters_t
nw_connection_group_copy_parameters(nw_connection_group_t group);

/*!
 * @function nw_connection_group_set_queue
 *
 * @abstract
 *		Sets the client callback queue, on which blocks for events will
 * 		be scheduled. This must be done before calling nw_connection_group_start().
 *
 * @param group
 *		The connection group object.
 *
 * @param queue
 *		The client's callback queue.
 */
API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0))
void
nw_connection_group_set_queue(nw_connection_group_t group,
							  dispatch_queue_t queue);

#ifdef __BLOCKS__

/*!
 * @typedef nw_connection_group_state_changed_handler_t
 *
 * @abstract
 *		A block called when the connection group changes state.
 *
 * @param state
 *		The new state of the connection group.
 *
 * @param error
 *		An optional error that is associated with the new state.
 */
typedef void (^nw_connection_group_state_changed_handler_t)(nw_connection_group_state_t state,
															_Nullable nw_error_t error);

/*!
 * @function nw_connection_group_set_state_changed_handler
 *
 * @abstract
 *		Sets the state changed handler. For clients that need to perform cleanup
 *		when the connection group has been cancelled, the nw_connection_group_state_cancelled state
 *		will be delivered last. This function must not be called after starting the connection group.
 *
 * @param group
 *		The connection group object.
 *
 * @param state_changed_handler
 *		The state changed handler to call when the connection group state changes.
 *		Pass NULL to remove the event handler.
 */
API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0))
void
nw_connection_group_set_state_changed_handler(nw_connection_group_t group,
											  _Nullable nw_connection_group_state_changed_handler_t state_changed_handler);

/*!
 * @typedef nw_connection_group_receive_handler_t
 *
 * @abstract
 *		A block called when a new inbound message arrives at the connection group. A client
 *		may reply to this message within the handler or it may choose to save the
 *		content context representing this message and provide a response
 *		at a later time. If an inbound context is deallocated without providing a response,
 *		the message is considered dropped and any internal state associated with the
 *		endpoint that sent that message will be removed.
 *
 * @param content
 *		The content associated with the body of the inbound message. If there is no
 *		body for this message `content` will be `nil`.
 *
 * @param context
 *		The content context representing this inbound message.
 *
 * @param is_complete
 *		True if the inbound message is complete and any content provided represents
 *		the entirety of the inbound message's body. If false, the inbound message context
 *		may be converted to a connection associated with this message and read
 *		the remainder of the body, or an appropriate error may be selected and sent in
 *		response.
 */
typedef void (^nw_connection_group_receive_handler_t)(_Nullable dispatch_data_t content,
													  nw_content_context_t context,
													  bool is_complete);

/*!
 * @function nw_connection_group_set_receive_handler
 *
 * @abstract
 *		Sets the handler to be invoked whenever a new inbound message
 *		arrives at the connection group. This function must not be called after starting the connection group.
 *
 * @param group
 *		The connection group object.
 *
 *	@param maximum_message_size
 *		The maximum message size that should be delivered as a complete message. Any
 *		inbound messages larger than this size will be delivered as a partial message and
 *		an application may convert the inbound message to an `nw_connection` to read
 *		any remaining data for that message until it is complete.
 *
 *	@param reject_oversized_messages
 *		True if messages larger than maximum_message_size should be treated as errors
 *		and the connection group should automatically reply to such messages. False if the
 *		connection group should deliver such messages as incomplete and allow the application
 *		to inspect the message prior to accepting or rejecting it.
 *
 * @param receive_handler
 *		The handler to call upon arrival of a new inbound message.
 *		Pass NULL to remove the handler.
 */
API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0))
void
nw_connection_group_set_receive_handler(nw_connection_group_t group,
										uint32_t maximum_message_size,
										bool reject_oversized_messages,
										_Nullable nw_connection_group_receive_handler_t receive_handler);

#endif // __BLOCKS__

/*!
 * @function nw_connection_group_start
 *
 * @abstract
 *		Starts the connection group, which begins listening for and processing incoming messages.
 *		You must call nw_connection_group_set_queue() and set a receive handler with
 *		nw_connection_group_set_receive_handler() before starting the connection group.
 *
 * @param group
 *		The connection group object.
 */
API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0))
void
nw_connection_group_start(nw_connection_group_t group);

/*!
 * @function nw_connection_group_cancel
 *
 * @abstract
 *		Cancels the connection group. The process of cancellation will be completed
 *		asynchronously, and the final callback event delivered to the caller
 *		will be a state update with a value of nw_connection_group_state_cancelled.
 *		Once this update is delivered, the caller may clean up any associated
 *		memory or objects.
 *
 * @param group
 *		The connection group object.
 */
API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0))
void
nw_connection_group_cancel(nw_connection_group_t group);

/*!
 * @function nw_connection_group_copy_remote_endpoint_for_message
 *
 * @abstract
 *		Copy the remote endpoint corresponding to a given inbound connection group message.
 *
 * @param group
 *		The connection group object.
 *
 * @param context
 *		A content context representing an inbound message received from this connection group.
 *
 * @result
 *		Returns the remote endpoint, or nil if the context is not a valid
 *		inbound message received from this connection group.
 */
API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0))
NW_RETURNS_RETAINED _Nullable nw_endpoint_t
nw_connection_group_copy_remote_endpoint_for_message(nw_connection_group_t group,
													 nw_content_context_t context);

/*!
 * @function nw_connection_group_copy_local_endpoint_for_message
 *
 * @abstract
 *		Copy the local endpoint corresponding to a given inbound connection group message.
 *
 * @param group
 *		The connection group object.
 *
 * @param context
 *		A content context representing an inbound message received from this connection group.
 *
 * @result
 *		Returns the local endpoint, or nil if the context is not a valid
 *		inbound message received from this connection group.
 */
API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0))
NW_RETURNS_RETAINED _Nullable nw_endpoint_t
nw_connection_group_copy_local_endpoint_for_message(nw_connection_group_t group,
													nw_content_context_t context);

/*!
 * @function nw_connection_group_copy_path_for_message
 *
 * @abstract
 *		Copy the path associated with a given inbound connection group message.
 *
 * @param group
 *		The connection group object.
 *
 * @param context
 *		A content context representing an inbound message received from this connection group.
 *
 * @result
 *		Returns the path associated with the provided message, or nil if the context
 *		is not a valid inbound message received from this connection group.
 */
API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0))
NW_RETURNS_RETAINED _Nullable nw_path_t
nw_connection_group_copy_path_for_message(nw_connection_group_t group,
										  nw_content_context_t context);

/*!
 * @function nw_connection_group_copy_protocol_metadata_for_message
 *
 * @abstract
 *		Copy the metadata corresponding to a given inbound connection group message.
 *
 * @param group
 *		The connection group object.
 *
 * @param definition
 *		The protocol definition for which metadata will be returned.
 *
 * @result
 *		Returns a retained protocol metadata object, or NULL if not found.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
_Nullable nw_protocol_metadata_t
nw_connection_group_copy_protocol_metadata_for_message(nw_connection_group_t group,
													   nw_content_context_t context,
													   nw_protocol_definition_t definition);

/*!
 * @function nw_connection_group_extract_connection_for_message
 *
 * @abstract
 *		Extract a connection corresponding to an inbound message from the
 *		connection group. Once extracted, subsequent messages from this
 *		remote endpoint on this connection will no longer be handled by the
 *		connection group. The connection may be used to read the remainder
 *		of a partial message or to send a large response with support for partial
 *		messages and backpressure.
 *		Any incoming messages from this remote endpoint which were saved from
 *		the receive handler may no longer be valid after a connection is returned.
 *      An extracted connection must have a queue set and be started before it can be used.
 *
 * @param group
 *		The connection group object from which the context was received. If the context was
 *		not received from this connection group, the extraction will fail.
 *
 *	@param context
 *		A content context representing an inbound message received from this connection group.
 *
 * @result
 *		Returns the connection associated with the provided message, or nil if the extraction
 *		fails. Extraction will fail if the provided message is not an inbound message from
 *		this connection group.
 */
API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0))
NW_RETURNS_RETAINED _Nullable nw_connection_t
nw_connection_group_extract_connection_for_message(nw_connection_group_t group,
												   nw_content_context_t context);

/*!
 * @function nw_connection_group_reply
 *
 * @abstract
 *		Send data in response to an inbound message received by a connection group.
 *
 * @param group
 *		The connection group object from which the reply_context was received.
 *
 * @param inbound_message
 * 		The inbound message received by the connection group for which this is a response.
 * 		An inbound message may be replied to exactly once.
 *
 * @param outbound_message
 *		The outbound message to send in response to the message received by the connection group.
 *
 *		The response context can also hold protocol metadata to define how to
 *		send content, such as flags for IP packets.
 *
 *		If the context is marked as "final", the  connection group will expect that no further communication is
 *		expected during this connection with the peer and may close the underlying transport.
 *		Subsequent connection attempts from the peer will continue to be delivered as incoming messages.
 *
 *	@param content
 *		A data object to send as the message body. This may be NULL if the outgoing
 *		context represents a metadata only message that contains no body data.
 *
 */
API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0))
void
nw_connection_group_reply(nw_connection_group_t group,
						  nw_content_context_t inbound_message,
						  nw_content_context_t outbound_message,
						  dispatch_data_t _Nullable content);

/*!
 * @function nw_connection_group_extract_connection
 *
 * @abstract
 *      Extract a connection from the connection group. For a multiplex connection group, this means that
 *      a new stream is opened and the corresponding nw_connection_t object is returned. For non-multiplex
 *      connection groups, a connection to the specified endpoint will be returned if allowed by the group descriptor.
 *
 *      The connection can be re-inserted into the group later. Once reinserted, the connection group
 *      will handle subsequent messages from this remote endpoint.
 *      An extracted connection must have a queue set and be started before it can be used.
 *
 * @param group
 *      The connection group object from which to extract a connection.
 *
 * @param endpoint
 *      The endpoint to use as the remote endpoint for the extracted connection, if applicable.
 *      For connection groups with multiplex group descriptors, this should be nil.
 *
 * @param protocol_options
 *      The protocol options to apply to the extracted connection. May be nil if not applicable.
 *
 * @result
 *      Returns the connection from the connection group.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
NW_RETURNS_RETAINED _Nullable nw_connection_t
nw_connection_group_extract_connection(nw_connection_group_t group,
									   _Nullable nw_endpoint_t endpoint,
									   _Nullable nw_protocol_options_t protocol_options);

/*!
 * @function nw_connection_group_reinsert_extracted_connection
 *
 * @abstract
 *		Reinsert a connection into a connection group. Once reinserted, the connection group
 *		will handle subsequent messages from this remote endpoint, and any outstanding reads on
 *		the connection will be cancelled.
 *
 * @param group
 *		The connection group object from which the connection was extracted. If the connection was
 *		not extracted from this connection group, the reinsertion will fail.
 *
 *	@param connection
 *		A connection that was extracted from this connection group.
 *
 * @result
 *		Returns true if the reinsertion was successful. Reinsertion will fail if the provided connection was
 *		not extracted from this connection group.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
bool
nw_connection_group_reinsert_extracted_connection(nw_connection_group_t group,
												  nw_connection_t connection);

#ifdef __BLOCKS__

/*!
 * @typedef nw_connection_group_send_completion_t
 * @abstract
 *		A send completion is invoked exactly once for a call to nw_connection_group_send_message().
 *		The completion indicates that the sent content has been processed by the stack
 *		(not necessarily that it has left the host), or else an error has occurred during
 *		sending.
 *
 * @param error
 *		An error will be delivered if the associated content could not be fully sent before an
 *		error occurred. An error will be sent for any outstanding sends when the connection
 *		is cancelled.
 */
typedef void (^nw_connection_group_send_completion_t)(_Nullable nw_error_t error);

/*!
 * @function nw_connection_group_send_message
 *
 * @abstract
 *		Send data that is not in response to an inbound message. This outgoing
 *		message will be sent from the local endpoint on which the connection group is
 *		listening for incoming messages.
 *
 *		This is an asynchronous send and the completion block can be used to
 *		determine when the send is complete. There is nothing preventing a client
 *		from issuing an excessive number of outstanding sends. To minimize memory
 *		footprint and excessive latency as a consequence of buffer bloat, it is
 *		advisable to keep a low number of outstanding sends. The completion block
 *		can be used to pace subsequent sends.
 *
 * @param group
 *		The connection group object from which to send the outbound data.
 *
 *	@param content
 *		A data object to send as the message body. This may be NULL if the outgoing
 *		context represents a metadata only message that contains no body data.
 *
 * @param endpoint
 * 		The destination endpoint to which the outbound message should be sent. If the
 * 		endpoint is NULL, the message will be sent to all members of the group.
 *
 * @param context
 *		An outbound message to send from the connection group.
 *
 *		The context can also hold protocol metadata to define how to send content,
 *		such as flags for IP packets.
 *
 *		If the context is marked as "final", the  connection group will expect that no further communication is
 *		expected during this connection with the peer and may close the underlying transport.
 *		Subsequent connection attempts from the peer will be delivered as incoming messages.
 *
 * @param completion
 *		A callback to be called when the message has been sent, or an error has occurred.
 *		This callback does not indicate that the remote side has acknowledged the data.
 *		This callback does indicate that the data has either been sent or it has been
 *		enqueued to be sent.
 */
API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0))
NW_SWIFT_DISABLE_ASYNC
void
nw_connection_group_send_message(nw_connection_group_t group,
								 _Nullable dispatch_data_t content,
								 _Nullable nw_endpoint_t endpoint,
								 nw_content_context_t context,
								 nw_connection_group_send_completion_t completion);

/*!
 * @typedef nw_connection_group_new_connection_handler_t
 *
 * @abstract
 *		A block called with a new connection when a multiplex group receives a new stream. If a new connection
 *		handler is set the user must handle connections received by this handler. There are three possible
 *		actions to take and one of these three actions must be taken.
 *		1) Take over the ownership of the connection. In this case, the connection is used by the client to
 *		   send and receive data as any other connection would be used. The client may insert this
 *		   connection back into the connection group at a later point if so desired.
 *		   The connection must have a queue set and be started before it can be used.
 *      2) If you want the connection group to handle this connection, simply insert this connection back into
 *         the connection group right away.
 *      3) If you don't want to accept this connection, simply cancel the connection.
 *
 * @param connection
 *		The connection representing the new stream on this multiplexing protocol
 */
typedef void (^nw_connection_group_new_connection_handler_t)(nw_connection_t connection);

/*!
 * @function nw_connection_group_set_new_connection_handler
 *
 * @abstract
 *		Sets the new connection handler to be invoked whenever a new inbound connection
 *		is received by the connection group. This function must not be called
 *		after starting the connection group.
 *
 * @param group
 *		The connection group object.
 *
 * @param new_connection_handler
 *		The new connection handler to call upon receipt of a new inbound connection.
 *		Pass NULL to remove the handler.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
void
nw_connection_group_set_new_connection_handler(nw_connection_group_t group,
											   _Nullable nw_connection_group_new_connection_handler_t new_connection_handler);

/*!
 * @function nw_connection_group_copy_protocol_metadata
 *
 * @abstract
 *		Copy the metadata corresponding to a given inbound connection group message.
 *
 * @param group
 *		The connection group object.
 *
 * @param definition
 *		The protocol definition for which metadata will be returned.
 *
 * @result
 *		Returns a retained protocol metadata object, or NULL if the connection
 *		group has not been established yet or is cancelled.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
_Nullable nw_protocol_metadata_t
nw_connection_group_copy_protocol_metadata(nw_connection_group_t group,
										   nw_protocol_definition_t definition);

#endif // __BLOCKS__

__END_DECLS

NW_ASSUME_NONNULL_END

#endif /* __NW_CONNECTION_GROUP_H__ */
