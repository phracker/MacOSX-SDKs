
/*
     File:       DiscRecordingEngine/DRCoreTrack.h
 
     Contains:   Track object interfaces for Disc Recording.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*!	@header 	
	@abstract		Track object interfaces for Disc Recording.

	@discussion		
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
#include <DiscRecordingEngine/DRCoreDevice.h>
#endif

#ifndef _H_DRCoreObject
#include <DiscRecordingEngine/DRCoreObject.h>
#endif

#ifndef __AVAILABILITYMACROS__
#include <AvailabilityMacros.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*!
	@typedef DRTrackRef
	A reference to a DRTrack object.
*/
typedef struct __DRTrack*	DRTrackRef;

/*!
	@function	DRTrackGetTypeID
	@abstract	Returns the Core Foundation type identifier of all DRTrack instances.
*/
extern
CFTypeID DRTrackGetTypeID()
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@typedef	DRTrackMessage
	@abstract	Messages sent to the @link DRTrackCallbackProc DRTrackCallbackProc @/link callback.
*/
typedef UInt32	DRTrackMessage;

/*!
    @typedef 	DRTrackCallbackProc
    @abstract	Callback defined in the client to produce track data for recording.
	@discussion	If your callback does not support a given function, it should return
				a value of @link //apple_ref/c/econst/kDRFunctionNotSupportedErr kDRFunctionNotSupportedErr @/link. 
    @param 		track		The track with this callback is associated.
    @param		message		Indicates the type of data requested as one of the constants
    						in the Track Messages enumeration.
 	@param		ioParam		Parameters are message-specific.
    @result 	Error code.  Your client application should return a value of @link //apple_ref/c/econst/kDRFunctionNotSupportedErr kDRFunctionNotSupportedErr @/link
				when a message is received that you don't respond to, and a value of noErr when
				the message is handled successfully.  Any other error will cause
				the burn to immediately fail with the value you return as the error code.
*/
typedef OSStatus (*DRTrackCallbackProc)(
		DRTrackRef 		track,
		DRTrackMessage 	message,
		void* 			ioParam);

typedef struct DRTrackProductionInfo DRTrackProductionInfo;

/*!
	@function	DRTrackCreate
	@abstract	Creates a new track object.
	@param		properties	A CFDictionary object containing the track properties. If this
							parameter is not a valid CFDictionary object the behavior is undefined.
	@param		callback	A pointer to a @link DRTrackCallbackProc DRTrackCallbackProc @/link callback. If this callback is NULL
							the behavior is undefined.
	@result		A reference to the new DRTrack object.
*/
extern
DRTrackRef DRTrackCreate(CFDictionaryRef properties, DRTrackCallbackProc callback)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRTrackSetProperties
	@abstract	Sets the properties of the track.
	@param		track		The track whose properties will be set. If this parameter 
							is not a valid DRTrack object, the behavior is undefined. 
	@param		properties	A CFDictionary object containing the track properties. If this
							parameter is not a valid CFDictionary object the behavior is undefined.
*/
extern
void DRTrackSetProperties(DRTrackRef track, CFDictionaryRef properties)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRTrackGetProperties
	@abstract	Returns the properties of the track.
	@param		track		The track whose properties will be retrieved. If this parameter 
							is not a valid DRTrack object, the behavior is undefined. 
	@result		A CFMutableDictionary object containing the track properties.
*/
extern
CFDictionaryRef DRTrackGetProperties(DRTrackRef track)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRTrackSpeedTest
	@abstract	Tests the speed at which data can be produced.
	@discussion	Runs a test track-production cycle, calling the produceData callback for the specified 
				number of milliseconds or until the specified number of bytes have been 
				produced, whichever comes first.
				
				Use this function to verify that the produceData callback can produce data fast 
				enough to satisfy the data throughput requirements of the burn.
				
				This function will automatically set a value for the @link kDRMaxBurnSpeedKey kDRMaxBurnSpeedKey @/link key in the track's
				properties dictionary, with a value equal to the return result.
	@param		track			The track to test. 
	@param		howManyMilliseconds	The maximum duration for the test production cycle. The 
								test may not run for the full requested duration if the byte limit
								is reached first. If this parameter is 0, the result is
								undefined.
	@param		howManyBytes	The maximum number of bytes of data the client should produce before
								completing the test. The test may not produce the requested number of bytes 
								if the time limit is reached first. If this parameter is 0, the result 
								is undefined. 
	@result		The maximum throughput obtained during the test cycle.
