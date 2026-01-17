/*
	File:  VTDecompressionSession.h
	
	Framework:  VideoToolbox
 
    Copyright 2006-2023 Apple Inc. All rights reserved.
  
	Video Toolbox client API for decompressing video frames.
	
	Decompression sessions convert compressed video frames in CMSampleBuffers 
	into uncompressed frames in CVImageBuffers.
*/

#ifndef VTDECOMPRESSIONSESSION_H
#define VTDECOMPRESSIONSESSION_H

#include <CoreMedia/CMBase.h>
#include <VideoToolbox/VTBase.h>

#include <CoreFoundation/CoreFoundation.h>
#include <CoreVideo/CoreVideo.h>
#include <CoreMedia/CMSampleBuffer.h>
#include <CoreMedia/CMFormatDescription.h>
#include <CoreMedia/CMTime.h>
#include <CoreMedia/CMTaggedBufferGroup.h>

#include <VideoToolbox/VTSession.h>
#include <VideoToolbox/VTDecompressionProperties.h>

#include <VideoToolbox/VTErrors.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)

/*!
	@typedef	VTDecompressionSessionRef
	@abstract	A reference to a Video Toolbox Decompression Session.
	@discussion
		A decompression session supports the decompression of a sequence of video frames.
		The session reference is a reference-counted CF object.
		To create a decompression session, call VTDecompressionSessionCreate; 
		then you can optionally configure the session using VTSessionSetProperty;
		then to decode frames, call VTDecompressionSessionDecodeFrame.
		When you are done with the session, you should call VTDecompressionSessionInvalidate
		to tear it down and CFRelease to release your object reference.
 */

typedef struct CM_BRIDGED_TYPE(id) OpaqueVTDecompressionSession*  VTDecompressionSessionRef CM_SWIFT_NONSENDABLE;

/*!
	@typedef	VTDecompressionOutputCallback
	@abstract	Prototype for callback invoked when frame decompression is complete.
	@discussion 
		When you create a decompression session, you pass in a callback function to be called 
		for decompressed frames.  This function will not necessarily be called in display order.
	@param	decompressionOutputRefCon
		The callback's reference value, copied from the decompressionOutputRefCon field of the
		VTDecompressionOutputCallbackRecord structure.
	@param	sourceFrameRefCon
		The frame's reference value, copied from the sourceFrameRefCon argument to 
		VTDecompressionSessionDecodeFrame.
	@param	status
		noErr if decompression was successful; an error code if decompression was not successful.
	@param	infoFlags
		Contains information about the decode operation.
		The kVTDecodeInfo_Asynchronous bit may be set if the decode ran asynchronously.
		The kVTDecodeInfo_FrameDropped bit may be set if the frame was dropped.
		If the kVTDecodeInfo_ImageBufferModifiable bit is set, it is safe for the client to modify the imageBuffer.
	@param	imageBuffer
		Contains the decompressed frame, if decompression was successful; otherwise, NULL.
		IMPORTANT: The video decompressor may still be referencing the imageBuffer returned in this
		callback if the kVTDecodeInfo_ImageBufferModifiable flag is not set.  Unless this flag
		is set, it is not safe to modify the returned imageBuffer.
	@param	presentationTimeStamp
		The frame's presentation timestamp, which will be determined by calling 
		CMSampleBufferGetOutputPresentationTimeStamp; kCMTimeInvalid if not available.
	@param	presentationDuration
		The frame's presentation duration, which will be determined by calling
		CMSampleBufferGetOutputDuration; kCMTimeInvalid if not available.
*/

typedef void (*VTDecompressionOutputCallback)(
		void * CM_NULLABLE decompressionOutputRefCon,
		void * CM_NULLABLE sourceFrameRefCon,
		OSStatus status, 
		VTDecodeInfoFlags infoFlags,
		CM_NULLABLE CVImageBufferRef imageBuffer,
		CMTime presentationTimeStamp, 
		CMTime presentationDuration ) API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0));

