/*
 * $Header$
 *
 * Copyright 1998-2006 Massachusetts Institute of Technology.
 * All Rights Reserved.
 *
 * Export of this software from the United States of America may
 * require a specific license from the United States Government.
 * It is the responsibility of any person or organization contemplating
 * export to obtain such a license before exporting.
 *
 * WITHIN THAT CONSTRAINT, permission to use, copy, modify, and
 * distribute this software and its documentation for any purpose and
 * without fee is hereby granted, provided that the above copyright
 * notice appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation, and that
 * the name of M.I.T. not be used in advertising or publicity pertaining
 * to distribution of the software without specific, written prior
 * permission.  Furthermore if you modify this software you must label
 * your software as modified software and not distribute it in such a
 * fashion that it might be confused with the original M.I.T. software.
 * M.I.T. makes no representations about the suitability of
 * this software for any purpose.  It is provided "as is" without express
 * or implied warranty.
 */
 
#ifndef __CREDENTIALSCACHE__
#define __CREDENTIALSCACHE__

#if defined(macintosh) || (defined(__MACH__) && defined(__APPLE__))
#include <TargetConditionals.h>
#endif

#if defined(_WIN32)
#include <winsock.h>
#else
#include <sys/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if TARGET_OS_MAC
#pragma pack(push,2)
#endif    

#if defined(_WIN32)
#define CCACHE_API 	__declspec(dllexport)

#if _INTEGRAL_MAX_BITS >= 64 && _MSC_VER >= 1400 && !defined(_WIN64) && !defined(_USE_32BIT_TIME_T)
#if defined(_TIME_T_DEFINED) || defined(_INC_IO) || defined(_INC_TIME) || defined(_INC_WCHAR)
#error time_t has been defined as a 64-bit integer which is incompatible with Kerberos on this platform.
#endif /* _TIME_T_DEFINED */
#define _USE_32BIT_TIME_T
#endif 
#else
#define CCACHE_API
#endif

#include <time.h>

/*
 * Constants
 */
 
/* API versions */
enum {
    ccapi_version_2 = 2,
    ccapi_version_3 = 3,
    ccapi_version_4 = 4,
    ccapi_version_5 = 5,
    ccapi_version_6 = 6,
    ccapi_version_max = ccapi_version_6
};
 
/* Errors */
enum {
    ccNoError						= 0,

    ccIteratorEnd					= 201,
    ccErrBadParam,
    ccErrNoMem,
    ccErrInvalidContext,
    ccErrInvalidCCache,

    ccErrInvalidString,					/* 206 */
    ccErrInvalidCredentials,
    ccErrInvalidCCacheIterator,
    ccErrInvalidCredentialsIterator,
    ccErrInvalidLock,

    ccErrBadName,					/* 211 */
    ccErrBadCredentialsVersion,
    ccErrBadAPIVersion,
    ccErrContextLocked,
    ccErrContextUnlocked,

    ccErrCCacheLocked,					/* 216 */
    ccErrCCacheUnlocked,
    ccErrBadLockType,
    ccErrNeverDefault,
    ccErrCredentialsNotFound,

    ccErrCCacheNotFound,				/* 221 */
    ccErrContextNotFound,
    ccErrServerUnavailable,
    ccErrServerInsecure,
    ccErrServerCantBecomeUID,
    
    ccErrTimeOffsetNotSet,				/* 226 */
    ccErrBadInternalMessage,
    ccErrNotImplemented
};

/* Credentials versions */
enum cc_credential_versions {
    cc_credentials_v4 = 1,
    cc_credentials_v5 = 2,
    cc_credentials_v4_v5 = 3
};

/* Lock types */
enum cc_lock_types {
    cc_lock_read = 0,
    cc_lock_write = 1,
    cc_lock_upgrade = 2,
    cc_lock_downgrade = 3
};

/* Locking Modes */
enum cc_lock_modes {
    cc_lock_noblock = 0,
    cc_lock_block = 1
};

/* Basic types */
 
