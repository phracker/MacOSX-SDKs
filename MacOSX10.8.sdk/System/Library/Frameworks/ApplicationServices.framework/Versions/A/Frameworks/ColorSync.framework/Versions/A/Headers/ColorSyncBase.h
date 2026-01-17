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
#  if defined(__GNUC__)
#    define CSEXTERN_PRIVATE __private_extern__
#  else /* !defined(__GNUC__) */
#    define CSEXTERN_PRIVATE CSEXTERN
#  endif /* !defined(__GNUC__) */
#endif /* !defined(CSEXTERN_PRIVATE) */

#ifdef __cplusplus
}
#endif

#endif /* __COLORSYNCBASE__ */
