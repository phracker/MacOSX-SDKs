/*
 * Copyright (c) 2000-2007 Apple Inc. All rights reserved.
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
/* Copyright (c) 1995 NeXT Computer, Inc. All Rights Reserved */
/*-
 * Copyright (c) 1982, 1988, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)systm.h	8.7 (Berkeley) 3/29/95
 */

/*
 * The `securelevel' variable controls the security level of the system.
 * It can only be decreased by process 1 (/sbin/init).
 *
 * Security levels are as follows:
 *   -1	permannently insecure mode - always run system in level 0 mode.
 *    0	insecure mode - immutable and append-only flags make be turned off.
 *	All devices may be read or written subject to permission modes.
 *    1	secure mode - immutable and append-only flags may not be changed;
 *	raw disks of mounted filesystems, /dev/mem, and /dev/kmem are
 *	read-only.
 *    2	highly secure mode - same as (1) plus raw disks are always
 *	read-only whether mounted or not. This level precludes tampering
 *	with filesystems by unmounting them, but also inhibits running
 *	newfs while the system is secured.
 *
 * In normal operation, the system runs in level 0 mode while single user
 * and in level 1 mode while multiuser. If level 2 mode is desired while
 * running multiuser, it can be set in the multiuser startup script
 * (/etc/rc.local) using sysctl(1). If it is desired to run the system
 * in level 0 mode while multiuser, initialize the variable securelevel
 * in /sys/kern/kern_sysctl.c to -1. Note that it is NOT initialized to
 * zero as that would allow the vmunix binary to be patched to -1.
 * Without initialization, securelevel loads in the BSS area which only
 * comes into existence when the kernel is loaded and hence cannot be
 * patched by a stalking hacker.
 */

#ifndef _SYS_SYSTM_H_
#define _SYS_SYSTM_H_

#include <sys/appleapiopts.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/malloc.h>
#include <sys/proc.h>
__BEGIN_DECLS
#include <libkern/libkern.h>
#include <kern/thread.h>
#include <kern/debug.h>
__END_DECLS



#define SYSINIT(a, b, c, d, e)
#define MALLOC_DEFINE(a, b, c)

#define getenv_int(a, b) (*b = 0)
#define KASSERT(exp, msg)
/*
 * General function declarations.
 */
__BEGIN_DECLS



int     nullop(void);
int     nulldev(void);
int     enoioctl(void);
int     enosys(void);
int     enxio(void);
int     eopnotsupp(void);
void    *hashinit(int count, int type, u_long *hashmask);
void    hashdestroy(void *, int type, u_long hashmask);
void    ovbcopy(const void *from, void *to, size_t len);
int     fubyte(user_addr_t addr);
int     fuibyte(user_addr_t addr);
int     subyte(user_addr_t addr, int byte);
int     suibyte(user_addr_t addr, int byte);
long   fuword(user_addr_t addr);
long   fuiword(user_addr_t addr);
int    suword(user_addr_t addr, long word);
int    suiword(user_addr_t addr, long word);
#define fusize(_a)      ((user_size_t)fulong(_a))
#define susize(_a, _s)  sulong((_a), (_s))
#define fuptr(a)        ((user_addr_t)fulong(_a)
#define suptr(_a, _p)   sulong((_a), (_p))
int     useracc(user_addr_t addr, user_size_t len, int prot);
typedef void (*timeout_fcn_t)(void *);
void    bsd_timeout(void (*)(void *), void *arg, struct timespec * ts);
void    bsd_untimeout(void (*)(void *), void *arg);
void    set_fsblocksize(struct vnode *);
uint64_t tvtoabstime(struct timeval *);
uint64_t tstoabstime(struct timespec *);
void    *throttle_info_create(void);
void    throttle_info_mount_ref(mount_t mp, void * throttle_info);
void    throttle_info_mount_rel(mount_t mp);
void    throttle_info_release(void *throttle_info);
void    throttle_info_update(void *throttle_info, int flags);
uint32_t throttle_lowpri_io(int sleep_amount);
/* returns TRUE if the throttle_lowpri_io called with the same sleep_amount would've slept */
int     throttle_lowpri_io_will_be_throttled(int sleep_amount);
void    throttle_set_thread_io_policy(int policy);
int     throttle_get_thread_effective_io_policy(void);
int     throttle_thread_io_tier_above_metadata(void);

typedef struct __throttle_info_handle *throttle_info_handle_t;
int     throttle_info_ref_by_mask(uint64_t throttle_mask, throttle_info_handle_t *throttle_info_handle);
void    throttle_info_rel_by_mask(throttle_info_handle_t throttle_info_handle);
void    throttle_info_update_by_mask(void *throttle_info_handle, int flags);
void    throttle_info_disable_throttle(int devno, boolean_t isfusion);
/*
 * 'throttle_info_handle' acquired via 'throttle_info_ref_by_mask'
 * 'policy' should be specified as either IOPOL_UTILITY or IPOL_THROTTLE,
 * all other values will be treated as IOPOL_NORMAL (i.e. no throttling)
 */
int     throttle_info_io_will_be_throttled(void *throttle_info_handle, int policy);




__END_DECLS

#endif /* !_SYS_SYSTM_H_ */