*/
extern
float DRTrackSpeedTest(DRTrackRef track, UInt32 howManyMilliseconds, UInt32 howManyBytes)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRTrackEstimateLength
	@abstract	Asks the track producer for a block size estimate.
	@discussion	This function calls the track producer to ask it to estimate the block size
				needed for its data.  This call is passed through to the @link DRTrackCallbackProc DRTrackCallbackProc @/link
				track production callback as @link kDRTrackMessageEstimateLength kDRTrackMessageEstimateLength @/link.
				
				For some types of tracks, this call may be very expensive.  For example,
				a file system track (@link DRFilesystemTrackRef DRFilesystemTrack @/link) may need to iterate through folders 
				on disk to provide an accurate estimate. If a large number of files and folders 
				are involved, this call may take 30 seconds or more.  Since your
				main thread should not block for this long, you may wish to call this
				function on a separate thread.
				
				The return value is the size in blocks that is specified in the
				track's properties dictionary.
				
	@param		track		The track to query.
	@result		The size of the track in blocks.
*/
extern
UInt64 DRTrackEstimateLength(DRTrackRef track)
AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* ------------------------------------ */
/*	The following track properties are required, and must be set on every track.  See the
	end of this file for definitions of common values. */
#pragma mark Required Track Properties
/*!
	@const		kDRTrackLengthKey
	@discussion	Required Key. This key corresponds to a CFNumber object containing the length of 
				the track data in blocks.
*/
extern const CFStringRef kDRTrackLengthKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRBlockSizeKey
	@discussion	Required key. This key corresponds to a CFNumber object containing the size
				of each block of the track. Common values are defined in the @link //apple_ref/c/tag/Block%32Sizes Block Sizes @/link
				enumeration.
*/
extern const CFStringRef kDRBlockSizeKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRBlockTypeKey
	@discussion	Required key. This key corresponds to a CFNumber object containing the type
				of each block of the track. Common values are defined in the @link //apple_ref/c/tag/Block%32Types Block Types @/link
				enumeration.
*/
extern const CFStringRef kDRBlockTypeKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRDataFormKey
	@discussion	Required key. This key corresponds to a CFNumber object containing the data format
				of each block of the track. Common values are defined in the @link //apple_ref/c/tag/Data%32Forms Data Forms @/link
				enumeration.
*/
extern const CFStringRef kDRDataFormKey				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRSessionFormatKey
	@discussion	Required key. This key corresponds to a CFNumber object containing the session format
				of the track. Common values are defined in the @link //apple_ref/c/tag/Session%32Mode Session Mode @/link enumeration.
*/
extern const CFStringRef kDRSessionFormatKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRTrackModeKey
	@discussion	Required key. This key corresponds to a CFNumber object containing the track mode
				of the track. Common values are defined in the @link //apple_ref/c/tag/Track%32Modes Track Modes @/link enumeration.
*/
extern const CFStringRef kDRTrackModeKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* ------------------------------------ */
/*	The following track properties are optional, and are not required.  The burn engine
	will generally assume reasonable defaults, but if you need more specific control
	over particular properties you can use these keys. */
#pragma mark Optional Track Properties

/*!
	@const		kDRVerificationTypeKey
	@discussion	Optional key. This track property key corresponds to a CFString object indicating the kind of verification
				that should be performed. If the key is not present, no verification will take 
				place.
*/
extern const CFStringRef kDRVerificationTypeKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRDVDCopyrightInfoKey
	@discussion	Optional key. This track property key corresponds to a CFData object containing Multi-Media Command 
				(MMC) copyright data. This data will be sent directly to the drive. If this key is 
				not present, no copyright information will be sent.
*/
extern const CFStringRef kDRDVDCopyrightInfoKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
													
/*!
	@const		kDRDVDTimestampKey
	@discussion	Optional key. This track property key corresponds to a CFData object containing Multi-Media Command 
				(MMC) timestamp data. This data will be sent directly to the drive. If this key 
				is not present, no timestamp will be sent.
*/
extern const CFStringRef kDRDVDTimestampKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
													
