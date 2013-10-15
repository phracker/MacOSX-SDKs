#ifndef	_audit_triggers_server_
#define	_audit_triggers_server_

/* Module audit_triggers */

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

#ifndef	audit_triggers_MSG_COUNT
#define	audit_triggers_MSG_COUNT	1
#endif	/* audit_triggers_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mig.h>
#include <mach/mig.h>
#include <mach/mach_types.h>

#ifdef __BeforeMigServerHeader
__BeforeMigServerHeader
#endif /* __BeforeMigServerHeader */


/* SimpleRoutine audit_triggers */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t audit_triggers
(
	mach_port_t audit_port,
	int flags
);

extern boolean_t audit_triggers_server(
		mach_msg_header_t *InHeadP,
		mach_msg_header_t *OutHeadP);

extern mig_routine_t audit_triggers_server_routine(
		mach_msg_header_t *InHeadP);


/* Description of this subsystem, for use in direct RPC */
extern const struct audit_triggers_subsystem {
	mig_server_routine_t	server;	/* Server routine */
	mach_msg_id_t	start;	/* Min routine number */
	mach_msg_id_t	end;	/* Max routine number + 1 */
	unsigned int	maxsize;	/* Max msg size */
	vm_address_t	reserved;	/* Reserved */
	struct routine_descriptor	/*Array of routine descriptors */
		routine[1];
} audit_triggers_subsystem;

/* typedefs for all requests */

#ifndef __Request__audit_triggers_subsystem__defined
#define __Request__audit_triggers_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int flags;
	} __Request__audit_triggers_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Request__audit_triggers_subsystem__defined */


/* union of all requests */

#ifndef __RequestUnion__audit_triggers_subsystem__defined
#define __RequestUnion__audit_triggers_subsystem__defined
union __RequestUnion__audit_triggers_subsystem {
	__Request__audit_triggers_t Request_audit_triggers;
};
#endif /* __RequestUnion__audit_triggers_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__audit_triggers_subsystem__defined
#define __Reply__audit_triggers_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__audit_triggers_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Reply__audit_triggers_subsystem__defined */


/* union of all replies */

#ifndef __ReplyUnion__audit_triggers_subsystem__defined
#define __ReplyUnion__audit_triggers_subsystem__defined
union __ReplyUnion__audit_triggers_subsystem {
	__Reply__audit_triggers_t Reply_audit_triggers;
};
#endif /* __RequestUnion__audit_triggers_subsystem__defined */

#ifndef subsystem_to_name_map_audit_triggers
#define subsystem_to_name_map_audit_triggers \
    { "audit_triggers", 123 }
#endif

#ifdef __AfterMigServerHeader
__AfterMigServerHeader
#endif /* __AfterMigServerHeader */

#endif	 /* _audit_triggers_server_ */
