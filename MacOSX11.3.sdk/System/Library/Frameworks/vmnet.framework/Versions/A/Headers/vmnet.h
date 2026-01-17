/*
 * Copyright (c) 2013-2020 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _VMNET_H_
#define _VMNET_H_

#include <dispatch/dispatch.h>
#include <xpc/xpc.h>
#include <objc/objc-api.h>
#include <os/availability.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

#if __has_feature(assume_nonnull)
_Pragma("clang assume_nonnull begin")
#endif

/*!
 * @header vmnet
 *
 * @discussion
 * The vmnet API allows a virtual machine (VM) to send and receive
 * network packets over a virtual vmnet network interface. The vmnet
 * interface can be configured to operate in either host mode,
 * shared mode, or bridged mode.
 *
 * In host mode, the VM can communicate with other VMs and the host OS,
 * but is unable to communicate with the outside network.
 *
 * In shared mode, the VM can reach the Internet through a
 * network address translator (NAT), as well as communicate with other
 * VMs and the host OS.
 *
 * In bridged mode, the VM traffic is bridged directly to a particular
 * physical network interface.
 *
 * @ignorefuncmacro OBJC_ENUM
 * @ignorefuncmacro OBJC_OPTIONS
 * @ignorefuncmacro API_AVAILABLE
 * @ignorefuncmacro API_DEPRECATED
 */

/*!
 * @typedef operating_modes_t
 *
 * @abstract
 * The list of operating modes for a vmnet interface.
 *
 * @discussion
 * The VM specifies the operating mode by setting the vmnet_operation_mode_key
 * property in the interface_desc dictionary.
 *
 * @constant VMNET_HOST_MODE
 * Allows the vmnet interface to communicate with other vmnet interfaces
 * that are in host mode and also with the native host.
 *
 * @constant VMNET_SHARED_MODE
 * Allows traffic originating from the vmnet interface to reach the
 * Internet through a network address translator (NAT). The vmnet interface
 * can also communicate with the native host. By default, the vmnet interface
 * is able to communicate with other shared mode interfaces. If a subnet range
 * is specified, the vmnet interface can communicate with other shared mode
 * interfaces on the same subnet.
 *
 * @constant VMNET_BRIDGED_MODE
 * Bridges the vmnet interface with a physical network interface.
 * In the call to vmnet_start_interface(), the interface_desc
 * dictionary must contain the vmnet_shared_interface_name_key
 * property specifying the name of the physical interface.
 */
typedef OBJC_ENUM(uint32_t, operating_modes_t) {
	VMNET_HOST_MODE					= 1000,
	VMNET_SHARED_MODE				= 1001,
	VMNET_BRIDGED_MODE API_AVAILABLE(macos(10.15))	= 1002
};

/*!
 * @typedef interface_event_t
 *
 * @abstract
 * The interface event bitmask.
 *
 * @discussion
 * The type of event provided to the interface event callback.
 *
 * @constant VMNET_INTERFACE_PACKETS_AVAILABLE
 * Packets are available to be read. The event dictionary passed in the
 * event may contain additional keys (vmnet_estimated_packets_available_key).
 */
typedef OBJC_OPTIONS(uint32_t, interface_event_t) {
	VMNET_INTERFACE_PACKETS_AVAILABLE	= 1<<0,
};


