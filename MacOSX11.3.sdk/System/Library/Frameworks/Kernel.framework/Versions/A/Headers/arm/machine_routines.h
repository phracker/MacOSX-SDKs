/*
 * Copyright (c) 2007-2020 Apple Inc. All rights reserved.
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
/*
 * @OSF_COPYRIGHT@
 */

#ifndef _ARM_MACHINE_ROUTINES_H_
#define _ARM_MACHINE_ROUTINES_H_

#include <mach/mach_types.h>
#include <mach/vm_types.h>
#include <mach/boolean.h>
#include <kern/kern_types.h>
#include <pexpert/pexpert.h>

#include <sys/cdefs.h>
#include <sys/appleapiopts.h>

#include <stdarg.h>

__BEGIN_DECLS


/* Interrupt handling */

void ml_cpu_signal(unsigned int cpu_id);
void ml_cpu_signal_deferred_adjust_timer(uint64_t nanosecs);
uint64_t ml_cpu_signal_deferred_get_timer(void);
void ml_cpu_signal_deferred(unsigned int cpu_id);
void ml_cpu_signal_retract(unsigned int cpu_id);
bool ml_cpu_signal_is_enabled(void);

/* Initialize Interrupts */
void    ml_init_interrupt(void);

/* Get Interrupts Enabled */
boolean_t ml_get_interrupts_enabled(void);

/* Set Interrupts Enabled */
boolean_t ml_set_interrupts_enabled(boolean_t enable);
boolean_t ml_early_set_interrupts_enabled(boolean_t enable);

/* Check if running at interrupt context */
boolean_t ml_at_interrupt_context(void);

/* Generate a fake interrupt */
void ml_cause_interrupt(void);

/* Clear interrupt spin debug state for thread */
#if INTERRUPT_MASKED_DEBUG
extern boolean_t interrupt_masked_debug;
extern uint64_t interrupt_masked_timeout;
extern uint64_t stackshot_interrupt_masked_timeout;

#define INTERRUPT_MASKED_DEBUG_START(handler_addr, type)                                    \
do {                                                                                        \
    if (interrupt_masked_debug) {                                                           \
	    thread_t thread = current_thread();                                                 \
	    thread->machine.int_type = type;                                                    \
	    thread->machine.int_handler_addr = (uintptr_t)VM_KERNEL_STRIP_PTR(handler_addr);    \
	    thread->machine.inthandler_timestamp = ml_get_timebase();                           \
	    thread->machine.int_vector = (uintptr_t)NULL;                                       \
    }                                                                                       \
} while (0)

#define INTERRUPT_MASKED_DEBUG_END()                                                        \
do {                                                                                        \
	if (interrupt_masked_debug) {                                                           \
	    thread_t thread = current_thread();                                                 \
	    ml_check_interrupt_handler_duration(thread);                                        \
	}                                                                                       \
} while (0)

void ml_irq_debug_start(uintptr_t handler, uintptr_t vector);
void ml_irq_debug_end(void);

void ml_spin_debug_reset(thread_t thread);
void ml_spin_debug_clear(thread_t thread);
void ml_spin_debug_clear_self(void);
void ml_check_interrupts_disabled_duration(thread_t thread);
void ml_check_stackshot_interrupt_disabled_duration(thread_t thread);
void ml_check_interrupt_handler_duration(thread_t thread);
#else
#define INTERRUPT_MASKED_DEBUG_START(handler_addr, type)
#define INTERRUPT_MASKED_DEBUG_END()
#endif


/* Type for the Time Base Enable function */
typedef void (*time_base_enable_t)(cpu_id_t cpu_id, boolean_t enable);

#define CacheConfig                     0x00000000UL
#define CacheControl                    0x00000001UL
#define CacheClean                      0x00000002UL
#define CacheCleanRegion                0x00000003UL
#define CacheCleanFlush                 0x00000004UL
#define CacheCleanFlushRegion           0x00000005UL
#define CacheShutdown                   0x00000006UL

#define CacheControlEnable              0x00000000UL

#define CacheConfigCCSIDR               0x00000001UL
#define CacheConfigSize                 0x00000100UL

/* Type for the Processor Idle function */
typedef void (*processor_idle_t)(cpu_id_t cpu_id, boolean_t enter, uint64_t *new_timeout_ticks);

