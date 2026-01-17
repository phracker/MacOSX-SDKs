/*
 * Copyright (c) 2006 - 2009 Kungliga Tekniska Högskolan
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

#ifndef GSSAPI_NETLOGON_H_
#define GSSAPI_NETLOGON_H_

#include <GSS/gssapi.h>

GSSAPI_CPP_START

extern GSSAPI_LIB_VARIABLE gss_OID_desc __gss_netlogon_mechanism_oid_desc;
#define GSS_NETLOGON_MECHANISM (&__gss_netlogon_mechanism_oid_desc)

extern GSSAPI_LIB_VARIABLE gss_OID_desc __gss_netlogon_nt_netbios_dns_name_oid_desc;
#define GSS_NETLOGON_NT_NETBIOS_DNS_NAME (&__gss_netlogon_nt_netbios_dns_name_oid_desc)

extern GSSAPI_LIB_VARIABLE gss_OID_desc __gss_netlogon_set_session_key_x_oid_desc;
#define GSS_NETLOGON_SET_SESSION_KEY_X (&__gss_netlogon_set_session_key_x_oid_desc)

extern GSSAPI_LIB_VARIABLE gss_OID_desc __gss_netlogon_set_sign_algorithm_x_oid_desc;
#define GSS_NETLOGON_SET_SIGN_ALGORITHM_X (&__gss_netlogon_set_sign_algorithm_x_oid_desc)

GSSAPI_CPP_END

#endif /* GSSAPI_NETLOGON_H_ */
