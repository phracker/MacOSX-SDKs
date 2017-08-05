/*
    File:       AVAudioUnit.h
    Framework:  AVFoundation
    
    Copyright (c) 2014-2015 Apple Inc. All Rights Reserved.
*/

#import <AVFAudio/AVAudioNode.h>

#if __has_include(<AudioToolbox/AudioUnit.h>)
#define AVAUDIOUNIT_HAVE_AUDIOUNIT 1
#import <AudioToolbox/AudioUnit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

#if __OBJC2__
@class AUAudioUnit;
#endif // __OBJC2__

/*! @class AVAudioUnit
    @abstract An AVAudioNode implemented by an audio unit.
    @discussion
        An AVAudioUnit is an AVAudioNode implemented by an audio unit. Depending on the type of
        the audio unit, audio is processed either in real-time or non real-time.
*/
NS_CLASS_AVAILABLE(10_10, 8_0) __WATCHOS_PROHIBITED
@interface AVAudioUnit : AVAudioNode

#if AVAUDIOUNIT_HAVE_AUDIOUNIT

/*!	@method	instantiateWithComponentDescription:options:completionHandler:
	@abstract Asynchronously create an instance of an audio unit component, wrapped in an AVAudioUnit.
	@param audioComponentDescription
		The component to instantiate.
	@param options
		Instantiation options.
	@param completionHandler
		Called in an arbitrary thread/queue context when instantiation is complete. The client
		should retain the provided AVAudioUnit.
	@discussion
		Components whose flags include kAudioComponentFlag_RequiresAsyncInstantiation must be 
		instantiated asynchronously, via this method if they are to be used with AVAudioEngine.
		See the discussion of this flag in AudioToolbox/AudioComponent.h.
		
		The returned AVAudioUnit instance normally will be of a subclass (AVAudioUnitEffect,
		AVAudioUnitGenerator, AVAudioUnitMIDIInstrument, or AVAudioUnitTimeEffect), selected
		according to the component's type.
*/
+ (void)instantiateWithComponentDescription:(AudioComponentDescription)audioComponentDescription options:(AudioComponentInstantiationOptions)options completionHandler:(void (^)(__kindof AVAudioUnit * __nullable audioUnit, NSError * __nullable error))completionHandler NS_AVAILABLE(10_11, 9_0);

/*! @method loadAudioUnitPresetAtURL:error:
    @abstract Load an audio unit preset.
    @param url
        NSURL of the .aupreset file.
	@param outError
    @discussion
        If the .aupreset file cannot be successfully loaded, an error is returned.
*/
- (BOOL)loadAudioUnitPresetAtURL:(NSURL *)url error:(NSError **)outError;

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

#if __OBJC2__
/*! @property AUAudioUnit
    @abstract An AUAudioUnit wrapping or underlying the implementation's AudioUnit.
    @discussion
        This provides an AUAudioUnit which either wraps or underlies the implementation's
        AudioUnit, depending on how that audio unit is packaged. Applications can interact with this
        AUAudioUnit to control custom properties, select presets, change parameters, etc.
 
        As with the audioUnit property, no operations that may conflict with state maintained by the
        engine should be performed directly on the audio unit. These include changing initialization
        state, stream formats, channel layouts or connections to other audio units.
*/
@property (nonatomic, readonly) AUAudioUnit *AUAudioUnit NS_AVAILABLE(10_11, 9_0);
#endif // __OBJC2__

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

#endif //AVAUDIOUNIT_HAVE_AUDIOUNIT

@end

NS_ASSUME_NONNULL_END
