/*
 * Copyright (c) 2003-2005 Apple Computer, Inc. All rights reserved.
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

#ifndef _KERN_LOCKS_H_
#define _KERN_LOCKS_H_

#include	<sys/cdefs.h>
#include	<sys/appleapiopts.h>
#include	<mach/boolean.h>
#include	<mach/mach_types.h>
#include	<kern/kern_types.h>
#include	<machine/locks.h>


typedef	unsigned int		lck_sleep_action_t;

#define	LCK_SLEEP_DEFAULT	0x00	/* Release the lock while waiting for the event, then reclaim */
									/* RW locks are returned in the same mode */
#define	LCK_SLEEP_UNLOCK	0x01	/* Release the lock and return unheld */
#define	LCK_SLEEP_SHARED	0x02	/* Reclaim the lock in shared mode (RW only) */
#define	LCK_SLEEP_EXCLUSIVE	0x04	/* Reclaim the lock in exclusive mode (RW only) */

#define	LCK_SLEEP_MASK		0x07	/* Valid actions */

typedef struct __lck_grp__ lck_grp_t;

typedef struct __lck_grp_attr__ lck_grp_attr_t;

#define LCK_GRP_ATTR_NULL	(lck_grp_attr_t *)0

__BEGIN_DECLS

extern	lck_grp_attr_t	*lck_grp_attr_alloc_init(
									void);

extern	void			lck_grp_attr_setdefault(
									lck_grp_attr_t	*attr);

extern	void			lck_grp_attr_setstat(
									lck_grp_attr_t  *attr);

extern	void			lck_grp_attr_free(
									lck_grp_attr_t	*attr);

extern	lck_grp_t		*lck_grp_alloc_init(
									const char*		grp_name,
									lck_grp_attr_t	*attr);

__END_DECLS


__BEGIN_DECLS

extern void				lck_grp_free(
									lck_grp_t		*grp);

__END_DECLS

typedef struct __lck_attr__ lck_attr_t;

#define LCK_ATTR_NULL (lck_attr_t *)0

__BEGIN_DECLS

extern	lck_attr_t		*lck_attr_alloc_init(
									void);

extern	void			lck_attr_setdefault(
									lck_attr_t		*attr);

extern	void			lck_attr_setdebug(
									lck_attr_t		*attr);


extern	void			lck_attr_free(
									lck_attr_t		*attr);

#define decl_lck_spin_data(class,name)     class lck_spin_t name;

extern lck_spin_t		*lck_spin_alloc_init(
									lck_grp_t		*grp,
									lck_attr_t		*attr);

extern void				lck_spin_init(
									lck_spin_t		*lck, 
									lck_grp_t		*grp,
									lck_attr_t		*attr);

extern void				lck_spin_lock(
									lck_spin_t		*lck);

extern void				lck_spin_unlock(
									lck_spin_t		*lck);

extern void				lck_spin_destroy(
									lck_spin_t		*lck,
									lck_grp_t		*grp);

extern void				lck_spin_free(
									lck_spin_t		*lck,
									lck_grp_t		*grp);

extern wait_result_t	lck_spin_sleep(
									lck_spin_t			*lck,
									lck_sleep_action_t	lck_sleep_action,
									event_t				event,
									wait_interrupt_t	interruptible);

extern wait_result_t	lck_spin_sleep_deadline(
									lck_spin_t			*lck,
									lck_sleep_action_t	lck_sleep_action,
									event_t				event,
									wait_interrupt_t	interruptible,
									uint64_t			deadline);



#define decl_lck_mtx_data(class,name)     class lck_mtx_t name;

extern lck_mtx_t		*lck_mtx_alloc_init(
									lck_grp_t		*grp,
									lck_attr_t		*attr);

extern void				lck_mtx_init(
									lck_mtx_t		*lck, 
									lck_grp_t		*grp,
									lck_attr_t		*attr);

extern void				lck_mtx_lock(
									lck_mtx_t		*lck);

extern void				lck_mtx_unlock(
									lck_mtx_t		*lck);

extern void				lck_mtx_destroy(
									lck_mtx_t		*lck,
									lck_grp_t		*grp);

extern void				lck_mtx_free(
									lck_mtx_t		*lck,
									lck_grp_t		*grp);

extern wait_result_t	lck_mtx_sleep(
									lck_mtx_t			*lck,
									lck_sleep_action_t	lck_sleep_action,
									event_t				event,
									wait_interrupt_t	interruptible);

extern wait_result_t	lck_mtx_sleep_deadline(
									lck_mtx_t			*lck,
									lck_sleep_action_t	lck_sleep_action,
									event_t				event,
									wait_interrupt_t	interruptible,
									uint64_t			deadline);


extern void				lck_mtx_assert(
									lck_mtx_t		*lck,
									unsigned int	type);

__END_DECLS

#define	LCK_MTX_ASSERT_OWNED	0x01
#define	LCK_MTX_ASSERT_NOTOWNED	0x02


#define decl_lck_rw_data(class,name)     class lck_rw_t name;

typedef unsigned int	 lck_rw_type_t;

#define	LCK_RW_TYPE_SHARED			0x01
#define	LCK_RW_TYPE_EXCLUSIVE		0x02

__BEGIN_DECLS

extern lck_rw_t			*lck_rw_alloc_init(
									lck_grp_t		*grp,
									lck_attr_t		*attr);

extern void				lck_rw_init(
									lck_rw_t		*lck, 
									lck_grp_t		*grp,
									lck_attr_t		*attr);

extern void				lck_rw_lock(
									lck_rw_t		*lck,
									lck_rw_type_t	lck_rw_type);

extern void				lck_rw_unlock(
									lck_rw_t		*lck,
									lck_rw_type_t	lck_rw_type);

extern void				lck_rw_lock_shared(
									lck_rw_t		*lck);

extern void				lck_rw_unlock_shared(
									lck_rw_t		*lck);

extern void				lck_rw_lock_exclusive(
									lck_rw_t		*lck);

extern void				lck_rw_unlock_exclusive(
									lck_rw_t		*lck);


extern void				lck_rw_destroy(
									lck_rw_t		*lck,
									lck_grp_t		*grp);

extern void				lck_rw_free(
									lck_rw_t		*lck,
									lck_grp_t		*grp);

extern wait_result_t	lck_rw_sleep(
									lck_rw_t			*lck,
									lck_sleep_action_t	lck_sleep_action,
									event_t				event,
									wait_interrupt_t	interruptible);

extern wait_result_t	lck_rw_sleep_deadline(
									lck_rw_t			*lck,
									lck_sleep_action_t	lck_sleep_action,
									event_t				event,
									wait_interrupt_t	interruptible,
									uint64_t			deadline);


__END_DECLS

#endif /* _KERN_LOCKS_H_ */
