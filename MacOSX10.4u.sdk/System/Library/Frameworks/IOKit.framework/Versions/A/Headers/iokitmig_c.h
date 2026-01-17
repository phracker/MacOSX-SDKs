#ifndef	_iokit_user_
#define	_iokit_user_

/* Module iokit */

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

#ifndef	iokit_MSG_COUNT
#define	iokit_MSG_COUNT	63
#endif	/* iokit_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mig.h>
#include <mach/mig.h>
#include <mach/mach_types.h>
#include <mach/mach_types.h>
#include <device/device_types.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */

#include <sys/cdefs.h>
__BEGIN_DECLS


/* Routine io_object_get_class */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_object_get_class
(
	mach_port_t object,
	io_name_t className
);

/* Routine io_object_conforms_to */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_object_conforms_to
(
	mach_port_t object,
	io_name_t className,
	boolean_t *conforms
);

/* Routine io_iterator_next */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_iterator_next
(
	mach_port_t iterator,
	mach_port_t *object
);

/* Routine io_iterator_reset */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_iterator_reset
(
	mach_port_t iterator
);

/* Routine io_service_get_matching_services */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_service_get_matching_services
(
	mach_port_t master_port,
	io_string_t matching,
	mach_port_t *existing
);

/* Routine io_registry_entry_get_property */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_registry_entry_get_property
(
	mach_port_t registry_entry,
	io_name_t property_name,
	io_buf_ptr_t *properties,
	mach_msg_type_number_t *propertiesCnt
);

/* Routine io_registry_create_iterator */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_registry_create_iterator
(
	mach_port_t master_port,
	io_name_t plane,
	int options,
	mach_port_t *iterator
);

/* Routine io_registry_iterator_enter_entry */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_registry_iterator_enter_entry
(
	mach_port_t iterator
);

/* Routine io_registry_iterator_exit_entry */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_registry_iterator_exit_entry
(
	mach_port_t iterator
);

/* Routine io_registry_entry_from_path */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_registry_entry_from_path
(
	mach_port_t master_port,
	io_string_t path,
	mach_port_t *registry_entry
);

/* Routine io_registry_entry_get_name */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_registry_entry_get_name
(
	mach_port_t registry_entry,
	io_name_t name
);

/* Routine io_registry_entry_get_properties */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_registry_entry_get_properties
(
	mach_port_t registry_entry,
	io_buf_ptr_t *properties,
	mach_msg_type_number_t *propertiesCnt
);

/* Routine io_registry_entry_get_property_bytes */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_registry_entry_get_property_bytes
(
	mach_port_t registry_entry,
	io_name_t property_name,
	io_struct_inband_t data,
	mach_msg_type_number_t *dataCnt
);

/* Routine io_registry_entry_get_child_iterator */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_registry_entry_get_child_iterator
(
	mach_port_t registry_entry,
	io_name_t plane,
	mach_port_t *iterator
);

/* Routine io_registry_entry_get_parent_iterator */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_registry_entry_get_parent_iterator
(
	mach_port_t registry_entry,
	io_name_t plane,
	mach_port_t *iterator
);

/* Routine io_service_open */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_service_open
(
	mach_port_t service,
	task_t owningTask,
	int connect_type,
	mach_port_t *connection
);

/* Routine io_service_close */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_service_close
(
	mach_port_t connection
);

/* Routine io_connect_get_service */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_connect_get_service
(
	mach_port_t connection,
	mach_port_t *service
);

/* Routine io_connect_set_notification_port */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_connect_set_notification_port
(
	mach_port_t connection,
	int notification_type,
	mach_port_t port,
	int reference
);

/* Routine io_connect_map_memory */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_connect_map_memory
(
	mach_port_t connection,
	int memory_type,
	task_t into_task,
	vm_address_t *address,
	vm_size_t *size,
	int flags
);

/* Routine io_connect_add_client */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_connect_add_client
(
	mach_port_t connection,
	mach_port_t connect_to
);

/* Routine io_connect_set_properties */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_connect_set_properties
(
	mach_port_t connection,
	io_buf_ptr_t properties,
	mach_msg_type_number_t propertiesCnt,
	natural_t *result
);

/* Routine io_connect_method_scalarI_scalarO */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_connect_method_scalarI_scalarO
(
	mach_port_t connection,
	int selector,
	io_scalar_inband_t input,
	mach_msg_type_number_t inputCnt,
	io_scalar_inband_t output,
	mach_msg_type_number_t *outputCnt
);

/* Routine io_connect_method_scalarI_structureO */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_connect_method_scalarI_structureO
(
	mach_port_t connection,
	int selector,
	io_scalar_inband_t input,
	mach_msg_type_number_t inputCnt,
	io_struct_inband_t output,
	mach_msg_type_number_t *outputCnt
);

/* Routine io_connect_method_scalarI_structureI */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_connect_method_scalarI_structureI
(
	mach_port_t connection,
	int selector,
	io_scalar_inband_t input,
	mach_msg_type_number_t inputCnt,
	io_struct_inband_t inputStruct,
	mach_msg_type_number_t inputStructCnt
);

/* Routine io_connect_method_structureI_structureO */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_connect_method_structureI_structureO
(
	mach_port_t connection,
	int selector,
	io_struct_inband_t input,
	mach_msg_type_number_t inputCnt,
	io_struct_inband_t output,
	mach_msg_type_number_t *outputCnt
);

/* Routine io_registry_entry_get_path */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_registry_entry_get_path
(
	mach_port_t registry_entry,
	io_name_t plane,
	io_string_t path
);

/* Routine io_registry_get_root_entry */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_registry_get_root_entry
(
	mach_port_t master_port,
	mach_port_t *root
);

