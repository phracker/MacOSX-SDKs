/*
 *  hv.h
 *  Hypervisor Framework
 *
 *  Copyright (c) 2013-2021 Apple Inc. All rights reserved.
 */

#ifndef __HYPERVISOR_HV__
#define __HYPERVISOR_HV__

#ifdef __x86_64__

#include <mach/mach_port.h>

#include <Hypervisor/hv_base.h>
#include <Hypervisor/hv_error.h>
#include <Hypervisor/hv_types.h>
#include <Hypervisor/hv_arch_x86.h>
#include <Hypervisor/hv_intr.h>
#include <Hypervisor/hv_vm_allocate.h>

#define __HV_10_10 __API_AVAILABLE(macos(10.10))
#define __HV_10_15 __API_AVAILABLE(macos(10.15))
#define __HV_11_0 __API_AVAILABLE(macos(11.0))
#define __HV_12_0 __API_AVAILABLE(macos(12.0))

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
 * @deprecated This API has no effect and always returns HV_UNSUPPORTED.
 * @discussion
 *             This API should be removed from your application.
 *
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_flush(hv_vcpuid_t vcpu)
__API_DEPRECATED("This API has no effect and always returns HV_UNSUPPORTED", macos(10.10, 11.0));

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

enum {
    HV_DEADLINE_FOREVER = (~0ull)
} __HV_11_0;

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
 * @function   hv_vcpu_get_idle_time
 * @abstract   Returns the cumulative idle time of a vCPU in nanoseconds
 * @param      vcpu  vCPU ID
 * @param      time  Pointer to idle time value (written on success)
 * @result     0 on success or error code
 * @discussion
 *			   This is the time spent in the kernel emulating instructions
 *			   that cause the virtual CPU to idle e.g. HLT.
 *
 *             Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_get_idle_time(hv_vcpuid_t vcpu,
	uint64_t *time) __HV_12_0;

/*!
 * @function	hv_tsc_clock
 * @abstract	Returns the value of an abstract clock.
 * @description	The abstract clock ticks at the same rate as the host TSC,
 * 				offset by an implementation-dependent constant. The clock
 * 				value is monotonically increasing. Should only be called
 * 				after the virtual machine has been created.
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

/*!
 * @function	hv_vcpu_vmx_status
 * @abstract	Return the ZF and CF bits after running a VM
 * @param		vcpu	vCPU ID
 * @param		status	Pointer to 32-bit flags
 * @result		0 on success or error code
 * @discussion
 * 				Returns the ZF (Zero) and CF (Carry) flag bits of the host
 * 				RFLAGS register, captured on the last unsuccessful attempt
 * 				to run the virtual CPU. If this routine returns HV_ERROR,
 * 				the vcpu may have never run, or a different VM configuration
 * 				problem was detected e.g. inconsistent configuration of MSRs.
 *
 * 				Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_vmx_status(hv_vcpuid_t vcpu, uint32_t *status) __HV_12_0;

/*!
 * @function	hv_vm_lapic_set_intr
 * @abstract	Deliver an interrupt to the local APIC core
 * @param		vcpu	Target vCPU ID
 * @param		vector	Interrupt vector
 * @param		trig	Trigger mode
 * @result		0 on success or error code
 * @discussion
 *				Does not need to be called by the owning thread.
 */
extern hv_return_t hv_vm_lapic_set_intr(hv_vcpuid_t vcpu, uint8_t vector,
	hv_apic_intr_trigger_t trig) __HV_12_0;

/*!
 * @function	hv_vm_lapic_msi
 * @abstract	Deliver an MSI interrupt to one or more vCPUs in the VM
 * @param		addr	MSI message address
 * @param		data	MSI message data
 * @result		0 on success or error code
 */
extern hv_return_t hv_vm_lapic_msi(uint64_t addr,
	uint64_t data) __HV_12_0;

/*!
 * @function	hv_vm_ioapic_assert_irq
 * @abstract	Raise the level on a virtual IOAPIC pin
 * @param		intin	Interrupt pin number
 * @result		0 on success or error code
 */
extern hv_return_t hv_vm_ioapic_assert_irq(int intin) __HV_12_0;

/*!
 * @function	hv_vm_ioapic_deassert_irq
 * @abstract	Lower the level on a virtual IOAPIC pin
 * @param		intin	Interrupt pin number
 * @result		0 on success or error code
 */
extern hv_return_t hv_vm_ioapic_deassert_irq(int intin) __HV_12_0;

/*!
 * @function	hv_vm_ioapic_pulse_irq
 * @abstract	Raise then lower the level on a virtual IOAPIC pin
 * @param		intin	Interrupt pin number
 * @result		0 on success or error code
 */
