/*
 * Copyright 1998-2003 Massachusetts Institute of Technology.
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

/*
 * This is backwards compatibility for CCache API v2 clients to be able to run 
 * against the CCache API v3 library
 */
 
#ifndef __CREDENTIALSCACHE2__
#define __CREDENTIALSCACHE2__
 
#if defined(macintosh) || (defined(__MACH__) && defined(__APPLE__))
#    include <TargetConditionals.h>
#    if TARGET_RT_MAC_CFM
#        error "Use KfM 4.0 SDK headers for CFM compilation."
#    endif
#endif

#include <Kerberos/CredentialsCache.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if TARGET_OS_MAC
#    if defined(__MWERKS__)
#        pragma import on
#    endif
#    pragma options align=mac68k
#endif
    
/* Some old types get directly mapped to new types */

typedef cc_context_d apiCB;
typedef cc_ccache_d ccache_p;
typedef cc_credentials_iterator_d ccache_cit_creds;
typedef cc_ccache_iterator_d ccache_cit_ccache;
typedef cc_data cc_data_compat;
typedef cc_int32 cc_cred_vers;
typedef cc_int32 cc_result;

/* This doesn't exist in API v3 */
typedef cc_uint32 cc_flags;

/* Credentials types are visible to the caller so we have to keep binary compatibility */

typedef struct cc_credentials_v5_compat {
	char*				client;
	char*				server;
	cc_data_compat		keyblock;
	cc_time_t			authtime;
	cc_time_t			starttime;
	cc_time_t			endtime;
	cc_time_t			renew_till;
	cc_uint32			is_skey;
	cc_uint32			ticket_flags;
	cc_data_compat**	addresses;
    cc_data_compat		ticket;
	cc_data_compat		second_ticket;
	cc_data_compat**	authdata;
} cc_credentials_v5_compat;
 
enum {
	MAX_V4_CRED_LEN = 1250
};
 
enum {
	KRB_NAME_SZ = 40,
	KRB_INSTANCE_SZ = 40,
	KRB_REALM_SZ = 40
};
 
typedef struct cc_credentials_v4_compat {
	unsigned char	kversion;
	char			principal[KRB_NAME_SZ+1];
	char			principal_instance[KRB_INSTANCE_SZ+1];
	char			service[KRB_NAME_SZ+1];
	char			service_instance[KRB_INSTANCE_SZ+1];
	char			realm[KRB_REALM_SZ+1];
	unsigned char	session_key[8];
	cc_int32		kvno;
	cc_int32		str_to_key;
	long			issue_date;
	cc_int32		lifetime;
    cc_uint32		address;
	cc_int32		ticket_sz;
	unsigned char	ticket[MAX_V4_CRED_LEN];
	unsigned long	oops;
} cc_credentials_v4_compat;

typedef union cred_ptr_union_compat {
    cc_credentials_v4_compat*	pV4Cred;
    cc_credentials_v5_compat*	pV5Cred;
} cred_ptr_union_compat;
 
typedef struct cred_union {
    cc_int32				cred_type;  // cc_cred_vers
    cred_ptr_union_compat	cred;
} cred_union;

/* NC info structure is gone in v3 */

struct infoNC {
	char*		name;
	char*		principal;
	cc_int32	vers;
};

typedef struct infoNC infoNC;

/* Some old type names */

typedef cc_credentials_v4_compat V4Cred_type;
typedef cc_credentials_v5_compat cc_creds;
struct ccache_cit;
typedef struct ccache_cit ccache_cit;

enum {
	CC_API_VER_2 = ccapi_version_2
};

enum {
	CC_NOERROR,
	CC_BADNAME,
	CC_NOTFOUND,
	CC_END,
	CC_IO,
	CC_WRITE,
	CC_NOMEM,
	CC_FORMAT,
	CC_LOCKED,
	CC_BAD_API_VERSION,
	CC_NO_EXIST,
	CC_NOT_SUPP,
	CC_BAD_PARM,
	CC_ERR_CACHE_ATTACH,
	CC_ERR_CACHE_RELEASE,
	CC_ERR_CACHE_FULL,
	CC_ERR_CRED_VERSION
};

enum {
	CC_CRED_UNKNOWN,
	CC_CRED_V4,
	CC_CRED_V5,
	CC_CRED_MAX
};

cc_int32 cc_shutdown (
	apiCB**				ioContext);
	
cc_int32 cc_get_NC_info (
	apiCB*				inContext,
	infoNC***			outInfo);
	
cc_int32 cc_get_change_time (
	apiCB*				inContext,
	cc_time_t*			outTime);
	
cc_int32 cc_open (
	apiCB*				inContext,
	const char*			inName,
	cc_int32			inVersion,
	cc_uint32			inFlags,
	ccache_p**			outCCache);
	
cc_int32 cc_create (
	apiCB*				inContext,
	const char*			inName,
	const char*			inPrincipal,
	cc_int32			inVersion,
	cc_uint32			inFlags,
	ccache_p**			outCCache);
	
cc_int32 cc_close (
	apiCB*				inContext,
	ccache_p**			ioCCache);
	
cc_int32 cc_destroy (
	apiCB*				inContext,
	ccache_p**			ioCCache);
	
cc_int32 cc_seq_fetch_NCs_begin (
	apiCB*				inContext,
	ccache_cit**		outIterator);

cc_int32 cc_seq_fetch_NCs_next (
	apiCB*				inContext,
	ccache_p**			outCCache,
	ccache_cit*			inIterator);

cc_int32 cc_seq_fetch_NCs_end (
	apiCB*				inContext,
	ccache_cit**		ioIterator);

cc_int32 cc_get_name (
	apiCB*				inContext,
	ccache_p*			inCCache,
	char**				outName);
	
cc_int32 cc_get_cred_version (
	apiCB*				inContext,
	ccache_p*			inCCache,
	cc_int32*			outVersion);
	
cc_int32 cc_set_principal (
	apiCB*				inContext,
	ccache_p*			inCCache,
	cc_int32			inVersion,
	char*				inPrincipal);
	
cc_int32 cc_get_principal (
	apiCB*				inContext,
	ccache_p*			inCCache,
	char**				outPrincipal);
	
cc_int32 cc_store (
	apiCB*				inContext,
	ccache_p*			inCCache,
	cred_union			inCredentials);

cc_int32 cc_remove_cred (
	apiCB*				inContext,
	ccache_p*			inCCache,
	cred_union			inCredentials);

cc_int32 cc_seq_fetch_creds_begin (
	apiCB*				inContext,
	const ccache_p*		inCCache,
	ccache_cit**		outIterator);

cc_int32 cc_seq_fetch_creds_next (
	apiCB*				inContext,
	cred_union**		outCreds,
	ccache_cit*			inIterator);
	
cc_int32 cc_seq_fetch_creds_end (
	apiCB*				inContext,
	ccache_cit**		ioIterator);
	
cc_int32 cc_free_principal (
	apiCB*				inContext,
	char**				ioPrincipal);

cc_int32 cc_free_name (
	apiCB*				inContext,
	char**				ioName);

cc_int32 cc_free_creds (
	apiCB*				inContext,
	cred_union**		creds);

cc_int32 cc_free_NC_info (
	apiCB*				inContext,
	infoNC***			ioInfo);

#if TARGET_OS_MAC
#    if defined(__MWERKS__)
#        pragma import reset
#    endif
#    pragma options align=reset
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CREDENTIALSCACHE2__ */
