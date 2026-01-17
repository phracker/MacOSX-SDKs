/*
 * Copyright (c) 2000-2019 Apple Inc. All rights reserved.
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

#ifndef _KERN_DEBUG_H_
#define _KERN_DEBUG_H_

#include <kern/kcdata.h>

#include <sys/appleapiopts.h>
#include <sys/cdefs.h>
#include <stdint.h>
#include <stdarg.h>
#include <uuid/uuid.h>
#include <mach/boolean.h>
#include <mach/kern_return.h>
#include <mach/vm_types.h>
#include <kern/panic_call.h>

#include <TargetConditionals.h>

__BEGIN_DECLS

#ifdef __APPLE_API_PRIVATE
#ifdef __APPLE_API_UNSTABLE

struct thread_snapshot {
	uint32_t                snapshot_magic;
	uint32_t                nkern_frames;
	uint32_t                nuser_frames;
	uint64_t                wait_event;
	uint64_t                continuation;
	uint64_t                thread_id;
	uint64_t                user_time;
	uint64_t                system_time;
	int32_t                 state;
	int32_t                 priority;    /*	static priority */
	int32_t                 sched_pri;   /* scheduled (current) priority */
	int32_t                 sched_flags; /* scheduler flags */
	char                    ss_flags;
	char                    ts_qos;      /* effective qos */
	char                    ts_rqos;     /* requested qos */
	char                    ts_rqos_override; /* requested qos override */
	char                    io_tier;
	/*
	 * In microstackshots, the low two bytes are the start of the first async
	 * frame in the thread's user space call stack.  If the call stack lacks
	 * async stack frames, it's `UINT16_MAX`.
	 */
	char                    _reserved[3]; /* pad for 4 byte alignement packing */

	/*
	 * I/O Statistics
	 * XXX: These fields must be together
	 */
	uint64_t                disk_reads_count;
	uint64_t                disk_reads_size;
	uint64_t                disk_writes_count;
	uint64_t                disk_writes_size;
	uint64_t                io_priority_count[STACKSHOT_IO_NUM_PRIORITIES];
	uint64_t                io_priority_size[STACKSHOT_IO_NUM_PRIORITIES];
	uint64_t                paging_count;
	uint64_t                paging_size;
	uint64_t                non_paging_count;
	uint64_t                non_paging_size;
	uint64_t                data_count;
	uint64_t                data_size;
	uint64_t                metadata_count;
	uint64_t                metadata_size;
	/* XXX: I/O Statistics end */

	uint64_t                voucher_identifier; /* obfuscated voucher identifier */
	uint64_t                total_syscalls;
	char                    pth_name[STACKSHOT_MAX_THREAD_NAME_SIZE];
} __attribute__((packed));

/* old, non kcdata format */
struct task_snapshot {
	uint32_t snapshot_magic;
	int32_t pid;
	uint64_t                uniqueid;
	uint64_t                user_time_in_terminated_threads;
	uint64_t                system_time_in_terminated_threads;
	uint8_t                 shared_cache_identifier[16];
	uint64_t                shared_cache_slide;
	uint32_t                nloadinfos;
	int                     suspend_count;
	int                     task_size;      /* pages */
	int                     faults;         /* number of page faults */
	int                     pageins;        /* number of actual pageins */
	int                     cow_faults;     /* number of copy-on-write faults */
	uint32_t                ss_flags;
	/*
	 * In microstackshots, `p_start_sec` is actually the resource coalition ID
	 * that this thread belongs to.
	 */
	uint64_t                p_start_sec;    /* from the bsd proc struct */
	/*
	 * In microstackshots, `p_stat_usec` is actually the resource coalition ID
	 * that this thread is doing work on behalf of.
	 */
	uint64_t                p_start_usec;   /* from the bsd proc struct */

