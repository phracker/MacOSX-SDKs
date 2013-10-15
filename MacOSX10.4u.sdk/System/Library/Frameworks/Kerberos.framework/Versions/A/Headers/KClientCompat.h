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
 * $Header$
 */

#ifndef	__KCLIENTCOMPAT__
#define	__KCLIENTCOMPAT__

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
    
/* Constants */

/* Error codes, only listing the ones actually returned by the library */
enum {
	cKrbMapDoesntExist			= -1020,	/* tried to access a map that doesn't exist (index too large, or criteria doesn't match anything) */
	cKrbSessDoesntExist			= -1019,	/* tried to access a session that doesn't exist */
	cKrbCredsDontExist			= -1018,	/* tried to access credentials that don't exist */
	cKrbUserCancelled			= -1016,	/* user cancelled a log in operation */
	cKrbConfigurationErr		= -1015,	/* Kerberos Preference file is not configured properly */
	cKrbServerRejected			= -1014,	/* A server rejected our ticket */
	cKrbServerImposter			= -1013,	/* Server appears to be a phoney */
	cKrbServerRespIncomplete	= -1012,	/* Server response is not complete */
	cKrbNotLoggedIn				= -1011,	/* Returned by cKrbGetUserName if user is not logged in */
	cKrbAppInBkgnd				= -1008,	/* driver won't put up password dialog when in background */
	cKrbInvalidSession			= -1007,	/* invalid structure passed to KClient/KServer routine */
		
	cKrbKerberosErrBlock		= -20000	/* start of block of 256 kerberos error numbers */
};

typedef KClientSession KClientSessionInfo;

enum {
	KClientLoggedIn,
	KClientNotLoggedIn
};

OSErr KClientVersionCompat (
	SInt16*						outMajorVersion,
	SInt16*						outMinorVersion,
	char*						outVersionString);

OSErr KClientNewSessionCompat (
	KClientSessionInfo*			inSession,
	UInt32						inLocalAddress,
	UInt16						inLocalPort,
	UInt32						inRemoteAddress,
	UInt16						inRemotePort);
	
OSErr KClientDisposeSessionCompat (
	KClientSessionInfo*			inSession);
	
OSErr KClientGetTicketForServiceCompat (
	KClientSessionInfo*			inSession,
	char*						inService,
	void*						inBuffer,
	UInt32*						outBufferLength);
	
OSErr KClientGetTicketForServiceWithChecksumCompat (
	KClientSessionInfo*			inSession,
	UInt32						inChecksum,
	char*						inService,
	void*						inBuffer,
	UInt32*						outBufferLength);
	
OSErr KClientLoginCompat (
	KClientSessionInfo*			inSession,
	KClientKey*					outPrivateKey);
	
OSErr KClientPasswordLoginCompat (
	KClientSessionInfo*			inSession,
	char*						inPassword,
	KClientKey*					outPrivateKey);
	
OSErr KClientLogoutCompat (void);

SInt16 KClientStatusCompat (void);

OSErr KClientGetSessionKeyCompat (
	KClientSessionInfo*			inSession,
	KClientKey*					outSessionKey);
	
OSErr KClientEncryptCompat (
	KClientSessionInfo*			inSession,
	void*						inPlainBuffer,
	UInt32						inPlainBufferLength,
	void*						outEncryptedBuffer,
	UInt32*						ioEncryptedBufferLength);
	
OSErr KClientDecryptCompat (
	KClientSessionInfo*			inSession,
	void*						inEncryptedBuffer,
	UInt32						inEncryptedBufferLength,
	UInt32*						outPlainBufferOffset,
	UInt32*						outPlainBufferLength);

OSErr KClientProtectIntegrityCompat (
	KClientSessionInfo*			inSession,
	void*						inPlainBuffer,
	UInt32						inPlainBufferLength,
	void*						outProtectedBuffer,
	UInt32*						ioProtectedBufferLength);

OSErr KClientVerifyIntegrityCompat (
	KClientSessionInfo*			inSession,
	void*						inProtectedBuffer,
	UInt32						inProtectedBufferLength,
	UInt32*						outPlainBufferOffset,
	UInt32*						outPlainBufferLength);

OSErr KServerNewSessionCompat (
	KClientSessionInfo*			inSession,
	char*						inService,
	UInt32						inLocalAddress,
	UInt16						inLocalPort,
	UInt32						inRemoteAddress,
	UInt16						inRemotePort);

OSErr KServerVerifyTicketCompat (
	KClientSessionInfo*			inSession,
	void*						inBuffer,
	char*						inFilename);
	
OSErr KServerGetReplyTicketCompat (
	KClientSessionInfo*			inSession,
	void*						outBuffer,
	UInt32*						ioBufferLength);
	
OSErr KServerAddKeyCompat (
	KClientSessionInfo*			inSession,
	KClientKey*					inPrivateKey,
	char*						inService,
	SInt32						inVersion,
	char*						inFilename);
	
OSErr KServerGetKeyCompat (
	KClientSessionInfo*			inSession,
	KClientKey*					outPrivateKey,
	char*						inService,
	SInt32						inVersion,
	char*						inFilename);

OSErr KServerGetSessionTimeRemainingCompat (
	KClientSessionInfo*			inSession,
	SInt32*						outSeconds);
	
OSErr KClientGetSessionUserNameCompat (
	KClientSessionInfo*			inSession,
	char*						outUserName,
	SInt16						inNameType);

OSErr KClientMakeSendAuthCompat (
	KClientSessionInfo*			inSession,
	char*						inService,
	void*						outBuffer,
	UInt32*						ioBufferLength,
	SInt32						inChecksum,
	char*						inApplicationVersion);
	
OSErr KClientVerifyReplyTicketCompat (
	KClientSessionInfo*			inSession,
	void*						inBuffer,
	UInt32*						ioBufferLength);
	
OSErr KClientVerifyUnencryptedReplyTicketCompat (
	KClientSessionInfo*			inSession,
	void*						inBuffer,
	UInt32*						ioBufferLength);

#if TARGET_OS_MAC
#    if defined(__MWERKS__)
#        pragma import reset
#    endif
#    pragma options align=reset
#endif

#ifdef __cplusplus
}
#endif

#endif /* __KCLIENTCOMPAT__ */
