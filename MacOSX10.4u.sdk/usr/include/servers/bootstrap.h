#ifndef	_bootstrap_user_
#define	_bootstrap_user_

/* Module bootstrap */

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

#ifndef	bootstrap_MSG_COUNT
#define	bootstrap_MSG_COUNT	11
#endif	/* bootstrap_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mig.h>
#include <mach/mach_types.h>
#include <servers/bootstrap_defs.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */

#include <sys/cdefs.h>
__BEGIN_DECLS


/* Routine bootstrap_create_server */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t bootstrap_create_server
(
	mach_port_t bootstrap_port,
	cmd_t server_cmd,
	integer_t server_uid,
	boolean_t on_demand,
	mach_port_t *server_port
);

/* Routine bootstrap_unprivileged */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t bootstrap_unprivileged
(
	mach_port_t bootstrap_port,
	mach_port_t *unpriv_port
);

/* Routine bootstrap_check_in */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t bootstrap_check_in
(
	mach_port_t bootstrap_port,
	name_t service_name,
	mach_port_t *service_port
);

/* Routine bootstrap_register */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t bootstrap_register
(
	mach_port_t bootstrap_port,
	name_t service_name,
	mach_port_t service_port
);

/* Routine bootstrap_look_up */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t bootstrap_look_up
(
	mach_port_t bootstrap_port,
	name_t service_name,
	mach_port_t *service_port
);

/* Routine bootstrap_look_up_array */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t bootstrap_look_up_array
(
	mach_port_t bootstrap_port,
	name_array_t service_names,
	mach_msg_type_number_t service_namesCnt,
	mach_port_array_t *service_ports,
	mach_msg_type_number_t *service_portsCnt,
	boolean_t *all_services_known
);

/* Routine bootstrap_parent */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t bootstrap_parent
(
	mach_port_t bootstrap_port,
	mach_port_t *parent_port
);

/* Routine bootstrap_status */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t bootstrap_status
(
	mach_port_t bootstrap_port,
	name_t service_name,
	bootstrap_status_t *service_active
);

/* Routine bootstrap_info */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t bootstrap_info
(
	mach_port_t bootstrap_port,
	name_array_t *service_names,
	mach_msg_type_number_t *service_namesCnt,
	name_array_t *server_names,
	mach_msg_type_number_t *server_namesCnt,
	bootstrap_status_array_t *service_active,
	mach_msg_type_number_t *service_activeCnt
);

/* Routine bootstrap_subset */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t bootstrap_subset
(
	mach_port_t bootstrap_port,
	mach_port_t requestor_port,
	mach_port_t *subset_port
);

/* Routine bootstrap_create_service */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t bootstrap_create_service
(
	mach_port_t bootstrap_port,
	name_t service_name,
	mach_port_t *service_port
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

#ifndef __Request__bootstrap_subsystem__defined
#define __Request__bootstrap_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		cmd_t server_cmd;
		integer_t server_uid;
		boolean_t on_demand;
	} __Request__bootstrap_create_server_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__bootstrap_unprivileged_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		name_t service_name;
	} __Request__bootstrap_check_in_t;
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
		mach_msg_port_descriptor_t service_port;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		name_t service_name;
	} __Request__bootstrap_register_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		name_t service_name;
	} __Request__bootstrap_look_up_t;
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
		mach_msg_ool_descriptor_t service_names;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t service_namesCnt;
	} __Request__bootstrap_look_up_array_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__bootstrap_parent_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		name_t service_name;
	} __Request__bootstrap_status_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__bootstrap_info_t;
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
		mach_msg_port_descriptor_t requestor_port;
		/* end of the kernel processed data */
	} __Request__bootstrap_subset_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		name_t service_name;
	} __Request__bootstrap_create_service_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Request__bootstrap_subsystem__defined */

/* union of all requests */

