#ifndef	_ledger_user_
#define	_ledger_user_

/* Module ledger */

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

#ifndef	ledger_MSG_COUNT
#define	ledger_MSG_COUNT	4
#endif	/* ledger_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mach_types.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */


/* Routine ledger_create */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t ledger_create
(
	ledger_t parent_ledger,
	ledger_t ledger_ledger,
	ledger_t *new_ledger,
	ledger_item_t transfer
);

/* Routine ledger_terminate */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t ledger_terminate
(
	ledger_t ledger
);

/* Routine ledger_transfer */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t ledger_transfer
(
	ledger_t parent_ledger,
	ledger_t child_ledger,
	ledger_item_t transfer
);

/* Routine ledger_read */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t ledger_read
(
	ledger_t ledger,
	ledger_item_t *balance,
	ledger_item_t *limit
);

#ifndef subsystem_to_name_map_ledger
#define subsystem_to_name_map_ledger \
    { "ledger_create", 5000 },\
    { "ledger_terminate", 5001 },\
    { "ledger_transfer", 5002 },\
    { "ledger_read", 5003 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _ledger_user_ */
