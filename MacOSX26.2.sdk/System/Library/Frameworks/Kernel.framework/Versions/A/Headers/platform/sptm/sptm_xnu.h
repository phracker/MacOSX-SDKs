/*
 * Copyright (c) 2023-2024 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

/**
 * Types and function prototypes in this file are intended for use only to
 * invoke SPTM services, not to invoke services offered by other domains.
 */
#pragma once

#if !defined(SPTM_INTERNAL)
/**
 * Only set the domain-specific define if this file is not being included with
 * the intent of accessing all definitions/declarations for all client domains
 * (which is done when accessing the headers internally in the SPTM).
 */
#define XNU_CLIENT 1
#endif

#include "sptm_common.h"

/**
 * Function IDs for each of the functions provided by the SPTM to client
 * domains.
 *
 * TODO: Rename to "ENDPOINTID".
 */
#define SPTM_FUNCTIONID_LOCKDOWN                  0
#define SPTM_FUNCTIONID_RETYPE                    1
#define SPTM_FUNCTIONID_MAP_PAGE                  2
#define SPTM_FUNCTIONID_MAP_TABLE                 3
#define SPTM_FUNCTIONID_UNMAP_TABLE               4
#define SPTM_FUNCTIONID_UPDATE_REGION             5
#define SPTM_FUNCTIONID_UPDATE_DISJOINT           6
#define SPTM_FUNCTIONID_UNMAP_REGION              7
#define SPTM_FUNCTIONID_UNMAP_DISJOINT            8
#define SPTM_FUNCTIONID_CONFIGURE_SHAREDREGION    9
#define SPTM_FUNCTIONID_NEST_REGION               10
#define SPTM_FUNCTIONID_UNNEST_REGION             11
#define SPTM_FUNCTIONID_CONFIGURE_ROOT            12
#define SPTM_FUNCTIONID_SWITCH_ROOT               13
#define SPTM_FUNCTIONID_REGISTER_CPU              14
#define SPTM_FUNCTIONID_FIXUPS_COMPLETE           15
#define SPTM_FUNCTIONID_SIGN_USER_POINTER         16
#define SPTM_FUNCTIONID_AUTH_USER_POINTER         17
#define SPTM_FUNCTIONID_REGISTER_EXC_RETURN       18
#define SPTM_FUNCTIONID_CPU_ID                    19
#define SPTM_FUNCTIONID_SLIDE_REGION              20
#define SPTM_FUNCTIONID_UPDATE_DISJOINT_MULTIPAGE 21
#define SPTM_FUNCTIONID_REG_READ                  22
#define SPTM_FUNCTIONID_REG_WRITE                 23
#define SPTM_FUNCTIONID_GUEST_VA_TO_IPA           24
#define SPTM_FUNCTIONID_GUEST_STAGE1_TLBOP        25
#define SPTM_FUNCTIONID_GUEST_STAGE2_TLBOP        26
#define SPTM_FUNCTIONID_GUEST_DISPATCH            27
#define SPTM_FUNCTIONID_GUEST_EXIT                28
#define SPTM_FUNCTIONID_MAP_SK_DOMAIN             29
#define SPTM_FUNCTIONID_HIB_BEGIN                 30
#define SPTM_FUNCTIONID_HIB_VERIFY_HASH_NON_WIRED 31
#define SPTM_FUNCTIONID_HIB_FINALIZE_NON_WIRED    32
#define SPTM_FUNCTIONID_IOFILTER_PROTECTED_WRITE  33
#define SPTM_FUNCTIONID_SPTM_SYSCTL              37
#define SPTM_FUNCTIONID_DISABLE_KERNEL_MODE_CPA2 38
#define SPTM_FUNCTIONID_SET_SHARED_REGION        39
#define SPTM_FUNCTIONID_BATCH_SIGN_USER_POINTER  40
#define SPTM_FUNCTIONID_SURT_ALLOC               41
#define SPTM_FUNCTIONID_SURT_FREE                42
#define SPTM_FUNCTIONID_SPTM_SERIAL_PUTC         43
#define SPTM_FUNCTIONID_SPTM_SERIAL_DISABLE      44

#ifndef __ASSEMBLER__

#include <stdbool.h>

/**
 * Include XNU's board_config header. This is ok since sptm_xnu.h should only
 * be used by XNU and SPTM, both of which have access to XNU's exported headers.
 */
#include <pexpert/arm64/board_config.h>


/**
 * SPTM API Return Codes (to be used with sptm_return_t types).
 *
 * The SPTM is designed to either return some flavor of success, or panic in
 * most cases. The only case where an error should be returned is when relaying
 * TXM enforcement errors.
 */
#define SPTM_SWITCH_RCTX_FLUSH_SHIFT      31
#define SPTM_SWITCH_ASID_TLBI_FLUSH_SHIFT 30
#define SPTM_SWITCH_RETURN_CODE_MASK      0xF0000000

enum : uint32_t {
	SPTM_SUCCESS,

	SPTM_MAP_VALID,
	SPTM_MAP_FLUSH_PENDING,
	SPTM_MAP_CODESIGN_ERROR,

	SPTM_UNMAP_FLUSH_PENDING,

	/* Update is successful, but TLBI is not issued as requested. */
	SPTM_UPDATE_DELAYED_TLBI,

	/* Switch is successful, and there has been an RCTX. */
	SPTM_SWITCH_RCTX_FLUSH = (1U << SPTM_SWITCH_RCTX_FLUSH_SHIFT),

	/* Switch is successful, and there has been a TLBI by ASID. */
	SPTM_SWITCH_ASID_TLBI_FLUSH = (1U << SPTM_SWITCH_ASID_TLBI_FLUSH_SHIFT),
};

/* SPTM API Limits. This is used to limit the amount of looping in the SPTM. */
#define SPTM_BATCHED_OPS_LIMIT 64U
#define SPTM_MAPPING_LIMIT     SPTM_BATCHED_OPS_LIMIT

/**
 * Definitions for supported Page Table geometries.
 *
 * @note Although these need to be defined all across the board since this
 *       is a public interface, certain SoC's may not support all configurations.
 *       See the definition for [supported_geometries] in sptm_page_tables.c.
 */
#define SPTM_PT_GEOMETRY_16K                    0U
#define SPTM_PT_GEOMETRY_4K                     1U
#define SPTM_PT_GEOMETRY_16K_KERN               2U
#define SPTM_PT_GEOMETRY_STAGE2_16K_DEFAULT_IPA 3U
#define SPTM_PT_GEOMETRY_STAGE2_16K_REDUCED_IPA 4U
#define SPTM_PT_GEOMETRY_STAGE2_4K              5U

#define SPTM_PT_N_GEOMETRY_IDS        6U
#define SPTM_PT_N_STAGE1_GEOMETRY_IDS 3U

/* Definitions for supported IOMMUs */
#define IOMMU_ID_SHART      0U
#define IOMMU_ID_SART       1U
#define IOMMU_ID_NVME       2U
#define IOMMU_ID_UAT        3U
#define IOMMU_ID_DART_T8020 4U
#define IOMMU_ID_DART_T8110 5U
#define IOMMU_ID_DART_T6000 6U
#define IOMMU_ID_DART_GEN3 8U

#define SPTM_IOMMUS_N_IDS 9U

/* A placeholder ID to represent no/invalid IOMMU. */
#define IOMMU_ID_INVALID SPTM_IOMMUS_N_IDS

/**
 * Definitions for flags associated with Root PT frames.
 *
 * These are either set or cleared for a given Root PT, and the SPTM
 * uses this information to determine what system register state needs
 * to be updated upon context switching to a Root PT.
 */

/**
 * May be set at retype time by XNU in the 'sk_flags' field of the retype_params
 * to indicate that this frame is expected to be mapped as tagged by the secure kernel.
 */
#define SPTM_SK_PAGE_FLAGS_TAGGABLE 0x1

/**
 * Commpage region definitions that must be shared between the SPTM and xnu.
 * These are the fixed VA ranges for the commpage areas on all arm64 targets;
 * they are needed for TLB management during SPTM context switch.
 */
#define SPTM_ARM64_COMMPAGE_REGION_START  0x0000000FC0000000ULL
#define SPTM_ARM64_COMMPAGE_REGION_SIZE   0x40000000ULL
#define SPTM_X86_64_COMMPAGE_REGION_START 0x00007FFFFFE00000ULL
#define SPTM_X86_64_COMMPAGE_REGION_SIZE  0x0000000000200000ULL

/**
 * For arm64_32 processes, we only support 16K page size so the commpage
 * nesting region is the 32MB block covering the commpage (0xFFFF4000).
 */
#define SPTM_ARM64_32_COMMPAGE_REGION_START 0x00000000FE000000ULL
#define SPTM_ARM64_32_COMMPAGE_REGION_SIZE  0x0000000002000000ULL

/**
 * The number of TTEs in a subpage user root table.
 */
#define SUBPAGE_USER_ROOT_TABLE_TTES 8

/**
 * The size (in bytes) of a subpage user root table.
 *
 * Each SURT has 8 TTEs and 64 bytes of metadata.
 */
#define SUBPAGE_USER_ROOT_TABLE_SIZE (SUBPAGE_USER_ROOT_TABLE_TTES * sizeof(sptm_pte_t) + 64)

/**
 * The number of subpage user root tables in a frame, which is also the number
 * of valid indexes into the array of subpage user root tables.
 */
#if XNU_CLIENT
#define SUBPAGE_USER_ROOT_TABLE_INDEXES (PAGE_SIZE / SUBPAGE_USER_ROOT_TABLE_SIZE)
#endif /* XNU_CLIENT */

/**
 * Passed to XNU's entry point to describe why it is being entered from the
 * SPTM. This is commonly used during the bootstrapping of a CPU so the
 * appropriate boot path can be executed when the SPTM hands control over to
 * XNU. This is also used when the SPTM wants to trigger the XNU panic path.
 *
 * SPTM_CPU_BOOT_COLD: Passed only once on the boot CPU during cold boot.
 * SPTM_CPU_BOOT_SECONDARY: Passed only once on every secondary CPU when
 *                          they are first released from reset.
 * SPTM_CPU_BOOT_WARM: Passed every time a CPU resumes from sleep.
 * SPTM_CPU_BOOT_HIB: Passed every time system is coming out of hibernation.
 * SPTM_CPU_PANIC: Passed when the SPTM is panicking and wants to jump to XNU's
 *                 panic handler.
 */
