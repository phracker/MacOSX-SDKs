//
//  connection_report.h
//  Network
//
//  Copyright (c) 2018-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_CONNECTION_REPORT_H__
#define __NW_CONNECTION_REPORT_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/connection.h>
#include <Network/interface.h>

NW_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

#pragma mark - Establishment Report

/*!
 * @typedef nw_establishment_report_t
 * @abstract
 *		An Establishment Report contains information about how an nw_connection_t
 *		became established. This is intended to be used for analysis of performance
 *		after connection establishment. The report cannot be gathered until a
 *		connection is in the "ready" state.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_ESTABLISHMENT_REPORT_IMPL
NW_OBJECT_DECL(nw_establishment_report);
#endif // NW_ESTABLISHMENT_REPORT_IMPL

#ifdef __BLOCKS__

typedef void (^nw_establishment_report_access_block_t)(_Nullable nw_establishment_report_t report);

/*!
 * @function nw_connection_access_establishment_report
 *
 * @abstract
 *		Access the establishment report for a connection. The report will be
 *		NULL until the connection is in the "ready" state.
 *
 *		The callback block will be invoked exactly once on the provided queue.
 *
 * @param connection
 *		An established connection.
 *
 * @param queue
 *		The dispatch queue on which to call the access_block.
 *
 * @param access_block
 *		A block to invoke with the establishment report, which may be NULL if the
 *		connection not ready.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_connection_access_establishment_report(nw_connection_t connection,
										  dispatch_queue_t queue,
										  nw_establishment_report_access_block_t access_block);

#endif // __BLOCKS__

/*!
 * @function nw_establishment_report_get_duration_milliseconds
 *
 * @abstract
 *		Retrieve the duration of the connection's establishment. This is
 *		the total time in milliseconds from when the connection attempt began
 *		until the connection becomes ready, including resolution, proxy
 *		evaluation, and protocol handshakes.
 *
 * @param report
 *		An establishment report.
 *
 * @result
 *		Returns the number of milliseconds the connection took to establish.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_establishment_report_get_duration_milliseconds(nw_establishment_report_t report);

/*!
 * @function nw_establishment_report_get_attempt_started_after_milliseconds
 *
 * @abstract
 *		Retrieve the delay from calling start() after which the successful connection
 *		attempt began. For connections that succeed on the first attempt, this value
 *		will be 0. For connections that move into the "waiting" state, this
 *		value will be greater than 0.
 *
 * @param report
 *		An establishment report.
 *
 * @result
 *		Returns the number of milliseconds from connection start to the beginning
 *		of the successful connection attempt.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_establishment_report_get_attempt_started_after_milliseconds(nw_establishment_report_t report);

/*!
 * @function nw_establishment_report_get_previous_attempt_count
 *
 * @abstract
 *		Retrieve the number of connection attempts made before the successful
 *		attempt. For connections that succeed on the first attempt, this value
 *		will be 0. For connections that move into the "waiting" state, this
 *		value will be greater than 0.
 *
 * @param report
 *		An establishment report.
 *
 * @result
 *		Returns the number of connection attempts made before the successful attempt.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint32_t
nw_establishment_report_get_previous_attempt_count(nw_establishment_report_t report);

/*!
 * @function nw_establishment_report_get_used_proxy
 *
 * @abstract
 *		Check if the connection used a proxy during establishment.
 *
 * @param report
 *		An establishment report.
 *
 * @result
 *		Returns true if the connection used a proxy, false otherwise.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_establishment_report_get_used_proxy(nw_establishment_report_t report);

/*!
 * @function nw_establishment_report_get_proxy_configured
 *
 * @abstract
 *		Check if a proxy configuration applied to the connection,
 *		even if the connection did not end up using a proxy for the
 *		successful attempt.
 *
 * @param report
 *		An establishment report.
 *
 * @result
 *		Returns true if a proxy configuration applied to the connection,
 *		false otherwise.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_establishment_report_get_proxy_configured(nw_establishment_report_t report);

/*!
 * @function nw_establishment_report_copy_proxy_endpoint
 *
 * @abstract
 *		Access the endpoint of the proxy used by a connection, if applicable.
 *
 * @param report
 *		An establishment report.
 *
 * @result
 *		Returns an allocated endpoint object if a proxy was used by the connection,
 *		or NULL if no proxy was used.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED _Nullable nw_endpoint_t
nw_establishment_report_copy_proxy_endpoint(nw_establishment_report_t report);

#ifdef __BLOCKS__

/*!
 * @typedef nw_report_resolution_source_t
 * @abstract
 *		The source of a resolution indicates if the set of endpoints was resolved
 *		locally using a cache, or sent a query over the network.
 */
