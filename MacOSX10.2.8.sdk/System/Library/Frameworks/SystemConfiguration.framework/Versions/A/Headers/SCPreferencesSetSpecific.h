/*
 * Copyright (c) 2000-2002 Apple Computer, Inc. All rights reserved.
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

#ifndef _SCPREFERENCESSETSPECIFIC_H
#define _SCPREFERENCESSETSPECIFIC_H

#include <sys/cdefs.h>
#include <CoreFoundation/CoreFoundation.h>
#include <SystemConfiguration/SCPreferences.h>


/*!
	@header SCPreferencesSetSpecific
	The following APIs allow an application to set specific
	configuration information about the current system (e.g. the
	computer/sharing name).
 */


__BEGIN_DECLS

/*!
	@function SCPreferencesSetComputerName
	@discussion Updates the computer/host name in the system preferences.

	Note: In order to commit these changes to permanent storage a call
	must be made to SCPreferencesCommitChanges().
	A call to SCPreferencesApplyChanges() is also required for the new
	name to become active.
	@param prefs An SCPreferencesRef that should be used for all API calls.
	@param name The computer/host name to be set.
	@param nameEncoding The encoding associated with the computer/host name.
	@result A boolean indicating the success (or failure) of the call.
 */
Boolean
SCPreferencesSetComputerName		(
					SCPreferencesRef	prefs,
					CFStringRef		name,
					CFStringEncoding	nameEncoding
					);

/*!
	@function SCPreferencesSetLocalHostName
	@discussion Updates the local host name in the system preferences.

	Note: In order to commit these changes to permanent storage a call
	must be made to SCPreferencesCommitChanges().
	A call to SCPreferencesApplyChanges() is also required for the new
	name to become active.
	@param prefs An SCPreferencesRef that should be used for all API calls.
	@param name The local host name to be set.

	Note: the string must conform to the naming conventions of a DNS host
		name as specified in RFC 1034 (section 3.5).
	@result A boolean indicating the success (or failure) of the call.
 */
Boolean
SCPreferencesSetLocalHostName		(
					SCPreferencesRef	prefs,
					CFStringRef		name
					);

__END_DECLS

#endif /* _SCPREFERENCESSETSPECIFIC_H */