__enum_closed_decl(xnu_entry_routine_t,
    uint8_t,
    {
        SPTM_CPU_BOOT_COLD,
        SPTM_CPU_BOOT_SECONDARY,
        SPTM_CPU_BOOT_WARM,
        SPTM_CPU_BOOT_HIB,
        SPTM_CPU_PANIC,
    });

/**
 * Random seed length and prefix.
 *
 * The random seed length is what the device tree uses. If that ever changes in the
 * EDT project, assert will fail and give opportunity to change the seed here.
 */
static size_t const random_seed_length = 0x100;
static char const random_seed_prefix[] = "randseed";

/**
 * SPTM bootstrapping arguments passed to XNU at bootstrap time which contain
 * all of the information XNU needs to initialize itself.
 */
typedef struct {
	/* Page used to return PTEs prior to modifying them during an SPTM request. */
	sptm_papt_t sptm_prev_ptes;

	/* Physical Aperture boundaries */
	sptm_papt_t physmap_base;
	sptm_papt_t physmap_end;

	/* First available physical address */
	sptm_paddr_t first_avail_phys;

	/* Physical slide boundaries. Used by XNU to release this memory to the VM. */
	sptm_papt_t phys_slide_papt;
	size_t phys_slide_size;

	/* Thread stacks, used by TXM when running in preemptible mode. */
	sptm_papt_t *txm_thread_stacks;

	/* Number of TXM thread stacks */
	unsigned int num_txm_thread_stacks;

	/**
	 * Virtual address bounds for all of the per-cpu stacks (SPTM, dispatch,
	 * and per-cpu TXM stacks). The start is inclusive, and the end is
	 * exclusive.
	 */
	sptm_papt_t cpu_stack_papt_start;
	sptm_papt_t cpu_stack_papt_end;

	/**
	 * Virtual address bounds for all executables loaded into the kernel (TTBR1)
	 * address space. These addresses can be used to know whether a virtual
	 * address (e.g., a PC value) is inside a kernel space segment. The start
	 * address is inclusive and the end address is exclusive.
	 */
	sptm_papt_t executables_papt_start;
	sptm_papt_t executables_papt_end;

	/* Pointer to the debug header */
	struct debug_header const *debug_header;

	/* Maximum number of virtual ASIDs supported by the system */
	uint32_t num_asids;

	/*
	 * Random seed from iBoot.
	 *
	 * The seed is prefixed with the string "randseed", to make sure that
	 * it has actually been fed with a seed, and not some not-so-random data.
	 * xnu has to compare and remove that prefix, and shorten the length.
	 *
	 * It is xnu's duty to zero out this copy of the seed.
	 */
	uint8_t random_seed[sizeof(random_seed_prefix) - 1 + random_seed_length];
	size_t random_seed_length;

	
	bool sk_bootstrapped;

	
	uint64_t sk_carveout_size;

	/*
	 * What variant of SPTM this is.
	 */
	enum {
		SPTM_VARIANT_RELEASE = 0,
		SPTM_VARIANT_DEVELOPMENT
	} sptm_variant;

	/*
	 * Pointer to the global variable within SPTM which XNU can set when XNU
	 * triggers a panic. XNU can then always read this pointer to check securely
	 * if it has ever triggered a panic or not. This provides assistance in
	 * hardening the panic path within XNU.
	 */
	const bool *xnu_triggered_panic;

	/**
	 * Consumers of this structure should not attempt to access members of the
	 * libsptm_state field. All accesses will be made through libsptm library
	 * interfaces only.
	 */
	libsptm_state_t libsptm_state;


	/* AuxKC Physical Aperture boundaries */
	sptm_papt_t auxkc_base;
	sptm_papt_t auxkc_mh;
	sptm_papt_t auxkc_end;

	/* Early boot timestamps */
	uint64_t timestamp_sk_bootstrap;
	uint64_t timestamp_xnu_bootstrap;
	uint64_t timestamp_txm_bootstrap;

	void *reserved1;

#if APPLEVIRTUALPLATFORM
	/**
	 * On virtual platforms, the PSCI-based reset logic in xnu needs to know
	 * the address of the reset vector.
	 */
	sptm_vaddr_t sptm_reset_vector_vaddr;
#endif
	/**
	 * SPTM-owned scratch page used by the hibernation driver to copy the
	 * contents of memory before hashing it. XNU will take the memory copied
	 * into this page, compress it, and write it into the hibernation image.
	 */
	sptm_paddr_t hib_scratch_page_paddr;

	/**
	 * SPTM parsed pmap-io-ranges table and its size.
	 */
	sptm_papt_t sptm_pmap_io_ranges;
	unsigned int sptm_pmap_io_ranges_count;

	/**
	 * SPTM parsed pmap-io-filters table and its size.
	 */
	sptm_papt_t sptm_pmap_io_filters;
	unsigned int sptm_pmap_io_filters_count;

	/* SPTM feature flags for use in XNU */
	uint64_t feature_flags;
} sptm_bootstrap_args_xnu_t;


/**
 * Data structures used to dispatch to guest VCPU context. Contains all the
 * relevant information that XNU must pass when entering guest VCPU context
 * including stage 2 page table root, desired host control registers such
 * as HCR, HACR, VTCR, non-banked system registers, NEON, and GPR register
 * files.
 *
 * @note The NEON and GPR register files are in their own substructures due
 *       to ARMv8 assembly addressing mode offset restrictions.
 */

typedef struct {
	uint64_t cptr_el2;
	uint64_t fpsr;
	uint64_t fpcr;
} sptm_guest_dispatch_neon_t;

typedef struct {
	uint64_t tpidr2_el0;
	uint64_t smpri_el1;
	uint64_t svcr;
} sptm_guest_dispatch_sme_t;

/* Maximum SME/SVE vector size (currently capped at 512 bits) */
static const size_t kSMEMaxVectorSize = 512 / 8;

/* Maximum SME/SVE predicate size */
static const size_t kSMEMaxPredicateSize = kSMEMaxVectorSize / 8;

/* Number of SME/SVE vector registers */
static const size_t kSMEVectorCount = 32;

/* Number of SME/SVE predicate registers */
static const size_t kSMEPredicateCount = 16;

typedef struct {
	union {
		/* Legacy NEON state */
		__uint128_t q[32];

		struct {
			/* SME/SVE vector state */
			uint8_t z[kSMEMaxVectorSize * kSMEVectorCount];

			/* SME/SVE predicate state */
			uint8_t p[kSMEMaxPredicateSize * kSMEPredicateCount];
		};
	};
} sptm_guest_dispatch_vec_t;

typedef struct {
	uint64_t x[29];
	uint64_t fp;
	uint64_t lr;
} sptm_guest_dispatch_gpr_t;

typedef struct {
#if USE_UNSAFE_TYPES
	sptm_stage2_root_pt_u stage2_root_pt;
#else
	sptm_paddr_t stage2_root_pt;
#endif

	/* Guarded mode protected host control registers. */
	uint64_t vtcr;
	uint64_t hcr;
	uint64_t hacr;
	uint64_t hcrx;
#if __APPLE_NV__
#if USE_UNSAFE_TYPES
	sptm_managed_addr_u vncr_paddr;
	sptm_managed_addr_u avncr_paddr;
#else
	sptm_paddr_t vncr_paddr;
	sptm_paddr_t avncr_paddr;
#endif /* */
#endif /* __APPLE_NV__ */

	/* Non Banked control registers. */
	uint64_t sp_el0;
	uint64_t sp_el1;
	uint64_t mdscr_el1;
	uint64_t tpidr_el1;
	uint64_t tpidr_el0;
	uint64_t tpidrro_el0;
	uint64_t par_el1;
	uint64_t csselr_el1;
	uint64_t afpcr_el0;
#if HAS_ACFG
	uint64_t acfg_el1;
#endif /* HAS_ACFG */
	uint64_t scxtnum_el0;

	/* NEON */
	sptm_guest_dispatch_neon_t neon;

	/* GPR */
	sptm_guest_dispatch_gpr_t gpr;

	/* SME */
	sptm_guest_dispatch_sme_t sme;

	/* Vector */
	sptm_guest_dispatch_vec_t vec;

	/* Exception Return registers. */
	uint64_t cpsr;
	uint64_t pc;
	uint64_t apstate;

	bool flush_local_tlb;
} sptm_guest_dispatch_t;

/**
 * Structure for the return state from the sptm_copy_callee_saved_state()
 * library function.
 */
typedef struct {
	uint64_t fp;
	uint64_t lr;
	uint64_t pc;
	uint64_t sp;
} xnu_saved_registers_t;

/**
 * Structure describing pmap I/O ranges, allowed I/O ranges and I/O ranges {addr, len, type}.
 * Used by SEAR/LASER userspace tools, so keep in sync with them.
 */
typedef struct {
	sptm_paddr_t addr;
	size_t len;
	sptm_frame_type_t type;
} sptm_io_range_t;

/**
 * Overridable "syscall" entry/exit hooks (weak symbols)
 *
 * @note Each hook is REQUIRED to preserve x0 through x7 and x16 if it clobbers
 *       those registers.
 *
 * @note Each set of hooks is executed before/after entering/exiting
 *       (respectively) the named destination domain.
 */
void __attribute__((weak)) _sptm_pre_entry_hook(void);
void __attribute__((weak)) _sptm_post_exit_hook(void);

void __attribute__((weak)) _sk_pre_entry_hook(void);
void __attribute__((weak)) _sk_post_exit_hook(void);

/**
 * Function called by the SPTM once it is ready for its CTRR and CTXR regions to
 * be locked. This must be called only once during cold boot.
 *
 * @note After calling this function, cL4 and SPTM will no longer be able to write
 *       to their RO memory.
 */
void sptm_lockdown(void);

/**
 * Function called by XNU once it is ready for for its CTRR and CTXR regions region
 * to be locked. This must be called only once during cold boot.
 *
 * @note After calling this function, TXM and XNU will no longer be able to write
 *       to their RO memory.
 */
void sptm_lockdown_xnu(void);

/**
 * Function called by XNU once its fixups phase is complete. During the fixups
 * phase, XNU can only execute code within a subrange of its RX region, called
 * the BX region; the rest of the RX region is mapped as XNU_DEFAULT so that XNU
 * can overwrite it. This function retypes the entirety of XNU's RX region as
 * SPTM_XNU_CODE.
 */
void sptm_init_xnu_fixups_complete(void);

/**
 * Function called by XNU to disable kernel-mode checked pointer arithmetic.
 * This must be called prior to machine lockdown.
 */
void sptm_disable_kernel_mode_cpa2(void);