typedef u_int32_t           cc_uint32;
typedef int32_t             cc_int32;
#if defined (WIN32)
typedef __int64             cc_int64;
typedef unsigned __int64    cc_uint64;
#else
typedef int64_t             cc_int64;
typedef u_int64_t           cc_uint64;
#endif
typedef cc_uint32           cc_time_t;

/* API types */
 
/* Forward declarations */
struct cc_context_f;
typedef struct cc_context_f cc_context_f;

struct cc_ccache_f;
typedef struct cc_ccache_f cc_ccache_f;

struct cc_ccache_iterator_f;
typedef struct cc_ccache_iterator_f cc_ccache_iterator_f;

struct cc_ccache_iterator_f;
typedef struct cc_credentials_iterator_f cc_credentials_iterator_f;

struct cc_string_f;
typedef struct cc_string_f cc_string_f;

struct cc_credentials_f;
typedef struct cc_credentials_f cc_credentials_f;

/* Credentials types */

enum {	/* Make sure all of these are multiples of four (for alignment sanity) */
    cc_v4_name_size     = 40,
    cc_v4_instance_size	= 40,
    cc_v4_realm_size    = 40,
    cc_v4_ticket_size   = 1254,
    cc_v4_key_size      = 8
};

enum cc_string_to_key_type {
    cc_v4_stk_afs = 0,
    cc_v4_stk_des = 1,
    cc_v4_stk_columbia_special = 2,
    cc_v4_stk_krb5 = 3,
    cc_v4_stk_unknown = 4
};

struct cc_credentials_v4_t {
    cc_uint32       version;
    char            principal [cc_v4_name_size];
    char            principal_instance [cc_v4_instance_size];
    char            service [cc_v4_name_size];
    char            service_instance [cc_v4_instance_size];
    char            realm [cc_v4_realm_size];
    unsigned char   session_key [cc_v4_key_size];
    cc_int32        kvno;
    cc_int32        string_to_key_type;
    cc_time_t       issue_date;
    cc_int32        lifetime;
    cc_uint32       address;
    cc_int32        ticket_size;
    unsigned char   ticket [cc_v4_ticket_size];
};      
typedef struct cc_credentials_v4_t cc_credentials_v4_t;

struct cc_data {
    cc_uint32			type;
    cc_uint32			length;
    void*			data;
};      
typedef struct cc_data cc_data;

struct cc_credentials_v5_t {
    char*      client;
    char*      server;
    cc_data    keyblock;
    cc_time_t  authtime;
    cc_time_t  starttime;
    cc_time_t  endtime;
    cc_time_t  renew_till;
    cc_uint32  is_skey;
    cc_uint32  ticket_flags;
    cc_data**  addresses;
    cc_data    ticket;
    cc_data    second_ticket;
    cc_data**  authdata;
};      
typedef struct cc_credentials_v5_t cc_credentials_v5_t;

struct cc_credentials_union {
    cc_uint32			version;
    union {
        cc_credentials_v4_t*	credentials_v4;
        cc_credentials_v5_t*	credentials_v5;
    }				credentials;
};
typedef struct cc_credentials_union cc_credentials_union;

/* Exposed parts */

struct cc_context_d {
    const cc_context_f *functions;
#if TARGET_OS_MAC
    const cc_context_f *vector_functions;
#endif
};
typedef struct cc_context_d cc_context_d;
typedef cc_context_d *cc_context_t;

struct cc_ccache_d {
    const cc_ccache_f *functions;
#if TARGET_OS_MAC
    const cc_ccache_f *vector_functions;
#endif
};
typedef struct cc_ccache_d cc_ccache_d;
typedef cc_ccache_d *cc_ccache_t;

struct cc_ccache_iterator_d {
    const cc_ccache_iterator_f *functions;
#if TARGET_OS_MAC
    const cc_ccache_iterator_f *vector_functions;
#endif
};
typedef struct cc_ccache_iterator_d cc_ccache_iterator_d;
typedef cc_ccache_iterator_d *cc_ccache_iterator_t;

