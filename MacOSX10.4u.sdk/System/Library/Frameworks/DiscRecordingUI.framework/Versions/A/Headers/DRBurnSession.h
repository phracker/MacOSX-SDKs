
/*
     File:       DiscRecordingUI/DRBurnSession.h
 
     Contains:   Carbon burn user interface for DiscRecording.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*!	
	@header		DRBurnSession.h
	@abstract	Burn configuration and progress user interface for Carbon applications
	@discussion	
*/

#ifndef _H_DRBurnSession
#define _H_DRBurnSession

#ifndef _H_DiscRecording
#import <DiscRecording/DiscRecording.h>
#endif

#ifndef __CARBON__
#import <Carbon/Carbon.h>
#endif

#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif


/*!
	@typedef DRBurnSessionRef
	This is the type of a reference to DRBurnSession instances.
*/
typedef struct __DRBurnSession*		DRBurnSessionRef;

/*!
	@function	DRBurnSessionGetTypeID
	@abstract	Returns the type identifier of all DRBurnSession instances.
	@result		A Core Foundation type ID.
*/
extern CFTypeID
DRBurnSessionGetTypeID()									AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@function	DRBurnSessionCreate
	@abstract	Creates a new burn session.
	@result		A reference to a new DRBurnSession.
*/
extern DRBurnSessionRef
DRBurnSessionCreate()										AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@function	DRBurnSessionSetBurn
	@abstract	Sets the burn object for this session.
	@param		burnSession	The burn session. If this parameter is not a valid
							@link DRBurnSessionRef DRBurnSessionRef @/link, the behavior is undefined. 
	@param		burn		The burn to use for the session. If this parameter is not a valid
							@link //apple_ref/c/tdef/DRBurnRef DRBurnRef @/link, the behavior is undefined. 
*/
extern void
DRBurnSessionSetBurn(
	DRBurnSessionRef	burnSession,
	DRBurnRef			burn)								AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@function	DRBurnSessionGetBurn
	@abstract	Returns the burn object for this session.
	@param		burnSession	The burn session. If this parameter is not a valid
							@link DRBurnSessionRef DRBurnSessionRef @/link, the behavior is undefined. 
	@result		A reference to the burn object for the session. If the setup dialog has not been run or
				a burn object has not been set with @link DRBurnSessionSetBurn DRBurnSessionSetBurn @/link, this function returns <i>NULL</i>.
*/
extern DRBurnRef
DRBurnSessionGetBurn(
	DRBurnSessionRef	burnSession)						AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*	¥ Dialog Result Codes
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*!
	@enum		Burn Session Dialog Result Codes
	@discussion	Return codes for the burn session setup dialog.
	@constant	kDRBurnSessionOK		Value returned by the setup dialog when the user has confirmed the burn setup.
	@constant	kDRBurnSessionCancel	Value returned by the setup dialog when the user has canceled the burn setup.
*/
enum {
	kDRBurnSessionOK				= 1,
	kDRBurnSessionCancel			= 0,
};


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*	¥ Setup Dialog Options
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*!
	@enum		DRBurnSessionSetupDialogOptions struct version
	@discussion	
*/
enum {
	kBurnSessionSetupDialogOptionsCurrentVersion      = 1
};

/*!
	@enum		Burn Setup Dialog Option Flags
	@discussion	Flags used to configure the burn setup dialog behavior
	@constant	kBurnSessionSetupDialogDefaultOptions	Use defaults for all the options
	@constant	kBurnSessionSetupDialogForceClosedDiscs	Force discs to be closed (not appendable)
	@constant	kBurnSessionSetupDialogDontHandleReservations	Burn session does not handle media reservations. Application handles them itself
	@constant	kBurnSessionSetupDialogAllowTestBurns Allow the user to perform a test burn
*/
enum {
	kBurnSessionSetupDialogDefaultOptions			= 0x00000000,	/* use defaults for all the options */
	kBurnSessionSetupDialogForceClosedDiscs			= 0x00000001,	/* Force discs to be closed (not appendable) */
	kBurnSessionSetupDialogDontHandleReservations	= 0x00000002,	/* Don't handle media reservations. Application handles them itself */
	kBurnSessionSetupDialogAllowTestBurns			= 0x80000004	/* Allow the user to perform a test burn */
};

