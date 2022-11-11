/* This is a generated file */
#ifndef __gssapi_protos_h__
#define __gssapi_protos_h__

#include <stdarg.h>

#ifndef HEIMDAL_PRINTF_ATTRIBUTE
#if defined(__GNUC__) && ((__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1 )))
#define HEIMDAL_PRINTF_ATTRIBUTE(x) __attribute__((format x))
#else
#define HEIMDAL_PRINTF_ATTRIBUTE(x)
#endif
#endif

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
 * @page internalVSmechname Internal names and mechanism names
 * @section gssapi_api_INvsMN Name forms
 *
 * There are two forms of name in GSS-API, Internal form and
 * Contiguous string ("flat") form. gss_export_name() and
 * gss_import_name() can be used to convert between the two forms.
 *
 * - The contiguous string form is described by an oid specificing the
 *   type and an octet string. A special form of the contiguous
 *   string form is the exported name object. The exported name
 *   defined for each mechanism, is something that can be stored and
 *   complared later. The exported name is what should be used for
 *   ACLs comparisons.
 *
 * - The Internal form
 *
 *   There is also special form of the Internal Name (IN), and that is
 *   the Mechanism Name (MN). In the mechanism name all the generic
 *   information is stripped of and only contain the information for
 *   one mechanism.  In GSS-API some function return MN and some
 *   require MN as input. Each of these function is marked up as such.
 *
 *
 * Describe relationship between import_name, canonicalize_name,
 * export_name and friends.
 */

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_accept_sec_context (
	 OM_uint32 * __nonnull minor_status,
	__nullable gss_ctx_id_t * __nonnull context_handle,
	__nullable const gss_cred_id_t acceptor_cred_handle,
	__nullable const gss_buffer_t input_token,
	__nullable const gss_channel_bindings_t input_chan_bindings,
	__nullable gss_name_t * __nullable src_name,
	__nullable gss_OID * __nullable mech_type,
	__nonnull gss_buffer_t output_token,
	OM_uint32 * __nullable ret_flags,
	OM_uint32 * __nullable time_rec,
	gss_cred_id_t __nullable * __nullable delegated_cred_handle)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_acquire_cred (
	OM_uint32 *__nonnull minor_status,
	__nullable const gss_name_t desired_name,
	OM_uint32 time_req,
	__nullable const gss_OID_set desired_mechs,
	gss_cred_usage_t cred_usage,
	__nullable gss_cred_id_t * __nonnull output_cred_handle,
	__nullable gss_OID_set * __nullable actual_mechs,
	OM_uint32 * __nullable time_rec)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_acquire_cred_with_password (
	OM_uint32 * __nonnull minor_status,
	__nonnull const gss_name_t desired_name,
	__nonnull const gss_buffer_t password,
	OM_uint32 time_req,
	__nullable const gss_OID_set desired_mechs,
	gss_cred_usage_t cred_usage,
	__nullable gss_cred_id_t * __nonnull output_cred_handle,
	__nullable gss_OID_set *__nullable actual_mechs,
	OM_uint32 * __nullable time_rec)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_add_buffer_set_member (
	OM_uint32 * __nonnull minor_status,
	__nonnull const gss_buffer_t member_buffer,
	__nonnull gss_buffer_set_t *__nonnull buffer_set)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_add_cred (
	OM_uint32 * __nonnull minor_status,
	__nullable const gss_cred_id_t input_cred_handle,
	__nullable const gss_name_t desired_name,
	__nullable const gss_OID desired_mech,
	gss_cred_usage_t cred_usage,
	OM_uint32 initiator_time_req,
	OM_uint32 acceptor_time_req,
	__nullable gss_cred_id_t * __nonnull output_cred_handle,
	__nullable gss_OID_set * __nullable actual_mechs,
	OM_uint32 * __nullable initiator_time_rec,
	OM_uint32 * __nullable acceptor_time_rec)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/**
 * Add a oid to the oid set, function does not make a copy of the oid,
 * so the pointer to member_oid needs to be stable for the whole time
 * oid_set is used.
 *
 * If there is a duplicate member of the oid, the new member is not
 * added to to the set.
 *
 * @param minor_status minor status code.
 * @param member_oid member to add to the oid set
 * @param oid_set oid set to add the member too
 *
 * @returns a gss_error code, see gss_display_status() about printing
 *          the error code.
 *
 * @ingroup gssapi
 */

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_add_oid_set_member (
	OM_uint32 * __nonnull minor_status,
	__nonnull gss_const_OID member_oid,
	__nonnull gss_OID_set * __nonnull oid_set)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/**
 *  gss_canonicalize_name takes a Internal Name (IN) and converts in into a
 *  mechanism specific Mechanism Name (MN).
 *
 *  The input name may multiple name, or generic name types.
 *
 *  If the input_name if of the GSS_C_NT_USER_NAME, and the Kerberos
 *  mechanism is specified, the resulting MN type is a
 *  GSS_KRB5_NT_PRINCIPAL_NAME.
 *
 *  For more information about @ref internalVSmechname.
 *
 *  @param minor_status minor status code.
 *  @param input_name name to covert, unchanged by gss_canonicalize_name().
 *  @param mech_type the type to convert Name too.
 *  @param output_name the resulting type, release with
 *         gss_release_name(), independent of input_name.
 *
 *  @returns a gss_error code, see gss_display_status() about printing
 *         the error code.
 *
 *  @ingroup gssapi
 */

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_canonicalize_name (
	OM_uint32 * __nonnull minor_status,
	__nonnull const gss_name_t input_name,
	__nonnull const gss_OID mech_type,
	__nullable gss_name_t * __nonnull output_name)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_compare_name (
	OM_uint32 *__nonnull minor_status,
	__nonnull const gss_name_t name1_arg,
	__nonnull const gss_name_t name2_arg,
	int *__nonnull name_equal)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_context_time (
	OM_uint32 * __nonnull minor_status,
	__nonnull const gss_ctx_id_t context_handle,
	OM_uint32 * __nonnull time_rec)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_create_empty_buffer_set (
	OM_uint32 * __nonnull minor_status,
	__nullable gss_buffer_set_t *__nonnull buffer_set)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_create_empty_oid_set (
	OM_uint32 *__nonnull minor_status,
	__nullable gss_OID_set *__nonnull oid_set)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_decapsulate_token (
	__nonnull gss_const_buffer_t input_token,
	__nonnull gss_const_OID oid,
	__nonnull gss_buffer_t output_token)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_delete_sec_context (
	OM_uint32 * __nonnull minor_status,
	__nullable gss_ctx_id_t * __nonnull context_handle,
	__nullable gss_buffer_t output_token)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/**
 * Destroy a credential 
 *
 * gss_release_cred() frees the memory, gss_destroy_cred() removes the credentials from memory/disk and then call gss_release_cred() on the credential.
 *
 * @param min_stat minor status code
 * @param cred_handle credentail to destory
 *
 * @returns a gss_error code, see gss_display_status() about printing
 *          the error code.
 * 
 * @ingroup gssapi
 */

