/*
 * Copyright 1998-2003  by the Massachusetts Institute of Technology.
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
 * permission.	Furthermore if you modify this software you must label
 * your software as modified software and not distribute it in such a
 * fashion that it might be confused with the original M.I.T. software.
 * M.I.T. makes no representations about the suitability of
 * this software for any purpose.  It is provided "as is" without express
 * or implied warranty.
 */

/* 
 * KClient 1.9 deprecated API
 *
 * $Header: /cvs/kfm/KerberosFramework/KClient/Headers/Kerberos/KClientDeprecated.h,v 1.12 2003/07/03 16:13:49 lxs Exp $
 */

#ifndef	__KCLIENTDEPRECATED__
#define	__KCLIENTDEPRECATED__

#if defined(macintosh) || (defined(__MACH__) && defined(__APPLE__))
#    include <TargetConditionals.h>
#    if TARGET_RT_MAC_CFM
#        error "Use KfM 4.0 SDK headers for CFM compilation."
#    endif
#endif

#if TARGET_OS_MAC
#    include <Kerberos/krb.h>
#    include <Kerberos/KClientTypes.h>
#else
#    include <kerberosIV/krb.h>
#    include <KClientTypes.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if TARGET_OS_MAC
#    if defined(__MWERKS__)
#        pragma import on
#    endif
#    pragma options align=mac68k
#endif
    
/* Max error text length returned by KClientGetErrorTextDeprecated */
#define kKClientMaxErrorTextLength 512

/*
 * Important!
 *
 * The following functions are deprecated. They will be removed from the library
 * and the header files in the future. See documentation for moving to KClient
 * 3.0 API to see how you can update your code.
 */

OSStatus
KClientCacheInitialTicketDeprecated (
	KClientSession*			inSession,
	char*					inService);

OSStatus KClientGetLocalRealmDeprecated (
	char*					outRealm);

OSStatus KClientSetLocalRealmDeprecated (
	const char*				inRealm);

OSStatus KClientGetRealmDeprecated (
	const char*				inHost,
	char*					outRealm);

OSStatus KClientAddRealmMapDeprecated (
	char*					inHost,
	char*					inRealm);

OSStatus KClientDeleteRealmMapDeprecated (
	char*					inHost);

OSStatus KClientGetNthRealmMapDeprecated (
	SInt32					inIndex,
	char*					outHost,
	char*					outRealm);

OSStatus KClientGetNthServerDeprecated (
	SInt32					inIndex,
	char*					outHost,
	char*					inRealm,
	Boolean					inAdmin);

OSStatus KClientAddServerMapDeprecated (
	char*					inHost,
	char*					inRealm,
	Boolean					inAdmin);

OSStatus KClientDeleteServerMapDeprecated (
	char*					inHost,
	char*					inRealm);

OSStatus KClientGetNthServerMapDeprecated (
	SInt32					inIndex,
	char*					outHost,
	char*					outRealm,
	Boolean*				outAdmin);

OSStatus KClientGetNthServerPortDeprecated (
	SInt32					inIndex,
	UInt16*					outPort);

OSStatus KClientSetNthServerPortDeprecated (
	SInt32					inIndex,
	UInt16					inPort);

OSStatus KClientGetNumSessionsDeprecated (
	SInt32*					outSessions);

OSStatus KClientGetNthSessionDeprecated (
	SInt32					inIndex,
	char*					outName,
	char*					outInstance,
	char*					outRealm);

OSStatus KClientDeleteSessionDeprecated (
	char*					inName,
	char*					inInstance,
	char*					inRealm);

OSStatus KClientGetCredentialsDeprecated (
	char*					inName,
	char*					inInstance,
	char*					inRealm,
	CREDENTIALS*			outCred);

OSStatus KClientAddCredentialsDeprecated (
	char*					inName,
	char*					inInstance,
	char*					inRealm,
	CREDENTIALS*			inCred);

OSStatus KClientDeleteCredentialsDeprecated (
	char*					inName,
	char*					inInstance,
	char*					inRealm, 
	char*					inSname,
	char*					inSinstance,
	char*					inSrealm);

OSStatus KClientGetNumCredentialsDeprecated (
	SInt32*					outNumCredentials,
	char*					inName,
	char*					inInstance,
	char*					inRealm);

OSStatus
KClientGetNthCredentialDeprecated (
	SInt32					inIndex,
	char*					inName,
	char*					inInstance,
	char*					inRealm,
	char*					inSname,
	char*					inSinstance,
	char*					inSrealm);

OSStatus
KClientGetUserNameDeprecated (
	char*					outUserName);
	
void
KClientGetErrorTextDeprecated (
	OSErr					inError,
	char*					outBuffer);


/*
 * Warning!
 *
 * The following are K5Client calls. Not only are they deprecated, but they should
 * never have existed in the first place. They are here so that KClient can swallow
 * K5Client (Yummmmmm)
 */
	
OSStatus
K5ClientGetTicketForServiceDeprecated (
	char*			inService,
	void*			outBuffer,
	UInt32*			outBufferLength);

OSStatus
K5ClientGetAuthenticatorForServiceDeprecated (
	char*			inService,
	char*			inApplicationVersion,
	void*			outBuffer,
	UInt32*			outBufferLength);

#if TARGET_OS_MAC
#    if defined(__MWERKS__)
#        pragma import reset
#    endif
#    pragma options align=reset
#endif

#ifdef __cplusplus
}
#endif

#endif /* __KCLIENTDEPRECATED__ */