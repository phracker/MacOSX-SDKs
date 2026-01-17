//
//  PHASESoundEventNodes.h
//  PHASE
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef PHASESoundEventNodes_h
#define PHASESoundEventNodes_h

#import <AVFAudio/AVAudioBuffer.h>
#import <AVFAudio/AVAudioFormat.h>
#import <AVFAudio/AVAudioTime.h>
#import <PHASE/PHASEEnvelope.h>
#import <PHASE/PHASEMetaParameter.h>
#import <PHASE/PHASEMixer.h>
#import <PHASE/PHASETypes.h>
#import <PHASE/PHASEGroup.h>

@class PHASESoundAsset;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - PHASEPushStreamBufferOptions

/****************************************************************************************************/
/*!
    @enum PHASEPushStreamBufferOptions
    @abstract Options controlling buffer scheduling.
    @constant PHASEPushStreamBufferDefault
        The buffer plays following any previously scheduled buffer(s).
    @constant PHASEPushStreamBufferLoops
        The buffer loops indefinitely.
    @constant PHASEPushStreamBufferInterrupts
        The buffer interrupts any buffer already playing.
    @constant PHASEPushStreamBufferInterruptsAtLoop
        The buffer interrupts any buffer already playing, at its loop point.
*/
typedef NS_OPTIONS(NSUInteger, PHASEPushStreamBufferOptions) {
    PHASEPushStreamBufferDefault = 1UL << 0,          // 0x01
    PHASEPushStreamBufferLoops = 1UL << 1,            // 0x02
    PHASEPushStreamBufferInterrupts = 1UL << 2,       // 0x04
    PHASEPushStreamBufferInterruptsAtLoop = 1UL << 3  // 0x08
};

#pragma mark - PHASEPushStreamCompletionCallbackCondition

/*!
    @enum PHASEPushStreamCompletionCallbackCondition
    @abstract Specifies when the completion handler must be invoked.
    @constant PHASEPushStreamCompletionDataRendered
        The buffer data has been rendered by the player.
        This does not account for any signal processing latencies downstream of the player in the engine.
*/
typedef NS_ENUM(NSInteger, PHASEPushStreamCompletionCallbackCondition) {
    PHASEPushStreamCompletionDataRendered = 0,
};

#pragma mark - PHASESoundEventNodeDefinition

/****************************************************************************************************/
/*!
    @interface PHASESoundEventNodeDefinition
    @abstract The base class for a sound event node definition.
    @discussion
        Sound event nodes are a hierarchical collection of objects that either generate or control playback of audio content in PHASE.
        Generator nodes produce audio. They are always leaf nodes in a node hierarchy. These include samplers and stream nodes.
        Control nodes set the logic for how generator nodes are selected, mixed and parameterized before downstream mixer processing.
        Control nodes are always parent nodes, and can be organized into hierarchies for complex sound design scenarios.
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASESoundEventNodeDefinition : PHASEDefinition

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @property children
    @abstract The children of this node definition.
*/
@property(readonly, copy) NSArray<PHASESoundEventNodeDefinition*>* children;

@end


#pragma mark - PHASEGeneratorNodeDefinition

/****************************************************************************************************/
/*!
    @interface PHASEGeneratorNodeDefinition
    @abstract An object for defining a generator node when building a sound event.
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEGeneratorNodeDefinition : PHASESoundEventNodeDefinition

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method setCalibrationMode:level
    @abstract Set the generator's calibration mode and level.
    @param calibrationMode
        The calibration mode.
    @param level
        The level.
    @note
        The level, including its underlying unit and range, are dependent on the calibration mode.
*/
- (void)setCalibrationMode:(PHASECalibrationMode)calibrationMode level:(double)level
NS_SWIFT_NAME(setCalibrationMode(calibrationMode:level:));

/*!
    @property calibrationMode
    @abstract The generator's calibration mode. The default value is PHASECalibrationModeNone.
*/
@property(readonly) PHASECalibrationMode calibrationMode;

