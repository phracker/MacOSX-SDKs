/*
     File:       DiscRecordingContent/DRContentTrack.h
 
     Contains:   Interface to track objects used in content creation.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*!	@header 	
	@abstract		Interface to track objects used in filesystem creation.

	@discussion		
*/

#ifndef _H_DRContentTrack
#define _H_DRContentTrack

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif

#ifndef _H_DRCoreTrack
#include <DiscRecordingEngine/DRCoreTrack.h>
#endif

#ifndef _H_DRContentFolder
#include <DiscRecordingContent/DRContentFolder.h>
#endif

#ifndef _H_DRContentProperties
#include <DiscRecordingContent/DRContentProperties.h>
#endif

#ifndef __AVAILABILITYMACROS__
#include <AvailabilityMacros.h>
#endif

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif



/* ------------------------------------------------------------------------------ */
/*!
	@typedef DRFilesystemTrackRef
	A DRFilesystemTrack is just a special DRTrack.  The type ID of a DRFilesystemTrack
	is the same as the type ID of a DRTrack.
*/
typedef DRTrackRef DRFilesystemTrackRef;

/*!
	@function	DRFilesystemTrackCreate
	@abstract	Creates a filesystem track capable of burning a folder.
	@discussion	You can set the filesystem track's properties using the calls
				in DRCoreTrack.h - see also DRContentProperties.h for a list
				of settable track properties.
	@param		rootFolder		The root folder for the filesystem.
	@result		A DRFilesystemTrack capable of burning the track.
*/
extern DRFilesystemTrackRef
DRFilesystemTrackCreate(
	DRFolderRef		rootFolder)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRFilesystemTrackEstimateOverhead
	@abstract	Provides an estimate of the approximate size that should be reserved
				for directory structures on a disc.  
	@discussion	This call provides a simple estimate of approximate overhead before any data
				has been specified, for situations where such information may be useful
				ahead of time.  One such example is in Finder burning, when a disk image
				is created that is sized to fit a newly-inserted disc.
				
				The result of this function is merely an estimate, and the actual number of
				blocks required may be lower or higher depending on the data to burn.  For
				more accurate results, wait until the burn is ready to start, create a
				DRFilesystemTrack, and then call @link //apple_ref/c/func/DRTrackEstimateLength DRTrackEstimateLength @/link  If size returned by that
				function is greater than the actual space available, then the burn will not
				succeed: ask the user to remove some data and try the burn again.
	@param		numBlocks		The number of blocks on the disc.
	@param		blockSize		The size of blocks on the disc (usually 2048).
	@param		fsMask			The requested filesystem mask, or @link kDRFilesystemMaskDefault kDRFilesystemMaskDefault @/link.
	@result		The number of blocks needed for filesystem overhead on a typical disc of this size.
*/
extern UInt64
DRFilesystemTrackEstimateOverhead(
	UInt64				numBlocks,
	UInt32				blockSize,
	DRFilesystemMask	fsMask)
AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/* ------------------------------------------------------------------------------ */
/*!
	@typedef DRAudioTrackRef
	A DRAudioTrack is just a special DRTrack.  The type ID of a DRAudioTrack
	is the same as the type ID of a DRTrack.
*/
typedef DRTrackRef DRAudioTrackRef;

/*!
	@function	DRAudioTrackCreate
	@abstract	Creates an audio track capable of burning RedBook CD audio from a file.
	@discussion	This function creates a track object configured and primed to output RedBook audio
				CD data. It accepts any file readable by QuickTime and extracts the audio data
				(if any) from the file, translating that into the correct format for output
				to the disc.
	@param		audioFile	An FSRef referencing the file to write.
	@result		A DRAudioTrack capable of burning the track.
*/
extern DRAudioTrackRef
DRAudioTrackCreate(
	const FSRef*		audioFile)
AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@function	DRAudioTrackCreateWithURL
	@abstract	Creates an audio track capable of burning RedBook CD audio from a file.
	@discussion	This function creates a track object configured and primed to output RedBook audio
				CD data. It accepts any file readable by QuickTime and extracts the audio data
				(if any) from the file, translating that into the correct format for output
				to the disc.
	@param		audioFileURL	A file CFURL referencing the on-disk file to write.
	@result		A DRAudioTrack capable of burning the track.
*/
extern DRAudioTrackRef
DRAudioTrackCreateWithURL(
	CFURLRef			audioFileURL)
AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


#ifdef __cplusplus
}
#endif

#endif /* _H_DRContentTrack */

