/*
    File:		AVAudioUnitDelay.h
    Framework:	AVFoundation
 
    Copyright (c) 2014-2015 Apple Inc. All Rights Reserved.
*/

#import <AVFAudio/AVAudioUnitEffect.h>

NS_ASSUME_NONNULL_BEGIN

/*! @class AVAudioUnitDelay
    @abstract an AVAudioUnitEffect that implements a delay effect
    @discussion
        A delay unit delays the input signal by the specified time interval
        and then blends it with the input signal. The amount of high frequency
        roll-off can also be controlled in order to simulate the effect of
        a tape delay.
 
*/
API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0)) API_UNAVAILABLE(watchos) 
@interface AVAudioUnitDelay : AVAudioUnitEffect

/*! @property delayTime
    Time taken by the delayed input signal to reach the output
    @abstract
    Range:      0 -> 2
    Default:    1
    Unit:       Seconds
 */
@property (nonatomic) NSTimeInterval delayTime;

/*! @property feedback
    @abstract
    Amount of the output signal fed back into the delay line
    Range:      -100 -> 100
    Default:    50
    Unit:       Percent
*/
@property (nonatomic) float feedback;

/*! @property lowPassCutoff
    @abstract
    Cutoff frequency above which high frequency content is rolled off
    Range:      10 -> (samplerate/2)
    Default:    15000
    Unit:       Hertz
*/
@property (nonatomic) float lowPassCutoff;

/*! @property wetDryMix
    @abstract
    Blend of the wet and dry signals
    Range:      0 (all dry) -> 100 (all wet)
    Default:    100
    Unit:       Percent
*/
@property (nonatomic) float wetDryMix;

@end

NS_ASSUME_NONNULL_END
