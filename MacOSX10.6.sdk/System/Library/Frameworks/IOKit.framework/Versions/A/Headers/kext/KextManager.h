/*
 * Copyright (c) 2000-2008 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
#ifndef __KEXTMANAGER_H__
#define __KEXTMANAGER_H__

#include <CoreFoundation/CoreFoundation.h>
#include <libkern/OSReturn.h>

#include <sys/cdefs.h>

__BEGIN_DECLS

/*!
 * @header KextManager.h
 *
 * @abstract
 * The KextManager API provides a simple interface for applications
 * to load kernel extensions (kexts) via RPC to kextd, and to look up the
 * URLs for kexts by bundle identifier.
 */
 
/*!
 * @function KextManagerCreateURLForBundleIdentifier
 * @abstract Create a URL locating a kext with a given bundle identifier.
 *
 * @param    allocator
 *           The allocator to use to allocate memory for the new object.
 *           Pass <code>NULL</code> or <code>kCFAllocatorDefault</code>
 *           to use the current default allocator.
 * @param    kextIdentifier
 *           The bundle identifier to look up.
 *
 * @result
 * A CFURLRef locating a kext with the requested bundle identifier.
 * Returns <code>NULL</code> if the kext cannot be found, or on error.
 *
 * @discussion
 * Kexts are looked up first by whether they are loaded, second by version.
 * Specifically, if <code>kextIdentifier</code> identifies a kext
 * that is currently loaded,
 * the returned URL will locate that kext if it's still present on disk.
 * If the requested kext is not loaded,
 * or if its bundle is not at the location it was originally loaded from,
 * the returned URL will locate the latest version of the desired kext,
 * if one can be found within the system extensions folder.
 * If no version of the kext can be found, <code>NULL</code> is returned.
 */
CFURLRef KextManagerCreateURLForBundleIdentifier(
    CFAllocatorRef allocator,
    CFStringRef    kextIdentifier);

/*!
 * @function KextManagerLoadKextWithIdentifier
 * @abstract
 * Request the kext loading system to load a kext with a given bundle identifier.
 *
 * @param    kextIdentifier
 *           The bundle identifier of the kext to look up and load.
 * @param    dependencyKextAndFolderURLs
 *           An array of additional URLs, of individual kexts and
 *           of folders that may contain kexts.
 *
 * @result
 * <code>kOSReturnSuccess</code> if the kext is successfully loaded
 * (or is already loaded), otherwise returns on error.
 *
 * @discussion
 * <code>kextIdentifier</code> is looked up in the system extensions
 * folder and among any kexts from <code>dependencyKextAndFolderURLs</code>.
 * Any non-kext URLs in <code>dependencyKextAndFolderURLs</code>
 * are scanned at the top level for kexts and plugins of kexts.
 *
 * Either the calling process must have an effective user id of 0 (superuser),
 * or the kext being loaded and all its dependencies must reside in
 * /System and have an OSBundleAllowUserLoad property of <code>true</code>.
 */
OSReturn KextManagerLoadKextWithIdentifier(
    CFStringRef    kextIdentifier,
    CFArrayRef     dependencyKextAndFolderURLs);

/*!
 * @function KextManagerLoadKextWithURL
 * @abstract
 * Request the kext loading system to load a kext with a given URL.
 *
 * @param    kextURL
 *           The URL of the kext to load.
 * @param    dependencyKextAndFolderURLs
 *           An array of additional URLs, of individual kexts and
 *           of folders that may contain kexts.
 *
 * @result
 * <code>kOSReturnSuccess</code> if the kext is successfully loaded
 * (or is already loaded), otherwise returns on error.
 *
 * @discussion
 * Any non-kext URLs in <code>dependencyKextAndFolderURLs</code>
 * are scanned at the top level for kexts and plugins of kexts.
 *
 * Either the calling process must have an effective user id of 0 (superuser),
 * or the kext being loaded and all its dependencies must reside in
 * /System and have an OSBundleAllowUserLoad property of <code>true</code>.
 */
OSReturn KextManagerLoadKextWithURL(
    CFURLRef    kextURL,
    CFArrayRef  dependencyKextAndFolderURLs);


__END_DECLS

#endif __KEXTMANAGER_H__
