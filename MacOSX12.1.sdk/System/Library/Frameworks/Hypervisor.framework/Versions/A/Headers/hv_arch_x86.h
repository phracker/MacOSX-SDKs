/*
 *  hv_arch_x86.h
 *  Hypervisor Framework
 *
 *  Copyright (c) 2013-2019 Apple Inc. All rights reserved.
 */

#ifndef __HYPERVISOR_HV_ARCH_X86__
#define __HYPERVISOR_HV_ARCH_X86__

#ifdef __x86_64__

/*
 * Note the #defines here enable access to the symbols from assembler source files.
 */
#define __HV_X86_RIP		0
#define __HV_X86_RFLAGS		1
#define __HV_X86_RAX		2
#define __HV_X86_RCX		3
#define __HV_X86_RDX		4
#define __HV_X86_RBX		5
#define __HV_X86_RSI		6
#define __HV_X86_RDI		7
#define __HV_X86_RSP		8
#define __HV_X86_RBP		9
#define __HV_X86_R8		10
#define __HV_X86_R9		11
#define __HV_X86_R10		12
#define __HV_X86_R11		13
#define __HV_X86_R12		14
#define __HV_X86_R13		15
#define __HV_X86_R14		16
#define __HV_X86_R15		17
#define __HV_X86_CS		18
#define __HV_X86_SS		19
#define __HV_X86_DS		20
#define __HV_X86_ES		21
#define __HV_X86_FS		22
#define __HV_X86_GS		23
#define __HV_X86_IDT_BASE	24
#define __HV_X86_IDT_LIMIT	25
#define __HV_X86_GDT_BASE	26
#define __HV_X86_GDT_LIMIT	27
#define __HV_X86_LDTR		28
#define __HV_X86_LDT_BASE	29
#define __HV_X86_LDT_LIMIT	30
#define __HV_X86_LDT_AR		31
#define __HV_X86_TR		32
#define __HV_X86_TSS_BASE	33
#define __HV_X86_TSS_LIMIT	34
#define __HV_X86_TSS_AR		35
#define __HV_X86_CR0		36
#define __HV_X86_CR1		37
#define __HV_X86_CR2		38
#define __HV_X86_CR3		39
#define __HV_X86_CR4		40
#define __HV_X86_DR0		41
#define __HV_X86_DR1		42
#define __HV_X86_DR2		43
#define __HV_X86_DR3		44
#define __HV_X86_DR4		45
#define __HV_X86_DR5		46
#define __HV_X86_DR6		47
#define __HV_X86_DR7		48
#define __HV_X86_TPR		49
#define __HV_X86_XCR0		50
#define __HV_X86_REGISTERS_MAX	51

#ifndef __ASSEMBLER__

OS_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 * @enum       hv_x86_reg_t
 * @abstract   x86 architectural register IDs
 */
typedef enum {
	HV_X86_RIP		= __HV_X86_RIP,
	HV_X86_RFLAGS		= __HV_X86_RFLAGS,
	HV_X86_RAX		= __HV_X86_RAX,
	HV_X86_RCX		= __HV_X86_RCX,
	HV_X86_RDX		= __HV_X86_RDX,
	HV_X86_RBX		= __HV_X86_RBX,
	HV_X86_RSI		= __HV_X86_RSI,
	HV_X86_RDI		= __HV_X86_RDI,
	HV_X86_RSP		= __HV_X86_RSP,
	HV_X86_RBP		= __HV_X86_RBP,
	HV_X86_R8		= __HV_X86_R8,
	HV_X86_R9		= __HV_X86_R9,
	HV_X86_R10		= __HV_X86_R10,
	HV_X86_R11		= __HV_X86_R11,
	HV_X86_R12		= __HV_X86_R12,
	HV_X86_R13		= __HV_X86_R13,
	HV_X86_R14		= __HV_X86_R14,
	HV_X86_R15		= __HV_X86_R15,
	HV_X86_CS		= __HV_X86_CS,
	HV_X86_SS		= __HV_X86_SS,
	HV_X86_DS		= __HV_X86_DS,
	HV_X86_ES		= __HV_X86_ES,
	HV_X86_FS		= __HV_X86_FS,
	HV_X86_GS		= __HV_X86_GS,
	HV_X86_IDT_BASE		= __HV_X86_IDT_BASE,
	HV_X86_IDT_LIMIT	= __HV_X86_IDT_LIMIT,
	HV_X86_GDT_BASE		= __HV_X86_GDT_BASE,
	HV_X86_GDT_LIMIT	= __HV_X86_GDT_LIMIT,
	HV_X86_LDTR		= __HV_X86_LDTR,
	HV_X86_LDT_BASE		= __HV_X86_LDT_BASE,
	HV_X86_LDT_LIMIT	= __HV_X86_LDT_LIMIT,
	HV_X86_LDT_AR		= __HV_X86_LDT_AR,
	HV_X86_TR		= __HV_X86_TR,
	HV_X86_TSS_BASE		= __HV_X86_TSS_BASE,
	HV_X86_TSS_LIMIT	= __HV_X86_TSS_LIMIT,
	HV_X86_TSS_AR		= __HV_X86_TSS_AR,
	HV_X86_CR0		= __HV_X86_CR0,
	HV_X86_CR1		= __HV_X86_CR1,
	HV_X86_CR2		= __HV_X86_CR2,
	HV_X86_CR3		= __HV_X86_CR3,
	HV_X86_CR4		= __HV_X86_CR4,
	HV_X86_DR0		= __HV_X86_DR0,
	HV_X86_DR1		= __HV_X86_DR1,
	HV_X86_DR2		= __HV_X86_DR2,
	HV_X86_DR3		= __HV_X86_DR3,
	HV_X86_DR4		= __HV_X86_DR4,
	HV_X86_DR5		= __HV_X86_DR5,
	HV_X86_DR6		= __HV_X86_DR6,
	HV_X86_DR7		= __HV_X86_DR7,
	HV_X86_TPR		= __HV_X86_TPR,
	HV_X86_XCR0		= __HV_X86_XCR0,
	HV_X86_REGISTERS_MAX	= __HV_X86_REGISTERS_MAX
} hv_x86_reg_t;

__END_DECLS

OS_ASSUME_NONNULL_END

#endif	/* ifndef __ASSEMBLER */

#endif /* __x86_64__ */

#endif /* __HYPERVISOR_HV_ARCH_X86__ */

