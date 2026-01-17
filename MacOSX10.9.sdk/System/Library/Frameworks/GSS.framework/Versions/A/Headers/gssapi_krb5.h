/*
 * Copyright (c) 1997 - 2006 Kungliga Tekniska Högskolan
 * (Royal Institute of Technology, Stockholm, Sweden).
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/* $Id$ */

#ifndef GSSAPI_KRB5_H_
#define GSSAPI_KRB5_H_

#include <GSS/gssapi.h>

GSSAPI_CPP_START

#if !defined(__GNUC__) && !defined(__attribute__)
#define __attribute__(x)
#endif

#ifndef GSSKRB5_FUNCTION_DEPRECATED
#define GSSKRB5_FUNCTION_DEPRECATED __attribute__((deprecated))
#endif


/*
 * This is for kerberos5 names.
 */

/* do not use this entry */
extern gss_OID_desc GSSAPI_LIB_VARIABLE __gss_krb5_nt_principal_oid_desc;
#define GSS_KRB5_NT_PRINCIPAL (&__gss_krb5_nt_principal_oid_desc)

extern gss_OID_desc GSSAPI_LIB_VARIABLE __gss_krb5_nt_principal_name_oid_desc;
#define GSS_KRB5_NT_PRINCIPAL_NAME (&__gss_krb5_nt_principal_name_oid_desc)

extern gss_OID_desc GSSAPI_LIB_VARIABLE __gss_krb5_nt_principal_name_referral_oid_desc;
#define GSS_KRB5_NT_PRINCIPAL_NAME_REFERRAL (&__gss_krb5_nt_principal_name_referral_oid_desc)

#define GSS_KRB5_NT_USER_NAME (&__gss_c_nt_user_name_oid_desc)
#define GSS_KRB5_NT_MACHINE_UID_NAME (&__gss_c_nt_machine_uid_name_oid_desc)
#define GSS_KRB5_NT_STRING_UID_NAME (&__gss_c_nt_string_uid_name_oid_desc)

/* for compatibility with MIT api */

#define gss_mech_krb5 GSS_KRB5_MECHANISM
#define gss_krb5_nt_general_name GSS_KRB5_NT_PRINCIPAL_NAME

/*
 * kerberos mechanism specific functions
 */

/*
 * Lucid - NFSv4 interface to GSS-API KRB5 to expose key material to
 * do GSS content token handling in-kernel.
 */

typedef struct gss_krb5_lucid_key {
	OM_uint32	type;
	OM_uint32	length;
	void *		data;
} gss_krb5_lucid_key_t;

typedef struct gss_krb5_rfc1964_keydata {
	OM_uint32		sign_alg;
	OM_uint32		seal_alg;
	gss_krb5_lucid_key_t	ctx_key;
} gss_krb5_rfc1964_keydata_t;

typedef struct gss_krb5_cfx_keydata {
	OM_uint32		have_acceptor_subkey;
	gss_krb5_lucid_key_t	ctx_key;
	gss_krb5_lucid_key_t	acceptor_subkey;
} gss_krb5_cfx_keydata_t;

typedef struct gss_krb5_lucid_context_v1 {
	OM_uint32	version;
	OM_uint32	initiate;
	OM_uint32	endtime;
	OM_uint64	send_seq;
	OM_uint64	recv_seq;
	OM_uint32	protocol;
	gss_krb5_rfc1964_keydata_t rfc1964_kd;
	gss_krb5_cfx_keydata_t	   cfx_kd;
} gss_krb5_lucid_context_v1_t;

typedef struct gss_krb5_lucid_context_version {
	OM_uint32	version;	/* Structure version number */
} gss_krb5_lucid_context_version_t;

GSSAPI_CPP_END

#endif /* GSSAPI_SPNEGO_H_ */
