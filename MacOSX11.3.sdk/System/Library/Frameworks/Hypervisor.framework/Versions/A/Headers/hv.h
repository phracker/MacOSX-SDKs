/*
 *  hv.h
 *  Hypervisor Framework
 *
 *  Copyright (c) 2013-2019 Apple Inc. All rights reserved.
 */

#ifndef __HYPERVISOR_HV__
#define __HYPERVISOR_HV__

#ifdef __x86_64__

#include <mach/mach_port.h>

#include <Hypervisor/hv_base.h>
#include <Hypervisor/hv_error.h>
#include <Hypervisor/hv_types.h>
#include <Hypervisor/hv_arch_x86.h>

#define __HV_10_10 __API_AVAILABLE(macos(10.10))
#define __HV_10_15 __API_AVAILABLE(macos(10.15))
#define __HV_11_0 __API_AVAILABLE(macos(11.0))

OS_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 * @function   hv_capability
 * @abstract   Enumerate supported hypervisor capabilities
 * @param      capability  ID of the capability
 * @result     0 on success or error code
 */
extern hv_return_t hv_capability(hv_capability_t capability,
    uint64_t *value) __HV_10_15;

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
 * @function   hv_vm_space_create
 * @abstract   Creates an additional guest address space for the current task
 * @param      asid  Pointer to the addresss space ID (written on success)
 * @result     0 on success or error code
 */
extern hv_return_t hv_vm_space_create(hv_vm_space_t *asid) __HV_10_15;

/*!
 * @function   hv_vm_space_destroy
 * @abstract   Destroys the address space instance associated with the
 *             current task
 * @param      asid  address space ID
 * @result     0 on success or error code
 */
extern hv_return_t hv_vm_space_destroy(hv_vm_space_t asid) __HV_10_15;

/*!
 * @function   hv_vm_map
 * @abstract   Maps a region in the virtual address space of the current task
 *             into the guest physical address space of the VM
 * @param      uva    Page aligned virtual address in the current task
 * @param      gpa    Page aligned address in the guest physical address space
 * @param      size   Size in bytes of the region to be mapped
 * @param      flags  READ, WRITE and EXECUTE permissions of the region
 * @result     0 on success or error code
 * @discussion
 *             Operates on the default address space
 */
extern hv_return_t hv_vm_map(hv_uvaddr_t uva, hv_gpaddr_t gpa, size_t size,
	hv_memory_flags_t flags) __HV_10_10;

/*!
 * @function   hv_vm_unmap
 * @abstract   Unmaps a region in the guest physical address space of the VM
 * @param      gpa   Page aligned address in the guest physical address space
 * @param      size  Size in bytes of the region to be unmapped
 * @result     0 on success or error code
 * @discussion
 *             Operates on the default address space
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
 * @discussion
 *             Operates on the default address space
 */
extern hv_return_t hv_vm_protect(hv_gpaddr_t gpa, size_t size,
	hv_memory_flags_t flags) __HV_10_10;

/*!
 * @function   hv_vm_map_space
 * @abstract   Maps a region in the virtual address space of the current task
 *             into a guest physical address space of the VM
 * @param      asid   Address space ID
 * @param      uva    Page aligned virtual address in the current task
 * @param      gpa    Page aligned address in the guest physical address space
 * @param      size   Size in bytes of the region to be mapped
 * @param      flags  READ, WRITE and EXECUTE permissions of the region
 * @result     0 on success or error code
 */
extern hv_return_t hv_vm_map_space(hv_vm_space_t asid, hv_uvaddr_t uva,
	hv_gpaddr_t gpa, size_t size, hv_memory_flags_t flags) __HV_10_15;

/*!
 * @function   hv_vm_unmap_space
 * @abstract   Unmaps a region in a guest physical address space of the VM
 * @param      asid  Address space ID
 * @param      gpa   Page aligned address in the guest physical address space
 * @param      size  Size in bytes of the region to be unmapped
 * @result     0 on success or error code
 */
extern hv_return_t hv_vm_unmap_space(hv_vm_space_t asid, hv_gpaddr_t gpa,
	size_t size) __HV_10_15;

/*!
 * @function   hv_vm_protect_space
 * @abstract   Modifies the permissions of a region in a guest physical
 *             address space of the VM
 * @param      asid  Address space ID
 * @param      gpa   Page aligned address in the guest physical address space
 * @param      size  Size in bytes of the region to be modified
 * @param      flags New READ, WRITE and EXECUTE permissions of the region
 * @result     0 on success or error code
 */
extern hv_return_t hv_vm_protect_space(hv_vm_space_t asid, hv_gpaddr_t gpa,
	size_t size, hv_memory_flags_t flags) __HV_10_15;

/*!
 * @function   hv_vm_sync_tsc
 * @abstract   Synchronizes guest TSC across all vCPUs
 * @param      tsc  Guest TSC value
 * @result     0 on success or error code
 */
extern hv_return_t hv_vm_sync_tsc(uint64_t tsc) __HV_10_10;

/*!
 * @function   hv_vm_add_pio_notifier
 * @abstract   Generate a notification when a matching guest port IO is issued.
 * @param      addr      Port IO address to match
 * @param      size      Size to match (1, 2, 4)
 * @param      value     Value to match
 * @param      mach_port Mach port with send right
 * @param      flags     Controlling options
 * @result     0 on success or error code
 * @discussion An installed notifier will suppress guest exits triggered by the
 *             matching IO and instead send a message (hv_ion_message_t) to the
 *             specified mach port. Only one notifier per port address is permitted.
 */
