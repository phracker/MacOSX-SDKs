//===--- HeapObject.h -------------------------------------------*- C++ -*-===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2017 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://swift.org/LICENSE.txt for license information
// See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//
#ifndef SWIFT_STDLIB_SHIMS_HEAPOBJECT_H
#define SWIFT_STDLIB_SHIMS_HEAPOBJECT_H

#include "RefCount.h"
#include "SwiftStddef.h"
#include "System.h"
#include "Target.h"

#define SWIFT_ABI_HEAP_OBJECT_HEADER_SIZE_64 16
#define SWIFT_ABI_HEAP_OBJECT_HEADER_SIZE_32 8

#ifndef __swift__
#include <type_traits>
#include "swift/Basic/type_traits.h"

namespace swift {

struct InProcess;

template <typename Target> struct TargetHeapMetadata;
using HeapMetadata = TargetHeapMetadata<InProcess>;
#else
typedef struct HeapMetadata HeapMetadata;
typedef struct HeapObject HeapObject;
#endif

// Hack: Clang doesn't define __ptrauth_objc_isa_pointer in phase 1 to avoid
// triggering auth-on-load in projects using the qualifier. However, we need the
// definition in phase 1, so create our own little copy of it.
#if !defined(__swift__) && __has_feature(ptrauth_calls) && SWIFT_PTRAUTH_SIGN_ISA
#include <ptrauth.h>
#define __ptrauth_swift_runtime_isa \
  __ptrauth(ptrauth_key_process_independent_data, 1, 0x6AE1)
#endif

// The members of the HeapObject header that are not shared by a
// standard Objective-C instance
#define SWIFT_HEAPOBJECT_NON_OBJC_MEMBERS       \
  InlineRefCounts refCounts

/// The Swift heap-object header.
/// This must match RefCountedStructTy in IRGen.
struct HeapObject {
#ifdef __swift__
  HeapMetadata const *metadata;
#else
  /// This is always a valid pointer to a metadata object.
private:
  HeapMetadata const *
#if SWIFT_PTRAUTH && SWIFT_PTRAUTH_SIGN_ISA
  __ptrauth_swift_runtime_isa
#endif
  metadata;

public:
#endif // ifdef __swift

  SWIFT_HEAPOBJECT_NON_OBJC_MEMBERS;

#ifndef __swift__
  HeapObject() = default;

  // Initialize a HeapObject header as appropriate for a newly-allocated object.
  constexpr HeapObject(HeapMetadata const *newMetadata) 
    : metadata(newMetadata)
    , refCounts(InlineRefCounts::Initialized)
  { }
  
  // Initialize a HeapObject header for an immortal object
  constexpr HeapObject(HeapMetadata const *newMetadata,
                       InlineRefCounts::Immortal_t immortal)
    : metadata(newMetadata)
  , refCounts(InlineRefCounts::Immortal)
  { }

  HeapMetadata const *getMetadata() const {
#if SWIFT_PTRAUTH_AUTH_ISA
    return metadata;
#else
    return __ptrauth_swift_isa_strip(*(HeapMetadata const * const *)&metadata);
#endif
  }

  void setMetadata(HeapMetadata const *newMetadata) {
    metadata = newMetadata;
  }

#ifndef NDEBUG
  void dump() const SWIFT_USED;
#endif

#endif // ndef __swift__
};

#ifdef __cplusplus
extern "C" {
#endif

SWIFT_RUNTIME_STDLIB_API
void _swift_instantiateInertHeapObject(void *address,
                                       const HeapMetadata *metadata);

SWIFT_RUNTIME_STDLIB_API
__swift_size_t swift_retainCount(HeapObject *obj);

SWIFT_RUNTIME_STDLIB_API
__swift_size_t swift_unownedRetainCount(HeapObject *obj);

SWIFT_RUNTIME_STDLIB_API
__swift_size_t swift_weakRetainCount(HeapObject *obj);

#ifdef __cplusplus
} // extern "C"
#endif

#ifndef __swift__
static_assert(std::is_trivially_destructible<HeapObject>::value,
              "HeapObject must be trivially destructible");

static_assert(sizeof(HeapObject) == 2*sizeof(void*),
              "HeapObject must be two pointers long");

static_assert(alignof(HeapObject) == alignof(void*),
              "HeapObject must be pointer-aligned");

} // end namespace swift
#endif // __cplusplus

