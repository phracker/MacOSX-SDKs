/*
	File:  VTCompressionProperties.h
	
	Framework:  VideoToolbox
	
	Copyright 2007-2020 Apple Inc. All rights reserved.
	
	Standard Video Toolbox compression properties.
*/

#ifndef VTCOMPRESSIONPROPERTIES_H
#define VTCOMPRESSIONPROPERTIES_H

#include <CoreMedia/CMBase.h>
#include <VideoToolbox/VTBase.h>

#include <CoreFoundation/CoreFoundation.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)    
	
CM_ASSUME_NONNULL_BEGIN

/*!
	@header
	@abstract
		Standard Video Toolbox compression properties
		
	@discussion
		This file defines standard properties used to describe and configure compression 
		operations managed by the video toolbox.  
		
		The video toolbox will provide direct support for some of these properties.
		Some properties are supported by individual encoders.
		
		Clients can query supported properties by calling VTSessionCopySupportedPropertyDictionary.
*/

#pragma mark Buffers

// Standard properties regarding buffer recycling.  
// These are implemented by the video toolbox.

/*!
	@constant	kVTCompressionPropertyKey_NumberOfPendingFrames
	@abstract
		The number of pending frames in the compression session. 
	@discussion
		This number may decrease asynchronously.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_NumberOfPendingFrames API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read-only, CFNumber<int>
	
/*!
	@constant	kVTCompressionPropertyKey_PixelBufferPoolIsShared
	@abstract
		Indicates whether the a common pixel buffer pool is shared between
		the video encoder and the session client. 
	@discussion
		This is false if separate pools are used because the video encoder's 
		and the client's pixel buffer attributes were incompatible.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_PixelBufferPoolIsShared API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read-only, CFBoolean

/*!
	@constant	kVTCompressionPropertyKey_VideoEncoderPixelBufferAttributes
	@abstract
		The video encoder's pixel buffer attributes for the compression session. 
	@discussion
		You can use these to create a pixel buffer pool for source pixel buffers. 
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_VideoEncoderPixelBufferAttributes API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read-only, CFDictionary

// Standard properties describing content.

// Standard properties regarding encoder behavior.
// Video encoders may report optionally report these.

#pragma mark Frame dependency

/*!
	@constant	kVTCompressionPropertyKey_MaxKeyFrameInterval
	@abstract
		The maximum interval between key frames, also known as the key frame rate. 
	@discussion
		Key frames, also known as sync frames, reset inter-frame
		dependencies; decoding a key frame is sufficient to prepare a
		decoder for correctly decoding the difference frames that
		follow. 
		Video encoders are allowed to generate key frames more frequently if
		this would result in more efficient compression. 
		The default key frame interval is 0, which indicates that the
		video encoder should choose where to place all key frames. A key
		frame interval of 1 indicates that every frame must be a key
		frame, 2 indicates that at least every other frame must be a key
		frame, etc.
		See also kVTCompressionPropertyKey_AllowTemporalCompression.
		
		This key can be set in conjunction with 
		kVTCompressionPropertyKey_MaxKeyFrameIntervalDuration,
		and both limits will be enforced - requiring a keyframe every X
		frames or every Y seconds, whichever comes first.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MaxKeyFrameInterval API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/write, CFNumber<int>, Optional

/*!
	@constant	kVTCompressionPropertyKey_MaxKeyFrameIntervalDuration
	@abstract
		The maximum duration from one key frame to the next in seconds. 
	@discussion
		Zero by default, which means no limit.  
		This property is particularly useful when the frame rate is variable.
		See kVTCompressionPropertyKey_MaxKeyFrameInterval for more discussion
		of key frames.
		
		This key can be set in conjunction with 
		kVTCompressionPropertyKey_MaxKeyFrameInterval,
		and both limits will be enforced - requiring a keyframe every X
		frames or every Y seconds, whichever comes first.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MaxKeyFrameIntervalDuration API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/write, CFNumber<seconds>, Optional


/*!
	@constant	kVTCompressionPropertyKey_AllowTemporalCompression
	@abstract
		Enables temporal compression.
	@discussion
		True by default.  Set this to false to require key-frame-only compression.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_AllowTemporalCompression API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/Write, CFBoolean, Optional, defaults to true

/*!
	@constant	kVTCompressionPropertyKey_AllowFrameReordering
	@abstract
		Enables frame reordering. 
	@discussion
		In order to encode B frames, a video encoder must reorder frames,
		which means that the order in which they will be emitted and
		stored (the decode order) is different from the order in which
		they were presented to the video encoder (the display order). 
		True by default.  Set this to false to prevent frame reordering.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_AllowFrameReordering API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/Write, CFBoolean, Optional, defaults to true

/*!
	@constant	kVTCompressionPropertyKey_AllowOpenGOP
	@abstract
		Enables Open GOP (Group Of Pictures) encoding.
	@discussion
		Only applicable to certain video encoders.  For HEVC encoding the property value is kCFBooleanTrue by default - which means
		that the encoder may use Open GOP structures, but it is not guaranteed to.
		Set this to kCFBooleanFalse to prevent the encoder from using any form of Open GOP during encoding.
		If set to kCFBooleanFalse, this will mean that the encoder will generate groups of pictures that are independently decodable; there
		will be no frame dependencies across sync samples (frames where kCMSampleAttachmentKey_NotSync is absent or kCFBooleanFalse)
		When the value is kCFBooleanTrue, the encoder may use Open GOP frame dependency structures to increase compression efficiency or quality.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_AllowOpenGOP API_AVAILABLE(macosx(10.14), ios(12.0), tvos(12.0)); // Read/Write, CFBoolean, Optional

#pragma mark Rate control

/*!
	@constant	kVTCompressionPropertyKey_AverageBitRate
	@abstract
		The long-term desired average bit rate in bits per second. 
	@discussion
		This is not a hard limit; the bit rate may peak above this. 
		The default bit rate is zero, which indicates that the video encoder 
		should determine the size of compressed data. 
		Note that bit rate settings only have an effect when timing
		information is provided for source frames, and that some codecs do
		not support limiting to specified bit rates.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_AverageBitRate API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/write, CFNumber<SInt32>, Optional

/*!
	@constant	kVTCompressionPropertyKey_DataRateLimits
	@abstract
		Zero, one or two hard limits on data rate.
	@discussion
		Each hard limit is described by a data size in bytes and a
		duration in seconds, and requires that the total size of
		compressed data for any contiguous segment of that duration (in
		decode time) must not exceed the data size. 
		By default, no data rate limits are set. 
		The property is a CFArray of an even number of CFNumbers,
		alternating between bytes and seconds.
		Note that data rate settings only have an effect when timing
		information is provided for source frames, and that some codecs do
		not support limiting to specified data rates.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_DataRateLimits API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/write, CFArray[CFNumber], [bytes, seconds, bytes, seconds...], Optional

/*!
	@constant	kVTCompressionPropertyKey_Quality
	@abstract
		The desired compression quality.
	@discussion
		Some encoders, such as JPEG, describe the compression level of each
		image with a quality value.  This value should be specified as a
		number in the range of 0.0 to 1.0, where low = 0.25, normal = 0.50,
		high = 0.75, and 1.0 implies lossless compression for encoders that
		support it.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_Quality API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/write, CFNumber<Float>, Optional

/*!
	@constant	kVTCompressionPropertyKey_TargetQualityForAlpha
	@abstract
		The target quality to use for encoding the alpha channel.
	@discussion
		The desired compression level to use for encoding the alpha channel.
		This value should be specified as a number in the range of 0.0 to 1.0.
		0.0 is lowest quality and 1.0 implies nearly lossless.  Alpha plane
		bit rates will tend to increase with increasing values.  When encoding
		the alpha channel, quality is given priority over bitrate.  Note this
		parameter is currently only applicable to HEVC with Alpha encoders.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_TargetQualityForAlpha	API_AVAILABLE(macosx(10.15), ios(13.0), tvos(13.0)); // Read/write, CFNumber<Float>, Optional, NULL by default

/*!
	@constant	kVTCompressionPropertyKey_MoreFramesBeforeStart
	@abstract
		Indicates whether and how a compression session's frames will be
		concatenated with other compressed frames to form a longer series.
	@discussion
		True if frames compressed in a separate session will be
		concatenated before the beginning of this one.  False if this is a
		stand-alone session, or if this session will encode the first
		segment of a multi-segment compression. By default, false.
		
		This information enables video encoders to ensure that compressed
		segments can be concatenated smoothly -- for example, avoiding
		data rate spikes where segments are joined. 
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MoreFramesBeforeStart API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/write, CFBoolean, Optional

/*!
	@constant	kVTCompressionPropertyKey_MoreFramesAfterEnd
	@abstract
		Indicates whether and how a compression session's frames will be
		concatenated with other compressed frames to form a longer series.
	@discussion
		True if frames compressed in a separate session will be
		concatenated following the end of this one. False if this is a
		stand-alone session, or if this session will encode the last
		segment of a multi-segment compression. By default, false.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MoreFramesAfterEnd API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/write, CFBoolean, Optional

/*!
	@constant	kVTCompressionPropertyKey_PrioritizeEncodingSpeedOverQuality
	@abstract
		Hint for the video encoder that it should maximize its speed during encode, sacrificing quality if needed
	@discussion
		Clients may set this property to kCFBooleanTrue to indicate that
		the encoder can take steps to maximize its speed by reducing quality.
		Setting the property to NULL is equivalent to setting it to kCFBooleanFalse.
		Not all video encoders support this property
		By default, this property is NULL.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_PrioritizeEncodingSpeedOverQuality API_AVAILABLE(macosx(11.0), ios(14.0), tvos(14.0)); // CFBoolean, Optional

#pragma mark Bitstream configuration

/*!
	@constant	kVTCompressionPropertyKey_ProfileLevel
	@abstract
		Specifies the profile and level for the encoded bitstream.
	@discussion
		Available profiles and levels vary across formats and between video encoders.
		Video encoders should use standard keys where available, and follow standard patterns where not.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ProfileLevel API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/write, CFString (enumeration), Optional
	
VT_EXPORT const CFStringRef kVTProfileLevel_HEVC_Main_AutoLevel API_AVAILABLE(macosx(10.13), ios(11.0), tvos(11.0));
VT_EXPORT const CFStringRef kVTProfileLevel_HEVC_Main10_AutoLevel API_AVAILABLE(macosx(10.13), ios(11.0), tvos(11.0));

VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_1_3 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_3_0 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_3_1 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_3_2 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_4_0 API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_4_1 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_4_2 API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_5_0 API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_5_1 API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_5_2 API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_AutoLevel API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_3_0 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_3_1 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_3_2 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_4_0 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_4_1 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_4_2 API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_5_0 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_5_1 API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_5_2 API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_AutoLevel API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Extended_5_0 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Extended_AutoLevel API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_3_0 API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_3_1 API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_3_2 API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_4_0 API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_4_1 API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_4_2 API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_5_0 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_5_1 API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_5_2 API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_AutoLevel API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2));

VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Simple_L0 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Simple_L1 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Simple_L2 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Simple_L3 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Main_L2 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Main_L3 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Main_L4 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_AdvancedSimple_L0 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_AdvancedSimple_L1 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_AdvancedSimple_L2 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_AdvancedSimple_L3 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_AdvancedSimple_L4 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));

VT_EXPORT const CFStringRef kVTProfileLevel_H263_Profile0_Level10 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H263_Profile0_Level45 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTProfileLevel_H263_Profile3_Level45 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));

/*!
    @constant    kVTCompressionPropertyKey_HDRMetadataInsertionMode
    @abstract
        The mode for HDR metadata in the output bitstream.
    @discussion
        If set to kVTHDRMetadataInsertionMode_None, no HDR metadata will
        be present in the output bitstream.  For other modes,
        VTCompressionSession will determine what type of HDR metadata
        to insert based on the output color space.  e.g. DolbyVision, HDR10, etc.
        This property has no effect if the output color space is not HDR, or if
        there is currently no underlying support for the HDR format.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_HDRMetadataInsertionMode API_AVAILABLE(macosx(11.0), ios(14.0), tvos(14.0), watchos(7.0)); // Read/write, CFString, Optional, default is kVTHDRMetadataInsertionMode_Auto
    VT_EXPORT const CFStringRef kVTHDRMetadataInsertionMode_None API_AVAILABLE(macosx(11.0), ios(14.0), tvos(14.0), watchos(7.0));
    VT_EXPORT const CFStringRef kVTHDRMetadataInsertionMode_Auto API_AVAILABLE(macosx(11.0), ios(14.0), tvos(14.0), watchos(7.0));

/*!
	 @constant	kVTCompressionPropertyKey_H264EntropyMode
	 @abstract
		The entropy encoding mode for H.264 compression.
	 @discussion
		If supported by an H.264 encoder, this property controls whether the encoder should use
		Context-based Adaptive Variable Length Coding (CAVLC) or Context-based Adaptive Binary Arithmetic Coding (CABAC).
		CABAC generally gives better compression at the expense of higher computational overhead.
		The default value is encoder-specific and may change depending on other encoder settings.
		Care should be taken when using this property -- changes may result in a configuration
		which is not compatible with a requested Profile and Level.  Results in this case are undefined,
		and could include encode errors or a non-compliant output stream.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_H264EntropyMode API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2));	// Read/write, CFString, optional
VT_EXPORT const CFStringRef kVTH264EntropyMode_CAVLC API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTH264EntropyMode_CABAC API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2));
	

/*!
	@constant	kVTCompressionPropertyKey_Depth
	@abstract
		The pixel depth of the encoded video.
	@discussion
		This property is only supported by video encoders for formats that are 
		tied to particular pixel formats (eg, 16-bit RGB, 24-bit RGB).
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_Depth API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/write, CFNumber (CMPixelFormatType), Optional

#pragma mark Runtime restrictions

/*!
	@constant	kVTCompressionPropertyKey_MaxFrameDelayCount
	@abstract
		The maximum frame delay count is the maximum number of frames that
		a compressor is allowed to hold before it must output a compressed
		frame.
	@discussion
		It limits the number of frames that may be held in the
		"compression window". If the maximum frame delay count is M, then
		before the call to encode frame N returns, frame N-M must have
		been emitted. 
		The default is kVTUnlimitedFrameDelayCount, which sets no limit
		on the compression window.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MaxFrameDelayCount API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/write, CFNumber, Optional
enum { kVTUnlimitedFrameDelayCount = -1 };
	
/*!
	@constant	kVTCompressionPropertyKey_MaxH264SliceBytes
	@abstract
		Specifies the maximum slice size for H.264 encoding
	@discussion
		If supported by an H.264 encoder, the value limits the size in bytes of 
		slices produced by the encoder, where possible.
		By default, no limit is specified.  A value of zero implies default behavior.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MaxH264SliceBytes API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/write, CFNumber<SInt32>, Optional

/*!
	@constant	kVTCompressionPropertyKey_RealTime
	@abstract
		Hints the video encoder that compression is, or is not, being performed in real time.
	@discussion
		For offline compression, clients may set this property to kCFBooleanFalse, which indicates that 
		it is OK for the video encoder to work slower than real time in order to produce a better result.
		For real-time compression, clients may set this property to kCFBooleanTrue to recommend that encoding stay timely.
		By default, this property is NULL, indicating unknown.  
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_RealTime API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2)); // Read/write, CFBoolean or NULL, Optional, default NULL

/*!
	@constant	kVTCompressionPropertyKey_MaximizePowerEfficiency
	@abstract
 		Hints to the video encoder that it should maximize power efficiency during encode.
	@discussion
		For compression where the client is operating in the background, clients may set this property to kCFBooleanTrue, which indicates that
		the encoder can take steps to minimize impact on power usage and other system activity.
		Setting the property to NULL is equivalent to setting it to kCFBooleanFalse.
 		Not all video encoders support this property
		By default, this property is NULL.
 */
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MaximizePowerEfficiency API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0)); // Read/write, CFBoolean or NULL, Optional, default is false


