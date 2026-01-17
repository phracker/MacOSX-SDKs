/*
     File:       DiscRecording/DRTrack.h
 
     Contains:   Base class for track handling.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#import <Foundation/Foundation.h>

#import <DiscRecording/DRCoreTrack.h>
#import <DiscRecording/DRDevice.h>

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
	the DRTrackDataProduction informal protocol. This informal protocol defines all of 
	the methods that a track object will call during a burn to obtain data. See the 
	documentation for the DRTrackDataProduction informal protocol for more information.
<i>YES to indicate that the burn should proceed and </i>
	<h3>Track Properties</h3>

	A DRTrack object contains several properties which define the track for the burn.
	These properties are stored in an NSDictionary and are accessed through the <b>properties</b>
	and <b>setProperties:</b> methods. 
	
	There are several properties that are required to be present and if they are not, will 
	cause the burn to fail. These are:
	
	<ul>
	<li>DRTrackLengthKey	Length of the track (see the DRMSF class documentation)</li>
	<li>DRBlockSizeKey	Size in bytes of each track block</li>
	<li>DRBlockTypeKey	Type of each track block</li>
	<li>DRDataFormKey		Data form of each block in the track</li>
	<li>DRSessionFormatKey Session format of the track</li>
	<li>DRTrackModeKey	Track mode of the track</li>
	</ul>
	
	The possible values of these properties are defined in the Mt. Fuji (IFF-8090i) 
	specification for CD/DVD devices. It's up to you to understand the possble values
	and meanings of each. However, there are two categories on DRTrack which you may 
	find useful. The first defines a method - <b>trackWithAudioOfLength:producer:</b> - which
	creates a track configured with the required properties to burn an audio track. The
	second defines - <b>trackForRootFolder:</b> - which uses the content creation classes to
	create a fully prepared track ready to write a data track. 
	
	All other keys contained in the properties dictionary are optional and can be omitted.
"*/
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
					it's producer's <b>produceDataIntoBuffer:length:atAddress:blockSize:ioFlags:</b> for the 
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
					it's producer's <b>produceDataIntoBuffer:length:atAddress:blockSize:ioFlags:</b> until 
					the specified length number of bytes have been produced.
						
					Use this function to verify that the the production code can produce data fast 
					enough to satisfy the data throughput requirements of the burn. 
					
					Returns the calculated maximum speed the at which the receiver can produce data. 
					This value should be used when setting up a burn to limit the burn speed
   	@param 			interval	The length of the test in seconds.
   	@result			The maximum speed data can be produced at.
*/
- (float) testProductionSpeedForLength:(uint32_t)length;

@end

@interface DRTrack (PropertyConvenience)

/*! 
   	@method 		length
   	@abstract		Returns the length of the track data.
   	@discussion		The length returned does not include the length of the pregap. Only the length
   					of the track data itself is returned.
*/
- (DRMSF*) length;

/*! 
   	@method 		preGap
   	@abstract		Returns the length of the pre gap.
*/
- (DRMSF*) preGap;

/*! 
   	@method 		setPreGap:
   	@abstract		Sets the length of the pre gap.
	@param			preGap	the pre gap length.
*/
- (void) setPreGap:(DRMSF*)preGap;

@end

#if 0
#pragma mark Required Track Properties
#endif

/*!
	@const		DRTrackLengthKey
	@discussion	DRMSF representing the length of the track (see the DRMSF class documentation)
*/
extern NSString* const DRTrackLengthKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRBlockSizeKey
	@discussion	NSNumber containing the size in bytes of each track block. 
				See the Mt. Fuji (IFF-8090i) specification for CD/DVD devices.
*/
extern NSString* const DRBlockSizeKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRBlockTypeKey
	@discussion	NSNumber containing the type of each track block.
				See the Mt. Fuji (IFF-8090i) specification for CD/DVD devices.
*/
extern NSString* const DRBlockTypeKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRDataFormKey
	@discussion	NSNumber containing the data form of each block in the track.
				See the Mt. Fuji (IFF-8090i) specification for CD/DVD devices.
*/
extern NSString* const DRDataFormKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRSessionFormatKey
	@discussion	NSNumber containing the session format of the track.
				See the Mt. Fuji (IFF-8090i) specification for CD/DVD devices.
*/
extern NSString* const DRSessionFormatKey	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRTrackModeKey
	@discussion	NSNumber containing the track mode of the track.
				See the Mt. Fuji (IFF-8090i) specification for CD/DVD devices.
*/
extern NSString* const DRTrackModeKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


#if 0
#pragma mark Optional Track Properties
#endif
/*!
	@const		DRMaxBurnSpeedKey
	@discussion	NSNumber containing the maximum burn speed the data can be produced at. 
				The speed is represented in kilobits per second (176.4, 352,8, etc). 
				This key can only be used to limit the speed the burn run at.
*/
extern NSString* const DRMaxBurnSpeedKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRPreGapLengthKey
	@discussion	NSNumber containing the length of silence at the begining of the track. 
				This defaults to 2 seconds of silence.
