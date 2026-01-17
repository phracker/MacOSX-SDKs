//
//  ip_options.h
//  Network
//
//  Copyright (c) 2017-2019 Apple. All rights reserved.
//

#ifndef __NW_IP_OPTIONS_H__
#define __NW_IP_OPTIONS_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/protocol_options.h>
#include <Network/parameters.h>

#include <uuid/uuid.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @function nw_protocol_copy_ip_definition
 *
 * @abstract
 *		Access the definition of the default system protocol implementation
 *		of IP (Internet Protocol). This protocol can be used
 *		as part of a connection's protocol stack as the internet protocol.
 *
 * @result
 *		Returns a retained protocol definition object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_protocol_definition_t
nw_protocol_copy_ip_definition(void);

#pragma mark - Options

/*!
 * @typedef nw_ip_version_t
 * @abstract
 *		A specific version of the Internet Protocol.
 */
typedef enum {
	/*! @const nw_ip_version_any Allow any IP version */
	nw_ip_version_any = 0,
	/*! @const nw_ip_version_4 Use IP version 4 (IPv4) */
	nw_ip_version_4 = 4,
	/*! @const nw_ip_version_6 Use IP version 6 (IPv6) */
	nw_ip_version_6 = 6,
} nw_ip_version_t;

/*!
 * @function nw_ip_options_set_version
 *
 * @abstract
 *		Specify a single version of the Internet Protocol to allow.
 *		Setting this value will constrain which address endpoints can
 *		be used, and will filter DNS results during connection establishment.
 *
 * @param options
 *		An IP protocol options object.
 *
 * @param version
 *		A specific, restricted IP version.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_ip_options_set_version(nw_protocol_options_t options,
						  nw_ip_version_t version);

/*!
 * @function nw_ip_options_set_hop_limit
 *
 * @abstract
 *		Configure the IP hop limit (or 'TTL' for IPv4).
 *
 * @param options
 *		An IP protocol options object.
 *
 * @param hop_limit
 *		The hop limit to set on outgoing IP packets.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_ip_options_set_hop_limit(nw_protocol_options_t options,
							uint8_t hop_limit);

/*!
 * @function nw_ip_options_set_use_minimum_mtu
 *
 * @abstract
 *		Configure IP to use the minimum MTU value, which
 *		is 1280 bytes for IPv6. This value has no effect for
 *		IPv4.
 *
 * @param options
 *		An IP protocol options object.
 *
 * @param use_minimum_mtu
 *		A boolean indicating that the IP should use
 *		its minimum MTU value.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_ip_options_set_use_minimum_mtu(nw_protocol_options_t options,
								  bool use_minimum_mtu);

/*!
 * @function nw_ip_options_set_disable_fragmentation
 *
 * @abstract
 *		Configure IP to disable fragmentation on outgoing
 *		packets.
 *
 * @param options
 *		An IP protocol options object.
 *
 * @param disable_fragmentation
 *		A boolean indicating that the IP should use
 *		disable fragmentation on outgoing packets.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_ip_options_set_disable_fragmentation(nw_protocol_options_t options,
										bool disable_fragmentation);

/*!
 * @function nw_ip_options_set_calculate_receive_time
 *
 * @abstract
 *		Configure IP to calculate receive time for inbound
 *		packets.
 *
 * @param options
 *		An IP protocol options object.
 *
 * @param calculate_receive_time
 *		A boolean indicating that the IP packets
 *		should mark their receive time in IP metadata.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_ip_options_set_calculate_receive_time(nw_protocol_options_t options,
										 bool calculate_receive_time);

/*!
 * @typedef nw_ip_local_address_preference_t
 * @abstract
 *		Preference for local addresses selection.
 */
typedef enum {
	/*! @const nw_ip_local_address_preference_default Use system default for address selection */
	nw_ip_local_address_preference_default = 0,
	/*! @const nw_ip_local_address_preference_temporary Prefer temporary (privacy) addresses */
	nw_ip_local_address_preference_temporary = 1,
	/*! @const nw_ip_local_address_preference_stable Prefer stable addresses */
	nw_ip_local_address_preference_stable = 2,
} nw_ip_local_address_preference_t;