OM_uint32 GSSAPI_LIB_FUNCTION
gss_destroy_cred (
	OM_uint32 *__nonnull min_stat,
	__nullable gss_cred_id_t * __nonnull cred_handle)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/**
 * Return names and descriptions of mech attributes
 *
 * @param minor_status minor status code
 * @param mech_attr attributes wanted
 * @param name name of attribute
 * @param short_desc short description
 * @param long_desc long description
 *
 * @return returns GSS_S_COMPLETE or an error code.
 */

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_display_mech_attr (
	OM_uint32 * __nonnull minor_status,
	__nonnull gss_const_OID mech_attr,
	__nullable gss_buffer_t name,
	__nullable gss_buffer_t short_desc,
	__nullable gss_buffer_t long_desc)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/**
 * Create a representstion of a name suitable for display
 *
 * A name that is useful to print to user, not suitable for
 * authorization. For authorization use gss_authorize_localname(), or
 * gss_userok().
 *
 * @param minor_status minor status code returned
 * @param input_name name to be converted into a name
 * @param output_name_buffer output buffer with name, must be released with gss_release_buffer() on success.
 * @param output_name_type type OID of then name
 *
 * @returns GSS major status code
 *
 * @ingroup gssapi
 */

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_display_name (
	OM_uint32 *__nonnull minor_status,
	__nonnull const gss_name_t input_name,
	__nonnull gss_buffer_t output_name_buffer,
	__nullable gss_OID * __nullable output_name_type)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_display_status (
	OM_uint32 *__nonnull minor_status,
	OM_uint32 status_value,
	int status_type,
	__nullable const gss_OID mech_type,
	OM_uint32 *__nonnull message_content,
	__nonnull gss_buffer_t status_string)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_duplicate_name (
	OM_uint32 *__nonnull minor_status,
	__nonnull const gss_name_t src_name,
	__nullable gss_name_t * __nonnull dest_name)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_duplicate_oid (
	 OM_uint32 *__nonnull minor_status,
	__nonnull gss_OID src_oid,
	__nullable gss_OID * __nonnull dest_oid )  __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_7, __MAC_10_9, __IPHONE_5_0, __IPHONE_7_0, "Not standardised");

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_encapsulate_token (
	__nonnull gss_const_buffer_t input_token,
	__nonnull gss_const_OID oid,
	__nonnull gss_buffer_t output_token)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_export_cred (
	OM_uint32 * __nonnull minor_status,
	__nonnull gss_cred_id_t cred_handle,
	__nonnull gss_buffer_t token)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_export_name (
	OM_uint32 *__nonnull minor_status,
	__nonnull const gss_name_t input_name,
	__nonnull gss_buffer_t exported_name)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_export_sec_context (
	OM_uint32 *__nonnull minor_status,
	__nullable gss_ctx_id_t * __nonnull context_handle,
	__nullable gss_buffer_t interprocess_token)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_get_mic (
	OM_uint32 *__nonnull minor_status,
	__nonnull const gss_ctx_id_t context_handle,
	gss_qop_t qop_req,
	__nonnull const gss_buffer_t message_buffer,
	__nonnull gss_buffer_t message_token)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_import_cred (
	OM_uint32 * __nonnull minor_status,
	__nonnull gss_buffer_t token,
	__nullable gss_cred_id_t * __nonnull cred_handle)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/**
 * Import a name internal or mechanism name
 *
 * Type of name and their format:
 * - GSS_C_NO_OID
 * - GSS_C_NT_USER_NAME
 * - GSS_C_NT_HOSTBASED_SERVICE
 * - GSS_C_NT_EXPORT_NAME
 * - GSS_C_NT_ANONYMOUS
 * - GSS_KRB5_NT_PRINCIPAL_NAME
 *
 * For more information about @ref internalVSmechname.
 *
 * @param minor_status minor status code
 * @param input_name_buffer import name buffer
 * @param input_name_type type of the import name buffer
 * @param output_name the resulting type, release with
 *        gss_release_name(), independent of input_name
 *
 * @returns a gss_error code, see gss_display_status() about printing
 *        the error code.
 *
 * @ingroup gssapi
 */

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_import_name (
	OM_uint32 *__nonnull minor_status,
	__nonnull const gss_buffer_t input_name_buffer,
	__nullable gss_const_OID input_name_type,
	__nullable gss_name_t * __nonnull output_name)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/**
	 * If we can't find a mechanism name for the name, we fail though.
 */

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_import_sec_context (
	OM_uint32 *__nonnull minor_status,
	__nonnull const gss_buffer_t interprocess_token,
	__nullable gss_ctx_id_t * __nonnull context_handle)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_indicate_mechs (
	OM_uint32 *__nonnull minor_status,
	__nullable gss_OID_set * __nonnull mech_set)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/**
 * Return set of mechanism that fullfill the criteria
 *
 * @return returns GSS_S_COMPLETE or an error code.
 */

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_indicate_mechs_by_attrs (
	OM_uint32 * __nonnull minor_status,
	__nullable gss_const_OID_set desired_mech_attrs,
	__nullable gss_const_OID_set except_mech_attrs,
	__nullable gss_const_OID_set critical_mech_attrs,
	__nullable gss_OID_set * __nonnull mechs)  __OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);