/**
 * Function called by XNU if XNU ever enters a panic state. When this happens, a
 * global variable within the SPTM is latched to be true, with no possibility of this
 * ever changing back to false. XNU and other domains can then query this variable
 * and build policy on top of that.
 */
void sptm_xnu_panic_begin(void);

#if !USE_UNSAFE_TYPES
sptm_return_t sptm_map_page(sptm_paddr_t root_pt_paddr, sptm_vaddr_t vaddr, sptm_pte_t new_pte);
#else
sptm_return_t sptm_map_page(sptm_root_pt_u root_pt_U,
    sptm_aligned_vaddr_u vaddr_U,
    sptm_pte_u new_pte_U);
#endif

/**
 * Map a page table page in an address space at the specified level.
 *
 * @note: The page table page represented by [new_tte] must pass a number of security
 *        checks in order to avoid triggering an SPTM violation:
 *        --It must already be typed as either XNU_PAGE_TABLE or
 *          XNU_PAGE_TABLE_COMMPAGE.  XNU_PAGE_TABLE_SHARED tables are expected
 *          to be inserted using sptm_nest_region().
 *        --It must be typed to reside at [target_level] + 1.
 *        --If not of type XNU_PAGE_TABLE_COMMPAGE, it must contain no existing
 *          mappings.
 *        --If not of type XNU_PAGE_TABLE_COMMPAGE, it must not be nested in any
 *          other paging hierarchy.
 *        --If not of type XNU_PAGE_TABLE_COMMPAGE, it must not be concurrently
 *          altered in any way by any other SPTM operation.
 *
 *       4K page table geometries come with additional restrictions. In such cases, XNU cannot
 *       target an arbirary TTE at a given level; instead, XNU must target a TTE whose index is
 *       divisible by the page ratio, which is the quotient of the native page size (16K) and the
 *       page size of the geometry at hand (in this case, 4K). Upon this request, the SPTM will then
 *       go ahead and create as many mappings of the requested geometry's size as required to
 *       completely map a 16K page. In addition to this, the physical address in the TTE provided by
 *       XNU must also be aligned to the native page size. For example, if XNU requests a mapping at
 *       a VA that targets TTE index 4 at a given level, the SPTM will create four mappings, at TTE
 *       indices 4, 5, 6 and 7, each of which maps a subset of the 16K page provided in the TTE's
 *       physical address field, resulting in the 16K page getting mapped being fully utilized by
 *       all four mappings combined. In doing so, there is no memory wastage incurred by
 *       underutilized 16K pages when used as 4K page table pages, and there is also no need for
 *       individual FTE's for each of the 4K page table pages getting mapped, since their reference
 *       and in-flight counts are effectively common to all four at any given point in time.
 *
 * @param root_pt_paddr Physical address of the Root Page Table to insert the mapping
 *                      into.
 * @param vaddr Virtual address at which to insert the mapping.
 * @param target_level Level in the page tables at which to insert the new Page Table.
 *                     For example, when mapping a newly-created L3 table, [target_level]
 *                     should be 2.
 * @param new_tte TTE to write into the page table.
 */
#if !USE_UNSAFE_TYPES
void sptm_map_table(sptm_paddr_t root_pt_paddr,
    sptm_vaddr_t vaddr,
    sptm_pt_level_t target_level,
    sptm_tte_t new_tte);
#else
void sptm_map_table(sptm_root_pt_u root_pt_U,
    sptm_aligned_vaddr_u aligned_vaddr_U,
    sptm_pt_level_u target_level_U,
    sptm_tte_u new_tte_U);
#endif

/**
 * Unmap a page table page in an address space at the specified level.
 *
 * @note The page table page to be removed must pass a number of security checks in
 *       order to avoid triggering an SPTM violation:
 *       --If it is of type XNU_PAGE_TABLE_SHARED, [root_pt_paddr] must be of type
 *         XNU_SHARED_ROOT_TABLE.  In other words, it is not permitted to use this
 *         API to remove a nested shared table from a user page table hierarchy.
 *       --Unless it is of type XNU_PAGE_TABLE_COMMPAGE, it must be nested only
 *         in the table hierarchy rooted at [root_pt_paddr].
 *         For XNU_PAGE_TABLE_SHARED tables, this means all user mappings must have
 *         previously been removed via sptm_unnest_region().
 *       --Kernel page tables may not be removed; that is, [root_pt_paddr] must not
 *         be the kernel root table.
 *
 *       4K page table geometries come with additional restrictions. In such cases, XNU cannot
 *       target an arbirary TTE at a given level; instead, XNU must target a TTE whose index is
 *       divisible by the page ratio, which is the quotient of the native page size (16K) and the
 *       page size of the geometry at hand (in this case, 4K). Upon this request, the SPTM will then
 *       go ahead and create as many mappings of the requested geometry's size as required to
 *       completely map a 16K page. In addition to this, the physical address in the TTE provided by
 *       XNU must also be aligned to the native page size. For example, if XNU requests a mapping at
 *       a VA that targets TTE index 4 at a given level, the SPTM will create four mappings, at TTE
 *       indices 4, 5, 6 and 7, each of which maps a subset of the 16K page provided in the TTE's
 *       physical address field, resulting in the 16K page getting mapped being fully utilized by
 *       all four mappings combined. In doing so, there is no memory wastage incurred by
 *       underutilized 16K pages when used as 4K page table pages, and there is also no need for
 *       individual FTE's for each of the 4K page table pages getting mapped, since their reference
 *       and in-flight counts are effectively common to all four at any given point in time.
 *
 * @param root_pt_paddr Physical address of the Root Page Table to remove the mapping
 *                      from.
 * @param vaddr Virtual address at which to remove the mapping.
 * @param target_level Level in the page tables at which to remove the exiting Page Table.
 *                     For example, when unmapping an L3 table, [target_level] should be 2.
 */
#if !USE_UNSAFE_TYPES
void sptm_unmap_table(sptm_paddr_t root_pt_paddr, sptm_vaddr_t vaddr, sptm_pt_level_t target_level);
#else
void sptm_unmap_table(sptm_root_pt_u root_pt_U,
    sptm_aligned_vaddr_u aligned_vaddr_U,
    sptm_pt_level_u target_level_U);
#endif

/**
 * Allocate a subpage user root table (SURT) in an XNU_SUBPAGE_USER_ROOT_TABLES frame.
 *
 * @param surt_frame The physical address of the XNU_SUBPAGE_USER_ROOT_TABLES frame.
 * @param surt_index The index of the subpage user root table to allocate.
 * @param attr_idx The attribute index corresponding to the page table geometry
 *                 of the new user address space.
 * @param flags The initial flags for the new user address space.
 * @param asid The ASID for the new user address space.
 */
#if !USE_UNSAFE_TYPES
void sptm_surt_alloc(sptm_paddr_t surt_frame,
    uint8_t surt_index,
    uint8_t attr_idx,
    uint8_t flags,
    sptm_asid_t asid);
#else
void sptm_surt_alloc(sptm_surt_frame_u surt_frame_U,
    sptm_surt_index_u surt_index_U,
    sptm_attr_idx_u attr_idx_U,
    sptm_root_flags_u flags_U,
    sptm_asid_u asid_U);
#endif

/**
 * Free a subpage user root table (SURT) in an XNU_SUBPAGE_USER_ROOT_TABLES frame.
 *
 * @param surt_frame The physical address of the XNU_SUBPAGE_USER_ROOT_TABLES frame.
 * @param surt_index The index of the subpage user root table to free.
 */
#if !USE_UNSAFE_TYPES
void sptm_surt_free(sptm_paddr_t surt_frame, uint8_t surt_index);
#else
void sptm_surt_free(sptm_surt_frame_u surt_frame_U, sptm_surt_index_u surt_index_U);
#endif

/**
 * Output a character onto the dockchannel interface.
 *
 * @note This function is meant to be used only for XNU early panics and not to be used
 *       for any other usecases including for normal printf. It is disabled after XNU
 *       serial initialization.
 *
 * @param c The character to output.
 */
void sptm_serial_putc(uint8_t c);

/**
 * Disables the use of the serial interface.
 *
 * @note This function is called right after serial_init() in XNU since
 *       the serial_init() can itself panic in various cases such as user error
 *       setting bad value for `serial-device` or `serial-device-name` boot-args.
 */
void sptm_serial_disable(void);

/**
 * Flags within the "mask" field used when updating already existing mappings.
 *
 * Note that key fields within the mapping like the PA and valid bit aren't
 * represented in the mask. This is how we prevent those fields from changing
 * during an update() call.
 */

/**
 * Represents whether a page is wired down. Updating this field does not require
 * TLBI since software-reserved bits are ignored by the hardware.
 */
#define SPTM_UPDATE_SW_WIRED 0x1U

/**
 * Updates to the permissions and "was writable" fields have to occur together.
 *
 * WAS_WRITABLE:
 * Mark that a mapping used to have write permissions, and that in a future
 * update call, write permissions can be added back without going through the
 * TXM. This field can ONLY be set if the permissions on the existing mapping
 * are writable. Adding writability to a page in a future call requires that
 * this field is already set in the current mapping and that the caller is also
 * trying to clear it in the new mapping.
 *
 * PERMS:
 * Represents all bits used to determine permissions: XN, PXN, AP[2:1]. Note
 * that the software-reserved "TN" bits are not included in this. Those bits
 * will always be zero.
 */
#define SPTM_UPDATE_PERMS_AND_WAS_WRITABLE 0x2U

/* Not Global flag. This field can only be set, it can't be cleared. */
#define SPTM_UPDATE_NG 0x4U

/* Access Flag. */
#define SPTM_UPDATE_AF 0x8U

/* Shareability Domain. */
#define SPTM_UPDATE_SH 0x10U

/* Memory Attribute Index Register. */
#define SPTM_UPDATE_MAIR 0x20U

/**
 * Update the in-memory PTE only w/o invalidating TLBI.
 *
 * @note Only supported by sptm_update_disjoint()/sptm_update_region().
 *
 * @note Only supported on XNU_DEFAULT typed pages. The TLBI will be issued
 *       unconditionally for unsupported types of pages.
 */
#define SPTM_UPDATE_DEFER_TLBI 0x100U

/**
 * When looping over the list of mappings to update in an
 * sptm_update_disjoint_multipage() call, avoid updating the PAPT mapping described
 * by the "per_paddr_header" struct. This is useful when one physical page has more
 * mappings than SPTM_MAPPING_LIMIT (which necessitates multiple SPTM calls to update
 * all mappings to that physical page). This flag also useful in situations in which
 * the PAPT doesn't need to be updated at all (which is basically anything besides a
 * MAIR update).
 *
 * @note Only supported in the per_paddr_header.options field passed to
 *       sptm_update_disjoint_multipage().
 */
