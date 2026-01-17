/**
 * @copyright
 * ====================================================================
 * Copyright (c) 2000-2004 CollabNet.  All rights reserved.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at http://subversion.tigris.org/license-1.html.
 * If newer versions of this license are posted there, you may use a
 * newer version instead, at your option.
 *
 * This software consists of voluntary contributions made by many
 * individuals.  For exact contribution history, see the revision
 * history and logs, available at http://subversion.tigris.org/.
 * ====================================================================
 * @endcopyright
 *
 * @file svn_cmdline.h
 * @brief Support functions for command line programs
 */




#ifndef SVN_CMDLINE_H
#define SVN_CMDLINE_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define APR_WANT_STDIO
#endif
#include <apr_want.h>
#include <apr_getopt.h>

#include "svn_utf.h"
#include "svn_auth.h"
#include "svn_config.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/** Set up the locale for character conversion, and initialize APR.
 * If @a error_stream is non-null, print error messages to the stream,
 * using @a progname as the program name. Return @c EXIT_SUCCESS if
 * successful, otherwise @c EXIT_FAILURE.
 *
 * @note This function should be called exactly once at program startup,
 *       before calling any other APR or Subversion functions.
 */
int svn_cmdline_init(const char *progname, FILE *error_stream);


/** Set @a *dest to an output-encoded C string from UTF-8 C string @a
 * src; allocate @a *dest in @a pool.
 */
svn_error_t *svn_cmdline_cstring_from_utf8(const char **dest,
                                           const char *src,
                                           apr_pool_t *pool);

/** Like svn_utf_cstring_from_utf8_fuzzy(), but converts to an
 * output-encoded C string. */
const char *svn_cmdline_cstring_from_utf8_fuzzy(const char *src,
                                                apr_pool_t *pool);

/** Set @a *dest to a UTF-8-encoded C string from input-encoded C
 * string @a src; allocate @a *dest in @a pool.
 */
svn_error_t * svn_cmdline_cstring_to_utf8(const char **dest,
                                          const char *src,
                                          apr_pool_t *pool);

/** Set @a *dest to an output-encoded natively-formatted path string
 * from canonical path @a src; allocate @a *dest in @a pool.
 */
svn_error_t *svn_cmdline_path_local_style_from_utf8(const char **dest,
                                                    const char *src,
                                                    apr_pool_t *pool);

/** Write to stdout, using a printf-like format string @a fmt, passed
 * through apr_pvsprintf().  All string arguments are in UTF-8; the output
 * is converted to the output encoding.  Use @a pool for temporary
 * allocation.
 *
 * @since New in 1.1.
 */
svn_error_t *svn_cmdline_printf(apr_pool_t *pool,
                                const char *fmt,
                                ...)
       __attribute__((format(printf, 2, 3)));

/** Write to the stdio @a stream, using a printf-like format string @a fmt,
 * passed through apr_pvsprintf().  All string arguments are in UTF-8;
 * the output is converted to the output encoding.  Use @a pool for
 * temporary allocation.
 *
 * @since New in 1.1.
 */
svn_error_t *svn_cmdline_fprintf(FILE *stream,
                                 apr_pool_t *pool,
                                 const char *fmt,
                                 ...)
       __attribute__((format(printf, 3, 4)));

/** Output the @a string to the stdio @a stream, converting from UTF-8
 * to the output encoding.  Use @a pool for temporary allocation.
 *
 * @since New in 1.1.
 */
svn_error_t *svn_cmdline_fputs(const char *string,
                               FILE *stream,
                               apr_pool_t *pool);

/** Flush output buffers of the stdio @a stream, returning an error if that
 * fails.  This is just a wrapper for the standard fflush() function for
 * consistent error handling. 
 *
 * @since New in 1.1.
 */
svn_error_t *svn_cmdline_fflush(FILE *stream);

/** Return the name of the output encoding allocated in @a pool, or @c
 * APR_LOCALE_CHARSET if the output encoding is the same as the locale
 * encoding.
 *
 * @since New in 1.3.
 */
const char *svn_cmdline_output_encoding(apr_pool_t *pool);

/** Handle @a error in preparation for immediate exit from a
 * command-line client.  Specifically:
 *
 * Call svn_handle_error2(@a error, stderr, FALSE, @a prefix), clear
 * @a error, destroy @a pool iff it is non-NULL, and return EXIT_FAILURE.
 *
 * @since New in 1.3.
 */
int svn_cmdline_handle_exit_error(svn_error_t *error,
                                  apr_pool_t *pool,
                                  const char *prefix);

/** Prompt the user for input, using @a prompt_str for the prompt and
 * returning the user's response in @a result, allocated in @a pool.
 *
 * @since New in 1.4.
 */