/*!
    @property level
    @abstract The generator's level. The default value is 1.
    @note The level's underlying unit and range are dependent on the calibrationMode.
*/
@property(readonly) double level;

/*!
    @property rate
    @abstract Linear rate scalar.
    @note
        Values are clamped to the range [0.25, 4]. Default value is 1.
*/
@property(nonatomic, assign) double rate;

/*!
    @property group
    @abstract The PHASEGroup object this generator should be associated with for gain and rate control.
*/
@property(nonatomic, nullable, weak) PHASEGroup* group;

/*!
    @property gainMetaParameterDefinition
    @abstract Optionally attach a metaparameter definition here to enable dynamic control of the gain during playback.
*/
@property(nonatomic, strong, nullable, readwrite) PHASENumberMetaParameterDefinition* gainMetaParameterDefinition;

/*!
    @property rateMetaParameterDefinition
    @abstract Optionally attach a metaparameter definition here to enable dynamic control of the rate during playback.
*/
@property(nonatomic, strong, nullable, readwrite) PHASENumberMetaParameterDefinition* rateMetaParameterDefinition;

/*!
    @property mixerDefinition
    @abstract The readonly property that returns the PHASEMixerDefinition this generator was created with and assigned to.
*/
@property(nonatomic, strong, readonly) PHASEMixerDefinition* mixerDefinition;

@end

#pragma mark - PHASESamplerNodeDefinition

/****************************************************************************************************/
/*!
    @interface PHASESamplerNodeDefinition
    @abstract Sampler node definition.
    @discussion
        Sampler nodes play back registered sound assets.
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASESamplerNodeDefinition : PHASEGeneratorNodeDefinition

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*! @method initWithSoundAssetIdentifier:mixerDefinition:identifier
    @abstract Create a sampler node definition
    @param soundAssetIdentifier
        The identifier of the registered sound asset this sampler will play
    @param mixerDefinition
        The mixer definition this sampler will be assigned to
    @param identifier
        An optional custom identifier to give to this object
    @return
        A new PHASESamplerNodeDefinition object
*/
- (instancetype)initWithSoundAssetIdentifier:(NSString*)soundAssetIdentifier mixerDefinition:(PHASEMixerDefinition*)mixerDefinition identifier:(NSString*)identifier;

/*! @method initWithSoundAssetIdentifier:mixerDefinition
    @abstract Create a sampler node definition
    @param soundAssetIdentifier
        The identifier of the registered sound asset this sampler will play
    @param mixerDefinition
        The mixer definition this sampler will be assigned to
    @return
        A new PHASESamplerNodeDefinition object
*/
- (instancetype)initWithSoundAssetIdentifier:(NSString*)soundAssetIdentifier
                      mixerDefinition:(PHASEMixerDefinition*)mixerDefinition NS_DESIGNATED_INITIALIZER;

/*! @property assetIdentifier
    @abstract The identifier that uniquely represents the registered sound asset this sampler will play.
*/
@property(nonatomic, strong, readonly) NSString* assetIdentifier;

/*! @property cullOption
    @abstract The cull option for the sampler.
    @discussion
        The default value is PHASECullOptionTerminate.
*/
 @property(nonatomic) PHASECullOption cullOption;

/*! @property playbackMode
    @abstract The playback mode for the sampler.
    @discussion
     If the playback mode is set to PHASEPlaybackModeOneShot, you need to make sure the the audio data in the registered sound asset associated with this sampler
 begins and ends at zero crossings. Otherwise, you'll hear a click when beginning playback and / or ending playback.
    If the playback mode is set to PHASEPlaybackModeLooping, you need to make sure the audio data in the registered sound asset associated with this sampler
 loops smoothly from the end sample to the start sample. Please verify this during authoring. Failing to do so will result in audible clicks at loop boundaries.
    The default value is PHASEPlaybackModeOneShot.
*/
@property(nonatomic) PHASEPlaybackMode playbackMode;

