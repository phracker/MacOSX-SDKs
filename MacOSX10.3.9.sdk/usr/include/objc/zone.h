/*
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
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

#ifndef _OBJC_ZONE_H_
#define _OBJC_ZONE_H_

#import <malloc/malloc.h>

typedef malloc_zone_t NXZone;

#define NX_NOZONE  ((NXZone *)0)

/*********	Interface to zone based malloc	************/

#include <sys/cdefs.h>

__BEGIN_DECLS
extern NXZone *NXDefaultMallocZone(void);
    // Returns the default zone used by the malloc(3) calls

extern NXZone *NXCreateZone(size_t startSize, size_t granularity, int canFree);
    // Create a new zone with its own memory pool.
    // canfree: if 0 the allocator will never free memory and mallocing will be fast

extern void NXNameZone(NXZone *z, const char *name);
    // name a zone; The string will be copied

extern void *NXZoneMalloc(malloc_zone_t *zone, size_t size);

extern void *NXZoneRealloc(malloc_zone_t *zone, void *ptr, size_t size);

extern void *NXZoneCalloc(NXZone *zonep, size_t numElems, size_t byteSize);
    // Allocates and then clears

extern void NXZoneFree(malloc_zone_t *zone, void *ptr);

extern void NXDestroyZone(malloc_zone_t *zone);

extern NXZone *NXZoneFromPtr(void *ptr);
    // Returns the zone for a pointer, or NX_NOZONE if not in any zone.
    // The ptr must have been returned from a malloc or realloc call.
__END_DECLS

#endif /* _OBJC_ZONE_H_ */