/* Routine io_registry_entry_set_properties */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_registry_entry_set_properties
(
	mach_port_t registry_entry,
	io_buf_ptr_t properties,
	mach_msg_type_number_t propertiesCnt,
	natural_t *result
);

/* Routine io_registry_entry_in_plane */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_registry_entry_in_plane
(
	mach_port_t registry_entry,
	io_name_t plane,
	boolean_t *inPlane
);

/* Routine io_object_get_retain_count */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_object_get_retain_count
(
	mach_port_t object,
	int *retainCount
);

/* Routine io_service_get_busy_state */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_service_get_busy_state
(
	mach_port_t service,
	int *busyState
);

/* Routine io_service_wait_quiet */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_service_wait_quiet
(
	mach_port_t service,
	mach_timespec_t wait_time
);

/* Routine io_registry_entry_create_iterator */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_registry_entry_create_iterator
(
	mach_port_t registry_entry,
	io_name_t plane,
	int options,
	mach_port_t *iterator
);

/* Routine io_iterator_is_valid */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_iterator_is_valid
(
	mach_port_t iterator,
	boolean_t *is_valid
);

/* Routine io_make_matching */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_make_matching
(
	mach_port_t master_port,
	int of_type,
	int options,
	io_struct_inband_t input,
	mach_msg_type_number_t inputCnt,
	io_string_t matching
);

/* Routine io_catalog_send_data */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_catalog_send_data
(
	mach_port_t master_port,
	int flag,
	io_buf_ptr_t inData,
	mach_msg_type_number_t inDataCnt,
	natural_t *result
);

/* Routine io_catalog_terminate */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_catalog_terminate
(
	mach_port_t master_port,
	int flag,
	io_name_t name
);

/* Routine io_catalog_get_data */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_catalog_get_data
(
	mach_port_t master_port,
	int flag,
	io_buf_ptr_t *outData,
	mach_msg_type_number_t *outDataCnt
);

/* Routine io_catalog_get_gen_count */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_catalog_get_gen_count
(
	mach_port_t master_port,
	int *genCount
);

/* Routine io_catalog_module_loaded */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_catalog_module_loaded
(
	mach_port_t master_port,
	io_name_t name
);

/* Routine io_catalog_reset */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_catalog_reset
(
	mach_port_t master_port,
	int flag
);

/* Routine io_service_request_probe */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_service_request_probe
(
	mach_port_t service,
	int options
);

/* Routine io_registry_entry_get_name_in_plane */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_registry_entry_get_name_in_plane
(
	mach_port_t registry_entry,
	io_name_t plane,
	io_name_t name
);

/* Routine io_service_match_property_table */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_service_match_property_table
(
	mach_port_t service,
	io_string_t matching,
	boolean_t *matches
);

/* Routine io_async_method_scalarI_scalarO */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_async_method_scalarI_scalarO
(
	mach_port_t connection,
	mach_port_t wake_port,
	io_async_ref_t reference,
	mach_msg_type_number_t referenceCnt,
	int selector,
	io_scalar_inband_t input,
	mach_msg_type_number_t inputCnt,
	io_scalar_inband_t output,
	mach_msg_type_number_t *outputCnt
);

/* Routine io_async_method_scalarI_structureO */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_async_method_scalarI_structureO
(
	mach_port_t connection,
	mach_port_t wake_port,
	io_async_ref_t reference,
	mach_msg_type_number_t referenceCnt,
	int selector,
	io_scalar_inband_t input,
	mach_msg_type_number_t inputCnt,
	io_struct_inband_t output,
	mach_msg_type_number_t *outputCnt
);

/* Routine io_async_method_scalarI_structureI */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_async_method_scalarI_structureI
(
	mach_port_t connection,
	mach_port_t wake_port,
	io_async_ref_t reference,
	mach_msg_type_number_t referenceCnt,
	int selector,
	io_scalar_inband_t input,
	mach_msg_type_number_t inputCnt,
	io_struct_inband_t inputStruct,
	mach_msg_type_number_t inputStructCnt
);

/* Routine io_async_method_structureI_structureO */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_async_method_structureI_structureO
(
	mach_port_t connection,
	mach_port_t wake_port,
	io_async_ref_t reference,
	mach_msg_type_number_t referenceCnt,
	int selector,
	io_struct_inband_t input,
	mach_msg_type_number_t inputCnt,
	io_struct_inband_t output,
	mach_msg_type_number_t *outputCnt
);

/* Routine io_service_add_notification */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_service_add_notification
(
	mach_port_t master_port,
	io_name_t notification_type,
	io_string_t matching,
	mach_port_t wake_port,
	io_async_ref_t reference,
	mach_msg_type_number_t referenceCnt,
	mach_port_t *notification
);

/* Routine io_service_add_interest_notification */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_service_add_interest_notification
(
	mach_port_t service,
	io_name_t type_of_interest,
	mach_port_t wake_port,
	io_async_ref_t reference,
	mach_msg_type_number_t referenceCnt,
	mach_port_t *notification
);

/* Routine io_service_acknowledge_notification */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_service_acknowledge_notification
(
	mach_port_t service,
	natural_t notify_ref,
	natural_t response
);

/* Routine io_connect_get_notification_semaphore */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_connect_get_notification_semaphore
(
	mach_port_t connection,
	natural_t notification_type,
	semaphore_t *semaphore
);

/* Routine io_connect_unmap_memory */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_connect_unmap_memory
(
	mach_port_t connection,
	int memory_type,
	task_t into_task,
	vm_address_t address
);

/* Routine io_registry_entry_get_location_in_plane */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_registry_entry_get_location_in_plane
(
	mach_port_t registry_entry,
	io_name_t plane,
	io_name_t location
);