/**
 * As the initiator build a context with an acceptor.
 *
 * This function is blocking and should not be used on threads blocking UI updates.
 *
 * Returns in the major
 * - GSS_S_COMPLETE - if the context if build
 * - GSS_S_CONTINUE_NEEDED -  if the caller needs  to continue another
 *	round of gss_i nit_sec_context
 * - error code - any other error code
 *
 * @param minor_status minor status code.
 *
 * @param initiator_cred_handle the credential to use when building
 *        the context, if GSS_C_NO_CREDENTIAL is passed, the default
 *        credential for the mechanism will be used.
 *
 * @param context_handle a pointer to a context handle, will be
 * 	  returned as long as there is not an error.
 *
 * @param target_name the target name of acceptor, created using
 * 	  gss_import_name(). The name is can be of any name types the
 * 	  mechanism supports, check supported name types with
 * 	  gss_inquire_names_for_mech().
 *
 * @param input_mech_type mechanism type to use, if GSS_C_NO_OID is
 *        used, Kerberos (GSS_KRB5_MECHANISM) will be tried. Other
 *        available mechanism are listed in the @ref gssapi_mechs_intro
 *        section.
 *
 * @param req_flags flags using when building the context, see @ref
 *        gssapi_context_flags
 *
 * @param time_req time requested this context should be valid in
 *        seconds, common used value is GSS_C_INDEFINITE
 *
 * @param input_chan_bindings Channel bindings used, if not exepected
 *        otherwise, used GSS_C_NO_CHANNEL_BINDINGS
 *
 * @param input_token input token sent from the acceptor, for the
 * 	  initial packet the buffer of { NULL, 0 } should be used.
 *
 * @param actual_mech_type the actual mech used, MUST NOT be freed
 *        since it pointing to static memory.
 *
 * @param output_token if there is an output token, regardless of
 * 	  complete, continue_needed, or error it should be sent to the
 * 	  acceptor
 *
 * @param ret_flags return what flags was negotitated, caller should
 * 	  check if they are accetable. For example, if
 * 	  GSS_C_MUTUAL_FLAG was negotiated with the acceptor or not.
 *
 * @param time_rec amount of time this context is valid for
 *
 * @returns a gss_error code, see gss_display_status() about printing
 *          the error code.
 *
 * @ingroup gssapi
 */

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_init_sec_context (
	OM_uint32 * __nonnull minor_status,
	__nullable const gss_cred_id_t initiator_cred_handle,
	__nullable gss_ctx_id_t * __nonnull context_handle,
	__nonnull const gss_name_t target_name,
	__nullable const gss_OID input_mech_type,
	OM_uint32 req_flags,
	OM_uint32 time_req,
	__nullable const gss_channel_bindings_t input_chan_bindings,
	__nullable const gss_buffer_t input_token,
	__nullable gss_OID * __nullable actual_mech_type,
	__nonnull gss_buffer_t output_token,
	OM_uint32 * __nullable ret_flags,
	OM_uint32 * __nullable time_rec)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/**
 * List support attributes for a mech and/or all mechanisms.
 *
 * @param minor_status minor status code
 * @param mech given together with mech_attr will return the list of
 *        attributes for mechanism, can optionally be GSS_C_NO_OID.
 * @param mech_attr see mech parameter, can optionally be NULL,
 *        release with gss_release_oid_set().
 * @param known_mech_attrs all attributes for mechanisms supported,
 *        release with gss_release_oid_set().
 *
 * @ingroup gssapi
 */

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_inquire_attrs_for_mech (
	OM_uint32 * __nonnull minor_status,
	__nonnull gss_const_OID mech,
	__nullable gss_OID_set *__nullable mech_attr,
	__nullable gss_OID_set *__nullable known_mech_attrs)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_inquire_context (
	OM_uint32 *__nonnull minor_status,
	__nonnull const gss_ctx_id_t context_handle,
	__nullable gss_name_t * __nullable src_name,
	__nullable gss_name_t * __nullable targ_name,
	OM_uint32 * __nullable lifetime_rec,
	__nullable gss_OID * __nullable mech_type,
	OM_uint32 * __nullable ctx_flags,
	int * __nullable locally_initiated,
	int * __nullable xopen)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_inquire_cred (
	OM_uint32 * __nonnull minor_status,
	__nullable const gss_cred_id_t cred_handle,
	__nullable gss_name_t * __nullable name_ret,
	OM_uint32 * __nullable lifetime,
	gss_cred_usage_t * __nullable cred_usage,
	__nullable gss_OID_set * __nullable mechanisms)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_inquire_cred_by_mech (
	OM_uint32 * __nonnull minor_status,
	__nullable const gss_cred_id_t cred_handle,
	__nonnull const gss_OID mech_type,
	__nullable gss_name_t * __nullable cred_name,
	OM_uint32 *__nullable initiator_lifetime,
	OM_uint32 *__nullable acceptor_lifetime,
	gss_cred_usage_t *__nullable cred_usage)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_inquire_cred_by_oid (
	OM_uint32 *__nonnull minor_status,
	__nonnull const gss_cred_id_t cred_handle,
	__nonnull const gss_OID desired_object,
	__nullable gss_buffer_set_t * __nonnull data_set)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/**
 * Find a mech for a sasl name
 *
 * @param minor_status minor status code
 * @param sasl_mech_name sasl mech name
 * @param mech_type mech type
 *
 * @return returns GSS_S_COMPLETE or an error code.
 */

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_inquire_mech_for_saslname (
	OM_uint32 *__nonnull minor_status,
	__nullable const gss_buffer_t sasl_mech_name,
	__nullable gss_OID * __nonnull mech_type)  __OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_inquire_mechs_for_name (
	OM_uint32 *__nonnull minor_status,
	__nonnull const gss_name_t input_name,
	__nullable gss_OID_set * __nonnull mech_types)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_inquire_name (
	OM_uint32 *__nonnull minor_status,
	__nonnull gss_name_t input_name,
	int *__nonnull name_is_MN,
	__nullable gss_OID * __nullable MN_mech,
	__nullable gss_buffer_set_t * __nullable attrs)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_inquire_names_for_mech (
	OM_uint32 *__nonnull minor_status,
	__nonnull gss_const_OID mechanism,
	__nullable gss_OID_set * __nonnull name_types)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/**
 * Returns different protocol names and description of the mechanism.
 *
 * @param minor_status minor status code
 * @param desired_mech mech list query
 * @param sasl_mech_name SASL GS2 protocol name
 * @param mech_name gssapi protocol name
 * @param mech_description description of gssapi mech
 *
 * @return returns GSS_S_COMPLETE or a error code.
 *
 * @ingroup gssapi
 */

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_inquire_saslname_for_mech (
	OM_uint32 *__nonnull minor_status,
	__nonnull const gss_OID desired_mech,
	__nullable gss_buffer_t sasl_mech_name,
	__nullable gss_buffer_t mech_name,
	__nullable gss_buffer_t mech_description)  __OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_inquire_sec_context_by_oid (
	OM_uint32 *__nonnull minor_status,
	__nonnull const gss_ctx_id_t context_handle,
	__nonnull const gss_OID desired_object,
	__nonnull gss_buffer_set_t * __nullable data_set)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/**
 * Iterate over all credentials
 *
 * @param min_stat set to minor status in case of an error
 * @param flags flags argument, no flags currently defined, pass in 0 (zero)
 * @param mech the mechanism type of credentials to iterate over, by passing in GSS_C_NO_OID, the function will iterate over all credentails
 * @param useriter block that will be called on each gss_cred_id_t, when NULL is passed the list is completed. Must free the credential with gss_release_cred().
 *
 * @ingroup gssapi
 */

