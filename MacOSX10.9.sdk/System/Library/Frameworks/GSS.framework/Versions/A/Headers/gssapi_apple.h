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
/**
 * Returns a GSS credential for a given UUID if the credential exists.
 *
 * @param uuid the UUID of the credential to fetch
 *
 * @returns a gss_cred_id_t, normal CoreFoundaton rules for rules
 * applies so the CFUUIDRef needs to be released with either CFRelease() or gss_release_name().
 *
 * @ingroup gssapi
 */
gss_cred_id_t GSSAPI_LIB_FUNCTION
GSSCreateCredentialFromUUID (CFUUIDRef /*uuid*/)  __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/**
 * Create a GSS name from a buffer and type.
 *
 * @param name name buffer describing a credential, can be either a CFDataRef or CFStringRef of a name.
 * @param name_type on OID of the GSS_C_NT_* OIDs constants specifiy the name type.
 * @param error if an error happen, this may be set to a CFErrorRef describing the failure futher.
 *
 * @returns returns gss_name_t or NULL on failure. Must be freed using gss_release_name() or CFRelease(). Follows CoreFoundation Create/Copy rule.
 *
 * @ingroup gssapi
 */
gss_name_t
GSSCreateName (
	CFTypeRef /*name*/,
	gss_const_OID /*name_type*/,
	CFErrorRef */*error*/)  __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/**
 * Copy the name describing the credential
 *
 * @param cred the credential to get the name from
 *
 * @returns returns gss_name_t or NULL on failure. Must be freed using gss_release_name() or CFRelease(). Follows CoreFoundation Create/Copy rule.
 *
 * @ingroup gssapi
 */
gss_name_t
GSSCredentialCopyName (gss_cred_id_t /*cred*/)  __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/**
 * Returns a copy of the UUID of the GSS credential
 *
 * @param credential credential
 *
 * @returns CFUUIDRef that can be used to turn into a credential,
 * normal CoreFoundaton rules for rules applies so the CFUUIDRef needs
 * to be released.
 *
 * @ingroup gssapi
 */
CFUUIDRef
GSSCredentialCopyUUID (gss_cred_id_t /*cred*/)  __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/**
 * Return the lifetime (in seconds) left of the credential.
 *
 * @param cred the credential to get the name from
 *
 * @returns the lifetime of the credentials. 0 on failure and
 * GSS_C_INDEFINITE on credentials that never expire.
 *
 * @ingroup gssapi
 */
OM_uint32
GSSCredentialGetLifetime (gss_cred_id_t /*cred*/)  __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/**
 * Returns a string that is suitable for displaying to user, must not
 * be used for verify subjects on an ACLs.
 *
 * @param name to get a display strings from
 *
 * @returns a string that is printable. Follows CoreFoundation Create/Copy rule.
 *
 * @ingroup gssapi
 */
CFStringRef
GSSNameCreateDisplayString (gss_name_t /*name*/)  __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/**
     * The credential can be validated by adding kGSSICVerifyCredential to the attributes with any value.
 */
OM_uint32 GSSAPI_LIB_FUNCTION
gss_aapl_change_password (
	const gss_name_t /*name*/,
	gss_const_OID /*mech*/,
	CFDictionaryRef /*attributes*/,
	CFErrorRef */*error*/)  __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);

/**
 * Acquire a new initial credentials using long term credentials (password, certificate).
 *
 * Credentials acquired should be free-ed with gss_release_cred() or
 * destroyed with (removed from storage) gss_destroy_cred().
 *
 * Some mechanism types can not directly acquire or validate
 * credential (for example PK-U2U, SCRAM, NTLM or IAKERB), for those
 * mechanisms its instead the gss_init_sec_context() that will either acquire or
 * force validation of the credential.
 *
 * This function is blocking and should not be used on threads used for UI updates.
 *
 * @param desired_name name to use to acquire credential. Import the name using gss_import_name(). The type of the name has to be supported by the desired_mech used.
 *
 * @param mech mechanism to use to acquire credential. GSS_C_NO_OID is not valid input and a mechanism must be selected. For example GSS_KRB5_MECHANISM, GSS_NTLM_MECHNISM or any other mechanisms supported by the implementation. See gss_indicate_mechs().
 *
 * @param attributes CFDictionary that contains how to acquire the credential, see below for examples
 *
 * @param output_cred_handle the resulting credential handle, value is set to GSS_C_NO_CREDENTIAL on failure.
 *
 * @param error an CFErrorRef returned in case of an error, that needs to be released with CFRelease() by the caller, input can be NULL.
 *
 * @returns a gss_error code, see the CFErrorRef passed back in error for the failure message.
 *
 * attributes must contains one of the following keys
 * * kGSSICPassword - CFStringRef password
 * * kGSSICCertificate - SecIdentityRef to the certificate to use with PKINIT/PKU2U
 *
 * optional keys
 * * kGSSCredentialUsage - one of kGSS_C_INITIATE, kGSS_C_ACCEPT, kGSS_C_BOTH, default if not given is kGSS_C_INITIATE
 * * kGSSICVerifyCredential - validate the credential with a trusted source that there was no MITM
 * * kGSSICLKDCHostname - CFStringRef hostname of LKDC hostname
 * * kGSSICKerberosCacheName - CFStringRef name of cache that will be created (including type)
 * * kGSSICAppIdentifierACL - CFArrayRef[CFStringRef] prefix of bundle ID allowed to access this credential
 *
 *
 *	  
 * @ingroup gssapi
 */
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