/* Routine io_registry_entry_get_property_recursively */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_registry_entry_get_property_recursively
(
	mach_port_t registry_entry,
	io_name_t plane,
	io_name_t property_name,
	int options,
	io_buf_ptr_t *properties,
	mach_msg_type_number_t *propertiesCnt
);

/* Routine io_service_get_state */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_service_get_state
(
	mach_port_t service,
	uint64_t *state
);

/* Routine io_service_get_matching_services_ool */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_service_get_matching_services_ool
(
	mach_port_t master_port,
	io_buf_ptr_t matching,
	mach_msg_type_number_t matchingCnt,
	natural_t *result,
	mach_port_t *existing
);

/* Routine io_service_match_property_table_ool */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_service_match_property_table_ool
(
	mach_port_t service,
	io_buf_ptr_t matching,
	mach_msg_type_number_t matchingCnt,
	natural_t *result,
	boolean_t *matches
);

/* Routine io_service_add_notification_ool */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_service_add_notification_ool
(
	mach_port_t master_port,
	io_name_t notification_type,
	io_buf_ptr_t matching,
	mach_msg_type_number_t matchingCnt,
	mach_port_t wake_port,
	io_async_ref_t reference,
	mach_msg_type_number_t referenceCnt,
	natural_t *result,
	mach_port_t *notification
);

/* Routine io_object_get_superclass */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_object_get_superclass
(
	mach_port_t master_port,
	io_name_t obj_name,
	io_name_t class_name
);

/* Routine io_object_get_bundle_identifier */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_object_get_bundle_identifier
(
	mach_port_t master_port,
	io_name_t obj_name,
	io_name_t class_name
);

