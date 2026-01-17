/*
     File:       DiscRecordingContent/DRContentFile.h
 
     Contains:   Interface to file objects used in filesystem creation.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
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
#include <DiscRecordingContent/DRContentObject.h>
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
	@abstract	Returns the type identifier of all DRFile objects.
*/
extern
CFTypeID DRFileGetTypeID()
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;




/*!
	@typedef	DRLinkType
	@abstract	Link types available for the <tt>DRFileCreateVirtualLink</tt> function.
*/
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
	@abstract	Messages sent to the <tt>DRFileProc</tt> callback during a burn.
*/
typedef UInt32	DRFileMessage;

enum {
	/*!	@constant	kDRFileMessageForkSize
		@abstract	Indicates a request for your <tt>DRFileProc</tt> callback to 
					supply a file track size.
		
		@discussion	Your <tt>DRFileProc</tt> callback should respond to this 
					message by placing the requested file fork size into the 
					<tt>DRFileForkSizeInfo</tt> structure, which is pointed to 
					by the callback's <tt>ioParam</tt> parameter. Your callback 
					may receive this message at any time after the file object 
					has been created.
					
					On input, the structure's <tt>fork</tt> field indicates which fork 
					you are being asked about, as defined in the <tt>DRFileForkIndex</tt> 
					enumeration.
					
					Also on input, the structure's <tt>query</tt> field indicates 
					whether you are being asked for an estimated or actual fork size, as
					defined in the <tt>DRFileForkSizeQuery</tt> enumeration.
		
					When the <tt>query</tt> field is <tt>kDRFileForkSizeEstimate</tt>, you are 
					being asked for an estimate of the final fork size, perhaps for the
					burn engine to estimate the track size. You do not have to be exact,
					but your estimate should err on the high side. This call may be made 
					at any time.
					
					When the <tt>query</tt> field is <tt>kDRFileForkSizeActual</tt>, you 
					are being asked for the actual fork size to be used in the burn.  This 
					call is made only in the burn phase.
	*/
	kDRFileMessageForkSize = 'fsiz',
	
	/*!	@constant	kDRFileMessagePreBurn
		@abstract	Indicates that your application should perform all necessary preparation
					for the burn.
		
		@discussion	Your <tt>DRFileProc</tt> callback should respond to this message
					by telling your application to open files, or to do any other pre-burn
					preparation work needed. The burn engine sends this message before the
					burn but after the disc's entire hierarchy is completely in place. You
					can query the hierarchy
					
					After this call, the burn's content is locked down, and you should be
					able to respond to the <tt>kDRFileMessageForkSize</tt> message with exact values.
					
					Sent before the burn.
					The callback's <tt>ioParam</tt> parameter is ignored.
	*/
	kDRFileMessagePreBurn = 'pre ',
	
	/*!	@constant	kDRFileMessageProduceData
		@abstract	Sent during the burn (after the pre-burn call).
					The callback's <tt>ioParam</tt> parameter points to a <tt>DRFileProductionInfo</tt>
					structure.
					
					Speed is critical during this call.  You should produce the data as fast
					as possible, and try not to perform any time-consuming tasks.
		@discussion	You may be asked to produce twice, once during the actual burn
					and once during verification. 
	*/
	kDRFileMessageProduceData = 'prod',
	
	/*!	@constant	kDRFileMessageVerificationStarting
		@abstract	Sent during the burn (after the pre-burn call, after production, before the
					post-burn call) to indicate that verification is about to begin.
					The callback's <tt>ioParam</tt> parameter is ignored.
		@discussion	This would be an appropriate place to seek back to the beginning of
					files, reset state machines, or do whatever else is needed to prepare to
					produce again.
	*/
	kDRFileMessageVerificationStarting = 'vrfy',
	
	/*!	@constant	kDRFileMessagePostBurn
		@abstract	Sent at the end of the burn.
					The callback's <tt>ioParam</tt> parameter is ignored.
		@discussion	This would be an appropriate place to close files, or do any other
					teardown work needed.  This call will always be made regardless of
					whether the burn succeeded or failed.
	*/
	kDRFileMessagePostBurn = 'post',
	
	/*!	@constant	kDRFileMessageRelease
		@abstract	Sent when the DRFileRef is released.
					The callback's <tt>ioParam</tt> parameter is ignored.
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
		@discussion	Typically, the resource fork contains secondary meta-data, which is not
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

enum
{
	/*!
		@constant	kDRFileForkSizeActual
		@abstract	Indicates a request for actual size.
	*/
	kDRFileForkSizeActual		= 0,

	/*!
		@constant	kDRFileForkSizeEstimate
		@abstract	Indicates a request for estimated size.
	*/
	kDRFileForkSizeEstimate		= 1
};