/*!
	@const		kDRBufferZone1DataKey
	@discussion	Optional key. This track property key corresponds to a CFData object containing the data to
				write to Buffer Zone 1 on drives which support it, such as the Pioneer DVR-S201.
				This data will be sent directly to the drive. If this key is not present, no 
				Buffer Zone 1 data will be sent.
*/
extern const CFStringRef kDRBufferZone1DataKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
													
/*!
	@const		kDRMaxBurnSpeedKey
	@discussion	Optional key. This track property key corresponds to a CFNumber object containing  
				the maximum sustained rate at which your application will request data from the 
				track callback, in units of kilobytes per second where 1 kilobyte = 1,000 bytes.
				
				The value for @link kDRMaxBurnSpeedKey kDRMaxBurnSpeedKey @/link must be greater than the drive's minimum burn 
				speed. It is usually safe to specify the appropriate flavor of 1x 
				(@link kDRDeviceBurnSpeedCD1x kDRDeviceBurnSpeedCD1x @/link or @link kDRDeviceBurnSpeedDVD1x kDRDeviceBurnSpeedDVD1x @/link), but some drives cannot slow  
				all the way down to 1x.
				
				Given the capabilities of the drive, the bus, and the recordable disc, the burn speed used 
				when writing a layout will generally be the highest data rate possible that is less 
				than or equal to the value of @link kDRMaxBurnSpeedKey kDRMaxBurnSpeedKey @/link for every track, as well as less
				than or equal to the value of the @link kDRBurnRequestedSpeedKey kDRBurnRequestedSpeedKey @/link key for the burn object.
				
				When this key is not present, the requested maximum sustained data rate defaults
				to a value of infinity. In this case, the Disc Recording engine assumes that your 
				track callback can produce data at any rate requested.
*/
extern const CFStringRef kDRMaxBurnSpeedKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRPreGapLengthKey
	@discussion	Optional key. This track property key corresponds to a CFNumber object containing the length in blocks of 
				empty space, or pregap, to be recorded before the track. If this key is not
				present the Disc Recording engine will assume a 2 second, or 150 block, pregap.
*/
extern const CFStringRef kDRPreGapLengthKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRPreGapIsRequiredKey
	@discussion	Optional key. This track property key corresponds to a CFBoolean object indicating whether 
				the pregap listed for the track is required.  If this key is not present, 
				the track will behave as though the key were <tt>false</tt>.
				
				If this key's value is set to <tt>true</tt> and the device does
				not support the exact pregap length, the burn
				will fail with a return value of @link //apple_ref/c/econst/kDRDevicePregapLengthNotAvailableErr @/link.
				
				If this key's value is set to <tt>false</tt> and the device does
				not support the suggested pregap length, the engine
				will choose an alternate pregap length. 
*/
extern const CFStringRef kDRPreGapIsRequiredKey					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRTrackISRCKey
	@discussion	Optional key. For CD-DA audio tracks only.  This track property key corresponds to a CFData
				object containing exactly 12 bytes, which will be written to the disc as the
				International Standard Recording Code (ISRC).  If this key is not present,
				no ISRC data is written.
				
				The use of this value should conform to the specifications of the IFPI.  See
				<a href="http://www.ifpi.org/isrc">http://www.ifpi.org/isrc</a> for details on the ISRC standard.
				
				Not all drives can write ISRC data. If this key is present in any track and 
				the drive cannot write ISRC data, the burn will fail with a return value of 
				@link //apple_ref/c/econst/kDRDeviceCantWriteISRCErr kDRDeviceCantWriteISRCErr @/link.
*/
extern const CFStringRef kDRTrackISRCKey						AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRIndexPointsKey
	@discussion	Optional key. For CD tracks only.  This track property key corresponds to a CFArray object
				containing CFNumber objects	describing index points within the track.  Each 
				index point is specified as a number of blocks, equivalent to frames, relative 
				to the start of the track.  There are 75 blocks in one second of CD audio.  No 
				more than 98 index points may be specified for a track.
				
				Not all drives can write index points, and not all consumer CD players report or 
				use them.  If this key is present in any track and the drive cannot write index 
				points, the burn will fail with a return value of @link //apple_ref/c/econst/kDRDeviceCantWriteIndexPointsErr kDRDeviceCantWriteIndexPointsErr @/link.
*/
extern const CFStringRef kDRIndexPointsKey						AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRAudioPreEmphasisKey
	@discussion	Optional key. For CD-DA audio tracks only. This track property key corresponds to a CFBoolean
				value indicating whether the track includes pre-emphasis of 50/15 microseconds.
				If this key is not present, the engine will use a default value of
				<tt>false</tt>.  On the disc, this key corresponds to bit 0 of the
				control field in sub-channel Q.
