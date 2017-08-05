#ifndef MACHINE_MONOTONIC_H
#define MACHINE_MONOTONIC_H

#if defined(__x86_64__)
#include <x86_64/monotonic.h>
#else
#error unsupported architecture
#endif

#include <stdatomic.h>
#include <stdbool.h>
#include <stdint.h>

extern bool mt_core_supported;

struct mt_cpu {
	uint64_t mtc_snaps[MT_CORE_NFIXED];
	uint64_t mtc_counts[MT_CORE_NFIXED];
	uint64_t mtc_counts_last[MT_CORE_NFIXED];
};

struct mt_thread {
	_Atomic uint64_t mth_gen;
	uint64_t mth_counts[MT_CORE_NFIXED];
};

struct mt_task {
	uint64_t mtk_counts[MT_CORE_NFIXED];
};

struct mt_cpu *mt_cur_cpu(void);
void mt_mtc_update_fixed_counts(struct mt_cpu *mtc, uint64_t *counts,
		uint64_t *counts_since);
uint64_t mt_mtc_update_count(struct mt_cpu *mtc, unsigned int ctr);
uint64_t mt_core_snap(unsigned int ctr);
void mt_core_set_snap(unsigned int ctr, uint64_t snap);
void mt_mtc_set_snap(struct mt_cpu *mtc, unsigned int ctr, uint64_t snap);

#endif /* !defined(MACHINE_MONOTONIC_H) */
