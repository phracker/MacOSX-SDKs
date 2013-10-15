/*
     File:       DiscRecordingEngine/DRTrack.h
 
     Contains:   Base class for track handling.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*!
	@header 		DRTrack.h
	@abstract		Base class for track handling
	@discussion	
	<h3>About tracks</h3>

	A @link //apple_ref/occ/cl/DRTrack DRTrack @/link provides data to the for the burn and contains a description of the 
	track on disc (length, block type, data format, etc). 
	Data is provided for the burn in a real-time thread. It is up to the track to 
	provide this data in a timely manner, otherwise a burn underrun can occur and
	ruin a disc.
	
	<h3>Data Production</h3>

	DRTracks do not typically store or cache the data to be written to disk, instead the 
	data is streamed to the disc from some data producer as it's needed. This is 
	accomplished through an object associated with the track when the track is created 
	called the <i>track producer</i>. A track producer is a class you create that implements 
	the @link //apple_ref/occ/intf/DRTrackDataProduction DRTrackDataProduction @/link informal protocol. This protocol defines all of 
	the methods that a track object will call during a burn to obtain data.
	
	<h3>Track Properties</h3>

	A DRTrack object contains several properties which define the track for the burn.
	These properties are stored in an NSDictionary and are accessed through the @link //apple_ref/occ/instm/DRTrack/properties properties @/link
	and @link //apple_ref/occ/instm/DRTrack/setProperties: setProperties: @/link methods. 
	
	There are several properties that are required to be present and if they are not, will 
	cause the burn to fail. These are:
	
	<ul>
	<li>@link DRTrackLengthKey DRTrackLengthKey @/link	Length of the track (see the DRMSF class documentation)</li>
	<li>@link DRBlockSizeKey DRBlockSizeKey @/link	Size in bytes of each track block</li>
	<li>@link DRBlockTypeKey DRBlockTypeKey @/link	Type of each track block</li>
	<li>@link DRDataFormKey DRDataFormKey @/link		Data form of each block in the track</li>
	<li>@link DRSessionFormatKey DRSessionFormatKey @/link Session format of the track</li>
	<li>@link DRTrackModeKey DRTrackModeKey @/link	Track mode of the track</li>
	</ul>
	
	The possible values of these properties are defined in the Mt. Fuji (IFF-8090i) 
	specification for CD/DVD devices. It's up to you to understand the possble values
	and meanings of each.
	
	All other keys contained in the properties dictionary are optional and can be omitted.
*/
#import <Foundation/Foundation.h>

#import <DiscRecordingEngine/DRCoreTrack.h>
#import <DiscRecordingEngine/DRDevice.h>

#include <stdint.h>
#include <AvailabilityMacros.h>

@class DRMSF;
@class DRBurn;

/*!
	@class 		DRTrack
	@abstract	The DRTrack class represents a track on the burned disc.
	@discussion	
	<h3>About tracks</h3>

	A DRTrack provides data to the for the burn and contains a description of the 
	track on disc (length, block type, data format, etc). 
	Data is provided for the burn in a real-time thread. It is up to the track to 
	provide this data in a timely manner, otherwise a burn underrun can occur and
	ruin a disc.
	
	<h3>Data Production</h3>

	DRTracks do not typically store or cache the data to be written to disk, instead the 
	data is streamed to the disc from some data producer as it's needed. This is 
	accomplished through an object associated with the track when the track is created 
	called the <i>track producer</i>. A track producer is a class you create that implements 
	the @link DRTrackDataProduction DRTrackDataProduction @/link informal protocol. This protocol defines all of 
	the methods that a track object will call during a burn to obtain data.
	
	<h3>Track Properties</h3>

	A DRTrack object contains several properties which define the track for the burn.
	These properties are stored in an NSDictionary and are accessed through the @link //apple_ref/occ/instm/DRTrack/properties properties @/link
	and @link //apple_ref/occ/instm/DRTrack/setProperties: setProperties: @/link methods. 
	
	There are several properties that are required to be present and if they are not, will 
	cause the burn to fail. These are:
	
	<ul>
	<li>@link DRTrackLengthKey DRTrackLengthKey @/link	Length of the track (see the DRMSF class documentation)</li>
	<li>@link DRBlockSizeKey DRBlockSizeKey @/link	Size in bytes of each track block</li>
	<li>@link DRBlockTypeKey DRBlockTypeKey @/link	Type of each track block</li>
	<li>@link DRDataFormKey DRDataFormKey @/link		Data form of each block in the track</li>
	<li>@link DRSessionFormatKey DRSessionFormatKey @/link Session format of the track</li>
	<li>@link DRTrackModeKey DRTrackModeKey @/link	Track mode of the track</li>
	</ul>
		
	The possible values of these properties are defined in the Mt. Fuji (IFF-8090i) 
	specification for CD/DVD devices. It's up to you to understand the possble values
	and meanings of each. 
	
	All other keys contained in the properties dictionary are optional and can be omitted.
*/
@interface DRTrack : NSObject 
{ 
@private
	void*	_ref;
}

