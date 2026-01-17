//
//  path.h
//  Network
//
//  Copyright (c) 2017-2018 Apple Inc. All rights reserved.
//

#ifndef __NW_PATH_H__
#define __NW_PATH_H__

#include <Network/endpoint.h>
#include <Network/interface.h>
#include <Network/nw_object.h>

#include <stdbool.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @typedef nw_path_t
 * @abstract
 *		A Network Path object represents a snapshot of network path state. This state
 *		represents the known information about the local interface and routes that may
 *		be used to send and receive data. If the network path for a connection changes
 *		due to interface characteristics, addresses, or other attributes, a new nw_path_t
 *		object will be generated. Note that the differences in the path attributes may not
 *		be visible through public accessors, and these changes should be treated merely
 *		as an indication that something about the network has changed.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_PATH_IMPL
NW_OBJECT_DECL(nw_path);
#endif // NW_PATH_IMPL

/*!
 * @typedef nw_path_status_t
 * @abstract
 *		A network path status indicates if there is a usable route available upon which to
 *		send and receive data.
 */
typedef enum {
	/*! @const nw_path_status_invalid The path is not valid */
	nw_path_status_invalid = 0,
	/*! @const nw_path_status_satisfied The path has a usable route upon which to send and receive data */
	nw_path_status_satisfied = 1,
	/*! @const nw_path_status_unsatisfied The path does not have a usable route. This may be due to a network interface being down, or due to system policy.  */
	nw_path_status_unsatisfied = 2,
	/*! @const nw_path_status_satisfiable The path does not currently have a usable route, but a connection attempt will trigger network attachment */
	nw_path_status_satisfiable = 3,
} nw_path_status_t;

/*!
 * @function nw_path_get_status
 *
 * @abstract
 *		Retrieves the status of a path. The status of a specific path object will never
 *		change, as the path object itself is static. If there is a network change, the
 *		object that generated the path object will generate a new path object.
 *
 * @param path
 *		The path object to check.
 *
 * @result
 *		Returns the status of the path, or nw_path_status_invalid if the object is NULL.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
nw_path_status_t
nw_path_get_status(nw_path_t path);

#ifdef __BLOCKS__

typedef bool (^nw_path_enumerate_interfaces_block_t)(nw_interface_t interface);

/*!
 * @function nw_path_enumerate_interfaces
 *
 * @abstract
 *		List all interfaces associated with the path.
 *
 * @param path
 *		The path object to check.
 *
 * @param enumerate_block
 *		A block that will return the interfaces associated with the path. Returning
 *		true from the block will continue to enumerate, and returning false will stop
 *		enumerating.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_path_enumerate_interfaces(nw_path_t path,
							 NW_NOESCAPE nw_path_enumerate_interfaces_block_t enumerate_block);

#endif // __BLOCKS__

/*!
 * @function nw_path_is_equal
 *
 * @abstract
 *		Compares two network path objects and checks if their content is equal.
 *		If they are not equal, they represent two different network states.
 *
 * @param path
 *		The first path object to compare.
 *
 * @param other_path
 *		The second path object to compare.
 *
 * @result
 *		Returns true if the paths are equivalent, or false if there is any difference
 *		between the paths.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_path_is_equal(nw_path_t path, nw_path_t other_path);

/*!
 * @function nw_path_is_expensive
 *
 * @abstract
 *		Checks if the path uses any network interfaces that are considered expensive
 *		to the user, such as, but not limited to, a cellular network.
 *
 * @param path
 *		The path object to check.
 *
 * @result
 *		Returns true if the path uses any network interface that is considered expensive,
 *		false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_path_is_expensive(nw_path_t path);

/*!
 * @function nw_path_has_ipv4
 *
 * @abstract
 *		Checks if the path uses a network interface that supports IPv4 connectivity.
 *
 * @param path
 *		The path object to check.
 *
 * @result
 *		Returns true if the path uses a network interface that supports IPv4,
 *		false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_path_has_ipv4(nw_path_t path);

/*!
 * @function nw_path_has_ipv6
 *
 * @abstract
 *		Checks if the path uses a network interface that supports IPv6 connectivity.
 *
 * @param path
 *		The path object to check.
 *
 * @result
 *		Returns true if the path uses a network interface that supports IPv6,
 *		false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_path_has_ipv6(nw_path_t path);

/*!
 * @function nw_path_has_dns
 *
 * @abstract
 *		Checks if the path has a DNS server configuration set.
 *
 * @param path
 *		The path object to check.
 *
 * @result
 *		Returns true if the path has a DNS server configuration set,
 *		false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_path_has_dns(nw_path_t path);

/*!
 * @function nw_path_uses_interface_type
 *
 * @abstract
 *		Checks if the path uses a network interface with the specified type.
 *
 * @param path
 *		The path object to check.
 *
 * @result
 *		Returns true if the path uses any network interface with the specified type,
 *		false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_path_uses_interface_type(nw_path_t path,
							nw_interface_type_t interface_type);

/*!
 * @function nw_path_copy_effective_local_endpoint
 *
 * @abstract
 *		Retrieve the local endpoint that is being used, if present. If this path
 *		is the path from an nw_connection_t, it represents the address that data
 *		is sent from.
 *
 * @param path
 *		The path object to check.
 *
 * @result
 *		Returns an endpoint that is assigned as the local endpoint for this path,
 *		or NULL if the path does not have a fixed local endpoint.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED _Nullable nw_endpoint_t
nw_path_copy_effective_local_endpoint(nw_path_t path);

/*!
 * @function nw_path_copy_effective_remote_endpoint
 *
 * @abstract
 *		Retrieve the remote endpoint that is being used, if present. If this path
 *		is the path from an nw_connection_t, it represents the address that data
 *		is sent to.
 *
 * @param path
 *		The path object to check.
 *
 * @result
 *		Returns an endpoint that is assigned as the remote endpoint for this path,
 *		or NULL if the path does not have a fixed remote endpoint.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED _Nullable nw_endpoint_t
nw_path_copy_effective_remote_endpoint(nw_path_t path);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif /* defined(__NW_PATH_H__) */

