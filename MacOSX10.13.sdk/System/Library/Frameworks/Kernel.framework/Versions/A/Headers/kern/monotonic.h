#ifndef KERN_MONOTONIC_H
#define KERN_MONOTONIC_H

#include <stdbool.h>
#include <stdint.h>

extern bool mt_task_thread_counting;
extern bool mt_debug;
extern _Atomic uint64_t mt_pmis;
extern _Atomic uint64_t mt_retrograde;

void mt_fixed_counts(uint64_t *counts);
void mt_cur_thread_fixed_counts(uint64_t *counts);
void mt_cur_task_fixed_counts(uint64_t *counts);
uint64_t mt_cur_cpu_instrs(void);
uint64_t mt_cur_cpu_cycles(void);
uint64_t mt_cur_thread_instrs(void);
uint64_t mt_cur_thread_cycles(void);


#endif /* !defined(KERN_MONOTONIC_H) */
