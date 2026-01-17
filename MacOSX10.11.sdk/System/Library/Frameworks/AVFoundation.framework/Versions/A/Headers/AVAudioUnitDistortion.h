/*
    File:		AVAudioUnitDistortion.h
    Framework:	AVFoundation
 
    Copyright (c) 2014-2015 Apple Inc. All Rights Reserved.
*/

#import <AVFoundation/AVAudioUnitEffect.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, AVAudioUnitDistortionPreset) {
    AVAudioUnitDistortionPresetDrumsBitBrush           = 0,
    AVAudioUnitDistortionPresetDrumsBufferBeats        = 1,
    AVAudioUnitDistortionPresetDrumsLoFi               = 2,
    AVAudioUnitDistortionPresetMultiBrokenSpeaker      = 3,
    AVAudioUnitDistortionPresetMultiCellphoneConcert   = 4,
    AVAudioUnitDistortionPresetMultiDecimated1         = 5,
    AVAudioUnitDistortionPresetMultiDecimated2         = 6,
    AVAudioUnitDistortionPresetMultiDecimated3         = 7,
    AVAudioUnitDistortionPresetMultiDecimated4         = 8,
    AVAudioUnitDistortionPresetMultiDistortedFunk      = 9,
    AVAudioUnitDistortionPresetMultiDistortedCubed     = 10,
    AVAudioUnitDistortionPresetMultiDistortedSquared   = 11,
    AVAudioUnitDistortionPresetMultiEcho1              = 12,
    AVAudioUnitDistortionPresetMultiEcho2              = 13,
    AVAudioUnitDistortionPresetMultiEchoTight1         = 14,
    AVAudioUnitDistortionPresetMultiEchoTight2         = 15,
    AVAudioUnitDistortionPresetMultiEverythingIsBroken = 16,
    AVAudioUnitDistortionPresetSpeechAlienChatter      = 17,
    AVAudioUnitDistortionPresetSpeechCosmicInterference = 18,
    AVAudioUnitDistortionPresetSpeechGoldenPi          = 19,
    AVAudioUnitDistortionPresetSpeechRadioTower        = 20,
    AVAudioUnitDistortionPresetSpeechWaves             = 21
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*! @class AVAudioUnitDistortion
    @abstract An AVAudioUnitEffect that implements a multi-stage distortion effect.
 
*/
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface AVAudioUnitDistortion : AVAudioUnitEffect

/*! @method loadFactoryPreset:
    @abstract Load a distortion preset.
    Default:    AVAudioUnitDistortionPresetDrumsBitBrush
*/
-(void)loadFactoryPreset:(AVAudioUnitDistortionPreset)preset;

/*! @property preGain
    @abstract
    Gain applied to the signal before being distorted
    Range:      -80 -> 20
    Default:    -6
    Unit:       dB
*/
@property (nonatomic) float preGain;

/*! @property wetDryMix
    @abstract
    Blend of the distorted and dry signals
    Range:      0 (all dry) -> 100 (all distorted)
    Default:    50
    Unit:       Percent
*/
@property (nonatomic) float wetDryMix;

@end

NS_ASSUME_NONNULL_END

