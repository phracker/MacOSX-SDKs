/*  Copyright (c) 2014 Apple, Inc. All rights reserved.                       */

#ifndef __SIMD_INTERNAL_HEADER__
#define __SIMD_INTERNAL_HEADER__

/*  Define __has_attribute for compilers that do not support it.              */
#ifndef __has_attribute
# define __has_attribute(__x) 0
#endif

#if __has_attribute(__ext_vector_type__) && __has_attribute(__overloadable__)
/*  The function of these headers fundamentally depends on the ext_vector_type
 *  and overloadable attributes.  There is no fallback if these attributes
 *  are not supported by your compiler.                                       */
#define __SIMD_REQUIRED_COMPILER_FEATURES__ 1

#if __has_attribute(__always_inline__) && __has_attribute(__const__)
# define __SIMD_INLINE__ __attribute__((__always_inline__,__const__))
# define __SIMD_ATTRIBUTES__ __attribute__((__overloadable__,__always_inline__,__const__))
#else
# define __SIMD_INLINE__ inline
# define __SIMD_ATTRIBUTES__ inline __attribute__((__overloadable__))
#endif
#define __SIMD_OVERLOAD__ __attribute__((__overloadable__))

#include <Availability.h>

#if defined __ARM_NEON__
#include <arm_neon.h>
#elif defined __i386__ || defined __x86_64__
#include <immintrin.h>
#endif

#define __SIMD_ELEMENTWISE_UNARY_2_IN_4(__name,__type) \
    static vector_##__type##2 __SIMD_ATTRIBUTES__ __name(vector_##__type##2 __x) { vector_##__type##4 __x4; __x4.lo = __x; vector_##__type##4 __r4 = __name(__x4); return __r4.lo; }
#define __SIMD_ELEMENTWISE_UNARY_3_IN_4(__name,__type) \
    static vector_##__type##3 __SIMD_ATTRIBUTES__ __name(vector_##__type##3 __x) { vector_##__type##4 __x4 = __x.xyzz; vector_##__type##4 __r4 = __name(__x4); return __r4.xyz; }
#define __SIMD_ELEMENTWISE_UNARY_4_IN_8(__name,__type) \
    static vector_##__type##4 __SIMD_ATTRIBUTES__ __name(vector_##__type##4 __x) { vector_##__type##8 __x8; __x8.lo = __x; vector_##__type##8 __r8 = __name(__x8); return __r8.lo; }
#define __SIMD_ELEMENTWISE_UNARY_8_IN_16(__name,__type) \
    static vector_##__type##8 __SIMD_ATTRIBUTES__ __name(vector_##__type##8 __x) { vector_##__type##16 __x16; __x16.lo = __x; vector_##__type##16 __r16 = __name(__x16); return __r16.lo; }
#define __SIMD_ELEMENTWISE_UNARY_4_IN_2(__name,__type) \
    static vector_##__type##4 __SIMD_ATTRIBUTES__ __name(vector_##__type##4 __x) { vector_##__type##4 __r; __r.lo = __name(__x.lo); __r.hi = __name(__x.hi); return __r; }
#define __SIMD_ELEMENTWISE_UNARY_8_IN_4(__name,__type) \
    static vector_##__type##8 __SIMD_ATTRIBUTES__ __name(vector_##__type##8 __x) { vector_##__type##8 __r; __r.lo = __name(__x.lo); __r.hi = __name(__x.hi); return __r; }
#define __SIMD_ELEMENTWISE_UNARY_16_IN_8(__name,__type) \
    static vector_##__type##16 __SIMD_ATTRIBUTES__ __name(vector_##__type##16 __x) { vector_##__type##16 __r; __r.lo = __name(__x.lo); __r.hi = __name(__x.hi); return __r; }
#define __SIMD_ELEMENTWISE_UNARY_32_IN_16(__name,__type) \
    static vector_##__type##32 __SIMD_ATTRIBUTES__ __name(vector_##__type##32 __x) { vector_##__type##32 __r; __r.lo = __name(__x.lo); __r.hi = __name(__x.hi); return __r; }