	/*
	 * We restrict ourselves to a statically defined
	 * (current as of 2009) length for the
	 * p_comm string, due to scoping issues (osfmk/bsd and user/kernel
	 * binary compatibility).
	 */
	char                    p_comm[17];
	uint32_t                was_throttled;
	uint32_t                did_throttle;
	uint32_t                latency_qos;
	/*
	 * I/O Statistics
	 * XXX: These fields must be together.
	 */
	/*
	 * In microstackshots, `disk_reads_count` is actually
	 * the full 64-bits of ss_flags.
	 */
	uint64_t                disk_reads_count;
	uint64_t                disk_reads_size;
	uint64_t                disk_writes_count;
	uint64_t                disk_writes_size;
	uint64_t                io_priority_count[STACKSHOT_IO_NUM_PRIORITIES];
	uint64_t                io_priority_size[STACKSHOT_IO_NUM_PRIORITIES];
	uint64_t                paging_count;
	uint64_t                paging_size;
	uint64_t                non_paging_count;
	uint64_t                non_paging_size;
	uint64_t                data_count;
	uint64_t                data_size;
	uint64_t                metadata_count;
	uint64_t                metadata_size;
	/* XXX: I/O Statistics end */

	uint32_t                donating_pid_count;
} __attribute__ ((packed));



struct micro_snapshot {
	uint32_t                snapshot_magic;
	uint32_t                ms_cpu;  /* cpu number this snapshot was recorded on */
	uint64_t                ms_time; /* time at sample (seconds) */
	uint64_t                ms_time_microsecs;
	uint8_t                 ms_flags;
	uint16_t                ms_opaque_flags;        /* managed by external entity, e.g. fdrmicrod */
} __attribute__ ((packed));


/*
 * mirrors the dyld_cache_header struct defined in dyld_cache_format.h from dyld source code
 */
struct _dyld_cache_header {
	char        magic[16];                          // e.g. "dyld_v0    i386"
	uint32_t    mappingOffset;      // file offset to first dyld_cache_mapping_info
	uint32_t    mappingCount;       // number of dyld_cache_mapping_info entries
	uint32_t    imagesOffset;       // file offset to first dyld_cache_image_info
	uint32_t    imagesCount;        // number of dyld_cache_image_info entries
	uint64_t    dyldBaseAddress;    // base address of dyld when cache was built
	uint64_t    codeSignatureOffset;// file offset of code signature blob
	uint64_t    codeSignatureSize;  // size of code signature blob (zero means to end of file)
	uint64_t    slideInfoOffset;    // file offset of kernel slid info
	uint64_t    slideInfoSize;      // size of kernel slid info
	uint64_t    localSymbolsOffset; // file offset of where local symbols are stored
	uint64_t    localSymbolsSize;   // size of local symbols information
	uint8_t     uuid[16];           // unique value for each shared cache file
	uint64_t    cacheType;          // 0 for development, 1 for production
	uint32_t    branchPoolsOffset;  // file offset to table of uint64_t pool addresses
	uint32_t    branchPoolsCount;   // number of uint64_t entries
	uint64_t    accelerateInfoAddr; // (unslid) address of optimization info
	uint64_t    accelerateInfoSize; // size of optimization info
	uint64_t    imagesTextOffset;   // file offset to first dyld_cache_image_text_info
	uint64_t    imagesTextCount;    // number of dyld_cache_image_text_info entries
	uint64_t    dylibsImageGroupAddr;// (unslid) address of ImageGroup for dylibs in this cache
	uint64_t    dylibsImageGroupSize;// size of ImageGroup for dylibs in this cache
	uint64_t    otherImageGroupAddr;// (unslid) address of ImageGroup for other OS dylibs
	uint64_t    otherImageGroupSize;// size of oImageGroup for other OS dylibs
	uint64_t    progClosuresAddr;   // (unslid) address of list of program launch closures
	uint64_t    progClosuresSize;   // size of list of program launch closures
	uint64_t    progClosuresTrieAddr;// (unslid) address of trie of indexes into program launch closures
	uint64_t    progClosuresTrieSize;// size of trie of indexes into program launch closures
	uint32_t    platform;           // platform number (macOS=1, etc)
	uint32_t    formatVersion        : 8,// dyld3::closure::kFormatVersion
	    dylibsExpectedOnDisk : 1,      // dyld should expect the dylib exists on disk and to compare inode/mtime to see if cache is valid
	    simulator            : 1,      // for simulator of specified platform
	    locallyBuiltCache    : 1,      // 0 for B&I built cache, 1 for locally built cache
	    padding              : 21;     // TBD
};

/*
 * mirrors the dyld_cache_image_text_info struct defined in dyld_cache_format.h from dyld source code
 */
