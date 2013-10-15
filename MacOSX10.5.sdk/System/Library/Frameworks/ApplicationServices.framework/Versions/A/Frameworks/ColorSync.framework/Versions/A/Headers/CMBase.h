/*
     File:       ColorSync/CMBase.h
 
     Contains:   ColorSync basic defines
 
     Copyright:  2000-2005 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult http://developer.apple.com/bugreporter/
 
*/


#ifndef __CMBASE__
#define __CMBASE__

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

#ifdef __cplusplus
}
#endif

#endif /* __CMBASE__ */