/* Type for the Idle Tickle function */
typedef void (*idle_tickle_t)(void);

/* Type for the Idle Timer function */
typedef void (*idle_timer_t)(void *refcon, uint64_t *new_timeout_ticks);

/* Type for the IPI Hander */
typedef void (*ipi_handler_t)(void);

/* Type for the Lockdown Hander */
typedef void (*lockdown_handler_t)(void *);

/* Type for the Platform specific Error Handler */
typedef void (*platform_error_handler_t)(void *refcon, vm_offset_t fault_addr);

/*
 * The exception callback (ex_cb) module allows kernel drivers to
 * register and receive callbacks for exceptions, and indicate
 * actions to be taken by the platform kernel
 * Currently this is supported for ARM64 but extending support for ARM32
 * should be straightforward
 */

/* Supported exception classes for callbacks */
typedef enum{
	EXCB_CLASS_ILLEGAL_INSTR_SET,
#ifdef CONFIG_XNUPOST
	EXCB_CLASS_TEST1,
	EXCB_CLASS_TEST2,
	EXCB_CLASS_TEST3,
#endif
	EXCB_CLASS_MAX          // this must be last
}
ex_cb_class_t;

/* Actions indicated by callbacks to be taken by platform kernel */
typedef enum{
	EXCB_ACTION_RERUN,      // re-run the faulting instruction
	EXCB_ACTION_NONE,       // continue normal exception handling
#ifdef CONFIG_XNUPOST
	EXCB_ACTION_TEST_FAIL,
#endif
}
ex_cb_action_t;

/*
 * Exception state
 * We cannot use a private kernel data structure such as arm_saved_state_t
 * The CPSR and ESR are not clobbered when the callback function is invoked so
 * those registers can be examined by the callback function;
 * the same is done in the platform error handlers
 */
typedef struct{
	vm_offset_t far;
}
ex_cb_state_t;

/* callback type definition */
typedef ex_cb_action_t (*ex_cb_t) (
	ex_cb_class_t           cb_class,
	void                            *refcon,// provided at registration
	const ex_cb_state_t     *state  // exception state
	);

/*
 * Callback registration
 * Currently we support only one registered callback per class but
 * it should be possible to support more callbacks
 */
kern_return_t ex_cb_register(
	ex_cb_class_t   cb_class,
	ex_cb_t                 cb,
	void                    *refcon );

/*
 * Called internally by platform kernel to invoke the registered callback for class
 */
ex_cb_action_t ex_cb_invoke(
	ex_cb_class_t   cb_class,
	vm_offset_t         far);


void ml_parse_cpu_topology(void);

unsigned int ml_get_cpu_count(void);

unsigned int ml_get_cluster_count(void);

int ml_get_boot_cpu_number(void);

int ml_get_cpu_number(uint32_t phys_id);

int ml_get_cluster_number(uint32_t phys_id);

int ml_get_max_cpu_number(void);

int ml_get_max_cluster_number(void);

unsigned int ml_get_first_cpu_id(unsigned int cluster_id);

#ifdef __arm64__
int ml_get_cluster_number_local(void);
unsigned int ml_get_cpu_number_local(void);
#endif /* __arm64__ */

/* Struct for ml_cpu_get_info */
struct ml_cpu_info {
	unsigned long           vector_unit;
	unsigned long           cache_line_size;
	unsigned long           l1_icache_size;
	unsigned long           l1_dcache_size;
	unsigned long           l2_settings;
	unsigned long           l2_cache_size;
	unsigned long           l3_settings;
	unsigned long           l3_cache_size;
};
typedef struct ml_cpu_info ml_cpu_info_t;

typedef enum {
	CLUSTER_TYPE_SMP,
	CLUSTER_TYPE_E,
	CLUSTER_TYPE_P,
} cluster_type_t;

cluster_type_t ml_get_boot_cluster(void);

