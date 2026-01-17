//
//  framer_options.h
//  Network
//
//  Copyright (c) 2018-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_FRAMER_OPTIONS_H__
#define __NW_FRAMER_OPTIONS_H__

#ifndef __NW_INDIRECT__
#error "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/protocol_options.h>
#include <Network/endpoint.h>
#include <Network/parameters.h>

#include <dispatch/dispatch.h>


__BEGIN_DECLS

/*!
 * @typedef nw_framer_t
 * @abstract
 *		A Network Framer is an instance of a protocol in a connection's protocol
 *		stack that parses and writes messages on top of a transport protocol, such
 *		as a TCP stream. A framer can add and parse headers or delimiters around
 *		application data to provide a message-oriented abstraction.
 *
 *		In order to create a framer protocol, first define it using
 *		nw_framer_create_definition(). This can be used to create options with
 *		nw_framer_create_options(), which can be added to an nw_protocol_stack_t.
 *		The callbacks and actions for the framer's protocol instance can be
 *		set once an instance of the framer is delivered with the start_handler.
 *
 *		In order to send and receive framer messages on an nw_connection_t, use
 *		nw_framer_message_t as part of a nw_content_context_t.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_FRAMER_IMPL
NW_OBJECT_DECL(nw_framer);
#endif // NW_FRAMER_IMPL

NW_ASSUME_NONNULL_BEGIN

#pragma mark - Messages

/*!
 * @typedef nw_framer_message_t
 * @abstract
 *		A framer message is an instance of protocol metadata associated
 *		with the definition of a framer, created by nw_framer_create_definition().
 */
typedef nw_protocol_metadata_t nw_framer_message_t;

/*!
 * @function nw_framer_protocol_create_message
 *
 * @abstract
 *		Create an instance of a framer message on which per-
 *		message options can be configured when sending data
 *		on a connection. This is intended to be used by the
 *		application above the connection to send message data
 *		down to the framer protocol instance.
 *
 * @param definition
 *		The framer protocol definition, as retrieved from
 *		nw_protocol_options_copy_definition() on the framer options.
 *
 * @result
 *		Returns a retained protocol metadata object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_framer_message_t
nw_framer_protocol_create_message(nw_protocol_definition_t definition);

/*!
 * @function nw_protocol_metadata_is_framer_message
 *
 * @abstract
 *		Checks if a protocol metadata object is a framer protocol
 *		message. This indicates whether or not it is compatible
 *		with the framer message setters and accessors.
 *
 * @param metadata
 *		The protocol metadata to check.
 *
 * @result
 *		Returns true if the metadata is associated with a framer
 *		protocol definition, false otherwise.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_protocol_metadata_is_framer_message(nw_protocol_metadata_t metadata);

/*!
 * @function nw_framer_message_create
 *
 * @abstract
 *		Create a framer message, given a framer instance. This
 *		is intended to be used within the implementation of
 *		the framer protocol to create messages that are delivered
 *		as input to the application.
 *
 * @param framer
 *		The framer instance object.
 *
 * @result
 *		Returns a retained framer message object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_framer_message_t
nw_framer_message_create(nw_framer_t framer);

#ifdef __BLOCKS__

/*!
 * @typedef nw_framer_message_dispose_value_t
 *
 * @abstract
 *		A block to be invoked when a value stored in a framer message is disposed.
 *		If the value was created using malloc(), for example, it should be freed here.
 *
 * @param value
 *		A pointer to the stored message value.
 */
typedef void (^nw_framer_message_dispose_value_t)(void *value);