extern hv_return_t hv_vm_ioapic_pulse_irq(int intin) __HV_12_0;

/*!
 * @function	hv_vm_ioapic_read
 * @abstract	Read a 32-bit IOAPIC register from the virtual IOAPIC
 * @param		gpa		Guest physical address of the register
 * @param		datap	Pointer to returned data
 * @result		0 on success or error code
 */
extern hv_return_t hv_vm_ioapic_read(hv_gpaddr_t gpa, uint32_t *datap) __HV_12_0;

/*!
 * @function	hv_vm_ioapic_write
 * @abstract	Write a 32-bit IOAPIC register to the virtual IOAPIC
 * @param		gpa		Guest physical address of the register
 * @param		data	Data to be written
 * @result		0 on success or error code
 */
extern hv_return_t hv_vm_ioapic_write(hv_gpaddr_t gpa, uint32_t data) __HV_12_0;

/*!
 * @function	hv_vm_ioapic_get_state
 * @abstract	Fetch the internal state of the virtual IOAPIC
 * @param		state	Pointer to the virtual IOAPIC state
 * @result		0 on success or error code
 * @discussion
 * 				The version field of the hv_ioapic_state_ext_t
 * 				structure must be set to HV_IOAPIC_STATE_EXT_VER
 * 				before invoking this API.
 */
extern hv_return_t hv_vm_ioapic_get_state(hv_ioapic_state_ext_t *state) __HV_12_0;

/*!
 * @function	hv_vm_ioapic_put_state
 * @abstract	Validate and restore the internal state of the virtual IOAPIC
 * @param		state	Pointer to the virtual IOAPIC state
 * @result		0 on success or error code
 * @discussion
 * 				This routine should only be used to restore the state of the
 * 				virtual IOAPIC captured by a previous call to
 * 				hv_vm_ioapic_get_state() on a fully quiescent virtual machine.
 */
extern hv_return_t hv_vm_ioapic_put_state(const hv_ioapic_state_ext_t *state) __HV_12_0;

/*!
 * @function	hv_vm_send_ioapic_intr
 * @abstract	Inject an IOAPIC interrupt into the VM
 * @param		data	Interrupt information
 * @result		0 on success or error code
 * @discussion
 * 				Allows interrupts to be sent to one or more APICs of the VM.
 * 				The format of the data should correspond to an IOAPIC
 * 				redirection table register.
 */
extern hv_return_t hv_vm_send_ioapic_intr(uint64_t data) __HV_12_0;

/*!
 * @function	hv_vm_atpic_assert_irq
 * @abstract	Raise the level on a virtual ATPIC pin
 * @param		irq		Interrupt pin number
 * @result		0 on success or error code
 */
extern hv_return_t hv_vm_atpic_assert_irq(int irq) __HV_12_0;

/*!
 * @function	hv_vm_atpic_deassert_irq
 * @abstract	Lower the level on a virtual ATPIC pin
 * @param		irq		Interrupt pin number
 * @result		0 on success or error code
 */
extern hv_return_t hv_vm_atpic_deassert_irq(int irq) __HV_12_0;

/*!
 * @function	hv_vm_atpic_port_read
 * @abstract	Read from a virtual APIC I/O port
 * @param		port	I/O port number
 * @param		valuep	Pointer to result of I/O instruction
 * @result		0 on success or error code
 */
extern hv_return_t hv_vm_atpic_port_read(int port, uint8_t *valuep);

/*!
 * @function	hv_vm_atpic_port_write
 * @abstract	Write to a virtual APIC I/O port
 * @param		port	I/O port number
 * @param		value	Value to write to port
 * @result		0 on success or error cod
 */
extern hv_return_t hv_vm_atpic_port_write(int port, uint8_t value);
/*!
 * @function	hv_vm_atpic_get_state
 * @abstract	Fetch the internal state of a virtual ATPIC
 * @param		state	Pointer to the virtual ATPIC state
 * @param		is_primary	Selects the primary or secondary ATPIC
 * @result		0 on success or error code
 * @discussion
 * 				The version field of the hv_atpic_state_ext_t
 * 				structure must be set to HV_ATPIC_STATE_EXT_VER
 * 				before invoking this API.
 */
extern hv_return_t hv_vm_atpic_get_state(hv_atpic_state_ext_t *state,
	bool is_primary) __HV_12_0;