*/
extern const CFStringRef kDRAudioPreEmphasisKey					AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRAudioFourChannelKey
	@discussion	Optional key. For CD-DA audio tracks only. This track property key corresponds to a CFBoolean
				value indicating whether the track data has four channels, as opposed to the
				two channels of normal stereo.  If this key is not present, the engine
				will use a default value of <tt>false</tt> and standard two-channel stereo
				is assumed.
				
				Four-channel audio is supported in the Red Book standard but never 
				caught on. It is probably being replaced by SACD, so you probably shouldn't 
				attempt to use it.
				
				On the disc, this key corresponds to bit 3 of the control field in
				sub-channel Q.
*/
extern const CFStringRef kDRAudioFourChannelKey					AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRSerialCopyManagementStateKey
	@discussion	Optional key. For CD tracks only.  This track property key corresponds to a CFString value
				indicating the Serial Copy Management System (SCMS) state of the track.  If 
				this key is not present, no SCMS data is written.
				
				Not all drives are capable of writing SCMS data.  If this key is present in any
				track and the drive cannot write SCMS, the burn will fail with a return value
				of @link //apple_ref/c/econst/kDRDeviceCantWriteSCMSErr kDRDeviceCantWriteSCMSErr @/link.
*/
extern const CFStringRef kDRSerialCopyManagementStateKey		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* ------------------------------------ */
/* Verification types */
/*!
	@const		kDRVerificationTypeNone
	@discussion	One value for the @link kDRVerificationTypeKey kDRVerificationTypeKey @/link dictionary key. This value indicates
				the engine will not do any sort of verification on the track data.
*/
extern const CFStringRef kDRVerificationTypeNone				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRVerificationTypeProduceAgain
	@discussion	One value for the @link kDRVerificationTypeKey kDRVerificationTypeKey @/link dictionary key. This value indicates
				the engine will start another production cycle and the client 
				simply produces data again from the start.
				
				Note that this verification mode currently only works with data CDs and DVDs.
*/
extern const CFStringRef kDRVerificationTypeProduceAgain		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRVerificationTypeReceiveData
	@discussion	One value for the @link kDRVerificationTypeKey kDRVerificationTypeKey @/link dictionary key. This value indicates
				the engine will read data from the disc and send it to the client
				through a series of calls to the callback.
*/
extern const CFStringRef kDRVerificationTypeReceiveData			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRVerificationTypeChecksum
	@discussion One value for the @link kDRVerificationTypeKey kDRVerificationTypeKey @/link dictionary key. This value indicates
				the engine will verify the track data with an internally calculated checksum.
*/
extern const CFStringRef kDRVerificationTypeChecksum			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* ------------------------------------ */
/* SCMS states */
/*!
	@const		kDRSCMSCopyrightFree
	@discussion	One value for the @link kDRSerialCopyManagementStateKey kDRSerialCopyManagementStateKey @/link dictionary key. This value indicates that
				the track has no copying restrictions.  Copies of this track should also be
				copyright free.
*/
extern const CFStringRef kDRSCMSCopyrightFree					AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRSCMSCopyrightProtectedOriginal
	@discussion	One value for the @link kDRSerialCopyManagementStateKey kDRSerialCopyManagementStateKey @/link dictionary key. This value indicates that
				the track is an original subject to copyright protection.  Digital copying of
				this track should be allowed, but copies should be marked with appropriate Serial Copy 
				Management System (SCMS) data.
*/
extern const CFStringRef kDRSCMSCopyrightProtectedOriginal		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRSCMSCopyrightProtectedCopy
	@discussion	One value for the @link kDRSerialCopyManagementStateKey kDRSerialCopyManagementStateKey @/link dictionary key. This value indicates that
				the track is a first-generation copy of an original that was subject to copy
				protection.  No further digital copying should be allowed.
*/
extern const CFStringRef kDRSCMSCopyrightProtectedCopy			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* ------------------------------------ */
/*	The following track properties are read-only, and are only valid on DRTrackRefs
	that have been created by the burn engine to represent the existing tracks on a disc. */
#pragma mark Read-Only Track Properties