/*!
 * @typedef vmnet_return_t
 *
 * @abstract
 * The status code returning the result of vmnet operations.
 *
 * @constant VMNET_SUCCESS		Successfully completed.
 * @constant VMNET_FAILURE		General failure.
 * @constant VMNET_MEM_FAILURE 		Memory allocation failure.
 * @constant VMNET_INVALID_ARGUMENT	Invalid argument specified.
 * @constant VMNET_SETUP_INCOMPLETE	Interface setup is not complete.
 * @constant VMNET_INVALID_ACCESS	Permission denied.
 * @constant VMNET_PACKET_TOO_BIG	Packet size larger than MTU.
 * @constant VMNET_BUFFER_EXHAUSTED	Buffers exhausted in kernel.
 * @constant VMNET_TOO_MANY_PACKETS 	Packet count exceeds limit.
 * @constant VMNET_SHARING_SERVICE_BUSY	Vmnet Interface cannot be started as conflicting sharing service is in use.
*/
typedef OBJC_ENUM(uint32_t, vmnet_return_t) {
	VMNET_SUCCESS				= 1000,
	VMNET_FAILURE				= 1001,
	VMNET_MEM_FAILURE			= 1002,
	VMNET_INVALID_ARGUMENT			= 1003,
	VMNET_SETUP_INCOMPLETE			= 1004,
	VMNET_INVALID_ACCESS			= 1005,
	VMNET_PACKET_TOO_BIG			= 1006,
	VMNET_BUFFER_EXHAUSTED			= 1007,
	VMNET_TOO_MANY_PACKETS			= 1008,
	VMNET_SHARING_SERVICE_BUSY		= 1009,
};

/*!
 * @struct vmpktdesc
 *
 * @abstract
 * The type used to represent a network packet in the vmnet read/write
 * routines.
 *
 * @field vm_pkt_size
 * The size of the packet.
 *
 * @field vm_pkt_iov
 * The array of buffers that make up the packet.
 *
 * @field vm_pkt_iovcnt
 * The number of elements in vm_pkt_iov.
 *
 * @field vm_flags
 * The flags associated with the packet.
 */
struct vmpktdesc {
	size_t		vm_pkt_size;
	struct iovec 	*vm_pkt_iov;
	uint32_t	vm_pkt_iovcnt;
	uint32_t	vm_flags;
};

/*!
 * @typedef interface_ref
 *
 * @abstract
 * The vmnet interface object.
 */
typedef struct vmnet_interface *interface_ref;

/*!
 * @constant vmnet_operation_mode_key
 * The mode (uint64) in which the vmnet interface instance should run.
 * See operating_modes_t for the list of possible values.
 * The property is specified in the interface_desc dictionary.
 */
extern const char *
vmnet_operation_mode_key API_AVAILABLE(macos(10.10));

/*!
 * @constant vmnet_shared_interface_name_key
 * The name of the interface (string) to use when the operating mode of the
 * interface is VMNET_BRIDGED_MODE. The property is specified in the
 * interface_desc dictionary.
 */
extern const char *
vmnet_shared_interface_name_key API_AVAILABLE(macos(10.15));

/*!
 * @constant vmnet_mac_address_key
 * The MAC address (string) that the VM is expected to use when originating
 * traffic on the vmnet interface. Supplied in the interface_param dictionary.
 */
extern const char *
vmnet_mac_address_key API_AVAILABLE(macos(10.10));


/*!
 * @constant vmnet_allocate_mac_address_key
 * Allocate a MAC address for the VM to use (bool). Default value is true.
 * If set to false, no MAC address will be generated.
 */
extern const char *
vmnet_allocate_mac_address_key API_AVAILABLE(macos(10.15));

/*!
 * @constant vmnet_mtu_key
 * The maximum transmission unit (uint64) for the interface. Supplied in the
 * interface_param dictionary.
 *
 * In shared and host modes, the MTU can be specified in the interface_desc
 * dictionary. In bridged mode, specifying the MTU in the interface_desc
 * dictionary results in an error.
 */
extern const char *
vmnet_mtu_key API_AVAILABLE(macos(10.10));

/*!
 * @constant vmnet_max_packet_size_key
 * The maximum packet size (uint64) on the interface. Supplied in the
 * interface_param dictionary.
 */
extern const char *
vmnet_max_packet_size_key API_AVAILABLE(macos(10.10));

/*!
 * @constant vmnet_interface_id_key
 * The identifier (uuid) to uniquely identify the specific interface instance.
 * Supplied in the interface_desc and interface_param dictionaries.
 */
