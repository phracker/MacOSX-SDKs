//
//  hv_gic.h
//  Hypervisor
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#pragma once

#ifdef __arm64__

#include <Hypervisor/hv_base.h>
#include <Hypervisor/hv_gic_types.h>
#include <Hypervisor/hv_vcpu.h>
#include <Hypervisor/hv_vm_types.h>
#include <arm64/hv/hv_kern_types.h>

OS_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 @abstract Create a GIC v3 device for a VM configuration.
 @param gic_config GIC configuration object.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    This function can be used to create an ARM Generic Interrupt Controller
    (GIC) v3 device. There must only be a single instance of this device per
    virtual machine. The device supports a distributor, redistributors, msi and
    GIC CPU system registers. When EL2 is enabled, the device supports GIC
    hypervisor control registers which are used by the guest hypervisor for
    injecting interrupts to its guest. hv_vcpu_{get/set}_interrupt functions
    are unsupported for injecting interrupts to a nested guest.

    The hv_gic_create() API must only be called after a virtual machine has
    been created. It must also be done before vCPU's have been created so that
    GIC CPU system resources can be allocated. If either of these conditions
    aren't met an error is returned.

    GIC v3 uses affinity based interrupt routing. vCPU's must set affinity
    values in their MPIDR_EL1 register. Once the virtual machine vcpus are
    running, its topology is considered final. Destroy vcpus only when you are
    tearing down the virtual machine.

    GIC MSI support is only provided if both an MSI region base address is
    configured and an MSI interrupt range is set.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_create(hv_gic_config_t gic_config);

