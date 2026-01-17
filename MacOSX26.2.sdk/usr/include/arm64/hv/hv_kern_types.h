/*
 * Copyright (c) 2019-2024 Apple Inc. All rights reserved.
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

#pragma once

#ifdef __arm64__

#include <stdint.h>
#include <mach/error.h>
#include <mach/message.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

#define err_sub_hypervisor err_sub(0xba5)
#define err_common_hypervisor (err_local | err_sub_hypervisor)

/*!
 * @enum       hv_return_t
 * @abstract   Hypervisor Framework return codes
 * @discussion
 *             These are the supported return codes for the Mach
 *             traps which may be issued by the userspace VMM.
 */
enum {
	HV_SUCCESS             = 0,
	HV_ERROR               = err_common_hypervisor | 0x01, /* (0xfae94001) */
	HV_BUSY                = err_common_hypervisor | 0x02, /* (0xfae94002) */
	HV_BAD_ARGUMENT        = err_common_hypervisor | 0x03, /* (0xfae94003) */
	HV_ILLEGAL_GUEST_STATE = err_common_hypervisor | 0x04, /* (0xfae94004) */
	HV_NO_RESOURCES        = err_common_hypervisor | 0x05, /* (0xfae94005) */
	HV_NO_DEVICE           = err_common_hypervisor | 0x06, /* (0xfae94006) */
	HV_DENIED              = err_common_hypervisor | 0x07, /* (0xfae94007) */
	HV_EXISTS              = err_common_hypervisor | 0x08, /* (0xfae94008) */
	HV_UNSUPPORTED         = err_common_hypervisor | 0x0f  /* (0xfae9400f) */
};

typedef mach_error_t hv_return_t;

/*!
 * @enum       hv_memory_flags_t
 * @abstract   Guest physical memory region permissions for hv_vm_map()
 *             and hv_vm_protect()
 */
enum {
	HV_MEMORY_READ  = (1ull << 0),
	HV_MEMORY_WRITE = (1ull << 1),
	HV_MEMORY_EXEC  = (1ull << 2)
};

typedef uint64_t hv_memory_flags_t;

/*!
 * @typedef hv_data_abort_notification_t
 * @abstract Data abort notification from the kernel.
 * @field context context registered by the VMM @see hv_vm_monitor_data_abort.
 * @field ipa fault IPA within the registered monitored memory range.
 * @field value value written in case of write access. Only least significant
 *              \c access_size bytes are valid, the rest should be ignored.
 * @field access_size access size.
 * @field access_type type of access: HV_MEMORY_READ or HV_MEMORY_WRITE.
 * @discussion Access faults on monitored memory regions get translated into a
 *             mach message by the kernel. The server task holding the receive
 *             right on the memory range port receives data of this type as the
 *             body of the mach message, immediately following the mach message
 *             header.
 *             @see TRAP_HV_VM_MONITOR_DATA_ABORT,
 *             @see hv_vm_monitor_data_abort_t
 */
typedef struct __attribute__((packed)) {
	uint64_t context;
	uint64_t ipa;
	uint64_t value;
	uint32_t access_size;
	uint32_t access_type;
} hv_data_abort_notification_t;

/*!
 * @typedef hv_vm_mem_access_msg_t
 * @field header Mach message header.
 * @field body hv_data_abort_notification_t structure describing
 *             the data abort.
 * @discussion Message sent by the kernel for monitored memory access
 *             fault.
 *             @see TRAP_HV_VM_MONITOR_DATA_ABORT,
 *             @see hv_vm_monitor_data_abort_t
 */
typedef struct {
	mach_msg_header_t header;
	hv_data_abort_notification_t body;
} hv_vm_mem_access_msg_t;

__END_DECLS

#endif