/*!
	@typedef 	DRBurnSessionSetupDialogOptionFlags
	@abstract	Specifies setup dialog configuration options.
*/
typedef UInt32 DRBurnSessionSetupDialogOptionFlags;


/*!
	@struct 	DRBurnSessionSetupDialogOptions
	@abstract	Options passed into the setup dialog to configure it.
	@field		version				Identifies the version of this structure.
	@field		dialogOptionFlags	One of several constants defined by the @link DRBurnSessionSetupDialogOptionFlags DRBurnSessionSetupDialogOptionFlags @/link 
									data type as described in @link //apple_ref/c/tag/Burn%32Setup%32Dialog%32Option%32Flags Burn Setup Dialog Option Flags @/link.
	@field		defaultButtonTitle	A CFStringRef that defines a custom title to be used for the dialog's default button.
									If you do not provide this string (passing <i>NULL</i>), the normal button title is used.
*/
struct DRBurnSessionSetupDialogOptions {
	UInt32									version;
	DRBurnSessionSetupDialogOptionFlags		dialogOptionFlags;		/* option flags for affecting the dialog's behavior */
	CFStringRef								defaultButtonTitle;		/* title of default button */
};
typedef struct DRBurnSessionSetupDialogOptions	DRBurnSessionSetupDialogOptions;


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*	¥ Setup Dialog Callbacks
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*!
	@enum		DRBurnSessionSetupCallbacks struct version
	@discussion	
*/
enum {
	kDRBurnSessionSetupCallbacksCurrentVersion	= 1
};

/*!
	@typedef	DRBurnSessionDeviceCheckProcPtr
	@abstract	Callback used for checking the suitability of a device.
	@discussion This callback is called whenever a new device appears. It's purpose is to allow the
				application to filter out devices which do not support the operation to be performed. for
				example, a device may filter our CD-R/Ws if it is a DVD creation appliacation.
	@param		burnSession	The burn session object.
	@param		device		The device to examine.
	@result		A Boolean value indicating the suitability of the device.
*/
typedef CALLBACK_API( Boolean , DRBurnSessionDeviceCheckProcPtr )(DRBurnSessionRef burnSession, DRDeviceRef device);

/*!
	@typedef	DRBurnSessionMediaCheckProcPtr
	@abstract	Callback used for checking the suitability of media in a device.
	@discussion This callback is called whenever the state of the media has changed. It's purpose is to allow the
				application to determine if the media is suitable for the operation to be performed. For example,
				the application an check to see if there is enough space on the media for the data to be written.
	@param		burnSession	The burn session object.
	@param		device		The device containing the media to examine.
	@param		prompt		A pointer to a CFStringRef. An application may return a custom message to display in the 
							setup dialog.
	@result		A Boolean value indicating the suitability of the media.
*/
typedef CALLBACK_API( Boolean , DRBurnSessionMediaCheckProcPtr )(DRBurnSessionRef burnSession, DRDeviceRef device, CFStringRef* prompt);

/*!
	@typedef	DRBurnSessionDeviceSelectionNotificationProcPtr
	@abstract	Callback used to notify the application of a new device selected.
	@param		burnSession	The burn session object.
	@param		device		The newly selected device.
*/
typedef CALLBACK_API( void , DRBurnSessionDeviceSelectionNotificationProcPtr )(DRBurnSessionRef burnSession, DRDeviceRef device);

