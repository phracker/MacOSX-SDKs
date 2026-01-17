/*	NSZone.h
	Copyright (c) 1994-2012, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObjCRuntime.h>
#include <CoreFoundation/CFBase.h>

@class NSString;

typedef struct _NSZone NSZone;


FOUNDATION_EXPORT NSZone *NSDefaultMallocZone(void);
FOUNDATION_EXPORT NSZone *NSCreateZone(NSUInteger startSize, NSUInteger granularity, BOOL canFree);
FOUNDATION_EXPORT void NSRecycleZone(NSZone *zone);
FOUNDATION_EXPORT void NSSetZoneName(NSZone *zone, NSString *name);
FOUNDATION_EXPORT NSString *NSZoneName(NSZone *zone);
FOUNDATION_EXPORT NSZone *NSZoneFromPointer(void *ptr);

FOUNDATION_EXPORT void *NSZoneMalloc(NSZone *zone, NSUInteger size);
FOUNDATION_EXPORT void *NSZoneCalloc(NSZone *zone, NSUInteger numElems, NSUInteger byteSize);
FOUNDATION_EXPORT void *NSZoneRealloc(NSZone *zone, void *ptr, NSUInteger size);
FOUNDATION_EXPORT void NSZoneFree(NSZone *zone, void *ptr);

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

/* Garbage Collected memory allocation.
   Raw memory may be directly allocated (and "realloc"ed) from the collector. The default unscanned memory returned by this call should not be used to hold live pointers to garbage collected memory.  Use the scanned option.  Further, the pointer type of the stored location must be marked with the __strong attribute in order for the write-barrier assignment primitive to be generated.  
   The NSCollectorDisabledOption provides an allocation for use as an external reference.
*/

enum {
    NSScannedOption = (1UL << 0), 
    NSCollectorDisabledOption = (1UL << 1),
};

FOUNDATION_EXPORT void *__strong NSAllocateCollectable(NSUInteger size, NSUInteger options);
FOUNDATION_EXPORT void *__strong NSReallocateCollectable(void *ptr, NSUInteger size, NSUInteger options);

#endif

#ifndef CF_CONSUMED
#if __has_feature(attribute_cf_consumed)
#define CF_CONSUMED __attribute__((cf_consumed))
#else
#define CF_CONSUMED
#endif
#endif

/*
 NSMakeCollectable
 CFTypeRef style objects are garbage collected, yet only sometime after the last CFRelease() is performed.  Particulary for fully-bridged CFTypeRef objects such as CFStrings and collections (CFDictionaryRef et alia) it is imperative that either CFMakeCollectable or the more type safe NSMakeCollectable be performed, preferably right upon allocation.  Conceptually, this moves them from a "C" style opaque pointer into an "id" style object.
 This function is unavailable in ARC mode. Use CFBridgingRelease instead.
*/
NS_INLINE NS_RETURNS_RETAINED id NSMakeCollectable(CFTypeRef CF_CONSUMED cf) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;
NS_INLINE NS_RETURNS_RETAINED id NSMakeCollectable(CFTypeRef CF_CONSUMED cf) {
#if __has_feature(objc_arc)
    return nil;
#else
    return (cf ? (id)CFMakeCollectable(cf) : nil);
#endif
}

FOUNDATION_EXPORT NSUInteger NSPageSize(void);
FOUNDATION_EXPORT NSUInteger NSLogPageSize(void);
FOUNDATION_EXPORT NSUInteger NSRoundUpToMultipleOfPageSize(NSUInteger bytes);
FOUNDATION_EXPORT NSUInteger NSRoundDownToMultipleOfPageSize(NSUInteger bytes);
FOUNDATION_EXPORT void *NSAllocateMemoryPages(NSUInteger bytes);
FOUNDATION_EXPORT void NSDeallocateMemoryPages(void *ptr, NSUInteger bytes);
FOUNDATION_EXPORT void NSCopyMemoryPages(const void *source, void *dest, NSUInteger bytes);
FOUNDATION_EXPORT NSUInteger NSRealMemoryAvailable(void) NS_DEPRECATED(10_0, 10_8, 2_0, 6_0); // see NSProcessInfo.h instead

