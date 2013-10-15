/*
	AppKitDefines.h
	Application Kit
	Copyright (c) 1995-2005, Apple Computer, Inc.
	All rights reserved.
*/
#ifndef _APPKITDEFINES_H
#define _APPKITDEFINES_H

#import <AvailabilityMacros.h>


//
//  Platform specific defs for externs
//

//
// For MACH
//

#if defined(__MACH__)

#ifdef __cplusplus
#define APPKIT_EXTERN		extern "C"
#define APPKIT_PRIVATE_EXTERN	__private_extern__
#else
#define APPKIT_EXTERN		extern
#define APPKIT_PRIVATE_EXTERN	__private_extern__
#endif

//
// For Windows
//

#elif defined(WIN32)

#ifndef _NSBUILDING_APPKIT_DLL
#define _NSWINDOWS_DLL_GOOP	__declspec(dllimport)
#else
#define _NSWINDOWS_DLL_GOOP	__declspec(dllexport)
#endif

#ifdef __cplusplus
#define APPKIT_EXTERN		extern "C" _NSWINDOWS_DLL_GOOP
#define APPKIT_PRIVATE_EXTERN	extern
#else
#define APPKIT_EXTERN		_NSWINDOWS_DLL_GOOP extern
#define APPKIT_PRIVATE_EXTERN	extern
#endif

//
//  For Solaris
//

#elif defined(SOLARIS)

#ifdef __cplusplus
#define APPKIT_EXTERN		extern "C"
#define APPKIT_PRIVATE_EXTERN	extern "C"
#else
#define APPKIT_EXTERN		extern
#define APPKIT_PRIVATE_EXTERN	extern
#endif

#endif

#endif // _APPKITDEFINES_H

