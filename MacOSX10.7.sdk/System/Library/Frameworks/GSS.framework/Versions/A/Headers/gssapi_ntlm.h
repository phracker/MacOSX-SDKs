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

#ifndef GSSAPI_NTLM_H_
#define GSSAPI_NTLM_H_

#include <GSS/gssapi.h>

GSSAPI_CPP_START

extern GSSAPI_LIB_VARIABLE gss_OID_desc __gss_ntlm_mechanism_oid_desc;
#define GSS_NTLM_MECHANISM (&__gss_ntlm_mechanism_oid_desc)

extern GSSAPI_LIB_VARIABLE gss_OID_desc __gss_c_nt_ntlm_oid_desc;
#define GSS_C_NT_NTLM (&__gss_c_nt_ntlm_oid_desc)

extern GSSAPI_LIB_VARIABLE gss_OID_desc __gss_ntlm_get_session_key_x_oid_desc;
#define GSS_NTLM_GET_SESSION_KEY_X (&__gss_ntlm_get_session_key_x_oid_desc)

extern GSSAPI_LIB_VARIABLE gss_OID_desc __gss_c_ntlm_guest_oid_desc;
#define GSS_C_NTLM_GUEST (&__gss_c_ntlm_guest_oid_desc)

extern GSSAPI_LIB_VARIABLE gss_OID_desc __gss_c_ntlm_v1;
#define GSS_C_NTLM_V1 (&__gss_c_ntlm_v1)

extern GSSAPI_LIB_VARIABLE gss_OID_desc __gss_c_ntlm_force_v1;
#define GSS_C_NTLM_FORCE_V1 (&__gss_c_ntlm_force_v1)

extern GSSAPI_LIB_VARIABLE gss_OID_desc __gss_c_ntlm_v2;
#define GSS_C_NTLM_V2 (&__gss_c_ntlm_v2)
    
extern GSSAPI_LIB_VARIABLE gss_OID_desc __gss_c_ntlm_session_key;
#define GSS_C_NTLM_SESSION_KEY (&__gss_c_ntlm_session_key)

extern GSSAPI_LIB_VARIABLE gss_OID_desc __gss_c_ntlm_support_channelbindings;
#define GSS_C_NTLM_SUPPORT_CHANNELBINDINGS (&__gss_c_ntlm_support_channelbindings)

extern GSSAPI_LIB_VARIABLE gss_OID_desc __gss_c_ntlm_support_lm2;
#define GSS_C_NTLM_SUPPORT_LM2 (&__gss_c_ntlm_support_lm2)

GSSAPI_CPP_END

#endif /* GSSAPI_NTLM_H_ */
