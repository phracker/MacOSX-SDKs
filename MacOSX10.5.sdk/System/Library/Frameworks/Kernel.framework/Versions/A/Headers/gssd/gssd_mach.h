#ifndef	_gssd_mach_user_
#define	_gssd_mach_user_

/* Module gssd_mach */

#include <string.h>
#include <mach/ndr.h>
#include <mach/boolean.h>
#include <mach/kern_return.h>
#include <mach/notify.h>
#include <mach/mach_types.h>
#include <mach/message.h>
#include <mach/mig_errors.h>
#include <mach/port.h>
#if	(__MigKernelSpecificCode) || (_MIG_KERNEL_SPECIFIC_CODE_)
#include <kern/ipc_mig.h>
#endif /* __MigKernelSpecificCode */

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

#ifndef	gssd_mach_MSG_COUNT
#define	gssd_mach_MSG_COUNT	3
#endif	/* gssd_mach_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mig.h>
#include <mach/mig.h>
#include <mach/mach_types.h>
#include <gssd/gssd_mach_types.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */

#include <sys/cdefs.h>
__BEGIN_DECLS


/* Routine mach_gss_init_sec_context */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t mach_gss_init_sec_context
(
	mach_port_t server,
	mechtype mech,
	byte_buffer intoken,
	mach_msg_type_number_t intokenCnt,
	uint32_t uid,
	string_t princ_namestr,
	string_t svc_namestr,
	uint32_t flags,
	gssd_verifier *verifier,
	uint32_t *context,
	uint32_t *cred_handle,
	byte_buffer *key,
	mach_msg_type_number_t *keyCnt,
	byte_buffer *outtoken,
	mach_msg_type_number_t *outtokenCnt,
	uint32_t *major_stat,
	uint32_t *minor_stat
);

/* Routine mach_gss_accept_sec_context */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t mach_gss_accept_sec_context
(
	mach_port_t server,
	byte_buffer intoken,
	mach_msg_type_number_t intokenCnt,
	string_t svc_namestr,
	uint32_t flags,
	gssd_verifier *verifier,
	uint32_t *context,
	uint32_t *cred_handle,
	uint32_t *uid,
	gid_list gids,
	mach_msg_type_number_t *gidsCnt,
	byte_buffer *key,
	mach_msg_type_number_t *keyCnt,
	byte_buffer *outtoken,
	mach_msg_type_number_t *outtokenCnt,
	uint32_t *major_stat,
	uint32_t *minor_stat
);

/* SimpleRoutine mach_gss_log_error */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t mach_gss_log_error
(
	mach_port_t server,
	string_t mnt,
	uint32_t uid,
	string_t source,
	uint32_t major_stat,
	uint32_t minor_stat
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

#ifndef __Request__gssd_mach_subsystem__defined
#define __Request__gssd_mach_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_ool_descriptor_t intoken;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mechtype mech;
		mach_msg_type_number_t intokenCnt;
		uint32_t uid;
		mach_msg_type_number_t princ_namestrOffset; /* MiG doesn't use it */
		mach_msg_type_number_t princ_namestrCnt;
		char princ_namestr[1024];
		mach_msg_type_number_t svc_namestrOffset; /* MiG doesn't use it */
		mach_msg_type_number_t svc_namestrCnt;
		char svc_namestr[1024];
		uint32_t flags;
		gssd_verifier verifier;
		uint32_t context;
		uint32_t cred_handle;
	} __Request__mach_gss_init_sec_context_t;
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
		mach_msg_ool_descriptor_t intoken;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t intokenCnt;
		mach_msg_type_number_t svc_namestrOffset; /* MiG doesn't use it */
		mach_msg_type_number_t svc_namestrCnt;
		char svc_namestr[1024];
		uint32_t flags;
		gssd_verifier verifier;
		uint32_t context;
		uint32_t cred_handle;
	} __Request__mach_gss_accept_sec_context_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t mntOffset; /* MiG doesn't use it */
		mach_msg_type_number_t mntCnt;
		char mnt[1024];
		uint32_t uid;
		mach_msg_type_number_t sourceOffset; /* MiG doesn't use it */
		mach_msg_type_number_t sourceCnt;
		char source[1024];
		uint32_t major_stat;
		uint32_t minor_stat;
	} __Request__mach_gss_log_error_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Request__gssd_mach_subsystem__defined */

/* union of all requests */

#ifndef __RequestUnion__gssd_mach_subsystem__defined
#define __RequestUnion__gssd_mach_subsystem__defined
union __RequestUnion__gssd_mach_subsystem {
	__Request__mach_gss_init_sec_context_t Request_mach_gss_init_sec_context;
	__Request__mach_gss_accept_sec_context_t Request_mach_gss_accept_sec_context;
	__Request__mach_gss_log_error_t Request_mach_gss_log_error;
};
#endif /* !__RequestUnion__gssd_mach_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__gssd_mach_subsystem__defined
#define __Reply__gssd_mach_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_ool_descriptor_t key;
		mach_msg_ool_descriptor_t outtoken;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		gssd_verifier verifier;
		uint32_t context;
		uint32_t cred_handle;
		mach_msg_type_number_t keyCnt;
		mach_msg_type_number_t outtokenCnt;
		uint32_t major_stat;
		uint32_t minor_stat;
	} __Reply__mach_gss_init_sec_context_t;
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
		mach_msg_ool_descriptor_t key;
		mach_msg_ool_descriptor_t outtoken;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		gssd_verifier verifier;
		uint32_t context;
		uint32_t cred_handle;
		uint32_t uid;
		mach_msg_type_number_t gidsCnt;
		uint32_t gids[16];
		mach_msg_type_number_t keyCnt;
		mach_msg_type_number_t outtokenCnt;
		uint32_t major_stat;
		uint32_t minor_stat;
	} __Reply__mach_gss_accept_sec_context_t;
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
	} __Reply__mach_gss_log_error_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Reply__gssd_mach_subsystem__defined */

/* union of all replies */

#ifndef __ReplyUnion__gssd_mach_subsystem__defined
#define __ReplyUnion__gssd_mach_subsystem__defined
union __ReplyUnion__gssd_mach_subsystem {
	__Reply__mach_gss_init_sec_context_t Reply_mach_gss_init_sec_context;
	__Reply__mach_gss_accept_sec_context_t Reply_mach_gss_accept_sec_context;
	__Reply__mach_gss_log_error_t Reply_mach_gss_log_error;
};
#endif /* !__RequestUnion__gssd_mach_subsystem__defined */

#ifndef subsystem_to_name_map_gssd_mach
#define subsystem_to_name_map_gssd_mach \
    { "mach_gss_init_sec_context", 999 },\
    { "mach_gss_accept_sec_context", 1000 },\
    { "mach_gss_log_error", 1001 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _gssd_mach_user_ */
