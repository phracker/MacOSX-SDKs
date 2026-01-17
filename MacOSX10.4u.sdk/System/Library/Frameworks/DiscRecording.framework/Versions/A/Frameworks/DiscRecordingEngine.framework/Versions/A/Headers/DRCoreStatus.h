/*
     File:       DiscRecordingEngine/DRCoreStatus.h
 
     Contains:   Status dictionary content keys.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*!	@header 	
	@abstract		Status dictionary content keys.

	@discussion		
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
	@abstract	The state of the burn or erase operation.
	@discussion	A key for the status dictionaries. The value of this key is a CFString object indicating 
				the current state of the burn or erase operation.
*/
extern const CFStringRef	kDRStatusStateKey				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusPercentCompleteKey
	@abstract	The burn or erase operation's percentage of completion.
	@discussion	A key for the status dictionaries. The value of this key is 
				a CFNumber object containing the precentage of completion for the burn 
				or erase operation, expressed as a foating point number from 0 to 1.
*/
extern const CFStringRef	kDRStatusPercentCompleteKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;




#pragma mark Burn status dictionary keys
/*!
	@const kDRStatusCurrentSpeedKey
	@abstract	The current burn or erase speed.
	@discussion	A key for the burn status dictionary. The value of this key is 
				a CFNumber object containing the current burn or erase speed.
*/
extern const CFStringRef	kDRStatusCurrentSpeedKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusCurrentSessionKey
	@abstract	The number of the burn session.
	@discussion	A key for the burn status dictionary. The value of this key is 
				a CFNumber object containing the number of the current burn session.
*/
extern const CFStringRef	kDRStatusCurrentSessionKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusCurrentTrackKey
	@abstract	The number of the track being burned.
	@discussion	A key for the status dictionaries. The value of this key is 
				a CFNumber object containing the number of the track being burned.
*/
extern const CFStringRef	kDRStatusCurrentTrackKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusTotalSessionsKey
	@abstract	The total number of burn sessions.
	@discussion	A key for the status dictionaries. The value of this key is 
				a CFNumber object containing the total number of sessions being burned.
*/
extern const CFStringRef	kDRStatusTotalSessionsKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusTotalTracksKey
	@abstract	The number of tracks in the current session.
	@discussion	A key for the status dictionaries. The value of this key is 
				a CFNumber object containing the total number of tracks being burned in the current session.
*/
extern const CFStringRef	kDRStatusTotalTracksKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;




#pragma mark Erase status dictionary keys
/*!
	@const kDRStatusEraseTypeKey
	@abstract	The type of erase operation.
	@discussion	A key for the erase status dictionary. The value of this key is 
				a CFString object containing the type of erase operation -- either @link kDREraseTypeQuick kDREraseTypeQuick @/link
				or @link kDREraseTypeComplete kDREraseTypeComplete @/link.
*/
extern const CFStringRef kDRStatusEraseTypeKey				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;




#pragma mark Common values for kDRStatusStateKey
/*!
	@const kDRStatusStateNone
	@abstract	The burn or erase operation has not begun.
	@discussion	A value for the @link kDRStatusStateKey kDRStatusStateKey @/link dictionary key. This value indicates the
				burn or erase operation has not yet begun.
*/
extern const CFStringRef kDRStatusStateNone					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusStatePreparing
	@abstract	The burn or erase operation is preparing to begin.
	@discussion	A value for the @link kDRStatusStateKey kDRStatusStateKey @/link dictionary key. This value indicates the
				burn or erase operation is preparing to begin.
*/
extern const CFStringRef kDRStatusStatePreparing			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusStateVerifying
	@abstract	The burn or erase operation is being verified.
	@discussion	A value for the @link kDRStatusStateKey kDRStatusStateKey @/link dictionary key. This value indicates the
				operation is verifying what it did.
*/
extern const CFStringRef	kDRStatusStateVerifying			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusStateDone
	@abstract	The burn or erase operation finished successfully.
	@discussion	A value for the @link kDRStatusStateKey kDRStatusStateKey @/link dictionary key. This value indicates the
				burn or erase operation finished and succeeded.
*/
extern const CFStringRef kDRStatusStateDone					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusStateFailed
	@abstract	The burn or erase operation failed.
	@discussion	A value for the @link kDRStatusStateKey kDRStatusStateKey @/link dictionary key. This value indicates the
				burn or erase operation finished but failed.
