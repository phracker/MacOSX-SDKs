/*
	CoreDataDefines.h
    Core Data
    Copyright (c) 2004-2007 Apple Inc.
	All rights reserved.
*/
#ifndef _COREDATADEFINES_H
#define _COREDATADEFINES_H

#import <AvailabilityMacros.h>


//
//  Platform specific defs for externs
//

//
// For MACH
//

#if defined(__MACH__)

#ifdef __cplusplus
#define COREDATA_EXTERN		extern "C"
#define COREDATA_PRIVATE_EXTERN	__private_extern__
#else
#define COREDATA_EXTERN		extern
#define COREDATA_PRIVATE_EXTERN	__private_extern__
#endif

//
// For Windows
//

#elif defined(WIN32)

#ifndef _NSBUILDING_COREDATA_DLL
#define _NSWINDOWS_DLL_GOOP	__declspec(dllimport)
#else
#define _NSWINDOWS_DLL_GOOP	__declspec(dllexport)
#endif

#ifdef __cplusplus
#define COREDATA_EXTERN		extern "C" _NSWINDOWS_DLL_GOOP
#define COREDATA_PRIVATE_EXTERN	extern
#else
#define COREDATA_EXTERN		_NSWINDOWS_DLL_GOOP extern
#define COREDATA_PRIVATE_EXTERN	extern
#endif

//
//  For Solaris
//

#elif defined(SOLARIS)

#ifdef __cplusplus
#define COREDATA_EXTERN		extern "C"
#define COREDATA_PRIVATE_EXTERN	extern "C"
#else
#define COREDATA_EXTERN		extern
#define COREDATA_PRIVATE_EXTERN	extern
#endif

#endif

//
//  Framework version
//

COREDATA_EXTERN double NSCoreDataVersionNumber;

#define NSCoreDataVersionNumber10_4       46.0
#define NSCoreDataVersionNumber10_4_3     77.0

#endif // _COREDATADEFINES_H