/*!
	@const		kDRNextWritableAddressKey
	@discussion	This key corresponds to a CFNumber object containing the Logical Block Address (LBA)
				of the next writable address in the track. This key is not present in closed tracks.
*/
extern const CFStringRef kDRNextWritableAddressKey			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRTrackStartAddressKey
	@discussion	This key corresponds to a CFNumber object containing the Logical Block Address (LBA)
				of the start address for the track.
*/
extern const CFStringRef kDRTrackStartAddressKey			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRFreeBlocksKey
	@discussion	This key corresponds to a CFNumber object containing the length, in blocks, which is
				still available in a writable track.
*/
extern const CFStringRef kDRFreeBlocksKey					AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRTrackNumberKey
	@discussion	This key corresponds to a CFNumber object containing the physical track number of a track.
*/
extern const CFStringRef kDRTrackNumberKey					AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRSessionNumberKey
	@discussion	This key corresponds to a CFNumber object containing the physical session number of a track.
*/
extern const CFStringRef kDRSessionNumberKey				AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRTrackTypeKey
	@discussion	This key corresponds to a CFString object indicating the type of track. Possible values are 
				@link kDRTrackTypeInvisible kDRTrackTypeInvisible @/link, @link kDRTrackTypeIncomplete kDRTrackTypeIncomplete @/link, 
				@link kDRTrackTypeReserved kDRTrackTypeReserved @/link , or @link kDRTrackTypeClosed kDRTrackTypeClosed @/link.
*/
extern const CFStringRef kDRTrackTypeKey					AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRTrackIsEmptyKey
	@discussion	This key corresponds to a CFBoolean object and indicates whether the track is empty.
*/
extern const CFStringRef kDRTrackIsEmptyKey					AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRTrackPacketTypeKey
	@discussion	This key corresponds to a CFString value indicating the kind of packets being written.
*/
extern const CFStringRef kDRTrackPacketTypeKey				AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRTrackPacketSizeKey
	@discussion	This key corresponds to a CFNumber object that contains the number of blocks per packet for
				the disc. It will only be present if the disc contains fixed packets. This key
				will contain '16' for DVD media, and typically contains either '16' or '32' for CD media.
*/
extern const CFStringRef kDRTrackPacketSizeKey				AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* --------------------------------- */
/* Track types */
/*!
	@const		kDRTrackTypeInvisible
	@discussion	One value for the @link kDRTrackTypeKey kDRTrackTypeKey @/link dictionary key. This value indicates the track is 
				invisible and available for writing. If it is packet written and not closed, 
				the kDRTrackPacketType key will be present along with the kDRTrackPacketSize keys.
*/
extern const CFStringRef kDRTrackTypeInvisible				AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRTrackTypeIncomplete
	@discussion	One value for the @link kDRTrackTypeKey kDRTrackTypeKey @/link dictionary key. This value indicates the track is 
				not invisible or reserved and is available for writing.
*/
extern const CFStringRef kDRTrackTypeIncomplete				AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRTrackTypeReserved
	@discussion	One value for the @link kDRTrackTypeKey kDRTrackTypeKey @/link dictionary key. This value indicates the track is 
				reserved for writing.
*/
extern const CFStringRef kDRTrackTypeReserved				AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRTrackTypeClosed
	@discussion	One value for the @link kDRTrackTypeKey kDRTrackTypeKey @/link dictionary key. This value indicates the track has been
				written and is closed.
*/
extern const CFStringRef kDRTrackTypeClosed					AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* --------------------------------- */
/* Packet types */
/*!
	@const		kDRTrackPacketTypeFixed
	@discussion	One value for the @link kDRTrackPacketTypeKey kDRTrackPacketTypeKey @/link dictionary key. This value indicates the disc is 
				writen with fixed sized packets.  When this value is present the kDRPacketSizeKey 
				dictionary key will also be present.
*/
extern const CFStringRef kDRTrackPacketTypeFixed			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRTrackPacketTypeVariable
	@discussion	One value for the @link kDRTrackPacketTypeKey kDRTrackPacketTypeKey @/link dictionary key. This value indicates the disc is 
				written with sequential, variable-sized packets.  When this key is present, the 
				kDRPacketSizeKey dictionary key will not be.