struct _dyld_cache_image_text_info {
	uuid_t      uuid;
	uint64_t    loadAddress;        // unslid address of start of __TEXT
	uint32_t    textSegmentSize;
	uint32_t    pathOffset;         // offset from start of cache file
};

#if CONFIG_X86_64_COMPAT
/*
 * mirrors the AotCacheHeader struct defined in SharedCacheMetadata.h from cambria source code
 */
#define CAMBRIA_VERSION_INFO_SIZE 32
struct _aot_cache_header {
	char     magic[8];
	uint8_t  uuid[16];
	uint8_t  x86_uuid[16];
	uint8_t  cambria_version[CAMBRIA_VERSION_INFO_SIZE];
	uint64_t code_signature_offset;
	uint64_t code_signature_size;
	uint32_t num_code_fragments;
	uint32_t header_size;
	// shared_file_mapping_np mappings is omitted here
};
#endif /* CONFIG_X86_64_COMPAT */

enum micro_snapshot_flags {
	/*
	 * (Timer) interrupt records are no longer supported.
	 */
	kInterruptRecord        = 0x01,
	/*
	 * Timer arming records are no longer supported.
	 */
	kTimerArmingRecord      = 0x02,
	kUserMode               = 0x04, /* interrupted usermode, or armed by usermode */
	kIORecord               = 0x08,
	kPMIRecord              = 0x10,
	kMACFRecord             = 0x20, /* armed by MACF policy */
	kKernelThread           = 0x40, /* sampled a kernel thread */
};

/*
 * Flags used in the following assortment of snapshots.
 */
enum generic_snapshot_flags {
	kUser64_p               = 0x1, /* Userspace uses 64 bit pointers */
	kKernel64_p             = 0x2  /* The kernel uses 64 bit pointers */
};

#define VM_PRESSURE_TIME_WINDOW 5 /* seconds */

__options_decl(stackshot_flags_t, uint64_t, {
	STACKSHOT_GET_DQ                           = 0x01,
	STACKSHOT_SAVE_LOADINFO                    = 0x02,
	STACKSHOT_GET_GLOBAL_MEM_STATS             = 0x04,
	STACKSHOT_SAVE_KEXT_LOADINFO               = 0x08,
	/*
	 * 0x10, 0x20, 0x40 and 0x80 are reserved.
	 *
	 * See microstackshot_flags_t whose members used to be part of this
	 * declaration.
	 */
	STACKSHOT_ACTIVE_KERNEL_THREADS_ONLY       = 0x100,
	STACKSHOT_GET_BOOT_PROFILE                 = 0x200,
	STACKSHOT_DO_COMPRESS                      = 0x400,
	/* Now on by default/unused */
	STACKSHOT_SAVE_IMP_DONATION_PIDS           = 0x2000,
	STACKSHOT_SAVE_IN_KERNEL_BUFFER            = 0x4000,
	STACKSHOT_RETRIEVE_EXISTING_BUFFER         = 0x8000,
	STACKSHOT_KCDATA_FORMAT                    = 0x10000,
	STACKSHOT_ENABLE_BT_FAULTING               = 0x20000,
	STACKSHOT_COLLECT_DELTA_SNAPSHOT           = 0x40000,
	/* Include the layout of the system shared cache */
	STACKSHOT_COLLECT_SHAREDCACHE_LAYOUT       = 0x80000,
	/*
	 * Kernel consumers of stackshot (via stack_snapshot_from_kernel) can ask
	 * that we try to take the stackshot lock, and fail if we don't get it.
	 */
	STACKSHOT_TRYLOCK                          = 0x100000,
	STACKSHOT_ENABLE_UUID_FAULTING             = 0x200000,
	STACKSHOT_FROM_PANIC                       = 0x400000,
	STACKSHOT_NO_IO_STATS                      = 0x800000,
	/* Report owners of and pointers to kernel objects that threads are blocked on */
	STACKSHOT_THREAD_WAITINFO                  = 0x1000000,
	STACKSHOT_THREAD_GROUP                     = 0x2000000,
	STACKSHOT_SAVE_JETSAM_COALITIONS           = 0x4000000,
	STACKSHOT_INSTRS_CYCLES                    = 0x8000000,
	STACKSHOT_ASID                             = 0x10000000,
	STACKSHOT_PAGE_TABLES                      = 0x20000000,
	STACKSHOT_DISABLE_LATENCY_INFO             = 0x40000000,
	STACKSHOT_SAVE_DYLD_COMPACTINFO            = 0x80000000,
	STACKSHOT_INCLUDE_DRIVER_THREADS_IN_KERNEL = 0x100000000,
	
	STACKSHOT_EXCLAVES                         = 0x200000000,
	
	STACKSHOT_SKIP_EXCLAVES                    = 0x400000000,
	STACKSHOT_MTEINFO                          = 0x800000000,
}); // Note: Add any new flags to kcdata.py (stackshot_in_flags)

