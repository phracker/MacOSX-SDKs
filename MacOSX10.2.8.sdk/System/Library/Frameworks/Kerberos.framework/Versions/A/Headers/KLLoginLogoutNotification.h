/*
 * API for Kerberos Login and Logout Notification plugins
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
        #pragma import on
        #pragma enumsalwaysint on
    #endif
    #pragma options align=mac68k
#endif

/* Plugin Information */
#define kKLN_PluginBundleNameSuffix ".loginLogout";
#define kKLN_PluginBundleFolder     "/Library/Kerberos Plug-Ins/";

/* API Versions */

enum {
	kKLN_APIVersion_1				= 1,
	kKLN_APIVersion_Current			= kKLN_APIVersion_1
};

/* Login types */

enum {
	kKLN_DialogLogin				= 1,
	kKLN_PasswordLogin				= 2
};

/* Types */

typedef u_int32_t KLN_APIVersion;
typedef u_int32_t KLN_LoginType;

/* Function prototypes */

#pragma export on

KLStatus KerberosLoginNotification_InitializePlugin (
	KLN_APIVersion		inAPIVersion);

KLStatus KerberosLoginNotification_Login (
	KLN_LoginType		inLoginType,
	const char*			inCredentialsCache);

void KerberosLoginNotification_Logout (
	const char*			inCredentialsCache);

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

#endif /* KLLoginLogoutNotification_h_ */
