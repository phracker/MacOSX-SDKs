/*
 *  hv_vmx.h
 *  Hypervisor Framework
 *
 *  Copyright (c) 2020 Apple Inc. All rights reserved.
 */

#ifndef __HYPERVISOR_HV_VMX__
#define __HYPERVISOR_HV_VMX__

#ifdef __x86_64__

#include <Availability.h>

#include <Hypervisor/hv_error.h>
#include <Hypervisor/hv_types.h>
#include <Hypervisor/hv_arch_x86.h>
#include <Hypervisor/hv_arch_vmx.h>

#define __HV_10_10 __API_AVAILABLE(macos(10.10))
#define __HV_10_15 __API_AVAILABLE(macos(10.15))
#define __HV_11_0 __API_AVAILABLE(macos(11.0))

OS_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 * @function   hv_vmx_vcpu_read_vmcs
 * @abstract   Returns the current value of a VMCS field of a vCPU
 * @param      vcpu   vCPU ID
 * @param      field  ID of the VMCS field to be read
 * @param      value  Pointer to the VMCS field value (written on success)
 * @result     0 on success or error code
 * @discussion
 *             See Documentation for a list of supported VMCS fields
 *
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vmx_vcpu_read_vmcs(hv_vcpuid_t vcpu, uint32_t field,
	uint64_t *value) __HV_10_10;

/*!
 * @function   hv_vmx_vcpu_write_vmcs
 * @abstract   Set the value of a VMCS field of a vCPU
 * @param      vcpu   vCPU ID
 * @param      field  ID of the VMCS field to be written
 * @param      value  Value of the VMCS field to be written
 * @result     0 on success or error code
 * @discussion
 *             Writes to the given VMCS field.
 *
 *             The masks returned by hv_vmx_vcpu_get_cap_write_vmcs
 *             will apply, see its documentation for the semantics of these
 *             masks.
 *             When writing, any bits that do not correspond to the
 *             masks may cause this function to fail. For fields that are
 *             scalar values instead of bit fields, the caller may assume
 *             that the masks are set appropriately to allow for any
 *             scalar within the allowed range.
 *
 *             See Documentation for a list of supported VMCS fields.
 *
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vmx_vcpu_write_vmcs(hv_vcpuid_t vcpu, uint32_t field,
	uint64_t value) __HV_10_10;

/*!
 * @function   hv_vmx_vcpu_get_cap_write_vmcs
 * @abstract   Returns the allowed-0 and allowed-1 masks for a VMCS field of a vCPU
 * @param      vcpu   vCPU ID
 * @param      field  ID of the VMCS field for which to return capabilities
 * @param      allowed_0  Pointer to the VMCS allowed 0 mask (written on success)
 * @param      allowed_1  Pointer to the VMCS allowed 1 mask (written on success)
 * @result     0 on success or error code
 * @discussion
 *             Returns the constraints imposed by the Hypervisor framework on
 *             the given VMCS field, in the form of allowed_0 and allowed_1 masks,
 *             indicating what bit values may be set when writing the given VMCS field.
 *
 *             When writing to a VMCS field, the caller is allowed to set bits that are
 *             0 in its allowed_0 mask to 0, and bits that are 1 in its allowed_1 mask
 *             to 1. This means:
 *
 *             allowed_0 = 0, allowed_1 = 0 -> must be NOT SET
 *             allowed_0 = 0, allowed_1 = 1 -> can be either
 *             allowed_0 = 1, allowed_1 = 0 -> undefined (should not happen)
 *             allowed_0 = 1, allowed_1 = 1 -> must be SET
 *
 *             See Documentation for a list of supported VMCS fields
 *
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vmx_vcpu_get_cap_write_vmcs(hv_vcpuid_t vcpu, uint32_t field,
    uint64_t *allowed_0, uint64_t *allowed_1) __HV_11_0;


/*!
 * @function   hv_vmx_vcpu_read_shadow_vmcs
 * @abstract   Returns the current value of a shadow VMCS field of a vCPU
 * @param      vcpu   vCPU ID
 * @param      field  ID of the shadow VMCS field to be read
 * @param      value  Pointer to the shadow VMCS field value (written on success)
 * @result     0 on success or error code
 * @discussion
 *             See Documentation for a list of supported shadow VMCS fields
 *
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vmx_vcpu_read_shadow_vmcs(hv_vcpuid_t vcpu,
	uint32_t field, uint64_t *value) __HV_10_15;

/*!
 * @function   hv_vmx_vcpu_write_shadow_vmcs
 * @abstract   Set the value of a shadow VMCS field of a vCPU
 * @param      vcpu   vCPU ID
 * @param      field  ID of the shadow VMCS field to be written
 * @param      value  Value of the shadow VMCS field to be written
 * @result     0 on success or error code
 * @discussion
 *             See Documentation for a list of supported shadow VMCS fields
 *
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vmx_vcpu_write_shadow_vmcs(hv_vcpuid_t vcpu,
	uint32_t field, uint64_t value) __HV_10_15;

/*!
 * @enum       hv_shadow_flags_t
 * @abstract   Shadow VMCS permissions for hv_vcpu_vmx_set_shadow_access()
 */
enum {
	HV_SHADOW_VMCS_NONE  = 0,
	HV_SHADOW_VMCS_READ  = (1ull << 0),
	HV_SHADOW_VMCS_WRITE = (1ull << 1),
};

