//
//  tls_options.h
//  Network
//
//  Copyright (c) 2017-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_TLS_OPTIONS_H__
#define __NW_TLS_OPTIONS_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/protocol_options.h>

#include <Security/Security.h>
#include <uuid/uuid.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @function nw_protocol_copy_tls_definition
 *
 * @abstract
 *		Access the definition of the default system protocol implementation
 *		of TLS (Transport Layer Security). This protocol can be used
 *		as part of a connection's protocol stack as an application protocol.
 *
 * @result
 *		Returns a retained protocol definition object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_protocol_definition_t
nw_protocol_copy_tls_definition(void);

#pragma mark - Options

/*!
 * @function nw_tls_create_options
 *
 * @abstract
 *		Create an instance of TLS protocol options. This object can be added
 *		to an nw_protocol_stack_t to be used in an nw_connection_t or
 *		an nw_listener_t.
 *
 * @result
 *		Returns a retained protocol options object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_protocol_options_t
nw_tls_create_options(void);

/*!
 * @function nw_tls_copy_sec_protocol_options
 *
 * @abstract
 *		Access the sec_protocol_options_t for a given network protocol
 *		options instance. See <Security/SecProtocolOptions.h> for functions
 *		to further configure security options.
 *
 * @param options
 *		An nw_protocol_options_t that has been created for TLS.
 *
 * @result
 *		Returns a retained sec_protocol_options_t object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED sec_protocol_options_t
nw_tls_copy_sec_protocol_options(nw_protocol_options_t options);

#pragma mark - Metadata

/*!
 * @function nw_protocol_metadata_is_tls
 *
 * @abstract
 *		Checks if a protocol metadata object is compatible with the
 *		accessors defined in this file for the default system
 *		implementation of TLS.
 *
 * @result
 *		Returns true if the metadata is for the default system TLS,
 *		false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_protocol_metadata_is_tls(nw_protocol_metadata_t metadata);

/*!
 * @function nw_tls_copy_sec_protocol_metadata
 *
 * @abstract
 *		Access the sec_protocol_metadata_t for a given network protocol
 *		metadata instance. See <Security/SecProtocolMetadata.h> for functions
 *		to access security properties.
 *
 * @param metadata
 *		An nw_protocol_metadata_t for the TLS protocol.
 *
 * @result
 *		Returns a retained sec_protocol_metadata_t object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED sec_protocol_metadata_t
nw_tls_copy_sec_protocol_metadata(nw_protocol_metadata_t metadata);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif // __NW_TLS_OPTIONS_H__