/*!
 * @typedef ml_topology_cpu_t
 * @brief Describes one CPU core in the topology.
 *
 * @field cpu_id            Logical CPU ID (EDT: cpu-id): 0, 1, 2, 3, 4, ...
 * @field phys_id           Physical CPU ID (EDT: reg).  Same as MPIDR[15:0], i.e.
 *                          (cluster_id << 8) | core_number_within_cluster
 * @field cluster_id        Cluster ID (EDT: cluster-id)
 * @field die_id            Die ID (EDT: die-id)
 * @field cluster_type      The type of CPUs found in this cluster.
 * @field l2_access_penalty Indicates that the scheduler should try to de-prioritize a core because
 *                          L2 accesses are slower than on the boot processor.
 * @field l2_cache_size     Size of the L2 cache, in bytes.  0 if unknown or not present.
 * @field l2_cache_id       l2-cache-id property read from EDT.
 * @field l3_cache_size     Size of the L3 cache, in bytes.  0 if unknown or not present.
 * @field l3_cache_id       l3-cache-id property read from EDT.
 * @field cpu_IMPL_regs     IO-mapped virtual address of cpuX_IMPL (implementation-defined) register block.
 * @field cpu_IMPL_pa       Physical address of cpuX_IMPL register block.
 * @field cpu_IMPL_len      Length of cpuX_IMPL register block.
 * @field cpu_UTTDBG_regs   IO-mapped virtual address of cpuX_UTTDBG register block.
 * @field cpu_UTTDBG_pa     Physical address of cpuX_UTTDBG register block, if set in DT, else zero
 * @field cpu_UTTDBG_len    Length of cpuX_UTTDBG register block, if set in DT, else zero
 * @field coresight_regs    IO-mapped virtual address of CoreSight debug register block.
 * @field coresight_pa      Physical address of CoreSight register block.
 * @field coresight_len     Length of CoreSight register block.
 * @field die_cluster_id    Cluster ID within the local die (EDT: die-cluster-id)
 * @field cluster_core_id   Core ID within the local cluster (EDT: cluster-core-id)
 */
typedef struct ml_topology_cpu {
	unsigned int                    cpu_id;
	uint32_t                        phys_id;
	unsigned int                    cluster_id;
	unsigned int                    die_id;
	cluster_type_t                  cluster_type;
	uint32_t                        l2_access_penalty;
	uint32_t                        l2_cache_size;
	uint32_t                        l2_cache_id;
	uint32_t                        l3_cache_size;
	uint32_t                        l3_cache_id;
	vm_offset_t                     cpu_IMPL_regs;
	uint64_t                        cpu_IMPL_pa;
	uint64_t                        cpu_IMPL_len;
	vm_offset_t                     cpu_UTTDBG_regs;
	uint64_t                        cpu_UTTDBG_pa;
	uint64_t                        cpu_UTTDBG_len;
	vm_offset_t                     coresight_regs;
	uint64_t                        coresight_pa;
	uint64_t                        coresight_len;
	unsigned int                    die_cluster_id;
	unsigned int                    cluster_core_id;
} ml_topology_cpu_t;

/*!
 * @typedef ml_topology_cluster_t
 * @brief Describes one cluster in the topology.
 *
 * @field cluster_id        Cluster ID (EDT: cluster-id)
 * @field cluster_type      The type of CPUs found in this cluster.
 * @field num_cpus          Total number of usable CPU cores in this cluster.
 * @field first_cpu_id      The cpu_id of the first CPU in the cluster.
 * @field cpu_mask          A bitmask representing the cpu_id's that belong to the cluster.  Example:
 *                          If the cluster contains CPU4 and CPU5, cpu_mask will be 0x30.
 * @field acc_IMPL_regs     IO-mapped virtual address of acc_IMPL (implementation-defined) register block.
 * @field acc_IMPL_pa       Physical address of acc_IMPL register block.
 * @field acc_IMPL_len      Length of acc_IMPL register block.
 * @field cpm_IMPL_regs     IO-mapped virtual address of cpm_IMPL (implementation-defined) register block.
 * @field cpm_IMPL_pa       Physical address of cpm_IMPL register block.
 * @field cpm_IMPL_len      Length of cpm_IMPL register block.
 */
typedef struct ml_topology_cluster {
	unsigned int                    cluster_id;
	cluster_type_t                  cluster_type;
	unsigned int                    num_cpus;
	unsigned int                    first_cpu_id;
	uint64_t                        cpu_mask;
	vm_offset_t                     acc_IMPL_regs;
	uint64_t                        acc_IMPL_pa;
	uint64_t                        acc_IMPL_len;
	vm_offset_t                     cpm_IMPL_regs;
	uint64_t                        cpm_IMPL_pa;
	uint64_t                        cpm_IMPL_len;
} ml_topology_cluster_t;

