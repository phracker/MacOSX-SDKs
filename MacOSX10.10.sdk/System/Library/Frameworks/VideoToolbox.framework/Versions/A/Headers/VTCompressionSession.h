/*
	File:  VTCompressionSession.h
	
	Framework:  VideoToolbox
	
	Copyright 2006-2013 Apple Inc. All rights reserved.
	
	Video Toolbox client API for compressing video frames.
	
	Compression sessions convert uncompressed frames in CVImageBuffers 
	into compressed video frames in CMSampleBuffers.
*/

#ifndef VTCOMPRESSIONSESSION_H
#define VTCOMPRESSIONSESSION_H

#include <CoreMedia/CMBase.h>
#include <VideoToolbox/VTBase.h>

#include <CoreFoundation/CoreFoundation.h>
#include <CoreVideo/CoreVideo.h>
#include <CoreMedia/CMSampleBuffer.h>
#include <CoreMedia/CMFormatDescription.h>
#include <CoreMedia/CMTime.h>
#include <CoreMedia/CMTimeRange.h>

#include <VideoToolbox/VTSession.h>
#include <VideoToolbox/VTCompressionProperties.h>

#include <VideoToolbox/VTErrors.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)
	
CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@typedef	VTCompressionSessionRef
	@abstract	A reference to a Video Toolbox Compression Session.
	@discussion
		A compression session supports the compression of a sequence of video frames.
		The session reference is a reference-counted CF object.
		To create a compression session, call VTCompressionSessionCreate; 
		then you can optionally configure the session using VTSessionSetProperty;
		then to encode frames, call VTCompressionSessionEncodeFrame.
		To force completion of some or all pending frames, call VTCompressionSessionCompleteFrames.
		When you are done with the session, you should call VTCompressionSessionInvalidate
		to tear it down and CFRelease to release your object reference.
 */

typedef struct OpaqueVTCompressionSession*  VTCompressionSessionRef;

/*!
	@typedef	VTCompressionOutputCallback
    @abstract   Prototype for callback invoked when frame compression is complete.
    @discussion 
		When you create a compression session, you pass in a callback function to be called 
		for compressed frames.  This function will be called in decode order (which is not
		necessarily the same as display order).
	@param	outputCallbackRefCon
		The callback's reference value.
	@param	sourceFrameRefCon
		The frame's reference value, copied from the sourceFrameRefCon argument to 
		VTCompressionSessionEncodeFrame.
	@param	status
		noErr if compression was successful; an error code if compression was not successful.
	@param	infoFlags
		Contains information about the encode operation.
		The kVTEncodeInfo_Asynchronous bit may be set if the encode ran asynchronously.
		The kVTEncodeInfo_FrameDropped bit may be set if the frame was dropped.
	@param	sampleBuffer
		Contains the compressed frame, if compression was successful and the frame was not dropped; 
		otherwise, NULL.
*/

typedef void (*VTCompressionOutputCallback)(
		void *outputCallbackRefCon, 
		void *sourceFrameRefCon, 
		OSStatus status, 
		VTEncodeInfoFlags infoFlags,
		CMSampleBufferRef sampleBuffer );
		
/*!
	@constant	kVTVideoEncoderSpecification_EncoderID
	@abstract
		Specifies a particular video encoder by its ID string.
	@discussion
		To specify a particular video encoder when creating a compression session, pass an 
		encoderSpecification CFDictionary containing this key and the EncoderID as its value.
		The EncoderID CFString may be obtained from the kVTVideoEncoderList_EncoderID entry in
		the array returned by VTCopyVideoEncoderList.
*/
VT_EXPORT const CFStringRef kVTVideoEncoderSpecification_EncoderID __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_8_0); // CFString

CF_IMPLICIT_BRIDGING_DISABLED
	
/*!
	@function	VTCompressionSessionCreate
	@abstract	Creates a session for compressing video frames.
    @discussion 
		Compressed frames will be emitted through calls to outputCallback.
	@param	allocator
		An allocator for the session.  Pass NULL to use the default allocator.
	@param	width
		The width of frames, in pixels.  
		If the video encoder cannot support the provided width and height it may change them.
	@param	height
		The height of frames in pixels.
	@param	cType
		The codec type.
	@param	encoderSpecification
		Specifies a particular video encoder that must be used.  
		Pass NULL to let the video toolbox choose a encoder.
	@param	sourceImageBufferAttributes
		Required attributes for source pixel buffers, used when creating a pixel buffer pool 
		for source frames.  If you do not want the Video Toolbox to create one for you, pass NULL.
		(Using pixel buffers not allocated by the Video Toolbox may increase the chance that
		it will be necessary to copy image data.)
	@param	compressedDataAllocator
		An allocator for the compressed data.  Pass NULL to use the default allocator.
	@param	outputCallback
		The callback to be called with compressed frames.
		This function may be called asynchronously, on a different thread from the one that calls VTCompressionSessionEncodeFrame.
	@param	outputCallbackRefCon
		Client-defined reference value for the output callback.
	@param	compressionSessionOut
		Points to a variable to receive the new compression session.
	
*/
VT_EXPORT OSStatus 
VTCompressionSessionCreate(
	CFAllocatorRef                              allocator,                  /* can be NULL */
	int32_t										width,
	int32_t										height,
	CMVideoCodecType							codecType,
	CFDictionaryRef								encoderSpecification,       /* can be NULL */
	CFDictionaryRef                             sourceImageBufferAttributes,/* can be NULL */
	CFAllocatorRef								compressedDataAllocator,	/* can be NULL */
	VTCompressionOutputCallback					outputCallback,
	void *										outputCallbackRefCon,
	VTCompressionSessionRef *					compressionSessionOut) __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_8_0);

