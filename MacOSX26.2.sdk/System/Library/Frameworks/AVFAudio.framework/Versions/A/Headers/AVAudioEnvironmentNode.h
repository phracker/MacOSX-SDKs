/*
    File:       AVAudioEnvironmentNode.h
    Framework:	AVFoundation
 
    Copyright (c) 2014-2015 Apple Inc. All Rights Reserved.
*/

#import <AVFAudio/AVAudioNode.h>
#import <AVFAudio/AVAudioUnitReverb.h>
#import <AVFAudio/AVAudioUnitEQ.h>
#import <AVFAudio/AVAudioMixing.h>

NS_ASSUME_NONNULL_BEGIN

/*! @enum AVAudioEnvironmentDistanceAttenuationModel
    @abstract Types of distance attenuation models
    @discussion
        Distance attenuation is the natural attenuation of sound when traveling from the source to 
        the listener. The different attenuation models listed below describe the drop-off in gain as 
        the source moves away from the listener.
     
        AVAudioEnvironmentDistanceAttenuationModelExponential
            distanceGain = (distance / referenceDistance) ^ (-rolloffFactor)
     
        AVAudioEnvironmentDistanceAttenuationModelInverse
            distanceGain = referenceDistance /  (referenceDistance + rolloffFactor *
                                                (distance – referenceDistance))
     
        AVAudioEnvironmentDistanceAttenuationModelLinear
            distanceGain = (1 – rolloffFactor * (distance – referenceDistance) /
                                                (maximumDistance – referenceDistance))
     
        With all the distance models, if the formula can not be evaluated then the source will not 
        be attenuated. For example, if a linear model is being used with referenceDistance equal 
        to maximumDistance, then the gain equation will have a divide-by-zero error in it. In this case,
        there is no attenuation for that source.
     
        All the values for distance are specified in meters.
*/
typedef NS_ENUM(NSInteger, AVAudioEnvironmentDistanceAttenuationModel) {
    AVAudioEnvironmentDistanceAttenuationModelExponential   = 1,
    AVAudioEnvironmentDistanceAttenuationModelInverse       = 2,
    AVAudioEnvironmentDistanceAttenuationModelLinear        = 3
} NS_ENUM_AVAILABLE(10_10, 8_0);


/*! @class AVAudioEnvironmentDistanceAttenuationParameters
    @abstract Parameters specifying the amount of distance attenuation
    @discussion
        A standalone instance of AVAudioEnvironmentDistanceAttenuationParameters cannot be created. 
        Only an instance vended out by a source object (e.g. AVAudioEnvironmentNode) can be used.
*/
API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
@interface AVAudioEnvironmentDistanceAttenuationParameters : NSObject {
@private
	void *_impl;
}

- (instancetype)init NS_UNAVAILABLE;

/*! @property distanceAttenuationModel
    @abstract Type of distance attenuation model
    @discussion
        Default:    AVAudioEnvironmentDistanceAttenuationModelInverse
*/
@property (nonatomic) AVAudioEnvironmentDistanceAttenuationModel distanceAttenuationModel;

/*! @property referenceDistance
    @abstract The minimum distance at which attenuation is applied
    @discussion
        Default:    1.0 meter
        Models:     AVAudioEnvironmentDistanceAttenuationModelInverse,
                    AVAudioEnvironmentDistanceAttenuationModelLinear
*/
@property (nonatomic) float referenceDistance;

/*! @property maximumDistance
    @abstract The distance beyond which no further attenuation is applied
    @discussion
        Default:    100000.0 meters
        Models:     AVAudioEnvironmentDistanceAttenuationModelLinear
*/
@property (nonatomic) float maximumDistance;

/*! @property rolloffFactor
    @abstract Determines the attenuation curve
    @discussion
        A higher value results in a steeper attenuation curve.
        The rolloff factor should be a value greater than 0.
        Default:    1.0
        Models:     AVAudioEnvironmentDistanceAttenuationModelExponential
                    AVAudioEnvironmentDistanceAttenuationModelInverse
                    AVAudioEnvironmentDistanceAttenuationModelLinear
*/
@property (nonatomic) float rolloffFactor;

