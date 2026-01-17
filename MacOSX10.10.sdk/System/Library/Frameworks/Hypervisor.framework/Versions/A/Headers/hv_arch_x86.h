/*
 *  hv_arch_x86.h
 *  Hypervisor Framework
 *
 *  Copyright (c) 2013 Apple Inc. All rights reserved.
 */

#ifndef __HYPERVISOR_HV_ARCH_X86__
#define __HYPERVISOR_HV_ARCH_X86__

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @enum       hv_x86_reg_t
 * @abstract   x86 architectural register IDs
 */
typedef enum {
	HV_X86_RIP,
	HV_X86_RFLAGS,
	HV_X86_RAX,
	HV_X86_RCX,
	HV_X86_RDX,
	HV_X86_RBX,
	HV_X86_RSI,
	HV_X86_RDI,
	HV_X86_RSP,
	HV_X86_RBP,
	HV_X86_R8,
	HV_X86_R9,
	HV_X86_R10,
	HV_X86_R11,
	HV_X86_R12,
	HV_X86_R13,
	HV_X86_R14,
	HV_X86_R15,
	HV_X86_CS,
	HV_X86_SS,
	HV_X86_DS,
	HV_X86_ES,
	HV_X86_FS,
	HV_X86_GS,
	HV_X86_IDT_BASE,
	HV_X86_IDT_LIMIT,
	HV_X86_GDT_BASE,
	HV_X86_GDT_LIMIT,
	HV_X86_LDTR,
	HV_X86_LDT_BASE,
	HV_X86_LDT_LIMIT,
	HV_X86_LDT_AR,
	HV_X86_TR,
	HV_X86_TSS_BASE,
	HV_X86_TSS_LIMIT,
	HV_X86_TSS_AR,
	HV_X86_CR0,
	HV_X86_CR1,
	HV_X86_CR2,
	HV_X86_CR3,
	HV_X86_CR4,
	HV_X86_DR0,
	HV_X86_DR1,
	HV_X86_DR2,
	HV_X86_DR3,
	HV_X86_DR4,
	HV_X86_DR5,
	HV_X86_DR6,
	HV_X86_DR7,
	HV_X86_TPR,
	HV_X86_XCR0,
	HV_X86_REGISTERS_MAX,
} hv_x86_reg_t;

#ifdef __cplusplus
}
#endif

#endif /* __HYPERVISOR_HV_ARCH_X86__ */