/*!
 * @function nw_framer_message_set_value
 *
 * @abstract
 *		Set a key-value pair on a framer message, with a custom
 *		dispose function for the value.
 *
 * @param message
 *		The framer message object.
 *
 * @param key
 *		The string key to identify the value.
 *
 * @param value
 *		A pointer to the value to store.
 *
 * @param dispose_value
 *		A block to invoke to dispose the stored value.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_message_set_value(nw_framer_message_t message,
							const char *key,
							void * _Nullable value,
							_Nullable nw_framer_message_dispose_value_t dispose_value);

/*!
 * @function nw_framer_message_access_value
 *
 * @abstract
 *		Access the value with a key on a framer message.
 *
 * @param message
 *		The framer message object.
 *
 * @param key
 *		The string key to identify the value.
 *
 * @param access_value
 *		A block to invoke inline with the pointer to the stored value.
 *		This pointer may be NULL if no value is stored for the key.
 *
 * @return
 *		Returns the boolean value returned by the access_value block,
 *		or else false if the parameters were invalid.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_framer_message_access_value(nw_framer_message_t message,
							   const char *key,
							   NW_NOESCAPE bool (^access_value)(const void * _Nullable value));

#endif // __BLOCKS__

#ifdef __OBJC__

/*!
 * @function nw_framer_message_set_object_value
 *
 * @abstract
 *		Set a key-value pair on a framer message, where the
 *		value is a reference-counted object.
 *
 * @param message
 *		The framer message object.
 *
 * @param key
 *		The string key to identify the value.
 *
 * @param value
 *		A reference counted object to store.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_message_set_object_value(nw_framer_message_t message,
								   const char *key,
								   _Nullable id value);

/*!
 * @function nw_framer_message_copy_object_value
 *
 * @abstract
 *		Copy the stored object value using a key on a framer message.
 *
 * @param message
 *		The framer message object.
 *
 * @param key
 *		The string key to identify the value.
 *
 * @return
 *		Returns a reference counted object with a +1 reference count,
 *		or NULL if no value was found for the specified key.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED _Nullable id
nw_framer_message_copy_object_value(nw_framer_message_t message,
									const char *key);

#endif // __OBJC__

#pragma mark - Framer Options

#ifdef __BLOCKS__

typedef enum {
	nw_framer_start_result_ready = 1,
	nw_framer_start_result_will_mark_ready = 2,
} nw_framer_start_result_t;

/*!
 * @typedef nw_framer_start_result_t
 *
 * @abstract
 *		A block to be invoked when starting a new instance of the framer
 *		protocol. This may occur more than once for a single nw_connection.
 *
 * @param framer
 *		A new instance of the framer protocol. This handle should be used
 *		to set callbacks, such as with nw_framer_set_input_handler()
 *		and nw_framer_set_output_handler(); and to perform actions, such
 *		as nw_framer_deliver_input() and nw_framer_write_output().
 *
 * @result
 *		Return whether or not the start should implicitly mark the protocol
 *		as "ready" using nw_framer_start_result_ready, or that the protocol
 *		will call nw_framer_mark_ready() later using
 *		nw_framer_start_result_will_mark_ready.
 */
typedef nw_framer_start_result_t (^nw_framer_start_handler_t)(nw_framer_t framer);

/*!
 * @define NW_FRAMER_CREATE_FLAGS_DEFAULT
 * @discussion Empty flags to define default options on a framer protocol.
 */
#define NW_FRAMER_CREATE_FLAGS_DEFAULT				0x00

/*!
 * @function nw_framer_create_definition
 *
 * @abstract
 *		Create a protocol definition for a custom framer protocol.
 *
 * @param identifier
 *		A string identifier used to name this framer protocol. This does not
 *		define uniqueness, and is primarily used for logging and debugging.
 *
 * @param flags
 *		Flags to describe extended options on framer protocol behavior,
 *		all prefixed with "NW_FRAMER_CREATE_FLAGS_".
 *
 * @param start_handler
 *		A block to be invoked when starting a new instance of the framer
 *		protocol. This may occur more than once for a single nw_connection.
 *
 * @result
 *		Returns a retained protocol definition that can be used with protocol
 *		options and metadata.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_protocol_definition_t
nw_framer_create_definition(const char *identifier,
							uint32_t flags,
							nw_framer_start_handler_t start_handler);

/*!
 * @function nw_framer_create_options
 *
 * @abstract
 *		Create protocol options from a framer definition. This object can
 *		be added to an nw_protocol_stack_t to be used in an nw_connection_t
 *		or an nw_listener_t.
 *
 * @param framer_definition
 *		A protocol definition created with nw_framer_create_definition().
 *
 * @result
 *		Returns a retained protocol options object to add into a protocol
 *		stack.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_protocol_options_t
nw_framer_create_options(nw_protocol_definition_t framer_definition);

#pragma mark - Framer Implementation Callbacks

/*!
 * @typedef nw_framer_input_handler_t
 *
 * @abstract
 *		A handler block to be invoked whenever new input
 *		data is available to be parsed. When this block is
 *		run, the implementation should call functions like
 *		nw_framer_parse_input() and nw_framer_deliver_input().
 *
 *		Each invocation represents new data being available
 *		to read from the network. This data may be insufficient
 *		to complete a message, or may contain multiple messages.
 *		Implementations are expected to try to parse messages
 *		in a loop until parsing fails to read enough to continue.
 *
 * @param framer
 *		The instance of the framer protocol.
 *
 * @result
 *		Return a hint of the number of bytes that should be present
 *		before invoking this handler again. Returning 0 indicates
 *		that the handler should be invoked once any data is available.
 */