@end


/*! @class AVAudioEnvironmentReverbParameters
    @abstract Parameters used to control the reverb in AVAudioEnvironmentNode
    @discussion
        Reverberation can be used to simulate the acoustic characteristics of an environment.
        AVAudioEnvironmentNode has a built in reverb that describes the space that the listener 
        is in.
 
        The reverb also has a single filter that sits at the end of the chain. This filter is useful 
        to shape the overall sound of the reverb. For instance, one of the reverb presets can be 
        selected to simulate the general space and then the filter can be used to brighten or darken 
        the overall sound.
 
        A standalone instance of AVAudioEnvironmentReverbParameters cannot be created.
        Only an instance vended out by a source object (e.g. AVAudioEnvironmentNode) can be used.
*/

API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
@interface AVAudioEnvironmentReverbParameters : NSObject {
@private
	void *_impl;
}

- (instancetype)init NS_UNAVAILABLE;

/*! @property enable
    @abstract Turns on/off the reverb
    @discussion
        Default:    NO
*/
@property (nonatomic) BOOL enable;

/*! @property level
    @abstract Controls the master level of the reverb
    @discussion
        Range:      -40 to 40 dB
        Default:    0.0
*/
@property (nonatomic) float level;

/*! @property filterParameters
    @abstract filter that applies to the output of the reverb
*/
@property (nonatomic, readonly) AVAudioUnitEQFilterParameters *filterParameters;

/*! @method loadFactoryReverbPreset:
    @abstract Load one of the reverb's factory presets
    @param preset
        Reverb preset to be set.
    @discussion
        Loading a factory reverb preset changes the sound of the reverb. This works independently
        of the filter which follows the reverb in the signal chain.
*/
- (void)loadFactoryReverbPreset:(AVAudioUnitReverbPreset)preset;

@end


/*! @enum AVAudioEnvironmentOutputType
 @abstract   Types of output for AVAudio3DMixingRenderingAlgorithmAuto
 @discussion
    The output type determines the rendering method for any input bus using
    AVAudio3DMixingRenderingAlgorithmAuto.
 
    AVAudioEnvironmentOutputTypeAuto
        Automatically detect playback route and pick the correct output type when possible.
        Wired output defaults to AVAudioEnvironmentOutputTypeHeadphones and Manual Rendering
        with a two-channel output layout defaults to AVAudioEnvironmentOutputTypeExternalSpeakers.
 
    AVAudioEnvironmentOutputTypeHeadphones
        Render for headphones.
 
    AVAudioEnvironmentOutputTypeBuiltInSpeakers
        Render for built-in speakers on the current hardware. The output will not be suitable
        for playback on other hardware. On iOS devices, the rendering may be specific to
        device orientation. Manual Rendering modes may not provide the intended rendering if
        the orientation changes between rendering the audio and playing it back.
 
    AVAudioEnvironmentOutputTypeExternalSpeakers
        Render for external speakers based on the environment node's output channel layout.
 */
typedef NS_ENUM(NSInteger, AVAudioEnvironmentOutputType) {
    AVAudioEnvironmentOutputTypeAuto                = 0,
    AVAudioEnvironmentOutputTypeHeadphones          = 1,
    AVAudioEnvironmentOutputTypeBuiltInSpeakers     = 2,
    AVAudioEnvironmentOutputTypeExternalSpeakers    = 3
} API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);


/*!
    @class AVAudioEnvironmentNode
    @abstract Mixer node that simulates a 3D environment
    @discussion
        AVAudioEnvironmentNode is a mixer node that simulates a 3D audio environment. Any node that 
        conforms to the AVAudioMixing protocol (e.g. AVAudioPlayerNode) can act as a source in this
        environment.
 
        The environment has an implicit "listener". By controlling the listener's position and
        orientation, the application controls the way the user experiences the virtual world. 
        In addition, this node also defines properties for distance attenuation and reverberation 
        that help characterize the environment.
 
        It is important to note that AVAudio3DMixingSourceMode affects how inputs with different channel
        configurations are rendered. By default, only inputs with a mono channel are spatialized.
 
        In order to set the environment node’s output to a multichannel format, use an AVAudioFormat
        with a desired AudioChannelLayout.
*/

