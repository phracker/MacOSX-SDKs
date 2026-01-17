#ifndef	_host_security_user_
#define	_host_security_user_

/* Module host_security */

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

#ifndef	host_security_MSG_COUNT
#define	host_security_MSG_COUNT	2
#endif	/* host_security_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mach_types.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */


/* Routine host_security_create_task_token */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t host_security_create_task_token
(
	host_security_t host_security,
	task_t parent_task,
	security_token_t sec_token,
	host_t host,
	ledger_array_t ledgers,
	mach_msg_type_number_t ledgersCnt,
	boolean_t inherit_memory,
	task_t *child_task
);

/* Routine host_security_set_task_token */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t host_security_set_task_token
(
	host_security_t host_security,
	task_t target_task,
	security_token_t sec_token,
	host_t host
);

#ifndef subsystem_to_name_map_host_security
#define subsystem_to_name_map_host_security \
    { "host_security_create_task_token", 600 },\
    { "host_security_set_task_token", 601 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _host_security_user_ */
