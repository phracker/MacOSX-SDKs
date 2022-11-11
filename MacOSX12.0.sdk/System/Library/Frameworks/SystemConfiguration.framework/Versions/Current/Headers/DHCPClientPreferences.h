/*
 * Copyright (c) 2001, 2004, 2005, 2008, 2015, 2017, 2018 Apple Inc. All rights reserved.
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

#ifndef _DHCPCLIENTPREFERENCES_H
#define _DHCPCLIENTPREFERENCES_H

#include <os/availability.h>
#include <sys/cdefs.h>
#include <CoreFoundation/CFString.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_ASSUME_NONNULL_BEGIN

/*!
	@header DHCPClientPreferences
	@discussion The DHCPClientPreferences API allows applications to get and update DHCP preferences.
		DHCP preferences are in the form of DHCP option codes, which are defined in RFC 2132.
 */

__BEGIN_DECLS

/*!
	@function DHCPClientPreferencesSetApplicationOptions
	@discussion Updates the DHCP client preferences to include the
		given list of options for the given application ID.
	@param applicationID The application's preference ID, for example:
		"com.apple.SystemPreferences".
	@param options An array of 8-bit values containing the
		DHCP option codes (see RFC 2132) for this application ID.
		A NULL value will clear the list of options for this
		application ID.
	@param count The number of elements in the options parameter.
	@result Returns TRUE if the operation succeeded, FALSE otherwise.
 */

Boolean
DHCPClientPreferencesSetApplicationOptions	(CFStringRef			applicationID,
						 const UInt8	* __nullable	options,
						 CFIndex			count)		API_AVAILABLE(macos(10.1)) API_UNAVAILABLE(ios, tvos, watchos);

/*!
	@function DHCPClientPreferencesCopyApplicationOptions
	@discussion Copies the requested DHCP options for the
		given application ID.
	@param applicationID The application's preference ID, for example
		"com.apple.SystemPreferences".
	@param count The number of elements in the returned array.
	@result Returns the list of options for the given application ID, or
		NULL if no options are defined or an error occurred.

		When you are finished, use free() to release a non-NULL return value.
 */

UInt8 * __nullable
DHCPClientPreferencesCopyApplicationOptions	(CFStringRef	applicationID,
						 CFIndex	*count)		API_AVAILABLE(macos(10.1)) API_UNAVAILABLE(ios, tvos, watchos);

__END_DECLS

CF_ASSUME_NONNULL_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif	/* _DHCPCLIENTPREFERENCES_H */