typedef uint64_t hv_shadow_flags_t;

/*!
 * @function   hv_vmx_vcpu_set_shadow_access
 * @abstract   Set the access permissions of a shadow VMCS field of a vCPU
 * @param      vcpu   vCPU ID
 * @param      field  ID of the shadow VMCS field
 * @param      flags  New READ, WRITE permissions for the shadow VMCS field
 * @result     0 on success or error code
 * @discussion
 *             See Documentation for a list of supported shadow VMCS fields
 *
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vmx_vcpu_set_shadow_access(hv_vcpuid_t vcpu,
	uint32_t field, hv_shadow_flags_t flags) __HV_10_15;

/*!
 * @typedef    hv_vmx_capability_t
 * @abstract   Enum type of VMX capability fields
 */
typedef enum {
	HV_VMX_CAP_PINBASED = 0,         /* pin-based VMX capabilities */
	HV_VMX_CAP_PROCBASED = 1,        /* primary proc.-based VMX capabilities */
	HV_VMX_CAP_PROCBASED2 = 2,       /* second. proc.-based VMX capabilities */
	HV_VMX_CAP_ENTRY = 3,            /* VM-entry VMX capabilities */
	HV_VMX_CAP_EXIT = 4,             /* VM-exit VMX capabilities */
	HV_VMX_CAP_BASIC = 5,            /* Basic VMX capabilities */
	HV_VMX_CAP_TRUE_PINBASED = 6,	 /* hw pin-based VMX capabilities */
	HV_VMX_CAP_TRUE_PROCBASED = 7,	 /* hw primary proc.-based VMX capabilities */
	HV_VMX_CAP_TRUE_ENTRY = 8,		 /* hw VM-entry VMX capabilities */
	HV_VMX_CAP_TRUE_EXIT = 9,		 /* hw VM-exit VMX capabilities */
	HV_VMX_CAP_MISC = 10,            /* Miscellaneous VMX capabilities */
	HV_VMX_CAP_CR0_FIXED0 = 11,      /* CR0 allowed zero bits */
	HV_VMX_CAP_CR0_FIXED1 = 12,      /* CR0 allowed one bits */
	HV_VMX_CAP_CR4_FIXED0 = 13,      /* CR4 allowed zero bits */
	HV_VMX_CAP_CR4_FIXED1 = 14,      /* CR4 allowed one bits */
	HV_VMX_CAP_VMCS_ENUM = 15,       /* VMCS enumeration */
	HV_VMX_CAP_EPT_VPID_CAP = 16,    /* EPT/VPID capabilities */
	HV_VMX_CAP_PREEMPTION_TIMER = 32 /* VMX preemption timer frequency */
} hv_vmx_capability_t;

/*!
 * @function   hv_vmx_read_capability
 * @abstract   Returns the VMX capabilities of the host processor
 * @param      field  ID of the VMX capability field to be read
 * @param      value  Pointer to the capability field value (written on success)
 * @result     0 on success or error code
 * @discussion
 *             See Documentation for VMX capabilities that can be / must (not)
 *             be set
 */
extern hv_return_t hv_vmx_read_capability(hv_vmx_capability_t field,
	uint64_t *value) __HV_10_10;

/*!
 * @typedef    hv_vmx_msr_info_t
 * @abstract   Enum type of MSR information fields
 */
enum {
	HV_VMX_INFO_MSR_IA32_ARCH_CAPABILITIES = 0,
	HV_VMX_INFO_MSR_IA32_PERF_CAPABILITIES = 1,
	HV_VMX_VALID_MSR_IA32_PERFEVNTSEL = 2,
	HV_VMX_VALID_MSR_IA32_FIXED_CTR_CTRL = 3,
	HV_VMX_VALID_MSR_IA32_PERF_GLOBAL_CTRL = 4,
	HV_VMX_VALID_MSR_IA32_PERF_GLOBAL_STATUS = 5,
	HV_VMX_VALID_MSR_IA32_DEBUGCTL = 6,
	HV_VMX_VALID_MSR_IA32_SPEC_CTRL = 7,
	HV_VMX_NEED_MSR_IA32_SPEC_CTRL = 8,
};

typedef uint64_t hv_vmx_msr_info_t;

/*!
 * @function   hv_vmx_get_msr_info
 * @abstract   Returns information about guest MSR configuration
 * @param      field  ID of the MSR to be examined
 * @param      value  Pointer to the info field value (written on success)
 * @result     0 on success or error code
 * @discussion
 *             See Documentation for info that can be requested.
 */
extern hv_return_t hv_vmx_get_msr_info(hv_vmx_msr_info_t field, uint64_t *value) __HV_11_0;

/*!
 * @function   hv_vmx_vcpu_set_apic_address
 * @abstract   Set the address of the guest APIC for a vCPU in the
 *             guest physical address space of the VM
 * @param      vcpu  vCPU ID
 * @param      gpa   Page aligned address in the guest physical address space
 * @result     0 on success or error code
 * @discussion
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vmx_vcpu_set_apic_address(hv_vcpuid_t vcpu,
	hv_gpaddr_t gpa) __HV_10_10;

__END_DECLS

OS_ASSUME_NONNULL_END

#undef __HV_10_10
#undef __HV_10_15
#undef __HV_11_0

#endif /* __x86_64__ */

#endif /* __HYPERVISOR_HV_VMX__ */
