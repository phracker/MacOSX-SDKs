/*
     File:       DiscRecordingEngine/DRStatus.h
 
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

#import <Foundation/Foundation.h>
#import <AvailabilityMacros.h>


#if 0
#pragma mark Common status dictionary keys
#endif
/*!
	@const DRStatusStateKey
	@discussion	A key for the status dictionaries. 
				NSString indicating the current state of the operation.
*/
extern NSString* const	DRStatusStateKey				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const DRStatusPercentCompleteKey
	@discussion	A key for the status dictionaries. 
				NSNumber containing the precent complete of the operation expressed as
				a foating point number from 0 to 1.
*/
extern NSString* const	DRStatusPercentCompleteKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;




#if 0
#pragma mark Burn status dictionary keys
#endif
/*!
	@const DRStatusCurrentSessionKey
	@discussion	A key for the burn status dictionary. 
				NSNumber indicating the current session being burned.
*/
extern NSString* const	DRStatusCurrentSessionKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const DRStatusCurrentTrackKey
	@discussion	A key for the status dictionaries. 
				NSNumber indicating the current track being burned.
*/
extern NSString* const	DRStatusCurrentTrackKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const DRStatusTotalSessionsKey
	@discussion	A key for the status dictionaries. 
				NSNumber indicating the total number of sessions being burned.
*/
extern NSString* const	DRStatusTotalSessionsKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const DRStatusTotalTracksKey
	@discussion	A key for the status dictionaries. 
				NSNumber indicating the total number of tracks in the current session being burned.
*/
extern NSString* const	DRStatusTotalTracksKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const DRStatusCurrentSpeedKey
	@discussion	A key for the burn status dictionary. 
				NSNumber indicating the current burn speed.
*/
extern NSString* const	DRStatusCurrentSpeedKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



#if 0
#pragma mark Erase status dictionary keys
#endif
/*!
	@const DRStatusEraseTypeKey
	@discussion	A key for the erase status dictionary. 	
				NSString indicating the type of erase operation.
*/
extern NSString* const DRStatusEraseTypeKey				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;




#if 0
#pragma mark Common values for DRStatusStateKey
#endif
/*!
	@const DRStatusStateNone
	@discussion	One possible value for @link DRStatusStateKey DRStatusStateKey @/link. Indicates the
				operation has not yet begun.
*/
extern NSString* const DRStatusStateNone					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const DRStatusStatePreparing
	@discussion	One possible value for @link DRStatusStateKey DRStatusStateKey @/link. Indicates the
				operation is preparing to begin.
*/
extern NSString* const DRStatusStatePreparing			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const DRStatusStateVerifying
	@discussion	One possible value for @link DRStatusStateKey DRStatusStateKey @/link. Indicates the
				operation is verifying what it did.
*/
extern NSString* const	DRStatusStateVerifying			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const DRStatusStateDone
	@discussion	One possible value for @link DRStatusStateKey DRStatusStateKey @/link. Indicates the
				operation is finished and it succeeded.
*/
extern NSString* const DRStatusStateDone					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const DRStatusStateFailed
	@discussion	One possible value for @link DRStatusStateKey DRStatusStateKey @/link. Indicates the
				operation is finished and it failed.
*/
extern NSString* const DRStatusStateFailed				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;




#if 0
#pragma mark Burn dictionary values for DRStatusStateKey
#endif
/*!
	@const DRStatusStateSessionOpen
	@discussion	One possible value for @link DRStatusStateKey DRStatusStateKey @/link in the burn status dictionary. 
				Indicates the burn is opening a session on disc. The exact session being opened
				is contained in @link DRStatusCurrentSessionKey DRStatusCurrentSessionKey @/link.
*/
extern NSString* const	DRStatusStateSessionOpen		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const DRStatusStateTrackOpen
	@discussion	One possible value for @link DRStatusStateKey DRStatusStateKey @/link in the burn status dictionary. 
				Indicates the burn is opening a track on disc. The exact track being opened
				is contained in @link DRStatusCurrentTrackKey DRStatusCurrentTrackKey @/link.