extern const char *
vmnet_interface_id_key API_AVAILABLE(macos(10.10));

/*!
 * @constant vmnet_start_address_key
 *
 * @abstract
 * The starting IPv4 address (string) to use for the interface.
 *
 * @discussion
 * This address is used as the gateway address. The subsequent
 * address up to and including vmnet_end_address_key are placed
 * in the DHCP pool. All other addresses are available for static
 * assignment.
 *
 * The address must be in the private IP range (RFC 1918).
 *
 * Must be specified along with vmnet_end_address_key and vmnet_subnet_mask_key.
 *
 * May be present in the interface_desc and interface_param dictionaries.
 */
extern const char *
vmnet_start_address_key API_AVAILABLE(macos(10.15));

/*!
 * @constant vmnet_end_address_key
 *
 * @abstract
 * The DHCP IPv4 range end address (string) to use for the interface.
 *
 * @discussion
 * The address must be in the private IP range (RFC 1918).
 *
 * Must be specified with vmnet_start_address_key and vmnet_subnet_mask_key.
 *
 * May be present in the interface_desc and interface_param dictionaries.
 */
extern const char *
vmnet_end_address_key API_AVAILABLE(macos(10.15));

/*!
 * @constant vmnet_subnet_mask_key
 *
 * @abstract
 * The IPv4 subnet mask (string) to use on the interface.
 *
 * @discussion
 * Must also specify vmnet_start_address_key and vmnet_end_address_key.
 *
 * Supplied in the interface_desc and interface_param dictionaries.
 */
extern const char *
vmnet_subnet_mask_key API_AVAILABLE(macos(10.15));

/*!
 * @constant vmnet_nat66_prefix_key
 * The IPv6 prefix (string) to use with VMNET_SHARED_MODE.
 * The prefix must be a ULA i.e. start with fd00::/8.
 */
extern const char *
vmnet_nat66_prefix_key API_AVAILABLE(macos(10.15));

/*!
 * @constant vmnet_nat66_prefix_length_key
 * The IPv6 prefix (uint64) to use with VMNET_SHARED_MODE.
 * The prefix_length must be 64, and hence use of this key is
 * deprecated.
 */
extern const char *
vmnet_nat66_prefix_length_key API_DEPRECATED("No longer supported",
					       macos(10.15, 11.0));

/*!
 * @constant vmnet_estimated_packets_available_key
 * The estimated number of packets available to read. Provided in the
 * event dictionary when the event_mask includes VMNET_PACKET_AVAILABLE.
 */
extern const char *
vmnet_estimated_packets_available_key API_AVAILABLE(macos(10.10));

/*!
 * @constant vmnet_network_identifier_key
 * The identifier (uuid) to uniquely identify the network.
 *
 * This property is only applicable to a vmnet_interface in
 * VMNET_HOST_MODE.
 *
 * If this property is set, the vmnet_interface is added to
 * an isolated network with the specified identifier.
 *
 * No DHCP service is provided on this network.
 */
extern const char *
vmnet_network_identifier_key API_AVAILABLE(macos(11.0));

/*!
 * @constant vmnet_host_ip_address_key
 * The IPv4 address (string) to be set on the host interface.
 *
 * This property is only applicable if vmnet_network_identifier_key
 * is also specified.
 */
extern const char *
vmnet_host_ip_address_key API_AVAILABLE(macos(11.0));

/*!
 * @constant vmnet_host_subnet_mask_key
 * The IPv4 subnet mask (string) to be set on the host interface.
 *
 * Must be specified with vmnet_host_ip_address_key.
 */
extern const char *
vmnet_host_subnet_mask_key API_AVAILABLE(macos(11.0));

/*!
 * @constant vmnet_host_ipv6_address_key
 * The IPv6 address (string) to be set on the host interface.
 *
 * This property is only applicable if vmnet_network_identifier_key
 * is also specified.
 */
