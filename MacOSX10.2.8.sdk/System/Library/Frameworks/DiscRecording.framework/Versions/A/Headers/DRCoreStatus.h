/*
     File:       DiscRecording/DRCoreStatus.h
 
     Contains:   Status dictionary content keys.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef _H_DRCoreStatus
#define _H_DRCoreStatus

#if PRAGMA_ONCE
#pragma once
#endif

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __AVAILABILITYMACROS__
#include <AvailabilityMacros.h>
#endif


#pragma mark Common status dictionary keys
/*!
	@const kDRStatusStateKey
	@discussion	A key for the status dictionaries. The value of this key is a CFString indicating 
				the current state of the operation.
*/
extern const CFStringRef	kDRStatusStateKey				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusPercentCompleteKey
	@discussion	A key for the status dictionaries. The value of this key is 
				a CFNumber containing the precent complete of the operation expressed as
				a foating point number from 0 to 1.
*/
extern const CFStringRef	kDRStatusPercentCompleteKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;




#pragma mark Burn status dictionary keys
/*!
	@const kDRStatusCurrentSpeedKey
	@discussion	A key for the burn status dictionary. The value of this key is 
				a CFNumber indicating the current burn speed.
*/
extern const CFStringRef	kDRStatusCurrentSpeedKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusCurrentSessionKey
	@discussion	A key for the burn status dictionary. The value of this key is 
				a CFNumber indicating the current session being burned.
*/
extern const CFStringRef	kDRStatusCurrentSessionKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusCurrentTrackKey
	@discussion	A key for the status dictionaries. The value of this key is 
				a CFNumber indicating the current track being burned.
*/
extern const CFStringRef	kDRStatusCurrentTrackKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusTotalSessionsKey
	@discussion	A key for the status dictionaries. The value of this key is 
				a CFNumber indicating the total number of sessions being burned.
*/
extern const CFStringRef	kDRStatusTotalSessionsKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusTotalTracksKey
	@discussion	A key for the status dictionaries. The value of this key is 
				a CFNumber indicating the total number of tracks in the current session being burned.
*/
extern const CFStringRef	kDRStatusTotalTracksKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;




#pragma mark Erase status dictionary keys
/*!
	@const kDRStatusEraseTypeKey
	@discussion	A key for the erase status dictionary. The value of this key is 
				a CFString indicating the type of erase operation.
*/
extern const CFStringRef kDRStatusEraseTypeKey				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;




#pragma mark Common values for kDRStatusStateKey
/*!
	@const kDRStatusStateNone
	@discussion	One possible value for kDRStatusStateKey. Indicates the
				operation has not yet begun.
*/
extern const CFStringRef kDRStatusStateNone					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusStatePreparingKey
	@discussion	One possible value for kDRStatusStateKey. Indicates the
				operation is preparing to begin.
*/
extern const CFStringRef kDRStatusStatePreparing			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusStateVerifying
	@discussion	One possible value for kDRStatusStateKey. Indicates the
				operation is verifying what it did.
*/
extern const CFStringRef	kDRStatusStateVerifying			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusStateDoneKey
	@discussion	One possible value for kDRStatusStateKey. Indicates the
				operation is finished and it succeeded.
*/
extern const CFStringRef kDRStatusStateDone					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusStateFailedKey
	@discussion	One possible value for kDRStatusStateKey. Indicates the
				operation is finished and it failed.
*/
extern const CFStringRef kDRStatusStateFailed				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;




#pragma mark Burn dictionary values for kDRStatusStateKey
/*!
	@const kDRStatusStateSessionOpen
	@discussion	One possible value for kDRStatusStateKey in the burn status dictionary. 
				Indicates the burn is opening a session on disc. The exact session being opened
				is contained in kDRStatusCurrentSessionKey.
*/
extern const CFStringRef	kDRStatusStateSessionOpen		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusStateTrackOpen
	@discussion	One possible value for kDRStatusStateKey in the burn status dictionary. 
				Indicates the burn is opening a track on disc. The exact track being opened
				is contained in kDRStatusCurrentTrackKey.
*/
extern const CFStringRef	kDRStatusStateTrackOpen			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusStateTrackWrite
	@discussion	One possible value for kDRStatusStateKey in the burn status dictionary. 
				Indicates the burn is writing a track on disc. The exact track being written
				is contained in kDRStatusCurrentTrackKey.
*/
extern const CFStringRef	kDRStatusStateTrackWrite		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusStateTrackClose
	@discussion	One possible value for kDRStatusStateKey in the burn status dictionary. 
				Indicates the burn is closing a track on disc. The exact track being closed
				is contained in kDRStatusCurrentTrackKey.
*/
extern const CFStringRef	kDRStatusStateTrackClose		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusStateSessionOpen
	@discussion	One possible value for kDRStatusStateKey in the burn status dictionary. 
				Indicates the burn is closing a session on disc. The exact session being closing
				is contained in kDRStatusCurrentSessionKey.
*/
extern const CFStringRef	kDRStatusStateSessionClose		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusStateFinishing
	@discussion	One possible value for kDRStatusStateKey in the burn status dictionary. 
				Indicates the burn is finishing up (closing the last session, writing the TOC, etc).
*/
extern const CFStringRef	kDRStatusStateFinishing			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;




#pragma mark Erase dictionary values for kDRStatusStateKey
/*!
	@const kDRStatusStateErasingKey
	@discussion	One possible value for kDRStatusStateKey in the erase status dictionary. 
				Indicates the erase is currently in progress.
*/
extern const CFStringRef kDRStatusStateErasing				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


#endif 	/* _H_DRCoreStatus */