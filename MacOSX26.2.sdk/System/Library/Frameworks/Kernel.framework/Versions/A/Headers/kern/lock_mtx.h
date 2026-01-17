/*
 * Copyright (c) 2022 Apple Inc. All rights reserved.
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

#ifndef _KERN_LOCK_MTX_H_
#define _KERN_LOCK_MTX_H_

#include <kern/lock_types.h>
#include <kern/lock_group.h>
#include <kern/lock_attr.h>


__BEGIN_DECLS


#define decl_lck_mtx_data(class, name)     class lck_mtx_t name

extern lck_mtx_t        *lck_mtx_alloc_init(
	lck_grp_t               *grp,
	lck_attr_t              *attr);

extern void             lck_mtx_init(
	lck_mtx_t               *lck,
	lck_grp_t               *grp,
	lck_attr_t              *attr);
extern void             lck_mtx_lock(
	lck_mtx_t               *lck);

extern void             lck_mtx_unlock(
	lck_mtx_t               *lck);

extern void             lck_mtx_destroy(
	lck_mtx_t               *lck,
	lck_grp_t               *grp);

extern void             lck_mtx_free(
	lck_mtx_t               *lck,
	lck_grp_t               *grp);

extern wait_result_t    lck_mtx_sleep(
	lck_mtx_t               *lck,
	lck_sleep_action_t      lck_sleep_action,
	event_t                 event,
	wait_interrupt_t        interruptible);

extern wait_result_t    lck_mtx_sleep_deadline(
	lck_mtx_t               *lck,
	lck_sleep_action_t      lck_sleep_action,
	event_t                 event,
	wait_interrupt_t        interruptible,
	uint64_t                deadline);

#define LCK_MTX_ASSERT_OWNED    LCK_ASSERT_OWNED
#define LCK_MTX_ASSERT_NOTOWNED LCK_ASSERT_NOTOWNED

extern void             lck_mtx_assert(
	lck_mtx_t               *lck,
	unsigned                int    type);

#if !LCK_MTX_USE_ARCH
extern void             lck_mtx_assert_owned_spin(
	lck_mtx_t               *lck);
#endif /* !LCK_MTX_USE_ARCH */

#if MACH_ASSERT
#define LCK_MTX_ASSERT(lck, type)       MACH_ASSERT_DO(lck_mtx_assert(lck, type))
#if !LCK_MTX_USE_ARCH
#define LCK_MTX_ASSERT_OWNED_SPIN(lck)  MACH_ASSERT_DO(lck_mtx_assert_owned_spin(lck))
#endif /* !LCK_MTX_USE_ARCH */
#else /* !MACH_ASSERT */
#define LCK_MTX_ASSERT(lck, type)
#if !LCK_MTX_USE_ARCH
#define LCK_MTX_ASSERT_OWNED_SPIN(lck)
#endif /* !LCK_MTX_USE_ARCH */
#endif /* !MACH_ASSERT */

#if DEBUG
#define LCK_MTX_ASSERT_DEBUG(lck, type)      lck_mtx_assert((lck),(type))
#define LCK_MTX_ASSERT_OWNED_SPIN_DEBUG(lck) lck_mtx_assert_owned_spin(lck)
#else /* DEBUG */
#define LCK_MTX_ASSERT_DEBUG(lck, type)
#if !LCK_MTX_USE_ARCH
#define LCK_MTX_ASSERT_OWNED_SPIN_DEBUG(lck)
#endif /* !LCK_MTX_USE_ARCH */
#endif /* DEBUG */


__END_DECLS

#endif /* _KERN_LOCK_RW_H_ */
