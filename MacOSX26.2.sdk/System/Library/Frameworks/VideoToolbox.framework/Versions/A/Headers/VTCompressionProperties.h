/*
	File:  VTCompressionProperties.h
	
	Framework:  VideoToolbox
	
	Copyright 2007-2025 Apple Inc. All rights reserved.
	
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

/*
	Recommendations for configuring VTCompressionSessions

	These are recommendations for configuring VTCompressionSessions for some common scenarios.
	These are starting points. The requirements of the application may necessitate further adjustments.

	Live capture and live broadcast scenarios:
		• kVTCompressionPropertyKey_RealTime: kCFBooleanTrue
		• kVTCompressionPropertyKey_ExpectedFrameRate: set to real-time frame rate if possible

	Offline transcode initiated by a user, who is waiting for the results:
		• kVTCompressionPropertyKey_RealTime: kCFBooleanFalse
		• kVTCompressionPropertyKey_MaximizePowerEfficiency: kCFBooleanFalse

	Offline transcode in the background (when the user is not aware):
		• kVTCompressionPropertyKey_RealTime: kCFBooleanFalse
		• kVTCompressionPropertyKey_MaximizePowerEfficiency: kCFBooleanTrue

	Ultra-low-latency conferencing and cloud gaming (cases where every millisecond counts):
		• kVTVideoEncoderSpecification_EnableLowLatencyRateControl: kCFBooleanTrue
		• kVTCompressionPropertyKey_RealTime: kCFBooleanTrue
		• kVTCompressionPropertyKey_ExpectedFrameRate: set to real-time frame rate if possible
		• kVTCompressionPropertyKey_PrioritizeEncodingSpeedOverQuality: kCFBooleanTrue

	Optionally, kVTCompressionPropertyKey_AllowTemporalCompression, kVTCompressionPropertyKey_AllowFrameReordering,
	    kVTCompressionPropertyKey_MaxKeyFrameInterval, and kVTCompressionPropertyKey_MaxKeyFrameIntervalDuration
	    may be used to configure frame dependencies in the video stream.

	kVTCompressionPropertyKey_AverageBitRate, kVTCompressionPropertyKey_DataRateLimits, kVTCompressionPropertyKey_ConstantBitRate, and kVTCompressionPropertyKey_VariableBitRate may be used to configure the video data rate.

		• kVTCompressionPropertyKey_AverageBitRate specifies the desired long term average bit rate. It is a soft limit, so the encoder may overshoot or undershoot and the average bit rate of the output video may be over or under the target.
		• kVTCompressionPropertyKey_DataRateLimits specifies a hard data rate cap for a given time window. The encoder will not overshoot. kVTCompressionPropertyKey_AverageBitRate and kVTCompressionPropertyKey_DataRateLimits may be used together to specify an overall target bit rate while also establishing hard limits over a smaller window.
		• kVTCompressionPropertyKey_ConstantBitRate is intended for legacy content distribution networks which require constant bitrate, and is not intended for general streaming scenarios.
		• kVTCompressionPropertyKey_VariableBitRate specifies the desired variable bitrate target. Encoder automatically allocates higher bitrate for complex segments of the video. It can be used along with kVTCompressionPropertyKey_VBVMaxBitRate to specify the maximum birate encoder can use.
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
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_NumberOfPendingFrames API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read-only, CFNumber<int>
	
/*!
	@constant	kVTCompressionPropertyKey_PixelBufferPoolIsShared
	@abstract
		Indicates whether the a common pixel buffer pool is shared between
		the video encoder and the session client. 
	@discussion
		This is false if separate pools are used because the video encoder's 
		and the client's pixel buffer attributes were incompatible.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_PixelBufferPoolIsShared API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read-only, CFBoolean

/*!
	@constant	kVTCompressionPropertyKey_VideoEncoderPixelBufferAttributes
	@abstract
		The video encoder's pixel buffer attributes for the compression session. 
	@discussion
		You can use these to create a pixel buffer pool for source pixel buffers. 
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_VideoEncoderPixelBufferAttributes API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read-only, CFDictionary

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
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MaxKeyFrameInterval API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFNumber<int>, Optional

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
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MaxKeyFrameIntervalDuration API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFNumber<seconds>, Optional


/*!
	@constant	kVTCompressionPropertyKey_AllowTemporalCompression
	@abstract
		Enables temporal compression.
	@discussion
		True by default.  Set this to false to require key-frame-only compression.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_AllowTemporalCompression API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/Write, CFBoolean, Optional, defaults to true

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
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_AllowFrameReordering API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/Write, CFBoolean, Optional, defaults to true

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
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_AllowOpenGOP API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/Write, CFBoolean, Optional

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
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_AverageBitRate API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFNumber<SInt32>, Optional

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

		When both kVTCompressionPropertyKey_DataRateLimits and
		kVTCompressionPropertyKey_AverageBitRate are supported,
		it is recommended that kVTCompressionPropertyKey_AverageBitRate
		be set when kVTCompressionPropertyKey_DataRateLimits is set.
		If kVTCompressionPropertyKey_AverageBitRate is not specified,
		an overall average bit rate target will be selected at a safe margin below
		the kVTCompressionPropertyKey_DataRateLimits target, so that regional
		overshoot in the encoding will not exceed the
		kVTCompressionPropertyKey_DataRateLimits.
		The overall average bitrate target generated from
		kVTCompressionPropertyKey_DataRateLimits in the absence of
		kVTCompressionPropertyKey_AverageBitRate may not be ideal for all
		scenarios.
		Encoding is more likely to undershoot a requested
		kVTCompressionPropertyKey_AverageBitRate if the specified target is too
		close to a hard limit specified by kVTCompressionPropertyKey_DataRateLimits.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_DataRateLimits API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFArray[CFNumber], [bytes, seconds, bytes, seconds...], Optional

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
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_Quality API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFNumber<Float>, Optional

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
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_TargetQualityForAlpha	API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFNumber<Float>, Optional, NULL by default

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
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MoreFramesBeforeStart API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFBoolean, Optional

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
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MoreFramesAfterEnd API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFBoolean, Optional

/*!
	@constant	kVTCompressionPropertyKey_PrioritizeEncodingSpeedOverQuality
	@abstract
		Hint for the video encoder that it should maximize its speed during encode, sacrificing quality if needed
	@discussion
		Video encoders sometimes have a tradeoff available between encoding speed and quality at a given bitrate.
		For example, by spending more time refining encoding decisions, it may be possible to make marginal improvements on quality.
		This property lets a client indicate its preference for any such tradeoff.
		Clients may set this property to kCFBooleanTrue to indicate that
		the encoder can take steps to maximize its speed by reducing quality, 
		or to kCFBooleanFalse to indicate that the priority should be maximizing quality (at a given bitrate).
		When the property value is NULL, the video encoder will choose its default behavior.
		H.264 and HEVC hardware video encoders prioritize quality over speed by default.
		ProRes hardware encoders currently prioritize speed over quality by default.
		Not all video encoders support this property.
		By default, this property is NULL.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_PrioritizeEncodingSpeedOverQuality API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0), visionos(1.0)) API_UNAVAILABLE(watchos); // CFBoolean, Optional

/*!
	@constant	kVTCompressionPropertyKey_ConstantBitRate
	@abstract
		Requires that the encoder use a Constant Bit Rate algorithm.
	@discussion
		The property kVTCompressionPropertyKey_ExpectedFrameRate should be set along with kVTCompressionPropertyKey_ConstantBitRate
		to ensure effective CBR rate control.

		This property is not compatible with kVTCompressionPropertyKey_DataRateLimits,
		kVTCompressionPropertyKey_AverageBitRate, and kVTCompressionPropertyKey_VariableBitRate.

		The encoder will pad the frame if they are smaller than they need to be based on the Constant BitRate. This
		property is not recommended for general streaming or export scenarios. It is intended for interoperability with
		certain streaming CDNs which specifically require that data rates not drop even during low motion and activity scenes.

		This is not supported in all encoders or in all encoder operating modes. kVTPropertyNotSupportedErr will be
		returned when this option is not supported.

*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ConstantBitRate API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos); // CFNumber bits per second, Optional

/*!
	@constant	kVTCompressionPropertyKey_EstimatedAverageBytesPerFrame
	@abstract
		Returns the encoder's estimate of the expected size of a single encoded frame in bytes, based on current configuration.
	@discussion
		When supported, this option is intended to allow clients to estimate the output file size for an encoded video stream.
		This property is not implemented by all video encoders.
		
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_EstimatedAverageBytesPerFrame API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos); // Read Only, CFNumber (bytes per frame)

/*!
	@constant    kVTCompressionPropertyKey_VariableBitRate
	@abstract
		Requires that the encoder use a variable bitrate (VBR) rate control algorithm and specifies the desired variable bitrate in bits per second.
	@discussion
		The actual peak bitrate present in the bitstream may be above or below this value based on other parameters such as kVTCompressionPropertyKey_VBVMaxBitRate.
		This property key needs to be set to achieve Variable Bitrate (VBR) rate control.
		This property key is not compatible with:
			1. kVTCompressionPropertyKey_AverageBitRate,
			2. kVTCompressionPropertyKey_ConstantBitRate,
			3. kVTCompressionPropertyKey_DataRateLimits,
			4. VTVideoEncoderSpecification_EnableLowLatencyRateControl = True.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_VariableBitRate API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos); // Read/write, CFNumber<UInt32>, Optional

/*!
	@constant    kVTCompressionPropertyKey_VBVMaxBitRate
	@abstract
		Defines the maximum bitrate that can enter the video buffering verifier (VBV) model at any time in variable bitrate (VBR) mode.
	@discussion
		The value of this property must be greater than zero.
		This property key is not compatible with:
			1. kVTCompressionPropertyKey_AverageBitRate,
			2. kVTCompressionPropertyKey_ConstantBitRate,
			3. kVTCompressionPropertyKey_DataRateLimits,
			4. VTVideoEncoderSpecification_EnableLowLatencyRateControl=True.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_VBVMaxBitRate API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos); // Read/write, CFNumber<UInt32>, Optional

/*!
	@constant    kVTCompressionPropertyKey_VBVBufferDuration
	@abstract
		Capacity of the video buffering verifier (VBV) model in seconds.
	@discussion
		VBV model allows for larger variations in bitrates while avoiding decoder-side overflows or underflows.
		A larger VBV model size may improve compression quality, but it requires more memory and may introduce delay.
		The value of this property must be greater than 0.0.
		The default value is set as 2.5 seconds.
		This property key is compatible with constant bitrate (CBR) or variable bitrate (VBR) rate control.
		This property key is incompatible with:
			1. kVTCompressionPropertyKey_AverageBitRate,
			2. kVTCompressionPropertyKey_DataRateLimits,
			3. VTVideoEncoderSpecification_EnableLowLatencyRateControl=True.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_VBVBufferDuration API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos); // Read/write, CFNumber<Float>, Optional

/*!
	@constant    kVTCompressionPropertyKey_VBVInitialDelayPercentage
	@abstract
		Initial delay of the VBV model between storing the picture in the VBV buffer model and decoding of that picture, as a percentage of VBV buffer duration.
	@discussion
		This value should be specified as a number in the range of 0 to 100.
		Larger value increases the delay but results in smoother playback.
		Default value is 90, meaning 90% of the VBV buffer duration.
		This property key is incompatible with:
			1. kVTCompressionPropertyKey_AverageBitRate,
			2. kVTCompressionPropertyKey_DataRateLimits,
			3. VTVideoEncoderSpecification_EnableLowLatencyRateControl=True.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_VBVInitialDelayPercentage API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos); // Read/write, CFNumber<Float>, Optional


#pragma mark Bitstream configuration

/*!
	@constant	kVTCompressionPropertyKey_ProfileLevel
	@abstract
		Specifies the profile and level for the encoded bitstream.
	@discussion
		Available profiles and levels vary across formats and between video encoders.
		Video encoders should use standard keys where available, and follow standard patterns where not.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ProfileLevel API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFString (enumeration), Optional
	
VT_EXPORT const CFStringRef kVTProfileLevel_HEVC_Main_AutoLevel API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_HEVC_Main10_AutoLevel API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_HEVC_Main42210_AutoLevel API_AVAILABLE(macos(12.3), ios(15.4), tvos(15.4), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_HEVC_Monochrome_AutoLevel API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_HEVC_Monochrome10_AutoLevel API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), visionos(1.0)) API_UNAVAILABLE(watchos);

VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_1_3 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_3_0 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_3_1 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_3_2 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_4_0 API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_4_1 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_4_2 API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_5_0 API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_5_1 API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_5_2 API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_AutoLevel API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_ConstrainedBaseline_AutoLevel API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_3_0 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_3_1 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_3_2 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_4_0 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_4_1 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_4_2 API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_5_0 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_5_1 API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_5_2 API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_AutoLevel API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Extended_5_0 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Extended_AutoLevel API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_3_0 API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_3_1 API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_3_2 API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_4_0 API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_4_1 API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_4_2 API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_5_0 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_5_1 API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_5_2 API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_AutoLevel API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_ConstrainedHigh_AutoLevel API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Simple_L0 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Simple_L1 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Simple_L2 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Simple_L3 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Main_L2 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Main_L3 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Main_L4 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_AdvancedSimple_L0 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_AdvancedSimple_L1 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_AdvancedSimple_L2 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_AdvancedSimple_L3 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_AdvancedSimple_L4 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);

VT_EXPORT const CFStringRef kVTProfileLevel_H263_Profile0_Level10 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H263_Profile0_Level45 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTProfileLevel_H263_Profile3_Level45 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@constant	kVTCompressionPropertyKey_OutputBitDepth
	@abstract
		 When set, requires the encoder to output bitstream with the requested bit depth, if supported by the configured profile level setting.
		 In the absence of this property, the video encoder will assume the highest bit depth allowable by the configured profile level setting.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_OutputBitDepth API_AVAILABLE(macos(12.3), ios(15.4), tvos(15.4), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, Optional, CFNumber, NULL by default

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
		kVTHDRMetadataInsertionMode_RequestSDRRangePreservation will
		only insert metadata when the following is true:
			transfer function is kCVImageBufferTransferFunction_SMPTE_ST_2084_PQ
			color primaries is kCVImageBufferColorPrimaries_ITU_R_2020
			color matrix is kCVImageBufferYCbCrMatrix_ITU_R_2020
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_HDRMetadataInsertionMode API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFString, Optional, default is kVTHDRMetadataInsertionMode_Auto
    VT_EXPORT const CFStringRef kVTHDRMetadataInsertionMode_None API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0), visionos(1.0)) API_UNAVAILABLE(watchos);
    VT_EXPORT const CFStringRef kVTHDRMetadataInsertionMode_Auto API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0), visionos(1.0)) API_UNAVAILABLE(watchos);
	VT_EXPORT const CFStringRef kVTHDRMetadataInsertionMode_RequestSDRRangePreservation API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

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
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_H264EntropyMode API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);	// Read/write, CFString, optional
VT_EXPORT const CFStringRef kVTH264EntropyMode_CAVLC API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTH264EntropyMode_CABAC API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);
	

/*!
	@constant	kVTCompressionPropertyKey_Depth
	@abstract
		The pixel depth of the encoded video.
	@discussion
		This property is only supported by video encoders for formats that are 
		tied to particular pixel formats (eg, 16-bit RGB, 24-bit RGB).
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_Depth API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFNumber (CMPixelFormatType), Optional

/*!
	@constant	kVTCompressionPropertyKey_PreserveAlphaChannel
	@abstract
		Instructs the encoder to encode or discard the alpha channel of input video frames
	@discussion
		This property allows a client to  specify whether or not the alpha channel in the source pixelBuffers should be encoded.
		The client may set this to kCFBooleanFalse in cases where they are not interested in preserving alpha, or if the alpha channel is known to be fully opaque.
		This property is not supported by all encoders.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_PreserveAlphaChannel API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFBoolean, Optional, (effectively) kCFBooleanTrue by default

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
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MaxFrameDelayCount API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFNumber, Optional
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
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MaxH264SliceBytes API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFNumber<SInt32>, Optional

/*!
	@constant	kVTCompressionPropertyKey_RealTime
	@abstract
		Hints the video encoder that compression is, or is not, being performed in real time.
	@discussion
		For offline compression, clients are advised to set this property to kCFBooleanFalse.
		This indicates that the timeline of the frames is not connected to wall-clock time at all.
		This allows the video encoder to run either slower than real-time or faster than real-time, 
		depending upon the situation and device capabilities.
		For real-time compression, clients are advised to set this property to kCFBooleanTrue.
		This indicates that the timeline of frames is connected to real time (so, for example, 
		the client expects to encode one second of frames each second, on average). 
		In such a case, it is important that encoding keep up, but it is also not valuable to encode 
		substantially faster than real time.  
		When this property is set to kCFBooleanTrue, the video encoder may use the value of the 
		kVTCompressionPropertyKey_ExpectedFrameRate property to optimize energy usage, 
		by anticipating that encoding requests will happen at this rate.
		By default, this property is NULL, indicating unknown.  
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_RealTime API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFBoolean or NULL, Optional, default NULL

/*!
	@constant	kVTCompressionPropertyKey_MaximizePowerEfficiency
	@abstract
 		Hints to the video encoder that it should maximize power efficiency during encode.
	@discussion
		For compression where the client is operating in the background, clients may set this property to kCFBooleanTrue, which indicates that
		the encoder can take steps to minimize impact on power usage and other system activity.
		Setting the property to NULL is equivalent to setting it to kCFBooleanFalse.
		Not all video encoders support this property.
		By default, this property is NULL.
		If the kVTCompressionPropertyKey_RealTime property is set to kCFBooleanTrue, 
		the video encoder may act as though this property were set to kCFBooleanFalse.
 */
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MaximizePowerEfficiency API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFBoolean or NULL, Optional, default is false


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
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_SourceFrameCount API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFNumber, Optional

