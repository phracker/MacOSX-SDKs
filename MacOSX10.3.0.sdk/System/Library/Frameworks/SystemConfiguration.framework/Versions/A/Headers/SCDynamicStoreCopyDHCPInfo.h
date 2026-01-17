/*
 * Copyright (c) 2001-2002 Apple Computer, Inc. All rights reserved.
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

#ifndef _SCDYNAMICSTORECOPYDHCPINFO_H
#define _SCDYNAMICSTORECOPYDHCPINFO_H

#include <sys/cdefs.h>
#include <CoreFoundation/CoreFoundation.h>
#include <SystemConfiguration/SCDynamicStore.h>


/*!
	@header SCDynamicStoreCopyDHCPInfo.h
	The following APIs allow an application to retrieve DHCP/BOOTP
	information, in particular DHCP/BOOTP options.
 */


__BEGIN_DECLS

/*!
	@function SCDynamicStoreCopyDHCPInfo
	@discussion Copies the DHCP/BOOTP information dictionary for the
		requested serviceID, or the primary service if
		serviceID == NULL.
	@param store An SCDynamicStoreRef that should be used for communication
		with the server.
		If NULL, a temporary session will be used.
	@param serviceID A CFStringRef containing the requested service.
		If NULL, returns information for the primary service.
	@result A dictionary containing DHCP/BOOTP information if successful,
		NULL otherwise.
		Use the DHCPInfoGetOption() to retrieve
		individual options from the returned dictionary.

		A non-NULL return value must be released using CFRelease().
 */
CFDictionaryRef
SCDynamicStoreCopyDHCPInfo(SCDynamicStoreRef store, CFStringRef serviceID);

/*!
	@function DHCPInfoGetOptionData
	@discussion Returns a non-NULL CFDataRef containing the BOOTP/DHCP
		option data if present, NULL otherwise.
	@param info The non-NULL DHCP information dictionary returned by
		calling SCDynamicStoreCopyDHCPInfo.
	@param code The DHCP/BOOTP option code (see RFC 2132) to return
		data for.
	@result A non-NULL CFDataRef containing the option data,
		NULL otherwise.

		The return value must NOT be released.
 */
CFDataRef
DHCPInfoGetOptionData(CFDictionaryRef info, UInt8 code);

/*!
	@function DHCPInfoGetLeaseStartTime
	@discussion Returns a CFDateRef corresponding to the lease start time,
		if present, NULL otherwise.  A NULL return value is returned
		if the configuration method is BOOTP.
	@param info The non-NULL DHCP information dictionary returned by
		calling SCDynamicStoreCopyDHCPInfo.
	@result A non-NULL CFDateRef if present, NULL otherwise.

		The return value must NOT be released.
 */
CFDateRef
DHCPInfoGetLeaseStartTime(CFDictionaryRef info);

__END_DECLS

#endif /* _SCDYNAMICSTORECOPYDHCPINFO_H */
