/*
    File:  AVMediaFormat.h

	Framework:  AVFoundation
 
	Copyright 2010 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

// Media types

AVF_EXPORT NSString *const AVMediaTypeVideo                 NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT NSString *const AVMediaTypeAudio                 NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT NSString *const AVMediaTypeText                  NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT NSString *const AVMediaTypeClosedCaption         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT NSString *const AVMediaTypeSubtitle              NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT NSString *const AVMediaTypeTimecode              NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT NSString *const AVMediaTypeTimedMetadata         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT NSString *const AVMediaTypeMuxed                 NS_AVAILABLE(10_7, 4_0);


// Media characteristics

AVF_EXPORT NSString *const AVMediaCharacteristicVisual      NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT NSString *const AVMediaCharacteristicAudible     NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT NSString *const AVMediaCharacteristicLegible     NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT NSString *const AVMediaCharacteristicFrameBased  NS_AVAILABLE(10_7, 4_0);

// File format UTIs

/*!
 @constant AVFileTypeQuickTimeMovie
 @abstract A UTI for the QuickTime movie file format.
 @discussion
 The value of this UTI is @"com.apple.quicktime-movie".
 Files are identified with the .mov and .qt extensions.
 */
AVF_EXPORT NSString *const AVFileTypeQuickTimeMovie NS_AVAILABLE(10_7, 4_0);

/*!
 @constant AVFileTypeMPEG4
 @abstract A UTI for the MPEG-4 file format.
 @discussion
 The value of this UTI is @"public.mpeg-4".
 Files are identified with the .mp4 extension.
 */
AVF_EXPORT NSString *const AVFileTypeMPEG4 NS_AVAILABLE(10_7, 4_0);

/*!
 @constant AVFileTypeAppleM4V
 @discussion
 The value of this UTI is @"com.apple.m4v-video".
 Files are identified with the .m4v extension.
 */
AVF_EXPORT NSString *const AVFileTypeAppleM4V NS_AVAILABLE(10_7, 4_0);

/*!
 @constant AVFileTypeAppleM4A
 @discussion
 The value of this UTI is @"com.apple.m4a-audio".
 Files are identified with the .m4a extension.
 */
AVF_EXPORT NSString *const AVFileTypeAppleM4A NS_AVAILABLE(10_7, 4_0);

#if TARGET_OS_IPHONE

/*!
 @constant AVFileType3GPP
 @abstract A UTI for the 3GPP file format.
 @discussion
 The value of this UTI is @"public.3gp".
 Files are identified with the .3gp, .3gpp, and .sdv extensions.
 */
AVF_EXPORT NSString *const AVFileType3GPP NS_AVAILABLE_IPHONE(4_0);

#endif // TARGET_OS_IPHONE

/*!
 @constant AVFileTypeCoreAudioFormat
 @abstract A UTI for the CoreAudio file format.
 @discussion
 The value of this UTI is @"com.apple.coreaudio-format".
 Files are identified with the .caf extension.
 */
AVF_EXPORT NSString *const AVFileTypeCoreAudioFormat NS_AVAILABLE(10_7, 4_0);

/*!
 @constant AVFileTypeWAVE
 @abstract A UTI for the WAVE audio file format.
 @discussion
 The value of this UTI is @"com.microsoft.waveform-audio".
 Files are identified with the .wav, .wave, and .bwf extensions.
 */
AVF_EXPORT NSString *const AVFileTypeWAVE NS_AVAILABLE(10_7, 4_0);

/*!
 @constant AVFileTypeAIFF
 @abstract A UTI for the AIFF audio file format.
 @discussion
 The value of this UTI is @"public.aiff-audio".
 Files are identified with the .aif and .aiff extensions.
 */
AVF_EXPORT NSString *const AVFileTypeAIFF NS_AVAILABLE(10_7, 4_0);

/*!
 @constant AVFileTypeAIFC
 @abstract A UTI for the AIFC audio file format.
 @discussion
 The value of this UTI is @"public.aifc-audio".
 Files are identified with the .aifc and .cdda extensions.
 */
AVF_EXPORT NSString *const AVFileTypeAIFC NS_AVAILABLE(10_7, 4_0);

/*!
 @constant AVFileTypeAMR
 @abstract A UTI for the adaptive multi-rate audio file format.
 @discussion
 The value of this UTI is @"org.3gpp.adaptive-multi-rate-audio".
 Files are identified with the .amr extension.
 */
AVF_EXPORT NSString *const AVFileTypeAMR NS_AVAILABLE(10_7, 4_0);