/// Global bit masks

// TODO(<rdar://problem/34837179>): Convert each macro below to static consts
// when static consts are visible to SIL.

// The extra inhabitants and spare bits of heap object pointers.
// These must align with the values in IRGen's SwiftTargetInfo.cpp.
#if defined(__x86_64__)

#ifdef __APPLE__
#define _swift_abi_LeastValidPointerValue                                      \
  (__swift_uintptr_t) SWIFT_ABI_DARWIN_X86_64_LEAST_VALID_POINTER
#else
#define _swift_abi_LeastValidPointerValue                                      \
  (__swift_uintptr_t) SWIFT_ABI_DEFAULT_LEAST_VALID_POINTER
#endif
#define _swift_abi_SwiftSpareBitsMask                                          \
  (__swift_uintptr_t) SWIFT_ABI_X86_64_SWIFT_SPARE_BITS_MASK
#if SWIFT_TARGET_OS_SIMULATOR
#define _swift_abi_ObjCReservedBitsMask                                        \
  (__swift_uintptr_t) SWIFT_ABI_X86_64_SIMULATOR_OBJC_RESERVED_BITS_MASK
#define _swift_abi_ObjCReservedLowBits                                         \
  (unsigned) SWIFT_ABI_X86_64_SIMULATOR_OBJC_NUM_RESERVED_LOW_BITS
#else
#define _swift_abi_ObjCReservedBitsMask                                        \
  (__swift_uintptr_t) SWIFT_ABI_X86_64_OBJC_RESERVED_BITS_MASK
#define _swift_abi_ObjCReservedLowBits                                         \
  (unsigned) SWIFT_ABI_X86_64_OBJC_NUM_RESERVED_LOW_BITS
#endif

#define _swift_BridgeObject_TaggedPointerBits                                  \
  (__swift_uintptr_t) SWIFT_ABI_DEFAULT_BRIDGEOBJECT_TAG_64

#elif (defined(__arm64__) || defined(__aarch64__) || defined(_M_ARM64)) &&     \
      (__POINTER_WIDTH__ == 64)

#ifdef __APPLE__
#define _swift_abi_LeastValidPointerValue                                      \
  (__swift_uintptr_t) SWIFT_ABI_DARWIN_ARM64_LEAST_VALID_POINTER
#else
#define _swift_abi_LeastValidPointerValue                                      \
  (__swift_uintptr_t) SWIFT_ABI_DEFAULT_LEAST_VALID_POINTER
#endif
#define _swift_abi_SwiftSpareBitsMask                                          \
  (__swift_uintptr_t) SWIFT_ABI_ARM64_SWIFT_SPARE_BITS_MASK
#define _swift_abi_ObjCReservedBitsMask                                        \
  (__swift_uintptr_t) SWIFT_ABI_ARM64_OBJC_RESERVED_BITS_MASK
#define _swift_abi_ObjCReservedLowBits                                         \
  (unsigned) SWIFT_ABI_ARM64_OBJC_NUM_RESERVED_LOW_BITS
#define _swift_BridgeObject_TaggedPointerBits                                  \
  (__swift_uintptr_t) SWIFT_ABI_DEFAULT_BRIDGEOBJECT_TAG_64

#elif defined(__powerpc64__)

#define _swift_abi_LeastValidPointerValue                                      \
  (__swift_uintptr_t) SWIFT_ABI_DEFAULT_LEAST_VALID_POINTER
#define _swift_abi_SwiftSpareBitsMask                                          \
  (__swift_uintptr_t) SWIFT_ABI_POWERPC64_SWIFT_SPARE_BITS_MASK
