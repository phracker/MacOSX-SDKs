/*
    File:		AVAudioUnitTimeEffect.h
    Framework:	AVFoundation
 
    Copyright (c) 2014-2015 Apple Inc. All Rights Reserved.
 */

#import <AVFAudio/AVAudioUnit.h>

NS_ASSUME_NONNULL_BEGIN

/*! @class AVAudioUnitTimeEffect
    @abstract an AVAudioUnit that processes audio in non real-time
    @discussion
    An AVAudioUnitTimeEffect represents an audio unit of type aufc.
    These effects do not process audio in real-time. The varispeed
    unit is an example of a time effect unit.
 
*/
NS_CLASS_AVAILABLE(10_10, 8_0) __WATCHOS_PROHIBITED
@interface AVAudioUnitTimeEffect : AVAudioUnit

#if AVAUDIOUNIT_HAVE_AUDIOUNIT
/*! @method initWithAudioComponentDescription:
    @abstract create an AVAudioUnitTimeEffect object
    
    @param audioComponentDescription
    @abstract AudioComponentDescription of the audio unit to be initialized
    @discussion 
    The componentType must be kAudioUnitType_FormatConverter
*/
- (instancetype)initWithAudioComponentDescription:(AudioComponentDescription)audioComponentDescription;
#endif

/*! @property bypass
    @abstract bypass state of the audio unit
*/
@property (nonatomic) BOOL bypass;

@end

NS_ASSUME_NONNULL_END