*/
extern NSString* const	DRStatusStateTrackOpen			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const DRStatusStateTrackWrite
	@discussion	One possible value for @link DRStatusStateKey DRStatusStateKey @/link in the burn status dictionary. 
				Indicates the burn is writing a track on disc. The exact track being written
				is contained in @link DRStatusCurrentTrackKey DRStatusCurrentTrackKey @/link.
*/
extern NSString* const	DRStatusStateTrackWrite		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const DRStatusStateTrackClose
	@discussion	One possible value for @link DRStatusStateKey DRStatusStateKey @/link in the burn status dictionary. 
				Indicates the burn is closing a track on disc. The exact track being closed
				is contained in @link DRStatusCurrentTrackKey DRStatusCurrentTrackKey @/link.
*/
extern NSString* const	DRStatusStateTrackClose		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const DRStatusStateSessionClose
	@discussion	One possible value for @link DRStatusStateKey DRStatusStateKey @/link in the burn status dictionary. 
				Indicates the burn is closing a session on disc. The exact session being closing
				is contained in @link DRStatusCurrentSessionKey DRStatusCurrentSessionKey @/link.
*/
extern NSString* const	DRStatusStateSessionClose		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const DRStatusStateFinishing
	@discussion	One possible value for @link DRStatusStateKey DRStatusStateKey @/link in the burn status dictionary. 
				Indicates the burn is finishing up (closing the last session, writing the TOC, etc).
*/
extern NSString* const	DRStatusStateFinishing			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;




#if 0
#pragma mark Erase dictionary values for DRStatusStateKey
#endif
/*!
	@const DRStatusStateErasing
	@discussion	One possible value for @link DRStatusStateKey DRStatusStateKey @/link in the erase status dictionary. 
				Indicates the erase is currently in progress.
*/
extern NSString* const DRStatusStateErasing				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



#if 0
#pragma mark Extended progress dictionary values
#endif
/*!
	@const DRStatusProgressInfoKey
	@abstract	A dictionary of extended progress information.
	@discussion A key for the status dictionary. The value of this key is a reference to a NSDictionary
				object containing extended progress information.
*/
extern NSString* const DRStatusProgressInfoKey			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const DRStatusProgressCurrentKPS
	@abstract	The current burn speed in kilobytes per second.
	@discussion This is an optional key within the @link DRStatusProgressInfoKey DRStatusProgressInfoKey @/link dictionary. The value of this
				key, if present, is a NSNumber object containing the write speed of the burn.
*/
extern NSString* const DRStatusProgressCurrentKPS		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const DRStatusProgressCurrentXFactor
	@abstract	The current burn speed in a media appropriate x-factor
	@discussion This is an optional key within the @link DRStatusProgressInfoKey DRStatusProgressInfoKey @/link dictionary. The value of this
				key, if present, is a NSNumber object containing the appropriate x-factor for the media.
*/
extern NSString* const DRStatusProgressCurrentXFactor	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;




#if 0
#pragma mark Status dictionary error keys
#endif

/*!
	@const		DRErrorStatusKey
	@discussion	The key in the status dictionary for the error dictionary.
*/
extern NSString* const DRErrorStatusKey							AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRErrorStatusErrorKey
	@discussion	An NSNumber containing the OS error code for the error.
*/
extern NSString* const DRErrorStatusErrorKey					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRErrorStatusErrorStringKey
	@discussion	An NSString describing the error in a user appropriate manner.
*/
extern NSString* const DRErrorStatusErrorStringKey				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRErrorStatusErrorInfoStringKey
	@discussion	An NSString describing extended error information in a user appropriate manner.
*/
extern NSString* const DRErrorStatusErrorInfoStringKey			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		DRErrorStatusSenseKey
	@discussion	An NSData object containing the raw RBC sense information structure reported by the device.
				If no sense is reported, this key will not be present.
*/
extern NSString* const DRErrorStatusSenseKey					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRErrorStatusSenseCodeStringKey
	@discussion	An NSString describing the RBC sense code returned by the device.
				If no sense is reported, this key will not be present.
*/
extern NSString* const DRErrorStatusSenseCodeStringKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRErrorStatusAdditionalSenseStringKey
	@discussion	An NSString describing the RBC additional sense code and additional 
				sense code qualifier pair returned by the device.
				If no sense is reported, this key will not be present.
*/
extern NSString* const DRErrorStatusAdditionalSenseStringKey	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