@end

#pragma mark - PHASEContainerNodeDefinition

/****************************************************************************************************/
/*!
    @interface PHASEContainerNodeDefinition
    @abstract An object for defining a container sound event node when building a sound event.
    @discussion
        A container node plays back all its children at once.
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEContainerNodeDefinition : PHASESoundEventNodeDefinition

/*!
    @method init
    @abstract Create a container node definition
    @return
        A new PHASEContainerNodeDefinition object
*/
- (instancetype)init;

/*!
    @method new
    @abstract Create a container node definition
    @return
        A new PHASEContainerNodeDefinition object
*/
+ (instancetype)new;

/*!
    @method initWithIdentifier
    @abstract Create a container node definition
    @param identifier
        An optional custom identifier to give to this object
    @return
        A new PHASEContainerNodeDefinition object
*/
- (instancetype)initWithIdentifier:(NSString*)identifier;

/*!
    @method addSubtree
    @abstract Add a subtree to this node
    @param subtree
        Add a subtree of PHASESoundEventNodeDefinition nodes beneath this node.
*/
- (void)addSubtree:(PHASESoundEventNodeDefinition*)subtree;

@end

#pragma mark - PHASEBlendNodeDefinition

/****************************************************************************************************/
/*!
    @interface PHASEBlendNodeDefinition
    @abstract An object for defining a blend sound event node when building a sound event.
    @discussion
        A blend node blends between its children based on a numeric parameter.
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEBlendNodeDefinition : PHASESoundEventNodeDefinition

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method initWithBlendMetaParameterDefinition:identifier
    @abstract Create a blend node definition
    @param blendMetaParameterDefinition
        A metaparameter definition that wil be used to control the parameter of the blend node at runtime.
    @param identifier
        An optional custom identifier to give to this object
    @return
        A new PHASEBlendNodeDefinition object
*/
- (instancetype)initWithBlendMetaParameterDefinition:(PHASENumberMetaParameterDefinition *)blendMetaParameterDefinition
                                          identifier:(NSString*)identifier;

/*!
    @method initWithBlendMetaParameterDefinition
    @abstract Create a blend node definition
    @param blendMetaParameterDefinition
        A metaparameter definition that wil be used to control the parameter of the blend node at runtime.
    @return
        A new PHASEBlendNodeDefinition object
*/
- (instancetype)initWithBlendMetaParameterDefinition:
    (PHASENumberMetaParameterDefinition *)blendMetaParameterDefinition
    NS_DESIGNATED_INITIALIZER;

/*!
    @method initDistanceBlendWithSpatialMixerDefinition:identifier
    @abstract Create a blend node definition
    @param spatialMixerDefinition
        A PHASESpatialMixerDefinition that will bind the blend parameter to the distance between the source and listener.
    @param identifier
        An optional custom identifier to give to this object
    @return
        A new PHASEBlendNodeDefinition object
*/
- (instancetype)initDistanceBlendWithSpatialMixerDefinition:(PHASESpatialMixerDefinition *)spatialMixerDefinition
                                                 identifier:(NSString*)identifier
NS_SWIFT_NAME(init(spatialMixerDefinition:identifier:));


/*!
    @method initDistanceBlendWithSpatialMixerDefinition
    @abstract Create a blend node definition
    @param spatialMixerDefinition
        A PHASESpatialMixerDefinition that will bind the blend parameter to the distance between the source and listener.
    @return
        A new PHASEBlendNodeDefinition object
*/
- (instancetype)initDistanceBlendWithSpatialMixerDefinition:
    (PHASESpatialMixerDefinition *)spatialMixerDefinition
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(spatialMixerDefinition:));

/*!
    @property blendParameterDefinition
    @abstract The readonly property that returns the PHASENumberMetaParameterDefinition this blend node was created with and assigned to.
*/
@property(nonatomic, strong, readonly, nullable)
    PHASENumberMetaParameterDefinition* blendParameterDefinition;

