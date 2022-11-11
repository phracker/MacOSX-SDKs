/*
 * Copyright (c) 2018 Apple Computer, Inc. All rights reserved.
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
#ifndef _KERN_LOCKSTAT_H
#define _KERN_LOCKSTAT_H

#include <machine/locks.h>
#include <machine/atomic.h>
#include <kern/lock_group.h>

__BEGIN_DECLS
#pragma GCC visibility push(hidden)

/*
 * DTrace lockstat probe definitions
 *
 */

enum lockstat_probe_id {
	/* Spinlocks */
	LS_LCK_SPIN_LOCK_ACQUIRE,
	LS_LCK_SPIN_LOCK_SPIN,
	LS_LCK_SPIN_UNLOCK_RELEASE,

	/*
	 * Mutexes can also have interlock-spin events, which are
	 * unique to our lock implementation.
	 */
	LS_LCK_MTX_LOCK_ACQUIRE,
	LS_LCK_MTX_LOCK_BLOCK,
	LS_LCK_MTX_LOCK_ADAPTIVE_SPIN,
	LS_LCK_MTX_LOCK_SPIN_SPIN,
	LS_LCK_MTX_LOCK_SPIN_ACQUIRE,
	LS_LCK_MTX_LOCK_ILK_SPIN,
	LS_LCK_MTX_TRY_LOCK_ACQUIRE,
	LS_LCK_MTX_TRY_LOCK_SPIN_ACQUIRE,
	LS_LCK_MTX_UNLOCK_RELEASE,

	/*
	 * Provide a parallel set for indirect mutexes
	 */
	LS_LCK_MTX_EXT_LOCK_ACQUIRE,
	LS_LCK_MTX_EXT_LOCK_BLOCK,
	LS_LCK_MTX_EXT_LOCK_SPIN_SPIN,
	LS_LCK_MTX_EXT_LOCK_ADAPTIVE_SPIN,
	LS_LCK_MTX_EXT_LOCK_ILK_SPIN,
	LS_LCK_MTX_EXT_UNLOCK_RELEASE,

	/*
	 * Reader-writer locks support a blocking upgrade primitive, as
	 * well as the possibility of spinning on the interlock.
	 */
	LS_LCK_RW_LOCK_SHARED_ACQUIRE,
	LS_LCK_RW_LOCK_SHARED_BLOCK,
	LS_LCK_RW_LOCK_SHARED_SPIN,

	LS_LCK_RW_LOCK_EXCL_ACQUIRE,
	LS_LCK_RW_LOCK_EXCL_BLOCK,
	LS_LCK_RW_LOCK_EXCL_SPIN,

	LS_LCK_RW_DONE_RELEASE,

	LS_LCK_RW_TRY_LOCK_SHARED_ACQUIRE,
	LS_LCK_RW_TRY_LOCK_SHARED_SPIN,

	LS_LCK_RW_TRY_LOCK_EXCL_ACQUIRE,
	LS_LCK_RW_TRY_LOCK_EXCL_ILK_SPIN,

	LS_LCK_RW_LOCK_SHARED_TO_EXCL_UPGRADE,
	LS_LCK_RW_LOCK_SHARED_TO_EXCL_SPIN,
	LS_LCK_RW_LOCK_SHARED_TO_EXCL_BLOCK,

	LS_LCK_RW_LOCK_EXCL_TO_SHARED_DOWNGRADE,
	LS_LCK_RW_LOCK_EXCL_TO_SHARED_ILK_SPIN,

	/* Ticket lock */
	LS_LCK_TICKET_LOCK_ACQUIRE,
	LS_LCK_TICKET_LOCK_RELEASE,
	LS_LCK_TICKET_LOCK_SPIN,

	LS_NPROBES
};


#pragma GCC visibility pop
__END_DECLS

#endif /* _KERN_LOCKSTAT_H */
