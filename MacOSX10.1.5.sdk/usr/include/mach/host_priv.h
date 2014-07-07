#ifndef	_host_priv_user_
#define	_host_priv_user_

/* Module host_priv */

#include <string.h>
#include <mach/ndr.h>
#include <mach/boolean.h>
#include <mach/kern_return.h>
#include <mach/notify.h>
#include <mach/mach_types.h>
#include <mach/message.h>
#include <mach/mig_errors.h>
#include <mach/port.h>

#ifdef AUTOTEST
#ifndef FUNCTION_PTR_T
#define FUNCTION_PTR_T
typedef void (*function_ptr_t)(mach_port_t, char *, mach_msg_type_number_t);
typedef struct {
        char            *name;
        function_ptr_t  function;
} function_table_entry;
typedef function_table_entry 	*function_table_t;
#endif /* FUNCTION_PTR_T */
#endif /* AUTOTEST */

#ifndef	host_priv_MSG_COUNT
#define	host_priv_MSG_COUNT	25
#endif	/* host_priv_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mach_types.h>
#include <mach/mach_types.h>
#include <mach_debug/mach_debug_types.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */


/* Routine host_get_boot_info */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t host_get_boot_info
(
	host_priv_t host_priv,
	kernel_boot_info_t boot_info
);

/* Routine host_reboot */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t host_reboot
(
	host_priv_t host_priv,
	int options
);

/* Routine host_priv_statistics */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t host_priv_statistics
(
	host_priv_t host_priv,
	host_flavor_t flavor,
	host_info_t host_info_out,
	mach_msg_type_number_t *host_info_outCnt
);

/* Routine host_default_memory_manager */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t host_default_memory_manager
(
	host_priv_t host_priv,
	memory_object_default_t *default_manager,
	vm_size_t cluster_size
);

/* Routine vm_wire */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_wire
(
	host_priv_t host_priv,
	vm_map_t task,
	vm_address_t address,
	vm_size_t size,
	vm_prot_t access
);

/* Routine thread_wire */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t thread_wire
(
	host_priv_t host_priv,
	thread_act_t thread,
	boolean_t wired
);

/* Routine vm_allocate_cpm */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_allocate_cpm
(
	host_priv_t host_priv,
	vm_map_t task,
	vm_address_t *address,
	vm_size_t size,
	boolean_t anywhere
);

/* Routine host_processors */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t host_processors
(
	host_priv_t host_priv,
	processor_array_t *processor_list,
	mach_msg_type_number_t *processor_listCnt
);

/* Routine host_get_clock_control */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t host_get_clock_control
(
	host_priv_t host_priv,
	clock_id_t clock_id,
	clock_ctrl_t *clock_ctrl
);

/* Routine kmod_create */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t kmod_create
(
	host_priv_t host_priv,
	vm_address_t info,
	kmod_t *module
);

/* Routine kmod_destroy */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t kmod_destroy
(
	host_priv_t host_priv,
	kmod_t module
);

/* Routine kmod_control */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t kmod_control
(
	host_priv_t host_priv,
	kmod_t module,
	kmod_control_flavor_t flavor,
	kmod_args_t *data,
	mach_msg_type_number_t *dataCnt
);

/* Routine host_get_special_port */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t host_get_special_port
(
	host_priv_t host_priv,
	int node,
	int which,
	mach_port_t *port
);

/* Routine host_set_special_port */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t host_set_special_port
(
	host_priv_t host_priv,
	int which,
	mach_port_t port
);

/* Routine host_set_exception_ports */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t host_set_exception_ports
(
	host_priv_t host_priv,
	exception_mask_t exception_mask,
	mach_port_t new_port,
	exception_behavior_t behavior,
	thread_state_flavor_t new_flavor
);

/* Routine host_get_exception_ports */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t host_get_exception_ports
(
	host_priv_t host_priv,
	exception_mask_t exception_mask,
	exception_mask_array_t masks,
	mach_msg_type_number_t *masksCnt,
	exception_handler_array_t old_handlers,
	exception_behavior_array_t old_behaviors,
	exception_flavor_array_t old_flavors
);

/* Routine host_swap_exception_ports */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t host_swap_exception_ports
(
	host_priv_t host_priv,
	exception_mask_t exception_mask,
	mach_port_t new_port,
	exception_behavior_t behavior,
	thread_state_flavor_t new_flavor,
	exception_mask_array_t masks,
	mach_msg_type_number_t *masksCnt,
	exception_handler_array_t old_handlerss,
	exception_behavior_array_t old_behaviors,
	exception_flavor_array_t old_flavors
);

/* Routine host_load_symbol_table */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t host_load_symbol_table
(
	host_priv_t host,
	task_t task,
	symtab_name_t name,
	vm_offset_t symtab,
	mach_msg_type_number_t symtabCnt
);

/* Routine task_swappable */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t task_swappable
(
	host_priv_t host_priv,
	task_t target_task,
	boolean_t make_swappable
);

/* Routine host_processor_sets */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t host_processor_sets
(
	host_priv_t host_priv,
	processor_set_name_array_t *processor_sets,
	mach_msg_type_number_t *processor_setsCnt
);

/* Routine host_processor_set_priv */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t host_processor_set_priv
(
	host_priv_t host_priv,
	processor_set_name_t set_name,
	processor_set_t *set
);

/* Routine set_dp_control_port */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t set_dp_control_port
(
	host_priv_t host,
	mach_port_t control_port
);

/* Routine get_dp_control_port */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t get_dp_control_port
(
	host_priv_t host,
	mach_port_t *contorl_port
);

/* Routine host_set_UNDServer */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t host_set_UNDServer
(
	host_priv_t host,
	UNDServerRef server
);

/* Routine host_get_UNDServer */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t host_get_UNDServer
(
	host_priv_t host,
	UNDServerRef *server
);

#ifndef subsystem_to_name_map_host_priv
#define subsystem_to_name_map_host_priv \
    { "host_get_boot_info", 400 },\
    { "host_reboot", 401 },\
    { "host_priv_statistics", 402 },\
    { "host_default_memory_manager", 403 },\
    { "vm_wire", 404 },\
    { "thread_wire", 405 },\
    { "vm_allocate_cpm", 406 },\
    { "host_processors", 407 },\
    { "host_get_clock_control", 408 },\
    { "kmod_create", 409 },\
    { "kmod_destroy", 410 },\
    { "kmod_control", 411 },\
    { "host_get_special_port", 412 },\
    { "host_set_special_port", 413 },\
    { "host_set_exception_ports", 414 },\
    { "host_get_exception_ports", 415 },\
    { "host_swap_exception_ports", 416 },\
    { "host_load_symbol_table", 417 },\
    { "task_swappable", 418 },\
    { "host_processor_sets", 419 },\
    { "host_processor_set_priv", 420 },\
    { "set_dp_control_port", 421 },\
    { "get_dp_control_port", 422 },\
    { "host_set_UNDServer", 423 },\
    { "host_get_UNDServer", 424 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _host_priv_user_ */