/*!
 * @function	hv_vm_atpic_put_state
 * @abstract	Validate and restore the internal state of a virtual ATPIC
 * @param		state	Pointer to the virtual ATPIC state
 * @param		is_primary	Selects the primary or secondary ATPIC
 * @result		0 on success or error code
 * @discussion
 * 				This routine should only be used to restore the state of the
 * 				virtual ATPIC captured by a previous call to
 * 				hv_vm_atpic_get_state() on a fully quiescent virtual machine.
 */
extern hv_return_t hv_vm_atpic_put_state(const hv_atpic_state_ext_t *state,
	bool is_primary) __HV_12_0;

/*!
 * @function	hv_vm_set_apic_bus_freq
 * @abstract	Set the APIC timer frequency in Hz
 * @param		freq	Frequency in Hz
 * @result		0 on success or error code
 * @discussion
 * 				Allows the virtual APIC timer frequency to be set. The
 * 				implementation allows values to be set between 16MHz and 2GHz.
 *				The value is shared by all APICs in the VM, and may
 *				only be modified when there are zero vcpus in the VM.
 */
extern hv_return_t hv_vm_set_apic_bus_freq(uint64_t freq) __HV_12_0;

/*!
 * @function	hv_vcpu_inject_extint
 * @abstract	Inject an external interrupt into the vCPU
 * @param		vcpu	vCPU ID
 * @result		0 on success or error code
 * @discussion
 * 				Only one external interrupt (injected via the VMCS) can
 * 				be enqueued at a time.
 *
 * 				Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_inject_extint(hv_vcpuid_t vcpu) __HV_12_0;

/*!
 * @function	hv_vcpu_apic_read
 * @abstract	Read from the vCPUs virtual local APIC
 * @param		vcpu	vCPU ID
 * @param		offset	Byte offset into the APIC page
 * @param		data	Pointer to the APIC data
 * @result		0 on success or error code
 * @discussion
 * 				Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_apic_read(hv_vcpuid_t vcpu,
	uint32_t offset, uint32_t *data) __HV_12_0;

/*!
 * @function	hv_vcpu_apic_write
 * @abstract	Write to the vCPUs virtual local APIC
 * @param		vcpu	vCPU ID
 * @param		offset	Byte offset into the APIC page
 * @param		data	Value to be written
 * @param		no_side_effect	Pointer to boolean flag value
 * @result		0 on success or error code
 * @discussion
 * 				Writes to certain locations may succeed but have related
 * 				side-effects which need to be handled by the caller. The
 * 				no_side_effect parameter is used to indicate this.
 * 				Use hv_vcpu_exit_info() to further identify the reason.
 *
 * 				Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_apic_write(hv_vcpuid_t vcpu,
	uint32_t offset, uint32_t data, bool *no_side_effect) __HV_12_0;

/*!
 * @function	hv_vcpu_apic_get_state
 * @abstract	Fetch the internal state of the virtual local APIC
 * @param		vcpu	vCPU ID
 * @param		state	Pointer to the virtual local APIC state
 * @result		0 on success or error code
 * @discussion
 * 				The version field of the hv_apic_state_ext_t
 * 				structure should be set to HV_APIC_STATE_EXT_VER
 * 				before invoking this API.
 *
 * 				Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_apic_get_state(hv_vcpuid_t vcpu,
	hv_apic_state_ext_t *state) __HV_12_0;

/*!
 * @function	hv_vcpu_apic_put_state
 * @abstract	Validate and restore the internal state of the virtual local APIC
 * @param		vcpu	vCPU ID
 * @param		state	Pointer to the virtual local APIC state
 * @result		0 on success or error code
 * @discussion
 * 				This API should only be used to restore the state of the
 * 				virtual local APIC captured by a previous call to
 * 				hv_vcpu_apic_get_state() on a fully quiescent virtual machine.
 *
 * 				Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_apic_put_state(hv_vcpuid_t vcpu,
	const hv_apic_state_ext_t *state) __HV_12_0;

/*!
 * @function	hv_vcpu_exit_info
 * @abstract	Return type of additional VM exit information
 * @param		vcpu	vCPU ID
 * @param		code	Pointer to type code
 * @result		0 on success or error code
 * @discussion
 * 				Provides the type of additional information available
 * 				about certain VM exits.
 *
 * 				Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_exit_info(hv_vcpuid_t vcpu, hv_vm_exitinfo_t *code) __HV_12_0;

/*!
 * @function	hv_vcpu_exit_init_ap
 * @abstract	Return vCPU IDs targeted by AP initialization
 * @param		vcpu	vCPU ID
 * @param		is_actv	Applicable processors, indexed by vCPU ID
 * @param		count	Number of array elements
 * @result		0 on success or error code
 * @discussion
 * 				This API can be called when the code returned by
 * 				hv_vcpu_exit_info() is HV_VM_EXITINFO_INIT_AP, which may
 * 				occur as part of handling writes to the ICR register.
 *
 * 				Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_exit_init_ap(hv_vcpuid_t vcpu,
	bool is_actv[_Nonnull], unsigned count) __HV_12_0;

/*!
 * @function	hv_vcpu_exit_startup_ap
 * @abstract	Return vCPU IDs targeted by AP startup
 * @param		vcpu	vCPU ID
 * @param		is_actv	Applicable processors, indexed by vCPU ID
 * @param		count	Number of array elements
 * @result		0 on success or error code
 * @discussion
 * 				This API can be called when the code returned by
 * 				hv_vcpu_exit_info() is HV_VM_EXITINFO_STARTUP_AP, which may
 * 				occur as part of handling a guest write to the ICR register.
 *
 * 				Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_exit_startup_ap(hv_vcpuid_t vcpu,
	bool is_actv[_Nonnull], unsigned count, uint64_t *ap_rip) __HV_12_0;

/*!
 * @function	hv_vcpu_exit_ioapic_eoi
 * @abstract	Return IOAPIC EOI vector
 * @param		vcpu	vCPU ID
 * @param		vec		Pointer to vector associated with EOI
 * @result		0 on success or error code
 * @discussion
 * 				This API can be called when the code returned by
 * 				hv_vcpu_exit_info() is HV_VM_EXITINFO_IOAPIC_EOI, which
 * 				may occur as part of handling a guest write to the EOI
 * 				register.
 *
 * 				Must be called by the owning thread.
 */
