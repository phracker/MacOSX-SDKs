/*
 * API for Kerberos Login Principal Translation plugins
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
        #pragma import on
        #pragma enumsalwaysint on
    #endif
    #pragma options align=mac68k
#endif

/* Plugin information */
#define	kKLPT_PluginBundleNameSuffix ".principalTranslator"
#define kKLPT_PluginBundleFolder     "/Library/Kerberos Plug-Ins/"

/* API Versions */

enum {
	kKLPT_APIVersion_1				= 1,
	kKLPT_APIVersion_Current		= kKLPT_APIVersion_1
};

/* Types */

typedef u_int32_t	KLPT_APIVersion;

/* Function prototypes */

#pragma export on

KLStatus KerberosLoginPrincipalTranslation_InitializePlugin (
	KLPT_APIVersion		inAPIVersion);

KLStatus KerberosLoginPrincipalTranslation_TranslatePrincipal (
	const char*		inName,
	const char*		inInstance,
	const char*		inRealm,
	const char**	outName,
	const char**	outInstance,
	const char**	outRealm,
	KLBoolean*		outChanged);

void KerberosLoginPrincipalTranslation_ReleasePrincipal (
	char*	inName,
	char*	inInstance,
	char*	inRealm);

#if TARGET_OS_MAC
    #if defined(__MWERKS__)
        #pragma enumsalwaysint reset
        #pragma import reset
    #endif
	#pragma options align=reset
#endif

#ifdef __cplusplus
}
#endif

#endif /* KLPrincipalTranslation_h_ */