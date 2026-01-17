/*
 *  CGSession.h
 *  CoreGraphics
 *
 *  Copyright (c) 2003 Apple Computer, Inc. All rights reserved.
 *
 */
#ifndef __CGSESSION_H__
#define __CGSESSION_H__ 1

#include <CoreGraphics/CGBase.h>
#include <CoreFoundation/CoreFoundation.h>

CG_EXTERN_C_BEGIN

/*
 * Fetch the current session's dictionary
 * Returns NULL if the caller is not within a GUI session, as when the caller is a UNIX daemon,
 * or if a system is configured to not run a Quartz GUI (window server disabled)
 */
CG_EXTERN CFDictionaryRef CGSessionCopyCurrentDictionary(void);

/*
 * Predefined keys for the Session dictionaries
 * Values are provided as CFSTR() macros rather than extern C data for PEF/CFM support.
 * Constant values will remain unchanged in future releases for PEF/CFM compatibility.
 *
 * These keys are guaranteed by the system to be present in a session dictionary.
 * Additional keys and values may be defined and added to the dictionary by
 * other system components as needed.
 */
#define kCGSessionUserIDKey		CFSTR("kCGSSessionUserIDKey")
        /* value is a CFNumber encoding a uid_t for the session's current user. */

#define kCGSessionUserNameKey		CFSTR("kCGSSessionUserNameKey")
        /* value is a CFString encoding the session's short user name as set by loginwindow */

#define kCGSessionConsoleSetKey		CFSTR("kCGSSessionConsoleSetKey")
        /* value is a CFNumber encoding a 32 bit unsigned  integer value representing a set of hardware composing a console */

#define kCGSessionOnConsoleKey		CFSTR("kCGSSessionOnConsoleKey")
        /* value is a CFBoolean, kCFBooleanTrue if the session is on a console, otherwise kCFBooleanFalse */

#define kCGSessionLoginDoneKey		CFSTR("kCGSessionLoginDoneKey")
        /* value is a CFBoolean, kCFBooleanTrue if login operation has been done, otherwise kCFBooleanFalse */

/*
 * When the GUI session on a console changes, a notification
 * is posted via the notify_post() API.  See notify (3) and
 * notify.h for details.
 */
#define kCGNotifyGUIConsoleSessionChanged		"com.apple.coregraphics.GUIConsoleSessionChanged"
/* When a user logs in or out of a session we post a notification via notify_post() */
#define kCGNotifyGUISessionUserChanged			"com.apple.coregraphics.GUISessionUserChanged"

CG_EXTERN_C_END

#endif /* __CGSESSION_H__ */
