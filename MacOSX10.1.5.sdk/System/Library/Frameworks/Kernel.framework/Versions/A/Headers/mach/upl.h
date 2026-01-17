#ifndef	_upl_user_
#define	_upl_user_

/* Module upl */

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

#ifndef	upl_MSG_COUNT
#define	upl_MSG_COUNT	4
#endif	/* upl_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mach_types.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */


/* Routine upl_abort */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t upl_abort
(
	upl_t upl_object,
	integer_t abort_cond
);

/* Routine upl_abort_range */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t upl_abort_range
(
	upl_t upl_object,
	vm_offset_t offset,
	vm_size_t size,
	integer_t abort_cond,
	boolean_t *empty
);

/* Routine upl_commit */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t upl_commit
(
	upl_t upl_object,
	upl_page_info_array_t page_list,
	mach_msg_type_number_t page_listCnt
);

/* Routine upl_commit_range */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t upl_commit_range
(
	upl_t upl_object,
	vm_offset_t offset,
	vm_size_t size,
	integer_t cntrl_flags,
	upl_page_info_array_t page_list,
	mach_msg_type_number_t page_listCnt,
	boolean_t *empty
);

#ifndef subsystem_to_name_map_upl
#define subsystem_to_name_map_upl \
    { "upl_abort", 2050 },\
    { "upl_abort_range", 2051 },\
    { "upl_commit", 2052 },\
    { "upl_commit_range", 2053 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _upl_user_ */