typedef size_t (^nw_framer_input_handler_t)(nw_framer_t framer);

/*!
 * @function nw_framer_set_input_handler
 *
 * @abstract
 *		Set a handler block to be invoked whenever new input
 *		data is available to be parsed. When this block is
 *		run, the implementation should call functions like
 *		nw_framer_parse_input() and nw_framer_deliver_input().
 *
 *		This setter is required, and must only be set from within
 *		the invocation of a nw_framer_start_handler_t.
 *
 * @param framer
 *		The framer instance object, passed via the
 *		nw_framer_start_handler_t block.
 *
 * @param input_handler
 *		The block to invoke whenever new input data is available.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_set_input_handler(nw_framer_t framer,
							nw_framer_input_handler_t input_handler);

/*!
 * @typedef nw_framer_output_handler_t
 *
 * @abstract
 *		A handler block to be invoked whenever an output
 *		message is ready to be sent. When this block is
 *		run, the implementation should call functions like
 *		nw_framer_parse_output() and nw_framer_write_output().
 *
 *		Each invocation represents a single complete or partial
 *		message that is being sent. The implementation is
 *		expected to write this message or let it be dropped
 *		in this handler.
 *
 * @param framer
 *		The instance of the framer protocol.
 *
 * @param message
 *		The framer message being sent.
 *
 * @param message_length
 *		The length of the data associated with this message send.
 *		If the message is not complete, the length represents the
 *		partial message length being sent, which may be smaller
 *		than the complete message length.
 *
 * @param is_complete
 *		A boolean indicating whether or not the message is now complete.
 */
typedef void (^nw_framer_output_handler_t)(nw_framer_t framer,
										   nw_framer_message_t message,
										   size_t message_length,
										   bool is_complete);

/*!
 * @function nw_framer_set_output_handler
 *
 * @abstract
 *		Set a handler block to be invoked whenever an output
 *		message is ready to be sent. When this block is
 *		run, the implementation should call functions like
 *		nw_framer_parse_output() and nw_framer_write_output().
 *
 *		This setter is required, and must only be set from within
 *		the invocation of a nw_framer_start_handler_t.
 *
 * @param framer
 *		The framer instance object, passed via the
 *		nw_framer_start_handler_t block.
 *
 * @param output_handler
 *		The block to invoke whenever a new output message is ready
 *		to be sent.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_set_output_handler(nw_framer_t framer,
							 nw_framer_output_handler_t output_handler);

/*!
 * @typedef nw_framer_wakeup_handler_t
 *
 * @abstract
 *		A handler block to be invoked whenever the wakeup timer
 *		set via nw_framer_schedule_wakeup() fires. This is intended to
 *		be used for sending keepalives or other control traffic.
 *
 * @param framer
 *		The instance of the framer protocol.
 */
typedef void (^nw_framer_wakeup_handler_t)(nw_framer_t framer);