#define SPTM_UPDATE_SKIP_PAPT 0x200U

/**
 * Mask representing all of the valid mask bits that can be passed to
 * sptm_update_*().
 *
 * The caller can pass other option bits like SPTM_UPDATE_DEFER_TLBI
 * along with the mask bits.
 */
#define SPTM_UPDATE_MASK                                                   \
	(SPTM_UPDATE_MAIR | SPTM_UPDATE_SH | SPTM_UPDATE_AF | SPTM_UPDATE_NG | \
	    SPTM_UPDATE_PERMS_AND_WAS_WRITABLE | SPTM_UPDATE_SW_WIRED)

/**
 * Update a contiguous set of mappings within a single leaf page table.
 *
 * TODO: Add list of security checks which must be passed for the mappings to
 *       get updated. This should be explicit at the API level.
 *
 * @param root_pt_paddr Physical address of the Root Page Table to update the
 *                      mappings from.
 * @param start_vaddr Virtual address of the first mapping to update.
 * @param num_mappings Number of mappings to update starting at [start_vaddr].
 * @param pte_templates_pa Physical address of an array which represents what
 *                         each mapping should get updated to. This array has to
 *                         contain [num_mappings] number of entries. The fields
 *                         denoted by [mask] will get copied out of this
 *                         template and will be used to generate the new PTE.
 * @param options The lower 8 bits is a bitmask representing which fields are
 *                being updated in this operation. Having a mask is required to
 *                be able to support multiple operations updating different
 *                fields within the same mapping. For instance, updating
 *                permissions at the same time as updating the memory type.
 *
 * @return SPTM_SUCCESS if the update succeeds and TLBIs are issued.
 *         SPTM_UPDATE_DELAYED_TLBI if the TLBIs are meant to be issued by the
 *         caller.
 *
 * @note In addition to the return value above, an array containing the values
 *       of the PTEs before modification is returned through the per-CPU scratch
 *       page. The array is located at the beginning of the scratch page and
 *       contiguously contains the previous PTEs starting with the one for
 *       [start_vaddr].
 */
#if !USE_UNSAFE_TYPES
sptm_return_t sptm_update_region(sptm_paddr_t root_pt_paddr,
    sptm_vaddr_t start_vaddr,
    unsigned int num_mappings,
    sptm_paddr_t pte_templates_pa,
    uint32_t options);
#else
sptm_return_t sptm_update_region(sptm_root_pt_u root_pt_U,
    sptm_aligned_vaddr_u aligned_vaddr_U,
    sptm_page_count_u page_count_U,
    sptm_managed_addr_u pte_templates_U,
    uint32_t options);
#endif

/**
 * Structure representing the necessary information to update/unmap a single
 * mapping within an arbitrary address space. An array of these entries will be
 * passed into the disjoint operations to allow for mappings within multiple
 * address spaces to be operated on within one SPTM call.
 */
typedef struct {
	/* Physical address of the root page table. */
#if !USE_UNSAFE_TYPES
	sptm_paddr_t root_pt_paddr;
#else
	sptm_root_pt_u root_pt_U;
#endif

	/**
	 * Virtual address of the mapping to update/unmap. The page table hierarchy
	 * will be walked using this VA to find the current page table entry.
	 */
#if !USE_UNSAFE_TYPES
	sptm_vaddr_t vaddr;
#else
	sptm_aligned_vaddr_u vaddr_U;
#endif

	/**
	 * The mapping template used to replace the existing entry with. For update
	 * operations, the `mask` parameter will determine which bits within this
	 * entry will get copied over the existing entry.
	 *
	 * For unmap operations, only ARM_PTE_COMPRESSED and ARM_PTE_COMPRESSED_ALT
	 * are allowed to be set on invalid entries, so the mask is implicitly set
	 * to those two bits.
	 */
	sptm_pte_t pte_template;
} sptm_disjoint_op_t;

/**
 * Update a set of mappings to a single physical page across multiple address
 * spaces.
 *
 * TODO: Add list of security checks which must be passed for the mappings to
 *       get updated. This should be explicit at the API level.
 *
 * @note This function can only operate on mappings to SPTM-managed memory.
 *
 * @note The number of mapping operations that can occur in a single call to
 *       this function is limited by SPTM_MAPPING_LIMIT so as to control latency
 *       when running within the SPTM's pre-emption disabled environment.
 *
 * @param paddr All existing mappings and new mappings must be mapping this
 *              physical address. The system will panic otherwise.
 * @param disjoint_ops_pa Physical address to a structure that represents which
 *                        mappings should be updated in which address spaces,
 *                        and what the new mappings should be. All new mappings
 *                        must be valid and contain the same physical address as
 *                        the existing mapping, as well as match the [paddr].
 * @param num_mappings The number of requested mapping update operations passed
 *                     in through [mapping_ops]. This can at most be
 *                     SPTM_MAPPING_LIMIT.
 * @param options The lower 8 bits is a bitmask representing which fields are
 *                being updated in this operation. Having a mask is required to
 *                be able to support multiple operations updating different
 *                fields within the same mapping. For instance, updating
 *                permissions at the same time as updating the memory type.
 *                You can also specify options like SPTM_UPDATE_DEFER_TLBI
 *                to modify the behavior of the function.
 *
 * @return SPTM_SUCCESS if the update succeeds and TLBIs are issued.
 *         SPTM_UPDATE_DELAYED_TLBI if the TLBIs are meant to be issued by the
 *         caller.
 *
 * @note An array containing the values of the PTEs before modification is returned
 *       through the per-CPU scratch page. The array is located at the beginning
 *       of the scratch page and contiguously contains the previous PTEs for each
 *       virtual address and root page table found in [disjoint_ops_pa].
 */
#if !USE_UNSAFE_TYPES
sptm_return_t sptm_update_disjoint(sptm_paddr_t paddr,
    sptm_paddr_t disjoint_ops_pa,
    unsigned int num_mappings,
    uint32_t options);
#else
sptm_return_t sptm_update_disjoint(sptm_managed_page_u paddr_U,
    sptm_managed_addr_u disjoint_ops_U,
    sptm_page_count_u page_count_U,
    uint32_t options);
#endif

/**
 * Structure used to represent an entry in the cache attribute update ops
 * table.
 *
 * The entries in a cache attribute updates ops table can either be a PAPT
 * header or an sptm_disjoint_op_t. When representing an sptm_disjoint_op_t,
 * it can be used the same way as a usual sptm_disjoint_op_t by functions like
 * sptm_update_disjoint(). In fact, the function that consumes these entries,
 * sptm_update_cache_attr(), calls into sptm_update_disjoint() for updating
 * the mappings.
 */
typedef union {
	/**
	 * Represents a header that contains information of the following disjoint
	 * ops for updating cache attributes of the mappings of a physical page.
	 */
	struct {
		/* Physical address of the page. */
#if !USE_UNSAFE_TYPES
		sptm_paddr_t paddr;
#else
		sptm_managed_page_u paddr_U;
#endif

		/**
		 * PAPT PTE template of the page to be updated.  This field will
		 * be ignored if SPTM_UPDATE_SKIP_PAPT is passed in the [options]
		 * field below.
		 */
		sptm_pte_t papt_pte_template;

		/* Number of sptm_disjoint_op_t entries following this header. */
		unsigned int num_mappings;

		/**
		 * Options to be passed to the SPTM when updating the mappings
		 * associated with this physical address header.  This is intended
		 * to be a mask of the regular SPTM_UPDATE_* flags.  Note that if
		 * SPTM_UPDATE_SKIP_PAPT is not included in this field, then
		 * only SPTM_UPDATE_MAIR, SPTM_UPDATE_SH, and SPTM_UPDATE_DEFER_TLBI
		 * will be honored when updating the PAPT mapping; all other update
		 * flags will be ignored.
		 */
		uint32_t options;
	} per_paddr_header;

	/**
	 * Represents an sptm_disjoint_op_t. See comments around sptm_disjoint_op_t
	 * for details.
	 */
	sptm_disjoint_op_t disjoint_op;
} sptm_update_disjoint_multipage_op_t;

_Static_assert(sizeof(sptm_update_disjoint_multipage_op_t) == sizeof(sptm_disjoint_op_t),
    "The size of sptm_update_disjoint_multipage_op_t has to be identical to sptm_disjoint_op_t "
    "to ensure that parts of the structure can be directly passed into sptm_disjoint_op().");

/**
 * Update multiple mappings, potentially spanning multiple physical pages.
 *
 * @note This function is different from the generic disjoint update function in
 *       that it allows mappings of multiple pages to be passed in via the
 *       same ops table, and it allows you to optionally update the PAPT mapping.
 *
 * @param multipage_ops_pa Physical address of the ops table. For each page
 *                          whose mappings are to be updated, a PAPT header
 *                          needs to precede all its disjoint ops, specifying
 *                          the physical address of the page, the new PAPT
 *                          PTE template, the number of mappings/disjoint
 *                          ops following the header, and the update options
 *                          to be used for the following sequence of disjoint
 *                          ops. The following disjoint ops are basically the
 *                          same as those consumed by sptm_update_disjoint().
 *                          See the definition of
 *                          sptm_update_disjoint_multipage_op_t for more
 *                          details about the layout of this array.
 *
 * @param num_entries The number of valid entries in the ops table, limited to
 *                    SPTM_MAPPING_LIMIT. This includes all the PAPT headers
 *                    and the disjoint ops.
 *
 * @return SPTM_SUCCESS if the update succeeds and TLBIs are issued.
 *         SPTM_UPDATE_DELAYED_TLBI if the TLB invalidations for any mapping
 *         were skipped due to the presence of SPTM_UPDATE_DEFER_TLBI in the
 *         update options for that mapping.
 *
 */
#if !USE_UNSAFE_TYPES
sptm_return_t sptm_update_disjoint_multipage(sptm_paddr_t multipage_ops_pa, size_t num_entries);
#else
sptm_return_t sptm_update_disjoint_multipage(sptm_managed_addr_u multipage_ops_U,
    sptm_multipage_num_entries_u num_entries_U);
#endif

/**
 * Option that can be passed into sptm_unmap_region() as a flag denoting that
 * compressed markings within invalid PTEs should get removed.
 */
#define SPTM_REMOVE_COMPRESSED 0x1

