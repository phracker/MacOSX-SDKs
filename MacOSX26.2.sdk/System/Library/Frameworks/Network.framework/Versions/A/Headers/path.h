//
//  path.h
//  Network
//
//  Copyright (c) 2017-2025 Apple Inc. All rights reserved.
//

#ifndef __NW_PATH_H__
#define __NW_PATH_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

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

/*!
 * @typedef nw_path_unsatisfied_reason_t
 * @abstract
 *		A network path unsatisfied reason may indicate the reason the path is currently unsatisfied for some conditions.
 */
typedef enum {
	/*! @const nw_path_unsatisfied_reason_not_available No reason is given */
	nw_path_unsatisfied_reason_not_available = 0,
	/*! @const nw_path_unsatisfied_reason_cellular_denied The user has disabled cellular */
	nw_path_unsatisfied_reason_cellular_denied = 1,
	/*! @const nw_path_unsatisfied_reason_wifi_denied The user has disabled Wi-Fi */
	nw_path_unsatisfied_reason_wifi_denied = 2,
	/*! @const nw_path_unsatisfied_reason_local_network_denied The user has disabled local network access */
	nw_path_unsatisfied_reason_local_network_denied = 3,
	/*! @const nw_path_unsatisfied_reason_vpn_inactive A required VPN is not active */
	nw_path_unsatisfied_reason_vpn_inactive API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0)) = 4,
} nw_path_unsatisfied_reason_t;

/*!
 * @function nw_path_get_unsatisfied_reason
 *
 * @abstract
 *		Retrieves a reason the path is not satisfied. In some cases, the reason helps to
 *		determine why the path is not satisfied. While the path may be unsatisfied for more
 *		than one reason, only the first reason will be given. In many cases, the path may be
 *		unsatisfied with no reason available.
 *
 * @param path
 *		The path object to check.
 *
 * @result
 *		Returns a reason the path is unsatisfied or nw_path_unsatisfied_reason_not_available if a reason is not available.
 */
API_AVAILABLE(macos(11.0), ios(14.2), watchos(7.1), tvos(14.2))
nw_path_unsatisfied_reason_t
nw_path_get_unsatisfied_reason(nw_path_t path);

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
 * @function nw_path_is_constrained
 *
 * @abstract
 *		Checks if the path uses any network interfaces that are considered constrained
 *		to the user.
 *
 * @param path
 *		The path object to check.
 *
 * @result
 *		Returns true if the path uses any network interface that is considered constrained,
 *		false otherwise.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_path_is_constrained(nw_path_t path);

/*!
 * @function nw_path_is_ultra_constrained
 *
 * @abstract
 *		Checks if the path uses any network interfaces that are considered ultra-constrained.
 *
 * @param path
 *		The path object to check.
 *
 * @result
 *		Returns true if the path uses any network interface that is considered ultra-constrained,
 *		false otherwise.
 */
API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0))
bool
nw_path_is_ultra_constrained(nw_path_t path);

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

#ifdef __BLOCKS__

typedef bool (^nw_path_enumerate_gateways_block_t)(nw_endpoint_t gateway);

/*!
 * @function nw_path_enumerate_gateways
 *
 * @abstract
 *		List the IP addresses of the routers acting as the gateways for the path.
 *
 * @param path
 *		The path object to check.
 *
 * @param enumerate_block
 *		A block that will return the gateways associated with the path. Returning
 *		true from the block will continue to enumerate, and returning false will stop
 *		enumerating.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_path_enumerate_gateways(nw_path_t path,
						   NW_NOESCAPE nw_path_enumerate_gateways_block_t enumerate_block);

#endif // __BLOCKS__

/*!
 * @typedef nw_link_quality_t
 * @abstract
 *		Link quality measurement is a representation of the expected capabilities of the link layer network
 *		attachment. Use this value to tune initial values for algorithms that can scale with the
 *		capabilities of the network. Do not use this value to gate connection attempts or to override
 *		adjustments that would be made based on actual network performance.
 */
typedef enum {
	/*! @const nw_link_quality_unknown No link quality measurement is available */
	nw_link_quality_unknown = 0,
	/*! @const nw_link_quality_minimal Link quality is minimal */
	nw_link_quality_minimal = 10,
	/*! @const nw_link_quality_moderate Link quality is moderate */
	nw_link_quality_moderate = 20,
	/*! @const nw_link_quality_good Link quality is good */
	nw_link_quality_good = 30
} nw_link_quality_t;

/*!
 * @function nw_path_get_link_quality
 *
 * @abstract
 *		Fetches the link quality measurement for the interface.
 *		Link quality measurement is a representation of the expected capabilities of the link layer network
 *		attachment. Use this value to tune initial values for algorithms that can scale with the
 *		capabilities of the network. Do not use this value to gate connection attempts or to override
 *		adjustments that would be made based on actual network performance.
 *
 * @param path
 *		The path object to check.
 *
 * @result
 *		Returns the link quality measurement of the link layer network attachment.
 *		Returns nw_link_quality_unknown if there is no measurement available.
 */
API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0))
nw_link_quality_t
nw_path_get_link_quality(nw_path_t path);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif /* defined(__NW_PATH_H__) */