/*!
 * @function nw_framer_set_wakeup_handler
 *
 * @abstract
 *		Set a handler block to be invoked whenever the wakeup timer
 *		set via nw_framer_schedule_wakeup() fires. This is intended to
 *		be used for sending keepalives or other control traffic.
 *
 *		This setter is optional, and must only be set from within
 *		the invocation of a nw_framer_start_handler_t.
 *
 * @param framer
 *		The framer instance object, passed via the
 *		nw_framer_start_handler_t block.
 *
 * @param wakeup_handler
 *		The block to invoke whenever the timeout set by
 *		nw_framer_schedule_wakeup() is reached.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_set_wakeup_handler(nw_framer_t framer,
							 nw_framer_wakeup_handler_t wakeup_handler);

/*!
 * @typedef nw_framer_stop_handler_t
 *
 * @abstract
 *		A handler block to be invoked when the connection
 *		is being disconnected, to allow the framer implementation
 *		a chance to send any final data.
 *
 * @param framer
 *		The instance of the framer protocol.
 *
 * @result
 *		Return true if the framer is done and the connection
 *		can be fully disconnected, or false the stop should
 *		be delayed. If false, the implementation must later
 *		call nw_framer_mark_failed_with_error().
 */
typedef bool (^nw_framer_stop_handler_t)(nw_framer_t framer);

/*!
 * @function nw_framer_set_stop_handler
 *
 * @abstract
 *		Set a handler block to be invoked when the connection
 *		is being disconnected, to allow the framer implementation
 *		a chance to send any final data.
 *
 *		This setter is optional, and must only be set from within
 *		the invocation of a nw_framer_start_handler_t.
 *
 * @param framer
 *		The framer instance object, passed via the
 *		nw_framer_start_handler_t block.
 *
 * @param stop_handler
 *		The block to invoke when the connection is disconnected.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_set_stop_handler(nw_framer_t framer,
						   nw_framer_stop_handler_t stop_handler);

/*!
 * @typedef nw_framer_cleanup_handler_t
 *
 * @abstract
 *		A handler block to be invoked when the protocol stack
 *		is being torn down and deallocated. This is the opportunity
 *		for the framer implementation to release any state it may
 *		have saved.
 *
 * @param framer
 *		The instance of the framer protocol.
 */
typedef void (^nw_framer_cleanup_handler_t)(nw_framer_t framer);

/*!
 * @function nw_framer_set_cleanup_handler
 *
 * @abstract
 *		Set a handler block to be invoked when the protocol stack
 *		is being torn down and deallocated. This is the opportunity
 *		for the framer implementation to release any state it may
 *		have saved.
 *
 *		This setter is optional, and must only be set from within
 *		the invocation of a nw_framer_start_handler_t.
 *
 * @param framer
 *		The framer instance object, passed via the
 *		nw_framer_start_handler_t block.
 *
 * @param cleanup_handler
 *		The block to invoke when the protocol stack is being deallocated.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_set_cleanup_handler(nw_framer_t framer,
							  nw_framer_cleanup_handler_t cleanup_handler);

#pragma mark - Framer Implementation Actions

/*!
 * @function nw_framer_mark_ready
 *
 * @abstract
 *		Mark the connection associated with the framer instance
 *		as ready (see nw_connection_state_ready). This is intended
 *		to be used by protocols that require a handshake before being
 *		able to send application data. This should only be called
 *		if the return value to the nw_framer_start_handler_t block
 *		was nw_framer_start_result_will_call_ready.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_mark_ready(nw_framer_t framer);

/*!
 * @function nw_framer_prepend_application_protocol
 *
 * @abstract
 *		Dynamically add a protocol to a connection establishment
 *		attempt "above" the framer protocol. This means that the
 *		protocol above will start running once the framer becomes
 *		ready by calling nw_framer_mark_ready(). This can only
 *		be used with framers that return a value of
 *		nw_framer_start_result_will_call_ready to their start
 *		handlers. An example of using this functionality is
 *		adding a security protocol, like TLS, above a framer
 *		once that framer completes its initial handshake.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance object.
 *
 * @param protocol_options
 *		Protocol options for an application protocol to dynamically
 *		add "above" the framer.
 *
 * @result Returns true if the protocol was successfully added,
 *		or false it it could not be added. This will fail if
 *		the framer is already marked ready.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_framer_prepend_application_protocol(nw_framer_t framer,
									   nw_protocol_options_t protocol_options);

/*!
 * @function nw_framer_mark_failed_with_error
 *
 * @abstract
 *		Mark the connection associated with the framer instance
 *		as failed (see nw_connection_state_failed).
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance object.
 *
 * @param error_code
 *		An error code to describe why the connection failed.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_mark_failed_with_error(nw_framer_t framer, int error_code);

/*!
 * @typedef nw_framer_parse_completion_t
 *
 * @abstract
 *		A completion block that is invoked inline to parse available
 *		bytes, either input or output. This is the way a framer can
 *		access the underlying buffer for data being sent or received.
 *		The block has a side effect of advancing the parsing cursor
 *		by the number of bytes specified in the return value.
 *
 * @param buffer
 *		The buffer of bytes being sent or received.
 *
 * @param buffer_length
 *		The number of valid bytes in buffer.
 *
 * @param is_complete
 *		The boolean indicating if this section of the buffer indicates
 *		the end of a message or stream.
 *
 * @result
 *		Return the number of bytes by which to advance the input or
 *		output cursor. For example, if nw_framer_parse_input() is called
 *		and the completion returns 0, calling nw_framer_parse_input() again
 *		will allow the implementation to start parsing again at the same
 *		start location. However, if the completion returns 10, the next
 *		call to nw_framer_parse_input() will return bytes starting from 10
 *		bytes beyond the previous call.
 *
 *		The cursors also define the offsets at which data being delivered
 *		or written using nw_framer_deliver_input_no_copy() and
 *		nw_framer_write_output_no_copy() will start.
 *
 *		The returned value for incrementing the cursor may be larger than
 *		the length of the buffer just parsed. This allows an implementation
 *		to "skip" ahead by a number of bytes if it knows it does not
 *		need to parse more.
 */