/**
 * Remove a single mapping from an address space.
 *
 * TODO: Add list of security checks which must be passed for the mappings to
 *       get updated. This should be explicit at the API level.
 *
 * @param root_pt_paddr Physical address of the Root Page Table to remove the mapping
 *                      from.
 * @param start_vaddr Virtual address at which to remove the first mapping.
 * @param num_mappings Number of mappings to remove.
 * @param options The following options can be specified:
 *     - SPTM_REMOVE_COMPRESSED: Remove any compressed markers in invalid
 *       mappings. Without this option, compressed mappings won't be removed.
 *
 * @note While there is no direct return value, an array containing the values
 *       of the PTEs before modification is returned through the per-CPU scratch
 *       page. The array is located at the beginning of the scratch page and
 *       contiguously contains the previous PTEs starting with the one for
 *       [start_vaddr].
 */
#if !USE_UNSAFE_TYPES
void sptm_unmap_region(sptm_paddr_t root_pt_paddr,
    sptm_vaddr_t start_vaddr,
    unsigned int num_mappings,
    uint32_t options);
#else
void sptm_unmap_region(sptm_root_pt_u root_pt_U,
    sptm_aligned_vaddr_u aligned_vaddr_U,
    sptm_page_count_u page_count_U,
    uint32_t options);
#endif

/**
 * Unmap a set of mappings (all mapping the same single physical page) across
 * multiple address spaces.
 *
 * TODO: Add list of security checks which must be passed for the mappings to
 *       get updated. This should be explicit at the API level.
 *
 * @note This function can only operate on mappings to SPTM-managed memory.
 *
 * @note The number of mapping operations that can occur in a single call to
 *       this function is limited by SPTM_MAPPING_LIMIT so as to control latency
 *       when running within the SPTM's pre-emption disabled environment.
 *
 * @note Compressed markers in invalid mappings cannot be removed using this
 *       function. Use sptm_unmap_region() with the SPTM_REMOVE_COMRESSED option
 *       to remove compressed mappings.
 *
 * @param paddr All existing mappings must be mapping this physical address. The
 *              system will panic otherwise.
 * @param disjoint_ops_pa Physical address to a structure that represents which
 *                        mappings should be unmapped in which address spaces,
 *                        and whether the invalid mappings should have flags set
 *                        in them. The valid pte_template options are:
 *                        ARM_PTE_EMPTY, ARM_PTE_COMPRESSED,
 *                        ARM_PTE_COMPRESSED_ALT, or a combination of those
 *                        three.
 * @param num_mappings The number of requested mapping update operations passed
 *                     in through [mapping_ops]. This can at most be
 *                     SPTM_MAPPING_LIMIT.
 *
 * @note While there is no direct return value, an array containing the values
 *       of the PTEs before modification is returned through the per-CPU scratch
 *       page. The array is located at the beginning of the scratch page and
 *       contiguously contains the previous PTEs for each virtual address and
 *       root page table found in [disjoint_ops_pa].
 */
#if !USE_UNSAFE_TYPES
void sptm_unmap_disjoint(sptm_paddr_t paddr,
    sptm_paddr_t disjoint_ops_pa,
    unsigned int num_mappings);
#else
void sptm_unmap_disjoint(sptm_managed_page_u paddr_U,
    sptm_managed_addr_u disjoint_ops_U,
    sptm_page_count_u page_count_U);
#endif

/* Maximum size allowed for a shared region is 64GB */
#define SPTM_MAX_SHARED_REGION_SIZE (1ULL << 36)

/**
 * Configure a shared region to be nested into one or more user address spaces.
 *
 * @note Once a page has been retyped to XNU_SHARED_ROOT_TABLE, this function must
 *       be called exactly once before the page may be used with
 *       sptm_set_shared_region()/sptm_nest_region()/sptm_unnest_region().
 *
 * @note Once this function has been called, sptm_set_shared_region() may be called
 *       any number of times with the same [shared_root_pt_paddr] but different user
 *       root tables.
 *
 * @param shared_root_pt_paddr Physical address of the Root Page Table representing the
 *                             region to be nested.  This page must already have been
 *                             retyped to XNU_SHARED_ROOT_TABLE.
 *
 * @param start_vaddr Page-aligned minimum virtual address at which nesting may begin.
 *
 * @param size Page-aligned maximum nesting size for this shared region.
 */
#if !USE_UNSAFE_TYPES
void sptm_configure_shared_region(sptm_paddr_t shared_root_pt_paddr,
    sptm_vaddr_t start_vaddr,
    unsigned int page_count);
#else
void sptm_configure_shared_region(sptm_shared_root_pt_u shared_root_pt_U,
    sptm_aligned_vaddr_u aligned_vaddr_U,
    sptm_page_count_u page_count_U);
#endif

/**
 * Associate a Shared Root with a User Root.
 *
 * @note sptm_configure_shared_region() must have been called on [shared_root_pt_paddr]
 *       prior to this call.
 *
 * @note Once this function has been called, sptm_nest_region() may be called any
 *       number of times with the same [user_root_pt_paddr] and [shared_root_pt_paddr]
 *       but with different VA ranges to be nested, as long as each VA range is
 *       entirely encompassed by the [start_vaddr, start_vaddr + size) region
 *       specified in the original call to sptm_configure_shared_region().
 *
 * @param user_root_pt_paddr Physical address of the Root Page Table representing
 *                           the user map.
 * @param shared_root_pt_paddr Physical address of the Root Page Table representing
 *                             the nested map.
 */
#if !USE_UNSAFE_TYPES
void sptm_set_shared_region(sptm_paddr_t user_root_pt_paddr, sptm_paddr_t shared_root_pt_paddr);
#else
void sptm_set_shared_region(sptm_user_root_pt_u user_root_pt_U,
    sptm_shared_root_pt_u shared_root_pt_U);
#endif

/**
 * Copy a set of leaf tables from a Shared Root into a User Root.
 *
 * @note Each XNU_USER_ROOT_TABLE is only allowed to nest a single shared region.
 *       Only one nest operation can be performed for each XNU_USER_ROOT_TABLE, and
 *       this call will nest the entirety of the region specified by
 *       [start_vaddr, start_vaddr + size) as long as that region falls within
 *       the configured bounds of the shared region.
 *
 * @note sptm_configure_shared_region() must be called exactly once to configure
 *       [shared_root_pt_paddr] prior to any sptm_nest_region() call against the
 *       same [shared_root_pt_paddr].
 *
 * @note For a given [shared_root_pt_paddr], all nesting operations across multiple
 *       user address spaces must specify some subset of the VA region specified
 *       in the prior call to sptm_configure_shared_region().
 *
 * @note The VA range defined by [start_vaddr, start_vaddr + size) cannot span
 *       a twig table boundary.
 *
 * @note Both [start_vaddr] and [size] must be page-aligned.
 *
 * @param user_root_pt_paddr Physical address of the Root Page Table representing
 *                           the user map.
 * @param shared_root_pt_paddr Physical address of the Root Page Table representing
 *                             the nested map.
 * @param start_vaddr Virtual address at which to start nesting the region.
 * @param size Size of the region to nest.
 */
#if !USE_UNSAFE_TYPES
void sptm_nest_region(sptm_paddr_t user_root_pt_paddr,
    sptm_paddr_t shared_root_pt_paddr,
    sptm_vaddr_t start_vaddr,
    unsigned int page_count);
#else
void sptm_nest_region(sptm_user_root_pt_u user_root_pt_U,
    sptm_shared_root_pt_u shared_root_pt_U,
    sptm_aligned_vaddr_u aligned_vaddr_U,
    sptm_page_count_u page_count_U);
#endif

/**
 * Remove a set of leaf tables from a User Root.
 *
 * @note The VA range defined by [start_vaddr, start_vaddr + size] must be covered
 *       by the specified shared region.
 *
 * @note Both [start_vaddr] and [size] must be page-aligned.
 *
 * @param user_root_pt_paddr Physical address of the Root Page Table representing
 *                           the user map.
 * @param shared_root_pt_paddr Physical address of the Root Page Table representing
 *                             the nested map.
 * @param start_vaddr Virtual address at which to start unnesting the region.
 * @param size Size of the region to unnest.
 */
#if !USE_UNSAFE_TYPES
void sptm_unnest_region(sptm_paddr_t user_root_pt_paddr,
    sptm_paddr_t shared_root_pt_paddr,
    sptm_vaddr_t start_vaddr,
    unsigned int page_count);
#else
void sptm_unnest_region(sptm_user_root_pt_u user_root_pt_U,
    sptm_shared_root_pt_u shared_root_pt_U,
    sptm_aligned_vaddr_u aligned_vaddr_U,
    sptm_page_count_u page_count_U);
#endif

/**
 * Configure a given User Root PT. This changes the set of flags for a given
 * User Root PT that determines what extra state needs to be switched at context
 * switch time.
 *
 * @note This call cannot be made concurrently on the same User Root PT.
 *
 * @param root_pt_paddr Physical address of the Root PT to configure.
 *                     Its associated FTE must be of type XNU_USER_ROOT_TABLE.
 * @param flags Set of flags that determines the configuration of the Root PT.
 *              SPTM_ROOT_PT_FLAG_JIT: User Root is JIT-enabled.
 *              SPTM_ROOT_PT_FLAG_JOP: User Root is JOP-enabled.
 *              SPTM_ROOT_PT_FLAG_X86_64: User Root belongs to an x86_64-compatible process.
 *              SPTM_ROOT_PT_FLAG_TPRO: User Root is TPRO-enabled.
 * @param mask Mask used to determine which flags need to be updated. When a given bit in [mask] is
 *             set, the corresponding bit in [flags] will be copied to the Root PT's flags.
 */
#if !USE_UNSAFE_TYPES
void sptm_configure_root(sptm_paddr_t root_pt_paddr, uint8_t flags, uint8_t mask);
#else
void sptm_configure_root(sptm_user_root_pt_u user_root_pt_U,
    sptm_root_config_u flags_U,
    sptm_root_config_u mask_U);
#endif

