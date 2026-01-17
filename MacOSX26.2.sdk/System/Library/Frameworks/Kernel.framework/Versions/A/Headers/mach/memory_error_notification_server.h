#ifndef	_memory_error_notification_server_
#define	_memory_error_notification_server_

/* Module memory_error_notification */

#include <string.h>
#include <mach/ndr.h>
#include <mach/boolean.h>
#include <mach/kern_return.h>
#include <mach/notify.h>
#include <mach/mach_types.h>
#include <mach/message.h>
#include <mach/mig_errors.h>
#include <mach/port.h>
	
/* BEGIN MIG_STRNCPY_ZEROFILL CODE */

#if defined(__has_include)
#if __has_include(<mach/mig_strncpy_zerofill_support.h>)
#ifndef USING_MIG_STRNCPY_ZEROFILL
#define USING_MIG_STRNCPY_ZEROFILL
#endif
#ifndef __MIG_STRNCPY_ZEROFILL_FORWARD_TYPE_DECLS__
#define __MIG_STRNCPY_ZEROFILL_FORWARD_TYPE_DECLS__
#ifdef __cplusplus
extern "C" {
#endif
#ifndef __MIG_STRNCPY_ZEROFILL_FORWARD_TYPE_DECLS_CSTRING_ATTR
#define __MIG_STRNCPY_ZEROFILL_FORWARD_TYPE_DECLS_CSTRING_COUNTEDBY_ATTR(C) __unsafe_indexable
#endif
	extern int mig_strncpy_zerofill(char * dest, const char * src, int len) __attribute__((weak_import));
#ifdef __cplusplus
}
#endif
#endif /* __MIG_STRNCPY_ZEROFILL_FORWARD_TYPE_DECLS__ */
#endif /* __has_include(<mach/mig_strncpy_zerofill_support.h>) */
#endif /* __has_include */
	
/* END MIG_STRNCPY_ZEROFILL CODE */


#ifdef AUTOTEST
#ifndef FUNCTION_PTR_T
#define FUNCTION_PTR_T
typedef void (*function_ptr_t)(mach_port_t, char *, mach_msg_type_number_t);
typedef struct {
        char            * name;
        function_ptr_t  function;
} function_table_entry;
typedef function_table_entry   *function_table_t;
#endif /* FUNCTION_PTR_T */
#endif /* AUTOTEST */

#ifndef	memory_error_notification_MSG_COUNT
#define	memory_error_notification_MSG_COUNT	2
#endif	/* memory_error_notification_MSG_COUNT */

#include <Availability.h>
#include <mach/std_types.h>
#include <mach/mig.h>
#include <mach/mig.h>
#include <mach/mach_types.h>
#include <kern/ecc.h>

#ifdef __BeforeMigServerHeader
__BeforeMigServerHeader
#endif /* __BeforeMigServerHeader */

#ifndef MIG_SERVER_ROUTINE
#define MIG_SERVER_ROUTINE
#endif


/* SimpleRoutine memory_error_notification */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t memory_error_notification
(
	mach_port_t memory_error_port,
	ecc_event_t event,
	audit_token_t atoken
);

/* SimpleRoutine mcc_memory_error_notification */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t mcc_memory_error_notification
(
	mach_port_t memory_error_port,
	mcc_ecc_event_t event,
	audit_token_t atoken
);

#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
boolean_t memory_error_notification_server(
		mach_msg_header_t *InHeadP,
		mach_msg_header_t *OutHeadP);

#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
mig_routine_t memory_error_notification_server_routine(
		mach_msg_header_t *InHeadP);


/* Description of this subsystem, for use in direct RPC */
extern const struct memory_error_notification_subsystem {
	mig_server_routine_t	server;	/* Server routine */
	mach_msg_id_t	start;	/* Min routine number */
	mach_msg_id_t	end;	/* Max routine number + 1 */
	unsigned int	maxsize;	/* Max msg size */
	vm_address_t	reserved;	/* Reserved */
	struct routine_descriptor	/* Array of routine descriptors */
		routine[2];
} memory_error_notification_subsystem;

/* typedefs for all requests */

#ifndef __Request__memory_error_notification_subsystem__defined
#define __Request__memory_error_notification_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		ecc_event_t event;
	} __Request__memory_error_notification_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mcc_ecc_event_t event;
	} __Request__mcc_memory_error_notification_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif
#endif /* !__Request__memory_error_notification_subsystem__defined */


/* union of all requests */

#ifndef __RequestUnion__memory_error_notification_subsystem__defined
#define __RequestUnion__memory_error_notification_subsystem__defined
union __RequestUnion__memory_error_notification_subsystem {
	__Request__memory_error_notification_t Request_memory_error_notification;
	__Request__mcc_memory_error_notification_t Request_mcc_memory_error_notification;
};
#endif /* __RequestUnion__memory_error_notification_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__memory_error_notification_subsystem__defined
#define __Reply__memory_error_notification_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__memory_error_notification_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__mcc_memory_error_notification_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif
#endif /* !__Reply__memory_error_notification_subsystem__defined */


/* union of all replies */

#ifndef __ReplyUnion__memory_error_notification_subsystem__defined
#define __ReplyUnion__memory_error_notification_subsystem__defined
union __ReplyUnion__memory_error_notification_subsystem {
	__Reply__memory_error_notification_t Reply_memory_error_notification;
	__Reply__mcc_memory_error_notification_t Reply_mcc_memory_error_notification;
};
#endif /* __ReplyUnion__memory_error_notification_subsystem__defined */

#ifndef subsystem_to_name_map_memory_error_notification
#define subsystem_to_name_map_memory_error_notification \
    { "memory_error_notification", 5900 },\
    { "mcc_memory_error_notification", 5901 }
#endif

#ifdef __AfterMigServerHeader
__AfterMigServerHeader
#endif /* __AfterMigServerHeader */

#endif	 /* _memory_error_notification_server_ */