#pragma mark Hints

/*!
	@constant	kVTCompressionPropertyKey_SourceFrameCount
	@abstract
		Indicates the number of source frames, if known.
	@discussion
		This property allows a client to give the video encoder advance guidance as to how 
		many frames will be encoded.
		If nonzero, this should be the exact number of times that the client calls
		VTCompressionSessionEncodeFrame in each pass. 
		The default is 0, which indicates that the number of source frames
		is not known.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_SourceFrameCount API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/write, CFNumber, Optional

/*!
	@constant	kVTCompressionPropertyKey_ExpectedFrameRate
	@abstract
		Indicates the expected frame rate, if known.
	@discussion
		The frame rate is measured in frames per second. 
		This is not used to control the frame rate; it is provided as a hint to the 
		video encoder so that it can set up internal configuration before compression begins. 
		The actual frame rate will depend on frame durations and may vary. 
		By default, this is zero, indicating "unknown".
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ExpectedFrameRate API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/write, CFNumber, Optional

/*!
	@constant	kVTCompressionPropertyKey_BaseLayerFrameRateFraction
	@abstract
		This property indicates the desired frame rate fraction of the base layer.
	@discussion
		This property indicates the fraction of total frames submitted that should be encoded in the base layer.
		For example, a value of 0.5 means that half of the frames are in the base layer, and half are in the enhancement layer.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_BaseLayerFrameRateFraction API_AVAILABLE(macosx(11.3), ios(14.5), tvos(14.5)); // Read/write, CFNumber<Float>, Optional

/*!
	@constant	kVTCompressionPropertyKey_ExpectedDuration
	@abstract
		Indicates the expected total duration for the compression session, if known.
	@discussion
		By default, this is zero, indicating "unknown".
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ExpectedDuration API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/write, CFNumber(seconds), Optional

/*!
	@constant	kVTCompressionPropertyKey_BaseLayerFrameRate
	@abstract
		This property indicates the desired frame rate for the base temporal layer used in hierarchical video encoding.
	@discussion
		The frame rate is measured in frames per second.
		This property is only implemented by encoders which support hierarchical frame encoding, and requests that this encoding feature be enabled.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_BaseLayerFrameRate API_AVAILABLE(macosx(10.13), ios(11.0), tvos(11.0)); // Read/write, CFNumber, Optional


#pragma mark Hardware acceleration
#if !TARGET_OS_IPHONE
/*!
	@constant	kVTVideoEncoderSpecification_EnableHardwareAcceleratedVideoEncoder
	@abstract
		If set to kCFBooleanTrue, use a hardware accelerated video encoder if available.  If set to
		kCFBooleanFalse, hardware encode will never be used.
	@discussion
		This key is set in the encoderSpecification passed in to VTCompressionSessionCreate.  Set it
		to kCFBooleanTrue to allow hardware accelerated encode.  To prevent hardware encode,
		this property can be set to kCFBooleanFalse.
 		In MacOS 10.15 and later, hardware encode is enabled in VTCompressionSessions by default.
*/
VT_EXPORT const CFStringRef kVTVideoEncoderSpecification_EnableHardwareAcceleratedVideoEncoder API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2)); // CFBoolean, Optional, true by default