typedef enum {
	/*! @const nw_report_resolution_source_query A query was sent over the network */
	nw_report_resolution_source_query = 1,
	/*! @const nw_report_resolution_source_cache The local cache was used  */
	nw_report_resolution_source_cache = 2,
	/*! @const nw_report_resolution_source_expired_cache An expired entry in the local cache was used */
	nw_report_resolution_source_expired_cache = 3,
} nw_report_resolution_source_t;

typedef bool (^nw_report_resolution_enumerator_t)(nw_report_resolution_source_t source,
												  uint64_t milliseconds,
												  uint32_t endpoint_count,
												  nw_endpoint_t successful_endpoint,
												  nw_endpoint_t preferred_endpoint);

/*!
 * @function nw_establishment_report_enumerate_resolutions
 *
 * @abstract
 *		Enumerate the steps of connection establishment that involved endpoint
 *		resolution, such as DNS hostname resolution and Bonjour service resolution.
 *		The provided block will be called inline zero or more times.
 *
 * @param report
 *		An establishment report.
 *
 * @param enumerate_block
 *		A block to be invoked zero or more times, once for each step of resolution
 *		used during connection establishment.
 *
 *		The values passed to the enumerator are:
 *		- source: The source of the resolution (query or cache).
 *		- milliseconds: The number of milliseconds spent on this resolution step.
 *		- endpoint_count: The number of resolved endpoints discovered by the resolution step.
 *		- successful_endpoint: The resolved endpoint that led to a successful connection.
 *		- preferred_endpoint: The first resolved endpoint attempted, which may be the same as the successful_endpoint.
 *
 *		Returning true from the block indicates that the enumeration should continue.
 *		Returning false indicates that the enumeration should stop.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_establishment_report_enumerate_resolutions(nw_establishment_report_t report,
											  NW_NOESCAPE nw_report_resolution_enumerator_t enumerate_block);

typedef bool (^nw_report_protocol_enumerator_t)(nw_protocol_definition_t protocol,
												uint64_t handshake_milliseconds,
												uint64_t handshake_rtt_milliseconds);

/*!
 * @function nw_establishment_report_enumerate_protocols
 *
 * @abstract
 *		Enumerate the protocols used in the established connection.
 *		The provided block will be called inline zero or more times.
 *
 * @param report
 *		An establishment report.
 *
 * @param enumerate_block
 *		A block to be invoked zero or more times, once for each protocol
 *		used in the established connection.
 *
 *		The values passed to the enumerator are:
 *		- protocol: The protocol definition.
 *		- handshake_milliseconds: The number of milliseconds spent on the protocol's handshake.
 *		- handshake_rtt_milliseconds: The round trip time in milliseconds measured by the protocol's handshake.
 *
 *		Returning true from the block indicates that the enumeration should continue.
 *		Returning false indicates that the enumeration should stop.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_establishment_report_enumerate_protocols(nw_establishment_report_t report,
											NW_NOESCAPE nw_report_protocol_enumerator_t enumerate_block);

#endif // __BLOCKS__

#pragma mark - Data Transfer Report

/*!
 * @typedef nw_data_transfer_report_t
 * @abstract
 *		A Data Transfer Report contains performance information about data
 *		transferred on an nw_connection_t for certain span of time. Multiple reports
 *		can be retrieved from a single connection, starting and ending at different times.
 *		This allows throughput to be measured based on how an application is using
 *		a connection. A report may be created prior to a connection moving into
 *		the "ready" state, but measurements will not be collected until after the
 *		connection is ready.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_DATA_TRANSFER_REPORT_IMPL
NW_OBJECT_DECL(nw_data_transfer_report);
#endif // NW_DATA_TRANSFER_REPORT_IMPL

/*!
 * @function nw_connection_create_new_data_transfer_report
 *
 * @abstract
 *		Create a new data transfer report on a connection. Multiple
 *		reports may be created for a single connection. The report begins
 *		capturing data when the connection becomes ready, or when the
 *		report is created (whichever occurs last).
 *
 *		Call nw_data_transfer_report_collect() to complete collection of
 *		report, after which point the details of the report will be available.
 *
 * @param connection
 *		A connection object, in or before the ready state.
 *
 * @result
 *		Returns an allocated nw_data_transfer_report_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_data_transfer_report_t
nw_connection_create_new_data_transfer_report(nw_connection_t connection);

/*!
 * @typedef nw_data_transfer_report_state_t
 * @abstract
 *		The state of a Data Transfer Report indicates whether or not the contents
 *		have been collected, and are ready to be accessed.
 */
typedef enum {
	/*! @const nw_data_transfer_report_state_collecting The report is outstanding; values cannot be accessed. */
	nw_data_transfer_report_state_collecting = 1,
	/*! @const nw_data_transfer_report_state_collected The report is complete; values can now be accessed. */
	nw_data_transfer_report_state_collected = 2,
} nw_data_transfer_report_state_t;

