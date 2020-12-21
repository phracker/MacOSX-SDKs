/*
 *  hv_types.h
 *  Hypervisor Framework
 *
 *  Copyright (c) 2020 Apple Inc. All rights reserved.
 */

#ifndef __HYPERVISOR_HV_TYPES__
#define __HYPERVISOR_HV_TYPES__

#ifdef __x86_64__

#include <Hypervisor/hv_base.h>

OS_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 * @enum       hv_capability_t
 * @abstract   Capability IDs
 */
enum {
	HV_CAP_VCPUMAX,
	HV_CAP_ADDRSPACEMAX
};

typedef uint64_t hv_capability_t;

/*!
 * @typedef    hv_vm_space_t
 * @abstract   Type of a guest address space
 */
enum {
	HV_VM_SPACE_DEFAULT = (0ull)
};

typedef unsigned hv_vm_space_t;

/*!
 * @enum       hv_vm_options_t
 * @abstract   Options for hv_vm_create()
 */
enum {
	HV_VM_DEFAULT = (0ull << 0),
	HV_VM_SPECIFY_MITIGATIONS = (1ull << 0),
	HV_VM_MITIGATION_A_ENABLE = (1ull << 1),
	HV_VM_MITIGATION_B_ENABLE = (1ull << 2),
	HV_VM_MITIGATION_C_ENABLE = (1ull << 3),
	HV_VM_MITIGATION_D_ENABLE = (1ull << 4),
	HV_VM_MITIGATION_E_ENABLE = (1ull << 6),
};

typedef uint64_t hv_vm_options_t;

/*!
 * @enum       hv_vcpu_options_t
 * @abstract   Options for hv_vcpu_create()
 */
enum {
	HV_VCPU_DEFAULT = (0ull),
	HV_VCPU_ACCEL_RDPMC = (1ull << 0),
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
 * @enum       hv_msr_flags_t
 * @abstract   Native MSR permissions for hv_vm_enable_managed_msr()
 */
enum {
    HV_MSR_NONE = 0,
    HV_MSR_READ = (1u << 0),
    HV_MSR_WRITE = (1u << 1),
};

typedef uint32_t hv_msr_flags_t;

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

__END_DECLS

OS_ASSUME_NONNULL_END

#endif /* __x86_64__ */

#endif /* __HYPERVISOR_HV_TYPES__ */