/*!
 @abstract Trigger a Shared Peripheral Interrupt (SPI).
 @param intid Interrupt number of the SPI.
 @param level High or low level for an interrupt. Setting level also
    causes an edge on the line for an edge triggered interrupt.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    Level interrupts can be caused by setting a level value. If you want to
    cause an edge interrupt, call with a level of true. A level of false, for
    an edge interrupt will be ignored.

    An interrupt identifier outside of hv_gic_get_spi_interrupt_range() or in
    the MSI interrupt range will return a HV_BAD_ARGUMENT error code.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_set_spi(uint32_t intid, bool level);

/*!
 @abstract Send a Message Signaled Interrupt (MSI).
 @param address Guest physical address for message based SPI.
 @param intid Interrupt identifier for the message based SPI.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    Use the address of the HV_GIC_REG_GICM_SET_SPI_NSR register in the MSI frame.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_send_msi(hv_ipa_t address, uint32_t intid);

/*!
 @abstract Read a GIC distributor register.
 @param reg GIC distributor register enum.
 @param value Pointer to distributor register value (written on success).
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    GIC distributor register enum values are equal to the device register
    offsets defined in the ARM GIC v3 specification. The client can use the
    offset alternatively, while looping through large register arrays.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_get_distributor_reg(hv_gic_distributor_reg_t reg, uint64_t *value);

/*!
 @abstract Write a GIC distributor register.
 @param reg GIC distributor register enum.
 @param value GIC distributor register value to be written.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    GIC distributor register enum values are equal to the device register
    offsets defined in the ARM GIC v3 specification. The client can use the
    offset alternatively, while looping through large register arrays.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_set_distributor_reg(hv_gic_distributor_reg_t reg, uint64_t value);

/*!
 @abstract Gets the redistributor base guest physical address for the given vcpu.
 @param vcpu Handle for the vcpu.
 @param redistributor_base_address Pointer to the redistributor base guest physical address (written on success).
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    Must be called after the affinity of the given vCPU has been set in its MPIDR_EL1 register.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_get_redistributor_base(hv_vcpu_t vcpu, hv_ipa_t *redistributor_base_address);

/*!
 @abstract Read a GIC redistributor register.
 @param vcpu Redistributor block for the vcpu.
 @param reg GIC redistributor register enum.
 @param value Pointer to redistributor register value (written on success).
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    Must be called by the owning thread.

    GIC redistributor register enum values are equal to the device register
    offsets defined in the ARM GIC v3 specification. The client can use the
    offset alternatively, while looping through large register arrays.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_get_redistributor_reg(hv_vcpu_t vcpu, hv_gic_redistributor_reg_t reg, uint64_t *value);

/*!
 @abstract Write a GIC redistributor register.
 @param vcpu Redistributor block for the vcpu.
 @param reg GIC redistributor register enum.
 @param value GIC redistributor register value to be written.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    Must be called by the owning thread.

    GIC redistributor register enum values are equal to the device register
    offsets defined in the ARM GIC v3 specification. The client can use the
    offset alternatively, while looping through large register arrays.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_set_redistributor_reg(hv_vcpu_t vcpu, hv_gic_redistributor_reg_t reg, uint64_t value);

/*!
 @abstract Read a GIC ICC cpu system register.
 @param vcpu Handle for the vcpu.
 @param reg GIC ICC system register enum.
 @param value Pointer to ICC register value (written on success).
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    Must be called by the owning thread.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_get_icc_reg(hv_vcpu_t vcpu, hv_gic_icc_reg_t reg, uint64_t *value);

/*!
 @abstract Write a GIC ICC cpu system register.
 @param vcpu Handle for the vcpu.
 @param reg GIC ICC system register enum.
 @param value GIC ICC register value to be written.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    Must be called by the owning thread.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_set_icc_reg(hv_vcpu_t vcpu, hv_gic_icc_reg_t reg, uint64_t value);

/*!
 @abstract Read a GIC ICH virtualization control system register.
 @param vcpu Handle for the vcpu.
 @param reg GIC ICH system register enum.
 @param value Pointer to ICH register value (written on success).
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    ICH registers are only available when EL2 is enabled, otherwise returns
    an error.

    Must be called by the owning thread.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_get_ich_reg(hv_vcpu_t vcpu, hv_gic_ich_reg_t reg, uint64_t* value);

/*!
 @abstract Write a GIC ICH virtualization control system register.
 @param vcpu Handle for the vcpu.
 @param reg GIC ICH system register enum.
 @param value GIC ICH register value to be written.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    ICH registers are only available when EL2 is enabled, otherwise returns
    an error.

    Must be called by the owning thread.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_set_ich_reg(hv_vcpu_t vcpu, hv_gic_ich_reg_t reg, uint64_t value);

/*!
 @abstract Read a GIC ICV system register.
 @param vcpu Handle for the vcpu.
 @param reg GIC ICV system register enum.
 @param value Pointer to ICV register value (written on success).
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    ICV registers are only available when EL2 is enabled, otherwise returns
    an error.

    Must be called by the owning thread.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_get_icv_reg(hv_vcpu_t vcpu, hv_gic_icv_reg_t reg, uint64_t* value);

/*!
 @abstract Write a GIC ICV system register.
 @param vcpu Handle for the vcpu.
 @param reg GIC ICV system register enum.
 @param value GIC ICV register value to be written.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    ICV registers are only available when EL2 is enabled, otherwise returns
    an error.

    Must be called by the owning thread.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_set_icv_reg(hv_vcpu_t vcpu, hv_gic_icv_reg_t reg, uint64_t value);

/*!
 @abstract Read a GIC distributor MSI register.
 @param reg GIC distributor MSI register enum.
 @param value Pointer to distributor MSI register value (written on success).
 @result HV_SUCCESS on success, an error code otherwise.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_get_msi_reg(hv_gic_msi_reg_t reg, uint64_t *value);

/*!
 @abstract Write a GIC distributor MSI register.
 @param reg GIC distributor MSI register enum.
 @param value GIC distributor MSI register value to be written.
 @result HV_SUCCESS on success, an error code otherwise.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_set_msi_reg(hv_gic_msi_reg_t reg, uint64_t value);

/*!
 @abstract Set state for GIC device to be restored.
 @param gic_state_data Pointer to the state buffer to set GIC with.
 @param gic_state_size Size of GIC state buffer.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    GIC state can only be restored after a GIC device and vcpus have been
    created and must be done before vcpu's are run. The rest of the virtual
    machine including GIC CPU registers must also be restored compatibly with
    the gic_state.

    In some cases hv_gic_set_state() can fail if a software update has changed
    the host in a way that would be incompatible with the previous format.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_set_state(const void *gic_state_data, size_t gic_state_size);

/*!
 @abstract Reset the GIC device.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    When the virtual machine is being reset, call this function to reset the
    GIC distributor, redistributor registers and the internal state of the
    device.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_reset();

__END_DECLS

OS_ASSUME_NONNULL_END

#endif
