//
//  ethernet_channel.h
//  Network
//
//  Copyright (c) 2019, 2021 Apple Inc. All rights reserved.
//

#ifndef __NW_ETHERNET_CHANNEL_H__
#define __NW_ETHERNET_CHANNEL_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/error.h>
#include <Network/parameters.h>

__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @typedef nw_ethernet_channel_t
 * @abstract
 *		An Ethernet channel is an object that represents a bi-directional data channel to send
 *      and receive Ethernet frames with a custom EtherType.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_ETHERNET_CHANNEL_IMPL
NW_OBJECT_DECL(nw_ethernet_channel);
#endif // NW_ETHERNET_CHANNEL_IMPL

/*!
 * @typedef nw_ethernet_channel_state_t
 * @abstract
 *		Channel states sent by nw_ethernet_channel_set_state_changed_handler.
 *		States generally progress forward and do not move backwards, with the
 *		exception of preparing and waiting, which may alternate before the channel
 *		becomes ready or failed.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
typedef enum {
	/*!
	 *	@const nw_ethernet_channel_state_invalid The state of the channel is not valid. This state
	 *		will never be delivered in the channel's state update handler, and can be treated as
	 *		an unexpected value.
	 */
	nw_ethernet_channel_state_invalid = 0,
	/*! @const nw_ethernet_channel_state_waiting The channel is waiting for a usable network before re-attempting */
	nw_ethernet_channel_state_waiting = 1,
	/*! @const nw_ethernet_channel_state_preparing The channel is in the process of establishing */
	nw_ethernet_channel_state_preparing = 2,
	/*! @const nw_ethernet_channel_state_ready The channel is established and ready to send and receive data */
	nw_ethernet_channel_state_ready = 3,
	/*! @const nw_ethernet_channel_state_failed The channel has irrecoverably closed or failed */
	nw_ethernet_channel_state_failed = 4,
	/*! @const nw_ethernet_channel_state_cancelled The channel has been cancelled by the caller */
	nw_ethernet_channel_state_cancelled = 5,
} nw_ethernet_channel_state_t;