/*!
	@method			initWithProducer:
	@abstract		Initializes a DRTrack with the producer
	@param			producer	The object to use as the data producer
	@result			A DRTrack
*/
- (id) initWithProducer:(id)producer;

/*! 
   	@method 		properties
   	@abstract		Returns the properties dictionary of the track.
    @result  		An NSDictionary containing the properties of the track.
*/
- (NSDictionary*) properties;

/*! 
   	@method 		setProperties:
   	@abstract		Sets the properties dictionary of the track
   	@param 			properties	NSDictionary of the properties to set.
*/
- (void) setProperties:(NSDictionary*)properties;

/*! 
   	@method 		testProductionSpeedForInterval:
   	@abstract		Tests the production speed for a specified interval.
   	@discussion		Runs a fake "production" cycle, repeatedly asking the receiver for data by calling
					it's producer's @link //apple_ref/occ/intfm/DRTrackDataProduction/produceDataIntoBuffer:length:atAddress:blockSize:ioFlags: produceDataIntoBuffer:length:atAddress:blockSize:ioFlags: @/link for the 
					specified time interval.
						
					Use this function to verify that the the production code can produce data fast 
					enough to satisfy the data throughput requirements of the burn. 
					
					Returns the calculated maximum speed the at which the receiver can produce data. 
					This value should be used when setting up a burn to limit the burn speed
   	@param 			interval	The length of the test in seconds.
   	@result			The maximum speed data can be produced at.
*/
- (float) testProductionSpeedForInterval:(NSTimeInterval)interval;

/*! 
   	@method 		testProductionSpeedForLength:
   	@abstract		Tests the production speed for a specified byte count.
   	@discussion		Runs a fake "production" cycle, repeatedly asking the receiver for data by calling
					it's producer's @link //apple_ref/occ/intfm/DRTrackDataProduction/produceDataIntoBuffer:length:atAddress:blockSize:ioFlags: produceDataIntoBuffer:length:atAddress:blockSize:ioFlags: @/link until 
					the specified length number of bytes have been produced.
						
					Use this function to verify that the the production code can produce data fast 
					enough to satisfy the data throughput requirements of the burn. 
					
					Returns the calculated maximum speed the at which the receiver can produce data. 
					This value should be used when setting up a burn to limit the burn speed
   	@param 			length	The length of the test in bytes.
   	@result			The maximum speed data can be produced at.
*/
- (float) testProductionSpeedForLength:(uint32_t)length;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
/*!
	@method		estimateLength
	@abstract	Asks the track producer for a size estimate.
	@discussion	This method calls the track producer to ask it to estimate the size
				needed for its data.
				
				For some types of track, this call may be very expensive. For example,
				a DRFilesystemTrack may need to iterate folders on disk to provide an
				accurate estimate, which (if a large number of files and folders are
				involved) can cause this call to take 30 seconds or more. Since your
				main thread should not be allowed to block for this long, you may wish
				to call this function on a separate thread.
	@result		The estimated length of the track.
*/
- (uint64_t) estimateLength;
#endif

@end

/* ------------------------------------ */
/* Property convenience methods */

/*! 
	@category		DRTrack (PropertyConvenience)
   	@discussion		This category on DRTrack defines methods that make setting and retrieving
   					the various DRTrack properties easier.
*/
@interface DRTrack (PropertyConvenience)

/*! 
   	@method 		length
   	@abstract		Returns the length of the track data.
   	@discussion		The length returned does not include the length of the pregap. Only the length
   					of the track data itself is returned. This is a simple wrapper to obtain the 
   					@link DRTrackLengthKey DRTrackLengthKey @/link. If the @link DRTrackLengthKey DRTrackLengthKey @/link property has not been set for the track
   					this method will return a zero-length @link //apple_ref/occ/cl/DRMSF DRMSF @/link object (0m:0s:0f).
	@result			A DRMSF representing the length of the track.
*/
- (DRMSF*) length;

/*! 
   	@method 		preGap
   	@abstract		Returns the length of the pre gap.
    @discussion		This is a simple wrapper to obtain the @link DRPreGapLengthKey DRPreGapLengthKey @/link. If the @link DRPreGapLengthKey DRPreGapLengthKey @/link 
    				property has not been set for the track this method will return a zero-length @link //apple_ref/occ/cl/DRMSF DRMSF @/link 
    				object (0m:0s:0f).
  	@result			A DRMSF representing the length of the pre gap.
*/
- (DRMSF*) preGap;

/*! 
   	@method 		setPreGap:
   	@abstract		Sets the length of the pre gap.
    @discussion		This is a simple wrapper to set the @link DRPreGapLengthKey DRPreGapLengthKey @/link.
	@param			preGap	the pre gap length.
*/
- (void) setPreGap:(DRMSF*)preGap;