struct cc_credentials_iterator_d {
    const cc_credentials_iterator_f *functions;
#if TARGET_OS_MAC
    const cc_credentials_iterator_f *vector_functions;
#endif
};
typedef struct cc_credentials_iterator_d cc_credentials_iterator_d;
typedef cc_credentials_iterator_d *cc_credentials_iterator_t;

struct cc_string_d {
    const char *data;
    const cc_string_f *functions;
#if TARGET_OS_MAC
    const cc_string_f *vector_functions;
#endif
};
typedef struct cc_string_d cc_string_d;
typedef cc_string_d *cc_string_t;

struct cc_credentials_d {
    const cc_credentials_union *data;
    const cc_credentials_f *functions;
#if TARGET_OS_MAC
    const cc_credentials_f *otherFunctions;
#endif
};
typedef struct cc_credentials_d cc_credentials_d;
typedef cc_credentials_d *cc_credentials_t;

/* Function pointer structs */

struct  cc_context_f {
    cc_int32 (*release) (cc_context_t in_context);
    
    cc_int32 (*get_change_time) (cc_context_t  in_context,
                                 cc_time_t    *out_time);
    
    cc_int32 (*get_default_ccache_name) (cc_context_t  in_context,
                                         cc_string_t  *out_name);
    
    cc_int32 (*open_ccache) (cc_context_t  in_context,
                             const char   *in_name,
                             cc_ccache_t  *out_ccache);
    
    cc_int32 (*open_default_ccache) (cc_context_t  in_context,
                                     cc_ccache_t  *out_ccache);
    
    cc_int32 (*create_ccache) (cc_context_t  in_context,
                               const char   *in_name,
                               cc_uint32     in_cred_vers,
                               const char   *in_principal, 
                               cc_ccache_t  *out_ccache);
    
    cc_int32 (*create_default_ccache) (cc_context_t  in_context,
                                       cc_uint32     in_cred_vers,
                                       const char   *in_principal, 
                                       cc_ccache_t  *out_ccache);
    
    cc_int32 (*create_new_ccache) (cc_context_t in_context,
                                   cc_uint32    in_cred_vers,
                                   const char  *in_principal, 
                                   cc_ccache_t *out_ccache);
    
    cc_int32 (*new_ccache_iterator) (cc_context_t          in_context,
                                     cc_ccache_iterator_t *out_iterator);
    
    cc_int32 (*lock) (cc_context_t in_context,
                      cc_uint32    in_lock_type,
                      cc_uint32    in_block);
    
    cc_int32 (*unlock) (cc_context_t in_cc_context);
    
    cc_int32 (*compare) (cc_context_t  in_cc_context,
                         cc_context_t  in_compare_to_context,
                         cc_uint32    *out_equal);
};

struct cc_ccache_f {
    cc_int32 (*release) (cc_ccache_t io_ccache);
    
    cc_int32 (*destroy) (cc_ccache_t io_ccache);
    
    cc_int32 (*set_default) (cc_ccache_t io_ccache);
    
    cc_int32 (*get_credentials_version) (cc_ccache_t  in_ccache,
                                         cc_uint32   *out_credentials_version);
    
    cc_int32 (*get_name) (cc_ccache_t  in_ccache,
                          cc_string_t *out_name);
    
    cc_int32 (*get_principal) (cc_ccache_t  in_ccache,
                               cc_uint32    in_credentials_version,
                               cc_string_t *out_principal);
    
    cc_int32 (*set_principal) (cc_ccache_t  io_ccache,
                               cc_uint32    in_credentials_version,
                               const char  *in_principal);
    
    cc_int32 (*store_credentials) (cc_ccache_t                 io_ccache,
                                   const cc_credentials_union *in_credentials_union);
    
    cc_int32 (*remove_credentials) (cc_ccache_t      io_ccache,
                                    cc_credentials_t in_credentials);
    
    cc_int32 (*new_credentials_iterator) (cc_ccache_t                in_ccache,
                                          cc_credentials_iterator_t *out_credentials_iterator);
    
