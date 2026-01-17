//
//  PHASEMixer.h
//  PHASE
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef PHASEMixer_h
#define PHASEMixer_h

#import <AVFoundation/AVFAudio.h>
#import <simd/types.h>

#import <PHASE/PHASETypes.h>
#import <PHASE/PHASEDefinition.h>

@class PHASESource;
@class PHASEListener;
@class PHASENumberMetaParameterDefinition;
@class PHASEMetaParameter;
@class PHASEDistanceModelParameters;
@class PHASEDirectivityModelParameters;
@class PHASESpatialPipeline;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - PHASEMixerDefinition

/****************************************************************************************************/
/*!
    @interface PHASEMixerDefinition
    @abstract The base class for a mixer definition.
    @discussion
        Mixer definitions control how audio will be rendered to the output in PHASE.
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEMixerDefinition : PHASEDefinition

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @property gain
    @abstract Linear gain scalar.
    @note
        Values are clamped to the range [0, 1]. Default value is 1.
*/
@property(nonatomic) double gain;

/*!
    @property gainMetaParameterDefinition
    @abstract Optionally attach a metaparameter definition here to enable real-time control of the gain during playback.
*/
@property(nonatomic, strong, nullable) PHASENumberMetaParameterDefinition* gainMetaParameterDefinition;

@end

#pragma mark - PHASESpatialMixerDefinition

/****************************************************************************************************/
/*!
    @interface PHASESpatialMixerDefinition
    @abstract Spatial mixer definition.
    @discussion
        Spatial mixers render audio with spatialization and environmental effects.
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASESpatialMixerDefinition : PHASEMixerDefinition

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method initWithSpatialPipeline
    @abstract Create a new PHASESpatialMixerDefinition
    @param spatialPipeline
        A spatial pipeline.
    @return
        A new PHASESpatialMixerDefinition object
*/
- (instancetype)initWithSpatialPipeline:(PHASESpatialPipeline*)spatialPipeline NS_DESIGNATED_INITIALIZER;

/*!
    @method initWithSpatialPipeline:identifier
    @abstract Create a new PHASESpatialMixerDefinition
    @param spatialPipeline
        A spatial pipeline.
    @param identifier
        An optional custom identifier to give to this object
    @return
        A new PHASESpatialMixerDefinition object
*/
- (instancetype)initWithSpatialPipeline:(PHASESpatialPipeline*)spatialPipeline identifier:(NSString*)identifier;

/*!
    @property spatialPipeline
    @abstract Spatial Pipeline.
*/
@property(nonatomic, strong, readonly) PHASESpatialPipeline* spatialPipeline;

/*!
    @property distanceModelParameters
    @abstract Distance model parameters (optional).
*/
@property(nullable, nonatomic, strong) PHASEDistanceModelParameters* distanceModelParameters;

/*!
    @property listenerDirectivityModelParameters
    @abstract Listener directivity model parameters (optional).
*/
@property(nullable, nonatomic, strong) PHASEDirectivityModelParameters* listenerDirectivityModelParameters;

/*!
    @property sourceDirectivityModelParameters
    @abstract Source directivity model parameters (optional).
*/
@property(nullable, nonatomic, strong) PHASEDirectivityModelParameters* sourceDirectivityModelParameters;

@end

#pragma mark - PHASEAmbientMixerDefinition

/****************************************************************************************************/
/*!
    @interface PHASEAmbientMixerDefinition
    @abstract Ambient mixer definition.
    @discussion
        Ambient mixers render audio with spatialization but without environmental effects.
        Use ambient mixers for content that isn't being simulated in the environment,
        but should still sound like it's coming from somewhere out in space.
    @note
        Ambient mixers do not support distance modeling or directivity modeling.
        Clients can however set the orientation at initialization time.
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEAmbientMixerDefinition : PHASEMixerDefinition

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method initWithChannelLayout:orientation:identifier
    @abstract Create a new PHASEAmbientMixerDefinition
    @param layout
        The input channel layout for this ambient mixer node. Any connected sampler must match this channel layout.
    @param orientation
        The orientation of the speaker layout, relative to scene root, as a quaternion.
    @param identifier
        An optional custom identifier to give to this object
    @return
        A new PHASEAmbientMixerDefinition object
*/
- (instancetype)initWithChannelLayout:(AVAudioChannelLayout*)layout orientation:(simd_quatf)orientation identifier:(NSString*)identifier
NS_SWIFT_NAME(init(channelLayout:orientation:identifier:));

