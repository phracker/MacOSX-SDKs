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

#ifndef	KClientTypes_h
#define	KClientTypes_h

#if defined(macintosh) || (defined(__MACH__) && defined(__APPLE__))
#    include <TargetConditionals.h>
#    if TARGET_RT_MAC_CFM
#        error "Use KfM 4.0 SDK headers for CFM compilation."
#    endif
#endif

#if TARGET_OS_MAC
#    include <Kerberos/des.h>
#    include <CoreServices/CoreServices.h>
#else
#    include <KerberosIV/des.h>
#    include <CoreServices.h>
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

/* Different kerberos name formats */
enum { 
	KClientLocalName,				/* Don't specify realm */
	KClientCommonName, 				/* Only specify realm if it isn't local */
	KClientFullName					/* Always specify realm */
};

/* Opaque types */

struct KClientSessionOpaque;
typedef struct KClientSessionOpaque* KClientSession;

struct KClientPrincipalOpaque;
typedef struct KClientPrincipalOpaque* KClientPrincipal;

/* Visible types */

typedef FSSpec KClientFile;

struct KClientAddress {
	UInt32				address;
	UInt16				port;
};
typedef struct KClientAddress KClientAddress;

struct KClientKey {
	des_cblock			key;
};
typedef struct KClientKey KClientKey;

struct KClientKeySchedule {
	des_key_schedule	keySchedule;
};
typedef struct KClientKeySchedule KClientKeySchedule;

#if TARGET_OS_MAC
#    if defined(__MWERKS__)
#        pragma import reset
#    endif
#    pragma options align=reset
#endif

#ifdef __cplusplus
}
#endif

#endif /* KClientTypes_h */