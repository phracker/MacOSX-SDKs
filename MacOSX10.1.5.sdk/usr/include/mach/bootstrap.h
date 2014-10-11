#ifndef	_bootstrap_user_
#define	_bootstrap_user_

/* Module bootstrap */

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

#ifndef	bootstrap_MSG_COUNT
#define	bootstrap_MSG_COUNT	4
#endif	/* bootstrap_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mach_types.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */


/* Routine bootstrap_ports */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t bootstrap_ports
(
	bootstrap_t bootstrap,
	mach_port_t *priv_host,
	mach_port_t *device_master,
	mach_port_t *wired_ledger,
	mach_port_t *paged_ledger,
	mach_port_t *host_security
);

/* Routine bootstrap_arguments */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t bootstrap_arguments
(
	bootstrap_t bootstrap,
	task_t task,
	vm_offset_t *arguments,
	mach_msg_type_number_t *argumentsCnt
);

/* Routine bootstrap_environment */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t bootstrap_environment
(
	bootstrap_t bootstrap,
	task_t task,
	vm_offset_t *environment,
	mach_msg_type_number_t *environmentCnt
);

/* SimpleRoutine bootstrap_completed */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t bootstrap_completed
(
	bootstrap_t bootstrap,
	task_t task
);

#ifndef subsystem_to_name_map_bootstrap
#define subsystem_to_name_map_bootstrap \
    { "bootstrap_ports", 1000001 },\
    { "bootstrap_arguments", 1000002 },\
    { "bootstrap_environment", 1000003 },\
    { "bootstrap_completed", 1000004 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _bootstrap_user_ */
