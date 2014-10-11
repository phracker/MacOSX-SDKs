#ifndef	_vm_map_user_
#define	_vm_map_user_

/* Module vm_map */

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

#ifndef	vm_map_MSG_COUNT
#define	vm_map_MSG_COUNT	30
#endif	/* vm_map_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mach_types.h>
#include <mach_debug/mach_debug_types.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */


/* Routine vm_region */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_region
(
	vm_map_t target_task,
	vm_address_t *address,
	vm_size_t *size,
	vm_region_flavor_t flavor,
	vm_region_info_t info,
	mach_msg_type_number_t *infoCnt,
	mach_port_t *object_name
);

/* Routine vm_allocate */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_allocate
(
	vm_map_t target_task,
	vm_address_t *address,
	vm_size_t size,
	int flags
);

/* Routine vm_deallocate */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_deallocate
(
	vm_map_t target_task,
	vm_address_t address,
	vm_size_t size
);

/* Routine vm_protect */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_protect
(
	vm_map_t target_task,
	vm_address_t address,
	vm_size_t size,
	boolean_t set_maximum,
	vm_prot_t new_protection
);

/* Routine vm_inherit */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_inherit
(
	vm_map_t target_task,
	vm_address_t address,
	vm_size_t size,
	vm_inherit_t new_inheritance
);

/* Routine vm_read */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_read
(
	vm_map_t target_task,
	vm_address_t address,
	vm_size_t size,
	vm_offset_t *data,
	mach_msg_type_number_t *dataCnt
);

/* Routine vm_read_list */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_read_list
(
	vm_map_t target_task,
	vm_read_entry_t data_list,
	natural_t count
);

/* Routine vm_write */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_write
(
	vm_map_t target_task,
	vm_address_t address,
	vm_offset_t data,
	mach_msg_type_number_t dataCnt
);

/* Routine vm_copy */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_copy
(
	vm_map_t target_task,
	vm_address_t source_address,
	vm_size_t size,
	vm_address_t dest_address
);

/* Routine vm_read_overwrite */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_read_overwrite
(
	vm_map_t target_task,
	vm_address_t address,
	vm_size_t size,
	vm_address_t data,
	vm_size_t *outsize
);

/* Routine vm_msync */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_msync
(
	vm_map_t target_task,
	vm_address_t address,
	vm_size_t size,
	vm_sync_t sync_flags
);

/* Routine vm_behavior_set */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_behavior_set
(
	vm_map_t target_task,
	vm_address_t address,
	vm_size_t size,
	vm_behavior_t new_behavior
);

/* Routine vm_map */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_map
(
	vm_map_t target_task,
	vm_address_t *address,
	vm_size_t size,
	vm_address_t mask,
	int flags,
	mem_entry_name_port_t object,
	vm_offset_t offset,
	boolean_t copy,
	vm_prot_t cur_protection,
	vm_prot_t max_protection,
	vm_inherit_t inheritance
);

/* Routine vm_machine_attribute */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_machine_attribute
(
	vm_map_t target_task,
	vm_address_t address,
	vm_size_t size,
	vm_machine_attribute_t attribute,
	vm_machine_attribute_val_t *value
);

/* Routine vm_remap */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_remap
(
	vm_map_t target_task,
	vm_address_t *target_address,
	vm_size_t size,
	vm_address_t mask,
	boolean_t anywhere,
	vm_map_t src_task,
	vm_address_t src_address,
	boolean_t copy,
	vm_prot_t *cur_protection,
	vm_prot_t *max_protection,
	vm_inherit_t inheritance
);

/* Routine task_wire */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t task_wire
(
	vm_map_t target_task,
	boolean_t must_wire
);

/* Routine mach_make_memory_entry */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t mach_make_memory_entry
(
	vm_map_t target_task,
	vm_size_t *size,
	vm_offset_t offset,
	vm_prot_t permission,
	mach_port_t *object_handle,
	mem_entry_name_port_t parent_entry
);

/* Routine vm_map_page_query */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_map_page_query
(
	vm_map_t target_map,
	vm_offset_t offset,
	integer_t *disposition,
	integer_t *ref_count
);

/* Routine mach_vm_region_info */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t mach_vm_region_info
(
	vm_map_t task,
	vm_address_t address,
	vm_info_region_t *region,
	vm_info_object_array_t *objects,
	mach_msg_type_number_t *objectsCnt
);

