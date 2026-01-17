//
//  hv_vcpu_types.h
//  Hypervisor
//
//  Copyright © 2018-2025 Apple Inc. All rights reserved.
//

#pragma once

#ifdef __arm64__

#include <Hypervisor/hv_base.h>
#include <Hypervisor/hv_vm_types.h>
#include <arm64/hv/hv_kern_types.h>
#include <os/object.h>

OS_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 @abstract Configuration for hv_vcpu_create().
*/
#if OS_OBJECT_USE_OBJC
OS_OBJECT_DECL(hv_vcpu_config);
#else // OS_OBJECT_USE_OBJC
typedef struct hv_vcpu_config_s *hv_vcpu_config_t;
#endif // OS_OBJECT_USE_OBJC

/*!
 @abstract Type of a vcpu instance ID
 */
typedef uint64_t hv_vcpu_t;

/*!
 @abstract Events that can trigger a guest exit to the VMM
 */
OS_ENUM(hv_exit_reason, uint32_t,
    /*! asynchronous exit requested explicitly by hv_vcpus_exit() call */
    HV_EXIT_REASON_CANCELED,
    /*! synchronous exception to a higher EL triggered by the guest */
    HV_EXIT_REASON_EXCEPTION,
    /*!
     ARM Generic VTimer became pending since the last hv_vcpu_run() call
     returned. The caller is expected to make the interrupt corresponding to
     the VTimer pending in the guest's interrupt controller.

     This exit automatically sets the VTimer mask.
     The VCPU will not exit with this status again until after the mask is cleared
     with hv_vcpu_set_vtimer_mask(), which should be called during a trap of
     the EOI for the guest's VTimer interrupt handler.
     */
    HV_EXIT_REASON_VTIMER_ACTIVATED,
    /*!
     Unable to determine exit reason: this should not happen under normal
     operation.
     */
    HV_EXIT_REASON_UNKNOWN
);

/*!
 @abstract Type of a vcpu exception syndrome (Corresponds to ESR_ELx).
 */
typedef uint64_t hv_exception_syndrome_t;

/*!
 @abstract Type of a vcpu exception virtual address. (Corresponds to FAR_ELx).
 */
typedef uint64_t hv_exception_address_t;

/*!
 @abstract Contains details of a vcpu exception.
 */
typedef struct {
    hv_exception_syndrome_t syndrome;
    hv_exception_address_t virtual_address;
    hv_ipa_t physical_address;
} hv_vcpu_exit_exception_t;

/*!
 @abstract Contains information about an exit from the vcpu to the host.
 */
typedef struct {
    hv_exit_reason_t reason;
    hv_vcpu_exit_exception_t exception;
} hv_vcpu_exit_t;

/*!
 @abstract Value of an ARM SIMD&FP register.
 */
typedef __attribute__((ext_vector_type(16))) uint8_t hv_simd_fp_uchar16_t;

/*!
 @abstract Type of an ARM register.
 @discussion
    Represents the X0-X30 GPRs, the Program Counter (PC), the Floating-point Control
    and Status registers (FPCR and FPSR), and the Current Program Status Register (CPSR).
 */
OS_ENUM(hv_reg, uint32_t,
    HV_REG_X0,
    HV_REG_X1,
    HV_REG_X2,
    HV_REG_X3,
    HV_REG_X4,
    HV_REG_X5,
    HV_REG_X6,
    HV_REG_X7,
    HV_REG_X8,
    HV_REG_X9,
    HV_REG_X10,
    HV_REG_X11,
    HV_REG_X12,
    HV_REG_X13,
    HV_REG_X14,
    HV_REG_X15,
    HV_REG_X16,
    HV_REG_X17,
    HV_REG_X18,
    HV_REG_X19,
    HV_REG_X20,
    HV_REG_X21,
    HV_REG_X22,
    HV_REG_X23,
    HV_REG_X24,
    HV_REG_X25,
    HV_REG_X26,
    HV_REG_X27,
    HV_REG_X28,
    HV_REG_X29,
    HV_REG_FP = HV_REG_X29,
    HV_REG_X30,
    HV_REG_LR = HV_REG_X30,
    HV_REG_PC,
    HV_REG_FPCR,
    HV_REG_FPSR,
    HV_REG_CPSR,
);

