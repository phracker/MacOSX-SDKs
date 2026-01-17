/*
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
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

#ifndef _SCNETWORK_H
#define _SCNETWORK_H

#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <CoreFoundation/CoreFoundation.h>


/*!
	@header SCNetwork
	The SCNetworkCheckReachabilityXXX() APIs allow an application to
	determine the status of the system's current network configuration.

	The term "reachable" reflects whether a data packet, sent by
	an application into the network stack, will be able to reach
	the destination host.

	Please note that being able to reach the destination host
	does not guarantee that the data packet will reach the
	host.

	The APIs provided by this framework communicate with the "configd"
	daemon to obtain information regarding the system's current
	configuration.
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
 */
typedef enum {
	kSCNetworkFlagsTransientConnection	=  1<<0,
	kSCNetworkFlagsReachable		=  1<<1,
	kSCNetworkFlagsConnectionRequired	=  1<<2,
	kSCNetworkFlagsConnectionAutomatic	=  1<<3,
	kSCNetworkFlagsInterventionRequired	=  1<<4,
} SCNetworkConnectionFlags;


__BEGIN_DECLS

/*!
	@function SCNetworkCheckReachabilityByAddress
	@discussion Determines if the given network address is
		reachable using the current network configuration.

		Note: This API is not thread safe.
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
					const int			addrlen,
					SCNetworkConnectionFlags	*flags
					);

/*!
	@function SCNetworkCheckReachabilityByName
	@discussion Determines if the given network host/node name is
		reachable using the current network configuration.

		Note: This API is not thread safe.

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

__END_DECLS

#endif /* _SCNETWORK_H */
