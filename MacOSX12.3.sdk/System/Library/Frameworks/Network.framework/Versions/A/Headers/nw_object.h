//
//  nw_object.h
//  Network
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
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
#  define NW_OBJECT_DECL_SUBCLASS(type, super) OS_OBJECT_DECL_SUBCLASS(type, super)
#else // OS_OBJECT_USE_OBJC
#  define NW_OBJECT_DECL(type)					\
		struct type;							\
		typedef	struct type *type##_t
#  define NW_OBJECT_DECL_SUBCLASS(type, super)	\
		typedef super##_t type##_t
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

#if __has_attribute(swift_async)
#  define NW_SWIFT_DISABLE_ASYNC __attribute__((swift_async(none)))
#else // __has_attribute(swift_async)
#  define NW_SWIFT_DISABLE_ASYNC
#endif // __has_attribute(swift_async)

#if defined(__OBJC__) && OS_OBJECT_USE_OBJC && __has_feature(attribute_ns_returns_not_retained)
#  define NW_RETURNS_NOT_RETAINED __attribute__((ns_returns_not_retained))
#else // __OBJC__ && OS_OBJECT_USE_OBJC && ns_returns_not_retained
#  define NW_RETURNS_NOT_RETAINED
#endif // __OBJC__ && OS_OBJECT_USE_OBJC && ns_returns_not_retained

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

#if __has_attribute(objc_direct_members)
#define NW_DIRECT_MEMBERS __attribute__((objc_direct_members))
#else // objc_direct_members
#define NW_DIRECT_MEMBERS
#endif // objc_direct_members

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
#if defined(__OBJC__) && __has_feature(objc_arc) && __has_attribute(objc_externally_retained)
#   define NW_EXTERNALLY_RETAINED              __attribute__((objc_externally_retained))
#   define NW_ASSUME_EXTERNALLY_RETAINED_BEGIN _Pragma("clang attribute NW_ASSUME_EXTERNALLY_RETAINED.push(__attribute__((objc_externally_retained)), apply_to=any(function, block, objc_method))")
#   define NW_ASSUME_EXTERNALLY_RETAINED_END   _Pragma("clang attribute NW_ASSUME_EXTERNALLY_RETAINED.pop")
#else // __OBJC__ && objc_arc && objc_externally_retained
#   define NW_EXTERNALLY_RETAINED
#   define NW_ASSUME_EXTERNALLY_RETAINED_BEGIN
#   define NW_ASSUME_EXTERNALLY_RETAINED_END
#endif // __OBJC__ && objc_arc && objc_externally_retained
#endif // !NW_EXTERNALLY_RETAINED

#ifndef NW_EXPORT_PROJECT
#  define NW_EXPORT_PROJECT __attribute__((visibility("default")))
#endif // !NW_EXPORT_PROJECT

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

#ifndef NW_ENUM
#if __has_attribute(enum_extensibility)
#define __NW_ENUM_ATTRIBUTES __attribute__((enum_extensibility(open)))
#else // __has_attribute(enum_extensibility)
#define __NW_ENUM_ATTRIBUTES
#endif // __has_attribute(enum_extensibility)

#define __NW_ENUM_GET_MACRO(_1, _2, NAME, ...) NAME
#if (defined(__cplusplus) && __cplusplus >= 201103L && (__has_extension(cxx_strong_enums) || __has_feature(objc_fixed_enum))) || (!defined(__cplusplus) && __has_feature(objc_fixed_enum))
#define __NW_NAMED_ENUM(_type, _name)     enum __NW_ENUM_ATTRIBUTES _name : _type _name; enum _name : _type
#define __NW_ANON_ENUM(_type)             enum __NW_ENUM_ATTRIBUTES : _type
#else // (defined(__cplusplus) && __cplusplus >= 201103L && (__has_extension(cxx_strong_enums) || __has_feature(objc_fixed_enum))) || (!defined(__cplusplus) && __has_feature(objc_fixed_enum))
#define __NW_NAMED_ENUM(_type, _name) _type _name; enum
#define __NW_ANON_ENUM(_type) enum
#endif // (defined(__cplusplus) && __cplusplus >= 201103L && (__has_extension(cxx_strong_enums) || __has_feature(objc_fixed_enum))) || (!defined(__cplusplus) && __has_feature(objc_fixed_enum))
#define NW_ENUM(...) __NW_ENUM_GET_MACRO(__VA_ARGS__, __NW_NAMED_ENUM, __NW_ANON_ENUM, )(__VA_ARGS__)
#endif // NW_ENUM


NW_OBJECT_DECL(nw_object);

#endif // __NW_OBJECT_H__
