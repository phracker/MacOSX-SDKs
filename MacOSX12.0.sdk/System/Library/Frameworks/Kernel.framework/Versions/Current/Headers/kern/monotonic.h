/*
 * Copyright (c) 2017-2019 Apple Inc. All rights reserved.
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
#ifndef KERN_MONOTONIC_H
#define KERN_MONOTONIC_H

#if MONOTONIC

#include <stdbool.h>
#include <stdint.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

extern bool mt_debug;
extern _Atomic uint64_t mt_pmis;
extern _Atomic uint64_t mt_retrograde;

void mt_fixed_counts(uint64_t *counts);
void mt_cur_thread_fixed_counts(uint64_t *counts);
void mt_cur_task_fixed_counts(uint64_t *counts);
uint64_t mt_cur_cpu_instrs(void);
uint64_t mt_cur_cpu_cycles(void);
void mt_cur_cpu_cycles_instrs_speculative(uint64_t *cycles, uint64_t *instrs);
uint64_t mt_cur_thread_instrs(void);
uint64_t mt_cur_thread_cycles(void);

bool mt_acquire_counters(void);
bool mt_owns_counters(void);
void mt_ownership_change(bool available);
void mt_release_counters(void);

__END_DECLS


#endif /* MONOTONIC */

#endif /* !defined(KERN_MONOTONIC_H) */
