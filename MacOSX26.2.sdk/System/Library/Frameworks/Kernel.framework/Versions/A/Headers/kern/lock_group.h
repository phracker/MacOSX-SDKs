/*
 * Copyright (c) 2018-2021 Apple Computer, Inc. All rights reserved.
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
#ifndef _KERN_LOCK_GROUP_H
#define _KERN_LOCK_GROUP_H

#include <kern/assert.h>
#include <kern/queue.h>
#include <kern/lock_types.h>

__BEGIN_DECLS

/*!
 * @typedef lck_grp_t
 *
 * @abstract
 * The opaque type of a lock group.
 *
 * @discussion
 * A lock group is used to denote a set of locks that serve
 * a similar purpose, and hold an equivalent "rank" in the lock hierarchy.
 *
 * This structure can then provide some statistics and anchor checks
 * in development kernels for an entire family of locks.
 */
typedef struct _lck_grp_        lck_grp_t;
#define LCK_GRP_NULL            ((lck_grp_t *)NULL)

/*!
 * @typedef lck_grp_attr_t
 *
 * @abstract
 * The opaque type for attributes to a group.
 *
 * @discussion
 * A lock group attribute is meant to configure
 * a group, as a group configuration becomes
 * immutable once made.
 */
typedef struct _lck_grp_attr_   lck_grp_attr_t;
#define LCK_GRP_ATTR_NULL       ((lck_grp_attr_t *)NULL)

extern lck_grp_attr_t  *lck_grp_attr_alloc_init(
	void);

extern void             lck_grp_attr_setdefault(
	lck_grp_attr_t         *attr);

extern void             lck_grp_attr_setstat(
	lck_grp_attr_t         *attr);

extern void             lck_grp_attr_free(
	lck_grp_attr_t         *attr);

extern lck_grp_t       *lck_grp_alloc_init(
	const char             *grp_name,
	lck_grp_attr_t         *attr);

extern void             lck_grp_free(
	lck_grp_t              *grp);


__END_DECLS

#endif /* _KERN_LOCK_GROUP_H */
