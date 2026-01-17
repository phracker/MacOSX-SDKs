/*
 * Copyright (c) 2003-2004 Apple Computer, Inc. All rights reserved.
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

#ifndef	LIBKERN_OSMALLOC_h
#define LIBKERN_OSMALLOC_h

#include <sys/cdefs.h>

__BEGIN_DECLS

#include <stdint.h>

typedef struct __OSMallocTag__	*OSMallocTag, *OSMallocTag_t;

#define	 OSMT_DEFAULT	0x00
#define	 OSMT_PAGEABLE	0x01

extern OSMallocTag		OSMalloc_Tagalloc(const char * str, uint32_t flags);

extern void				OSMalloc_Tagfree(OSMallocTag tag);

extern void *			OSMalloc(uint32_t size, OSMallocTag tag);

extern void *			OSMalloc_nowait(uint32_t size, OSMallocTag tag);

extern void *			OSMalloc_noblock(uint32_t size, OSMallocTag tag);

extern void				OSFree(void * addr, uint32_t size, OSMallocTag tag); 

__END_DECLS

#endif	/* LIBKERN_OSMALLOC_h */
