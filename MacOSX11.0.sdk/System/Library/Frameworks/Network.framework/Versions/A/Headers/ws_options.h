//
//  ws_options.h
//  libnetcore
//
//  Copyright (c) 2018-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_WS_OPTIONS_H__
#define __NW_WS_OPTIONS_H__

#ifndef __NW_INDIRECT__
#error "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/error.h>
#include <Network/protocol_options.h>

__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

# pragma mark - WebSocket Constants

/*!
 * @typedef nw_ws_opcode_t
 * @abstract
 *		WebSocket opcodes that denote the type of frame sent or received by
 *		a WebSocket endpoint. Opcodes define the interpretation of their
 *		associated payload data.
 */
typedef enum {

	/*!
	 *	@const nw_ws_opcode_invalid Denotes an invalid frame.
	 */
	nw_ws_opcode_invalid = -1,

	/*!
	 *	@const nw_ws_opcode_cont Denotes a continuation frame.
	 */
	nw_ws_opcode_cont = 0x0,

	/*!
	 *	@const nw_ws_opcode_text Denotes a text frame.
	 */
	nw_ws_opcode_text = 0x1,

	/*!
	 *	@const nw_ws_opcode_text Denotes a binary frame.
	 */
	nw_ws_opcode_binary = 0x2,

	/*!
	 *	@const nw_ws_opcode_text Denotes a close frame.
	 */
	nw_ws_opcode_close = 0x8,

	/*!
	 *	@const nw_ws_opcode_text Denotes a ping frame.
	 */
	nw_ws_opcode_ping = 0x9,

	/*!
	 *	@const nw_ws_opcode_text Denotes a pong frame.
	 */
	nw_ws_opcode_pong = 0xA,

} nw_ws_opcode_t;

/*!
 * @typedef nw_ws_close_code_t
 * @abstract
 *		WebSocket close codes that describe the reason for closing a WebSocket
 *		connection. Endpoints MAY use the following pre-defined status codes
 *		when sending a Close frame.
 */
typedef enum {
	/*!
	 *	@const nw_ws_close_code_normal_closure Indicates a normal closure,
	 *		meaning that the purpose for which the connection was established
	 *		has been fulfilled.
	 */
	nw_ws_close_code_normal_closure = 1000,

	/*!
	 *	@const nw_ws_close_code_normal_going_away Indicates that an endpoint is
	 *		"going away", such as a server going down or a browser having
	 *		navigated away from a page.
	 */
	nw_ws_close_code_going_away = 1001,

	/*!
	 *	@const nw_ws_close_code_protocol_error Indicates that an endpoint is
	 *		terminating the connection due to a protocol error.
	 */
	nw_ws_close_code_protocol_error = 1002,

	/*!
	 *	@const nw_ws_close_code_normal_closure Indicates that an endpoint is
	 *		terminating the connection because it has received a type of data
	 *		it cannot accept (e.g., an endpoint that understands only text data
	 *		MAY send this if it receives a binary message).
	 */
	nw_ws_close_code_unsupported_data = 1003,

	/*!
	 *	@const nw_ws_close_code_no_status_received A reserved value and MUST NOT
	 *		be set as a status code in a Close control frame by an endpoint. It
	 *		is designated for use in applications expecting a status code to
	 *		indicate that no status code was actually present.
	 */
	nw_ws_close_code_no_status_received = 1005,

	/*!
	 *	@const nw_ws_close_code_abnormal_closure A reserved value and MUST NOT
	 *		be set as a status code in a Close control frame by an endpoint.
	 *		It is designated for use in applications expecting a status code to
	 *		indicate that the connection was closed abnormally, e.g., without
	 *		sending or receiving a Close control frame.
	 */
	nw_ws_close_code_abnormal_closure = 1006,

	/*!
	 *	@const nw_ws_close_code_invalid_frame_payload_data Indicates that an
	 *		endpoint is terminating the connection because it has received data
	 *		within a message that was not consistent with the type of the
	 *		message (e.g., non-UTF-8 [RFC3629] data within a text message).
	 */
	nw_ws_close_code_invalid_frame_payload_data = 1007,

	/*!
	 *	@const nw_ws_close_code_policy_violation Indicates that an endpoint is
	 *		terminating the connection because it has received a message that
	 *		violates its policy. This is a generic status code that can be
	 *		returned when there is no other more suitable status code (e.g.,
	 *		1003 or 1009) or if there is a need to hide specific details about
	 *		the policy.
	 */
	nw_ws_close_code_policy_violation = 1008,

	/*!
	 *	@const nw_ws_close_code_message_too_big Indicates that an endpoint is
	 *		terminating the connection because it has received a message that
	 *		is too big for it to process.
	 */
	nw_ws_close_code_message_too_big = 1009,

	/*!
	 *	@const nw_ws_close_code_mandatory_extension Indicates that an endpoint
	 *		(client) is terminating the connection because it has expected the
	 *		server to negotiate one or more extensions, but the server didn't
	 *		return them in the response message of the WebSocket handshake. The
	 *		list of extensions that are needed SHOULD appear in the /reason/
	 *		part of the Close frame. Note that this status code is not used by
	 *		the server, because it can fail the WebSocket handshake instead.
	 */
	nw_ws_close_code_mandatory_extension = 1010,

	/*!
	 *	@const nw_ws_close_code_internal_server_error Indicates that a server is
	 *		terminating the connection because it encountered an unexpected
	 *		condition that prevented it from fulfilling the request.
	 */
	nw_ws_close_code_internal_server_error = 1011,

	/*!
	 *	@const nw_ws_close_code_tls_handshake A reserved value and MUST NOT
	 *		be set as a status code in a Close control frame by an endpoint. It
	 *		is designated for use in applications expecting a status code to
	 *		indicate that the connection was closed due to a failure to perform
	 *		a TLS handshake (e.g., the server certificate can't be verified).
	 */
	nw_ws_close_code_tls_handshake = 1015,
} nw_ws_close_code_t;

