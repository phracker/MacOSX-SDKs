/*
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
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
/*
 * @OSF_COPYRIGHT@
 * 
 */
#ifndef	MACH_VM_TYPES_H_
#define MACH_VM_TYPES_H_

#include <mach/port.h>
#include <mach/machine/vm_types.h>

typedef vm_offset_t     	pointer_t;
typedef vm_offset_t     	vm_address_t;
typedef unsigned long long	vm_object_offset_t;


typedef mach_port_t		upl_t;
typedef mach_port_t		vm_map_t;
typedef mach_port_t		vm_named_entry_t;


#define UPL_NULL		((upl_t) 0)
#define VM_MAP_NULL		((vm_map_t) 0)
#define VM_NAMED_ENTRY_NULL	((vm_named_entry_t) 0)

#endif	/* MACH_VM_TYPES_H_ */