struct VTDecompressionOutputCallbackRecord {
	CM_NULLABLE VTDecompressionOutputCallback  decompressionOutputCallback;
	void * CM_NULLABLE                         decompressionOutputRefCon;
} CM_SWIFT_NONSENDABLE API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0));
typedef struct VTDecompressionOutputCallbackRecord VTDecompressionOutputCallbackRecord CM_SWIFT_NONSENDABLE API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@function	VTDecompressionSessionCreate
	@abstract	Creates a session for decompressing video frames.
    @discussion 
		Decompressed frames will be emitted through calls to outputCallback.
	@param	allocator
		An allocator for the session.  Pass NULL to use the default allocator.
	@param	videoFormatDescription
		Describes the source video frames.
	@param	videoDecoderSpecification
		Specifies a particular video decoder that must be used.  
		Pass NULL to let the video toolbox choose a decoder.
	@param	destinationImageBufferAttributes
		Describes requirements for emitted pixel buffers.
		Pass NULL to set no requirements.
	@param	outputCallback
		The callback to be called with decompressed frames.
		Pass NULL if and only if you will be calling VTDecompressionSessionDecodeFrameWithOutputHandler for decoding frames.
	@param	decompressionSessionOut
		Points to a variable to receive the new decompression session.
	
*/
VT_EXPORT OSStatus 
VTDecompressionSessionCreate(
	CM_NULLABLE CFAllocatorRef                              allocator,
	CM_NONNULL CMVideoFormatDescriptionRef					videoFormatDescription,
	CM_NULLABLE CFDictionaryRef								videoDecoderSpecification,
	CM_NULLABLE CFDictionaryRef                             destinationImageBufferAttributes,
	const VTDecompressionOutputCallbackRecord * CM_NULLABLE outputCallback,
	CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE VTDecompressionSessionRef * CM_NONNULL decompressionSessionOut) API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);

CF_IMPLICIT_BRIDGING_ENABLED
	
/*!
	@function	VTDecompressionSessionInvalidate
	@abstract	Tears down a decompression session.
    @discussion 
    	When you are done with a decompression session you created, call VTDecompressionSessionInvalidate 
    	to tear it down and then CFRelease to release your object reference.
    	When a decompression session's retain count reaches zero, it is automatically invalidated, but 
    	since sessions may be retained by multiple parties, it can be hard to predict when this will happen.
    	Calling VTDecompressionSessionInvalidate ensures a deterministic, orderly teardown.
*/
VT_EXPORT void 
VTDecompressionSessionInvalidate( CM_NONNULL VTDecompressionSessionRef session ) API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@function VTDecompressionSessionGetTypeID
	@abstract Returns the CFTypeID for decompression sessions.  
*/
VT_EXPORT CFTypeID 
VTDecompressionSessionGetTypeID(void) API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@function	VTDecompressionSessionDecodeFrame
	@abstract	Decompresses a video frame.
	@discussion
		If an error is returned from this function, there will be no callback.  Otherwise
		the callback provided during VTDecompressionSessionCreate will be called.
	@param	session
		The decompression session.
	@param	sampleBuffer
		A CMSampleBuffer containing one or more video frames.  
	@param	decodeFlags
		A bitfield of directives to the decompression session and decoder.
		The kVTDecodeFrame_EnableAsynchronousDecompression bit indicates whether the video decoder 
		may decompress the frame asynchronously.
		The kVTDecodeFrame_EnableTemporalProcessing bit indicates whether the decoder may delay calls to the output callback
		so as to enable processing in temporal (display) order.
		If both flags are clear, the decompression shall complete and your output callback function will be called 
		before VTDecompressionSessionDecodeFrame returns.
		If either flag is set, VTDecompressionSessionDecodeFrame may return before the output callback function is called.  
	@param	sourceFrameRefCon
		Your reference value for the frame.  
		Note that if sampleBuffer contains multiple frames, the output callback function will be called
		multiple times with this sourceFrameRefCon.
	@param	infoFlagsOut
		Points to a VTDecodeInfoFlags to receive information about the decode operation.
		The kVTDecodeInfo_Asynchronous bit may be set if the decode is (or was) running
		asynchronously.
		The kVTDecodeInfo_FrameDropped bit may be set if the frame was dropped (synchronously).
		Pass NULL if you do not want to receive this information.