@end


/* ------------------------------------ */
/*!
	@protocol 	DRTrackDataProduction
	@abstract	Informal protocol describing methods implemented by a track data producer.
	@discussion	
	The DRTrackDataProduction informal protocol defines those methods that a track data producer 
	instance can implement. A track data producer is the object that is
	resposible for providing the track data to the burn engine on request. 
	
	In concept a track data producer similar to an NSTable data source in Cocoa. 
	Each producer method receives a pointer to the track it should produce data for. 
	There is one method that <b>must</b> be implemented -
	@link //apple_ref/occ/intfm/DRTrackDataProduction/produceDataForTrack:intoBuffer:length:atAddress:blockSize:ioFlags: produceDataForTrack:intoBuffer:length:atAddress:blockSize:ioFlags: @/link.
	
	The methods of this protocol will be called in roughly this order:
	
	<ol type="1">
	<li>@link //apple_ref/occ/intfm/DRTrackDataProduction/prepareTrackForBurn: prepareTrackForBurn: @/link</li>
	<li>@link //apple_ref/occ/intfm/DRTrackDataProduction/producePreGapForTrack:intoBuffer:length:atAddress:blockSize:ioFlags: producePreGapForTrack:intoBuffer:length:atAddress:blockSize:ioFlags: @/link</li>
	<li>@link //apple_ref/occ/intfm/DRTrackDataProduction/produceDataForTrack:intoBuffer:length:atAddress:blockSize:ioFlags: produceDataForTrack:intoBuffer:length:atAddress:blockSize:ioFlags: @/link</li>
	<li>@link //apple_ref/occ/intfm/DRTrackDataProduction/prepareTrackForVerification: prepareTrackForVerification: @/link</li>
	<li>@link //apple_ref/occ/intfm/DRTrackDataProduction/verifyDataForTrack:inBuffer:length:atAddress:blockSize:ioFlags: verifyDataForTrack:inBuffer:length:atAddress:blockSize:ioFlags: @/link</li>
	<li>@link //apple_ref/occ/intfm/DRTrackDataProduction/cleanupTrackAfterVerification: cleanupTrackAfterVerification: @/link</li>
	<li>@link //apple_ref/occ/intfm/DRTrackDataProduction/cleanupTrackAfterBurn: cleanupTrackAfterBurn: @/link</li>
	</ol>
	
	If verification of the disc is not requested, or a track omits or defines 
	@link DRVerificationTypeKey DRVerificationTypeKey @/link to be @link DRVerificationTypeNone DRVerificationTypeNone @/link, then 
	@link //apple_ref/occ/intfm/DRTrackDataProduction/prepareTrackForVerification: prepareTrackForVerification: @/link, 
	@link //apple_ref/occ/intfm/DRTrackDataProduction/verifyDataForTrack:inBuffer:length:atAddress:blockSize:ioFlags: verifyDataForTrack:inBuffer:length:atAddress:blockSize:ioFlags: @/link and
	@link //apple_ref/occ/intfm/DRTrackDataProduction/cleanupTrackAfterVerification: cleanupTrackAfterVerification: @/link
	will not be called.
	
	During a burn, @link //apple_ref/occ/intfm/DRTrackDataProduction/produceDataForTrack:intoBuffer:length:atAddress:blockSize:ioFlags: produceDataForTrack:intoBuffer:length:atAddress:blockSize:ioFlags: @/link is called
	very frequently in a real-time thread. Because of this, it is of utmost importance that
	this method very effficient and does not perform any long task, since by doing so, the
	burn may fail because data is not available to write to the disc.
*/
@protocol DRTrackDataProduction

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
/*!
	@method			estimateLengthOfTrack:
	@abstract		Estimates the size of the track to be burned.
	@discussion		This message is sent outside of a burn cycle in response to a -estimateLength message 
					sent to the track.
					
					
	@param			track	The track object for which to estimate the size
	@result			The number of blocks of data that the track will occupy. The estimate should be 
					reasonably accurate, and no smaller than the actual size that will be needed.
*/
- (uint64_t) estimateLengthOfTrack:(DRTrack*)track;
#endif

/*!
	@method			prepareTrack:forBurn:toMedia:
	@abstract		Prepares the track for burning.
	@discussion		Called before any burning starts. Do any sort of setup that needs to be performed
					(such as opening files). This method can calculate and update the exact track length
					that will be burned.
					
					Since this method is called before the laser is turned on, this method can perform 
					time consuming tasks. 
	@param			track	The track object being burned
	@param			burn	The burn object controlling the burn
	@param			mediaInfo	The media being burned to. This is the same dictionary as returned by @link //apple_ref/occ/instm/DRDevice/status -[DRDevice status] @/link.
	@result			<i>YES</i> to indicate that the burn should proceed and <i>NO</i> to indicate a failure occurred.
*/
- (BOOL) prepareTrack:(DRTrack*)track forBurn:(DRBurn*)burn toMedia:(NSDictionary*)mediaInfo;

