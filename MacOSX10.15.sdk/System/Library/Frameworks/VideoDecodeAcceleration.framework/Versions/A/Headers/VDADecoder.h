/*
 *  VDADecoder.h
 *
 *  Copyright 2009 Apple Inc. All rights reserved.
 *
 */ 

/*
  VideoDecodeAcceleration.framework has been deprecated in 10.11.

  The full functionality of VideoDecodeAcceleration.framework is available through VideoToolbox.framework.
  Hardware accelerated decode can be achieved using the VTDecompressionSession interface and specifying
  the kVTVideoDecoderSpecification_EnableHardwareAcceleratedVideoDecoder key or the 
  kVTVideoDecoderSpecification_RequireHardwareAcceleratedVideoDecoder key.
*/


#ifndef VDADECODER_H
#define VDADECODER_H

#include <CoreFoundation/CoreFoundation.h>
#include <CoreVideo/CoreVideo.h>
#include <AvailabilityMacros.h>
#include <Availability.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)

/*!
	 @enum VDADecoder Errors
	 @discussion The errors returned from the VDADecoder APIs
	 @constant	kCMBlockBufferNoErr Success
	 @constant	kVDADecoderHardwareNotSupportedErr the hardware doesnt support accelerated video services
	 @constant	kVDADecoderFormatNotSupportedErr the hardware may support accelerated decode, but not this format
	 @constant	kVDADecoderConfigurationError invalid or unsupported configuration parameters were specified
	 @constant	kVDADecoderDecoderFailedErr an error was returned by the decoder layer
*/
enum {
	kVDADecoderNoErr					= 0,
	kVDADecoderHardwareNotSupportedErr	= -12470,		
	kVDADecoderFormatNotSupportedErr	= -12471,
	kVDADecoderConfigurationError		= -12472,
	kVDADecoderDecoderFailedErr			= -12473,
	kVDADecoderParamErr			= -12474,
	kVDADecoderAllocationFailedErr	= -12475,
};

/*!
	@typedef	VDADecoder
	@abstract	A reference to a video decoder object
	@discussion
		A simple hardware decoder object providing an interface to
	utilize hardware resources for accelerated video decode.
 */
typedef struct OpaqueVDADecoder*  VDADecoder;


/*!
	@typedef	VDADecoderOutputCallback
    @abstract   Prototype for callback invoked when frame decode is complete.
    @discussion 
		When you create a VDADecoder object, you pass in a callback function to be used in order 
		to return decompressed frames.  This function may be called in decode order rather than presentation
		order.
	@param	decompressionOutputRefCon
		The decompressor objects callback reference value as passed into VDADecoderCreate
	@param	frameInfo
		The frameInfo passed into the VDADecoderDecode call for this frame.  This will be released
		after returning from this call, so retain it if you need it beyond this point.
	@param	status
		noErr if decompression was successful; an error code if decompression was not successful.
	@param	infoFlags
		Contains information about the decode operation.
		The kDecodeInfo_FrameDropped bit may be set if the frame was dropped.
	@param	imageBuffer
		Contains the decoded frame, if the decode operation was successful.  Otherwise, NULL.
*/
typedef void (*VDADecoderOutputCallback)(
		void 				*decompressionOutputRefCon, 
		CFDictionaryRef 	frameInfo, 
		OSStatus 			status, 
		uint32_t 			infoFlags,
		CVImageBufferRef 	imageBuffer );

//decoderConfiguration keys
extern const CFStringRef kVDADecoderConfiguration_Height;		// CFNumber
extern const CFStringRef kVDADecoderConfiguration_Width;		// CFNumber
extern const CFStringRef kVDADecoderConfiguration_SourceFormat;	// CFNumber - SInt32, FourCharacterCode for format
extern const CFStringRef kVDADecoderConfiguration_avcCData;		// avc1 decoder configuration data

