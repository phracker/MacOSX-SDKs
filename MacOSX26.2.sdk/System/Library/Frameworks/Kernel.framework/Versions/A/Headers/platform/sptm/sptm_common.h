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
 * This file (along with the domain-specific headers) defines the SPTM's public
 * API that is exported to the rest of the system. Only place types/prototypes
 * into this file if it's meant to be consumed by other projects.
 *
 * SPTM internal modules should include sptm_public.h to gain access to all
 * declarations/definitions in this file (do NOT include sptm_common.h directly
 * unless you know what you're doing).
 */

#pragma once

/* SPTM dispatch logic GENTER immediate values */
#define SPTM_GENTER_DISPATCH_CALL         0
#define SPTM_GENTER_RESUME_FROM_EXCEPTION 1
#define SPTM_GENTER_TXM_RESUME            2
#define SPTM_GENTER_SK_RESUME             3
#define SPTM_GENTER_XNU_PANIC_BEGIN       4

/* Domain IDs */
#define SPTM_DOMAIN    0U
#define XNU_DOMAIN     1U
#define TXM_DOMAIN     2U
#define SK_DOMAIN      3U
#define XNU_HIB_DOMAIN 4U
#define MAX_DOMAINS    5U

/* Invalid Domain ID to represent a non-panicking domain. */
#define NO_PANICKING_DOMAIN 255U

/* SPTM Dispatch Table IDs */
#define SPTM_DISPATCH_TABLE_XNU_BOOTSTRAP  0
#define SPTM_DISPATCH_TABLE_TXM_BOOTSTRAP  1
#define SPTM_DISPATCH_TABLE_SK_BOOTSTRAP   2
#define SPTM_DISPATCH_TABLE_T8110_DART_XNU 3
#define SPTM_DISPATCH_TABLE_T8110_DART_SK  4
#define SPTM_DISPATCH_TABLE_SART           5
#define SPTM_DISPATCH_TABLE_NVME           6
#define SPTM_DISPATCH_TABLE_UAT            7
#define SPTM_DISPATCH_TABLE_SHART          8
#define SPTM_DISPATCH_TABLE_RESERVED 9
#define SPTM_DISPATCH_TABLE_HIB           10
#define SPTM_DISPATCH_TABLE_GEN3_DART_XNU 11
#define SPTM_DISPATCH_TABLE_GEN3_DART_SK  12
#define SPTM_DISPATCH_TABLE_INVALID       13

#define SPTM_DISPATCH_TABLE_RETURN_TO_CALLER      0xFD
#define SPTM_DISPATCH_TABLE_PANIC                 0xFE
#define SPTM_DISPATCH_TABLE_EXCEPTION_STATE_SAVED 0xFF

/* SPTM Feature Flags */
#define SPTM_FEATURE_SYSREG                (1ULL << 2)
#define SPTM_FEATURE_BTI                   (1ULL << 3)
#define SPTM_FEATURE_LARGE_MEMORY          (1ULL << 4)
#define SPTM_FEATURE_LARGE_MEMORY_KERNONLY (1ULL << 5)

/**
 * For drivers that support both XNU and SK-dedicated dispatch tables,
 * offset from a given IOMMU driver's primary dispatch table at which to find the
 * driver's SK-dedicated dispatch table.
 */
#define IOMMU_SK_DISPATCH_TABLE_ID_OFFSET 1

/**
 * Parameters in functions that are exposed to other domains use internally
 * struct-wrapped types to force programmers into running them through
 * a validation function that returns a sanitized version of the argument.
 * Since these types must not be exposed to client domains, the following
 * macro can be used in interface headers to differentiate between the
 * public-facing types and the internal ones. Note that the test environment
 * is treated as an external client here for the purposes of interacting with
 * the SPTM API.
 */
#define USE_UNSAFE_TYPES (SPTM_INTERNAL && !SPTM_TESTS)

#if DEVELOPMENT || DEBUG
/* Enable tracing on DEV builds */
#define SPTM_TRACING 1
#endif /* DEVELOPMENT || DEBUG */

#ifndef __ASSEMBLER__
/**
 * Make sure that any IOMMU SK-dedicated dispatch table IDs follow the XNU-dedicated counterpart.
 *
 * @note IOMMU Driver developers adding new SK-dedicated tables must add static asserts to enforce
 *       this invariant below.
 */
_Static_assert(SPTM_DISPATCH_TABLE_T8110_DART_SK ==
        (SPTM_DISPATCH_TABLE_T8110_DART_XNU + IOMMU_SK_DISPATCH_TABLE_ID_OFFSET),
    "T8110 DART Driver XNU and SK dispatch table IDs not [IOMMU_SK_DISPATCH_TABLE_ID_OFFSET] apart");
_Static_assert(SPTM_DISPATCH_TABLE_GEN3_DART_SK ==
        (SPTM_DISPATCH_TABLE_GEN3_DART_XNU + IOMMU_SK_DISPATCH_TABLE_ID_OFFSET),
    "GEN3 DART Driver XNU and SK dispatch table IDs not [IOMMU_SK_DISPATCH_TABLE_ID_OFFSET] apart");
#endif

/**
 * Helper utility for setting the "x"th bit in an unsigned integer type.
 * The result type is the type of `x + 1ULL`.
 */
#define SET_BIT(x) ((((x) ^ (x)) + 1ULL) << (x))

/**
 * Set the specified [n] number of LSBs of an unsigned integer type.
 * The result type is the type of `SET_BIT(n)`.
 */
#define _ONES(n) (SET_BIT(n) - 1)

/**
 * Create a bitfield mask of length [bits] starting at LSB [shift]
 * The result type is the type of `SET_BIT(bits)`.
 */
#define BITFIELD_MASK(bits, shift) (_ONES((bits)) << (shift))

/**
 * Mask and shift to extract a bitfield.
 * The result type is the type of `val + SET_BIT(width)`.
 */
#define EXTRACT_BITFIELD(width, shift, val) (((val) & BITFIELD_MASK((width), (shift))) >> shift)

/**
 * Mask and shift to pack a bitfield.
 * The result type is the type of `val + SET_BIT(width)`.
 */
#define PACK_BITFIELD(width, shift, val) (((val) & _ONES(width)) << (shift))

/* Helper macros to pack/extract domain/table/endpoint IDs */
#define DOMAIN_ID_SHIFT 48
#define DOMAIN_ID_WIDTH 8
#define EXTRACT_DOMAIN_ID(x) \
	((sptm_domain_t)EXTRACT_BITFIELD(DOMAIN_ID_WIDTH, DOMAIN_ID_SHIFT, (x)))
#define PACK_DOMAIN_ID(x) PACK_BITFIELD(DOMAIN_ID_WIDTH, DOMAIN_ID_SHIFT, (x))

#define DISPATCH_TABLE_ID_SHIFT 32
#define DISPATCH_TABLE_ID_WIDTH 8
#define EXTRACT_TABLE_ID(x)                                                                       \
	((sptm_dispatch_table_id_t)EXTRACT_BITFIELD(DISPATCH_TABLE_ID_WIDTH, DISPATCH_TABLE_ID_SHIFT, \
	    (x)))
#define PACK_TABLE_ID(x) PACK_BITFIELD(DISPATCH_TABLE_ID_WIDTH, DISPATCH_TABLE_ID_SHIFT, (x))

#define ENDPOINT_ID_SHIFT 0
#define ENDPOINT_ID_WIDTH 32
#define EXTRACT_ENDPOINT_ID(x) \
	((sptm_dispatch_endpoint_id_t)EXTRACT_BITFIELD(ENDPOINT_ID_WIDTH, ENDPOINT_ID_SHIFT, (x)))
#define PACK_ENDPOINT_ID(x) PACK_BITFIELD(ENDPOINT_ID_WIDTH, ENDPOINT_ID_SHIFT, (x))

#define BUILD_DISPATCH_ID(domain, table, endpoint) \
	(PACK_DOMAIN_ID(domain) | PACK_TABLE_ID(table) | PACK_ENDPOINT_ID(endpoint))

/* Helper macros for dispatch ID construction and stringification helpers for GEN_NAMED_STUB */
#define _STRINGIFY(A) #A
#define _XSTR(A)      _STRINGIFY(A)
#define GEN_DISPATCH_ID_STR(domain, table, endpoint) \
	_XSTR(BUILD_DISPATCH_ID(domain, table, endpoint))

/**
 * Clang-format does not understand assembler macros, so disable formatting around all of the
 * assembler-only code.
 */
/* clang-format off */
#ifdef __ASSEMBLER__
/**
 * Assembler macro for loading the SPTM call register with the dispatch ID
 *
 * @param domain_ID The destination domain ID
 * @param table_ID The destination table ID
 * @param endpoint_ID The destination endpoint ID
 */
.macro SPTM_LOAD_DISPATCH_ID domain_ID, table_ID, endpoint_ID
		movk x16, #((( BUILD_DISPATCH_ID(\domain_ID, \table_ID, \endpoint_ID) ) >> 48) & 0xFFFF), lsl #48
		movk x16, #((( BUILD_DISPATCH_ID(\domain_ID, \table_ID, \endpoint_ID) ) >> 32) & 0xFFFF), lsl #32
		movk x16, #((( BUILD_DISPATCH_ID(\domain_ID, \table_ID, \endpoint_ID) ) >> 16) & 0xFFFF), lsl #16
		movk x16, #((( BUILD_DISPATCH_ID(\domain_ID, \table_ID, \endpoint_ID) ) >> 00) & 0xFFFF)
.endm
#else /* __ASSEMBLER__ */
/* Helper macro for the stub-generating macros defined below */
#define GEN_LOAD_DISPATCH_ID_CODE_SEQUENCE(domain_ID, table_ID, endpoint_ID) \
	 "movk x16, #(((" GEN_DISPATCH_ID_STR(domain_ID, table_ID, endpoint_ID)  ") >> 48) & 0xFFFF), lsl #48\n" \
	 "movk x16, #(((" GEN_DISPATCH_ID_STR(domain_ID, table_ID, endpoint_ID)  ") >> 32) & 0xFFFF), lsl #32\n" \
	 "movk x16, #(((" GEN_DISPATCH_ID_STR(domain_ID, table_ID, endpoint_ID)  ") >> 16) & 0xFFFF), lsl #16\n" \
	 "movk x16, #(((" GEN_DISPATCH_ID_STR(domain_ID, table_ID, endpoint_ID)  ") >> 00) & 0xFFFF)\n"
#endif /* __ASSEMBLER__ */

/**
 * For consumers that want to roll their own stubs, the following assembly macro
 * includes the appropriate entry sequence, given that the appropriate *_CLIENT
 * define is set correctly (which it should as the consumer should be including
 * this file indirectly through their domain-specific SPTM header).
 */
#ifdef __ASSEMBLER__
/**
 * Domain-entry assembler macro for consumers who want to roll their own stubs.
 *
 * @param src_reg The register to copy the dispatch ID from. The register is
 *                typically the x16 register, and if not, then the value in the
 *                provided register will be copied into the x16 register before
 *                entering the SPTM.
 */
.macro SPTM_DOMAIN_ENTER src_reg
	/* No need to mov if the source register is x16 */
.ifnc \src_reg,x16
	mov		x16, \src_reg
.endif
#if defined(TXM_CLIENT)
	svc		#0
#elif defined(SK_CLIENT)
	hvc		#0
#elif defined(XNU_CLIENT)
	genter	#0
#elif !defined(SPTM_INTERNAL)
#error Unknown client domain
#endif
.endm

/**
 * Macro to generate a domain-specific entry stub.
 *
 * @param stub_name Name of the stub function (without leading underscore).
 * @param domain_name Name of the domain to which this stub provides entry.
 * @param has_hooks "yes" to call pre/post hooks before/after entering the
 *                  wanted domain. "no" otherwise (the default value).
 * @param domain_ID ID of domain to hard-code as part of the entry sequence.
 * @param table_ID ID of the table to hard-code as part of the entry sequence.
 *
 * @note pre- and post- entry hooks are generated only when XNU_CLIENT is
 *       defined (when XNU is calling into another domain) and hooks are
 *       requested via the "has_hooks" parameter. The hook name is also
 *       determined by the second argument (the hook names will be
 *       __<domain_name>_pre_entry_hook and __<domain_name>_post_exit_hook).
 *
 * @note NOT specifying a domain_ID/table_ID implies that the caller has already
 *       set up x16 with the appropriate dispatch target ID, which tells this
 *       macro not to setup x16. Otherwise, the generated stub expects x0 to
 *       contain the endpoint ID ONLY, and x1 must contain a pointer to a
 *       structure of type sptm_call_regs_t (from which x0..x7 will be loaded
 *       just prior to dispatching the call). This macro will then use the
 *       endpoint ID in x0 and the domain_ID/table_ID to generate the correct
 *       dispatch target ID to program x16 with.
 */
.macro GEN_DOMAIN_ENTRY_STUB stub_name, domain_name, has_hooks=no, domain_ID=none, table_ID=none
	.align 2
	.global EXT(\stub_name)
LEXT(\stub_name)
	/*
	 * If the caller was built with PAC-enabled, then sign the LR.
	 * This also serves double-duty as a BTI landing pad where applicable.
	 */
#if __has_feature(ptrauth_returns)
	pacibsp
#else
	ARM64_PROLOG
#endif

#if defined(XNU_CLIENT)
.ifc \has_hooks,yes
	/* Push a stack frame to preserve the original caller's FP/LR across the hook. */
	stp		fp, lr, [sp, #-16]!
	mov		fp, sp

	bl		__\domain_name\()_pre_entry_hook

	/* Pop the frame to ensure that the SPTM is saving the caller's FP/LR. */
	mov		sp, fp
	ldp		fp, lr, [sp], #16
.endif
#endif /* XNU_CLIENT */

.ifnc \domain_ID,none

.ifc \table_ID,none
.error "If the domain_ID is set, then the table_ID must also be specified."
.endif /* table_ID == none */

	/**
	 * x0 contains the endpoint ID.
	 *
	 * Note this code has knowledge of the bitfield sizes, so any change to the
	 * PACK_*_ID macros above will require changes here as well.
	 */
	mov		w16, w0
	movk	x16, (((PACK_DOMAIN_ID(\domain_ID) | PACK_TABLE_ID(\table_ID)) >> 48) & 0xFFFF), lsl #48
	movk	x16, (((PACK_DOMAIN_ID(\domain_ID) | PACK_TABLE_ID(\table_ID)) >> 32) & 0xFFFF), lsl #32

	/* Load argument registers from sptm_call_regs_t passed in x1 */
	mov		x10, x1
	ldp		x0, x1, [x10]
	ldp		x2, x3, [x10, 0x10]
	ldp		x4, x5, [x10, 0x20]
	ldp		x6, x7, [x10, 0x30]
.endif /* domain_ID == none */

	/**
	 * Actually enter the SPTM dispatch logic. The SPTM will return to this
	 * point when the domain being called into (defined by x16) completes its
	 * call.
	 */
	SPTM_DOMAIN_ENTER x16

#if defined(XNU_CLIENT)
.ifc \has_hooks,yes
	/* Push a stack frame to preserve the original caller's FP/LR across the hook. */
	stp		fp, lr, [sp, #-16]!
	mov		fp, sp

	bl		__\domain_name\()_post_exit_hook

	/* Pop the original caller's FP/LR to allow for returning later. */
	mov		sp, fp
	ldp		fp, lr, [sp], #16
.endif
#endif /* XNU_CLIENT */

#if __has_feature(ptrauth_returns)
	retab
#else
	ret
#endif
.endm

/* clang-format on */

#define SPTM_VECTOR_IRQ    0
#define SPTM_VECTOR_FIQ    1
#define SPTM_VECTOR_SERROR 2
#define SPTM_VECTOR_SYNC   3

#else /* __ASSEMBLER__ */

#include <sys/cdefs.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <ptrauth.h>

__BEGIN_DECLS

/**
 * The maximum number of shared regions that can exist at any single point in
 * time. TXM needs this define which is why it's in this file.
 */
#define SHARED_REGION_MAX 255U

/* User-facing SPTM-defined types */
typedef uint64_t sptm_paddr_t;
typedef uint32_t sptm_ppnum_t;
typedef uint64_t sptm_poff_t;
typedef uint16_t sptm_asid_t;
typedef uint16_t sptm_vmid_t;
typedef uint64_t sptm_vaddr_t;
typedef uint64_t sptm_voff_t;
typedef uint64_t sptm_papt_t;
typedef uint8_t sptm_domain_t;
typedef uint32_t sptm_return_t;
typedef uint64_t sptm_pte_t;
typedef uint64_t sptm_tte_t;
typedef uint8_t sptm_pt_level_t;
typedef uint8_t sptm_iommu_id_t;
typedef uint16_t sptm_instance_id_t;
typedef uint32_t sptm_iommu_retype_params_t;

/**
 * The heart of the SPTM is its type system; here's the exhaustive list :).
 *
 * @note For all types T, make sure there's an entry for T in the `type_strings`
 *       array for debugging purposes.
 */
__enum_closed_decl(sptm_frame_type_t,
    uint8_t,
    {
        /* SPTM-owned type IDs */
        SPTM_UNTYPED,
        SPTM_UNUSED,
        SPTM_DEFAULT,
        SPTM_RO,
        SPTM_CODE,
        SPTM_TXM_CODE,
        SPTM_XNU_CODE,
        SPTM_XNU_CODE_DBG_RW, // Replaces SPTM_XNU_CODE if CTRR off.
        SPTM_KERNEL_ROOT_TABLE,
        SPTM_PAGE_TABLE,
        SPTM_IOMMU_BOOTSTRAP,

        /* XNU-owned type IDs */
        XNU_DEFAULT,
        XNU_RO,
        XNU_RO_DBG_RW, /* Replaces XNU_RO if CTRR off. */
        XNU_USER_EXEC,
        XNU_USER_DEBUG,
        XNU_USER_JIT,
        XNU_USER_ROOT_TABLE,
        XNU_SHARED_ROOT_TABLE,
        XNU_PAGE_TABLE,
        XNU_PAGE_TABLE_SHARED,
        XNU_PAGE_TABLE_ROZONE,
        XNU_PAGE_TABLE_COMMPAGE,
        XNU_IOMMU,
        XNU_ROZONE,
        XNU_IO,
        XNU_PROTECTED_IO,
        XNU_COMMPAGE_RW,
        XNU_COMMPAGE_RO,
        XNU_COMMPAGE_RX,
        XNU_TAG_STORAGE,
        XNU_STAGE2_ROOT_TABLE,
        XNU_STAGE2_PAGE_TABLE,
        XNU_KERNEL_RESTRICTED,
        XNU_RESERVED_1,
        XNU_RESERVED_2,
        XNU_RESTRICTED_IO,
        XNU_RESTRICTED_IO_TELEMETRY,
        XNU_SUBPAGE_USER_ROOT_TABLES,

        /* TXM-owned type IDs */
        TXM_DEFAULT,
        TXM_RO,
        TXM_RW,
        TXM_CPU_STACK,
        TXM_THREAD_STACK,
        TXM_ADDRESS_SPACE_TABLE,
        TXM_MALLOC_PAGE,
        TXM_FREE_LIST,
        TXM_SLAB_TRUST_CACHE,
        TXM_SLAB_PROFILE,
        TXM_SLAB_CODE_SIGNATURE,
        TXM_SLAB_CODE_REGION,
        TXM_SLAB_ADDRESS_SPACE,
        TXM_BUCKET_1024,
        TXM_BUCKET_2048,
        TXM_BUCKET_4096,
        TXM_BUCKET_8192,
        TXM_BULK_DATA,
        TXM_BULK_DATA_READ_ONLY,
        TXM_LOG,
        TXM_SEP_SECURE_CHANNEL,

        /* SK-owned type IDs */
        SK_DEFAULT,
        SK_SHARED_RO,
        SK_SHARED_RW,
        SK_IO,

        /* Everything below this point is not a real type ID */

        /* The number of real type IDs */
        N_FRAME_TYPES,

        FRAME_TYPE_INVALID,

        /**
         * A sentinel frame type used by some APIs. It may be passed by the caller
         * as the source type when retyping entire regions of memory, and behaves as
         * a catch-all value that will cause the entire region to be retyped,
         * regardless of the source type.
         */
        FRAME_TYPE_ANY,
    });

/**
 * A bitmask type to represent all frame types.
 *
 * BitInt, with current compiler settings, has an upper limit of 128 bits.
 * This limit can be overriden with an 'experimental' compiler option.
 * rdar://136538696 tracks making this option non-experimental.
 * Additionally, BitInt isn't playing nicely with XCTest. There's a
 * different rdar://136543539 to track fixing that. The plan is
 * to use __uint128_t until rdar://136543539 then BitInt(N_FRAME_TYPES).
 * The joys of being an early-adopter >_<.
 */
typedef __uint128_t frame_type_bitmask_t;

/**
 * Used to represent the target of a function call via the dispatch logic. A
 * Dispatch target effectively identifies a specific called domain, dispatch
 * table ID, and endpoint ID.
 *
 * ```
 *  63      56 55           48 47      40 39                      32 31                          0
 * +----------+---------------+----------+--------------------------+-----------------------------+
 * | Reserved | sptm_domain_t | Reserved | sptm_dispatch_table_id_t | sptm_dispatch_endpoint_id_t |
 * +----------+---------------+----------+--------------------------+-----------------------------+
 * ```
 */
typedef uint64_t sptm_dispatch_target_t;

/* Types used to represent fields within a dispatch target ID. */
typedef uint8_t sptm_dispatch_table_id_t;
typedef uint8_t sptm_dispatch_endpoint_id_t;

#if USE_UNSAFE_TYPES
/**
 * Only include this header when building the SPTM proper. To avoid needing to
 * include sptm_common.h itself inside of sptm_unsafe_params.h (to get access to
 * the above typedefs), just include the file after defining those typedefs.
 * Other files typically should not include sptm_unsafe_params.h directly, but
 * instead get it implicitly through including this file (which in turn is most
 * likely included indirectly itself).
 */
#include "sptm_unsafe_params.h"
#endif

/**
 * Describe the possible exception vector types that SPTM may handle. Used when
 * computing the offset of the XNU exception vector to hand control to when
 * an exception occurs during SPTM runtime.
 */
__enum_closed_decl(sptm_vector_type_t,
    uint8_t,
    {
        SPTM_VECTOR_IRQ,
        SPTM_VECTOR_FIQ,
        SPTM_VECTOR_SERROR,
        SPTM_VECTOR_SYNC,
        SPTM_N_VECTOR_TYPES,
    });

/**
 * SPTM Trace structure definition.
 */
#define SPTM_TRACE_SIZE_SHIFT     (6)
#define SPTM_TRACE_SIZE           (1) << SPTM_TRACE_SIZE_SHIFT

typedef struct {
	/* Unique trace identifier */
	uint64_t trace_id;

	/* Type of trace. This determines which structure to use below. */
	uint32_t trace_type;

	/* Dispatch ID of the trace emitter */
	uint16_t dispatch_id;

	/* ID of the CPU that emitted the trace */
	uint16_t cpu_id;

	/* Union  */
	union {
#define SPTM_TRACE_MAX_PARAMS     6
		uint64_t params[SPTM_TRACE_MAX_PARAMS];
	};
} sptm_trace_t __attribute__((aligned((SPTM_TRACE_SIZE))));

_Static_assert(sizeof(sptm_trace_t) == (SPTM_TRACE_SIZE),
    "Unexpected size for sptm_trace_t. Exceeded maxinum number of parameters?");

/**
 * SPTM Trace Codes.
 */
enum : uint32_t {
	/**
	 * This space is reserved for the allocation of trace IDs for traces that have
	 * arbitrary purposes. At present, the SPTM uses the tracing facilities solely
	 * for the purpose of flagging soft violations, which get their own ID space
	 * overlayed on top of this one (see the enum below).
	 */

	/**
	 * The following member is here to represent the number of supported
	 * traces. It does not represent a valid Trace Type.
	 */
	SPTM_N_TRACES,
};

/**
 * SPTM Public Violation Codes.
 *
 * @note These are just special-purpose trace codes. Their IDs are allocated
 *       in a way such that private and public violation ID spaces don't collide,
 *       effectively making all of the facilities associated with regular violations
 *       compatible with soft violations.
 *
 * @note If a new violation code is added, [violation_strings_public] should be updated
 *       as well, with an entry that maps the new violation ID with a description string.
 */
#define VIOLATION_FIRST_PUBLIC_ID 0xFF000000U
#define VIOLATION_PUBLIC_ID_MASK(violation_id) \
	SET_BIT(((violation_id) & ~VIOLATION_FIRST_PUBLIC_ID))

enum : uint32_t {
	VIOLATION_INVALID_IO_PADDR = VIOLATION_FIRST_PUBLIC_ID,
	VIOLATION_INVALID_DT_RANGE,
	VIOLATION_INVALID_RESTRICTED_IO_PADDR,

	/**
	 * The following member is here to represent the number of supported
	 * public violations. It does not represent a valid Violation ID.
	 */
	SPTM_N_PUBLIC_VIOLATIONS,
};

#define SPTM_TRACE_N_TRACES_PER_BUFFER (255ULL)

typedef struct {
	uint64_t write_index;
	sptm_trace_t buffer[SPTM_TRACE_N_TRACES_PER_BUFFER];
} sptm_trace_buffer_t __attribute__((aligned((1 << 14))));

_Static_assert(sizeof(sptm_trace_buffer_t) == (1 << 14), "Unexpected size for sptm_trace_buffer_t.");

/**
 * Structure that must be passed to the libsptm library's initialization
 * function before invoking any of the utility functions.
 *
 * @note Virtual addresses provided in the fields of this structure assume the
 *       the domain dereferencing them shares the same TTBR1 mappings as the
 *       SPTM.
 *
 * @note Some types below are void * because the actual type is an internal
 *       SPTM implementation detail. The library code will type-cast these
 *       values correctly as its built with the internal headers.
 */
#define LIBSPTM_VERSION_1              1U
#define LIBSPTM_VERSION_2              2U
#define LIBSPTM_VERSION_3              3U
#define LIBSPTM_VERSION_4              4U
#define LIBSPTM_VERSION_5              5U
#define LIBSPTM_VERSION_6              6U
#define LIBSPTM_VERSION_7              7U
#define LIBSPTM_VERSION_8              8U
#define LIBSPTM_VERSION_9              9U
#define LIBSPTM_VERSION_10             10U
#define LIBSPTM_VERSION                LIBSPTM_VERSION_10

typedef struct sptm_client_state {
	/* Version number identifying the set of included fields */
	int version;

	/* Version 1 fields: */
	/* The number of PAPT ranges the papt_ranges field points to */
	unsigned int *n_papt_ranges;

	/* The set of PAPT ranges */
	const void *papt_ranges;

	/* The first physical address */
	sptm_paddr_t first_phys;

	/* The last physical address */
	sptm_paddr_t last_phys;

	/* The first PAPT (virtual) address */
	sptm_papt_t first_papt;

	/* The last PAPT (virtual) address */
	sptm_papt_t last_papt;

	/* Physical address of this domain's TTBR1 root table */
	sptm_paddr_t root_table_paddr;

	/* Virtual address of the physical frame table */
	const void *frame_table;

	/* Virtual address of the type parameters table */
	const void *frame_type_params;

	/* Virtual address of the page-table attribute table */
	const void **pt_attr_table;

	/**
	 * CPU features, which may enable runtime support of SoC-specific
	 * functionality:
	 *
	 * LIBSPTM_CPU_FEATURE_USERAT: Set if the current system supports executing
	 *                             the AT instruction in userspace.
	 */
#define LIBSPTM_CPU_FEATURE_USERAT     1U
	uint64_t cpu_features;

	/* Number of IO frame table ranges */
	unsigned int n_io_ranges;

	/* Virtual address of the IO frame table */
	const void *io_frame_table;

	/* End of Version 1 fields */

	/* Version 2 fields removed in Version 6 */

	/* Version 3 fields: */
	sptm_paddr_t sptm_first_tag_storage_paddr;
	sptm_paddr_t sptm_last_tag_storage_paddr;
	const _Atomic(uint16_t) *sptm_panicking_cpu_id;

	/* Version 4 fields: */
	sptm_trace_buffer_t *trace_buffer;

	/* End of Version 4 fields */

	/* Version 5 fields: */
	const void *percpu_dispatch_state;
	unsigned int max_cpus;
	/* End of Version 5 fields */

	/* Version 6 fields: */
	const void *percpu_xnu_saved_state;
	/* End of Version 6 fields */

	/* Version 7 fields: */
	uint64_t feature_flags;

	/* Version 8 fields: */
	/* Virtual address of the allowed IO frame table and its size */
	const void *allowed_io_frame_table;
	unsigned int sptm_n_allowed_io_ranges;

	/* Virtual address of the sptm_pmap_io_ranges table and its size */
	const void *sptm_pmap_io_ranges;
	unsigned int sptm_pmap_io_ranges_count;
	/* End of Version 8 fields */

	/* Version 9 fields: */
	sptm_domain_t *sptm_panicking_domain_id;
	/* End of Version 9 fields */

	/* Version 10 fields: */
	const void *percpu_event_counters;
	/* End of Version 10 fields */

	/* Padding for future expansion */
	uint8_t reserved[88];
} libsptm_state_t;

/**
 * SPTM doesn't need to work on non-LP64 targets, but some drivers still build
 * against arm64_32, so only static_assert the size of libsptm_state_t on LP64
 * targets to avoid breaking these drivers. This can be removed once they no
 * longer build against arm64_32.
 */
#ifdef __LP64__
_Static_assert(sizeof(libsptm_state_t) == 312, "unexpected libsptm_state_t size");
#endif /* __LP64__ */

/**
 * Structure representing parameters than can be passed
 * to sptm_retype() depending on the type that a frame is
 * being transitioned to.
 */
typedef struct {
	union {
		/* Retype parameters when retyping to a CPU root table. */
		struct {
			/* Page table attribute index (e.g., SPTM_PT_GEOMETRY_16K). */
#if !USE_UNSAFE_TYPES
			uint8_t attr_idx;
#else
			sptm_attr_idx_u attr_idx_U;
#endif

			/* Root table flags to be set at retype time. */
#if !USE_UNSAFE_TYPES
			uint8_t flags;
#else
			sptm_root_flags_u flags_U;
#endif

			union {
				/**
				 * ASID to be used for stage 1 user root table. The zeroth ASID is reserved
				 * for the kernel, so the only valid values are 1 through
				 * MAX_HW_ASIDS (inclusive).
				 */
#if !USE_UNSAFE_TYPES
				sptm_asid_t asid;
#else
				sptm_asid_u asid_U;
#endif

				/*
				 * VMID to be used for stage 2 root table.  The zeroth VMID is reserved
				 * for Secure Kernel, so the only valid values are [1, MAX_VMIDS).
				 */
#if !USE_UNSAFE_TYPES
				sptm_vmid_t vmid;
#else
				sptm_vmid_u vmid_U;
#endif
			};
		};

		/* Retype parameters when retyping to a CPU page table. */
#if !USE_UNSAFE_TYPES
		sptm_pt_level_t level;
#else
		sptm_pt_level_u level_U;
#endif

		/* Retype parameters when retyping to an IOMMU page. */
		struct {
			/* The ID of the IOMMU driver who will be using this page. */
#if !USE_UNSAFE_TYPES
			uint8_t iommu_id;
#else
			sptm_iommu_id_u iommu_id_U;
#endif

			/* IOMMU-specific data that can be stored in each IOMMU page. */
#if !USE_UNSAFE_TYPES
			sptm_iommu_retype_params_t iommu_retype_params;
#else
			sptm_iommu_retype_params_t iommu_retype_params_U;
#endif
		};

		/* Retype parameters when retyping to an SK page. */
		struct {
#if !USE_UNSAFE_TYPES
			uint8_t sk_flags;
#else
			sptm_sk_flags_u sk_flags_U;
#endif
		};

		/* Used to set all of the retype parameters in one access. */
#if !USE_UNSAFE_TYPES
		uint64_t raw;
#else
		uint64_t raw_U;
#endif
	};
} sptm_retype_params_t;

/* Use this value when no retyping parameters are needed. */
#define SPTM_RETYPE_PARAMS_NULL (0ULL)

/**
 * An sptm_retype_params_t object should fit in a register.
 */
_Static_assert(sizeof(sptm_retype_params_t) == sizeof(uint64_t),
    "sptm_retype_params_t does not fit in a single register");

/**
 * Arguments for a domain-specific call, passed to the stub that
 * GEN_DOMAIN_ENTRY_STUB generates.
 *
 * @note The offset of each field is hard-coded in the macro.
 */
typedef struct {
	uint64_t x0;
	uint64_t x1;
	uint64_t x2;
	uint64_t x3;
	uint64_t x4;
	uint64_t x5;
	uint64_t x6;
	uint64_t x7;
} sptm_call_regs_t;

/**
 * Since we use hard-coded (not symbolic) offsets in GEN_DOMAIN_ENTRY_STUB,
 * assert that each field is where we expect.
 */
_Static_assert(offsetof(sptm_call_regs_t, x0) == (0 * sizeof(uint64_t)),
    "Unexpected sptm_call_regs_t offset");
_Static_assert(offsetof(sptm_call_regs_t, x1) == (1 * sizeof(uint64_t)),
    "Unexpected sptm_call_regs_t offset");
_Static_assert(offsetof(sptm_call_regs_t, x2) == (2 * sizeof(uint64_t)),
    "Unexpected sptm_call_regs_t offset");
_Static_assert(offsetof(sptm_call_regs_t, x3) == (3 * sizeof(uint64_t)),
    "Unexpected sptm_call_regs_t offset");
_Static_assert(offsetof(sptm_call_regs_t, x4) == (4 * sizeof(uint64_t)),
    "Unexpected sptm_call_regs_t offset");
_Static_assert(offsetof(sptm_call_regs_t, x5) == (5 * sizeof(uint64_t)),
    "Unexpected sptm_call_regs_t offset");
_Static_assert(offsetof(sptm_call_regs_t, x6) == (6 * sizeof(uint64_t)),
    "Unexpected sptm_call_regs_t offset");
_Static_assert(offsetof(sptm_call_regs_t, x7) == (7 * sizeof(uint64_t)),
    "Unexpected sptm_call_regs_t offset");

/**
 * Instantiates an entry stub with the specified name with the specified dispatch information.
 *
 * @param location_directive An assembly directive that describes where the code
 *                           should be located.
 * @param function_name The name of the stub.
 * @param entry_stub_name The name of the domain-entry stub (quoted string),
 *                        without the leading underscore.
 * @param domainID The dispatch domain ID of the call's destination.
 * @param tableID The dispatch table ID of the call's destination.
 * @param endpointID The dispatch endpoint ID of the call's destination.
 *
 * @return If the stub's dispatch destination returns a value (or values), it
 *         is in accordance with the 64-bit AAPCS.
 *
 * Disable clang-format around this macro as it gets very confused by macro-ized assembly.
 */
/* clang-format off */
#define GEN_NAMED_STUB(location_directive, function_name, entry_stub_name, domain_ID, table_ID, endpoint_ID) \
	__asm__ ( location_directive " \n" \
			 ".align 2 \n" \
			 ".globl _" #function_name "\n" \
			 "_" #function_name ":\n" \
			 "bti c\n" \
			 GEN_LOAD_DISPATCH_ID_CODE_SEQUENCE(domain_ID, table_ID, endpoint_ID) \
			 "b _" entry_stub_name "\n")
/* clang-format on */

#if defined(XNU_CLIENT) || defined(TXM_CLIENT) || defined(SK_CLIENT) || defined(SPTM_INTERNAL)
/**
 * Instantiates a named SPTM entry stub with the specified dispatch information.
 *
 * @param function_name The name of the stub.
 * @param tableID The dispatch table ID of the call's destination.
 * @param endpointID The dispatch endpoint ID of the call's destination.
 *
 * @return If the stub's dispatch destination returns a value (or values), it
 *         is in accordance with the 64-bit AAPCS.
 */
#define GEN_NAMED_SPTM_STUB(function_name, table_ID, endpoint_ID) \
	GEN_NAMED_STUB(".text", function_name, "sptm_enter", SPTM_DOMAIN, table_ID, endpoint_ID)

/**
 * Instantiates a named SPTM guest vcpu mode entry stub with the specified dispatch information.
 *
 * @note The sptm_guest_enter entry stub name does not call any hooks in XNU
 *       as we want to avoid modifying the XNU thread preemption state when
 *       operating in guest VCPU context.
 *
 * @param function_name The name of the stub.
 * @param tableID The dispatch table ID of the call's destination.
 * @param endpointID The dispatch endpoint ID of the call's destination.
 *
 * @return If the stub's dispatch destination returns a value (or values), it
 *         is in accordance with the 64-bit AAPCS.
 */
#define GEN_NAMED_SPTM_GUEST_STUB(function_name, table_ID, endpoint_ID)                    \
	GEN_NAMED_STUB(".text", function_name, "sptm_guest_mode_enter", SPTM_DOMAIN, table_ID, \
	    endpoint_ID)

/**
 * Instantiates a named SPTM entry stub with the specified dispatch information
 * that is callable before virtual address fixups have been applied in the
 * calling domain.
 *
 * @note This stub generator is meant to only be applied to stubs that call into
 *       the SPTM during the bootstrap process of a calling domain to tell the
 *       SPTM that it has completed its fixups (and that the SPTM should update
 *       the permissions for the normal TEXT section). Before this is done, the
 *       TEXT section (where all other stubs live) is not executable. During
 *       that time, only code in the BOOT_EXEC section is executable which is
 *       why this macro is needed.
 *
 * @param function_name The name of the stub.
 * @param tableID The dispatch table ID of the call's destination.
 * @param endpointID The dispatch endpoint ID of the call's destination.
 *
 * @return If the stub's dispatch destination returns a value (or values), it
 *         is in accordance with the 64-bit AAPCS.
 */
#define GEN_NAMED_SPTM_STUB_BOOTEXEC(function_name, table_ID, endpoint_ID)              \
	GEN_NAMED_STUB(".section __TEXT_BOOT_EXEC, __bootcode, regular, pure_instructions", \
	    function_name, "sptm_enter", SPTM_DOMAIN, table_ID, endpoint_ID)
#endif /* defined(XNU_CLIENT) || defined(TXM_CLIENT) || defined(SK_CLIENT) || defined(SPTM_INTERNAL) */

/**
 * Retype frame at a given physical address.
 *
 * @note [paddr] must be page-aligned.
 *
 * TODO: Add list of security checks which must be passed for the mappings to
 *       get updated. This should be explicit at the API level.
 *
 * @note This operation cannot gracefully fail; it will either succeed, or panic.
 *
 * @param paddr Physical address of the frame to retype.
 * @param current_type The current type of the frame must match this value.
 * @param new_type Frame to retype the frame to.
 * @param retype_params Type-specific information set at retype time.
 */
#if !USE_UNSAFE_TYPES
void sptm_retype(sptm_paddr_t paddr,
    sptm_frame_type_t current_type,
    sptm_frame_type_t new_type,
    sptm_retype_params_t retype_params);
#else
void sptm_retype(sptm_managed_page_u managed_page_U,
    sptm_frame_type_t current_type,
    sptm_frame_type_u new_type_U,
    sptm_retype_params_t retype_params_U);
#endif

#if defined(TXM_CLIENT) || defined(SK_CLIENT) || defined(SPTM_INTERNAL)

/**
 * Register a dispatch table with the SPTM dispatch logic. This registration
 * will associate a dispatch table ID with an entry point in the wanted domain.
 *
 * @note Any callable domain must register its dispatch table entries with this
 *       function during bootstrap. This will add an entry into the global
 *       dispatch table so future domains can call into it. If the requested
 *       entry in the table already exists a violation is thrown.
 *
 * @note Each calling domain has its own namespace for dispatch table IDs and
 *       the dispatch logic tracks which domain is calling this function by the
 *       calling_domain field in the per CPU dispatch state data.
 *
 * @param table_id_U The ID of the dispatch table to register for the calling
 *                  domain. The table IDs are unique for each domain performing
 *                  the registration, and should start at zero and go up from
 *                  here.
 * @param dispatch_entry Virtual address of the entry point to jump to when a
 *                       domain attempts to transition into the dispatch table
 *                       being registered. Depending on the domain performing
 *                       the registration, this virtual address may or may not
 *                       be accessible by the SPTM. This shouldn't matter as
 *                       long as the virtual address is executable within the
 *                       domain being entered.
 * @param permissions A bitmask describing which domains are allowed to call
 *                    endpoints within this dispatch table. Use the SET_BIT and
 *                    domain macros like such to define these permissions:
 *
 *                    permissions = SET_BIT(XNU_DOMAIN) | SET_BIT(TXM_DOMAIN);
 */
#if !USE_UNSAFE_TYPES
void sptm_register_dispatch_table(sptm_dispatch_table_id_t table_id,
    sptm_vaddr_t dispatch_entry,
    uint64_t permissions);
#else
void sptm_register_dispatch_table(sptm_dispatch_table_id_u table_id_U,
    sptm_dispatch_entry_addr_u dispatch_entry_U,
    uint64_t permissions);
#endif

/**
 * Initiate a system panic.
 *
 * @param panic_string The string to pass to SPTM that identifies the reason for the panic.
 *
 * @note This function does not retturn.
 */
void __attribute__((noreturn)) sptm_initiate_panic(const char *panic_string);

/**
 * Jumps to the SPTM dispatch logic from a client domain so it can return to
 * the domain that originally called it.
 *
 * @param return_value The return value to pass to the calling domain.
 *
 * @note This function does not return.
 */
void __attribute__((noreturn)) sptm_return_to_caller(uint64_t return_value);

/**
 * Jumps to the SPTM dispatch logic from a client domain when that client domain
 * is done saving its state after taking an interrupt. This tells SPTM dispatch logic
 * to proceed to hand off control to XNU to process the interrupt.
 *
 * @param vector_type Indicates which type of interrupt was received by the
 *                   domain. This parameter is ignored when TXM calls
 *                   this function, as TXM does not directly handle interrupts.
 * @param scheduler_interrupted Indicates that the SK scheduler was
 *                             was interrupted. This parameter is ignored
 *                             when TXM calls this function.
 *
 * @note This function does not return.
 */
void __attribute__((noreturn)) sptm_exception_state_saved(sptm_vector_type_t vector_type,
    bool scheduler_interrupted);
#endif /* defined(TXM_CLIENT) || defined(SK_CLIENT) */

/* Return values from the utility functions */
__enum_closed_decl(libsptm_error_t,
    uint8_t,
    {
        /* The libsptm call completed with no failures. */
        LIBSPTM_SUCCESS = 0,

        /* libsptm_init has not been called. */
        LIBSPTM_NOT_INITTED = 1,

        /* An invalid argument was passed into the library. */
        LIBSPTM_INVALID_ARG = 2,

        /* Physical frame type mismatch. */
        LIBSPTM_TYPE_MISMATCH = 3,

        /* Non-specific failure. */
        LIBSPTM_FAILURE = 4,
    });

/**
 * Refcounts types of frame types to use when interacting with the
 * refcount query API.
 */
__enum_closed_decl(libsptm_refcnt_type_t,
    uint8_t,
    {
        /* Caller doesn't have mapping. */
        SPTM_REFCOUNT_NONE = 0,
        /* Caller claims to have one read-only mapping of a cpu_page frame. */
        SPTM_REFCOUNT_RO = 1,
        /* Caller claims to have one write-exec mapping of a cpu_page frame. */
        SPTM_REFCOUNT_WX = 2,
        /* Caller claims to have one mapping to an XNU_IOMMU frame. */
        SPTM_REFCOUNT_IOMMU = 3,
    });

/**
 * SPTM CPU state types to use when interacting with the SPTM
 * CPU state query API.
 */
__enum_closed_decl(libsptm_cpu_state_t,
    uint8_t,
    {
        /* CPU is running in SPTM interrupted context. */
        CPUSTATE_SPTM_INTERRUPTED = 0,

        /* CPU is halted in an indefinite panic spin state. */
        CPUSTATE_PANIC_SPIN = 1,
    });

/* SPTM Library Utility Functions. */
#if defined(XNU_CLIENT) || defined(TXM_CLIENT) || defined(SPTM_INTERNAL)

/**
 * Initializes the SPTM library.
 *
 * @note This is an SPTM library function which does not require a call into the
 *       SPTM to complete.
 *
 * @param statep A pointer to a libsptm_state_t, which contains data essential
 *               to the library's utility functions. This structure should have
 *               been passed to the client domain through the bootstrap
 *               arguments setup by the SPTM.
 *
 * @return LIBSPTM_INVALID_ARG if [statep] is NULL, otherwise LIBPSTM_SUCCESS.
 */
extern libsptm_error_t __attribute__((__warn_unused_result__)) libsptm_init(
    const libsptm_state_t *statep);

/**
 * Translates the specified kernel virtual address to a physical address.
 *
 * @note This is an SPTM library function which does not require a call into the
 *       SPTM to complete.
 *
 * @note [paddrp] is only initialized on successful return.
 *
 * @param vaddr Virtual address to translate.
 * @param paddrp Pointer to a physical address to store the result.
 *
 * @return LIBSPTM_SUCCESS if the virtual address was successfully translated.
 *         LIBPSPTM_INVALID_ARG if [paddrp] is NULL.
 *         LIBSPTM_FAILURE otherwise.
 */
extern libsptm_error_t __attribute__((__warn_unused_result__)) sptm_kvtophys(sptm_papt_t vaddr,
    sptm_paddr_t *paddrp);

/**
 * Translates the physical address given to a virtual address within the
 * physical aperture.
 *
 * @note This is an SPTM library function which does not require a call into the
 *       SPTM to complete.
 *
 * @note [vaddrp] is only initialized on successful return.
 *
 * @param paddr The physical address to translate.
 * @param vaddrp A pointer to storage holding the translated virtual address.
 *
 * @return LIBSPTM_SUCCESS if the physical address was successfully translated.
 *         LIBPSPTM_INVALID_ARG if [vaddrp] is NULL.
 *         LIBSPTM_FAILURE otherwise.
 */
extern libsptm_error_t __attribute__((__warn_unused_result__)) sptm_phystokv(sptm_paddr_t paddr,
    sptm_papt_t *vaddrp);

/**
 * Returns the frame type of the physical page backing the specified virtual
 * address.
 *
 * @note This is an SPTM library function which does not require a call into the
 *       SPTM to complete.
 *
 * @note [frame_typep] is only initialized on successful return.
 *
 * @param vaddr The virtual address whose physical address's type is to be
 *              returned.
 * @param frame_typep A pointer to the frame type variable that will hold the
 *                    result.
 *
 * @return LIBSPTM_SUCCESS If the virtual address was successfully translated
 *                         to a physical address AND if that physical address
 *                         corresponds to typed memory.
 *         LIBPSPTM_INVALID_ARG if [frame_typep] is NULL.
 *         LIBSPTM_FAILURE otherwise.
 */
extern libsptm_error_t __attribute__((__warn_unused_result__)) sptm_get_vaddr_type(sptm_vaddr_t vaddr,
    sptm_frame_type_t *frame_typep);

/**
 * Returns the frame type of the specified physical page.
 *
 * @note This is an SPTM library function which does not require a call into the
 *       SPTM to complete.
 *
 * @note [frame_typep] is only initialized on successful return.
 *
 * @param paddr The physical address whose type is sought.
 * @param frame_typep A pointer to the frame type variable that will hold the
 *                    result.
 *
 * @return LIBSPTM_SUCCESS if the specified physical address corresponds to
 *                         typed memory.
 *         LIBPSPTM_INVALID_ARG if [frame_typep] is NULL.
 *         LIBSPTM_FAILURE otherwise.
 */
extern libsptm_error_t __attribute__((__warn_unused_result__)) sptm_get_paddr_type(sptm_paddr_t paddr,
    sptm_frame_type_t *frame_typep);

/**
 * Provides information on whether the number of mappings of a given physical
 * page is zero or not.
 *
 * @note This is an SPTM library function which does not require a call into the
 *       SPTM to complete.
 *
 * @note For now, the function supports only types of cpu-page and XNU_IOMMU.
 *
 * @note [is_lastp] is only initialized on successful return.
 *
 * @note [refcnt_type] represents the kind of mapping the caller claims to have,
 *       and the [is_lastp] set to TRUE iff there are no mappings BESIDES that one.
 *
 * @note The caller may claim to have only ONE mapping, and if this kind doesn't exist,
 *       the function returns LIBSPTM_FAILURE.
 *
 * @note If the caller claims to own no mappings [refcnt_type] should be
 *       SPTM_REFCOUNT_NONE.
 *
 * @param paddr The physical address whose refcount to check.
 *
 * @param refcnt_type An enum describes the kind of mappings the caller may
 *        claim to own. If this kind doesn't align up with the type of the
 *        frame, the function returns LIBSPTM_FAILURE.
 *
 * @param is_lastp A pointer to a boolean holds the results, indicates if the number
 *        of all mappings of [paddr] is zero or not, not including the one mapping
 *        the owner claims to have.
 *
 * @return LIBSPTM_SUCCESS if the information is obtained successfully.
 *         LIBPSPTM_INVALID_ARG if [is_lastp] is NULL.
 *         LIBSPTM_FAILURE otherwise.
 */
extern libsptm_error_t __attribute__((__warn_unused_result__))
sptm_paddr_is_last_mapping(sptm_paddr_t paddr, libsptm_refcnt_type_t refcnt_type, bool *is_lastp);

/**
 * Retrieves the domain ID of the source that triggered the SPTM panic.
 *
 * @param panic_domain_id Pointer to store the domain ID of the panicking source.
 *
 * @return LIBSPTM_SUCCESS if the `panic_domain_id` pointer is successfully set.
 *         LIBSPTM_NOT_INITTED if libsptm is not yet initialized
 *         LIBPSPTM_INVALID_ARG if the input parameter `panic_domain_id` pointer is NULL.
 *         LIBSPTM_FAILURE if `libsptm_panicking_domain_id` pointer is NULL or
 *                         if `libsptm_panicking_domain_id` is an invalid domain.
 */
extern libsptm_error_t __attribute__((__warn_unused_result__)) sptm_panic_source(
    sptm_domain_t *panic_domain_id);

/**
 * Provides information on the current dispatch state of each SPTM CPU.
 *
 * @note This is an SPTM library function which does not require a call into the
 *       SPTM to complete.
 *
 * @note CAUTION: For performance reasons, SPTM dispatch does not
 *       issue memory barriers when dispatch state changes. This call is not
 *       guaranteed to return the instantaneous state of a core when being used to
 *       query the state of a core other than the core issuing the query.
 *
 * @param sptm_logical_cpu_id The SPTM logical CPU ID being queried.
 *
 * @param state_type The particular state the client is querying for. See
 *        the libsptm_cpu_state_t enum for supported states.
 *
 * @param state Output parameter indicating whether the CPU being queried
 *        is currently in the [state_type] state.
 *
 * @return LIBSPTM_SUCCESS if the information is correctly returned
 *         LIBSPTM_FAILURE otherwise.
 */
extern libsptm_error_t __attribute__((__warn_unused_result__))
sptm_get_cpu_state(uint64_t sptm_logical_cpu_id, libsptm_cpu_state_t state_type, bool *state);

/**
 * Provides information on the current SPTM panic state.
 *
 * @note This is an SPTM library function which does not require a call into the
 *       SPTM to complete.
 *
 * @param sptm_logical_cpu_id Pointer to the SPTM logical CPU ID to
 *       be returned.
 *
 * @return LIBSPTM_SUCCESS if the information is correctly returned
 *         LIBSPTM_NOT_INITTED if libsptm is not yet initialized
 *         LIBSPTM_INVALID_ARG if the input parameter is NULL
 *         LIBSPTM_FAILURE if there is not a recorded panicking CPU
 */
extern libsptm_error_t __attribute__((__warn_unused_result__)) sptm_get_panicking_cpu_id(
    uint64_t *sptm_logical_cpu_id);

/**
 * Provides information on whether certain optional features are supported.
 *
 * @note Refer to the SPTM_FEATURE_* definitions above to see what feature flags
 *       are available.
 *
 * @param features Bitmap that conveys the feature flags that the caller is checking for.
 *
 * @param available Pointer to a boolean that this function will set to true if all queried
 *                  features are available, or false if at least one of them is not.
 *
 * @return LIBSPTM_SUCCESS if the information is correctly returned
 *         LIBSPTM_FAILURE otherwise.
 */
extern libsptm_error_t __attribute__((__warn_unused_result__))
sptm_features_available(uint64_t features, bool *available);

#endif /* defined(XNU_CLIENT) || defined(TXM_CLIENT) || defined(SPTM_INTERNAL) */

__END_DECLS

#endif /* __ASSEMBLER__ */
