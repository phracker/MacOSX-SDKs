/*
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
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

#ifndef _SCDYNAMICSTORE_H
#define _SCDYNAMICSTORE_H

#include <sys/cdefs.h>
#include <sys/syslog.h>
#include <mach/message.h>
#include <CoreFoundation/CoreFoundation.h>


/*!
	@header SCDynamicStore
	The SystemConfiguration framework provides access to the
	data used to configure a running system.  The APIs provided
	by this framework communicate with the "configd" daemon.

	The "configd" daemon manages a "dynamic store" reflecting the
	desired configuration settings as well as the current state
	of the system.  The daemon provides a notification mechanism
	for user-level processes that need to be aware of changes
	made to the data.  Lastly, the daemon loads a number of
	bundles (or plug-ins) that monitor low-level kernel events
	and, via a set of policy modules, keep the state data up
	to date.
 */


/*!
	@typedef SCDynamicStoreRef
	@discussion This is the handle to an open "dynamic store" session
		with the system configuration daemon.
 */
typedef const struct __SCDynamicStore *	SCDynamicStoreRef;

/*!
	@typedef SCDynamicStoreContext
 */
typedef struct {
	CFIndex		version;
	void *		info;
	const void	*(*retain)(const void *info);
	void		(*release)(const void *info);
	CFStringRef	(*copyDescription)(const void *info);
} SCDynamicStoreContext;

/*!
	@typedef SCDynamicStoreCallBack
	@discussion Type of the callback function used when a
		dynamic store change is delivered.
	@param store The "dynamic store" session.
	@param changedKeys The list of changed keys.
	@param info ....
 */
typedef void (*SCDynamicStoreCallBack)	(
					SCDynamicStoreRef	store,
					CFArrayRef		changedKeys,
					void			*info
					);


__BEGIN_DECLS

/*!
	@function SCDynamicStoreGetTypeID
	Returns the type identifier of all SCDynamicStore instances.
 */
CFTypeID
SCDynamicStoreGetTypeID			(void);


/*!
	@function SCDynamicStoreCreate
	@discussion Creates a new session used to interact with the dynamic
		store maintained by the SystemConfiguration server.
	@param allocator The CFAllocator which should be used to allocate
		memory for the local "dynamic store" and its storage for
		values.
		This parameter may be NULL in which case the current
		default CFAllocator is used. If this reference is not
		a valid CFAllocator, the behavior is undefined.
	@param name A string that describes the name of the calling
		process or plug-in of the caller.
	@param callout The function to be called when a watched value
		in the "dynamic store" is changed.
		A NULL value can be specified if no callouts are
		desired.
	@param context The SCDynamicStoreContext associated with the callout.
	@result A reference to the new SCDynamicStore.
 */
SCDynamicStoreRef
SCDynamicStoreCreate			(
					CFAllocatorRef			allocator,
					CFStringRef			name,
					SCDynamicStoreCallBack		callout,
					SCDynamicStoreContext		*context
					);

/*!
	@function SCDynamicStoreCreateRunLoopSource
	@discussion Creates a new session used to interact with the dynamic
		store maintained by the SystemConfiguration server.
	@param allocator The CFAllocator which should be used to allocate
		memory for the local "dynamic store" and its storage for
		values.
		This parameter may be NULL in which case the current
		default CFAllocator is used. If this reference is not
		a valid CFAllocator, the behavior is undefined.
	@param store The "dynamic store" session.
	@param order On platforms which support it, this parameter
		determines the order in which the sources which are
		ready to be processed are handled.  A lower order
		number causes processing before higher order number
		sources. It is inadvisable to depend on the order
		number for any architectural or design aspect of
		code. In the absence of any reason to do otherwise,
		zero should be used.
	@result A reference to the new CFRunLoopSource.
		You must release the returned value.

 */
CFRunLoopSourceRef
SCDynamicStoreCreateRunLoopSource	(
					CFAllocatorRef			allocator,
					SCDynamicStoreRef		store,
					CFIndex				order
					);

/*!
	@function SCDynamicStoreCopyKeyList
	@discussion Returns an array of CFString keys representing the
		configuration "dynamic store" entries that match a
		specified pattern.
	@param store The "dynamic store" session.
	@param pattern A regex(3) regular expression pattern that
		will be used to match the "dynamic store" keys.
	@result The list of matching keys.
		You must release the returned value.
		A NULL value will be returned if the list could not be obtained.
 */
CFArrayRef
SCDynamicStoreCopyKeyList		(
					SCDynamicStoreRef		store,
					CFStringRef			pattern
					);

/*!
	@function SCDynamicStoreAddValue
	@discussion Adds the key-value pair to the "dynamic store" if no
		such key already exists.
	@param store The "dynamic store" session.
	@param key The key of the value to add to the "dynamic store".
	@param value The value to add to the "dynamic store".
	@result TRUE if the key was added; FALSE if the key was already
		present in the "dynamic store" or if an error was encountered.
 */
Boolean
SCDynamicStoreAddValue			(
					SCDynamicStoreRef		store,
					CFStringRef			key,
					CFPropertyListRef		value
					);