/*!
 * @function nw_ip_options_set_local_address_preference
 *
 * @abstract
 *		Specify a preference for how to select local addresses for outbound
 *		connections.
 *
 * @param options
 *		An IP protocol options object.
 *
 * @param preference
 *		Preference for how to select local addresses.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_ip_options_set_local_address_preference(nw_protocol_options_t options,
										   nw_ip_local_address_preference_t preference);

#pragma mark - Metadata

/*!
 * @function nw_ip_create_metadata
 *
 * @abstract
 *		Create an instance of IP metadata that can be used
 *		to configure per-packet options when sending data
 *		on a connection.
 *
 * @result
 *		Returns a retained protocol metadata object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_protocol_metadata_t
nw_ip_create_metadata(void);

/*!
 * @function nw_protocol_metadata_is_ip
 *
 * @abstract
 *		Checks if a protocol metadata object is compatible with the
 *		accessors defined in this file for the default system
 *		implementation of IP.
 *
 * @result
 *		Returns true if the metadata is for the default system IP,
 *		false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_protocol_metadata_is_ip(nw_protocol_metadata_t metadata);

/*!
 * @typedef nw_ip_ecn_flag_t
 * @abstract
 *		ECN flags marked in IP headers to indicate congestion.
 */
typedef enum {
	/*! @const nw_ip_ecn_flag_non_ect Non ECN-Capable Transport, value 0b00*/
	nw_ip_ecn_flag_non_ect = 0,
	/*! @const nw_ip_ecn_flag_ect_0 ECN Capable Transport (0), value 0b10 */
	nw_ip_ecn_flag_ect_0 = 2,
	/*! @const nw_ip_ecn_flag_ect_1 ECN Capable Transport (1), value 0b01 */
	nw_ip_ecn_flag_ect_1 = 1,
	/*! @const nw_ip_ecn_flag_ce Congestion Experienced, value 0b11 */
	nw_ip_ecn_flag_ce = 3,
} nw_ip_ecn_flag_t;

/*!
 * @function nw_ip_metadata_set_ecn_flag
 *
 * @abstract
 *		Sets ECN flags on IP metadata. This will take effect if
 *		applied to any sent content.
 *
 * @param metadata
 *		An IP metadata object.
 *
 * @param ecn_flag
 *		The ECN flag to apply to packets.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_ip_metadata_set_ecn_flag(nw_protocol_metadata_t metadata,
							nw_ip_ecn_flag_t ecn_flag);

/*!
 * @function nw_ip_metadata_get_ecn_flag
 *
 * @abstract
 *		Gets ECN flags from IP metadata. This will be set only
 *		for metadata associated with received content.
 *
 * @param metadata
 *		An IP metadata object.
 *
 * @return
 *		Returns the ECN flag received from a packet.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
nw_ip_ecn_flag_t
nw_ip_metadata_get_ecn_flag(nw_protocol_metadata_t metadata);

/*!
 * @function nw_ip_metadata_set_service_class
 *
 * @abstract
 *		Sets service class on IP metadata. This will not generally
 *		translate into TOS or Traffic Class bits unless the network
 *		explictly supports it, but it will impact local queuing of
 *		packets.
 *
 * @param metadata
 *		An IP metadata object.
 *
 * @param service_class
 *		The service class to apply to packets.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_ip_metadata_set_service_class(nw_protocol_metadata_t metadata,
								 nw_service_class_t service_class);

/*!
 * @function nw_ip_metadata_get_service_class
 *
 * @abstract
 *		Gets service class from IP metadata. This reflects the value
 *		set using nw_ip_metadata_set_service_class. It will not
 *		be received from the network.
 *
 * @param metadata
 *		An IP metadata object.
 *
 * @return
 *		Returns the service class set on a packet.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
nw_service_class_t
nw_ip_metadata_get_service_class(nw_protocol_metadata_t metadata);

/*!
 * @function nw_ip_metadata_get_receive_time
 *
 * @abstract
 *		Access the time at which a packet was received. This is
 *		useful for calculating precise timing for round-trip-time
 *		estimates. Same as clock_gettime_nsec_np(CLOCK_MONOTONIC_RAW).
 *
 *		The receive time will be 0 unless timestamps have been enabled
 *		using nw_ip_options_set_calculate_receive_time().
 *
 * @param metadata
 *		An IP metadata object.
 *
 * @return
 *		Returns the time that the packet was received.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
uint64_t
nw_ip_metadata_get_receive_time(nw_protocol_metadata_t metadata);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif // __NW_IP_OPTIONS_H__
