/*
 * Copyright (c) 1999-2000, 2009 Apple Inc. All rights reserved.
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

/*
 This API returns the various standard system directories where apps, resources, etc get installed.
 Because queries can return multiple directories, the API is in the form of an enumeration.
 The directories are returned in search path order; that is, the first place to look is returned first.
 This API may return directories that do not exist yet.
 If NSUserDomain is included in a query, then the results will contain "~" to refer to the user's directory.
 NEXT_ROOT is prepended as necessary to the returned values.
 Some calls might return no directories!
 The buffer that is passed in will be filled with a null-terminated string, possibly containing as many as PATH_MAX-1 characters.

 Typical usage:
 
    #include <limits.h>
    #include <NSSystemDirectories.h>

    char path[PATH_MAX];
    NSSearchPathEnumerationState state = NSStartSearchPathEnumeration(dir, domainMask);
    while (state = NSGetNextSearchPathEnumeration(state, path)) {
        // Handle path
    }


*/

#ifndef __NS_SYSTEM_DIRECTORIES_H__
#define __NS_SYSTEM_DIRECTORIES_H__

#include <sys/cdefs.h>
#include <Availability.h>

// Directories

typedef enum {
    NSApplicationDirectory __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0)                                           = 1,    // supported applications (Applications)
    NSDemoApplicationDirectory __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_NA, __IPHONE_2_0, __IPHONE_9_0)         = 2,    // unsupported applications, demonstration versions (Applications/GrabBag)
    NSDeveloperApplicationDirectory __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_NA, __IPHONE_2_0, __IPHONE_9_0)    = 3,    // developer applications (Developer/Applications) Soft deprecated as of __MAC_10_5 - there is no one single Developer directory
    NSAdminApplicationDirectory __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_NA, __IPHONE_2_0, __IPHONE_9_0)        = 4,    // system and network administration applications (Applications/Utilities)
    NSLibraryDirectory __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0)                                               = 5,    // various user-visible documentation, support, and configuration files, resources (Library)
    NSDeveloperDirectory __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_NA, __IPHONE_2_0, __IPHONE_9_0)               = 6,    // developer resources (Developer) Soft deprecated as of __MAC_10_5 - there is no one single Developer directory
    NSUserDirectory __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_NA, __IPHONE_2_0, __IPHONE_9_0)                    = 7,    // user home directories (Users)
    NSDocumentationDirectory __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_NA, __IPHONE_2_0, __IPHONE_9_0)           = 8,    // documentation (Library/Documentation)
    NSDocumentDirectory __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0)                                              = 9,    // documents (Documents)
    NSCoreServiceDirectory __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0)                                           = 10,   // location of core services (System/Library/CoreServices)
    NSAutosavedInformationDirectory __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_6, __MAC_NA, __IPHONE_4_0, __IPHONE_9_0)    = 11,   // location of user's directory for use with autosaving (Library/Autosave Information)
    NSDesktopDirectory __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_4, __MAC_NA, __IPHONE_2_0, __IPHONE_9_0)                 = 12,   // location of user's Desktop (Desktop)
    NSCachesDirectory __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0)                                                = 13,   // location of discardable cache files (Library/Caches)
    NSApplicationSupportDirectory __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0)                                    = 14,   // location of application support files (plug-ins, etc) (Library/Application Support)
    NSDownloadsDirectory __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_5, __MAC_NA, __IPHONE_2_0, __IPHONE_9_0)               = 15,   // location of user's Downloads directory (Downloads)
    NSInputMethodsDirectory __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_6, __MAC_NA, __IPHONE_4_0, __IPHONE_9_0)            = 16,   // input methods (Library/Input Methods)
    NSMoviesDirectory __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_6, __MAC_NA, __IPHONE_4_0, __IPHONE_9_0)                  = 17,   // location of user's Movies directory (~/Movies)
    NSMusicDirectory __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_6, __MAC_NA, __IPHONE_4_0, __IPHONE_9_0)                   = 18,   // location of user's Music directory (~/Music)
    NSPicturesDirectory __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_6, __MAC_NA, __IPHONE_4_0, __IPHONE_9_0)                = 19,   // location of user's Pictures directory (~/Pictures)
    NSPrinterDescriptionDirectory __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_6, __MAC_NA, __IPHONE_4_0, __IPHONE_9_0)      = 20,   // location of system's PPDs directory (Library/Printers/PPDs)
    NSSharedPublicDirectory __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_6, __MAC_NA, __IPHONE_4_0, __IPHONE_9_0)            = 21,   // location of user's Public sharing directory (~/Public)
    NSPreferencePanesDirectory __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_6, __MAC_NA, __IPHONE_4_0, __IPHONE_9_0)         = 22,   // location of the PreferencePanes directory for use with System Preferences (Library/PreferencePanes)
    NSAllApplicationsDirectory __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0)                                       = 100,  // all directories where applications can occur (Applications, Applications/Utilities, Developer/Applications, ...)
    NSAllLibrariesDirectory __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0)                                          = 101   // all directories where resources can occur (Library, Developer)
} NSSearchPathDirectory __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

// Domains

typedef enum {
    NSUserDomainMask __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0)                                     = 1,        // user's home directory --- place to install user's personal items (~)
    NSLocalDomainMask __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0)                                    = 2,        // local to the current machine --- place to install items available to everyone on this machine
    NSNetworkDomainMask __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_NA, __IPHONE_2_0, __IPHONE_9_0)    = 4,        // publically available location in the local area network --- place to install items available on the network (/Network)
    NSSystemDomainMask __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0)                                   = 8,        // provided by Apple
    NSAllDomainsMask __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0)                                     = 0x0ffff   // all domains: all of the above and more, future items
} NSSearchPathDomainMask __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

typedef unsigned int NSSearchPathEnumerationState;

__BEGIN_DECLS

/*!
 * @function NSStartSearchPathEnumeration
 *
 * @discussion
 * Call this function to begin enumeration of the filesystem paths for the
 * specified directory in the desired domains. The return value should be
 * passed to one or more calls to NSGetNextSearchPathEnumeration() to obtain
 * the filesystem path and continue the enumeration.
 *
 * @param dir
 * The special directory to enumerate.
 *
 * @param domainMask
 * The domains in which the special directory should be enumerated.
 *
 * @return
 * An enumeration state value to pass to NSGetNextSearchPathEnumeration().
 */
__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0)
extern NSSearchPathEnumerationState
NSStartSearchPathEnumeration(NSSearchPathDirectory dir,
			     NSSearchPathDomainMask domainMask);

/*!
 * @function NSGetNextSearchPathEnumeration
 *
 * @discussion
 * Returns the filesystem path for a special directory in the domain(s)
 * specified by the state value returned by NSStartSearchPathEnumeration().
 * Subsequent calls to NSGetNextSearchPathEnumeration() should pass the state
 * value returned by the previous call to continue the enumeration in each
 * domain. A state value of zero will be returned when all domains have been
 * enumerated.
 *
 * @param state
 * The state value returned by NSStartSearchPathEnumeration() or by a previous
 * call to this function.
 *
 * @param path
 * A buffer to which the NUL-terminated filesystem path of the special
 * directory will be written. The buffer size must be at least PATH_MAX bytes.
 *
 * @return
 * An enumeration state value to pass to a subsequent call to
 * NSGetNextSearchPathEnumeration(), or zero if enumeration is complete.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0)
extern NSSearchPathEnumerationState
NSGetNextSearchPathEnumeration(NSSearchPathEnumerationState state, char *path);

__END_DECLS

#endif /* __NS_SYSTEM_DIRECTORIES_H__ */