extern hv_return_t hv_vcpu_exit_ioapic_eoi(hv_vcpuid_t vcpu,
	uint8_t *vec) __HV_12_0;

/*!
 * @function	hv_vcpu_exit_apic_access_read
 * @abstract	Return APIC value being read
 * @param		vcpu	vCPU ID
 * @param		value	Pointer to APIC register value
 * @result		0 on success or error code
 * @discussion
 * 				This API can be called when the code returned by
 * 				hv_vcpu_exit_info() is HV_VM_EXITINFO_APIC_ACCESS_READ, which
 * 				can only occur as part of handling an APIC access VM exit.
 * 				It provides a low-overhead way to access the value of
 * 				the APIC register the guest is trying to read.
 *
 * 				Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_exit_apic_access_read(hv_vcpuid_t vcpu,
	uint32_t *value) __HV_12_0;

/*!
 * @function	hv_vcpu_exit_inject_excp
 * @abstract	Return exception parameters to be injected
 * @param		vcpu	vCPU ID
 * @param		vec		Pointer to exception vector number
 * @param		valid	Pointer to valid flag
 * @param		code	Pointer to exception error code
 * @param		restart	Pointer to restart flag
 * @result		0 on success or error code
 * @discussion
 * 				This API can be called when the code returned by
 * 				hv_vcpu_exit_info() is HV_VM_EXITINFO_INJECT_EXCP.
 * 				If this code is encountered, the guest vcpu may have performed
 * 				an illegal operation on its APIC, so the exception should
 * 				usually be directed back into the guest.
 *
 * 				Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_exit_inject_excp(hv_vcpuid_t vcpu,
	uint8_t *vec, bool *valid, uint32_t *code, bool *restart) __HV_12_0;

/*!
 * @function	hv_vcpu_apic_lsc_enter_r32
 * @abstract	Add an entry to the APIC load-store cache
 * @param		vcpu	vCPU ID
 * @param		is_load	True for a load register instruction
 * @param		rip		Instruction pointer of movl instruction
 * @param		ilen	Instruction length of movl instruction
 * @param		cs		Code selector register at rip
 * @param		reg		Register target of movl instruction
 * @param		uva		User addresses of page(s) containing [rip, rip+ilen)
 * @param		count	Number of valid addresses in uva[] (0, 1 or 2)
 * @result		0 on success or error code
 * @discussion
 * 				Each virtual CPU implements a limited capacity cache which
 * 				can performs a basic register move operation on the local
 * 				APIC page in response to an APIC access VM exit.
 * 				When an APIC access VM-exit occurs, iff the the set of
 * 				(rip, ilen, cs) parameters specified matches, the kernel
 * 				will perform the appropriate move to (or from) the
 * 				target register.
 *
 *				If uva is non-NULL, it should contain an array of
 *				page-aligned addresses in the current task that
 *				correspond to the page(s) containing the guest rip in
 *				the guest physical address space. If these addresses are
 *				provided, the kernel will record the bytes at [rip, rip+ilen),
 *				along with paging-related fields from guest control registers.
 *				Each time a cache hit occurs these will be compared,
 *				and the cache entry will be invalidated if any changes
 *				are detected.
 *
 * 				Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_apic_lsc_enter_r32(hv_vcpuid_t vcpu, bool is_load,
	uint64_t rip, unsigned ilen, uint16_t cs, hv_x86_reg_t reg,
	uint64_t uva[_Nullable], unsigned count) __HV_12_0;

/*!
 * @function	hv_vcpu_apic_lsc_enter_imm32
 * @abstract	Add an entry to the APIC load-store cache
 * @param		vcpu	vCPU ID
 * @param		rip		Instruction pointer of movl instruction
 * @param		ilen	Instruction length of movl instruction
 * @param		cs		Code selector register at rip
 * @param		imm32	Constant value to be stored
 * @param		uva		User addresses of page(s) containing [rip, rip+ilen)
 * @param		count	Number of valid addresses in uva[] (0, 1, or 2)
 * @result		0 on success or error code
 * @discussion
 * 				Each virtual CPU implements a limited capacity cache which
 * 				can performs a basic register move operation on the local
 * 				APIC page in response to an APIC access VM exit.
 * 				When an APIC access VM-exit occurs, iff the the set of
 * 				(rip, ilen, cs) parameters specified matches, the kernel
 * 				will perform a move of the imm32 constant to the
 * 				target APIC register.
 *
 * 				Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_apic_lsc_enter_imm32(hv_vcpuid_t vcpu,
	uint64_t rip, unsigned ilen, uint16_t cs, uint32_t imm32,
	uint64_t uva[_Nullable], unsigned count) __HV_12_0;

/*!
 * @function	hv_vcpu_apic_lsc_invalidate
 * @abstract	Invalidate the APIC load-store cache
 * @param		vcpu	vCPU ID
 * @result		0 on success or error code
 * @discussion
 * 				Invalidates all cache entries for the vcpu.
 *
 * 				Must be called by the owning thread
 */