*/
extern const CFStringRef kDRTrackPacketTypeVariable			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* --------------------------------- */
/* The following keys are used in dictionaries sent as the ioParam in a callback. */
#pragma mark PreBurn Track Message Properties
/*!
	@const		kDRBurnKey
	@discussion	This key corresponds to the DRBurn object for which the PreBurn message applies.
*/
extern const CFStringRef kDRBurnKey					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/* --------------------------------- */
/* The following values are commonly used values for the track properties in a few standard types of CDs. */
#pragma mark - Block Sizes
/*!
	@enum 		Block Sizes
	@discussion	Common block sizes for different types of track data.
	@constant	kDRBlockSizeAudio			Audio data.
	@constant	kDRBlockSizeMode1Data		Mode 1 data.
	@constant	kDRBlockSizeMode2Data		Mode 2 data. Photo CD and CD-i use this.
	@constant	kDRBlockSizeMode2Form1Data	Mode 2 Form 1 data.
	@constant	kDRBlockSizeMode2Form2Data	Mode 2 Form 2 data.
	@constant	kDRBlockSizeDVDData			DVD data.
*/	
enum
{
	kDRBlockSizeAudio			= 2352,
	kDRBlockSizeMode1Data		= 2048,
	kDRBlockSizeMode2Data		= 2332,
	kDRBlockSizeMode2Form1Data	= 2048,
	kDRBlockSizeMode2Form2Data	= 2324,
	kDRBlockSizeDVDData			= 2048
};

#pragma mark - Block Types
/*!
	@enum 		Block Types
	@discussion	Common block type values for types of track data.
	@constant	kDRBlockTypeAudio			Audio data.
	@constant	kDRBlockTypeMode1Data		Mode 1 data.
	@constant	kDRBlockTypeMode2Data		Mode 2 data. Photo CD and CD-i use this.
	@constant	kDRBlockTypeMode2Form1Data	Mode 2 Form 1 data.
	@constant	kDRBlockTypeMode2Form2Data	Mode 2 Form 2 data.
	@constant	kDRBlockTypeDVDData			DVD data.
*/
enum
{
	kDRBlockTypeAudio			= 0,
	kDRBlockTypeMode1Data		= 8,
	kDRBlockTypeMode2Data		= 13,
	kDRBlockTypeMode2Form1Data	= 10,
	kDRBlockTypeMode2Form2Data	= 12,
	kDRBlockTypeDVDData			= 8
};

#pragma mark - Data Forms
/*!
	@enum 		Data Forms
	@discussion	Common data form values for types of track data.
	@constant	kDRDataFormAudio			Audio data.
	@constant	kDRDataFormMode1Data		Mode 1 data.
	@constant	kDRDataFormMode2Data		Mode 2 data. Photo CD and CD-i use this.
	@constant	kDRDataFormMode2Form1Data	Mode 2 Form 1 data.
	@constant	kDRDataFormMode2Form2Data	Mode 2 Form 2 data.
	@constant	kDRDataFormDVDData			DVD data.
*/	
enum
{
	kDRDataFormAudio			= 0,
	kDRDataFormMode1Data		= 16,
	kDRDataFormMode2Data		= 32,
	kDRDataFormMode2Form1Data	= 32,
	kDRDataFormMode2Form2Data	= 32,
	kDRDataFormDVDData			= 16
};

#pragma mark - Track Modes
/*!
	@enum 		Track Modes
	@discussion	Common track mode values for types of track data.
	@constant	kDRTrackModeAudio			Audio data.
	@constant	kDRTrackMode1Data			Mode 1 data.
	@constant	kDRTrackMode2Data			Mode 2 data. Photo CD and CD-i use this.
	@constant	kDRTrackMode2Form1Data		Mode 2 Form 1 data.
	@constant	kDRTrackMode2Form2Data		Mode 2 Form 2 data.
	@constant	kDRTrackModeDVDData			DVD data.
*/
enum
{
	kDRTrackModeAudio		= 0,
	kDRTrackMode1Data		= 4,
	kDRTrackMode2Data		= 4,
	kDRTrackMode2Form1Data	= 4,
	kDRTrackMode2Form2Data	= 4,
	kDRTrackModeDVDData		= 5
};

#pragma mark - Session Format
/*!
	@enum 		Session Format
	@discussion	Common session format values for types of track data.
	@constant	kDRSessionFormatAudio		Audio data.
	@constant	kDRSessionFormatMode1Data	Mode 1 data.
	@constant	kDRSessionFormatCDI			CD-I disc.
	@constant	kDRSessionFormatCDXA		CD-ROM XA disc.
	@constant	kDRSessionFormatDVDData		DVD data.
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
	@constant	kDRFlagNoMoreData	Indicates the end of variable length data.
*/
enum
{
	kDRFlagNoMoreData			= (1 << 0)
};