/*!
    @property distanceSpatialMixerDefinition
    @abstract The readonly property that returns the PHASESpatialMixerDefinition this blend node was created with and assigned to.
*/
@property(nonatomic, strong, readonly, nullable)
    PHASESpatialMixerDefinition* spatialMixerDefinitionForDistance;


/*!
    @method addRangeForInputValuesBelow:fullGainAtValue:fadeCurveType:subtree
    @abstract Create a blend range that is active for all values below a given threshold.
    @param value
        The value for which the range will be active if the blend node's input value is below this threshold.
    @param fullGainAtValue
        This value defines a threshold for which a fade curve will be applied to the gain, when the input value is between "value" and "fullGainAtValue".
    @param fadeCurveType
        A curve type that defines which kind of fade curve to apply.
    @param subtree
        A PHASESoundEventNodeDefinition subtree that will be active for this range.
*/
- (void)addRangeForInputValuesBelow:(double)value
                    fullGainAtValue:(double)fullGainAtValue
                      fadeCurveType:(PHASECurveType)fadeCurveType
                            subtree:(PHASESoundEventNodeDefinition*)subtree
NS_SWIFT_NAME(addRangeForInputValuesBelow(value:fullGainAtValue:fadeCurveType:subtree:));

/*!
    @method addRangeForInputValuesBetween:highValue:fullGainAtLowValue:fullGainAtHighValue:lowFadeCurveType:highFadeCurveType:subtree
    @abstract Create a blend range that is active for all input values between lowValue and highValue
    @param lowValue
        The lower bound for which this range is active.
    @param highValue
        The upper bound for which this range is active.
    @param fullGainAtLowValue
        The threshold for which a fade curve defined by lowFadeCurveType will be applied to the gain when the input value is between lowValue and fullGainAtLowValue
    @param fullGainAtHighValue
        The threshold for which a fade curve defined by highFadeCurveType will be applied to the gain when the input value is between highValue and fullGainAtHighValue
    @param lowFadeCurveType
        A curve type that defines which kind of fade curve to apply for the low fade range.
    @param highFadeCurveType
        A curve type that defines which kind of fade curve to apply for the high fade range..
    @param subtree
        A PHASESoundEventNodeDefinition subtree that will be active for this range.
*/
- (void)addRangeForInputValuesBetween:(double)lowValue
                            highValue:(double)highValue
                   fullGainAtLowValue:(double)fullGainAtLowValue
                  fullGainAtHighValue:(double)fullGainAtHighValue
                     lowFadeCurveType:(PHASECurveType)lowFadeCurveType
                    highFadeCurveType:(PHASECurveType)highFadeCurveType
                              subtree:(PHASESoundEventNodeDefinition*)subtree
NS_SWIFT_NAME(addRangeForInputValuesBetween(lowValue:highValue:fullGainAtLowValue:fullGainAtHighValue:lowFadeCurveType:highFadeCurveType:subtree:));

/*!
    @method addRangeForInputValuesAbove:fullGainAtValue:fadeCurveType:subtree
    @abstract Create a blend range that is active for all values above a given threshold.
    @param value
        The value for which the range will be active if the blend node's input value is above this threshold.
    @param fullGainAtValue
        This value defines a threshold for which a fade curve will be applied to the gain, when the input value is between "value" and "fullGainAtValue".
    @param fadeCurveType
        A curve type that defines which kind of fade curve to apply.
    @param subtree
        A PHASESoundEventNodeDefinition subtree that will be active for this range.
*/
- (void)addRangeForInputValuesAbove:(double)value
                    fullGainAtValue:(double)fullGainAtValue
                      fadeCurveType:(PHASECurveType)fadeCurveType
                            subtree:(PHASESoundEventNodeDefinition*)subtree
NS_SWIFT_NAME(addRangeForInputValuesAbove(value:fullGainAtValue:fadeCurveType:subtree:));