/*!
 * @typedef nw_ws_version_t
 * @abstract
 *		The WebSocket Protocol version.
 */
typedef enum {
	/*! @const nw_ws_version_invalid An invalid WebSocket version */
	nw_ws_version_invalid = 0,
	/*! @const nw_ws_version_13 WebSocket v13 as defined in RFC 6455 */
	nw_ws_version_13 = 1,
} nw_ws_version_t;

# pragma mark - WebSocket Definition

/*!
 * @function nw_protocol_copy_ws_definition
 *
 * @abstract
 *		Access the definition of the default system implementation of the
 *		WebSocket protocol. This protocol can be appended to a connection's
 *		protocol stack.
 *
 * @result
 *		Returns a retained protocol definition object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_protocol_definition_t
nw_protocol_copy_ws_definition(void);

# pragma mark - WebSocket Options

/*!
 * @function nw_ws_create_options
 *
 * @abstract
 *		Create an instance of WebSocket protocol options. This object can be
 *		added to an nw_protocol_stack_t to be used in an nw_connection_t or
 *		an nw_listener_t.
 *
 * @result
 *		Returns a retained protocol options object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_protocol_options_t
nw_ws_create_options(nw_ws_version_t version);

/*!
 * @function nw_ws_options_add_additional_header
 *
 * @abstract
 *		Set additional HTTP headers to be sent by the client during the
 *		WebSocket handshake.
 *
 * @param options
 *		The WebSocket protocol options object.
 *
 * @param name
 *		The HTTP header name.
 *
 * @param value
 *		The HTTP header value.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_ws_options_add_additional_header(nw_protocol_options_t options,
									const char *name, const char *value);

/*!
 * @function nw_ws_options_add_subprotocol
 *
 * @abstract
 *		Add to the list of subprotocols that will be presented to a
 *		WebSocket server during connection establishment.
 *
 * @param options
 *		The WebSocket protocol options object.
 *
 * @param subprotocol
 *		The subprotocol supported by the client.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_ws_options_add_subprotocol(nw_protocol_options_t options,
							  const char *subprotocol);

/*!
 * @function nw_ws_options_set_auto_reply_ping
 *
 * @abstract
 *		Set whether the WebSocket connection should automatically reply to all
 *		incoming pings.
 *
 * @param options
 *		The WebSocket protocol options object.
 *
 * @param auto_reply_ping
 *		Whether the WebSocket connection should automatically reply to all
 *		incoming pings.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_ws_options_set_auto_reply_ping(nw_protocol_options_t options,
								  bool auto_reply_ping);

/*!
 * @function nw_ws_options_set_skip_handshake
 *
 * @abstract
 *		Set whether the WebSocket protocol should skip the opening handshake
 *		and begin framing data as soon as a connection is established.
 *
 * @param options
 *		The WebSocket protocol options object.
 *
 * @param skip_handshake
 *		Whether the WebSocket connection should skip the opening handshake.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_ws_options_set_skip_handshake(nw_protocol_options_t options, bool skip_handshake);

/*!
 * @function nw_ws_options_set_maximum_message_size
 *
 * @abstract
 *		Set the maximum allowed message size to be received by the WebSocket
 *		connection. This does not limit the sending message size.
 *
 * @param options
 *		The WebSocket protocol options object.
 *
 * @param maximum_message_size
 *		The maximum message size in bytes. A maximum message size of 0 means
 *		there is no receive limit. The default maximum message size is 0.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_ws_options_set_maximum_message_size(nw_protocol_options_t options,
									   size_t maximum_message_size);

# pragma mark - WebSocket Metadata

/*!
 * @function nw_protocol_metadata_is_ws
 *
 * @abstract
 *		Checks if a protocol metadata object is compatible with the
 *		accessors defined in this file for the default system
 *		implementation of WebSocket.
 *
 * @result
 *		Returns true if the metadata is for the default system
 *		implementation of WebSocket, false otherwise.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_protocol_metadata_is_ws(nw_protocol_metadata_t metadata);

/*!
 * @function nw_ws_create_metadata
 *
 * @abstract
 *		Creates a protocol metadata object that can be used to define the
 *		content context of messages sent over a WebSocket connection.
 *
 * @param opcode
 *		Set the opcode on a WebSocket frame. This must be defined on create.
 *
 * @result
 *		Returns a retained metadata object representing the WebSocket frame.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_protocol_metadata_t
nw_ws_create_metadata(nw_ws_opcode_t opcode);

/*!
 * @function nw_ws_metadata_get_opcode
 *
 * @abstract
 *		Get the opcode on a WebSocket frame.
 *
 * @param metadata
 *		The metadata object representing the WebSocket frame.
 *
 * @result
 *		The opcode on the WebSocket frame.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
nw_ws_opcode_t
nw_ws_metadata_get_opcode(nw_protocol_metadata_t metadata);

/*!
 * @function nw_ws_metadata_set_close_code
 *
 * @abstract
 *		Set the close code on a WebSocket frame. The WebSocket frame's opcode
 *		should be nw_ws_opcode_close.
 *
 * @param metadata
 *		The metadata object representing the WebSocket frame.
 *
 * @param close_code
 *		The close code on the WebSocket frame.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_ws_metadata_set_close_code(nw_protocol_metadata_t metadata, nw_ws_close_code_t close_code);

/*!
 * @function nw_ws_metadata_get_close_code
 *
 * @abstract
 *		Get the close code from a WebSocket frame. If the close code is equal
 *		to nw_ws_close_code_no_status_received, it means that a close code
 *		was not actually present in the WebSocket frame.
 *
 * @param metadata
 *		The metadata object representing the WebSocket frame.
 *
 * @result
 *		The close code on the WebSocket frame.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
nw_ws_close_code_t
nw_ws_metadata_get_close_code(nw_protocol_metadata_t metadata);

#ifdef __BLOCKS__

/*!
 * @typedef nw_ws_pong_handler_t
 *
 * @abstract
 *		A block to be invoked when a pong reply is received after sending a ping
 *		message, or if the WebSocket connection has closed or failed.
 *
 * @param error
 *		An optional error if the WebSocket connection fails or closes before a
 *		pong reply is received.
 */
