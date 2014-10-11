
/*
     File:       DiscRecording/DRCoreTrack.h
 
     Contains:   Track object interfaces for DiscRecording.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef _H_DRCoreTrack
#define _H_DRCoreTrack

#if PRAGMA_ONCE
#pragma once
#endif

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef _H_DRCoreDevice
#include <DiscRecording/DRCoreDevice.h>
#endif

#ifndef _H_DRCoreObject
#include <DiscRecording/DRCoreObject.h>
#endif

#ifndef __AVAILABILITYMACROS__
#include <AvailabilityMacros.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*!
	@typedef DRTrackRef
	This is the type of a reference to DRTracks.
*/
typedef struct __DRTrack*	DRTrackRef;

/*!
	@function	DRTrackGetTypeID
	@abstract	Returns the type identifier of all DRTrack instances.
*/
extern
CFTypeID DRTrackGetTypeID()
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@typedef	DRFileMessage
	@abstract	Messages sent to DRTrackCallbackProc.
*/
typedef UInt32	DRTrackMessage;

/*!
    @typedef 	DRTrackCallbackProc
    @abstract	Callback function in the client to produce track data for recording.
	@discussion	If your callback does not support a given function, it should return
				kDRFunctionNotSupportedErr. 
    @param 		track		The track this callback is associated with.
    @param		message		Indicates the type of data requested. One of the enums in <i>Track Messages</i>.
 	@param		ioParam		Parameters are message-specific.
    @result 	Error code.  You should return kDRFunctionNotSupportedErr
				when a message was passed that you don't respond to.
*/
typedef OSStatus (*DRTrackCallbackProc)(
		DRTrackRef 		track,
		DRTrackMessage 	message,
		void* 			ioParam);

typedef struct DRTrackProductionInfo DRTrackProductionInfo;

/*!
	@function	DRTrackCreate
	@abstract	Creates a new track object.
	@param		properties	A CFDictionaryRef containing the track properties. If this
							parameter is not a valid CFDictionaryRef the behavior is undefined.
	@param		callbacks	A pointer to a DRTrackCallbackProc. If this callback is NULL
							the behavior is undefined.
	@result		A reference to the new DRTrack.
*/
extern
DRTrackRef DRTrackCreate(CFDictionaryRef properties, DRTrackCallbackProc callback)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRTrackSetProperties
	@abstract	Sets the properties of the track.
	@param		track		The track to set the properties of. If this parameter 
							is not a valid DRTrack, the behavior is undefined. 
	@param		properties	A CFDictionaryRef containing the track properties. If this
							parameter is not a valid CFDictionaryRef the behavior is undefined.
*/
extern
void DRTrackSetProperties(DRTrackRef track, CFDictionaryRef properties)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRTrackGetProperties
	@abstract	Returns the properties of the track.
	@param		track		The track to get the properties of. If this parameter 
							is not a valid DRTrack, the behavior is undefined. 
	@result		A CFMutableDictionaryRef containing the track properties.
*/
extern
CFDictionaryRef DRTrackGetProperties(DRTrackRef track)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

#pragma mark Required Track Properties
/*!
	@const		kDRTrackLengthKey
	@discussion	[Required Key] This key points to a CFNumber value holding the length of 
				the track data in blocks.
*/
extern const CFStringRef kDRTrackLengthKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRBlockSizeKey
	@discussion	[Required Key] This key points to a CFNumber value holding the size
				of each block of the track. Common values are defined in the <i>Block Sizes</i>
				enum.
*/
extern const CFStringRef kDRBlockSizeKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRBlockTypeKey
	@discussion	[Required Key] This key points to a CFNumber value holding the type
				of each block of the track. Common values are defined in the <i>Block Types</i>
				enum.
*/
extern const CFStringRef kDRBlockTypeKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRDataFormKey
	@discussion	[Required Key] This key points to a CFNumber value holding the data format
				of each block of the track. Common values are defined in the <i>Data Forms</i>
				enum.
*/
extern const CFStringRef kDRDataFormKey				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRSessionFormatKey
	@discussion	[Required Key] This key points to a CFNumber value holding the session format
				of the track. Common values are defined in the <i>Session Mode</i>
				enum.
*/
extern const CFStringRef kDRSessionFormatKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRTrackModeKey
	@discussion	[Required Key] This key points to a CFNumber value holding the track mode
				of the track. Common values are defined in the <i>Track Modes</i>
				enum.
*/
extern const CFStringRef kDRTrackModeKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


#pragma mark Optional Track Properties
/*!
	@const		kDRVerificationTypeKey
	@discussion	[Optional Key] This key points to a CFString indicating the kind of verification
				that should be performed. If the key is not present, no verification will take 
				place.
*/
extern const CFStringRef kDRVerificationTypeKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRVerificationTypeNone
	@discussion	If the kDRVerificationTypeKey's value is this then
				the engine will not do any sort of verification on the
				track data.