*/
extern NSString* const DRPreGapLengthKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRDVDTimestampKey
	@discussion	NSData containing the DVD timestamp structure sent through the SEND DVD STRUCTURE command. 
				The contents of this will be sent directly to the drive.
*/
extern NSString* const DRDVDTimestampKey		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRDVDCopyrightInfoKey
	@discussion	NSData containing the DVD copyright info structure sent through the SEND DVD STRUCTURE command. 
				The contents of this will be sent directly to the drive.
*/
extern NSString* const DRDVDCopyrightInfoKey	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRVerificationTypeKey
	@discussion	NSString indicating the type of verification to be performed. If this is not present, no 
				verificaton of the resultsing disc will occur.
*/
extern NSString* const DRVerificationTypeKey	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRVerificationTypeNone
	@discussion	One of the possible values of the DRVerificationTypeKey.
				No verification is desired, so verification will be skipped.
*/
extern NSString* const DRVerificationTypeNone			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRVerificationTypeProduceAgain
	@discussion	One of the possible values of the DRVerificationTypeKey.
				The engine will simply begin another production cycle and start calling 
				<b>produceDataIntoBuffer:length:atAddress:blockSize:ioFlags:</b> again.
*/
extern NSString* const DRVerificationTypeProduceAgain	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRVerificationTypeReceiveData
	@discussion	One of the possible values of the DRVerificationTypeKey.
				The engine will begin reading data from the disc and calling
				<b>verifyDataInBuffer:length:atAddress:blockSize:ioFlags:</b>.
*/
extern NSString* const DRVerificationTypeReceiveData	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*" This category on DRTrack creates a track configured to burn audio data to disc. "*/
@interface DRTrack (AudioContent)

/*!
	@method			trackForAudioOfLength:producer:
	@abstract		Creates a DRTrack set up to write audio data to disc.
	@param			length		The length of the track that will be produced.
	@param			producer	The object to use as the data producer
	@result			An autoreleased DRTrack
*/
+ (DRTrack*) trackForAudioOfLength:(DRMSF*)length producer:(id)producer;

@end

@class DRFolder;

/*" This category on DRTrack creates a custom DRTrack instance which is set up to burn
	a DRFolder to disc. It implements only one method <b>trackForRootFolder:</b> which
	creates and returns the track to the caller. "*/
@interface DRTrack (DataContent)

/*!
	@method			trackForRootFolder:
	@abstract		Creates a DRTrack that will write a data track.
	@discussion		Additional track properties can be set controlling the various 
					filesystems to be generated.
	@param			rootFolder		The root of the volume to be created.
	@result			An autoreleased DRTrack
*/
+ (DRTrack*) trackForRootFolder:(DRFolder*)rootFolder;

@end

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
	@discussion	NSString indicating the application identifier for ISO and Joliet volumes.
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
extern NSString* const DRSuppressMacSpecificFiles	WEAK_IMPORT_ATTRIBUTE; /* 10.2.3 */


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
	<b>produceDataForTrack:intoBuffer:length:atAddress:blockSize:ioFlags:</b>. Without this
	method there's not much point in creating the track object. In fact, a track cannot
	be created without a producer that implements this method.
	
	The methods of this protocol will be called in roughly this order:
	
	<ol type="1">
	<li><b>prepareTrackForBurn:</b></li>
	<li><b>produceDataForTrack:intoBuffer:length:atAddress:blockSize:ioFlags:</b></li>
	<li><b>prepareTrackForVerification:</b></li>
	<li><b>verifyDataForTrack:inBuffer:length:atAddress:blockSize:ioFlags:</b></li>
	<li><b>cleanupTrackAfterVerification:</b></li>
	<li><b>cleanupTrackAfterBurn:</b></li>
	</ol>
	
	If verification of the disc is not requested, or a track omits or defines 
	DRVerificationTypeKey to be DRVerificationTypeNone, then 
	<b>prepareTrackForVerification:</b>, 
	<b>verifyDataForTrack:inBuffer:length:atAddress:blockSize:ioFlags:</b> and
	<b>cleanupTrackAfterVerification:</b>
	will not be called.
	
	During a burn, <b>produceDataForTrack:intoBuffer:length:atAddress:blockSize:ioFlags:</b> is called
	very frequently in a real-time thread. Because of this, it is of utmost importance that
	this method very effficient and does not perform any long task, since by doing so, the
	burn may fail because data is not available to write to the disc.
*/
@protocol DRTrackDataProduction

/*!
	@method			prepareTrack:forBurn:toMedia:
	@abstract		Prepares the track for burning.
	@discussion		Called before any burning starts. Do any sort of setup that needs to be performed
					(such as opening files). 
					
					Since this method is called before the laser is turned on, this method can perform 
					time consuming tasks. 
	@param			track	The track object being burned
	@param			burn	The burn object controlling the burn
	@param			mediaInfo	The media being burned to. This is the same dictioanry as returned by -[DRDevice status]
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
	@method			verifyDataForTrack:inBuffer:length:atAddress:blockSize:ioFlags:
	@abstract		Cleans up the track after the burn completes.
	@discussion		If the class implementing this method asks for a verification type of <i>DRVerificationTypeReceiveData</i>, 
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
