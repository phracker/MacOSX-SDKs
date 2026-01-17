#ifndef	_memory_object_server_
#define	_memory_object_server_

/* Module memory_object */

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

#ifndef	memory_object_MSG_COUNT
#define	memory_object_MSG_COUNT	8
#endif	/* memory_object_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mig.h>
#include <mach/mig.h>
#include <mach/mach_types.h>

#ifdef __BeforeMigServerHeader
__BeforeMigServerHeader
#endif /* __BeforeMigServerHeader */


/* Routine memory_object_init */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t memory_object_init
(
	memory_object_t memory_object,
	memory_object_control_t memory_control,
	memory_object_cluster_size_t memory_object_page_size
);

/* Routine memory_object_terminate */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t memory_object_terminate
(
	memory_object_t memory_object
);

/* Routine memory_object_data_request */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t memory_object_data_request
(
	memory_object_t memory_object,
	memory_object_offset_t offset,
	memory_object_cluster_size_t length,
	vm_prot_t desired_access
);

/* Routine memory_object_data_return */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t memory_object_data_return
(
	memory_object_t memory_object,
	memory_object_offset_t offset,
	memory_object_cluster_size_t size,
	memory_object_offset_t *resid_offset,
	int *io_error,
	boolean_t dirty,
	boolean_t kernel_copy,
	int upl_flags
);

/* Routine memory_object_data_initialize */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t memory_object_data_initialize
(
	memory_object_t memory_object,
	memory_object_offset_t offset,
	memory_object_cluster_size_t size
);

/* Routine memory_object_data_unlock */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t memory_object_data_unlock
(
	memory_object_t memory_object,
	memory_object_offset_t offset,
	memory_object_cluster_size_t size,
	vm_prot_t desired_access
);

/* Routine memory_object_synchronize */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t memory_object_synchronize
(
	memory_object_t memory_object,
	memory_object_offset_t offset,
	memory_object_cluster_size_t size,
	vm_sync_t sync_flags
);

/* Routine memory_object_unmap */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t memory_object_unmap
(
	memory_object_t memory_object
);

extern boolean_t memory_object_server(
		mach_msg_header_t *InHeadP,
		mach_msg_header_t *OutHeadP);

extern mig_routine_t memory_object_server_routine(
		mach_msg_header_t *InHeadP);


/* Description of this subsystem, for use in direct RPC */
extern const struct memory_object_subsystem {
	mig_server_routine_t	server;	/* Server routine */
	mach_msg_id_t	start;	/* Min routine number */
	mach_msg_id_t	end;	/* Max routine number + 1 */
	unsigned int	maxsize;	/* Max msg size */
	vm_address_t	reserved;	/* Reserved */
	struct routine_descriptor	/*Array of routine descriptors */
		routine[8];
} memory_object_subsystem;

/* typedefs for all requests */

#ifndef __Request__memory_object_subsystem__defined
#define __Request__memory_object_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t memory_control;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		memory_object_cluster_size_t memory_object_page_size;
	} __Request__memory_object_init_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__memory_object_terminate_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		memory_object_offset_t offset;
		memory_object_cluster_size_t length;
		vm_prot_t desired_access;
	} __Request__memory_object_data_request_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		memory_object_offset_t offset;
		memory_object_cluster_size_t size;
		boolean_t dirty;
		boolean_t kernel_copy;
		int upl_flags;
	} __Request__memory_object_data_return_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		memory_object_offset_t offset;
		memory_object_cluster_size_t size;
	} __Request__memory_object_data_initialize_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		memory_object_offset_t offset;
		memory_object_cluster_size_t size;
		vm_prot_t desired_access;
	} __Request__memory_object_data_unlock_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		memory_object_offset_t offset;
		memory_object_cluster_size_t size;
		vm_sync_t sync_flags;
	} __Request__memory_object_synchronize_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__memory_object_unmap_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Request__memory_object_subsystem__defined */


/* union of all requests */

#ifndef __RequestUnion__memory_object_subsystem__defined
#define __RequestUnion__memory_object_subsystem__defined
union __RequestUnion__memory_object_subsystem {
	__Request__memory_object_init_t Request_memory_object_init;
	__Request__memory_object_terminate_t Request_memory_object_terminate;
	__Request__memory_object_data_request_t Request_memory_object_data_request;
	__Request__memory_object_data_return_t Request_memory_object_data_return;
	__Request__memory_object_data_initialize_t Request_memory_object_data_initialize;
	__Request__memory_object_data_unlock_t Request_memory_object_data_unlock;
	__Request__memory_object_synchronize_t Request_memory_object_synchronize;
	__Request__memory_object_unmap_t Request_memory_object_unmap;
};
#endif /* __RequestUnion__memory_object_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__memory_object_subsystem__defined
#define __Reply__memory_object_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__memory_object_init_t;
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
	} __Reply__memory_object_terminate_t;
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
	} __Reply__memory_object_data_request_t;
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
		memory_object_offset_t resid_offset;
		int io_error;
	} __Reply__memory_object_data_return_t;
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
	} __Reply__memory_object_data_initialize_t;
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
	} __Reply__memory_object_data_unlock_t;
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
	} __Reply__memory_object_synchronize_t;
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
	} __Reply__memory_object_unmap_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Reply__memory_object_subsystem__defined */


/* union of all replies */

#ifndef __ReplyUnion__memory_object_subsystem__defined
#define __ReplyUnion__memory_object_subsystem__defined
union __ReplyUnion__memory_object_subsystem {
	__Reply__memory_object_init_t Reply_memory_object_init;
	__Reply__memory_object_terminate_t Reply_memory_object_terminate;
	__Reply__memory_object_data_request_t Reply_memory_object_data_request;
	__Reply__memory_object_data_return_t Reply_memory_object_data_return;
	__Reply__memory_object_data_initialize_t Reply_memory_object_data_initialize;
	__Reply__memory_object_data_unlock_t Reply_memory_object_data_unlock;
	__Reply__memory_object_synchronize_t Reply_memory_object_synchronize;
	__Reply__memory_object_unmap_t Reply_memory_object_unmap;
};
#endif /* __RequestUnion__memory_object_subsystem__defined */

#ifndef subsystem_to_name_map_memory_object
#define subsystem_to_name_map_memory_object \
    { "memory_object_init", 2200 },\
    { "memory_object_terminate", 2201 },\
    { "memory_object_data_request", 2202 },\
    { "memory_object_data_return", 2203 },\
    { "memory_object_data_initialize", 2204 },\
    { "memory_object_data_unlock", 2205 },\
    { "memory_object_synchronize", 2206 },\
    { "memory_object_unmap", 2207 }
#endif

#ifdef __AfterMigServerHeader
__AfterMigServerHeader
#endif /* __AfterMigServerHeader */

#endif	 /* _memory_object_server_ */
