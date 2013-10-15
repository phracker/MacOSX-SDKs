/*
 * Copyright (c) 2000-2003 Apple Computer, Inc. All rights reserved.
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

#ifndef _SCNETWORK_H
#define _SCNETWORK_H

#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <CoreFoundation/CoreFoundation.h>


/*!
	@header SCNetwork

	SCNetworkCheckReachabilityXXX()

	The SCNetworkCheckReachabilityXXX() APIs allow an application to
	determine the status of the system's current network configuration
	and the accessibility of a target host/address.

	The term "reachable" reflects whether a data packet, sent by
	an application into the network stack, can be sent to the
	the target host/address.  Please note that their is no
	guarantee that the data packet will actually be received by
	the host.


	SCNetworkInterfaceRefreshConfiguration()

	This API sends a notification to interested network configuration
	agents to retry	their configuraton immediately. For example, calling
	this API will cause the DHCP client to contact the DHCP server
	immediately rather than waiting until its timeout has expired.
	The utility of this API is to allow the caller to give a hint to
	the system that the network infrastructure/configuration has changed.
 */

/*!
	@enum SCNetworkConnectionFlags
	@discussion Flags that indicate whether the specified network
		nodename/address is reachable, requires a connection,
		requires some user intervention in establishing the
		connection, and whether the calling application must
		initiate the connection using the (TBD???) API.

	@constant kSCNetworkFlagsTransientConnection
		This flag indicates that the specified nodename/address can
		be reached via a transient (e.g. PPP) connection.

	@constant kSCNetworkFlagsReachable
		This flag indicates that the specified nodename/address can
		be reached using the current network configuration.

	@constant kSCNetworkFlagsConnectionRequired
		This flag indicates that the specified nodename/address can
		be reached using the current network configuration but a
		connection must first be established.

		As an example, this status would be returned for a dialup
		connection that was not currently active but could handle
		network traffic for the target system.

	@constant kSCNetworkFlagsConnectionAutomatic
		This flag indicates that the specified nodename/address can
		be reached using the current network configuration but a
		connection must first be established.  Any traffic directed
		to the specified name/address will initiate the connection.

	@constant kSCNetworkFlagsInterventionRequired
		This flag indicates that the specified nodename/address can
		be reached using the current network configuration but a
		connection must first be established.  In addition, some
		form of user intervention will be required to establish
		this connection (e.g. providing a password, authentication
		token, etc.).

	@constant kSCNetworkFlagsIsLocalAddress
		This flag indicates that the specified nodename/address
		is one associated with a network interface on the current
		system.

	@constant kSCNetworkFlagsIsDirect
		This flag indicates that network traffic to the specified
		nodename/address will not go through a gateway but is routed
		directly to one of the interfaces in the system.
 */
enum {
	kSCNetworkFlagsTransientConnection	= 1<<0,
	kSCNetworkFlagsReachable		= 1<<1,
	kSCNetworkFlagsConnectionRequired	= 1<<2,
	kSCNetworkFlagsConnectionAutomatic	= 1<<3,
	kSCNetworkFlagsInterventionRequired	= 1<<4,
	kSCNetworkFlagsIsLocalAddress		= 1<<16,
	kSCNetworkFlagsIsDirect			= 1<<17
};
typedef	uint32_t	SCNetworkConnectionFlags;

__BEGIN_DECLS

/*!
	@function SCNetworkCheckReachabilityByAddress
	@discussion Determines if the given network address is
		reachable using the current network configuration.
	@param address The network address of the desired host.
	@param addrlen The length, in bytes, of the address.
	@param flags A pointer to memory that will be filled with a
		set of SCNetworkConnectionFlags detailing the reachability
		of the specified address.
	@result TRUE if the network connection flags are valid; FALSE if the
		status could not be determined.
 */
Boolean
SCNetworkCheckReachabilityByAddress	(
					const struct sockaddr		*address,
					int				addrlen,
					SCNetworkConnectionFlags	*flags
					);

/*!
	@function SCNetworkCheckReachabilityByName
	@discussion Determines if the given network host/node name is
		reachable using the current network configuration.
	@param nodename The node name of the desired host. This name would
		be the same as that passed to gethostbyname() or getaddrinfo().
	@param flags A pointer to memory that will be filled with a
		set of SCNetworkConnectionFlags detailing the reachability
		of the specified node name.
	@result TRUE if the network connection flags are valid; FALSE if the
		status could not be determined.
 */
Boolean
SCNetworkCheckReachabilityByName	(
					const char			*nodename,
					SCNetworkConnectionFlags	*flags
					);
/*!
	@function SCNetworkInterfaceRefreshConfiguration
	@discussion Sends a notification to interested configuration agents
		to have them immediately retry their configuration over a
		particular network interface.
		Note: This API must be invoked by root (uid == 0).

	@param ifName The BSD name of the network interface e.g. CFSTR("en0").
	@result TRUE if the notification was sent; FALSE otherwise.
 */
Boolean
SCNetworkInterfaceRefreshConfiguration	(
					CFStringRef ifName
					);
__END_DECLS

#endif /* _SCNETWORK_H */
