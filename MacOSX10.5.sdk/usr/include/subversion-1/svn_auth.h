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
 * @file svn_auth.h
 * @brief Subversion's authentication system
 */

#ifndef SVN_AUTH_H
#define SVN_AUTH_H

#include <apr_pools.h>

#include "svn_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Overview of the svn authentication system.
 *    
 * We define an authentication "provider" as a module that is able to
 * return a specific set of credentials. (e.g. username/password,
 * certificate, etc.)  Each provider implements a vtable that
 *
 * - can fetch initial credentials
 * - can retry the fetch (or try to fetch something different)
 * - can store the credentials for future use
 *
 * For any given type of credentials, there can exist any number of
 * separate providers -- each provider has a different method of
 * fetching. (i.e. from a disk store, by prompting the user, etc.)
 *
 * The application begins by creating an auth baton object, and
 * "registers" some number of providers with the auth baton, in a
 * specific order.  (For example, it may first register a
 * username/password provider that looks in disk store, then register
 * a username/password provider that prompts the user.)
 *
 * Later on, when any svn library is challenged, it asks the auth
 * baton for the specific credentials.  If the initial credentials
 * fail to authenticate, the caller keeps requesting new credentials.
 * Under the hood, libsvn_auth effectively "walks" over each provider
 * (in order of registry), one at a time, until all the providers have
 * exhausted all their retry options.
 *
 * This system allows an application to flexibly define authentication
 * behaviors (by changing registration order), and very easily write
 * new authentication providers.
 *
 * An auth_baton also contains an internal hashtable of run-time
 * parameters; any provider or library layer can set these run-time
 * parameters at any time, so that the provider has access to the
 * data.  (For example, certain run-time data may not be available
 * until an authentication challenge is made.)  Each credential type
 * must document the run-time parameters that are made available to
 * its providers.
 *
 * @defgroup auth_fns authentication functions
 * @{
 */


/** The type of a Subversion authentication object */
typedef struct svn_auth_baton_t svn_auth_baton_t;

/** The type of a Subversion authentication-iteration object */
typedef struct svn_auth_iterstate_t svn_auth_iterstate_t;


/** The main authentication "provider" vtable. */
typedef struct svn_auth_provider_t
{
  /** The kind of credentials this provider knows how to retrieve. */
  const char *cred_kind;
  
  /** Get an initial set of credentials.
   *
   * Set @a *credentials to a set of valid credentials within @a
   * realmstring, or NULL if no credentials are available.  Set @a
   * *iter_baton to context that allows a subsequent call to @c
   * next_credentials, in case the first credentials fail to
   * authenticate.  @a provider_baton is general context for the
   * vtable, @a parameters contains any run-time data that the
   * provider may need, and @a realmstring comes from the
   * svn_auth_first_credentials() call.
   */
  svn_error_t * (*first_credentials)(void **credentials,
                                     void **iter_baton,
                                     void *provider_baton,
                                     apr_hash_t *parameters,
                                     const char *realmstring,
                                     apr_pool_t *pool);

  /** Get a different set of credentials.
   *
   * Set @a *credentials to another set of valid credentials (using @a
   * iter_baton as the context from previous call to first_credentials
   * or next_credentials).  If no more credentials are available, set
   * @a *credentials to NULL.  If the provider only has one set of
   * credentials, this function pointer should simply be NULL. @a
   * provider_baton is general context for the vtable, @a parameters
   * contains any run-time data that the provider may need, and @a
   * realmstring comes from the svn_auth_first_credentials() call.
   */
  svn_error_t * (*next_credentials)(void **credentials,
                                    void *iter_baton,
                                    void *provider_baton,
                                    apr_hash_t *parameters,
                                    const char *realmstring,
                                    apr_pool_t *pool);
  
  /** Save credentials.
   *
   * Store @a credentials for future use.  @a provider_baton is
   * general context for the vtable, and @a parameters contains any
   * run-time data the provider may need.  Set @a *saved to true if
   * the save happened, or false if not.  The provider is not required
   * to save; if it refuses or is unable to save for non-fatal
   * reasons, return false.  If the provider never saves data, then
   * this function pointer should simply be NULL. @a realmstring comes
   * from the svn_auth_first_credentials() call.
   */
  svn_error_t * (*save_credentials)(svn_boolean_t *saved,
                                    void *credentials,
                                    void *provider_baton,
                                    apr_hash_t *parameters,
                                    const char *realmstring,
                                    apr_pool_t *pool);
  
} svn_auth_provider_t;


/** A provider object, ready to be put into an array and given to
    svn_auth_open(). */
typedef struct svn_auth_provider_object_t
{
  const svn_auth_provider_t *vtable;
  void *provider_baton;

} svn_auth_provider_object_t;



/** Specific types of credentials **/

/** Simple username/password pair credential kind.
 *
 * The following auth parameters may be available to the providers:
 *
 * - @c SVN_AUTH_PARAM_NO_AUTH_CACHE (@c void*)
 * - @c SVN_AUTH_PARAM_DEFAULT_USERNAME (@c char*)
 * - @c SVN_AUTH_PARAM_DEFAULT_PASSWORD (@c char*)
 */
#define SVN_AUTH_CRED_SIMPLE "svn.simple"

/** @c SVN_AUTH_CRED_SIMPLE credentials. */
typedef struct svn_auth_cred_simple_t
{
  /** Username */
  const char *username;
  /** Password */
  const char *password;
  /** Indicates if the credentials may be saved (to disk). For example, a
   * GUI prompt implementation with a remember password checkbox shall set
   * @a may_save to TRUE if the checkbox is checked.
   */
  svn_boolean_t may_save;
} svn_auth_cred_simple_t;


/** Username credential kind.
 *
 * The following optional auth parameters are relevant to the providers:
 *
 * - @c SVN_AUTH_PARAM_NO_AUTH_CACHE (@c void*)
 * - @c SVN_AUTH_PARAM_DEFAULT_USERNAME (@c char*)
 */
#define SVN_AUTH_CRED_USERNAME "svn.username"

/** @c SVN_AUTH_CRED_USERNAME credentials. */
typedef struct svn_auth_cred_username_t
{
  /** Username */
  const char *username;
  /** Indicates if the credentials may be saved (to disk). For example, a
   * GUI prompt implementation with a remember username checkbox shall set
   * @a may_save to TRUE if the checkbox is checked.
   */
  svn_boolean_t may_save;
} svn_auth_cred_username_t;


/** SSL client certificate credential type.
 *
 * The following auth parameters are available to the providers:
 *
 * - @c SVN_AUTH_PARAM_CONFIG (@c svn_config_t*)
 * - @c SVN_AUTH_PARAM_SERVER_GROUP (@c char*)
 *
 * The following optional auth parameters are relevant to the providers:
 *
 * - @c SVN_AUTH_PARAM_NO_AUTH_CACHE (@c void*)
 */
#define SVN_AUTH_CRED_SSL_CLIENT_CERT "svn.ssl.client-cert"

/** @c SVN_AUTH_CRED_SSL_CLIENT_CERT credentials. */
typedef struct svn_auth_cred_ssl_client_cert_t
{
  /** Full paths to the certificate file */
  const char *cert_file;
  /** Indicates if the credentials may be saved (to disk). For example, a
   * GUI prompt implementation with a remember certificate checkbox shall
   * set @a may_save to TRUE if the checkbox is checked.
   */
  svn_boolean_t may_save;
} svn_auth_cred_ssl_client_cert_t;


/** SSL client certificate passphrase credential type.
 *
 * @note The realmstring used with this credential type must be a name that
 * makes it possible for the user to identify the certificate.
 *
 * The following auth parameters are available to the providers:
 *
 * - @c SVN_AUTH_PARAM_CONFIG (@c svn_config_t*)
 * - @c SVN_AUTH_PARAM_SERVER_GROUP (@c char*)
 *
 * The following optional auth parameters are relevant to the providers:
 *
 * - @c SVN_AUTH_PARAM_NO_AUTH_CACHE (@c void*)
 */
#define SVN_AUTH_CRED_SSL_CLIENT_CERT_PW "svn.ssl.client-passphrase"

/** @c SVN_AUTH_CRED_SSL_CLIENT_CERT_PW credentials. */
typedef struct svn_auth_cred_ssl_client_cert_pw_t
{
  /** Certificate password */
  const char *password;
  /** Indicates if the credentials may be saved (to disk). For example, a
   * GUI prompt implementation with a remember password checkbox shall set
   * @a may_save to TRUE if the checkbox is checked.
   */
  svn_boolean_t may_save;
} svn_auth_cred_ssl_client_cert_pw_t;


/** SSL server verification credential type.
 *
 * The following auth parameters are available to the providers:
 *
 * - @c SVN_AUTH_PARAM_CONFIG (@c svn_config_t*)
 * - @c SVN_AUTH_PARAM_SERVER_GROUP (@c char*)
 * - @c SVN_AUTH_PARAM_SSL_SERVER_FAILURES (@c apr_uint32_t*)
 * - @c SVN_AUTH_PARAM_SSL_SERVER_CERT_INFO
 *      (@c svn_auth_ssl_server_cert_info_t*)
 *
 * The following optional auth parameters are relevant to the providers:
 *
 * - @c SVN_AUTH_PARAM_NO_AUTH_CACHE (@c void*)
 */
#define SVN_AUTH_CRED_SSL_SERVER_TRUST "svn.ssl.server"

/** SSL server certificate information used by @c
 * SVN_AUTH_CRED_SSL_SERVER_TRUST providers.
 */
typedef struct svn_auth_ssl_server_cert_info_t 
{
  /** Primary CN */
  const char *hostname;
  /** ASCII fingerprint */
  const char *fingerprint;
  /** ASCII date from which the certificate is valid */
  const char *valid_from;
  /** ASCII date until which the certificate is valid */
  const char *valid_until;
  /** DN of the certificate issuer */
  const char *issuer_dname;
  /** Base-64 encoded DER certificate representation */
  const char *ascii_cert;
} svn_auth_ssl_server_cert_info_t;

/**
 * Return a deep copy of @a info, allocated in @a pool.
 *
 * @since New in 1.3.
 */
svn_auth_ssl_server_cert_info_t *
svn_auth_ssl_server_cert_info_dup(const svn_auth_ssl_server_cert_info_t *info,
                                  apr_pool_t *pool);

/** @c SVN_AUTH_CRED_SSL_SERVER_TRUST credentials. */
typedef struct svn_auth_cred_ssl_server_trust_t
{
  /** Indicates if the credentials may be saved (to disk). For example, a
   * GUI prompt implementation with a checkbox to accept the certificate
   * permanently shall set @a may_save to TRUE if the checkbox is checked.
   */
  svn_boolean_t may_save;
  /** Bit mask of the accepted failures */
  apr_uint32_t accepted_failures;
} svn_auth_cred_ssl_server_trust_t;



/** Credential-constructing prompt functions. **/

/** These exist so that different client applications can use
 * different prompt mechanisms to supply the same credentials.  For
 * example, if authentication requires a username and password, a
 * command-line client's prompting function might prompt first for the
 * username and then for the password, whereas a GUI client's would
 * present a single dialog box asking for both, and a telepathic
 * client's would read all the information directly from the user's
 * mind.  All these prompting functions return the same type of
 * credential, but the information used to construct the credential is
 * gathered in an interface-specific way in each case.
 */

/** Set @a *cred by prompting the user, allocating @a *cred in @a pool.
 * @a baton is an implementation-specific closure.
 *
 * If @a realm is non-null, maybe use it in the prompt string.
 *
 * If @a username is non-null, then the user might be prompted only
 * for a password, but @a *cred would still be filled with both
 * username and password.  For example, a typical usage would be to
 * pass @a username on the first call, but then leave it null for
 * subsequent calls, on the theory that if credentials failed, it's
 * as likely to be due to incorrect username as incorrect password.
 *
 * If @a may_save is FALSE, the auth system does not allow the credentials
 * to be saved (to disk). A prompt function shall not ask the user if the
 * credentials shall be saved if @a may_save is FALSE. For example, a GUI
 * client with a remember password checkbox would grey out the checkbox if
 * @a may_save is FALSE.
 */
typedef svn_error_t *(*svn_auth_simple_prompt_func_t)
  (svn_auth_cred_simple_t **cred,
   void *baton,
   const char *realm,
   const char *username,
   svn_boolean_t may_save,
   apr_pool_t *pool);


/** Set @a *cred by prompting the user, allocating @a *cred in @a pool.
 * @a baton is an implementation-specific closure.
 *
 * If @a realm is non-null, maybe use it in the prompt string.
 *
 * If @a may_save is FALSE, the auth system does not allow the credentials
 * to be saved (to disk). A prompt function shall not ask the user if the
 * credentials shall be saved if @a may_save is FALSE. For example, a GUI
 * client with a remember username checkbox would grey out the checkbox if
 * @a may_save is FALSE.
 */
typedef svn_error_t *(*svn_auth_username_prompt_func_t)
  (svn_auth_cred_username_t **cred,
   void *baton,
   const char *realm,
   svn_boolean_t may_save,
   apr_pool_t *pool);


/** @name SSL server certificate failure bits
 *
 * @note These values are stored in the on disk auth cache by the SSL
 * server certificate auth provider, so the meaning of these bits must
 * not be changed.
 * @{
 */
/** Certificate is not yet valid. */
#define SVN_AUTH_SSL_NOTYETVALID 0x00000001
/** Certificate has expired. */
#define SVN_AUTH_SSL_EXPIRED     0x00000002
/** Certificate's CN (hostname) does not match the remote hostname. */
#define SVN_AUTH_SSL_CNMISMATCH  0x00000004
/** @brief Certificate authority is unknown (i.e. not trusted) */
#define SVN_AUTH_SSL_UNKNOWNCA   0x00000008
/** @brief Other failure. This can happen if neon has introduced a new
 * failure bit that we do not handle yet. */
#define SVN_AUTH_SSL_OTHER       0x40000000
/** @} */

/** Set @a *cred by prompting the user, allocating @a *cred in @a pool.
 * @a baton is an implementation-specific closure.
 *
 * @a cert_info is a structure describing the server cert that was
 * presented to the client, and @a failures is a bitmask that
 * describes exactly why the cert could not be automatically validated,
 * composed from the constants SVN_AUTH_SSL_* (@c SVN_AUTH_SSL_NOTYETVALID
 * etc.).  @a realm is a string that can be used in the prompt string.
 *
 * If @a may_save is FALSE, the auth system does not allow the credentials
 * to be saved (to disk). A prompt function shall not ask the user if the
 * credentials shall be saved if @a may_save is FALSE. For example, a GUI
 * client with a trust permanently checkbox would grey out the checkbox if
 * @a may_save is FALSE.
 */
typedef svn_error_t *(*svn_auth_ssl_server_trust_prompt_func_t)
  (svn_auth_cred_ssl_server_trust_t **cred,
   void *baton,
   const char *realm,
   apr_uint32_t failures,
   const svn_auth_ssl_server_cert_info_t *cert_info,
   svn_boolean_t may_save,
   apr_pool_t *pool);


/** Set @a *cred by prompting the user, allocating @a *cred in @a pool.
 * @a baton is an implementation-specific closure.  @a realm is a string
 * that can be used in the prompt string.
 *
 * If @a may_save is FALSE, the auth system does not allow the credentials
 * to be saved (to disk). A prompt function shall not ask the user if the
 * credentials shall be saved if @a may_save is FALSE. For example, a GUI
 * client with a remember certificate checkbox would grey out the checkbox
 * if @a may_save is FALSE.
 */
typedef svn_error_t *(*svn_auth_ssl_client_cert_prompt_func_t)
  (svn_auth_cred_ssl_client_cert_t **cred,
   void *baton,
   const char *realm,
   svn_boolean_t may_save,
   apr_pool_t *pool);


/** Set @a *cred by prompting the user, allocating @a *cred in @a pool.
 * @a baton is an implementation-specific closure.  @a realm is a string
 * identifying the certificate, and can be used in the prompt string.
 *
 * If @a may_save is FALSE, the auth system does not allow the credentials
 * to be saved (to disk). A prompt function shall not ask the user if the
 * credentials shall be saved if @a may_save is FALSE. For example, a GUI
 * client with a remember password checkbox would grey out the checkbox if
 * @a may_save is FALSE.
 */
typedef svn_error_t *(*svn_auth_ssl_client_cert_pw_prompt_func_t)
  (svn_auth_cred_ssl_client_cert_pw_t **cred,
   void *baton,
   const char *realm,
   svn_boolean_t may_save,
   apr_pool_t *pool);



/** Initialize an authentication system.
 *
 * Return an authentication object in @a *auth_baton (allocated in @a
 * pool) that represents a particular instance of the svn
 * authentication system.  @a providers is an array of @c
 * svn_auth_provider_object_t pointers, already allocated in @a pool
 * and intentionally ordered.  These pointers will be stored within @a
 * *auth_baton, grouped by credential type, and searched in this exact
 * order.
 */
void svn_auth_open(svn_auth_baton_t **auth_baton,
                   apr_array_header_t *providers,
                   apr_pool_t *pool);

/** Set an authentication run-time parameter.
 *
 * Store @a name / @a value pair as a run-time parameter in @a
 * auth_baton, making the data accessible to all providers.  @a name
 * and @a value will NOT be duplicated into the auth_baton's pool.
 * To delete a run-time parameter, pass NULL for @a value.
 */
void svn_auth_set_parameter(svn_auth_baton_t *auth_baton,
                            const char *name,
                            const void *value);

/** Get an authentication run-time parameter.
 *
 * Return a value for run-time parameter @a name from @a auth_baton.
 * Return NULL if the parameter doesn't exist.
 */
const void * svn_auth_get_parameter(svn_auth_baton_t *auth_baton,
                                    const char *name);

/** Universal run-time parameters, made available to all providers.

    If you are writing a new provider, then to be a "good citizen",
    you should notice these global parameters!  Note that these
    run-time params should be treated as read-only by providers; the
    application is responsible for placing them into the auth_baton
    hash. */

/** The auth-hash prefix indicating that the parameter is global. */
#define SVN_AUTH_PARAM_PREFIX "svn:auth:"

/**
 * @name Default credentials defines
 * Any 'default' credentials that came in through the application itself,
 * (e.g. --username and --password options). Property values are
 * const char *.
 * @{ */
#define SVN_AUTH_PARAM_DEFAULT_USERNAME  SVN_AUTH_PARAM_PREFIX "username"
#define SVN_AUTH_PARAM_DEFAULT_PASSWORD  SVN_AUTH_PARAM_PREFIX "password"
/** @} */

/** @brief The application doesn't want any providers to prompt
 * users. Property value is irrelevant; only property's existence
 * matters. */
#define SVN_AUTH_PARAM_NON_INTERACTIVE  SVN_AUTH_PARAM_PREFIX "non-interactive"

/** @brief The application doesn't want any providers to save passwords
 * to disk. Property value is irrelevant; only property's existence
 * matters. */
#define SVN_AUTH_PARAM_DONT_STORE_PASSWORDS  SVN_AUTH_PARAM_PREFIX \
                                                 "dont-store-passwords"

/** @brief The application doesn't want any providers to save credentials
 * to disk. Property value is irrelevant; only property's existence
 * matters. */
#define SVN_AUTH_PARAM_NO_AUTH_CACHE  SVN_AUTH_PARAM_PREFIX "no-auth-cache"

/** @brief The following property is for SSL server cert providers. This
 * provides a pointer to an @c apr_uint32_t containing the failures
 * detected by the certificate validator. */
#define SVN_AUTH_PARAM_SSL_SERVER_FAILURES SVN_AUTH_PARAM_PREFIX \
  "ssl:failures"

/** @brief The following property is for SSL server cert providers. This
 * provides the cert info (svn_auth_ssl_server_cert_info_t). */
#define SVN_AUTH_PARAM_SSL_SERVER_CERT_INFO SVN_AUTH_PARAM_PREFIX \
  "ssl:cert-info"

/** Some providers need access to the @c svn_config_t configuration. */
#define SVN_AUTH_PARAM_CONFIG SVN_AUTH_PARAM_PREFIX "config"

/** The current server group. */
#define SVN_AUTH_PARAM_SERVER_GROUP SVN_AUTH_PARAM_PREFIX "server-group"

/** @brief A configuration directory that overrides the default
 * ~/.subversion. */
#define SVN_AUTH_PARAM_CONFIG_DIR SVN_AUTH_PARAM_PREFIX "config-dir"


/** Get an initial set of credentials.
 *
 * Ask @a auth_baton to set @a *credentials to a set of credentials
 * defined by @a cred_kind and valid within @a realmstring, or NULL if
 * no credentials are available.  Otherwise, return an iteration state
 * in @a *state, so that the caller can call
 * svn_auth_next_credentials(), in case the first set of credentials
 * fails to authenticate.
 *
 * Use @a pool to allocate @a *state, and for temporary allocation.
 * Note that @a *credentials will be allocated in @a auth_baton's pool.
 */
svn_error_t * svn_auth_first_credentials(void **credentials,
                                         svn_auth_iterstate_t **state,
                                         const char *cred_kind,
                                         const char *realmstring,
                                         svn_auth_baton_t *auth_baton,
                                         apr_pool_t *pool);

/** Get another set of credentials, assuming previous ones failed to
 * authenticate.
 *
 * Use @a state to fetch a different set of @a *credentials, as a
 * follow-up to svn_auth_first_credentials() or
 * svn_auth_next_credentials().  If no more credentials are available,
 * set @a *credentials to NULL.
 *
 * Note that @a *credentials will be allocated in @c auth_baton's pool.
 */
svn_error_t * svn_auth_next_credentials(void **credentials,
                                        svn_auth_iterstate_t *state,
                                        apr_pool_t *pool);

/** Save a set of credentials.
 *
 * Ask @a state to store the most recently returned credentials,
 * presumably because they successfully authenticated.  Use @a pool
 * for temporary allocation.  If no credentials were ever returned, do
 * nothing.
 */
svn_error_t * svn_auth_save_credentials(svn_auth_iterstate_t *state,
                                        apr_pool_t *pool);

/** @} */

/** Create and return @a *provider, an authentication provider of type
 * svn_auth_cred_simple_t that gets information by prompting the user
 * with @a prompt_func and @a prompt_baton.  Allocate @a *provider in
 * @a pool.
 *
 * If both @c SVN_AUTH_PARAM_DEFAULT_USERNAME and
 * @c SVN_AUTH_PARAM_DEFAULT_PASSWORD are defined as runtime
 * parameters in the @c auth_baton, then @a *provider will return the
 * default arguments when svn_auth_first_credentials() is called.  If
 * svn_auth_first_credentials() fails, then @a *provider will
 * re-prompt @a retry_limit times (via svn_auth_next_credentials()).
 *
 * @since New in 1.4.
 */
void
svn_auth_get_simple_prompt_provider(svn_auth_provider_object_t **provider,
                                    svn_auth_simple_prompt_func_t prompt_func,
                                    void *prompt_baton,
                                    int retry_limit,
                                    apr_pool_t *pool);


/** Create and return @a *provider, an authentication provider of type @c
 * svn_auth_cred_username_t that gets information by prompting the
 * user with @a prompt_func and @a prompt_baton.  Allocate @a *provider
 * in @a pool.
 *
 * If @c SVN_AUTH_PARAM_DEFAULT_USERNAME is defined as a runtime
 * parameter in the @c auth_baton, then @a *provider will return the
 * default argument when svn_auth_first_credentials() is called.  If
 * svn_auth_first_credentials() fails, then @a *provider will
 * re-prompt @a retry_limit times (via svn_auth_next_credentials()).
 *
 * @since New in 1.4.
 */
void svn_auth_get_username_prompt_provider
  (svn_auth_provider_object_t **provider,
   svn_auth_username_prompt_func_t prompt_func,
   void *prompt_baton,
   int retry_limit,
   apr_pool_t *pool);


/** Create and return @a *provider, an authentication provider of type @c
 * svn_auth_cred_simple_t that gets/sets information from the user's
 * ~/.subversion configuration directory.  Allocate @a *provider in
 * @a pool.
 *  
 * If a default username or password is available, @a *provider will
 * honor them as well, and return them when
 * svn_auth_first_credentials() is called.  (see @c
 * SVN_AUTH_PARAM_DEFAULT_USERNAME and @c
 * SVN_AUTH_PARAM_DEFAULT_PASSWORD). 
 *
 * @since New in 1.4.
 */
void svn_auth_get_simple_provider(svn_auth_provider_object_t **provider,
                                  apr_pool_t *pool);


#if defined(WIN32) || defined(DOXYGEN)
/**
 * Create and return @a *provider, an authentication provider of type @c
 * svn_auth_cred_simple_t that gets/sets information from the user's
 * ~/.subversion configuration directory.  Allocate @a *provider in
 * @a pool.
 *
 * This is like svn_client_get_simple_provider(), except that, when
 * running on Window 2000 or newer (or any other Windows version that
 * includes the CryptoAPI), the provider encrypts the password before
 * storing it to disk. On earlier versions of Windows, the provider
 * does nothing.
 *
 * @since New in 1.4.
 * @note This function is only available on Windows.
 *
 * @note An administrative password reset may invalidate the account's
 * secret key. This function will detect that situation and behave as
 * if the password were not cached at all.
 */
void
svn_auth_get_windows_simple_provider(svn_auth_provider_object_t **provider,
                                     apr_pool_t *pool);
#endif /* WIN32 || DOXYGEN */

#if defined(DARWIN) || defined(DOXYGEN)

/**
 * Create and return @a *provider, an authentication provider of type @c
 * svn_auth_cred_simple_t that gets/sets information from the user's
 * ~/.subversion configuration directory.  Allocate @a *provider in
 * @a pool.
 *
 * This is like svn_client_get_simple_provider(), except that the
 * password is stored in the Mac OS KeyChain.
 *
 * @since New in 1.4
 * @note This function is only available on Mac OS 10.2 and higher.
 */
void
svn_auth_get_keychain_simple_provider(svn_auth_provider_object_t **provider,
                                      apr_pool_t *pool);

#endif /* DARWIN || DOXYGEN */

/** Create and return @a *provider, an authentication provider of type @c
 * svn_auth_cred_username_t that gets/sets information from a user's
 * ~/.subversion configuration directory.  Allocate @a *provider in
 * @a pool.
 *
 * If a default username is available, @a *provider will honor it,
 * and return it when svn_auth_first_credentials() is called.  (See
 * @c SVN_AUTH_PARAM_DEFAULT_USERNAME.)
 *
 * @since New in 1.4.
 */
void svn_auth_get_username_provider(svn_auth_provider_object_t **provider,
                                    apr_pool_t *pool);


/** Create and return @a *provider, an authentication provider of type @c
 * svn_auth_cred_ssl_server_trust_t, allocated in @a pool.
 *
 * @a *provider retrieves its credentials from the configuration
 * mechanism.  The returned credential is used to override SSL
 * security on an error.
 *
 * @since New in 1.4.
 */
void svn_auth_get_ssl_server_trust_file_provider
  (svn_auth_provider_object_t **provider,
   apr_pool_t *pool);


/** Create and return @a *provider, an authentication provider of type @c
 * svn_auth_cred_ssl_client_cert_t, allocated in @a pool.
 *
 * @a *provider retrieves its credentials from the configuration
 * mechanism.  The returned credential is used to load the appropriate
 * client certificate for authentication when requested by a server.
 *
 * @since New in 1.4.
 */
void svn_auth_get_ssl_client_cert_file_provider
  (svn_auth_provider_object_t **provider,
   apr_pool_t *pool);


/** Create and return @a *provider, an authentication provider of type @c
 * svn_auth_cred_ssl_client_cert_pw_t, allocated in @a pool.
 *
 * @a *provider retrieves its credentials from the configuration
 * mechanism.  The returned credential is used when a loaded client
 * certificate is protected by a passphrase.
 *
 * @since New in 1.4.
 */
void svn_auth_get_ssl_client_cert_pw_file_provider
  (svn_auth_provider_object_t **provider,
   apr_pool_t *pool);


/** Create and return @a *provider, an authentication provider of type @c
 * svn_auth_cred_ssl_server_trust_t, allocated in @a pool.  
 *
 * @a *provider retrieves its credentials by using the @a prompt_func
 * and @a prompt_baton.  The returned credential is used to override
 * SSL security on an error.
 *
 * @since New in 1.4.
 */
void svn_auth_get_ssl_server_trust_prompt_provider
  (svn_auth_provider_object_t **provider,
   svn_auth_ssl_server_trust_prompt_func_t prompt_func,
   void *prompt_baton,
   apr_pool_t *pool);


/** Create and return @a *provider, an authentication provider of type @c
 * svn_auth_cred_ssl_client_cert_t, allocated in @a pool.
 *
 * @a *provider retrieves its credentials by using the @a prompt_func
 * and @a prompt_baton.  The returned credential is used to load the
 * appropriate client certificate for authentication when requested by
 * a server.  The prompt will be retried @a retry_limit times.
 *
 * @since New in 1.4.
 */
void svn_auth_get_ssl_client_cert_prompt_provider
  (svn_auth_provider_object_t **provider,
   svn_auth_ssl_client_cert_prompt_func_t prompt_func,
   void *prompt_baton,
   int retry_limit,
   apr_pool_t *pool);


/** Create and return @a *provider, an authentication provider of type @c
 * svn_auth_cred_ssl_client_cert_pw_t, allocated in @a pool.
 *
 * @a *provider retrieves its credentials by using the @a prompt_func
 * and @a prompt_baton.  The returned credential is used when a loaded
 * client certificate is protected by a passphrase.  The prompt will
 * be retried @a retry_limit times.
 *
 * @since New in 1.4.
 */
void svn_auth_get_ssl_client_cert_pw_prompt_provider
  (svn_auth_provider_object_t **provider,
   svn_auth_ssl_client_cert_pw_prompt_func_t prompt_func,
   void *prompt_baton,
   int retry_limit,
   apr_pool_t *pool);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SVN_AUTH_H */
