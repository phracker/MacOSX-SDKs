//
//  hv_vcpu.h
//  Hypervisor
//
//  Copyright © 2018-2024 Apple Inc. All rights reserved.
//

#pragma once

#ifdef __arm64__

#include <Hypervisor/hv_base.h>
#include <Hypervisor/hv_vcpu_types.h>

OS_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 @abstract Creates a vCPU instance for the current thread
 @param vcpu Pointer to the ID of the vCPU instance (written on success)
 @param exit Pointer to pointer to the vcpu exit information (written on success)
 @param config Configuration.
 @result 0 on success or error code
 @discussion Each thread can only have one vCPU associated at a time.
 */
OS_EXPORT API_AVAILABLE(macos(11.0))
hv_return_t hv_vcpu_create(hv_vcpu_t *vcpu, hv_vcpu_exit_t * _Nullable * _Nonnull exit,
    hv_vcpu_config_t _Nullable config);

/*!
 @abstract Destroys the vCPU instance associated with the current thread
 @param vcpu ID of the vCPU instance
 @result 0 on success or error code
 @discussion
    Must be called by the owning thread
 */
OS_EXPORT API_AVAILABLE(macos(11.0))
hv_return_t hv_vcpu_destroy(hv_vcpu_t vcpu);

/*!
 @abstract Returns the current value of a vCPU register.
 @param vcpu ID of the vCPU instance
 @param reg ID of the register.
 @param value Pointer to the register value.
 @result 0 on success or error code
 @discussion
    Must be called by the owning thread
 */
OS_EXPORT API_AVAILABLE(macos(11.0))
hv_return_t hv_vcpu_get_reg(hv_vcpu_t vcpu, hv_reg_t reg, uint64_t *value);

/*!
 @abstract Sets the value of a vCPU register.
 @param vcpu ID of the vCPU instance
 @param reg ID of the register.
 @param value The register value.
 @result 0 on success or error code
 @discussion
    Must be called by the owning thread
 */
OS_EXPORT API_AVAILABLE(macos(11.0))
hv_return_t hv_vcpu_set_reg(hv_vcpu_t vcpu, hv_reg_t reg, uint64_t value);

/*!
 @abstract Returns the current value of a vCPU SIMD&FP register
 @param vcpu ID of the vCPU instance
 @param reg ID of the SIMD&FP register.
 @param value Pointer to the register value.
 @result 0 on success or error code
 @discussion
    Must be called by the owning thread

    In streaming SVE mode, the SIMD Q registers are aliased to the bottom 128 bits of the
    corresponding Z register, and any modification will reflect on the Z register state.
 */
OS_EXPORT API_AVAILABLE(macos(11.0))
hv_return_t hv_vcpu_get_simd_fp_reg(hv_vcpu_t vcpu, hv_simd_fp_reg_t reg, hv_simd_fp_uchar16_t *value);

/*!
 @abstract Sets the value of a vCPU SIMD&FP register
 @param vcpu ID of the vCPU instance
 @param reg ID of the register.
 @param value The register value.
 @result 0 on success or error code
 @discussion
    Must be called by the owning thread

    In streaming SVE mode, the SIMD Q registers are aliased to the bottom 128 bits of the
    corresponding Z register, and any modification will reflect on the Z register state.
 */
OS_EXPORT API_AVAILABLE(macos(11.0))

hv_return_t hv_vcpu_set_simd_fp_reg(hv_vcpu_t vcpu, hv_simd_fp_reg_t reg, hv_simd_fp_uchar16_t value);

/*!
 @abstract Gets the current SME state consisting of the streaming SVE mode (PSTATE.SM) and ZA storage enable (PSTATE.ZA).
 @param vcpu ID of the vCPU instance.
 @param sme_state Pointer to the SME state.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    Must be called by the owning thread.

    In streaming SVE mode, the SIMD Q registers are aliased to the bottom 128 bits of the
    corresponding Z register, and any modification will reflect on the Z register state.

    Returns HV_UNSUPPORTED if SME is not supported.
 */
OS_EXPORT API_AVAILABLE(macos(15.2))
hv_return_t hv_vcpu_get_sme_state(hv_vcpu_t vcpu, hv_vcpu_sme_state_t *sme_state);

/*!
 @abstract Sets the SME state consisting of the streaming SVE mode and ZA storage enable.
 @param vcpu ID of the vCPU instance.
 @param sme_state Pointer to the SME state to set.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    Must be called by the owning thread.

    For any entry or exit from streaming SVE mode, all Z vector and P predicate registers
    are set to zero, and all FPSR flags are set; this state must be saved if it needs to be
    retained across streaming SVE mode transitions.

    In streaming SVE mode, the SIMD Q registers are aliased to the bottom 128 bits of the
    corresponding Z register, and any modification will reflect on the Z register state.

    If the optional FEAT_SME_FA64 is implemented, the full SIMD instruction set is supported
    in streaming SVE mode; otherwise many legacy SIMD instructions are illegal in this mode.

    When finished, disable streaming SVE mode and ZA storage; this serves as a power-down
    hint for SME-related hardware.

    Returns HV_UNSUPPORTED if SME is not supported.
 */
