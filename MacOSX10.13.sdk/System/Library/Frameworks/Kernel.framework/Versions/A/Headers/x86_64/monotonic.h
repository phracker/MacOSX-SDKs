#ifndef X86_64_MONOTONIC_H
#define X86_64_MONOTONIC_H

#include <stdint.h>

#define MT_NDEVS 1

#define MT_CORE_NFIXED 3

#define MT_CORE_INSTRS 0
#define MT_CORE_CYCLES 1
#define MT_CORE_REFCYCLES 2
#define MT_CORE_MAXVAL ((UINT64_C(1) << 48) - 1)

#endif /* !defined(X86_64_MONOTONIC_H) */