__options_decl(microstackshot_flags_t, uint32_t, {
	/*
	 * Collect and consume kernel thread microstackshots.
	 */
	STACKSHOT_GET_KERNEL_MICROSTACKSHOT        = 0x0008,
	/*
	 * Collect user thread microstackshots.
	 */
	STACKSHOT_GET_MICROSTACKSHOT               = 0x0010,
	/*
	 * Enable and disable are longer supported; use telemetry(2) instead.
	 */
	STACKSHOT_GLOBAL_MICROSTACKSHOT_ENABLE     = 0x0020,
	STACKSHOT_GLOBAL_MICROSTACKSHOT_DISABLE    = 0x0040,
	/*
	 * For user thread microstackshots, set a mark to consume the entries.
	 */
	STACKSHOT_SET_MICROSTACKSHOT_MARK          = 0x0080,
});

__options_decl(telemetry_notice_t, uint32_t, {
	/*
	 * User space microstackshots should be read.
	 */
	TELEMETRY_NOTICE_BASE                 = 0x00,
	/*
	 * Kernel microstackshots should be read.
	 */
	TELEMETRY_NOTICE_KERNEL_MICROSTACKSHOT = 0x01,
});

#define STACKSHOT_THREAD_SNAPSHOT_MAGIC     0xfeedface
#define STACKSHOT_TASK_SNAPSHOT_MAGIC       0xdecafbad
#define STACKSHOT_MEM_AND_IO_SNAPSHOT_MAGIC 0xbfcabcde
#define STACKSHOT_MICRO_SNAPSHOT_MAGIC      0x31c54011

#define STACKSHOT_PAGETABLES_MASK_ALL           ~0

__options_closed_decl(kf_override_flag_t, uint32_t, {
	KF_SERIAL_OVRD                            = 0x2,
	KF_PMAPV_OVRD                             = 0x4,
	KF_MATV_OVRD                              = 0x8,
	KF_STACKSHOT_OVRD                         = 0x10,
	KF_COMPRSV_OVRD                           = 0x20,
	KF_INTERRUPT_MASKED_DEBUG_OVRD            = 0x40,
	KF_TRAPTRACE_OVRD                         = 0x80,
	KF_IOTRACE_OVRD                           = 0x100,
	KF_INTERRUPT_MASKED_DEBUG_STACKSHOT_OVRD  = 0x200,
	KF_SCHED_HYGIENE_DEBUG_PMC_OVRD           = 0x400,
	KF_MACH_ASSERT_OVRD                       = 0x800,
	KF_MADVISE_FREE_DEBUG_OVRD                = 0x1000,
	KF_DISABLE_FP_POPC_ON_PGFLT               = 0x2000,
	KF_DISABLE_PROD_TRC_VALIDATION            = 0x4000,
	KF_IO_TIMEOUT_OVRD                        = 0x8000,
	KF_PREEMPTION_DISABLED_DEBUG_OVRD         = 0x10000,
	/*
	 * Disable panics (with retaining backtraces) on leaked proc refs across syscall boundary.
	 */
	KF_DISABLE_PROCREF_TRACKING_OVRD          = 0x20000,
});

#define KF_SERVER_PERF_MODE_OVRD ( \
	KF_SERIAL_OVRD | \
	KF_PMAPV_OVRD | \
	KF_MATV_OVRD | \
	KF_COMPRSV_OVRD | \
	KF_INTERRUPT_MASKED_DEBUG_OVRD | \
	KF_TRAPTRACE_OVRD | \
	KF_IOTRACE_OVRD  | \
	KF_SCHED_HYGIENE_DEBUG_PMC_OVRD | \
	KF_MACH_ASSERT_OVRD | \
	KF_MADVISE_FREE_DEBUG_OVRD | \
	KF_DISABLE_PROD_TRC_VALIDATION | \
	0)

