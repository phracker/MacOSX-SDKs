/*
 * Copyright (c) 2003 Apple Computer, Inc. All rights reserved.
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

#ifndef _I386_CPU_CAPABILITIES_H
#define _I386_CPU_CAPABILITIES_H

/* Sadly, some clients of this interface misspell __APPLE_API_PRIVATE.
 * To avoid breaking them, we accept the incorrect _APPLE_API_PRIVATE.
 */
#ifdef	_APPLE_API_PRIVATE
#ifndef __APPLE_API_PRIVATE
#define	__APPLE_API_PRIVATE
#endif	/* __APPLE_API_PRIVATE */
#endif	/* _APPLE_API_PRIVATE */

#ifndef __APPLE_API_PRIVATE
#error	cpu_capabilities.h is for Apple Internal use only
#else	/* __APPLE_API_PRIVATE */

/* _cpu_capabilities
 *
 * This is the authoritative way to determine from user mode what
 * implementation-specific processor features are available.
 * This API only supported for Apple internal use.
 * 
 */

#ifndef	__ASSEMBLER__
 
extern int _cpu_capabilities;
 
#endif

/* Bit definitions for _cpu_capabilities: */

#endif /* __APPLE_API_PRIVATE */
#endif /* _I386_CPU_CAPABILITIES_H */
