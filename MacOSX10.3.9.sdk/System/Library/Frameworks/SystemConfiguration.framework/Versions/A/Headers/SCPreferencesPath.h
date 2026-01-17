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

#ifndef _SCPREFERENCESPATH_H
#define _SCPREFERENCESPATH_H

#include <sys/cdefs.h>
#include <CoreFoundation/CoreFoundation.h>
#include <SystemConfiguration/SCPreferences.h>


/*!
	@header SCPreferencesPath
	The SCPreferencesPathXXX() APIs allow an application to
	load and store XML configuration data in a controlled
	manner and provide the necessary notifications to other
	applications that need to be aware of configuration
	changes.

	The SCPreferencesPathXXX() APIs make certain assumptions
	about the layout of the preferences data.  These APIs view
	the data as a collection of dictionaries of key/value pairs
	and an associated path name.  The root path ("/") identifies
	the top-level dictionary.  Additional path components
	specify the keys for sub-dictionaries.

	For example, the following dictionary can be accessed via
	two paths.  The root ("/") path would return a dictionary
	with all keys and values.  The path "/path1" would only
	return the dictionary with the "key3" and "key4" properties.

	<PRE>
	<BR>    &lt;dict&gt;
	<BR>        &lt;key&gt;key1&lt;/key&gt;
	<BR>        &lt;string&gt;val1&lt;/string&gt;
	<BR>        &lt;key&gt;key2&lt;/key&gt;
	<BR>        &lt;string&gt;val2&lt;/string&gt;
	<BR>        &lt;key&gt;path1&lt;/key&gt;
	<BR>        &lt;dict&gt;
	<BR>            &lt;key&gt;key3&lt;/key&gt;
	<BR>            &lt;string&gt;val3&lt;/string&gt;
	<BR>        &lt;key&gt;key4&lt;/key&gt;
	<BR>        &lt;string&gt;val4&lt;/string&gt;
	<BR>        &lt;/dict&gt;
	<BR>    &lt;/dict&gt;
	</PRE>

	Each dictionary can also include the kSCResvLink key.  The
	value associated with this key is interpreted as a "link" to
	another path.  If this key is present, a call to the
	SCPreferencesPathGetValue() API will return the dictionary
	specified by the link.
 */


__BEGIN_DECLS

/*!
	@function SCPreferencesPathCreateUniqueChild
	@discussion Creates a new path component within the dictionary
		hierarchy.
	@param session The SCPreferencesRef handle that should be used to
	 communicate with the APIs.
	@param prefix A string that represents the parent path.
	@result A string representing the new (unique) child path; NULL
		if the specified path does not exist.
 */
CFStringRef
SCPreferencesPathCreateUniqueChild	(
					SCPreferencesRef	session,
					CFStringRef		prefix
					);

/*!
	@function SCPreferencesPathGetValue
	@discussion Returns the dictionary associated with the specified
		path.
	@param session The SCPreferencesRef handle that should be used to
		communicate with the APIs.
	@param path A string that represents the path to be returned.
	@result	The dictionary associated with the specified path; NULL
		if the path does not exist.
 */
CFDictionaryRef
SCPreferencesPathGetValue		(
					SCPreferencesRef	session,
					CFStringRef		path
					);

/*!
	@function SCPreferencesPathGetLink
	@discussion Returns the link (if one exists) associated with the
		specified path.
	@param session The SCPreferencesRef handle that should be used to
	 communicate with the APIs.
	@param path A string that represents the path to be returned.
	@result The dictionary associated with the specified path; NULL
		if the path is not a link or does not exist.
 */
CFStringRef
SCPreferencesPathGetLink		(
					SCPreferencesRef	session,
					CFStringRef		path
					);

/*!
	@function SCPreferencesPathSetValue
	@discussion Associates a dictionary with the specified path.
	@param session The SCPreferencesRef handle that should be used to
	 communicate with the APIs.
	@param path A string that represents the path to be updated.
	@param value A dictionary that represents the data to be
		stored at the specified path.
	@result A boolean indicating the success (or failure) of the call.
 */
Boolean
SCPreferencesPathSetValue		(
					SCPreferencesRef	session,
					CFStringRef		path,
					CFDictionaryRef		value
					);

/*!
	@function SCPreferencesPathSetLink
	@discussion Associates a link to a second dictionary at the
		specified path.
	@param session The SCPreferencesRef handle that should be used to
		communicate with the APIs.
	@param path A string that represents the path to be updated.
	@param link A string that represents the link to be stored
		at the specified path.
	@result A boolean indicating the success (or failure) of the call.
 */
Boolean
SCPreferencesPathSetLink		(
					SCPreferencesRef	session,
					CFStringRef		path,
					CFStringRef		link
					);

/*!
	@function SCPreferencesPathRemoveValue
	@discussion Removes the data associated with the specified path.
	@param session The SCPreferencesRef handle that should be used to
	 communicate with the APIs.
	@param path A string that represents the path to be returned.
	@result A boolean indicating the success (or failure) of the call.
 */
Boolean
SCPreferencesPathRemoveValue		(
					SCPreferencesRef	session,
					CFStringRef		path
					);

__END_DECLS

#endif /* _SCPREFERENCESPATH_H */