/*!
    @method addRangeWithEnvelope:subtree
    @abstract Create a blend range defined by a PHASEEnvelope object.
    @param envelope
        The PHASEEnvelope object that defines the output gain for a range.
    @param subtree
        A PHASESoundEventNodeDefinition subtree that will be active for this range.
*/
- (void)addRangeWithEnvelope:(PHASEEnvelope*)envelope
                     subtree:(PHASESoundEventNodeDefinition*)subtree
NS_SWIFT_NAME(addRange(envelope:subtree:));

@end

#pragma mark - PHASESwitchNodeDefinition

/****************************************************************************************************/
/*!
    @interface PHASESwitchNodeDefinition
    @abstract An object for defining a switch sound event node when building a sound event.
    @discussion
        A switch node switches between its children based on a string parameter.
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASESwitchNodeDefinition : PHASESoundEventNodeDefinition

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method initWithSwitchMetaParameterDefinition:identifier
    @abstract Create a switch node definition
    @param switchMetaParameterDefinition
        A metaparameter definition that wil be used to control the parameter of the switch node at runtime.
    @param identifier
        An optional custom identifier to give to this object
    @return
        A new PHASESwitchNodeDefinition object
*/
- (instancetype)initWithSwitchMetaParameterDefinition:(PHASEStringMetaParameterDefinition*)switchMetaParameterDefinition
                                           identifier:(NSString*)identifier
NS_SWIFT_NAME(init(switchMetaParameterDefinition:identifier:));

/*!
    @method initWithSwitchMetaParameterDefinition
    @abstract Create a switch node definition
    @param switchMetaParameterDefinition
        A metaparameter definition that wil be used to control the parameter of the switch node at runtime.
    @return
        A new PHASESwitchNodeDefinition object
*/
- (instancetype)initWithSwitchMetaParameterDefinition:(PHASEStringMetaParameterDefinition*)switchMetaParameterDefinition
NS_SWIFT_NAME(init(switchMetaParameterDefinition:))NS_DESIGNATED_INITIALIZER;

/*!
    @method addSubtree
    @abstract Add a subtree to a switch node
    @param subtree
        A PHASESoundEventNodeDefinition that will be a child node of this switch node
    @param switchValue
        A string value that the metaparameter will use to activate this subtree
*/
- (void)addSubtree:(PHASESoundEventNodeDefinition*)subtree switchValue:(NSString*)switchValue;

/*!
    @property mixerDefinition
    @abstract The readonly property that returns the PHASEMixerDefinition this sampler was created with and assigned to.
*/
@property(nonatomic, strong, readonly) PHASEStringMetaParameterDefinition* switchMetaParameterDefinition;

@end


#pragma mark - PHASERandomNodeDefinition

/****************************************************************************************************/
/*!
    @interface PHASERandomNodeDefinition
    @abstract An object for defining a random sound event node when building a sound event.
    @discussion
        A random node selects one of its children based on a weighted random choice.
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASERandomNodeDefinition : PHASESoundEventNodeDefinition

/*!
    @method init
    @abstract Create a random node definition
    @return
        A new PHASERandomNodeDefinition object
*/
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/*!
    @method initWithIdentifier
    @abstract Create a random node definition
    @param identifier
        An optional custom identifier to give to this object
    @return
        A new PHASERandomNodeDefinition object
*/
- (instancetype)initWithIdentifier:(NSString*)identifier;

/*!
    @method addSubtree
    @abstract Add a subtree to a random node
    @param subtree
        A PHASESoundEventNodeDefinition that will be a child node of this random node
    @param weight
        The probability weight of this subtree.  Higher numbers compared to other subtree weights will increase the likelihood of being
        chosen. This value must be greater than or equal to 1, and is clamped otherwise.
*/
- (void)addSubtree:(PHASESoundEventNodeDefinition*)subtree weight:(NSNumber*)weight;