/*!
	@struct		DRBurnSessionSetupCallbacks
	@abstract	Callback functions passed to the setup dialog.
	@field		version					Identifies the version of this structure.
	@field		deviceShouldBeTarget	Pointer to a DRBurnSessionDeviceCheckProcPtr. The value of this field may be <i>NULL</i>.
	@field		containsSuitableMedia	Pointer to a DRBurnSessionMediaCheckProcPtr. The value of this field may be <i>NULL</i>.
	@field		deviceSelectionChanged	Pointer to a DRBurnSessionDeviceSelectionNotificationProcPtr. The value of this field may be <i>NULL</i>.
*/
struct DRBurnSessionSetupCallbacks {
	UInt32											version;
	DRBurnSessionDeviceCheckProcPtr					deviceShouldBeTarget;
	DRBurnSessionMediaCheckProcPtr					containsSuitableMedia;
	DRBurnSessionDeviceSelectionNotificationProcPtr	deviceSelectionChanged;
};
typedef struct DRBurnSessionSetupCallbacks	DRBurnSessionSetupCallbacks;


/*!
	@function	DRBurnSessionSetupDialog
	@abstract	Presents the setup interface as a modal dialog.
	@discussion	This function present the user with a modal dialog that allows them to configure a burn to their custom
				settings. These include: the device to use, whether or not to eject the media when finished, the burn speed
				and others. The function does not return until the user dismissed the dialog.
	@param		burnSession	The burn session object
	@param		options		A pointer to a structure of type @link DRBurnSessionSetupDialogOptions DRBurnSessionSetupDialogOptions @/link. 
							This pointer may be <i>NULL</i> if no custom configuration is required.
	@param		setupCallbacks	A pointer to a structure of type @link DRBurnSessionSetupCallbacks DRBurnSessionSetupCallbacks @/link. 
								This pointer may be <i>NULL</i> if no custom behavior is desired.
	@result		Returns one of the constants defined by @link //apple_ref/c/tag/Burn%32Session%32Dialog%32Result%32Codes Burn Session Dialog Result Codes @/link.
*/
extern SInt8
DRBurnSessionSetupDialog(
	DRBurnSessionRef					burnSession,
	DRBurnSessionSetupDialogOptions*	options,
	DRBurnSessionSetupCallbacks*		setupCallbacks)		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
	

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*	¥ Progress Dialog Callbacks
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*!
	@enum		kDRBurnProgressSetupCallbacksCurrentVersion struct version
	@discussion	
*/
enum {
	kDRBurnProgressSetupCallbacksCurrentVersion	= 1
};


/*!
	@typedef	DRBurnSessionProgressBeginNotificationProcPtr
	@abstract	Callback notifying the application the burn progress is about to begin.
	@discussion	This callback is called when the burn progress is about to be displayed. This allows the application
				to do things such as disable the quit menu item, or the close menu for a document window.
	@param		burnSession	The burn session object.
*/
typedef CALLBACK_API( void , DRBurnSessionProgressBeginNotificationProcPtr )(DRBurnSessionRef burnSession);

/*!
	@typedef	DRBurnSessionProgressFinishNotificationProcPtr
	@abstract	Callback notifying the application the burn progress has finished.
	@discussion	This callback is called when the burn progress has been removed from view. This allows the application
				to do things such as re-enable the quit menu item, or the close menu for a document window.
	@param		burnSession	The burn session object.
*/
typedef CALLBACK_API( void , DRBurnSessionProgressFinishNotificationProcPtr )(DRBurnSessionRef burnSession);

/*!
	@typedef	DRBurnSessionBurnCompleteProcPtr
	@abstract	Callback notifying the application the burn has finished.
	@discussion	This callback is called when the burn operation completes, either successfully or with an error.
				This function can be used by the application to present it's own custom end-of-burn handling. 
				Return a false return value to prevent the burn session from presenting it's own notification.
	@param		burnSession	The burn session object.
	@param		burn		The burn instance that just finished.
	@result		A Boolean value controlling the display of the burn session's error dialog.
*/
typedef CALLBACK_API( Boolean , DRBurnSessionBurnCompleteProcPtr )(DRBurnSessionRef burnSession, DRBurnRef burn);