#ifdef __BLOCKS__
OM_uint32 GSSAPI_LIB_FUNCTION
gss_iter_creds (
	OM_uint32 *__nonnull min_stat,
	OM_uint32 flags,
	__nullable gss_const_OID mech,
	void (^__nonnull useriter)(__nullable gss_iter_OID, __nullable gss_cred_id_t))  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);
#endif /* __BLOCKS__ */

/**
 * Iterate over all credentials
 *
 * @param min_stat set to minor status in case of an error
 * @param flags flags argument, no flags currently defined, pass in 0 (zero)
 * @param mech the mechanism type of credentials to iterate over, by passing in GSS_C_NO_OID, the function will iterate over all credentails
 * @param userctx user context passed to the useriter funcion
 * @param useriter function that will be called on each gss_cred_id_t, when NULL is passed the list is completed. Must free the credential with gss_release_cred().
 *
 * @ingroup gssapi
 */

OM_uint32 GSSAPI_LIB_FUNCTION
gss_iter_creds_f (
	OM_uint32 *__nonnull min_stat,
	OM_uint32 flags,
	__nullable gss_const_OID mech,
	void * __nullable userctx,
	void (*__nonnull useriter)(void *__nullable , __nullable gss_iter_OID, __nullable gss_cred_id_t))  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_krb5_ccache_name (
	OM_uint32 *__nonnull minor_status,
	const char *__nullable name,
	const char *__nullable *__nullable out_name)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_krb5_copy_ccache (
	OM_uint32 * __nonnull minor_status,
	__nonnull gss_cred_id_t cred,
	struct krb5_ccache_data *__nonnull out)  __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_7, __MAC_10_9, __IPHONE_5_0, __IPHONE_7_0, "Use gss_export_cred");

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_krb5_export_lucid_sec_context (
	OM_uint32 *__nonnull minor_status,
	__nullable gss_ctx_id_t * __nonnull context_handle,
	OM_uint32 version,
	void *__nonnull * __nullable rctx)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_krb5_free_lucid_sec_context (
	OM_uint32 * __nonnull minor_status,
	void *__nonnull c)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_krb5_set_allowable_enctypes (
	OM_uint32 *__nonnull minor_status,
	__nonnull gss_cred_id_t cred,
	OM_uint32 num_enctypes,
	int32_t *__nonnull enctypes)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/**
 * Compare two GSS-API OIDs with each other.
 *
 * GSS_C_NO_OID matches nothing, not even it-self.
 *
 * @param a first oid to compare
 * @param b second oid to compare
 *
 * @return non-zero when both oid are the same OID, zero when they are
 *         not the same.
 *
 * @ingroup gssapi
 */

