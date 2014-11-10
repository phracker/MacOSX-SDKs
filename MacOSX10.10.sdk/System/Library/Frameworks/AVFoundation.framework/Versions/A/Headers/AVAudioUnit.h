/*
	File:		AVAudioUnit.h
	Framework:	AVFoundation
	
	Copyright (c) 2014 Apple Inc. All Rights Reserved.
*/

#import <AVFoundation/AVAudioNode.h>
#import <AudioUnit/AudioUnit.h>

/*! @class AVAudioUnit
    @abstract An AVAudioNode implemented by an audio unit.
    @discussion
		An AVAudioUnit is an AVAudioNode implemented by an audio unit. Depending on the type of
		the audio unit, audio is processed either in real-time or non real-time.
*/
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface AVAudioUnit : AVAudioNode

/*! @method loadAudioUnitPresetAtURL:error:
    @abstract Load an audio unit preset.
    @param url
        NSURL of the .aupreset file.
    @discussion
        If the .aupreset file cannot be successfully loaded, an error is returned.
*/
- (BOOL)loadAudioUnitPresetAtURL:(NSURL *)url error:(NSError **)error;

/*! @property audioComponentDescription
	@abstract AudioComponentDescription of the underlying audio unit.
*/
@property (nonatomic, readonly) AudioComponentDescription audioComponentDescription;

/*! @property audioUnit
    @abstract Reference to the underlying audio unit.
    @discussion
        A reference to the underlying audio unit is provided so that parameters that are not
        exposed by AVAudioUnit subclasses can be modified using the AudioUnit C API.
 
        No operations that may conflict with state maintained by the engine should be performed
        directly on the audio unit. These include changing initialization state, stream formats,
        channel layouts or connections to other audio units.
*/
@property (nonatomic, readonly) AudioUnit audioUnit;

/*! @property name
    @abstract Name of the audio unit.
*/
@property (nonatomic, readonly) NSString *name;

/*! @property manufacturerName
    @abstract Manufacturer name of the audio unit.
*/
@property (nonatomic, readonly) NSString *manufacturerName;

/*! @property version
    @abstract Version number of the audio unit.
*/
@property (nonatomic, readonly) NSUInteger version;

@end
