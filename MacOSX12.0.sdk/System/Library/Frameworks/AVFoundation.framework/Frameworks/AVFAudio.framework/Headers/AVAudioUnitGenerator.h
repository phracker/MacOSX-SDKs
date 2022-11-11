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
API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVAudioUnitGenerator : AVAudioUnit <AVAudioMixing>

#if AVAUDIOUNIT_HAVE_AUDIOUNIT
/*! @method initWithAudioComponentDescription:
    @abstract Create an AVAudioUnitGenerator object.
    
    @param audioComponentDescription
    AudioComponentDescription of the audio unit to be instantiated.
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
