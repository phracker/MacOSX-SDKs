/* This is a generated file */
#ifndef __gssapi_protos_h__
#define __gssapi_protos_h__

#include <stdarg.h>

#ifndef GSSAPI_DEPRECATED_FUNCTION
#ifndef __has_extension
#define __has_extension(x) 0
#define GSSAPI_DEPRECATED_FUNCTIONhas_extension 1
#endif
#if __has_extension(attribute_deprecated_with_message)
#define GSSAPI_DEPRECATED_FUNCTION(x) __attribute__((__deprecated__(x)))
#elif defined(__GNUC__) && ((__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1 )))
#define GSSAPI_DEPRECATED_FUNCTION(X) __attribute__((__deprecated__))
#else
#define GSSAPI_DEPRECATED_FUNCTION(X)
#endif
#ifdef GSSAPI_DEPRECATED_FUNCTIONhas_extension
#undef __has_extension
#undef GSSAPI_DEPRECATED_FUNCTIONhas_extension
#endif
#endif /* GSSAPI_DEPRECATED_FUNCTION */


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
GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_accept_sec_context (
	OM_uint32 */*minor_status*/,
	gss_ctx_id_t */*context_handle*/,
	const gss_cred_id_t /*acceptor_cred_handle*/,
	const gss_buffer_t /*input_token*/,
	const gss_channel_bindings_t /*input_chan_bindings*/,
	gss_name_t */*src_name*/,
	gss_OID */*mech_type*/,
	gss_buffer_t /*output_token*/,
	OM_uint32 */*ret_flags*/,
	OM_uint32 */*time_rec*/,
	gss_cred_id_t */*delegated_cred_handle*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_acquire_cred (
	OM_uint32 */*minor_status*/,
	const gss_name_t /*desired_name*/,
	OM_uint32 /*time_req*/,
	const gss_OID_set /*desired_mechs*/,
	gss_cred_usage_t /*cred_usage*/,
	gss_cred_id_t */*output_cred_handle*/,
	gss_OID_set */*actual_mechs*/,
	OM_uint32 */*time_rec*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_acquire_cred_with_password (
	OM_uint32 */*minor_status*/,
	const gss_name_t /*desired_name*/,
	const gss_buffer_t /*password*/,
	OM_uint32 /*time_req*/,
	const gss_OID_set /*desired_mechs*/,
	gss_cred_usage_t /*cred_usage*/,
	gss_cred_id_t */*output_cred_handle*/,
	gss_OID_set */*actual_mechs*/,
	OM_uint32 */*time_rec*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_add_buffer_set_member (
	OM_uint32 * /*minor_status*/,
	const gss_buffer_t /*member_buffer*/,
	gss_buffer_set_t */*buffer_set*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_add_cred (
	OM_uint32 */*minor_status*/,
	const gss_cred_id_t /*input_cred_handle*/,
	const gss_name_t /*desired_name*/,
	const gss_OID /*desired_mech*/,
	gss_cred_usage_t /*cred_usage*/,
	OM_uint32 /*initiator_time_req*/,
	OM_uint32 /*acceptor_time_req*/,
	gss_cred_id_t */*output_cred_handle*/,
	gss_OID_set */*actual_mechs*/,
	OM_uint32 */*initiator_time_rec*/,
	OM_uint32 */*acceptor_time_rec*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_add_oid_set_member (
	OM_uint32 * /*minor_status*/,
	gss_const_OID /*member_oid*/,
	gss_OID_set * /*oid_set*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_canonicalize_name (
	OM_uint32 */*minor_status*/,
	const gss_name_t /*input_name*/,
	const gss_OID /*mech_type*/,
	gss_name_t */*output_name*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_compare_name (
	OM_uint32 */*minor_status*/,
	const gss_name_t /*name1_arg*/,
	const gss_name_t /*name2_arg*/,
	int */*name_equal*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_context_time (
	OM_uint32 */*minor_status*/,
	const gss_ctx_id_t /*context_handle*/,
	OM_uint32 */*time_rec*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_create_empty_buffer_set (
	OM_uint32 * /*minor_status*/,
	gss_buffer_set_t */*buffer_set*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_create_empty_oid_set (
	OM_uint32 */*minor_status*/,
	gss_OID_set */*oid_set*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_decapsulate_token (
	gss_const_buffer_t /*input_token*/,
	gss_const_OID /*oid*/,
	gss_buffer_t /*output_token*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_delete_sec_context (
	OM_uint32 */*minor_status*/,
	gss_ctx_id_t */*context_handle*/,
	gss_buffer_t /*output_token*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

OM_uint32 GSSAPI_LIB_FUNCTION
gss_destroy_cred (
	OM_uint32 */*min_stat*/,
	gss_cred_id_t */*cred_handle*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_display_mech_attr (
	OM_uint32 * /*minor_status*/,
	gss_const_OID /*mech_attr*/,
	gss_buffer_t /*name*/,
	gss_buffer_t /*short_desc*/,
	gss_buffer_t /*long_desc*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_display_name (
	OM_uint32 */*minor_status*/,
	const gss_name_t /*input_name*/,
	gss_buffer_t /*output_name_buffer*/,
	gss_OID */*output_name_type*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_display_status (
	OM_uint32 */*minor_status*/,
	OM_uint32 /*status_value*/,
	int /*status_type*/,
	const gss_OID /*mech_type*/,
	OM_uint32 */*message_content*/,
	gss_buffer_t /*status_string*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_duplicate_name (
	OM_uint32 */*minor_status*/,
	const gss_name_t /*src_name*/,
	gss_name_t */*dest_name*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_duplicate_oid (
	 OM_uint32 */*minor_status*/,
	gss_OID /*src_oid*/,
	gss_OID *dest_oid )  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_encapsulate_token (
	gss_const_buffer_t /*input_token*/,
	gss_const_OID /*oid*/,
	gss_buffer_t /*output_token*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_export_cred (
	OM_uint32 * /*minor_status*/,
	gss_cred_id_t /*cred_handle*/,
	gss_buffer_t /*token*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_export_name (
	OM_uint32 */*minor_status*/,
	const gss_name_t /*input_name*/,
	gss_buffer_t /*exported_name*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_export_sec_context (
	OM_uint32 */*minor_status*/,
	gss_ctx_id_t */*context_handle*/,
	gss_buffer_t /*interprocess_token*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_get_mic (
	OM_uint32 */*minor_status*/,
	const gss_ctx_id_t /*context_handle*/,
	gss_qop_t /*qop_req*/,
	const gss_buffer_t /*message_buffer*/,
	gss_buffer_t /*message_token*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_import_cred (
	OM_uint32 * /*minor_status*/,
	gss_buffer_t /*token*/,
	gss_cred_id_t * /*cred_handle*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_import_name (
	OM_uint32 */*minor_status*/,
	const gss_buffer_t /*input_name_buffer*/,
	gss_const_OID /*input_name_type*/,
	gss_name_t */*output_name*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_import_sec_context (
	OM_uint32 */*minor_status*/,
	const gss_buffer_t /*interprocess_token*/,
	gss_ctx_id_t */*context_handle*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_indicate_mechs (
	OM_uint32 */*minor_status*/,
	gss_OID_set */*mech_set*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_init_sec_context (
	OM_uint32 * /*minor_status*/,
	const gss_cred_id_t /*initiator_cred_handle*/,
	gss_ctx_id_t * /*context_handle*/,
	const gss_name_t /*target_name*/,
	const gss_OID /*input_mech_type*/,
	OM_uint32 /*req_flags*/,
	OM_uint32 /*time_req*/,
	const gss_channel_bindings_t /*input_chan_bindings*/,
	const gss_buffer_t /*input_token*/,
	gss_OID * /*actual_mech_type*/,
	gss_buffer_t /*output_token*/,
	OM_uint32 * /*ret_flags*/,
	OM_uint32 * /*time_rec*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_inquire_attrs_for_mech (
	OM_uint32 * /*minor_status*/,
	gss_const_OID /*mech*/,
	gss_OID_set */*mech_attr*/,
	gss_OID_set */*known_mech_attrs*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_inquire_context (
	OM_uint32 */*minor_status*/,
	const gss_ctx_id_t /*context_handle*/,
	gss_name_t */*src_name*/,
	gss_name_t */*targ_name*/,
	OM_uint32 */*lifetime_rec*/,
	gss_OID */*mech_type*/,
	OM_uint32 */*ctx_flags*/,
	int */*locally_initiated*/,
	int */*xopen*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_inquire_cred (
	OM_uint32 */*minor_status*/,
	const gss_cred_id_t /*cred_handle*/,
	gss_name_t */*name_ret*/,
	OM_uint32 */*lifetime*/,
	gss_cred_usage_t */*cred_usage*/,
	gss_OID_set */*mechanisms*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_inquire_cred_by_mech (
	OM_uint32 */*minor_status*/,
	const gss_cred_id_t /*cred_handle*/,
	const gss_OID /*mech_type*/,
	gss_name_t */*cred_name*/,
	OM_uint32 */*initiator_lifetime*/,
	OM_uint32 */*acceptor_lifetime*/,
	gss_cred_usage_t */*cred_usage*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_inquire_cred_by_oid (
	OM_uint32 */*minor_status*/,
	const gss_cred_id_t /*cred_handle*/,
	const gss_OID /*desired_object*/,
	gss_buffer_set_t */*data_set*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_inquire_mechs_for_name (
	OM_uint32 */*minor_status*/,
	const gss_name_t /*input_name*/,
	gss_OID_set */*mech_types*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_inquire_names_for_mech (
	OM_uint32 */*minor_status*/,
	gss_const_OID /*mechanism*/,
	gss_OID_set */*name_types*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_inquire_sec_context_by_oid (
	OM_uint32 */*minor_status*/,
	const gss_ctx_id_t /*context_handle*/,
	const gss_OID /*desired_object*/,
	gss_buffer_set_t */*data_set*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

#ifdef __BLOCKS__
OM_uint32 GSSAPI_LIB_FUNCTION
gss_iter_creds (
	OM_uint32 */*min_stat*/,
	OM_uint32 /*flags*/,
	gss_const_OID /*mech*/,
	void (^useriter)(gss_iter_OID, gss_cred_id_t))  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);
