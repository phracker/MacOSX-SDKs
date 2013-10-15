/*
 * Copyright (c) 1998-2005 Apple Computer, Inc. All rights reserved.
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

/*!
 * @header IOStorage
 * @abstract
 * This header contains the IOStorage class definition.
 */

#ifndef _IOSTORAGE_H
#define _IOSTORAGE_H

#include <IOKit/IOTypes.h>

/*!
 * @defined kIOStorageClass
 * @abstract
 * The name of the IOStorage class.
 */

#define kIOStorageClass "IOStorage"

/*!
 * @enum IOStorageAccess
 * @discussion
 * The IOStorageAccess enumeration describes the possible access levels for open
 * requests.
 * @constant kIOStorageAccessNone
 * No access is requested; should not be passed to open().
 * @constant kIOStorageAccessReader
 * Read-only access is requested.
 * @constant kIOStorageAccessReaderWriter
 * Read and write access is requested.
 * @constant kIOStorageAccessSharedLock
 * Shared access is requested.
 * @constant kIOStorageAccessExclusiveLock
 * Exclusive access is requested.
 */

enum
{
    kIOStorageAccessNone          = 0x00,
    kIOStorageAccessReader        = 0x01,
    kIOStorageAccessReaderWriter  = 0x03,
    kIOStorageAccessSharedLock    = 0x04,
    kIOStorageAccessExclusiveLock = 0x08
};

typedef UInt32 IOStorageAccess;

/*!
 * @defined kIOStorageCategory
 * @abstract
 * kIOStorageCategory is a value for IOService's kIOMatchCategoryKey property.
 * @discussion
 * The kIOStorageCategory value is the standard value for the IOService property
 * kIOMatchCategoryKey ("IOMatchCategory") for all storage drivers.  All storage
 * objects that expect to drive new content (that is, produce new media objects)
 * are expected to compete within the kIOStorageCategory namespace.
 *
 * See the IOService documentation for more information on match categories.
 */

#define kIOStorageCategory "IOStorage"                /* (as IOMatchCategory) */

#endif /* !_IOSTORAGE_H */
