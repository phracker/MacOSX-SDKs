#ifndef	_memory_object_name_user_
#define	_memory_object_name_user_

/* Module memory_object_name */

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

#ifndef	memory_object_name_MSG_COUNT
#define	memory_object_name_MSG_COUNT	0
#endif	/* memory_object_name_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mig.h>
#include <mach/mig.h>
#include <mach/mach_types.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */

#include <sys/cdefs.h>
__BEGIN_DECLS


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

#ifndef __Request__memory_object_name_subsystem__defined
#define __Request__memory_object_name_subsystem__defined
#endif /* !__Request__memory_object_name_subsystem__defined */

/* union of all requests */

#ifndef __RequestUnion__memory_object_name_subsystem__defined
#define __RequestUnion__memory_object_name_subsystem__defined
union __RequestUnion__memory_object_name_subsystem {
};
#endif /* !__RequestUnion__memory_object_name_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__memory_object_name_subsystem__defined
#define __Reply__memory_object_name_subsystem__defined
#endif /* !__Reply__memory_object_name_subsystem__defined */

/* union of all replies */

#ifndef __ReplyUnion__memory_object_name_subsystem__defined
#define __ReplyUnion__memory_object_name_subsystem__defined
union __ReplyUnion__memory_object_name_subsystem {
};
#endif /* !__RequestUnion__memory_object_name_subsystem__defined */

#ifndef subsystem_to_name_map_memory_object_name
#define subsystem_to_name_map_memory_object_name \

#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _memory_object_name_user_ */