// Bump this version number any time any ml_topology_* struct changes, so
// that KPI users can check whether their headers are compatible with
// the running kernel.
#define CPU_TOPOLOGY_VERSION 1

/*!
 * @typedef ml_topology_info_t
 * @brief Describes the CPU topology for all APs in the system.  Populated from EDT and read-only at runtime.
 * @discussion This struct only lists CPU cores that are considered usable by both iBoot and XNU.  Some
 *             physically present CPU cores may be considered unusable due to configuration options like
 *             the "cpus=" boot-arg.  Cores that are disabled in hardware will not show up in EDT at all, so
 *             they also will not be present in this struct.
 *
 * @field version           Version of the struct (set to CPU_TOPOLOGY_VERSION).
 * @field num_cpus          Total number of usable CPU cores.
 * @field max_cpu_id        The highest usable logical CPU ID.
 * @field num_clusters      Total number of AP CPU clusters on the system (usable or not).
 * @field max_cluster_id    The highest cluster ID found in EDT.
 * @field cpus              List of |num_cpus| entries.
 * @field clusters          List of |num_clusters| entries.
 * @field boot_cpu          Points to the |cpus| entry for the boot CPU.
 * @field boot_cluster      Points to the |clusters| entry which contains the boot CPU.
 * @field chip_revision     Silicon revision reported by iBoot, which comes from the
 *                          SoC-specific fuse bits.  See CPU_VERSION_xx macros for definitions.
 */
typedef struct ml_topology_info {
	unsigned int                    version;
	unsigned int                    num_cpus;
	unsigned int                    max_cpu_id;
	unsigned int                    num_clusters;
	unsigned int                    max_cluster_id;
	unsigned int                    max_die_id;
	ml_topology_cpu_t               *cpus;
	ml_topology_cluster_t           *clusters;
	ml_topology_cpu_t               *boot_cpu;
	ml_topology_cluster_t           *boot_cluster;
	unsigned int                    chip_revision;
} ml_topology_info_t;

/*!
 * @function ml_get_topology_info
 * @result A pointer to the read-only topology struct.  Does not need to be freed.  Returns NULL
 *         if the struct hasn't been initialized or the feature is unsupported.
 */
const ml_topology_info_t *ml_get_topology_info(void);

/*!
 * @function ml_map_cpu_pio
 * @brief Maps per-CPU and per-cluster PIO registers found in EDT.  This needs to be
 *        called after arm_vm_init() so it can't be part of ml_parse_cpu_topology().
 */
void ml_map_cpu_pio(void);

/* Struct for ml_processor_register */
struct ml_processor_info {
	cpu_id_t                        cpu_id;
	vm_offset_t                     start_paddr;
	boolean_t                       supports_nap;
	void                            *platform_cache_dispatch;
	time_base_enable_t              time_base_enable;
	processor_idle_t                processor_idle;
	idle_tickle_t                   *idle_tickle;
	idle_timer_t                    idle_timer;
	void                            *idle_timer_refcon;
	vm_offset_t                     powergate_stub_addr;
	uint32_t                        powergate_stub_length;
	uint32_t                        powergate_latency;
	platform_error_handler_t        platform_error_handler;
	uint64_t                        regmap_paddr;
	uint32_t                        phys_id;
	uint32_t                        log_id;
	uint32_t                        l2_access_penalty;
	uint32_t                        cluster_id;
	cluster_type_t                  cluster_type;
	uint32_t                        l2_cache_id;
	uint32_t                        l2_cache_size;
	uint32_t                        l3_cache_id;
	uint32_t                        l3_cache_size;
};
typedef struct ml_processor_info ml_processor_info_t;


/*!
 * @function ml_processor_register
 *
 * @abstract callback from platform kext to register processor
 *
 * @discussion This function is called by the platform kext when a processor is
 * being registered.  This is called while running on the CPU itself, as part of
 * its initialization.
 *
 * @param ml_processor_info provides machine-specific information about the
 * processor to xnu.
 *
 * @param processor is set as an out-parameter to an opaque handle that should
 * be used by the platform kext when referring to this processor in the future.
 *
 * @param ipi_handler is set as an out-parameter to the function that should be
 * registered as the IPI handler.
 *
 * @param pmi_handler is set as an out-parameter to the function that should be
 * registered as the PMI handler.
 *
 * @returns KERN_SUCCESS on success and an error code, otherwise.
 */
