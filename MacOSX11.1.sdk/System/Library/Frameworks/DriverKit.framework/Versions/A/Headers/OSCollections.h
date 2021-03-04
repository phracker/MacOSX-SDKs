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

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
 * DRIVERKIT_ macros below can be used to describe the ownership semantics
 * of functions handling subclasses of OSObject.
 * The attributes propagate with inheritance, but can be overriden.
 * New versions of the Clang Static Analyzer can use this knowledge to
 * check the code for leaks or uses-after-free.
 */

/*
 * By default, methods returning OSObjects are assumed to have the following
 * owneship semantics:
 *   - Functions and methods that have "Get" in their name are assumed to be getters.
 *  They return at "+0" and the caller is not responsible for releasing the
 *  returned object.
 *
 *  - All other methods are assumed to return at "+1", and the caller is
 *  responsible for releasing the returned object.
 *
 *  The semantics implied by the naming convention described above can be
 *  overriden using either DRIVERKIT_RETURNS_RETAINED or DRIVERKIT_RETURNS_NOT_RETAINED
 *  attribute applied to a function.
 *  In the former case, it stipulates that the function is returning at "+1",
 *  and in the latter case "+0".
 *
 *  DRIVERKIT_RETURNS_RETAINED and DRIVERKIT_RETURNS_NOT_RETAINED attributes
 *  can be also applied to out parameters, in which case they specify
 *  that an out parameter is written into at +1 or +0 respectively.
 *  Behavior of out parameters of non-void functions can be additionally
 *  customized via annotations that explain how a function returns a retained
 *  or a non-retained value through its out-parameter depending on its
 *  return value: DRIVERKIT_RETURNS_RETAINED_ON_ZERO and
 *  DRIVERKIT_RETURNS_RETAINED_ON_NONZERO.
 */
#if __has_attribute(os_returns_retained)
#define DRIVERKIT_RETURNS_RETAINED __attribute__((os_returns_retained))
#else
#define DRIVERKIT_RETURNS_RETAINED
#endif
#if __has_attribute(os_returns_not_retained)
#define DRIVERKIT_RETURNS_NOT_RETAINED __attribute__((os_returns_not_retained))
#else
#define DRIVERKIT_RETURNS_NOT_RETAINED
#endif

/*
 * DRIVERKIT_CONSUMED attribute can be applied to parameters.
 * It specifies that this function call would consume the reference to the
 * annotated parameter.
 */
#if __has_attribute(os_consumed)
#define DRIVERKIT_CONSUMED __attribute__((os_consumed))
#else
#define DRIVERKIT_CONSUMED
#endif

/*
 * DRIVERKIT_CONSUMES_THIS attribute can be applied to C++ methods.
 * It specifies that this method call consumes a reference to "this" (e.g.
 * by storing a reference to "this" in a passed parameter).
 */
#if __has_attribute(os_consumes_this)
#define DRIVERKIT_CONSUMES_THIS __attribute__((os_consumes_this))
#else
#define DRIVERKIT_CONSUMES_THIS
#endif

/*
 * DRIVERKIT_RETURNS_RETAINED_ON_ZERO is an attribute applicable to out
 * parameters.
 * It specifies that an out parameter at +1 is written into an argument iff
 * the function returns a zero return value.
 */
#if __has_attribute(os_returns_retained_on_zero)
#define DRIVERKIT_RETURNS_RETAINED_ON_ZERO __attribute__((os_returns_retained_on_zero))
#else
#define DRIVERKIT_RETURNS_RETAINED_ON_ZERO
#endif

/*
 * DRIVERKIT_RETURNS_RETAINED_ON_NON_ZERO is an attribute applicable to out
 * parameters.
 * It specifies that an out parameter at +1 is written into an argument iff
 * the function returns a non-zero return value.
 */
#if __has_attribute(os_returns_retained_on_non_zero)
#define DRIVERKIT_RETURNS_RETAINED_ON_NONZERO __attribute__((os_returns_retained_on_non_zero))
#else
#define DRIVERKIT_RETURNS_RETAINED_ON_NONZERO
#endif

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

const char *
OSStringGetStringPtr(OSStringPtr obj);

size_t
OSStringGetLength(OSStringPtr string);

OSStringPtr
OSStringCreate(const char * cstring, size_t length);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

size_t
OSDataGetLength(OSDataPtr obj);

const void *
OSDataGetBytesPtr(OSDataPtr obj, size_t offset, size_t length);

size_t
OSDataGetBytes(OSDataPtr obj, void * buffer, size_t offset, size_t length);

OSDataPtr
OSDataCreate(const void * bytes, size_t length);

bool
OSDataAppendBytes(OSDataPtr data, const void * bytes, size_t length);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

uint64_t
OSNumberGetUInt64Value(OSNumberPtr obj);

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
OSDictionaryApply(OSDictionaryPtr obj, OSDictionaryApplier applier);

bool
OSDictionarySetValue(OSDictionaryPtr obj, const char * key, OSObjectPtr value);

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
OSArrayApply(OSArrayPtr obj, OSArrayApplier applier);

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
