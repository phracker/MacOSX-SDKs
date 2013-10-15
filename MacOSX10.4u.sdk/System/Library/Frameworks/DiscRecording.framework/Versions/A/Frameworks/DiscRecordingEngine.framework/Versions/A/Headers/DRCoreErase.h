/*
     File:       DiscRecordingEngine/DRCoreErase.h
 
     Contains:   Erase object interfaces for Disc Recording.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*!	@header 	
	@abstract		Erase object interfaces for Disc Recording.

	@discussion		
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
#include <DiscRecordingEngine/DRCoreObject.h>
#endif

#ifndef _H_DRCoreDevice
#include <DiscRecordingEngine/DRCoreDevice.h>
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
	@abstract	Obtains the type identifier of all DRErase instances.
*/
extern
CFTypeID DREraseGetTypeID()
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DREraseCreate
	@abstract	Creates a new eraser.
	@param		device		A reference to the device to erase. If this parameter is not a 
							valid DRDevice, the behavior is undefined.
	@result		Returns a reference to a new DRErase opaque type.
*/
extern
DREraseRef DREraseCreate(DRDeviceRef device)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DREraseStart
	@abstract	Begin the erase process.
	@param		erase		The eraser object that should be started. If this parameter 
							is not a valid DRErase oject, the behavior is undefined.
	@result		An error code indicating if the erase could be started.
*/
extern
OSStatus DREraseStart(DREraseRef erase)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DREraseCopyStatus
	@abstract	Obtains the status of the erase process.
	@discussion	This function obtains a reference to a CFDictionary object containing the status of the erase process, including the 
				percentage complete and any errors reported. The reference is implicitly retained 
				by the caller. This is the same dictionary sent to observers of @link kDREraseStatusChangedNotification kDREraseStatusChangedNotification @/link.
	@param		erase		The eraser object that status is wanted on. 
	@result		Returns a reference to a CFDictionary object. 
*/
extern
CFDictionaryRef DREraseCopyStatus(DREraseRef erase)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDREraseStatusChangedNotification
	@discussion	The notification sent when a DRErase object has updated status.
*/
extern const CFStringRef kDREraseStatusChangedNotification
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!
	@function	DREraseGetDevice
	@abstract	Obtains a reference to the device containing the disc to erase.
	@param		erase	The eraser containing a reference to the device. If this parameter 
						is not a valid DRErase object, the behavior is undefined. 
	@result		Returns reference to the device containing the disc to erase.
*/
extern
DRDeviceRef DREraseGetDevice(DREraseRef erase)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DREraseSetProperties
	@abstract	Sets the properties of the erase process.
	@param		erase		The erase process to set the properties of. If this parameter 
							is not a valid DRErase object, the behavior is undefined. 
	@param		properties	A CFDictionary object containing the erase properties. If this
							parameter is not a valid CFDictionary object the behavior is undefined.
*/
extern
void DREraseSetProperties(DREraseRef erase, CFDictionaryRef properties)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DREraseGetProperties
	@abstract	Returns properties of the erase.
	@param		erase		The erase process to get the properties of. If this parameter 
							is not a valid DRErase object, the behavior is undefined. 
	@result		Returns a CFDictionary object containing the erase properties.
*/
extern
CFDictionaryRef DREraseGetProperties(DREraseRef erase)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

#pragma mark Erase Properties
/*!
	@const kDREraseTypeKey
	@discussion	This key points to a CFString object describing the type of erase to be performed.
				If this key is not present, a @link kDREraseTypeQuick kDREraseTypeQuick @/link erase type is assumed.
*/
extern const CFStringRef kDREraseTypeKey
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDREraseTypeQuick
	@discussion	A CFString object indicating the erase operation should do the minimal amount of
				work to make the disc appear blank. This operation typically takes only a
				minute or two.
*/
extern const CFStringRef kDREraseTypeQuick
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDREraseTypeComplete
	@discussion	A CFString object indicating the erase operation should erase every byte on the
				disc. This operation is slow, taking on the order of 30 minutes.
*/
extern const CFStringRef kDREraseTypeComplete
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

#ifdef __cplusplus
}
#endif

#endif /* _H_DRCoreErase */