typedef void (^nw_ws_pong_handler_t)(nw_error_t _Nullable error);

/*!
 * @function nw_ws_metadata_set_pong_handler
 *
 * @abstract
 *		Set a callback that will notify the client when a pong message has been
 *		received for a ping message sent. The metadata object's associated
 *		opcode should be nw_ws_opcode_ping.
 *
 * @param metadata
 *		The WebSocket metadata object.
 *
 * @param client_queue
 *		The queue on which the pong handler will be delivered.
 *
 * @param pong_handler
 *		The handler that gets called when a pong reply is received.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_ws_metadata_set_pong_handler(nw_protocol_metadata_t metadata,
								dispatch_queue_t client_queue,
								nw_ws_pong_handler_t pong_handler);

#endif // __BLOCKS__

# pragma mark - WebSocket Request

/*!
 * @typedef nw_ws_request_t
 * @abstract
 *		A WebSocket request represents a client's request to connect to a WebSocket
 *		server.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_WS_REQUEST_IMPL
NW_OBJECT_DECL(nw_ws_request);
#endif // NW_WS_REQUEST_IMPL

#ifdef __BLOCKS__

/*!
 * @typedef nw_ws_subprotocol_enumerator_t
 *
 * @abstract
 *		A block that can be applied to every subprotocol in a client's WebSocket
 *		request.
 *
 * @param subprotocol
 *		A subprotocol presented by the client.
 *
 * @result
 *		A boolean value that indicating if enumeration should continue.
 */
