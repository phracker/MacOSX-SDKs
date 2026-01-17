/*
    File:		AVAudioUnitGenerator.h
    Framework:	AVFoundation
 
    Copyright (c) 2014-2015 Apple Inc. All Rights Reserved.
 */

#import <AVFAudio/AVAudioUnit.h>
#import <AVFAudio/AVAudioMixing.h>

NS_ASSUME_NONNULL_BEGIN

/*! @class AVAudioUnitGenerator
    @abstract an AVAudioUnit that generates audio output
    @discussion
    An AVAudioUnitGenerator represents an audio unit of type kAudioUnitType_Generator or
	kAudioUnitType_RemoteGenerator.
    A generator will have no audio input, but will just produce audio output.
    A tone generator is an example of this. 
*/
NS_CLASS_AVAILABLE(10_10, 8_0) __WATCHOS_PROHIBITED
@interface AVAudioUnitGenerator : AVAudioUnit <AVAudioMixing>

#if AVAUDIOUNIT_HAVE_AUDIOUNIT
/*! @method initWithAudioComponentDescription:
    @abstract Create an AVAudioUnitGenerator object.
    
    @param audioComponentDescription
    @abstract AudioComponentDescription of the audio unit to be instantiated.
    @discussion
    The componentType must be kAudioUnitType_Generator or kAudioUnitType_RemoteGenerator
*/
- (instancetype)initWithAudioComponentDescription:(AudioComponentDescription)audioComponentDescription;
#endif

/*! @property bypass
    @abstract Bypass state of the audio unit.
*/
@property (nonatomic) BOOL bypass;

@end

NS_ASSUME_NONNULL_END
