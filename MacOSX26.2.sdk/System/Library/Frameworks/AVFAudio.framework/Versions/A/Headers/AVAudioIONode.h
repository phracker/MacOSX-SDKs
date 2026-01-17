/*
	File:		AVAudioIONode.h
	Framework:	AVFoundation
	
	Copyright (c) 2014-2015 Apple Inc. All Rights Reserved.
*/

#import <AVFAudio/AVAudioNode.h>
#import <AVFAudio/AVAudioMixing.h>
#if __has_include(<AudioToolbox/AudioUnit.h>)
#define AVAUDIOIONODE_HAVE_AUDIOUNIT 1
#import <AudioToolbox/AudioUnit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

/*! @typedef AVAudioIONodeInputBlock
    @abstract 
		A block which will be called by AVAudioEngine's render call when operating in the manual 
		rendering mode, to get input data as needed.
	@param inNumberOfFrames
		The number of frames required to complete the request. You may supply either these many 
		frames or none.
	@return
		An AudioBufferList containing data to be rendered, or null if no data is available.
		The data in the returned buffer must not be cleared or re-filled until the input block is 
		called again or the rendering has finished.
		The format of the returned buffer must match the format specified when registering the
		block.
	@discussion
		If you are out of data and return null or less than the requested number of frames, this
		data will not be used for rendering. The engine will try to render from other active
		sources in the processing graph, and will inform about the input node's status in the error
		returned from its render call.
 
		Note that when the engine is configured to operate in 
		`AVAudioEngineManualRenderingModeRealtime`, this block will be called from a realtime 
		context. Care should be taken not to make any blocking call (e.g. calling libdispatch,
		blocking on a mutex, allocating memory etc.) which may cause an overload at the lower layers.
*/
typedef const AudioBufferList * __nullable (^AVAudioIONodeInputBlock)(AVAudioFrameCount inNumberOfFrames) API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*!
	@enum       AVAudioVoiceProcessingSpeechActivityEvent
	@abstract	Types of speech activity events.
	@constant	AVAudioVoiceProcessingSpeechActivityStarted
				Speech activity has started.
	@constant	AVAudioVoiceProcessingSpeechActivityEnded
				Speech activity has ended.
*/
typedef NS_ENUM(NSInteger, AVAudioVoiceProcessingSpeechActivityEvent)
{
	AVAudioVoiceProcessingSpeechActivityStarted = 0,
	AVAudioVoiceProcessingSpeechActivityEnded = 1
} API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
	@enum	AVAudioVoiceProcessingOtherAudioDuckingLevel
	@abstract Ducking level applied to other (i.e. non-voice) audio by AVAudio voice processing AU.
	@discussion
			DuckingLevelDefault = Default ducking level to other audio for typical voice chat.
			DuckingLevelMin = minimum ducking to other audio.
			DuckingLevelMid = medium ducking to other audio.
			DuckingLevelMax = maximum ducking to other audio.
*/
typedef NS_ENUM(NSInteger, AVAudioVoiceProcessingOtherAudioDuckingLevel) {
	AVAudioVoiceProcessingOtherAudioDuckingLevelDefault = 0,
	AVAudioVoiceProcessingOtherAudioDuckingLevelMin = 10,
	AVAudioVoiceProcessingOtherAudioDuckingLevelMid = 20,
	AVAudioVoiceProcessingOtherAudioDuckingLevelMax = 30
} API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_NAME(AVAudioVoiceProcessingOtherAudioDuckingConfiguration.Level);

/*!
	@struct          AVAudioVoiceProcessingOtherAudioDuckingConfiguration
	@abstract        The configuration of ducking other (i.e. non-voice) audio

	@var             enableAdvancedDucking
						 Enables advanced ducking which ducks other audio based on the presence of voice activity from local and/or remote chat participants.
	@var             duckingLevel
						 Ducking level of other audio
*/
NS_SWIFT_SENDABLE
typedef struct API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(tvos, watchos) AVAudioVoiceProcessingOtherAudioDuckingConfiguration {
	BOOL enableAdvancedDucking;
	AVAudioVoiceProcessingOtherAudioDuckingLevel duckingLevel;
} AVAudioVoiceProcessingOtherAudioDuckingConfiguration API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(tvos, watchos);