#ifndef __RequestUnion__bootstrap_subsystem__defined
#define __RequestUnion__bootstrap_subsystem__defined
union __RequestUnion__bootstrap_subsystem {
	__Request__bootstrap_create_server_t Request_bootstrap_create_server;
	__Request__bootstrap_unprivileged_t Request_bootstrap_unprivileged;
	__Request__bootstrap_check_in_t Request_bootstrap_check_in;
	__Request__bootstrap_register_t Request_bootstrap_register;
	__Request__bootstrap_look_up_t Request_bootstrap_look_up;
	__Request__bootstrap_look_up_array_t Request_bootstrap_look_up_array;
	__Request__bootstrap_parent_t Request_bootstrap_parent;
	__Request__bootstrap_status_t Request_bootstrap_status;
	__Request__bootstrap_info_t Request_bootstrap_info;
	__Request__bootstrap_subset_t Request_bootstrap_subset;
	__Request__bootstrap_create_service_t Request_bootstrap_create_service;
};
#endif /* !__RequestUnion__bootstrap_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__bootstrap_subsystem__defined
#define __Reply__bootstrap_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t server_port;
		/* end of the kernel processed data */
	} __Reply__bootstrap_create_server_t;
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
		mach_msg_port_descriptor_t unpriv_port;
		/* end of the kernel processed data */
	} __Reply__bootstrap_unprivileged_t;
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
		mach_msg_port_descriptor_t service_port;
		/* end of the kernel processed data */
	} __Reply__bootstrap_check_in_t;
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
	} __Reply__bootstrap_register_t;
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
		mach_msg_port_descriptor_t service_port;
		/* end of the kernel processed data */
	} __Reply__bootstrap_look_up_t;
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
		mach_msg_ool_ports_descriptor_t service_ports;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t service_portsCnt;
		boolean_t all_services_known;
	} __Reply__bootstrap_look_up_array_t;
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
		mach_msg_port_descriptor_t parent_port;
		/* end of the kernel processed data */
	} __Reply__bootstrap_parent_t;
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
		bootstrap_status_t service_active;
	} __Reply__bootstrap_status_t;
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
		mach_msg_ool_descriptor_t service_names;
		mach_msg_ool_descriptor_t server_names;
		mach_msg_ool_descriptor_t service_active;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t service_namesCnt;
		mach_msg_type_number_t server_namesCnt;
		mach_msg_type_number_t service_activeCnt;
	} __Reply__bootstrap_info_t;
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
		mach_msg_port_descriptor_t subset_port;
		/* end of the kernel processed data */
	} __Reply__bootstrap_subset_t;
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
		mach_msg_port_descriptor_t service_port;
		/* end of the kernel processed data */
	} __Reply__bootstrap_create_service_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Reply__bootstrap_subsystem__defined */

/* union of all replies */

#ifndef __ReplyUnion__bootstrap_subsystem__defined
#define __ReplyUnion__bootstrap_subsystem__defined
union __ReplyUnion__bootstrap_subsystem {
	__Reply__bootstrap_create_server_t Reply_bootstrap_create_server;
	__Reply__bootstrap_unprivileged_t Reply_bootstrap_unprivileged;
	__Reply__bootstrap_check_in_t Reply_bootstrap_check_in;
	__Reply__bootstrap_register_t Reply_bootstrap_register;
	__Reply__bootstrap_look_up_t Reply_bootstrap_look_up;
	__Reply__bootstrap_look_up_array_t Reply_bootstrap_look_up_array;
	__Reply__bootstrap_parent_t Reply_bootstrap_parent;
	__Reply__bootstrap_status_t Reply_bootstrap_status;
	__Reply__bootstrap_info_t Reply_bootstrap_info;
	__Reply__bootstrap_subset_t Reply_bootstrap_subset;
	__Reply__bootstrap_create_service_t Reply_bootstrap_create_service;
};
#endif /* !__RequestUnion__bootstrap_subsystem__defined */

#ifndef subsystem_to_name_map_bootstrap
#define subsystem_to_name_map_bootstrap \
    { "bootstrap_create_server", 400 },\
    { "bootstrap_unprivileged", 401 },\
    { "bootstrap_check_in", 402 },\
    { "bootstrap_register", 403 },\
    { "bootstrap_look_up", 404 },\
    { "bootstrap_look_up_array", 405 },\
    { "bootstrap_parent", 406 },\
    { "bootstrap_status", 407 },\
    { "bootstrap_info", 408 },\
    { "bootstrap_subset", 409 },\
    { "bootstrap_create_service", 410 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _bootstrap_user_ */