/*!
    @method initWithChannelLayout:orientation
    @abstract Create a new PHASEAmbientMixerDefinition
    @param layout
        The input channel layout for this channel mixer node. Any connected sampler must match this channel layout.
    @param orientation
        The orientation of the speaker layout, relative to scene root, as a quaternion.
    @return
        A new PHASEAmbientMixerDefinition object
*/
- (instancetype)initWithChannelLayout:(AVAudioChannelLayout*)layout orientation:(simd_quatf)orientation NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(channelLayout:orientation:));

/*!
    @property orientation
    @abstract A readonly value of the ambient source's orientation relative to the scene root.
*/
@property(nonatomic, readonly) simd_quatf orientation;

/*!
    @property inputChannelLayout
    @abstract A readonly value of the input channel layout this mixer was initialized with.
*/
@property(nonatomic, strong, readonly) AVAudioChannelLayout* inputChannelLayout;

@end

#pragma mark - PHASEChannelMixerDefinition

/****************************************************************************************************/
/*!
    @interface PHASEChannelMixerDefinition
    @abstract Channel mixer definition.
    @discussion
        Channel mixers render audio without spatialization or environmental effects.
        Use channel mixers for regular stem-based content that needs be rendered directly to the output device, such as stereo music
        or center channel narrative dialogue.
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEChannelMixerDefinition : PHASEMixerDefinition

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method initWithChannelLayout:identifier
    @abstract Create a new PHASEChannelMixerDefinition
    @note
        Any connected sampler must match this channel layout.
    @param layout
        The input channel layout.
    @param identifier
        An optional custom identifier to give to this object
    @return
        A new PHASEChannelMixerDefinition object
*/
- (instancetype)initWithChannelLayout:(AVAudioChannelLayout*)layout identifier:(NSString*)identifier
NS_SWIFT_NAME(init(channelLayout:identifier:));

/*!
    @method initWithChannelLayout
    @abstract Create a new PHASEChannelMixerDefinition
    @note
        Any connected sampler must match this channel layout.
    @param layout
        The input channel layout. Any connected sampler must match this channel layout.
    @return
        A new PHASEChannelMixerDefinition object
*/
- (instancetype)initWithChannelLayout:(AVAudioChannelLayout*)layout NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(channelLayout:));

/*!
    @property inputChannelLayout
    @abstract A readonly value of the input channel layout this mixer was initialized with.
*/
@property(nonatomic, strong, readonly) AVAudioChannelLayout* inputChannelLayout;

@end


#pragma mark - PHASEMixer

/****************************************************************************************************/
/*!
    @interface PHASEMixer
    @abstract A generic object the represents an active mixer in the system
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEMixer : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @property identifier
    @abstract The identifier that uniquely represents this mixer.
*/
@property(nonatomic, readonly, strong) NSString* identifier;

/*!
    @property gain
    @abstract Linear gain scalar.
    @note Values are clamped to the range [0, 1]. Default value is 1.
*/
@property(nonatomic, readonly) double gain;

/*!
    @property gainMetaParameter
    @abstract The metaparameter that can be used to adjust the gain during playback
*/
@property(nonatomic, strong, readonly, nullable) PHASEMetaParameter* gainMetaParameter;

@end

#pragma mark - PHASEMixerParameters

/****************************************************************************************************/
/*!
    @interface PHASEMixerParameters
    @abstract An object that holds runtime parameters for mixers when creating PHASESoundEvents.
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEMixerParameters : NSObject

/*!
    @method addSpatialMixerParametersWithIdentifier:source:listener
    @abstract Adds runtime parameters for a spatial mixer
    @param identifier
        The unique identifier assigned to a spatial submixer object.
    @param source
        The PHASESource object that this mixer will use to spatialize sounds.
    @param listener
        The PHASEListener object that this mixer will use to spatialize sounds.
*/
- (void)addSpatialMixerParametersWithIdentifier:(NSString*)identifier source:(PHASESource*)source listener:(PHASEListener*)listener
NS_SWIFT_NAME(addSpatialMixerParameters(identifier:source:listener:));

/*!
    @method addAmbientMixerParametersWithIdentifier:listener
    @abstract Adds runtime parameters for an ambient mixer
    @param identifier
        The unique identifier assigned to a spatial submixer object.
    @param listener
        The PHASEListener object that this mixer will use to orient sounds.
*/
- (void)addAmbientMixerParametersWithIdentifier:(NSString*)identifier listener:(PHASEListener*)listener
NS_SWIFT_NAME(addAmbientMixerParameters(identifier:listener:));

@end

NS_ASSUME_NONNULL_END

#endif /* PHASEMixer_h */
