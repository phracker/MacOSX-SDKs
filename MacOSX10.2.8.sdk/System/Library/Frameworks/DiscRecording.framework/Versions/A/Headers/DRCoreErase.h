/*
     File:       DiscRecording/DRCoreErase.h
 
     Contains:   Erase object interfaces for DiscRecording.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef _H_DRCoreErase
#define _H_DRCoreErase

#if PRAGMA_ONCE
#pragma once
#endif

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef _H_DRCoreObject
#include <DiscRecording/DRCoreObject.h>
#endif

#ifndef _H_DRCoreDevice
#include <DiscRecording/DRCoreDevice.h>
#endif

#ifndef __AVAILABILITYMACROS__
#include <AvailabilityMacros.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*!
	@typedef DREraseRef
	This is the type of a reference to DRErases.
*/
typedef struct __DRErase*	DREraseRef;

/*!
	@function	DREraseGetTypeID
	@abstract	Returns the type identifier of all DRErase instances.
*/
extern
CFTypeID DREraseGetTypeID()
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DREraseCreate
	@abstract	Creates a new eraser.
	@param		device		A reference to the device to erase. If this parameter is not a 
							valid DRDevice, the behavior is undefined.
	@result		A reference to a new DRErase.
*/
extern
DREraseRef DREraseCreate(DRDeviceRef device)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DREraseStart
	@abstract	Begin the erase process.
	@param		erase		The eraser object that should be started. If this parameter 
							is not a valid DRErase, the behavior is undefined.
*/
extern
OSStatus DREraseStart(DREraseRef erase)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DREraseCopyStatus
	@abstract	Obtain the progress/status of the eraser.
	@discussion	Returns a CFDictionary containing the progress/status of the erase. This dictionary
				will contain the percentage complete and any errors reported.
	@result		A reference to a CFDictionary containing the progress of the erase as well as
				any errors reported. The dictionary reference is implicitly retained by the caller.
				This is the same dictionary sent to observers of kDREraseStatusChangedNotification.
*/
extern
CFDictionaryRef DREraseCopyStatus(DREraseRef erase)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDREraseStatusChangedNotification
	@discussion	The notification sent when a DREraseRef has updated status.
*/
extern const CFStringRef kDREraseStatusChangedNotification
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!
	@function	DREraseGetDevice
	@abstract	Return a reference to the device to erase.
	@param		erase	The erase object to get the device for. If this parameter 
						is not a valid DRErase, the behavior is undefined. 
	@result		The a reference to the device to erase to.
*/
extern
DRDeviceRef DREraseGetDevice(DREraseRef erase)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DREraseSetProperties
	@abstract	Sets the properties of the erase.
	@param		erase		The erase to set the properties of. If this parameter 
							is not a valid DRErase, the behavior is undefined. 
	@param		properties	A CFDictionaryRef containing the erase properties. If this
							parameter is not a valid CFDictionaryRef the behavior is undefined.
*/
extern
void DREraseSetProperties(DREraseRef erase, CFDictionaryRef properties)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DREraseGetProperties
	@abstract	Returns properties of the erase.
	@param		erase		The erase to get the properties of. If this parameter 
							is not a valid DRErase, the behavior is undefined. 
	@result		A CFDictionaryRef containing the erase properties.
*/
extern
CFDictionaryRef DREraseGetProperties(DREraseRef erase)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

#pragma mark Erase Properties
/*!
	@const kDREraseTypeKey
	@discussion	This key points to a CFString describing the type of erase to be performed.
				If this key is not present, kDREraseTypeQuick is assumed.
*/
extern const CFStringRef kDREraseTypeKey
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDREraseTypeQuick
	@discussion	A CFString indicating the erase operation should do the minimal amount of
				work to make the disc appear blank. This operation typically takes only a
				minute or two.
*/
extern const CFStringRef kDREraseTypeQuick
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDREraseTypeComplete
	@discussion	A CFString indicating the erase operation should erase every byte on the
				disk. This operation is slow (on the order of 30 minutes) to complete.
*/
extern const CFStringRef kDREraseTypeComplete
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

#ifdef __cplusplus
}
#endif

#endif /* _H_DRCoreErase */
