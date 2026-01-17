/*
    File:		AVAudioUnitEffect.h
    Framework:	AVFoundation
 
    Copyright (c) 2014-2015 Apple Inc. All Rights Reserved.
*/

#import <AVFAudio/AVAudioUnit.h>

NS_ASSUME_NONNULL_BEGIN

/*! @class AVAudioUnitEffect
    @abstract an AVAudioUnit that processes audio in real-time
    @discussion
    An AVAudioUnitEffect represents an audio unit of type kAudioUnitType_Effect,
    kAudioUnitType_MusicEffect, kAudioUnitType_Panner, kAudioUnitType_RemoteEffect or 
    kAudioUnitType_RemoteMusicEffect.

    These effects run in real-time and process some x number of audio input 
    samples to produce x number of audio output samples. A delay unit is an 
    example of an effect unit.
 
*/
NS_CLASS_AVAILABLE(10_10, 8_0) __WATCHOS_PROHIBITED
@interface AVAudioUnitEffect : AVAudioUnit

#if AVAUDIOUNIT_HAVE_AUDIOUNIT
/*! @method initWithAudioComponentDescription:
    @abstract Create an AVAudioUnitEffect object.
    
    @param audioComponentDescription
    @abstract AudioComponentDescription of the audio unit to be instantiated.
    @discussion
    The componentType must be one of these types
    kAudioUnitType_Effect
    kAudioUnitType_MusicEffect
    kAudioUnitType_Panner
    kAudioUnitType_RemoteEffect
    kAudioUnitType_RemoteMusicEffect

*/
- (instancetype)initWithAudioComponentDescription:(AudioComponentDescription)audioComponentDescription;
#endif

/*! @property bypass
    @abstract Bypass state of the audio unit.
*/
@property (nonatomic) BOOL bypass;

@end

NS_ASSUME_NONNULL_END

