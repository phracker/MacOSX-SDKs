#ifndef	_mach_i386_server_
#define	_mach_i386_server_

/* Module mach_i386 */

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

#ifndef	mach_i386_MSG_COUNT
#define	mach_i386_MSG_COUNT	5
#endif	/* mach_i386_MSG_COUNT */

#include <mach/std_types.h>
#include <kern/ipc_mig.h>
#include <mach/mach_types.h>
#include <device/device_types.h>
#include <mach/i386/mach_i386_types.h>

#ifdef __BeforeMigServerHeader
__BeforeMigServerHeader
#endif /* __BeforeMigServerHeader */

/* typedefs for all requests */

	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t device;
		/* end of the kernel processed data */
	} __Request__i386_io_port_add_t;

	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t device;
		/* end of the kernel processed data */
	} __Request__i386_io_port_remove_t;

	typedef struct {
		mach_msg_header_t Head;
	} __Request__i386_io_port_list_t;

	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_ool_descriptor_t desc_list;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		int first_selector;
		mach_msg_type_number_t desc_listCnt;
	} __Request__i386_set_ldt_t;

	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int first_selector;
		int selector_count;
	} __Request__i386_get_ldt_t;


/* union of all requests */

union __RequestUnion__mach_i386_subsystem {
	__Request__i386_io_port_add_t Request_i386_io_port_add;
	__Request__i386_io_port_remove_t Request_i386_io_port_remove;
	__Request__i386_io_port_list_t Request_i386_io_port_list;
	__Request__i386_set_ldt_t Request_i386_set_ldt;
	__Request__i386_get_ldt_t Request_i386_get_ldt;
};
/* typedefs for all replies */

	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__i386_io_port_add_t;

	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__i386_io_port_remove_t;

	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_ool_ports_descriptor_t device_list;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t device_listCnt;
	} __Reply__i386_io_port_list_t;

	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__i386_set_ldt_t;

	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_ool_descriptor_t desc_list;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t desc_listCnt;
	} __Reply__i386_get_ldt_t;


/* union of all replies */

union __ReplyUnion__mach_i386_subsystem {
	__Reply__i386_io_port_add_t Reply_i386_io_port_add;
	__Reply__i386_io_port_remove_t Reply_i386_io_port_remove;
	__Reply__i386_io_port_list_t Reply_i386_io_port_list;
	__Reply__i386_set_ldt_t Reply_i386_set_ldt;
	__Reply__i386_get_ldt_t Reply_i386_get_ldt;
};

/* Routine i386_io_port_add */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t i386_io_port_add
(
	thread_act_t target_act,
	device_t device
);

/* Routine i386_io_port_remove */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t i386_io_port_remove
(
	thread_act_t target_act,
	device_t device
);

/* Routine i386_io_port_list */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t i386_io_port_list
(
	thread_act_t target_act,
	device_list_t *device_list,
	mach_msg_type_number_t *device_listCnt
);

/* Routine i386_set_ldt */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t i386_set_ldt
(
	thread_act_t target_act,
	int first_selector,
	descriptor_list_t desc_list,
	mach_msg_type_number_t desc_listCnt
);

/* Routine i386_get_ldt */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t i386_get_ldt
(
	thread_act_t target_act,
	int first_selector,
	int selector_count,
	descriptor_list_t *desc_list,
	mach_msg_type_number_t *desc_listCnt
);

extern boolean_t mach_i386_server(
		mach_msg_header_t *InHeadP,
		mach_msg_header_t *OutHeadP);

extern mig_routine_t mach_i386_server_routine(
		mach_msg_header_t *InHeadP);


/* Description of this subsystem, for use in direct RPC */
extern const struct mach_i386_subsystem {
	struct subsystem *	subsystem;	/* Reserved for system use */
	mach_msg_id_t	start;	/* Min routine number */
	mach_msg_id_t	end;	/* Max routine number + 1 */
	unsigned int	maxsize;	/* Max msg size */
	vm_address_t	base_addr;	/* Base ddress */
	struct routine_descriptor	/*Array of routine descriptors */
		routine[5];
} mach_i386_subsystem;


#ifndef subsystem_to_name_map_mach_i386
#define subsystem_to_name_map_mach_i386 \
    { "i386_io_port_add", 3800 },\
    { "i386_io_port_remove", 3801 },\
    { "i386_io_port_list", 3802 },\
    { "i386_set_ldt", 3803 },\
    { "i386_get_ldt", 3804 }
#endif

#ifdef __AfterMigServerHeader
__AfterMigServerHeader
#endif /* __AfterMigServerHeader */

#endif	 /* _mach_i386_server_ */