/*!
	@function	VDADecoderCreate
	@abstract	Creates an interface for utilizing hardware resources to decode video.
    @discussion 
    	Returns an error if hardware doesn't exist to decode the provided format or
    	if there are insufficient hardware resources to decode currently.
		Decoded frames will be emitted through calls to outputCallback.
	@param	decoderConfiguration
		a CFDictionary describing the source data and configuration for the desired decoder
	@param	destinationImageBufferAttributes
		Describes requirements for emitted pixel buffers.
		Pass NULL to set no requirements.
	@param	outputCallback
		The callback to be called with decompressed frames.
	@param	decoderOutputCallbackRefcon
		The refCon to be passed to the outputCallback for all frames from this decoderObject
	@param	decoderOut
		Points to a variable to receive the new decoder object.
	
*/
OSStatus VDADecoderCreate( 
	CFDictionaryRef							decoderConfiguration, 
	CFDictionaryRef							destinationImageBufferAttributes,         /* can be NULL */
	VDADecoderOutputCallback				*outputCallback, 
	void 									*decoderOutputCallbackRefcon,
	VDADecoder								*decoderOut )   DEPRECATED_IN_MAC_OS_X_VERSION_10_11_AND_LATER;

// decodeFlags
enum {
	kVDADecoderDecodeFlags_DontEmitFrame = 		1 << 0 	// tells the decoder not to bother returning
															// a CVPixelBuffer in the outputCallback. The
															// output callback will still be called.
};

/*!
	@function	VDADecoderDecode
	@abstract	pass compressed data to hw decoder interface to be decoded
    @discussion 
    	Send the included compressed data to the hardware decoder
	@param	decoder
		the hardware decoder interface to do the decoding
	@param	decodeFlags
		flags field with any special requests for this decode operation 
	@param	compressedBuffer
		CFDataRef contianing the compressed buffer to be decoded
	@param	frameInfo
		a CFDictionary containing information to be returned in the outputCallback for this frame.  This can contain
		client information associated with this frame, including presentation time.  This will be retained.
*/
OSStatus VDADecoderDecode( 
	VDADecoder							decoder, 
	uint32_t								decodeFlags,
	CFTypeRef 								compressedBuffer, 
	CFDictionaryRef 						frameInfo /* can be NULL */ ) DEPRECATED_IN_MAC_OS_X_VERSION_10_11_AND_LATER;

// FlushDecoder flags
enum {
	kVDADecoderFlush_EmitFrames = 	1 << 0		// decode and return buffers for all frames currently in flight
};

/*!
	@function	VDADecoderFlush
	@abstract	flush all frames currently in flight in the decoder
    @discussion 
    	This call cancels all frames currently queued in the decoder which have not yet been completed
    	and returned on the outputCallback.  Note that the decoder is generally running asynchronously
    	so there is the possibility of a frame completing while this call is being made, but none should
    	be returned after control returns from this call.  The output callback will still be
    	called for all frames, but no CVImageBufferRef will be returned, and a frameFlushed indicator will
    	will be set in the status field.
    	If the kVDADecoderFlush_emitFrames flag is specified, the flush will return CVImageBuffers
    	in the callback.
	@param	decoder
		the hardware decoder interface to flush
	@param	flushFlags
		flags to control flush behavior, such as whether decodes in flight will be completed or not
*/
OSStatus VDADecoderFlush( 
	VDADecoder							decoder, 
	uint32_t 								flushFlags )    DEPRECATED_IN_MAC_OS_X_VERSION_10_11_AND_LATER;

/*!
	@function	VDADestroyDecoder
	@abstract	release the decoder object
    @discussion 
    	This call frees the decoder object and releases all resources currently in use in the decoder.
    	Internally it will flush currently queued frames without calling the output callback.  Previously
    	emitted CVImageBuffers still need to be released by the client if they have been retained.
	@param	decoder
		the hardware decoder interface that you are destroying.  This should not be referenced any longer
		after the destroy call.
*/
OSStatus VDADecoderDestroy( VDADecoder decoder )    DEPRECATED_IN_MAC_OS_X_VERSION_10_11_AND_LATER;

#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif // VDADECODER_H
