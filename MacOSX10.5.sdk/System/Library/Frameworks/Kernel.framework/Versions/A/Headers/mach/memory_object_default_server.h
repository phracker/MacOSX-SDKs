#ifndef	_memory_object_default_server_
#define	_memory_object_default_server_

/* Module memory_object_default */

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

#ifndef	memory_object_default_MSG_COUNT
#define	memory_object_default_MSG_COUNT	1
#endif	/* memory_object_default_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mig.h>
#include <mach/mig.h>
#include <mach/mach_types.h>

#ifdef __BeforeMigServerHeader
__BeforeMigServerHeader
#endif /* __BeforeMigServerHeader */


/* Routine memory_object_create */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t memory_object_create
(
	memory_object_default_t default_memory_manager,
	vm_size_t new_memory_object_size,
	memory_object_t *new_memory_object
);

extern boolean_t memory_object_default_server(
		mach_msg_header_t *InHeadP,
		mach_msg_header_t *OutHeadP);

extern mig_routine_t memory_object_default_server_routine(
		mach_msg_header_t *InHeadP);


/* Description of this subsystem, for use in direct RPC */
extern const struct memory_object_default_subsystem {
	mig_server_routine_t	server;	/* Server routine */
	mach_msg_id_t	start;	/* Min routine number */
	mach_msg_id_t	end;	/* Max routine number + 1 */
	unsigned int	maxsize;	/* Max msg size */
	vm_address_t	reserved;	/* Reserved */
	struct routine_descriptor	/*Array of routine descriptors */
		routine[1];
} memory_object_default_subsystem;

/* typedefs for all requests */

#ifndef __Request__memory_object_default_subsystem__defined
#define __Request__memory_object_default_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		vm_size_t new_memory_object_size;
	} __Request__memory_object_create_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Request__memory_object_default_subsystem__defined */


/* union of all requests */

#ifndef __RequestUnion__memory_object_default_subsystem__defined
#define __RequestUnion__memory_object_default_subsystem__defined
union __RequestUnion__memory_object_default_subsystem {
	__Request__memory_object_create_t Request_memory_object_create;
};
#endif /* __RequestUnion__memory_object_default_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__memory_object_default_subsystem__defined
#define __Reply__memory_object_default_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t new_memory_object;
		/* end of the kernel processed data */
	} __Reply__memory_object_create_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Reply__memory_object_default_subsystem__defined */


/* union of all replies */

#ifndef __ReplyUnion__memory_object_default_subsystem__defined
#define __ReplyUnion__memory_object_default_subsystem__defined
union __ReplyUnion__memory_object_default_subsystem {
	__Reply__memory_object_create_t Reply_memory_object_create;
};
#endif /* __RequestUnion__memory_object_default_subsystem__defined */

#ifndef subsystem_to_name_map_memory_object_default
#define subsystem_to_name_map_memory_object_default \
    { "memory_object_create", 2250 }
#endif

#ifdef __AfterMigServerHeader
__AfterMigServerHeader
#endif /* __AfterMigServerHeader */

#endif	 /* _memory_object_default_server_ */