typedef bool (^nw_ws_subprotocol_enumerator_t)(const char *subprotocol);

/*!
 * @function nw_ws_request_enumerate_subprotocols
 *
 * @abstract
 *		Enumerates the list of subprotocols on the client's request.
 *
 * @param request
 *		The client request.
 *
 * @param enumerator
 *		The enumerator block.
 *
 * @result
 *		Whether the enumeration completed.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_ws_request_enumerate_subprotocols(nw_ws_request_t request,
									 NW_NOESCAPE nw_ws_subprotocol_enumerator_t enumerator);

/*!
 * @typedef nw_ws_additional_header_enumerator_t
 *
 * @abstract
 *		A block that can be applied to every additional header in a client's
 *		WebSocket request.
 *
 * @param name
 *		The HTTP name.
 *
 * @param value
 *		The HTTP value.
 */
typedef bool (^nw_ws_additional_header_enumerator_t)(const char *name,
													 const char *value);

/*!
 * @function nw_ws_request_enumerate_additional_headers
 *
 * @abstract
 *		Enumerates the list of additional headers on the client's request.
 *
 * @param request
 *		The client request.
 *
 * @param enumerator
 *		The enumerator block.
 *
 * @result
 *		Whether the enumeration completed.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_ws_request_enumerate_additional_headers(nw_ws_request_t request,
										   NW_NOESCAPE nw_ws_additional_header_enumerator_t enumerator);

#endif // __BLOCKS__

# pragma mark - WebSocket Response

/*!
 * @typedef nw_ws_response_t
 * @abstract
 *		A WebSocket response represents a server's response to a client's request
 *		to connect.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_WS_RESPONSE_IMPL
NW_OBJECT_DECL(nw_ws_response);
#endif // NW_WS_RESPONSE_IMPL

/*!
 * @typedef nw_ws_response_status_t
 * @abstract
 *		The status of a WebSocket server's response to a client's request to
 *		connect.
 */
typedef enum {

	/*!
	 *	@const nw_ws_response_status_invalid The response is invalid. This should
	 *		be treated as an unexpected value.
	 */
	nw_ws_response_status_invalid = 0,

	/*!
	 *	@const nw_ws_response_status_accept Accept the request to connect. The
	 *		WebSocket connection will begin framing data.
	 */
	nw_ws_response_status_accept = 1,

	/*!
	 *	@const nw_ws_response_status_accept Reject the request to connect. The
	 *		WebSocket connection will be closed.
	 */
	nw_ws_response_status_reject = 2,
} nw_ws_response_status_t;