#endif /* __BLOCKS__ */

OM_uint32 GSSAPI_LIB_FUNCTION
gss_iter_creds_f (
	OM_uint32 */*min_stat*/,
	OM_uint32 /*flags*/,
	gss_const_OID /*mech*/,
	void * /*userctx*/,
	void (*/*useriter*/)(void *, gss_iter_OID, gss_cred_id_t))  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_krb5_ccache_name (
	OM_uint32 */*minor_status*/,
	const char */*name*/,
	const char **/*out_name*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_krb5_copy_ccache (
	OM_uint32 */*minor_status*/,
	gss_cred_id_t /*cred*/,
	struct krb5_ccache_data */*out*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0)  GSSAPI_DEPRECATED_FUNCTION("Use gss_export_cred");

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_krb5_export_lucid_sec_context (
	OM_uint32 */*minor_status*/,
	gss_ctx_id_t */*context_handle*/,
	OM_uint32 /*version*/,
	void **/*rctx*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_krb5_free_lucid_sec_context (
	OM_uint32 */*minor_status*/,
	void */*c*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_krb5_set_allowable_enctypes (
	OM_uint32 */*minor_status*/,
	gss_cred_id_t /*cred*/,
	OM_uint32 /*num_enctypes*/,
	int32_t */*enctypes*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION int GSSAPI_LIB_CALL
gss_oid_equal (
	gss_const_OID /*a*/,
	gss_const_OID /*b*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_oid_to_str (
	OM_uint32 */*minor_status*/,
	gss_OID /*oid*/,
	gss_buffer_t /*oid_str*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_process_context_token (
	OM_uint32 */*minor_status*/,
	const gss_ctx_id_t /*context_handle*/,
	const gss_buffer_t /*token_buffer*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_pseudo_random (
	OM_uint32 */*minor_status*/,
	gss_ctx_id_t /*context*/,
	int /*prf_key*/,
	const gss_buffer_t /*prf_in*/,
	ssize_t /*desired_output_len*/,
	gss_buffer_t /*prf_out*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_release_buffer (
	OM_uint32 */*minor_status*/,
	gss_buffer_t /*buffer*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_release_buffer_set (
	OM_uint32 * /*minor_status*/,
	gss_buffer_set_t */*buffer_set*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_release_cred (
	OM_uint32 */*minor_status*/,
	gss_cred_id_t */*cred_handle*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_release_name (
	OM_uint32 */*minor_status*/,
	gss_name_t */*input_name*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_release_oid (
	OM_uint32 */*minor_status*/,
	gss_OID */*oid*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_release_oid_set (
	OM_uint32 */*minor_status*/,
	gss_OID_set */*set*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_seal (
	OM_uint32 */*minor_status*/,
	gss_ctx_id_t /*context_handle*/,
	int /*conf_req_flag*/,
	int /*qop_req*/,
	gss_buffer_t /*input_message_buffer*/,
	int */*conf_state*/,
	gss_buffer_t /*output_message_buffer*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0)  GSSAPI_DEPRECATED_FUNCTION("Use gss_wrap");

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_set_cred_option (
	OM_uint32 */*minor_status*/,
	gss_cred_id_t */*cred_handle*/,
	const gss_OID /*object*/,
	const gss_buffer_t /*value*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_set_sec_context_option (
	OM_uint32 */*minor_status*/,
	gss_ctx_id_t */*context_handle*/,
	const gss_OID /*object*/,
	const gss_buffer_t /*value*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_sign (
	OM_uint32 */*minor_status*/,
	gss_ctx_id_t /*context_handle*/,
	int /*qop_req*/,
	gss_buffer_t /*message_buffer*/,
	gss_buffer_t /*message_token*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0)  GSSAPI_DEPRECATED_FUNCTION("Use gss_get_mic");

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_test_oid_set_member (
	OM_uint32 */*minor_status*/,
	gss_const_OID /*member*/,
	const gss_OID_set /*set*/,
	int */*present*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_unseal (
	OM_uint32 */*minor_status*/,
	gss_ctx_id_t /*context_handle*/,
	gss_buffer_t /*input_message_buffer*/,
	gss_buffer_t /*output_message_buffer*/,
	int */*conf_state*/,
	int */*qop_state*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0)  GSSAPI_DEPRECATED_FUNCTION("Use gss_unwrap");

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_unwrap (
	OM_uint32 */*minor_status*/,
	const gss_ctx_id_t /*context_handle*/,
	const gss_buffer_t /*input_message_buffer*/,
	gss_buffer_t /*output_message_buffer*/,
	int */*conf_state*/,
	gss_qop_t */*qop_state*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_verify (
	OM_uint32 */*minor_status*/,
	gss_ctx_id_t /*context_handle*/,
	gss_buffer_t /*message_buffer*/,
	gss_buffer_t /*token_buffer*/,
	int */*qop_state*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0)  GSSAPI_DEPRECATED_FUNCTION("Use gss_verify_mic");

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_verify_mic (
	OM_uint32 */*minor_status*/,
	const gss_ctx_id_t /*context_handle*/,
	const gss_buffer_t /*message_buffer*/,
	const gss_buffer_t /*token_buffer*/,
	gss_qop_t */*qop_state*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_wrap (
	OM_uint32 */*minor_status*/,
	const gss_ctx_id_t /*context_handle*/,
	int /*conf_req_flag*/,
	gss_qop_t /*qop_req*/,
	const gss_buffer_t /*input_message_buffer*/,
	int */*conf_state*/,
	gss_buffer_t /*output_message_buffer*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gss_wrap_size_limit (
	OM_uint32 */*minor_status*/,
	const gss_ctx_id_t /*context_handle*/,
	int /*conf_req_flag*/,
	gss_qop_t /*qop_req*/,
	OM_uint32 /*req_output_size*/,
	OM_uint32 */*max_input_size*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gsskrb5_extract_authz_data_from_sec_context (
	OM_uint32 */*minor_status*/,
	gss_ctx_id_t /*context_handle*/,
	int /*ad_type*/,
	gss_buffer_t /*ad_data*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
gsskrb5_register_acceptor_identity (const char */*identity*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

GSSAPI_LIB_FUNCTION OM_uint32 GSSAPI_LIB_CALL
krb5_gss_register_acceptor_identity (const char */*identity*/)  __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

#ifdef __cplusplus
}
#endif

#undef GSSAPI_DEPRECATED_FUNCTION

#endif /* __gssapi_protos_h__ */