/*!
	@constant	kVTCompressionPropertyKey_ExpectedFrameRate
	@abstract
		Indicates the expected frame rate of the video to be encoded.
	@discussion
		The frame rate is measured in frames per second.
		This property is used to inform the encoder of the expected cadence of the presentation time stamp values of frames that will be submitted to the encoder. 
		The actual frame rate may vary, and will depend on the frame durations calculated by the difference between subsequent presentation time stamps.
		If kVTCompressionPropertyKey_RealTime has been set to true, the ExpectedFrameRate may be used to optimize energy usage as well as perform internal encoder configuration before compression begins.
		If kVTCompressionPropertyKey_RealTime is not set, or has been set to false, the ExpectedFrameRate is still helpful and allows the encoder to optimize internal encoder configuration before compression begins.
		By default, the property has a value of zero indicating "unknown".
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ExpectedFrameRate API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFNumber, Optional

/*!
	@constant	kVTCompressionPropertyKey_MaximumRealTimeFrameRate
	@abstract
		Indicates the maximum real time rate at which frames could be submitted to the VTCompressionSession
	@discussion
		The frame rate is measured in frames per second.
		This property can be used to inform the encoder of the maximum rate that frames could be submitted to the encoder during realtime encoding.  This allows the encoder to configure itself to ensure this capability.
		This property can only be used when kVTCompressionPropertyKey_RealTime has been set to true.
		Unlike kVTCompressionPropertyKey_ExpectedFrameRate, this property informs the maximum possible rate that the VTCompressionSession could see, not the average frame rate that is expected in normal operation.
		By default, the property has a value of zero indicating "unknown".
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MaximumRealTimeFrameRate API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos); // Read/write, CFNumber, Optional

/*!
	@constant	kVTCompressionPropertyKey_BaseLayerFrameRateFraction
	@abstract
		This property indicates the desired frame rate fraction of the base layer.
	@discussion
		This property indicates the fraction of total frames submitted that should be encoded in the base layer.
		For example, a value of 0.5 means that half of the frames are in the base layer, and half are in the enhancement layer.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_BaseLayerFrameRateFraction API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFNumber<Float>, Optional

/*!
	@constant	kVTCompressionPropertyKey_BaseLayerBitRateFraction
	@abstract
		This property indicates the desired bit rate fraction of the base layer
	@discussion
		This is not a hard limit; the encoder will attempt to satisfy this ratio when possible. If not set, the encoder will manage the ratio.
		For example: If the target bitrate is set to 500kbps and kVTCompressionPropertyKey_BaseLayerBitRateFraction is set to 0.6, the base layer will be given a
		budget of 300kbps and the enhancement layer 200kbps.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_BaseLayerBitRateFraction API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFNumber<Float>, Optional

/*!
	@constant	kVTCompressionPropertyKey_ExpectedDuration
	@abstract
		Indicates the expected total duration for the compression session, if known.
	@discussion
		By default, this is zero, indicating "unknown".
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ExpectedDuration API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFNumber(seconds), Optional

/*!
	@constant	kVTCompressionPropertyKey_BaseLayerFrameRate
	@abstract
		This property indicates the desired frame rate for the base temporal layer used in hierarchical video encoding.
	@discussion
		The frame rate is measured in frames per second.
		This property is only implemented by encoders which support hierarchical frame encoding, and requests that this encoding feature be enabled.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_BaseLayerFrameRate API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFNumber, Optional

/*!
	 @constant	kVTCompressionPropertyKey_ReferenceBufferCount
	 @abstract
		The client will be able to control the the maximum allowed ReferenceBufferCount using this optional key.
	 @discussion
		This is typically used to force the encoder to use lower count than allowed by the stantard for a level/profile.
		The encoder will fail and  report an error if the requested value exceeds the limit set by the standard for such a level/profile.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ReferenceBufferCount API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos); // CFNumber, Optional


/*!
	@constant	kVTCompressionPropertyKey_CalculateMeanSquaredError
	@abstract
		This property requests that the encoder measure and output the Mean Squared Error(MSE) quality metric.
	@discussion
		The MSE value returned may be measured using an internal representation of the decoded frame which may lack filtering or processing present in the actual decoded frame.  Because of this, there may be a small delta between the reported MSE and the true MSE.
		If supported, the MSE values will be returned as sample buffer attachments on the encoded frame using the kVTSampleAttachmentKey_QualityMetrics key.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_CalculateMeanSquaredError API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos); // Read/write, CFBoolean


/*!
	@constant	kVTSampleAttachmentKey_QualityMetrics
	@abstract
		The value for this key contain quality-related metadata from the video encoder for a video frame.
	@discussion
		The video encoder will attach this via the CMSampleBufferGetSampleAttachmentsArray interface before emitting the sample buffer.
*/
VT_EXPORT const CFStringRef kVTSampleAttachmentKey_QualityMetrics API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos); //CFDictionary

