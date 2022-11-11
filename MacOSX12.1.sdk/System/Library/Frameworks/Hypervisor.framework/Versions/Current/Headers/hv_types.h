/*
 *  hv_types.h
 *  Hypervisor Framework
 *
 *  Copyright (c) 2021 Apple Inc. All rights reserved.
 */

#ifndef __HYPERVISOR_HV_TYPES__
#define __HYPERVISOR_HV_TYPES__

#ifdef __x86_64__

#include <Hypervisor/hv_base.h>
#include <Kernel/kern/hv_io_notifier.h>

#include <mach/message.h>

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
    HV_VM_ACCEL_APIC = UINT64_C(1) << 10,
};

typedef uint64_t hv_vm_options_t;

/*!
 * @enum       hv_vcpu_options_t
 * @abstract   Options for hv_vcpu_create()
 */
enum {
    HV_VCPU_DEFAULT      = (0ull),
    HV_VCPU_ACCEL_RDPMC  = (1ull << 0),
    HV_VCPU_TSC_RELATIVE = (1ull << 1),
};

typedef uint64_t hv_vcpu_options_t;

/*!
 * @enum       hv_memory_flags_t
 * @abstract   Guest physical memory region permissions for hv_vm_map()
 *             and hv_vm_protect()
 */
enum {
    HV_MEMORY_READ          = (1ull << 0),
    HV_MEMORY_WRITE         = (1ull << 1),
    HV_MEMORY_EXEC          = (1ull << 2),
    HV_MEMORY_UEXEC         = (1ull << 3),
    HV_MEMORY_MAXPROT       = (1ull << 4),
    HV_MEMORY_MAXPROT_READ  = (1ull << 5),
    HV_MEMORY_MAXPROT_WRITE = (1ull << 6),
    HV_MEMORY_MAXPROT_EXEC  = (1ull << 7),
    HV_MEMORY_MAXPROT_UEXEC = (1ull << 8)
};

typedef uint64_t hv_memory_flags_t;

/*!
 * @enum       hv_msr_flags_t
 * @abstract   Native MSR permissions for hv_vm_enable_managed_msr()
 */
enum {
    HV_MSR_NONE  = 0,
    HV_MSR_READ  = (1u << 0),
    HV_MSR_WRITE = (1u << 1),
};

typedef uint32_t hv_msr_flags_t;

/*!
 * @enum       hv_ion_flags_t
 * @abstract   Options for hv_vcpu_add_io_notifier()
 * @constant   HV_ION_ANY_VALUE    Match on any value
 * @constant   HV_ION_ANY_SIZE     Match on any size
 * @constant   HV_ION_EXIT_FULL    Return if notification queue is full
 */
enum {
    HV_ION_NONE      = kHV_ION_NONE,
    HV_ION_ANY_VALUE = kHV_ION_ANY_VALUE,
    HV_ION_ANY_SIZE  = kHV_ION_ANY_SIZE,
    HV_ION_EXIT_FULL = kHV_ION_EXIT_FULL,
};

typedef uint32_t hv_ion_flags_t;

/*!
 * @typedef    hv_ion_message_t
 * @abstract   Mach message sent when an IO notifier fires
 * @field      header  Mach message header
 * @field      addr    Address of the IO write
 * @field      size    Size of the value written
 * @field      value   Value written
 * @field      trailer Mach message trailer
 */
typedef struct {
	mach_msg_header_t header;
	uint64_t addr;
	uint64_t size;
	uint64_t value;
	mach_msg_trailer_t trailer;
} hv_ion_message_t;

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

/*!
 * @enum       hv_vm_exitinfo_t
 * @abstract   Type of additional VM exit information available
 */
OS_ENUM(hv_vm_exitinfo, uint32_t,
    HV_VM_EXITINFO_VMX = 1,
    HV_VM_EXITINFO_INIT_AP = 2,
    HV_VM_EXITINFO_STARTUP_AP = 3,
    HV_VM_EXITINFO_IOAPIC_EOI = 4,
    HV_VM_EXITINFO_INJECT_EXCP = 5,
    HV_VM_EXITINFO_SMI = 6,
    HV_VM_EXITINFO_APIC_ACCESS_READ = 7,
);

/*!
 * @enum       hv_apic_ctrl_t
 * @abstract   APIC behavior and extensions
 */
OS_ENUM(hv_apic_ctrl, uint64_t,
    HV_APIC_CTRL_DEFAULT = 0,
    HV_APIC_CTRL_EOI_ICR_TPR = UINT64_C(1) << 0,
    HV_APIC_CTRL_GUEST_IDLE = UINT64_C(1) << 1,
    HV_APIC_CTRL_NO_TIMER = UINT64_C(1) << 2,
    HV_APIC_CTRL_IOAPIC_EOI = UINT64_C(1) << 3,
);

/*!
 * @enum       hv_apic_lvt_flavor_t
 * @abstract   APIC local vector table types
 */
OS_ENUM(hv_apic_lvt_flavor, uint32_t,
    HV_APIC_LVT_FLAVOR_TIMER = 1,
);

/*!
 * @enum	   hv_apic_intr_trigger_t
 * @abstract   APIC triggers
 */
OS_ENUM(hv_apic_intr_trigger, uint32_t,
    HV_APIC_EDGE_TRIGGER = 0,
    HV_APIC_EDGE_TRIGGER_AEOI = 1,
    HV_APIC_LEVEL_TRIGGER = 2,
);

__END_DECLS

OS_ASSUME_NONNULL_END

#endif /* __x86_64__ */

#endif /* __HYPERVISOR_HV_TYPES__ */