/*!
	@constant	kVTVideoEncoderSpecification_RequireHardwareAcceleratedVideoEncoder
	@abstract
		If set to kCFBooleanTrue, only use hardware encode and return an error if this isn't possible.
		Setting this key automatically implies kVTVideoEncoderSpecification_EnableHardwareAcceleratedVideoEncoder -- 
		there is no need to set both and the Enable key does nothing if the Require key is set.
	@discussion
		This key is set in the encoderSpecification passed in to VTCompressionSessionCreate.  Set it
		to kCFBooleanTrue to require hardware accelerated encode.  If hardware acceleration is not
		possible, the VTCompressionSessionCreate call will fail.
		This key is useful for clients that have their own software encode implementation or
		those that may want to configure software and hardware encode sessions differently.
		Hardware acceleration may be unavailable for a number of reasons.  A few common cases are:
			- the machine does not have hardware acceleration capabilities
			- the requested encoding format or encoding configuration is not supported
			- the hardware encoding resources on the machine are busy
*/
VT_EXPORT const CFStringRef kVTVideoEncoderSpecification_RequireHardwareAcceleratedVideoEncoder API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2)); // CFBoolean, Optional

/*!
	@constant	kVTCompressionPropertyKey_UsingHardwareAcceleratedVideoEncoder
	@abstract
		If set to kCFBooleanTrue, a hardware accelerated video encoder is being used.
	@discussion
		You can query this property using VTSessionCopyProperty after you have enabled hardware
		accelerated encode using kVTVideoEncoderSpecification_EnableHardwareAcceleratedVideoEncoder
		to see if a hardware accelerated encoder was selected.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_UsingHardwareAcceleratedVideoEncoder API_AVAILABLE(macosx(10.9), ios(8.0), tvos(10.2)); // CFBoolean, Read; assumed false by default
#endif // !TARGET_OS_IPHONE

/*!
	@constant	kVTVideoEncoderSpecification_RequiredEncoderGPURegistryID
	@abstract
		If set, the VideoToolbox will only use a hardware encoder running on the GPU specified by the provided GPU registryID.
	@discussion
		This specification implies kVTVideoEncoderSpecification_EnableHardwareAcceleratedVideoEncoder.  A separate hardware encode opt-in is not required.
		The GPU registryID can be obtained from a MTLDevice using [MTLDevice registryID] or can be obtained from OpenGL or OpenCL.
*/
VT_EXPORT const CFStringRef kVTVideoEncoderSpecification_RequiredEncoderGPURegistryID API_AVAILABLE(macosx(10.14)); // CFNumber, Optional

