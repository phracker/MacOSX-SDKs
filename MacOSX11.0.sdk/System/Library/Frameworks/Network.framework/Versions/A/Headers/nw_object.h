//
//  nw_object.h
//  Network
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#ifndef __NW_OBJECT_H__
#define __NW_OBJECT_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <sys/cdefs.h>
#include <os/object.h>
#include <TargetConditionals.h> // TARGET_OS_*

/*
 * By default, nw_objects are declared as Objective-C types when building
 * with an Objective-C compiler. This allows them to participate in ARC, in RR
 * management by the Blocks runtime and in leaks checking by the static
 * analyzer, and enables them to be added to Cocoa collections.
 * See <os/object.h> for details.
 */


#if OS_OBJECT_USE_OBJC
#  define NW_OBJECT_DECL(type) OS_OBJECT_DECL(type)
#else // OS_OBJECT_USE_OBJC
#  define NW_OBJECT_DECL(type)				\
		struct type;						\
		typedef	struct type *type##_t
#endif // OS_OBJECT_USE_OBJC


#if __has_feature(assume_nonnull)
#  define NW_ASSUME_NONNULL_BEGIN _Pragma("clang assume_nonnull begin")
#  define NW_ASSUME_NONNULL_END   _Pragma("clang assume_nonnull end")
#else // assume_nonnull
#  define NW_ASSUME_NONNULL_BEGIN
#  define NW_ASSUME_NONNULL_END
#endif // assume_nonnull

#if __has_feature(nullability_on_arrays)
# define NW_NONNULL_ARRAY _Nonnull
#else // nullability_on_arrays
# define NW_NONNULL_ARRAY
#endif// nullability_on_arrays

#ifndef __has_attribute
#  define __has_attribute(x) 0
#endif // !__has_attribute

#ifndef NW_RETURNS_RETAINED
#  define NW_RETURNS_RETAINED OS_OBJECT_RETURNS_RETAINED
#endif // !NW_RETURNS_RETAINED

#if defined(__OBJC__) && __has_feature(attribute_ns_returns_not_retained)
#  define NW_RETURNS_NOT_RETAINED __attribute__((ns_returns_not_retained))
#else // __OBJC__ && ns_returns_not_retained
#  define NW_RETURNS_NOT_RETAINED
#endif // __OBJC__ && ns_returns_not_retained

#if __has_attribute(noescape)
#define NW_NOESCAPE __attribute__((__noescape__))
#else // noescape
#define NW_NOESCAPE
#endif // noescape

#if __has_attribute(objc_direct)
#define NW_DIRECT __attribute__((objc_direct))
#else // objc_direct
#define NW_DIRECT
#endif // objc_direct

#if defined(__OBJC__) && __has_attribute(ns_consumed)
#  define NW_RELEASES_ARGUMENT __attribute__((__ns_consumed__))
#else // __OBJC__ && ns_consumed
#  define NW_RELEASES_ARGUMENT
#endif // __OBJC__ && ns_consumed

#if defined(__OBJC__) && __has_attribute(objc_precise_lifetime)
#  define NW_VALID_UNTIL_END_OF_SCOPE __attribute__((objc_precise_lifetime))
#else // __OBJC__ && objc_precise_lifetime
#  define NW_VALID_UNTIL_END_OF_SCOPE
#endif // __OBJC__ && objc_precise_lifetime

#if defined(__OBJC__) && __has_attribute(objc_returns_inner_pointer)
#  define NW_RETURNS_INNER_POINTER __attribute__((objc_returns_inner_pointer))
#else // __OBJC__ && objc_returns_inner_pointer
#  define NW_RETURNS_INNER_POINTER
#endif // __OBJC__ && objc_returns_inner_pointer

#ifndef NW_UNSAFE_UNRETAINED
#  if defined(__OBJC__) && OS_OBJECT_USE_OBJC
#	  define NW_UNSAFE_UNRETAINED __unsafe_unretained
#  else // __OBJC__ && OS_OBJECT_USE_OBJC
#	  define NW_UNSAFE_UNRETAINED
#  endif // __OBJC__ && OS_OBJECT_USE_OBJC
#endif // !NW_UNSAFE_UNRETAINED

#ifndef NW_EXTERNALLY_RETAINED
#if defined(__OBJC__) && __has_attribute(objc_externally_retained)
#   define NW_EXTERNALLY_RETAINED              __attribute__((objc_externally_retained))
#   define NW_ASSUME_EXTERNALLY_RETAINED_BEGIN _Pragma("clang attribute NW_ASSUME_EXTERNALLY_RETAINED.push(__attribute__((objc_externally_retained)), apply_to=any(function, block, objc_method))")
#   define NW_ASSUME_EXTERNALLY_RETAINED_END   _Pragma("clang attribute NW_ASSUME_EXTERNALLY_RETAINED.pop")
#else // __OBJC__ && objc_externally_retained
#   define NW_EXTERNALLY_RETAINED
#   define NW_ASSUME_EXTERNALLY_RETAINED_BEGIN
#   define NW_ASSUME_EXTERNALLY_RETAINED_END
#endif // __OBJC__ && objc_externally_retained
#endif // !NW_EXTERNALLY_RETAINED

#ifndef NW_EXPORT
#  define NW_EXPORT __attribute__((visibility("default")))
#endif // !NW_EXPORT

#ifndef NW_EXPORT_PROJECT
#  define NW_EXPORT_PROJECT NW_EXPORT
#endif // !NW_EXPORT

#ifndef NW_NOT_i386_MAC
#  if !TARGET_OS_OSX || !defined(__i386__)
#    define NW_NOT_i386_MAC 1
#  else // !TARGET_OS_OSX || !__i386__
#    define NW_NOT_i386_MAC 0
#  endif // !TARGET_OS_OSX || !__i386__
#endif // NW_NOT_i386_MAC


#if !OS_OBJECT_USE_OBJC_RETAIN_RELEASE

__BEGIN_DECLS

API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void *nw_retain(void *obj);

API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void nw_release(void *obj);

__END_DECLS

#else // !OS_OBJECT_USE_OBJC_RETAIN_RELEASE

#undef nw_retain
#undef nw_release
#define nw_retain(object) [(object) retain]
#define nw_release(object) [(object) release]

#endif // !OS_OBJECT_USE_OBJC_RETAIN_RELEASE


NW_OBJECT_DECL(nw_object);

#endif // __NW_OBJECT_H__
