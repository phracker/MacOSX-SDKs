/*
	File:  AVVideoSettings.h

	Framework:  AVFoundation
 
	Copyright 2010-2015 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

/*!
 @header AVVideoSettings
 @abstract
	NSDictionary keys for configuring output video format
	
 @discussion
	A video settings dictionary may take one of two forms:
	
	1. For compressed video output, use only the keys in this header, AVVideoSettings.h.
	2. For uncompressed video output, start with kCVPixelBuffer* keys in <CoreVideo/CVPixelBuffer.h>.
	
	In addition to the keys in CVPixelBuffer.h, uncompressed video settings dictionaries may also contain the following keys:
 
		AVVideoPixelAspectRatioKey
		AVVideoCleanApertureKey
		AVVideoScalingModeKey
		AVVideoColorPropertiesKey
		AVVideoAllowWideColorKey
 
	It is an error to add any other AVVideoSettings.h keys to an uncompressed video settings dictionary.
*/

AVF_EXPORT NSString *const AVVideoCodecKey /* NSString (CMVideoCodecType) */				NS_AVAILABLE(10_7, 4_0);
	AVF_EXPORT NSString *const AVVideoCodecH264 /* @"avc1" */								NS_AVAILABLE(10_7, 4_0);
    AVF_EXPORT NSString *const AVVideoCodecJPEG /* @"jpeg" */								NS_AVAILABLE(10_7, 4_0);
    AVF_EXPORT NSString *const AVVideoCodecAppleProRes4444 /* @"ap4h" */					NS_AVAILABLE(10_7, NA);
    AVF_EXPORT NSString *const AVVideoCodecAppleProRes422   /* @"apcn" */					NS_AVAILABLE(10_7, NA);

// For best results, always use even number values for AVVideoWidthKey and AVVideoHeightKey when encoding to AVVideoCodecH264 or any other format that uses 4:2:0 downsampling
AVF_EXPORT NSString *const AVVideoWidthKey /* NSNumber (encoded pixels) */					NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT NSString *const AVVideoHeightKey /* NSNumber (encoded pixels) */					NS_AVAILABLE(10_7, 4_0);

/*!
 @constant	AVVideoPixelAspectRatioKey
 @abstract	The aspect ratio of the pixels in the video frame
 @discussion
	The value for this key is an NSDictionary containing AVVideoPixelAspectRatio*Key keys.  If no value is specified for this key, the default value for the codec is used.  Usually this is 1:1, meaning square pixels.
 
	Note that prior to OS X 10.9 and iOS 7.0, this key could only be specified as part of the dictionary given for AVVideoCompressionPropertiesKey.  As of OS X 10.9 and iOS 7.0, the top level of an AVVideoSettings dictionary is the preferred place to specify this key.
*/
AVF_EXPORT NSString *const AVVideoPixelAspectRatioKey										NS_AVAILABLE(10_7, 4_0);
	AVF_EXPORT NSString *const AVVideoPixelAspectRatioHorizontalSpacingKey /* NSNumber */	NS_AVAILABLE(10_7, 4_0);
	AVF_EXPORT NSString *const AVVideoPixelAspectRatioVerticalSpacingKey /* NSNumber */		NS_AVAILABLE(10_7, 4_0);

/*!
 @constant	AVVideoCleanApertureKey
 @abstract	Defines the region within the video dimensions that will be displayed during playback
 @discussion
	The value for this key is an NSDictionary containing AVVideoCleanAperture*Key keys.  AVVideoCleanApertureWidthKey and AVVideoCleanApertureHeightKey define a clean rectangle which is centered on the video frame.  To offset this rectangle from center, use AVVideoCleanApertureHorizontalOffsetKey and AVVideoCleanApertureVerticalOffsetKey.  A positive value for AVVideoCleanApertureHorizontalOffsetKey moves the clean aperture region to the right, and a positive value for AVVideoCleanApertureVerticalOffsetKey moves the clean aperture region down.
 
	If no clean aperture region is specified, the entire frame will be displayed during playback.
 
	Note that prior to OS X 10.9 and iOS 7.0, this key could only be specified as part of the dictionary given for AVVideoCompressionPropertiesKey.  As of OS X 10.9 and iOS 7.0, the top level of an AVVideoSettings dictionary is the preferred place to specify this key.
*/
AVF_EXPORT NSString *const AVVideoCleanApertureKey											NS_AVAILABLE(10_7, 4_0);
	AVF_EXPORT NSString *const AVVideoCleanApertureWidthKey /* NSNumber */					NS_AVAILABLE(10_7, 4_0);
	AVF_EXPORT NSString *const AVVideoCleanApertureHeightKey /* NSNumber */					NS_AVAILABLE(10_7, 4_0);
	AVF_EXPORT NSString *const AVVideoCleanApertureHorizontalOffsetKey /* NSNumber */		NS_AVAILABLE(10_7, 4_0);
	AVF_EXPORT NSString *const AVVideoCleanApertureVerticalOffsetKey /* NSNumber */			NS_AVAILABLE(10_7, 4_0);