/*!
	@constant	kVTVideoEncoderSpecification_PreferredEncoderGPURegistryID
	@abstract
		If set, the VideoToolbox will try to use a hardware encoder running on the GPU specified by the provided GPU registryID.  If the
		GPU does not support encode of the specified format, the VideoToolbox will fall back to alternate encoders.
	@discussion
		This specification implies kVTVideoEncoderSpecification_EnableHardwareAcceleratedVideoEncoder.  A separate hardware encode opt-in is not required.
		If both kVTVideoEncoderSpecification_PreferredEncoderGPURegistryID and kVTVideoEncoderSpecification_RequiredEncoderGPURegistryID are set, kVTVideoEncoderSpecification_PreferredEncoderGPURegistryID will be ignored.
		This specification can be used in conjunction with kVTVideoEncoderSpecification_RequireHardwareAcceleratedVideoEncoder to prevent a fallback to software encode.
		The GPU registryID can be obtained from a MTLDevice using [MTLDevice registryID] or can be obtained from OpenGL or OpenCL.
*/
VT_EXPORT const CFStringRef kVTVideoEncoderSpecification_PreferredEncoderGPURegistryID API_AVAILABLE(macosx(10.14)); // CFNumber, Optional

/*!
	@constant	kVTCompressionPropertyKey_UsingGPURegistryID
	@abstract
	returns CFNumber indicating the gpu registryID of the encoder that was selected.  NULL indicates a built-in encoder or software encode was used.
	@discussion
		You can query this property using VTSessionCopyProperty after building a VTCompressionSession to find out which GPU the encoder is using.
		If a encoder based on a built-in GPU was used it will return NULL.  If a software encoder is used, it will return NULL
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_UsingGPURegistryID API_AVAILABLE(macosx(10.15)) ; // CFNumberRef, Read;

#pragma mark Per-frame configuration
	
/*!
	@constant	kVTEncodeFrameOptionKey_ForceKeyFrame
	@abstract
		CFBoolean forcing the current frame to be a key frame
	@discussion
		This value is set in the frameProperties CFDictionary passed to 
		VTCompressionSessionEncodeFrame to force the current frame to be a 
		keyframe or not.  
		Note that it may not be possible for the encoder to accomodate all
		requests.
*/
VT_EXPORT const CFStringRef kVTEncodeFrameOptionKey_ForceKeyFrame API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); //  CFBoolean


