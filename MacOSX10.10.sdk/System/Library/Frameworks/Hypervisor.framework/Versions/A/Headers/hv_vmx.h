/*
 *  hv_vmx.h
 *  Hypervisor Framework
 *
 *  Copyright (c) 2013 Apple Inc. All rights reserved.
 */

#ifndef __HYPERVISOR_HV_VMX__
#define __HYPERVISOR_HV_VMX__

#include <Availability.h>

#include <Hypervisor/hv_error.h>
#include <Hypervisor/hv_types.h>
#include <Hypervisor/hv_arch_x86.h>
#include <Hypervisor/hv_arch_vmx.h>

#define __HV_10_10 __OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_NA)

#ifdef __cplusplus
extern "C" {
#endif

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
 *             See Documentation for a list of supported VMCS fields
 *
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vmx_vcpu_write_vmcs(hv_vcpuid_t vcpu, uint32_t field,
	uint64_t value) __HV_10_10;

/*!
 * @typedef    hv_vmx_capability_t
 * @abstract   Enum type of VMX cabability fields
 */
typedef enum {
	HV_VMX_CAP_PINBASED = 0,         /* pin-based VMX capabilities */
	HV_VMX_CAP_PROCBASED = 1,        /* primary proc.-based VMX capabilities */
	HV_VMX_CAP_PROCBASED2 = 2,       /* second. proc.-based VMX capabilities */
	HV_VMX_CAP_ENTRY = 3,            /* VM-entry VMX capabilities */
	HV_VMX_CAP_EXIT = 4,             /* VM-exit VMX capabilities */
	HV_VMX_CAP_PREEMPTION_TIMER = 32 /* VMX preemption timer frequency */
} hv_vmx_capability_t;

/*!
 * @function   hv_vmx_vcpu_read_capability
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

#ifdef __cplusplus
}
#endif

#undef __HV_10_10

#endif /* __HYPERVISOR_HV_VMX__ */