/*!
	@method			cleanupTrackAfterBurn:
	@abstract		Cleans up the track after the burn completes.
	@discussion		Called after burning is complete. Typically you'll clean up what was setup in <b>prepareTrackForBurn</b>. 
					Since this method is called after the laser is turned off and the burn is finished, 
					this method can perform time consuming tasks. 
	@param			track	The track object being burned
	@result			<i>YES</i> to indicate that the burn should proceed and <i>NO</i> to indicate a failure occurred.
*/
- (void) cleanupTrackAfterBurn:(DRTrack*)track;

/*!
	@method			producePreGapForTrack:intoBuffer:length:atAddress:blockSize:ioFlags:
	@abstract		Produces the pregap data.
	@discussion		This method is called to obtain data for the track's pregap. If the @link DRPreGapLengthKey DRPreGapLengthKey @/link 
					key is present in the track properties, the track producer will be asked for the pregap 
					data first. If the producer implements this selector, then it's the responsibility
					of the producer to provide data for the pregap, otherwise that length of 
					silence will be produced by DiscRecording.
					
					The buffer passed in will be a multiple of blockSize (bufferLength == blockSize * N, where N > 1) 
					and should be filled as full as possible with data. address is the sector address on the disc from
					the start of the track that is the buffer will be written to.
					
					Since while burning, keeping the drive's buffer full is 
					of utmost importance, you should not perform lengthy operations or block for data in this method.
					This method should return the number of bytes actually in the buffer or 0 to indicate that there
					was an error producing the data.. 
	@param			track	The track object being burned
	@param			buffer	The buffer to place data into
	@param			bufferLength	The length of buffer
	@param			address	The on-disc address of where data will be written
	@param			blockSize	the size of each block on the disc. It's best to return a multiple of this size.
	@param			flags	flags
	@result			The number of bytes produced.
*/
- (uint32_t) producePreGapForTrack:(DRTrack*)track intoBuffer:(char*)buffer length:(uint32_t)bufferLength atAddress:(uint64_t)address blockSize:(uint32_t)blockSize ioFlags:(uint32_t*)flags;

/*!
	@method			produceDataForTrack:intoBuffer:length:atAddress:blockSize:ioFlags:
	@abstract		Produces the track data.
	@discussion		This method is called many times over the course of a burn to obtain data for the track. 
					The buffer passed in will be a multiple of blockSize (bufferLength == blockSize * N, where N > 1) 
					and should be filled as full as possible with data. address is the sector address on the disc from
					the start of the track that is the buffer will be written to.
					
					Since while burning, keeping the drive's buffer full is 
					of utmost importance, you should not perform lengthy operations or block for data in this method.
					This method should return the number of bytes actually in the buffer or 0 to indicate that there
					was an error producing the data.. 
	@param			track	The track object being burned
	@param			buffer	The buffer to place data into
	@param			bufferLength	The length of buffer
	@param			address	The on-disc address of where data will be written
	@param			blockSize	the size of each block on the disc. It's best to return a multiple of this size.
	@param			flags	flags
	@result			The number of bytes produced.
*/
- (uint32_t) produceDataForTrack:(DRTrack*)track intoBuffer:(char*)buffer length:(uint32_t)bufferLength atAddress:(uint64_t)address blockSize:(uint32_t)blockSize ioFlags:(uint32_t*)flags;

/*!
	@method			prepareTrackForVerification:
	@abstract		Prepare the track to be verified.
	@discussion		This method is called after the burn complets writing data to disc and before verification
					phase starts. Now would be a good time to prepare to produce data again by rewinding to the start
					of files, etc. 
	@param			track	The track object being burned
	@result			<i>YES</i> to indicate that the verification should proceed and <i>NO</i> to indicate a failure occurred.
*/
- (BOOL) prepareTrackForVerification:(DRTrack*)track;

/*!
	@method			verifyPreGapForTrack:inBuffer:length:atAddress:blockSize:ioFlags:
	@abstract		Checks the integrity track pregap after a burn.
	@discussion		If the class implementing this method asks for a verification type of @link DRVerificationTypeReceiveData DRVerificationTypeReceiveData @/link, 
					then a series of calls to this method will start. It's up to the class to reproduce the pregap
					again and compare it to the data passed in buffer. The buffer passed in will be a multiple of blockSize 
					(bufferLength == blockSize * N, where N > 1). address is the sector address on the disc from
					the start of the track that is the buffer was written to.
	@param			track	The track object being burned
	@param			buffer	The data read in from the track to compare with
	@param			bufferLength	The length of buffer
	@param			address	The on-disc address of where data will was read from.
	@param			blockSize	the size of each block on the disc. It's best to return a multiple of this size.
	@param			flags	flags
	@result			<i>YES</i> to indicate that the data compared successfully and <i>NO</i> to indicate a failure occurred.
*/
- (BOOL) verifyPreGapForTrack:(DRTrack*)track inBuffer:(const char*)buffer length:(uint32_t)bufferLength atAddress:(uint64_t)address blockSize:(uint32_t)blockSize ioFlags:(uint32_t*)flags;