    cc_int32 (*move) (cc_ccache_t io_source_ccache,
                      cc_ccache_t io_destination_ccache);
    
    cc_int32 (*lock) (cc_ccache_t io_ccache,
                      cc_uint32   in_lock_type,
                      cc_uint32   in_block);
    
    cc_int32 (*unlock) (cc_ccache_t io_ccache);
    
    cc_int32 (*get_last_default_time) (cc_ccache_t  in_ccache,
                                       cc_time_t   *out_last_default_time);
    
    cc_int32 (*get_change_time) (cc_ccache_t  in_ccache,
                                 cc_time_t   *out_change_time);
    
    cc_int32 (*compare) (cc_ccache_t  in_ccache,
                         cc_ccache_t  in_compare_to_ccache,
                         cc_uint32   *out_equal);
    
    cc_int32 (*get_kdc_time_offset) (cc_ccache_t  in_ccache,
                                     cc_uint32    in_credentials_version,
                                     cc_time_t   *out_time_offset);
    
    cc_int32 (*set_kdc_time_offset) (cc_ccache_t io_ccache,
                                     cc_uint32   in_credentials_version,
                                     cc_time_t   in_time_offset);
    
    cc_int32 (*clear_kdc_time_offset) (cc_ccache_t io_ccache,
                                       cc_uint32   in_credentials_version);
};

struct cc_string_f {
    cc_int32 (*release) (cc_string_t in_string);
};

struct cc_credentials_f {
    cc_int32 (*release) (cc_credentials_t  io_credentials);
    
    cc_int32 (*compare) (cc_credentials_t  in_credentials,
                         cc_credentials_t  in_compare_to_credentials,
                         cc_uint32        *out_equal);
};


struct cc_ccache_iterator_f {
    cc_int32 (*release) (cc_ccache_iterator_t io_ccache_iterator);
    
    cc_int32 (*next) (cc_ccache_iterator_t  in_ccache_iterator,
                      cc_ccache_t          *out_ccache);
    
    cc_int32 (*clone) (cc_ccache_iterator_t  in_ccache_iterator,
                       cc_ccache_iterator_t *out_ccache_iterator);
};

struct cc_credentials_iterator_f {
    cc_int32 (*release) (cc_credentials_iterator_t io_credentials_iterator);
    
    cc_int32 (*next) (cc_credentials_iterator_t  in_credentials_iterator,
                      cc_credentials_t          *out_credentials);
    
    cc_int32 (*clone) (cc_credentials_iterator_t  in_credentials_iterator,
                       cc_credentials_iterator_t *out_credentials_iterator);
};

/* API functions */

CCACHE_API cc_int32 cc_initialize (cc_context_t  *out_context,
                                   cc_int32       in_version,
                                   cc_int32      *out_supported_version,
                                   char const   **out_vendor);
	
/* Convenience macros */
 
#define		cc_context_release(context) \
			((context) -> functions -> release (context))
#define		cc_context_get_change_time(context, change_time) \
			((context) -> functions -> get_change_time (context, change_time))
#define		cc_context_get_default_ccache_name(context, name) \
			((context) -> functions -> get_default_ccache_name (context, name))
#define		cc_context_open_ccache(context, name, ccache) \
			((context) -> functions -> open_ccache (context, name, ccache))
#define		cc_context_open_default_ccache(context, ccache) \
			((context) -> functions -> open_default_ccache (context, ccache))
#define		cc_context_create_ccache(context, name, version, principal, ccache) \
			((context) -> functions -> create_ccache (context, name, version, principal, ccache))
#define		cc_context_create_default_ccache(context, version, principal, ccache) \
			((context) -> functions -> create_default_ccache (context, version, principal, ccache))
#define		cc_context_create_new_ccache(context, version, principal, ccache) \
			((context) -> functions -> create_new_ccache (context, version, principal, ccache))
#define		cc_context_new_ccache_iterator(context, iterator) \
			((context) -> functions -> new_ccache_iterator (context, iterator))
