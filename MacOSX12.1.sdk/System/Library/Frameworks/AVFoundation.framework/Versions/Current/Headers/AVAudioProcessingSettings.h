#if !__has_include(<AVFCore/AVAudioProcessingSettings.h>)
/*
    File:  AVAudioProcessingSettings.h
 
    Framework:  AVFoundation
 
	Copyright 2013-2021 Apple Inc. All rights reserved.
 
 */

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>


/*!
 @typedef AVAudioTimePitchAlgorithm
 @abstract
    The type of a time pitch algorithm.
 @discussion
	On macOS and iOS, the default algorithm for playback for applications linked on or after iOS 15.0 or macOS 12.0 is is AVAudioTimePitchAlgorithmTimeDomain. For iOS versions prior to 15.0 the default value is AVAudioTimePitchAlgorithmLowQualityZeroLatency. For macOS versions prior to 12.0 the default value is AVAudioTimePitchAlgorithmSpectral.
 The default for export & other offline processing is AVAudioTimePitchAlgorithmSpectral.

	For scaled audio edits, i.e. when the timeMapping of an AVAssetTrackSegment is between timeRanges of unequal duration, it is important to choose an algorithm that supports the full range of edit rates present in the source media.  AVAudioTimePitchAlgorithmSpectral is often the best choice due to the highly inclusive range of rates it supports, assuming that it is desirable to maintain a constant pitch regardless of the edit rate.  If it is instead desirable to allow the pitch to vary with the edit rate, AVAudioTimePitchAlgorithmVarispeed is the best choice.
 
*/
typedef NSString * AVAudioTimePitchAlgorithm NS_STRING_ENUM;

/*!
 @abstract		Values for time pitch algorithm
 
 @constant      AVAudioTimePitchAlgorithmLowQualityZeroLatency
				Low quality, very inexpensive. Suitable for brief fast-forward/rewind effects, low quality voice.
                Rate snapped to {0.5, 0.666667, 0.8, 1.0, 1.25, 1.5, 2.0}.

 @constant      AVAudioTimePitchAlgorithmTimeDomain
				Modest quality, less expensive. Suitable for voice.
                Variable rate from 1/32 to 32.

 @constant      AVAudioTimePitchAlgorithmSpectral
				Highest quality, most computationally expensive. Suitable for music.
                Variable rate from 1/32 to 32.

 @constant      AVAudioTimePitchAlgorithmVarispeed
				High quality, no pitch correction. Pitch varies with rate.
                Variable rate from 1/32 to 32.
 
*/
AVF_EXPORT AVAudioTimePitchAlgorithm const AVAudioTimePitchAlgorithmLowQualityZeroLatency API_DEPRECATED("Use AVAudioTimePitchAlgorithmTimeDomain instead", ios(7.0, 15.0), tvos(9.0, 15.0), watchos(1.0, 8.0)) API_UNAVAILABLE(macos);
AVF_EXPORT AVAudioTimePitchAlgorithm const AVAudioTimePitchAlgorithmTimeDomain API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVAudioTimePitchAlgorithm const AVAudioTimePitchAlgorithmSpectral API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVAudioTimePitchAlgorithm const AVAudioTimePitchAlgorithmVarispeed API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

/*!
@enum AVAudioSpatializationFormats
 @abstract
	These constants can be used to specify values for allowedAudioSpatializationFormats.
 
 @constant	 AVAudioSpatializationFormatNone
	Indicates that no audio spatialization is allowed.
 @constant	 AVAudioSpatializationFormatMonoAndStereo
	Indicates that only mono and stereo formats may be used for audio spatialization.
 @constant	 AVAudioSpatializationFormatMultichannel
	Indicates that only multichannel layouts may be used for audio spatialization.
 @constant	 AVAudioSpatializationFormatMonoStereoAndMultichannel
	Indicates that mono, stereo and multichannel layouts may be used for audio spatialization.
 */
typedef NS_OPTIONS(NSUInteger, AVAudioSpatializationFormats) {
	AVAudioSpatializationFormatNone = 0UL,
	AVAudioSpatializationFormatMonoAndStereo = 0x3UL,
	AVAudioSpatializationFormatMultichannel = 0x4UL,
	AVAudioSpatializationFormatMonoStereoAndMultichannel = 0x7UL
};

#else
#import <AVFCore/AVAudioProcessingSettings.h>
#endif
