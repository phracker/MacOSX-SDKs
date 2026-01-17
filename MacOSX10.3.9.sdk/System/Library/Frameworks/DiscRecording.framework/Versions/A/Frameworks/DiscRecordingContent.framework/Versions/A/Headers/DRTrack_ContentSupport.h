/*
     File:       DiscRecordingContent/DRTrack_ContentSupport.h
 
     Contains:   ObjC interface to track objects used in filesystem creation.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*!	@header 	DRTrack_ContentSupport.h
	@abstract	Preconfigured track objects to burn audio and data content to disc.
	@discussion	The methods here provide a fairly simple interface for creating the most
				common tracks. 
*/

#import <Foundation/Foundation.h>

#import <DiscRecordingEngine/DRTrack.h>
#import <DiscRecordingEngine/DRMSF.h>
#import <DiscRecordingContent/DRFolder.h>

#include <AvailabilityMacros.h>

/* ------------------------------------------------------------------------------ */
/* Preconfigured track types */
/*!
	@category DRTrack (AudioContentCreation)
	@discussion This category on DRTrack creates a track configured to burn audio data to disc.
				It impelements two methods @link //apple_ref/occ/instm/DRTrack(DataContentCreation)/trackForAudioOfLength%58producer%58 trackForAudioOfLength:producer: @/link.
				and @link //apple_ref/occ/instm/DRTrack(DataContentCreation)/trackForAudioFile%58 trackForAudioFile: @/link which
				create and returns a fully configured track to the caller.
*/
@interface DRTrack (AudioContentCreation)

/*!
	@method			trackForAudioOfLength:producer:
	@abstract		Creates a DRTrack capable of burning RedBook CD audio.
	@discussion		This method configures a track object configured to accept standard RedBook audio
					CD data. It is up to the client to provide that data to the 
					track object through the producer object. The producer is an object
					which implements the @link //apple_ref/occ/intf/DRTrackDataProduction DRTrackDataProduction @/link protocol.
	@param			length		The length of the track that will be produced.
	@param			producer	The object to use as the data producer
	@result			An autoreleased DRTrack
*/

+ (DRTrack*) trackForAudioOfLength:(DRMSF*)length producer:(id)producer;

/*!
	@method			trackForAudioFile:
	@abstract		Creates a DRTrack capable of burning RedBook CD audio from a QuickTime readable file.
	@discussion		This method creates a track object configured and primed to output RedBook audio
					CD data. It accepts any file readable by QuickTime and extracts the audio data
					(if any) from the file, translating that into the correct format for output
					to the disc.
	@param			path	The path to the file. This file must be one that can be read by
							QuickTime. 
	@result			An autoreleased DRTrack
*/
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
+ (DRTrack*) trackForAudioFile:(NSString*)path;
#endif

@end


/*!
	@category DRTrack (DataContentCreation)
	@discussion	This category on DRTrack creates a custom DRTrack instance which is set up to burn
				a DRFolder to disc. It implements only one method, @link //apple_ref/occ/instm/DRTrack(DataContentCreation)/trackForRootFolder%58 trackForRootFolder: @/link which
				creates and returns a fully configured track to the caller.
*/
@interface DRTrack (DataContentCreation)

/*!
	@method			trackForRootFolder:
	@abstract		Creates a DRTrack capable of burning a folder to disc.
	@discussion		Additional track properties can be set controlling the various 
					filesystems to be generated. See the documentation for DRTrack.h for more info.
	@param			rootFolder		The root of the volume to be created.
	@result			An autoreleased DRTrack
*/
+ (DRTrack*) trackForRootFolder:(DRFolder*)rootFolder;

@end
