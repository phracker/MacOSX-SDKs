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
/*
 * @OSF_COPYRIGHT@
 */
/*
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988,1987 Carnegie Mellon University
 * All Rights Reserved.
 *
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 *
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 *
 * Carnegie Mellon requests users of this software to return to
 *
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 *
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
/*
 */
/*
 *	File:	vm/vm_kern.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *	Date:	1985
 *
 *	Kernel memory management definitions.
 */

#ifndef _VM_VM_KERN_H_
#define _VM_VM_KERN_H_

#include <mach/mach_types.h>
#include <mach/boolean.h>
#include <mach/kern_return.h>
#include <mach/vm_types.h>


__BEGIN_DECLS


#pragma mark - kernel address obfuscation / hashing for logging

/*!
 * @function vm_kernel_addrhide()
 *
 * @brief
 * Unslides a kernel pointer.
 *
 * @discussion
 * This is exporting the VM_KERNEL_ADDRHIDE() functionality to kernel
 * extensions.
 *
 * @param addr          the kernel address to unslide
 * @param hide_addr     the unslid value of @c addr if it was part of a slid
 *                      region of the kernel.
 *
 *                      0 on release kernels if @c addr is not part of a slid
 *                      region of the kernel.
 *
 *                      @c addr on development kernels if @c addr is not part of
 *                      a slid region of the kernel.
 */
extern void vm_kernel_addrhide(
	vm_offset_t             addr,
	vm_offset_t            *hide_addr);


/*!
 * @function vm_kernel_addrperm_external()
 *
 * @brief
 * Unslides or "permutate" a kernel pointer.
 *
 * @discussion
 * This is exporting the VM_KERNEL_ADDRPERM() functionality to kernel
 * extensions.
 *
 * The level of "hiding" of heap kernel pointers done by this function is
 * insufficient. Using @c vm_kernel_addrhash() is preferred when possible.
 *
 * Note that this function might cause lazy allocation to preserve the floating
 * point register state on Intel and is generally unsafe to call under lock.
 *
 * @param addr          the kernel address to unslide
 * @param perm_addr     the unslid value of @c addr if it was part of a slid
 *                      region of the kernel.
 */
extern void vm_kernel_addrperm_external(
	vm_offset_t             addr,
	vm_offset_t            *perm_addr);


/*!
 * @function vm_kernel_unslide_or_perm_external()
 *
 * @brief
 * Equivalent to vm_kernel_addrperm_external().
 */
extern void vm_kernel_unslide_or_perm_external(
	vm_offset_t             addr,
	vm_offset_t            *perm_addr);


/*!
 * @function vm_kernel_addrhash()
 *
 * @brief
 * Unslides or hashes a kernel pointer.
 *
 * @discussion
 * This is exporting the VM_KERNEL_ADDRHASH() functionality to kernel
 * extensions.
 *
 * @param addr          the kernel address to unslide
 * @returns             the unslid value of @c addr if it was part of a slid
 *                      region of the kernel.
 *
 *                      a hashed value of @c addr otherwise.
 */
extern vm_offset_t vm_kernel_addrhash(
	vm_offset_t             addr);


__END_DECLS

#endif  /* _VM_VM_KERN_H_ */
