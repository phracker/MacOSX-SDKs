#ifndef	_clock_priv_user_
#define	_clock_priv_user_

/* Module clock_priv */

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

#ifndef	clock_priv_MSG_COUNT
#define	clock_priv_MSG_COUNT	2
#endif	/* clock_priv_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mach_types.h>
#include <mach/mach_types.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */


/* Routine clock_set_time */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t clock_set_time
(
	clock_ctrl_t clock_ctrl,
	mach_timespec_t new_time
);

/* Routine clock_set_attributes */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t clock_set_attributes
(
	clock_ctrl_t clock_ctrl,
	clock_flavor_t flavor,
	clock_attr_t clock_attr,
	mach_msg_type_number_t clock_attrCnt
);

#ifndef subsystem_to_name_map_clock_priv
#define subsystem_to_name_map_clock_priv \
    { "clock_set_time", 1200 },\
    { "clock_set_attributes", 1201 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _clock_priv_user_ */