#pragma mark Clean aperture and pixel aspect ratio

/*!
	@constant	kVTCompressionPropertyKey_CleanAperture
	@abstract
		Describes the clean aperture for encoded frames.
	@discussion
		Some video encoders may enforce specific clean apertures; 
		in those cases this property will be read-only (SetProperty will return kVTPropertyReadOnlyErr).
		The clean aperture will be set on the format description for output samples,
		and may affect source frame scaling.
		NULL is a valid value for this property, meaning that the clean aperture is the full width and height.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_CleanAperture API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/write, CFDictionary (see CMFormatDescription.h), Optional

/*!
	@constant	kVTCompressionPropertyKey_PixelAspectRatio
	@abstract
		Describes the pixel aspect ratio for encoded frames.
	@discussion
		Some video encoders may enforce specific pixel aspect ratios; 
		in those cases this property will be read-only (SetProperty will return kVTPropertyReadOnlyErr).
		The pixel aspect ratio will be set on the format description for output samples,
		and may affect source frame scaling.
		NULL is a valid value for this property, meaning square pixels (1:1).
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_PixelAspectRatio API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/write, CFDictionary (see CMFormatDescription.h), Optional

/*!
	@constant	kVTCompressionPropertyKey_FieldCount
	@abstract
		Indicates whether the frames should be encoded progressive (1) or interlaced (2).
	@discussion
		The field count will be set on the format description for output samples,
		and may affect source frame scaling.
		NULL is a valid value for this property.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_FieldCount API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/write, CFNumber (see kCMFormatDescriptionExtension_FieldCount), Optional

/*!
	@constant	kVTCompressionPropertyKey_FieldDetail
	@abstract
		Indicates field ordering for encoded interlaced frames.
	@discussion
		Some video encoders may enforce specific field ordering; 
		in those cases this property will be read-only (SetProperty will return kVTPropertyReadOnlyErr).
		The field detail will be set on the format description for output samples,
		and may affect source frame scaling.
		NULL is a valid value for this property.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_FieldDetail API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/write, CFString (see kCMFormatDescriptionExtension_FieldDetail), Optional

/*!
	@constant	kVTCompressionPropertyKey_AspectRatio16x9
	@abstract
		Indicates that the DV video stream should have the 16x9 flag set.
	@discussion
		This property is supported by the DV25/50 family of encoders.
		When false, the picture aspect ratio is 4:3.  
		When true, the picture aspect ratio is 16:9.
		Either way, a fixed PixelAspectRatio is used (the specific value depends on whether the format is NTSC or PAL).
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_AspectRatio16x9 API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/write, CFBoolean, Optional

/*!
	@constant	kVTCompressionPropertyKey_ProgressiveScan
	@abstract
		Indicates that the DV video stream should have the progressive flag set.
	@discussion
		This property is supported by the DV25/50 family of encoders.
		If false, content is encoded as interlaced.
		If true, content is encoded as progressive.
		The value of this property fixes the FieldCount and FieldDetail properties.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ProgressiveScan API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/write, CFBoolean, Optional

#pragma mark Color

/*!
	@constant	kVTCompressionPropertyKey_ColorPrimaries
	@abstract
		Indicates color primaries for compressed content.
	@discussion
		Some video encoders may enforce specific colorimetry; 
		in those cases this property will be read-only (SetProperty will return kVTPropertyReadOnlyErr).
		The value will be set on the format description for output sample buffers.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ColorPrimaries API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/write, CFString (see kCMFormatDescriptionExtension_ColorPrimaries), Optional

/*!
	@constant	kVTCompressionPropertyKey_TransferFunction
	@abstract
		Indicates transfer function for compressed content.
	@discussion
		Some video encoders may enforce specific colorimetry; 
		in those cases this property will be read-only (SetProperty will return kVTPropertyReadOnlyErr).
		The value will be set on the format description for output sample buffers.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_TransferFunction API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/write, CFString (see kCMFormatDescriptionExtension_TransferFunction), Optional

/*!
	@constant	kVTCompressionPropertyKey_YCbCrMatrix
	@abstract
		Indicates YCbCr matrix for compressed content.
	@discussion
		Some video encoders may enforce specific colorimetry; 
		in those cases this property will be read-only (SetProperty will return kVTPropertyReadOnlyErr).
		The value will be set on the format description for output sample buffers.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_YCbCrMatrix API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/write, CFString (see kCMFormatDescriptionExtension_YCbCrMatrix), Optional

/*!
	@constant	kVTCompressionPropertyKey_ICCProfile
	@abstract
		Indicates ICC profile for compressed content.
	@discussion
		Some video encoders may enforce specific colorimetry; 
		in those cases this property will be read-only (SetProperty will return kVTPropertyReadOnlyErr).
		If this property and any of the previous three are all set, they should be set to consistent values, 
		or undefined behavior may occur.
		The value will be set on the format description for output sample buffers.
		NULL can be a valid value for this property.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ICCProfile API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/write, CFData (see kCMFormatDescriptionExtension_ICCProfile), Optional

/*!
	@constant	kVTCompressionPropertyKey_MasteringDisplayColorVolume
	@abstract
		The value is 24 bytes containing a big-endian structure as defined in ISO/IEC 23008-2:2015(E), D.2.28 Mastering display colour volume SEI message.
	@discussion
		The value will be set on the format description for output sample buffers,
		and incorporated into the appropriate SEI NAL unit where supported by the encoder.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MasteringDisplayColorVolume API_AVAILABLE(macosx(10.13), ios(11.0), tvos(11.0)); // Read/write, CFData(24 bytes) (see kCMFormatDescriptionExtension_MasteringDisplayColorVolume), Optional

/*!
	@constant	kVTCompressionPropertyKey_ContentLightLevelInfo
	@abstract
		The value is 4 bytes containing a big-endian structure as defined in the Content Light Level Info SEI message.
	@discussion
		The value will be set on the format description for output sample buffers,
		and incorporated into the appropriate SEI NAL unit where supported by the encoder.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ContentLightLevelInfo API_AVAILABLE(macosx(10.13), ios(11.0), tvos(11.0)); // Read/write, CFData(4 bytes) (see kCMFormatDescriptionExtension_ContentLightLevelInfo), Optional


/*!
	@constant  kVTCompressionPropertyKey_GammaLevel
	@abstract
		Indicates gamma level for compressed content.
	@discussion
		This property allows the caller to specify a gamma value to include in the CMVideoFormatDescription attached to output CMSampleBuffers. It does not change pixel data being encoded.
*/
	VT_EXPORT const CFStringRef kVTCompressionPropertyKey_GammaLevel VT_AVAILABLE_STARTING(10_9); // Read/write, CFNumber (see kCMFormatDescriptionExtension_GammaLevel), Optional
	

