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
 * KClient 3.0 API
 *
 * $Header$
 */

#ifndef	__KCLIENT__
#define	__KCLIENT__

#if defined(macintosh) || (defined(__MACH__) && defined(__APPLE__))
#    include <TargetConditionals.h>
#    if TARGET_RT_MAC_CFM
#        error "Use KfM 4.0 SDK headers for CFM compilation."
#    endif
#endif

#if TARGET_OS_MAC
#    include <Kerberos/CredentialsCache.h>
#    include <Kerberos/profile.h>
#    include <Kerberos/des.h>
#    include <Kerberos/KClientTypes.h>
#    include <CoreServices/CoreServices.h>
#else
#    include <CredentialsCache.h>
#    include <profile.h>
#    include <kerberosIV/des.h>
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
    
/* Constants */

enum {
	/* No error */
	kcNoError					= 0,
	
	/* General runtime errors */
	kcErrNoMemory				= 23000,
	kcErrBadParam,

	/* Various invalid structures */
	kcErrInvalidSession			= 23010,
	kcErrInvalidPrincipal,
	kcErrInvalidAddress,
	kcErrInvalidFile,

	/* Missing required settings in the session */
	kcErrNoClientPrincipal		= 23020,
	kcErrNoServerPrincipal,
	kcErrNoLocalAddress,
	kcErrNoRemoteAddress,
	kcErrNoSessionKey,
	kcErrNoServiceKey,
	kcErrNoChecksum,
	
	kcErrNotLoggedIn			= 23030,
	kcErrUserCancelled,
	kcErrIncorrectPassword,
	
	kcErrBufferTooSmall			= 23040,
	kcErrKeyFileAccess,
	kcErrFileNotFound,
	kcErrInvalidPreferences,
	kcErrChecksumMismatch,
	
	kcFirstKerberosError				= 20000,
	kcLastKerberosError					= 20256	/* Mac OS X rez is dumb -- no addition */
};

enum {
	kKClientEncryptionOverhead				= 26,
	kKClientProtectionOverhead				= 31
};

/* Functions */

OSStatus KClientGetVersion (
	UInt16*					outMajorVersion,
	UInt16*					outMinorVersion,
	const char**			outVersionString);

/* Initialization / destruction */

OSStatus KClientNewClientSession (
	KClientSession*			outSession);
	
OSStatus KClientNewServerSession (
	KClientSession*			inSession,
	KClientPrincipal		inService);
	
OSStatus KClientDisposeSession (
	KClientSession			inSession);
	
/* Accessing session properties */
OSStatus KClientGetClientPrincipal (
	KClientSession			inSession,
	KClientPrincipal*		outPrincipal);
	
OSStatus KClientSetClientPrincipal (
	KClientSession			inSession,
	KClientPrincipal		inPrincipal);
	
OSStatus KClientGetServerPrincipal (
	KClientSession			inSession,
	KClientPrincipal*		outPrincipal);
	
OSStatus KClientSetServerPrincipal (
	KClientSession			inSession,
	KClientPrincipal		inPrincipal);
	
OSStatus KClientGetLocalAddress (
	KClientSession			inSession,
	KClientAddress*			outLocalAddress);
	
OSStatus KClientSetLocalAddress (
	KClientSession			inSession,
	const KClientAddress*	inLocalAddress);
	
OSStatus KClientGetRemoteAddress (
	KClientSession			inSession,
	KClientAddress*			outRemoteAddress);
	
OSStatus KClientSetRemoteAddress (
	KClientSession			inSession,
	const KClientAddress*	inRemoteAddress);
	
OSStatus KClientGetSessionKey (
	KClientSession			inSession,
	KClientKey*				outKey);

OSStatus KClientGetExpirationTime (
	KClientSession			inSession,
	UInt32*					outExpiration);
	
OSStatus KClientSetKeyFile (
	KClientSession			inSession,
	const KClientFile*		inKeyFile);
	
/* Logging in and out (client) */

OSStatus KClientLogin (
	KClientSession			inSession);

OSStatus KClientPasswordLogin (
	KClientSession			inSession,
	const char* 			inPassword);
	
