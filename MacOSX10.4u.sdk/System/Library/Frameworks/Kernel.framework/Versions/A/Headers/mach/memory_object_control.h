#ifndef	_memory_object_control_user_
#define	_memory_object_control_user_

/* Module memory_object_control */

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

#ifndef	memory_object_control_MSG_COUNT
#define	memory_object_control_MSG_COUNT	11
#endif	/* memory_object_control_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mig.h>
#include <mach/mig.h>
#include <mach/mach_types.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */

#include <sys/cdefs.h>
__BEGIN_DECLS


/* Routine memory_object_get_attributes */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t memory_object_get_attributes
(
	memory_object_control_t memory_control,
	memory_object_flavor_t flavor,
	memory_object_info_t attributes,
	mach_msg_type_number_t *attributesCnt
);

/* Routine memory_object_change_attributes */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t memory_object_change_attributes
(
	memory_object_control_t memory_control,
	memory_object_flavor_t flavor,
	memory_object_info_t attributes,
	mach_msg_type_number_t attributesCnt
);

/* Routine memory_object_synchronize_completed */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t memory_object_synchronize_completed
(
	memory_object_control_t memory_control,
	memory_object_offset_t offset,
	vm_offset_t length
);

/* Routine memory_object_lock_request */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t memory_object_lock_request
(
	memory_object_control_t memory_control,
	memory_object_offset_t offset,
	memory_object_size_t size,
	memory_object_offset_t *resid_offset,
	integer_t *io_errno,
	memory_object_return_t should_return,
	integer_t flags,
	vm_prot_t lock_value
);

/* Routine memory_object_destroy */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t memory_object_destroy
(
	memory_object_control_t memory_control,
	kern_return_t reason
);

/* Routine memory_object_upl_request */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t memory_object_upl_request
(
	memory_object_control_t memory_control,
	memory_object_offset_t offset,
	vm_size_t size,
	upl_t *upl,
	upl_page_info_array_t page_list,
	mach_msg_type_number_t *page_listCnt,
	integer_t cntrl_flags
);

/* Routine memory_object_super_upl_request */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t memory_object_super_upl_request
(
	memory_object_control_t memory_control,
	memory_object_offset_t offset,
	vm_size_t size,
	vm_size_t super_size,
	upl_t *upl,
	upl_page_info_array_t page_list,
	mach_msg_type_number_t *page_listCnt,
	integer_t cntrl_flags
);

/* Routine memory_object_page_op */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t memory_object_page_op
(
	memory_object_control_t memory_control,
	memory_object_offset_t offset,
	integer_t ops,
	uint32_t *phys_entry,
	integer_t *flags
);

/* Routine memory_object_recover_named */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t memory_object_recover_named
(
	memory_object_control_t memory_control,
	boolean_t wait_on_terminating
);

/* Routine memory_object_release_name */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t memory_object_release_name
(
	memory_object_control_t memory_control,
	integer_t flags
);

/* Routine memory_object_range_op */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t memory_object_range_op
(
	memory_object_control_t memory_control,
	memory_object_offset_t offset_beg,
	memory_object_offset_t offset_end,
	integer_t ops,
	integer_t *range
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

#ifndef __Request__memory_object_control_subsystem__defined
#define __Request__memory_object_control_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		memory_object_flavor_t flavor;
		mach_msg_type_number_t attributesCnt;
	} __Request__memory_object_get_attributes_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		memory_object_flavor_t flavor;
		mach_msg_type_number_t attributesCnt;
		int attributes[6];
	} __Request__memory_object_change_attributes_t;
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
		vm_offset_t length;
	} __Request__memory_object_synchronize_completed_t;
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
		memory_object_size_t size;
		memory_object_return_t should_return;
		integer_t flags;
		vm_prot_t lock_value;
	} __Request__memory_object_lock_request_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t reason;
	} __Request__memory_object_destroy_t;
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
		vm_size_t size;
		mach_msg_type_number_t page_listCnt;
		integer_t cntrl_flags;
	} __Request__memory_object_upl_request_t;
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
		vm_size_t size;
		vm_size_t super_size;
		mach_msg_type_number_t page_listCnt;
		integer_t cntrl_flags;
	} __Request__memory_object_super_upl_request_t;
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
		integer_t ops;
	} __Request__memory_object_page_op_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		boolean_t wait_on_terminating;
	} __Request__memory_object_recover_named_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		integer_t flags;
	} __Request__memory_object_release_name_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		memory_object_offset_t offset_beg;
		memory_object_offset_t offset_end;
		integer_t ops;
	} __Request__memory_object_range_op_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Request__memory_object_control_subsystem__defined */

