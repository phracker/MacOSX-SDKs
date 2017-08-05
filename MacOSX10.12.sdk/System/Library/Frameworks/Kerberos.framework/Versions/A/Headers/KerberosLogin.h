/*
* Copyright 2008 Massachusetts Institute of Technology.
* All Rights Reserved.
*
* Export of this software from the United States of America may
* require a specific license from the United States Government.
* It is the responsibility of any person or organization contemplating
* export to obtain such a license before exporting.
* 
* WITHIN THAT CONSTRAINT, permission to use, copy, modify, and
* distribute this software and its documentation for any purpose and
* without fee is hereby granted, provided that the above copyright
* notice appear in all copies and that both that copyright notice and
* this permission notice appear in supporting documentation, and that
* the name of M.I.T. not be used in advertising or publicity pertaining
* to distribution of the software without specific, written prior
* permission.  Furthermore if you modify this software you must label
* your software as modified software and not distribute it in such a
* fashion that it might be confused with the original M.I.T. software.
* M.I.T. makes no representations about the suitability of
* this software for any purpose.  It is provided "as is" without express
* or implied warranty.
*/

#ifndef __KERBEROSLOGIN__
#define __KERBEROSLOGIN__

#if defined(macintosh) || (defined(__MACH__) && defined(__APPLE__))
#    include <TargetConditionals.h>
#    if TARGET_RT_MAC_CFM
#        error "Use KfM 4.0 SDK headers for CFM compilation."
#    endif
#endif

#ifndef __has_extension
#define __has_extension(x) 0
#endif

#ifndef KERBEROS_APPLE_DEPRECATED
#if __has_extension(attribute_deprecated_with_message)
#define KERBEROS_APPLE_DEPRECATED(x) __attribute__((deprecated(x)))
#elif __has_extension(deprecated)
#define KERBEROS_APPLE_DEPRECATED(x) __attribute__((deprecated))
#else
#define KERBEROS_APPLE_DEPRECATED(x)
#endif
#endif



#include <sys/types.h>
#include <Kerberos/krb5.h>