CF_IMPLICIT_BRIDGING_ENABLED
	
/*!
	@function	VTCompressionSessionInvalidate
	@abstract	Tears down a compression session.
    @discussion 
    	When you are done with a compression session you created, call VTCompressionSessionInvalidate 
    	to tear it down and then CFRelease to release your object reference.
    	When a compression session's retain count reaches zero, it is automatically invalidated, but 
    	since sessions may be retained by multiple parties, it can be hard to predict when this will happen.
    	Calling VTCompressionSessionInvalidate ensures a deterministic, orderly teardown.
*/
VT_EXPORT void 
VTCompressionSessionInvalidate( VTCompressionSessionRef session ) __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_8_0);

/*!
	@function VTCompressionSessionGetTypeID
	@abstract Returns the CFTypeID for compression sessions.  
*/
VT_EXPORT CFTypeID 
VTCompressionSessionGetTypeID(void) __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_8_0);

/*!
	@function	VTCompressionSessionGetPixelBufferPool
	@abstract	Returns a pool that can provide ideal source pixel buffers for a compression session.
	@discussion
		The compression session creates this pixel buffer pool based on
		the compressor's pixel buffer attributes and any pixel buffer
		attributes passed in to VTCompressionSessionCreate.  If the
		source pixel buffer attributes and the compressor pixel buffer
		attributes cannot be reconciled, the pool is based on the source
		pixel buffer attributes and the Video Toolbox converts each CVImageBuffer
		internally.
		<BR>
		While clients can call VTCompressionSessionGetPixelBufferPool once
		and retain the resulting pool, the call is cheap enough that it's OK 
		to call it once per frame.  If a change of session properties causes 
		the compressor's pixel buffer attributes to change, it's possible that
		VTCompressionSessionGetPixelBufferPool might return a different pool.
*/
VT_EXPORT CVPixelBufferPoolRef 
VTCompressionSessionGetPixelBufferPool(
	VTCompressionSessionRef		session ) __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_8_0);

/*!
	@function	VTCompressionSessionPrepareToEncodeFrames
	@abstract
		You can optionally call this function to provide the encoder with an opportunity to perform
		any necessary resource allocation before it begins encoding frames.
	@discussion
		This optional call can be used to provide the encoder an opportunity to allocate
		any resources necessary before it begins encoding frames.  If this isn't called, any
		necessary resources will be allocated on the first VTCompressionSessionEncodeFrame call.
		Extra calls to this function will have no effect.
	@param	session
		The compression session.
*/
VT_EXPORT OSStatus
VTCompressionSessionPrepareToEncodeFrames( VTCompressionSessionRef session ) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_8_0);
	
/*!
	@function	VTCompressionSessionEncodeFrame
	@abstract
		Call this function to present frames to the compression session.
		Encoded frames may or may not be output before the function returns.
	@discussion
		The client should not modify the pixel data after making this call.
		The session and/or encoder will retain the image buffer as long as necessary. 
	@param	session
		The compression session.
	@param	imageBuffer
		A CVImageBuffer containing a video frame to be compressed.  
		Must have a nonzero reference count.
	@param	presentationTimeStamp
		The presentation timestamp for this frame, to be attached to the sample buffer.
		Each presentation timestamp passed to a session must be greater than the previous one.
	@param	duration
		The presentation duration for this frame, to be attached to the sample buffer.  
		If you do not have duration information, pass kCMTimeInvalid.
	@param	frameProperties
		Contains key/value pairs specifying additional properties for encoding this frame.
		Note that some session properties may also be changed between frames.
		Such changes have effect on subsequently encoded frames.
	@param	sourceFrameRefCon
		Your reference value for the frame, which will be passed to the output callback function.
	@param	infoFlagsOut
		Points to a VTEncodeInfoFlags to receive information about the encode operation.
		The kVTEncodeInfo_Asynchronous bit may be set if the encode is (or was) running
		asynchronously.
		The kVTEncodeInfo_FrameDropped bit may be set if the frame was dropped (synchronously).
		Pass NULL if you do not want to receive this information.
*/
VT_EXPORT OSStatus
VTCompressionSessionEncodeFrame(
	VTCompressionSessionRef		session,
	CVImageBufferRef			imageBuffer, 
	CMTime						presentationTimeStamp,
	CMTime						duration, // may be kCMTimeInvalid
	CFDictionaryRef				frameProperties, // may be NULL
	void *						sourceFrameRefCon,
	VTEncodeInfoFlags			*infoFlagsOut /* may be NULL */ ) __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_8_0);

