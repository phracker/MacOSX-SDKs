/*
 * Copyright (c) 1997 - 2007 Kungliga Tekniska Högskolan
 * (Royal Institute of Technology, Stockholm, Sweden).
 * All rights reserved.
 *
 * Portions Copyright (c) 2009 Apple Inc. All rights reserved.
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

#ifndef GSSAPI_GSSAPI_H_
#define GSSAPI_GSSAPI_H_

/*
 * First, include stddef.h to get size_t defined.
 */
#include <stddef.h>

#include <inttypes.h>
#include <unistd.h>

#ifndef BUILD_GSSAPI_LIB
#if defined(_WIN32)
#define GSSAPI_LIB_FUNCTION __declspec(dllimport)
#define GSSAPI_LIB_CALL     __stdcall
#define GSSAPI_LIB_VARIABLE __declspec(dllimport)
#else
#define GSSAPI_LIB_FUNCTION
#define GSSAPI_LIB_CALL
#define GSSAPI_LIB_VARIABLE
#endif
#endif

#ifdef __GSS_ITER_CRED_USES_CONST_OID
#define gss_iter_OID gss_const_OID
#else
#define gss_iter_OID gss_OID
#endif

/* Compatiblity with MIT Kerberos on the Mac */
#if defined(__APPLE__) && (defined(__ppc__) || defined(__ppc64__) || defined(__i386__) || defined(__x86_64__))
#pragma pack(push,2)
#endif


#ifdef __cplusplus
#define GSSAPI_CPP_START	extern "C" {
#define GSSAPI_CPP_END		}
#else
#define GSSAPI_CPP_START
#define GSSAPI_CPP_END
#endif

#ifdef _WIN32
#define GSSAPI_CALLCONV __stdcall
#else
#define GSSAPI_CALLCONV
#endif

/*
 * Now define the three implementation-dependent types.
 */

typedef uint32_t OM_uint32;
typedef uint64_t OM_uint64;

typedef uint32_t gss_uint32;

struct gss_name_t_desc_struct;
typedef struct gss_name_t_desc_struct *gss_name_t;
typedef const struct gss_name_t_desc_struct *gss_const_name_t;

struct gss_ctx_id_t_desc_struct;
typedef struct gss_ctx_id_t_desc_struct *gss_ctx_id_t;
typedef const struct gss_ctx_id_t_desc_struct gss_const_ctx_id_t;

typedef struct gss_OID_desc_struct {
      OM_uint32 length;
      void      *elements;
} gss_OID_desc, *gss_OID;
typedef const gss_OID_desc * gss_const_OID;

typedef struct gss_OID_set_desc_struct  {
      size_t     count;
      gss_OID    elements;
} gss_OID_set_desc, *gss_OID_set;
typedef const gss_OID_set_desc * gss_const_OID_set;

typedef int gss_cred_usage_t;

struct gss_cred_id_t_desc_struct;
typedef struct gss_cred_id_t_desc_struct *gss_cred_id_t;
typedef const struct gss_cred_id_t_desc_struct *gss_const_cred_id_t;

typedef struct gss_buffer_desc_struct {
      size_t length;
      void *value;
} gss_buffer_desc, *gss_buffer_t;
typedef const gss_buffer_desc * gss_const_buffer_t;

typedef struct gss_channel_bindings_struct {
      OM_uint32 initiator_addrtype;
      gss_buffer_desc initiator_address;
      OM_uint32 acceptor_addrtype;
      gss_buffer_desc acceptor_address;
      gss_buffer_desc application_data;
} *gss_channel_bindings_t;
typedef const struct gss_channel_bindings_struct *gss_const_channel_bindings_t;

/* GGF extension data types */
typedef struct gss_buffer_set_desc_struct {
      size_t count;
      gss_buffer_desc *elements;
} gss_buffer_set_desc, *gss_buffer_set_t;

typedef struct gss_iov_buffer_desc_struct {
    OM_uint32 type;
    gss_buffer_desc buffer;
} gss_iov_buffer_desc, *gss_iov_buffer_t;

/*
 * For now, define a QOP-type as an OM_uint32
 */
typedef OM_uint32 gss_qop_t;

/* XXX glue for old code */
typedef OM_uint32 *gss_status_id_t;
typedef struct gss_auth_identity *gss_auth_identity_t;