svn_error_t *
svn_cmdline_prompt_user(const char **result,
                        const char *prompt_str,
                        apr_pool_t *pool);

/** A cancellation function/baton pair to be passed as the baton argument
 * to the @c svn_cmdline_*_prompt functions.
 *
 * @since New in 1.4.
 */
typedef struct svn_cmdline_prompt_baton_t {
  svn_cancel_func_t cancel_func;
  void *cancel_baton;
} svn_cmdline_prompt_baton_t;

/** An implementation of @c svn_auth_simple_prompt_func_t that prompts
 * the user for keyboard input on the command line.
 *
 * @since New in 1.4.
 *
 * Expects a @c svn_cmdline_prompt_baton_t to be passed as @a baton.
 */
svn_error_t *
svn_cmdline_auth_simple_prompt(svn_auth_cred_simple_t **cred_p,
                               void *baton,
                               const char *realm,
                               const char *username,
                               svn_boolean_t may_save,
                               apr_pool_t *pool);


/** An implementation of @c svn_auth_username_prompt_func_t that prompts
 * the user for their username via the command line.
 *
 * @since New in 1.4.
 *
 * Expects a @c svn_cmdline_prompt_baton_t to be passed as @a baton.
 */
svn_error_t *
svn_cmdline_auth_username_prompt(svn_auth_cred_username_t **cred_p,
                                 void *baton,
                                 const char *realm,
                                 svn_boolean_t may_save,
                                 apr_pool_t *pool);


/** An implementation of @c svn_auth_ssl_server_trust_prompt_func_t that
 * asks the user if they trust a specific ssl server via the command line.
 *
 * @since New in 1.4.
 *
 * Expects a @c svn_cmdline_prompt_baton_t to be passed as @a baton.
 */
svn_error_t *
svn_cmdline_auth_ssl_server_trust_prompt
  (svn_auth_cred_ssl_server_trust_t **cred_p,
   void *baton,
   const char *realm,
   apr_uint32_t failures,
   const svn_auth_ssl_server_cert_info_t *cert_info,
   svn_boolean_t may_save,
   apr_pool_t *pool);


/** An implementation of @c svn_auth_ssl_client_cert_prompt_func_t that
 * prompts the user for the filename of their SSL client certificate via
 * the command line.
 *
 * @since New in 1.4.
 *
 * Expects a @c svn_cmdline_prompt_baton_t to be passed as @a baton.
 */
svn_error_t *
svn_cmdline_auth_ssl_client_cert_prompt
  (svn_auth_cred_ssl_client_cert_t **cred_p,
   void *baton,
   const char *realm,
   svn_boolean_t may_save,
   apr_pool_t *pool);


/** An implementation of @c svn_auth_ssl_client_cert_pw_prompt_func_t that
 * prompts the user for their SSL certificate password via the command line.
 *
 * @since New in 1.4.
 *
 * Expects a @c svn_cmdline_prompt_baton_t to be passed as @a baton.
 */
svn_error_t *
svn_cmdline_auth_ssl_client_cert_pw_prompt
  (svn_auth_cred_ssl_client_cert_pw_t **cred_p,
   void *baton,
   const char *realm,
   svn_boolean_t may_save,
   apr_pool_t *pool);

/** Initialize auth baton @a ab with the standard set of authentication
 * providers used by the command line client.  @a non_interactive,
 * @a username, @a password, @a config_dir, and @a auth_cache are the 
 * values of the command line options of the same names.  @a cfg is the
 * @c SVN_CONFIG_CATEGORY_CONFIG configuration, and @a cancel_func and
 * @a cancel_baton control the cancellation of the prompting providers
 * that are initialized.  @a pool is used for all allocations.
 *
 * @since New in 1.4.
 */
svn_error_t *
svn_cmdline_setup_auth_baton(svn_auth_baton_t **ab,
                             svn_boolean_t non_interactive,
                             const char *username,
                             const char *password,
                             const char *config_dir,
                             svn_boolean_t no_auth_cache,
                             svn_config_t *cfg,
                             svn_cancel_func_t cancel_func,
                             void *cancel_baton,
                             apr_pool_t *pool);

/** Wrapper for apr_getopt_init(), which see.
 *
 * @since New in 1.4.
 * 
 * On OS400 V5R4, prior to calling apr_getopt_init(), converts each of the
 * @a argc strings in @a argv[] in place from EBCDIC to UTF-8, allocating
 * each new UTF-8 string in @a pool.
 *
 * This is a private API for Subversion's own use.
 */
svn_error_t *
svn_cmdline__getopt_init(apr_getopt_t **os,
                         int argc,
                         const char *argv[],
                         apr_pool_t *pool);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SVN_CMDLINE_H */