#ifdef __cplusplus
extern "C" {
#endif

#if TARGET_OS_MAC
#    pragma pack(push,2)
#endif

/* 
 * Kerberos version constants
 */
enum {
    kerberosVersion_Any		= 0,
    kerberosVersion_V4		= 1,
    kerberosVersion_V5		= 2,
    kerberosVersion_All		= 0xFFFFFFFF
};
typedef int32_t KLEKerberosVersion;

/* 
 * Dialog identifier constants 
 */
enum {
    loginLibrary_LoginDialog,
    loginLibrary_OptionsDialog,
    loginLibrary_ChangePasswordDialog,
    loginLibrary_ProgressDialog,
    loginLibrary_PrompterDialog,
    loginLibrary_UnknownDialog = -1
};
typedef int32_t KLEDialogIdentifiers;


/* 
 * Option identifier constants 
 */
enum {
    /* Initial values and ranges */
    loginOption_LoginName                  = 'name',
    loginOption_LoginInstance              = 'inst',
    
    loginOption_RememberPrincipal          = 'prin',
    loginOption_RememberExtras             = 'extr',
    
    loginOption_MinimalTicketLifetime      = '-lif',
    loginOption_MaximalTicketLifetime      = '+lif',
    loginOption_DefaultTicketLifetime      = '0lif',
    
    loginOption_DefaultRenewableTicket     = '0rtx',
    loginOption_MinimalRenewableLifetime   = '-rlf',
    loginOption_MaximalRenewableLifetime   = '+rlf',
    loginOption_DefaultRenewableLifetime   = '0rlf',
    
    loginOption_DefaultForwardableTicket   = '0fwd',
    loginOption_DefaultProxiableTicket     = '0prx',
    loginOption_DefaultAddresslessTicket   = '0adr'    
};
typedef int32_t KLEDefaultLoginOptions;


/* 
 * Realm list constants 
 */
enum {
    realmList_Start  = 0,
    realmList_End    = 0xFFFF
};
typedef int32_t KLERealmListIndexes;

#define klFirstError 19276
#define klLastError  19876

/* 
 * Error codes 
 */
enum {
    klNoErr                             = 0,
    
    /* Parameter errors */
    klParameterErr                      = 19276,
    klBadPrincipalErr,
    klBadPasswordErr,
    klBadLoginOptionsErr,
    klInvalidVersionErr,
    klCapsLockErr,
    klBadV5ContextErr,
    
    /* Get/SetKerberosOption errors */
    klBufferTooSmallErr                 = 19376,
    klBufferTooLargeErr,
    klInvalidOptionErr,
    klBadOptionValueErr,
    
    /* Runtime Login errors */
    klUserCanceledErr                   = 19476,
    klMemFullErr,
    klPreferencesReadErr,
    klPreferencesWriteErr,
    klV5InitializationFailedErr,
    klPrincipalDoesNotExistErr,
    klSystemDefaultDoesNotExistErr,
    klCredentialsExpiredErr,
    klNoRealmsErr,
    klRealmDoesNotExistErr,
    klNoCredentialsErr,
    klCredentialsBadAddressErr,
    klCacheDoesNotExistErr,
    klNoHostnameErr,
    klCredentialsNeedValidationErr,
    
    /* Password changing errors */
    klPasswordMismatchErr               = 19576,
    klInsecurePasswordErr,
    klPasswordChangeFailedErr,
    
    /* Login IPC errors */
    klCantContactServerErr              = 19776,
    klCantDisplayUIErr,
    klServerInsecureErr
    
};
typedef int32_t KLEStatus;

/*
 * Types
 */

typedef	int32_t   KLStatus;               /* one of KLEStatus */
typedef	u_int32_t KLKerberosVersion;      /* one of KLEKerberosVersion */
typedef	u_int32_t KLDefaultLoginOption;   /* one of KLEDefaultLoginOptions */
typedef	u_int32_t KLLoginMode;            /* one of KLELoginMode */
typedef	u_int32_t KLDialogIdentifier;     /* one of KLEDialogIdentifiers */
typedef	u_int32_t KLIndex;                /* index (used for the realm list) */
typedef	u_int32_t KLLifetime;             /* Lifetime in seconds */
typedef	u_int32_t KLTime;                 /* Unix time (seconds since 1/1/1970 00:00:00 GMT) */
typedef	u_int32_t KLSize;                 /* size of a buffer */
typedef	u_int32_t KLRefCon;               /* application ref con */
typedef int8_t    KLBoolean;              /* true or false! (unsigned 8 byte value to match Boolean) */
typedef	int16_t   KLSInt16;               /* used for Darwin-compat for KLApplicationOptions */

/* Callback API for Kerberos Login Mach IPC idle filter */
typedef void (*KLIdleCallback) (KLRefCon appData);
#define CallKLIdleCallback(userRoutine, appData) ((userRoutine) (appData))

/* Principal information */
typedef struct kim_identity_opaque *KLPrincipal;

/* Login Options */
typedef struct kim_options_opaque *KLLoginOptions;

/*
 *
 * Functions
 *
 */

/* Deprecated functions -- provided for compatibility with KfM 4.0 */

KLStatus KLAcquireTickets (KLPrincipal   inPrincipal,
                           KLPrincipal  *outPrincipal,
                           char        **outCredCacheName) 
    KERBEROS_APPLE_DEPRECATED("use gssapi instead (gss_aapl_initial_cred)");

KLStatus KLAcquireNewTickets (KLPrincipal  inPrincipal,
                              KLPrincipal  *outPrincipal,
                              char        **outCredCacheName) 
    KERBEROS_APPLE_DEPRECATED("use gssapi instead (gss_aapl_initial_cred)");

KLStatus KLAcquireTicketsWithPassword (KLPrincipal      inPrincipal,
                                       KLLoginOptions   inLoginOptions,
                                       const char      *inPassword,
                                       char           **outCredCacheName) 
    KERBEROS_APPLE_DEPRECATED("use gssapi instead (gss_aapl_initial_cred)");

KLStatus KLAcquireNewTicketsWithPassword (KLPrincipal      inPrincipal,
                                          KLLoginOptions   inLoginOptions,
                                          const char      *inPassword,
                                          char           **outCredCacheName) 
    KERBEROS_APPLE_DEPRECATED("use gssapi instead (gss_aapl_initial_cred)");

KLStatus KLSetApplicationOptions (const void *inAppOptions) 
    KERBEROS_APPLE_DEPRECATED("no replacement");

KLStatus KLGetApplicationOptions (void *outAppOptions) 
    KERBEROS_APPLE_DEPRECATED("no replacement");


/* Kerberos Login high-level API */
KLStatus KLAcquireInitialTickets (KLPrincipal      inPrincipal,
                                  KLLoginOptions   inLoginOptions,
                                  KLPrincipal     *outPrincipal,
                                  char           **outCredCacheName)
    KERBEROS_APPLE_DEPRECATED("use gssapi instead (gss_aapl_initial_cred)");

KLStatus KLAcquireNewInitialTickets (KLPrincipal      inPrincipal,
                                     KLLoginOptions   inLoginOptions,
                                     KLPrincipal     *outPrincipal,
                                     char           **outCredCacheName)
    KERBEROS_APPLE_DEPRECATED("use gssapi instead (gss_aapl_initial_cred)");


KLStatus KLDestroyTickets (KLPrincipal inPrincipal)
    KERBEROS_APPLE_DEPRECATED("use gssapi instead (gss_destroy_cred)");


KLStatus KLChangePassword (KLPrincipal inPrincipal)
    KERBEROS_APPLE_DEPRECATED("no replacement");



/* Kerberos Login dialog low level functions */

KLStatus KLAcquireInitialTicketsWithPassword (KLPrincipal      inPrincipal,
                                              KLLoginOptions   inLoginOptions,
                                              const char      *inPassword,
                                              char           **outCredCacheName)
    KERBEROS_APPLE_DEPRECATED("use gssapi instead (gss_aapl_initial_cred)");


KLStatus KLAcquireNewInitialTicketsWithPassword (KLPrincipal      inPrincipal,
                                                 KLLoginOptions   inLoginOptions,
                                                 const char      *inPassword,
                                                 char           **outCredCacheName)
    KERBEROS_APPLE_DEPRECATED("use gssapi instead (gss_aapl_initial_cred)");


KLStatus KLAcquireNewInitialTicketCredentialsWithPassword (KLPrincipal      inPrincipal,
                                                           KLLoginOptions   inLoginOptions,
                                                           const char      *inPassword,
                                                           krb5_context     inV5Context,
                                                           KLBoolean       *outGotV4Credentials,
                                                           KLBoolean       *outGotV5Credentials,
                                                           void            *outV4Credentials,
                                                           krb5_creds      *outV5Credentials)
    KERBEROS_APPLE_DEPRECATED("use gssapi instead (gss_aapl_initial_cred)");


KLStatus KLStoreNewInitialTicketCredentials (KLPrincipal     inPrincipal,
                                             krb5_context    inV5Context,
                                             void           *inV4Credentials,
                                             krb5_creds     *inV5Credentials,
                                             char          **outCredCacheName)
    KERBEROS_APPLE_DEPRECATED("use gssapi instead (gss_aapl_initial_cred)");


KLStatus KLVerifyInitialTickets (KLPrincipal   inPrincipal,
                                 KLBoolean     inFailIfNoHostKey,
                                 char        **outCredCacheName)
    KERBEROS_APPLE_DEPRECATED("no replacement");


KLStatus KLVerifyInitialTicketCredentials (void        *inV4Credentials,
                                           krb5_creds  *inV5Credentials,
                                           KLBoolean    inFailIfNoHostKey)
    KERBEROS_APPLE_DEPRECATED("no replacement");

KLStatus KLAcquireNewInitialTicketsWithKeytab (KLPrincipal      inPrincipal,
                                               KLLoginOptions   inLoginOptions,
                                               const char      *inKeytabName,
                                               char           **outCredCacheName)
    KERBEROS_APPLE_DEPRECATED("use gssapi instead (gss_acquire_cred)");

KLStatus KLRenewInitialTickets (KLPrincipal      inPrincipal,
                                KLLoginOptions   inLoginOptions,
                                KLPrincipal     *outPrincipal,
                                char           **outCredCacheName)
    KERBEROS_APPLE_DEPRECATED("use gssapi instead (gss_aapl_initial_cred)");

KLStatus KLValidateInitialTickets (KLPrincipal      inPrincipal,
                                   KLLoginOptions   inLoginOptions,
                                   char           **outCredCacheName)
    KERBEROS_APPLE_DEPRECATED("use gssapi instead (gss_aapl_initial_cred)");


KLStatus KLLastChangedTime (KLTime *outLastChangedTime)
    KERBEROS_APPLE_DEPRECATED("use gssapi instead (gss_inquire_cred)");


KLStatus KLCacheHasValidTickets (KLPrincipal         inPrincipal,
                                 KLKerberosVersion   inKerberosVersion,
                                 KLBoolean          *outFoundValidTickets,
                                 KLPrincipal        *outPrincipal,
                                 char              **outCredCacheName)
    KERBEROS_APPLE_DEPRECATED("use gssapi instead (gss_inquire_cred)");

KLStatus KLTicketStartTime (KLPrincipal        inPrincipal,
                            KLKerberosVersion  inKerberosVersion,
                            KLTime            *outStartTime)
    KERBEROS_APPLE_DEPRECATED("use gssapi instead (gss_inquire_cred)");


KLStatus KLTicketExpirationTime (KLPrincipal        inPrincipal,
                                 KLKerberosVersion  inKerberosVersion,
                                 KLTime            *outExpirationTime)
    KERBEROS_APPLE_DEPRECATED("use gssapi instead (gss_inquire_cred)");


KLStatus KLSetSystemDefaultCache (KLPrincipal inPrincipal)
    KERBEROS_APPLE_DEPRECATED("use gssapi instead");


KLStatus KLHandleError (KLStatus           inError,
                        KLDialogIdentifier inDialogIdentifier,
                        KLBoolean          inShowAlert)
    KERBEROS_APPLE_DEPRECATED("no replacement");

KLStatus KLGetErrorString (KLStatus   inError,
                           char     **outErrorString)
    KERBEROS_APPLE_DEPRECATED("no replacement");

KLStatus KLCancelAllDialogs (void)
    KERBEROS_APPLE_DEPRECATED("no replacement");

/* Kerberos change password dialog low level functions */

KLStatus KLChangePasswordWithPasswords (KLPrincipal   inPrincipal,
                                        const char   *inOldPassword,
                                        const char   *inNewPassword,
                                        KLBoolean    *outRejected,
                                        char        **outRejectionError,
                                        char        **outRejectionDescription)
    KERBEROS_APPLE_DEPRECATED("no replacement");


/* Application Configuration functions */

KLStatus KLSetIdleCallback (const KLIdleCallback inCallback,
                            const KLRefCon inRefCon)
    KERBEROS_APPLE_DEPRECATED("no replacement");


KLStatus KLGetIdleCallback (KLIdleCallback* inCallback,
                            KLRefCon* inRefCon)
    KERBEROS_APPLE_DEPRECATED("no replacement");


/* Library configuration functions */

KLStatus KLGetDefaultLoginOption (const KLDefaultLoginOption  inOption,
                                  void                       *ioBuffer,
                                  KLSize                     *ioBufferSize)
    KERBEROS_APPLE_DEPRECATED("no replacement");


KLStatus KLSetDefaultLoginOption (const KLDefaultLoginOption  inOption,
                                  const void                 *inBuffer,
                                  const KLSize                inBufferSize)
    KERBEROS_APPLE_DEPRECATED("no replacement");


/* Realm configuration functions */

KLStatus KLFindKerberosRealmByName (const char *inRealmName,
                                    KLIndex    *outIndex)
    KERBEROS_APPLE_DEPRECATED("no replacement");


KLStatus KLGetKerberosRealm (KLIndex   inIndex,
                             char    **outRealmName)
    KERBEROS_APPLE_DEPRECATED("no replacement");


KLStatus KLSetKerberosRealm (KLIndex     inIndex,
                             const char *inRealmName)
    KERBEROS_APPLE_DEPRECATED("no replacement");


KLStatus KLRemoveKerberosRealm (KLIndex inIndex)
    KERBEROS_APPLE_DEPRECATED("no replacement");

KLStatus KLInsertKerberosRealm (KLIndex     inInsertBeforeIndex,
                                const char *inRealmName)
    KERBEROS_APPLE_DEPRECATED("no replacement");

KLStatus KLRemoveAllKerberosRealms (void)
    KERBEROS_APPLE_DEPRECATED("no replacement");

KLSize KLCountKerberosRealms (void)
    KERBEROS_APPLE_DEPRECATED("no replacement");

KLStatus KLGetKerberosDefaultRealm(KLIndex *outIndex)
    KERBEROS_APPLE_DEPRECATED("no replacement");

KLStatus KLGetKerberosDefaultRealmByName (char **outRealmName)
    KERBEROS_APPLE_DEPRECATED("no replacement");

KLStatus KLSetKerberosDefaultRealm (KLIndex inIndex)
    KERBEROS_APPLE_DEPRECATED("no replacement");

KLStatus KLSetKerberosDefaultRealmByName (const char *inRealm)
    KERBEROS_APPLE_DEPRECATED("no replacement");


/* KLPrincipal functions */

KLStatus KLCreatePrincipalFromTriplet (const char  *inName,
                                       const char  *inInstance,
                                       const char  *inRealm,
                                       KLPrincipal *outPrincipal)
    KERBEROS_APPLE_DEPRECATED("gss_import_name");


KLStatus KLCreatePrincipalFromString (const char        *inFullPrincipal,
                                      KLKerberosVersion  inKerberosVersion,
                                      KLPrincipal       *outPrincipal)
    KERBEROS_APPLE_DEPRECATED("gss_import_name");


KLStatus KLCreatePrincipalFromKerberos5Principal (krb5_principal  inKerberos5Principal,
                                                  KLPrincipal    *outPrincipal)
    KERBEROS_APPLE_DEPRECATED("gss_import_name");


KLStatus KLCreatePrincipalFromPrincipal (KLPrincipal inPrincipal,
                                         KLPrincipal *outPrincipal)
    KERBEROS_APPLE_DEPRECATED("gss_import_name");


KLStatus KLGetTripletFromPrincipal (KLPrincipal   inPrincipal,
                                    char        **outName,
                                    char        **outInstance,
                                    char        **outRealm)
    KERBEROS_APPLE_DEPRECATED("gss_display_name");

KLStatus KLGetStringFromPrincipal (KLPrincipal         inPrincipal,
                                   KLKerberosVersion   inKerberosVersion,
                                   char              **outFullPrincipal)
    KERBEROS_APPLE_DEPRECATED("gss_display_name");

KLStatus KLGetDisplayStringFromPrincipal (KLPrincipal         inPrincipal,
                                          KLKerberosVersion   inKerberosVersion,
                                          char              **outFullPrincipal)
    KERBEROS_APPLE_DEPRECATED("gss_display_name");

KLStatus KLComparePrincipal (KLPrincipal  inFirstPrincipal,
                             KLPrincipal  inSecondPrincipal,
                             KLBoolean   *outAreEquivalent)
    KERBEROS_APPLE_DEPRECATED("gss_compare_name");

KLStatus KLDisposePrincipal (KLPrincipal inPrincipal)
    KERBEROS_APPLE_DEPRECATED("gss_release_name");

/* KLLoginOptions functions */

KLStatus KLCreateLoginOptions (KLLoginOptions *outOptions)
    KERBEROS_APPLE_DEPRECATED("gss_aapl_initial_cred");

KLStatus KLLoginOptionsSetTicketLifetime (KLLoginOptions ioOptions,
                                          KLLifetime     inTicketLifetime)
    KERBEROS_APPLE_DEPRECATED("gss_aapl_initial_cred");

KLStatus KLLoginOptionsSetForwardable (KLLoginOptions ioOptions,
                                       KLBoolean      inForwardable)
    KERBEROS_APPLE_DEPRECATED("gss_aapl_initial_cred");

KLStatus KLLoginOptionsSetProxiable (KLLoginOptions ioOptions,
                                     KLBoolean      inProxiable)
    KERBEROS_APPLE_DEPRECATED("gss_aapl_initial_cred");

KLStatus KLLoginOptionsSetRenewableLifetime (KLLoginOptions ioOptions,
                                             KLLifetime     inRenewableLifetime)
    KERBEROS_APPLE_DEPRECATED("gss_aapl_initial_cred");

KLStatus KLLoginOptionsSetAddressless (KLLoginOptions ioOptions,
                                       KLBoolean      inAddressless)
    KERBEROS_APPLE_DEPRECATED("gss_aapl_initial_cred");

KLStatus KLLoginOptionsSetTicketStartTime (KLLoginOptions ioOptions,
                                           KLTime         inStartTime)
    KERBEROS_APPLE_DEPRECATED("gss_aapl_initial_cred");

KLStatus KLLoginOptionsSetServiceName (KLLoginOptions  ioOptions,
                                       const char     *inServiceName)
    KERBEROS_APPLE_DEPRECATED("gss_aapl_initial_cred");

KLStatus KLDisposeLoginOptions(KLLoginOptions ioOptions)
    KERBEROS_APPLE_DEPRECATED("gss_aapl_initial_cred");


/* Misc function */

KLStatus KLDisposeString (char *inStringToDispose)
    KERBEROS_APPLE_DEPRECATED("no replacement");

#if TARGET_OS_MAC
#    pragma pack(pop)
#endif

#ifdef __cplusplus
}
#endif

#endif /* __KERBEROSLOGIN__ */