/*!
	@constant	kVTSampleAttachmentQualityMetricsKey_LumaMeanSquaredError
	@abstract
		Key for mean squared error (MSE) of the encoded Luma channel from the video encoder.
	@discussion
		For single-view video, a CFNumber value is returned.
		For multi-view video, a CFArray value is returned, and each element (CFNumber) in the CFArray includes MSE for the corresponding view.
		The video encoder will attach this in kVTSampleAttachmentKey_QualityMetrics via the CMSampleBufferGetSampleAttachmentsArray interface before emitting the sample buffer.
*/
VT_EXPORT const CFStringRef kVTSampleAttachmentQualityMetricsKey_LumaMeanSquaredError API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos); // CFNumber, CFArray

/*!
	@constant	kVTSampleAttachmentQualityMetricsKey_ChromaBlueMeanSquaredError
	@abstract
		Key for mean squared error (MSE) of the encoded Chroma Blue channel from the video encoder.
	@discussion
		For single-view video, a CFNumber value is returned.
		For multi-view video, a CFArray value is returned, and each element (CFNumber) in the CFArray includes MSE for the corresponding view.
		The video encoder will attach this in kVTSampleAttachmentKey_QualityMetrics via the CMSampleBufferGetSampleAttachmentsArray interface before emitting the sample buffer.
**/
VT_EXPORT const CFStringRef kVTSampleAttachmentQualityMetricsKey_ChromaBlueMeanSquaredError API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos); // CFNumber, CFArray