API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVAudioEnvironmentNode : AVAudioNode <AVAudioMixing>

- (instancetype)init NS_DESIGNATED_INITIALIZER;

/*! @property outputType
    @abstract Type of output hardware to be used with AVAudio3DMixingRenderingAlgorithmAuto
    @discussion
        Output hardware cannot be automatically determined in Manual Rendering modes or for wired
        output. This property can be used to override the output type if the correct type is known.
 
        Selecting an output type that does not match the actual hardware can produce unexpected
        results, especially with AVAudioEnvironmentOutputTypeBuiltInSpeakers. An app choosing
        a value other than AVAudio3DMixingOutputTypeAuto should listen to route change
        notifications and update the output type accordingly.
 
        Default:    AVAudio3DMixingOutputTypeAuto
 */
@property (nonatomic) AVAudioEnvironmentOutputType outputType API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos) ;

/*! @property outputVolume
	@abstract The mixer's output volume.
	@discussion
        This accesses the mixer's output volume (0.0-1.0, inclusive).
*/
@property (nonatomic) float outputVolume;

/*! @property nextAvailableInputBus
    @abstract Find an unused input bus
    @discussion
        This will find and return the first input bus to which no other node is connected.
*/
@property (nonatomic, readonly) AVAudioNodeBus nextAvailableInputBus;

/*! @property listenerPosition
    @abstract Sets the listener's position in the 3D environment
    @discussion
        The coordinates are specified in meters.
        Default:
            The default position of the listener is at the origin.
            x: 0.0
            y: 0.0
            z: 0.0
*/
@property (nonatomic) AVAudio3DPoint listenerPosition;

/*! @property listenerVectorOrientation
    @abstract The listener's orientation in the environment
    @discussion
    Changing listenerVectorOrientation will result in a corresponding change in listenerAngularOrientation.
        Default:
            The default orientation is with the listener looking directly along the negative Z axis.
            forward: (0, 0, -1)
            up:      (0, 1, 0)
*/
@property (nonatomic) AVAudio3DVectorOrientation listenerVectorOrientation;

/*! @property listenerAngularOrientation
    @abstract The listener's orientation in the environment
    @discussion
    Changing listenerAngularOrientation will result in a corresponding change in listenerVectorOrientation.
        All angles are specified in degrees.
        Default:
            The default orientation is with the listener looking directly along the negative Z axis.
            yaw: 0.0
            pitch: 0.0
            roll: 0.0
*/
@property (nonatomic) AVAudio3DAngularOrientation listenerAngularOrientation;

/*! @property distanceAttenuationParameters
    @abstract The distance attenuation parameters for the environment
*/
@property (nonatomic, readonly) AVAudioEnvironmentDistanceAttenuationParameters *distanceAttenuationParameters;

/*! @property reverbParameters
    @abstract The reverb parameters for the environment
*/
@property (nonatomic, readonly) AVAudioEnvironmentReverbParameters *reverbParameters;

/*! @property applicableRenderingAlgorithms
    @abstract Returns an array of AVAudio3DMixingRenderingAlgorithm values based on the current output format
    @discussion
        AVAudioEnvironmentNode supports several rendering algorithms per input bus which are defined 
        in <AVFAudio/AVAudioMixing.h>.
 
        Depending on the current output format of the environment node, this method returns 
        an immutable array of the applicable rendering algorithms. This is important when the
        environment node has been configured to a multichannel output format because only a subset
        of the available rendering algorithms are designed to render to all of the channels.
        
        This information should be retrieved after a successful connection to the destination node 
        via the engine's connect method.
*/
@property (nonatomic, readonly) NSArray<NSNumber *> *applicableRenderingAlgorithms;

/*! @property listenerHeadTrackingEnabled
    @abstract On capable devices, listener orientation will be automatically rotated based on user's head-orientation if enabled.
*/
@property (nonatomic, getter=isListenerHeadTrackingEnabled) BOOL listenerHeadTrackingEnabled API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0)) API_UNAVAILABLE( watchos, visionos);

@end

NS_ASSUME_NONNULL_END
