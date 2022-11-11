/*
 * Copyright (c) 2008 Apple Inc. All rights reserved.
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
#ifndef _KEXT_ALLOC_H_
#define _KEXT_ALLOC_H_

#include <mach/kern_return.h>
#include <mach/vm_types.h>

__BEGIN_DECLS

vm_offset_t get_address_from_kext_map(vm_size_t fsize);

void kext_alloc_init(void);

kern_return_t kext_alloc(vm_offset_t *addr, vm_size_t size, boolean_t fixed);

void kext_free(vm_offset_t addr, vm_size_t size);

kern_return_t kext_receipt(void **addrp, size_t *sizep);

kern_return_t kext_receipt_set_queried(void);

__END_DECLS

#endif /* _KEXT_ALLOC_H_ */