/*!
 * @function nw_data_transfer_report_get_state
 *
 * @abstract
 *		Access the state of a data transfer report. Once a report
 *		is "collected", individual fields may be read.
 *
 * @param report
 *		A data transfer report to check.
 *
 * @result
 *		Returns the current state of the data transfer report.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
nw_data_transfer_report_state_t
nw_data_transfer_report_get_state(nw_data_transfer_report_t report);

#ifdef __BLOCKS__

typedef void (^nw_data_transfer_report_collect_block_t)(nw_data_transfer_report_t report);

/*!
 * @function nw_data_transfer_report_collect
 *
 * @abstract
 *		Mark a data transfer report as complete, and request collection of
 *		values. Once the report has been collected, the callback block
 *		will be invoked exactly once on the provided dispatch queue.
 *
 *		If a connection is cancelled or fails prior to the report being collected,
 *		the report will automatically be collected. Calling
 *		nw_data_transfer_report_collect() will be redundant but not harmful.
 *
 * @param report
 *		A data transfer report to check.
 *
 * @param queue
 *		The dispatch queue on which to call the collect_block.
 *
 * @param collect_block
 *		A block to invoke once the report has been collected.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_data_transfer_report_collect(nw_data_transfer_report_t report,
								dispatch_queue_t queue,
								nw_data_transfer_report_collect_block_t collect_block);

#endif // __BLOCKS__

/*!
 * @const NW_ALL_PATHS
 * @discussion Pass NW_ALL_PATHS to data transfer report accessors to sum
 *		values across paths where applicable. For values that cannot
 *		sum, the value of the primary path is used.
 */
NW_EXPORT extern const uint32_t _nw_data_transfer_report_all_paths;
#define NW_ALL_PATHS (_nw_data_transfer_report_all_paths)