#define __SIMD_ELEMENTWISE_UNARY_IN_SCALAR(__name,__type,__count) \
    static vector_##__type##__count __SIMD_ATTRIBUTES__ __name(vector_##__type##__count __x) { vector_##__type##__count __r; for (int i=0; i<__count; ++i) __r[i] = __name(__x[i]); return __r; }

#define __SIMD_ELEMENTWISE_BINARY_2_IN_4(__name,__type) \
    static vector_##__type##2 __SIMD_ATTRIBUTES__ __name(vector_##__type##2 __x, vector_##__type##2 __y) { vector_##__type##4 __x4, __y4; __x4.lo = __x; __y4.lo = __y; vector_##__type##4 __r4 = __name(__x4,__y4); return __r4.lo; }
#define __SIMD_ELEMENTWISE_BINARY_3_IN_4(__name,__type) \
    static vector_##__type##3 __SIMD_ATTRIBUTES__ __name(vector_##__type##3 __x, vector_##__type##3 __y) { vector_##__type##4 __x4 = __x.xyzz; vector_##__type##4 __y4 = __y.xyzz; vector_##__type##4 __r4 = __name(__x4,__y4); return __r4.xyz; }
#define __SIMD_ELEMENTWISE_BINARY_4_IN_8(__name,__type) \
    static vector_##__type##4 __SIMD_ATTRIBUTES__ __name(vector_##__type##4 __x, vector_##__type##4 __y) { vector_##__type##8 __x8, __y8; __x8.lo = __x; __y8.lo = __y; vector_##__type##8 __r8 = __name(__x8,__y8); return __r8.lo; }
#define __SIMD_ELEMENTWISE_BINARY_8_IN_16(__name,__type) \
    static vector_##__type##8 __SIMD_ATTRIBUTES__ __name(vector_##__type##8 __x, vector_##__type##8 __y) { vector_##__type##16 __x16, __y16; __x16.lo = __x; __y16.lo = __y; vector_##__type##16 __r16 = __name(__x16,__y16); return __r16.lo; }
#define __SIMD_ELEMENTWISE_BINARY_4_IN_2(__name,__type) \
    static vector_##__type##4 __SIMD_ATTRIBUTES__ __name(vector_##__type##4 __x, vector_##__type##4 __y) { vector_##__type##4 __r; __r.lo = __name(__x.lo,__y.lo); __r.hi = __name(__x.hi,__y.hi); return __r; }
#define __SIMD_ELEMENTWISE_BINARY_8_IN_4(__name,__type) \
    static vector_##__type##8 __SIMD_ATTRIBUTES__ __name(vector_##__type##8 __x, vector_##__type##8 __y) { vector_##__type##8 __r; __r.lo = __name(__x.lo,__y.lo); __r.hi = __name(__x.hi,__y.hi); return __r; }
#define __SIMD_ELEMENTWISE_BINARY_16_IN_8(__name,__type) \
    static vector_##__type##16 __SIMD_ATTRIBUTES__ __name(vector_##__type##16 __x, vector_##__type##16 __y) { vector_##__type##16 __r; __r.lo = __name(__x.lo,__y.lo); __r.hi = __name(__x.hi,__y.hi); return __r; }
#define __SIMD_ELEMENTWISE_BINARY_32_IN_16(__name,__type) \
    static vector_##__type##32 __SIMD_ATTRIBUTES__ __name(vector_##__type##32 __x, vector_##__type##32 __y) { vector_##__type##32 __r; __r.lo = __name(__x.lo,__y.lo); __r.hi = __name(__x.hi,__y.hi); return __r; }
#define __SIMD_ELEMENTWISE_BINARY_IN_SCALAR(__name,__type,__count) \
    static vector_##__type##__count __SIMD_ATTRIBUTES__ __name(vector_##__type##__count __x, vector_##__type##__count __y) { vector_##__type##__count __r; for (int i=0; i<__count; ++i) __r[i] = __name(__x[i],__y[i]); return __r; }

#else /* Missing required compiler features */
#define __SIMD_REQUIRED_COMPILER_FEATURES__ 0
#endif /* required feature check.  */
#endif /* __SIMD_INTERNAL_HEADER__ */
