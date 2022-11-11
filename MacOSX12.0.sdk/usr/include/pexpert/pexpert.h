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
#ifndef _PEXPERT_PEXPERT_H_
#define _PEXPERT_PEXPERT_H_

#include <sys/cdefs.h>



__BEGIN_DECLS
#include <mach/boolean.h>
#include <mach/kern_return.h>
#include <mach/machine/vm_types.h>

#include <pexpert/boot.h>

typedef void *cpu_id_t;


extern void lpss_uart_enable(boolean_t on_off);

void PE_enter_debugger(
	const char *cause);

void PE_init_platform(
	boolean_t vm_initialized,
	void *args);

/*
 * Copies the requested number of bytes from the "random-seed" property in
 * the device tree, and zeros the corresponding bytes in the device tree.
 * Returns the number of bytes actually copied.
 */
uint32_t PE_get_random_seed(
	unsigned char * dst_random_seed,
	uint32_t request_size);

uint32_t PE_i_can_has_debugger(
	uint32_t *);

int PE_stub_poll_input(unsigned int options, char *c);

#if defined(__arm__) || defined(__arm64__)
boolean_t PE_panic_debugging_enabled(void);

void PE_mark_hwaccess(uint64_t thread);
#endif /* defined(__arm__) || defined(__arm64__) */

/* Return the offset of the specified address into the panic region */
uint32_t PE_get_offset_into_panic_region(
	char *location);

/* Zeroes the panic header, sets the panic magic and initializes the header to be used */
void PE_init_panicheader(
	void);

/* Updates the panic header during a nested panic */
void PE_update_panicheader_nestedpanic(
	void);

/* Invokes AppleARMIO::handlePlatformError() if present */
bool PE_handle_platform_error(
	vm_offset_t far);


extern int32_t gPESerialBaud;

extern uint8_t gPlatformECID[8];

extern uint32_t gPlatformMemoryID;

unsigned int PE_init_taproot(vm_offset_t *taddr);

extern void (*PE_kputc)(char c);

void PE_init_printf(
	boolean_t vm_initialized);

extern void (*PE_putc)(char c);

/*
 * Perform pre-lockdown IOKit initialization.
 * This is guaranteed to execute prior to machine_lockdown().
 * The precise operations performed by this function depend upon
 * the security model employed by the platform, but in general this
 * function should be expected to at least perform basic C++ runtime
 * and I/O registry initialization.
 */
void PE_init_iokit(
	void);

/*
 * Perform post-lockdown IOKit initialization.
 * This is guaranteed to execute after machine_lockdown().
 * The precise operations performed by this function depend upon
 * the security model employed by the platform.  For example, if
 * the platform treats machine_lockdown() as a strict security
 * checkpoint, general-purpose IOKit matching may not begin until
 * this function is called.
 */
void PE_lockdown_iokit(
	void);

struct clock_frequency_info_t {
	unsigned long bus_clock_rate_hz;
	unsigned long cpu_clock_rate_hz;
	unsigned long dec_clock_rate_hz;
	unsigned long bus_clock_rate_num;
	unsigned long bus_clock_rate_den;
	unsigned long bus_to_cpu_rate_num;
	unsigned long bus_to_cpu_rate_den;
	unsigned long bus_to_dec_rate_num;
	unsigned long bus_to_dec_rate_den;
	unsigned long timebase_frequency_hz;
	unsigned long timebase_frequency_num;
	unsigned long timebase_frequency_den;
	unsigned long long bus_frequency_hz;
	unsigned long long bus_frequency_min_hz;
	unsigned long long bus_frequency_max_hz;
	unsigned long long cpu_frequency_hz;
	unsigned long long cpu_frequency_min_hz;
	unsigned long long cpu_frequency_max_hz;
	unsigned long long prf_frequency_hz;
	unsigned long long prf_frequency_min_hz;
	unsigned long long prf_frequency_max_hz;
	unsigned long long mem_frequency_hz;
	unsigned long long mem_frequency_min_hz;
	unsigned long long mem_frequency_max_hz;
	unsigned long long fix_frequency_hz;
};