/* Routine io_service_open_extended */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t io_service_open_extended
(
	mach_port_t service,
	task_t owningTask,
	int connect_type,
	NDR_record_t ndr,
	io_buf_ptr_t properties,
	mach_msg_type_number_t propertiesCnt,
	natural_t *result,
	mach_port_t *connection
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

#ifndef __Request__iokit_subsystem__defined
#define __Request__iokit_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__io_object_get_class_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t classNameOffset; /* MiG doesn't use it */
		mach_msg_type_number_t classNameCnt;
		char className[128];
	} __Request__io_object_conforms_to_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__io_iterator_next_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__io_iterator_reset_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t matchingOffset; /* MiG doesn't use it */
		mach_msg_type_number_t matchingCnt;
		char matching[512];
	} __Request__io_service_get_matching_services_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t property_nameOffset; /* MiG doesn't use it */
		mach_msg_type_number_t property_nameCnt;
		char property_name[128];
	} __Request__io_registry_entry_get_property_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t planeOffset; /* MiG doesn't use it */
		mach_msg_type_number_t planeCnt;
		char plane[128];
		int options;
	} __Request__io_registry_create_iterator_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__io_registry_iterator_enter_entry_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__io_registry_iterator_exit_entry_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t pathOffset; /* MiG doesn't use it */
		mach_msg_type_number_t pathCnt;
		char path[512];
	} __Request__io_registry_entry_from_path_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__io_registry_entry_get_name_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__io_registry_entry_get_properties_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t property_nameOffset; /* MiG doesn't use it */
		mach_msg_type_number_t property_nameCnt;
		char property_name[128];
		mach_msg_type_number_t dataCnt;
	} __Request__io_registry_entry_get_property_bytes_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t planeOffset; /* MiG doesn't use it */
		mach_msg_type_number_t planeCnt;
		char plane[128];
	} __Request__io_registry_entry_get_child_iterator_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t planeOffset; /* MiG doesn't use it */
		mach_msg_type_number_t planeCnt;
		char plane[128];
	} __Request__io_registry_entry_get_parent_iterator_t;
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
		mach_msg_port_descriptor_t owningTask;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		int connect_type;
	} __Request__io_service_open_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__io_service_close_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__io_connect_get_service_t;
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
		mach_msg_port_descriptor_t port;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		int notification_type;
		int reference;
	} __Request__io_connect_set_notification_port_t;
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
		mach_msg_port_descriptor_t into_task;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		int memory_type;
		vm_address_t address;
		vm_size_t size;
		int flags;
	} __Request__io_connect_map_memory_t;
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
		mach_msg_port_descriptor_t connect_to;
		/* end of the kernel processed data */
	} __Request__io_connect_add_client_t;
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
		mach_msg_ool_descriptor_t properties;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t propertiesCnt;
	} __Request__io_connect_set_properties_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int selector;
		mach_msg_type_number_t inputCnt;
		int input[16];
		mach_msg_type_number_t outputCnt;
	} __Request__io_connect_method_scalarI_scalarO_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int selector;
		mach_msg_type_number_t inputCnt;
		int input[16];
		mach_msg_type_number_t outputCnt;
	} __Request__io_connect_method_scalarI_structureO_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int selector;
		mach_msg_type_number_t inputCnt;
		int input[16];
		mach_msg_type_number_t inputStructCnt;
		char inputStruct[4096];
	} __Request__io_connect_method_scalarI_structureI_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int selector;
		mach_msg_type_number_t inputCnt;
		char input[4096];
		mach_msg_type_number_t outputCnt;
	} __Request__io_connect_method_structureI_structureO_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t planeOffset; /* MiG doesn't use it */
		mach_msg_type_number_t planeCnt;
		char plane[128];
	} __Request__io_registry_entry_get_path_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__io_registry_get_root_entry_t;
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
		mach_msg_ool_descriptor_t properties;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t propertiesCnt;
	} __Request__io_registry_entry_set_properties_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t planeOffset; /* MiG doesn't use it */
		mach_msg_type_number_t planeCnt;
		char plane[128];
	} __Request__io_registry_entry_in_plane_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__io_object_get_retain_count_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__io_service_get_busy_state_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_timespec_t wait_time;
	} __Request__io_service_wait_quiet_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t planeOffset; /* MiG doesn't use it */
		mach_msg_type_number_t planeCnt;
		char plane[128];
		int options;
	} __Request__io_registry_entry_create_iterator_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__io_iterator_is_valid_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int of_type;
		int options;
		mach_msg_type_number_t inputCnt;
		char input[4096];
	} __Request__io_make_matching_t;
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
		mach_msg_ool_descriptor_t inData;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		int flag;
		mach_msg_type_number_t inDataCnt;
	} __Request__io_catalog_send_data_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int flag;
		mach_msg_type_number_t nameOffset; /* MiG doesn't use it */
		mach_msg_type_number_t nameCnt;
		char name[128];
	} __Request__io_catalog_terminate_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int flag;
	} __Request__io_catalog_get_data_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__io_catalog_get_gen_count_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t nameOffset; /* MiG doesn't use it */
		mach_msg_type_number_t nameCnt;
		char name[128];
	} __Request__io_catalog_module_loaded_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int flag;
	} __Request__io_catalog_reset_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int options;
	} __Request__io_service_request_probe_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t planeOffset; /* MiG doesn't use it */
		mach_msg_type_number_t planeCnt;
		char plane[128];
	} __Request__io_registry_entry_get_name_in_plane_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t matchingOffset; /* MiG doesn't use it */
		mach_msg_type_number_t matchingCnt;
		char matching[512];
	} __Request__io_service_match_property_table_t;
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
		mach_msg_port_descriptor_t wake_port;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t referenceCnt;
		natural_t reference[8];
		int selector;
		mach_msg_type_number_t inputCnt;
		int input[16];
		mach_msg_type_number_t outputCnt;
	} __Request__io_async_method_scalarI_scalarO_t;
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
		mach_msg_port_descriptor_t wake_port;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t referenceCnt;
		natural_t reference[8];
		int selector;
		mach_msg_type_number_t inputCnt;
		int input[16];
		mach_msg_type_number_t outputCnt;
	} __Request__io_async_method_scalarI_structureO_t;
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
		mach_msg_port_descriptor_t wake_port;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t referenceCnt;
		natural_t reference[8];
		int selector;
		mach_msg_type_number_t inputCnt;
		int input[16];
		mach_msg_type_number_t inputStructCnt;
		char inputStruct[4096];
	} __Request__io_async_method_scalarI_structureI_t;
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
		mach_msg_port_descriptor_t wake_port;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t referenceCnt;
		natural_t reference[8];
		int selector;
		mach_msg_type_number_t inputCnt;
		char input[4096];
		mach_msg_type_number_t outputCnt;
	} __Request__io_async_method_structureI_structureO_t;
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
		mach_msg_port_descriptor_t wake_port;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t notification_typeOffset; /* MiG doesn't use it */
		mach_msg_type_number_t notification_typeCnt;
		char notification_type[128];
		mach_msg_type_number_t matchingOffset; /* MiG doesn't use it */
		mach_msg_type_number_t matchingCnt;
		char matching[512];
		mach_msg_type_number_t referenceCnt;
		natural_t reference[8];
	} __Request__io_service_add_notification_t;
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
		mach_msg_port_descriptor_t wake_port;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t type_of_interestOffset; /* MiG doesn't use it */
		mach_msg_type_number_t type_of_interestCnt;
		char type_of_interest[128];
		mach_msg_type_number_t referenceCnt;
		natural_t reference[8];
	} __Request__io_service_add_interest_notification_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		natural_t notify_ref;
		natural_t response;
	} __Request__io_service_acknowledge_notification_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		natural_t notification_type;
	} __Request__io_connect_get_notification_semaphore_t;
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
		mach_msg_port_descriptor_t into_task;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		int memory_type;
		vm_address_t address;
	} __Request__io_connect_unmap_memory_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t planeOffset; /* MiG doesn't use it */
		mach_msg_type_number_t planeCnt;
		char plane[128];
	} __Request__io_registry_entry_get_location_in_plane_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t planeOffset; /* MiG doesn't use it */
		mach_msg_type_number_t planeCnt;
		char plane[128];
		mach_msg_type_number_t property_nameOffset; /* MiG doesn't use it */
		mach_msg_type_number_t property_nameCnt;
		char property_name[128];
		int options;
	} __Request__io_registry_entry_get_property_recursively_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__io_service_get_state_t;
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
		mach_msg_ool_descriptor_t matching;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t matchingCnt;
	} __Request__io_service_get_matching_services_ool_t;
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
		mach_msg_ool_descriptor_t matching;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t matchingCnt;
	} __Request__io_service_match_property_table_ool_t;
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
		mach_msg_ool_descriptor_t matching;
		mach_msg_port_descriptor_t wake_port;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t notification_typeOffset; /* MiG doesn't use it */
		mach_msg_type_number_t notification_typeCnt;
		char notification_type[128];
		mach_msg_type_number_t matchingCnt;
		mach_msg_type_number_t referenceCnt;
		natural_t reference[8];
	} __Request__io_service_add_notification_ool_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t obj_nameOffset; /* MiG doesn't use it */
		mach_msg_type_number_t obj_nameCnt;
		char obj_name[128];
	} __Request__io_object_get_superclass_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t obj_nameOffset; /* MiG doesn't use it */
		mach_msg_type_number_t obj_nameCnt;
		char obj_name[128];
	} __Request__io_object_get_bundle_identifier_t;
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
		mach_msg_port_descriptor_t owningTask;
		mach_msg_ool_descriptor_t properties;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		int connect_type;
		NDR_record_t ndr;
		mach_msg_type_number_t propertiesCnt;
	} __Request__io_service_open_extended_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Request__iokit_subsystem__defined */