/*!
	@struct		DRBurnSessionProgressCallbacks
	@abstract	Callback functions passed to the progress dialog.
	@field		version				Identifies the version of this structure.
	@field		progressWillBegin	Pointer to a DRBurnSessionProgressBeginNotificationProcPtr. The value of this field may be <i>NULL</i>.
	@field		progressDidFinish	Pointer to a DRBurnSessionProgressFinishNotificationProcPtr. The value of this field may be <i>NULL</i>.
	@field		burnDidFinish	Pointer to a DRBurnSessionBurnCompleteProcPtr. The value of this field may be <i>NULL</i>.
*/
struct DRBurnSessionProgressCallbacks {
	UInt32											version;
	DRBurnSessionProgressBeginNotificationProcPtr	progressWillBegin;
	DRBurnSessionProgressFinishNotificationProcPtr	progressDidFinish;
	DRBurnSessionBurnCompleteProcPtr				burnDidFinish;
};
typedef struct DRBurnSessionProgressCallbacks	DRBurnSessionProgressCallbacks;


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*	¥ Progress Dialog Options
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*!
	@enum		DRBurnSessionProgressDialogOptions struct version
	@discussion	
*/
enum {
	kBurnSessionProgressDialogOptionsCurrentVersion      = 1
};

/*!
	@enum		Burn Progress Dialog Option Flags
	@discussion	Flags used to configure the burn progress dialog behavior
	@constant	kBurnSessionProgressDialogDefaultOptions	Use defaults for all the options
	@constant	kBurnSessionProgressDialogDisplayVerboseProgress	Report all status changes in detail
*/
enum {
	kBurnSessionProgressDialogDefaultOptions			= 0x00000000,	/* use defaults for all the options */
	kBurnSessionProgressDialogDisplayVerboseProgress	= 0x00000001	/* Report all status changes in detail */
};

/*!
	@typedef 	DRBurnSessionProgressDialogOptionFlags
	@abstract	Specifies progress dialog configuration options.
*/
typedef UInt32 DRBurnSessionProgressDialogOptionFlags;

/*!
	@struct 	DRBurnSessionProgressDialogOptions
	@abstract	Options passed into the progress dialog to configure it.
	@field		version				Identifies the version of this structure.
	@field		dialogOptionFlags	One of several constants defined by the @link DRBurnSessionProgressDialogOptionFlags DRBurnSessionProgressDialogOptionFlags @/link 
									data type as described in @link //apple_ref/c/tag/Burn%32Progress%32Dialog%32Option%32Flags Burn Progress Dialog Option Flags @/link.
	@field		description			A CFStringRef that defines a custom description to be used for the dialog.
									If you do not provide this string (passing <i>NULL</i>), the normal description is used.
*/
struct DRBurnSessionProgressDialogOptions {
	UInt32									version;
	DRBurnSessionProgressDialogOptionFlags	dialogOptionFlags;		/* option flags for affecting the dialog's behavior */
	CFStringRef								description;			/* optional description of the burn */
};
typedef struct DRBurnSessionProgressDialogOptions	DRBurnSessionProgressDialogOptions;


/*!
	@function	DRBurnSessionBeginProgressDialog
	@abstract	Presents the progress interface as a non-modal dialog.
	@discussion	This function present the user with a non-modal dialog that shows the burn progress.
	@param		burnSession	The burn session object
	@param		layout		The track layout to be used for the burn.
	@param		options		A pointer to a structure of type @link DRBurnSessionSetupDialogOptions DRBurnSessionSetupDialogOptions @/link. 
	@param		progressCallbacks	A pointer to a structure of type @link DRBurnSessionProgressCallbacks DRBurnSessionProgressCallbacks @/link. 
									This pointer may be <i>NULL</i> if no custom behavior is desired.
*/
extern void
DRBurnSessionBeginProgressDialog(
	DRBurnSessionRef					burnSession,
	CFTypeRef							layout,
	DRBurnSessionProgressDialogOptions*	options,
	DRBurnSessionProgressCallbacks*		progressCallbacks)		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



#ifdef __cplusplus
}
#endif

#endif /* _H_DRBurnSession */
