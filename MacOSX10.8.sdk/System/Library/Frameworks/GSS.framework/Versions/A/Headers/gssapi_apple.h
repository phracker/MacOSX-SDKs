/* This is a generated file */
#ifndef __gssapi_apple_h__
#define __gssapi_apple_h__

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GSS_LIB
#ifndef GSS_LIB_FUNCTION
#if defined(_WIN32)
#define GSS_LIB_FUNCTION __declspec(dllimport)
#define GSS_LIB_CALL __stdcall
#define GSS_LIB_VARIABLE __declspec(dllimport)
#else
#define GSS_LIB_FUNCTION
#define GSS_LIB_CALL
#define GSS_LIB_VARIABLE
#endif
#endif
#endif
OM_uint32 GSSAPI_LIB_FUNCTION
gss_aapl_initial_cred (
	const gss_name_t /*desired_name*/,
	gss_const_OID /*desired_mech*/,
	CFDictionaryRef /*attributes*/,
	gss_cred_id_t * /*output_cred_handle*/,
	CFErrorRef */*error*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

#ifdef __cplusplus
}
#endif

#endif /* __gssapi_apple_h__ */