extern int debug_cpu_performance_degradation_factor;

typedef struct clock_frequency_info_t clock_frequency_info_t;

extern clock_frequency_info_t gPEClockFrequencyInfo;

struct timebase_freq_t {
	unsigned long timebase_num;
	unsigned long timebase_den;
};

typedef void (*timebase_callback_func)(struct timebase_freq_t *timebase_freq);

void PE_register_timebase_callback(timebase_callback_func callback);

void PE_call_timebase_callback(void);


extern bool disable_serial_output;
extern bool disable_kprintf_output;

#ifndef _FN_KPRINTF
#define _FN_KPRINTF
void kprintf(const char *fmt, ...) __printflike(1, 2);
#endif


#if CONFIG_NO_KPRINTF_STRINGS
#define kprintf(x, ...) do {} while (0)
#endif

void init_display_putc(unsigned char *baseaddr, int rowbytes, int height);
void display_putc(char c);

enum {
	kPEReadTOD,
	kPEWriteTOD
};

enum {
	kPEWaitForInput     = 0x00000001,
	kPERawInput         = 0x00000002
};

/* Private Stuff - eventually put in pexpertprivate.h */
enum {
	kDebugTypeNone    = 0,
	kDebugTypeDisplay = 1,
	kDebugTypeSerial  = 2
};

/*  Scale factor values for PE_Video.v_scale */
enum {
	kPEScaleFactorUnknown = 0,
	kPEScaleFactor1x      = 1,
	kPEScaleFactor2x      = 2
};

struct PE_Video {
	unsigned long   v_baseAddr;     /* Base address of video memory */
	unsigned long   v_rowBytes;     /* Number of bytes per pixel row */
	unsigned long   v_width;        /* Width */
	unsigned long   v_height;       /* Height */
	unsigned long   v_depth;        /* Pixel Depth */
	unsigned long   v_display;      /* Text or Graphics */
	char            v_pixelFormat[64];
	unsigned long   v_offset;       /* offset into video memory to start at */
	unsigned long   v_length;       /* length of video memory (0 for v_rowBytes * v_height) */
	unsigned char   v_rotate;       /* Rotation: 0:normal, 1:right 90, 2:left 180, 3:left 90 */
	unsigned char   v_scale;        /* Scale Factor for both X & Y */
	char            reserved1[2];
#ifdef __LP64__
	long            reserved2;
#else
	long            v_baseAddrHigh;
#endif
};

typedef struct PE_Video       PE_Video;

extern void initialize_screen(PE_Video *, unsigned int);

extern void dim_screen(void);

extern int PE_current_console(
	PE_Video *info);

extern void PE_create_console(
	void);

extern int PE_initialize_console(
	PE_Video *newInfo,
	int op);

#define kPEGraphicsMode         1
#define kPETextMode             2
#define kPETextScreen           3
#define kPEAcquireScreen        4
#define kPEReleaseScreen        5
#define kPEEnableScreen         6
#define kPEDisableScreen        7
#define kPEBaseAddressChange    8
#define kPERefreshBootGraphics  9

extern void PE_display_icon( unsigned int flags,
    const char * name );

typedef struct PE_state {
	boolean_t       initialized;
	PE_Video        video;
	void            *deviceTreeHead;
	void            *bootArgs;
	vm_size_t       deviceTreeSize;
} PE_state_t;

extern PE_state_t PE_state;

extern char * PE_boot_args(
	void);

extern boolean_t PE_parse_boot_argn(
	const char      *arg_string,
	void            *arg_ptr,
	int                     max_arg);


extern boolean_t PE_get_default(
	const char      *property_name,
	void            *property_ptr,
	unsigned int max_property);

#define PE_default_value(_key, _variable, _default)     \
	do {                                                                                                                      \
	        if (!PE_get_default((_key), &(_variable), sizeof(_variable))) \
	                _variable = _default;                                                                     \
	} while(0)

enum {
	kPEOptionKey        = 0x3a,
	kPECommandKey       = 0x37,
	kPEControlKey       = 0x36,
	kPEShiftKey         = 0x38
};

