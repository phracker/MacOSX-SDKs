/*
 * Copyright (c) 2019-2019 Apple Inc. All rights reserved.
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

#include <stdint.h>
#include <stdlib.h>
#include <sys/cdefs.h>

#include <DriverKit/OSCollection.h>
#include <DriverKit/OSContainer.h>
#include <DriverKit/OSSerialization.h>
#include <DriverKit/OSDictionary.h>
#include <DriverKit/OSArray.h>
#include <DriverKit/OSDictionary.h>
#if __has_include(<DriverKit/OSSet.h>)
#include <DriverKit/OSSet.h>
#endif
#if __has_include(<DriverKit/OSOrderedSet.h>)
#include <DriverKit/OSOrderedSet.h>
#endif
#include <DriverKit/OSString.h>
#include <DriverKit/OSData.h>
#include <DriverKit/OSNumber.h>
#include <DriverKit/OSBoolean.h>

#ifndef DRIVERKIT_OSCOLLECTIONS_H
#define DRIVERKIT_OSCOLLECTIONS_H

__BEGIN_DECLS

#ifdef __cplusplus
class OSObject;
#else
typedef struct OSObject OSObject;
#endif

typedef OSObject * OSObjectPtr;

typedef uint64_t OSCollectionType;

enum 
{
     kOSCollectionTypeDictionary    = 1,
     kOSCollectionTypeArray         = 2,
     kOSCollectionTypeSet           = 3,
     kOSCollectionTypeNumber        = 4,
     kOSCollectionTypeSymbol        = 8,
     kOSCollectionTypeString        = 9,
     kOSCollectionTypeData          = 10,
     kOSCollectionTypeBoolean       = 11,
     kOSCollectionTypeSerialization = 13,
};

const char *
OSCollectionTypeName(OSCollectionType t);

OSCollectionType
OSCollectionTypeID(OSObjectPtr obj);

void
OSObjectRetain(OSObjectPtr container);

void
OSObjectRelease(OSObjectPtr container);

#define OSObjectSafeReleaseNULL(ptr)                 \
    do {                                                \
        if ((ptr)) {                                    \
            OSObjectRelease(ptr);                    \
            (ptr) = NULL;                               \
        }                                               \
    } while (0)                                         \


void
OSCollectionsInitialize();

struct __OSStringStatic {
    const char * cString;
    OSString * osString;
};

#define OSSTR(cStr) ({ \
    static struct __OSStringStatic __attribute__((used, visibility("hidden"),section("__DATA,__osstringinfo,regular,no_dead_strip"),no_sanitize("address"))) static_str = { cStr, NULL }; \
    static_str.osString; \
})

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

const char *
OSStringGetStringPtr(OSStringPtr obj) __attribute__((nonnull(1)));

size_t
OSStringGetLength(OSStringPtr string) __attribute__((nonnull(1)));

OSStringPtr
OSStringCreate(const char *cstring, size_t length)  __attribute__((nonnull(1)));

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

size_t
OSDataGetLength(OSDataPtr obj);

const void *
OSDataGetBytesPtr(OSDataPtr obj, size_t offset, size_t length) __attribute__((nonnull(1)));

size_t
OSDataGetBytes(OSDataPtr obj, void * buffer, size_t offset, size_t length);

OSDataPtr
OSDataCreate(const void * bytes, size_t length);

bool
OSDataAppendBytes(OSDataPtr data, const void * bytes, size_t length);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

uint64_t
OSNumberGetUInt64Value(OSNumberPtr obj) __attribute__((nonnull(1)));

OSNumberPtr
OSNumberCreateWithUInt64Value(uint64_t value);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// return true to terminate the iteration
typedef bool (^OSDictionaryApplier)(const char * key, OSObjectPtr value);

OSDictionaryPtr
OSDictionaryCreate(void);

uint32_t
OSDictionaryGetCount(OSDictionaryPtr obj);

bool
OSDictionaryApply(OSDictionaryPtr obj, OSDictionaryApplier applier) __attribute__((nonnull(1,2)));

bool
OSDictionarySetValue(OSDictionaryPtr obj, const char * key, OSObjectPtr value) __attribute__((nonnull(1,2)));

OSObjectPtr
OSDictionaryGetValue(OSDictionaryPtr obj, const char * key);

const char *
OSDictionaryGetStringValue(OSDictionaryPtr obj, const char * key);

uint64_t
OSDictionaryGetUInt64Value(OSDictionaryPtr obj, const char * key);

void
OSDictionarySetStringValue(OSDictionaryPtr obj, const char * key, const char * value);
void
OSDictionarySetUInt64Value(OSDictionaryPtr obj, const char * key, uint64_t value);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// return true to terminate the iteration
typedef bool (^OSArrayApplier)(OSObjectPtr value);

enum
{
     kOSArrayAppend = ((size_t)(-1))
};

OSArrayPtr
OSArrayCreate(void);

uint32_t
OSArrayGetCount(OSArrayPtr obj);

bool
OSArrayApply(OSArrayPtr obj, OSArrayApplier applier) __attribute__((nonnull(1,2)));

bool
OSArraySetValue(OSArrayPtr obj, size_t index, OSObjectPtr value);

bool
OSArrayReplaceValue(OSArrayPtr obj, size_t index, OSObjectPtr value);

bool
OSArrayAppendValue(OSArrayPtr obj, OSObjectPtr value);

OSObjectPtr
OSArrayGetValue(OSArrayPtr obj, size_t index);

const char *
OSArrayGetStringValue(OSArrayPtr obj, size_t index);

void
OSArraySetStringValue(OSArrayPtr obj, size_t index, const char * value);

uint64_t
OSArrayGetUInt64Value(OSArrayPtr obj, size_t index);

void
OSArraySetUInt64Value(OSArrayPtr obj, size_t index, uint64_t value);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

OSObjectPtr
OSCreateObjectFromSerialization(OSSerializationPtr serial);

OSSerializationPtr
OSCreateSerializationFromObject(OSObjectPtr obj);

OSSerializationPtr
OSCreateSerializationFromBytes(const void * bytes, size_t length, OSSerializationFreeBufferHandler freeBuffer);

const void *
OSSerializationGetBytes(OSSerializationPtr serial, size_t * length);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void
OSObjectLog(OSObjectPtr obj);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

__END_DECLS

#endif /* DRIVERKIT_OSCOLLECTIONS_H */
