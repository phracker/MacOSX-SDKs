//
//  protocol_options.h
//  Network
//
//  Copyright (c) 2017-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_PROTOCOL_OPTIONS_H__
#define __NW_PROTOCOL_OPTIONS_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/nw_object.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @typedef nw_protocol_definition_t
 * @abstract
 *		A Network Protocol Definition is a handle that represents a protocol implementation
 *		that can be added into a protocol stack, configured, and used to transmit data and
 *		metadata. For example, a protocol definition for TCP represents an implementation of
 *		TCP that can be used for a connection.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_PROTOCOL_DEFINITION_IMPL
NW_OBJECT_DECL(nw_protocol_definition);
#endif // NW_PROTOCOL_DEFINITION_IMPL

/*!
 * @function nw_protocol_definition_is_equal
 *
 * @abstract
 *		Compare two protocol definitions to check if they represent the same protocol.
 *
 * @param definition1
 *		The first definition to compare
 *
 * @param definition2
 *		The second definition to compare
 *
 * @result
 *		Returns true if the definitions represent the same protocol, false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_protocol_definition_is_equal(nw_protocol_definition_t definition1, nw_protocol_definition_t definition2);

/*!
 * @typedef nw_protocol_options_t
 * @abstract
 *		A Network Protocol Options object holds a single definition (nw_protocol_definition_t)
 *		along with a set of protocol-specific options. The options are used to build protocol
 *		stack definitions in an nw_parameters_t object. Each protocol is responsible for
 *		defining its own accessor functions to set and get options.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_PROTOCOL_OPTIONS_IMPL
NW_OBJECT_DECL(nw_protocol_options);
#endif // NW_PROTOCOL_OPTIONS_IMPL

/*!
 * @function nw_protocol_options_copy_definition
 *
 * @abstract
 *		Retrieve the protocol definition for a given options object.
 *
 * @param options
 *		The protocol options to check
 *
 * @result
 *		Returns a reference-counted protocol definition object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_protocol_definition_t
nw_protocol_options_copy_definition(nw_protocol_options_t options);

/*!
 * @typedef nw_protocol_metadata_t
 * @abstract
 *		A Network Protocol Metadata object holds a single definition (nw_protocol_definition_t)
 *		along with a set of protocol-specific metadata. This metadata allows clients to pass down
 *		protocol requirements specific to some content being sent, as well as to retrieve metadata
 *		specific to some content that was received. Each protocol is responsible for defining
 *		its own accessor functions to set and get metadata.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_PROTOCOL_METADATA_IMPL
NW_OBJECT_DECL(nw_protocol_metadata);
#endif // NW_PROTOCOL_METADATA_IMPL

/*!
 * @function nw_protocol_metadata_copy_definition
 *
 * @abstract
 *		Retrieve the protocol definition for a given metadata object.
 *
 * @param metadata
 *		The protocol metadata to check
 *
 * @result
 *		Returns a reference-counted protocol definition object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_protocol_definition_t
nw_protocol_metadata_copy_definition(nw_protocol_metadata_t metadata);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif // __NW_PROTOCOL_OPTIONS_H__
