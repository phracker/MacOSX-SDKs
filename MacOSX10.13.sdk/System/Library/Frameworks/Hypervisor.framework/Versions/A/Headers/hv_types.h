/*
 *  hv_types.h
 *  Hypervisor Framework
 *
 *  Copyright (c) 2013 Apple Inc. All rights reserved.
 */

#ifndef __HYPERVISOR_HV_TYPES__
#define __HYPERVISOR_HV_TYPES__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @enum       hv_vm_options_t
 * @abstract   Options for hv_vm_create()
 */
enum {
	HV_VM_DEFAULT = (0ull << 0)
};

typedef uint64_t hv_vm_options_t;

/*!
 * @enum       hv_vcpu_options_t
 * @abstract   Options for hv_vcpu_create()
 */
enum {
	HV_VCPU_DEFAULT = (0ull)
};

typedef uint64_t hv_vcpu_options_t;

/*!
 * @enum       hv_memory_flags_t
 * @abstract   Guest physical memory region permissions for hv_vm_map()
 *             and hv_vm_protect()
 */
enum {
	HV_MEMORY_READ	= (1ull << 0),
	HV_MEMORY_WRITE	= (1ull << 1),
	HV_MEMORY_EXEC	= (1ull << 2)
};

typedef uint64_t hv_memory_flags_t;

/*!
 * @typedef    hv_vcpu_id_t
 * @abstract   Type of a vCPU ID
 */
typedef unsigned hv_vcpuid_t;

/*!
 * @typedef    hv_uvaddr_t
 * @abstract   Type of a user virtual address
 */
typedef const void* hv_uvaddr_t;

/*!
 * @typedef    hv_gpaddr_t
 * @abstract   Type of a guest physical address
 */
typedef uint64_t hv_gpaddr_t;

#ifdef __cplusplus
}
#endif

#endif /* __HYPERVISOR_HV_TYPES__ */
