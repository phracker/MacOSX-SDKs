/*
 * Copyright 1998-2003 Massachusetts Institute of Technology.
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

/*
 * KLLoginLogoutNotification.h
 *
 * $Header$
 */
 
#ifndef KLLoginLogoutNotification_h_
#define KLLoginLogoutNotification_h_

#if defined(macintosh) || (defined(__MACH__) && defined(__APPLE__))
	#include <TargetConditionals.h>
    #if TARGET_RT_MAC_CFM
        #error "Use KfM 4.0 SDK headers for CFM compilation."
    #endif
#endif

#include <Kerberos/KerberosLogin.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#if TARGET_OS_MAC
    #if defined(__MWERKS__)
        #pragma export on
    #endif
#endif

/* Plugin Information */
#define kKLN_PluginBundleNameSuffix ".loginLogout"
#define kKLN_PluginBundleFolder     "/Library/Kerberos Plug-Ins/"

/* API Versions */

enum {
    kKLN_APIVersion_1       = 1,
    kKLN_APIVersion_Current = kKLN_APIVersion_1
};

/* Login types */

enum {
    kKLN_DialogLogin   = 1,
    kKLN_PasswordLogin = 2
};

/* Types */

typedef u_int32_t KLN_APIVersion;
typedef u_int32_t KLN_LoginType;

/* Function prototypes */

KLStatus KerberosLoginNotification_InitializePlugin (KLN_APIVersion inAPIVersion);

KLStatus KerberosLoginNotification_Login (KLN_LoginType inLoginType,
                                          const char   *inCredentialsCache);

void KerberosLoginNotification_Logout (const char *inCredentialsCache);

#if TARGET_OS_MAC
    #if defined(__MWERKS__)
        #pragma export reset
    #endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* KLLoginLogoutNotification_h_ */