/*!
	@struct		DRFileForkSizeInfo
	@abstract	Structure used when requesting fork sizes.
	@field		fork					(in) which fork is being requested
	@field		query					(in) type of query, estimate or actual
	@field		size					(out) returned size
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
	@abstract	Structure used by the <tt>DRFileProc</tt> callback during production of a track.
	@field		requestedAddress		(out) byte address that the burn engine is requesting
	@field		buffer					(out) buffer to produce into
	@field		reqCount				(out) number of bytes requested
	@field		actCount				(in) number of bytes you actually produced
	@field		blockSize				(out) current block size, you must always return multiples of this
	@field		fork					(out) which fork is being requested
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
	@abstract	Callback function to produce and manage a file for recording a track.
	@discussion	Your application needs to implement a callback to create files representing
				tracks to burn, and to interact with those tracks by responding to the 
				messages in the <tt>DRFileMessage</tt> enumeration.
	
				If you name your function <tt>MyDRFileCallback</tt>, you would
				declare it like this:
				
				<pre>
					OSStatus MyDRFileCallback (
						void			*refCon,
						DRFileRef		file,
						DRFileMessage	message,
						void			*ioParam
					);
				</pre>
				
				Your callback places the requested data
				
				If your callback does not support a given function, it should return
				<tt>kDRFunctionNotSupportedErr</tt>.
				
	@param	refCon		Reference context for your use, established when
						the callback is registered.
	@param	file		The file object being produced.
	@param	message		Sent by the Disc Recording engine to indicate the 
						type of data it needs your application to supply. The 
						various messages are defined in the <tt>DRFileMessage</tt> 
						enumeration.
	@param	ioParam		Parameters are message-specific. See the <tt>DRFileMessage</tt>
						enumeration.
	@result				Your application should return <tt>kDRFunctionNotSupportedErr</tt>
						when a message was passed that it doesn't respond to.
*/

typedef OSStatus (*DRFileProc)(
		void *			refCon,
		DRFileRef		file,
		DRFileMessage	message,
		void *			ioParam);


/*!
	@function	DRFileCreateReal
	@abstract		Creates a new real file object corresponding to a given FSRef.
	@discussion		A real file object is a file object which corresponds to a real
					file on disk.  The content of the file object corresponds to the
					actual on-disk content of the file.
	@param	fsRef	An <tt>FSRef</tt> reference to a file on-disk.
	@result			The newly-created file, or <tt>NULL</tt>.
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
	@result		Returns a reference to the newly-created real file object, or <tt>NULL</tt>.
*/
extern DRFileRef
DRFileCreateRealWithURL(
	const CFURLRef		urlRef)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!
	@function	DRFileCreateVirtualWithData
	@abstract			Creates a virtual file object with the specified data.
	@discussion			A virtual file is a file object which does not correspond to any real
						file on disk, but represents a file you want to appear in the file
						structure of the disc you are burning. It is created and modified 
						using Disc Recording's 'content' functions -- see the 
						documentation for DRContentObject.h.
				
						The file data passed in to this function is copied internally. Although 
						it's possible to create files of arbitrary size with this function, you 
						should limit files created in this way to a reasonable size, such as
						100K or less, because each file consumes a corresponding amount of memory.
				
						On multi-fork file systems the file data is used for the data fork.
	@param	baseName	The base name to assign to the new virtual file.
	@param	fileData	A pointer to the data for the file.  May be <tt>NULL</tt> if
						<tt>inFileLength</tt> is zero.
	@param	fileDataLength	The length of data in bytes.
	@result				Returns a reference to the newly-created virtual file object, or <tt>NULL</tt>.
*/
extern DRFileRef
DRFileCreateVirtualWithData(
	CFStringRef			baseName,
	void *				fileData,
	UInt32				fileDataLength)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!
	@function	DRFileCreateVirtualWithCallback
	@abstract			Creates a virtual file object that will be filled in during data production
						by a callback function.
	@discussion			A virtual file is a file object which does not correspond to any real file
						on disk, but represents a file you want to appear in the file
						structure of the disc you are burning. It is created and modified 
						using Disc Recording's 'content' functions -- see the 
						documentation for DRContentObject.h.
				
						The Disc Recording framework may invoke the callback at any time, and the 
						calls may be made in any order, until the file object has been disposed.
	@param	baseName	The base name to assign to the new virtual file. For information on base
						names and how Disc Recording works with them, see <tt>DRFSObjectSetBaseName</tt>
						and <tt>DRFSObjectSetSpecificName</tt>.
	@param	fileProc	Your application-implemented callback function to generate file data.
	@param	fileProcRefCon	An optional reference context for the callback to use.
	@result				Returns a reference to the newly-created virtual file object, or <tt>NULL</tt>.
*/
extern DRFileRef
DRFileCreateVirtualWithCallback(
	CFStringRef			baseName,
	DRFileProc			fileProc,
	void *				fileProcRefCon)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!
	@function	DRFileCreateVirtualLink
	@abstract			Creates a virtual file or folder object in the form of a link to another
						file or folder in the hierarchy.
	@discussion			Disc Recording currently supports four link types: symbolic links, hard links,
						Finder aliases, and combination symbolic link/Finder aliases.
				
						Links often include relative path information.  Since the relative path
						between two objects can be different depending on the target file system, you
						must specify a target file system when requesting a link.  The file system 
						mask on the newly-created link will automatically be set to ensure the file 
						appears only in that file system.
	@param	original	The file or folder to link to.
	@param	linkType	The type of link to create. See the <tt>DRLinkType</tt> enumeration.
	@param	fsKey		The target file system for the link. The various keys are defined in
						DRContentProperties.h.
	@result				A reference to the newly-created virtual file or folder object.
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

