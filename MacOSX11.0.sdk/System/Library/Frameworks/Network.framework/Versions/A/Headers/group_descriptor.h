//
//  group_descriptor.h
//  Network
//
//  Copyright (c) 2019-2020 Apple Inc. All rights reserved.
//

#ifndef __NW_GROUP_DESCRIPTOR_H__
#define __NW_GROUP_DESCRIPTOR_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/endpoint.h>


NW_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 * @typedef nw_group_descriptor_t
 * @abstract
 *		A Group Descriptor is a collection of endpoints which can be used
 *		for sending and receiving messages.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_GROUP_DESCRIPTOR_IMPL
NW_OBJECT_DECL(nw_group_descriptor);
#endif // NW_GROUP_DESCRIPTOR_IMPL

/*!
 * @function nw_group_descriptor_create_multicast
 *
 * @abstract
 *		Creates a new group descriptor object based on a multicast group,
 *		represented as an address endpoint.
 *
 * @param multicast_group
 *		An address endpoint that contains a multicast group to join.
 *
 * @result
 *		An instantiated group descriptor object or nil if the specified
 *		endpoint is not an address endpoint representing a valid multicast
 *		group.
 */
NW_EXPORT
NW_RETURNS_RETAINED nw_group_descriptor_t
nw_group_descriptor_create_multicast(nw_endpoint_t multicast_group);

/*!
 * @function nw_group_descriptor_add_endpoint
 *
 * @abstract
 *		Add an additional endpoint to a given group descriptor.
 *
 * @param descriptor
 *		A group descriptor.
 *
 * @param endpoint
 *		An endpoint to add to the group.
 *
 * @result Returns true if the endpoint was added, false if the endpoint was
 * 		not of a valid type and therefore not added.
 */
NW_EXPORT
bool
nw_group_descriptor_add_endpoint(nw_group_descriptor_t descriptor,
								 nw_endpoint_t endpoint);

#ifdef __BLOCKS__

/*!
 * @typedef nw_group_descriptor_enumerate_endpoints_block_t
 *
 * @abstract
 *		A block called to enumerate the endpoints that are members of a group.
 *
 * @param endpoint
 *		A member of a group.
 *
 * @return Returning true from the block will continue enumeration, and returning
 * 		false will stop enumeration.
 */
typedef bool (^nw_group_descriptor_enumerate_endpoints_block_t)(nw_endpoint_t endpoint);

/*!
 * @function nw_group_descriptor_enumerate_endpoints
 *
 * @abstract
 *		List all endpoints associated with the group descriptor.
 *
 * @param descriptor
 *		The group descriptor object to check.
 *
 * @param enumerate_block
 *		A block to which the endpoints associated with the descriptor will be passed.
 *		Returning true from the block will continue to enumerate, and returning false will stop
 *		enumerating.
 */
NW_EXPORT
void
nw_group_descriptor_enumerate_endpoints(nw_group_descriptor_t descriptor,
										NW_NOESCAPE nw_group_descriptor_enumerate_endpoints_block_t enumerate_block);

#endif // __BLOCKS__

/*!
 * @function nw_multicast_group_descriptor_set_specific_source
 *
 * @abstract
 *		Require a particular source for this multicast group descriptor.
 *
 * @param multicast_descriptor
 *		The multicast group descriptor to modify.
 *
 * @param source
 *		An endpoint describing the source for this descriptor.
 */
NW_EXPORT
void
nw_multicast_group_descriptor_set_specific_source(nw_group_descriptor_t multicast_descriptor,
												  nw_endpoint_t source);

/*!
 * @function nw_multicast_group_descriptor_set_disable_unicast_traffic
 *
 * @abstract
 *		Disable receiving unicast traffic for a connection group that is also receiving multicast traffic.
 *
 * @param multicast_descriptor
 *		The multicast group descriptor to modify.
 *
 * @param disable_unicast_traffic
 *		A boolean indicating if receiving unicast traffic should be disabled.
 */
NW_EXPORT
void
nw_multicast_group_descriptor_set_disable_unicast_traffic(nw_group_descriptor_t multicast_descriptor,
														  bool disable_unicast_traffic);

/*!
 * @function nw_multicast_group_descriptor_get_disable_unicast_traffic
 *
 * @abstract
 *		Check if receiving unicast traffic has been disabled for a multicast connection group.
 *
 * @param multicast_descriptor
 *		The multicast group descriptor to check.
 *
 * @result A boolean indicating if receiving unicast traffic should be disabled.
 */
NW_EXPORT
bool
nw_multicast_group_descriptor_get_disable_unicast_traffic(nw_group_descriptor_t multicast_descriptor);

__END_DECLS

NW_ASSUME_NONNULL_END

#endif /* __NW_GROUP_DESCRIPTOR_H__ */