/*!
	@constant	kVTSampleAttachmentQualityMetricsKey_ChromaRedMeanSquaredError
	@abstract
		Key for mean squared error (MSE) of the encoded Chroma Red channel from the video encoder.
	@discussion
		For single-view video, a CFNumber value is returned.
		For multi-view video, a CFArray value is returned, and each element (CFNumber) in the CFArray includes MSE for the corresponding view.
		The video encoder will attach this in kVTSampleAttachmentKey_QualityMetrics via the CMSampleBufferGetSampleAttachmentsArray interface before emitting the sample buffer.
*/
VT_EXPORT const CFStringRef kVTSampleAttachmentQualityMetricsKey_ChromaRedMeanSquaredError API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos); // CFNumber, CFArray



#pragma mark Hardware acceleration
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
VT_EXPORT const CFStringRef kVTVideoEncoderSpecification_EnableHardwareAcceleratedVideoEncoder API_AVAILABLE(macos(10.9), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos); // CFBoolean, Optional, true by default

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
VT_EXPORT const CFStringRef kVTVideoEncoderSpecification_RequireHardwareAcceleratedVideoEncoder API_AVAILABLE(macos(10.9), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos); // CFBoolean, Optional

/*!
	@constant	kVTCompressionPropertyKey_UsingHardwareAcceleratedVideoEncoder
	@abstract
		If set to kCFBooleanTrue, a hardware accelerated video encoder is being used.
	@discussion
		You can query this property using VTSessionCopyProperty after you have enabled hardware
		accelerated encode using kVTVideoEncoderSpecification_EnableHardwareAcceleratedVideoEncoder
		to see if a hardware accelerated encoder was selected.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_UsingHardwareAcceleratedVideoEncoder API_AVAILABLE(macos(10.9), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos); // CFBoolean, Read; assumed false by default

/*!
	@constant	kVTVideoEncoderSpecification_RequiredEncoderGPURegistryID
	@abstract
		If set, the VideoToolbox will only use a hardware encoder running on the GPU specified by the provided GPU registryID.
	@discussion
		This specification implies kVTVideoEncoderSpecification_EnableHardwareAcceleratedVideoEncoder.  A separate hardware encode opt-in is not required.
		The GPU registryID can be obtained from a MTLDevice using [MTLDevice registryID] or can be obtained from OpenGL or OpenCL.
*/
VT_EXPORT const CFStringRef kVTVideoEncoderSpecification_RequiredEncoderGPURegistryID API_AVAILABLE(macos(10.14), ios(13.0), tvos(13.0), visionos(1.0)) API_UNAVAILABLE(watchos); // CFNumber, Optional

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
VT_EXPORT const CFStringRef kVTVideoEncoderSpecification_PreferredEncoderGPURegistryID API_AVAILABLE(macos(10.14), ios(13.0), tvos(13.0), visionos(1.0)) API_UNAVAILABLE(watchos); // CFNumber, Optional

/*!
	@constant	kVTCompressionPropertyKey_UsingGPURegistryID
	@abstract
	returns CFNumber indicating the gpu registryID of the encoder that was selected.  NULL indicates a built-in encoder or software encode was used.
	@discussion
		You can query this property using VTSessionCopyProperty after building a VTCompressionSession to find out which GPU the encoder is using.
		If a encoder based on a built-in GPU was used it will return NULL.  If a software encoder is used, it will return NULL
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_UsingGPURegistryID API_AVAILABLE(macos(10.14), ios(13.0), tvos(13.0), visionos(1.0)) API_UNAVAILABLE(watchos); // CFNumberRef, Read;

/*!
	@constant  kVTCompressionPropertyKey_SupportsBaseFrameQP
	@abstract
		This property can be queried to determine if the encoder supports base frame QP requests.
	@discussion
		If this property returns kCFBooleanTrue, it indicates that the encoder supports base frame QP requests through kVTEncodeFrameOptionKey_BaseFrameQP. If it returns false or kVTPropertyNotSupportedErr, base frame QP requests will cause errors on VTCompressionSessionEncodeFrame calls, or will be ignored.

*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_SupportsBaseFrameQP API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos); // Read only, CFBoolean, Optional, false by default

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
VT_EXPORT const CFStringRef kVTEncodeFrameOptionKey_ForceKeyFrame API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); //  CFBoolean

/*!
	@constant  kVTEncodeFrameOptionKey_BaseFrameQP
	@abstract
		CFNumberRef requesting the current frame to use the provided base frame QP.
	@discussion
		This value is set in the frameProperties CFDictionary passed to VTCompressionSessionEncodeFrame to force
		the QP value for the current frame. This is an optional parameter. Use it only when you have a specific requirement
		for the video quality and you are familiar with frame QP and are prepared to assume full responsibility for rate control.
		Otherwise it is strongly encouraged to rely on the encoder’s rate control for adjusting frame QP.
 
		Setting BaseFrameQP turns off standard rate control and will cause the following properties to be ignored::
			kVTCompressionPropertyKey_DataRateLimits
			kVTCompressionPropertyKey_AverageBitRate
			kVTCompressionPropertyKey_BaseLayerBitRateFraction
			kVTCompressionPropertyKey_Quality
			kVTCompressionPropertyKey_MaxAllowedFrameQP
			kVTCompressionPropertyKey_MinAllowedFrameQP
 
		If kVTEncodeFrameOptionKey_BaseFrameQP is used, it must be set for all frames in a session. The QP value specified is
		frame-level but macro-block level QP may be modulated inside a frame. There will be no rate-control related frame dropping
		if kVTEncodeFrameOptionKey_BaseFrameQP is used.

		kVTEncodeFrameOptionKey_BaseFrameQP is only supported if the encoder returns kCFBooleanTrue when the
		kVTCompressionPropertyKey_SupportsBaseFrameQP is queried. If this FrameOptionKey is set for encoder which
		does not support it, it will be ignored.

		Note that it may not be possible for the encoder to accommodate all requests.
*/
VT_EXPORT const CFStringRef kVTEncodeFrameOptionKey_BaseFrameQP API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos); // CFNumberRef, Optional


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
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_CleanAperture API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFDictionary (see CMFormatDescription.h), Optional

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
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_PixelAspectRatio API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFDictionary (see CMFormatDescription.h), Optional