*/
VT_EXPORT OSStatus
VTDecompressionSessionDecodeFrame(
	CM_NONNULL VTDecompressionSessionRef	session,
	CM_NONNULL CMSampleBufferRef			sampleBuffer,
	VTDecodeFrameFlags						decodeFlags, // bit 0 is enableAsynchronousDecompression
	void * CM_NULLABLE						sourceFrameRefCon,
	VTDecodeInfoFlags * CM_NULLABLE 		infoFlagsOut) API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
	
#if __BLOCKS__
/*!
	@typedef	VTDecompressionOutputHandler
	@abstract	Prototype for block invoked when frame decompression is complete.
	@discussion
		When you decode a frame, you pass in a callback block to be called
		for that decompressed frame.  This block will not necessarily be called in display order.
		If the VTDecompressionSessionDecodeFrameWithOutputHandler call returns an error, the block
		will not be called.
	@param	status
		noErr if decompression was successful; an error code if decompression was not successful.
	@param	infoFlags
		Contains information about the decode operation.
		The kVTDecodeInfo_Asynchronous bit may be set if the decode ran asynchronously.
		The kVTDecodeInfo_FrameDropped bit may be set if the frame was dropped.
		If the kVTDecodeInfo_ImageBufferModifiable bit is set, it is safe for the client to modify the imageBuffer.
	@param	imageBuffer
		Contains the decompressed frame, if decompression was successful; otherwise, NULL.
		IMPORTANT: The video decompressor may still be referencing the imageBuffer returned in this
		callback if the kVTDecodeInfo_ImageBufferModifiable flag is not set.  Unless this flag
		is set, it is not safe to modify the returned imageBuffer.
	@param	presentationTimeStamp
		The frame's presentation timestamp; kCMTimeInvalid if not available.
	@param	presentationDuration
		The frame's presentation duration; kCMTimeInvalid if not available.
 */