GSSAPI_LIB_FUNCTION int GSSAPI_LIB_CALL
gss_oid_equal (
	__nullable gss_const_OID a,
	__nullable gss_const_OID b)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/**
 * Turn an mech OID into an name
 *
 * Try to turn a OID into a mechanism name. If a matching OID can't be
 * found, this function will return NULL.
 *
 * The caller must free the oid_str buffer with gss_release_buffer()
 * when done with the string.
 *	  
 * @param minor_status an minor status code
 * @param oid an oid
 * @param oid_str buffer that will point to a NUL terminated string that is the numreric OID
 *
 * @returns a gss major status code
 *
 * @ingroup gssapi
 */

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_oid_to_str (
	OM_uint32 *__nonnull minor_status,
	__nonnull gss_OID oid,
	__nonnull gss_buffer_t oid_str)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_process_context_token (
	OM_uint32 *__nonnull minor_status,
	__nonnull const gss_ctx_id_t context_handle,
	__nonnull const gss_buffer_t token_buffer)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_pseudo_random (
	OM_uint32 *__nonnull minor_status,
	__nonnull gss_ctx_id_t context,
	int prf_key,
	__nonnull const gss_buffer_t prf_in,
	ssize_t desired_output_len,
	__nonnull gss_buffer_t prf_out)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_release_buffer (
	OM_uint32 *__nonnull minor_status,
	__nonnull gss_buffer_t buffer)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_release_buffer_set (
	OM_uint32 * __nonnull minor_status,
	__nullable gss_buffer_set_t * __nonnull  buffer_set)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/**
 * Release a credentials
 *
 * Its ok to release the GSS_C_NO_CREDENTIAL/NULL credential, it will
 * return a GSS_S_COMPLETE error code. On return cred_handle is set ot
 * GSS_C_NO_CREDENTIAL.
 *
 * Example:
 *
 * @code
 * gss_cred_id_t cred = GSS_C_NO_CREDENTIAL;
 * major = gss_release_cred(&minor, &cred);
 * @endcode
 *
 * @param minor_status minor status return code, mech specific
 * @param cred_handle a pointer to the credential too release
 *
 * @return an gssapi error code
 *
 * @ingroup gssapi
 */

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_release_cred (
	OM_uint32 *__nonnull minor_status,
	__nullable gss_cred_id_t * __nonnull cred_handle)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/**
 * Free a name
 *
 * import_name can point to NULL or be NULL, or a pointer to a
 * gss_name_t structure. If it was a pointer to gss_name_t, the
 * pointer will be set to NULL on success and failure.
 *
 * @param minor_status minor status code
 * @param input_name name to free
 *
 * @returns a gss_error code, see gss_display_status() about printing
 *        the error code.
 *
 * @ingroup gssapi
 */

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_release_name (
	OM_uint32 *__nonnull minor_status,
	__nullable gss_name_t * __nonnull input_name)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/**
 * Release a gss_OID
 *
 * This function should never be used, this is since many of the
 * gss_OID objects passed around are stack and data objected that are
 * not free-able.
 *
 * The function tries to find internal OIDs that are static and avoid
 * trying to free them.
 *
 * One could guess that gss_name_to_oid() might return an allocated
 * OID.  In this implementation it wont, so there is no need to call
 * gss_release_oid().
 *
 * @param minor_status minor status code returned
 * @param oid oid to be released/freed.
 *
 * @returns GSS major status code
 *
 * @ingroup gssapi
 */

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_release_oid (
	OM_uint32 *__nonnull minor_status,
	__nullable gss_OID * __nonnull oid)  __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_7, __MAC_10_9, __IPHONE_5_0, __IPHONE_7_0, "Not standardised and not safe to call for most gss_OIDs");

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_release_oid_set (
	OM_uint32 *__nonnull minor_status,
	__nullable gss_OID_set * __nonnull set)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_seal (
	OM_uint32 *__nonnull minor_status,
	__nonnull gss_ctx_id_t context_handle,
	int conf_req_flag,
	int qop_req,
	__nonnull gss_buffer_t input_message_buffer,
	int *__nonnull conf_state,
	__nonnull gss_buffer_t output_message_buffer)  __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_7, __MAC_10_9, __IPHONE_5_0, __IPHONE_7_0, "Use gss_wrap");

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_set_cred_option (
	OM_uint32 *__nonnull minor_status,
	__nullable gss_cred_id_t * __nullable cred_handle,
	__nonnull const gss_OID object,
	__nullable const gss_buffer_t value)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_set_sec_context_option (
	OM_uint32 *__nonnull minor_status,
	__nonnull gss_ctx_id_t * __nullable context_handle,
	__nonnull const gss_OID object,
	__nullable const gss_buffer_t value)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_sign (
	OM_uint32 *__nonnull minor_status,
	__nonnull gss_ctx_id_t context_handle,
	int qop_req,
	__nonnull gss_buffer_t message_buffer,
	__nonnull gss_buffer_t message_token)  __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_7, __MAC_10_9, __IPHONE_5_0, __IPHONE_7_0, "Use gss_get_mic");

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_test_oid_set_member (
	OM_uint32 *__nonnull minor_status,
	__nonnull gss_const_OID member,
	__nonnull const gss_OID_set set,
	int *__nonnull present)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_unseal (
	OM_uint32 *__nonnull minor_status,
	__nonnull gss_ctx_id_t context_handle,
	__nonnull gss_buffer_t input_message_buffer,
	__nonnull gss_buffer_t output_message_buffer,
	int *__nonnull conf_state,
	int *__nonnull qop_state)  __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_7, __MAC_10_9, __IPHONE_5_0, __IPHONE_7_0, "Use gss_unwrap");

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_unwrap (
	OM_uint32 *__nonnull minor_status,
	__nonnull const gss_ctx_id_t context_handle,
	__nonnull const gss_buffer_t input_message_buffer,
	__nonnull gss_buffer_t output_message_buffer,
	int * __nullable conf_state,
	gss_qop_t *__nullable qop_state)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION int GSSAPI_LIB_CALL
