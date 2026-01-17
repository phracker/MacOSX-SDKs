// EODefines.h
// Copyright (c) 1996, 1998 Apple Computer, Inc.
// All rights reserved.
//
//
//  Platform specific defs for externs
//

#ifndef _EOMODELERDEFINES_H
#define _EOMODELERDEFINES_H

//
// For MACH
//

#if defined(__MACH__)

#ifdef __cplusplus
   // This isnt extern "C" because the compiler will not allow this if it has
   // seen an extern "Objective-C"
#  define EOMODELER_EXTERN		extern
#  define PRIVATE_EXTERN		__private_extern__
#else
#  define EOMODELER_EXTERN		extern
#  define PRIVATE_EXTERN		__private_extern__
#endif

#define EOMODELER_EXTERN_IMP	PUBLIC_EXTERN
#define PRIVATE_EXTERN_IMP	PRIVATE_EXTERN


//
// For Windows
//

#elif defined(WIN32)

#ifdef __cplusplus
#  ifndef _NSBUILDING_EOMODELER_DLL
#    define EOMODELER_EXTERN		__declspec(dllimport) extern "C"
#  else
#    define EOMODELER_EXTERN		extern "C"
#  endif
#  define EOMODELER_PRIVATE_EXTERN		extern "C"
#else
#  ifndef _NSBUILDING_EOMODELER_DLL
#    define EOMODELER_EXTERN		__declspec(dllimport) extern
#  else
#    define EOMODELER_EXTERN		extern
#  endif
#    define EOMODELER_PRIVATE_EXTERN		extern
#endif

#define EOMODELER_EXTERN_IMP	PUBLIC_EXTERN
#define EOMODELER_PRIVATE_EXTERN_IMP	PRIVATE_EXTERN


//
//  For Solaris
//

#elif defined(__svr4__)

#ifdef __cplusplus
#  define EOMODELER_EXTERN		extern "C"
#  define EOMODELER_PRIVATE_EXTERN		extern "C"
#else
#  define EOMODELER_EXTERN		extern
#  define EOMODELER_PRIVATE_EXTERN		extern
#endif

#define EOMODELER_EXTERN_IMP	EOMODELER_EXTERN
#define EOMODELER_PRIVATE_EXTERN_IMP	PRIVATE_EXTERN

#elif defined(hpux)

#ifdef __cplusplus
#  define EOMODELER_EXTERN		extern "C"
#  define EOMODELER_PRIVATE_EXTERN		extern "C"
#else
#  define EOMODELER_EXTERN		extern
#  define EOMODELER_PRIVATE_EXTERN		extern
#endif

#define EOMODELER_EXTERN_IMP	EOMODELER_EXTERN
#define EOMODELER_PRIVATE_EXTERN_IMP	PRIVATE_EXTERN

#else

#error Unknown platform.

#endif

#endif // _EOMODELERDEFINES_H