OS_EXPORT API_AVAILABLE(macos(15.2))
hv_return_t hv_vcpu_set_sme_state(hv_vcpu_t vcpu, const hv_vcpu_sme_state_t *sme_state);

/*!
 @abstract Returns the value of a vCPU Z vector register in streaming SVE mode.
 @param vcpu ID of the vCPU instance.
 @param reg ID of the Z vector register.
 @param value Pointer to the retrieved register value.
 @param length The length (in bytes) of the provided value storage.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    Must be called by the owning thread.

    Returns an error if not in streaming SVE mode (i.e. streaming_sve_mode_enabled is false),
    or if the provided value storage is not maximum SVL bytes.
 */
OS_EXPORT API_AVAILABLE(macos(15.2))
hv_return_t hv_vcpu_get_sme_z_reg(hv_vcpu_t vcpu, hv_sme_z_reg_t reg, uint8_t *value, size_t length);

/*!
 @abstract Sets the value of a vCPU Z vector register in streaming SVE mode.
 @param vcpu ID of the vCPU instance.
 @param reg ID of the Z vector register.
 @param value Pointer to the register value to set.
 @param length The length (in bytes) of the Z register value.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    Must be called by the owning thread.

    Returns an error if not in streaming SVE mode (i.e. streaming_sve_mode_enabled is false),
    or if the value length is not maximum SVL bytes.
 */
OS_EXPORT API_AVAILABLE(macos(15.2))
hv_return_t hv_vcpu_set_sme_z_reg(hv_vcpu_t vcpu, hv_sme_z_reg_t reg, const uint8_t *value, size_t length);

/*!
 @abstract Returns the value of a vCPU P predicate register in streaming SVE mode.
 @param vcpu ID of the vCPU instance.
 @param reg ID of the P predicate register.
 @param value Pointer to the retrieved register value.
 @param length The length (in bytes) of the provided value storage.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    Must be called by the owning thread.

    Returns an error if not in streaming SVE mode (i.e. streaming_sve_mode_enabled is false),
    or if the provided value storage is not maximum SVL / 8 bytes.
 */
OS_EXPORT API_AVAILABLE(macos(15.2))
hv_return_t hv_vcpu_get_sme_p_reg(hv_vcpu_t vcpu, hv_sme_p_reg_t reg, uint8_t *value, size_t length);

/*!
 @abstract Sets the value of a vCPU P predicate register in streaming SVE mode.
 @param vcpu ID of the vCPU instance.
 @param reg ID of the P predicate register.
 @param value Pointer to the register value to set.
 @param length The length (in bytes) of the P register value.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    Must be called by the owning thread.

    Returns an error if not in streaming SVE mode (i.e. streaming_sve_mode_enabled is false),
    or if the value length is not the maximum SVL / 8 bytes.
 */
OS_EXPORT API_AVAILABLE(macos(15.2))
hv_return_t hv_vcpu_set_sme_p_reg(hv_vcpu_t vcpu, hv_sme_p_reg_t reg, const uint8_t *value, size_t length);

/*!
 @abstract Returns the value of the vCPU ZA matrix register in streaming SVE mode.
 @param vcpu ID of the vCPU instance.
 @param value Pointer to the retrieved register value.
 @param length The length (in bytes) of the provided value storage.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    Must be called by the owning thread.

    Returns an error if PSTATE.ZA is 0 (i.e. za_storage_enabled is false), or if the provided value storage
    is not [maximum SVL bytes x maximum SVL bytes].

    Does not require streaming SVE mode enabled.
 */
OS_EXPORT API_AVAILABLE(macos(15.2))
hv_return_t hv_vcpu_get_sme_za_reg(hv_vcpu_t vcpu, uint8_t *value, size_t length);

/*!
 @abstract Sets the value of the vCPU ZA matrix register in streaming SVE mode.
 @param vcpu ID of the vCPU instance.
 @param value Pointer to the register value to set.
 @param length The length (in bytes) of the provided ZA register value.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    Must be called by the owning thread.

    Returns an error if PSTATE.ZA is 0 (i.e. za_storage_enabled is false), or if the value length
    is not [maximum SVL bytes x maximum SVL bytes].

    Does not require streaming SVE mode enabled.
 */