/*!
	@function SCDynamicStoreAddTemporaryValue
	@discussion Adds the key-value pair on a temporary basis to the
		"dynamic store" if no such key already exists.  This entry
		will, unless updated by another session, automatically be
		removed when the session is closed.
	@param store The "dynamic store" session.
	@param key The key of the value to add to the "dynamic store".
	@param value The value to add to the "dynamic store".
	@result TRUE if the key was added; FALSE if the key was already
		present in the "dynamic store" or if an error was encountered.
 */
Boolean
SCDynamicStoreAddTemporaryValue		(
					SCDynamicStoreRef		store,
					CFStringRef			key,
					CFPropertyListRef		value
					);

/*!
	@function SCDynamicStoreCopyValue
	@discussion Obtains a value from the "dynamic store" for the
		specified key.
	@param store The "dynamic store" session.
	@param key The key you wish to obtain.
	@result The value from the store that is associated with the
		given key.  The value is returned as a Core Foundation
		Property List data type.
		You must release the returned value.
		If no value was located, NULL is returned.
 */
CFPropertyListRef
SCDynamicStoreCopyValue			(
					SCDynamicStoreRef		store,
					CFStringRef			key
					);

/*!
	@function SCDynamicStoreCopyMultiple
	@discussion Fetches multiple values in the "dynamic store".
	@param store The "dynamic store" session.
	@param keys The keys to be fetched; NULL if no specific keys
		are requested.
	@param patterns The regex(3) pattern strings to be fetched; NULL
		if no key patterns are requested.
	@result A dictionary containing the specific keys which were found
		in the "dynamic store" and any keys which matched the specified
		patterns; NULL is returned if an error was encountered.
		You must release the returned value.
 */
CFDictionaryRef
SCDynamicStoreCopyMultiple		(
					SCDynamicStoreRef		store,
					CFArrayRef			keys,
					CFArrayRef			patterns
					);

/*!
	@function SCDynamicStoreSetValue
	@discussion Adds or replaces a value in the "dynamic store" for
		the specified key.
	@param store The "dynamic store" session.
	@param key The key you wish to set.
	@param value The value to add to or replace in the "dynamic store".
	@result TRUE if the key was updated; FALSE if an error was encountered.
 */
Boolean
SCDynamicStoreSetValue			(
					SCDynamicStoreRef		store,
					CFStringRef			key,
					CFPropertyListRef		value
					);

/*!
	@function SCDynamicStoreSetMultiple
	@discussion Updates multiple values in the "dynamic store".
	@param store The "dynamic store" session.
	@param keysToSet Key/value pairs you wish to set into the "dynamic store".
	@param keysToRemove A list of keys you wish to remove from the "dynamic store".
	@param keysToNotify A list of keys to flag as changed (without actually changing the data).
	@result TRUE if the dynamic store updates were successful; FALSE if an error was encountered.
 */
Boolean
SCDynamicStoreSetMultiple		(
					SCDynamicStoreRef		store,
					CFDictionaryRef			keysToSet,
					CFArrayRef			keysToRemove,
					CFArrayRef			keysToNotify
					);

/*!
	@function SCDynamicStoreRemoveValue
	@discussion Removes the value of the specified key from the
		"dynamic store".
	@param store The "dynamic store" session.
	@param key The key of the value you wish to remove.
	@result TRUE if the key was removed; FALSE if no value was
		located or an error was encountered.
 */
Boolean
SCDynamicStoreRemoveValue		(
					SCDynamicStoreRef		store,
					CFStringRef			key
					);

/*!
	@function SCDynamicStoreNotifyValue
	@discussion Triggers a notification to be delivered for the
		specified key in the dynamic store.
	@param store The "dynamic store" session.
	@param key The key which should be flagged as changed (without actually changing the data).
	@result TRUE if the value was updated; FALSE if an error was encountered.
 */
Boolean
SCDynamicStoreNotifyValue		(
					SCDynamicStoreRef		store,
					CFStringRef			key
					);

/*!
	@function SCDynamicStoreSetNotificationKeys
	@discussion Specifies a set of specific keys and key patterns
		which should be monitored for changes.
	@param store The "dynamic store" session being watched.
	@param keys The keys to be monitored; NULL if no specific keys
		are to be monitored.
	@param patterns The regex(3) pattern strings to be monitored; NULL
		if no key patterns are to be monitored.
	@result TRUE if the monitored keys were set; FALSE if an error
		was encountered.
 */
Boolean
SCDynamicStoreSetNotificationKeys	(
					SCDynamicStoreRef		store,
					CFArrayRef			keys,
					CFArrayRef			patterns
					);

/*!
	@function SCDynamicStoreCopyNotifiedKeys
	@discussion Returns an array of CFString keys representing the
		"dynamic store" entries that have changed since this
		function was last called.
	@param store The "dynamic store" session.
	@result The list of changed keys.
		You must release the returned value.
		A NULL value will be returned if the list could not be obtained.
 */
CFArrayRef
SCDynamicStoreCopyNotifiedKeys		(
					SCDynamicStoreRef		store
					);

__END_DECLS

#endif /* _SCDYNAMICSTORE_H */