kern_return_t ml_processor_register(ml_processor_info_t *ml_processor_info,
    processor_t *processor, ipi_handler_t *ipi_handler,
    perfmon_interrupt_handler_func *pmi_handler);

/* Register a lockdown handler */
kern_return_t ml_lockdown_handler_register(lockdown_handler_t, void *);


/* Initialize Interrupts */
void ml_install_interrupt_handler(
	void *nub,
	int source,
	void *target,
	IOInterruptHandler handler,
	void *refCon);

vm_offset_t
    ml_static_vtop(
	vm_offset_t);

kern_return_t
ml_static_verify_page_protections(
	uint64_t base, uint64_t size, vm_prot_t prot);

vm_offset_t
    ml_static_ptovirt(
	vm_offset_t);

vm_offset_t ml_static_slide(
	vm_offset_t vaddr);

vm_offset_t ml_static_unslide(
	vm_offset_t vaddr);

/* Offset required to obtain absolute time value from tick counter */
uint64_t ml_get_abstime_offset(void);

/* Offset required to obtain continuous time value from tick counter */
uint64_t ml_get_conttime_offset(void);

#ifdef __APPLE_API_UNSTABLE
/* PCI config cycle probing */
boolean_t ml_probe_read(
	vm_offset_t paddr,
	unsigned int *val);
boolean_t ml_probe_read_64(
	addr64_t paddr,
	unsigned int *val);

/* Read physical address byte */
unsigned int ml_phys_read_byte(
	vm_offset_t paddr);
unsigned int ml_phys_read_byte_64(
	addr64_t paddr);

/* Read physical address half word */
unsigned int ml_phys_read_half(
	vm_offset_t paddr);
unsigned int ml_phys_read_half_64(
	addr64_t paddr);

/* Read physical address word*/
unsigned int ml_phys_read(
	vm_offset_t paddr);
unsigned int ml_phys_read_64(
	addr64_t paddr);
unsigned int ml_phys_read_word(
	vm_offset_t paddr);
unsigned int ml_phys_read_word_64(
	addr64_t paddr);

unsigned long long ml_io_read(uintptr_t iovaddr, int iovsz);
unsigned int ml_io_read8(uintptr_t iovaddr);
unsigned int ml_io_read16(uintptr_t iovaddr);
unsigned int ml_io_read32(uintptr_t iovaddr);
unsigned long long ml_io_read64(uintptr_t iovaddr);

extern void ml_io_write(uintptr_t vaddr, uint64_t val, int size);
extern void ml_io_write8(uintptr_t vaddr, uint8_t val);
extern void ml_io_write16(uintptr_t vaddr, uint16_t val);
extern void ml_io_write32(uintptr_t vaddr, uint32_t val);
extern void ml_io_write64(uintptr_t vaddr, uint64_t val);

/* Read physical address double word */
unsigned long long ml_phys_read_double(
	vm_offset_t paddr);
unsigned long long ml_phys_read_double_64(
	addr64_t paddr);

/* Write physical address byte */
void ml_phys_write_byte(
	vm_offset_t paddr, unsigned int data);
void ml_phys_write_byte_64(
	addr64_t paddr, unsigned int data);

/* Write physical address half word */
void ml_phys_write_half(
	vm_offset_t paddr, unsigned int data);
void ml_phys_write_half_64(
	addr64_t paddr, unsigned int data);

/* Write physical address word */
void ml_phys_write(
	vm_offset_t paddr, unsigned int data);
void ml_phys_write_64(
	addr64_t paddr, unsigned int data);
void ml_phys_write_word(
	vm_offset_t paddr, unsigned int data);
void ml_phys_write_word_64(
	addr64_t paddr, unsigned int data);

/* Write physical address double word */
void ml_phys_write_double(
	vm_offset_t paddr, unsigned long long data);
void ml_phys_write_double_64(
	addr64_t paddr, unsigned long long data);

void ml_static_mfree(
	vm_offset_t,
	vm_size_t);

kern_return_t
ml_static_protect(
	vm_offset_t start,
	vm_size_t size,
	vm_prot_t new_prot);

/* virtual to physical on wired pages */
vm_offset_t ml_vtophys(
	vm_offset_t vaddr);

