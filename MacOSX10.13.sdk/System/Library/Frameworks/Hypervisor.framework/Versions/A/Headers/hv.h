/*
 *  hv.h
 *  Hypervisor Framework
 *
 *  Copyright (c) 2013 Apple Inc. All rights reserved.
 */

#ifndef __HYPERVISOR_HV__
#define __HYPERVISOR_HV__

#include <stdbool.h>
#include <sys/types.h>
#include <Availability.h>

#include <Hypervisor/hv_error.h>
#include <Hypervisor/hv_types.h>
#include <Hypervisor/hv_arch_x86.h>

#define __HV_10_10 __OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_NA)

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @function   hv_vm_create
 * @abstract   Creates a VM instance for the current task
 * @param      flags  RESERVED
 * @result     0 on success or error code
 */
extern hv_return_t hv_vm_create(hv_vm_options_t flags) __HV_10_10;

/*!
 * @function   hv_vm_destroy
 * @abstract   Destroys the VM instance associated with the current task
 * @result     0 on success or error code
 */
extern hv_return_t hv_vm_destroy(void) __HV_10_10;

/*!
 * @function   hv_vm_map
 * @abstract   Maps a region in the virtual address space of the current task
 *             into the guest physical address space of the VM
 * @param      uva    Page aligned virtual address in the current task
 * @param      gpa    Page aligned address in the guest physical address space
 * @param      size   Size in bytes of the region to be mapped
 * @param      flags  READ, WRITE and EXECUTE permissions of the region
 * @result     0 on success or error code
 */
extern hv_return_t hv_vm_map(hv_uvaddr_t uva, hv_gpaddr_t gpa, size_t size,
	hv_memory_flags_t flags) __HV_10_10;

/*!
 * @function   hv_vm_unmap
 * @abstract   Unmaps a region in the guest physical address space of the VM
 * @param      gpa   Page aligned address in the guest physical address space
 * @param      size  Size in bytes of the region to be unmapped
 * @result     0 on success or error code
 */
extern hv_return_t hv_vm_unmap(hv_gpaddr_t gpa, size_t size) __HV_10_10;

/*!
 * @function   hv_vm_protect
 * @abstract   Modifies the permissions of a region in the guest physical
 *             address space of the VM
 * @param      gpa   Page aligned address in the guest physical address space
 * @param      size  Size in bytes of the region to be modified
 * @param      flags New READ, WRITE and EXECUTE permissions of the region
 * @result     0 on success or error code
 */
extern hv_return_t hv_vm_protect(hv_gpaddr_t gpa, size_t size,
	hv_memory_flags_t flags) __HV_10_10;

/*!
 * @function   hv_vm_sync_tsc
 * @abstract   Synchronizes guest TSC across all vCPUs
 * @param      tsc  Guest TSC value
 * @result     0 on success or error code
 */
extern hv_return_t hv_vm_sync_tsc(uint64_t tsc) __HV_10_10;

/*!
 * @function   hv_vcpu_create
 * @abstract   Creates a vCPU instance for the current thread
 * @param      vcpu   Pointer to the vCPU ID (written on success)
 * @param      flags  RESERVED
 * @result     0 on success or error code
 */
extern hv_return_t hv_vcpu_create(hv_vcpuid_t *vcpu,
	hv_vcpu_options_t flags) __HV_10_10;

