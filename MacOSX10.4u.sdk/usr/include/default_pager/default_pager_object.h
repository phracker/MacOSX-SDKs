#ifndef	_default_pager_object_user_
#define	_default_pager_object_user_

/* Module default_pager_object */

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

#ifndef	default_pager_object_MSG_COUNT
#define	default_pager_object_MSG_COUNT	11
#endif	/* default_pager_object_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mig.h>
#include <mach/mig.h>
#include <mach/mach_types.h>
#include <default_pager/default_pager_types.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */

#include <sys/cdefs.h>
__BEGIN_DECLS


/* Routine default_pager_object_create */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t default_pager_object_create
(
	mach_port_t default_pager,
	vm_size_t object_size,
	memory_object_t *memory_object
);

/* Routine default_pager_info */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t default_pager_info
(
	mach_port_t default_pager,
	default_pager_info_t *info
);

/* Routine default_pager_objects */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t default_pager_objects
(
	mach_port_t default_pager,
	default_pager_object_array_t *objects,
	mach_msg_type_number_t *objectsCnt,
	mach_port_array_t *ports,
	mach_msg_type_number_t *portsCnt
);

/* Routine default_pager_object_pages */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t default_pager_object_pages
(
	mach_port_t default_pager,
	mach_port_t memory_object,
	default_pager_page_array_t *pages,
	mach_msg_type_number_t *pagesCnt
);

/* Routine default_pager_backing_store_create */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t default_pager_backing_store_create
(
	mach_port_t default_pager,
	int priority,
	int clsize,
	mach_port_t *backing_store
);

/* Routine default_pager_backing_store_delete */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t default_pager_backing_store_delete
(
	mach_port_t backing_store
);

/* Routine default_pager_backing_store_info */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t default_pager_backing_store_info
(
	mach_port_t backing_store,
	backing_store_flavor_t flavor,
	backing_store_info_t info,
	mach_msg_type_number_t *infoCnt
);

/* Routine default_pager_add_file */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t default_pager_add_file
(
	mach_port_t backing_store,
	vnode_ptr_t vnode,
	int record_size,
	vm_size_t size
);

/* Routine default_pager_triggers */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t default_pager_triggers
(
	mach_port_t default_pager,
	int hi_wat,
	int lo_wat,
	int flags,
	mach_port_t trigger_port
);

/* Routine default_pager_info_64 */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t default_pager_info_64
(
	mach_port_t default_pager,
	default_pager_info_64_t *info
);

__END_DECLS

/********************** Caution **************************/
/* The following data types should be used to calculate  */
/* maximum message sizes only. The actual message may be */
/* smaller, and the position of the arguments within the */
/* message layout may vary from what is presented here.  */
/* For example, if any of the arguments are variable-    */
/* sized, and less than the maximum is sent, the data    */
/* will be packed tight in the actual message to reduce  */
/* the presence of holes.                                */
/********************** Caution **************************/

/* typedefs for all requests */

#ifndef __Request__default_pager_object_subsystem__defined
#define __Request__default_pager_object_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_size_t object_size;
	} __Request__default_pager_object_create_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__default_pager_info_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__default_pager_objects_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t memory_object;
		/* end of the kernel processed data */
	} __Request__default_pager_object_pages_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int priority;
		int clsize;
	} __Request__default_pager_backing_store_create_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__default_pager_backing_store_delete_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		backing_store_flavor_t flavor;
		mach_msg_type_number_t infoCnt;
	} __Request__default_pager_backing_store_info_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vnode_ptr_t vnode;
		int record_size;
		vm_size_t size;
	} __Request__default_pager_add_file_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t trigger_port;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		int hi_wat;
		int lo_wat;
		int flags;
	} __Request__default_pager_triggers_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__default_pager_info_64_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Request__default_pager_object_subsystem__defined */

/* union of all requests */

#ifndef __RequestUnion__default_pager_object_subsystem__defined
#define __RequestUnion__default_pager_object_subsystem__defined
union __RequestUnion__default_pager_object_subsystem {
	__Request__default_pager_object_create_t Request_default_pager_object_create;
	__Request__default_pager_info_t Request_default_pager_info;
	__Request__default_pager_objects_t Request_default_pager_objects;
	__Request__default_pager_object_pages_t Request_default_pager_object_pages;
	__Request__default_pager_backing_store_create_t Request_default_pager_backing_store_create;
	__Request__default_pager_backing_store_delete_t Request_default_pager_backing_store_delete;
	__Request__default_pager_backing_store_info_t Request_default_pager_backing_store_info;
	__Request__default_pager_add_file_t Request_default_pager_add_file;
	__Request__default_pager_triggers_t Request_default_pager_triggers;
	__Request__default_pager_info_64_t Request_default_pager_info_64;
};
#endif /* !__RequestUnion__default_pager_object_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__default_pager_object_subsystem__defined
#define __Reply__default_pager_object_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t memory_object;
		/* end of the kernel processed data */
	} __Reply__default_pager_object_create_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
		default_pager_info_t info;
	} __Reply__default_pager_info_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_ool_descriptor_t objects;
		mach_msg_ool_ports_descriptor_t ports;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t objectsCnt;
		mach_msg_type_number_t portsCnt;
	} __Reply__default_pager_objects_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_ool_descriptor_t pages;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t pagesCnt;
	} __Reply__default_pager_object_pages_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t backing_store;
		/* end of the kernel processed data */
	} __Reply__default_pager_backing_store_create_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__default_pager_backing_store_delete_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
		mach_msg_type_number_t infoCnt;
		integer_t info[20];
	} __Reply__default_pager_backing_store_info_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__default_pager_add_file_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__default_pager_triggers_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
		default_pager_info_64_t info;
	} __Reply__default_pager_info_64_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Reply__default_pager_object_subsystem__defined */

/* union of all replies */

#ifndef __ReplyUnion__default_pager_object_subsystem__defined
#define __ReplyUnion__default_pager_object_subsystem__defined
union __ReplyUnion__default_pager_object_subsystem {
	__Reply__default_pager_object_create_t Reply_default_pager_object_create;
	__Reply__default_pager_info_t Reply_default_pager_info;
	__Reply__default_pager_objects_t Reply_default_pager_objects;
	__Reply__default_pager_object_pages_t Reply_default_pager_object_pages;
	__Reply__default_pager_backing_store_create_t Reply_default_pager_backing_store_create;
	__Reply__default_pager_backing_store_delete_t Reply_default_pager_backing_store_delete;
	__Reply__default_pager_backing_store_info_t Reply_default_pager_backing_store_info;
	__Reply__default_pager_add_file_t Reply_default_pager_add_file;
	__Reply__default_pager_triggers_t Reply_default_pager_triggers;
	__Reply__default_pager_info_64_t Reply_default_pager_info_64;
};
#endif /* !__RequestUnion__default_pager_object_subsystem__defined */

#ifndef subsystem_to_name_map_default_pager_object
#define subsystem_to_name_map_default_pager_object \
    { "default_pager_object_create", 2275 },\
    { "default_pager_info", 2276 },\
    { "default_pager_objects", 2277 },\
    { "default_pager_object_pages", 2278 },\
    { "default_pager_backing_store_create", 2280 },\
    { "default_pager_backing_store_delete", 2281 },\
    { "default_pager_backing_store_info", 2282 },\
    { "default_pager_add_file", 2283 },\
    { "default_pager_triggers", 2284 },\
    { "default_pager_info_64", 2285 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _default_pager_object_user_ */