typedef size_t (^nw_framer_parse_completion_t)(uint8_t * _Nullable buffer,
											   size_t buffer_length,
											   bool is_complete);

/*!
 * @function nw_framer_parse_input
 *
 * @abstract
 *		Parse currently available input from the location of the input
 *		cursor in the stream or message being parsed.
 *
 *		The parse completion block will always be invoked inline exactly once.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance object.
 *
 * @param minimum_incomplete_length
 *		The minimum number of bytes to parse. If this amount is
 *		not available, the parse completion block will be invoked
 *		with 0 bytes.
 *
 * @param maximum_length
 *		The maximum number of bytes to parse as a contiguous buffer.
 *		If temp_buffer is not NULL, then this represents the length
 *		of valid bytes in temp_buffer.
 *
 * @param temp_buffer
 *		A buffer provided by the caller to copy parse bytes into.
 *		If it is not NULL, it must have at least maximum_length bytes
 *		available, and any parsed bytes will be copied into the buffer.
 *		If it is NULL, the buffer provided in the completion will not
 *		copy unless a copy is required to provide the minimum bytes
 *		as a contiguous buffer. The temp_buffer allows the caller to
 *		guarantee alignment properties of the buffer it parses.
 *
 * @param parse
 *		The completion that provides the bytes to parse, which will
 *		be called exactly once.
 *
 * @result
 *		Returns true if the parse succeeded, or false if not enough
 *		bytes were available.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_framer_parse_input(nw_framer_t framer,
					  size_t minimum_incomplete_length,
					  size_t maximum_length,
					  uint8_t * _Nullable temp_buffer,
					  NW_NOESCAPE nw_framer_parse_completion_t parse);

/*!
 * @function nw_framer_deliver_input
 *
 * @abstract
 *		Deliver arbitrary data to the application. This is intended to
 *		deliver any data that is generated or transformed by the
 *		protocol instance. It will incur a copy of bytes.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance object.
 *
 * @param input_buffer
 *		The bytes to deliver to the application. This must be non-NULL.
 *		If an empty message needs to be delivered, use
 *		nw_framer_deliver_input_no_copy().
 *
 * @param input_length
 *		The length of input_buffer. This must be non-zero.
 *
 * @param message
 *		The message to associate with the received data.
 *
 * @param is_complete
 *		A boolean indicating whether or not this data represents
 *		the end of the message.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_deliver_input(nw_framer_t framer,
						const uint8_t *input_buffer,
						size_t input_length,
						nw_framer_message_t message,
						bool is_complete);

/*!
 * @function nw_framer_deliver_input_no_copy
 *
 * @abstract
 *		Deliver bytes directly to the application without any
 *		transformation or copy. The bytes will start at the current
 *		input cursor used for parsing, and will implicitly advance
 *		the cursor by the length being delivered.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance object.
 *
 * @param input_length
 *		The number of input bytes to deliver. This will advance
 *		the parsing cursor by the specified number of bytes.
 *
 *		The length may be 0, which can be used to indicate the
 *		end of the message if is_complete is set.
 *
 * @param message
 *		The message to associate with the received data.
 *
 * @param is_complete
 *		A boolean indicating whether or not this data represents
 *		the end of the message.
 *
 * @result
 *		Returns true if the input was delivered immediately, or
 *		false if it will be delivered once more bytes become available.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_framer_deliver_input_no_copy(nw_framer_t framer,
								size_t input_length,
								nw_framer_message_t message,
								bool is_complete);

/*!
 * @function nw_framer_pass_through_input
 *
 * @abstract
 *		Mark the input side of the framer as a pass-through, which
 *		means the framer will not be notified of any further input
 *		data.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_pass_through_input(nw_framer_t framer);

/*!
 * @function nw_framer_parse_output
 *
 * @abstract
 *		Parse currently available output from a message from the location
 *		of the output cursor in the message being parsed.
 *
 *		The parse completion block will always be invoked inline exactly once.
 *
 *		This function must only be called from within the output handler
 *		set with nw_framer_set_output_handler().
 *
 * @param framer
 *		The framer instance object.
 *
 * @param minimum_incomplete_length
 *		The minimum number of bytes to parse. If this amount is
 *		not available, the parse completion block will be invoked
 *		with 0 bytes.
 *
 * @param maximum_length
 *		The maximum number of bytes to parse as a contiguous buffer.
 *		If temp_buffer is not NULL, then this represents the length
 *		of valid bytes in temp_buffer.
 *
 * @param temp_buffer
 *		A buffer provided by the caller to copy parse bytes into.
 *		If it is not NULL, it must have at least maximum_length bytes
 *		available, and any parsed bytes will be copied into the buffer.
 *		If it is NULL, the buffer provided in the completion will not
 *		copy unless a copy is required to provide the minimum bytes
 *		as a contiguous buffer. The temp_buffer allows the caller to
 *		guarantee alignment properties of the buffer it parses.
 *
 * @param parse
 *		The completion that provides the bytes to parse, which will
 *		be called exactly once.
 *
 * @result
 *		Returns true if the parse succeeded, or false if not enough
 *		bytes were available.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_framer_parse_output(nw_framer_t framer,
					   size_t minimum_incomplete_length,
					   size_t maximum_length,
					   uint8_t * _Nullable temp_buffer,
					   NW_NOESCAPE nw_framer_parse_completion_t parse);

/*!
 * @function nw_framer_write_output
 *
 * @abstract
 *		Write arbitrary bytes as part of an outbound message. This
 *		is intended to be used for adding headers around application
 *		data, or writing any other data that is generated or transformed
 *		by the protocol instance. It does not pass along data directly
 *		from the application.
 *
 *		This variant will copy bytes.
 *
 *		This function may be called as part of any framer callback,
 *		not just the output handler.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance object.
 *
 * @param output_buffer
 *		The bytes to write.
 *
 * @param output_length
 *		The length of output_buffer.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_write_output(nw_framer_t framer,
					   const uint8_t *output_buffer,
					   size_t output_length);

/*!
 * @function nw_framer_write_output_data
 *
 * @abstract
 *		Write arbitrary bytes as part of an outbound message. This
 *		is intended to be used for adding headers around application
 *		data, or writing any other data that is generated or transformed
 *		by the protocol instance. It does not pass along data directly
 *		from the application.
 *
 *		This variant is the same as nw_framer_write_output(), but allows
 *		the implementation to pass its buffer as a dispatch_data_t to
 *		avoid a copy.
 *
 *		This function may be called as part of any framer callback,
 *		not just the output handler.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance object.
 *
 * @param output_data
 *		A dispatch_data_t to write.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_write_output_data(nw_framer_t framer,
							dispatch_data_t output_data);

/*!
 * @function nw_framer_write_output_no_copy
 *
 * @abstract
 *		Write bytes directly from the application without any
 *		transformation or copy. The bytes will start at the current
 *		output cursor used for parsing, and will implicitly advance
 *		the cursor by the length being written.
 *
 *		This function must only be called from within the output handler
 *		set with nw_framer_set_output_handler().
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance object.
 *
 * @param output_length
 *		The number of application bytes to write. This will advance
 *		the parsing cursor by the specified number of bytes.
 *
 * @return
 *		Returns true if the write could be completed, otherwise
 *		false if the call was made from an invalid context
 *		or with an invalid number of bytes.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_framer_write_output_no_copy(nw_framer_t framer,
							   size_t output_length);

/*!
 * @function nw_framer_pass_through_output
 *
 * @abstract
 *		Mark the output side of the framer as a pass-through, which
 *		means the framer will not be notified of any further output
 *		data.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_pass_through_output(nw_framer_t framer);

#define NW_FRAMER_WAKEUP_TIME_FOREVER (~0ull)

/*!
 * @function nw_framer_schedule_wakeup
 *
 * @abstract
 *		Schedule a wakeup on the framer instance for a number of
 *		milliseconds into the future. If this is called multiple
 *		times before the timeout is reached, the new value replaces
 *		the previous value.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance object.
 *
 * @param milliseconds
 *		The number of milliseconds into the future at which to
 *		invoke the wakeup handler. Pass the reserved value
 *		NW_FRAMER_WAKEUP_TIME_FOREVER to push the wakeup timer
 *		out to "forever", effectively unscheduling the timer.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_schedule_wakeup(nw_framer_t framer,
						  uint64_t milliseconds);

/*!
 * @typedef nw_framer_block_t
 *
 * @abstract
 *		A block to perform actions on a framer's scheduling context.
 */
