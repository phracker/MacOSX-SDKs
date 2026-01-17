/*
     File:       DiscRecording/DRContentFile.h
 
     Contains:   Interface to file objects used in filesystem creation.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef _H_DRContentFile
#define _H_DRContentFile

#if PRAGMA_ONCE
#pragma once
#endif

#ifndef _H_DRContentObject
#include <DiscRecording/DRContentObject.h>
#endif

#ifndef __COREFOUNDATION_CFURL__
#include <CoreFoundation/CFURL.h>
#endif

#ifndef __AVAILABILITYMACROS__
#include <AvailabilityMacros.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


/*!
	@function	DRFileGetTypeID
	@abstract	Returns the type identifier of all DRFile instances.
*/
extern
CFTypeID DRFileGetTypeID()
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;




typedef UInt32 DRLinkType;
enum {
	/*! @constant kDRLinkTypeHardLink
		@abstract	Link type for hard links. */
	kDRLinkTypeHardLink		= 1,

	/*! @constant kDRLinkTypeSymbolicLink
		@abstract	Link type for symbolic links. */
	kDRLinkTypeSymbolicLink	= 2,
	
	/*! @constant kDRLinkTypeFinderAlias
		@abstract	Link type for Finder aliases. */
	kDRLinkTypeFinderAlias	= 3
};




/*!
	@typedef	DRFileMessage
	@abstract	Messages sent to DRFileProc.
*/
typedef UInt32	DRFileMessage;

enum {
	/*!	@constant	kDRFileMessageForkSize
		@abstract	May be sent at any time after the file object has been created.
					ioParam is a (DRFileForkSizeInfo*). 
		@discussion	The fork value indicates which fork you are being asked about.
					
					When the query type is kDRFileForkSizeEstimate, you are being asked for
					an estimate of the final fork size, perhaps to provide an estimate
					of the track size, and do not have to be exact.  Estimates should
					err on the high side; it's better to overestimate than underestimate.
					This call may be made at any time.
					
					When the query type is kDRFileForkSizeActual, you are being asked for
					the actual fork size, to be used in the burn.  This call is only
					made in the burn phase.
	*/
	kDRFileMessageForkSize = 'fsiz',
	
	/*!	@constant	kDRFileMessagePreBurn
		@abstract	Sent before the burn.
					ioParam is ignored.
		@discussion	This would be an appropriate place to open files, or do any other prep
					work needed.  The disc's entire hierarchy is completely in place and
					can be queried if needed. 
					
					After this call, the burn's content is locked down, and you should be
					able to respond to the kDRFileMessageForkSize message with exact values.
	*/
	kDRFileMessagePreBurn = 'pre ',
	
	/*!	@constant	kDRFileMessageProduceData
		@abstract	Sent during the burn (after the pre-burn call).
					ioParam is a (DRFileProductionInfo*) - see the definition of
					that structure below for more info.
					
					Speed is critical during this call.  You should produce the data as fast
					as possible, and try not to perform any time-consuming tasks.
		@discussion	You may be asked to produce twice, once during the actual burn
					and once during verification. 
	*/
	kDRFileMessageProduceData = 'prod',
	
	/*!	@constant	kDRFileMessageVerificationStarting
		@abstract	Sent during the burn (after the pre-burn call, after production, before the
					post-burn call) to indicate that verification is about to begin.
					ioParam is ignored.
		@discussion	This would be an appropriate place to seek back to the beginning of
					files, reset state machines, or do whatever else is needed to prepare to
					produce again.
	*/
	kDRFileMessageVerificationStarting = 'vrfy',
	
	/*!	@constant	kDRFileMessagePostBurn
		@abstract	Sent at the end of the burn.
					ioParam is ignored.
		@discussion	This would be an appropriate place to close files, or do any other
					teardown work needed.  This call will always be made regardless of
					whether the burn succeeded or failed.
	*/
	kDRFileMessagePostBurn = 'post',
	
	/*!	@constant	kDRFileMessageRelease
		@abstract	Sent when the DRFileRef is released.
					ioParam is ignored.
		@discussion	No further messages will be sent for this object.  This would be an
					appropriate time to release any memory allocated by the object (whether
					in the refCon or anywhere else).
	*/
	kDRFileMessageRelease = 'bye '
};



/*!
	@typedef	DRFileForkIndex
	@abstract	Index used for accessing the forks of a file.
	@discussion	The data fork and resource fork always have fixed indices.  Other forks
				may be allowed in the future.
*/
typedef UInt32 DRFileForkIndex;

enum
{
	/*!	@constant	kDRFileForkData
		@abstract	Typically, the data fork contains the primary information for the file and
					is the fork used for files such as JPEGs, text files, etc.
	*/
	kDRFileForkData		= 0,
	
	/*!	@constant	kDRFileForkResource
		@abstract	Typically, the resource fork contains secondary meta-data, which is not
					important to the primary content of the file and may safely be ignored
					when the file is sent to a filesystem or OS which does not support
					multiple forks.  See Inside Macintosh: Resources for more information on
					the format of a resource fork.
	*/
	kDRFileForkResource	= 1
};


/*!
	@typedef	DRFileForkSizeQuery
	@abstract	Type used to define queries on the fork size.
*/
typedef UInt32	DRFileForkSizeQuery;

/*!
	@constant	kDRFileForkSizeActual		Indicates a request for actual size.
	@constant	kDRFileForkSizeEstimate		Indicates a request for estimated size.
*/
enum
{
	kDRFileForkSizeActual		= 0,
	kDRFileForkSizeEstimate		= 1
};