/*!
 * @function nw_ws_response_create
 *
 * @abstract
 *      Create a server response to a WebSocket client's opening handshake.
 *
 * @param status
 *      The status of the response. If the status is nw_ws_response_status_accept,
 *      the server will accept the handshake and open the WebSocket connection.
 *      If the status is nw_ws_response_status_reject, the server will reject the
 *      handshake and respond with the HTTP error 400 Bad Request.
 *
 * @param selected_subprotocol
 *      The server's selected protocol from the client's list of proposed
 *		subprotocols. If the status of this response is nw_ws_response_status_reject,
 *      this parameter is ignored. Pass NULL to indicate the server did not find
 *      a suitable subprotocol, but has accepted the handshake anyways.
 *      Passing an empty string is prohibited by the WebSocket protocol.
 *
 * @result
 *      An instantiated WebSocket server response object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_ws_response_t
nw_ws_response_create(nw_ws_response_status_t status,
					  const char * _Nullable selected_subprotocol);

/*!
 * @function nw_ws_response_get_status
 *
 * @abstract
 *		Get the status from a WebSocket server's response. If the response is
 *		nil, the return value will be nw_ws_response_status_invalid.
 *
 * @param response
 *		The server response.
 *
 * @result
 *		The status of the server's response.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
nw_ws_response_status_t
nw_ws_response_get_status(nw_ws_response_t _Nullable response);

/*!
 * @function nw_ws_response_get_selected_subprotocol
 *
 * @abstract
 *		Get the selected subprotocol from a WebSocket server's response.
 *
 * @param response
 *		The server response.
 *
 * @result
 *		The status of the server's response.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
const char * _Nullable
nw_ws_response_get_selected_subprotocol(nw_ws_response_t response);

/*!
 * @function nw_ws_response_add_additional_header
 *
 * @abstract
 *		Add additional HTTP headers to be sent back to the WebSocket client in
 *		the server's response.
 *
 * @param response
 *		The server response.
 *
 * @param name
 *		The HTTP name.
 *
 * @param value
 *		The HTTP value.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_ws_response_add_additional_header(nw_ws_response_t response,
									 const char *name, const char *value);

/*!
 * @function nw_ws_metadata_copy_server_response
 *
 * @abstract
 *		Copy the WebSocket server's response to a client's request to connect.
 *		If this is called on a WebSocket server, the response object will contain
 *		the server's own response to the client.
 *
 * @param metadata
 *		The metadata object representing the WebSocket connection.
 *
 * @result
 *		The server response.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_ws_response_t
nw_ws_metadata_copy_server_response(nw_protocol_metadata_t metadata);

#ifdef __BLOCKS__

/*!
 * @function nw_ws_response_enumerate_additional_headers
 *
 * @abstract
 *		Enumerates the list of additional headers on the server's response.
 *
 * @param response
 *		The server response.
 *
 * @param enumerator
 *		The enumerator block.
 *
 * @result
 *		Whether the enumeration completed.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_ws_response_enumerate_additional_headers(nw_ws_response_t response,
											NW_NOESCAPE nw_ws_additional_header_enumerator_t enumerator);

/*!
 * @typedef nw_ws_client_request_handler_t
 *
 * @abstract
 *		A block to be invoked when a WebSocket server receives a WebSocket
 *		client's request to connect.
 *
 * @param request
 *		The client request.
 *
 * @result
 *		The server response.
 */
typedef _Nonnull nw_ws_response_t (^nw_ws_client_request_handler_t)(_Nonnull nw_ws_request_t request);

/*!
 * @typedef nw_ws_options_set_client_request_handler
 *
 * @abstract
 *		Set callback handler to be invoked when a WebSocket server receives a
 *		WebSocket client's request to connect.
 *
 * @param options
 *		The protocol options object.
 *
 * @param client_queue
 *		The queue on which the client request handler will be delivered.
 *
 * @param handler
 *		The callback handler.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_ws_options_set_client_request_handler(nw_protocol_options_t options,
										 dispatch_queue_t client_queue,
										 nw_ws_client_request_handler_t handler);

#endif // __BLOCKS__

NW_ASSUME_NONNULL_END

__END_DECLS

#endif /* __NW_WS_OPTIONS_H__ */