/*!
	@constant	kVTCompressionPropertyKey_AlphaChannelMode
	@abstract
		Specifies whether the source images' RGB values have been premultiplied by the alpha channel values.
	@discussion
		Video compression will fail if source image buffers have a mismatched value in their kCVImageBufferAlphaChannelMode attachment.
		If this property is not set, the encoder may read the first source image buffer's kCVImageBufferAlphaChannelMode attachment.
		If neither the property nor the first buffer's attachment is set, defaults to kVTAlphaChannelMode_PremultipliedAlpha.
 */
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_AlphaChannelMode	API_AVAILABLE(macosx(10.15), ios(13.0), tvos(13.0), watchos(6.0)); // Read/write, Optional, CFString(kVTAlphaChannelMode_*); if property is not set, matches first source frame's attachment; if that's also not set, defaults to premultiplied alpha
VT_EXPORT const CFStringRef kVTAlphaChannelMode_StraightAlpha	API_AVAILABLE(macosx(10.15), ios(13.0), tvos(13.0), watchos(6.0));
VT_EXPORT const CFStringRef kVTAlphaChannelMode_PremultipliedAlpha	API_AVAILABLE(macosx(10.15), ios(13.0), tvos(13.0), watchos(6.0));

	
#pragma mark Pre-compression processing

