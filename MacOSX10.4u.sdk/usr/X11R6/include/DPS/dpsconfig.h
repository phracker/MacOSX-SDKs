/*
 * dpsconfig.h
 *
 * (c) Copyright 1984-1994 Adobe Systems Incorporated.
 * All rights reserved.
 * 
 * Permission to use, copy, modify, distribute, and sublicense this software
 * and its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notices appear in all copies and that
 * both those copyright notices and this permission notice appear in
 * supporting documentation and that the name of Adobe Systems Incorporated
 * not be used in advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.  No trademark license
 * to use the Adobe trademarks is hereby granted.  If the Adobe trademark
 * "Display PostScript"(tm) is used to describe this software, its
 * functionality or for any other purpose, such use shall be limited to a
 * statement that this software works in conjunction with the Display
 * PostScript system.  Proper trademark attribution to reflect Adobe's
 * ownership of the trademark shall be given whenever any such reference to
 * the Display PostScript system is made.
 * 
 * ADOBE MAKES NO REPRESENTATIONS ABOUT THE SUITABILITY OF THE SOFTWARE FOR
 * ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
 * ADOBE DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON- INFRINGEMENT OF THIRD PARTY RIGHTS.  IN NO EVENT SHALL ADOBE BE LIABLE
 * TO YOU OR ANY OTHER PARTY FOR ANY SPECIAL, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE, STRICT LIABILITY OR ANY OTHER ACTION ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.  ADOBE WILL NOT
 * PROVIDE ANY TRAINING OR OTHER SUPPORT FOR THE SOFTWARE.
 * 
 * Adobe, PostScript, and Display PostScript are trademarks of Adobe Systems
 * Incorporated which may be registered in certain jurisdictions
 * 
 * Author:  Adobe Systems Incorporated
 */
/* $XFree86: xc/include/DPS/dpsconfig.h,v 1.7 2003/06/12 14:12:27 eich Exp $ */

#ifndef	DPSCONFIG_H
#define	DPSCONFIG_H

/*
 * IEEEFLOAT is true if the representation of type "float" is the IEEE
 * standard 32-bit floating point format, with byte order as defined
 * by SWAPBITS (below). IEEEFLOAT is false if some other representation
 * is used (or, heaven forbid, IEEE representation with some inconsistent
 * byte order). This determines the conditions under which conversions
 * are required when manipulating external binary representations.
 *
 * IEEEFLOAT should be true (1) for:
 *	mc680x0 series, i80x86 series, IBM R6000, MIPS Rx000 series,
 *	SPARC, Alpha, HPPA
 * IEEEFLOAT should be false (0) for:
 *	VAX
 *
 * For all non-IEEE architectures, the DPS_FORMATNAME macro must agree
 * 	with the floating point format returned by extensions on that
 *	server, if any. 
 */

#ifndef IEEEFLOAT

#ifdef vax
#define IEEEFLOAT 0
#define DPS_FORMATNAME "VAX"
#endif /* vax */

#ifdef MIPSEL
#define IEEEFLOAT 1
#endif /* MIPSEL */

#ifdef MIPSEB
#define IEEEFLOAT 1
#endif /* MIPSEB */

#ifdef sparc
#define IEEEFLOAT 1
#endif /* sparc */

#ifdef mc68000
#define IEEEFLOAT 1
#endif /* mc68000 */

#if defined(_IBMR2) || defined(_POWER)
#define IEEEFLOAT 1
#endif /* _IBMR2 */

#if defined(__alpha) || defined(__alpha__) || \
    defined(__ia64__) || defined(ia64) || \
    defined(__s390x__) || \
    defined(__AMD64__) || defined(AMD64)
#define IEEEFLOAT 1
#endif

#ifdef __i386__
#define IEEEFLOAT 1
#endif /* __i386__ */

#ifndef IEEEFLOAT
#define IEEEFLOAT 1
#endif /* IEEEFLOAT */

#endif /* IEEEFLOAT */

