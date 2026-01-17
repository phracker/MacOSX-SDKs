/*
	File:  VTHDRPerFrameMetadataGenerationSession.h
 
	Framework:  VideoToolbox
 
	Copyright 2023 Apple Inc. All rights reserved.
 
 */

#ifndef VTHDRPerFrameMetadataGenerationSession_H
#define VTHDRPerFrameMetadataGenerationSession_H

#include <CoreMedia/CMBase.h>
#include <VideoToolbox/VTBase.h>
#include <VideoToolbox/VTErrors.h>
#include <VideoToolbox/VTSession.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreVideo/CoreVideo.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push)
#pragma pack()

CF_IMPLICIT_BRIDGING_ENABLED

CM_ASSUME_NONNULL_BEGIN

/*!
	@header
	@abstract
		Video Toolbox HDR Metadata Generation Session
		
	@discussion
		This file defines the public API for the VTHDRPerFrameMetadataGenerationSession.
 
*/

typedef CFStringRef VTHDRPerFrameMetadataGenerationHDRFormatType CF_EXTENSIBLE_STRING_ENUM API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

/*!
	@constant	kVTHDRPerFrameMetadataGenerationHDRFormatType_DolbyVision
	@abstract		Specifies that DolbyVision data should be generated and attached for each pixel buffer.
 */
VT_EXPORT const VTHDRPerFrameMetadataGenerationHDRFormatType kVTHDRPerFrameMetadataGenerationHDRFormatType_DolbyVision API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

/*!
	@constant	kVTHDRPerFrameMetadataGenerationOptionsKey_HDRFormats
	@abstract		Specifies an array of HDR formats that should be generated.
	@discussion
		This key represents a CFArrayRef. Only one key is supported ( kVTHDRPerFrameMetadataGenerationHDRFormatType_DolbyVision ).
 */
VT_EXPORT const CFStringRef kVTHDRPerFrameMetadataGenerationOptionsKey_HDRFormats API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos); // Write-only, Optional, CFArray


/*!
	@typedef	VTHDRPerFrameMetadataGenerationSessionRef
	@abstract	A mechanism for generating HDR Per Frame Metadata and attaching that metadata to a CVPixelBuffer and the backing IOSurface.
	@discussion
		VTHDRPerFrameMetadataGenerationSessionRef is a CF type, so call CFRelease to release your object reference.
*/
typedef struct CM_BRIDGED_TYPE( id ) OpaqueVTHDRPerFrameMetadataGenerationSession*  VTHDRPerFrameMetadataGenerationSessionRef  CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos); // a CF type, call CFRetain and CFRelease

VT_EXPORT CFTypeID VTHDRPerFrameMetadataGenerationSessionGetTypeID( void ) API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), visionos(2.0)) CF_REFINED_FOR_SWIFT API_UNAVAILABLE(watchos);
	
// Interface for video compression session clients:

/*!
	@function	VTHDRPerFrameMetadataGenerationSessionCreate
	@abstract	Creates a VTHDRPerFrameMetadataGenerationSession object.
	@discussion
		The returned VTHDRPerFrameMetadataGenerationSession object may be used to perform HDR Per Frame Metadata Generation
		Call CFRelease to release your object reference.
	@param framesPerSecond
		Value must be greater than 0.0
	@param options
		CFDictionary may contain the key kVTHDRPerFrameMetadataGenerationOptionsHDRFormatsKey.
*/
VT_EXPORT OSStatus
VTHDRPerFrameMetadataGenerationSessionCreate(
	CM_NULLABLE CFAllocatorRef			allocator,
	float								framesPerSecond,
	CM_NULLABLE CFDictionaryRef			options,
	CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE VTHDRPerFrameMetadataGenerationSessionRef * CM_NONNULL hdrPerFrameMetadataGenerationSessionOut )  CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

/*!
	@function	VTHDRPerFrameMetadataGenerationSessionAttachMetadata
	@abstract	Attaches the Per Frame Metadata to the CVPixelBuffer and the backing IOSurface
	@discussion
			Call this to analyze and attach HDR Metadata. This call will change CVPixelBuffer attachments and backing IOSurface attachments.
	@param hdrPerFrameMetadataGenerationSession
	@param pixelBuffer
	@param sceneChange
			If this frame changes significantly in brightness from the previous frame, for example going from an indoor scene to an outdoor scene or
			from a night scene to a daytime scene, set this to true.
*/
VT_EXPORT OSStatus
VTHDRPerFrameMetadataGenerationSessionAttachMetadata(
	VTHDRPerFrameMetadataGenerationSessionRef hdrPerFrameMetadataGenerationSession,
	CVPixelBufferRef pixelBuffer,
	Boolean sceneChange ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), visionos(2.0))  API_UNAVAILABLE(watchos);

CM_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#pragma pack(pop)

#if defined(__cplusplus)
}
#endif

#endif // VTHDRPerFrameMetadataGenerationSession_H