boolean_t kern_feature_override(kf_override_flag_t fmask);

__options_decl(eph_panic_flags_t, uint64_t, {
	EMBEDDED_PANIC_HEADER_FLAG_COREDUMP_COMPLETE              = 0x01,                               /* INFO: coredump completed */
	EMBEDDED_PANIC_HEADER_FLAG_STACKSHOT_SUCCEEDED            = 0x02,                               /* INFO: stackshot completed */
	EMBEDDED_PANIC_HEADER_FLAG_STACKSHOT_FAILED_DEBUGGERSYNC  = 0x04,                               /* ERROR: stackshot failed to sync with external debugger */
	EMBEDDED_PANIC_HEADER_FLAG_STACKSHOT_FAILED_ERROR         = 0x08,                               /* ERROR: stackshot failed */
	EMBEDDED_PANIC_HEADER_FLAG_STACKSHOT_FAILED_INCOMPLETE    = 0x10,                               /* ERROR: stackshot is partially complete */
	EMBEDDED_PANIC_HEADER_FLAG_STACKSHOT_FAILED_NESTED        = 0x20,                               /* ERROR: stackshot caused a nested panic */
	EMBEDDED_PANIC_HEADER_FLAG_NESTED_PANIC                   = 0x40,                               /* ERROR: panic handler encountered a panic */
	EMBEDDED_PANIC_HEADER_FLAG_BUTTON_RESET_PANIC             = 0x80,                               /* INFO: force-reset panic: user held power button to force shutdown */
	EMBEDDED_PANIC_HEADER_FLAG_COMPANION_PROC_INITIATED_PANIC = 0x100,                              /* INFO: panic was triggered by a companion processor (external to the SOC) */
	EMBEDDED_PANIC_HEADER_FLAG_COREDUMP_FAILED                = 0x200,                              /* ERROR: coredump failed to complete */
	EMBEDDED_PANIC_HEADER_FLAG_COMPRESS_FAILED                = 0x400,                              /* ERROR: stackshot failed to compress */
	EMBEDDED_PANIC_HEADER_FLAG_STACKSHOT_DATA_COMPRESSED      = 0x800,                              /* INFO: stackshot data is compressed */
	EMBEDDED_PANIC_HEADER_FLAG_ENCRYPTED_COREDUMP_SKIPPED     = 0x1000,                             /* ERROR: coredump policy requires encryption, but encryptions is not initialized or available */
	EMBEDDED_PANIC_HEADER_FLAG_KERNEL_COREDUMP_SKIPPED_EXCLUDE_REGIONS_UNAVAILABLE   = 0x2000,      /* ERROR: coredump region exclusion list is not available */
	EMBEDDED_PANIC_HEADER_FLAG_COREFILE_UNLINKED              = 0x4000,                             /* ERROR: coredump output file is not linked */
	EMBEDDED_PANIC_HEADER_FLAG_INCOHERENT_PANICLOG            = 0x8000,                             /* ERROR: paniclog integrity check failed (a warning to consumer code i.e. DumpPanic) */
	EMBEDDED_PANIC_HEADER_FLAG_EXCLAVE_PANIC                  = 0x10000,                            
	EMBEDDED_PANIC_HEADER_FLAG_USERSPACE_INITIATED_PANIC      = 0x20000,                            /* INFO: panic was initiated by userspace */
	EMBEDDED_PANIC_HEADER_FLAG_INTEGRATED_COPROC_INITIATED_PANIC = 0x40000,                         /* INFO: panic was initiated by an SOC-integrated coprocessor */
});

#define MAX_PANIC_INITIATOR_SIZE 256

#define EMBEDDED_PANIC_HEADER_CURRENT_VERSION 6
#define EMBEDDED_PANIC_MAGIC 0x46554E4B /* FUNK */
#define EMBEDDED_PANIC_HEADER_OSVERSION_LEN 32