/*!
	@function VTCompressionSessionCompleteFrames
	@abstract Forces the compression session to complete encoding frames.
	@discussion
		If completeUntilPresentationTimeStamp is numeric, frames with presentation timestamps
		up to and including this timestamp will be emitted before the function returns.
		If completeUntilPresentationTimeStamp is non-numeric, all pending frames
		will be emitted before the function returns.
*/
VT_EXPORT OSStatus
VTCompressionSessionCompleteFrames(
	VTCompressionSessionRef		session,
	CMTime						completeUntilPresentationTimeStamp) __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_8_0); // complete all frames if non-numeric
	
#pragma mark Multi-pass
	
/*
	When multi-pass encoding has been enabled by setting kVTCompressionPropertyKey_MultiPassStorage, you must call VTCompressionSessionBeginPass before each pass in which you call VTCompressionSessionEncodeFrame for source frames; you must call VTCompressionSessionEndPass to end each pass; and in each pass you must pass an identical sequence of source frames, frame properties and timestamps (except that source frames outside a pass' time ranges should be skipped).  See kVTCompressionPropertyKey_MultiPassStorage for additional rules and guidance.
*/
	
	
typedef CF_OPTIONS(uint32_t, VTCompressionSessionOptionFlags) {
	kVTCompressionSessionBeginFinalPass = 1<<0
};

/*!
	@function	VTCompressionSessionBeginPass
	@abstract	Call to announce the start of a specific compression pass.
	@discussion
		During multi-pass encoding, this function must be called before VTCompressionSessionEncodeFrame.
		It is an error to call this function when multi-pass encoding has not been enabled by setting kVTCompressionPropertyKey_MultiPassStorage.
	@param	beginPassFlags
		Pass kVTCompressionSessionBeginFinalPass to inform the encoder that the pass must be the final pass.
*/
VT_EXPORT OSStatus
VTCompressionSessionBeginPass(
	VTCompressionSessionRef			session,
	VTCompressionSessionOptionFlags	beginPassFlags,
	uint32_t						*reserved /* pass NULL */ ) __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
	
/*!
	@function	VTCompressionSessionEndPass
	@abstract	Call to announce the end of a pass.
	@discussion
		VTCompressionSessionEndPass can take a long time, since the video encoder may perform significant processing between passes.
		VTCompressionSessionEndPass will indicate via the furtherPassesRequestedOut argument whether the video encoder would like to perform another pass.  There is no particular bound on the number of passes the video encoder may request, but the client is free to disregard this request and use the last-emitted set of frames.
		It is an error to call this function when multi-pass encoding has not been enabled by setting kVTCompressionPropertyKey_MultiPassStorage.
	@param furtherPassesRequestedOut
		Points to a Boolean that will be set to true if the video encoder would like to perform another pass, false otherwise.
		You may pass NULL to indicate that the client is certain to use this as the final pass, in which case the video encoder can skip that evaluation step.
*/
VT_EXPORT OSStatus
VTCompressionSessionEndPass(
	VTCompressionSessionRef		session,
	Boolean						*furtherPassesRequestedOut,
	uint32_t					*reserved /* pass NULL */ ) __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
	
/*!
	 @function	VTCompressionSessionGetTimeRangesForNextPass
	 @abstract	Retrieves the time ranges for the next pass.
	 @discussion
		If VTCompressionSessionEndPass sets *furtherPassesRequestedOut to true, call VTCompressionSessionGetTimeRangesForNextPass to find out the time ranges for the next pass.  Source frames outside these time ranges should be skipped.
		Each time range is considered to include any frame at its start time and not to include any frame at its end time.
		It is an error to call this function when multi-pass encoding has not been enabled by setting kVTCompressionPropertyKey_MultiPassStorage, or when VTCompressionSessionEndPass did not set *furtherPassesRequestedOut to true.
	 @param timeRangeCountOut
		Points to a CMItemCount to receive the number of CMTimeRanges.
	 @param timeRangeArrayOut
		Points to a const CMTimeRange * to receive a pointer to a C array of CMTimeRanges.
		The storage for this array belongs to the VTCompressionSession and should not be modified.
		The pointer will be valid until the next call to VTCompressionSessionEndPass, or until the VTCompressionSession is invalidated or finalized.
*/
VT_EXPORT OSStatus
VTCompressionSessionGetTimeRangesForNextPass(
	VTCompressionSessionRef		session,
	CMItemCount *				timeRangeCountOut,
	const CMTimeRange **		timeRangeArrayOut ) __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0); /* returned pointer will be valid until next call to VTCompressionSessionEndPass */

// See VTSession.h for property access APIs on VTCompressionSessions.
// See VTCompressionProperties.h for standard property keys and values for compression sessions.
	
CF_IMPLICIT_BRIDGING_DISABLED

#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif // VTCOMPRESSIONSESSION_H