/*! @property uniqueSelectionQueueLength
    @abstract Subtrees will not be repeated until after this random node is activated uniqueSelectionQueueLength number of times.
*/
@property(nonatomic) NSInteger uniqueSelectionQueueLength;

@end

#pragma mark - PHASEStreamNode

/****************************************************************************************************/
/*!
    @interface PHASEStreamNode
    @abstract The base class for stream nodes, exposing common elements.
 */
OS_EXPORT API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos)
@interface PHASEStreamNode : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @property gainMetaParameter
    @abstract If specified during construction, the metaparameter for controlling gain will be available here
*/
@property(nonatomic, strong, nullable, readonly) PHASENumberMetaParameter* gainMetaParameter;

/*!
    @property rateMetaParameter
    @abstract If specified during construction, the metaparameter for controlling rate/pitch will be available here
*/
@property(nonatomic, strong, nullable, readonly) PHASENumberMetaParameter* rateMetaParameter;

/*!
    @property mixer
    @abstract The readonly property that returns the PHASEMixer this stream was created with and assigned to.
*/
@property(nonatomic, strong, readonly) PHASEMixer* mixer;

/*!
    @property format
    @abstract The readonly property that returns the AVAudioFormat that this stream was initialized with.
*/
@property(nonatomic, strong, readonly) AVAudioFormat* format;

@end

#pragma mark - PHASEPushStreamNodeDefinition

/****************************************************************************************************/
/*!
    @interface PHASEPushStreamNodeDefinition
    @abstract An object for defining a push stream sound event node when building a sound event.
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEPushStreamNodeDefinition : PHASEGeneratorNodeDefinition

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method initWithMixerDefinition:format:identifier
    @abstract Create a push stream node definition
    @param mixerDefinition
        The mixer definition this stream will be assigned to
    @param format
        The AVAudioFormat object that will define the attributes of the audio this node will accept.
        Only Core Audio's standard deinterleaved 32-bit floating-point formats are supported.
    @param identifier
        An optional custom identifier to give to this object
    @return
        A new PHASEPushStreamNodeDefinition object
*/
- (instancetype)initWithMixerDefinition:(PHASEMixerDefinition*)mixerDefinition format:(AVAudioFormat*)format identifier:(NSString*)identifier;

/*!
    @method initWithMixerDefinition:format
    @abstract Create a push stream node definition
    @param mixerDefinition
        The mixer definition this stream will be assigned to
    @param format
        The AVAudioFormat object that will define the attributes of the audio this node will accept.
        Only Core Audio's standard deinterleaved 32-bit floating-point formats are supported.
    @return
        A new PHASEPushStreamNodeDefinition object
*/
- (instancetype)initWithMixerDefinition:(PHASEMixerDefinition*)mixerDefinition format:(AVAudioFormat*)format NS_DESIGNATED_INITIALIZER;

/*!
    @property format
    @abstract The readonly property that returns the AVAudioFormat that this stream was initialized with
*/
@property(nonatomic, strong, readonly) AVAudioFormat* format;

/*!
    @property normalize
    @abstract Determines whether or not the engine should normalize the stream. The default value is NO.
    @discussion
        In general, clients are advised to normalize the input. Normalization is required to properly calibrate the output level.
        If you set this value to NO, it's advised that you do custom normalization of the audio data prior to passing the buffers to PHASE.
*/
@property(nonatomic) BOOL normalize;

@end

#pragma mark - PHASEPushStreamNode

/****************************************************************************************************/
/*!
    @interface PHASEPushStreamNode
    @abstract An object for addessing an instance of a stream in an executing sound event
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEPushStreamNode : PHASEStreamNode

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @property gainMetaParameter
    @abstract If specified during construction, the metaparameter for controlling gain will be available here
*/
@property(nonatomic, strong, nullable, readonly) PHASENumberMetaParameter* gainMetaParameter;

/*!
    @property rateMetaParameter
    @abstract If specified during construction, the metaparameter for controlling rate/pitch will be available here
*/
@property(nonatomic, strong, nullable, readonly) PHASENumberMetaParameter* rateMetaParameter;

