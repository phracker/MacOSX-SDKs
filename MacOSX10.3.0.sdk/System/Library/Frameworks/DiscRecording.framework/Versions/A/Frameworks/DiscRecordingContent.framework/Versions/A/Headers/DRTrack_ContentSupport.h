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

#import <Foundation/Foundation.h>

#import <DiscRecordingEngine/DRTrack.h>
#import <DiscRecordingEngine/DRMSF.h>
#import <DiscRecordingContent/DRFolder.h>

#include <AvailabilityMacros.h>

/* ------------------------------------------------------------------------------ */
/* Preconfigured track types */
/*" This category on DRTrack creates a track configured to burn audio data to disc. "*/
@interface DRTrack (AudioContentCreation)

/*!
	@method			trackForAudioOfLength:producer:
	@abstract		Creates a DRTrack capable of burning RedBook CD audio.
	@param			length		The length of the track that will be produced.
	@param			producer	The object to use as the data producer
	@result			An autoreleased DRTrack
*/

+ (DRTrack*) trackForAudioOfLength:(DRMSF*)length producer:(id)producer;

/*!
	@method			trackForAudioFile:producer:
	@abstract		Creates a DRTrack capable of burning RedBook CD audio from a QuickTime readable file.
	@param			path	The path to the file. This file must be one that can be read by
							QuickTime. 
	@result			An autoreleased DRTrack
*/
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
+ (DRTrack*) trackForAudioFile:(NSString*)path;
#endif

@end


/*" This category on DRTrack creates a custom DRTrack instance which is set up to burn
	a DRFolder to disc. It implements only one method, <b>trackForRootFolder:</b> which
	creates and returns a fully configured track to the caller. "*/
@interface DRTrack (DataContentCreation)

/*!
	@method			trackForRootFolder:
	@abstract		Creates a DRTrack capable of burning a folder to disc.
	@discussion		Additional track properties can be set controlling the various 
					filesystems to be generated.
	@param			rootFolder		The root of the volume to be created.
	@result			An autoreleased DRTrack
*/
+ (DRTrack*) trackForRootFolder:(DRFolder*)rootFolder;

@end
