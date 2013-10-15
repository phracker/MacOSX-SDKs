#include "sysv.h"

#define DONT_USE_NLIST 1

#undef NPROC_SYMBOL

#undef bsdlike

#define ARP_SCAN_FOUR_ARGUMENTS

/* uncomment this to read process names from /proc/X/cmdline (like <= 5.0) */
/* #define USE_PROC_CMDLINE */

/*
 * red hat >= 5.0 doesn't have this 
 */
#ifndef MNTTYPE_PROC
#define MNTTYPE_PROC "proc"
#endif
