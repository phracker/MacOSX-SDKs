#ifndef	_lock_set_user_
#define	_lock_set_user_

/* Module lock_set */

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

#ifndef	lock_set_MSG_COUNT
#define	lock_set_MSG_COUNT	6
#endif	/* lock_set_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mach_types.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */


/* Routine lock_acquire */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t lock_acquire
(
	lock_set_t lock_set,
	int lock_id
);

/* Routine lock_release */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t lock_release
(
	lock_set_t lock_set,
	int lock_id
);

/* Routine lock_try */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t lock_try
(
	lock_set_t lock_set,
	int lock_id
);

/* Routine lock_make_stable */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t lock_make_stable
(
	lock_set_t lock_set,
	int lock_id
);

/* Routine lock_handoff */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t lock_handoff
(
	lock_set_t lock_set,
	int lock_id
);

/* Routine lock_handoff_accept */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t lock_handoff_accept
(
	lock_set_t lock_set,
	int lock_id
);

#ifndef subsystem_to_name_map_lock_set
#define subsystem_to_name_map_lock_set \
    { "lock_acquire", 617000 },\
    { "lock_release", 617001 },\
    { "lock_try", 617002 },\
    { "lock_make_stable", 617003 },\
    { "lock_handoff", 617004 },\
    { "lock_handoff_accept", 617005 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _lock_set_user_ */