/* union of all requests */

#ifndef __RequestUnion__iokit_subsystem__defined
#define __RequestUnion__iokit_subsystem__defined
union __RequestUnion__iokit_subsystem {
	__Request__io_object_get_class_t Request_io_object_get_class;
	__Request__io_object_conforms_to_t Request_io_object_conforms_to;
	__Request__io_iterator_next_t Request_io_iterator_next;
	__Request__io_iterator_reset_t Request_io_iterator_reset;
	__Request__io_service_get_matching_services_t Request_io_service_get_matching_services;
	__Request__io_registry_entry_get_property_t Request_io_registry_entry_get_property;
	__Request__io_registry_create_iterator_t Request_io_registry_create_iterator;
	__Request__io_registry_iterator_enter_entry_t Request_io_registry_iterator_enter_entry;
	__Request__io_registry_iterator_exit_entry_t Request_io_registry_iterator_exit_entry;
	__Request__io_registry_entry_from_path_t Request_io_registry_entry_from_path;
	__Request__io_registry_entry_get_name_t Request_io_registry_entry_get_name;
	__Request__io_registry_entry_get_properties_t Request_io_registry_entry_get_properties;
	__Request__io_registry_entry_get_property_bytes_t Request_io_registry_entry_get_property_bytes;
	__Request__io_registry_entry_get_child_iterator_t Request_io_registry_entry_get_child_iterator;
	__Request__io_registry_entry_get_parent_iterator_t Request_io_registry_entry_get_parent_iterator;
	__Request__io_service_open_t Request_io_service_open;
	__Request__io_service_close_t Request_io_service_close;
	__Request__io_connect_get_service_t Request_io_connect_get_service;
	__Request__io_connect_set_notification_port_t Request_io_connect_set_notification_port;
	__Request__io_connect_map_memory_t Request_io_connect_map_memory;
	__Request__io_connect_add_client_t Request_io_connect_add_client;
	__Request__io_connect_set_properties_t Request_io_connect_set_properties;
	__Request__io_connect_method_scalarI_scalarO_t Request_io_connect_method_scalarI_scalarO;
	__Request__io_connect_method_scalarI_structureO_t Request_io_connect_method_scalarI_structureO;
	__Request__io_connect_method_scalarI_structureI_t Request_io_connect_method_scalarI_structureI;
	__Request__io_connect_method_structureI_structureO_t Request_io_connect_method_structureI_structureO;
	__Request__io_registry_entry_get_path_t Request_io_registry_entry_get_path;
	__Request__io_registry_get_root_entry_t Request_io_registry_get_root_entry;
	__Request__io_registry_entry_set_properties_t Request_io_registry_entry_set_properties;
	__Request__io_registry_entry_in_plane_t Request_io_registry_entry_in_plane;
	__Request__io_object_get_retain_count_t Request_io_object_get_retain_count;
	__Request__io_service_get_busy_state_t Request_io_service_get_busy_state;
	__Request__io_service_wait_quiet_t Request_io_service_wait_quiet;
	__Request__io_registry_entry_create_iterator_t Request_io_registry_entry_create_iterator;
	__Request__io_iterator_is_valid_t Request_io_iterator_is_valid;
	__Request__io_make_matching_t Request_io_make_matching;
	__Request__io_catalog_send_data_t Request_io_catalog_send_data;
	__Request__io_catalog_terminate_t Request_io_catalog_terminate;
	__Request__io_catalog_get_data_t Request_io_catalog_get_data;
	__Request__io_catalog_get_gen_count_t Request_io_catalog_get_gen_count;
	__Request__io_catalog_module_loaded_t Request_io_catalog_module_loaded;
	__Request__io_catalog_reset_t Request_io_catalog_reset;
	__Request__io_service_request_probe_t Request_io_service_request_probe;
	__Request__io_registry_entry_get_name_in_plane_t Request_io_registry_entry_get_name_in_plane;
	__Request__io_service_match_property_table_t Request_io_service_match_property_table;
	__Request__io_async_method_scalarI_scalarO_t Request_io_async_method_scalarI_scalarO;
	__Request__io_async_method_scalarI_structureO_t Request_io_async_method_scalarI_structureO;
	__Request__io_async_method_scalarI_structureI_t Request_io_async_method_scalarI_structureI;
	__Request__io_async_method_structureI_structureO_t Request_io_async_method_structureI_structureO;
	__Request__io_service_add_notification_t Request_io_service_add_notification;
	__Request__io_service_add_interest_notification_t Request_io_service_add_interest_notification;
	__Request__io_service_acknowledge_notification_t Request_io_service_acknowledge_notification;
	__Request__io_connect_get_notification_semaphore_t Request_io_connect_get_notification_semaphore;
	__Request__io_connect_unmap_memory_t Request_io_connect_unmap_memory;
	__Request__io_registry_entry_get_location_in_plane_t Request_io_registry_entry_get_location_in_plane;
	__Request__io_registry_entry_get_property_recursively_t Request_io_registry_entry_get_property_recursively;
	__Request__io_service_get_state_t Request_io_service_get_state;
	__Request__io_service_get_matching_services_ool_t Request_io_service_get_matching_services_ool;
	__Request__io_service_match_property_table_ool_t Request_io_service_match_property_table_ool;
	__Request__io_service_add_notification_ool_t Request_io_service_add_notification_ool;
	__Request__io_object_get_superclass_t Request_io_object_get_superclass;
	__Request__io_object_get_bundle_identifier_t Request_io_object_get_bundle_identifier;
	__Request__io_service_open_extended_t Request_io_service_open_extended;
};
#endif /* !__RequestUnion__iokit_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__iokit_subsystem__defined
#define __Reply__iokit_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
		mach_msg_type_number_t classNameOffset; /* MiG doesn't use it */
		mach_msg_type_number_t classNameCnt;
		char className[128];
	} __Reply__io_object_get_class_t;
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
		boolean_t conforms;
	} __Reply__io_object_conforms_to_t;
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
		mach_msg_port_descriptor_t object;
		/* end of the kernel processed data */
	} __Reply__io_iterator_next_t;
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
	} __Reply__io_iterator_reset_t;
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
		mach_msg_port_descriptor_t existing;
		/* end of the kernel processed data */
	} __Reply__io_service_get_matching_services_t;
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
		mach_msg_ool_descriptor_t properties;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t propertiesCnt;
	} __Reply__io_registry_entry_get_property_t;
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
		mach_msg_port_descriptor_t iterator;
		/* end of the kernel processed data */
	} __Reply__io_registry_create_iterator_t;
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
	} __Reply__io_registry_iterator_enter_entry_t;
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
	} __Reply__io_registry_iterator_exit_entry_t;
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
		mach_msg_port_descriptor_t registry_entry;
		/* end of the kernel processed data */
	} __Reply__io_registry_entry_from_path_t;
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
		mach_msg_type_number_t nameOffset; /* MiG doesn't use it */
		mach_msg_type_number_t nameCnt;
		char name[128];
	} __Reply__io_registry_entry_get_name_t;
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
		mach_msg_ool_descriptor_t properties;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t propertiesCnt;
	} __Reply__io_registry_entry_get_properties_t;
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
		mach_msg_type_number_t dataCnt;
		char data[4096];
	} __Reply__io_registry_entry_get_property_bytes_t;
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
		mach_msg_port_descriptor_t iterator;
		/* end of the kernel processed data */
	} __Reply__io_registry_entry_get_child_iterator_t;
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
		mach_msg_port_descriptor_t iterator;
		/* end of the kernel processed data */
	} __Reply__io_registry_entry_get_parent_iterator_t;
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
		mach_msg_port_descriptor_t connection;
		/* end of the kernel processed data */
	} __Reply__io_service_open_t;
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
	} __Reply__io_service_close_t;
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
		mach_msg_port_descriptor_t service;
		/* end of the kernel processed data */
	} __Reply__io_connect_get_service_t;
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
	} __Reply__io_connect_set_notification_port_t;
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
		vm_address_t address;
		vm_size_t size;
	} __Reply__io_connect_map_memory_t;
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
	} __Reply__io_connect_add_client_t;
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
		natural_t result;
	} __Reply__io_connect_set_properties_t;
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
		mach_msg_type_number_t outputCnt;
		int output[16];
	} __Reply__io_connect_method_scalarI_scalarO_t;
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
		mach_msg_type_number_t outputCnt;
		char output[4096];
	} __Reply__io_connect_method_scalarI_structureO_t;
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
	} __Reply__io_connect_method_scalarI_structureI_t;
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
		mach_msg_type_number_t outputCnt;
		char output[4096];
	} __Reply__io_connect_method_structureI_structureO_t;
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
		mach_msg_type_number_t pathOffset; /* MiG doesn't use it */
		mach_msg_type_number_t pathCnt;
		char path[512];
	} __Reply__io_registry_entry_get_path_t;
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
		mach_msg_port_descriptor_t root;
		/* end of the kernel processed data */
	} __Reply__io_registry_get_root_entry_t;
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
		natural_t result;
	} __Reply__io_registry_entry_set_properties_t;
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
		boolean_t inPlane;
	} __Reply__io_registry_entry_in_plane_t;
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
		int retainCount;
	} __Reply__io_object_get_retain_count_t;
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
		int busyState;
	} __Reply__io_service_get_busy_state_t;
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
	} __Reply__io_service_wait_quiet_t;
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
		mach_msg_port_descriptor_t iterator;
		/* end of the kernel processed data */
	} __Reply__io_registry_entry_create_iterator_t;
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
		boolean_t is_valid;
	} __Reply__io_iterator_is_valid_t;
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
		mach_msg_type_number_t matchingOffset; /* MiG doesn't use it */
		mach_msg_type_number_t matchingCnt;
		char matching[512];
	} __Reply__io_make_matching_t;
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
		natural_t result;
	} __Reply__io_catalog_send_data_t;
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
	} __Reply__io_catalog_terminate_t;
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
		mach_msg_ool_descriptor_t outData;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t outDataCnt;
	} __Reply__io_catalog_get_data_t;
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
		int genCount;
	} __Reply__io_catalog_get_gen_count_t;
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
	} __Reply__io_catalog_module_loaded_t;
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
	} __Reply__io_catalog_reset_t;
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
	} __Reply__io_service_request_probe_t;
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
		mach_msg_type_number_t nameOffset; /* MiG doesn't use it */
		mach_msg_type_number_t nameCnt;
		char name[128];
	} __Reply__io_registry_entry_get_name_in_plane_t;
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
		boolean_t matches;
	} __Reply__io_service_match_property_table_t;
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
		mach_msg_type_number_t outputCnt;
		int output[16];
	} __Reply__io_async_method_scalarI_scalarO_t;
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
		mach_msg_type_number_t outputCnt;
		char output[4096];
	} __Reply__io_async_method_scalarI_structureO_t;
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
	} __Reply__io_async_method_scalarI_structureI_t;
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
		mach_msg_type_number_t outputCnt;
		char output[4096];
	} __Reply__io_async_method_structureI_structureO_t;
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
		mach_msg_port_descriptor_t notification;
		/* end of the kernel processed data */
	} __Reply__io_service_add_notification_t;
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
		mach_msg_port_descriptor_t notification;
		/* end of the kernel processed data */
	} __Reply__io_service_add_interest_notification_t;
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
	} __Reply__io_service_acknowledge_notification_t;
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
		mach_msg_port_descriptor_t semaphore;
		/* end of the kernel processed data */
	} __Reply__io_connect_get_notification_semaphore_t;
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
	} __Reply__io_connect_unmap_memory_t;
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
		mach_msg_type_number_t locationOffset; /* MiG doesn't use it */
		mach_msg_type_number_t locationCnt;
		char location[128];
	} __Reply__io_registry_entry_get_location_in_plane_t;
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
		mach_msg_ool_descriptor_t properties;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t propertiesCnt;
	} __Reply__io_registry_entry_get_property_recursively_t;
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
		uint64_t state;
	} __Reply__io_service_get_state_t;
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
		mach_msg_port_descriptor_t existing;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		natural_t result;
	} __Reply__io_service_get_matching_services_ool_t;
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
		natural_t result;
		boolean_t matches;
	} __Reply__io_service_match_property_table_ool_t;
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
		mach_msg_port_descriptor_t notification;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		natural_t result;
	} __Reply__io_service_add_notification_ool_t;
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
		mach_msg_type_number_t class_nameOffset; /* MiG doesn't use it */
		mach_msg_type_number_t class_nameCnt;
		char class_name[128];
	} __Reply__io_object_get_superclass_t;
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
		mach_msg_type_number_t class_nameOffset; /* MiG doesn't use it */
		mach_msg_type_number_t class_nameCnt;
		char class_name[128];
	} __Reply__io_object_get_bundle_identifier_t;
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
		mach_msg_port_descriptor_t connection;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		natural_t result;
	} __Reply__io_service_open_extended_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Reply__iokit_subsystem__defined */

