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

#ifndef _SYSTEMCONFIGURATION_H
#define _SYSTEMCONFIGURATION_H

#include <sys/cdefs.h>
#include <CoreFoundation/CoreFoundation.h>


/*!
	@header SystemConfiguration.h
	The SystemConfiguration framework provides access to the
	data used to configure a running system.  The APIs provided
	by this framework communicate with the "configd" daemon.

	The "configd" daemon manages a "dynamic store" reflecting the
	desired configuration settings as well as the current state
	of the system.  The daemon provides a notification mechanism
	for user-level processes which need to be aware of changes
	made to the data.  Lastly, the daemon loads a number of
	bundles (or plug-ins) that monitor low-level kernel events
	and, via a set of policy modules, keep the state data up
	to date.
 */

/*!
	@enum
	@discussion Returned status codes.

	@constant kSCStatusOK			Success
	@constant kSCStatusFailed		Non-specific Failure
	@constant kSCStatusInvalidArgument	Invalid argument
	@constant kSCStatusAccessError		Permission denied
	@constant kSCStatusNoKey		No such key
	@constant kSCStatusKeyExists		Data associated with key already defined
	@constant kSCStatusLocked		Lock already held
	@constant kSCStatusNeedLock		Lock required for this operation

	@constant kSCStatusNoStoreSession	Configuration daemon session not active
	@constant kSCStatusNoStoreServer	Configuration daemon not (no longer) available
	@constant kSCStatusNotifierActive	Notifier is currently active

	@constant kSCStatusNoPrefsSession	Preference session not active
	@constant kSCStatusPrefsBusy		Preferences update currently in progress
	@constant kSCStatusNoConfigFile		Configuration file not found
	@constant kSCStatusNoLink		No such link
	@constant kSCStatusStale		Write attempted on stale version of object

	@constant kSCStatusReachabilityUnknown
		A determination could not be made regarding the reachability
		of the specified nodename/address.
*/
enum {
	/*
	 * Generic status codes
	 */
	kSCStatusOK				= 0,	/* Success */
	kSCStatusFailed				= 1001,	/* Non-specific failure */
	kSCStatusInvalidArgument		= 1002,	/* Invalid argument */
	kSCStatusAccessError			= 1003,	/* Permission denied
							   - must be root to obtain lock
							   - could not create access/create preferences
							 */
	kSCStatusNoKey				= 1004,	/* No such key */
	kSCStatusKeyExists			= 1005,	/* Key already defined */
	kSCStatusLocked				= 1006,	/* Lock already held */
	kSCStatusNeedLock			= 1007,	/* Lock required for this operation */
	/*
	 * SCDynamicStore status codes
	 */
	kSCStatusNoStoreSession			= 2001,	/* Configuration daemon session not active */
	kSCStatusNoStoreServer			= 2002,	/* Configuration daemon not (no longer) available */
	kSCStatusNotifierActive			= 2003,	/* Notifier is currently active */
	/*
	 * SCPreferences status codes
	 */
	kSCStatusNoPrefsSession			= 3001,	/* Preference session not active */
	kSCStatusPrefsBusy			= 3002,	/* Preferences update currently in progress */
	kSCStatusNoConfigFile			= 3003,	/* Configuration file not found */
	kSCStatusNoLink				= 3004,	/* No such link */
	kSCStatusStale				= 3005,	/* Write attempted on stale version of object */
	/*
	 * SCNetwork status codes
	 */
	kSCStatusReachabilityUnknown		= 4001,	/* Network reachability cannot be determined */
};


/* store access APIs */
#include <SystemConfiguration/SCDynamicStore.h>
#include <SystemConfiguration/SCDynamicStoreKey.h>
#include <SystemConfiguration/SCDynamicStoreCopySpecific.h>

/* preference access APIs */
#include <SystemConfiguration/SCPreferences.h>
#include <SystemConfiguration/SCPreferencesPath.h>

/* store and preference scheme definitions */
#include <SystemConfiguration/SCSchemaDefinitions.h>

/* "network reachability" APIs */
#include <SystemConfiguration/SCNetwork.h>

__BEGIN_DECLS

/*!
	@function SCError
	@discussion Returns a last SystemConfiguration.framework API error code.
	@result The last error encountered.
 */
int	SCError				();

/*!
	@function SCErrorString
	@discussion Returns a pointer to the error message string associated
		with the specified status.
	@param status The SCDynamicStoreStatus to be returned.
	@result The error message string.
 */
const char *	SCErrorString		(int	status);

__END_DECLS

#endif /* _SYSTEMCONFIGURATION_H */