/**
 * Switch the current Root PT for the invoking CPU.
 *
 * The caller may also request that SPTM override one or more user Root PT flags when
 * configuring the CPU.  These overrides are not written back to the Root PT,
 * so they only take effect until the next `sptm_switch_root` call on this CPU.
 *
 * @note The ASID to be programmed is inferred from the Root Page Table FTE.
 *
 * @param root_pt_paddr Physical address of the Root PT to switch to.
 *                     Its associated FTE must be of type SPTM_KERNEL_ROOT_TABLE or
 *                     XNU_USER_ROOT_TABLE.
 * @param override_flags Set of flags that override the configuration stored in
 *                       the user Root PT.  This value must be 0 when [root_pt_addr]
 *                       is of type SPTM_KERNEL_ROOT_TABLE.
 * @param override_mask Mask used to determine which user Root PT flags are
 *                      overridden. When a given bit in [override_mask] is set,
 *                      the corresponding bit will be taken from
 *                      [override_flags] instead of the Root PT's flags.  This
 *                      value must be 0 when [root_pt_addr] is of type
 *                      SPTM_KERNEL_ROOT_TABLE.
 *
 * @return SPTM_SUCCESS or a combination of SPTM_SWITCH_RCTX_FLUSH and
 *         SPTM_SWITCH_ASID_TLBI_FLUSH when applicable. See the definition
 *         of these values for details.
 */
#if !USE_UNSAFE_TYPES
sptm_return_t sptm_switch_root(sptm_paddr_t root_pt_paddr,
    uint8_t override_flags,
    uint8_t override_mask);
#else
sptm_return_t sptm_switch_root(sptm_root_pt_u root_pt_U,
    sptm_root_config_u override_flags_U,
    sptm_root_config_u override_mask_U);
#endif

/**
 * Perform a guest virtual address to intermediate physical address translation.
 *
 * Enables the guest translation regime with the provided stage 2 translation
 * table and performs a guest kernel mode stage 1 address translation with read permissions.
 * After performing the address translation this function disables the guest translation
 * regime.
 *
 * @note The appropriate guest stage 1 address translation regime registers (TTBRx_EL12, etc.)
 *       must be loaded by the hypervisor before calling this function.
 *
 * @param root_pt_paddr Physical address of the Root PT to switch to.
 *                      Its associated FTE must be of type XNU_STAGE2_ROOT_TABLE.
 * @param gva The guest virtual address to perform stage 1 address translation on.
 *
 * @return The result of the stage 1 address translation is an intermediate
 *         physical address (IPA), or UINT64_MAX if the address translation fails.
 */
#if !USE_UNSAFE_TYPES
uint64_t sptm_guest_va_to_ipa(sptm_paddr_t stage2_root_pt_paddr, uint64_t gva);
#else
uint64_t sptm_guest_va_to_ipa(sptm_stage2_root_pt_u stage2_root_pt_U, uint64_t gva);
#endif

/**
 * enumeration of `op` values accepted by sptm_guest_stage1_tlb_op()
 * `SPTM_GUEST_S1_TLB_OP_<instr>` results in `TLBI <instr>`
 *
 * These values must match those in the PMAP_S1_TLB_OP_- definitions in
 * XNU's pmap.h.
 *
 * (Note that these are the inner-shareable TLBI instructions trapped by
 * HCR_EL2.TTLB=1)
 */
typedef enum : uint8_t {
	SPTM_GUEST_S1_TLB_OP_ASIDE1IS,
	SPTM_GUEST_S1_TLB_OP_VAE1IS,
	SPTM_GUEST_S1_TLB_OP_VAAE1IS,
	SPTM_GUEST_S1_TLB_OP_VAALE1IS,
	SPTM_GUEST_S1_TLB_OP_VALE1IS,
	SPTM_GUEST_S1_TLB_OP_VMALLE1IS,
	SPTM_GUEST_S1_TLB_OP_RVAE1IS,
	SPTM_GUEST_S1_TLB_OP_RVAAE1IS,
	SPTM_GUEST_S1_TLB_OP_RVAALE1IS,
	SPTM_GUEST_S1_TLB_OP_RVALE1IS,
	SPTM_GUEST_S1_TLB_OP_INVALID,
} sptm_guest_stage1_tlb_op_t;

/**
 * Perform a guest stage 1 TLB invalidate operation.
 *
 * Enables the guest translation regime with the provided stage 2 translation
 * table and performs a stage 1 TLB invalidate operation. After performing the
 * requested TLB operation, this function disables the guest translation regime.
 *
 * @note The appropriate guest stage 1 address translation regime registers (TTBRx_EL12, etc.)
 *       must be loaded by the hypervisor before calling this function.
 *
 * @param root_pt_paddr Physical address of the Root PT to switch to.
 *                      Its associated FTE must be of type XNU_STAGE2_ROOT_TABLE.
 * @param op The type of stage 1 TLB operation requested.
 * @param param The argument, if necessary, to the TLB operation requested.
 */
#if !USE_UNSAFE_TYPES
void sptm_guest_stage1_tlb_op(sptm_paddr_t stage2_root_pt_paddr,
    sptm_guest_stage1_tlb_op_t op,
    uint64_t param);
#else
void sptm_guest_stage1_tlb_op(sptm_stage2_root_pt_u stage2_root_pt_U,
    sptm_guest_stage1_tlb_op_t op,
    uint64_t param);
#endif

/**
 * Perform a guest stage 2 TLB invalidate operation.
 *
 * Enables the guest translation regime with the provided stage 2 translation
 * table and performs a stage 2 TLB invalidate operation for the given IPA range.
 * After performing the requested TLB operation, this function disables the guest
 * translation regime.
 *
 * @note This function performs the architecturally required guest stage 1
 *       TLB invalidation as well.
 *
 * @param root_pt_paddr Physical address of the Root PT to switch to.
 *                      Its associated FTE must be of type XNU_STAGE2_ROOT_TABLE.
 * @param aligned_vaddr The starting page aligned IPA of the region being invalidated.
 * @param num_mappings The number of pages for the IPA range of translations being invalidated.
 * @param last_level_only Whether the invalidation is for the leaf level or all levels
 *                        of the translation table.
 */
#if !USE_UNSAFE_TYPES
void sptm_guest_stage2_tlb_op(sptm_paddr_t stage2_root_pt_paddr,
    sptm_vaddr_t aligned_vaddr,
    unsigned int num_mappings,
    bool last_level_only);
#else
void sptm_guest_stage2_tlb_op(sptm_stage2_root_pt_u stage2_root_pt_U,
    sptm_aligned_vaddr_u aligned_vaddr_U,
    sptm_page_count_u num_mappings,
    bool last_level_only);
#endif

/**
 * Exit a guest VCPU EL0/EL1 translation regime and restores the normal EL0/EL2 translation
 * regime for host OS operation.
 *
 * @note This call is the only way out of the special dispatch state machine state
 *       that disallows other SPTM calls.
 *
 * @param root_pt_paddr Physical address of the Root PT to switch from.
 *                     Its associated FTE must be of type XNU_STAGE2_ROOT_TABLE.
 */
#if !USE_UNSAFE_TYPES
void sptm_guest_exit(sptm_paddr_t stage2_root_pt_paddr);
#else
void sptm_guest_exit(sptm_stage2_root_pt_u stage2_root_pt_U);
#endif

/**
 * Set up the EL0/EL1 translation regime and dispatch a guest VCPU. This call
 * performs an sptm_guest_enter to setup the guest translation regime then loads
 * all the non-banked system registers, NEON registers and GPRs required to start
 * the guest VCPU. This call then performs a GEXIT to the guest VCPU and does not
 * return.
 *
 * @note Due to special handling, this call moves the dispatch state machine
 *       into a state which does not allow any SPTM calls besides
 *       sptm_exit_guest() to be called to prevent any TLB maintenence while
 *       guest VCPU EL0/EL1 translation regime is enabled.
 *
 * @param guest_state_paddr Physical address of the guest dispatch structure containing all the
 *                 info needed to dispatch the guest VPCU.
 */
#if !USE_UNSAFE_TYPES
void sptm_guest_dispatch(sptm_paddr_t guest_state_paddr);
#else
void sptm_guest_dispatch(sptm_managed_addr_u guest_state_paddr_U);
#endif

#if HAS_APPLE_PAC
/**
 * Sign a pointer using the user keys.
 *
 * @param value Pointer to sign.
 * @param key Name of the key to sign the pointer with.
 * @param discriminator Value to use as a diversifier.
 * @param jop_key JOP key to use to sign the pointer.
 *
 * @return Signed pointer.
 */
#if !USE_UNSAFE_TYPES
void *sptm_sign_user_pointer(void *value, ptrauth_key key, uint64_t discriminator, uint64_t jop_key);
#else
void *sptm_sign_user_pointer(void *value,
    sptm_ptrauth_user_key_u key_U,
    uint64_t discriminator,
    uint64_t jop_key);
#endif

/**
 * Authenticate a pointer using the user keys.
 *
 * @note On failure, this function does not poison the pointer. Instead, it
 *       simply returns SPTM_AUTH_FAILURE, and the caller is responsible for
 *       doing the poisoning.
 *
 * @param value Pointer to authenticate.
 * @param key Name of the key to authenticate the pointer with.
 * @param discriminator Value to use as a diversifier.
 * @param jop_key JOP key to use to authenticate the pointer.
 *
 * @return Authenticated pointer on success.
 *         SPTM_AUTH_FAILURE on failure.
 */
#define SPTM_AUTH_FAILURE (void *)-1
#if !USE_UNSAFE_TYPES
void *sptm_auth_user_pointer(void *value, ptrauth_key key, uint64_t discriminator, uint64_t jop_key);
#else
void *sptm_auth_user_pointer(void *value,
    sptm_ptrauth_user_key_u key_U,
    uint64_t discriminator,
    uint64_t jop_key);
#endif

/**
 * Structure to represent one user pointer signing operation in a batched user
 * pointer signing request.
 */
typedef struct {
	/* The value of the user pointer to be signed. */
	uintptr_t value;

	/* The discriminator for this op. */
	uint64_t discriminator;

#if !USE_UNSAFE_TYPES
	/* The value of the key (IA or DA) for this op. */
	ptrauth_key key;
#else
	sptm_ptrauth_user_key_u key_U;
#endif
} sptm_user_pointer_op_t;

/**
 * Sign an array of up to SPTM_BATCHED_OPS_LIMIT user pointers.
 *
 * @note This function is preferred when a client has many pointers to sign
 *       in a batch to avoid the cost of multiple entries of SPTM and flips of
 *       interrupt states and pointer authentication states.
 *
 * @note This function will panic if interrupts are enabled.
 *
 * @note This function does not have a return value. The signed pointers
 *       are returned in the SPTM sratch page.
 *
 * @param user_pointer_ops_pa Physical address of the user pointer ops array.
 * @param ops_count Number of ops contained in the ops array.
 * @param jop_key JOP key to use to sign the pointer.
 *
 */