/*!
	@method			verifyDataForTrack:inBuffer:length:atAddress:blockSize:ioFlags:
	@abstract		Cleans up the track after the burn completes.
	@discussion		If the class implementing this method asks for a verification type of @link DRVerificationTypeReceiveData DRVerificationTypeReceiveData @/link, 
					then a series of calls to this method will start. It's up to the class to reproduce the data
					again and compare it to the data passed in buffer. The buffer passed in will be a multiple of blockSize 
					(bufferLength == blockSize * N, where N > 1). address is the sector address on the disc from
					the start of the track that is the buffer was written to.
	@param			track	The track object being burned
	@param			buffer	The data read in from the track to compare with
	@param			bufferLength	The length of buffer
	@param			address	The on-disc address of where data will was read from.
	@param			blockSize	the size of each block on the disc. It's best to return a multiple of this size.
	@param			flags	flags
	@result			<i>YES</i> to indicate that the data compared successfully and <i>NO</i> to indicate a failure occurred.
*/
- (BOOL) verifyDataForTrack:(DRTrack*)track inBuffer:(const char*)buffer length:(uint32_t)bufferLength atAddress:(uint64_t)address blockSize:(uint32_t)blockSize ioFlags:(uint32_t*)flags;

/*!
	@method			cleanupTrackAfterVerification:
	@abstract		Cleans up the track after the verification completes.
	@discussion		Once the verification phase is complete, this method is called. The class implementing
					the method has a chance to do anything up to and including failing the verification. 
	@param			track	The track object being burned
	@result			Return <i>YES</i> to indicate success, <i>NO</i> to indicate failure.
*/
- (BOOL) cleanupTrackAfterVerification:(DRTrack*)track;

@end


/* ------------------------------------ */
/*	The following track properties are required, and must be set on every track. 
	Note that the preconfigured tracks have these properties set already. */
#if 0
#pragma mark Required Track Properties
#endif

/*!
	@const		DRTrackLengthKey
	@discussion	@link //apple_ref/occ/cl/DRMSF DRMSF @/link representing the length of the track
*/
extern NSString* const DRTrackLengthKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRBlockSizeKey
	@discussion	NSNumber containing the size in bytes of each track block. 
				See the Mt. Fuji (INF-8090i) specification for CD/DVD devices for possible
				values for this property.
*/
extern NSString* const DRBlockSizeKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRBlockTypeKey
	@discussion	NSNumber containing the type of each track block.
				See the Mt. Fuji (INF-8090i) specification for CD/DVD devices for possible
				values for this property.
*/
extern NSString* const DRBlockTypeKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRDataFormKey
	@discussion	NSNumber containing the data form of each block in the track.
				See the Mt. Fuji (INF-8090i) specification for CD/DVD devices for possible
				values for this property.
*/
extern NSString* const DRDataFormKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRSessionFormatKey
	@discussion	NSNumber containing the session format of the track.
				See the Mt. Fuji (INF-8090i) specification for CD/DVD devices for possible
				values for this property.
*/
extern NSString* const DRSessionFormatKey	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRTrackModeKey
	@discussion	NSNumber containing the track mode of the track.
				See the Mt. Fuji (INF-8090i) specification for CD/DVD devices for possible
				values for this property.
*/
extern NSString* const DRTrackModeKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* ------------------------------------ */
/*	The following track properties are optional, and are not required.  The burn engine
	will generally assume reasonable defaults, but if you need more specific control
	over particular properties you can use these keys. */
#if 0
#pragma mark Optional Track Properties
#endif
/*!
	@const		DRVerificationTypeKey
	@discussion	NSString indicating the type of verification to be performed. If this is not
				present, the track will not be verified.
*/
extern NSString* const DRVerificationTypeKey	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRMaxBurnSpeedKey
	@discussion	NSNumber containing the maximum burn speed at which data can be produced. 
				The speed is represented in KB/s (1 KB = 1000 bytes).  This key can only
				be used to limit the speed at which the burn runs.
*/
extern NSString* const DRMaxBurnSpeedKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRPreGapLengthKey
	@discussion	For CD tracks only.  NSNumber containing the length of silence or data at the
				beginning of the track.  This defaults to 2 seconds of silence. If this 
				key is present, the track producer will be asked for the pregap data first.
				If the producer implements the proper selector, then it's the responsibility
				of the producer to provide data for the pregap, otherwise that length of 
				silence will be produced by Disc Recording.