// Standard properties about processing to be performed before compression.
// These are implemented by the video toolbox.

/*!
	@constant	kVTCompressionPropertyKey_PixelTransferProperties
	@abstract
		Specifies properties to configure a VTPixelTransferSession used to transfer source frames
		from the client's image buffers to the video encoder's image buffers, if necessary.
	@discussion
		Setting this property alone does not necessarily guarantee that a VTPixelTransferSession will be created.
		See VTPixelTransferProperties.h.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_PixelTransferProperties API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // Read/Write, CFDictionary containing properties from VTPixelTransferProperties.h.
	
#pragma mark Multi-pass
	
/*!
	@const		kVTCompressionPropertyKey_MultiPassStorage
	@abstract	Enables multi-pass compression and provides storage for encoder-private data.
	@discussion
	Some video encoders support multi-pass encoding.  To determine whether a VTCompressionSession supports multi-pass encoding, you can inspect the dictionary returned by VTSessionCopySupportedPropertyDictionary to see if it contains kVTCompressionPropertyKey_MultiPassStorage.
	 
	To enable multi-pass encoding, set the kVTCompressionPropertyKey_MultiPassStorage property to a VTMultiPassStorage object, which you can create by calling VTMultiPassStorageCreate.  Then make one or more passes over the source frames.  Bracket each pass with a call to VTCompressionSessionBeginPass at the beginning and VTCompressionSessionEndPass at the end.
	 
	In the first pass of multi-pass encoding, call VTCompressionSessionEncodeFrame for every source frame (just as in single-pass encoding).  At the end of every pass, call VTCompressionSessionEndPass.  This may take some time as the video encoder determines whether it can improve the encoding by performing another pass.  If the user cancels encoding during this time, call VTCompressionSessionInvalidate to interrupt the processing.  VTCompressionSessionEndPass will indicate via the furtherPassesRequestedOut argument whether the video encoder would like to perform another pass.  There is no particular bound on the number of passes the video encoder may request, but the client is free to disregard this request and use the last-emitted set of frames.
	 
	If *furtherPassesRequestedOut is set to true and you want to perform another pass, call VTCompressionSessionGetTimeRangesForNextPass to determine the time ranges for the next pass.  Only the source frames within these time ranges need to be passed to VTCompressionSessionEncodeFrame; the video encoder is satisfied with the already-emitted compressed frames outside these ranges and they can be kept for the final output.
	 
	In second and successive passes, you must pass identical source frames, frame properties and timestamps to VTCompressionSessionEncodeFrame as in the first pass, with the exception that frames not in the requested time ranges should be skipped.
	 
	You can create and use a VTFrameSilo object to merge sequences of compressed frames across passes during multi-pass encoding.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MultiPassStorage API_AVAILABLE(macosx(10.10), ios(8.0), tvos(10.2)); // VTMultiPassStorage, optional, default is NULL

#pragma mark Encoder information
	
/*!
	@constant	kVTCompressionPropertyKey_EncoderID
	@abstract
		Specifies a particular video encoder by its ID string.
	@discussion
		Matches the value specified in kVTVideoEncoderSpecification_EncoderID, and the kVTVideoEncoderList_EncoderID value returned from VTCopyVideoEncoderList.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_EncoderID API_AVAILABLE(macosx(10.13), ios(11.0), tvos(11.0)); // CFStringRef

/*!
	@constant	kVTCompressionPropertyKey_PreserveDynamicHDRMetadata
	@abstract
		Controls whether or not to preserve any dynamic HDR metadata on the input pixel buffer
	@discussion
		If set to false, and kVTCompressionPropertyKey_HDRMetadataInsertionMode is not
		kVTHDRMetadataInsertionMode_None, then VTCompressionSession will generate the
		dynamic HDR metadata for the pixel buffer, if the HDR format is supported.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_PreserveDynamicHDRMetadata // CFBoolean, Write, Optional
							API_AVAILABLE(macosx(11.0), ios(14.0), tvos(14.0));

/*!
	@constant	kVTVideoEncoderSpecification_EnableLowLatencyRateControl
	@abstract
		Requires that an encoder which supports low-latency operation be selected, and enables low-latency mode.
	@discussion
		Low latency RateControl enforces the following behaviors: 
		- Infinite GOP (all P frames following the beginning IDR).
		- No frame reordering (B frame) or looking ahead.
		- Only High profiles. Levels are left for the encoder to automatically set. 
		- Temporal Layer structure.

		Also see:
			kVTCompressionPropertyKey_AverageBitRate
			kVTCompressionPropertyKey_BaseLayerFrameRateFraction
			kVTEncodeFrameOptionKey_ForceKeyFrame
*/
VT_EXPORT const CFStringRef kVTVideoEncoderSpecification_EnableLowLatencyRateControl API_AVAILABLE(macosx(11.3), ios(14.5), tvos(14.5)); // Read/write, CFBoolean, Optional

	
CM_ASSUME_NONNULL_END

#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif // VTCOMPRESSIONPROPERTIES_H
