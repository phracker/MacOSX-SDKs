//
//  udp_options.h
//  Network
//
//  Copyright (c) 2017-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_UDP_OPTIONS_H__
#define __NW_UDP_OPTIONS_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/protocol_options.h>

#include <uuid/uuid.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @function nw_protocol_copy_udp_definition
 *
 * @abstract
 *		Access the definition of the default system protocol implementation
 *		of UDP (User Datagram Protocol). This protocol can be used
 *		as part of a connection's protocol stack as the transport protocol.
 *
 * @result
 *		Returns a retained protocol definition object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_protocol_definition_t
nw_protocol_copy_udp_definition(void);

#pragma mark - Options

/*!
 * @function nw_udp_create_options
 *
 * @abstract
 *		Create an instance of UDP protocol options. This object can be added
 *		to an nw_protocol_stack_t to be used in an nw_connection_t or
 *		an nw_listener_t.
 *
 * @result
 *		Returns a retained protocol options object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_protocol_options_t
nw_udp_create_options(void);

/*!
 * @function nw_udp_options_set_prefer_no_checksum
 *
 * @abstract
 *		Configure UDP to skip computing checksums when sending.
 *		This will only take effect when running over IPv4.
 *
 * @param options
 *		A UDP protocol options object.
 *
 * @param prefer_no_checksum
 *		A boolean that indicates if UDP is allowed to skip computing
 *		its checksum.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_udp_options_set_prefer_no_checksum(nw_protocol_options_t options,
									  bool prefer_no_checksum);

#pragma mark - Metadata

/*!
 * @function nw_udp_create_metadata
 *
 * @abstract
 *		Create an instance of UDP metadata that can be used
 *		to configure per-datagram options when sending data
 *		on a connection.
 *
 * @result
 *		Returns a retained protocol metadata object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_protocol_metadata_t
nw_udp_create_metadata(void);

/*!
 * @function nw_protocol_metadata_is_udp
 *
 * @abstract
 *		Checks if a protocol metadata object is compatible with the
 *		accessors defined in this file for the default system
 *		implementation of UDP.
 *
 * @result
 *		Returns true if the metadata is for the default system UDP,
 *		false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_protocol_metadata_is_udp(nw_protocol_metadata_t metadata);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif // __NW_UDP_OPTIONS_H__
