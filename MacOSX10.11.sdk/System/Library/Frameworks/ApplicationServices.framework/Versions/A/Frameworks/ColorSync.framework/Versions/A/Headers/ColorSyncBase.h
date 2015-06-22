/*
 * ColorSync - ColorSyncBase.h
 * Copyright (c)  2008 Apple Inc.
 * All rights reserved.
 */

#ifndef __COLORSYNCBASE__
#define __COLORSYNCBASE__

#include <CoreFoundation/CoreFoundation.h>

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(__CS_HAS_COMPILER_ATTRIBUTE)
    #if defined(__has_attribute)
        #define __CS_HAS_COMPILER_ATTRIBUTE(attribute) __has_attribute(attribute)
    #elif defined(__GNUC__) && __GNUC__ >= 4
        #define __CS_HAS_COMPILER_ATTRIBUTE(attribute) (1)
    #else
        #define __CS_HAS_COMPILER_ATTRIBUTE(attribute) (0)
    #endif
#endif
    
#if !defined(CSEXTERN)
    #if defined(_MSC_VER)
        #if defined(CG_BUILDING_CG)
            #define CSEXTERN __declspec(dllexport) extern
        #else
            #define CSEXTERN __declspec(dllimport) extern
        #endif
    #else
        #define CSEXTERN    __attribute__((visibility("default"))) extern
    #endif
#endif

#if !defined(CSEXPORT)
    #if defined(_MSC_VER)
        #if defined(CG_BUILDING_CG)
            #define CSEXPORT __declspec(dllexport)
        #else
            #define CSEXPORT __declspec(dllimport)
        #endif
    #else
        #define CSEXPORT    __attribute__((visibility("default")))
    #endif
#endif

#if !defined(CSEXTERN_PRIVATE)
    #if __CS_HAS_COMPILER_ATTRIBUTE(visibility)
        #if defined(__cplusplus)
            #define CSEXTERN_PRIVATE extern "C" __attribute__((visibility("hidden")))
        #else
            #define CSEXTERN_PRIVATE extern __attribute__((visibility("hidden")))
        #endif
    #else
        #define CSEXTERN_PRIVATE CSEXTERN
    #endif
#endif /* !defined(CSEXTERN_PRIVATE) */
    
#ifdef __cplusplus
}
#endif

#endif /* __COLORSYNCBASE__ */