#if !USE_UNSAFE_TYPES
void sptm_batch_sign_user_pointer(sptm_paddr_t user_pointer_ops_pa,
    uint64_t ops_count,
    uint64_t jop_key);
#else
void sptm_batch_sign_user_pointer(sptm_managed_addr_u user_pointer_ops_pa_U,
    sptm_user_pointer_ops_count_u ops_count_U,
    uint64_t jop_key);
#endif
#endif /* HAS_APPLE_PAC */

/* The SPTM sysreg RW API is only exposed in DEVELOPMENT || DEBUG builds. */
#if DEVELOPMENT

/**
 * SPTM-managed register identifiers.
 * Test register documentation : for test purposes, the register
 * SPTM_REG_PROD_TRC_STRM_BASE0_GL2 is used internally with a custom write
 * protection mask to verify that the write mask check procedure works correctly.
 * This feature is only enabled when BOARD_CONFIG_USERSPACE_TEST_ENV is defined,
 * and should never be observed by xny.
 */
__enum_closed_decl(sptm_regid_t,
    uint8_t,
    {
        SPTM_REG_VBAR_GL1 = 0,

        /**
         * The following member is here to represent the number of supported
         * register IDs. It does not represent a valid register ID.
         */
        SPTM_REGS_NUM,
    });

/**
 * Read the content of an sptm-managed register.
 *
 * @note If @regid is invalid, an sptm violation is generated.
 *
 * @note If @regid corresponds to a register that is not accessible in the
 *       current CPU (ex : accessing SPTM_REG_PROD_TRC_STRM_BASE0_GL2 in a Coll E CPU),
 *       a fault will occur.
 *
 * @param regid Identifier of the register to read.
 *
 * @return The content of the register.
 */
uint64_t sptm_reg_read(sptm_regid_t regid);

/**
 * Write the content of an sptm-managed register.
 *
 * @note If regid is invalid, an sptm violation is generated.
 *
 * @note If the write modifies non-writeable bits, an sptm violation
 *       is generated.
 *
 * @param regid Identifier of the register to read.
 * @param new_value Value to write.
 */
void sptm_reg_write(sptm_regid_t regid, uint64_t new_value);

/**
 * Maps all SK_DOMAIN pages into PAPT with permissions that allow XNU to read
 * the memory.
 *
 * @note This is required for on-device coredump of secure domain.
 *
 * @note Called late from XNU panic path when the system is running in single
 *       core mode with interrupts disabled (world is stopped).
 */
void sptm_map_sk_domain(void);

#endif /* DEVELOPMENT */

/**
 * XNU must tell SPTM the vaddr of the SPTM exception return handler via this
 * function. When handling an exception, SPTM will insert this address in the
 * kernel mode ELR before handing control to XNU's exception vectors. When XNU
 * is done handling the exception, it will ERET to this address. The exception
 * return handler will then hand control back to SPTM by performing a GENTER
 * letting SPTM know to resume where it was interrupted.
 *
 * @param return_addr The virtual address of XNU's SPTM exception return handler.
 */
void sptm_register_xnu_exc_return(sptm_vaddr_t return_addr);

/**
 * Register a CPU.
 *
 * This function is intended for XNU to call into as many times as CPUs are
 * supported by the system on the boot CPU. This must be done before machine
 * lockdown, the point at which the topology is set in stone.
 *
 * @note Order of registration determines the logical CPU ID for each of the
 *       CPUs, since they are allocated sequentially.
 *
 * @note The boot CPU must always be registered first. This is required because
 *       the SPTM assumes that logical ID 0 corresponds to the boot CPU.
 *
 * @param physical_id Should match the contents of MPIDR_EL1 for the CPU being
 *                   registered. The SPTM will only bring up CPUs that have been
 *                   registered by XNU, and to enforce this, it ensures that
 *                   [physical_id] matches the real one.
 */
void sptm_register_cpu(uint64_t physical_id);

/**
 * Slides an XNU segment, either partially or completely.
 *
 * This function is intended for XNU to call into before lockdown occurs, and is required
 * to make sure that memory that gets jettisoned is not mapped using CTRR-protected
 * page tables.
 *
 * @note The SPTM decides where in the physical aperture the requested region is remapped;
 *       all that it guarantees is that the PTEs that map it can be modified post-lockdown via
 *       the various SPTM-provided page table management APIs.
 *
 * @note The SPTM enforces that only certain segments can be slid. This is to prevent XNU from
 *       sliding arbitrary memory, potentially memory that doesn't even belong to it.
 *
 * @param target_papt_start_U Current PAPT address of the memory that needs to be slid.
 * @param num_mappings_U Number of frames that need to be remapped.
 */
#if !USE_UNSAFE_TYPES
void sptm_slide_region(sptm_papt_t target_papt_start, uint32_t num_mappings);
#else
void sptm_slide_region(sptm_papt_u target_papt_start_U, sptm_page_count_u num_mappings_U);
#endif

/**
 * Obtain the SPTM logical CPU ID associated with a given physical ID.
 *
 * This function is intended for XNU to call during early boot to associate its
 * logical CPU IDs with per-CPU fields that are used by both SPTM and XNU. An
 * example of this is the scratch page.
 *
 * @note This function is not performant, and XNU is expected to cache its
 *       result in the event that it requires this information on a hot path.
 *
 * @param physical_id Should match the contents of MPIDR_EL1 for the CPU being
 *                    searched.
 *
 * @return The SPTM logical CPU ID associated with [physical_id].
 */
uint16_t sptm_cpu_id(uint64_t physical_id);

/**
 * Request SPTM to write to a PIO register on a XNU_PROTECTED_IO page.
 *
 * This function queries the pmap-io-ranges table and the pmap-io-filter table
 * to find out if the access defined by `paddr` and `width` is allowed. It
 * performs the write if the access is allowed, but it will throw violations
 * or panic if it is not. It is the caller's responsibility to request an
 * allowed write.
 *
 * @param paddr The physical address to write to. It has to be aligned to
 *              `width` bytes.
 * @param value The value to write.
 * @param width The width of the write. It has to be 1, 2, 4 or 8.
 */
#if !USE_UNSAFE_TYPES
void sptm_iofilter_protected_write(sptm_paddr_t paddr, uint64_t value, uint64_t width);
#else
void sptm_iofilter_protected_write(sptm_io_filter_protected_paddr_u paddr,
    uint64_t value,
    sptm_io_filter_protected_write_size_u width);
#endif

/**
 * Enters TXM, invoking the function identified by the endpoint ID passed in,
 * using arguments passed in via a sptm_call_regs_t structure.
 *
 * @param endpoint_id The function to invoke in the TXM domain.
 * @param argsp A pointer to a structure containing the arguments for the
 *              specified endpoint ID function.
 *
 * @return The function's return depends on the endpoint ID passed in, and must
 *         be interpreted in that context.
 */
uint64_t txm_enter(uint32_t endpoint_id, sptm_call_regs_t *argsp);

/**
 * Entry point into TXM which is explicitly used to resume from an interrupt
 * that interrupted during execution of the TXM.
 *
 * @note This function will never return. When TXM completes its call it will
 *       return to the original entry point into TXM (not this resume entry
 *       point).
 *
 * @param thread_stack_paddr The stack of the TXM thread to resume.
 */
__attribute__((noreturn)) void txm_resume(uint64_t thread_stack_paddr);

/**
 * Called by XNU after returning from an exception on a thread that was
 * interrupted while running SPTM code.
 *
 * @note This function will never return.  SPTM will resume operation from where
 *       it was interrupted.
 */
__attribute__((noreturn)) void sptm_resume_from_exception(void);

/**
 * Entry point into SK which is explicitly used to resume from an interrupt
 * that interrupted during execution of the SK.
 *
 * @note This function will never return. When SK completes its call it will
 *       return to the original entry point into SK (not this resume entry
 *       point).
 *
 * @note XNU will tell SK which thread to resume via a shared memory
 *       interface, hence no parameters to this call.
 */
__attribute__((noreturn)) void sk_resume(void);

/**
 * Enters the SK, invoking the function identified by the endpoint ID passed in,
 * using arguments passed in via a sptm_call_regs_t structure.
 *
 * @param endpoint_id The function to invoke in the SK domain.
 * @param argsp A pointer to a structure containing the arguments for the
 *              specified endpoint ID function.
 *
 * @return The function's return depends on the endpoint ID passed in, and must
 *         be interpreted in that context.
 */
uint64_t sk_enter(uint32_t endpoint_id, sptm_call_regs_t *argsp);


#if HAS_SPTM_SYSCTL
/* Return values when sysctl op is SPTM_SYSCTL_SET. */
typedef enum : uint64_t {
	SPTM_SYSCTL_SET_SUCCESS,
	SPTM_SYSCTL_SET_NOT_ALLOWED
} sptm_sysctl_setter_return_t;

/* Supported sysctls. */
typedef enum : uint64_t {
	SPTM_SYSCTL_DISARM_PROTECTED_IO = 0ULL,
	SPTM_SYSCTL_NUM_SYSCTLS
} sptm_sysctl_selector_t;

/* Supported sysctl ops. */
typedef enum : uint8_t {
	SPTM_SYSCTL_SET = 0,
	SPTM_SYSCTL_GET,
	SPTM_SYSCTL_NUM_OPS
} sptm_sysctl_op_t;

/**
 * Interface for xnu to set control variables on *development* builds to alter
 * SPTM behaviors. This will be an empty endpoint on release builds.
 *
 * @param selector What sysctl is being operated on.
 * @param op Whether the sysctl is being read or written.
 * @param arg The value to write to the sysctl when the op is SPTM_SYSCTL_SET
 *
 * @return A value of type sptm_sysctl_setter_return_t when the op is SPTM_SYSCTL_SET.
 *         The value of the sysctl when the op is SPTM_SYSCTL_GET.
 *
 */
#if !USE_UNSAFE_TYPES
uint64_t sptm_sysctl(sptm_sysctl_selector_t selector, sptm_sysctl_op_t op, uint64_t arg);
#else
uint64_t sptm_sysctl(sptm_sysctl_selector_u selector_U, sptm_sysctl_op_u op_U, uint64_t arg);
#endif /* !USE_UNSAFE_TYPES */
#endif /* HAS_SPTM_SYSCTL */

/**
 * An X-macro list of all the SPTM event counters.
 *
 * Recall that the X-macro metaprogramming pattern is used to generate code from
 * a list of elements. This particular X-macro makes it easy to, for example,
 * generate sysctl accessors for the SPTM event counters on the XNU side.
 */