/*!
	@constant	kVTCompressionPropertyKey_FieldCount
	@abstract
		Indicates whether the frames should be encoded progressive (1) or interlaced (2).
	@discussion
		The field count will be set on the format description for output samples,
		and may affect source frame scaling.
		NULL is a valid value for this property.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_FieldCount API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFNumber (see kCMFormatDescriptionExtension_FieldCount), Optional

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
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_FieldDetail API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFString (see kCMFormatDescriptionExtension_FieldDetail), Optional

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
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_AspectRatio16x9 API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFBoolean, Optional

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
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ProgressiveScan API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFBoolean, Optional

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
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ColorPrimaries API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFString (see kCMFormatDescriptionExtension_ColorPrimaries), Optional

/*!
	@constant	kVTCompressionPropertyKey_TransferFunction
	@abstract
		Indicates transfer function for compressed content.
	@discussion
		Some video encoders may enforce specific colorimetry; 
		in those cases this property will be read-only (SetProperty will return kVTPropertyReadOnlyErr).
		The value will be set on the format description for output sample buffers.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_TransferFunction API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFString (see kCMFormatDescriptionExtension_TransferFunction), Optional

/*!
	@constant	kVTCompressionPropertyKey_YCbCrMatrix
	@abstract
		Indicates YCbCr matrix for compressed content.
	@discussion
		Some video encoders may enforce specific colorimetry; 
		in those cases this property will be read-only (SetProperty will return kVTPropertyReadOnlyErr).
		The value will be set on the format description for output sample buffers.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_YCbCrMatrix API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFString (see kCMFormatDescriptionExtension_YCbCrMatrix), Optional

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
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ICCProfile API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFData (see kCMFormatDescriptionExtension_ICCProfile), Optional

/*!
	@constant	kVTCompressionPropertyKey_MasteringDisplayColorVolume
	@abstract
		The value is 24 bytes containing a big-endian structure as defined in ISO/IEC 23008-2:2015(E), D.2.28 Mastering display colour volume SEI message.
	@discussion
		The value will be set on the format description for output sample buffers,
		and incorporated into the appropriate SEI NAL unit where supported by the encoder.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MasteringDisplayColorVolume API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFData(24 bytes) (see kCMFormatDescriptionExtension_MasteringDisplayColorVolume), Optional

/*!
	@constant	kVTCompressionPropertyKey_ContentLightLevelInfo
	@abstract
		The value is 4 bytes containing a big-endian structure as defined in the Content Light Level Info SEI message.
	@discussion
		The value will be set on the format description for output sample buffers,
		and incorporated into the appropriate SEI NAL unit where supported by the encoder.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ContentLightLevelInfo API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFData(4 bytes) (see kCMFormatDescriptionExtension_ContentLightLevelInfo), Optional


/*!
	@constant  kVTCompressionPropertyKey_GammaLevel
	@abstract
		Indicates gamma level for compressed content.
	@discussion
		This property allows the caller to specify a gamma value to include in the CMVideoFormatDescription attached to output CMSampleBuffers. It does not change pixel data being encoded.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_GammaLevel API_AVAILABLE(macos(10.9), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFNumber (see kCMFormatDescriptionExtension_GammaLevel), Optional
	

/*!
	@constant	kVTCompressionPropertyKey_AlphaChannelMode
	@abstract
		Specifies whether the source images' RGB values have been premultiplied by the alpha channel values.
	@discussion
		Video compression will fail if source image buffers have a mismatched value in their kCVImageBufferAlphaChannelMode attachment.
		If this property is not set, the encoder may read the first source image buffer's kCVImageBufferAlphaChannelMode attachment.
		If neither the property nor the first buffer's attachment is set, defaults to kVTAlphaChannelMode_PremultipliedAlpha.
 */
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_AlphaChannelMode	API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, Optional, CFString(kVTAlphaChannelMode_*); if property is not set, matches first source frame's attachment; if that's also not set, defaults to premultiplied alpha
VT_EXPORT const CFStringRef kVTAlphaChannelMode_StraightAlpha	API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTAlphaChannelMode_PremultipliedAlpha	API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), visionos(1.0)) API_UNAVAILABLE(watchos);

	
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
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_PixelTransferProperties API_AVAILABLE(macos(10.8), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/Write, CFDictionary containing properties from VTPixelTransferProperties.h.
	
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
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MultiPassStorage API_AVAILABLE(macos(10.10), ios(8.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos); // VTMultiPassStorage, optional, default is NULL

#pragma mark Encoder information
	
/*!
	@constant	kVTCompressionPropertyKey_EncoderID
	@abstract
		Specifies a particular video encoder by its ID string.
	@discussion
		Matches the value specified in kVTVideoEncoderSpecification_EncoderID, and the kVTVideoEncoderList_EncoderID value returned from VTCopyVideoEncoderList.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_EncoderID API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), visionos(1.0)) API_UNAVAILABLE(watchos); // CFStringRef

/*!
	@constant	kVTCompressionPropertyKey_RecommendedParallelizationLimit
	@abstract
		If supported by the underlying video encoder, returns the recommended number of VTCompressionSessions to instantiate in a parallel encoding configuration.
	@discussion
		Parallel encoding VTCompressionSessions require the use of the properties kVTCompressionPropertyKey_MoreFramesBeforeStart, kVTCompressionPropertyKey_MoreFramesAfterEnd, and kVTCompressionPropertyKey_SourceFrameCount.
		e.g. If the property returns 4, a setup for 4 VTCompressionSessions on a 400 frame movie might look like:
			compressionSession1
				kVTCompressionPropertyKey_MoreFramesBeforeStart = false
				kVTCompressionPropertyKey_MoreFramesAfterEnd = true
				kVTCompressionPropertyKey_SourceFrameCount = 100
			compressionSession2
				kVTCompressionPropertyKey_MoreFramesBeforeStart = true
				kVTCompressionPropertyKey_MoreFramesAfterEnd = true
				kVTCompressionPropertyKey_SourceFrameCount = 100
			compressionSession3
				kVTCompressionPropertyKey_MoreFramesBeforeStart = true
				kVTCompressionPropertyKey_MoreFramesAfterEnd = true
				kVTCompressionPropertyKey_SourceFrameCount = 100
			compressionSession4
				kVTCompressionPropertyKey_MoreFramesBeforeStart = true
				kVTCompressionPropertyKey_MoreFramesAfterEnd = false
				kVTCompressionPropertyKey_SourceFrameCount = 100
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_RecommendedParallelizationLimit API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos); // Read-only, CFNumber<int>

/*!
	@constant	kVTCompressionPropertyKey_RecommendedParallelizedSubdivisionMinimumFrameCount
	@abstract
		If supported by the underlying video encoder, returns the recommended minimum number of video frames for a given subdivision in a parallel encoding configuration.
	@discussion
		For best results, ensure that the total number of frames of a parallelized subdivision is greater than or equal to this returned value.
		See also kVTCompressionPropertyKey_RecommendedParallelizationLimit
		See also kVTCompressionPropertyKey_RecommendedParallelizedSubdivisionMinimumDuration
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_RecommendedParallelizedSubdivisionMinimumFrameCount API_AVAILABLE(macos(14.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos); // Read-only, CFNumber<uint64_t>

/*!
	@constant	kVTCompressionPropertyKey_RecommendedParallelizedSubdivisionMinimumDuration
	@abstract
		If supported by the underlying video encoder, returns the recommended minimum duration for a given subdivision in a parallel encoding configuration.
	@discussion
		For best results, ensure that the total duration of a parallelized subdivision is greater than or equal to this returned value.
		See also kVTCompressionPropertyKey_RecommendedParallelizationLimit
		See also kVTCompressionPropertyKey_RecommendedParallelizedSubdivisionMinimumFrameCount
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_RecommendedParallelizedSubdivisionMinimumDuration API_AVAILABLE(macos(14.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos); // Read-only, CMTime as CFDictionary

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
							API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0), visionos(1.0)) API_UNAVAILABLE(watchos);

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
VT_EXPORT const CFStringRef kVTVideoEncoderSpecification_EnableLowLatencyRateControl API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFBoolean, Optional

/*!
	@constant	kVTCompressionPropertyKey_MaxAllowedFrameQP
	@abstract
		Specifies the maximum allowed encoded frame QP (Quantization Parameter).
	@discussion
		This is an optional parameter. Use it only when you have a specific requirement for the video quality and you are
		familiar with frame QP. To satisfy this requirement, the encoder may drop frames to maintain bitrate and QP goals.
		This is not supported in all encoders or in all encoder operating modes. kVTPropertyNotSupportedErr will be
		returned when this option is not supported.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MaxAllowedFrameQP API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFNumberRef, Optional

/*!
	@constant	kVTCompressionPropertyKey_MinAllowedFrameQP
	@abstract
		Specifies the minimum allowed encoded frame QP (Quantization Parameter).
	@discussion
		This is an optional parameter. Use it only when you have a specific requirement for the video quality and you are
		familiar with frame QP. 
		This is not supported in all encoders or in all encoder operating modes. kVTPropertyNotSupportedErr will be
		returned when this option is not supported.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MinAllowedFrameQP API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFNumberRef, Optional

/*!
	@constant	kVTCompressionPropertyKey_EnableLTR
	@abstract
		Enable Long Term Reference (LTR) frames during encoding
	@discussion
		When an LTR frame is encoded, encoder will signal a unique token of the LTR frame in the encoder callback through:
			kVTSampleAttachmentKey_RequireLTRAcknowledgementToken
		Clients are responsible for reporting acknowledged LTR frames to the encoder through:
			kVTEncodeFrameOptionKey_AcknowledgedLTRTokens
		Client can request a refresh frame at any time through:
			kVTEncodeFrameOptionKey_ForceLTRRefresh
		Encoder will encode a P frame by using one of acknowledged LTR frames
		as the reference. Encoder will encode a new reference frame using an acknowledged LTR, or an IDR if no LTR frames have been acknowledged.

		Also see:
			kVTEncodeFrameOptionKey_AcknowledgedLTRTokens
			kVTEncodeFrameOptionKey_ForceLTRRefresh
			kVTSampleAttachmentKey_RequireLTRAcknowledgementToken
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_EnableLTR API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos); // Read/write, CFBoolean, Optional

/*!
	@constant	kVTEncodeFrameOptionKey_AcknowledgedLTRTokens
	@abstract
		A CFArray of CFNumbers containing the kVTSampleAttachmentKey_RequireLTRAcknowledgementToken values which have been successfully sent to the receiver and can be used as references
	@discussion
		When an LTR frame is encoded, the encoder will return a unique token for the LTR frame on the output CMSampleBuffer through kVTSampleAttachmentKey_RequireLTRAcknowledgementToken.
					This token is then returned to the encoder via kVTEncodeFrameOptionKey_AcknowledgedLTRTokens when the LTR frame is received by the remote consumer(s).

	Also see:
		kVTCompressionPropertyKey_EnableLTR
		kVTEncodeFrameOptionKey_ForceLTRRefresh
		kVTSampleAttachmentKey_RequireLTRAcknowledgementToken
*/
VT_EXPORT const CFStringRef kVTEncodeFrameOptionKey_AcknowledgedLTRTokens API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos); // CFArray[CFNumberRef], Optional

/*!
	@constant	kVTEncodeFrameOptionKey_ForceLTRRefresh
	@abstract
		Set this option to kCFBooleanTrue to force an LTR refresh
	@discussion
		When the encoder receives this request on an incoming frame, the encoder will encode a new reference frame using a previously 
					acknowledged LTR, or it will encode a new IDR if no LTR frames have been acknowledged.

		Also see:
			kVTCompressionPropertyKey_EnableLTR
			kVTEncodeFrameOptionKey_AcknowledgedLTRTokens
			kVTSampleAttachmentKey_RequireLTRAcknowledgementToken
*/
VT_EXPORT const CFStringRef kVTEncodeFrameOptionKey_ForceLTRRefresh API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos); // CFNumberRef, Optional