extern const char *
vmnet_host_ipv6_address_key API_AVAILABLE(macos(11.0));

/*!
 * @constant vmnet_enable_tso_key
 * Enable TCP segmentation offload. Note, when this is enabled, the
 * interface may generate large (64K) TCP frames. It must also
 * be prepared to accept large TCP frames as well.
 */
extern const char *
vmnet_enable_tso_key API_AVAILABLE(macos(11.0));

/*!
 * @constant vmnet_enable_isolation_key
 * Enable isolation for this interface. Interface isolation ensures that
 * network communication between multiple vmnet_interface instances is
 * not possible.
 */
extern const char *
vmnet_enable_isolation_key API_AVAILABLE(macos(11.0));

/*!
 *  @typedef vmnet_start_interface_completion_handler_t
 *
 *  @abstract
 *  The type of the block provided in the call to vmnet_start_interface.
 *
 *  @param status
 *  If status is VMNET_SUCCESS, the interface was created successfully.
 *  Otherwise, the interface failed to be created.
 *
 *  @param interface_param
 *  A dictionary containing interface parameters that describe the
 *  interface.
 */
typedef void (^vmnet_start_interface_completion_handler_t)
    (vmnet_return_t status, xpc_object_t __nullable interface_param);


/*!
 * @function vmnet_start_interface
 *
 * @abstract
 * Starts a new virtual interface instance.
 *
 * @discussion
 * Attributes of the virtual interface are specified using the
 * interface_desc dictionary.
 *
 * @param interface_desc
 * A dictionary describing parameters to use when creating the interface.
 *
 * @param queue
 * The queue on which to schedule the completion handler.
 *
 * @param handler
 * The block to invoke when the start interface request completes.
 *
 * @result
 * Returns a non-NULL interface handle on success, NULL otherwise.
 */
interface_ref __nullable
vmnet_start_interface(xpc_object_t interface_desc, dispatch_queue_t queue,
    vmnet_start_interface_completion_handler_t handler)
    API_AVAILABLE(macos(10.10));

/*!
 * @typedef vmnet_interface_event_callback_t
 *
 * @abstract
 * The type of the block provided in the call to
 * vmnet_interface_set_event_callback().
 *
 * @param event_mask
 * The bitmask of events that have taken place.
 *
 * @param event
 * A dictionary containing additional information about the event.
 */
typedef void (^vmnet_interface_event_callback_t)(interface_event_t event_mask,
    xpc_object_t event);

/*!
 * @function vmnet_interface_set_event_callback
 *
 * @abstract
 * Enable or disable the event callback for an interface.
 *
 * @discussion
 * Enables events for an interface when callback and queue are both non-NULL.
 * Disables events when callback and queue are both NULL.
 *
 * @param interface
 * The vmnet interface on which to enable/disable events.
 *
 * @param event_mask
 * The bitmask of events to enable.
 *
 * @param queue
 * The queue to schedule the callback block on.
 *
 * @param callback
 * The callback block to invoke when an event is received.
 *
 * @result
 * Returns VMNET_SUCCESS on success or an error code on failure.
 */
vmnet_return_t
vmnet_interface_set_event_callback(interface_ref interface,
    interface_event_t event_mask, dispatch_queue_t __nullable queue,
    __nullable vmnet_interface_event_callback_t callback)
    API_AVAILABLE(macos(10.10));


/*!
 * @function vmnet_write
 *
 * @abstract
 * Called to write packets on the interface.
 *
 * @discussion
 * Attempts to write *pktcnt packets of data from the specified packets.
 * The size of each packet should not be larger than the value of
 * vmnet_max_packet_size_key. All data will be written or the write will fail.
 *
 * @param interface
 * The interface to write packets to.
 *
 * @param packets
 * The array of packets to write.
 *
 * @param pktcnt
 * On input, *pkcnt specifies the number of packets to write.
 * On output, *pktcnt holds the number of packets written.
 *
 * @result
 * Returns VMNET_SUCCESS on success or an error code on failure.
 */
