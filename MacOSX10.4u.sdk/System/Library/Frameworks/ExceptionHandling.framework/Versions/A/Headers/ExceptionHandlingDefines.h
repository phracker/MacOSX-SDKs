/*
	ExceptionHandlingDefines.h
	Exception Handling
	Copyright (c) 1998, Apple Computer, Inc.
	All rights reserved.
*/

#ifndef _EXCEPTIONHANDLINGDEFINES_H
#define _EXCEPTIONHANDLINGDEFINES_H

#if defined(__WIN32__)
    #undef EXCEPTIONHANDLING_EXPORT
    #if defined(NSBUILDINGEXCEPTIONHANDLING)
	#define EXCEPTIONHANDLING_EXPORT __declspec(dllexport) extern
    #else
	#define EXCEPTIONHANDLING_EXPORT __declspec(dllimport) extern
    #endif
    #if !defined(EXCEPTIONHANDLING_IMPORT)
	#define EXCEPTIONHANDLING_IMPORT __declspec(dllimport) extern
    #endif
#endif

#if !defined(EXCEPTIONHANDLING_EXPORT)
    #define EXCEPTIONHANDLING_EXPORT extern
#endif

#if !defined(EXCEPTIONHANDLING_IMPORT)
    #define EXCEPTIONHANDLING_IMPORT extern
#endif

#endif // _EXCEPTIONHANDLINGDEFINES_H