extern hv_return_t hv_vcpu_apic_lsc_invalidate(hv_vcpuid_t vcpu) __HV_12_0;

/*!
 * @function	hv_vcpu_apic_ctrl
 * @abstract	Modify the behavior of the virtual APIC
 * @param		vcpu	vCPU ID
 * @param		ctrls	APIC behavior flags
 * @result		0 on success or error code
 * @discussion
 * 				The virtual CPU and APIC behavior can be modified
 * 				by setting various flags from the hv_apic_ctls_t enumeration.
 *
 *				HV_APIC_CTRL_EOI_ICR_TPR enables support for MSRs that allow
 *				the virtual APIC EOI, ICR and TPR registers to be accessed by
 *				the guest via rdmsr and wrmsr instructions, even when the
 *				APIC is in xAPIC mode.
 *
 *				HV_APIC_CTRL_GUEST_IDLE enables support for an MSR that
 *				allows the vcpu to be placed into an idle state.
 *
 *				HV_APIC_CTRL_NO_TIMER disables all timer operations by
 *				the virtual APIC and allows related VM exits to return the
 *				client. The virtual APIC tracks guest updates to the APIC
 *				timer registers, but the timer does not run, no timer
 *				interrupts are generated, so the hypervisor client must
 *				handle all timer operations.
 *
 *				HV_APIC_CTRL_IOAPIC_EOI causes the APIC to convert EOI
 *				notifications intended for an IOAPIC into a VM exit instead.
 *				The vector can be retrieved using hv_vcpu_exit_ioapic_eoi().
 *
 * 				Must be called by the owning thread.
 */
extern hv_return_t hv_vcpu_apic_ctrl(hv_vcpuid_t vcpu,
	hv_apic_ctrl_t ctrls) __HV_12_0;

/*!
 * @function	hv_vcpu_apic_trigger_lvt
 * @abstract	Trigger an APIC local vector entry
 * @param		vcpu	vCPU ID
 * @param		flavor	APIC vector type
 * @result		0 on success or error code
 * @discussion
 * 				Causes the local vector table entry to issue an interrupt
 * 				request.
 * 				Only HV_APIC_LVT_TIMER is currently supported.
 *
 * 				Must be called by the owning thread.
 */
extern hv_return_t hv_vcpu_apic_trigger_lvt(hv_vcpuid_t vcpu, hv_apic_lvt_flavor_t flavor) __HV_12_0;

__END_DECLS

OS_ASSUME_NONNULL_END

#undef __HV_10_10
#undef __HV_10_15
#undef __HV_11_0
#undef __HV_12_0

#endif /* __x86_64__ */

#endif /* __HYPERVISOR_HV__ */