/* union of all replies */

#ifndef __ReplyUnion__iokit_subsystem__defined
#define __ReplyUnion__iokit_subsystem__defined
union __ReplyUnion__iokit_subsystem {
	__Reply__io_object_get_class_t Reply_io_object_get_class;
	__Reply__io_object_conforms_to_t Reply_io_object_conforms_to;
	__Reply__io_iterator_next_t Reply_io_iterator_next;
	__Reply__io_iterator_reset_t Reply_io_iterator_reset;
	__Reply__io_service_get_matching_services_t Reply_io_service_get_matching_services;
	__Reply__io_registry_entry_get_property_t Reply_io_registry_entry_get_property;
	__Reply__io_registry_create_iterator_t Reply_io_registry_create_iterator;
	__Reply__io_registry_iterator_enter_entry_t Reply_io_registry_iterator_enter_entry;
	__Reply__io_registry_iterator_exit_entry_t Reply_io_registry_iterator_exit_entry;
	__Reply__io_registry_entry_from_path_t Reply_io_registry_entry_from_path;
	__Reply__io_registry_entry_get_name_t Reply_io_registry_entry_get_name;
	__Reply__io_registry_entry_get_properties_t Reply_io_registry_entry_get_properties;
	__Reply__io_registry_entry_get_property_bytes_t Reply_io_registry_entry_get_property_bytes;
	__Reply__io_registry_entry_get_child_iterator_t Reply_io_registry_entry_get_child_iterator;
	__Reply__io_registry_entry_get_parent_iterator_t Reply_io_registry_entry_get_parent_iterator;
	__Reply__io_service_open_t Reply_io_service_open;
	__Reply__io_service_close_t Reply_io_service_close;
	__Reply__io_connect_get_service_t Reply_io_connect_get_service;
	__Reply__io_connect_set_notification_port_t Reply_io_connect_set_notification_port;
	__Reply__io_connect_map_memory_t Reply_io_connect_map_memory;
	__Reply__io_connect_add_client_t Reply_io_connect_add_client;
	__Reply__io_connect_set_properties_t Reply_io_connect_set_properties;
	__Reply__io_connect_method_scalarI_scalarO_t Reply_io_connect_method_scalarI_scalarO;
	__Reply__io_connect_method_scalarI_structureO_t Reply_io_connect_method_scalarI_structureO;
	__Reply__io_connect_method_scalarI_structureI_t Reply_io_connect_method_scalarI_structureI;
	__Reply__io_connect_method_structureI_structureO_t Reply_io_connect_method_structureI_structureO;
	__Reply__io_registry_entry_get_path_t Reply_io_registry_entry_get_path;
	__Reply__io_registry_get_root_entry_t Reply_io_registry_get_root_entry;
	__Reply__io_registry_entry_set_properties_t Reply_io_registry_entry_set_properties;
	__Reply__io_registry_entry_in_plane_t Reply_io_registry_entry_in_plane;
	__Reply__io_object_get_retain_count_t Reply_io_object_get_retain_count;
	__Reply__io_service_get_busy_state_t Reply_io_service_get_busy_state;
	__Reply__io_service_wait_quiet_t Reply_io_service_wait_quiet;
	__Reply__io_registry_entry_create_iterator_t Reply_io_registry_entry_create_iterator;
	__Reply__io_iterator_is_valid_t Reply_io_iterator_is_valid;
	__Reply__io_make_matching_t Reply_io_make_matching;
	__Reply__io_catalog_send_data_t Reply_io_catalog_send_data;
	__Reply__io_catalog_terminate_t Reply_io_catalog_terminate;
	__Reply__io_catalog_get_data_t Reply_io_catalog_get_data;
	__Reply__io_catalog_get_gen_count_t Reply_io_catalog_get_gen_count;
	__Reply__io_catalog_module_loaded_t Reply_io_catalog_module_loaded;
	__Reply__io_catalog_reset_t Reply_io_catalog_reset;
	__Reply__io_service_request_probe_t Reply_io_service_request_probe;
	__Reply__io_registry_entry_get_name_in_plane_t Reply_io_registry_entry_get_name_in_plane;
	__Reply__io_service_match_property_table_t Reply_io_service_match_property_table;
	__Reply__io_async_method_scalarI_scalarO_t Reply_io_async_method_scalarI_scalarO;
	__Reply__io_async_method_scalarI_structureO_t Reply_io_async_method_scalarI_structureO;
	__Reply__io_async_method_scalarI_structureI_t Reply_io_async_method_scalarI_structureI;
	__Reply__io_async_method_structureI_structureO_t Reply_io_async_method_structureI_structureO;
	__Reply__io_service_add_notification_t Reply_io_service_add_notification;
	__Reply__io_service_add_interest_notification_t Reply_io_service_add_interest_notification;
	__Reply__io_service_acknowledge_notification_t Reply_io_service_acknowledge_notification;
	__Reply__io_connect_get_notification_semaphore_t Reply_io_connect_get_notification_semaphore;
	__Reply__io_connect_unmap_memory_t Reply_io_connect_unmap_memory;
	__Reply__io_registry_entry_get_location_in_plane_t Reply_io_registry_entry_get_location_in_plane;
	__Reply__io_registry_entry_get_property_recursively_t Reply_io_registry_entry_get_property_recursively;
	__Reply__io_service_get_state_t Reply_io_service_get_state;
	__Reply__io_service_get_matching_services_ool_t Reply_io_service_get_matching_services_ool;
	__Reply__io_service_match_property_table_ool_t Reply_io_service_match_property_table_ool;
	__Reply__io_service_add_notification_ool_t Reply_io_service_add_notification_ool;
	__Reply__io_object_get_superclass_t Reply_io_object_get_superclass;
	__Reply__io_object_get_bundle_identifier_t Reply_io_object_get_bundle_identifier;
	__Reply__io_service_open_extended_t Reply_io_service_open_extended;
};
#endif /* !__RequestUnion__iokit_subsystem__defined */

