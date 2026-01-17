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
#define	iokit_MSG_COUNT	56
#endif	/* iokit_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mach_types.h>
#include <mach/mach_types.h>
#include <device/device_types.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */


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
    { "io_registry_entry_get_property_recursively", 2855 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _iokit_user_ */