vmnet_return_t
vmnet_write(interface_ref interface, struct vmpktdesc *packets, int *pktcnt)
    API_AVAILABLE(macos(10.10));



/*!
 * @function vmnet_read
 *
 * @abstract
 * Called to read packets from the interface.
 *
 * @discussion
 * Attempts to read *pktcnt packets of data from the interface into the
 * specified packets array. Each packet passed to vmnet_read() should be
 * at least as large as vmnet_max_packet_size_key to avoid incomplete read.
 *
 * @param interface
 * The interface to read packets from.
 *
 * @param packets
 * The array of packets to fill with read data.
 *
 * @param pktcnt
 * On input, *pktcnt is set to the size of the packets array.
 * On output, *pkcnt contains the actual number of packets read, which may
 * be zero if no packets are available.
 *
 * @result
 * Returns VMNET_SUCCESS if successful, an error code otherwise.
 */
vmnet_return_t
vmnet_read(interface_ref interface, struct vmpktdesc *packets, int *pktcnt)
    API_AVAILABLE(macos(10.10));


/*!
 * @typedef vmnet_interface_completion_handler_t
 *
 * @abstract
 * The vmnet interface completion block.
 *
 * @discussion
 * The type of the block used to provide feedback when the operation
 * has completed.
 *
 * @param status
 * status is VMNET_SUCCESS if successful, an error code otherwise.
 */
typedef void (^vmnet_interface_completion_handler_t)
    (vmnet_return_t status);

/*!
 * @function vmnet_stop_interface
 *
 * @abstract
 * Stops I/O on the virtual interface.
 *
 * @discussion
 * Once this function is called, subsequent calls to read/write packets
 * on this interface will fail.
 *
 * @param interface
 * The interface to halt I/O on.
 *
 * @param queue
 * The queue to schedule the stop handler on.
 *
 * @param handler
 * The block that is invoked when the stop interface request completes.
 *
 * @result
 * Returns VMNET_SUCCESS if completion handler was scheduled, an error
 * code otherwise.
 */
vmnet_return_t
vmnet_stop_interface(interface_ref interface, dispatch_queue_t queue,
    vmnet_interface_completion_handler_t handler)
    API_AVAILABLE(macos(10.10));


/*!
 * @function vmnet_interface_add_port_forwarding_rule
 *
 * @abstract
 * Add a port forwarding rule for the vmnet interface.
 *
 * @discussion
 * Adds a rule to forward traffic destined to an external port to
 * an internal IP address and port for either TCP or UDP.
 *
 * @param interface
 * The vmnet interface instance to use.
 *
 * @param protocol
 * The protocol to apply the port forwarding rule to.
 * Must be either IPPROTO_TCP or IPPROTO_UDP (see <netinet/in.h>).
 *
 * @param external_port
 * The TCP or UDP port on the outside network that should be redirected from.
 * Must be in host byte order.
 *
 * @param internal_address
 * The IP address of the machine on the internal network that should receive the
 * forwarded traffic.
 *
 * @param internal_port
 * The TCP or UDP port that the forwarded traffic should be redirected to.
 * Must be in host byte order.
 *
 * @param handler
 * The completion handler to invoke when the operation completes.
 *
 * @result
 * Returns VMNET_SUCCESS if the completion handler handler was scheduled,
 * an error code otherwise.
 */
vmnet_return_t
vmnet_interface_add_port_forwarding_rule(interface_ref interface,
    uint8_t protocol,
    uint16_t external_port,
    struct in_addr internal_address,
    uint16_t internal_port,
    __nullable vmnet_interface_completion_handler_t handler)
    API_AVAILABLE(macos(10.15));

