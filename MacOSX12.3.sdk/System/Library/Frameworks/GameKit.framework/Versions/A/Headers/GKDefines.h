//
//  GKDefines.h
//  Game Center
//
//  Copyright 2010-2022 Apple Inc. All rights reserved.
//

#ifndef GK_EXTERN
#ifdef __cplusplus
#define GK_EXTERN   extern "C" __attribute__((visibility ("default")))
#else
#define GK_EXTERN   extern __attribute__((visibility ("default")))
#endif
#endif

#ifndef GK_EXTERN_WEAK
#define GK_EXTERN_WEAK  GK_EXTERN __attribute__((weak_import))
#endif

#if !defined(__GK_HAS_COMPILER_ATTRIBUTE)
# if defined(__has_attribute)
#  define __GK_HAS_COMPILER_ATTRIBUTE(attribute) __has_attribute(attribute)
# elif defined(__GNUC__) && __GNUC__ >= 4
#  define __GK_HAS_COMPILER_ATTRIBUTE(attribute) (1)
# else
#  define __GK_HAS_COMPILER_ATTRIBUTE(attribute) (0)
# endif
#endif

#if !defined(GK_API_DEPRECATED)
# if __GK_HAS_COMPILER_ATTRIBUTE(deprecated) && !defined(GK_BUILDING_GK)
#  define GK_API_DEPRECATED(...) API_DEPRECATED(__VA_ARGS__)
# else
#  define GK_API_DEPRECATED(...)
# endif
#endif