/*
 * Any updates to this header should be also updated in astris as it can not
 * grab this header from the SDK.
 *
 * NOTE: DO NOT REMOVE OR CHANGE THE MEANING OF ANY FIELDS FROM THIS STRUCTURE.
 *       Any modifications should add new fields at the end, bump the version number
 *       and be done alongside astris and DumpPanic changes.
 */
struct embedded_panic_header {
	uint32_t eph_magic;                /* EMBEDDED_PANIC_MAGIC if valid */
	uint32_t eph_crc;                  /* CRC of everything following the ph_crc in the header and the contents */
	uint32_t eph_version;              /* embedded_panic_header version */
	eph_panic_flags_t eph_panic_flags; /* Flags indicating any state or relevant details */
	uint32_t eph_panic_log_offset;     /* Offset of the beginning of the panic log from the beginning of the header */
	uint32_t eph_panic_log_len;        /* length of the panic log */
	uint32_t eph_stackshot_offset;     /* Offset of the beginning of the panic stackshot from the beginning of the header */
	uint32_t eph_stackshot_len;        /* length of the panic stackshot (0 if not valid ) */
	uint32_t eph_other_log_offset;     /* Offset of the other log (any logging subsequent to the stackshot) from the beginning of the header */
	uint32_t eph_other_log_len;        /* length of the other log */
	union {
		struct {
			uint64_t eph_x86_power_state:8,
			    eph_x86_efi_boot_state:8,
			    eph_x86_system_state:8,
			    eph_x86_unused_bits:40;
		}; // anonymous struct to group the bitfields together.
		uint64_t eph_x86_do_not_use; /* Used for offsetof/sizeof when parsing header */
	} __attribute__((packed));
	char eph_os_version[EMBEDDED_PANIC_HEADER_OSVERSION_LEN];
	char eph_macos_version[EMBEDDED_PANIC_HEADER_OSVERSION_LEN];
	uuid_string_t eph_bootsessionuuid_string;                      /* boot session UUID */
	uint64_t eph_roots_installed;                                  /* bitmap indicating which roots are installed on this system */
	uint32_t eph_ext_paniclog_offset;
	uint32_t eph_ext_paniclog_len;
	uint32_t eph_panic_initiator_offset;
	uint32_t eph_panic_initiator_len;
} __attribute__((packed));


#define MACOS_PANIC_HEADER_CURRENT_VERSION 3
#define MACOS_PANIC_MAGIC 0x44454544 /* DEED */

__options_decl(mph_panic_flags_t, uint64_t, {
	MACOS_PANIC_HEADER_FLAG_NESTED_PANIC                   = 0x01,                                /* ERROR: panic handler encountered a panic */
	MACOS_PANIC_HEADER_FLAG_COMPANION_PROC_INITIATED_PANIC = 0x02,                                /* INFO: panic was triggered by a companion processor (external to the SOC) */
	MACOS_PANIC_HEADER_FLAG_STACKSHOT_SUCCEEDED            = 0x04,                                /* INFO: stackshot completed */
	MACOS_PANIC_HEADER_FLAG_STACKSHOT_DATA_COMPRESSED      = 0x08,                                /* INFO: stackshot data is compressed */
	MACOS_PANIC_HEADER_FLAG_STACKSHOT_FAILED_DEBUGGERSYNC  = 0x10,                                /* ERROR: stackshot failed to sync with external debugger */
	MACOS_PANIC_HEADER_FLAG_STACKSHOT_FAILED_ERROR         = 0x20,                                /* ERROR: stackshot failed */
	MACOS_PANIC_HEADER_FLAG_STACKSHOT_FAILED_INCOMPLETE    = 0x40,                                /* ERROR: stackshot is partially complete */
	MACOS_PANIC_HEADER_FLAG_STACKSHOT_FAILED_NESTED        = 0x80,                                /* ERROR: stackshot caused a nested panic */
	MACOS_PANIC_HEADER_FLAG_COREDUMP_COMPLETE              = 0x100,                               /* INFO: coredump completed */
	MACOS_PANIC_HEADER_FLAG_COREDUMP_FAILED                = 0x200,                               /* ERROR: coredump failed to complete */
	MACOS_PANIC_HEADER_FLAG_STACKSHOT_KERNEL_ONLY          = 0x400,                               /* ERROR: stackshot contains only kernel data (e.g. due to space limitations) */
	MACOS_PANIC_HEADER_FLAG_STACKSHOT_FAILED_COMPRESS      = 0x800,                               /* ERROR: stackshot failed to compress */
	MACOS_PANIC_HEADER_FLAG_ENCRYPTED_COREDUMP_SKIPPED     = 0x1000,                              /* ERROR: coredump policy requires encryption, but encryptions is not initialized or available */
	MACOS_PANIC_HEADER_FLAG_KERNEL_COREDUMP_SKIPPED_EXCLUDE_REGIONS_UNAVAILABLE     = 0x2000,     /* ERROR: coredump region exclusion list is not available */
	MACOS_PANIC_HEADER_FLAG_COREFILE_UNLINKED              = 0x4000,                              /* ERROR: coredump output file is not linked */
	MACOS_PANIC_HEADER_FLAG_INCOHERENT_PANICLOG            = 0x8000,                              /* ERROR: paniclog integrity check failed (a warning to consumer code i.e. DumpPanic) */
	MACOS_PANIC_HEADER_FLAG_USERSPACE_INITIATED_PANIC      = 0x10000,                             /* INFO: panic was initiated by userspace */
	MACOS_PANIC_HEADER_FLAG_INTEGRATED_COPROC_INITIATED_PANIC = 0x20000,                          /* INFO: panic was initiated by an SOC-integrated coprocessor */
});