/*!
    @property mixer
    @abstract The readonly property that returns the PHASEMixer this stream was created with and assigned to.
*/
@property(nonatomic, strong, readonly) PHASEMixer* mixer;

/*!
    @property format
    @abstract The readonly property that returns the AVAudioFormat that this stream was initialized with.
*/
@property(nonatomic, strong, readonly) AVAudioFormat* format;

/*!
    @method scheduleBuffer
    @abstract Schedule a buffer for playback.
    @param buffer
        The buffer with PCM audio data.
    @discussion
        Schedules the buffer to be played following any previously scheduled buffer(s).
        The buffer format must be same as format specified during player instantiation
*/
- (void)scheduleBuffer:(AVAudioPCMBuffer*)buffer
NS_SWIFT_NAME(scheduleBuffer(buffer:));

/*!
    @method scheduleBuffer:completionCallbackType:completionHandler:
    @abstract Schedule a buffer for playback.
    @discussion
        Schedules the buffer to be played following any previously scheduled buffer(s).
        The buffer format must be same as format specified during player instantiation
    @param buffer
        The buffer with PCM audio data.
    @param completionCallbackType
        Option to specify when the completion handler must be called.
    @param completionHandler
        The completionHandler to be called as per the specified completion callback type
        or when the player is stopped, at which point the buffer can be recycled.
*/
- (void)scheduleBuffer:(AVAudioPCMBuffer*)buffer
  completionCallbackType:(PHASEPushStreamCompletionCallbackCondition)completionCallbackType
       completionHandler:(void (^)(PHASEPushStreamCompletionCallbackCondition callbackType))completionHandler
NS_SWIFT_NAME(scheduleBuffer(buffer:completionCallbackType:completionHandler:));

/*! @method scheduleBuffer:atTime:options:
    @abstract Schedule a buffer for playback at a given time.
    @discussion
        The buffer format must be same as format specified during player instantiation
    @param buffer
        The buffer with PCM audio data.
    @param when
        The time at which to play the buffer.
    @param options
        Options for looping, interrupting other buffers, etc.
*/
- (void)scheduleBuffer:(AVAudioPCMBuffer*)buffer atTime:(nullable AVAudioTime*)when options:(PHASEPushStreamBufferOptions)options
NS_SWIFT_NAME(scheduleBuffer(buffer:time:options:));

/*!
    @method scheduleBuffer:atTime:options:completionCallbackType:completionHandler:
    @abstract Schedule a buffer for playback at a given time.
    @discussion
        The buffer format must be same as format specified during player instantiation
    @param buffer
        The buffer with PCM audio data.
    @param when
        The time at which to play the buffer.
    @param options
        Options for looping, interrupting other buffers, etc.
    @param completionCallbackType
        Option to specify when the completion handler must be called.
    @param completionHandler
        The completionHandler to be called as per the callback type specified or when
        the player is stopped, at which point the buffer can be recycled.
*/
- (void)scheduleBuffer:(AVAudioPCMBuffer*)buffer
                atTime:(nullable AVAudioTime*)when
               options:(PHASEPushStreamBufferOptions)options
completionCallbackType:(PHASEPushStreamCompletionCallbackCondition)completionCallbackType
     completionHandler:(void (^)(PHASEPushStreamCompletionCallbackCondition callbackType))completionHandler
NS_SWIFT_NAME(scheduleBuffer(buffer:time:options:completionCallbackType:completionHandler:));

@end

#pragma mark - PHASEPullStreamNodeDefinition