@class CASpatialAudioExperience;

/*!	@class AVAudioIONode
	@abstract 
		Base class for a node that performs audio input or output in the engine.
	@discussion
		When the engine is configured to render to/from an audio device, on macOS, AVAudioInputNode 
		and AVAudioOutputNode communicate with the system's default input and output devices. 
		On iOS, they communicate with the devices appropriate to the app's AVAudioSession category 
		and other configuration, also considering the user's actions such as 
		connecting/disconnecting external devices.
 
		In the manual rendering mode, the AVAudioInputNode and AVAudioOutputNode perform the input
		and output in the engine, in response to client's request.
*/
API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
@interface AVAudioIONode : AVAudioNode

/*!	@property presentationLatency
	@abstract 
		The presentation or hardware latency, applicable when the engine is rendering to/from an
		audio device.
	@discussion
		This corresponds to kAudioDevicePropertyLatency and kAudioStreamPropertyLatency.
		See <CoreAudio/AudioHardwareBase.h>.
*/
@property (nonatomic, readonly) NSTimeInterval presentationLatency;

#if AVAUDIOIONODE_HAVE_AUDIOUNIT
/*!	@property audioUnit
	@abstract 
		The node's underlying AudioUnit, if any.
	@discussion
		This is only necessary for certain advanced usages.
*/
@property (nonatomic, readonly, nullable) AudioUnit audioUnit;
#endif

/*! @property voiceProcessingEnabled
    @abstract
        Indicates whether voice processing is enabled.
*/
@property (nonatomic, readonly, getter=isVoiceProcessingEnabled) BOOL voiceProcessingEnabled API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/*! @method setVoiceProcessingEnabled:error:
    @abstract
        Enable or disable voice processing on the IO node.
	@param enabled
		Whether voice processing is to be enabled.
    @param outError
        On exit, if the IO node cannot enable or diable voice processing, a description of the error
    @return
        YES for success
    @discussion
        If enabled, the input node does signal processing on the incoming audio (taking out any
        of the audio that is played from the device at a given time from the incoming audio).
        Disabling this mode on either of the IO nodes automatically disabled it on the other IO node.

        Voice processing requires both input and output nodes to be in the voice processing mode.
        Enabling this mode on either of the IO nodes automatically enables it on the other IO node.
        Voice processing is only supported when the engine is rendering to the audio device and not
        in the manual rendering mode.
        Voice processing can only be be enabled or disabled when the engine is in a stopped state.

        The output format of the input node and the input format of the output node have to be
        the same and they can only be changed when the engine is in a stopped state.
 */
- (BOOL)setVoiceProcessingEnabled:(BOOL)enabled error:(NSError **)outError API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

@end


/*! @class AVAudioInputNode
	@abstract 
		A node that performs audio input in the engine.
	@discussion
 		When the engine is rendering to/from an audio device, this node connects to the system's 
		audio input.
		When the engine is operating in manual rendering mode, this node can be used to supply
		the input data to the engine.
 
		This node has one element.
		The format of the input scope reflects:
			- the audio hardware sample rate and channel count, when connected to the hardware
			- the format of the PCM audio data that the node will supply to the engine, in the
			  manual rendering mode (see `setManualRenderingInputPCMFormat:inputBlock:`)
 
		When rendering from an audio device, the input node does not support format conversion.
		Hence the format of the output scope must be same as that of the input, as well as the
		formats for all the nodes connected in the input node chain.
 
		In the manual rendering mode, the format of the output scope is initially the same as that
		of the input, but you may set it to a different format, in which case the node will convert.
*/
API_AVAILABLE(macos(10.10), ios(8.0), watchos(4.0), tvos(11.0))
@interface AVAudioInputNode : AVAudioIONode <AVAudioMixing>
- (instancetype)init NS_UNAVAILABLE; // fetch instance via -[AVAudioEngine inputNode].