struct macos_panic_header {
	uint32_t mph_magic;                   /* MACOS_PANIC_MAGIC if valid */
	uint32_t mph_crc;                     /* CRC of everything following mph_crc in the header and the contents */
	uint32_t mph_version;                 /* macos_panic_header version */
	uint32_t mph_padding;                 /* unused */
	mph_panic_flags_t mph_panic_flags;    /* Flags indicating any state or relevant details */
	uint32_t mph_panic_log_offset;        /* Offset of the panic log from the beginning of the header */
	uint32_t mph_panic_log_len;           /* length of the panic log */
	uint32_t mph_stackshot_offset;        /* Offset of the panic stackshot from the beginning of the header */
	uint32_t mph_stackshot_len;           /* length of the panic stackshot */
	uint32_t mph_other_log_offset;        /* Offset of the other log (any logging subsequent to the stackshot) from the beginning of the header */
	uint32_t mph_other_log_len;           /* length of the other log */
	uint64_t mph_roots_installed;         /* bitmap indicating which roots are installed on this system */
	char     mph_data[];                  /* panic data -- DO NOT ACCESS THIS FIELD DIRECTLY. Use the offsets above relative to the beginning of the header */
} __attribute__((packed));

/*
 * Any change to the below structure should mirror the structure defined in MacEFIFirmware
 * (and vice versa)
 */

struct efi_aurr_panic_header {
	uint32_t efi_aurr_magic;
	uint32_t efi_aurr_crc;
	uint32_t efi_aurr_version;
	uint32_t efi_aurr_reset_cause;
	uint32_t efi_aurr_reset_log_offset;
	uint32_t efi_aurr_reset_log_len;
	char efi_aurr_panic_data[];
} __attribute__((packed));

/*
 * EXTENDED_/DEBUG_BUF_SIZE can't grow without updates to SMC and iBoot to store larger panic logs on co-processor systems
 */
#define EXTENDED_DEBUG_BUF_SIZE 0x0013ff80

#define EFI_AURR_PANIC_STRING_MAX_LEN 112
#define EFI_AURR_EXTENDED_LOG_SIZE (EXTENDED_DEBUG_BUF_SIZE - sizeof(struct efi_aurr_panic_header) - EFI_AURR_PANIC_STRING_MAX_LEN)

struct efi_aurr_extended_panic_log {
	char efi_aurr_extended_log_buf[EFI_AURR_EXTENDED_LOG_SIZE];
	uint32_t efi_aurr_log_tail; /* Circular buffer indices */
	uint32_t efi_aurr_log_head; /* ditto.. */
} __attribute__((packed));

#endif /* __APPLE_API_UNSTABLE */
#endif /* __APPLE_API_PRIVATE */

/*
 * If non-zero, this physical address had an ECC error that led to a panic.
 */
extern uint64_t ecc_panic_physical_address;



__END_DECLS

#endif  /* _KERN_DEBUG_H_ */