*/
extern NSString* const DRPreGapLengthKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRPreGapIsRequiredKey
	@discussion	For CD tracks only. NSNumber indicating whether the pregap listed for the 
				track is required.  If this key is not present, the track will behave as 
				though the key were <i>NO</i>.
				
				If this key's value is set to <i>YES</i> and the device does
				not support the exact pregap length, the burn
				will fail with a return value of @link //apple_ref/c/econst/kDRDevicePregapLengthNotAvailableErr kDRDevicePregapLengthNotAvailableErr @/link.
				
				If this key's value is set to <i>YES</i> and the device does
				not support any of the suggested pregap length, the engine
				will choose an alternate pregap length. 
*/
extern const CFStringRef kDRPreGapIsRequiredKey					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		DRDVDTimestampKey
	@discussion	For DVD tracks only.  NSData containing the DVD timestamp structure sent
				through the SEND DVD STRUCTURE command.  The contents of this will be
				sent directly to the drive.
*/
extern NSString* const DRDVDTimestampKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRDVDCopyrightInfoKey
	@discussion	For DVD tracks only.  NSData containing the DVD copyright info structure
				sent through the SEND DVD STRUCTURE command.  The contents of this will
				be sent directly to the drive.
*/
extern NSString* const DRDVDCopyrightInfoKey	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRTrackISRCKey
	@discussion	For CD-DA audio tracks only.  This key points to an NSData containing
				exactly 12 bytes, which will be written to the disc as the International
				Standard Recording Code (ISRC).  If this key is not present, no ISRC
				is written.
				
				The use of this value should conform to the specifications of the IFPI. See
				<a href="http://www.ifpi.org/isrc/">http://www.ifpi.org/isrc/</a> for more details on the ISRC standard.
				
				Not all drives are capable of the write modes necessary to write the ISRC.
				If this key is present in any track and the drive cannot write the ISRC, the
				burn will fail with @link //apple_ref/c/econst/kDRDeviceCantWriteISRCErr kDRDeviceCantWriteISRCErr @/link.
*/
extern NSString* const DRTrackISRCKey			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		DRIndexPointsKey
	@discussion	For CD tracks only. This key points to an NSArray of NSNumbers, indicating
				the index points inside the track.  Each index point is specified as a number
				of blocks (frames) relative to the start of the track.  There are 75 blocks
				in one second of CD audio.  No more than 98 index points may be specified
				for a track.
				
				Not all drives are capable of writing index points, and not all consumer
				CD players report or use them.  If this key is present in any track and the
				drive cannot write index points, the burn will fail with
				@link //apple_ref/c/econst/kDRDeviceCantWriteIndexPointsErr kDRDeviceCantWriteIndexPointsErr @/link.
*/
extern NSString* const DRIndexPointsKey			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		DRAudioPreEmphasisKey
	@discussion	For CD-DA audio tracks only. This key points to a BOOL value indicating
				whether the track includes pre-emphasis of 50/15us.  If this key is not
				present, the engine will use a default value of NO.  On the media, this
				key corresponds to bit 0 of the control field in sub-channel Q.
*/
extern NSString* const DRAudioPreEmphasisKey	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		DRAudioFourChannelKey
	@discussion	For CD-DA audio tracks only. This key points to a BOOL value indicating
				whether the track data has four channels, as opposed to the
				two channels of normal stereo.  If this key is not present, the engine
				will use a default value of NO and standard two-channel stereo
				is assumed.
				
				Note that while four-channel is technically allowed in the Red Book,
				it never caught on and is probably being replaced by SACD, so
				you probably shouldn't attempt to use it.
				
				On the media, this key corresponds to bit 3 of the control field in
				sub-channel Q.
*/
extern NSString* const DRAudioFourChannelKey	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		DRSerialCopyManagementStateKey
	@discussion	For CD tracks only.  This key points to an NSString value indicating the
				SCMS state of the track.  If this key is not present, no SCMS data is
				written.
				
				Not all drives are capable of writing SCMS.  If this key is present in
				any track and the drive cannot write SCMS, the burn will fail with
				@link //apple_ref/c/econst/kDRDeviceCantWriteSCMSErr kDRDeviceCantWriteSCMSErr @/link.
*/
extern NSString* const DRSerialCopyManagementStateKey	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* ------------------------------------ */
/* Verification types */
/*!
	@const		DRVerificationTypeProduceAgain
	@discussion	One of the possible values of the @link DRVerificationTypeKey DRVerificationTypeKey @/link.
				The engine will simply begin another production cycle and start calling 
				<@link //apple_ref/occ/intfm/DRTrackDataProduction/produceDataForTrack:intoBuffer:length:atAddress:blockSize:ioFlags: produceDataForTrack:intoBuffer:length:atAddress:blockSize:ioFlags: @/link again.
*/
extern NSString* const DRVerificationTypeProduceAgain	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRVerificationTypeReceiveData
	@discussion	One of the possible values of the @link DRVerificationTypeKey DRVerificationTypeKey @/link.
				The engine will begin reading data from the disc and calling
				@link //apple_ref/occ/intfm/DRTrackDataProduction/verifyDataForTrack:inBuffer:length:atAddress:blockSize:ioFlags: verifyDataForTrack:inBuffer:length:atAddress:blockSize:ioFlags: @/link.