/* union of all requests */

#ifndef __RequestUnion__memory_object_control_subsystem__defined
#define __RequestUnion__memory_object_control_subsystem__defined
union __RequestUnion__memory_object_control_subsystem {
	__Request__memory_object_get_attributes_t Request_memory_object_get_attributes;
	__Request__memory_object_change_attributes_t Request_memory_object_change_attributes;
	__Request__memory_object_synchronize_completed_t Request_memory_object_synchronize_completed;
	__Request__memory_object_lock_request_t Request_memory_object_lock_request;
	__Request__memory_object_destroy_t Request_memory_object_destroy;
	__Request__memory_object_upl_request_t Request_memory_object_upl_request;
	__Request__memory_object_super_upl_request_t Request_memory_object_super_upl_request;
	__Request__memory_object_page_op_t Request_memory_object_page_op;
	__Request__memory_object_recover_named_t Request_memory_object_recover_named;
	__Request__memory_object_release_name_t Request_memory_object_release_name;
	__Request__memory_object_range_op_t Request_memory_object_range_op;
};
#endif /* !__RequestUnion__memory_object_control_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__memory_object_control_subsystem__defined
#define __Reply__memory_object_control_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
		mach_msg_type_number_t attributesCnt;
		int attributes[6];
	} __Reply__memory_object_get_attributes_t;
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
	} __Reply__memory_object_change_attributes_t;
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
	} __Reply__memory_object_synchronize_completed_t;
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
		integer_t io_errno;
	} __Reply__memory_object_lock_request_t;
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
	} __Reply__memory_object_destroy_t;
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
		mach_msg_port_descriptor_t upl;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t page_listCnt;
		upl_page_info_t page_list[256];
	} __Reply__memory_object_upl_request_t;
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
		mach_msg_port_descriptor_t upl;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t page_listCnt;
		upl_page_info_t page_list[256];
	} __Reply__memory_object_super_upl_request_t;
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
		uint32_t phys_entry;
		integer_t flags;
	} __Reply__memory_object_page_op_t;
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
	} __Reply__memory_object_recover_named_t;
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
	} __Reply__memory_object_release_name_t;
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
		integer_t range;
	} __Reply__memory_object_range_op_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Reply__memory_object_control_subsystem__defined */

/* union of all replies */

#ifndef __ReplyUnion__memory_object_control_subsystem__defined
#define __ReplyUnion__memory_object_control_subsystem__defined
union __ReplyUnion__memory_object_control_subsystem {
	__Reply__memory_object_get_attributes_t Reply_memory_object_get_attributes;
	__Reply__memory_object_change_attributes_t Reply_memory_object_change_attributes;
	__Reply__memory_object_synchronize_completed_t Reply_memory_object_synchronize_completed;
	__Reply__memory_object_lock_request_t Reply_memory_object_lock_request;
	__Reply__memory_object_destroy_t Reply_memory_object_destroy;
	__Reply__memory_object_upl_request_t Reply_memory_object_upl_request;
	__Reply__memory_object_super_upl_request_t Reply_memory_object_super_upl_request;
	__Reply__memory_object_page_op_t Reply_memory_object_page_op;
	__Reply__memory_object_recover_named_t Reply_memory_object_recover_named;
	__Reply__memory_object_release_name_t Reply_memory_object_release_name;
	__Reply__memory_object_range_op_t Reply_memory_object_range_op;
};
#endif /* !__RequestUnion__memory_object_control_subsystem__defined */

#ifndef subsystem_to_name_map_memory_object_control
#define subsystem_to_name_map_memory_object_control \
    { "memory_object_get_attributes", 2000 },\
    { "memory_object_change_attributes", 2001 },\
    { "memory_object_synchronize_completed", 2002 },\
    { "memory_object_lock_request", 2003 },\
    { "memory_object_destroy", 2004 },\
    { "memory_object_upl_request", 2005 },\
    { "memory_object_super_upl_request", 2006 },\
    { "memory_object_page_op", 2007 },\
    { "memory_object_recover_named", 2008 },\
    { "memory_object_release_name", 2009 },\
    { "memory_object_range_op", 2010 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _memory_object_control_user_ */