/*!
 * @function   hv_vcpu_destroy
 * @abstract   Destroys the vCPU instance associated with the current thread
 * @param      vcpu  vCPU ID
 * @result     0 on success or error code
 * @discussion
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_destroy(hv_vcpuid_t vcpu) __HV_10_10;

/*!
 * @function   hv_vcpu_read_register
 * @abstract   Returns the current value of an architectural x86 register
 *             of a vCPU
 * @param      vcpu   vCPU ID
 * @param      reg    ID of the register to be read
 * @param      value  Pointer to the register value (written on success)
 * @result     0 on success or error code
 * @discussion
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_read_register(hv_vcpuid_t vcpu, hv_x86_reg_t reg,
	uint64_t *value) __HV_10_10;

/*!
 * @function   hv_vcpu_write_register
 * @abstract   Set the value of an architectural x86 register of a vCPU
 * @param      vcpu   vCPU ID
 * @param      reg    ID of the register to be written
 * @param      value  Value of the register to be written
 * @result     0 on success or error code
 * @discussion
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_write_register(hv_vcpuid_t vcpu, hv_x86_reg_t reg,
	uint64_t value) __HV_10_10;

/*!
 * @function   hv_vcpu_read_fpstate
 * @abstract   Returns the current architectural x86 floating point and
 *             SIMD state of a vCPU
 * @param      vcpu    vCPU ID
 * @param      buffer  Pointer to a memory buffer (written on success)
 * @param      size    Size of the memory buffer in bytes
 * @result     0 on success or error code
 * @discussion
 *             Structure and size are defined by the XSAVE feature set of
 *             the host processor
 *
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_read_fpstate(hv_vcpuid_t vcpu, void *buffer,
	size_t size) __HV_10_10;

/*!
 * @function   hv_vcpu_write_fpstate
 * @abstract   Sets the architectural x86 floating point and SIMD state of
 *             a vCPU
 * @param      vcpu    vCPU ID
 * @param      buffer  Pointer to a memory buffer holding the state
 *                     to be written
 * @param      size    Size of the memory buffer in bytes
 * @result     0 on success or error code
 * @discussion
 *             Structure and size are defined by the XSAVE feature set of
 *             the host processor
 *
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_write_fpstate(hv_vcpuid_t vcpu, void *buffer,
	size_t size) __HV_10_10;

/*!
 * @function   hvvcpu_enable_native_msr
 * @abstract   Enables an MSR to be used natively by the VM
 * @param      vcpu    vCPU ID
 * @param      msr     ID of the MSR
 * @param      enable  Enable or disable the native use of the MSR
 * @result     0 on success or error code
 * @discussion
 *             See Documentation for a list of supported MSRs
 *
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_enable_native_msr(hv_vcpuid_t vcpu, uint32_t msr,
	bool enable) __HV_10_10;

/*!
 * @function   hv_vcpu_read_msr
 * @abstract   Returns the current value of an MSR of a vCPU
 * @param      vcpu   vCPU ID
 * @param      msr    ID of the MSR to be read
 * @param      value  Pointer to the MSR value (written on success)
 * @result     0 on success or error code
 * @discussion
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_read_msr(hv_vcpuid_t vcpu, uint32_t msr,
	uint64_t *value) __HV_10_10;

/*!
 * @function   hv_vcpu_write_msr
 * @abstract   Set the value of an MSR of a vCPU
 * @param      vcpu   vCPU ID
 * @param      msr    ID of the MSR to be written
 * @param      value  Value of the MSR to be written
 * @result     0 on success or error code
 * @discussion
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_write_msr(hv_vcpuid_t vcpu, uint32_t msr,
	uint64_t value) __HV_10_10;

/*!
 * @function   hv_vcpu_flush
 * @abstract   Forces flushing of cached vCPU state
 * @param      vcpu  vCPU ID
 * @result     0 on success or error code
 * @discussion
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_flush(hv_vcpuid_t vcpu) __HV_10_10;

/*!
 * @function   hv_vcpu_invalidate_tlb
 * @abstract   Invalidates the TLB of a vCPU
 * @param      vcpu  vCPU ID
 * @result     0 on success or error code
 * @discussion
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_invalidate_tlb(hv_vcpuid_t vcpu) __HV_10_10;

/*!
 * @function   hv_vcpu_run
 * @abstract   Executes a vCPU
 * @param      vcpu  vCPU ID
 * @result     0 on success or error code
 * @discussion
 *             Call blocks until the next VMEXIT of the vCPU
 *
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_run(hv_vcpuid_t vcpu) __HV_10_10;

/*!
 * @function   hv_vcpu_interrupt
 * @abstract   Forces an immediate VMEXIT of a set of vCPUs of the VM
 * @param      vcpus       Pointer to a list of vCPU IDs
 * @param      vcpu_count  Number of vCPUs in the list
 * @result     0 on success or error code
 */
extern hv_return_t hv_vcpu_interrupt(hv_vcpuid_t* vcpus,
	unsigned int vcpu_count) __HV_10_10;

/*!
 * @function   hv_vcpu_get_exec_time
 * @abstract   Returns the cumulative execution time of a vCPU in nanoseconds
 * @param      vcpu  vCPU ID
 * @param      time  Pointer to execution time value (written on success)
 * @result     0 on success or error code
 * @discussion
 *             Must be called by the owning thread!
 */
extern hv_return_t hv_vcpu_get_exec_time(hv_vcpuid_t vcpu,
	uint64_t *time) __HV_10_10;

#ifdef __cplusplus
}
#endif

#undef __HV_10_10

#endif /* __HYPERVISOR_HV__ */
