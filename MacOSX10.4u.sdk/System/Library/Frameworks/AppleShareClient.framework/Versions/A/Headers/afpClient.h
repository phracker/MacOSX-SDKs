/*
	File:		afpClient.h

	Contains:	Shared library interface to the AppleShare Client

	Version:	AppleShare X

	Copyright:	© 2000 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	 <RASC3>	 3/14/00	law		Add support for VolumePasswords and better support for the
									HLMount routines
	 <RASC2>	 2/25/00	law		Working on the public interface
		 <1>	  2/3/00	law		first checked in
*/


#ifndef __AFPCLIENT__
#define __AFPCLIENT__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __CARBON__
#include <Carbon/Carbon.h>
#endif




#if PRAGMA_ONCE
#pragma once
#endif

/* used to be __cplusplus	*/
#if __cplusplus		
extern "C" {
#endif


#if PRAGMA_IMPORT
#pragma import on
#endif

#if PRAGMA_STRUCT_ALIGN
	#pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
	#pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
	#pragma pack(2)
#endif


/* Data Types */
typedef UInt32 							AFPSharedVolumesEnumeratorRef;
typedef UInt32 							ATEventCode;
typedef UInt32 							ATPortRef;
typedef UInt32 							OneBasedIndex;

/* error codes	*/
enum {
	kNavigationAPIErrorBase		= 1,
	kATEnumeratorBadIndexErr	= kNavigationAPIErrorBase,
	kATEnumeratorBadReferenceErr = 2,
	kATEnumeratorBadZoneErr		= 3,
	kATEnumeratorBadPortErr		= 4,
	kATAppleShareNotAvailableErr = 5,
	kATServerNotFoundErr		= 6,
	kLastErrorCodeIndex			= 7,
	kLastAndMeaningLessItemInEnum = 8
};

typedef	struct sockaddr *AddressPtr;	


/* notifier events for ATNotifyProc	*/
enum {
																/* Returned by the AppleShare volumes emnumerator*/
	AT_SHAREDVOLUMES_COMPLETE	= FOUR_CHAR_CODE('vols')
};

/*---------------------------------------------------------------------------*/
/*	Finding out if the library is present and getting its version			 */
/*---------------------------------------------------------------------------*/

EXTERN_API( UInt32 )
AFPLibraryVersion				(void);

EXTERN_API_C( Boolean )
AFPLibraryPresent				(void);


#ifdef __cplusplus														
inline	Boolean AFPLibraryPresent()										
{																		
	return AFPLibraryVersion != (void*)kUnresolvedCFragSymbolAddress;	
}																		
#endif																	

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*	AFP URL Support	had moved to "AppleShareClientCore/afpURL.h"														 */
/*---------------------------------------------------------------------------*/

		
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*	Enumerating shared volumes on AppleShare file servers					 */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*	Event callback for the login dialogs									 */
/*---------------------------------------------------------------------------*/
typedef CALLBACK_API( void , AShareEventProcPtr )(EventRecord *theEvent, void *contextPtr);
typedef CALLBACK_API( void , ATNotifyProcPtr )(void *contextPtr, ATEventCode code, OSStatus result, void *cookie);
typedef CALLBACK_API( Boolean , ATFilterProcPtr )(StringPtr name, void *data);
typedef CALLBACK_API( void , ATNetworkEventNotifierProcPtr )(UInt32 eventCode, void *cookie);
typedef STACK_UPP_TYPE(AShareEventProcPtr) 						AShareEventUPP;
typedef STACK_UPP_TYPE(ATNotifyProcPtr) 						ATNotifyUPP;
typedef STACK_UPP_TYPE(ATFilterProcPtr) 						ATFilterUPP;
typedef STACK_UPP_TYPE(ATNetworkEventNotifierProcPtr) 			ATNetworkEventNotifierUPP;

#if OPAQUE_UPP_TYPES
	EXTERN_API(AShareEventUPP)
	NewAShareEventUPP			   (AShareEventProcPtr		userRoutine);

	EXTERN_API(ATNotifyUPP)
	NewATNotifyUPP				   (ATNotifyProcPtr			userRoutine);

	EXTERN_API(ATFilterUPP)
	NewATFilterUPP				   (ATFilterProcPtr			userRoutine);

	EXTERN_API(ATNetworkEventNotifierUPP)
	NewATNetworkEventNotifierUPP    (ATNetworkEventNotifierProcPtr userRoutine);

	EXTERN_API(void)
	DisposeAShareEventUPP		   (AShareEventUPP			userUPP);

	EXTERN_API(void)
	DisposeATNotifyUPP			   (ATNotifyUPP				userUPP);

	EXTERN_API(void)
	DisposeATFilterUPP			   (ATFilterUPP				userUPP);

	EXTERN_API(void)
	DisposeATNetworkEventNotifierUPP    (ATNetworkEventNotifierUPP userUPP);

	EXTERN_API(void)
	InvokeAShareEventUPP		   (EventRecord *			theEvent,
									void *					contextPtr,
									AShareEventUPP			userUPP);

	EXTERN_API(void)
	InvokeATNotifyUPP			   (void *					contextPtr,
									ATEventCode				code,
									OSStatus				result,
									void *					cookie,
									ATNotifyUPP				userUPP);

	EXTERN_API(Boolean)
	InvokeATFilterUPP			   (StringPtr				name,
									void *					data,
									ATFilterUPP				userUPP);

	EXTERN_API(void)
	InvokeATNetworkEventNotifierUPP    (UInt32				eventCode,
									void *					cookie,
									ATNetworkEventNotifierUPP userUPP);

#else
	enum { uppAShareEventProcInfo = 0x000003C0 }; 					/* pascal no_return_value Func(4_bytes, 4_bytes) */
	enum { uppATNotifyProcInfo = 0x00003FC0 }; 						/* pascal no_return_value Func(4_bytes, 4_bytes, 4_bytes, 4_bytes) */
	enum { uppATFilterProcInfo = 0x000003D0 }; 						/* pascal 1_byte Func(4_bytes, 4_bytes) */
	enum { uppATNetworkEventNotifierProcInfo = 0x000003C0 }; 		/* pascal no_return_value Func(4_bytes, 4_bytes) */
	#define NewAShareEventUPP(userRoutine) 							(AShareEventUPP)NewRoutineDescriptor((ProcPtr)(userRoutine), uppAShareEventProcInfo, GetCurrentArchitecture())
	#define NewATNotifyUPP(userRoutine) 							(ATNotifyUPP)NewRoutineDescriptor((ProcPtr)(userRoutine), uppATNotifyProcInfo, GetCurrentArchitecture())
	#define NewATFilterUPP(userRoutine) 							(ATFilterUPP)NewRoutineDescriptor((ProcPtr)(userRoutine), uppATFilterProcInfo, GetCurrentArchitecture())
	#define NewATNetworkEventNotifierUPP(userRoutine) 				(ATNetworkEventNotifierUPP)NewRoutineDescriptor((ProcPtr)(userRoutine), uppATNetworkEventNotifierProcInfo, GetCurrentArchitecture())
	#define DisposeAShareEventUPP(userUPP) 							DisposeRoutineDescriptor(userUPP)
	#define DisposeATNotifyUPP(userUPP) 							DisposeRoutineDescriptor(userUPP)
	#define DisposeATFilterUPP(userUPP) 							DisposeRoutineDescriptor(userUPP)
	#define DisposeATNetworkEventNotifierUPP(userUPP) 				DisposeRoutineDescriptor(userUPP)
	#define InvokeAShareEventUPP(theEvent, contextPtr, userUPP) 	CALL_TWO_PARAMETER_UPP((userUPP), uppAShareEventProcInfo, (theEvent), (contextPtr))
	#define InvokeATNotifyUPP(contextPtr, code, result, cookie, userUPP)  CALL_FOUR_PARAMETER_UPP((userUPP), uppATNotifyProcInfo, (contextPtr), (code), (result), (cookie))
	#define InvokeATFilterUPP(name, data, userUPP) 					(Boolean)CALL_TWO_PARAMETER_UPP((userUPP), uppATFilterProcInfo, (name), (data))
	#define InvokeATNetworkEventNotifierUPP(eventCode, cookie, userUPP)  CALL_TWO_PARAMETER_UPP((userUPP), uppATNetworkEventNotifierProcInfo, (eventCode), (cookie))
#endif

/* support for pre-Carbon UPP routines: NewXXXProc and CallXXXProc */
#define NewAShareEventProc(userRoutine) 						NewAShareEventUPP(userRoutine)
#define NewATNotifyProc(userRoutine) 							NewATNotifyUPP(userRoutine)
#define NewATFilterProc(userRoutine) 							NewATFilterUPP(userRoutine)
#define NewATNetworkEventNotifierProc(userRoutine) 				NewATNetworkEventNotifierUPP(userRoutine)
#define CallAShareEventProc(userRoutine, theEvent, contextPtr)	InvokeAShareEventUPP(theEvent, contextPtr, userRoutine)
#define CallATNotifyProc(userRoutine, contextPtr, code, result, cookie) InvokeATNotifyUPP(contextPtr, code, result, cookie, userRoutine)
#define CallATFilterProc(userRoutine, name, data)				InvokeATFilterUPP(name, data, userRoutine)
#define CallATNetworkEventNotifierProc(userRoutine, eventCode, cookie) InvokeATNetworkEventNotifierUPP(eventCode, cookie, userRoutine)

/*---------------------------------------------------------------------------*/
/* AFPCreateSharedVolumesEnumerator: creates an enumerator for the volumes 	 */
/* on an AppleShare server.													 */
/*																			 */
/* Accepts an optional volume name filter to restrict the volumes matched.	 */
/* Use the predefined filters or your own or pass NULL to match all volumes	 */
/* Accepts an optional notifier to call when the list of volumes has been	 */
/* found. 																	 */
/* Pass NULL for polling mode												 */
/* For connections over TCP/IP pass NULL for serverZone and the DNS name in	 */
/* serverName.																 */
/* These calls may put up UI, pass a UPP to a routine to handle events that	 */
/* affect other windows in your application.								 */
/*---------------------------------------------------------------------------*/

EXTERN_API( OSStatus )
AFPCreateSharedVolumesEnumerator (StringPtr 			serverName,
								 StringPtr 				serverZone,
								 StringPtr 				uamName,
								 StringPtr 				userName,
								 StringPtr 				password,
								 AShareEventUPP 		callback,
								 void *					evtContext,
								 ATFilterUPP 			filter,
								 void *					filterParam,
								 ATNotifyUPP 			notifier,
								 void *					contextPtr,
								 AFPSharedVolumesEnumeratorRef * ref);

EXTERN_API( OSStatus )
AFPCreateSVEFromAddress(	    AddressPtr				serverAddress,
								StringPtr 				uamName,
								StringPtr 				userName,
								StringPtr 				password,
								AFPSharedVolumesEnumeratorRef * 	ref);
								
/*---------------------------------------------------------------------------*/
/*	AFPGetSharedVolumesCount: returns the number of AppleShare volumes 		 */
/*  found so far. Indicates if all volumes have been found					 */
/*---------------------------------------------------------------------------*/
EXTERN_API( OSStatus )
AFPGetSharedVolumesCount		(AFPSharedVolumesEnumeratorRef  ref,
								 Boolean *				allFound,
								 UInt32 *				count);

/*---------------------------------------------------------------------------*/
/*	AFPGetIndexedSharedVolume: returns the name of volumes by index			 */
/*---------------------------------------------------------------------------*/
EXTERN_API( OSStatus )
AFPGetIndexedSharedVolume		(AFPSharedVolumesEnumeratorRef  ref,
								 OneBasedIndex 			index,
								 StringPtr 				volumeName);

/*---------------------------------------------------------------------------*/
/*	AFPSortSharedVolumes: sorts the list of volumes by alphabetical order	 */
/*---------------------------------------------------------------------------*/
EXTERN_API( OSStatus )
AFPSortSharedVolumes			(AFPSharedVolumesEnumeratorRef  ref);

/*---------------------------------------------------------------------------*/
/*	AFPMountSharedVolume: mounts a volume by name, 							 */
/* leave isMounted NULL if you don't care wether or not the volume was		 */
/* already mounted															 */
/*---------------------------------------------------------------------------*/
EXTERN_API( OSStatus )
AFPMountSharedVolume			(AFPSharedVolumesEnumeratorRef  ref,
								 Str255 				volumeName,
								 short *				volumeRefNum,
								 Boolean *				isMounted);


/*--------------------------------------------------------------------------*/
/*	AFPMountSharedVolume: mounts a volume by name, on the specified	     	*/
/*	 mount point with the given flags. inMountFlags & inAltFlags are the	*/
/* 	same as	those passed to the Mount System Call 				     		*/
/*--------------------------------------------------------------------------*/

EXTERN_API( OSStatus )
AFPMountSharedVolumeOnMP		(AFPSharedVolumesEnumeratorRef  ref,
								StringPtr inVolumeName,
								const UInt8* inVolPassword,
								const char* inMountPoint,
								UInt32 inMountFlags, UInt32 inAltFlags, Boolean inMakeUnique,
								UInt32 inMaxPath, char* outMountPath);


/*---------------------------------------------------------------------------*/
/* AFPGetMountAtStartup: returns the startup mounting state of the named 	 */
/* volume;  																 */
/*  returns noErr if the volume is set to mount at startup					 */
/*  returns nsvErr if the volume is not set to mount at startup				 */
/*---------------------------------------------------------------------------*/

EXTERN_API( OSStatus )
AFPGetMountAtStartup			(AFPSharedVolumesEnumeratorRef * ref,
								 StringPtr 				volumeName);

/*---------------------------------------------------------------------------*/
/* AFPSetMountAtStartup: sets the startup mounting state of the named volume */
/*---------------------------------------------------------------------------*/

EXTERN_API( OSStatus )
AFPSetMountAtStartup			(AFPSharedVolumesEnumeratorRef * ref,
								 StringPtr 				volumeName,
								 Boolean 				toMount);


/*---------------------------------------------------------------------------*/
/* AFPDeleteSharedVolumesEnumerator: deletes the enumerator					 */
/*---------------------------------------------------------------------------*/

EXTERN_API( OSStatus )
AFPDeleteSharedVolumesEnumerator (AFPSharedVolumesEnumeratorRef * ref);

/*---------------------------------------------------------------------------*/
/* AFPGetLoginInformation: returns the login information (will change)		 */
/*---------------------------------------------------------------------------*/

EXTERN_API( OSStatus )
AFPGetLoginInformation			(AFPSharedVolumesEnumeratorRef  ref,
								 Boolean *				isGuest,
								 Str255 				userName,
								 Str255 				password);


/*---------------------------------------------------------------------------*/
/* AFPChangePassword: Changes the password from oldPassword to newPassword	 */
/*---------------------------------------------------------------------------*/

EXTERN_API( OSStatus )
AFPChangePassword				(AFPSharedVolumesEnumeratorRef * ref,
								 StringPtr 				oldPassword,
								 StringPtr 				newPassword);



#if PRAGMA_STRUCT_ALIGN
	#pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
	#pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
	#pragma pack()
#endif

#ifdef PRAGMA_IMPORT_OFF
#pragma import off
#elif PRAGMA_IMPORT
#pragma import reset
#endif

#ifdef __cplusplus
}
#endif

#endif /* _AFPCLIENT__ */

