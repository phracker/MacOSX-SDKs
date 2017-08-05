/*
 * ColorSync - ColorSyncBase.h
 * Copyright (c)  2008 Apple Inc.
 * All rights reserved.
 */

#ifndef __COLORSYNCBASE__
#define __COLORSYNCBASE__

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

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

#if !defined(CSLOCAL)
    #if __CS_HAS_COMPILER_ATTRIBUTE(visibility)
        #if defined(__cplusplus)
            #define CSLOCAL extern "C" __attribute__((visibility("hidden")))
        #else
            #define CSLOCAL extern __attribute__((visibility("hidden")))
        #endif
    #else
        #define CSLOCAL CSEXTERN
    #endif
#endif /* !defined(CSLOCAL) */
    
#ifdef __cplusplus
}
#endif

#endif /* __COLORSYNCBASE__ */