OSStatus KClientKeyFileLogin (
	KClientSession			inSession);

/*OSStatus KClientKeyLogin (
	KClientSession			inSession,
	const KClientKey*		inKey);*/
	
OSStatus KClientLogout (
	KClientSession			inSession);
	
/* Accessing service keys (server) */

OSStatus KClientGetServiceKey (
	KClientSession			inSession,
	UInt32					inVersion,
	KClientKey*				outKey);
	
OSStatus KClientAddServiceKey (
	KClientSession			inSession,
	UInt32					inVersion,
	const KClientKey*		inKey);
	
/* Authenticating to a service (client) */

OSStatus KClientGetTicketForService (
	KClientSession			inSession,
	UInt32					inChecksum,
	void*					outBuffer,
	UInt32*					ioBufferLength);
	
OSStatus KClientGetAuthenticatorForService (
	KClientSession			inSession,
	UInt32					inChecksum,
	const char*				inApplicationVersion,
	void*					outBuffer,
	UInt32*					ioBufferLength);

OSStatus KClientVerifyEncryptedServiceReply (
	KClientSession			inSession,
	const void*				inBuffer,
	UInt32					inBufferLength);
	
OSStatus KClientVerifyProtectedServiceReply (
	KClientSession			inSession,
	const void*				inBuffer,
	UInt32					inBufferLength);
	
/* Authenticating a client (server) */

OSStatus KClientVerifyAuthenticator (
	KClientSession			inSession,
	const void*				inBuffer,
	UInt32					inBufferLength);
	
OSStatus KClientGetEncryptedServiceReply (
	KClientSession			inSession,
	void*					outBuffer,
	UInt32*					ioBufferSize);
	
OSStatus KClientGetProtectedServiceReply (
	KClientSession			inSession,
	void*					outBuffer,
	UInt32*					ioBufferSize);
	
/* Communicating between a server and a client */

OSStatus KClientEncrypt (
	KClientSession			inSession,
	const void*				inPlainBuffer,
	UInt32					inPlainBufferLength,
	void*					outEncryptedBuffer,
	UInt32*					ioEncryptedBufferLength);

OSStatus KClientDecrypt (
	KClientSession			inSession,
	void*					inEncryptedBuffer,
	UInt32					inDecryptedBufferLength,
	UInt32*					outPlainOffset,
	UInt32*					outPlainLength);
	
OSStatus KClientProtectIntegrity (
	KClientSession			inSession,
	const void*				inPlainBuffer,
	UInt32					inPlainBufferLength,
	void*					outProtectedBuffer,
	UInt32*					ioProtectedBufferLength);

OSStatus KClientVerifyIntegrity (
	KClientSession			inSession,
	void*					inProtectedBuffer,
	UInt32					inProtectedBufferLength,
	UInt32*					outPlainOffset,
	UInt32*					outPlainLength);
	
/* Miscellaneous */

OSStatus KClientPasswordToKey (
	KClientSession			inSession,
	const char*				inPassword,
	KClientKey*				outKey);
	
/* Getting to other APIs */

OSStatus KClientGetCCacheReference (
	KClientSession			inSession,
	cc_ccache_t*			outCCacheReference);

OSStatus KClientGetProfileHandle (
	KClientSession			inSession,
	profile_t*				outProfileHandle);

/* Principal manipulation */

OSStatus KClientV4StringToPrincipal (
	const char*				inPrincipalString,
	KClientPrincipal*		outPrincipal);
	
OSStatus KClientPrincipalToV4String (
	KClientPrincipal		inPrincipal,
	char*					outPrincipalString);
	
OSStatus KClientPrincipalToV4Triplet (
	KClientPrincipal		inPrincipal,
	char*					outName,
	char*					outInstance,
	char*					outRealm);
	
OSStatus KClientDisposePrincipal (
	KClientPrincipal		inPrincipal);

#if TARGET_OS_MAC
#    if defined(__MWERKS__)
#        pragma import reset
#    endif
#    pragma options align=reset
#endif

#ifdef __cplusplus
}
#endif

#endif /* __KCLIENT__ */