#define FOREACH_SPTM_EVENT_COUNTER(DO)                                                     \
	DO(RETYPES, "Number of retype operations")                                             \
	DO(SWWA_TLBI_ASID, "Number of extra SWWA OSH TLBI ASIDs (for rdar://154685324)")       \
	DO(SWWA_TLBI_ALL, "Number of extra SWWA OSH TLBI ALLs (for rdar://154685324)")         \
	DO(UAT_UNMAP_PROCESSED,                                                                \
	    "Number of pages processed by the UAT unmapping function (for rdar://154685324)")  \
	DO(UAT_UNMAP_MARKED,                                                                   \
	    "Number of pages marked by the UAT unmapping function (for rdar://154685324)")     \
	DO(UAT_UNMAP_UNMARKED,                                                                 \
	    "Number of pages not marked by the UAT unmapping function (for rdar://154685324)") \
	DO(SWWA_TLBI_ASID_ELIDED,                                                              \
	    "Number of elided SWWA OSH TLBI ASIDs with the epoch counters optimization (for rdar://154685324)")

/**
 * Maps an SPTM event counter to its `sptm_get_info()` enum value.
 */
#define SPTM_EVENT_COUNTER_TO_ENUM(event_counter) INFO_SPTM_EVNT_CNTR_ ## event_counter

/**
 * Values that can be passed to sptm_get_info() to retrieve the corresponding
 * information from SPTM.
 */
__enum_closed_decl(sptm_info_t,
    uint8_t,
    {
        /**
         * Retrieve SPTM allowed I/O range by index.
         *
         * arg: `unsigned int`
         * pointer type: `sptm_io_range_t`
         */
        INFO_SPTM_ALLOWED_IO_RANGES,

        /**
         * Retrieve total number of SPTM allowed I/O ranges.
         *
         * arg: none
         * pointer type: `unsigned int`
         */
        INFO_SPTM_ALLOWED_IO_RANGES_COUNT,

        /**
         * Retrieve SPTM pmap I/O range by index.
         *
         * arg: `unsigned int`
         * pointer type: `sptm_io_range_t`
         */
        INFO_SPTM_PMAP_IO_RANGES,

        /**
         * Retrieve total number of SPTM pmap I/O ranges.
         *
         * arg: none
         * type: `unsigned int`
         */
        INFO_SPTM_PMAP_IO_RANGES_COUNT,

        /**
         * Retrieve SPTM I/O range by index.
         *
         * arg: `unsigned int`
         * pointer type: `sptm_io_range_t`
         */
        INFO_SPTM_IO_RANGES,

        /**
         * Retrieve total number of SPTM I/O ranges.
         *
         * arg: none
         * pointer type: `unsigned int`
         */
        INFO_SPTM_IO_RANGES_COUNT,

/* X-macro to generate an enum value for each SPTM event counter. */
#define GENERATE_SPTM_EVNT_CNTR_ENUM_VALUE(event_counter, description) \
	SPTM_EVENT_COUNTER_TO_ENUM(event_counter),

        /**
         * These enum values are used to retrieve the SPTM event counters.
         *
         * arg: `uint64_t` logical CPU ID
         * pointer type: `uint64_t`
         */
        FOREACH_SPTM_EVENT_COUNTER(GENERATE_SPTM_EVNT_CNTR_ENUM_VALUE)

        /**
         * Placeholder value indicating the current number of supported info,
         * not actually a valid info.
         */
        MAX_SPTM_INFOS,
    });

/**
 * Libsptm library function for checking whether an SPTM operation on a given
 * page is in-flight.
 *
 * @note This function only works on SPTM-managed memory.
 *
 * @param paddr The physical address of the managed page against which to check
 *              for in-flight operations.
 * @param is_inflightp An output parameter used to store whether or not the page
 *                     has an in-flight SPTM operation. This will only get set
 *                     when LIBPSPTM_SUCCESS is returned.
 *
 * @return LIBPSPTM_SUCCESS if the passed in page is SPTM-managed and
 *                          [is_inflightp] was updated appropriately.
 *         LIBSPTM_INVALID_ARG if [is_inflightp] is NULL.
 *         LIBSPTM_FAILURE if the passed in page is not SPTM-managed memory.
 */
libsptm_error_t sptm_check_inflight(sptm_paddr_t paddr, bool *is_inflightp);

/**
 * Libsptm library function for querying the mapping count of a page table page.
 *
 * @note This function only works on SPTM-managed memory typed for use as an
 *       SPTM or XNU page table or root table, including shared tables.
 *
 * @param table_paddr The physical address of the page table page against which
 *                    to query the mapping count.
 * @param mapping_countp An output parameter used to store the mapping count.
 *                       This will only be populated if LIBSPTM_SUCCESS is returned.
 *
 * @return LIBSPTM_SUCCESS if the passed in page is of an appropriate type and
 *                         [mapping_countp] was updated appropriately.
 *         LIBSPTM_INVALID_ARG if [mapping_countp] is NULL.
 *         LIBSPTM_FAILURE if the passed in page is not SPTM-managed memory.
 *         LIBSPTM_TYPE_MISMATCH if the passed in page is not of a supported page
 *                               table type.
 */
libsptm_error_t sptm_get_table_mapping_count(sptm_paddr_t table_paddr, uint16_t *mapping_countp);

/**
 * Prefetch the FTE associated with paddr to L1 cache.
 *
 * @param paddr The physical address whose associated FTE to prefetch.
 *
 * @return LIBSPTM_SUCCESS on successful prefetch.
 *         LIBSPTM_FAILURE if there's no FTE associated with paddr.
 */
libsptm_error_t sptm_prefetch_fte(sptm_paddr_t paddr);

/**
 * Copy the number of requested traces from the per-CPU trace buffer into XNU memory.
 *
 * @note [num_traces_copied] might be smaller than [max_num_traces]. This will happen if the number
 *        of traces available is smaller than [max_num_traces].
 *
 * @note This function copies traces starting from the oldest one. If the number of traces in the
 *       target trace buffer is larger than [max_num_traces], only the oldest [max_num_traces] will
 *       be copied.
 *
 * @note Since the SPTM will overwrite old traces when the trace buffer is full, this function must
 *       be called often enough with large enough buffers in order for the SPTM to not drop old
 *       traces.
 *
 * @param sptm_cpu_id CPU ID of the CPU trace buffer to target.
 * @param dst_buffer Pointer to the buffer where the traces should be copied into. The underlying
 *                  memory must be XNU-writable.
 * @param max_num_traces Maximum number of traces that the caller wants to get copied into the
 *                       buffer.
 * @param read_index Pointer to the read index associated with the CPU that owns the trace buffer
 *                   being targeted. This will be updated upon consuming traces.
 * @param num_traces_copied Pointer where the library will store the actual number of traces that
 *                          were copied.
 *
 * @return LIBPSPTM_SUCCESS if the passed in pointers were successfully set.
 *         LIBSPTM_INVALID_ARG if either of the passed in pointers is NULL.
 */
libsptm_error_t sptm_trace_copy_traces(uint16_t sptm_cpu_id,
    sptm_trace_t *dst_buffer,
    unsigned int max_num_traces,
    uint64_t *read_index,
    unsigned int *num_traces_copied);

/**
 * Returns the number of new traces since [prev_state]. The SPTM populates [prev_state] every time
 * this function gets called, and XNU should pass that value in a subsequent call to calculate the
 * delta.
 *
 * @note It is expected that in some cases XNU will call this function for the sole purpose of
 *       capturing [prev_state], prior to a subsequent call to get the number of traces that were
 *       generated between both calls. In such cases, XNU is free to ignore [num_new_traces].
 *
 * @param sptm_cpu_id CPU ID of the CPU trace buffer to target.
 * @param prev_state Pointer to where the library will store a handle that XNU can pass on a
 *                  subsequent call to obtain the delta for the number of traces generated.
 * @param num_new_traces Pointer to where the library will store the number of traces that have been
 *                      generated since the last call.
 *
 * @return LIBPSPTM_SUCCESS if the passed in pointers were successfully set.
 *         LIBSPTM_INVALID_ARG if either of the passed in pointers is NULL.
 */
libsptm_error_t sptm_trace_num_new_traces(uint16_t sptm_cpu_id,
    uint64_t *prev_state,
    unsigned int *num_new_traces);

/**
 * Retrieve the saved XNU state for a CPU which is in the panic loop.
 *
 * @param sptm_logical_cpu_id CPU ID of the CPU to target.
 * @param regp Pointer to return saved registers into.
 *
 * @return LIBSPTM_SUCCESS if the passsed in pointers were successfully set,
 *         LIBSPTM_INVALID_ARG if the passed in pointer is NULL or the
 *         CPU ID requested is invalid,
 *         LIBSPTM_FAILURE if the requested CPU is not in the panic loop.
 */
libsptm_error_t sptm_copy_callee_saved_state(uint64_t sptm_logical_cpu_id,
    xnu_saved_registers_t *regp);

/**
 * Returns the pointer to the requested SPTM information.
 *
 * @param info SPTM information to retrieve from the list of enums such
 *             as pmap or allowed I/O ranges and their count.
 * @param arg Input argument such as index to one of the I/O ranges, this
 *            might be unused for other kinds of info such as I/O ranges count.
 *            See definition of sptm_info_t for more details for what each info
 *            expects as an argument.
 * @param output Pointer to return output information. See definition of sptm_info_t
 *               for more details for what each info expects as its pointer type.
 *
 * @return LIBSPTM_SUCCESS if the passed in output pointer is successfully set.
 *         LIBSPTM_INVALID_ARG if the passed in input is invalid or the output pointer is NULL.
 *         LIBSPTM_FAILURE if the requested SPTM info is invalid.
 */
libsptm_error_t sptm_get_info(sptm_info_t info, uint64_t arg, void *output);

/**
 * Returns whether the given frame type is ECC retireable.
 *
 * @param type SPTM frame type to check.
 * @param is_ecc_retireable Pointer to a boolean that will be set to true if the
 *                          frame type is ECC retireable, false otherwise.
 *
 * @return LIBSPTM_SUCCESS if the `is_ecc_retireable` pointer is successfully set.
 *         LIBSPTM_INVALID_ARG if the input frame type is invalid or the
 *         `is_ecc_retireable` pointer is NULL.
 */
libsptm_error_t sptm_type_is_ecc_retireable(sptm_frame_type_t type, bool *is_ecc_retireable);
#endif /* __ASSEMBLER__ */