/*!
 @abstract Type of an ARM SIMD&FP register.
 */
OS_ENUM(hv_simd_fp_reg, uint32_t,
    HV_SIMD_FP_REG_Q0,
    HV_SIMD_FP_REG_Q1,
    HV_SIMD_FP_REG_Q2,
    HV_SIMD_FP_REG_Q3,
    HV_SIMD_FP_REG_Q4,
    HV_SIMD_FP_REG_Q5,
    HV_SIMD_FP_REG_Q6,
    HV_SIMD_FP_REG_Q7,
    HV_SIMD_FP_REG_Q8,
    HV_SIMD_FP_REG_Q9,
    HV_SIMD_FP_REG_Q10,
    HV_SIMD_FP_REG_Q11,
    HV_SIMD_FP_REG_Q12,
    HV_SIMD_FP_REG_Q13,
    HV_SIMD_FP_REG_Q14,
    HV_SIMD_FP_REG_Q15,
    HV_SIMD_FP_REG_Q16,
    HV_SIMD_FP_REG_Q17,
    HV_SIMD_FP_REG_Q18,
    HV_SIMD_FP_REG_Q19,
    HV_SIMD_FP_REG_Q20,
    HV_SIMD_FP_REG_Q21,
    HV_SIMD_FP_REG_Q22,
    HV_SIMD_FP_REG_Q23,
    HV_SIMD_FP_REG_Q24,
    HV_SIMD_FP_REG_Q25,
    HV_SIMD_FP_REG_Q26,
    HV_SIMD_FP_REG_Q27,
    HV_SIMD_FP_REG_Q28,
    HV_SIMD_FP_REG_Q29,
    HV_SIMD_FP_REG_Q30,
    HV_SIMD_FP_REG_Q31,
);

/*!
 @abstract Contains information about SME PSTATE.
 @discussion
    streaming_sve_mode_enabled controls PSTATE.SM and za_storage_enabled controls PSTATE.ZA.
 */
API_AVAILABLE(macos(15.2))
typedef struct {
    bool streaming_sve_mode_enabled;
    bool za_storage_enabled;
} hv_vcpu_sme_state_t;

/*!
 @abstract Type of an ARM SME Z vector register.
 */
OS_ENUM(hv_sme_z_reg, uint32_t,
    HV_SME_Z_REG_0,
    HV_SME_Z_REG_1,
    HV_SME_Z_REG_2,
    HV_SME_Z_REG_3,
    HV_SME_Z_REG_4,
    HV_SME_Z_REG_5,
    HV_SME_Z_REG_6,
    HV_SME_Z_REG_7,
    HV_SME_Z_REG_8,
    HV_SME_Z_REG_9,
    HV_SME_Z_REG_10,
    HV_SME_Z_REG_11,
    HV_SME_Z_REG_12,
    HV_SME_Z_REG_13,
    HV_SME_Z_REG_14,
    HV_SME_Z_REG_15,
    HV_SME_Z_REG_16,
    HV_SME_Z_REG_17,
    HV_SME_Z_REG_18,
    HV_SME_Z_REG_19,
    HV_SME_Z_REG_20,
    HV_SME_Z_REG_21,
    HV_SME_Z_REG_22,
    HV_SME_Z_REG_23,
    HV_SME_Z_REG_24,
    HV_SME_Z_REG_25,
    HV_SME_Z_REG_26,
    HV_SME_Z_REG_27,
    HV_SME_Z_REG_28,
    HV_SME_Z_REG_29,
    HV_SME_Z_REG_30,
    HV_SME_Z_REG_31,
) API_AVAILABLE(macos(15.2));

