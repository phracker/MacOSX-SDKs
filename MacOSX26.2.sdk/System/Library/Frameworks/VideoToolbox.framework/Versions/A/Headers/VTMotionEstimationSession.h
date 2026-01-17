/*
	File:  VTMotionEstimationSession.h
	
	Framework:  VideoToolbox
 
	Copyright 2022-2023 Apple Inc. All rights reserved.
  
	Video Toolbox client API for generating motion vectors from CVPixelBuffers.
*/

#ifndef VTMotionEstimationSession_h
#define VTMotionEstimationSession_h

#include <CoreFoundation/CoreFoundation.h>
#include <CoreVideo/CoreVideo.h>
#include <CoreMedia/CMBase.h>
#include <VideoToolbox/VTBase.h>
#include <VideoToolbox/VTSession.h>

#if defined(__cplusplus)
extern "C"
{
#endif
	
#pragma pack(push)
#pragma pack()

#if __BLOCKS__

CF_IMPLICIT_BRIDGING_ENABLED


/// Flags to control processing of a frame you pass to the motion-estimation session.
typedef CF_OPTIONS(uint32_t, VTMotionEstimationFrameFlags) {
	/// A hint to the motion-estimation session that you are going to reuse the `currentBuffer` as `referenceBuffer` in
	/// the next call to ``VTMotionEstimationSessionEstimateMotionVectors``. Using this flag allows the motion-estimation
	/// processor to deliver better performance.
	kVTMotionEstimationFrameFlags_CurrentBufferWillBeNextReferenceBuffer = 1<<0,
} CF_REFINED_FOR_SWIFT;

/// Directives that provide information back to you with the results of motion-estimation.
typedef CF_OPTIONS(uint32_t, VTMotionEstimationInfoFlags) {
	kVTMotionEstimationInfoFlags_Reserved0 = 1<<0,
} CF_REFINED_FOR_SWIFT;

/// A reference to a Video Toolbox motion-estimation session.
///
/// A motion-estimation session supports two `CVPixelBuffer`s of the same size and type, and returns motion vectors in
/// the form of a ``CVPixelBuffer``. The session is a reference-counted CF object. To create a motion-estimation session,
/// call ``VTMotionEstimationSessionCreate``; then you can optionally configure the session using `VTSessionSetProperty`.
/// To create motion-estimations, call ``VTMotionEstimationSessionCreateMotionEstimation``. When you are done with the
/// session, you should call ``VTMotionEstimationSessionInvalidate`` to tear it down and ``CFRelease`` to release the
/// session object reference.
typedef struct CM_BRIDGED_TYPE(id) OpaqueVTMotionEstimationSession*  VTMotionEstimationSessionRef CF_REFINED_FOR_SWIFT
	API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

/// Get the CoreFoundation type identifier for motion-estimation session type.
VT_EXPORT CFTypeID VTMotionEstimationSessionGetTypeID( void ) CF_REFINED_FOR_SWIFT
	API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

/// Creates a session you use to generate a pixel buffer of motion vectors from two pixel buffers.
///
/// The function creates a session for computing motion vectors between two pixel buffers.
///
/// - Parameters:
///   - allocator: An allocator for the session. Pass NULL to use the default allocator.
///   - motionVectorProcessorSelectionOptions: Available creation options are:
///     - term ``kVTMotionEstimationSessionCreationOption_MotionVectorSize``: Size of the search block.
///     - term ``kVTMotionEstimationSessionCreationOption_UseMultiPassSearch``: Use multiple passes to detect true motion.
///     - term ``kVTMotionEstimationSessionCreationOption_Label``: Label used for logging and resource tracking.
///   - width: The width of frames in pixels.
///   - height: The height of frames in pixels.
///   - motionEstimationSessionOut: Points to a variable to receive the new motion-estimation session.
VT_EXPORT OSStatus
VTMotionEstimationSessionCreate(
		CM_NULLABLE CFAllocatorRef	 allocator,
		CM_NULLABLE CFDictionaryRef	 motionVectorProcessorSelectionOptions,
		uint32_t					 width,
		uint32_t					 height,
		CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE VTMotionEstimationSessionRef * CM_NONNULL motionEstimationSessionOut) CF_REFINED_FOR_SWIFT
		API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

/// Copies the attributes for source pixel buffers expected by motion-estimation session.
///
/// This function provides a `CFDictionary` of attributes that you must release. Use this function to query
/// ``VTMotionEstimationSession`` for the native source attributes. If you provide an input ``CVPixelBuffer`` that is
/// not compatible with the attributes that this function returns, ``VTMotionEstimationSession`` automatically
/// converts the input pixel buffer into a compatible pixel buffer for processing.
///
/// - Parameters:
///   - session: The motion-estimation session.
///   - attributesOut: Points to a variable to receive the attributes dictionary.
VT_EXPORT OSStatus
VTMotionEstimationSessionCopySourcePixelBufferAttributes(
		CM_NONNULL VTMotionEstimationSessionRef	 motionEstimationSession,
		CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE CFDictionaryRef * CM_NONNULL attributesOut) CF_REFINED_FOR_SWIFT
		API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

/// Tears down a motion-estimation session.
///
/// When you are done with a motion-estimation session you created, call this function to tear
/// it down and then `CFRelease` to release the session object reference. When a motion-estimation session's retain count
/// reaches zero, the system automatically invalidates it, but because multiple parties may retain sessions, it can be
/// hard to predict when this happens. Calling this function ensures a deterministic, orderly teardown.
VT_EXPORT void
VTMotionEstimationSessionInvalidate(
		CM_NONNULL VTMotionEstimationSessionRef session ) CF_REFINED_FOR_SWIFT
		API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

/// A block invoked by motion-estimation session when frame processing is complete.
///
/// When the client requests a motion-estimation, the client passes in a callback block that the system invokes for the
/// result of that request. If the ``VTMotionEstimationSessionCreateMotionEstimation`` call returns an error, the system
/// does not invoke this block.
///
/// - Parameters:
///   - status: `noErr` if processing request was successful; an error code if motion-estimation was not successful.
///   - infoFlags: A bit field that contains information about the processing operation.
///   - additionalInfo: Additional processing information about the operation that cannot fit in `infoFlags`.
///   Currently, the system expects this to be NULL.
///   - motionVectorPixelBuffer: A `CVPixelBuffer` that contains the motion vector information, if processing request
///   was successful; otherwise, NULL.
typedef void (^VTMotionEstimationOutputHandler)(
		OSStatus status,
		VTMotionEstimationInfoFlags infoFlags,
		CM_NULLABLE CFDictionaryRef additionalInfo,
		CM_NULLABLE CVPixelBufferRef motionVectors);

/// Creates a new pixel buffer that contains motion vectors between the input pixel buffers.
///
/// The motion-estimation session compares the reference frame to the current frame, and generates motion vectors in
/// the form of a `CVPixelBuffer`.
///
/// - Parameters:
///   - session: The motion-estimation session.
///   - referenceImage: The reference image.
///   - currentImage: The current image.
///   - motionEstimationFrameFlags: A bit field with per-frame options. See ``kVTMotionEstimationFrameFlags_CurrentBufferWillBeNextReferenceBuffer``.
///   - additionalFrameOptions: A way to pass additional information that doesn't fit in `motionEstimationFrameFlags`;
///   currently the system expects it to be `NULL`.
///   - outputHandler: The block invoked by the syetem when the processing request is completed. If the
///   `VTMotionEstimationSessionCreateMotionEstimation` call returns an error, the system does not invoke the block.
///
/// - Returns: If the call was successful, returns `noErr`; otherwise, returns an error code, such as `kVTMotionEstimationNotSupportedErr`.
VT_EXPORT OSStatus
VTMotionEstimationSessionEstimateMotionVectors(
		CM_NONNULL VTMotionEstimationSessionRef    session,
		CM_NONNULL CVPixelBufferRef                referenceImage,
		CM_NONNULL CVPixelBufferRef                currentImage,
		VTMotionEstimationFrameFlags			   motionEstimationFrameFlags,
		CM_NULLABLE CFDictionaryRef			   	   additionalFrameOptions,
		CM_NONNULL VTMotionEstimationOutputHandler outputHandler ) CF_REFINED_FOR_SWIFT
		API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

/// Directs the motion-estimation session to emit all pending frames and waits for completion.
///
/// Directs the motion-estimation session to emit all pending frames, then waits for all outstanding requests to complete, then returns.
VT_EXPORT OSStatus
VTMotionEstimationSessionCompleteFrames(
		CM_NONNULL VTMotionEstimationSessionRef		session) CF_REFINED_FOR_SWIFT
		API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

CF_IMPLICIT_BRIDGING_DISABLED

// For information on property access APIs on ``VTMotionEstimationSession``, see ``VTSession.h``.
// For information on standard property keys and values for pixel transfer sessions, see ``VTMotionEstimationSessionProperties.h``.

#endif // __BLOCKS__

#pragma pack(pop)

#if defined(__cplusplus)
}
#endif

#endif /* VTMotionEstimationSession_h */