extern boolean_t PE_get_hotkey(
	unsigned char   key);

extern kern_return_t PE_cpu_start(
	cpu_id_t target,
	vm_offset_t start_paddr,
	vm_offset_t arg_paddr);

extern void PE_cpu_halt(
	cpu_id_t target);

extern bool PE_cpu_down(
	cpu_id_t target);

extern void PE_cpu_signal(
	cpu_id_t source,
	cpu_id_t target);

extern void PE_cpu_signal_deferred(
	cpu_id_t source,
	cpu_id_t target);

extern void PE_cpu_signal_cancel(
	cpu_id_t source,
	cpu_id_t target);

extern void PE_cpu_machine_init(
	cpu_id_t target,
	boolean_t bootb);

extern void PE_cpu_machine_quiesce(
	cpu_id_t target);

extern void pe_init_debug(void);

extern boolean_t PE_imgsrc_mount_supported(void);

extern void PE_panic_hook(const char *str);

extern void PE_init_cpu(void);

extern void PE_handle_ext_interrupt(void);

#if defined(__arm__) || defined(__arm64__)
typedef void (*perfmon_interrupt_handler_func)(cpu_id_t source);
extern kern_return_t PE_cpu_perfmon_interrupt_install_handler(perfmon_interrupt_handler_func handler);
extern void PE_cpu_perfmon_interrupt_enable(cpu_id_t target, boolean_t enable);

#if DEVELOPMENT || DEBUG
/* panic_trace boot-arg modes */
typedef enum {
	panic_trace_disabled = 0,       /* Tracing disabled (default) */
	panic_trace_unused,             /* Unused for backward compatibility */
	panic_trace_enabled,            /* Tracing enabled to SRAM */
	panic_trace_alt_enabled,        /* Tracing enabled to L2 */
#ifdef CPU_HAS_TRACE_TO_DRAM
	panic_trace_dram_enabled,       /* Tracing enabled to DRAM */
#endif /* CPU_HAS_TRACE_TO_DRAM */
} panic_trace_t;
extern panic_trace_t panic_trace;

extern void PE_arm_debug_enable_trace(void);
extern void (*PE_arm_debug_panic_hook)(const char *str);
#else
extern void(*const PE_arm_debug_panic_hook)(const char *str);
#endif
#endif


typedef enum kc_kind {
	KCKindNone      = -1,
	KCKindUnknown   = 0,
	KCKindPrimary   = 1,
	KCKindPageable  = 2,
	KCKindAuxiliary = 3,
	KCNumKinds      = 4,
} kc_kind_t;

typedef enum kc_format {
	KCFormatUnknown = 0,
	KCFormatStatic  = 1,
	KCFormatDynamic = 2,
	KCFormatFileset = 3,
	KCFormatKCGEN   = 4,
} kc_format_t;

/* returns a pointer to the mach-o header for a give KC type, returns NULL if nothing's been set */
extern void *PE_get_kc_header(kc_kind_t type);
/* returns a pointer to the lowest VA of of the KC of the given type */
extern void *PE_get_kc_baseaddress(kc_kind_t type);
/* returns an array of length KCNumKinds of the lowest VAs of each KC type - members could be NULL */
extern const void * const*PE_get_kc_base_pointers(void);
/* returns the slide for the kext collection */
extern uintptr_t PE_get_kc_slide(kc_kind_t type);
/* quickly accesss the format of the primary kc */
extern bool PE_get_primary_kc_format(kc_format_t *type);
/* set vnode ptr for kc fileset */
extern void PE_set_kc_vp(kc_kind_t type, void *vp);
/* quickly set vnode ptr for kc fileset */
void * PE_get_kc_vp(kc_kind_t type);
/* drop reference to kc fileset vnodes */
void PE_reset_all_kc_vp(void);


extern vm_size_t PE_init_socd_client(void);
extern void PE_write_socd_client_buffer(vm_offset_t offset, const void *buff, vm_size_t size);

__END_DECLS

#endif /* _PEXPERT_PEXPERT_H_ */