/*
 * Flag bits for context-level services.
 */
#define GSS_C_DELEG_FLAG 1
#define GSS_C_MUTUAL_FLAG 2
#define GSS_C_REPLAY_FLAG 4
#define GSS_C_SEQUENCE_FLAG 8
#define GSS_C_CONF_FLAG 16
#define GSS_C_INTEG_FLAG 32
#define GSS_C_ANON_FLAG 64
#define GSS_C_PROT_READY_FLAG 128
#define GSS_C_TRANS_FLAG 256

#define GSS_C_DCE_STYLE 4096
#define GSS_C_IDENTIFY_FLAG 8192
#define GSS_C_EXTENDED_ERROR_FLAG 16384
#define GSS_C_DELEG_POLICY_FLAG 32768

/*
 * Credential usage options
 */
#define GSS_C_BOTH 0
#define GSS_C_INITIATE 1
#define GSS_C_ACCEPT 2

#define GSS_C_OPTION_MASK 0xffff
#define GSS_C_CRED_NO_UI  0x10000

/*
 * Status code types for gss_display_status
 */
#define GSS_C_GSS_CODE 1
#define GSS_C_MECH_CODE 2

/*
 * The constant definitions for channel-bindings address families
 */
#define GSS_C_AF_UNSPEC     0
#define GSS_C_AF_LOCAL      1
#define GSS_C_AF_INET       2
#define GSS_C_AF_IMPLINK    3
#define GSS_C_AF_PUP        4
#define GSS_C_AF_CHAOS      5
#define GSS_C_AF_NS         6
#define GSS_C_AF_NBS        7
#define GSS_C_AF_ECMA       8
#define GSS_C_AF_DATAKIT    9
#define GSS_C_AF_CCITT      10
#define GSS_C_AF_SNA        11
#define GSS_C_AF_DECnet     12
#define GSS_C_AF_DLI        13
#define GSS_C_AF_LAT        14
#define GSS_C_AF_HYLINK     15
#define GSS_C_AF_APPLETALK  16
#define GSS_C_AF_BSC        17
#define GSS_C_AF_DSS        18
#define GSS_C_AF_OSI        19
#define GSS_C_AF_X25        21
#define GSS_C_AF_INET6	    24

#define GSS_C_AF_NULLADDR   255

/*
 * Various Null values
 */
#define GSS_C_NO_NAME ((gss_name_t) 0)
#define GSS_C_NO_BUFFER ((gss_buffer_t) 0)
#define GSS_C_NO_BUFFER_SET ((gss_buffer_set_t) 0)
#define GSS_C_NO_OID ((gss_OID) 0)
#define GSS_C_NO_OID_SET ((gss_OID_set) 0)
#define GSS_C_NO_CONTEXT ((gss_ctx_id_t) 0)
#define GSS_C_NO_CREDENTIAL ((gss_cred_id_t) 0)
#define GSS_C_NO_CHANNEL_BINDINGS ((gss_channel_bindings_t) 0)
#define GSS_C_EMPTY_BUFFER {0, NULL}
#define GSS_C_NO_IOV_BUFFER ((gss_iov_buffer_t)0)

/*
 * Some alternate names for a couple of the above
 * values.  These are defined for V1 compatibility.
 */
#define GSS_C_NULL_OID GSS_C_NO_OID
#define GSS_C_NULL_OID_SET GSS_C_NO_OID_SET

/*
 * Define the default Quality of Protection for per-message
 * services.  Note that an implementation that offers multiple
 * levels of QOP may define GSS_C_QOP_DEFAULT to be either zero
 * (as done here) to mean "default protection", or to a specific
 * explicit QOP value.  However, a value of 0 should always be
 * interpreted by a GSSAPI implementation as a request for the
 * default protection level.
 */
#define GSS_C_QOP_DEFAULT 0

#define GSS_KRB5_CONF_C_QOP_DES		0x0100
#define GSS_KRB5_CONF_C_QOP_DES3_KD	0x0200

/*
 * Expiration time of 2^32-1 seconds means infinite lifetime for a
 * credential or security context
 */
#define GSS_C_INDEFINITE 0xfffffffful

/*
 * Type of gss_wrap_iov()/gss_unwrap_iov().
 */