*/
extern NSString* const DRVerificationTypeReceiveData	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRVerificationTypeChecksum
	@discussion	One of the possible values of the @link DRVerificationTypeKey DRVerificationTypeKey @/link.
				The engine will verify the track data with an internally calculated checksum.
*/
extern NSString * const DRVerificationTypeChecksum		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		DRVerificationTypeNone
	@discussion	One of the possible values of the @link DRVerificationTypeKey DRVerificationTypeKey @/link.
				No verification is desired, so verification will be skipped.
*/
extern NSString* const DRVerificationTypeNone			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* ------------------------------------ */
/* SCMS states */
/*!
	@const		DRSCMSCopyrightFree
	@discussion	One possible value for the @link DRSerialCopyManagementStateKey DRSerialCopyManagementStateKey @/link.  Indicates that
				the track has no copying restrictions.  Copies of this track should also be
				copyright free.
*/
extern NSString* const DRSCMSCopyrightFree					AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		DRSCMSCopyrightProtectedOriginal
	@discussion	One possible value for the @link DRSerialCopyManagementStateKey DRSerialCopyManagementStateKey @/link.  Indicates that
				the track is an original subject to copyright protection.  Digital copying of
				this track should be allowed, but copies should be marked with SCMS.
*/
extern NSString* const DRSCMSCopyrightProtectedOriginal		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		DRSCMSCopyrightProtectedCopy
	@discussion	One possible value for the @link DRSerialCopyManagementStateKey DRSerialCopyManagementStateKey @/link.  Indicates that
				the track is a first-generation copy of an original that was subject to copy
				protection.  No further digital copying should be allowed.
*/
extern NSString* const DRSCMSCopyrightProtectedCopy			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/* ------------------------------------ */
/*	The following track properties are read-only, and are only valid on DRTrackRefs
	that have been created by the burn engine to represent the existing tracks on a disc. */
#if 0
#pragma mark Read-Only Track Properties
#endif
/*!
	@const		DRNextWritableAddressKey
	@discussion	NSNumber containing the LBA of the next writable address
				in the track. This key is not present in closed tracks.
*/
extern NSString* const DRNextWritableAddressKey			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		DRTrackStartAddressKey
	@discussion	NSNumber containing the LBA of the start address for the
				track.
*/
extern NSString* const DRTrackStartAddressKey			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		DRFreeBlocksKey
	@discussion	NSNumber containing the length, in blocks, which is
				still available in a writable track.
*/
extern NSString* const DRFreeBlocksKey					AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		DRTrackNumberKey
	@discussion	NSNumber containing the physical track number of a track.
*/
extern NSString* const DRTrackNumberKey					AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		DRSessionNumberKey
	@discussion	NSNumber containing the physical session number of a track.
*/
extern NSString* const DRSessionNumberKey				AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		DRTrackTypeKey
	@discussion	NSString indicating the type of track. Possible values are: 
				@link DRTrackTypeInvisible DRTrackTypeInvisible @/link, @link DRTrackTypeIncomplete DRTrackTypeIncomplete @/link, 
				@link DRTrackTypeReserved DRTrackTypeReserved @/link or @link DRTrackTypeClosed DRTrackTypeClosed @/link.
*/
extern NSString* const DRTrackTypeKey					AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		DRTrackIsEmptyKey
	@discussion	NSNumber containing a BOOL value and indicates whether the track is empty.
*/
extern NSString* const DRTrackIsEmptyKey					AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		DRTrackPacketTypeKey
	@discussion	NSString indicating the kind of packets being written.
*/
extern NSString* const DRTrackPacketTypeKey				AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		DRTrackPacketSizeKey
	@discussion	NSNumber containing the number of blocks per packet for
				the disc. It will only be present if the disc contains fixed packets. This key
				will contain 16 for DVD media, and typically contains either 16 or 32 for CD media.
*/
extern NSString* const DRTrackPacketSizeKey				AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* --------------------------------- */
/* Track types */
/*!
	@const		DRTrackTypeInvisible
	@discussion	If this is the value of the @link DRTrackTypeKey DRTrackTypeKey @/link then the track is invisible and
				available to writing. If it is packet written and not closed, DRPacketTypeKey will
				be present, along with DRTrackPacketType and DRTrackPacketSize keys.
*/
extern NSString* const DRTrackTypeInvisible				AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		DRTrackTypeIncomplete
	@discussion	If this is the value of the @link DRTrackTypeKey DRTrackTypeKey @/link then the track is not invisible or
				reserved and is available for writing.