/*! @typedef PHASEPullStreamRenderBlock
    @abstract Block to supply audio data to PHASEPullStreamNode
    @param isSilence
        The client may use this flag to indicate that the buffer it vends contains only silence.
        The receiver of the buffer can then use the flag as a hint as to whether the buffer needs
        to be processed or not.
        Note that because the flag is only a hint, when setting the silence flag, the originator of
        a buffer must also ensure that it contains silence (zeroes).
    @param timestamp
        The HAL time at which the audio data will be rendered. If there is a sample rate conversion
        or time compression/expansion downstream, the sample time will not be valid.
    @param frameCount
        The number of sample frames of audio data requested.
    @param outputData
        The output data.

        The caller must supply valid buffers in outputData's mBuffers' mData and mDataByteSize.
        mDataByteSize must be consistent with frameCount. This block may provide output in those
        specified buffers, or it may replace the mData pointers with pointers to memory which it
        owns and guarantees will remain valid until the next render cycle.
    @return
        An OSStatus result code. If an error is returned, the audio data should be assumed to be
        invalid.
 */
NS_SWIFT_NAME(PHASEPullStreamRenderHandler)
typedef OSStatus (^PHASEPullStreamRenderBlock)(BOOL *isSilence, const AudioTimeStamp *timestamp, AVAudioFrameCount frameCount, AudioBufferList *outputData);

/****************************************************************************************************/
/*!
    @interface PHASEPullStreamNodeDefinition
    @abstract An object for defining a pull stream sound event node when building a sound event.
 */
OS_EXPORT API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos)
@interface PHASEPullStreamNodeDefinition : PHASEGeneratorNodeDefinition

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method initWithMixerDefinition:format:identifier
    @abstract Create a pull stream node definition
    @param mixerDefinition
        The mixer definition this stream will be assigned to
    @param format
        The AVAudioFormat object that will define the attributes of the audio this node will accept.
        Only Core Audio's standard deinterleaved 32-bit floating-point formats are supported.
    @param identifier
        An optional custom identifier to give to this object
    @return
        A new PHASEPullStreamNodeDefinition object
*/
- (instancetype)initWithMixerDefinition:(PHASEMixerDefinition*)mixerDefinition format:(AVAudioFormat*)format identifier:(NSString*)identifier;

/*!
    @method initWithMixerDefinition:format
    @abstract Create a pull stream node definition
    @param mixerDefinition
        The mixer definition this stream will be assigned to
    @param format
        The AVAudioFormat object that will define the attributes of the audio this node will accept.
        Only Core Audio's standard deinterleaved 32-bit floating-point formats are supported.
    @return
        A new PHASEPullStreamNodeDefinition object
*/
- (instancetype)initWithMixerDefinition:(PHASEMixerDefinition*)mixerDefinition format:(AVAudioFormat*)format NS_DESIGNATED_INITIALIZER;

/*!
    @property format
    @abstract The readonly property that returns the AVAudioFormat that this stream was initialized with
*/
@property(nonatomic, strong, readonly) AVAudioFormat* format;

/*!
    @property normalize
    @abstract Determines whether or not the engine should normalize the stream. The default value is NO.
    @discussion
        In general, clients are advised to normalize the input. Normalization is required to properly calibrate the output level.
        If you set this value to NO, it's advised that you do custom normalization of the audio data prior to passing the buffers to PHASE.
*/
@property(nonatomic) BOOL normalize;

@end

#pragma mark - PHASEPullStreamNode

/****************************************************************************************************/
/*!
    @interface PHASEPullStreamNode
    @abstract An object for addessing an instance of a stream in an executing sound event
 */
OS_EXPORT API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos)
@interface PHASEPullStreamNode : PHASEStreamNode

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @property renderBlock
    @abstract A property to set the render block callback that will render the samplesIW
    @discussion
        The renderBlock must be set before the PHASESoundEvent is prepared or started.  The callback will be called from a high priority realtime thread.
        Your implementation must be performant and not perform any realtime unsafe operations such as lock mutexes or allocate memory.
*/
@property(nonatomic, strong) PHASEPullStreamRenderBlock renderBlock NS_SWIFT_NAME(renderHandler);

@end

NS_ASSUME_NONNULL_END

#endif /* PHASESoundEventNodes_h */
