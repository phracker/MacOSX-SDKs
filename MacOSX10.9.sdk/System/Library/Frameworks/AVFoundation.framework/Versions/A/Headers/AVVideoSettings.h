/*
	File:  AVVideoSettings.h

	Framework:  AVFoundation
 
	Copyright 2010-2013 Apple Inc. All rights reserved.

*/

/*!
 @class AVVideoSettings
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
 
	It is an error to add any other AVVideoSettings.h keys to an uncompressed video settings dictionary.
*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

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
 
	Note that prior to OSX 10.9 and iOS 7.0, this key could only be specified as part of the dictionary given for AVVideoCompressionPropertiesKey.  As of OSX 10.9 and iOS 7.0, the top level of an AVVideoSettings dictionary is the preferred place to specify this key.
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
 
	Note that prior to OSX 10.9 and iOS 7.0, this key could only be specified as part of the dictionary given for AVVideoCompressionPropertiesKey.  As of OSX 10.9 and iOS 7.0, the top level of an AVVideoSettings dictionary is the preferred place to specify this key.
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

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

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
 
	AVFoundation will color match if the source and destination color properties differ.
	It is important that the source be tagged.
*/
AVF_EXPORT NSString *const AVVideoColorPropertiesKey /* NSDictionary, all 3 below keys required */           NS_AVAILABLE(10_7, NA);
	AVF_EXPORT NSString *const AVVideoColorPrimariesKey /* NSString */                                       NS_AVAILABLE(10_7, NA);
		AVF_EXPORT NSString *const AVVideoColorPrimaries_ITU_R_709_2                                         NS_AVAILABLE(10_7, NA);
		AVF_EXPORT NSString *const AVVideoColorPrimaries_EBU_3213                                            NS_AVAILABLE(10_7, NA);
		AVF_EXPORT NSString *const AVVideoColorPrimaries_SMPTE_C                                             NS_AVAILABLE(10_7, NA);
	AVF_EXPORT NSString *const AVVideoTransferFunctionKey /* NSString */                                     NS_AVAILABLE(10_7, NA);
		AVF_EXPORT NSString *const AVVideoTransferFunction_ITU_R_709_2                                       NS_AVAILABLE(10_7, NA);
		AVF_EXPORT NSString *const AVVideoTransferFunction_SMPTE_240M_1995                                   NS_AVAILABLE(10_7, NA);
	AVF_EXPORT NSString *const AVVideoYCbCrMatrixKey /* NSString */                                          NS_AVAILABLE(10_7, NA);
		AVF_EXPORT NSString *const AVVideoYCbCrMatrix_ITU_R_709_2                                            NS_AVAILABLE(10_7, NA);
		AVF_EXPORT NSString *const AVVideoYCbCrMatrix_ITU_R_601_4                                            NS_AVAILABLE(10_7, NA);
		AVF_EXPORT NSString *const AVVideoYCbCrMatrix_SMPTE_240M_1995                                        NS_AVAILABLE(10_7, NA);

#endif // (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

/*!
 @constant	AVVideoCompressionPropertiesKey
 @abstract
	The value for this key is an instance of NSDictionary, containing properties to be passed down to the video encoder.
 @discussion
	Package the below keys in an instance of NSDictionary and use it as the value for AVVideoCompressionPropertiesKey in the top-level AVVideoSettings dictionary.  In addition to the keys listed below, on OSX you can also include keys from VideoToolbox/VTCompressionProperties.h.
 
	Most keys can only be used for certain encoders.  Look at individual keys for details.
 */
AVF_EXPORT NSString *const AVVideoCompressionPropertiesKey /* NSDictionary */                                NS_AVAILABLE(10_7, 4_0);
	AVF_EXPORT NSString *const AVVideoAverageBitRateKey /* NSNumber (bits per second, H.264 only) */         NS_AVAILABLE(10_7, 4_0);
	AVF_EXPORT NSString *const AVVideoQualityKey /* NSNumber (0.0-1.0, JPEG only) */                         NS_AVAILABLE(10_7, 5_0);
	AVF_EXPORT NSString *const AVVideoMaxKeyFrameIntervalKey /* NSNumber (1 means key frames only, H.264 only) */ NS_AVAILABLE(10_7, 4_0);
	AVF_EXPORT NSString *const AVVideoMaxKeyFrameIntervalDurationKey /* NSNumber (0 means no limit, H.264 only) */ NS_AVAILABLE(10_9, 7_0);

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