*/
extern const CFStringRef kDRVerificationTypeNone	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRVerificationTypeProduceAgain
	@discussion	If the kDRVerificationTypeKey's value is this then
				the engine will start another production cycle and the client 
				simply produces data again from the start.
*/
extern const CFStringRef kDRVerificationTypeProduceAgain	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRVerificationTypeReceiveData
	@discussion	If the kDRVerificationTypeKey's value is this then
				the engine read data from the disc and send it to the client
				through a series of calls to the callback.
*/
extern const CFStringRef kDRVerificationTypeReceiveData	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRDVDCopyrightInfoKey
	@discussion	[Optional Key] This key points to a CFData containing the correct MMC
				copyright info data. The contents of this data will
				be sent directly to the drive. If this key
				is not present, then no copyright information will be sent.
*/
extern const CFStringRef kDRDVDCopyrightInfoKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
													
/*!
	@const		kDRDVDTimestampKey
	@discussion	[Optional Key] This key points to a CFData containing the correct MMC
				timestamp data. The contents of this data will
				be sent directly to the drive. If this key 
				is not present, then no timestamp will be sent.
*/
extern const CFStringRef kDRDVDTimestampKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
													
/*!
	@const		kDRBufferZone1DataKey
	@discussion	[Optional Key] This key points to a CFData containing the data to
				write to Buffer Zone 1, on drives which support it (Pioneer DVR-S201).
				The contents of this data will be sent directly to the drive. If this
				key is not present, then no Buffer Zone 1 data will be sent.
*/
extern const CFStringRef kDRBufferZone1DataKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
													
/*!
	@const		kDRMaxBurnSpeedKey
	@discussion	[Optional Key] This key points to a CFNumber value holding the maximum 
				burn speed in Kps. Minimum is kDRDeviceBurnSpeed_CD_1x. If this key is not
				present the engine will assume minimum is kDRDeviceBurnSpeed_Max.
*/
extern const CFStringRef kDRMaxBurnSpeedKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRMaxBurnSpeedKey
	@discussion	[Optional Key] This key points to a CFNumber value holding the length of 
				empty space to be recorded before the track, in blocks. If this key is not
				present the engine will assume a 2 second (150 block) pregap.
*/
extern const CFStringRef kDRPreGapLengthKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


#pragma mark PreBurn Track Message Properties
/*!
	@const		kDRBurnKey
	@discussion	This key points to the DRBurnRef for which the PreBurn message applies.
*/
extern const CFStringRef kDRBurnKey					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*!
	@function	DRTrackSpeedTest
	@abstract	Test the speed that data can be produced at.
	@discussion	Runs a fake "production" cycle, calling the produceData callback for the specified 
				number of milliseconds, or until the specified number of bytes have been 
				produced, whichever comes first.
				Use this function to verify that the produceData callback can produce data fast 
				enough to satisfy the data throughput requirements of the burn.
	@param		track		The track to test. If this parameter 
							is not a valid DRTrack, the behavior is undefined. 
	@param		howManyMilliseconds	The maximum time the "production" cycle should run for. The 
								test may not run for this many milliseconds if the byte limit
								is reached first. If this parameter is 0, then the result is
								undefined.
	@param		howManyBytes	The maximum number of bytes of data the client should produce before
								completing the test. The test may not produce this many b yes if the 
								time limit is reached first. If this parameter is 0, then the result 
								is undefined. 
	@result		The maximum throughput obtained during the test cycle.
*/
extern
float DRTrackSpeedTest(DRTrackRef track, UInt32 howManyMilliseconds, UInt32 howManyBytes)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


#pragma mark - Block Sizes
/*!
	@enum 		Block Sizes
	@abstract	Common block sizes for different types of track data.
	@constant	kDRBlockSizeAudio		Audio data
	@constant	kDRBlockSizeMode1Data	Mode 1 data
	@constant	kDRBlockSizeDVDData		DVD data
*/	
enum
{
	kDRBlockSizeAudio		= 2352,
	kDRBlockSizeMode1Data	= 2048,
	kDRBlockSizeDVDData		= 2048
};

#pragma mark - Block Types
/*!
	@enum 		Block Types
	@abstract	Common block type values for types of track data.
	@constant	kDRBlockTypeAudio		Audio data
	@constant	kDRBlockTypeMode1Data	Mode 1 data
	@constant	kDRBlockTypeMode2Data	Mode 2 data. Photo CD and CD-i use this.
	@constant	kDRBlockTypeDVDData		DVD data
*/
enum
{
	kDRBlockTypeAudio		= 0,
	kDRBlockTypeMode1Data	= 8,
	kDRBlockTypeMode2Data	= 13,
	kDRBlockTypeDVDData		= 8
};