typedef void (^nw_framer_block_t)(void);

/*!
 * @function nw_framer_async
 *
 * @abstract
 *		Schedule a block asynchronously on the framer instance. This
 *		must be used anytime the caller wants to perform any other
 *		action on the framer instance while not directly in the callstack
 *		of a callback from the framer.
 *
 * @param framer
 *		The framer instance object.
 *
 * @param async_block
 *		A block to execute on the correct scheduling context for the
 *		framer instance.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_framer_async(nw_framer_t framer,
				nw_framer_block_t async_block);

#endif // __BLOCKS__

#pragma mark - Framer Implementation Accessors

/*!
 * @function nw_framer_copy_remote_endpoint
 *
 * @abstract
 *		Access the remote endpoint being used for a given
 *		instance of a framer.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance.
 *
 * @return
 *		Returns a retained endpoint object representing
 *		the remote side of a connection.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_endpoint_t
nw_framer_copy_remote_endpoint(nw_framer_t framer);

/*!
 * @function nw_framer_copy_local_endpoint
 *
 * @abstract
 *		Access the local endpoint being used for a given
 *		instance of a framer.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance.
 *
 * @return
 *		Returns a retained endpoint object representing
 *		the local side of a connection.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_endpoint_t
nw_framer_copy_local_endpoint(nw_framer_t framer);

/*!
 * @function nw_framer_copy_parameters
 *
 * @abstract
 *		Access the parameters being used for a given
 *		instance of a framer.
 *
 *		To ensure thread safety, this function can only be called
 *		in one of the callback blocks invoked on the framer, or
 *		in a block passed to nw_framer_async().
 *
 * @param framer
 *		The framer instance.
 *
 * @return
 *		Returns a retained parameters object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_parameters_t
nw_framer_copy_parameters(nw_framer_t framer);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif // __NW_FRAMER_OPTIONS_H__