/*!
	@constant	kVTSampleAttachmentKey_RequireLTRAcknowledgementToken
	@abstract
		CFNumber containing a unique token for this LTR
	@discussion
		This CMSampleBuffer attachment contains a unique token which can be returned to the encoder through 
					kVTEncodeFrameOptionKey_AcknowledgedLTRTokens to indicate that the LTR has been received and may be used as a reference.

		Also see:
			kVTCompressionPropertyKey_EnableLTR
			kVTEncodeFrameOptionKey_AcknowledgedLTRTokens
			kVTEncodeFrameOptionKey_ForceLTRRefresh
*/
VT_EXPORT const CFStringRef kVTSampleAttachmentKey_RequireLTRAcknowledgementToken API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos); // CFNumberRef, Optional

#pragma mark Multi-image compression

/*!
    @constant	kVTCompressionPropertyKey_MVHEVCVideoLayerIDs
    @abstract
        Requests multi-image encoding; advises encoder to expect CMTaggedBufferGroups with specific CMTags referencing these MV-HEVC VideoLayerIDs.
    @discussion
        MV-HEVC specific.
        The property value is a CFArray containing VideoLayerIDs as CFNumbers.
        The property is NULL by default.
 */
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MVHEVCVideoLayerIDs API_AVAILABLE(macos(14.0), ios(17.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos); // Read/write, CFArray(CFNumber), Optional

/*!
    @constant	kVTCompressionPropertyKey_MVHEVCViewIDs
    @abstract
        Specifies the ViewIDs corresponding to the VideoLayerIDs provided via kVTCompressionPropertyKey_MVHEVCVideoLayerIDs.
    @discussion
        MV-HEVC specific.
        The property value is a CFArray containing ViewIDs as CFNumbers.
        The entries in this array should be in the same order and have the same count as the value set via kVTCompressionPropertyKey_MVHEVCVideoLayerIDs.
        The property is NULL by default.
 */
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MVHEVCViewIDs API_AVAILABLE(macos(14.0), ios(17.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos); // Read/write, CFArray(CFNumber), Optional

/*!
    @constant	kVTCompressionPropertyKey_MVHEVCLeftAndRightViewIDs
    @abstract
        Specifies which of the ViewIDs provided via kVTCompressionPropertyKey_MVHEVCViewIDs is the "left view id" and which is the "right view id".
    @discussion
        MV-HEVC specific.
        These ViewIDs will be incorporated into the 3D Reference Displays Info SEI message.
        The property value is a CFArray containing two ViewIDs as CFNumbers with the first correspponding to the left eye and the second corresponding to the right eye.
        The property is NULL by default.
 */
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MVHEVCLeftAndRightViewIDs API_AVAILABLE(macos(14.0), ios(17.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos); // Read/write, CFArray[CFNumber(left view ID), CFNumber(right view ID)], Optional

#pragma mark VideoExtendedUsage signaling

/*!
    @constant	kVTCompressionPropertyKey_HeroEye
    @abstract
        Specifies the value of kCMFormatDescriptionExtension_HeroEye.
    @discussion
        The value will be set on the format description for output samples and may affect the decoded frame presentation.
 */
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_HeroEye API_AVAILABLE(macos(14.0), ios(17.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);	// CFString, see kCMFormatDescriptionExtension_HeroEye
VT_EXPORT const CFStringRef kVTHeroEye_Left API_AVAILABLE(macos(26.0), ios(26.0), visionos(26.0)) API_UNAVAILABLE(tvos, watchos);
VT_EXPORT const CFStringRef kVTHeroEye_Right API_AVAILABLE(macos(26.0), ios(26.0), visionos(26.0)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant	kVTCompressionPropertyKey_StereoCameraBaseline
    @abstract
        Specifies the value of kCMFormatDescriptionExtension_StereoCameraBaseline.
    @discussion
        The value will be set on the format description for output samples and may affect the decoded frame presentation.
 */
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_StereoCameraBaseline API_AVAILABLE(macos(14.0), ios(17.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);	// CFNumber(uint32), see kCMFormatDescriptionExtension_StereoCameraBaseline

/*!
    @constant	kVTCompressionPropertyKey_HorizontalDisparityAdjustment
    @abstract
        Specifies the value of kCMFormatDescriptionExtension_HorizontalDisparityAdjustment.
    @discussion
        The value will be set on the format description for output samples and may affect the decoded frame presentation.
 */

VT_EXPORT const CFStringRef kVTCompressionPropertyKey_HorizontalDisparityAdjustment API_AVAILABLE(macos(14.0), ios(17.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);	// CFNumber(int32), see kCMFormatDescriptionExtension_HorizontalDisparityAdjustment

/*!
    @constant    kVTCompressionPropertyKey_HasLeftStereoEyeView
    @abstract
        Specifies the value of kCMFormatDescriptionExtension_HasLeftStereoEyeView.
    @discussion
        The value will be set on the format description for output samples and may affect the decoded frame presentation.
 */
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_HasLeftStereoEyeView API_AVAILABLE(macos(14.0), ios(17.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);  // CFBoolean, see kCMFormatDescriptionExtension_HasLeftStereoEyeView

/*!
    @constant    kVTCompressionPropertyKey_HasRightStereoEyeView
    @abstract
        Specifies the value of kCMFormatDescriptionExtension_HasRightStereoEyeView.
    @discussion
        The value will be set on the format description for output samples and may affect the decoded frame presentation.
 */
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_HasRightStereoEyeView API_AVAILABLE(macos(14.0), ios(17.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);  // CFBoolean, see kCMFormatDescriptionExtension_HasRightStereoEyeView

/*!
    @constant    kVTCompressionPropertyKey_HorizontalFieldOfView
    @abstract
        Specifies the value of kCMFormatDescriptionExtension_HorizontalFieldOfView.
    @discussion
    The value is a CFNumber holding an unsigned 32-bit integer that is interpreted in millidegree or thousandths of a degree (e.g., 123456 is 123.456 degree).
    This property is optional and should only be specified if the field of view is known.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_HorizontalFieldOfView API_AVAILABLE(macos(14.4), ios(17.4), visionos(1.1)) API_UNAVAILABLE(tvos, watchos);     // CFNumber(uint32) as millidegrees

/*!
	@constant	kVTCompressionPropertyKey_ProjectionKind
	@abstract
		Specifies the value of kCMFormatDescriptionExtension_ProjectionKind.
	@discussion
		The value will be set on the format description for output samples and may affect the decoded frame presentation.
 */
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ProjectionKind API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);  // CFString, see kCMFormatDescriptionExtension_ProjectionKind.
VT_EXPORT const CFStringRef kVTProjectionKind_Rectilinear API_AVAILABLE(macos(26.0), ios(26.0), visionos(26.0)) API_UNAVAILABLE(tvos, watchos);
VT_EXPORT const CFStringRef kVTProjectionKind_Equirectangular API_AVAILABLE(macos(26.0), ios(26.0), visionos(26.0)) API_UNAVAILABLE(tvos, watchos);
VT_EXPORT const CFStringRef kVTProjectionKind_HalfEquirectangular API_AVAILABLE(macos(26.0), ios(26.0), visionos(26.0)) API_UNAVAILABLE(tvos, watchos);
VT_EXPORT const CFStringRef kVTProjectionKind_ParametricImmersive API_AVAILABLE(macos(26.0), ios(26.0), visionos(26.0)) API_UNAVAILABLE(tvos, watchos);
/*!
	@constant	kVTCompressionPropertyKey_ViewPackingKind
	@abstract
		Specifies the value of kCMFormatDescriptionExtension_ViewPackingKind.
	@discussion
		The value will be set on the format description for output samples and may affect the decoded frame presentation.
 */
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ViewPackingKind API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos); // CFString, see kCMFormatDescriptionExtension_ViewPackingKind.
VT_EXPORT const CFStringRef kVTViewPackingKind_SideBySide API_AVAILABLE(macos(26.0), ios(26.0), visionos(26.0)) API_UNAVAILABLE(tvos, watchos);
VT_EXPORT const CFStringRef kVTViewPackingKind_OverUnder API_AVAILABLE(macos(26.0), ios(26.0), visionos(26.0)) API_UNAVAILABLE(tvos, watchos);
	
/*!
	@constant kVTCompressionPropertyKey_CameraCalibrationDataLensCollection
	@abstract	Specifies intrinsic and extrinsic parameters for single or multiple lenses.
	@discussion
		The property value is an array of dictionaries describing the camera calibration data for each lens. The camera calibration data includes intrinsics and extrinics with other parameters.
		For a stereoscopic camera system, the left and right lens signaling can be done with the kVTCompressionPropertyCameraCalibrationKey_LensRole key and its value.
 */
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_CameraCalibrationDataLensCollection API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));	// CFArray of CFDictionaries

/*!
	The following keys are required in each kVTCompressionPropertyKey_CameraCalibrationDataLensCollection dictionary.

	@constant kVTCompressionPropertyCameraCalibrationKey_LensAlgorithmKind
	@abstract	Specifies the camera calibration methodology.
	@discussion
		If the algorithm kind is ParametricLens, the camera lens collection requires camera intrinsic and extrinsic parameters.

	@constant kVTCompressionPropertyCameraCalibrationKey_LensDomain
	@abstract	Specifies the kind of lens (e.g., color).

	@constant kVTCompressionPropertyCameraCalibrationKey_LensIdentifier
	@abstract	Specifies a unique number associated with a lens.

	@constant kVTCompressionPropertyCameraCalibrationKey_LensRole
	@abstract	Specifies the particular use of the lens in the camera system (e.g., left or right for a stereo system).
	@discussion
		For a stereoscopic camera system, one lens should have the left role and another should have the right role.

	@constant kVTCompressionPropertyCameraCalibrationKey_LensDistortions
	@abstract	Specifies the first and second radial distortion coefficients(k1 and k2) used to correct the distortion that appeared as curved lines for straight lines and the first and second tangential distortion coefficients(p1 and p2) used to correct the distortion caused by a lens's improper alignment of physical elements.
	@discussion
		The values are in a CFArray of four CFNumbers in k1, k2, p1 and p2 order.

    @constant kVTCompressionPropertyCameraCalibrationKey_LensFrameAdjustmentsPolynomialX
    @abstract    Specifies a three element polynomial for mapping x axis UV parameters with an adjustment using the equation `x' = polynomialX[0] + polynomialX[1]*x + polynomialX[2]*x^3`.
    @discussion
		The values are in a CFArray of three CFNumbers(float) in the order polynomialX[0], polynomialX[1] & polynomialX[2].
		The polynomial transform origin is at the center of the frame. The default values of elements of polynomialX[] are [0.0, 1.0, 0.0].

    @constant kVTCompressionPropertyCameraCalibrationKey_LensFrameAdjustmentsPolynomialY
    @abstract    Specifies a three element polynomial for mapping y axis UV parameters with an adjustment using the equation `y' = polynomialY[0] + polynomialY[1]*y + polynomialY[2]*y^3`.
    @discussion
		The values are in a CFArray of three CFNumbers(float) in the order polynomialY[0], polynomialY[1] & polynomialY[2].
		The polynomial transform origin is at the center of the frame. The default values of elements of polynomialY[] are [0.0, 1.0, 0.0].
 
	@constant kVTCompressionPropertyCameraCalibrationKey_RadialAngleLimit
	@abstract	Specifies the outer limit of the calibration validity in degrees of angle eccentric from the optical axis.
	@discussion
		The value is linked to radial distortion corrections with k1 and k2.

	@constant kVTCompressionPropertyCameraCalibrationKey_IntrinsicMatrix
	@abstract	Specifies the 3x3 camera intrinsic matrix for camera calibration.
	@discussion
		Camera intrinsic matrix is a CFData containing a matrix_float3x3, which is column-major. Each element is in IEEE754 native-endian 32-bit floating point. It has the following contents:
			fx	s	cx
			0	fy	cy
			0	0	1
			fx and fy are the focal length in pixels. For square pixels, they will have the same value.
			cx and cy are the coordinates of the principal point. The origin is the upper left of the frame.
			s is an optional skew factor.

	@constant kVTCompressionPropertyCameraCalibrationKey_IntrinsicMatrixProjectionOffset
	@abstract	Specifies the offset of the point of perspective relative to the rectilinear projection.

	@constant kVTCompressionPropertyCameraCalibrationKey_IntrinsicMatrixReferenceDimensions
	@abstract	Specifies the image dimensions to which the camera’s intrinsic matrix values are relative.
	@discussion
		Values are width and height in a CFDictionary. Dictionary keys are compatible with CGSize dictionary, namely "Width" and "Height".

	@constant kVTCompressionPropertyCameraCalibrationKey_ExtrinsicOriginSource
	@abstract	Identifies how the origin of the camera system's extrinsics are determined.
	@discussion
		The 'blin' value indicates the center of transform is determined by the point mid way along the dimensions indicated by the StereoCameraSystemBaselineBox held in the StereoCameraSystemBox.
		Each left and right lens within a stereoscopic camera system is equidistant from this point, so the 'blin' value is halved when associated with the respective left and right lenses.

	@constant kVTCompressionPropertyCameraCalibrationKey_ExtrinsicOrientationQuaternion
	@abstract	Specifies a camera’s orientation to a world or scene coordinate system. The orientation value is a unit quaternion(ix, iy, and iz) instead of the classical 3x3 matrix.
	@discussion
		The values are in a CFArray of three CFNumbers in ix, iy, and iz order.
 */
VT_EXPORT const CFStringRef kVTCompressionPropertyCameraCalibrationKey_LensAlgorithmKind API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));	// CFString one of
VT_EXPORT const CFStringRef kVTCameraCalibrationLensAlgorithmKind_ParametricLens API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));
VT_EXPORT const CFStringRef kVTCompressionPropertyCameraCalibrationKey_LensDomain API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));	// CFString one of
VT_EXPORT const CFStringRef kVTCameraCalibrationLensDomain_Color API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));
VT_EXPORT const CFStringRef kVTCompressionPropertyCameraCalibrationKey_LensIdentifier API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));	// CFNumber(int32)
VT_EXPORT const CFStringRef kVTCompressionPropertyCameraCalibrationKey_LensRole API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));	// CFString one of
VT_EXPORT const CFStringRef kVTCameraCalibrationLensRole_Mono API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));
VT_EXPORT const CFStringRef kVTCameraCalibrationLensRole_Left API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));
VT_EXPORT const CFStringRef kVTCameraCalibrationLensRole_Right API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));
VT_EXPORT const CFStringRef kVTCompressionPropertyCameraCalibrationKey_LensDistortions API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));	// CFArray[CFNumber(float)]
VT_EXPORT const CFStringRef kVTCompressionPropertyCameraCalibrationKey_RadialAngleLimit API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));	// CFNumber(float)
VT_EXPORT const CFStringRef kVTCompressionPropertyCameraCalibrationKey_LensFrameAdjustmentsPolynomialX API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));	// CFArray[CFNumber(float)]
VT_EXPORT const CFStringRef kVTCompressionPropertyCameraCalibrationKey_LensFrameAdjustmentsPolynomialY API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));	// CFArray[CFNumber(float)]
VT_EXPORT const CFStringRef kVTCompressionPropertyCameraCalibrationKey_IntrinsicMatrix API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));	// CFData(matrix_float3x3)
VT_EXPORT const CFStringRef kVTCompressionPropertyCameraCalibrationKey_IntrinsicMatrixProjectionOffset API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));	// CFNumber(float)
VT_EXPORT const CFStringRef kVTCompressionPropertyCameraCalibrationKey_IntrinsicMatrixReferenceDimensions API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));	// CGSize dictionary
VT_EXPORT const CFStringRef kVTCompressionPropertyCameraCalibrationKey_ExtrinsicOriginSource API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));	// CFString one of
VT_EXPORT const CFStringRef kVTCameraCalibrationExtrinsicOriginSource_StereoCameraSystemBaseline API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));
VT_EXPORT const CFStringRef kVTCompressionPropertyCameraCalibrationKey_ExtrinsicOrientationQuaternion API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));	// CFArray[CFNumber(float)], , ix, iy & iz order 