/*!
 * @function nw_data_transfer_report_get_duration_milliseconds
 *
 * @abstract
 *		Retrieve the duration of the data transfer report. This is a length
 *		of time in milliseconds which can be used to calculate throughput
 *		when compared to application and transport byte counts.
 *
 *		The start time is calculated from when the report was created, or the connection
 *		became ready if the connection was not ready when the report was created.
 *		The duration ends when the report is collected, or the connection fails
 *		or is cancelled.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @result
 *		Returns the duration of the data transport report in milliseconds, or 0
 *		if the report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_duration_milliseconds(nw_data_transfer_report_t report);

/*!
 * @function nw_data_transfer_report_get_path_count
 *
 * @abstract
 *		Retrieve the number of paths used by the connection for the
 *		duration of the report. Any value greater than or equal to 0 and
 *		less than this count may be used as a "path_index" for retrieving
 *		specific details from the report.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @result
 *		Returns the number of paths used by the connection, which
 *		limits the value of the "path_index" parameter used in other report
 *		functions. Returns 0 if the report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint32_t
nw_data_transfer_report_get_path_count(nw_data_transfer_report_t report);

/*!
 * @function nw_data_transfer_report_get_received_ip_packet_count
 *
 * @abstract
 *		Retrieve the number of IP packets received on a given path for the
 *		duration of the report.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function returns
 *		the sum of all paths.
 *
 * @result
 *		Returns the number of IP packets received, or 0
 *		if the report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_received_ip_packet_count(nw_data_transfer_report_t report,
													 uint32_t path_index);

/*!
 * @function nw_data_transfer_report_get_sent_ip_packet_count
 *
 * @abstract
 *		Retrieve the number of IP packets sent on a given path for the
 *		duration of the report.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function returns
 *		the sum of all paths.
 *
 * @result
 *		Returns the number of IP packets sent, or 0 if the report is not
 *		in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_sent_ip_packet_count(nw_data_transfer_report_t report,
												 uint32_t path_index);

/*!
 * @function nw_data_transfer_report_get_received_transport_byte_count
 *
 * @abstract
 *		Retrieve the number of transport protocol bytes (such as TCP stream bytes)
 *		received on a given path for the duration of the report.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function returns
 *		the sum of all paths.
 *
 * @result
 *		Returns the number of transport protocol bytes received, or 0 if the
 *		report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_received_transport_byte_count(nw_data_transfer_report_t report,
														  uint32_t path_index);

/*!
 * @function nw_data_transfer_report_get_received_transport_duplicate_byte_count
 *
 * @abstract
 *		Retrieve the number of duplicate transport protocol bytes (such as
 *		duplicate TCP bytes) received on a given path for the duration of the report.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function returns
 *		the sum of all paths.
 *
 * @result
 *		Returns the number of duplicate transport protocol bytes received, or 0
 *		if the report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_received_transport_duplicate_byte_count(nw_data_transfer_report_t report,
																	uint32_t path_index);

/*!
 * @function nw_data_transfer_report_get_received_transport_out_of_order_byte_count
 *
 * @abstract
 *		Retrieve the number of out-of-order transport protocol bytes (such as
 *		out-of-order TCP bytes) received on a given path for the duration of the report.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function returns
 *		the sum of all paths.
 *
 * @result
 *		Returns the number of out-of-order transport protocol bytes received, or 0
 *		if the report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_received_transport_out_of_order_byte_count(nw_data_transfer_report_t report,
																	   uint32_t path_index);

/*!
 * @function nw_data_transfer_report_get_sent_transport_byte_count
 *
 * @abstract
 *		Retrieve the number of transport protocol bytes (such as TCP stream bytes)
 *		sent on a given path for the duration of the report.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function returns
 *		the sum of all paths.
 *
 * @result
 *		Returns the number of transport protocol bytes sent, or 0
 *		if the report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_sent_transport_byte_count(nw_data_transfer_report_t report,
													  uint32_t path_index);

/*!
 * @function nw_data_transfer_report_get_sent_transport_retransmitted_byte_count
 *
 * @abstract
 *		Retrieve the number of retransmitted transport protocol bytes (such as
 *		retransmitted TCP bytes) sent on a given path for the duration of the report.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function returns
 *		the sum of all paths.
 *
 * @result
 *		Returns the number of retransmitted transport protocol bytes sent, or 0
 *		if the report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_sent_transport_retransmitted_byte_count(nw_data_transfer_report_t report,
																	uint32_t path_index);

/*!
 * @function nw_data_transfer_report_get_transport_smoothed_rtt_milliseconds
 *
 * @abstract
 *		Retrieve the smoothed average for the transport protocol's round trip time
 *		(RTT) on a given path for the duration of the report, measured in milliseconds.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function is
 *		equivalent to passing 0.
 *
 * @result
 *		Returns the smoothed RTT as measured by the transport protocol, or 0
 *		if the report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_transport_smoothed_rtt_milliseconds(nw_data_transfer_report_t report,
																uint32_t path_index);

/*!
 * @function nw_data_transfer_report_get_transport_minimum_rtt_milliseconds
 *
 * @abstract
 *		Retrieve the minimum (best) round trip time (RTT) on a given path for
 *		the duration of the report, measured in milliseconds.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function is
 *		equivalent to passing 0.
 *
 * @result
 *		Returns the minimum RTT as measured by the transport protocol, or 0
 *		if the report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_transport_minimum_rtt_milliseconds(nw_data_transfer_report_t report,
															   uint32_t path_index);

/*!
 * @function nw_data_transfer_report_get_transport_rtt_variance
 *
 * @abstract
 *		Retrieve the variance of the round trip time (RTT) on a given path for
 *		the duration of the report.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function is
 *		equivalent to passing 0.
 *
 * @result
 *		Returns the RTT variance as measured by the transport protocol, or 0
 *		if the report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_transport_rtt_variance(nw_data_transfer_report_t report,
												   uint32_t path_index);

/*!
 * @function nw_data_transfer_report_get_received_application_byte_count
 *
 * @abstract
 *		Retrieve the number of application bytes received on a given
 *		path for the duration of the report.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function returns
 *		the sum of all paths.
 *
 * @result
 *		Returns the number of application bytes received, or 0
 *		if the report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_received_application_byte_count(nw_data_transfer_report_t report,
															uint32_t path_index);

/*!
 * @function nw_data_transfer_report_get_sent_application_byte_count
 *
 * @abstract
 *		Retrieve the number of application bytes sent on a given
 *		path for the duration of the report.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function returns
 *		the sum of all paths.
 *
 * @result
 *		Returns the number of application bytes sent, or 0
 *		if the report is not in the "collected" state.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
uint64_t
nw_data_transfer_report_get_sent_application_byte_count(nw_data_transfer_report_t report,
														uint32_t path_index);

/*!
 * @function nw_data_transfer_report_copy_path_interface
 *
 * @abstract
 *		Retrieve the interface used for data transfer for a given
 *		path used by a connection.
 *
 * @param report
 *		A data transfer report in the "collected" state.
 *
 * @param path_index
 *		The index for the path over which data is transferred.
 *		For non-multipath connections, pass 0 as the path index to access
 *		the single path. Passing NW_ALL_PATHS for this function is
 *		equivalent to passing 0.
 *
 * @result
 *		Returns a retained nw_interface_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails if the report is not yet collected.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_interface_t
nw_data_transfer_report_copy_path_interface(nw_data_transfer_report_t report,
											uint32_t path_index);

__END_DECLS

NW_ASSUME_NONNULL_END

#endif /* defined(__NW_CONNECTION_REPORT_H__) */
