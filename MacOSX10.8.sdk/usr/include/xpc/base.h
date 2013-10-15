/* Copyright (c) 2009-2011 Apple Inc. All rights reserved. */

#ifndef __XPC_BASE_H__
#define __XPC_BASE_H__

__BEGIN_DECLS

#ifndef __XPC_INDIRECT__
#error "Please #include <xpc/xpc.h> instead of this file directly."
#endif /* __XPC_INDIRECT__ */

#pragma mark Attribute Shims
#ifdef __GNUC__
#define XPC_CONSTRUCTOR __attribute__((constructor))
#define XPC_NORETURN __attribute__((__noreturn__))
#define XPC_NOTHROW __attribute__((__nothrow__))
#define XPC_NONNULL1 __attribute__((__nonnull__(1)))
#define XPC_NONNULL2 __attribute__((__nonnull__(2)))
#define XPC_NONNULL3 __attribute__((__nonnull__(3)))
#define XPC_NONNULL4 __attribute__((__nonnull__(4)))
#define XPC_NONNULL5 __attribute__((__nonnull__(5)))
#define XPC_NONNULL6 __attribute__((__nonnull__(6)))
#define XPC_NONNULL7 __attribute__((__nonnull__(7)))
#define XPC_NONNULL_ALL __attribute__((__nonnull__))
#define XPC_SENTINEL __attribute__((__sentinel__))
#define XPC_PURE __attribute__((__pure__))
#define XPC_WARN_RESULT __attribute__((__warn_unused_result__))
#define XPC_MALLOC __attribute__((__malloc__))
#define XPC_UNUSED __attribute__((unused))
#define XPC_USED __attribute__((used))
#define XPC_PACKED __attribute__((__packed__))
#define XPC_PRINTF(m, n)	__attribute__((format(printf, m, n)))
#define XPC_INLINE static __inline__ __attribute__((__always_inline__))
#define XPC_NOINLINE __attribute__((noinline))
#define XPC_NOIMPL __attribute__((unavailable))
#define XPC_EXPORT extern __attribute__((visibility("default")))
#define XPC_NOEXPORT __attribute__((visibility("hidden")))
#define XPC_WEAKIMPORT extern __attribute__((weak_import))
#define XPC_DEBUGGER_EXCL XPC_NOEXPORT XPC_USED
#if __clang__
#define XPC_DEPRECATED(m)	__attribute__((deprecated(m)))
#else
#define XPC_DEPRECATED(m)	__attribute__((deprecated))
#endif /* __clang */
#else /* __GNUC__ */
/*! @parseOnly */
#define XPC_CONSTRUCTOR
/*! @parseOnly */
#define XPC_NORETURN
/*! @parseOnly */
#define XPC_NOTHROW
/*! @parseOnly */
#define XPC_NONNULL1
/*! @parseOnly */
#define XPC_NONNULL2
/*! @parseOnly */
#define XPC_NONNULL3
/*! @parseOnly */
#define XPC_NONNULL4
/*! @parseOnly */
#define XPC_NONNULL5
/*! @parseOnly */
#define XPC_NONNULL6
/*! @parseOnly */
#define XPC_NONNULL7
/*! @parseOnly */
#define XPC_NONNULL(n)
/*! @parseOnly */
#define XPC_NONNULL_ALL
/*! @parseOnly */
#define XPC_SENTINEL
/*! @parseOnly */
#define XPC_PURE
/*! @parseOnly */
#define XPC_WARN_RESULT
/*! @parseOnly */
#define XPC_MALLOC
/*! @parseOnly */
#define XPC_UNUSED
/*! @parseOnly */
#define XPC_PACKED
/*! @parseOnly */
#define XPC_PRINTF(m, n)
/*! @parseOnly */
#define XPC_INLINE static inline
/*! @parseOnly */
#define XPC_NOINLINE
/*! @parseOnly */
#define XPC_NOIMPL
/*! @parseOnly */
#define XPC_EXPORT extern
/*! @parseOnly */
#define XPC_WEAKIMPORT
/*! @parseOnly */
#define XPC_DEPRECATED
#endif /* __GNUC__ */

__END_DECLS

#endif /* __XPC_BASE_H__ */