/*!
    @constant	kVTCompressionPropertyKey_SuggestedLookAheadFrameCount
	@abstract
		Requests that the encoder retain the specified number of frames during encoding. These frames will be used for additional analysis and statistics
		gathering before the frame is finally encoded at the end of the window. When this property is not set, video encoder will automatically determine
		the number of lookahead frames.
	@discussion
		Encoder will choose number of lookahead frames closer to the suggested value based on internal configuration. This property directly affects latency
		of the video encoder. The following properties also affect look ahead frames:
		1. Value of this property must be less than or equal to `kVTCompressionPropertyKey_MaxFrameDelayCount`.
		2. This property is ignored when `VTVideoEncoderSpecification_EnableLowLatencyRateControl` is set to true
		3. This property is ignored when `kVTCompressionPropertyKey_Quality` is set to 1.0
		4. This property can not be used in conjunction with multi-pass feature (`kVTCompressionPropertyKey_MultiPassStorage`)
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_SuggestedLookAheadFrameCount API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos); // Read/write, CFNumberRef, Optional

/*!
	@constant	kVTCompressionPropertyKey_SpatialAdaptiveQPLevel
	@abstract
		Control spatial adaptation of the quantization parameter (QP) based on per-frame statistics.
		If set to kVTQPModulationLevel_Disable, spatial QP adaptation is not applied based on per-frame statistics.
		If set to kVTQPModulationLevel_Default, video encoder is allowed to apply spatial QP adaptation for each macro block (or coding unit) within a video frame.
		QP adaptation is based on spatial characteristics of a frame and the level of spatial QP adaptation is decided internally by the rate controller.
	@discussion
		This property must be disabled when low latency rate control is enabled. Support for this property is codec dependent.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_SpatialAdaptiveQPLevel API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos); // Read/write, CFNumberRef, Optional
enum {
	kVTQPModulationLevel_Default = -1,
	kVTQPModulationLevel_Disable = 0,
};

#pragma mark Encoder Settings Assistant

/*!
@constant kVTCompressionPropertyKey_SupportedPresetDictionaries
@abstract
	Where supported by video encoders, returns a dictionary whose keys are the available compression presets (prefixed by `kVTCompressionPreset_`) and the values are dictionaries containing the corresponding settings property key/value pairs.
@discussion
	Clients can select a compression preset for their encoding needs and use its encoder settings to configure the encoder.
	Clients may also use the encoder settings as a base configuration that they can customize as they require.

	See also kVTCompressionPreset_HighQuality, kVTCompressionPreset_Balanced, kVTCompressionPreset_HighSpeed, kVTCompressionPreset_VideoConferencing.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_SupportedPresetDictionaries API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0)); // Read-only, CFDictionary

/*!
@constant kVTCompressionPreset_HighQuality
@abstract
	A preset to achieve a high compression quality.
@discussion
	An encoder configured using this preset is expected to achieve a higher quality with a slower encoding than an encoder configured with the preset kVTCompressionPreset_Balanced or kVTCompressionPreset_HighSpeed.
	The presets kVTCompressionPreset_Balanced and kVTCompressionPreset_HighSpeed may be preferred for a faster encoding.

	See also kVTCompressionPreset_Balanced, kVTCompressionPreset_HighSpeed, kVTCompressionPreset_VideoConferencing.
*/
VT_EXPORT const CFStringRef kVTCompressionPreset_HighQuality API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/*!
@constant kVTCompressionPreset_Balanced
@abstract
	A preset to provide a balanced compression quality and encoding speed.
@discussion
	An encoder configured using this preset is expected to achieve a higher quality than an encoder configured with the preset kVTCompressionPreset_HighSpeed.
	The preset kVTCompressionPreset_HighSpeed may be preferred for a faster encoding.
	The preset kVTCompressionPreset_HighQuality may be preferred for a higher compression quality.

	See also kVTCompressionPreset_HighQuality, kVTCompressionPreset_HighSpeed, kVTCompressionPreset_VideoConferencing.
*/
VT_EXPORT const CFStringRef kVTCompressionPreset_Balanced API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/*!
@constant kVTCompressionPreset_HighSpeed
@abstract
	A preset to provide a high-speed encoding.
@discussion
	An encoder configured using this preset is expected to achieve a faster encoding at a lower compression quality than an encoder configured with the preset kVTCompressionPreset_HighQuality or kVTCompressionPreset_Balanced.
	The presets kVTCompressionPreset_HighQuality and kVTCompressionPreset_Balanced may be preferred for a higher compression quality.

	See also kVTCompressionPreset_HighQuality, kVTCompressionPreset_Balanced, kVTCompressionPreset_VideoConferencing.
*/
VT_EXPORT const CFStringRef kVTCompressionPreset_HighSpeed API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/*!
@constant kVTCompressionPreset_VideoConferencing
@abstract
	A preset to achieve low-latency encoding for real-time communication applications.
@discussion
	This preset requires setting kVTVideoEncoderSpecification_EnableLowLatencyRateControl to kCFBooleanTrue for encoding in the low-latency mode.

	See also kVTCompressionPreset_HighQuality, kVTCompressionPreset_Balanced, kVTCompressionPreset_HighSpeed.
*/
VT_EXPORT const CFStringRef kVTCompressionPreset_VideoConferencing API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

	
CM_ASSUME_NONNULL_END

#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif // VTCOMPRESSIONPROPERTIES_H
