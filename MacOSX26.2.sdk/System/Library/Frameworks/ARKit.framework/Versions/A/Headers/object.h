#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/object.h>)
//
//  object.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//
#ifndef ar_object_h
#define ar_object_h

/**
 By default, all ARKit objects are declared as Objective-C types when building with an
 Objective-C compiler.

 To opt-out of this behavior, add `-DAR_OBJECT_USE_OBJC=0` to your compiler flags.

 @seealso `<os/object.h>`
 */

#import <Availability.h>
#import <os/availability.h>
#import <os/base.h>

#ifndef AR_OBJECT_USE_OBJC
#define AR_OBJECT_USE_OBJC OS_OBJECT_USE_OBJC
#endif // AR_OBJECT_USE_OBJC

#ifdef __OBJC__
// Compiling for ObjC.
#import <Foundation/Foundation.h>
#import <objc/NSObjCRuntime.h>
#else // __OBJC__
// Compiling for C.
#import <stdbool.h>
#import <stdint.h>
#define NS_REQUIRES_NIL_TERMINATION
#endif // __OBJC__

#if defined(__cplusplus)
#define AR_EXTERN extern "C"
#else
#define AR_EXTERN extern
#endif

#if !defined(AR_EXTERN_C_BEGIN) && defined(__cplusplus)
#define AR_EXTERN_C_BEGIN extern "C" {
#define AR_EXTERN_C_END }
#elif !defined(AR_EXTERN_C_BEGIN) && !defined(__cplusplus)
#define AR_EXTERN_C_BEGIN
#define AR_EXTERN_C_END
#endif

#define AR_ASSUME_NONNULL_BEGIN _Pragma("clang assume_nonnull begin")
#define AR_ASSUME_NONNULL_END _Pragma("clang assume_nonnull end")
#define AR_REFINED_FOR_SWIFT OS_REFINED_FOR_SWIFT

#ifndef AR_MT_UNSAFE
#define AR_MT_UNSAFE __attribute__((annotate("AR_MT_UNSAFE")))
#endif

#if AR_OBJECT_USE_OBJC

#define AR_OBJECT_DECL(type) OS_OBJECT_DECL(type)
#define AR_OBJECT_DECL_SUBCLASS(subclass, parentclass) OS_OBJECT_DECL_SUBCLASS(subclass, parentclass)
#define AR_OBJECT_RETURNS_RETAINED OS_OBJECT_RETURNS_RETAINED
#define AR_SWIFT_SENDABLE NS_SWIFT_SENDABLE

#else // AR_OBJECT_USE_OBJC

#define AR_OBJECT_DECL(type) \
    struct type##_s;         \
    typedef struct type##_s *type##_t
#define AR_OBJECT_DECL_SUBCLASS(subclass, parentclass) AR_OBJECT_DECL(subclass)
#define AR_OBJECT_RETURNS_RETAINED

// Copied from Foundation/NSObjCRuntime.h in order to avoid depending on the Foundation module from non-objc code.
#define AR_SWIFT_SENDABLE __attribute__((swift_attr("@Sendable")))

#endif // AR_OBJECT_USE_OBJC

AR_ASSUME_NONNULL_BEGIN
AR_EXTERN_C_BEGIN

/**
 Increment the reference count of an ARKit.framework object.

 @param object ARKit.framework object.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN __SWIFT_UNAVAILABLE_MSG("Can't be used with ARC") void *_Nullable ar_retain(void *_Nullable object) AR_REFINED_FOR_SWIFT;

/**
 Decrement the reference count of an ARKit.framework object.

 @param object ARKit.framework object.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN __SWIFT_UNAVAILABLE_MSG("Can't be used with ARC") void ar_release(void *_Nullable object) AR_REFINED_FOR_SWIFT;

#if AR_OBJECT_USE_OBJC

#undef ar_retain
#undef ar_release
#define ar_retain(object) [(object) retain]
#define ar_release(object) [(object) release]

#endif // AR_OBJECT_USE_OBJC

AR_EXTERN_C_END
AR_ASSUME_NONNULL_END

#endif // ar_object_h
#else
#import <ARKitCore/object.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/object.h>)