/*!
 @abstract Type of an ARM SME P predicate register.
 */
OS_ENUM(hv_sme_p_reg, uint32_t,
    HV_SME_P_REG_0,
    HV_SME_P_REG_1,
    HV_SME_P_REG_2,
    HV_SME_P_REG_3,
    HV_SME_P_REG_4,
    HV_SME_P_REG_5,
    HV_SME_P_REG_6,
    HV_SME_P_REG_7,
    HV_SME_P_REG_8,
    HV_SME_P_REG_9,
    HV_SME_P_REG_10,
    HV_SME_P_REG_11,
    HV_SME_P_REG_12,
    HV_SME_P_REG_13,
    HV_SME_P_REG_14,
    HV_SME_P_REG_15,
) API_AVAILABLE(macos(15.2));

/*!
 @abstract Type of the SME2 ZT0 register.
 */
API_AVAILABLE(macos(15.2))
typedef __attribute__((ext_vector_type(64))) uint8_t hv_sme_zt0_uchar64_t;

/*!
 @abstract Type of an ARM system register.
*/
OS_ENUM(hv_sys_reg, uint16_t,
    HV_SYS_REG_DBGBVR0_EL1 = 0x8004,
    HV_SYS_REG_DBGBCR0_EL1 = 0x8005,
    HV_SYS_REG_DBGWVR0_EL1 = 0x8006,
    HV_SYS_REG_DBGWCR0_EL1 = 0x8007,
    HV_SYS_REG_DBGBVR1_EL1 = 0x800c,
    HV_SYS_REG_DBGBCR1_EL1 = 0x800d,
    HV_SYS_REG_DBGWVR1_EL1 = 0x800e,
    HV_SYS_REG_DBGWCR1_EL1 = 0x800f,
    HV_SYS_REG_MDCCINT_EL1 = 0x8010,
    HV_SYS_REG_MDSCR_EL1 = 0x8012,
    HV_SYS_REG_DBGBVR2_EL1 = 0x8014,
    HV_SYS_REG_DBGBCR2_EL1 = 0x8015,
    HV_SYS_REG_DBGWVR2_EL1 = 0x8016,
    HV_SYS_REG_DBGWCR2_EL1 = 0x8017,
    HV_SYS_REG_DBGBVR3_EL1 = 0x801c,
    HV_SYS_REG_DBGBCR3_EL1 = 0x801d,
    HV_SYS_REG_DBGWVR3_EL1 = 0x801e,
    HV_SYS_REG_DBGWCR3_EL1 = 0x801f,
    HV_SYS_REG_DBGBVR4_EL1 = 0x8024,
    HV_SYS_REG_DBGBCR4_EL1 = 0x8025,
    HV_SYS_REG_DBGWVR4_EL1 = 0x8026,
    HV_SYS_REG_DBGWCR4_EL1 = 0x8027,
    HV_SYS_REG_DBGBVR5_EL1 = 0x802c,
    HV_SYS_REG_DBGBCR5_EL1 = 0x802d,
    HV_SYS_REG_DBGWVR5_EL1 = 0x802e,
    HV_SYS_REG_DBGWCR5_EL1 = 0x802f,
    HV_SYS_REG_DBGBVR6_EL1 = 0x8034,
    HV_SYS_REG_DBGBCR6_EL1 = 0x8035,
    HV_SYS_REG_DBGWVR6_EL1 = 0x8036,
    HV_SYS_REG_DBGWCR6_EL1 = 0x8037,
    HV_SYS_REG_DBGBVR7_EL1 = 0x803c,
    HV_SYS_REG_DBGBCR7_EL1 = 0x803d,
    HV_SYS_REG_DBGWVR7_EL1 = 0x803e,
    HV_SYS_REG_DBGWCR7_EL1 = 0x803f,
    HV_SYS_REG_DBGBVR8_EL1 = 0x8044,
    HV_SYS_REG_DBGBCR8_EL1 = 0x8045,
    HV_SYS_REG_DBGWVR8_EL1 = 0x8046,
    HV_SYS_REG_DBGWCR8_EL1 = 0x8047,
    HV_SYS_REG_DBGBVR9_EL1 = 0x804c,
    HV_SYS_REG_DBGBCR9_EL1 = 0x804d,
    HV_SYS_REG_DBGWVR9_EL1 = 0x804e,
    HV_SYS_REG_DBGWCR9_EL1 = 0x804f,
    HV_SYS_REG_DBGBVR10_EL1 = 0x8054,
    HV_SYS_REG_DBGBCR10_EL1 = 0x8055,
    HV_SYS_REG_DBGWVR10_EL1 = 0x8056,
    HV_SYS_REG_DBGWCR10_EL1 = 0x8057,
    HV_SYS_REG_DBGBVR11_EL1 = 0x805c,
    HV_SYS_REG_DBGBCR11_EL1 = 0x805d,
    HV_SYS_REG_DBGWVR11_EL1 = 0x805e,
    HV_SYS_REG_DBGWCR11_EL1 = 0x805f,
    HV_SYS_REG_DBGBVR12_EL1 = 0x8064,
    HV_SYS_REG_DBGBCR12_EL1 = 0x8065,
    HV_SYS_REG_DBGWVR12_EL1 = 0x8066,
    HV_SYS_REG_DBGWCR12_EL1 = 0x8067,
    HV_SYS_REG_DBGBVR13_EL1 = 0x806c,
    HV_SYS_REG_DBGBCR13_EL1 = 0x806d,
    HV_SYS_REG_DBGWVR13_EL1 = 0x806e,
    HV_SYS_REG_DBGWCR13_EL1 = 0x806f,
    HV_SYS_REG_DBGBVR14_EL1 = 0x8074,
    HV_SYS_REG_DBGBCR14_EL1 = 0x8075,
    HV_SYS_REG_DBGWVR14_EL1 = 0x8076,
    HV_SYS_REG_DBGWCR14_EL1 = 0x8077,
    HV_SYS_REG_DBGBVR15_EL1 = 0x807c,
    HV_SYS_REG_DBGBCR15_EL1 = 0x807d,
    HV_SYS_REG_DBGWVR15_EL1 = 0x807e,
    HV_SYS_REG_DBGWCR15_EL1 = 0x807f,
    HV_SYS_REG_MIDR_EL1 = 0xc000,
    HV_SYS_REG_MPIDR_EL1 = 0xc005,
    HV_SYS_REG_ID_AA64PFR0_EL1 = 0xc020,
    HV_SYS_REG_ID_AA64PFR1_EL1 = 0xc021,
    HV_SYS_REG_ID_AA64ZFR0_EL1 API_AVAILABLE(macos(15.2)) = 0xc024,
    HV_SYS_REG_ID_AA64SMFR0_EL1 API_AVAILABLE(macos(15.2)) = 0xc025,
    HV_SYS_REG_ID_AA64DFR0_EL1 = 0xc028,
    HV_SYS_REG_ID_AA64DFR1_EL1 = 0xc029,
    HV_SYS_REG_ID_AA64ISAR0_EL1 = 0xc030,
    HV_SYS_REG_ID_AA64ISAR1_EL1 = 0xc031,
    HV_SYS_REG_ID_AA64MMFR0_EL1 = 0xc038,
    HV_SYS_REG_ID_AA64MMFR1_EL1 = 0xc039,
    HV_SYS_REG_ID_AA64MMFR2_EL1 = 0xc03a,
    HV_SYS_REG_SCTLR_EL1 = 0xc080,

    /*!
     @abstract The ACTLR_EL1 register
     @discussion
        This only allows getting / setting of the ACTLR_EL1.EnTSO bit (index 1). Setting this bit to 1
        will cause the vcpu to use a TSO memory model, whereas clearing it will cause the vcpu to use
        the default ARM64 memory model (weakly ordered loads / stores).
    */
    HV_SYS_REG_ACTLR_EL1 API_AVAILABLE(macos(15.0)) = 0xc081,
    HV_SYS_REG_CPACR_EL1 = 0xc082,
    HV_SYS_REG_SMPRI_EL1 API_AVAILABLE(macos(15.2)) = 0xc094,
    HV_SYS_REG_SMCR_EL1 API_AVAILABLE(macos(15.2)) = 0xc096,
    HV_SYS_REG_TTBR0_EL1 = 0xc100,
    HV_SYS_REG_TTBR1_EL1 = 0xc101,
    HV_SYS_REG_TCR_EL1 = 0xc102,
    HV_SYS_REG_APIAKEYLO_EL1 = 0xc108,
    HV_SYS_REG_APIAKEYHI_EL1 = 0xc109,
    HV_SYS_REG_APIBKEYLO_EL1 = 0xc10a,
    HV_SYS_REG_APIBKEYHI_EL1 = 0xc10b,
    HV_SYS_REG_APDAKEYLO_EL1 = 0xc110,
    HV_SYS_REG_APDAKEYHI_EL1 = 0xc111,
    HV_SYS_REG_APDBKEYLO_EL1 = 0xc112,
    HV_SYS_REG_APDBKEYHI_EL1 = 0xc113,
    HV_SYS_REG_APGAKEYLO_EL1 = 0xc118,
    HV_SYS_REG_APGAKEYHI_EL1 = 0xc119,
    HV_SYS_REG_SPSR_EL1 = 0xc200,
    HV_SYS_REG_ELR_EL1 = 0xc201,
    HV_SYS_REG_SP_EL0 = 0xc208,
    HV_SYS_REG_AFSR0_EL1 = 0xc288,
    HV_SYS_REG_AFSR1_EL1 = 0xc289,
    HV_SYS_REG_ESR_EL1 = 0xc290,
    HV_SYS_REG_FAR_EL1 = 0xc300,
    HV_SYS_REG_PAR_EL1 = 0xc3a0,
    HV_SYS_REG_MAIR_EL1 = 0xc510,
    HV_SYS_REG_AMAIR_EL1 = 0xc518,
    HV_SYS_REG_VBAR_EL1 = 0xc600,
    HV_SYS_REG_CONTEXTIDR_EL1 = 0xc681,
    HV_SYS_REG_TPIDR_EL1 = 0xc684,
    HV_SYS_REG_SCXTNUM_EL1 API_AVAILABLE(macos(15.2)) = 0xc687,
    HV_SYS_REG_CNTKCTL_EL1 = 0xc708,
    HV_SYS_REG_CSSELR_EL1 = 0xd000,
    HV_SYS_REG_TPIDR_EL0 = 0xde82,
    HV_SYS_REG_TPIDRRO_EL0 = 0xde83,
    HV_SYS_REG_TPIDR2_EL0 API_AVAILABLE(macos(15.2)) = 0xde85,
    HV_SYS_REG_SCXTNUM_EL0 API_AVAILABLE(macos(15.2)) = 0xde87,
    HV_SYS_REG_CNTV_CTL_EL0 = 0xdf19,
    HV_SYS_REG_CNTV_CVAL_EL0 = 0xdf1a,
    HV_SYS_REG_SP_EL1 = 0xe208,

    // Physical timer registers.
    // These registers are only available if the VM was created with a GIC device (hv_gic_create).
    HV_SYS_REG_CNTP_CTL_EL0 API_AVAILABLE(macos(15.0)) = 0xdf11,
    HV_SYS_REG_CNTP_CVAL_EL0 API_AVAILABLE(macos(15.0)) = 0xdf12,
    HV_SYS_REG_CNTP_TVAL_EL0 API_AVAILABLE(macos(15.0)) = 0xdf10,

    // Exception Level 2 (EL2) registers.
    // These registers are only available if EL2 was enabled in the VM configuration.
    HV_SYS_REG_CNTHCTL_EL2 API_AVAILABLE(macos(15.0)) = 0xe708,
    HV_SYS_REG_CNTHP_CTL_EL2 API_AVAILABLE(macos(15.0)) = 0xe711,
    HV_SYS_REG_CNTHP_CVAL_EL2 API_AVAILABLE(macos(15.0)) = 0xe712,
    HV_SYS_REG_CNTHP_TVAL_EL2 API_AVAILABLE(macos(15.0)) = 0xe710,
    HV_SYS_REG_CNTVOFF_EL2 API_AVAILABLE(macos(15.0)) = 0xe703,
    HV_SYS_REG_CPTR_EL2 API_AVAILABLE(macos(15.0)) = 0xe08a,
    HV_SYS_REG_ELR_EL2 API_AVAILABLE(macos(15.0)) = 0xe201,
    HV_SYS_REG_ESR_EL2 API_AVAILABLE(macos(15.0)) = 0xe290,
    HV_SYS_REG_FAR_EL2 API_AVAILABLE(macos(15.0)) = 0xe300,
    HV_SYS_REG_HCR_EL2 API_AVAILABLE(macos(15.0)) = 0xe088,
    HV_SYS_REG_HPFAR_EL2 API_AVAILABLE(macos(15.0)) = 0xe304,
    HV_SYS_REG_MAIR_EL2 API_AVAILABLE(macos(15.0)) = 0xe510,
    HV_SYS_REG_MDCR_EL2 API_AVAILABLE(macos(15.0)) = 0xe089,
    HV_SYS_REG_SCTLR_EL2 API_AVAILABLE(macos(15.0)) = 0xe080,
    HV_SYS_REG_SPSR_EL2 API_AVAILABLE(macos(15.0)) = 0xe200,
    HV_SYS_REG_SP_EL2 API_AVAILABLE(macos(15.0)) = 0xf208,
    HV_SYS_REG_TCR_EL2 API_AVAILABLE(macos(15.0)) = 0xe102,
    HV_SYS_REG_TPIDR_EL2 API_AVAILABLE(macos(15.0)) = 0xe682,
    HV_SYS_REG_TTBR0_EL2 API_AVAILABLE(macos(15.0)) = 0xe100,
    HV_SYS_REG_TTBR1_EL2 API_AVAILABLE(macos(15.0)) = 0xe101,
    HV_SYS_REG_VBAR_EL2 API_AVAILABLE(macos(15.0)) = 0xe600,
    HV_SYS_REG_VMPIDR_EL2 API_AVAILABLE(macos(15.0)) = 0xe005,
    HV_SYS_REG_VPIDR_EL2 API_AVAILABLE(macos(15.0)) = 0xe000,
    HV_SYS_REG_VTCR_EL2 API_AVAILABLE(macos(15.0)) = 0xe10a,
    HV_SYS_REG_VTTBR_EL2 API_AVAILABLE(macos(15.0)) = 0xe108,
);

/*!
 @abstract Injected interrupt type.
 @discussion Passed to hv_vcpu_get_interrupt_level and hv_vcpu_set_interrupt_level to get
    and set virtual interrupt levels.
*/
OS_ENUM(hv_interrupt_type, uint32_t,
    /*! Corresponds to an ARM IRQ .*/
    HV_INTERRUPT_TYPE_IRQ,

    /*! Corresponds to an ARM FIQ. */
    HV_INTERRUPT_TYPE_FIQ,
);

/*!
 @abstract Cache type.
*/
OS_ENUM(hv_cache_type, uint32_t,
    /*! Data or unified cache */
    HV_CACHE_TYPE_DATA,

    /*! Instruction cache */
    HV_CACHE_TYPE_INSTRUCTION,
);

__END_DECLS

OS_ASSUME_NONNULL_END

#endif
