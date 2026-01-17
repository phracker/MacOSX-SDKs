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

#ifndef _SCPREFERENCES_H
#define _SCPREFERENCES_H


#include <sys/cdefs.h>
#include <CoreFoundation/CoreFoundation.h>
#include <SystemConfiguration/SCDynamicStore.h>


/*!
	@header SCPreferences
	The SCPreferencesXXX() APIs allow an application to load and
	store XML configuration data in a controlled manner and provide
	the necessary notifications to other applications that need to
	be aware of configuration changes.

	The stored XML configuration data is accessed using a prefsID. A
	NULL value indicates that the default system preferences are to
	be accessed.
	A string which starts with a leading "/" character specifies the
	path to the file containing te preferences to be accessed.
	A string which does not start with a leading "/" character
	specifies a file relative to the default system preferences
	directory.

	The APIs provided by this framework communicate with the "configd"
	daemon for any tasks requiring synchronization and/or notification.
 */


/*!
	@typedef SCPreferencesRef
	@discussion This is the handle to an open "session" for
		accessing system configuration preferences.
 */
typedef const struct __SCPreferences *	SCPreferencesRef;


__BEGIN_DECLS

/*!
	@function SCPreferencesGetTypeID
	Returns the type identifier of all SCPreferences instances.
 */
CFTypeID
SCPreferencesGetTypeID		(void);


/*!
	@function SCPreferencesCreate
	@discussion Initiates access to the per-system set of configuration
		preferences.
	@param allocator ...
	@param name A string that describes the name of the calling
		process.
	@param prefsID A string that identifies the name of the
		group of preferences to be accessed/updated.
	@result prefs A pointer to memory that will be filled with an
		SCPreferencesRef handle to be used for all subsequent requests.
		If a session cannot be established, the contents of
		memory pointed to by this parameter are undefined.
 */
SCPreferencesRef
SCPreferencesCreate		(
				CFAllocatorRef		allocator,
				CFStringRef		name,
				CFStringRef		prefsID
				);

/*!
	@function SCPreferencesLock
	@discussion Locks access to the configuration preferences.

	This function obtains exclusive access to the configuration
	preferences associated with this prefsID. Clients attempting
	to obtain exclusive access to the preferences will either receive
	an kSCStatusPrefsBusy error or block waiting for the lock to be
	released.
	@param session An SCPreferencesRef handle that should be used for
		all API calls.
	@param wait A boolean flag indicating whether the calling process
		should block waiting for another process to complete its update
		operation and release its lock.
	@result TRUE if the lock was obtained; FALSE if an error occurred.

	XXXXX: old API error codes included kSCStatusPrefsBusy, kSCStatusAccessError, and kSCStatusStale
 */
Boolean
SCPreferencesLock		(
				SCPreferencesRef	session,
				Boolean			wait
				);

/*!
	@function SCPreferencesCommitChanges
	@discussion Commits changes made to the configuration preferences to
		persitent storage.

		This function commits any changes to permanent storage. An
		implicit call to SCPreferencesLock/SCPreferencesUnlock will
		be made if exclusive access has not already been established.
	@param session An SCPreferencesRef handle that should be used for
		all API calls.
	@result TRUE if the lock was obtained; FALSE if an error occurred.

	XXXXX: old API error codes included kSCStatusAccessError, kSCStatusStale
 */
Boolean
SCPreferencesCommitChanges	(
				SCPreferencesRef	session
				);

/*!
	@function SCPreferencesApplyChanges
	@discussion Requests that the currently stored configuration
		preferences be applied to the active configuration.
	@param session An SCPreferencesRef handle that should be used for
		all API calls.
	@result TRUE if the lock was obtained; FALSE if an error occurred.
 */
Boolean
SCPreferencesApplyChanges	(
				SCPreferencesRef	session
				);

/*!
	@function SCPreferencesUnlock
	@discussion Releases exclusive access to the configuration preferences.

		This function releases the exclusive access "lock" for this prefsID.
		Other clients will be now be able to establish exclusive access to
		the preferences.
	@param session An SCPreferencesRef handle that should be used for
		all API calls.
	@result TRUE if the lock was obtained; FALSE if an error occurred.
 */
Boolean
SCPreferencesUnlock		(
				SCPreferencesRef	session
				);

/*!
	@function SCPreferencesGetSignature
	@discussion Returns a sequence of bytes that can be used to determine
		if the saved configuration preferences have changed.
	@param session An SCPreferencesRef handle that should be used for
		all API calls.
	@param signature A pointer to a CFDataRef that will reflect
		the signature of the configuration preferences at the time
		of the call to SCPreferencesCreate().
	@result A CFDataRef that reflects the signature of the configuration
		preferences at the time of the call to SCPreferencesCreate().
 */
CFDataRef
SCPreferencesGetSignature	(
				SCPreferencesRef	session
				);

/*!
	@function SCPreferencesCopyKeyList
	@discussion Returns an array of currently defined preference keys.
	@param session An SCPreferencesRef handle that should be used for
		all API calls.
	@result The list of keys.  You must release the returned value.
 */
CFArrayRef
SCPreferencesCopyKeyList	(
				SCPreferencesRef	session
				);

/*!
	@function SCPreferencesGetValue
	@discussion Returns the data associated with a preference key.

		This function retrieves data associated with a key for the prefsID.

		Note:  You could read stale data and not know it, unless you
		first call SCPreferencesLock().
	@param session An SCPreferencesRef handle that should be used for
		all API calls.
	@param key The preference key to be returned.
	@result The value associated with the specified preference key; If no
		value was located, NULL is returned.
 */
CFPropertyListRef
SCPreferencesGetValue		(
				SCPreferencesRef	session,
				CFStringRef		key
				);

/*!
	@function SCPreferencesAddValue
	@discussion Adds data for a preference key.

	This function associates new data with the specified key. In order
	to commit these changes to permanent storage a call must be made to
	SCPreferencesCommitChanges().
	@param session The SCPreferencesRef handle that should be used to
		communicate with the APIs.
	@param key The preference key to be updated.
	@param value The CFPropertyListRef object containing the
		value to be associated with the specified preference key.
	@result TRUE if the value was added; FALSE if the key already exists or
		if an error occurred.
 */
Boolean
SCPreferencesAddValue		(
				SCPreferencesRef	session,
				CFStringRef		key,
				CFPropertyListRef	value
				);

/*!
	@function SCPreferencesSetValue
	@discussion Updates the data associated with a preference key.

	This function adds or replaces the value associated with the
	specified key. In order to commit these changes to permanent
	storage a call must be made to SCPreferencesCommitChanges().
	@param session The SCPreferencesRef handle that should be used to
		communicate with the APIs.
	@param key The preference key to be updated.
	@param value The CFPropertyListRef object containing the
		data to be associated with the specified preference key.
	@result TRUE if the value was set; FALSE if an error occurred.
 */
Boolean
SCPreferencesSetValue		(
				SCPreferencesRef	session,
				CFStringRef		key,
				CFPropertyListRef	value
				);

/*!
	@function SCPreferencesRemoveValue
	@discussion Removes the data associated with a preference key.

	This function removes the data associated with the specified
	key. In order to commit these changes to permanent storage a
	call must be made to SCPreferencesCommitChanges().
	@param session The SCPreferencesRef handle that should be used to
		communicate with the APIs.
	@param key The preference key to be removed.
	@result TRUE if the value was removed; FALSE if the key did not exist or
		if an error occurred.
 */
Boolean
SCPreferencesRemoveValue	(
				SCPreferencesRef	session,
				CFStringRef		key
				);

__END_DECLS

#endif /* _SCPREFERENCES_H */