extern hv_return_t hv_vm_add_pio_notifier(uint16_t addr, size_t size,
	uint32_t value, mach_port_t mach_port, hv_ion_flags_t flags) __HV_11_0;

/*!
 * @function   hv_vm_remove_pio_notifier
 * @abstract   Remove a previously added notifier.
 * @param      addr      Previously specified port IO address
 * @param      size      Previously specified size
 * @param      value     Previously specified value
 * @param      mach_port Previously specified mach port
 * @param      flags     Previously specified options
 * @result     0 on success or error code
 * @discussion Arguments much match those previously used to add the notifier.
 */
extern hv_return_t hv_vm_remove_pio_notifier(uint16_t addr, size_t size,
	uint32_t value, mach_port_t mach_port, hv_ion_flags_t flags) __HV_11_0;

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
 * @function   hv_vcpu_set_space
 * @abstract   Associates the vCPU instance with an allocated address space
 * @param      vcpu  vCPU ID
 * @param      asid  address space ID
 * @result     0 on success or error code
 * @discussion
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_set_space(hv_vcpuid_t vcpu, hv_vm_space_t asid)
	__HV_10_15;

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
 * @function   hv_vcpu_enable_native_msr
 * @abstract   Enables an MSR to be used natively by the vCPU
 * @param      vcpu    vCPU ID
 * @param      msr     ID of the MSR
 * @param      enable  Enable or disable the guest use of the MSR
 * @result     0 on success or error code
 * @discussion
 *             See Documentation for a list of supported MSRs
 *
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_enable_native_msr(hv_vcpuid_t vcpu, uint32_t msr,
	bool enable) __HV_10_10;

/*!
 * @function   hv_vcpu_enable_managed_msr
 * @abstract   Enables an MSR to be used by the vCPU
 * @param      vcpu    vCPU ID
 * @param      msr     ID of the MSR
 * @param      enable  Enable or disable the guest use of the MSR
 * @result     0 on success or error code
 * @discussion
 *             See Documentation for a list of supported MSRs
 *
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_enable_managed_msr(hv_vcpuid_t vcpu, uint32_t msr,
	bool enable) __HV_11_0;

/*!
 * @function   hv_vcpu_set_msr_access
 * @abstract   Controls the guest access to a managed MSR
 * @param      vcpu    vCPU ID
 * @param      msr     ID of the MSR
 * @param      flags   Enable or disable the guest use of the MSR
 * @result     0 on success or error code
 * @discussion
 *             See Documentation for a list of supported MSRs
 *
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_set_msr_access(hv_vcpuid_t vcpu, uint32_t msr,
	hv_msr_flags_t flags) __HV_11_0;

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
 * @deprecated Use hv_vcpu_run_until(..., HV_DEADLINE_FOREVER) instead.
 * @discussion
 *             Call blocks until the next VMEXIT of the vCPU, even if the
 *             VMEXIT was transparently handled. vm_vcpu_run_until()
 *             only returns on unhandled VMEXITs.
 *
 *             Use hv_vcpu_run_until(..., HV_DEADLINE_FOREVER) for
 *             an alternative that does not block on transparently handled
 *             VMEXITs instead.
 *
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_run(hv_vcpuid_t vcpu);

/*!
 * @function   hv_vcpu_run_until
 * @abstract   Executes a vCPU until the given deadline.
 * @param      vcpu      vCPU ID
 * @param      deadline  The timer deadline in mach absolute time units.
 * @result     0 on success or error code
 * @discussion
 *             This call blocks until the next VMEXIT or until the given
 *             deadline expires. The special value HV_DEADLINE_FOREVER
 *             specifies a deadline that never expires.
 *
 *             If a deadline other than HV_DEADLINE_FOREVER is specified,
 *             this call uses the VMX preemption timer, and returns
 *             HV_UNSUPPORTED if the hardware does not support it.
 *
 *             This function supersedes hv_vcpu_run(). Unlike hv_vcpu_run(),
 *             hv_vcpu_run_until() does not return on VMEXITs that were
 *             handled transparently (e.g. EPT violations in mapped regions).
 *
 *             Must be called by the owning thread
 */
enum {
    HV_DEADLINE_FOREVER = (~0ull)
} __HV_11_0;

extern hv_return_t hv_vcpu_run_until(hv_vcpuid_t vcpu,
	uint64_t deadline) __HV_10_15;

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
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_get_exec_time(hv_vcpuid_t vcpu,
	uint64_t *time) __HV_10_10;

/*!
 * @function	hv_tsc_clock
 * @abstract	Returns the value of an abstract clock.
 * @description	The abstract clock ticks at the same rate as the host TSC,
 * 				offset by an implementation-dependent constant. The clock
 * 				value is monotonically increasing.
 */
extern uint64_t hv_tsc_clock(void) __HV_11_0;

/*!
 * @function	hv_vcpu_set_tsc_relative
 * @abstract	Sets the offset of the guest TSC relative to the hv_tsc_clock()
 * @param		vcpu  	vCPU ID
 * @param		offset	Relative offset value to apply to VMCS TSC-offset field
 * @result		0 on success or error code
 * @discussion	The routine arranges to set the TSC-offset field in the VMCS such
 * 				that the TSC value in the guest will be the value
 * 				of hv_tsc_clock() plus the given offset.
 */
extern hv_return_t hv_vcpu_set_tsc_relative(hv_vcpuid_t vcpu,
	int64_t offset) __HV_11_0;

__END_DECLS

OS_ASSUME_NONNULL_END

#undef __HV_10_10
#undef __HV_10_15
#undef __HV_11_0

#endif /* __x86_64__ */

#endif /* __HYPERVISOR_HV__ */
