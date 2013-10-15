/*	NSZone.h
	Copyright (c) 1994-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObjCRuntime.h>

@class NSString;

typedef struct _NSZone NSZone;


FOUNDATION_EXPORT NSZone *NSDefaultMallocZone(void);
FOUNDATION_EXPORT NSZone *NSCreateZone(unsigned startSize, unsigned granularity, BOOL canFree);
FOUNDATION_EXPORT void NSRecycleZone(NSZone *zone);
FOUNDATION_EXPORT void NSSetZoneName(NSZone *zone, NSString *name);
FOUNDATION_EXPORT NSString *NSZoneName(NSZone *zone);
FOUNDATION_EXPORT NSZone *NSZoneFromPointer(void *ptr);

FOUNDATION_EXPORT void *NSZoneMalloc(NSZone *zone, unsigned size);
FOUNDATION_EXPORT void *NSZoneCalloc(NSZone *zone, unsigned numElems, unsigned byteSize);
FOUNDATION_EXPORT void *NSZoneRealloc(NSZone *zone, void *ptr, unsigned size);
FOUNDATION_EXPORT void NSZoneFree(NSZone *zone, void *ptr);

enum {
    NSScannedOption = (1<<0)
};

FOUNDATION_EXPORT void *NSAllocateCollectable(unsigned long size, unsigned long options) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
FOUNDATION_EXPORT void *NSReallocateCollectable(void *ptr, unsigned long size, unsigned long options) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

FOUNDATION_EXPORT unsigned NSPageSize(void);
FOUNDATION_EXPORT unsigned NSLogPageSize(void);
FOUNDATION_EXPORT unsigned NSRoundUpToMultipleOfPageSize(unsigned bytes);
FOUNDATION_EXPORT unsigned NSRoundDownToMultipleOfPageSize(unsigned bytes);
FOUNDATION_EXPORT void *NSAllocateMemoryPages(unsigned bytes);
FOUNDATION_EXPORT void NSDeallocateMemoryPages(void *ptr, unsigned bytes);
FOUNDATION_EXPORT void NSCopyMemoryPages(const void *source, void *dest, unsigned bytes);
FOUNDATION_EXPORT unsigned NSRealMemoryAvailable(void);