#define GSS_IOV_BUFFER_TYPE_EMPTY 0
#define GSS_IOV_BUFFER_TYPE_DATA 1
#define GSS_IOV_BUFFER_TYPE_HEADER 2
#define GSS_IOV_BUFFER_TYPE_MECH_PARAMS 3

#define GSS_IOV_BUFFER_TYPE_TRAILER 7
#define GSS_IOV_BUFFER_TYPE_PADDING 9
#define GSS_IOV_BUFFER_TYPE_STREAM 10
#define GSS_IOV_BUFFER_TYPE_SIGN_ONLY 11

#define GSS_IOV_BUFFER_TYPE_FLAG_MASK		0xffff0000
#define GSS_IOV_BUFFER_FLAG_ALLOCATE		0x00010000
#define GSS_IOV_BUFFER_FLAG_ALLOCATED		0x00020000

#define GSS_IOV_BUFFER_TYPE_FLAG_ALLOCATE	0x00010000 /* old name */
#define GSS_IOV_BUFFER_TYPE_FLAG_ALLOCATED	0x00020000 /* old name */

#define GSS_IOV_BUFFER_TYPE(_t) ((_t) & ~GSS_IOV_BUFFER_TYPE_FLAG_MASK)
#define GSS_IOV_BUFFER_FLAGS(_t) ((_t) & GSS_IOV_BUFFER_TYPE_FLAG_MASK)

GSSAPI_CPP_START

#ifndef __KRB5_H__ /* provide forward declaration if its not already defined */
struct krb5_ccache_data; /* for gss_krb5_copy_ccache, deprecated */
#endif

#include <GSS/gssapi_oid.h>
#include <GSS/gssapi_protos.h>

/* Major status codes */

#define GSS_S_COMPLETE 0

/*
 * Some "helper" definitions to make the status code macros obvious.
 */
#define GSS_C_CALLING_ERROR_OFFSET 24
#define GSS_C_ROUTINE_ERROR_OFFSET 16
#define GSS_C_SUPPLEMENTARY_OFFSET 0
#define GSS_C_CALLING_ERROR_MASK 0377ul
#define GSS_C_ROUTINE_ERROR_MASK 0377ul
#define GSS_C_SUPPLEMENTARY_MASK 0177777ul

/*
 * The macros that test status codes for error conditions.
 * Note that the GSS_ERROR() macro has changed slightly from
 * the V1 GSSAPI so that it now evaluates its argument
 * only once.
 */
#define GSS_CALLING_ERROR(x) \
  (x & (GSS_C_CALLING_ERROR_MASK << GSS_C_CALLING_ERROR_OFFSET))
#define GSS_ROUTINE_ERROR(x) \
  (x & (GSS_C_ROUTINE_ERROR_MASK << GSS_C_ROUTINE_ERROR_OFFSET))
#define GSS_SUPPLEMENTARY_INFO(x) \
  (x & (GSS_C_SUPPLEMENTARY_MASK << GSS_C_SUPPLEMENTARY_OFFSET))
#define GSS_ERROR(x) \
  (x & ((GSS_C_CALLING_ERROR_MASK << GSS_C_CALLING_ERROR_OFFSET) | \
        (GSS_C_ROUTINE_ERROR_MASK << GSS_C_ROUTINE_ERROR_OFFSET)))

/*
 * Now the actual status code definitions
 */

/*
 * Calling errors:
 */
#define GSS_S_CALL_INACCESSIBLE_READ \
                             (1ul << GSS_C_CALLING_ERROR_OFFSET)
#define GSS_S_CALL_INACCESSIBLE_WRITE \
                             (2ul << GSS_C_CALLING_ERROR_OFFSET)
#define GSS_S_CALL_BAD_STRUCTURE \
                             (3ul << GSS_C_CALLING_ERROR_OFFSET)

/*
 * Routine errors:
 */
#define GSS_S_BAD_MECH (1ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_BAD_NAME (2ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_BAD_NAMETYPE (3ul << GSS_C_ROUTINE_ERROR_OFFSET)

