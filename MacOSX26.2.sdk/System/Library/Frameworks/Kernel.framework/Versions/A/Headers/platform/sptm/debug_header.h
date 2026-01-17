/*
 * Copyright (c) 2023 Apple Inc. All rights reserved.
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

#pragma once

#include <stddef.h>
#include <stdint.h>

static uint32_t const DEBUG_HEADER_MAGIC_VAL = 'GBED'; /* "DEBG" in little endian */
static uint32_t const DEBUG_HEADER_CURRENT_VERSION = 0x2UL;

typedef void *debug_header_entry;

/**
 * The debug header.
 *
 * A simple structure that helps a debugger find all loaded images.
 *
 * It consists of simple magic, version, and count fields. Following
 * it are pointers to the start of all loaded images (usually also
 * their mach-O headers).
 *
 * The debug header must always be exactly 4096 bytes after VBAR_GL2,
 * or VBAR_EL2 if GXF is not enabled yet. Therefore, any collection
 * of exception handlers that VBAR may point to during bootstrap needs
 * to be followed by a separate debug header.
 *
 * The pointers must always be currently valid virtual addresses, so
 * the entries of some debug headers may undergo some transition during
 * bootstrap, when we switch between address translations (e.g. because
 * we switch away from V=P mappings).
 */

typedef struct __attribute__((__packed__)) debug_header {
	uint32_t magic;
	uint32_t version;
	uint32_t count;
	uint32_t resvd;

	// <count> entries of currently valid virtual addresses pointing to loaded images.
	debug_header_entry image[];
} debug_header_t;

_Static_assert((offsetof(debug_header_t, image) % 8) == 0, "image list not aligned");

/**
 * The debug trailer is simply what's after the `entry_image[]` list above. New fields can be
 * added here, without confusing older versions of astris (or anything else).
 */

typedef struct debug_trailer {
	/* Pointer to the consistent debug page, which iBoot allocates. */
	struct sptm_consistent_debug *sptm_consistent_debug;

	/**
	 * Flag used during bootstrap, indicating whether the debug header
	 * has been translated to the final address space (i.not anymore
	 * in a V=P mapping while the MMU is off).
	 */
	uint64_t translated;
} debug_trailer_t;

/**
 * Fixed indices for the known SPTM, XNU, TXM images.
 *
 * While the debug header is followed by a generic list of entries,
 * debuggers make some assumptions about what order images appear
 * in this list.
 */
static int const DEBUG_HEADER_ENTRY_SPTM = 0;
static int const DEBUG_HEADER_ENTRY_XNU = 1;
static int const DEBUG_HEADER_ENTRY_TXM = 2;

/**
 * SPTM consistent debug page
 *
 * astris cannot resolve the debug header for checking whether the SPTM panicked
 * during early boot, as `VBAR_EL2/GL2` is only accessible via MSR. For this, we
 * have an extra page allocated by iBoot, which the consistent debug region references.
 * astris can use the consistent debug region to find the page and check for a panic.
 *
 * For exceptions, we also capture a few registers of the first exception, which can be
 * immensely helpful when e.g. debugging early bootstrap exceptions.
 *
 * Adjust CONSISTENT_DEBUG_PANIC_LEN if required when adding any new panic strings.
 */
static size_t const CONSISTENT_DEBUG_PANIC_LEN = 1088;

typedef struct __attribute__((__packed__)) sptm_consistent_debug {
	uint64_t magic;
	uint64_t version;
	uint64_t is_panic;
	uint64_t exception_number; /* 0 if it's a regular panic, not an early exception. */
	uint64_t first_esr;
	uint64_t first_elr;
	uint64_t first_far;

	/* Added in version 2: */

	/* physical, optional, if 0 there might be a panic string in panic_string */
	uint64_t panic_string_addr_phys;
	uint64_t panic_source;
	/* optional, but always 0-terminated. */
	char panic_string[CONSISTENT_DEBUG_PANIC_LEN];
} sptm_consistent_debug_t;

static uint64_t const CONSISTENT_DEBUG_PANIC_SOURCE_SPTM = 0;
static uint64_t const CONSISTENT_DEBUG_PANIC_SOURCE_TXM = 1;
static uint64_t const CONSISTENT_DEBUG_PANIC_SOURCE_SK = 2;

static int const CONSISTENT_DEBUG_MAGIC_VAL = 'MTPS'; /* "SPTM" in little endian */
static int const CONSISTENT_DEBUG_VERSION_VAL = 2;
