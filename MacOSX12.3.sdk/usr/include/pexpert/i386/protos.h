/*
 * Copyright (c) 2000-2006 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
#ifndef _PEXPERT_I386_PROTOS_H
#define _PEXPERT_I386_PROTOS_H

//------------------------------------------------------------------------
// x86 IN/OUT I/O inline functions.
//
// IN :  inb, inw, inl
//       IN(port)
//
// OUT:  outb, outw, outl
//       OUT(port, data)

typedef unsigned short   i386_ioport_t;

#define __IN(s, u) \
static __inline__ unsigned u \
in##s(i386_ioport_t port) \
{ \
    unsigned u data; \
    asm volatile ( \
	"in" #s " %1,%0" \
	: "=a" (data) \
	: "d" (port)); \
    return (data); \
}

#define __OUT(s, u) \
static __inline__ void \
out##s(i386_ioport_t port, unsigned u data) \
{ \
    asm volatile ( \
	"out" #s " %1,%0" \
	: \
	: "d" (port), "a" (data)); \
}

__IN(b, char)
__IN(w, short)
__IN(l, long)

__OUT(b, char)
__OUT(w, short)
__OUT(l, long)

extern void cninit(void);
extern int  sprintf(char * str, const char * format, ...);

/* ------------------------------------------------------------------------
 * from osfmk/i386/serial_io.h
 */
int switch_to_serial_console(void);
void switch_to_old_console(int);
boolean_t console_is_serial(void);
int serial_init(void);
void serial_putc(char);
int serial_getc(void);


/* ------------------------------------------------------------------------
 * from osfmk/kern/misc_protos.h
 */
void console_write_unbuffered(char);

#endif /* _PEXPERT_I386_PROTOS_H */