gss_userok (
	__nonnull const gss_name_t name,
	const char *__nonnull user)  __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_verify (
	OM_uint32 *__nonnull minor_status,
	__nonnull gss_ctx_id_t context_handle,
	__nonnull gss_buffer_t message_buffer,
	__nonnull gss_buffer_t token_buffer,
	int *__nonnull qop_state)  __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_7, __MAC_10_9, __IPHONE_5_0, __IPHONE_7_0, "Use gss_verify_mic");

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_verify_mic (
	OM_uint32 *__nonnull minor_status,
	__nonnull const gss_ctx_id_t context_handle,
	__nonnull const gss_buffer_t message_buffer,
	__nonnull const gss_buffer_t token_buffer,
	gss_qop_t * __nullable qop_state)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/**
 * Wrap a message using either confidentiality (encryption +
 * signature) or sealing (signature).
 *
 * @param minor_status minor status code.
 * @param context_handle context handle.
 * @param conf_req_flag if non zero, confidentiality is requestd.
 * @param qop_req type of protection needed, in most cases it GSS_C_QOP_DEFAULT should be passed in.
 * @param input_message_buffer messages to wrap
 * @param conf_state returns non zero if confidentiality was honoured.
 * @param output_message_buffer the resulting buffer, release with gss_release_buffer().
 *
 * @ingroup gssapi
 */

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_wrap (
	OM_uint32 *__nonnull minor_status,
	__nonnull const gss_ctx_id_t context_handle,
	int conf_req_flag,
	gss_qop_t qop_req,
	__nonnull const gss_buffer_t input_message_buffer,
	int *__nullable conf_state,
	__nonnull gss_buffer_t output_message_buffer)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_wrap_size_limit (
	OM_uint32 *__nonnull minor_status,
	__nonnull const gss_ctx_id_t context_handle,
	int conf_req_flag,
	gss_qop_t qop_req,
	OM_uint32 req_output_size,
	OM_uint32 *__nonnull max_input_size)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gsskrb5_extract_authz_data_from_sec_context (
	OM_uint32 *__nonnull minor_status,
	__nonnull gss_ctx_id_t context_handle,
	int ad_type,
	__nonnull gss_buffer_t ad_data)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gsskrb5_register_acceptor_identity (const char *__nonnull identity)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
krb5_gss_register_acceptor_identity (const char *__nonnull identity)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

#ifdef __cplusplus
}
#endif

#endif /* __gssapi_protos_h__ */