#pragma mark - Track Messages
/*!
	@enum	Track Messages
	@discussion Messages sent to the @link DRTrackCallbackProc DRTrackCallbackProc @/link callback during a burn.
	@constant kDRTrackMessagePreBurn				Message sent to the track production callback indicating a burn is about to begin.
													Clients should open any files needed to produce data and get ready to 
													start sending data.
													
													The ioParam parameter contains a CFDictionary object with information about 
													the burn. It currently holds @link kDRBurnKey kDRBurnKey @/link and @link kDRDeviceMediaInfoKey kDRDeviceMediaInfoKey @/link dictionary keys, 
													but may be extended to hold other properties in the future.

	@constant kDRTrackMessageProduceData			Message sent to the track production callback requesting that the client 
													produce the next chunk of data for the track.
													
													The ioParam parameter is a pointer to a DRTrackProductionInfo structure.
													
	@constant kDRTrackMessageVerificationStarting	Message sent to the callback proc indicating that verification 
													is about to begin.
													
													ioParam is not used and is NULL.
																										
	@constant kDRTrackMessageVerifyData				Message sent to the track production callback when the client has chosen
													the @link kDRVerificationTypeReceiveData kDRVerificationTypeReceiveData @/link option. 
													
													The ioParam parameter is a pointer to a @link DRTrackProductionInfo DRTrackProductionInfo @/link structure describing 
    												the data passed to the callback.
    												
	@constant kDRTrackMessageVerificationDone		Message sent to the track production callback when verification is complete.
	
													The ioParam parameter is not used and is NULL.
													
	@constant kDRTrackMessagePostBurn				Message sent to the track production callback indicating a burn has completed.
										
													The ioParam parameter is not used and is NULL.

	@constant kDRTrackMessageEstimateLength			Message sent to the track production callback asking it to estimate
													the length of the track.  This message is sent outside of a burn
													cycle, when the @link DRTrackEstimateLength DRTrackEstimateLength @/link function is called.  
													
													The ioParam parameter is a pointer to a UInt64 value, which the callback fills 
													in with an estimated number of blocks for the track.  The estimate should
													be reasonably accurate and no smaller than the actual size that
													will be needed. 
	
	@constant kDRTrackMessageProducePreGap			Message sent to the track production callback requesting that the client
													produce the next chunk of the pregap.
													
													The ioParam parameter is a pointer to a @link DRTrackProductionInfo DRTrackProductionInfo @/link structure.

	@constant kDRTrackMessageVerifyPreGap			Message sent to the track production callback when the client has chosen
													the @link kDRVerificationTypeReceiveData kDRVerificationTypeReceiveData @/link option. The data produced by the client 
													for the @link kDRTrackMessageProducePreGap kDRTrackMessageProducePreGap @/link should be verified.
													
													The ioParam parameter is a pointer to a @link DRTrackProductionInfo DRTrackProductionInfo @/link structure describing 
    												the data passed to the callback.   												
*/
enum
{
	kDRTrackMessagePreBurn				= 'pre ',
	kDRTrackMessageProduceData			= 'prod',
	kDRTrackMessageVerificationStarting	= 'vstr',
	kDRTrackMessageVerifyData			= 'vrfy',
	kDRTrackMessageVerificationDone		= 'vdon',
	kDRTrackMessagePostBurn				= 'post',
	kDRTrackMessageEstimateLength		= 'esti',	/* added in 10.3 */
	kDRTrackMessageProducePreGap		= 'prpr',	/* added in 10.3 */
	kDRTrackMessageVerifyPreGap			= 'vrpr'	/* added in 10.4 */
};

/*!
	@struct		DRTrackProductionInfo
	@abstract	Parmeter block used for data production.
	@field		buffer				In - The buffer to produce into. This buffer is passed into the
									track production callback and only the contents should be modified.
	@field		reqCount			In - The number of bytes requested by the engine.
	@field		actCount			Out - The number of bytes actually produced (between 0 and reqCount).
	@field		flags				InOut - Miscellaneous flags. Flags are passed into the track production callback  
									callback from the Disc Recording engine and the callback can set flags to be 
									passed back to the engine.
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
