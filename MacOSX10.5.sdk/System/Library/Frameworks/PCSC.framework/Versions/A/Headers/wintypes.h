/*
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 *
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

/*
 * MUSCLE SmartCard Development ( http://www.linuxnet.com )
 *
 * Copyright (C) 1999
 *  David Corcoran <corcoran@linuxnet.com>
 *
 * $Id: wintypes.h 2071 2006-06-06 09:20:19Z rousseau $
 */

/**
 * @file
 * @brief This keeps a list of Windows(R) types.
 */

#ifndef __wintypes_h__
#define __wintypes_h__

#ifdef __cplusplus
extern "C"
{
#endif

#if !defined(WIN32)

#include <stdint.h>

#ifndef BYTE
	typedef uint8_t BYTE;
#endif
	typedef uint8_t UCHAR;
	typedef uint8_t *PUCHAR;
	typedef uint16_t USHORT;

#ifndef __COREFOUNDATION_CFPLUGINCOM__
	typedef uint32_t ULONG;
	typedef void *LPVOID;
	typedef int16_t BOOL;
#endif

	typedef uint32_t *PULONG;
	typedef const void *LPCVOID;
	typedef uint32_t DWORD;
	typedef uint32_t *PDWORD;
	typedef uint16_t WORD;
	typedef int32_t LONG;
	typedef int32_t RESPONSECODE;
	typedef const char *LPCSTR;
	typedef const BYTE *LPCBYTE;
	typedef BYTE *LPBYTE;
	typedef DWORD *LPDWORD;
	typedef char *LPSTR;

	/* these types are deprecated but still used by old drivers and applications
	 * You should use LPSTR instead */
	typedef char *LPTSTR
#ifdef __GNUC__
		/* __attribute__ is a GCC only extension */
		__attribute__ ((deprecated))
#endif
		;
	typedef const char *LPCTSTR
#ifdef __GNUC__
		/* __attribute__ is a GCC only extension */
		__attribute__ ((deprecated))
#endif
		;
	typedef char *LPCWSTR
#ifdef __GNUC__
		/* __attribute__ is a GCC only extension */
		__attribute__ ((deprecated))
#endif
		;

#else
#include <windows.h>
#endif

#ifdef __cplusplus
}
#endif

#endif
