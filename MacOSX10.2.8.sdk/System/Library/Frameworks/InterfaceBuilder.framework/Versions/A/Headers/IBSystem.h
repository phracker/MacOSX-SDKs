// ================================================================================
//	**** PUBLIC HEADER ****
//
//	InterfaceBuilder.framework - IBSystem.h 
//	Copyright (c) 1995-2000 Apple Computer, Inc.
//	All rights reserved.
//
// ================================================================================

/* System-dependencies for InterfaceBuilder framework. */

#ifndef _IB_SYSTEM_H
#define _IB_SYSTEM_H

#ifndef IB_EXTERN

#if defined(__MACH__) || defined(SOLARIS)

//
// For MACH or SOLARIS.
//

#ifdef __cplusplus
#define IB_EXTERN	extern "C"
#else
#define IB_EXTERN	extern
#endif

#elif defined(WIN32)

//
// For Windows.
//

#ifndef IB_DLL_EXPORT
#define IB_DLL_EXPORT __declspec(dllimport)
#endif

#ifdef __cplusplus
#define IB_EXTERN	extern "C" IB_DLL_EXPORT
#else
#define IB_EXTERN	IB_DLL_EXPORT extern
#endif

#endif	/* Systems */

#endif	/* IB_EXTERN */

#endif	/* _IB_SYSTEM_H */