typedef void (^VTDecompressionOutputHandler)(
	OSStatus status,
	VTDecodeInfoFlags infoFlags,
	CM_NULLABLE CVImageBufferRef imageBuffer,
	CMTime presentationTimeStamp,
	CMTime presentationDuration ) CM_SWIFT_SENDABLE API_AVAILABLE(macos(10.11), ios(9.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
	
/*!
	@function	VTDecompressionSessionDecodeFrameWithOutputHandler
	@abstract	Decompresses a video frame.
	@discussion
		Cannot be called with a session created with a VTDecompressionOutputCallbackRecord.
		If the VTDecompressionSessionDecodeFrameWithOutputHandler call returns an error, the block
		will not be called.
	@param	session
		The decompression session.
	@param	sampleBuffer
		A CMSampleBuffer containing one or more video frames.
	@param	decodeFlags
		A bitfield of directives to the decompression session and decoder.
		The kVTDecodeFrame_EnableAsynchronousDecompression bit indicates whether the video decoder
		may decompress the frame asynchronously.
		The kVTDecodeFrame_EnableTemporalProcessing bit indicates whether the decoder may delay calls to the output callback
		so as to enable processing in temporal (display) order.
		If both flags are clear, the decompression shall complete and your output callback function will be called
		before VTDecompressionSessionDecodeFrame returns.
		If either flag is set, VTDecompressionSessionDecodeFrame may return before the output callback function is called.
	@param	infoFlagsOut
		Points to a VTDecodeInfoFlags to receive information about the decode operation.
		The kVTDecodeInfo_Asynchronous bit may be set if the decode is (or was) running
		asynchronously.
		The kVTDecodeInfo_FrameDropped bit may be set if the frame was dropped (synchronously).
		Pass NULL if you do not want to receive this information.
	@param	outputHandler
		The block to be called when decoding the frame is completed.  If the VTDecompressionSessionDecodeFrameWithOutputHandler
		call returns an error, the block will not be called.
 */
VT_EXPORT OSStatus
VTDecompressionSessionDecodeFrameWithOutputHandler(
	CM_NONNULL VTDecompressionSessionRef	session,
	CM_NONNULL CMSampleBufferRef			sampleBuffer,
	VTDecodeFrameFlags						decodeFlags, // bit 0 is enableAsynchronousDecompression
	VTDecodeInfoFlags * CM_NULLABLE			infoFlagsOut,
	CM_NONNULL VTDecompressionOutputHandler	outputHandler ) API_AVAILABLE(macos(10.11), ios(9.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
#endif // __BLOCKS__

/*!
	@function VTDecompressionSessionFinishDelayedFrames
	@abstract Directs the decompression session to emit all delayed frames.
	@discussion
		By default, the decompression session may not delay frames indefinitely; 
		frames may only be indefinitely delayed if the client opts in via
		kVTDecodeFrame_EnableTemporalProcessing.
		IMPORTANT NOTE: This function may return before all delayed frames are emitted. 
		To wait for them, call VTDecompressionSessionWaitForAsynchronousFrames instead.
*/
VT_EXPORT OSStatus
VTDecompressionSessionFinishDelayedFrames(
	CM_NONNULL VTDecompressionSessionRef		session) API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@function VTDecompressionSessionCanAcceptFormatDescription
	@abstract Indicates whether the session can decode frames with the given format description.
	@discussion
		Some video decoders are able to accommodate minor changes in format without needing to be
		completely reset in a new session.  This function can be used to test whether a format change
		is sufficiently minor.
*/
VT_EXPORT Boolean 
VTDecompressionSessionCanAcceptFormatDescription( 
	CM_NONNULL VTDecompressionSessionRef		session,
	CM_NONNULL CMFormatDescriptionRef			newFormatDesc ) API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@function VTDecompressionSessionWaitForAsynchronousFrames
	@abstract Waits for any and all outstanding asynchronous and delayed frames to complete, then returns.
	@discussion
		This function automatically calls VTDecompressionSessionFinishDelayedFrames, 
		so clients don't have to call both.  
*/
VT_EXPORT OSStatus
VTDecompressionSessionWaitForAsynchronousFrames(
	CM_NONNULL VTDecompressionSessionRef       session) API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);

CF_IMPLICIT_BRIDGING_DISABLED
	
/*!
	@function	VTDecompressionSessionCopyBlackPixelBuffer
	@abstract	Copies a black pixel buffer from the decompression session.
    @discussion 
		The pixel buffer is in the same format that the session is decompressing to.
	@param	session
		The decompression session.
	@param	pixelBufferOut
		Points to a variable to receive the copied pixel buffer.
	
*/
VT_EXPORT OSStatus
VTDecompressionSessionCopyBlackPixelBuffer(
   CM_NONNULL VTDecompressionSessionRef			session,
   CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE CVPixelBufferRef * CM_NONNULL pixelBufferOut ) API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
	
/*!
	@function VTIsHardwareDecodeSupported
	@abstract Indicates whether the current system supports hardware decode for a given codec
	@discussion
		This routine reports whether the current system supports hardware decode.  Using
		this information, clients can make informed decisions regarding remote assets to load,
		favoring alternate encodings when hardware decode is not supported.
		This call returning true does not guarantee that hardware decode resources will be
		available at all times.
 */
VT_EXPORT Boolean
VTIsHardwareDecodeSupported( CMVideoCodecType codecType ) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), visionos(1.0)) API_UNAVAILABLE(watchos);
	
// See VTSession.h for property access APIs on VTDecompressionSessions.
// See VTDecompressionProperties.h for standard property keys and values for decompression sessions.

#pragma mark Multi-image decompression

/*!
 	@function     VTIsStereoMVHEVCDecodeSupported
 	@abstract	  Indicates whether the current system supports stereo MV-HEVC decode.
 	@discussion   This call returning true does not guarantee that decode resources will be available at all times.
 */
VT_EXPORT Boolean
VTIsStereoMVHEVCDecodeSupported( void ) API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@typedef	VTDecompressionOutputMultiImageCallback
	@abstract	Prototype for callback invoked when multi-image frame decompression is complete.
	@discussion
		When you create a decompression session, you pass in a callback function to be called
		for decompressed frames.  This function will not necessarily be called in display order.
	@param	decompressionOutputMultiImageRefCon
		The callback's reference value, copied from the outputMultiImageRefcon passed to
		VTDecompressionSessionSetMultiImageCallback.
	@param	sourceFrameRefCon
		The frame's reference value, copied from the sourceFrameRefCon argument to
		VTDecompressionSessionDecodeFrame.
	@param	status
		noErr if decompression was successful; an error code if decompression was not successful.
	@param	infoFlags
		Contains information about the decode operation.
		The kVTDecodeInfo_Asynchronous bit may be set if the decode ran asynchronously.
		The kVTDecodeInfo_FrameDropped bit may be set if the frame was dropped.
		If the kVTDecodeInfo_ImageBufferModifiable bit is set, it is safe for the client to modify the imageBuffer.
	@param	taggedBufferGroup
		Contains the decompressed frame's multiple images, if decompression was successful; otherwise, NULL.
		IMPORTANT: The video decompressor may still be referencing the pixelBuffers returned in this
		callback if the kVTDecodeInfo_ImageBufferModifiable flag is not set.  Unless this flag
		is set, it is not safe to modify the returned pixelBuffers.
	@param	presentationTimeStamp
		The frame's presentation timestamp, which will be determined by calling
		CMSampleBufferGetOutputPresentationTimeStamp; kCMTimeInvalid if not available.
	@param	presentationDuration
		The frame's presentation duration, which will be determined by calling
		CMSampleBufferGetOutputDuration; kCMTimeInvalid if not available.
*/

typedef void (*VTDecompressionOutputMultiImageCallback)(
		void * CM_NULLABLE decompressionOutputMultiImageRefCon,
		void * CM_NULLABLE sourceFrameRefCon,
		OSStatus status,
		VTDecodeInfoFlags infoFlags,
		CM_NULLABLE CMTaggedBufferGroupRef taggedBufferGroup,
		CMTime presentationTimeStamp,
		CMTime presentationDuration ) API_AVAILABLE(macos(14.0), ios(17.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function	VTDecompressionSessionSetMultiImageCallback
	@abstract	Provides a callback capable of receiving multiple images for individual DecodeFrame requests.
	@discussion
		The outputMultiImageCallback will be used when the video decoder outputs CMTaggedBufferGroups.
		When installed, outputMultiImageCallback will also be used when DecodeFrame operations fail and return a nonzero status.
		The original single-image callback will only be used in the case where the video decoder outputs a CVImageBuffer instead of a CMTaggedBufferGroup.
		Terminology note: in multi-image decompression, a single video sample (from one CMSampleBuffer) contains a single frame (with one PTS) that is decoded to produce multiple images.
*/
VT_EXPORT OSStatus
VTDecompressionSessionSetMultiImageCallback(
	CM_NONNULL VTDecompressionSessionRef				decompressionSession,
	CM_NONNULL VTDecompressionOutputMultiImageCallback	outputMultiImageCallback,
	void * CM_NULLABLE									outputMultiImageRefcon) API_AVAILABLE(macos(14.0), ios(17.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos) CF_SWIFT_UNAVAILABLE("Unavailable in Swift");

#if __BLOCKS__
/*!
	@typedef	VTDecompressionMultiImageCapableOutputHandler
	@abstract	Prototype for block invoked when frame decompression is complete.
	@discussion
		When you decode a frame, you pass in a callback block to be called
		for that decompressed frame.  This block will not necessarily be called in display order.
		If the VTDecompressionSessionDecodeFrameWithOutputHandler call returns an error, the block
		will not be called.
	@param	status
		noErr if decompression was successful; an error code if decompression was not successful.
	@param	infoFlags
		Contains information about the decode operation.
		The kVTDecodeInfo_Asynchronous bit may be set if the decode ran asynchronously.
		The kVTDecodeInfo_FrameDropped bit may be set if the frame was dropped.
		If the kVTDecodeInfo_ImageBufferModifiable bit is set, it is safe for the client to modify the imageBuffer.
	@param	imageBuffer
		Contains the decompressed frame, if decompression was successful and the CMSampleBuffer contained
		a single image frame; otherwise, NULL.
		IMPORTANT: The video decompressor may still be referencing the imageBuffer returned in this
		callback if the kVTDecodeInfo_ImageBufferModifiable flag is not set.  Unless this flag
		is set, it is not safe to modify the returned imageBuffer.
	@param	taggedBufferGroup
		Contains the decompressed frame's multiple images, if decompression was successful and the CMSampleBuffer
		contained a multi-image frame; otherwise, NULL.
		IMPORTANT: The video decompressor may still be referencing the pixelBuffers returned in this
		callback if the kVTDecodeInfo_ImageBufferModifiable flag is not set.  Unless this flag
		is set, it is not safe to modify the returned pixelBuffers.
	@param	presentationTimeStamp
		The frame's presentation timestamp; kCMTimeInvalid if not available.
	@param	presentationDuration
		The frame's presentation duration; kCMTimeInvalid if not available.
 */
typedef void (^VTDecompressionMultiImageCapableOutputHandler)(
	OSStatus status,
	VTDecodeInfoFlags infoFlags,
	CM_NULLABLE CVImageBufferRef imageBuffer,
	CM_NULLABLE CMTaggedBufferGroupRef taggedBufferGroup,
	CMTime presentationTimeStamp,
	CMTime presentationDuration ) CM_SWIFT_SENDABLE API_AVAILABLE(macos(14.0), ios(17.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function	VTDecompressionSessionDecodeFrameWithMultiImageCapableOutputHandler
	@abstract	Decompresses a video frame.
	@discussion
		Cannot be called with a session created with a VTDecompressionOutputCallbackRecord.
		If the VTDecompressionSessionDecodeFrameWithOutputHandler call returns an error, the block
		will not be called.
	@param	session
		The decompression session.
	@param	sampleBuffer
		A CMSampleBuffer containing one or more video frames.
	@param	decodeFlags
		A bitfield of directives to the decompression session and decoder.
		The kVTDecodeFrame_EnableAsynchronousDecompression bit indicates whether the video decoder
		may decompress the frame asynchronously.
		The kVTDecodeFrame_EnableTemporalProcessing bit indicates whether the decoder may delay calls to the output callback
		so as to enable processing in temporal (display) order.
		If both flags are clear, the decompression shall complete and your output callback function will be called
		before VTDecompressionSessionDecodeFrame returns.
		If either flag is set, VTDecompressionSessionDecodeFrame may return before the output callback function is called.
	@param	infoFlagsOut
		Points to a VTDecodeInfoFlags to receive information about the decode operation.
		The kVTDecodeInfo_Asynchronous bit may be set if the decode is (or was) running
		asynchronously.
		The kVTDecodeInfo_FrameDropped bit may be set if the frame was dropped (synchronously).
		Pass NULL if you do not want to receive this information.
	@param	multiImageCapableOutputHandler
		The block to be called when decoding the frame is completed.  If the
		VTDecompressionSessionDecodeFrameWithMultiImageCapableOutputHandler call returns an error,
		the block will not be called.
 */
VT_EXPORT OSStatus
VTDecompressionSessionDecodeFrameWithMultiImageCapableOutputHandler(
	CM_NONNULL VTDecompressionSessionRef		session,
	CM_NONNULL CMSampleBufferRef				sampleBuffer,
	VTDecodeFrameFlags							decodeFlags, // bit 0 is enableAsynchronousDecompression
	VTDecodeInfoFlags * CM_NULLABLE				infoFlagsOut,
	CM_NONNULL VTDecompressionMultiImageCapableOutputHandler	multiImageCapableOutputHandler )  API_AVAILABLE(macos(14.0), ios(17.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos) CF_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/*!
	@function	VTDecompressionSessionDecodeFrameWithOptions
	@abstract	Decompresses a video frame.
	@discussion
		If an error is returned from this function, there will be no callback.  Otherwise
		the callback provided during VTDecompressionSessionCreate will be called.
	@param	session
		The decompression session.
	@param	sampleBuffer
		A CMSampleBuffer containing one or more video frames.
	@param	decodeFlags
		A bitfield of directives to the decompression session and decoder.
		The kVTDecodeFrame_EnableAsynchronousDecompression bit indicates whether the video decoder
		may decompress the frame asynchronously.
		The kVTDecodeFrame_EnableTemporalProcessing bit indicates whether the decoder may delay calls to the output callback
		so as to enable processing in temporal (display) order.
		If both flags are clear, the decompression shall complete and your output callback function will be called
		before VTDecompressionSessionDecodeFrameWithOptions returns.
		If either flag is set, VTDecompressionSessionDecodeFrameWithOptions may return before the output callback function is called.
	@param	frameOptions
		Contains key/value pairs specifying additional options for decoding this frame.
		Only keys with `kVTDecodeFrameOptionKey_` prefix should be used in this dictionary.
	@param	sourceFrameRefCon
		Your reference value for the frame.
		Note that if sampleBuffer contains multiple frames, the output callback function will be called
		multiple times with this sourceFrameRefCon.
	@param	infoFlagsOut
		Points to a VTDecodeInfoFlags to receive information about the decode operation.
		The kVTDecodeInfo_Asynchronous bit may be set if the decode is (or was) running
		asynchronously.
		The kVTDecodeInfo_FrameDropped bit may be set if the frame was dropped (synchronously).
		Pass NULL if you do not want to receive this information.
*/
VT_EXPORT OSStatus
VTDecompressionSessionDecodeFrameWithOptions(
	CM_NONNULL VTDecompressionSessionRef	session,
	CM_NONNULL CMSampleBufferRef			sampleBuffer,
	VTDecodeFrameFlags						decodeFlags, // bit 0 is enableAsynchronousDecompression
	CM_NULLABLE CFDictionaryRef				frameOptions,
	void * CM_NULLABLE						sourceFrameRefCon,
	VTDecodeInfoFlags * CM_NULLABLE 		infoFlagsOut) API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

#if __BLOCKS__
/*!
	@function	VTDecompressionSessionDecodeFrameWithOptionsAndOutputHandler
	@abstract	Decompresses a video frame.
	@discussion
		Cannot be called with a session created with a VTDecompressionOutputCallbackRecord.
		If the VTDecompressionSessionDecodeFrameWithOptionsAndOutputHandler call returns an error,
		the block will not be called.
	@param	session
		The decompression session.
	@param	sampleBuffer
		A CMSampleBuffer containing one or more video frames.
	@param	decodeFlags
		A bitfield of directives to the decompression session and decoder.
		The kVTDecodeFrame_EnableAsynchronousDecompression bit indicates whether the video decoder
		may decompress the frame asynchronously.
		The kVTDecodeFrame_EnableTemporalProcessing bit indicates whether the decoder may delay calls to the output callback
		so as to enable processing in temporal (display) order.
		If both flags are clear, the decompression shall complete and your output callback function will be called
		before VTDecompressionSessionDecodeFrameWithOptionsAndOutputHandler returns.
		If either flag is set, VTDecompressionSessionDecodeFrameWithOptionsAndOutputHandler may return before the output
		callback function is called.
	@param	frameOptions
		Contains key/value pairs specifying additional options for decoding this frame.
		Only keys with `kVTDecodeFrameOptionKey_` prefix should be used in this dictionary.
	@param	infoFlagsOut
		Points to a VTDecodeInfoFlags to receive information about the decode operation.
		The kVTDecodeInfo_Asynchronous bit may be set if the decode is (or was) running
		asynchronously.
		The kVTDecodeInfo_FrameDropped bit may be set if the frame was dropped (synchronously).
		Pass NULL if you do not want to receive this information.
	@param	outputHandler
		The block to be called when decoding the frame is completed.  If the VTDecompressionSessionDecodeFrameWithOptionsAndOutputHandler
		call returns an error, the block will not be called.
 */
VT_EXPORT OSStatus
VTDecompressionSessionDecodeFrameWithOptionsAndOutputHandler(
	CM_NONNULL VTDecompressionSessionRef	session,
	CM_NONNULL CMSampleBufferRef			sampleBuffer,
	VTDecodeFrameFlags						decodeFlags, // bit 0 is enableAsynchronousDecompression
	CM_NULLABLE CFDictionaryRef				frameOptions,
	VTDecodeInfoFlags * CM_NULLABLE			infoFlagsOut,
	CM_NONNULL VTDecompressionOutputHandler	outputHandler ) API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);
#endif // __BLOCKS__

#pragma pack(pop)

#if defined(__cplusplus)
}
#endif


#endif // VTDECOMPRESSIONSESSION_H
