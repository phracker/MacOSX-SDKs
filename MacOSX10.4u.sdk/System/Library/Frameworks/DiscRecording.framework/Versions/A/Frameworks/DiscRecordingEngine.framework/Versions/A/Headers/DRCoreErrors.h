/*
     File:       DiscRecordingEngine/DRCoreErrors.h
 
     Contains:   Error code interfaces for Disc Recording.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*!
	@header
	@abstract		Disc Recording error codes and descriptions.

	@discussion		Disc Recording provides functions to map OS errors it defines
					and sense information returned from device command errors to
					localized string representations.
*/

#ifndef _H_DRCoreErrors
#define _H_DRCoreErrors

#if PRAGMA_ONCE
#pragma once
#endif

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __AVAILABILITYMACROS__
#include <AvailabilityMacros.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*! 
	@enum DiscRecording Errors
	@discussion	Errors returned from the Disc Recording framework. All errors returned by 
				the Disc Recording framework will fall into the range of 0x80020000 -> 0x8002FFFF.
	@constant kDRInternalErr  Internal Disc Recording error. 
	@constant kDRDeviceAccessErr  Device is not accessible, hardware is disconnected, etc. 
	@constant kDRDeviceBusyErr  Device is in use by another process 
	@constant kDRDeviceCommunicationErr  Device failed to respond properly, unable to recover or retry. 
	@constant kDRDeviceInvalidErr  Attempt was made to use an invalid DRDeviceRef. 
	@constant kDRDeviceNotReadyErr  Device is unable to respond now, please try again later. 
	@constant kDRDeviceNotSupportedErr  Device is not supported for the requested burn operation. 
	@constant kDRMediaBusyErr  Disc is busy, usually indicating the volume is unmountable. 
	@constant kDRMediaNotPresentErr  Disc isn't present, and needs to be. 
	@constant kDRMediaNotWritableErr  Disc isn't writable, and needs to be. 
	@constant kDRMediaNotSupportedErr  Disc isn't supported for the requested burn operation. 
	@constant kDRMediaNotBlankErr  Disc isn't blank, and the requested operation needs it to be. 
	@constant kDRMediaNotErasableErr  Disc isn't erasable, and the requested operation needs it to be. 
	@constant kDRBurnUnderrunErr  The burn failed because the device drained its buffer without burn underrun protection. 
	@constant kDRBurnNotAllowedErr  User is not allowed to burn to this device on this system. 
	@constant kDRDataProductionErr  Error while producing data for the burn 
	@constant kDRVerificationFailedErr  Data verification failed 
	@constant kDRTooManyTracksForDVDErr  DVD discs can contain only one track 
	@constant kDRBadLayoutErr  Too many tracks or sessions 
	@constant kDRUserCanceledErr  User canceled the burn 
	@constant kDRFunctionNotSupportedErr  Track producer cannot perform requested function 
	@constant kDRTrackReusedErr One or more tracks were included multiple times in the burn
	@constant kDRFileModifiedDuringBurnErr  File changed during flatten or burn 
	@constant kDRFileLocationConflictErr  Conflicting locations specified for two files 
	@constant kDRTooManyNameConflictsErr  Too many filename conflicts to resolve (10,000,000 or more) 
	@constant kDRDeviceCantWriteCDTextErr Device does not support writing CD-Text
	@constant kDRDeviceBurnStrategyNotAvailableErr  Device does not support the required burn strategy for this burn 
	@constant kDRDeviceCantWriteIndexPointsErr  Device does not support writing index points 
	@constant kDRDeviceCantWriteISRCErr  Device does not support writing ISRC 
	@constant kDRDeviceCantWriteSCMSErr  Device does not support writing SCMS 
	@constant kDRDevicePreGapLengthNotValidErr	Device does not support the required pregap length for the track
*/
enum
{
	kDRFirstErr						= 0x80020000,
	kDRInternalErr					= kDRFirstErr,
	
	kDRDeviceAccessErr				= 0x80020020,
	kDRDeviceBusyErr				= 0x80020021,
	kDRDeviceCommunicationErr		= 0x80020022,
	kDRDeviceInvalidErr				= 0x80020023,
	kDRDeviceNotReadyErr			= 0x80020024,
	kDRDeviceNotSupportedErr		= 0x80020025,
	
	kDRMediaBusyErr					= 0x80020040,
	kDRMediaNotPresentErr			= 0x80020041,
	kDRMediaNotWritableErr			= 0x80020042,
	kDRMediaNotSupportedErr			= 0x80020043,
	kDRMediaNotBlankErr				= 0x80020044,
	kDRMediaNotErasableErr			= 0x80020045,
	
	kDRBurnUnderrunErr				= 0x80020060,
	kDRBurnNotAllowedErr			= 0x80020061,
	kDRDataProductionErr			= 0x80020062,
	kDRVerificationFailedErr		= 0x80020063,
	kDRTooManyTracksForDVDErr		= 0x80020064,
	kDRBadLayoutErr					= 0x80020065,
	kDRUserCanceledErr				= 0x80020066,
	kDRFunctionNotSupportedErr		= 0x80020067,
	kDRTrackReusedErr				= 0x8002006F,

