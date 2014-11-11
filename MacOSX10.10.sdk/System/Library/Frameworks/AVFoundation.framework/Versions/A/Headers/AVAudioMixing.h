/*
    File:       AVAudioMixing.h
    Framework:	AVFoundation
 
    Copyright (c) 2014 Apple Inc. All Rights Reserved.
*/

#import <AVFoundation/AVAudioTypes.h>


/*! @protocol   AVAudioMixing
    @abstract   Protocol that defines properties applicable to the input bus of a mixer
                node
    @discussion
        Nodes that conforms to the AVAudioMixing protocol can talk to a mixer node downstream,
        specifically of type AVAudioMixerNode or AVAudioEnvironmentNode. The properties defined 
        by this protocol apply to the respective input bus of the mixer node that the source node is 
        connected to. Note that effect nodes cannot talk to their downstream mixer.
 
        The state of properties that are set via this protocol before the source node is connected 
        to the mixer node are cached and then applied on the mixer once the physical connection is 
        made. Similarly, after disconnection, the state of the properties are once again cached.
 
        Source nodes can be disconnected from one mixer and connected to another mixer with their 
        mixing settings intact. For example, an AVAudioPlayerNode that is being used in a gaming scenario
        can set up its 3D mixing settings and then move from one environment to another.
*/
@protocol AVAudioStereoMixing;
@protocol AVAudio3DMixing;

NS_CLASS_AVAILABLE(10_10, 8_0)
@protocol AVAudioMixing <AVAudioStereoMixing, AVAudio3DMixing>

/*! @property volume
    @abstract Set a bus's input volume
    @discussion
        Range:      0.0 -> 1.0
        Default:    1.0
        Mixers:     AVAudioMixerNode, AVAudioEnvironmentNode
*/
@property (nonatomic) float volume;

@end


/*! @protocol   AVAudioStereoMixing
    @abstract   Protocol that defines stereo mixing properties
*/
NS_CLASS_AVAILABLE(10_10, 8_0)
@protocol AVAudioStereoMixing <NSObject>

/*! @property pan
    @abstract Set a bus's stereo pan
    @discussion
        Range:      -1.0 -> 1.0
        Default:    0.0
        Mixer:      AVAudioMixerNode
*/
@property (nonatomic) float pan;

@end


/*! @enum AVAudio3DMixingRenderingAlgorithm
    @abstract   Types of rendering algorithms available per input bus of the environment node
    @discussion
        The rendering algorithms differ in terms of quality and cpu cost. 
        AVAudio3DMixingRenderingAlgorithmEqualPowerPanning is the simplest panning algorithm and also 
        the least expensive computationally.
 
        With the exception of AVAudio3DMixingRenderingAlgorithmSoundField, while the mixer is
        rendering to multi channel hardware, audio data will only be rendered to channels 1 & 2.
 
        AVAudio3DMixingRenderingAlgorithmEqualPowerPanning
            EqualPowerPanning merely pans the data of the mixer bus into a stereo field. This 
            algorithm is analogous to the pan knob found on a mixing board channel strip. 
 
        AVAudio3DMixingRenderingAlgorithmSphericalHead
            SphericalHead is designed to emulate 3 dimensional space in headphones by simulating 
            inter-aural time delays and other spatial cues. SphericalHead is slightly less CPU 
            intensive than the HRTF algorithm.
 
        AVAudio3DMixingRenderingAlgorithmHRTF
            HRTF (Head Related Transfer Function) is a high quality algorithm using filtering to 
            emulate 3 dimensional space in headphones. HRTF is a cpu intensive algorithm.
 
        AVAudio3DMixingRenderingAlgorithmSoundField
            SoundField is designed for rendering to multi channel hardware. The mixer takes data 
            being rendered with SoundField and distributes it amongst all the output channels with 
            a weighting toward the location in which the sound derives. It is very effective for 
            ambient sounds, which may derive from a specific location in space, yet should be heard 
            through the listener's entire space.
 
        AVAudio3DMixingRenderingAlgorithmStereoPassThrough
            StereoPassThrough should be used when no localization is desired for the source data. 
            Setting this algorithm tells the mixer to take mono/stereo input and pass it directly to 
            channels 1 & 2 without localization.
 
*/
typedef NS_ENUM(NSInteger, AVAudio3DMixingRenderingAlgorithm) {
    AVAudio3DMixingRenderingAlgorithmEqualPowerPanning      = 0,
    AVAudio3DMixingRenderingAlgorithmSphericalHead          = 1,
    AVAudio3DMixingRenderingAlgorithmHRTF                   = 2,
    AVAudio3DMixingRenderingAlgorithmSoundField             = 3,
    AVAudio3DMixingRenderingAlgorithmStereoPassThrough      = 5
} NS_ENUM_AVAILABLE(10_10, 8_0);


/*! @protocol   AVAudio3DMixing
    @abstract   Protocol that defines 3D mixing properties
*/
@protocol AVAudio3DMixing <NSObject>

/*! @property renderingAlgorithm
    @abstract Type of rendering algorithm used
    @discussion
        Depending on the current output format of the AVAudioEnvironmentNode, only a subset of the 
        rendering algorithms may be supported. An array of valid rendering algorithms can be 
        retrieved by calling applicableRenderingAlgorithms on AVAudioEnvironmentNode.
 
        Default:    AVAudio3DMixingRenderingAlgorithmEqualPowerPanning
        Mixer:      AVAudioEnvironmentNode
*/
@property (nonatomic) AVAudio3DMixingRenderingAlgorithm renderingAlgorithm;

/*! @property rate
    @abstract Changes the playback rate of the input signal
    @discussion
        A value of 2.0 results in the output audio playing one octave higher.
        A value of 0.5, results in the output audio playing one octave lower.
     
        Range:      0.5 -> 2.0
        Default:    1.0
        Mixer:      AVAudioEnvironmentNode
*/
@property (nonatomic) float rate;

/*! @property reverbBlend
    @abstract Controls the blend of dry and reverb processed audio
    @discussion
        This property controls the amount of the source's audio that will be processed by the reverb 
        in AVAudioEnvironmentNode. A value of 0.5 will result in an equal blend of dry and processed 
        (wet) audio.
 
        Range:      0.0 (completely dry) -> 1.0 (completely wet)
        Default:    0.0
        Mixer:      AVAudioEnvironmentNode
*/
@property (nonatomic) float reverbBlend;

/*! @property obstruction
    @abstract Simulates filtering of the direct path of sound due to an obstacle
    @discussion
        Only the direct path of sound between the source and listener is blocked.
 
        Range:      -100.0 -> 0.0 dB
        Default:    0.0
        Mixer:      AVAudioEnvironmentNode
*/
@property (nonatomic) float obstruction;

/*! @property occlusion
    @abstract Simulates filtering of the direct and reverb paths of sound due to an obstacle
    @discussion
        Both the direct and reverb paths of sound between the source and listener are blocked.
 
        Range:      -100.0 -> 0.0 dB
        Default:    0.0
        Mixer:      AVAudioEnvironmentNode
*/
@property (nonatomic) float occlusion;

/*! @property position
    @abstract The location of the source in the 3D environment
    @discussion
        The coordinates are specified in meters.
 
        Mixer:      AVAudioEnvironmentNode
*/
@property (nonatomic) AVAudio3DPoint position;

@end

