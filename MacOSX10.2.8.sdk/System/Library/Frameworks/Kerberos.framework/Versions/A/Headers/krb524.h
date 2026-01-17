/*
 * This file is auto generated.
 * Please do not edit it.
 */

#ifndef __KRB524_H__

/* Environment dependent macros */
#define SIZEOF_LONG		4
#define SIZEOF_INT		4
#define SIZEOF_SHORT	2
#define	HAVE_STDARG_H		1
#define HAVE_SYS_TYPES_H	1


/* Error tables from krb524_err.h */
#define initialize_k524_error_table()
#define KRB524_BADKEY                            (-1750206208L)
#define KRB524_BADADDR                           (-1750206207L)
#define KRB524_BADPRINC                          (-1750206206L)
#define KRB524_BADREALM                          (-1750206205L)
#define KRB524_V4ERR                             (-1750206204L)
#define KRB524_ENCFULL                           (-1750206203L)
#define KRB524_DECEMPTY                          (-1750206202L)
#define KRB524_NOTRESP                           (-1750206201L)
#define ERROR_TABLE_BASE_k524                    (-1750206208L)
/*
 * Copyright 1994 by OpenVision Technologies, Inc.
 * 
 * Permission to use, copy, modify, distribute, and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appears in all copies and
 * that both that copyright notice and this permission notice appear in
 * supporting documentation, and that the name of OpenVision not be used
 * in advertising or publicity pertaining to distribution of the software
 * without specific, written prior permission. OpenVision makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 * 
 * OPENVISION DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL OPENVISION BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef __KRB524_H__
#define __KRB524_H__

#define KRB524_SERVICE "krb524"
#define KRB524_PORT 4444

#if defined(macintosh) || (defined(__MACH__) && defined(__APPLE__))
	#include <TargetConditionals.h>
    #include <Kerberos/krb5.h>
    #include <Kerberos/krb.h>
    #ifndef KRB524_PRIVATE /* Allow e.g. build system to override */
		#define KRB524_PRIVATE 0
	#endif
#else
    #include "krb524_err.h"
	#ifndef KRB524_PRIVATE
		#define KRB524_PRIVATE 1
	#endif
#endif	

#if defined(__cplusplus) && !defined(KRB524INT_BEGIN_DECLS)
#define KRB524INT_BEGIN_DECLS	extern "C" {
#define KRB524INT_END_DECLS	}
#else
#define KRB524INT_BEGIN_DECLS
#define KRB524INT_END_DECLS
#endif

#if TARGET_OS_MAC
    #if defined(__MWERKS__)
        #pragma import on
        #pragma enumsalwaysint on
    #endif
    #pragma options align=mac68k
#endif

KRB524INT_BEGIN_DECLS

#if KRB524_PRIVATE
extern int krb524_debug;

int krb524_convert_tkt_skey
	KRB5_PROTOTYPE((krb5_context context, krb5_ticket *v5tkt, KTEXT_ST *v4tkt, 
		   krb5_keyblock *v5_skey, krb5_keyblock *v4_skey,
			struct sockaddr_in *saddr));

/* conv_princ.c */

int krb524_convert_princs
	KRB5_PROTOTYPE((krb5_context context, krb5_principal client, 
		   krb5_principal server, char *pname, 
		   char *pinst, char *prealm, char *sname, char *sinst));

/* conv_creds.c */

int krb524_convert_creds_addr
	KRB5_PROTOTYPE((krb5_context context, krb5_creds *v5creds, 
		   CREDENTIALS *v4creds, struct sockaddr *saddr));
#endif /* KRB524_PRIVATE */

int krb524_convert_creds_kdc
	KRB5_PROTOTYPE((krb5_context context, krb5_creds *v5creds, 
		   CREDENTIALS *v4creds));

#if KRB524_PRIVATE
/* conv_tkt.c */

int krb524_convert_tkt
	KRB5_PROTOTYPE((krb5_principal server, krb5_data *v5tkt, KTEXT_ST *v4tkt,
		   int *kvno, struct sockaddr_in *saddr));

/* encode.c */

int encode_v4tkt
	KRB5_PROTOTYPE((KTEXT_ST *v4tkt, char *buf, int *encoded_len));

int decode_v4tkt
	KRB5_PROTOTYPE((KTEXT_ST *v4tkt, char *buf, int *encoded_len));


/* misc.c */

void krb524_init_ets
	KRB5_PROTOTYPE((krb5_context context));

/* sendmsg.c */

int krb524_send_message 
	KRB5_PROTOTYPE((const struct sockaddr * addr, const krb5_data * message,
		   krb5_data * reply));
#endif /* KRB524_PRIVATE */

#if TARGET_OS_MAC
    #if defined(__MWERKS__)
        #pragma enumsalwaysint reset
        #pragma import reset
    #endif
	#pragma options align=reset
#endif

KRB524INT_END_DECLS

#endif /* __KRB524_H__ */
#endif /* __KRB524_H__  */