/* Get processor cache info */
void ml_cpu_get_info(ml_cpu_info_t *ml_cpu_info);

#endif /* __APPLE_API_UNSTABLE */

#ifdef __APPLE_API_PRIVATE

/* Zero bytes starting at a physical address */
void bzero_phys(
	addr64_t phys_address,
	vm_size_t length);

void bzero_phys_nc(addr64_t src64, vm_size_t bytes);


void ml_thread_policy(
	thread_t thread,
	unsigned policy_id,
	unsigned policy_info);

#define MACHINE_GROUP                                   0x00000001
#define MACHINE_NETWORK_GROUP                   0x10000000
#define MACHINE_NETWORK_WORKLOOP                0x00000001
#define MACHINE_NETWORK_NETISR                  0x00000002

/* Set the maximum number of CPUs */
void ml_set_max_cpus(
	unsigned int max_cpus);

/* Return the maximum number of CPUs set by ml_set_max_cpus(), waiting if necessary */
unsigned int ml_wait_max_cpus(
	void);

/* Return the maximum memory size */
unsigned int ml_get_machine_mem(void);


extern void     ml_cpu_init_completed(void);
extern void     ml_cpu_up(void);
extern void     ml_cpu_down(void);
extern void     ml_arm_sleep(void);

extern uint64_t ml_get_wake_timebase(void);
extern uint64_t ml_get_conttime_wake_time(void);

/* Time since the system was reset (as part of boot/wake) */
uint64_t ml_get_time_since_reset(void);

/*
 * Called by ApplePMGR to set wake time.  Units and epoch are identical
 * to mach_continuous_time().  Has no effect on !HAS_CONTINUOUS_HWCLOCK
 * chips.  If wake_time == UINT64_MAX, that means the wake time is
 * unknown and calls to ml_get_time_since_reset() will return UINT64_MAX.
 */
void ml_set_reset_time(uint64_t wake_time);


/* Bytes available on current stack */
vm_offset_t ml_stack_remaining(void);


extern  uint32_t        arm_debug_read_dscr(void);

extern int      set_be_bit(void);
extern int      clr_be_bit(void);
extern int      be_tracing(void);

/* Please note that cpu_broadcast_xcall is not as simple is you would like it to be.
 * It will sometimes put the calling thread to sleep, and it is up to your callback
 * to wake it up as needed, where "as needed" is defined as "all other CPUs have
 * called the broadcast func". Look around the kernel for examples, or instead use
 * cpu_broadcast_xcall_simple() which does indeed act like you would expect, given
 * the prototype. cpu_broadcast_immediate_xcall has the same caveats and has a similar
 * _simple() wrapper
 */
typedef void (*broadcastFunc) (void *);
unsigned int cpu_broadcast_xcall(uint32_t *, boolean_t, broadcastFunc, void *);
unsigned int cpu_broadcast_xcall_simple(boolean_t, broadcastFunc, void *);
kern_return_t cpu_xcall(int, broadcastFunc, void *);
unsigned int cpu_broadcast_immediate_xcall(uint32_t *, boolean_t, broadcastFunc, void *);
unsigned int cpu_broadcast_immediate_xcall_simple(boolean_t, broadcastFunc, void *);
kern_return_t cpu_immediate_xcall(int, broadcastFunc, void *);


boolean_t machine_timeout_suspended(void);
void ml_get_power_state(boolean_t *, boolean_t *);

uint32_t get_arm_cpu_version(void);
boolean_t user_cont_hwclock_allowed(void);
uint8_t user_timebase_type(void);
boolean_t ml_thread_is64bit(thread_t thread);

#ifdef __arm64__
bool ml_feature_supported(uint32_t feature_bit);
void ml_set_align_checking(void);
extern void wfe_timeout_configure(void);
extern void wfe_timeout_init(void);
#endif /* __arm64__ */

void ml_timer_evaluate(void);
boolean_t ml_timer_forced_evaluation(void);
uint64_t ml_energy_stat(thread_t);
void ml_gpu_stat_update(uint64_t);
uint64_t ml_gpu_stat(thread_t);
#endif /* __APPLE_API_PRIVATE */





void ml_hibernate_active_pre(void);
void ml_hibernate_active_post(void);

__END_DECLS

#endif /* _ARM_MACHINE_ROUTINES_H_ */
