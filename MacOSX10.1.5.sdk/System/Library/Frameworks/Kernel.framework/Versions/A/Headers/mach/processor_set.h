#ifndef	_processor_set_user_
#define	_processor_set_user_

/* Module processor_set */

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

#ifndef	processor_set_MSG_COUNT
#define	processor_set_MSG_COUNT	10
#endif	/* processor_set_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mach_types.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */


/* Routine processor_set_statistics */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t processor_set_statistics
(
	processor_set_name_t pset,
	processor_set_flavor_t flavor,
	processor_set_info_t info_out,
	mach_msg_type_number_t *info_outCnt
);

/* Routine processor_set_destroy */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t processor_set_destroy
(
	processor_set_t set
);

/* Routine processor_set_max_priority */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t processor_set_max_priority
(
	processor_set_t processor_set,
	int max_priority,
	boolean_t change_threads
);

/* Routine processor_set_policy_enable */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t processor_set_policy_enable
(
	processor_set_t processor_set,
	int policy
);

/* Routine processor_set_policy_disable */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t processor_set_policy_disable
(
	processor_set_t processor_set,
	int policy,
	boolean_t change_threads
);

/* Routine processor_set_tasks */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t processor_set_tasks
(
	processor_set_t processor_set,
	task_array_t *task_list,
	mach_msg_type_number_t *task_listCnt
);

/* Routine processor_set_threads */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t processor_set_threads
(
	processor_set_t processor_set,
	thread_act_array_t *thread_list,
	mach_msg_type_number_t *thread_listCnt
);

/* Routine processor_set_policy_control */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t processor_set_policy_control
(
	processor_set_t pset,
	processor_set_flavor_t flavor,
	processor_set_info_t policy_info,
	mach_msg_type_number_t policy_infoCnt,
	boolean_t change
);

/* Routine processor_set_stack_usage */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t processor_set_stack_usage
(
	processor_set_t pset,
	unsigned *total,
	vm_size_t *space,
	vm_size_t *resident,
	vm_size_t *maxusage,
	vm_offset_t *maxstack
);

/* Routine processor_set_info */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t processor_set_info
(
	processor_set_name_t set_name,
	int flavor,
	host_t *host,
	processor_set_info_t info_out,
	mach_msg_type_number_t *info_outCnt
);

#ifndef subsystem_to_name_map_processor_set
#define subsystem_to_name_map_processor_set \
    { "processor_set_statistics", 4000 },\
    { "processor_set_destroy", 4001 },\
    { "processor_set_max_priority", 4002 },\
    { "processor_set_policy_enable", 4003 },\
    { "processor_set_policy_disable", 4004 },\
    { "processor_set_tasks", 4005 },\
    { "processor_set_threads", 4006 },\
    { "processor_set_policy_control", 4007 },\
    { "processor_set_stack_usage", 4008 },\
    { "processor_set_info", 4009 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _processor_set_user_ */