/*!
 * @function vmnet_interface_remove_port_forwarding_rule
 *
 * @abstract
 * Removes a port forwarding rule for the vmnet interface.
 *
 * @discussion
 * Removes the rule to forward an external port to the specified
 * internal IP address and port.
 *
 * @param interface
 * The vmnet interface instance to use.
 *
 * @param protocol
 * The protocol to apply the port forwarding rule to.
 * Must be either IPPROTO_TCP or IPPROTO_UDP (see <netinet/in.h>).
 *
 * @param external_port
 * The TCP or UDP port on the outside network that should be redirected from.
 * Must be in host byte order.
 *
 * @param handler
 * The completion handler to invoke when the operation completes.
 *
 * @result
 * Returns VMNET_SUCCESS if the completion handler handler was scheduled,
 * an error code otherwise.
 */
vmnet_return_t
vmnet_interface_remove_port_forwarding_rule(interface_ref interface,
    uint8_t protocol,
    uint16_t external_port,
    __nullable vmnet_interface_completion_handler_t handler)
    API_AVAILABLE(macos(10.15));

/*!
 * @typedef vmnet_interface_get_port_forwarding_rules_handler_t
 *
 * @abstract
 * The type of the block provided to
 * vmnet_interface_get_port_forwarding_rules().
 *
 * @param rules
 * If non-NULL, the xpc_array of xpc_dictionary rules.
 * If NULL, no port forwarding rules exist.
 *
 */
typedef void (^vmnet_interface_get_port_forwarding_rules_handler_t)
    (__nullable xpc_object_t rules);

/*!
 * @function vmnet_port_forwarding_rule_get_details
 *
 * @abstract
 * Extracts port forwarding rule details from the rule xpc dictionary object.
 *
 * @discussion
 * Allows the protocol, external port, internal address and internal port to
 * be extracted from the xpc dictionary object.
 *
 * @param rule
 * The xpc dictionary element from the xpc array provided to the
 * vmnet_interface_get_port_forward_rules_handler_t callback.
 *
 * @param protocol
 * Either IPPROTO_TCP or IPPROTO_UDP (see <netinet/in.h>).
 *
 * @param external_port
 * The TCP or UDP port on the outside network that should be redirected from.
 * Must be in host byte order.
 *
 * @result
 * Returns VMNET_SUCCESS if rule is valid and all details were populated,
 * an error code otherwise.
 */
vmnet_return_t
vmnet_port_forwarding_rule_get_details(xpc_object_t rule,
				       uint8_t * protocol,
				       uint16_t * external_port,
				       struct in_addr * internal_address,
				       uint16_t * internal_port)
    API_AVAILABLE(macos(10.15));

/*!
 * @function vmnet_interface_get_port_forwarding_rules
 *
 * @abstract
 * Get the list of port forwarding rules that have been configured.
 *
 * @discussion
 * Gets the list of port forwarding rules that have been configured
 * via previous calls to vmnet_interface_add_port_forwarding_rule().
 *
 * @param interface
 * The vmnet interface instance to use.
 *
 * @param handler
 * The completion handler to invoke when the operation completes.
 *
 * @result
 * Returns VMNET_SUCCESS if the completion handler handler was scheduled,
 * an error code otherwise.
 */
vmnet_return_t
vmnet_interface_get_port_forwarding_rules(interface_ref interface,
    vmnet_interface_get_port_forwarding_rules_handler_t handler)
    API_AVAILABLE(macos(10.15));

/*!
 * @function vmnet_copy_shared_interface_list
 *
 * @abstract
 * Returns a list of interface names available for use with VMNET_BRIDGED_MODE.
 *
 * @discussion
 * Not every network interface on the system can be used with bridged mode.
 * This API returns the list of interfaces that can be used.
 *
 * @result
 * Returns a non-NULL array of strings if successful, NULL otherwise.
 */
xpc_object_t __nullable
vmnet_copy_shared_interface_list(void)
    API_AVAILABLE(macos(10.15));


#if __has_feature(assume_nonnull)
_Pragma("clang assume_nonnull end")
#endif

__END_DECLS

#endif /* _VMNET_H_ */