OS_EXPORT API_AVAILABLE(macos(15.2))
hv_return_t hv_vcpu_set_sme_za_reg(hv_vcpu_t vcpu, const uint8_t *value, size_t length);

/*!
 @abstract Returns the current value of the vCPU ZT0 register in streaming SVE mode.
 @param vcpu ID of the vCPU instance.
 @param value Pointer to the retrieved register value.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    Must be called by the owning thread.

    Returns an error if PSTATE.ZA is 0 (i.e. za_storage_enabled is false).

    Does not require streaming SVE mode enabled.
 */
OS_EXPORT API_AVAILABLE(macos(15.2))
hv_return_t hv_vcpu_get_sme_zt0_reg(hv_vcpu_t vcpu, hv_sme_zt0_uchar64_t *value);

/*!
 @abstract Sets the value of the vCPU ZT0 register in streaming SVE mode.
 @param vcpu ID of the vCPU instance.
 @param value Pointer to the register value to set.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    Must be called by the owning thread.

    Returns an error if PSTATE.ZA is 0 (i.e. za_storage_enabled is false).

    Does not require streaming SVE mode enabled.
 */
OS_EXPORT API_AVAILABLE(macos(15.2))
hv_return_t hv_vcpu_set_sme_zt0_reg(hv_vcpu_t vcpu, const hv_sme_zt0_uchar64_t *value);

/*!
 @abstract Returns the current value of a vCPU system register
 @param vcpu ID of the vCPU instance
 @param reg ID of the system register.
 @param value Pointer to the system register value.
 @result 0 on success or error code
 @discussion
    Must be called by the owning thread
 */
OS_EXPORT API_AVAILABLE(macos(11.0))
hv_return_t hv_vcpu_get_sys_reg(hv_vcpu_t vcpu, hv_sys_reg_t reg, uint64_t *value);

/*!
 @abstract Sets the value of a vCPU system register
 @param vcpu ID of the vCPU instance
 @param reg ID of the system register.
 @param value The system register value.
 @result 0 on success or error code
 @discussion
    Must be called by the owning thread
 */
OS_EXPORT API_AVAILABLE(macos(11.0))
hv_return_t hv_vcpu_set_sys_reg(hv_vcpu_t vcpu, hv_sys_reg_t reg, uint64_t value);

/*!
 @abstract Gets pending interrupts for a vcpu.
 @param vcpu ID of the vcpu instance.
 @param type Interrupt type.
 @param pending Returns whether the interrupt is pending or not.
 @discussion
    Must be called by the owning thread.
 */
OS_EXPORT API_AVAILABLE(macos(11.0))
hv_return_t hv_vcpu_get_pending_interrupt(hv_vcpu_t vcpu, hv_interrupt_type_t type, bool *pending);

/*!
 @abstract Sets pending interrupts for a vcpu.
 @param vcpu ID of the vcpu instance.
 @param type Interrupt type.
 @param pending Whether the interrupt is pending or not.
 @discussion
    Must be called by the owning thread.
    The pending interrupts automatically cleared after hv_vcpu_run returns. It is expected that
    hv_vcpu_set_pending_interrupt be called before every hv_vcpu_run to set pending interrupts.
 */
OS_EXPORT API_AVAILABLE(macos(11.0))
hv_return_t hv_vcpu_set_pending_interrupt(hv_vcpu_t vcpu, hv_interrupt_type_t type, bool pending);

/*!
 @abstract Get whether debug exceptions in the guest are trapped to the host.
 @param vcpu ID of the vcpu instance.
 @param value Pointer to the result.
 @discussion
    Must be called by the owning thread.
 */
OS_EXPORT API_AVAILABLE(macos(11.0))
hv_return_t hv_vcpu_get_trap_debug_exceptions(hv_vcpu_t vcpu, bool *value);

/*!
 @abstract Set whether debug exceptions in the guest are trapped to the host.
 @param vcpu ID of the vcpu instance.
 @param value If true, debug exceptions in the guest are trapped to the host
 @discussion
    Must be called by the owning thread.
 */
OS_EXPORT API_AVAILABLE(macos(11.0))
hv_return_t hv_vcpu_set_trap_debug_exceptions(hv_vcpu_t vcpu, bool value);

/*!
 @abstract Get whether debug register accesses in the guest are trapped to the host.
 @param vcpu ID of the vcpu instance.
 @param value Pointer to the result.
 @discussion
    Must be called by the owning thread.
    This includes the DBGBCR<n>_EL1, DBGBVR<n>_EL1, DBGWCR<n>_EL1,
    DBGWVR<n>_EL1 and MDSCR_EL1 registers.
 */
OS_EXPORT API_AVAILABLE(macos(11.0))
hv_return_t hv_vcpu_get_trap_debug_reg_accesses(hv_vcpu_t vcpu, bool *value);

