#ifndef	_netname_user_
#define	_netname_user_

/* Module netname */

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

#ifndef	netname_MSG_COUNT
#define	netname_MSG_COUNT	4
#endif	/* netname_MSG_COUNT */

#include <mach/std_types.h>
#include <servers/netname_defs.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */


/* Routine netname_check_in */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t netname_check_in
(
	mach_port_t server_port,
	netname_name_t port_name,
	mach_port_t signature,
	mach_port_t port_id
);

/* Routine netname_look_up */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t netname_look_up
(
	mach_port_t server_port,
	netname_name_t host_name,
	netname_name_t port_name,
	mach_port_t *port_id
);

/* Routine netname_check_out */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t netname_check_out
(
	mach_port_t server_port,
	netname_name_t port_name,
	mach_port_t signature
);

/* Routine netname_version */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t netname_version
(
	mach_port_t server_port,
	netname_name_t version
);

#ifndef subsystem_to_name_map_netname
#define subsystem_to_name_map_netname \
    { "netname_check_in", 1040 },\
    { "netname_look_up", 1041 },\
    { "netname_check_out", 1042 },\
    { "netname_version", 1043 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _netname_user_ */
