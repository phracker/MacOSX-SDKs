/*
     File:       DiscRecordingContent/DRFile.h
 
     Contains:   ObjC interface to file objects used in filesystem creation.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#import <Foundation/Foundation.h>
#import <DiscRecordingContent/DRFSObject.h>
#import <AvailabilityMacros.h>

/*!
	@class		DRFile
	@abstract	Represents a file to be created on the disc.
	@discussion
				A file can be either a pointer to a real file or can be created at burn time from data passed 
				into the burn engine as requested. DRFile's can only exist inside of "virtual"
				DRFolder objects.
*/
@interface DRFile : DRFSObject
{ }

/*! 
   	@method 		fileWithPath:
   	@abstract		Creates a "real" file object
	@discussion		This type of DRFile reads in data from an 
					existing file located at path and burns that data to disc.
   	@param 			path	The path to an existing file.
    @result  		An autoreleased DRFile object.
*/
+ (DRFile*) fileWithPath:(NSString*)path;

/*! 
   	@method 		initWithPath:
   	@abstract		Initializes a "real" file object
	@discussion		This type of DRFile reads in data from an 
					existing file located at path and burns that data to disc.
   	@param 			path	The path to an existing file.
    @result  		An DRFile object.
*/
- (id) initWithPath:(NSString*)path;

@end

/*" This category on DRFile implements methods that allow the
	file to be specified using data passed in at creation time. "*/
@interface DRFile (VirtualFiles)

/*! 
   	@method 		virtualFileWithName:data:
   	@abstract		Creates a "virtual" file object
	@discussion		This type of DRFile burns the data passed in to disc, creating a
					file with the passed in name.
   	@param 			name	The name of the file on disc.
   	@param			data	The data that will become the contents of the file on the disc.
    @result  		An autoreleased DRFile object.
*/
+ (DRFile*) virtualFileWithName:(NSString*)name data:(NSData*)data;

/*! 
   	@method 		virtualFileWithName:dataProducer:
   	@abstract		Creates a "virtual" file object
	@discussion		This type of DRFile burns the data produced to the output disc, creating a
					file with the passed in name.
   	@param 			name	The name of the file on disc.
   	@param			data	The data that will become the contents of the file on the disc.
    @result  		An autoreleased DRFile object.
*/
+ (DRFile*) virtualFileWithName:(NSString*)name dataProducer:(id)producer;

/*! 
   	@method 		initWithName:data:
   	@abstract		Initializes a "virtual" file object
	@discussion		This type of DRFile burns the data passed in to the output disc, creating a
					file with the passed in name.
   	@param 			name	The name of the file on output disc.
   	@param			data	The data that will become the contents of the file on the output disc.
    @result  		A DRFile object.
*/
- (id) initWithName:(NSString*)name data:(NSData*)data;

/*! 
   	@method 		initWithName:dataProducer:
   	@abstract		Initializes a "virtual" file object
	@discussion		This type of DRFile burns the data produced to the output disc, creating a
					file with the passed in name.
   	@param 			name		The name of the file on output disc.
   	@param			producer	The object supplying the file data to the burn.
    @result  		A DRFile object.
*/
- (id) initWithName:(NSString*)name dataProducer:(id)producer;

@end

/*" This category on DRFile implements methods that allow various
	link/alias files to be created on the resulting disc which may not
	exist in the source. "*/
@interface DRFile (VirtualLinks)

/*! 
   	@method 		hardLinkPointingTo:inFilesystem:
   	@abstract		Creates a hard link to another file on the output disc.
   	@param 			original	The file to point he hard link to
   	@param			filesystem	The filesystem this link will exist on.
    @result  		An autoreleased DRFile object.
*/
+ (DRFile*) hardLinkPointingTo:(DRFile*)original inFilesystem:(NSString*)filesystem;

/*! 
   	@method 		hardLinkPointingTo:inFilesystem:
   	@abstract		Creates a symbolic link to another file on the output disc.
   	@param 			original	The file to point he hard link to
   	@param			filesystem	The filesystem this link will exist on.
    @result  		An autoreleased DRFile object.
*/
+ (DRFile*) symLinkPointingTo:(DRFSObject*)original inFilesystem:(NSString*)filesystem;

/*! 
   	@method 		finderAliasPointingTo:inFilesystem:
   	@abstract		Creates a Finder alias to another file on the output disc.
   	@param 			original	The file to point he hard link to
   	@param			filesystem	The filesystem this link will exist on.
    @result  		An autoreleased DRFile object.
*/
+ (DRFile*) finderAliasPointingTo:(DRFSObject*)original inFilesystem:(NSString*)filesystem;

/*! 
   	@method 		initWithLinkType:pointingTo:inFilesystem:
   	@abstract		Initializes a file object to point to another file on the output disc.
   	@param 			linkType	The type of link that will be created.
   	@param 			original	The file to point he hard link to
   	@param			filesystem	The filesystem this link will exist on.
    @result  		A DRFile object.
*/
- (id) initWithLinkType:(NSString*)linkType pointingTo:(DRFSObject*)original inFilesystem:(NSString*)filesystem;

@end

/*!
	@const		DRLinkTypeHardLink
	@discussion	A hard link.
*/
extern NSString* const DRLinkTypeHardLink			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRLinkTypeSymbolicLink
	@discussion	A symbolic link.
