/*
 * Copyright (c) 1998-2021 Apple Computer, Inc. All rights reserved.
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

#ifndef __IOKIT_IOMAPTYPES_H
#define __IOKIT_IOMAPTYPES_H

// IOConnectMapMemory memoryTypes
enum {
	kIODefaultMemoryType        = 0
};

enum {
	kIODefaultCache             = 0,
	kIOInhibitCache             = 1,
	kIOWriteThruCache           = 2,
	kIOCopybackCache            = 3,
	kIOWriteCombineCache        = 4,
	kIOCopybackInnerCache       = 5,
	kIOPostedWrite              = 6,
	kIORealTimeCache            = 7,
	kIOPostedReordered          = 8,
	kIOPostedCombinedReordered  = 9,
};

// IOMemory mapping options
enum {
	kIOMapAnywhere                = 0x00000001,

	kIOMapCacheMask               = 0x00000f00,
	kIOMapCacheShift              = 8,
	kIOMapDefaultCache            = kIODefaultCache            << kIOMapCacheShift,
	kIOMapInhibitCache            = kIOInhibitCache            << kIOMapCacheShift,
	kIOMapWriteThruCache          = kIOWriteThruCache          << kIOMapCacheShift,
	kIOMapCopybackCache           = kIOCopybackCache           << kIOMapCacheShift,
	kIOMapWriteCombineCache       = kIOWriteCombineCache       << kIOMapCacheShift,
	kIOMapCopybackInnerCache      = kIOCopybackInnerCache      << kIOMapCacheShift,
	kIOMapPostedWrite             = kIOPostedWrite             << kIOMapCacheShift,
	kIOMapRealTimeCache           = kIORealTimeCache           << kIOMapCacheShift,
	kIOMapPostedReordered         = kIOPostedReordered         << kIOMapCacheShift,
	kIOMapPostedCombinedReordered = kIOPostedCombinedReordered << kIOMapCacheShift,

	kIOMapUserOptionsMask         = 0x00000fff,

	kIOMapReadOnly                = 0x00001000,

	kIOMapStatic                  = 0x01000000,
	kIOMapReference               = 0x02000000,
	kIOMapUnique                  = 0x04000000,
	kIOMapPrefault                = 0x10000000,
	kIOMapOverwrite               = 0x20000000,
	kIOMapGuardedMask             = 0xC0000000,
	kIOMapGuardedSmall            = 0x40000000,
	kIOMapGuardedLarge            = 0x80000000
};

#endif /* ! __IOKIT_IOMAPTYPES_H */