AVF_EXPORT NSString *const AVVideoScalingModeKey /* NSString */								NS_AVAILABLE(10_7, 5_0);
	/* AVVideoScalingModeFit - Crop to remove edge processing region; preserve aspect ratio of cropped source by reducing specified width or height if necessary.  Will not scale a small source up to larger dimensions. */
	AVF_EXPORT NSString *const AVVideoScalingModeFit										NS_AVAILABLE(10_7, 5_0);
	/* AVVideoScalingModeResize - Crop to remove edge processing region; scale remainder to destination area.  Does not preserve aspect ratio. */
	AVF_EXPORT NSString *const AVVideoScalingModeResize										NS_AVAILABLE(10_7, 5_0);
	/* AVVideoScalingModeResizeAspect - Preserve aspect ratio of the source, and fill remaining areas with black to fit destination dimensions. */
	AVF_EXPORT NSString *const AVVideoScalingModeResizeAspect								NS_AVAILABLE(10_7, 5_0);
	/* AVVideoScalingModeResizeAspectFill - Preserve aspect ratio of the source, and crop picture to fit destination dimensions. */
	AVF_EXPORT NSString *const AVVideoScalingModeResizeAspectFill							NS_AVAILABLE(10_7, 5_0);

/*
	Clients who specify AVVideoColorPropertiesKey must specify a color primary, transfer function, and Y'CbCr matrix.
	Most clients will want to specify HD, which consists of:
 
		AVVideoColorPrimaries_ITU_R_709_2
		AVVideoTransferFunction_ITU_R_709_2
		AVVideoYCbCrMatrix_ITU_R_709_2
 
	If you require SD colorimetry use:
 
		AVVideoColorPrimaries_SMPTE_C
		AVVideoTransferFunction_ITU_R_709_2
		AVVideoYCbCrMatrix_ITU_R_601_4
 
	If you require wide gamut HD colorimetry, you can use:
 
		 AVVideoColorPrimaries_P3_D65
		 AVVideoTransferFunction_ITU_R_709_2
		 AVVideoYCbCrMatrix_ITU_R_709_2
 
	AVFoundation will color match if the source and destination color properties differ according to the following rules:
 
	If you want to override the tagging of color properties in the video that you will be processing, set a value for AVVideoColorPropertiesKey:
 
	If AVVideoColorPropertiesKey is set in the output settings and the source buffers are not tagged with color properties, then the output will be tagged according to the AVVideoColorPropertiesKey color properties.
	If AVVideoColorPropertiesKey is set in the output settings and the source buffers are also tagged with color properties, then if necessary the source buffers will be color converted to match the color properties specified by AVVideoColorPropertiesKey, and the output will be tagged according to the AVVideoColorPropertiesKey color properties.
 
	If you do not want to override the tagging of color properties in the video that you will be processing, do not set a value for AVVideoColorPropertiesKey:
 
	If AVVideoColorPropertiesKey is not set in the output settings and the source buffers are tagged with color properties, then the output will be tagged according to the source buffer color properties.
	If AVVideoColorPropertiesKey is not set in the output settings and the source buffers are not tagged with color properties, then the output will not be tagged with any color properties.
 
	 It is important that the source be tagged.
*/
AVF_EXPORT NSString *const AVVideoColorPropertiesKey /* NSDictionary, all 3 below keys required */           NS_AVAILABLE(10_7, 10_0);
	AVF_EXPORT NSString *const AVVideoColorPrimariesKey /* NSString */                                       NS_AVAILABLE(10_7, 10_0);
		AVF_EXPORT NSString *const AVVideoColorPrimaries_ITU_R_709_2                                         NS_AVAILABLE(10_7, 10_0);
		AVF_EXPORT NSString *const AVVideoColorPrimaries_EBU_3213                                            NS_AVAILABLE(10_7, NA);
		AVF_EXPORT NSString *const AVVideoColorPrimaries_SMPTE_C                                             NS_AVAILABLE(10_7, 10_0);
		AVF_EXPORT NSString *const AVVideoColorPrimaries_P3_D65                                              NS_AVAILABLE(10_12, 10_0);
	AVF_EXPORT NSString *const AVVideoTransferFunctionKey /* NSString */                                     NS_AVAILABLE(10_7, 10_0);
		AVF_EXPORT NSString *const AVVideoTransferFunction_ITU_R_709_2                                       NS_AVAILABLE(10_7, 10_0);
		AVF_EXPORT NSString *const AVVideoTransferFunction_SMPTE_240M_1995                                   NS_AVAILABLE(10_7, NA);
	AVF_EXPORT NSString *const AVVideoYCbCrMatrixKey /* NSString */                                          NS_AVAILABLE(10_7, 10_0);
		AVF_EXPORT NSString *const AVVideoYCbCrMatrix_ITU_R_709_2                                            NS_AVAILABLE(10_7, 10_0);
		AVF_EXPORT NSString *const AVVideoYCbCrMatrix_ITU_R_601_4                                            NS_AVAILABLE(10_7, 10_0);
		AVF_EXPORT NSString *const AVVideoYCbCrMatrix_SMPTE_240M_1995                                        NS_AVAILABLE(10_7, NA);