/*!
 @abstract Set whether debug register accesses in the guest are trapped to the host.
 @param vcpu ID of the vcpu instance.
 @param value If true, debug register accesses in the guest are trapped to the host.
 @discussion
    Must be called by the owning thread.
    This includes the DBGBCR<n>_EL1, DBGBVR<n>_EL1, DBGWCR<n>_EL1,
    DBGWVR<n>_EL1 and MDSCR_EL1 registers.
 */
OS_EXPORT API_AVAILABLE(macos(11.0))
hv_return_t hv_vcpu_set_trap_debug_reg_accesses(hv_vcpu_t vcpu, bool value);

/*!
 @abstract Executes a vCPU
 @param vcpu ID of the vCPU instance
 @result 0 on success or error code
 @discussion
    Call blocks until the next exit from the vCPU or the
    execution is canceled using hv_vcpus_exit.

    Must be called by the owning thread
 */
OS_EXPORT API_AVAILABLE(macos(11.0))
hv_return_t hv_vcpu_run(hv_vcpu_t vcpu);

/*!
 @abstract Forces an immediate exit of a set of vcpus of the VM.
 @param vcpus Pointer to a list of vcpu IDs
 @param vcpu_count  Number of vcpus in the list
 @result 0 on success or error code
 @discussion
    If a vcpu is not running, the next time hv_vcpu_run is called for the corresponding
    vcpu, it will return immediately without entering the guest.
 */
OS_EXPORT API_AVAILABLE(macos(11.0))
hv_return_t hv_vcpus_exit(hv_vcpu_t *vcpus, uint32_t vcpu_count);

/*!
 @abstract Returns the cumulative execution time of a vCPU in units of mach_absolute_time().
 @param vcpu vCPU ID
 @param time Pointer to execution time value (written on success)
 @result 0 on success or error code
 @discussion
    Must be called by the owning thread
 */
OS_EXPORT API_AVAILABLE(macos(11.0))
hv_return_t hv_vcpu_get_exec_time(hv_vcpu_t vcpu, uint64_t *time);

/*!
 @abstract Gets the VTimer mask.
 @param vcpu ID of the vcpu instance.
 @param vtimer_is_masked Value of the mask.
 @result 0 on success or error code.
 */
OS_EXPORT API_AVAILABLE(macos(11.0))
hv_return_t hv_vcpu_get_vtimer_mask(hv_vcpu_t vcpu, bool *vtimer_is_masked);

/*!
 @abstract Sets the VTimer mask.
 @param vcpu ID of the vcpu instance.
 @param vtimer_is_masked New value of the mask.
 @result 0 on success or error code.
 @discussion
    When the mask is set, the vCPU does not exit if the VTimer times out.

    After hv_vcpu_run() returns with the exit reason
    HV_EXIT_REASON_VTIMER_ACTIVATED, the timer is masked automatically.
    The vCPU will not exit with this reason again until the masked is cleared
    even when hv_vcpu_run() is called with the VTimer interrupt in a
    pending state.

    After receiving a HV_EXIT_REASON_VTIMER_ACTIVATED exit reason,
    the caller of hv_vcpu_run() is expected to make the interrupt
    corresponding to the VTimer pending in the guest's virtual
    interrupt controller and to be able to detect when
    the guest has completed servicing this interrupt. For example,
    when emulating a GIC, this function should be called when
    deactivating an interrupt whose ID matches that of the VTimer.
 */
OS_EXPORT API_AVAILABLE(macos(11.0))
hv_return_t hv_vcpu_set_vtimer_mask(hv_vcpu_t vcpu, bool vtimer_is_masked);

/*!
 @abstract Gets the VTimer offset.
 @param vcpu ID of the vCPU instance.
 @param vtimer_offset Pointer to VTimer offset. (Written on success).
 @result 0 on success or error code.
 @seealso hv_vcpu_set_vtimer_offset
 */
OS_EXPORT API_AVAILABLE(macos(11.0))
hv_return_t hv_vcpu_get_vtimer_offset(hv_vcpu_t vcpu, uint64_t *vtimer_offset);

/*!
 @abstract Sets the VTimer offset.
 @param vcpu ID of the vCPU instance.
 @param vtimer_offset New VTimer offset.
 @result 0 on success or error code.
 @discussion
    This specifies how the CNTVCT_EL0 register relates to mach_absolute_time():

    CNTVCT_EL0 = mach_absolute_time() - vtimer_offset.
 */
OS_EXPORT API_AVAILABLE(macos(11.0))
hv_return_t hv_vcpu_set_vtimer_offset(hv_vcpu_t vcpu, uint64_t vtimer_offset);

__END_DECLS

OS_ASSUME_NONNULL_END

#endif
