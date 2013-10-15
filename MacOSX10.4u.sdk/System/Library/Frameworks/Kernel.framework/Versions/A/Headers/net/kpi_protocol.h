/*
 * Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*!
	@header kpi_protocol.h
	This header defines an API to interact with protocols in the kernel.
	The KPIs in this header file can be used to interact with protocols
	that already exist in the stack. These KPIs can be used to support
	existing protocols over media types that are not natively supported
	in the kernel, such as ATM.
 */

#ifndef __KPI_PROTOCOL__
#define __KPI_PROTOCOL__
#include <sys/kernel_types.h>
#include <net/kpi_interface.h>


__BEGIN_DECLS

/****************************************************************************/
/* Protocol input/inject													*/
/****************************************************************************/


/*!
	@function proto_input
	@discussion Inputs a packet on the specified protocol from the input
		path.
	@param protocol The protocol of the packet.
	@param packet The first packet in a chain of packets to be input.
	@result A errno error on failure. Unless proto_input returns zero,
		the caller is responsible for freeing the mbuf.
 */
errno_t	proto_input(protocol_family_t protocol, mbuf_t packet);

/*!
	@function proto_inject
	@discussion Injects a packet on the specified protocol from
		anywhere. To avoid recursion, the protocol may need to queue the
		packet to be handled later.
	@param protocol The protocol of the packet.
	@param packet The first packet in a chain of packets to be injected.
	@result A errno error on failure. Unless proto_inject returns zero,
		the caller is responsible for freeing the mbuf.
 */
errno_t	proto_inject(protocol_family_t protocol, mbuf_t packet);


/****************************************************************************/
/* Protocol plumbing														*/
/****************************************************************************/

/*!
	@typedef proto_plumb_handler
	@discussion proto_plumb_handler is called to attach a protocol to an
		interface. A typical protocol plumb function would fill out an
		ifnet_attach_proto_param and call ifnet_attach_protocol.
	@param ifp The interface the protocol should be attached to.
	@param protocol_family The protocol that should be attached to the
		interface.
	@result
		A non-zero value of the attach failed.
 */
typedef errno_t (*proto_plumb_handler)(ifnet_t ifp, protocol_family_t protocol);

/*!
	@typedef proto_unplumb_handler
	@discussion proto_unplumb_handler is called to detach a protocol
		from an interface. A typical unplumb function would call
		ifnet_detach_protocol and perform any necessary cleanup.
	@param ifp The interface the protocol should be detached from.
	@param protocol_family The protocol that should be detached from the
		interface.
 */
typedef void (*proto_unplumb_handler)(ifnet_t ifp, protocol_family_t protocol);

/*!
	@function proto_register_plumber
	@discussion Allows the caller to specify the functions called when a protocol
		is attached to an interface belonging to the specified family and when
		that protocol is detached.
	@param proto_fam The protocol family these plumbing functions will
		handle.
	@param if_fam The interface family these plumbing functions will
		handle.
	@param plumb The function to call to attach the protocol to an
		interface.
	@param unplumb The function to call to detach the protocol to an
		interface, may be NULL in which case ifnet_detach_protocol will
		be used to detach the protocol.
	@result A non-zero value of the attach failed.
 */
errno_t	proto_register_plumber(protocol_family_t proto_fam, ifnet_family_t if_fam,
							   proto_plumb_handler plumb, proto_unplumb_handler unplumb);

/*!
	@function proto_unregister_plumber
	@discussion Unregisters a previously registered plumbing function.
	@param proto_fam The protocol family these plumbing functions
		handle.
	@param if_fam The interface family these plumbing functions handle.
 */
void	proto_unregister_plumber(protocol_family_t proto_fam, ifnet_family_t if_fam);

__END_DECLS

#endif