#define		cc_context_lock(context, type, block) \
			((context) -> functions -> lock (context, type, block))
#define		cc_context_unlock(context) \
			((context) -> functions -> unlock (context))
#define		cc_context_compare(context, compare_to, equal) \
			((context) -> functions -> compare (context, compare_to, equal))

#define		cc_ccache_release(ccache) \
			((ccache) -> functions -> release (ccache))
#define		cc_ccache_destroy(ccache) \
			((ccache) -> functions -> destroy (ccache))
#define		cc_ccache_set_default(ccache) \
			((ccache) -> functions -> set_default (ccache))
#define		cc_ccache_get_credentials_version(ccache, version) \
			((ccache) -> functions -> get_credentials_version (ccache, version))
#define		cc_ccache_get_name(ccache, name) \
			((ccache) -> functions -> get_name (ccache, name))
#define		cc_ccache_get_principal(ccache, version, principal) \
			((ccache) -> functions -> get_principal (ccache, version, principal))
#define		cc_ccache_set_principal(ccache, version, principal) \
			((ccache) -> functions -> set_principal (ccache, version, principal))
#define		cc_ccache_store_credentials(ccache, credentials) \
			((ccache) -> functions -> store_credentials (ccache, credentials))
#define		cc_ccache_remove_credentials(ccache, credentials) \
			((ccache) -> functions -> remove_credentials (ccache, credentials))
#define		cc_ccache_new_credentials_iterator(ccache, iterator) \
			((ccache) -> functions -> new_credentials_iterator (ccache, iterator))
#define		cc_ccache_lock(ccache, type, block) \
			((ccache) -> functions -> lock (ccache, type, block))
#define		cc_ccache_unlock(ccache, unlock) \
			((ccache) -> functions -> unlock (ccache, unlock))
#define		cc_ccache_get_last_default_time(ccache, last_default_time) \
			((ccache) -> functions -> get_last_default_time (ccache, last_default_time))
#define		cc_ccache_get_change_time(ccache, change_time) \
			((ccache) -> functions -> get_change_time (ccache, change_time))
#define		cc_ccache_move(source, destination) \
			((source) -> functions -> move (source, destination))
#define		cc_ccache_compare(ccache, compare_to, equal) \
			((ccache) -> functions -> compare (ccache, compare_to, equal))
#define		cc_ccache_get_kdc_time_offset(ccache, version, time_offset) \
                        ((ccache) -> functions -> get_kdc_time_offset (ccache, version, time_offset))
#define		cc_ccache_set_kdc_time_offset(ccache, version, time_offset) \
                        ((ccache) -> functions -> set_kdc_time_offset (ccache, version, time_offset))
#define		cc_ccache_clear_kdc_time_offset(ccache, version) \
                        ((ccache) -> functions -> clear_kdc_time_offset (ccache, version))

#define		cc_string_release(string) \
			((string) -> functions -> release (string))

#define		cc_credentials_release(credentials) \
			((credentials) -> functions -> release (credentials))
#define		cc_credentials_compare(credentials, compare_to, equal) \
			((credentials) -> functions -> compare (credentials, compare_to, equal))

#define		cc_ccache_iterator_release(iterator) \
			((iterator) -> functions -> release (iterator))
#define		cc_ccache_iterator_next(iterator, ccache) \
			((iterator) -> functions -> next (iterator, ccache))
#define		cc_ccache_iterator_clone(iterator, new_iterator) \
			((iterator) -> functions -> clone (iterator, new_iterator))
	
#define		cc_credentials_iterator_release(iterator) \
			((iterator) -> functions -> release (iterator))
#define		cc_credentials_iterator_next(iterator, credentials) \
			((iterator) -> functions -> next (iterator, credentials))
#define		cc_credentials_iterator_clone(iterator, new_iterator) \
			((iterator) -> functions -> clone (iterator, new_iterator))
			
#if TARGET_OS_MAC
#pragma pack(pop)
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CREDENTIALSCACHE__ */