#define _swift_abi_ObjCReservedBitsMask                                        \
  (__swift_uintptr_t) SWIFT_ABI_DEFAULT_OBJC_RESERVED_BITS_MASK
#define _swift_abi_ObjCReservedLowBits                                         \
  (unsigned) SWIFT_ABI_DEFAULT_OBJC_NUM_RESERVED_LOW_BITS
#define _swift_BridgeObject_TaggedPointerBits                                  \
  (__swift_uintptr_t) SWIFT_ABI_DEFAULT_BRIDGEOBJECT_TAG_64

#elif defined(__s390x__)

#define _swift_abi_LeastValidPointerValue                                      \
  (__swift_uintptr_t) SWIFT_ABI_DEFAULT_LEAST_VALID_POINTER
#define _swift_abi_SwiftSpareBitsMask                                          \
  (__swift_uintptr_t) SWIFT_ABI_S390X_SWIFT_SPARE_BITS_MASK
#define _swift_abi_ObjCReservedBitsMask                                        \
  (__swift_uintptr_t) SWIFT_ABI_S390X_OBJC_RESERVED_BITS_MASK
#define _swift_abi_ObjCReservedLowBits                                         \
  (unsigned) SWIFT_ABI_S390X_OBJC_NUM_RESERVED_LOW_BITS
#define _swift_BridgeObject_TaggedPointerBits                                  \
  (__swift_uintptr_t) SWIFT_ABI_DEFAULT_BRIDGEOBJECT_TAG_64

#else

#define _swift_abi_LeastValidPointerValue                                      \
  (__swift_uintptr_t) SWIFT_ABI_DEFAULT_LEAST_VALID_POINTER

#if defined(__i386__)
#define _swift_abi_SwiftSpareBitsMask                                          \
  (__swift_uintptr_t) SWIFT_ABI_I386_SWIFT_SPARE_BITS_MASK
#elif defined(__arm__) || defined(_M_ARM) ||                                   \
      (defined(__arm64__) && (__POINTER_WIDTH__ == 32))
#define _swift_abi_SwiftSpareBitsMask                                          \
  (__swift_uintptr_t) SWIFT_ABI_ARM_SWIFT_SPARE_BITS_MASK
#else
#define _swift_abi_SwiftSpareBitsMask                                          \
  (__swift_uintptr_t) SWIFT_ABI_DEFAULT_SWIFT_SPARE_BITS_MASK
#endif

#define _swift_abi_ObjCReservedBitsMask                                        \
  (__swift_uintptr_t) SWIFT_ABI_DEFAULT_OBJC_RESERVED_BITS_MASK
#define _swift_abi_ObjCReservedLowBits                                         \
  (unsigned) SWIFT_ABI_DEFAULT_OBJC_NUM_RESERVED_LOW_BITS

#if __POINTER_WIDTH__ == 64
#define _swift_BridgeObject_TaggedPointerBits                                  \
  (__swift_uintptr_t) SWIFT_ABI_DEFAULT_BRIDGEOBJECT_TAG_64
#else
#define _swift_BridgeObject_TaggedPointerBits                                  \
  (__swift_uintptr_t) SWIFT_ABI_DEFAULT_BRIDGEOBJECT_TAG_32
#endif

#endif

/// Corresponding namespaced decls
#ifdef __cplusplus
namespace heap_object_abi {
static const __swift_uintptr_t LeastValidPointerValue =
    _swift_abi_LeastValidPointerValue;
static const __swift_uintptr_t SwiftSpareBitsMask =
    _swift_abi_SwiftSpareBitsMask;
static const __swift_uintptr_t ObjCReservedBitsMask =
    _swift_abi_ObjCReservedBitsMask;
static const unsigned ObjCReservedLowBits =
    _swift_abi_ObjCReservedLowBits;
static const __swift_uintptr_t BridgeObjectTagBitsMask =
    _swift_BridgeObject_TaggedPointerBits;
} // heap_object_abi
#endif // __cplusplus

#endif // SWIFT_STDLIB_SHIMS_HEAPOBJECT_H
