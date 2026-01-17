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
 * KLPrincipalTranslation.h
 *
 * $Header$
 */
 
#ifndef KLPrincipalTranslation_h_
#define KLPrincipalTranslation_h_

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

/* Plugin information */
#define	kKLPT_PluginBundleNameSuffix ".principalTranslator"
#define kKLPT_PluginBundleFolder     "/Library/Kerberos Plug-Ins/"

/* API Versions */

enum {
    kKLPT_APIVersion_1       = 1,
    kKLPT_APIVersion_Current = kKLPT_APIVersion_1
};

/* Types */

typedef u_int32_t KLPT_APIVersion;

/* Function prototypes */

KLStatus KerberosLoginPrincipalTranslation_InitializePlugin (KLPT_APIVersion inAPIVersion);

KLStatus KerberosLoginPrincipalTranslation_TranslatePrincipal (const char  *inName,
                                                               const char  *inInstance,
                                                               const char  *inRealm,
                                                               const char **outName,
                                                               const char **outInstance,
                                                               const char **outRealm,
                                                               KLBoolean   *outChanged);

void KerberosLoginPrincipalTranslation_ReleasePrincipal (char*	inName,
                                                         char*	inInstance,
                                                         char*	inRealm);

#if TARGET_OS_MAC
    #if defined(__MWERKS__)
        #pragma export reset
    #endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* KLPrincipalTranslation_h_ */
