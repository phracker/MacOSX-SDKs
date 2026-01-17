/*
 * Copyright (c) 2013-2015 Apple Inc. All rights reserved.
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

#ifdef  __cplusplus
extern "C" {
#endif

#include <dispatch/dispatch.h>
#include <xpc/xpc.h>
#include <objc/objc-api.h>

#ifndef EXPORT
#define EXPORT __attribute__((visibility("default")))
#endif

#if __has_feature(nullability)
#pragma clang assume_nonnull begin
#endif

/*
 * @enum operating_modes_t
 * 	List of operating modes for an interface.
 * @const VMNET_HOST_MODE
 *	This mode lets the guest network interface communicate with other guest network
 *	interfaces in the host mode and to the native host.
 * @const VMNET_SHARED_MODE
 *	This mode lets the guest network interface reach the Internet using a network
 *	address translator. In addition, the shared mode interface, can communicate with
 * 	shared mode interfaces in other guest operating system and also to the native host.
 */
typedef OBJC_ENUM(uint32_t, operating_modes_t) {
	VMNET_HOST_MODE				= 1000,
	VMNET_SHARED_MODE			= 1001,
};

/*
 * @enum interface_event_t
 *	List of interface event types.
 * @const VMNET_PACKET_AVAILABLE
 *	Packets are available to be read. The event dictionary passed in the callback is NULL.
 */
typedef OBJC_OPTIONS(uint32_t, interface_event_t) {
	VMNET_INTERFACE_PACKETS_AVAILABLE	= 1<<0,
};

typedef OBJC_ENUM(uint32_t, vmnet_return_t) {
	/* Error */
	VMNET_SUCCESS				= 1000,	/* success */
	VMNET_FAILURE				= 1001,	/* generic failure */
	VMNET_MEM_FAILURE			= 1002,	/* out of memory */
	VMNET_INVALID_ARGUMENT			= 1003,	/* invalid argument */
	VMNET_SETUP_INCOMPLETE			= 1004, /* interface setup is not complete */
	VMNET_INVALID_ACCESS			= 1005,	/* permission denied */
	VMNET_PACKET_TOO_BIG			= 1006,	/* packet size larger than MTU */
	VMNET_BUFFER_EXHAUSTED			= 1007,	/* buffers exhausted temporarily in kernel */
	VMNET_TOO_MANY_PACKETS			= 1008, /* packets larger than limit */
};

struct vmpktdesc {
	size_t		vm_pkt_size;      	/* the size of the packet */
	struct iovec 	*vm_pkt_iov;		/* array of buffers */
	uint32_t	vm_pkt_iovcnt;		/* number of buffers in the array */
	uint32_t	vm_flags;		/* flags */
};

typedef struct vmnet_interface *interface_ref;

/* XPC Dictionary keys */
extern const char *vmnet_operation_mode_key EXPORT;			/* key for interface_desc dictionary */
extern const char *vmnet_interface_id_key EXPORT;			/* key for interface_desc and interface_param dictionary */
extern const char *vmnet_mac_address_key EXPORT;			/* key for interface_param dictionary */
extern const char *vmnet_mtu_key EXPORT;				/* key for interface_param dictionary */
extern const char *vmnet_max_packet_size_key EXPORT;			/* key for interface_param dictionary */
extern const char *vmnet_estimated_packets_available_key EXPORT;	/* key for read callback dictionary */

/*
 * Start host or shared mode on an interface. The interface parameters passed by the client
 * in interface_desc will be used to configure the interface.
 *
 * @param interface_desc
 *	A xpc dictionary describing parameters of the interface.
 * @param queue
 *	Queue on which the handler is scheduled.
 * @param handler
 *	Block which is scheduled when the request completes. status returns VMNET_SUCCESS
 * 	on success or an error code on failure. interface_param returns additional information
 * 	about the interface.
 * @result
 *	Returns an interface handle. In case of error, NULL is returned.
 */
EXPORT interface_ref __nullable
vmnet_start_interface(xpc_object_t interface_desc, dispatch_queue_t queue,
    void (^handler) (vmnet_return_t status, xpc_object_t __nullable interface_param));

/*
 * Sets a dispatch block on an interface, that is scheduled when events specific to the
 * interface are received. Once the block is set, the callback can be stopped by passing
 * a NULL queue and a NULL handler. To restart the callback, the dispatch block and queue
 * needs to be set again
 *
 * @param interface
 *	The interface reference.
 * @param flags
 *	Flags indicating the events that the handler block will be called upon.
 * @param queue
 *	Queue on which the handler is scheduled.
 * @param handler
 *	Block which will be scheduled when an event is received. The event_id describe
 *	the type of event. The event dictionary holds additional information about the event.
 * @result
 *	Returns VMNET_SUCCESS on success or an error code on failure.
 */
EXPORT vmnet_return_t
vmnet_interface_set_event_callback(interface_ref interface, interface_event_t flags,
    dispatch_queue_t __nullable queue, void (^ __nullable handler)(interface_event_t event_id, xpc_object_t event));

/*
 * Attempts to write pktcnt packets of data to an interface referenced by interface from
 * the buffers pointed to by packets. Each packet passed to write should not be greater than
 * the value of vmnet_max_packet_size_key for the interface. All data will be written or the write
 * will fail.
 *
 * @param interface
 *	The interface reference.
 * @param packets
 *	Array of packets to be sent.
 * @param pktcnt
 *	Number of packets to write. On output the pktcnt holds the number of packets written.
 * @result
 *	Returns VMNET_SUCCESS on success or an error code on failure.
 */
EXPORT vmnet_return_t
vmnet_write(interface_ref interface, struct vmpktdesc *packets, int *pktcnt);

/*
 * Attempts to read pktcnt packets of data from the interface referenced by interface into the
 * buffers pointed to by packets. Each packet buffer passed to vmnet_read() should be at least
 * as large as the value of vmnet_max_packet_size_key for the interface to avoid incomplete read
 * of a packet.
 *
 * @param interface
 *	The interface reference.
 * @param packets
 *	Buffers to read an array of packets.
 * @param pktcnt
 *	Initialized to number of packets passed to the vmnet_read(). On return, pkcnt
 *	returns the number of packets read. If no packets are available to be read, pkcnt is
 * 	set to zero.
 * @result
 *	Returns VMNET_SUCCESS on success or a error code on failure.
 */
EXPORT vmnet_return_t
vmnet_read(interface_ref interface, struct vmpktdesc *packets, int *pktcnt);

/*
 * Stops the interface. Any further calls to read/write packets on this interface will fail.
 * @param interface
 * 	The interface reference.
 * @param queue
 *	Queue on which the handler is scheduled.
 * @param handler
 *	Block which is scheduled when the request completes. status returns VMNET_SUCCESS
 * 	on success or an error code on failure.
 * @result
 *	Returns 0 on success or an error code on failure.
 */
EXPORT vmnet_return_t
vmnet_stop_interface(interface_ref interface, dispatch_queue_t queue,
    void (^handler)(vmnet_return_t status));

#if __has_feature(nullability)
#pragma clang assume_nonnull end
#endif

#ifdef  __cplusplus
}
#endif
#endif /* _VMNET_H_ */
