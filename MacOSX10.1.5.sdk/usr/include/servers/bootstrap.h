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
#define	bootstrap_MSG_COUNT	11
#endif	/* bootstrap_MSG_COUNT */

#include <mach/std_types.h>
#include <servers/bootstrap_defs.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */


/* Routine bootstrap_check_in */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t bootstrap_check_in
(
	mach_port_t bootstrap_port,
	name_t service_name,
	mach_port_t *service_port
);

/* Routine bootstrap_register */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t bootstrap_register
(
	mach_port_t bootstrap_port,
	name_t service_name,
	mach_port_t service_port
);

/* Routine bootstrap_look_up */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t bootstrap_look_up
(
	mach_port_t bootstrap_port,
	name_t service_name,
	mach_port_t *service_port
);

/* Routine bootstrap_look_up_array */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t bootstrap_look_up_array
(
	mach_port_t bootstrap_port,
	name_array_t service_names,
	mach_msg_type_number_t service_namesCnt,
	mach_port_array_t *service_ports,
	mach_msg_type_number_t *service_portsCnt,
	boolean_t *all_services_known
);

/* Routine bootstrap_status */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t bootstrap_status
(
	mach_port_t bootstrap_port,
	name_t service_name,
	boolean_t *service_active
);

/* Routine bootstrap_info */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t bootstrap_info
(
	mach_port_t bootstrap_port,
	name_array_t *service_names,
	mach_msg_type_number_t *service_namesCnt,
	name_array_t *server_names,
	mach_msg_type_number_t *server_namesCnt,
	bool_array_t *service_active,
	mach_msg_type_number_t *service_activeCnt
);

/* Routine bootstrap_subset */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t bootstrap_subset
(
	mach_port_t bootstrap_port,
	mach_port_t requestor_port,
	mach_port_t *subset_port
);

/* Routine bootstrap_create_service */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t bootstrap_create_service
(
	mach_port_t bootstrap_port,
	name_t service_name,
	mach_port_t *service_port
);

#ifndef subsystem_to_name_map_bootstrap
#define subsystem_to_name_map_bootstrap \
    { "bootstrap_check_in", 402 },\
    { "bootstrap_register", 403 },\
    { "bootstrap_look_up", 404 },\
    { "bootstrap_look_up_array", 405 },\
    { "bootstrap_status", 407 },\
    { "bootstrap_info", 408 },\
    { "bootstrap_subset", 409 },\
    { "bootstrap_create_service", 410 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _bootstrap_user_ */