*/
extern NSString* const DRLinkTypeSymbolicLink		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DRLinkTypeFinderAlias
	@discussion	A Finder alias.
*/
extern NSString* const DRLinkTypeFinderAlias		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@typedef	DRFileFork
	@abstract	Index used for accessing the forks of a file.
	@discussion	The data fork and resource fork always have fixed indices.  Other forks
				may be allowed in the future.
*/
typedef UInt32 DRFileFork;

enum
{
	/*!	@constant	DRFileForkData
		@abstract	Typically, the data fork contains the primary information for the file and
					is the fork used for files such as JPEGs, text files, etc.
	*/
	DRFileForkData		= 0,
	
	/*!	@constant	DRFileForkResource
		@abstract	Typically, the resource fork contains secondary meta-data, which is not
					important to the primary content of the file and may safely be ignored
					when the file is sent to a filesystem or OS which does not support
					multiple forks.  See Inside Macintosh: Resources for more information on
					the format of a resource fork.
	*/
	DRFileForkResource	= 1
};

/*!
	@protocol	DRFileDataProduction
	@abstract	Informal protocol describing methods implemented by the file data producer.
	@discussion	The DRFileDataProduction informal protocol defines those methods that a file data producer 
				instance must implement. A file data producer is the object that
				resposible for providing the file data to the burn engine on request
*/
@protocol DRFileDataProduction

/*! 
   	@method 		calculateSizeOfFile:fork:estimating:
   	@abstract		Calculates the size of a file's fork.
   	@discussion		This method may be sent at any time after the file object has been instantiated. 
					Requests that the recevier calculate the file size of file fork (for instance data or resource).

					If estimate is <i>YES</i>, you are being asked for an estimate of the final 
					fork size, perhaps to provide an estimate of the track size, and do not 
					have to be exact.  Estimates should err on the high side; it's better to 
					overestimate than underestimate.
					
					An estimate call may be made at any time.

					If estimate is <i>NO</i>, you are being asked for
					the actual fork size, to be used in the burn.  This call is only
					made in the burn phase.
   	@param 			file	The file object.
   	@param 			fork	The fork of the file whose size is to be calculated.
   	@param			estimate	If the file size should be estimated or exact.
    @result  		The length of the file's fork.
*/
- (uint64_t) calculateSizeOfFile:(DRFile*)file fork:(DRFileFork)fork estimating:(BOOL)estimate;

/*! 
   	@method 		prepareFileForBurn:
   	@abstract		Prepare the file object for burning.
   	@discussion		Sent to the recevier before the burn begins. This would be an appropriate 
					method to open files, or do any other prep work needed.  The disc's entire 
					hierarchy is completely in place and can be queried if needed. 
									
					After this call, the burn's content is locked down, and you should be
					able to respond to the <b>calculateSizeOfFile:fork:estimating:</b> messages with exact values.
   	@param 			file	The file object.
    @result  		<i>YES</i> if the burn should proceed.
*/
- (BOOL) prepareFileForBurn:(DRFile*)file;

/*! 
   	@method 		produceFile:fork:intoBuffer:length:atAddress:blockSize:
   	@abstract		Calculates the size of a file's fork.
   	@discussion		Sent during the burn (after the <b>prepareFileForBurn</b> message) requesting that the receiver
					produce the data fork contents. 
									
					The recevier should fill up the buffer passed in as full as possible 
					and then return control to the caller. Since while burning, keeping the drive's buffer full is 
					of utmost importance, you should not perform lengthy operations or block for data in this method.
					This method should return the number of bytes actually in the buffer or 0 to indicate that there
					was an error producing the data.
					
					You may be asked to produce twice, once during the actual burn and once during 
					verification.
   	@param 			file	The file object.
   	@param 			fork	The fork of the file to produce.
   	@param			buffer	The buffer to produce data into.
   	@param			bufferLength	The length of the buffer to produce data into
   	@param			blockSize	The size of the track blocks
	@result			The number of bytes produced.
*/
- (uint32_t) produceFile:(DRFile*)file fork:(DRFileFork)fork intoBuffer:(char*)buffer length:(uint32_t)bufferLength atAddress:(uint64_t)address blockSize:(uint32_t)blockSize;

/*! 
   	@method 		prepareFileForVerification:
   	@abstract		Prepare the file object for verification.
   	@discussion		Sent during the burn (after production, before the <b>cleanupFileAfterBurn</b> message) to 
   					indicate that verification is about to begin. Now would be a good
					time to rewind to the start of the file, reset state machines, or do whatever else 
					is needed to prepare to produce again. .
   	@param 			file	The file object.
	@result			<i>YES</i> to indicate that the verification should proceed and <i>NO</i> to indicate a failure occurred.
*/
- (BOOL) prepareFileForVerification:(DRFile*)file;

/*! 
   	@method 		cleanupFileAfterBurn:
   	@abstract		Cleanup the file once the burn is complete.
   	@discussion		Sent to the receiver after the burn completes. This would be an appropriate 
					place to close files, or do any other teardown work needed.  This message will 
					always be sent regardless of whether the burn succeeded or failed
   	@param 			file	The file object.
   	@param 			fork	The fork of the file whose size is to be calculated.
   	@param			estimate	If the file size should be estimated or exact.
*/
- (void) cleanupFileAfterBurn:(DRFile*)file;

@end

