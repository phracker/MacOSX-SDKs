/*
    File:		AVAudioUnitReverb.h
    Framework:	AVFoundation
 
    Copyright (c) 2014-2015 Apple Inc. All Rights Reserved.
 */

#import <AVFoundation/AVAudioUnitEffect.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, AVAudioUnitReverbPreset) {
    AVAudioUnitReverbPresetSmallRoom       = 0,
    AVAudioUnitReverbPresetMediumRoom      = 1,
    AVAudioUnitReverbPresetLargeRoom       = 2,
    AVAudioUnitReverbPresetMediumHall      = 3,
    AVAudioUnitReverbPresetLargeHall       = 4,
    AVAudioUnitReverbPresetPlate           = 5,
    AVAudioUnitReverbPresetMediumChamber   = 6,
    AVAudioUnitReverbPresetLargeChamber    = 7,
    AVAudioUnitReverbPresetCathedral       = 8,
    AVAudioUnitReverbPresetLargeRoom2      = 9,
    AVAudioUnitReverbPresetMediumHall2     = 10,
    AVAudioUnitReverbPresetMediumHall3     = 11,
    AVAudioUnitReverbPresetLargeHall2      = 12
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*! @class AVAudioUnitReverb
    @abstract an AVAudioUnitEffect that implements a reverb
    @discussion
        A reverb simulates the acoustic characteristics of a particular environment.
        Use the different presets to simulate a particular space and blend it in with
        the original signal using the wetDryMix parameter.
 
*/
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface AVAudioUnitReverb : AVAudioUnitEffect

/*! @method loadFactoryPreset:
    @abstract load a reverb preset
    Default:    AVAudioUnitReverbPresetMediumHall
*/
- (void)loadFactoryPreset:(AVAudioUnitReverbPreset)preset;

/*! @property wetDryMix
    @abstract
    Blend of the wet and dry signals
    Range:      0 (all dry) -> 100 (all wet)
    Unit:       Percent
*/
@property (nonatomic) float wetDryMix;

@end

NS_ASSUME_NONNULL_END