	/* content errors */
	kDRFileModifiedDuringBurnErr	= 0x80020100,
	kDRFileLocationConflictErr		= 0x80020101,
	kDRTooManyNameConflictsErr		= 0x80020102,
	kDRDeviceCantWriteCDTextErr		= 0x80020201,
	
	/* drive feature errors */
	kDRDeviceBurnStrategyNotAvailableErr	= 0x80020200,
	kDRDeviceCantWriteIndexPointsErr		= 0x80020202,
	kDRDeviceCantWriteISRCErr				= 0x80020203,
	kDRDeviceCantWriteSCMSErr				= 0x80020204,
	kDRDevicePreGapLengthNotValidErr		= 0x80020205
};

/*!
	@function 	DRCopyLocalizedStringForDiscRecordingError
	@abstract 	Maps an operating system error code to a localized string.
	@discussion If a localized string cannot be found, this function returns the error code 
				as a string.
	@param 		osError 	The OS error code.
	@result 	A value of type CFStringRef which contains the localized string. 
				This reference is implicitly retained by the caller. 
*/
CFStringRef DRCopyLocalizedStringForDiscRecordingError(OSStatus osError);

/*!
	@function 	DRCopyLocalizedStringForSenseCode
	@abstract 	Maps a SCSI sense code to a localized string.
	@discussion This function takes a sense code and finds the corresponding localized string. 
				If a localized string cannot be found, it returns the sense code as a string.
	@param 		senseCode 	A sense code generated by a device conforming to the SCSI standard.
	@result 	A value of type CFStringRef containing the localized string. 
				This reference is implicitly retained by the caller. 
*/
CFStringRef DRCopyLocalizedStringForSenseCode(UInt8 senseCode);

/*!
	@function 	DRCopyLocalizedStringForAdditionalSense
	@abstract 	Maps the Additional Sense Code (ASC) and Additional Sense Key Qualifier (ASCQ) to a localized string.
	@discussion This function takes an ASC/ASCQ pair and finds the correct localized string corresponding
				to that pair. The function attempts to find the exact pair, followed by one of the range ASC codes.
				If neither of those can be found, it will determine if the pair is reserved or is a vendor specific pair and will
				return a string indicating that. If a localized string cannot be found, it will return the ASC and ASCQ codes 
				as a string.
	@param 		ASC 	The Additional Sense Code generated by a device conforming the SCSI standard.
	@param 		ASCQ 	The Additional Sense Code Qualifier generated by a device conforming to the SCSI standard.
	@result 	A value of type CFStringRef containing the localized string. 
				This reference is implicitly retained by the caller. 
*/
CFStringRef DRCopyLocalizedStringForAdditionalSense(UInt8 ASC, UInt8 ASCQ);

/*!
	@const kDRErrorStatusKey
	@discussion	A key for the DRErrorStatus dictionary, returned by any of the <tt>DRxxxCopyStatus</tt> calls or
				<tt>kDRxxxStatusChangedNotifications</tt>, to describe a failure.  The value of this key is a
				CFDictionary object containing error code and device sense information.
*/
extern const CFStringRef kDRErrorStatusKey							AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRErrorStatusErrorKey
	@discussion	A key for the DRErrorStatus dictionary. The value of this key is a CFNumber object containing
				the OSStatus value corresponding to the failure.
*/
extern const CFStringRef kDRErrorStatusErrorKey						AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRErrorStatusErrorStringKey
	@discussion	A key for the DRErrorStatus dictionary. The value of this key is a CFString object containing
				the localized string describing the kDRErrorStatusErrorKey key.  This value is optional and
				may not be present if a suitable string does not exist to describe the failure.
*/
extern const CFStringRef kDRErrorStatusErrorStringKey				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRErrorStatusErrorInfoStringKey
	@discussion	A key for the DRErrorStatus dictionary. The value of this key is a CFString object containing
				a string providing additional information for the error.  This value is optional and
				may not be present if a suitable string does not exist to describe the failure.
*/
extern const CFStringRef kDRErrorStatusErrorInfoStringKey			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const kDRErrorStatusSenseKey
	@discussion	A key for the DRErrorStatus dictionary. The value of this key is a CFData object containing
				the device sense data describing the failure.  This value is optional and may not be
				present if the failure was not device-related, or if the device failed in a way which
				did not provide meaningful sense data.
*/
extern const CFStringRef kDRErrorStatusSenseKey						AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRErrorStatusSenseCodeStringKey
	@discussion	A key for the DRErrorStatus dictionary. The value of this key is a CFString object containing
				the localized string describing the sense key from the sense data for the failure.
				This value is optional and will not be present if the kDRErrorStatusSenseKey key is not present
				or if a suitable string does not exist to describe the failure.
*/
extern const CFStringRef kDRErrorStatusSenseCodeStringKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRErrorStatusAdditionalSenseStringKey
	@discussion	A key for the DRErrorStatus dictionary. The value of this key is a CFString object containing
				the localized string describing the additonal sense from the sense data for the
				failure.  This value is optional and will not be present if the kDRErrorStatusSenseKey key is
				not present or if a suitable string does not exist to describe the failure.
*/
extern const CFStringRef kDRErrorStatusAdditionalSenseStringKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

#ifdef __cplusplus
}
#endif

#endif /* _H_DRCoreErrors */
