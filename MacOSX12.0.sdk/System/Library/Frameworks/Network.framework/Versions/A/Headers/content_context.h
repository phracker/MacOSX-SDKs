//
//  content_context.h
//  Network
//
//  Copyright (c) 2017-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_CONTENT_CONTEXT_H__
#define __NW_CONTENT_CONTEXT_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/protocol_options.h>
#include <Network/nw_object.h>

#include <dispatch/dispatch.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @typedef nw_content_context_t
 * @abstract
 *		A Content Context represents a set of metadata associated with the act of
 *		sending or receiving data on a connection.
 *
 *		The number of contexts that will exist on a single connection will vary
 *		based on the protocol used by the connection. Protocols that present a
 *		byte-stream abstraction will have a single context in each direction
 *		(send and receive); protocols that present a datagram or message-based
 *		abstraction will have many contexts, one per datagram or message. The
 *		granularity of contexts will always represent the highest-level protocol
 *		in the connection. To be specific, if a byte-stream protocol is running
 *		a datagram protocol (such as TCP over IP), there will only be one context
 *		in each direction, as dictated by TCP; whereas if a message-based protocol
 *		is running over a byte-stream protocol (such as a framing protocol over TCP),
 *		there will be one context for each framed message.
 *
 *		When sending content, the context also allows the client of the API to specify
 *		how the content should be treated relative to other content on the connection,
 *		via priority, expiration, and dependencies.
 *
 *		A context may contain one or more metadata handles to set or access protocol-
 *		specific data associated with the content.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_CONTENT_CONTEXT_IMPL
NW_OBJECT_DECL(nw_content_context);
#endif // NW_CONTENT_CONTEXT_IMPL

/*!
 * @function nw_content_context_create
 * @discussion Create a context object to represent properties associated with
 *		networking content. If the same context object is associated with multiple
 *		content blobs, then those pieces of content will be considered to be continuations
 *		of the same message.
 * @param context_identifier A string description of the context
 * @result Returns a new context context object
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_content_context_t
nw_content_context_create(const char *context_identifier);

/*!
 * @function nw_content_context_get_identifier
 * @discussion Access the identifier description.
 * @result Returns the context's identifier string.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
const char *
nw_content_context_get_identifier(nw_content_context_t context);

/*!
 * @function nw_content_context_get_is_final
 * @discussion Check if this is the final context for a connection. When receiving,
 *		once a final context is complete, the connection is "read closed" and will not
 *		receive more content. See nw_content_context_set_is_final() for a description
 *		of how to set is_final for sending contexts.
 * @param context The context object
 * @result Returns true if the context is the final context for a connection.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_content_context_get_is_final(nw_content_context_t context);

/*!
 * @function nw_content_context_set_is_final
 * @discussion Mark whether or not this context is the final context for a
 *		connection. When sending, marking a context as final will perform
 *		a "write close" once the context is complete, indicating that no more content
 *		will be sent. As a convenience for sending a final context, use
 *		NW_CONNECTION_FINAL_MESSAGE_CONTEXT.
 * @param context The context object
 * @param is_final If set to true, mark the context as the final context to send on a connection.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_content_context_set_is_final(nw_content_context_t context,
								bool is_final);

/*!
 * @function nw_content_context_get_expiration_milliseconds
 * @discussion Retrieve the number of milliseconds after which the content will expire.
 *		See nw_content_context_set_expiration_milliseconds for further discussion.
 * @param context The context object
 * @result Returns content expiration, or 0 if not set.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
uint64_t
nw_content_context_get_expiration_milliseconds(nw_content_context_t context);

/*!
 * @function nw_content_context_set_expiration_milliseconds
 * @discussion Set an expiration (in milliseconds) after which content may be dropped.
 *		If the expiration time is reached, the content may not be sent. If the value is
 *		0, there is no expiration for the content. The expiration timer starts when the
 *		content is enqueued using nw_connection_send().
 * @param context The context object
 * @param expiration_milliseconds The number of milliseconds after which content will expire
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_content_context_set_expiration_milliseconds(nw_content_context_t context,
											   uint64_t expiration_milliseconds);

/*!
 * @function nw_content_context_get_relative_priority
 * @discussion Get the relative priority for the content. See
 *		nw_content_context_set_relative_priority for further discussion.
 * @param context The context object
 * @result Returns the relative priority, between 0.0 (lowest priority)
 *		to 1.0 (highest priority). The default value is 0.5.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
double
nw_content_context_get_relative_priority(nw_content_context_t context);

/*!
 * @function nw_content_context_set_relative_priority
 * @discussion Set A relative priority of the content, compared to other
 *		content on the same connection. Priorities range from 0.0 (lowest
 *		priority) to 1.0 (highest priority), where content with higher
 *		priority will scheduled first if all else is equal.
 *		The default value is 0.5.
 * @param context The context object
 * @param relative_priority The relative priority of the content, between
 *		0.0 (lowest priority) to 1.0 (highest priority).
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_content_context_set_relative_priority(nw_content_context_t context,
										 double relative_priority);

/*!
 * @function nw_content_context_set_antecedent
 * @discussion Set a context as an antecedent to this content context.
 *		The associated content will not be sent until all of its antecedents have been
 *		completed. If any of the antecedents fail with an error, this content will
 *		fail as well.
 * @param context The context object
 * @param antecendent_context A context associated with content that should precede
 *		this content.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_content_context_set_antecedent(nw_content_context_t context,
								  _Nullable nw_content_context_t antecendent_context);

/*!
 * @function nw_content_context_copy_antecedent
 * @discussion Copy the optional content context that must be sent prior to this
 *		content. See nw_content_context_set_antecedent for further discussion.
 * @param context The context object
 * @result Returns a context object set as the antecedent, or NULL.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED _Nullable nw_content_context_t
nw_content_context_copy_antecedent(nw_content_context_t context);

/*!
 * @function nw_content_context_set_metadata_for_protocol
 * @discussion Set protocol-specific metadata to a parent content context. If
 *		metadata for the same protocol is set multiple times, the most recently
 *		set metadata will be applied.
 * @param context The context context parent object
 * @param protocol_metadata The per-protocol metadata context object to set
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_content_context_set_metadata_for_protocol(nw_content_context_t context,
											 nw_protocol_metadata_t protocol_metadata);

/*!
 * @function nw_content_context_copy_protocol_metadata
 * @discussion Copy the per-protocol metadata from a parent content context
 * @param context The context context parent object
 * @param protocol The definition identifier of the protocol to retrieve metadata for
 * @result Returns the metadata registered for the protocol, or NULL if there is none
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
_Nullable NW_RETURNS_RETAINED nw_protocol_metadata_t
nw_content_context_copy_protocol_metadata(nw_content_context_t context,
										  nw_protocol_definition_t protocol);

#ifdef __BLOCKS__
/*!
 * @function nw_content_context_foreach_protocol_metadata
 * @discussion Access all per-protocol metadata objects from a parent content context
 * @param context The context context parent object
 * @param foreach_block A block in which protocol definition and metadata will be sent
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_content_context_foreach_protocol_metadata(nw_content_context_t context,
											 void (^foreach_block)(nw_protocol_definition_t definition,
																   nw_protocol_metadata_t metadata));
#endif // __BLOCKS__

NW_ASSUME_NONNULL_END

__END_DECLS

#endif // __NW_CONTENT_CONTEXT_H__
