/*
     File:       DiscRecording/DRContentTrack.h
 
     Contains:   Interface to track objects used in content creation.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef _H_DRContentTrack
#define _H_DRContentTrack

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif

#ifndef _H_DRCoreTrack
#include <DiscRecording/DRCoreTrack.h>
#endif

#ifndef _H_DRContentFolder
#include <DiscRecording/DRContentFolder.h>
#endif

#ifndef _H_DRContentProperties
#include <DiscRecording/DRContentProperties.h>
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




#ifdef __cplusplus
}
#endif

#endif /* _H_DRContentTrack */