#ifndef DPS_FORMATNAME
#if IEEEFLOAT
#define DPS_FORMATNAME "IEEE"
#else /* IEEEFLOAT */
#define DPS_FORMATNAME UNKNOWN	/* This should raise an error */
#endif /* IEEEFLOAT */
#endif /* DPS_FORMATNAME */

/*
 * SWAPBITS is true on a CPU whose native order is "little-endian", i.e.,
 * the low-order byte of a multiple-byte unit (word, longword) appears
 * at the lowest address in memory. SWAPBITS is false on a "big-endian"
 * CPU, where the high-order byte comes first. This affects the layout
 * of structures and determines whether or not conversions are required
 * when manipulating external binary representations.
 *
 * SWAPBITS should be true (1) for:
 *	Alpha, VAX, i80x86 series, ia64, MIPS little-endian (e.g. DEC version)
 * SWAPBITS should be false (0) for:
 *	mc680x0 series, IBM R6000, MIPS big-endian (e.g. SGI version), SPARC,
 *	HPPA
 */

#ifndef SWAPBITS

#if defined(__alpha) || defined(__alpha__) || \
    defined(__ia64__) || defined(ia64) 
#define SWAPBITS 1
#endif /* __alpha */

#ifdef vax
#define SWAPBITS 1
#endif /* vax */

#ifdef MIPSEL
#define SWAPBITS 1
#endif /* MIPSEL */

#ifdef MIPSEB
#define SWAPBITS 0
#endif /* MIPSEB */

#ifdef sparc
#define SWAPBITS 0
#endif /* sparc */

#ifdef mc68000
#define SWAPBITS 0
#endif /* mc68000 */

#if defined(__s390x__) || defined (__s390__)
#define SWAPBITS 0
#endif /* s390 and s390x */

#if (defined(_IBMR2) || defined(_POWER)) && defined(AIXV3)
#define SWAPBITS 0
#endif /* _IBMR2 */

#ifdef __i386__
#define SWAPBITS 1
#endif /* __i386__ */

#ifndef SWAPBITS
#define SWAPBITS 0
#endif /* SWAPBITS */

#endif /* SWAPBITS */

/* 
 * MIN_POINTER_ALIGN gives the minimum alignment requirements for pointers
 * to structures.  If a pointer to an arbitrary buffer is to be cast to
 * a pointer to a structure, the buffer must be aligned according to
 * MIN_POINTER_ALIGN.  MIN_POINTER_ALIGN must be a power of 2.
 *
 * MIN_POINTER_ALIGN must be 8 on
 *	Alpha, IA-64, hppa64 (aka hppa2.0 in wide mode)
 * MIN_POINTER_ALIGN must be 4 on
 *	VAX, i80x86 series, MIPS, mc680x0 series, IBM R6000, SPARC, HPPA
 */

#ifndef MIN_POINTER_ALIGN
 
#if defined(__alpha) || defined(__alpha__) || \
    defined(__ia64__) || defined(ia64) || \
    defined(__s390x__)
#define MIN_POINTER_ALIGN 8
#endif /* __alpha */

#if defined(__hppa__)
#if defined(__LP64__)
#define MIN_POINTER_ALIGN 8
#else
#define MIN_POINTER_ALIGN 4
#endif
#endif

#ifdef vax
#define MIN_POINTER_ALIGN 4
#endif /* vax */

#ifdef MIPSEL
#define MIN_POINTER_ALIGN 4
#endif /* MIPSEL */

#ifdef MIPSEB
#define MIN_POINTER_ALIGN 4
#endif /* MIPSEB */

#ifdef sparc
#define MIN_POINTER_ALIGN 4
#endif /* sparc */

#ifdef mc68000
#define MIN_POINTER_ALIGN 4
#endif /* mc68000 */

#if defined(_IBMR2) || defined(_POWER)
#define MIN_POINTER_ALIGN 4
#endif /* _IBMR2 */

#ifndef MIN_POINTER_ALIGN
#define MIN_POINTER_ALIGN 4
#endif /* MIN_POINTER_ALIGN */

#endif /* MIN_POINTER_ALIGN */

#endif /* DPSCONFIG_H */