*/
extern NSString* const DRTrackTypeIncomplete				AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		DRTrackTypeReserved
	@discussion	If this is the value of the @link DRTrackTypeKey DRTrackTypeKey @/link then the track is reserved for writing.
*/
extern NSString* const DRTrackTypeReserved				AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		DRTrackTypeClosed
	@discussion	If this is the value of the @link DRTrackTypeKey DRTrackTypeKey @/link then the track has been
				written and is closed.
*/
extern NSString* const DRTrackTypeClosed					AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* --------------------------------- */
/* Packet types */
/*!
	@const		DRTrackPacketTypeFixed
	@discussion	If this is the value of the @link DRTrackPacketTypeKey DRTrackPacketTypeKey @/link then the disc is writen with
				fixed sized packets.  When this value is present the DRPacketSizeKey will also be
				present.
*/
extern NSString* const DRTrackPacketTypeFixed			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		DRTrackPacketTypeVariable
	@discussion	If this is the value of the @link DRTrackPacketTypeKey DRTrackPacketTypeKey @/link then the disc is written with
				sequential variable sized packets.  The presence of this value indicates the lack
				of the DRPacketSizeKey.
*/
extern NSString* const DRTrackPacketTypeVariable			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/* ------------------------------------ */
/* Filesystem track properties */
/* These properties are valid only on tracks created through the DataContentCreation category.
	In general the burn engine will assume reasonable defaults; only change these properties
	if you require a specific behavior. */
#if 0
#pragma mark Filesystem Track Properties
#endif

/*!
	@const		DRISOLevel
	@discussion	NSNumber containing the ISO level of the ISO-9660 filesystem on the track. Currently should be 1 or 2.
*/
extern NSString* const DRISOLevel					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
 
/*!
	@const		DRVolumeSet
	@discussion	NSString indicating the volume set name for ISO and Joliet volumes.
*/
extern NSString* const DRVolumeSet					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRPublisher
	@discussion	NSString indicating the publisher for ISO and Joliet volumes.
*/
extern NSString* const DRPublisher					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRDataPreparer
	@discussion	NSString indicating the data preparer for ISO and Joliet volumes.
*/
extern NSString* const DRDataPreparer				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRApplicationIdentifier
	@discussion	NSString indicating the application identifier for ISO, Joliet and UDF volumes.
*/
extern NSString* const DRApplicationIdentifier		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRSystemIdentifier
	@discussion	NSString indicating the system identifier for ISO and Joliet volumes.
*/
extern NSString* const DRSystemIdentifier			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRCopyrightFile
	@discussion	DRFile pointing to the copyright file for ISO and Joliet volumes. The file must be in the root directory.
*/
extern NSString* const DRCopyrightFile				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRAbstractFile
	@discussion	DRFile pointing to the abstract file for ISO and Joliet volumes. The file must be in the root directory.
*/
extern NSString* const DRAbstractFile				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRBibliographicFile
	@discussion	DRFile pointing to the bibliographic file for ISO and Joliet volumes. The file must be in the root directory.
*/
extern NSString* const DRBibliographicFile			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRBlockSize
	@discussion	NSNumber indicating the block size of the track. Currently always 2048.  Do not change.
*/
extern NSString* const DRBlockSize					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRDefaultDate
	@discussion	NSDate containing the default date to use for any unspecified dates in the filesystem. The current date and time is used if unspecified.
*/
extern NSString* const DRDefaultDate				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRVolumeCreationDate
	@discussion	NSDate containing the volume creation date. DRDefaultDate is used if unspecified.
*/
extern NSString* const DRVolumeCreationDate			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRVolumeModificationDate
	@discussion	NSDate containing the volume modification date. DRDefaultDate is used if unspecified.
*/
extern NSString* const DRVolumeModificationDate		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRVolumeCheckedDate
	@discussion		NSDate containing the volume-checked date for HFS+ volumes. DRDefaultDate is used if unspecified.
*/
extern NSString* const DRVolumeCheckedDate			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRVolumeExpirationDate
	@discussion	NSDate containing the volume expiration date for ISO and Joliet volumes.
*/
extern NSString* const DRVolumeExpirationDate		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRVolumeEffectiveDate
	@discussion	NSDate containing the date and time at which the volume is effective for ISO and Joliet volumes.
*/
extern NSString* const DRVolumeEffectiveDate		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRISOMacExtensions
	@discussion	NSBoolean indicating whether the track should have Mac extensions.
*/
extern NSString* const DRISOMacExtensions			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRISORockRidgeExtensions
	@discussion	NSBoolean indicating whether the track should have RockRidge (POSIX) extensions.
*/
extern NSString* const DRISORockRidgeExtensions		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRSuppressMacSpecificFiles
	@discussion	NSBoolean indicating whether the track should suppress Mac-specific files from
				non-HFS filesystems.
*/
extern NSString* const DRSuppressMacSpecificFiles	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