#define GSS_S_BAD_BINDINGS (4ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_BAD_STATUS (5ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_BAD_SIG (6ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_BAD_MIC GSS_S_BAD_SIG
#define GSS_S_NO_CRED (7ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_NO_CONTEXT (8ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_DEFECTIVE_TOKEN (9ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_DEFECTIVE_CREDENTIAL (10ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_CREDENTIALS_EXPIRED (11ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_CONTEXT_EXPIRED (12ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_FAILURE (13ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_BAD_QOP (14ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_UNAUTHORIZED (15ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_UNAVAILABLE (16ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_DUPLICATE_ELEMENT (17ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_NAME_NOT_MN (18ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_BAD_MECH_ATTR (19ul << GSS_C_ROUTINE_ERROR_OFFSET)

/*
 * Apparently awating spec fix.
 */
#define GSS_S_CRED_UNAVAIL GSS_S_FAILURE

/*
 * Supplementary info bits:
 */
#define GSS_S_CONTINUE_NEEDED (1ul << (GSS_C_SUPPLEMENTARY_OFFSET + 0))
#define GSS_S_DUPLICATE_TOKEN (1ul << (GSS_C_SUPPLEMENTARY_OFFSET + 1))
#define GSS_S_OLD_TOKEN (1ul << (GSS_C_SUPPLEMENTARY_OFFSET + 2))
#define GSS_S_UNSEQ_TOKEN (1ul << (GSS_C_SUPPLEMENTARY_OFFSET + 3))
#define GSS_S_GAP_TOKEN (1ul << (GSS_C_SUPPLEMENTARY_OFFSET + 4))

/* gss_acquire_cred options mask hack */
#define GSS_C_OPTION_MASK 0xffff
#define GSS_C_CRED_NO_UI  0x10000

/*
 * RFC 4401 - gss_pseudo_random
 */

#define GSS_C_PRF_KEY_FULL 0
#define GSS_C_PRF_KEY_PARTIAL 1

extern GSSAPI_LIB_VARIABLE gss_buffer_desc __gss_c_attr_local_login_user;
#define GSS_C_ATTR_LOCAL_LOGIN_USER (&__gss_c_attr_local_login_user)

/*
 *
 */

#ifdef __APPLE__

#include <CoreFoundation/CoreFoundation.h>

#define kGSSICPassword			CFSTR("kGSSICPassword")
#define kGSSICCertificate		CFSTR("kGSSICCertificate")
#define kGSSICVerifyCredential		CFSTR("kGSSICVerifyCredential")

#define kGSSCredentialUsage		CFSTR("kGSSCredentialUsage")
#define kGSS_C_INITIATE			CFSTR("kGSS_C_INITIATE")
#define kGSS_C_ACCEPT			CFSTR("kGSS_C_ACCEPT")
#define kGSS_C_BOTH			CFSTR("kGSS_C_BOTH")

#define kGSSICLKDCHostname		CFSTR("kGSSICLKDCHostname")

#define kGSSICKerberosCacheName		CFSTR("kGSSICKerberosCacheName")
#define kGSSICSiteName			CFSTR("kGSSICSiteName")
#define kGSSICAppIdentifierACL		CFSTR("kGSSICAppIdentifierACL")
#define kGSSICVerifyCredentialAcceptorName CFSTR("kGSSICVerifyCredentialAcceptorName")
#define kGSSICCreateNewCredential	CFSTR("kGSSICCreateNewCredential")
#define kGSSICAppleSourceApp		CFSTR("kGSSICAppleSourceApp")
#define kGSSICAppleSourceAppAuditToken	CFSTR("kGSSICAppleSourceAppAuditToken")
#define kGSSICAppleSourceAppPID		CFSTR("kGSSICAppleSourceAppPID")
#define kGSSICAppleSourceAppSigningIdentity CFSTR("kGSSICAppleSourceAppSigningIdentity")

#include <GSS/gssapi_apple.h>


#define kGSSChangePasswordOldPassword	CFSTR("kGSSChangePasswordOldPassword")
#define kGSSChangePasswordNewPassword	CFSTR("kGSSChangePasswordNewPassword")

#endif

/* Include Apple private SPI */
#ifdef __GSSAPI_APPLE_API_PRIVATE
#include <GSS/gssapi_spi.h>
#endif

GSSAPI_CPP_END

#if defined(__APPLE__) && (defined(__ppc__) || defined(__ppc64__) || defined(__i386__) || defined(__x86_64__))
#pragma pack(pop)
#endif

#endif /* GSSAPI_GSSAPI_H_ */