#ifndef subsystem_to_name_map_iokit
#define subsystem_to_name_map_iokit \
    { "io_object_get_class", 2800 },\
    { "io_object_conforms_to", 2801 },\
    { "io_iterator_next", 2802 },\
    { "io_iterator_reset", 2803 },\
    { "io_service_get_matching_services", 2804 },\
    { "io_registry_entry_get_property", 2805 },\
    { "io_registry_create_iterator", 2806 },\
    { "io_registry_iterator_enter_entry", 2807 },\
    { "io_registry_iterator_exit_entry", 2808 },\
    { "io_registry_entry_from_path", 2809 },\
    { "io_registry_entry_get_name", 2810 },\
    { "io_registry_entry_get_properties", 2811 },\
    { "io_registry_entry_get_property_bytes", 2812 },\
    { "io_registry_entry_get_child_iterator", 2813 },\
    { "io_registry_entry_get_parent_iterator", 2814 },\
    { "io_service_open", 2815 },\
    { "io_service_close", 2816 },\
    { "io_connect_get_service", 2817 },\
    { "io_connect_set_notification_port", 2818 },\
    { "io_connect_map_memory", 2819 },\
    { "io_connect_add_client", 2820 },\
    { "io_connect_set_properties", 2821 },\
    { "io_connect_method_scalarI_scalarO", 2822 },\
    { "io_connect_method_scalarI_structureO", 2823 },\
    { "io_connect_method_scalarI_structureI", 2824 },\
    { "io_connect_method_structureI_structureO", 2825 },\
    { "io_registry_entry_get_path", 2826 },\
    { "io_registry_get_root_entry", 2827 },\
    { "io_registry_entry_set_properties", 2828 },\
    { "io_registry_entry_in_plane", 2829 },\
    { "io_object_get_retain_count", 2830 },\
    { "io_service_get_busy_state", 2831 },\
    { "io_service_wait_quiet", 2832 },\
    { "io_registry_entry_create_iterator", 2833 },\
    { "io_iterator_is_valid", 2834 },\
    { "io_make_matching", 2835 },\
    { "io_catalog_send_data", 2836 },\
    { "io_catalog_terminate", 2837 },\
    { "io_catalog_get_data", 2838 },\
    { "io_catalog_get_gen_count", 2839 },\
    { "io_catalog_module_loaded", 2840 },\
    { "io_catalog_reset", 2841 },\
    { "io_service_request_probe", 2842 },\
    { "io_registry_entry_get_name_in_plane", 2843 },\
    { "io_service_match_property_table", 2844 },\
    { "io_async_method_scalarI_scalarO", 2845 },\
    { "io_async_method_scalarI_structureO", 2846 },\
    { "io_async_method_scalarI_structureI", 2847 },\
    { "io_async_method_structureI_structureO", 2848 },\
    { "io_service_add_notification", 2849 },\
    { "io_service_add_interest_notification", 2850 },\
    { "io_service_acknowledge_notification", 2851 },\
    { "io_connect_get_notification_semaphore", 2852 },\
    { "io_connect_unmap_memory", 2853 },\
    { "io_registry_entry_get_location_in_plane", 2854 },\
    { "io_registry_entry_get_property_recursively", 2855 },\
    { "io_service_get_state", 2856 },\
    { "io_service_get_matching_services_ool", 2857 },\
    { "io_service_match_property_table_ool", 2858 },\
    { "io_service_add_notification_ool", 2859 },\
    { "io_object_get_superclass", 2860 },\
    { "io_object_get_bundle_identifier", 2861 },\
    { "io_service_open_extended", 2862 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _iokit_user_ */
