/*
	File:  VTDecompressionProperties.h
	
	Framework:  VideoToolbox
 
    Copyright 2007-2012 Apple Inc. All rights reserved.
  
	Standard Video Toolbox decompression properties.
*/

#ifndef VTDECOMPRESSIONPROPERTIES_H
#define VTDECOMPRESSIONPROPERTIES_H

#include <CoreMedia/CMBase.h>

#include <CoreFoundation/CoreFoundation.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)

/*!
	@header
	@abstract
		Standard Video Toolbox decompression properties
		
	@discussion
		This file defines standard properties used to describe and configure decompression 
		operations managed by the video toolbox.  
		
		The video toolbox will provide direct support for some of these properties.
		Some properties are supported by individual decoders.
		
		Clients can query supported properties by calling VTSessionCopySupportedPropertyDictionary.
*/

#pragma mark Pixel buffer pools

// Standard properties regarding buffer recycling.  
// These are implemented by the video toolbox.

/*!
	@constant	kVTDecompressionPropertyKey_PixelBufferPool
	@abstract
		A pixel buffer pool for pixel buffers being output by the decompression session.
	@discussion
		This pixel buffer pool is always compatible with the client's pixel buffer attributes
		as specified when calling VTDecompressionSessionCreate.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_PixelBufferPool AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER; // Read-only, CVPixelBufferPool

/*!
	@constant	kVTDecompressionPropertyKey_PixelBufferPoolIsShared
	@abstract
		Indicates whether a common pixel buffer pool is shared between
		the video decoder and the session client. 
	@discussion
		This is false if separate pools are used because the pixel buffer attributes specified 
		by the video decoder and the client were incompatible.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_PixelBufferPoolIsShared AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER; // Read-only, CFBoolean

#pragma mark Asynchronous state

// Standard properties regarding asynchronous state.  
// These are implemented by the video toolbox.

/*!
	@constant	kVTDecompressionPropertyKey_NumberOfFramesBeingDecoded
	@abstract
		Returns the number of frames currently being decoded.
	@discussion
		This number may decrease asynchronously as frames are output.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_NumberOfFramesBeingDecoded AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER; // Read-only, CFNumber. 

/*!
	@constant	kVTDecompressionPropertyKey_MinOutputPresentationTimeStampOfFramesBeingDecoded
	@abstract
		The minimum output presentation timestamp of the frames currently being decoded.
	@discussion
		This may change asynchronously as frames are output.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_MinOutputPresentationTimeStampOfFramesBeingDecoded AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER; // Read-only, CMTime as CFDictionary.  

/*!
	@constant	kVTDecompressionPropertyKey_MaxOutputPresentationTimeStampOfFramesBeingDecoded
	@abstract
		The maximum output presentation timestamp of the frames currently being decoded.
	@discussion
		This may change asynchronously as frames are output.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_MaxOutputPresentationTimeStampOfFramesBeingDecoded AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER; // Read-only, CMTime as CFDictionary.  
	
#pragma mark Content

// Standard properties describing content.
// Video decoders may optionally report these.

/*!
	@constant	kVTDecompressionPropertyKey_ContentHasInterframeDependencies
	@abstract
		Indicates whether the content being decoded has interframe dependencies, if the decoder knows.
	@discussion
		This is an optional property for video decoders to implement.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_ContentHasInterframeDependencies AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER; // Read-only, CFBoolean

#pragma mark Decoder behavior

// Standard properties regarding decoder behavior.
// Video decoders may report optionally report these.

/*!
	@constant	kVTDecompressionPropertyKey_ThreadCount
	@abstract
		Gets number of threads used by codec or suggests number of threads to use.
	@discussion
		This is an optional property for video decoders to implement.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_ThreadCount AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER; // Read/write, CFNumber

// Standard properties about quality of service.
// By default, a decoder should completely decode every frame at full resolution.
// A decoder may support properties to modify the quality of service, using these keys and/or custom keys.

/*!
	@constant	kVTDecompressionPropertyKey_FieldMode
	@abstract
		Requests special handling of interlaced content.  
	@discussion
		This is an optional property for video decoders to implement.
		Decoders should only accept the modes that they will implement.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_FieldMode AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER; // Read/write, CFString, one of
VT_EXPORT const CFStringRef kVTDecompressionProperty_FieldMode_BothFields AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER;
VT_EXPORT const CFStringRef kVTDecompressionProperty_FieldMode_TopFieldOnly AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER;
VT_EXPORT const CFStringRef kVTDecompressionProperty_FieldMode_BottomFieldOnly AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER;
VT_EXPORT const CFStringRef kVTDecompressionProperty_FieldMode_SingleField AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER;  // Most appropriate of either TopFieldOnly or BottomFieldOnly
VT_EXPORT const CFStringRef kVTDecompressionProperty_FieldMode_DeinterlaceFields AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER;

/*!
	@constant	kVTDecompressionPropertyKey_DeinterlaceMode
	@abstract
		Requests a specific deinterlacing technique.  
	@discussion
		This is an optional property for video decoders to implement.
		Decoders should only accept the modes that they will implement.
		This property is only applicable if kVTDecompressionPropertyKey_FieldMode 
		is set to kVTDecompressionProperty_FieldMode_DeinterlaceFields.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_DeinterlaceMode AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER;   // Read/write, CFString; only applicable if kVTDecompressionPropertyKey_FieldMode is kVTDecompressionProperty_FieldMode_DeinterlaceFields; supported values may include:
VT_EXPORT const CFStringRef kVTDecompressionProperty_DeinterlaceMode_VerticalFilter AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER;   // apply 0.25-0.50-0.25 vertical filter to individual interlaced frames; default mode
VT_EXPORT const CFStringRef kVTDecompressionProperty_DeinterlaceMode_Temporal AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER;	// apply filter that makes use of a window of multiple frames to generate deinterlaced results, and provides a better result at the expense of a pipeline delay; this mode is only used if kVTDecodeFrame_EnableTemporalProcessing is set, otherwise a non-temporal mode (eg, VerticalFilter) will be used instead

/*!
	@constant	kVTDecompressionPropertyKey_ReducedResolutionDecode
	@abstract
		Requests decoding at a smaller resolution than full-size.  
	@discussion
		This is an optional property for video decoders to implement.
		Decoders that only support a fixed set of resolutions should pick the smallest resolution 
		greater than or equal to the requested width x height.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_ReducedResolutionDecode AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER; // Read/write, CFDictionary containing width and height keys and CFNumber values:
VT_EXPORT const CFStringRef kVTDecompressionResolutionKey_Width AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER; // CFNumber
VT_EXPORT const CFStringRef kVTDecompressionResolutionKey_Height AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER; // CFNumber

/*!
	@constant	kVTDecompressionPropertyKey_ReducedCoefficientDecode
	@abstract
		Requests approximation during decoding.  
	@discussion
		This is an optional property for video decoders to implement.
		Only decoders for which such approximations make sense should implement this property.
		The meaning of the number of coefficients will be decoder-specific.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_ReducedCoefficientDecode AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER; // Read/write, CFNumber

/*!
	@constant	kVTDecompressionPropertyKey_ReducedFrameDelivery
	@abstract
		Requests frame dropping.
	@discussion
		This is an optional property for video decoders to implement.
		This number is a fraction between 0.0 and 1.0 that indicates what proportion of frames 
		should be delivered -- others may be dropped.  
		For example, 0.25 would indicate that only one frame in every 4 should be delivered.  
		This is a guideline; actual selection of frames is up to the decoder, which will know 
		which frames can be skipped without harm.
		If the decoder does not support this property directly, but reports that the content has 
		no interframe dependencies, the video toolbox may step in and perform simple frame dropping.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_ReducedFrameDelivery AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER; // Read/write, CFNumber in range [0.0,1.0].

/*!
	@constant	kVTDecompressionPropertyKey_OnlyTheseFrames
	@abstract
		Requests that frames be filtered by type.  
	@discussion
		This is an optional property for video decoders to implement.
		If kVTDecompressionPropertyKey_ReducedFrameDelivery is supported and used in conjunction with 
		this property, the ReducedFrameDelivery is the proportion of the frames selected by this property: 
		0.25 and IFrames would indicate that only one I frame in every four should be delivered.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_OnlyTheseFrames AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER; // Read/write, CFString, supported values may include:
VT_EXPORT const CFStringRef kVTDecompressionProperty_OnlyTheseFrames_AllFrames AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER;
VT_EXPORT const CFStringRef kVTDecompressionProperty_OnlyTheseFrames_NonDroppableFrames AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER;
VT_EXPORT const CFStringRef kVTDecompressionProperty_OnlyTheseFrames_IFrames AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER;
VT_EXPORT const CFStringRef kVTDecompressionProperty_OnlyTheseFrames_KeyFrames AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER;


/*!
	@constant	kVTDecompressionPropertyKey_SuggestedQualityOfServiceTiers
	@abstract
		Suggests how quality-of-service may be lowered in order to maintain realtime playback.
	@discussion
		This is an optional property for video decoders to implement.
		This property value is an array containing dictionaries of property key/value pairs.  
		The first dictionary in the array should contain the set of properties that restore the 
		default (full) quality of service; later dictionaries should contain property sets with 
		decreasing qualities of service.  Clients may work their way down these tiers until they are 
		able to keep up with the frame rate.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_SuggestedQualityOfServiceTiers AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER; // Read-only, CFArray of CFDictionaries containing property key/value pairs

/*!
	@constant	kVTDecompressionPropertyKey_SupportedPixelFormatsOrderedByQuality
	@abstract
		Provides hints about quality tradeoffs between pixel formats.
	@discussion
		This is an optional property for video decoders to implement.
		This property value is an array containing CFNumbers holding CMPixelFormatType values,
		ordered by quality from best to worse.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_SupportedPixelFormatsOrderedByQuality AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER; // Read-only, CFArray[CFNumber(CMPixelFormatType)] ordered best to worst, optional

/*!
	@constant	kVTDecompressionPropertyKey_SupportedPixelFormatsOrderedByPerformance
	@abstract
		Provides hints about speed tradeoffs between pixel formats.
	@discussion
		This is an optional property for video decoders to implement.
		This property value is an array containing CFNumbers holding CMPixelFormatType values,
		ordered by speed from fast to slow.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_SupportedPixelFormatsOrderedByPerformance AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER; // Read-only, CFArray[CFNumber(CMPixelFormatType)] ordered fast to slow, optional

/*!
	@constant	kVTDecompressionPropertyKey_PixelFormatsWithReducedResolutionSupport
	@abstract
		Indicates which pixel formats support reduced resolution decoding.
	@discussion
		This is an optional property for video decoders to implement.
		This property value is an array containing CFNumbers holding CMPixelFormatType values.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_PixelFormatsWithReducedResolutionSupport AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER; // Read-only, CFArray[CFNumber(CMPixelFormatType)], optional

#pragma mark Post-decompression processing

// Standard properties about processing to be performed after decompression.
// These are implemented by the video toolbox.

/*!
	@constant	kVTDecompressionPropertyKey_PixelTransferProperties
	@abstract
		Requests particular pixel transfer features.  
	@discussion
		This property is implemented by the video toolbox.
		This property value is a CFDictionary containing properties from VTPixelTransferProperties.h.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_PixelTransferProperties AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER; // Read/Write, CFDictionary containing properties from VTPixelTransferProperties.h.


#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif // VTDECOMPRESSIONPROPERTIES_H
