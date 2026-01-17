#ifndef	_doubleagent_server_
#define	_doubleagent_server_

/* Module doubleagent */

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

#ifndef	doubleagent_MSG_COUNT
#define	doubleagent_MSG_COUNT	4
#endif	/* doubleagent_MSG_COUNT */

#include <Availability.h>
#include <mach/std_types.h>
#include <mach/mig.h>
#include <mach/mig.h>
#include <mach/mach_types.h>
#include <mach/doubleagent_types.h>

#ifdef __BeforeMigServerHeader
__BeforeMigServerHeader
#endif /* __BeforeMigServerHeader */

#ifndef MIG_SERVER_ROUTINE
#define MIG_SERVER_ROUTINE
#endif


/* Routine doubleagent_lookup_xattr */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t doubleagent_lookup_xattr
(
	mach_port_t server,
	mach_port_t file_port,
	int64_t file_size,
	xattrname name,
	int *err,
	uint64_t *value_offset,
	uint64_t *value_length
);

/* Routine doubleagent_allocate_xattr */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t doubleagent_allocate_xattr
(
	mach_port_t server,
	mach_port_t file_port,
	int64_t file_size,
	xattrname name,
	uint64_t size,
	uint32_t options,
	int *err,
	uint64_t *value_offset
);

/* Routine doubleagent_list_xattrs */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t doubleagent_list_xattrs
(
	mach_port_t server,
	mach_port_t file_port,
	int64_t file_size,
	int *err,
	listxattrs_result_t *result
);

/* Routine doubleagent_remove_xattr */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t doubleagent_remove_xattr
(
	mach_port_t server,
	mach_port_t file_port,
	int64_t file_size,
	xattrname name,
	int *err,
	boolean_t *is_empty
);

#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
boolean_t doubleagent_server(
		mach_msg_header_t *InHeadP,
		mach_msg_header_t *OutHeadP);

#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
mig_routine_t doubleagent_server_routine(
		mach_msg_header_t *InHeadP);


/* Description of this subsystem, for use in direct RPC */
extern const struct doubleagent_subsystem {
	mig_server_routine_t	server;	/* Server routine */
	mach_msg_id_t	start;	/* Min routine number */
	mach_msg_id_t	end;	/* Max routine number + 1 */
	unsigned int	maxsize;	/* Max msg size */
	vm_address_t	reserved;	/* Reserved */
	struct routine_descriptor	/* Array of routine descriptors */
		routine[4];
} doubleagent_subsystem;

/* typedefs for all requests */

#ifndef __Request__doubleagent_subsystem__defined
#define __Request__doubleagent_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t file_port;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		int64_t file_size;
		mach_msg_type_number_t nameOffset; /* MiG doesn't use it */
		mach_msg_type_number_t nameCnt;
		char name[128];
	} __Request__doubleagent_lookup_xattr_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t file_port;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		int64_t file_size;
		mach_msg_type_number_t nameOffset; /* MiG doesn't use it */
		mach_msg_type_number_t nameCnt;
		char name[128];
		uint64_t size;
		uint32_t options;
	} __Request__doubleagent_allocate_xattr_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t file_port;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		int64_t file_size;
	} __Request__doubleagent_list_xattrs_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t file_port;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		int64_t file_size;
		mach_msg_type_number_t nameOffset; /* MiG doesn't use it */
		mach_msg_type_number_t nameCnt;
		char name[128];
	} __Request__doubleagent_remove_xattr_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif
#endif /* !__Request__doubleagent_subsystem__defined */


/* union of all requests */

#ifndef __RequestUnion__doubleagent_subsystem__defined
#define __RequestUnion__doubleagent_subsystem__defined
union __RequestUnion__doubleagent_subsystem {
	__Request__doubleagent_lookup_xattr_t Request_doubleagent_lookup_xattr;
	__Request__doubleagent_allocate_xattr_t Request_doubleagent_allocate_xattr;
	__Request__doubleagent_list_xattrs_t Request_doubleagent_list_xattrs;
	__Request__doubleagent_remove_xattr_t Request_doubleagent_remove_xattr;
};
#endif /* __RequestUnion__doubleagent_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__doubleagent_subsystem__defined
#define __Reply__doubleagent_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
		int err;
		uint64_t value_offset;
		uint64_t value_length;
	} __Reply__doubleagent_lookup_xattr_t __attribute__((unused));
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
		int err;
		uint64_t value_offset;
	} __Reply__doubleagent_allocate_xattr_t __attribute__((unused));
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
		int err;
		listxattrs_result_t result;
	} __Reply__doubleagent_list_xattrs_t __attribute__((unused));
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
		int err;
		boolean_t is_empty;
	} __Reply__doubleagent_remove_xattr_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif
#endif /* !__Reply__doubleagent_subsystem__defined */


/* union of all replies */

#ifndef __ReplyUnion__doubleagent_subsystem__defined
#define __ReplyUnion__doubleagent_subsystem__defined
union __ReplyUnion__doubleagent_subsystem {
	__Reply__doubleagent_lookup_xattr_t Reply_doubleagent_lookup_xattr;
	__Reply__doubleagent_allocate_xattr_t Reply_doubleagent_allocate_xattr;
	__Reply__doubleagent_list_xattrs_t Reply_doubleagent_list_xattrs;
	__Reply__doubleagent_remove_xattr_t Reply_doubleagent_remove_xattr;
};
#endif /* __ReplyUnion__doubleagent_subsystem__defined */

#ifndef subsystem_to_name_map_doubleagent
#define subsystem_to_name_map_doubleagent \
    { "doubleagent_lookup_xattr", 6300 },\
    { "doubleagent_allocate_xattr", 6301 },\
    { "doubleagent_list_xattrs", 6302 },\
    { "doubleagent_remove_xattr", 6303 }
#endif

#ifdef __AfterMigServerHeader
__AfterMigServerHeader
#endif /* __AfterMigServerHeader */

#endif	 /* _doubleagent_server_ */
