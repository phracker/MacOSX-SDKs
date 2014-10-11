#ifndef	_lookup_user_
#define	_lookup_user_

/* Module lookup */

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

#ifndef	lookup_MSG_COUNT
#define	lookup_MSG_COUNT	4
#endif	/* lookup_MSG_COUNT */

#include <netinfo/lookup_types.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */


/* Routine _lookup_link */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t _lookup_link
(
	mach_port_t server,
	lookup_name name,
	int *procno
);

/* Routine _lookup_all */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t _lookup_all
(
	mach_port_t server,
	int proc,
	inline_data indata,
	mach_msg_type_number_t indataCnt,
	ooline_data *outdata,
	mach_msg_type_number_t *outdataCnt
);

/* Routine _lookup_one */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t _lookup_one
(
	mach_port_t server,
	int proc,
	inline_data indata,
	mach_msg_type_number_t indataCnt,
	inline_data outdata,
	mach_msg_type_number_t *outdataCnt
);

/* Routine _lookup_ooall */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t _lookup_ooall
(
	mach_port_t server,
	int proc,
	ooline_data indata,
	mach_msg_type_number_t indataCnt,
	ooline_data *outdata,
	mach_msg_type_number_t *outdataCnt
);

#ifndef subsystem_to_name_map_lookup
#define subsystem_to_name_map_lookup \
    { "_lookup_link", 4241775 },\
    { "_lookup_all", 4241776 },\
    { "_lookup_one", 4241777 },\
    { "_lookup_ooall", 4241778 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _lookup_user_ */
