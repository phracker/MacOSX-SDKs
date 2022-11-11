/*
	File:  VTMultiPassStorage.h
	
	Framework:  VideoToolbox
	
	Copyright 2012-2013 Apple Inc. All rights reserved.
	
	Video Toolbox object for storage of multi-pass video encoding metadata.
*/

#ifndef VTMULTIPASSSTORAGE_H
#define VTMULTIPASSSTORAGE_H

#include <CoreMedia/CMBase.h>
#include <VideoToolbox/VTBase.h>
#include <CoreMedia/CMTimeRange.h>

#include <VideoToolbox/VTErrors.h>

#include <CoreFoundation/CoreFoundation.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)    
	
CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@typedef	VTMultiPassStorageRef
	@abstract	A mechanism for storing information for each frame of a multi-pass compression session.
	@discussion
		VTMultiPassStorageRef is a CF type, so call CFRelease and CFRetain to manage objects of this type.
		The data stored in the VTMultiPassStorage is private to the video encoder.
*/
typedef struct CM_BRIDGED_TYPE(id) OpaqueVTMultiPassStorage*  VTMultiPassStorageRef; // a CF type, call CFRetain and CFRelease

VT_EXPORT CFTypeID VTMultiPassStorageGetTypeID(void) API_AVAILABLE(macosx(10.10), ios(8.0), tvos(10.2));
	
CF_IMPLICIT_BRIDGING_DISABLED

// Interface for video compression session clients:

/*!
	@function	VTMultiPassStorageCreate
	@abstract	Creates a VTMultiPassStorage object using a temporary file.
	@discussion
		The returned VTMultiPassStorage object may be used to perform multi-pass encoding; see kVTCompressionPropertyKey_MultiPassStorage.
		Call CFRelease to release your retain on the created VTMultiPassStorage object when you are done with it.
	@param fileURL
		Specifies where to put the backing file for the VTMultiPassStorage object.
		If you pass NULL for fileURL, the video toolbox will pick a unique temporary file name.
	@param timeRange
		Gives a hint to the multi pass storage about valid time stamps for data.
	@param options
		If the file did not exist when the storage was created, the file will be deleted when the VTMultiPassStorage object is finalized, unless you set the kVTMultiPassStorageCreationOption_DoNotDelete option to kCFBooleanTrue in the options dictionary.
*/
VT_EXPORT OSStatus 
VTMultiPassStorageCreate(
	CM_NULLABLE CFAllocatorRef						allocator,
	CM_NULLABLE CFURLRef							fileURL,
	CMTimeRange										timeRange,				   /* can be kCMTimeRangeInvalid */
	CM_NULLABLE CFDictionaryRef						options,
	CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE VTMultiPassStorageRef * CM_NONNULL multiPassStorageOut) API_AVAILABLE(macosx(10.10), ios(8.0), tvos(10.2));
	
CF_IMPLICIT_BRIDGING_ENABLED
	
CM_ASSUME_NONNULL_BEGIN

VT_EXPORT const CFStringRef kVTMultiPassStorageCreationOption_DoNotDelete; // CFBoolean, false by default.  Provided for use when debugging video encoders.
	
CM_ASSUME_NONNULL_END


/*!
	@function	VTMultiPassStorageClose
	@abstract	Ensures that any pending data is written to the multipass storage file and closes the file.
	@discussion
		After this function is called, all methods on the multipass storage object will fail.
		It is still necessary to release the object by calling CFRelease.
*/
VT_EXPORT OSStatus 
VTMultiPassStorageClose(
	CM_NONNULL VTMultiPassStorageRef	multiPassStorage ) API_AVAILABLE(macosx(10.10), ios(8.0), tvos(10.2));
	
CF_IMPLICIT_BRIDGING_DISABLED

#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif // VTMULTIPASSSTORAGE_H
