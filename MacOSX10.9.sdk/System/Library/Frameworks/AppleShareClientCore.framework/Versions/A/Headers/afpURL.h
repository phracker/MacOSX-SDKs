/*
	File:		afpURL.h

	Contains:	URL functions in the AppleShare Client

	Version:	AppleShare X

	Copyright:	(c) 2000 - 2007 by Apple Inc., all rights reserved.	
*/

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#if PRAGMA_ONCE
#pragma once
#endif


/* used to be __cplusplus	*/
#ifdef __cplusplus		
extern "C" {
#endif


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*	AFP URL Support															 */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Building and disposing of an AFP URL										 */
/*---------------------------------------------------------------------------*/
EXTERN_API_C( char *)
NewAFPURL						(StringPtr 				protocolName,
								 StringPtr 				serverNameOrHost,
								 StringPtr 				zoneNameOrNULL,
								 StringPtr 				uamName,
								 StringPtr 				userName,
								 StringPtr 				password,
								 StringPtr 				volume,
								 StringPtr 				path)  __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_9, __IPHONE_NA, __IPHONE_NA);

EXTERN_API_C( void )
DisposeAFPURL					(char *					url)  __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_9, __IPHONE_NA, __IPHONE_NA);


/*---------------------------------------------------------------------------*/
/* Parsing an AFP URL: IsAFPURL simply tests the scheme						 */
/*---------------------------------------------------------------------------*/
EXTERN_API_C( Boolean )
IsAFPURL						(const char *					url)  __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_9, __IPHONE_NA, __IPHONE_NA);

/*---------------------------------------------------------------------------*/
/* ParseAFPURL parses all the fields of the URL. Any StringPtr can be NULL,	 */
/* If provided the StringPtr must point to a string large enough to 		 */
/* accomodate maximum length value (Str255)									 */
/*---------------------------------------------------------------------------*/
EXTERN_API_C( OSStatus )
ParseAFPURL		(const char *					url,
			StringPtr 				protocolName,
			StringPtr  				serverNameOrHost,
			StringPtr 				zoneNameOr,
			StringPtr 				uamName,
			StringPtr 				userName,
			StringPtr 				password,
			StringPtr 				volume,
			StringPtr 				path)  __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_9, __IPHONE_NA, __IPHONE_NA);


/*---------------------------------------------------------------------------*/
/* AFPMountURL mounts a volume given an afp URL, the mount flags are the 	 */
/* same as the flags used by the mount system call. errno is set on error	 */
/* NOTE: inMountPoint must exist. This call will not bring up HI.			 */
/*---------------------------------------------------------------------------*/


EXTERN_API_C( OSStatus )
AFPMountURL(const char* inURL,
			const char* inMountPoint,
			UInt32 inMountFlags, UInt32 inAltFlags)  __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_9, __IPHONE_NA, __IPHONE_NA);


/* used to be __cplusplus	*/
#ifdef __cplusplus		
};
#endif

