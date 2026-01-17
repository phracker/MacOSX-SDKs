//
//  tcp_options.h
//  Network
//
//  Copyright (c) 2017-2018 Apple. All rights reserved.
//

#ifndef __NW_TCP_OPTIONS_H__
#define __NW_TCP_OPTIONS_H__

#include <Network/protocol_options.h>

#include <uuid/uuid.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @function nw_protocol_copy_tcp_definition
 *
 * @abstract
 *		Access the definition of the default system protocol implementation
 *		of TCP (Transmission Control Protocol). This protocol can be used
 *		as part of a connection's protocol stack as the transport protocol.
 *
 * @result
 *		Returns a retained protocol definition object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_protocol_definition_t
nw_protocol_copy_tcp_definition(void);

#pragma mark - Options

/*!
 * @function nw_tcp_create_options
 *
 * @abstract
 *		Create an instance of TCP protocol options. This object can be added
 *		to an nw_protocol_stack_t to be used in an nw_connection_t or
 *		an nw_listener_t.
 *
 * @result
 *		Returns a retained protocol options object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_protocol_options_t
nw_tcp_create_options(void);

/*!
 * @function nw_tcp_options_set_no_delay
 *
 * @abstract
 *		Configure TCP to disable Nagle's algorithm, which will
 *		delay sending packets to coalesce sending.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param no_delay
 *		A boolean indicating that TCP should disable
 *		Nagle's algorithm.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_no_delay(nw_protocol_options_t options,
							bool no_delay);

/*!
 * @function nw_tcp_options_set_no_push
 *
 * @abstract
 *		Wait to send TCP data until the connection has finished
 *		writing, or else the TCP send buffer is full.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param no_push
 *		A boolean indicating that TCP should be set into
 *		no-push mode.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_no_push(nw_protocol_options_t options,
						   bool no_push);

/*!
 * @function nw_tcp_options_set_no_options
 *
 * @abstract
 *		Disable sending TCP options and extensions.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param no_options
 *		A boolean indicating that TCP should be set into
 *		no-options mode.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_no_options(nw_protocol_options_t options,
							  bool no_options);

/*!
 * @function nw_tcp_options_set_enable_keepalive
 *
 * @abstract
 *		Enable sending TCP keepalive probes.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param enable_keepalive
 *		A boolean indicating that TCP should send keepalives.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_enable_keepalive(nw_protocol_options_t options,
									bool enable_keepalive);

/*!
 * @function nw_tcp_options_set_keepalive_count
 *
 * @abstract
 *		Configure the number of times TCP keepalive probes
 *		should be sent without reply before terminating
 *		the connection.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param keepalive_count
 *		The number of keepalive probes to send before terminating
 *		the connection.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_keepalive_count(nw_protocol_options_t options,
								   uint32_t keepalive_count);

/*!
 * @function nw_tcp_options_set_keepalive_idle_time
 *
 * @abstract
 *		Configure the amount of time that a connection must be
 *		idle before TCP should start sending keepalive probes.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param keepalive_idle_time
 *		The number of seconds of idleness to wait before keepalive
 *		probes are sent by TCP.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_keepalive_idle_time(nw_protocol_options_t options,
									   uint32_t keepalive_idle_time);

/*!
 * @function nw_tcp_options_set_keepalive_interval
 *
 * @abstract
 *		Configure the amount of time between sending TCP keepalive
 *		probes when the peer is not responding.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param keepalive_interval
 *		The number of seconds of to wait before resending TCP
 *		keepalive probes.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_keepalive_interval(nw_protocol_options_t options,
									  uint32_t keepalive_interval);

/*!
 * @function nw_tcp_options_set_maximum_segment_size
 *
 * @abstract
 *		Directly configure the maximum segment size (MSS)
 *		TCP will use.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param maximum_segment_size
 *		The maximum segment size in bytes.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_maximum_segment_size(nw_protocol_options_t options,
										uint32_t maximum_segment_size);

/*!
 * @function nw_tcp_options_set_connection_timeout
 *
 * @abstract
 *		Define a timeout value after which TCP connection
 *		establishment will give up.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param connection_timeout
 *		A timeout for TCP connection establishment, in seconds.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_connection_timeout(nw_protocol_options_t options,
									  uint32_t connection_timeout);

/*!
 * @function nw_tcp_options_set_persist_timeout
 *
 * @abstract
 *		Define a timeout value after which TCP connections
 *		in the persist state will terminate. See RFC 6429.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param persist_timeout
 *		The TCP persist timeout, in seconds.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_persist_timeout(nw_protocol_options_t options,
								   uint32_t persist_timeout);

/*!
 * @function nw_tcp_options_set_retransmit_connection_drop_time
 *
 * @abstract
 *		Define a timeout value after which TCP will drop
 *		a connection with unacknowledged retransmissions.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param retransmit_connection_drop_time
 *		A timeout for TCP retransmission attempts, in seconds.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_retransmit_connection_drop_time(nw_protocol_options_t options,
												   uint32_t retransmit_connection_drop_time);

/*!
 * @function nw_tcp_options_set_retransmit_fin_drop
 *
 * @abstract
 *		Cause TCP to drop connections after not receiving
 *		an ACK multiple times after a FIN, currently set at three.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param retransmit_fin_drop
 *		A boolean to cause TCP to drop its connection after
 *		not receiving an ACK after a FIN.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_retransmit_fin_drop(nw_protocol_options_t options,
									   bool retransmit_fin_drop);

/*!
 * @function nw_tcp_options_set_disable_ack_stretching
 *
 * @abstract
 *		Configure TCP to disable ACK stretching. ACKs will be sent
 *		for every other data packet.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param disable_ack_stretching
 *		A boolean to cause TCP to disable ACK stretching.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_disable_ack_stretching(nw_protocol_options_t options,
										  bool disable_ack_stretching);

/*!
 * @function nw_tcp_options_set_enable_fast_open
 *
 * @abstract
 *		Configure TCP to enable TCP Fast Open (TFO). This may take effect
 *		even when TCP is not the top-level protocol in the protocol stack.
 *		For example, if TLS is running over TCP, the Client Hello message
 *		may be sent as fast open data.
 *
 *		If TCP is the top-level protocol in the stack (the one the application
 *		directly interacts with), TFO will be disabled unless the application
 *		indicated that it will provide its own fast open data by calling
 *		nw_parameters_set_fast_open_enabled().
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param enable_fast_open
 *		A boolean to enable TFO.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_enable_fast_open(nw_protocol_options_t options,
									bool enable_fast_open);

/*!
 * @function nw_tcp_options_set_disable_ecn
 *
 * @abstract
 *		Configure TCP to disable default Explicit Congestion
 *		Notification (ECN) behavior.
 *
 * @param options
 *		A TCP protocol options object.
 *
 * @param disable_ecn
 *		A boolean to disable ECN support in TCP.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_tcp_options_set_disable_ecn(nw_protocol_options_t options,
							   bool disable_ecn);

#pragma mark - Metadata

/*!
 * @function nw_protocol_metadata_is_tcp
 *
 * @abstract
 *		Checks if a protocol metadata object is compatible with the
 *		accessors defined in this file for the default system
 *		implementation of TCP.
 *
 * @result
 *		Returns true if the metadata is for the default system TCP,
 *		false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_protocol_metadata_is_tcp(nw_protocol_metadata_t metadata);

/*!
 * @function nw_tcp_get_available_receive_buffer
 *
 * @abstract
 *		Fetch the number of bytes waiting to be read from the receive buffer.
 *
 * @result
 *		The number of bytes available in the receive buffer.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
uint32_t
nw_tcp_get_available_receive_buffer(nw_protocol_metadata_t metadata);

/*!
 * @function nw_tcp_get_available_send_buffer
 *
 * @abstract
 *		Fetch the number of bytes waiting to be acknowledged in the send buffer.
 *
 * @result
 *		The number of bytes waiting to be acknowledged.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
uint32_t
nw_tcp_get_available_send_buffer(nw_protocol_metadata_t metadata);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif // __NW_TCP_OPTIONS_H__