/*!
 * @function nw_ethernet_channel_create
 *
 * @abstract
 *		Creates an Ethernet channel with a custom EtherType.
 *
 * @param ether_type
 *		The custom EtherType to be used for all Ethernet frames in this channel. The
 *		EtherType is the two-octet field in an Ethernet frame, indicating the protocol
 *		encapsulated in the payload of the frame.  This parameter is in little-endian
 *		byte order.  Only custom EtherType values are supported. This parameter cannot
 *		be an EtherType already handled by the system, such as IPv4, IPv6, ARP, VLAN Tag,
 *		or 802.1x.
 *
 *		Calling processes must hold the "com.apple.developer.networking.custom-protocol"
 *		entitlement.
 *
 * @param interface
 *		The interface on which this custom Ethernet channel will be allowed.
 *
 * @result
 *		Returns an allocated nw_ethernet_channel_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
NW_RETURNS_RETAINED nw_ethernet_channel_t
nw_ethernet_channel_create(uint16_t ether_type, nw_interface_t interface);

/*!
 * @function nw_ethernet_channel_create_with_parameters
 *
 * @abstract
 *		Creates an Ethernet channel with a custom EtherType and networking parameters
 *
 * @param ether_type
 *		The custom EtherType to be used for all Ethernet frames in this channel. The
 *		EtherType is the two-octet field in an Ethernet frame, indicating the protocol
 *		encapsulated in the payload of the frame.  This parameter is in little-endian
 *		byte order.  Only custom EtherType values are supported. This parameter cannot
 *		be an EtherType already handled by the system, such as IPv4, IPv6, ARP, VLAN Tag,
 *		or 802.1x.
 *
 *		Calling processes must hold the "com.apple.developer.networking.custom-protocol"
 *		entitlement.
 *
 * @param interface
 *		The interface on which this custom Ethernet channel will be allowed.
 *
 * @param parameters
 *		nw_parameters_t that allows caller to specify networking parameters such as custom context and queue.
 *
 * @result
 *		Returns an allocated nw_ethernet_channel_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(13.0)) API_UNAVAILABLE(ios, watchos, tvos)
NW_RETURNS_RETAINED nw_ethernet_channel_t
nw_ethernet_channel_create_with_parameters(uint16_t ether_type, nw_interface_t interface, nw_parameters_t parameters);
#ifdef __BLOCKS__

/*!
 * @typedef nw_ethernet_channel_state_changed_handler_t
 * @abstract
 *      A state change handler to handle state changes.
 *
 * @param state
 *	   The current state.
 *
 * @param error
 *     error if present, indicates the reason of the failure.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
typedef void (^nw_ethernet_channel_state_changed_handler_t)(nw_ethernet_channel_state_t state, _Nullable nw_error_t error);

/*!
 * @function nw_ethernet_channel_set_state_changed_handler
 *
 * @abstract
 *		Sets the state change handler. For clients that need to perform cleanup when the
 *		channel has been cancelled, the nw_ethernet_channel_state_cancelled state will
 *		be delivered last.
 *
 * @param ethernet_channel
 *		The ethernet_channel object.
 *
 * @param handler
 *		The state changed handler to call when the channel state changes.
 *		Pass NULL to remove the state changed handler.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
void
nw_ethernet_channel_set_state_changed_handler(nw_ethernet_channel_t ethernet_channel,
											  _Nullable nw_ethernet_channel_state_changed_handler_t handler);

#endif // __BLOCKS__

/*!
 * @function nw_ethernet_channel_set_queue
 *
 * @abstract
 *		Sets the client callback queue, on which blocks for events will
 *		be scheduled. This must be done before calling nw_ethernet_channel_start().
 *
 * @param ethernet_channel
 *		The ethernet_channel object.
 *
 * @param queue
 *		The client's dispatch queue.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
void
nw_ethernet_channel_set_queue(nw_ethernet_channel_t ethernet_channel, dispatch_queue_t queue);

/*!
 * @function nw_ethernet_channel_get_maximum_payload_size
 *
 * @abstract
 *		Returns the maximum payload size that can be written
 *		on the channel. Any payloads written must be less than
 *		or equal to this size.  Payloads exceeding this size will be
 *		dropped by 'nw_ethernet_channel_send()'.
 *
 * @param ethernet_channel
 *		The ethernet_channel object.
 *
 * @result
 *		Returns a payload size based on the current MTU of the channel.
 */
API_AVAILABLE(macos(13.0)) API_UNAVAILABLE(ios, watchos, tvos)
uint32_t
nw_ethernet_channel_get_maximum_payload_size(nw_ethernet_channel_t ethernet_channel);

