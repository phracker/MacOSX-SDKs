#ifndef	_processor_user_
#define	_processor_user_

/* Module processor */

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

#ifndef	processor_MSG_COUNT
#define	processor_MSG_COUNT	6
#endif	/* processor_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mach_types.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */


/* Routine processor_start */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t processor_start
(
	processor_t processor
);

/* Routine processor_exit */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t processor_exit
(
	processor_t processor
);

/* Routine processor_info */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t processor_info
(
	processor_t processor,
	processor_flavor_t flavor,
	host_t *host,
	processor_info_t processor_info_out,
	mach_msg_type_number_t *processor_info_outCnt
);

/* Routine processor_control */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t processor_control
(
	processor_t processor,
	processor_info_t processor_cmd,
	mach_msg_type_number_t processor_cmdCnt
);

/* Routine processor_assign */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t processor_assign
(
	processor_t processor,
	processor_set_t new_set,
	boolean_t wait
);

/* Routine processor_get_assignment */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t processor_get_assignment
(
	processor_t processor,
	processor_set_name_t *assigned_set
);

#ifndef subsystem_to_name_map_processor
#define subsystem_to_name_map_processor \
    { "processor_start", 3000 },\
    { "processor_exit", 3001 },\
    { "processor_info", 3002 },\
    { "processor_control", 3003 },\
    { "processor_assign", 3004 },\
    { "processor_get_assignment", 3005 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _processor_user_ */