/*!
 @constant	AVVideoAllowWideColorKey
 @abstract	Indicates whether the client can process wide color
 @discussion
	Clients who wish to process wide color content should set the value of this key to @YES, or specify AVVideoColorPropertiesKey.
 
	The default value, @NO, permits implicit color conversions to occur to a non-wide gamut color space.
 */
AVF_EXPORT NSString *const AVVideoAllowWideColorKey /* NSNumber(BOOL)	*/					NS_AVAILABLE(10_12, 10_0);

/*!
 @constant	AVVideoCompressionPropertiesKey
 @abstract
	The value for this key is an instance of NSDictionary, containing properties to be passed down to the video encoder.
 @discussion
	Package the below keys in an instance of NSDictionary and use it as the value for AVVideoCompressionPropertiesKey in the top-level AVVideoSettings dictionary.  In addition to the keys listed below, you can also include keys from VideoToolbox/VTCompressionProperties.h.
 
	Most keys can only be used for certain encoders.  Look at individual keys for details.
 */
AVF_EXPORT NSString *const AVVideoCompressionPropertiesKey /* NSDictionary */                                NS_AVAILABLE(10_7, 4_0);
	AVF_EXPORT NSString *const AVVideoAverageBitRateKey /* NSNumber (bits per second, H.264 only) */         NS_AVAILABLE(10_7, 4_0);
	AVF_EXPORT NSString *const AVVideoQualityKey /* NSNumber (0.0-1.0, JPEG only) */                         NS_AVAILABLE(10_7, 5_0);
	AVF_EXPORT NSString *const AVVideoMaxKeyFrameIntervalKey /* NSNumber (frames, 1 means key frames only, H.264 only) */ NS_AVAILABLE(10_7, 4_0);
	AVF_EXPORT NSString *const AVVideoMaxKeyFrameIntervalDurationKey /* NSNumber (seconds, 0.0 means no limit, H.264 only) */ NS_AVAILABLE(10_9, 7_0);

	/*!
	 @constant	AVVideoAllowFrameReorderingKey
	 @abstract
		 Enables or disables frame reordering.
	 @discussion
		 In order to achieve the best compression while maintaining image quality, some video encoders can reorder frames.  This means that the order in which the frames will be emitted and stored (the decode order) will be different from the order in which they are presented to the video encoder (the display order).
		
		Encoding using frame reordering requires more system resources than encoding without frame reordering, so encoding performance should be taken into account when deciding whether to enable frame reordering.  This is especially important when encoding video data from a real-time source, such as AVCaptureVideoDataOutput.  In this situation, using a value of @NO for AVVideoAllowFrameReorderingKey may yield the best results.
	 
		The default is @YES, which means that the encoder decides whether to enable frame reordering.
	 */
	AVF_EXPORT NSString *const AVVideoAllowFrameReorderingKey /* NSNumber (BOOL) */							 NS_AVAILABLE(10_10, 7_0);

	AVF_EXPORT NSString *const AVVideoProfileLevelKey /* NSString, H.264 only, one of: */                    NS_AVAILABLE(10_8, 4_0);
		AVF_EXPORT NSString *const AVVideoProfileLevelH264Baseline30 /* Baseline Profile Level 3.0 */        NS_AVAILABLE(10_8, 4_0);
		AVF_EXPORT NSString *const AVVideoProfileLevelH264Baseline31 /* Baseline Profile Level 3.1 */        NS_AVAILABLE(10_8, 4_0);
        AVF_EXPORT NSString *const AVVideoProfileLevelH264Baseline41 /* Baseline Profile Level 4.1 */        NS_AVAILABLE(10_8, 5_0);
		AVF_EXPORT NSString *const AVVideoProfileLevelH264BaselineAutoLevel /* Baseline Profile Auto Level */ NS_AVAILABLE(10_9, 7_0);
		AVF_EXPORT NSString *const AVVideoProfileLevelH264Main30 /* Main Profile Level 3.0 */                NS_AVAILABLE(10_8, 4_0);
		AVF_EXPORT NSString *const AVVideoProfileLevelH264Main31 /* Main Profile Level 3.1 */                NS_AVAILABLE(10_8, 4_0);
		AVF_EXPORT NSString *const AVVideoProfileLevelH264Main32 /* Main Profile Level 3.2 */                NS_AVAILABLE(10_8, 5_0);
		AVF_EXPORT NSString *const AVVideoProfileLevelH264Main41 /* Main Profile Level 4.1 */                NS_AVAILABLE(10_8, 5_0);
		AVF_EXPORT NSString *const AVVideoProfileLevelH264MainAutoLevel /* Main Profile Auto Level */        NS_AVAILABLE(10_9, 7_0);
		AVF_EXPORT NSString *const AVVideoProfileLevelH264High40 /* High Profile Level 4.0 */                NS_AVAILABLE(10_9, 6_0);
		AVF_EXPORT NSString *const AVVideoProfileLevelH264High41 /* High Profile Level 4.1 */                NS_AVAILABLE(10_9, 6_0);
		AVF_EXPORT NSString *const AVVideoProfileLevelH264HighAutoLevel /* High Profile Auto Level */        NS_AVAILABLE(10_9, 7_0);

	/*!
	 @constant	AVVideoH264EntropyModeKey
	 @abstract
		The entropy encoding mode for H.264 compression.
	 @discussion
		If supported by an H.264 encoder, this property controls whether the encoder should use Context-based Adaptive Variable Length Coding (CAVLC) or Context-based Adaptive Binary Arithmetic Coding (CABAC).  CABAC generally gives better compression at the expense of higher computational overhead.  The default value is encoder-specific and may change depending on other encoder settings.  Care should be taken when using this property -- changes may result in a configuration which is not compatible with a requested Profile and Level.  Results in this case are undefined, and could include encode errors or a non-compliant output stream.
	*/
	AVF_EXPORT NSString *const AVVideoH264EntropyModeKey     /* NSString, H.264 only, one of: */			 NS_AVAILABLE(10_10, 7_0);
		AVF_EXPORT NSString *const AVVideoH264EntropyModeCAVLC /* Context-based Adaptive Variable Length Coding */   NS_AVAILABLE(10_10, 7_0);
		AVF_EXPORT NSString *const AVVideoH264EntropyModeCABAC /* Context-based Adaptive Binary Arithmetic Coding */ NS_AVAILABLE(10_10, 7_0);

	/*!
	 @constant	AVVideoExpectedSourceFrameRateKey
	 @abstract
		Indicates the expected source frame rate, if known.
	 @discussion
		The frame rate is measured in frames per second. This is not used to control the frame rate; it is provided as a hint to the video encoder so that it can set up internal configuration before compression begins. The actual frame rate will depend on frame durations and may vary. This should be set if an AutoLevel AVVideoProfileLevelKey is used, or if the source content has a high frame rate (higher than 30 fps). The encoder might have to drop frames to satisfy bit stream requirements if this key is not specified.
	 */
	AVF_EXPORT NSString *const AVVideoExpectedSourceFrameRateKey /* NSNumber (frames per second) */				NS_AVAILABLE(10_10, 7_0);

	/*!
	 @constant	AVVideoAverageNonDroppableFrameRateKey
	 @abstract
		The desired average number of non-droppable frames to be encoded for each second of video.
	 @discussion
		Some video encoders can produce a flexible mixture of non-droppable frames and droppable frames.  The difference between these types is that it is necessary for a video decoder to decode a non-droppable frame in order to successfully decode subsequent frames, whereas droppable frames are optional and can be skipped without impact on decode of subsequent frames.  Having a proportion of droppable frames in a sequence has advantages for temporal scalability: at playback time more or fewer frames may be decoded depending on the play rate.  This property requests that the encoder emit an overall proportion of non-droppable and droppable frames so that there are the specified number of non-droppable frames per second.
 
		For example, to specify that the encoder should include an average of 30 non-droppable frames for each second of video:
 
		[myVideoSettings setObject:@30 forKey:AVVideoAverageNonDroppableFrameRateKey];
	 */
	AVF_EXPORT NSString *const AVVideoAverageNonDroppableFrameRateKey /* NSNumber (frames per second) */		NS_AVAILABLE(10_10, 7_0);

/*!
	@constant AVVideoEncoderSpecificationKey
	@abstract
		The video encoder specification includes options for choosing a specific video encoder.
		
	@discussion
		The value for this key is a dictionary containing kVTVideoEncoderSpecification_* keys specified in the VideoToolbox framework.  This key should be specified at the top level of an AVVideoSettings dictionary.
 */
AVF_EXPORT NSString *const AVVideoEncoderSpecificationKey /* NSDictionary */ NS_AVAILABLE(10_10, NA);