*/
extern const CFStringRef kDRStatusStateFailed				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;




#pragma mark Burn dictionary values for kDRStatusStateKey
/*!
	@const kDRStatusStateSessionOpen
	@abstract	The burn session is opening.
	@discussion	A value for the @link kDRStatusStateKey kDRStatusStateKey @/link key in the burn status dictionary. 
				This value indicates the burn engine is opening a session on disc. The number of the session being opened
				is available as the value for the @link kDRStatusCurrentSessionKey kDRStatusCurrentSessionKey @/link dictionary key.
*/
extern const CFStringRef	kDRStatusStateSessionOpen		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusStateTrackOpen
	@abstract	The burn session is opening a track.
	@discussion	A value for the @link kDRStatusStateKey kDRStatusStateKey @/link key in the burn status dictionary. 
				This value indicates the burn engine is opening a track on disc. The number of the track being opened
				is available as the value for the @link kDRStatusCurrentTrackKey kDRStatusCurrentTrackKey @/link dictionary key.
*/
extern const CFStringRef	kDRStatusStateTrackOpen			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusStateTrackWrite
	@abstract	The burn session is writing a track.
	@discussion	A value for the @link kDRStatusStateKey kDRStatusStateKey @/link key in the burn status dictionary. 
				This value indicates the burn engine is writing a track on disc. The number of the track being written
				is available as the value for the in @link kDRStatusCurrentTrackKey kDRStatusCurrentTrackKey @/link dictionary key.
*/
extern const CFStringRef	kDRStatusStateTrackWrite		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusStateTrackClose
	@abstract	The burn session is closing a track.
	@discussion	A value for the @link kDRStatusStateKey kDRStatusStateKey @/link key in the burn status dictionary. 
				This value indicates the burn engine is closing a track on disc. The number of the track being closed
				is available as the value for the @link kDRStatusCurrentTrackKey kDRStatusCurrentTrackKey @/link dictionary key.
*/
extern const CFStringRef	kDRStatusStateTrackClose		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusStateSessionClose
	@abstract	The burn session is closing.
	@discussion	A value for the @link kDRStatusStateKey kDRStatusStateKey @/link key in the burn status dictionary. 
				This value indicates the burn engine is closing a session on disc. The number of the session being closed
				is available as the value for the @link kDRStatusCurrentSessionKey kDRStatusCurrentSessionKey @/link dictionary key.
*/
extern const CFStringRef	kDRStatusStateSessionClose		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRStatusStateFinishing
	@abstract	The burn session is finishing.
	@discussion	A value for the @link kDRStatusStateKey kDRStatusStateKey @/link key in the burn status dictionary. 
				This value indicates the burn is finishing--closing the last session, writing the TOC, and so on.
*/
extern const CFStringRef	kDRStatusStateFinishing			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;




#pragma mark Erase dictionary values for kDRStatusStateKey
/*!
	@const kDRStatusStateErasing
	@abstract	The disc is being erased.
	@discussion	A value for the @link kDRStatusStateKey kDRStatusStateKey @/link key in the erase status dictionary. 
				This value indicates the erase is currently in progress.
*/
extern const CFStringRef kDRStatusStateErasing				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;




#pragma mark Extended progress dictionary values
/*!
	@const kDRStatusProgressInfoKey
	@abstract	A dictionary of extended progress information.
	@discussion A key for the status dictionary. The value of this key is a reference to a CFDictionary
				object containing extended progress information.
*/
extern const CFStringRef kDRStatusProgressInfoKey			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const kDRStatusProgressCurrentKPS
	@abstract	The current burn speed in kilobytes per second.
	@discussion This is an optional key within the kDRStatusProgressInfo dictionary. The value of this
				key, if present, is a CFNumber object containing the write speed of the burn.
*/
extern const CFStringRef kDRStatusProgressCurrentKPS		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const kDRStatusProgressCurrentXFactor
	@abstract	The current burn speed in a media appropriate x-factor
	@discussion This is an optional key within the kDRStatusProgressInfo dictionary. The value of this
				key, if present, is a CFNumber object containing the appropriate x-factor for the media.
*/
extern const CFStringRef kDRStatusProgressCurrentXFactor	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


#endif 	/* _H_DRCoreStatus */
