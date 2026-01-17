/*
	File:  VTPixelRotationSession.h
 
	Framework:  VideoToolbox
 
	Copyright 2021-2023 Apple Inc. All rights reserved.
 
*/

#ifndef _VT_PIXELROTATIONSESSION_H_
#define _VT_PIXELROTATIONSESSION_H_

#include <CoreFoundation/CoreFoundation.h>
#include <CoreVideo/CoreVideo.h>
#include <CoreMedia/CMBase.h>
#include <VideoToolbox/VTBase.h>
#include <VideoToolbox/VTSession.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)

/*!
	@typedef	VTPixelRotationSessionRef
	@abstract	A reference to a Video Toolbox Pixel Rotation Session.
	@discussion
		A pixel rotation session supports the rotating of images from source CVPixelBuffers to
		destination CVPixelBuffers.  The session reference is a reference-counted CF object.
		To create an image rotation session, call VTPixelRotationSessionCreate;
		then you can optionally configure the session using VTSessionSetProperty;
		then to transfer pixels, call VTPixelRotationSessionRotateImage.
		When you are done with the session, you should call CFRelease to tear it down
		and release your object reference.
 */

typedef struct CM_BRIDGED_TYPE(id) OpaqueVTPixelRotationSession*  VTPixelRotationSessionRef CM_SWIFT_NONSENDABLE API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@function	VTPixelRotationSessionCreate
	@abstract	Creates a session for rotating images between CVPixelBuffers.
	@param	allocator
		An allocator for the session.  Pass NULL to use the default allocator.
	@param	pixelRotationSessionOut
		Points to a variable to receive the new pixel rotation session.
*/
VT_EXPORT OSStatus
VTPixelRotationSessionCreate(
	CM_NULLABLE CFAllocatorRef														 allocator,
	CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE VTPixelRotationSessionRef * CM_NONNULL pixelRotationSessionOut) API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@function	VTPixelRotationSessionInvalidate
	@abstract	Tears down a pixel rotation session.
    @discussion 
    	When you are done with an image rotation session you created, call VTPixelRotationSessionInvalidate
    	to tear it down and then CFRelease to release your object reference.
    	When an pixel rotation session's retain count reaches zero, it is automatically invalidated, but
    	since sessions may be retained by multiple parties, it can be hard to predict when this will happen.
    	Calling VTPixelRotationSessionInvalidate ensures a deterministic, orderly teardown.
*/
VT_EXPORT void
VTPixelRotationSessionInvalidate( CM_NONNULL VTPixelRotationSessionRef session ) API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@function VTPixelRotationSessionGetTypeID
	@abstract Returns the CFTypeID for pixel rotation sessions.
*/
VT_EXPORT CFTypeID
VTPixelRotationSessionGetTypeID(void) API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@function	VTPixelRotationSessionRotateImage
	@abstract	Rotates a pixel buffer.
	@discussion
		Rotates sourceBuffer and places the output in destinationBuffer.
		For 90 and 270 degree rotations, the width and height of destinationBuffer must be the inverse
		of sourceBuffer.
		For 180 degree rotations, the width and height of destinationBuffer and sourceBuffer must match.
		By default, all existing attachments on destinationBuffer are removed and new attachments
		are set describing the transferred image.  Unrecognised attachments on sourceBuffer will 
		be propagated to destinationBuffer.
		Some properties may modify this behaviour; see VTPixelRotationProperties.h for more details.
	@param	session
		The pixel rotation session.
	@param	sourceBuffer
		The source buffer.
	@param	destinationBuffer
		The destination buffer.  
	@result
		If the transfer was successful, noErr; otherwise an error code, such as kVTPixelRotationNotSupportedErr.
*/
VT_EXPORT OSStatus
VTPixelRotationSessionRotateImage(
	CM_NONNULL VTPixelRotationSessionRef       session,
	CM_NONNULL CVPixelBufferRef                sourceBuffer,
	CM_NONNULL CVPixelBufferRef                destinationBuffer) API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos);

// See VTSession.h for property access APIs on VTPixelRotationSession.

#pragma pack(pop)

#if defined(__cplusplus)
}
#endif

#endif // _VT_PIXELROTATIONSESSION_H_
