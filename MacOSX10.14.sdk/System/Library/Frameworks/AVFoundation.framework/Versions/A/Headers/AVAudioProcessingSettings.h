/*
    File:  AVAudioProcessingSettings.h
 
    Framework:  AVFoundation
 
	Copyright 2013-2018 Apple Inc. All rights reserved.
 
 */

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>


/*!
 @typedef AVAudioTimePitchAlgorithm
 @abstract
    The type of a time pitch algorithm.
 @discussion
	On OS X, the default algorithm for all time pitch operations is AVAudioTimePitchAlgorithmSpectral.  On iOS, the default algorithm for playback is AVAudioTimePitchAlgorithmLowQualityZeroLatency and the default for export & other offline processing is AVAudioTimePitchAlgorithmSpectral.

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
AVF_EXPORT AVAudioTimePitchAlgorithm const AVAudioTimePitchAlgorithmLowQualityZeroLatency API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED;
AVF_EXPORT AVAudioTimePitchAlgorithm const AVAudioTimePitchAlgorithmTimeDomain NS_AVAILABLE(10_9, 7_0);
AVF_EXPORT AVAudioTimePitchAlgorithm const AVAudioTimePitchAlgorithmSpectral NS_AVAILABLE(10_9, 7_0);
AVF_EXPORT AVAudioTimePitchAlgorithm const AVAudioTimePitchAlgorithmVarispeed NS_AVAILABLE(10_9, 7_0);