/*!
	@struct		DRFileForkSizeInfo
	@abstract	Structure used when requesting fork sizes.
	@field		fork					--> which fork is being requested
	@field		query					--> type of query, estimate or actual
	@field		size					<-- returned size
*/
struct DRFileForkSizeInfo
{
	DRFileForkIndex			fork;
	DRFileForkSizeQuery		query;
	UInt64					size;
};
typedef struct DRFileForkSizeInfo DRFileForkSizeInfo;

/*!
	@struct		DRFileProductionInfo
	@abstract	Table used during production of a file.
	@field		requestedAddress		<-- byte address that the burn engine is requesting
	@field		buffer					<-- buffer to produce into
	@field		reqCount				<-- number of bytes requested
	@field		actCount				--> number of bytes you actually produced
	@field		blockSize				<-- current block size, you must always return multiples of this
	@field		fork					<-- which fork is being requested
*/
struct DRFileProductionInfo
{
	UInt64					requestedAddress;
	void *					buffer;
	UInt32					reqCount;
	UInt32					actCount;
	UInt32					blockSize;
	DRFileForkIndex			fork;
};
typedef struct DRFileProductionInfo DRFileProductionInfo;

/*!
	@typedef	DRFileProc
	@abstract	Callback function in the client to produce a file for recording.
	@discussion	The messages and parameters are defined as enums starting with
				kDRFileMessage. 
				
				If your callback does not support a given function, it should return
				kDRFunctionNotSupportedErr. 
	@param		refCon					Reference parameter for your use, established when
										 the callback is registered.
	@param		file					The file object being produced.
	@param		message					Indicates the type of data requested.
	@param		ioParam					Parameters are message-specific.
	@result		Error code.  You should return kDRFunctionNotSupportedErr
				when a message was passed that you don't respond to.
*/

typedef OSStatus (*DRFileProc)(
		void *			refCon,
		DRFileRef		file,
		DRFileMessage	message,
		void *			ioParam);


/*!
	@function	DRFileCreateReal
	@abstract	Creates a new real file object corresponding to a given FSRef.
	@discussion	A real file object is a file object which corresponds to a real
				file on disk.  The content of the file object corresponds to the
				actual on-disk content of the file.
	@param		fsRef					FSRef reference to a file on-disk.
	@result		The newly-created file, or NULL.
*/
extern DRFileRef
DRFileCreateReal(
	const FSRef *		fsRef)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!
	@function	DRFileCreateRealWithURL
	@abstract	Creates a new real file object corresponding to a given file URL.
	@discussion	A real file object is a file object which corresponds to a real
				file on disk.  The content of the file object corresponds to the
				actual on-disk content of the file.
	@param		urlRef					CFURLRef reference to a file on-disk.
	@result		The newly-created file, or NULL.
*/
extern DRFileRef
DRFileCreateRealWithURL(
	const CFURLRef		urlRef)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!
	@function	DRFileCreateVirtualWithData
	@abstract	Creates a virtual file object with the specified data.
	@discussion	A virtual file is a file object which does not correspond to any real
				file on disk.  It is created and modified using the DRContent calls.
				
				The file data passed in is copied internally. Although it's possible to
				create files of arbitrary size with this call, you should limit files
				created in this way to a reasonable size - say, 100K or less - because
				each file takes up a corresponding amount of memory.
				
				On multi-fork filesystems the file data is used for the data fork.
	@param		baseName				The base name to assign to the new virtual file.
	@param		fileData				A pointer to the data for the file.  May be NULL, if
										inFileLength is zero.
	@param		fileDataLength			The length of data in bytes.
	@result		The newly-created file.
*/
extern DRFileRef
DRFileCreateVirtualWithData(
	CFStringRef			baseName,
	void *				fileData,
	UInt32				fileDataLength)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!
	@function	DRFileCreateVirtualWithCallback
	@abstract	Creates a virtual file object that will be filled in during data production
				by a callback function.
	@discussion	A virtual file is a file object which does not correspond to any real file
				on disk.  It is created and populated using the DRContent calls.
				
				The framework may call the callback at any time, and the calls may be
				made in any order, until the file object has been disposed.
	@param		baseName				The base name to assign to the new virtual file.
	@param		fileProc				Callback function to generate file data.
	@param		fileProcRefCon			An optional reference parameter for the callback to use.
	@result		The newly-created file.
*/
extern DRFileRef
DRFileCreateVirtualWithCallback(
	CFStringRef			baseName,
	DRFileProc			fileProc,
	void *				fileProcRefCon)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!
	@function	DRFileCreateVirtualLink
	@abstract	Creates a virtual file object which is actually a link to another
				file or folder in the hierarchy.
	@discussion	Four link types are currently defined: symbolic links, hard links,
				Finder aliases, and combination symbolic link/Finder aliases.
				
				Links often include relative path information.  Since the relative path
				between any two objects can be different depending on the target filesystem, you
				must specify a target filesystem for the link.  The filesystem mask on the
				newly-created link will automatically be set so the file appears only in that
				filesystem.
	@param		original				The file or folder to link to.
	@param		linkType				The type of link to create.
	@param		fsKey					The target filesystem for the link.
	@result		The newly-created file.
*/
extern DRFileRef
DRFileCreateVirtualLink(
	DRFSObjectRef			original,
	DRLinkType				linkType,
	CFStringRef				fsKey)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



#ifdef __cplusplus
}
#endif

#endif /* _H_DRContentFile */