/* Routine vm_mapped_pages_info */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_mapped_pages_info
(
	vm_map_t task,
	page_address_array_t *pages,
	mach_msg_type_number_t *pagesCnt
);

/* Routine vm_region_object_create */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_region_object_create
(
	vm_map_t target_task,
	vm_size_t size,
	mach_port_t *region_object
);

/* Routine vm_region_recurse */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_region_recurse
(
	vm_map_t target_task,
	vm_address_t *address,
	vm_size_t *size,
	natural_t *nesting_depth,
	vm_region_recurse_info_t info,
	mach_msg_type_number_t *infoCnt
);

/* Routine vm_region_recurse_64 */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_region_recurse_64
(
	vm_map_t target_task,
	vm_address_t *address,
	vm_size_t *size,
	natural_t *nesting_depth,
	vm_region_recurse_info_64_t info,
	mach_msg_type_number_t *infoCnt
);

/* Routine mach_vm_region_info_64 */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t mach_vm_region_info_64
(
	vm_map_t task,
	vm_address_t address,
	vm_info_region_64_t *region,
	vm_info_object_array_t *objects,
	mach_msg_type_number_t *objectsCnt
);

/* Routine vm_region_64 */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_region_64
(
	vm_map_t target_task,
	vm_address_t *address,
	vm_size_t *size,
	vm_region_flavor_t flavor,
	vm_region_info_64_t info,
	mach_msg_type_number_t *infoCnt,
	mach_port_t *object_name
);

/* Routine mach_make_memory_entry_64 */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t mach_make_memory_entry_64
(
	vm_map_t target_task,
	memory_object_size_t *size,
	memory_object_offset_t offset,
	vm_prot_t permission,
	mach_port_t *object_handle,
	mem_entry_name_port_t parent_entry
);

/* Routine vm_map_64 */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_map_64
(
	vm_map_t target_task,
	vm_address_t *address,
	vm_size_t size,
	vm_address_t mask,
	int flags,
	mem_entry_name_port_t object,
	memory_object_offset_t offset,
	boolean_t copy,
	vm_prot_t cur_protection,
	vm_prot_t max_protection,
	vm_inherit_t inheritance
);

/* Routine vm_map_get_upl */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_map_get_upl
(
	vm_map_t target_task,
	vm_address_t address,
	vm_size_t *size,
	upl_t *upl,
	upl_page_info_array_t page_info,
	mach_msg_type_number_t *page_infoCnt,
	integer_t *flags,
	integer_t force_data_sync
);

/* Routine vm_upl_map */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_upl_map
(
	vm_map_t target_task,
	upl_t upl,
	vm_address_t *address
);

/* Routine vm_upl_unmap */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t vm_upl_unmap
(
	vm_map_t target_task,
	upl_t upl
);

#ifndef subsystem_to_name_map_vm_map
#define subsystem_to_name_map_vm_map \
    { "vm_region", 3800 },\
    { "vm_allocate", 3801 },\
    { "vm_deallocate", 3802 },\
    { "vm_protect", 3803 },\
    { "vm_inherit", 3804 },\
    { "vm_read", 3805 },\
    { "vm_read_list", 3806 },\
    { "vm_write", 3807 },\
    { "vm_copy", 3808 },\
    { "vm_read_overwrite", 3809 },\
    { "vm_msync", 3810 },\
    { "vm_behavior_set", 3811 },\
    { "vm_map", 3812 },\
    { "vm_machine_attribute", 3813 },\
    { "vm_remap", 3814 },\
    { "task_wire", 3815 },\
    { "mach_make_memory_entry", 3816 },\
    { "vm_map_page_query", 3817 },\
    { "mach_vm_region_info", 3818 },\
    { "vm_mapped_pages_info", 3819 },\
    { "vm_region_object_create", 3820 },\
    { "vm_region_recurse", 3821 },\
    { "vm_region_recurse_64", 3822 },\
    { "mach_vm_region_info_64", 3823 },\
    { "vm_region_64", 3824 },\
    { "mach_make_memory_entry_64", 3825 },\
    { "vm_map_64", 3826 },\
    { "vm_map_get_upl", 3827 },\
    { "vm_upl_map", 3828 },\
    { "vm_upl_unmap", 3829 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _vm_map_user_ */