#pragma mark - Data Forms
/*!
	@enum 		Data Forms
	@abstract	Common data form values for types of track data.
	@constant	kDRDataFormAudio		Audio data
	@constant	kDRDataFormMode1Data	Mode 1 data
	@constant	kDRDataFormMode2Data	Mode 2 data. Photo CD and CD-i use this.
	@constant	kDRDataFormDVDData		DVD data
*/	
enum
{
	kDRDataFormAudio		= 0,
	kDRDataFormMode1Data	= 16,
	kDRDataFormMode2Data	= 32,
	kDRDataFormDVDData		= 16
};

#pragma mark - Track Modes
/*!
	@enum 		Track Modes
	@abstract	Common track mode values for types of track data.
	@constant	kDRTrackModeAudio		Audio data
	@constant	kDRTrackMode1Data		Mode 1 data
	@constant	kDRTrackMode2Data		Mode 2 data. Photo CD and CD-i use this.
	@constant	kDRTrackModeDVDData		DVD data
*/
enum
{
	kDRTrackModeAudio		= 0,
	kDRTrackMode1Data		= 4,
	kDRTrackMode2Data		= 4,
	kDRTrackModeDVDData		= 5
};

#pragma mark - Session Format
/*!
	@enum 		Session Format
	@abstract	Common session format values for types of track data.
	@constant	kDRSessionFormatAudio		Audio data
	@constant	kDRSessionFormatMode1Data	Mode 1 data
	@constant	kDRSessionFormatCDI			CD-I disc
	@constant	kDRSessionFormatCDXA		CD-ROM XA disc 
	@constant	kDRSessionFormatDVDData		DVD data
*/
enum
{
	kDRSessionFormatAudio		= 0,
	kDRSessionFormatMode1Data	= 0,
	kDRSessionFormatCDI			= 0x10,
	kDRSessionFormatCDXA		= 0x20,
	kDRSessionFormatDVDData		= 0
};

#pragma mark - Track Flags
/*!
	@enum	Track Flags
	@discussion	These flags are options in the DRTrackProductionInfo structure.
	@constant	kDRFlagNoMoreData				Flags used to indicate the end of variable length data.
*/
enum
{
	kDRFlagNoMoreData			= (1 << 0)
};

#pragma mark - Track Messages
/*!
	@enum	Track Messages
	@discussion	These messages are listed in the order that they will be sent. 
	@constant kDRTrackMessagePreBurn				Message sent to the callback proc indicating a burn is about to begin.
													Clients should open up any files needed to produce data and get ready to 
													start sending data.
													
													ioParam is a CFDictionaryRef containing information about the burn.
													It currently holds a kDRBurnKey and a kDRDeviceMediaInfoKey, but may
													be extended to hold other properties in the future.

	@constant kDRTrackMessageProduceData			Message sent to the callback proc requesting that the client 
													produce the next chunk of data.
													
													ioParam is a pointer to a DRTrackProductionInfo structure.
													
	@constant kDRTrackMessageVerificationStarting	Message sent to the callback proc indicating that verification 
													is about to begin.
													
													ioParam is not used and is NULL.
																										
	@constant kDRTrackMessageVerifyData				Message sent to the callback proc when the client has chosen
													kDRVerificationTypeReceiveData. 
													
													ioParam is a pointer to a DRTrackProductionInfo structure describing the
    												data being passed to the callback.
    												
	@constant kDRTrackMessageVerificationDone		Message sent to the callback proc when verification is complete.
	
													ioParam is not used and is NULL.
													
	@constant kDRTrackMessagePostBurn				Message sent to the callback proc indicating a burn has completed.
										
													ioParam is not used and is NULL.
*/
enum
{
	kDRTrackMessagePreBurn				= 'pre ',
	kDRTrackMessageProduceData			= 'prod',
	kDRTrackMessageVerificationStarting	= 'vstr',
	kDRTrackMessageVerifyData			= 'vrfy',
	kDRTrackMessageVerificationDone		= 'vdon',
	kDRTrackMessagePostBurn				= 'post'
};

/*!
	@struct		DRTrackProductionInfo
	@abstract	Parmeter block used for data production.
	@field		buffer				In - The buffer to produce into. This buffer is passed into the
									callback and only the contents should be modified.
	@field		reqCount			In - The number of bytes requested by the engine.
	@field		actCount			Out - The number of bytes actually produced (between 0 and reqCount).
	@field		flags				InOut - Miscellaneous flags. Flags are passed into the callback from the 
									engine and the callback can set flags to be passed back to the 
									engine.
	@field		blockSize			In - The block size the engine is expecting. For best results, return 
									multiples of this size. 
	@field		requestedAddress	In - The byte address that the burn engine is requesting from the 
									object (0-based). This increments when you send data, as one 
									would expect. 
*/
struct DRTrackProductionInfo
{
	void *	 	buffer;	
	UInt32		reqCount;
	UInt32		actCount;
	UInt32		flags;
	UInt32		blockSize;
	UInt64		requestedAddress;
};

#ifdef __cplusplus
}
#endif

#endif /* _H_DRCoreTrack */
