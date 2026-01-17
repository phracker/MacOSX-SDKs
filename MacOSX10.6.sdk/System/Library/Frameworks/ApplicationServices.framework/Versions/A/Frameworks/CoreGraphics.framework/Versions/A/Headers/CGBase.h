/* CoreGraphics - CGBase.h
   Copyright (c) 2000-2009 Apple Inc.
   All rights reserved. */

#ifndef CGBASE_H_
#define CGBASE_H_

#include <stdbool.h>
#include <stddef.h>
#include <float.h>

#if !defined(__WIN32__)
# if defined(_WIN32) || defined(__CYGWIN32__)
#  define __WIN32__ 1
# endif
#endif /* !defined(__WIN32__) */

#if defined(CG_BUILDING_CG)
# define CG_AVAILABLE_STARTING(_mac,_iphone)
# define CG_AVAILABLE_BUT_DEPRECATED(_mac,_macDep,_iphone,_iphoneDep)
#else /* !defined(CG_BUILDING_CG) */
# include <Availability.h>
# define CG_AVAILABLE_STARTING __OSX_AVAILABLE_STARTING
# define CG_AVAILABLE_BUT_DEPRECATED __OSX_AVAILABLE_BUT_DEPRECATED
#endif /* !defined(CG_BUILDING_CG) */

#if !defined(CG_EXTERN)
# if defined(__WIN32__)
#  if defined(CG_BUILDING_CG)
#   if defined(__cplusplus)
#    define CG_EXTERN extern "C" __declspec(dllexport)
#   else /* !defined(__cplusplus) */
#    define CG_EXTERN extern __declspec(dllexport)
#   endif /* !defined(__cplusplus) */
#  else /* !defined(CG_BUILDING_CG) */
#   if defined(__cplusplus)
#    define CG_EXTERN extern "C" __declspec(dllimport) 
#   else /* !defined(__cplusplus) */
#    define CG_EXTERN extern __declspec(dllimport)
#   endif /* !defined(__cplusplus) */
#  endif /* !defined(CG_BUILDING_CG) */
# else /* !defined(__WIN32__) */
#  if defined(__cplusplus)
#   define CG_EXTERN extern "C"
#  else /* !defined(__cplusplus) */
#   define CG_EXTERN extern
#  endif /* !defined(__cplusplus) */
# endif /* !defined(__WIN32__) */
#endif /* !defined(CG_EXTERN) */

#if !defined(CG_LOCAL)
# if defined(__GNUC__)
#  define CG_LOCAL __private_extern__
# else /* !defined(__GNUC__) */
#  define CG_LOCAL CG_EXTERN
# endif /* !defined(__GNUC__) */
#endif /* !defined(CG_LOCAL) */

#if !defined(CG_PRIVATE_EXTERN)
# define CG_PRIVATE_EXTERN CG_LOCAL
#endif

#if !defined(CG_OBSOLETE)
# if defined(__GNUC__)
#  if (__GNUC__ == 3 && __GNUC_MINOR__ >= 1) || __GNUC__ >= 4
#   define CG_OBSOLETE __attribute__((deprecated))
#  else
#   define CG_OBSOLETE
#  endif
# else /* !defined(__GNUC__) */
#  define CG_OBSOLETE
# endif /* !defined(__GNUC__) */
#endif /* !defined(CG_OBSOLETE) */

#if !defined(CG_INLINE)
# if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#  define CG_INLINE static inline
# elif defined(__MWERKS__) || defined(__cplusplus)
#  define CG_INLINE static inline
# elif defined(__GNUC__)
#  define CG_INLINE static __inline__
# elif defined(__WIN32__)
#  define CG_INLINE static __inline
# else
#  define CG_INLINE static    
# endif
#endif /* !defined(CG_INLINE) */

#if !(defined(__GNUC__) || (defined(__MWERKS__) && !defined(__WIN32__)))
# define __attribute__(attribute)
#endif

#if defined(__LP64__) && __LP64__
# define CGFLOAT_TYPE double
# define CGFLOAT_IS_DOUBLE 1
# define CGFLOAT_MIN DBL_MIN
# define CGFLOAT_MAX DBL_MAX
#else /* !defined(__LP64__) || !__LP64__ */
# define CGFLOAT_TYPE float
# define CGFLOAT_IS_DOUBLE 0
# define CGFLOAT_MIN FLT_MIN
# define CGFLOAT_MAX FLT_MAX
#endif /* !defined(__LP64__) || !__LP64__ */

typedef CGFLOAT_TYPE CGFloat;
#define CGFLOAT_DEFINED 1

#endif /* CGBASE_H_ */