/*!	@method setManualRenderingInputPCMFormat:inputBlock:
	@abstract
		Supply the data through the input node to the engine operating in the manual rendering mode.
	@param format
		The format of the PCM audio data the block will supply to the engine
	@param block
		The block the engine will call on the input node to get the audio to send to the output,
		when operating in the manual rendering mode. See `AVAudioIONodeInputBlock` for more details
	@return
		YES for success
	@discussion
 		This block must be set if the input node is being used when the engine is operating in 
		manual rendering mode.
		Switching the engine to render to/from an audio device invalidates any previously set block, 
		and makes this method ineffective.
*/
- (BOOL)setManualRenderingInputPCMFormat:(AVAudioFormat *)format inputBlock:(AVAudioIONodeInputBlock)block API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*! @property voiceProcessingBypassed
    @abstract
       Bypass all processing for microphone uplink done by the voice processing unit.
    @discussion
       Querying this property when voice processing is disabled will return false.
 */
@property (nonatomic, getter=isVoiceProcessingBypassed) BOOL voiceProcessingBypassed API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/*! @property voiceProcessingAGCEnabled
    @abstract
        Enable automatic gain control on the processed microphone uplink.
        signal. Enabled by default.
    @discussion
        Querying this property when voice processing is disabled will return false.
 */
@property (nonatomic, getter=isVoiceProcessingAGCEnabled) BOOL voiceProcessingAGCEnabled API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/*! @property voiceProcessingInputMuted
    @abstract
        Mutes the input of the voice processing unit.
    @discussion
        Querying this property when voice processing is disabled will return false.
*/
@property (nonatomic, getter=isVoiceProcessingInputMuted) BOOL voiceProcessingInputMuted API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/*! @method setMutedSpeechActivityEventListener
	@abstract
		Register a listener to be notified when speech activity event occurs while the input is muted.
	@param listenerBlock
		The block the engine will call when speech activity event occurs while the input is muted.
		Passing nil will remove an already set block.
	@return
		YES for success
	@discussion
		Continuous presence of or lack of speech activity during mute will not cause redundant notification.
		In order to use this API, it's expected to implement the mute via the voiceProcessingInputMuted.
*/
- (BOOL)setMutedSpeechActivityEventListener:(nullable void (^)(AVAudioVoiceProcessingSpeechActivityEvent event))listenerBlock API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*! @property voiceProcessingOtherAudioDuckingConfiguration
	@abstract
		The configuration of ducking other (i.e. non-voice) audio
	@discussion
		Configures the ducking of other (i.e. non-voice) audio, including advanced ducking enablement and ducking level.
		In general, when other audio is played during voice chat, applying a higher level of ducking could increase the intelligibility of the voice chat.
		If not set, the default ducking configuration is to disable advanced ducking, with a ducking level set to AVAudioVoiceProcessingOtherAudioDuckingLevelDefault.
*/
@property (nonatomic) AVAudioVoiceProcessingOtherAudioDuckingConfiguration voiceProcessingOtherAudioDuckingConfiguration API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(watchos, tvos);

@end

/*! @class AVAudioOutputNode
	@abstract 
		A node that performs audio output in the engine.
	@discussion
		When the engine is rendering to/from an audio device, this node connects to the system's 
		audio output.
		When the engine is operating in manual rendering mode, this node performs output in
		response to client's requests.
 
		This node has one element.
		The format of the output scope reflects:
			- the audio hardware sample rate and channel count, when connected to the hardware
			- the engine's manual rendering mode output format (see 
			  `AVAudioEngine(manualRenderingFormat)`), in the manual rendering mode
 
		The format of the input scope is initially the same as that of the
		output, but you may set it to a different format, in which case the node will convert.
*/
API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
@interface AVAudioOutputNode : AVAudioIONode
- (instancetype)init NS_UNAVAILABLE; // fetch instance via -[AVAudioEngine outputNode].

/*! @property intendedSpatialExperience
    @abstract
        The AVAudioOutputNode's intended `CASpatialAudioExperience`
    @discussion
        Not applicable to AVAudioEngine instances configured in manual rendering
        mode. If unspecified, the property value defaults to `CAAutomaticSpatialAudio`
 */
@property (nonnull, copy) CASpatialAudioExperience *intendedSpatialExperience API_AVAILABLE(visionos(26.0)) API_UNAVAILABLE(ios, watchos, tvos, macos) NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