/*!
 * @function nw_ethernet_channel_start
 *
 * @abstract
 *		Starts the Ethernet channel, which will cause the channel to evaluate
 *      its path, and try to become readable and writable.
 *
 * @param ethernet_channel
 *		The ethernet_channel object.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
void
nw_ethernet_channel_start(nw_ethernet_channel_t ethernet_channel);

/*!
 * @function nw_ethernet_channel_cancel
 *
 * @abstract
 *		Cancel the Ethernet channel. This will close the channel. The process of cancellation will be
 *      completed asynchronously, and the final callback event delivered to the caller will be
 *      a state update with a value of nw_ethernet_channel_state_cancelled. Once this update is
 *      delivered, the caller may clean up any associated memory or objects.
 *
 *		Outstanding sends and receives will receive errors before the state changes to cancelled.
 *		There is no guarantee that any outstanding sends that have not yet delivered
 *		completion handlers will send data before the channel is closed.
 *
 * @param ethernet_channel
 *		The ethernet_channel object.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
void
nw_ethernet_channel_cancel(nw_ethernet_channel_t ethernet_channel);

#ifdef __BLOCKS__

/*!
 * @typedef nw_ethernet_address_t
 * @abstract
 *		Address for an Ethernet Frame.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
typedef unsigned char nw_ethernet_address_t[6];

/*!
 * @typedef nw_ethernet_channel_receive_handler_t
 * @abstract
 *		This receive handler is invoked when a frame of the set EtherType is received from the Ethernet
 *      channel.
 *
 * @param content
 *		The received Ethernet payload, which has a length constrained by the maximum Ethernet frame size
 *      of 1518 minus Ethernet header size of (18/14 bytes with/without vlan tag).
 *
 * @param vlan_tag
 *      The vlan tag of the frame, 0 if there is no vlan tag.  This parameter is in little-endian
 *      byte order.
 *
 * @param local_address
 *		The local Ethernet address in the received Ethernet frame header.
 *
 * @param remote_address
 *		The remote Ethernet address in the received Ethernet frame header.
 *
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
typedef void (^nw_ethernet_channel_receive_handler_t)(dispatch_data_t content,
													  uint16_t vlan_tag,
													  _Nonnull nw_ethernet_address_t local_address,
													  _Nonnull nw_ethernet_address_t remote_address);

/*!
 * @function nw_ethernet_channel_set_receive_handler
 *
 * @abstract
 *		Sets the Ethernet channel receive handler. Should be called before nw_ethernet_channel_start.
 *
 * @param ethernet_channel
 *		The Ethernet channel object.
 *
 * @param handler
 *		The event handler to call when the Ethernet channel receives a new frame.
 *		Pass NULL to remove the receive handler.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
void
nw_ethernet_channel_set_receive_handler(nw_ethernet_channel_t ethernet_channel,
										_Nullable nw_ethernet_channel_receive_handler_t handler);

/*!
 * @typedef nw_ethernet_channel_send_completion_t
 * @abstract
 *		A send completion is invoked exactly once for a call to nw_ethernet_channel_send().
 *		The completion indicates that the sent Ethernet frame has been processed by the stack
 *		(not necessarily that it has left the host), or else an error has occurred during
 *		sending.
 *
 * @param error
 *		An error will be sent if the associated frame could not be fully sent before an
 *		error occurred. An error will be sent for any outstanding sends when the channel
 *		is cancelled.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
typedef void (^nw_ethernet_channel_send_completion_t)(_Nullable nw_error_t error);

/*!
 * @function nw_ethernet_channel_send
 *
 * @abstract
 *		Send an Ethernet frame on a channel.  This must be called after the channel
 *      becomes ready.  This is an asynchronous send and the completion block can be used
 *      to determine when the send is complete.
 *
 * @param ethernet_channel
 *		The ethernet_channel object on which to send frame.
 *
 * @param content
 *		An Ethernet payload to send.
 *
 * @param vlan_tag
 *      The vlan tag of the frame.  If vlan_tag is specified, the 802.1Q tag will be included.
 *      TPID will be set to 0x8100 followed by the specified 16-bit vlan_tag (only the highest
 *      3-bit class of service field is supported.  The remaining 13 bits must be set to zero).
 *      Pass 0 to omit the vlan tag for this frame.
 *
 * @param remote_address
 *		Remote Ethernet address for this Ethernet frame.  This is a required parameter.
 *      Note that the local Ethernet address will be the Ethernet address of the specified
 *      interface of this Ethernet channel.
 *
 * @param completion
 *		A callback to be called when the data has been sent, or an error has occurred.
 *		This callback does not indicate that the remote side has acknowledged the data.
 *		This callback does indicate that the data has been sent.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
NW_SWIFT_DISABLE_ASYNC
void
nw_ethernet_channel_send(nw_ethernet_channel_t ethernet_channel,
						 dispatch_data_t content,
						 uint16_t vlan_tag,
						 _Nonnull nw_ethernet_address_t remote_address,
						 nw_ethernet_channel_send_completion_t completion);

#endif // __BLOCKS__

NW_ASSUME_NONNULL_END

__END_DECLS

#endif /* __NW_ETHERNET_CHANNEL_H__ */
