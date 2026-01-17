#if (defined(USE_AVFAUDIO_PUBLIC_HEADERS) && USE_AVFAUDIO_PUBLIC_HEADERS) || !__has_include(<AudioSession/AVAudioSession.h>)
/*!
	@file		AVAudioSession.h
	@framework	AudioSession.framework
	@copyright	(c) 2009-2024 Apple Inc. All rights reserved.
*/

#ifndef AudioSession_AVAudioSession_h
#define AudioSession_AVAudioSession_h

#import <os/availability.h>
// Note: historically, declarations in AVAudioSessionRoute.h and AVAudioSessionTypes.h were
// declared in AVAudioSession.h. They must be imported here to preserve backwards compatibility.
#import <AVFAudio/AVAudioSessionRoute.h>
#import <AVFAudio/AVAudioSessionTypes.h>
#import <CoreAudioTypes/AudioSessionTypes.h>

NS_ASSUME_NONNULL_BEGIN

// Forward declarations
@class NSError, NSString, NSNumber;
@class AVAudioChannelLayout;

// =================================================================================================
#pragma mark-- iOS/tvOS/watchOS AVAudioSession interface --

NS_SWIFT_SENDABLE
API_AVAILABLE(ios(3.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos) 
@interface AVAudioSession : NSObject {
@private
	void *_impl;
}

/// Return singleton instance.
+ (AVAudioSession *)sharedInstance API_AVAILABLE(ios(3.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Get the list of categories available on the device.  Certain categories may be unavailable on
/// particular devices.  For example, AVAudioSessionCategoryRecord will not be available on devices
/// that have no support for audio input.
@property (readonly, nonatomic) NSArray<AVAudioSessionCategory> *availableCategories API_AVAILABLE(ios(9.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Set session category.
- (BOOL)setCategory:(AVAudioSessionCategory)category error:(NSError **)outError API_AVAILABLE(ios(3.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);
/// Set session category with options.
- (BOOL)setCategory:(AVAudioSessionCategory)category
		withOptions:(AVAudioSessionCategoryOptions)options
			  error:(NSError **)outError
	API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);
/// Set session category and mode with options.
- (BOOL)setCategory:(AVAudioSessionCategory)category
			   mode:(AVAudioSessionMode)mode
			options:(AVAudioSessionCategoryOptions)options
			  error:(NSError **)outError
	API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
	@brief	Set session category, mode, routing sharing policy, and options.

	Use of the long-form route sharing policy is only valid in conjunction with a limited set of
	category, mode, and option values.

	Allowed categories: AVAudioSessionCategoryPlayback.

	Allowed modes: AVAudioSessionModeDefault, AVAudioSessionModeMoviePlayback,
	AVAudioSessionModeSpokenAudio.

	Allowed options: None. Options are allowed when changing the routing policy back to Default,
	however.
*/
- (BOOL)setCategory:(AVAudioSessionCategory)category
				  mode:(AVAudioSessionMode)mode
	routeSharingPolicy:(AVAudioSessionRouteSharingPolicy)policy
			   options:(AVAudioSessionCategoryOptions)options
				 error:(NSError **)outError API_AVAILABLE(ios(11.0), tvos(11.0), watchos(5.0)) API_UNAVAILABLE(macos);

/// Get session category.
/// Examples: AVAudioSessionCategoryRecord, AVAudioSessionCategoryPlayAndRecord, etc.
@property (readonly) AVAudioSessionCategory category API_AVAILABLE(ios(3.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Get the current set of AVAudioSessionCategoryOptions.
@property (readonly) AVAudioSessionCategoryOptions categoryOptions API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*!
	@brief	Get the route sharing policy.

	See AVAudioSessionRouteSharingPolicy for a description of the available policies.
	See setCategory:mode:routeSharingPolicy:options:error: for additional discussion.
*/
@property (readonly) AVAudioSessionRouteSharingPolicy routeSharingPolicy API_AVAILABLE(ios(11.0), tvos(11.0), watchos(5.0)) API_UNAVAILABLE(macos);

/// Get the list of modes available on the device.  Certain modes may be unavailable on particular
/// devices.  For example, AVAudioSessionModeVideoRecording will not be available on devices that
/// have no support for recording video.
@property (readonly) NSArray<AVAudioSessionMode> *availableModes API_AVAILABLE(ios(9.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*!
	@brief	Set the session's mode.

	Modes modify the audio category in order to introduce behavior that is tailored to the specific
	use of audio within an application. Examples:  AVAudioSessionModeVideoRecording,
	AVAudioSessionModeVoiceChat, AVAudioSessionModeMeasurement, etc.
*/
- (BOOL)setMode:(AVAudioSessionMode)mode
		  error:(NSError **)outError
	API_AVAILABLE(ios(5.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Get the session's mode.
@property (readonly)
	AVAudioSessionMode mode API_AVAILABLE(ios(5.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Set allowHapticsAndSystemSoundsDuringRecording to YES in order to allow system sounds and haptics to play while the session is actively using audio input.
/// Default value is NO.
- (BOOL)setAllowHapticsAndSystemSoundsDuringRecording:(BOOL)inValue error:(NSError **)outError API_AVAILABLE(ios(13.0), watchos(6.0), tvos(13.0)) API_UNAVAILABLE(macos);

/// Whether system sounds and haptics can play while the session is actively using audio input.
@property(readonly) BOOL allowHapticsAndSystemSoundsDuringRecording API_AVAILABLE(ios(13.0), watchos(6.0), tvos(13.0)) API_UNAVAILABLE(macos);

/// Returns an enum indicating whether the user has granted or denied permission to record, or has
/// not been asked
@property (readonly) AVAudioSessionRecordPermission recordPermission API_DEPRECATED("Please use AVAudioApplication recordPermission", ios(8.0, 17.0), watchos(4.0, 10.0)) API_UNAVAILABLE(macos, tvos);

/*!
 	@brief Checks to see if calling process has permission to record audio.
 
	The 'response' block will be called immediately if permission has already been granted or
	denied.  Otherwise, it presents a dialog to notify the user and allow them to choose, and calls
	the block once the UI has been dismissed.  'granted' indicates whether permission has been
	granted. Note that the block may be called in a different thread context.
*/
- (void)requestRecordPermission:(void (^)(BOOL granted))response API_DEPRECATED("Please use AVAudioApplication requestRecordPermissionWithCompletionHandler", ios(7.0, 17.0), watchos(4.0, 10.0)) API_UNAVAILABLE(macos, tvos);

/*!
    @brief Use this method to temporarily override the output to built-in speaker.
 
    This method is only valid for a session using PlayAndRecord category. This change remains in
    effect only until the current route changes or you call this method again with the
    AVAudioSessionPortOverrideNone option. Sessions using PlayAndRecord category that always want to
    prefer the built-in speaker output over the receiver, should use
    AVAudioSessionCategoryOptionDefaultToSpeaker instead.
*/
- (BOOL)overrideOutputAudioPort:(AVAudioSessionPortOverride)portOverride
						  error:(NSError **)outError
	API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);


/*!
    @brief Select a preferred input port for audio routing.
 
    If the input port is already part of the current audio route, this will have no effect.
    Otherwise, selecting an input port for routing will initiate a route change to use the preferred
    input port. Setting a nil value will clear the preference.
*/
- (BOOL)setPreferredInput:(nullable AVAudioSessionPortDescription *)inPort
					error:(NSError **)outError API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/// Get the preferred input port.  Will be nil if no preference has been set.
@property (readonly, nullable) AVAudioSessionPortDescription *preferredInput API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/*!
    @brief Set ringtone and alert interruption preference.
 
    Inform the system when the session prefers to not be interrupted by
    ringtones and alerts. By setting this property to YES, clients will not be interrupted
    by incoming call notifications and other alerts. Starting in iOS 14.0, users can set a global
    preference for incoming call display style to "Banner" or "Full Screen". With "Banner" display style,
    if below property is set to YES then system audio will be silenced. Thus, clients will not be interrupted
    on incoming call notification and user will have opportunity to accept or decline the call. If call is declined,
    the session will not be interrupted, but if user accepts the incoming call, the session will be interrupted.
    With  display style set as "Full Screen", below property will have no effect and clients will be
    interrupted by incoming calls. Apps that record audio and/or video and apps that are used for
    music performance are candidates for using this feature.
 */
- (BOOL)setPrefersNoInterruptionsFromSystemAlerts:(BOOL)inValue error:(NSError**)outError API_AVAILABLE(ios(14.5), watchos(7.3), tvos(14.5)) API_UNAVAILABLE(macos);
@property (readonly, nonatomic) BOOL prefersNoInterruptionsFromSystemAlerts API_AVAILABLE(ios(14.5), watchos(7.3), tvos(14.5)) API_UNAVAILABLE(macos);

/// Get the currently resolved rendering mode to badge content appropriately.
/// Clients should use this property to determine what to badge content as.
@property(readonly) AVAudioSessionRenderingMode renderingMode API_AVAILABLE(ios(17.2), tvos(17.2)) API_UNAVAILABLE(watchos, macos, visionos);

/*!
 @brief Set a preference to enable echo cancelled input on supported hardware

Applications might want to record the built-in microphone's input while also playing audio out via the built-in speaker.
Enabling echo cancelled input is useful when the application needs the input signal to be clear of any echoes
from the audio playing out of the built-in speaker.

Audio sessions using Voice Processor don't need this option as echo cancellation is implicitly applied for those routes.
The Voice Processor solution is tuned for voice signals, unlike this option, which is tuned for better capture
of wider range of audio signals in the presence of built-in speaker echo.

This option is only available on certain 2024 or later iPhone models and is valid only when used with the following configurations:
 - AVAudioSessionCategoryPlayAndRecord and AVAudioSessionModeDefault
 - AVAudioSessionCategoryMultiRoute and AVAudioSessionModeDualRoute
Support can be queried using property `isEchoCancelledInputAvailable`.
Other recording sessions might be interrupted if this option is not compatible with sessions that are already recording.

After an audio session goes active, `isEchoCancelledInputEnabled` property can be queried to check if the option was honored.
Note that the enabled state may change after route changes, e.g. if user plugs in a headset, that route might not support echo cancellation.
*/
- (BOOL)setPrefersEchoCancelledInput:(BOOL)value error:(NSError **)error API_AVAILABLE(ios(18.2)) API_UNAVAILABLE(tvos, watchos, macos, visionos);
@property (readonly, nonatomic) BOOL prefersEchoCancelledInput API_AVAILABLE(ios(18.2)) API_UNAVAILABLE(tvos, watchos, macos, visionos);

/// Returns YES if echo cancelled input is successfully enabled on an active session.
/// Please see `prefersEchoCancelledInput` above for more details.
@property (readonly, nonatomic) BOOL isEchoCancelledInputEnabled API_AVAILABLE(ios(18.2)) API_UNAVAILABLE(tvos, watchos, macos, visionos);

/// This property will return YES if the device supports echo cancellation with the following category and mode combinations:
///	- ``AVAudioSessionCategoryPlayAndRecord`` with ``AVAudioSessionModeDefault``
///	- ``AVAudioSessionCategoryMultiRoute`` with ``AVAudioSessionModeDualRoute``
///
/// Query whether built-in mic / built-in speaker route supports echo cancellation for the session's given category and mode.
@property(readonly, nonatomic) BOOL isEchoCancelledInputAvailable API_AVAILABLE(ios(18.2)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(macos);

/// Sets a Boolean value to inform the system to mute the session's output audio. The default value is false (unmuted).
///
/// This property is supported with all categories and modes, except for
/// ``AVAudioSessionCategoryPlayAndRecord`` where it is only supported with ``AVAudioSessionModeDefault``.
/// Changing the mode to non-default mode with ``AVAudioSessionCategoryPlayAndRecord``
/// category will cause the session to unmute.
///
/// Changes in output mute state can be observed via ``AVAudioSessionOutputMuteStateChangeNotification``.
/// If this value is set to true, ``AVAudioSessionUserIntentToUnmuteOutputNotification``
/// may be sent when a user hints to unmute by changing the volume.
///
/// - Note: This will not mute system sounds and haptics.
///
/// - Parameters:
/// - `muted`: A Boolean value to set the audio output to the desired muted state.
/// - `error`: A pointer to an error object. If an error occurs, the framework sets the pointer to an error object that describes the failure.
- (BOOL)setOutputMuted:(BOOL)muted error:(NSError **)outError API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, tvos, visionos, macos);
/// A Boolean value that indicates whether audio output is in a muted state.
@property(readonly, getter=isOutputMuted) BOOL outputMuted API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, tvos, visionos, macos);

@end

// -------------------------------------------------------------------------------------------------
#pragma mark-- activation and deactivation --
// -------------------------------------------------------------------------------------------------
@interface AVAudioSession (Activation)

/*!
    @brief  Set the session active or inactive.
 
	Note that activating an audio session is a synchronous (blocking) operation.
	Therefore, we recommend that applications not activate their session from a thread where a long
	blocking operation will be problematic.
	Apps may activate a AVAudioSessionCategoryPlayback session when another app is hosting a
	call (to start a SharePlay activity for example). However, they are not permitted to capture the
    microphone of the active call, so attempts to activate a session with category
	AVAudioSessionCategoryRecord or AVAudioSessionCategoryPlayAndRecord will fail with error
	AVAudioSessionErrorCodeInsufficientPriority.
	When deactivating a session, the caller is required to
	first stop or pause all running I/Os (e.g. audio queues, players, recorders, converters,
	remote I/Os, etc.). Starting in iOS 8, if the session has running I/Os at the time that
	deactivation is requested, the session will be deactivated, but the method will return NO and
	populate the NSError with the code property set to AVAudioSessionErrorCodeIsBusy to indicate the
	misuse of the API. Prior to iOS 8, the session would have remained active if it had running I/Os
	at the time of the deactivation request. Starting in iOS 26.0, deactivating while IO is running will
	no longer return AVAudioSessionErrorCodeIsBusy.
*/
- (BOOL)setActive:(BOOL)active error:(NSError **)outError API_AVAILABLE(ios(3.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);
- (BOOL)setActive:(BOOL)active withOptions:(AVAudioSessionSetActiveOptions)options error:(NSError **)outError API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*!
    @brief Asynchronously activate the session.
 
	This is a relatively time consuming operation. The completion handler will be called when the
	activation completes or if an error occurs while attempting to activate the session. If the
	session is configured to use AVAudioSessionRouteSharingPolicyLongFormAudio on watchOS, this
	method will also cause a route picker to be presented to the user in cases where an appropriate
	output route has not already been selected automatically. watchOS apps using
	AVAudioSessionRouteSharingPolicyLongFormAudio should be prepared for this method to fail if no
	eligible audio route can be activated or if the user cancels the route picker view.
*/
- (void)activateWithOptions:(AVAudioSessionActivationOptions)options completionHandler:(void (^)(BOOL activated, NSError * _Nullable error))handler API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios, tvos) API_UNAVAILABLE(macos, macCatalyst);

@end // AVAudioSession(Activation)

/*!
    @brief this category deals with the set of properties that reflect the current state of
	audio hardware in the current route.  Applications whose functionality depends on these
	properties should reevaluate them any time the route changes.
*/
@interface AVAudioSession (AVAudioSessionHardwareConfiguration)

/*! Get and set preferred values for hardware properties.  Note: that there are corresponding read-only
 properties that describe the actual values for sample rate, I/O buffer duration, etc.
*/

/// The preferred hardware sample rate for the session. The actual sample rate may be different.
- (BOOL)setPreferredSampleRate:(double)sampleRate error:(NSError **)outError API_AVAILABLE(ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);
@property (readonly) double preferredSampleRate API_AVAILABLE(ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/// The preferred hardware IO buffer duration in seconds. The actual IO buffer duration may be
/// different.
- (BOOL)setPreferredIOBufferDuration:(NSTimeInterval)duration error:(NSError **)outError API_AVAILABLE(ios(3.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);
@property (readonly) NSTimeInterval preferredIOBufferDuration API_AVAILABLE(ios(3.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/// Sets the number of input channels that the app would prefer for the current route
- (BOOL)setPreferredInputNumberOfChannels:(NSInteger)count error:(NSError **)outError API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);
@property (readonly) NSInteger preferredInputNumberOfChannels API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/// Sets the number of output channels that the app would prefer for the current route
- (BOOL)setPreferredOutputNumberOfChannels:(NSInteger)count error:(NSError **)outError API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);
@property (readonly) NSInteger preferredOutputNumberOfChannels API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/*! Sets the preferred input orientation.
 The input orientation determines which directions will be left and right
 when a built-in mic data source with the AVAudioSessionPolarPatternStereo polar pattern is selected.
 Typically, this orientation should match how the user is holding the device while recording, which will match
 the application's interface orientation when a single app is on the screen.
 The actual input orientation may be different, for example, if another app's session is in control of routing.
 The input orientation is independent of the orientation property of an AVAudioSessionDataSourceDescription. */
- (BOOL)setPreferredInputOrientation:(AVAudioStereoOrientation)orientation error:(NSError **)outError API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos, macos);
@property (readonly) AVAudioStereoOrientation preferredInputOrientation API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos, macos);

/// Describes the orientation of the input data source (valid for the built-in mic input data source when a stereo polar pattern is selected).
@property (readonly) AVAudioStereoOrientation inputOrientation API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos, macos);

/// Returns the largest number of audio input channels available for the current route
@property (readonly) NSInteger maximumInputNumberOfChannels API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Returns the largest number of audio output channels available for the current route
@property (readonly) NSInteger maximumOutputNumberOfChannels API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*!
	@brief A value defined over the range [0.0, 1.0], with 0.0 corresponding to the lowest analog
	gain setting and 1.0 corresponding to the highest analog gain setting.

	Attempting to set values outside of the defined range will result in the value being "clamped"
	to a valid input.  This is a global input gain setting that applies to the current input source
	for the entire system. When no applications are using the input gain control, the system will
	restore the default input gain setting for the input source.  Note that some audio accessories,
	such as USB devices, may not have a default value.  This property is only valid if
	inputGainSettable is true.  Note: inputGain is key-value observable.
*/
- (BOOL)setInputGain:(float)gain error:(NSError **)outError API_AVAILABLE(ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);
/// value in range [0.0, 1.0]
@property (readonly) float inputGain API_AVAILABLE(ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/// True when audio input gain is available.  Some input ports may not provide the ability to set the
/// input gain, so check this value before attempting to set input gain.
@property (readonly, getter=isInputGainSettable) BOOL inputGainSettable API_AVAILABLE(ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/// True if input hardware is available. Key-value observable.
@property (readonly, getter=isInputAvailable) BOOL inputAvailable API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*!
	@brief DataSource methods are for use with routes that support input or output data source
	selection.
 
	If the attached accessory supports data source selection, the data source properties/methods
	provide for discovery and selection of input and/or output data sources. Note that the
	properties and methods for data source selection below are equivalent to the properties and
	methods on AVAudioSessionPortDescription. The methods below only apply to the currently routed
	ports.
	
	Key-value observable.
*/
@property (readonly, nullable) NSArray<AVAudioSessionDataSourceDescription *> *inputDataSources API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Obtain the currently selected input data source.  Will be nil if no data sources are available.
@property (readonly, nullable) AVAudioSessionDataSourceDescription *inputDataSource API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Select a new input data source. Setting a nil value will clear the data source preference.
- (BOOL)setInputDataSource:(nullable AVAudioSessionDataSourceDescription *)dataSource error:(NSError **)outError API_AVAILABLE(ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/// See inputDataSources for background. Key-value observable.
@property (readonly, nullable) NSArray<AVAudioSessionDataSourceDescription *> *outputDataSources API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Obtain the currently selected output data source.  Will be nil if no data sources are available.
@property (readonly, nullable) AVAudioSessionDataSourceDescription *outputDataSource API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Select a new output data source. Setting a nil value will clear the data source preference.
- (BOOL)setOutputDataSource:(nullable AVAudioSessionDataSourceDescription *)dataSource error:(NSError **)outError API_AVAILABLE(ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/*!
	@brief Current values for hardware properties.
 
	Note that most of these properties have corresponding methods for getting and setting preferred
	values.  Input- and output-specific properties will generate an error if they are queried if the
	audio session category does not support them.  Each of these will return 0 (or 0.0) if there is
	an error.
*/

/// The current hardware sample rate. Is key-value observable (starting iOS 18.0).
@property (readonly) double sampleRate API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// The current number of hardware input channels. Is key-value observable.
@property (readonly) NSInteger inputNumberOfChannels API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// The current number of hardware output channels. Is key-value observable.
@property (readonly) NSInteger outputNumberOfChannels API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// The current hardware input latency in seconds.
@property (readonly) NSTimeInterval inputLatency API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// The current hardware output latency in seconds.
@property (readonly) NSTimeInterval outputLatency API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// The current hardware IO buffer duration in seconds. Is key-value observable.
@property (readonly) NSTimeInterval IOBufferDuration API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Get an array of channel layouts that the current route supports.
/// This property is only supported when the output is routed to ports of type AVAudioSessionPortCarAudio or AVAudioSessionPortAirPlay
/// Otherwise, an empty array will be returned. Note that this will return an empty array if session is inactive.
/// Clients should listen to AVAudioSessionRenderingCapabilitiesChangeNotification to be notified when this changes.
@property(readonly) NSArray<AVAudioChannelLayout*>* supportedOutputChannelLayouts API_AVAILABLE(ios(17.2), tvos(17.2)) API_UNAVAILABLE(watchos, macos, visionos);

@end


// -------------------------------------------------------------------------------------------------
#pragma mark-- observation --
// -------------------------------------------------------------------------------------------------
@interface AVAudioSession (Observation)

/*!
	@brief	True when another application is playing audio.

	Note: As of iOS 8.0, Apple recommends that most applications use
	secondaryAudioShouldBeSilencedHint instead of this property. The otherAudioPlaying property
    will be true if any other audio (including audio from an app using
    AVAudioSessionCategoryAmbient) is playing, whereas the secondaryAudioShouldBeSilencedHint
    property is more restrictive in its consideration of whether primary audio from another
    application is playing.
*/
@property (readonly, getter=isOtherAudioPlaying) BOOL otherAudioPlaying API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*!
	@brief	True when another application with a non-mixable audio session is playing audio.

	Applications may use this property as a hint to silence audio that is secondary to the
	functionality of the application. For example, a game app using AVAudioSessionCategoryAmbient
	may use this property to decide to mute its soundtrack while leaving its sound effects unmuted.
	Note: This property is closely related to AVAudioSessionSilenceSecondaryAudioHintNotification.
*/
@property (readonly) BOOL secondaryAudioShouldBeSilencedHint API_AVAILABLE(ios(8.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// The current output volume. Value in range [0.0, 1.0]. Is key-value observable.
@property (readonly) float outputVolume API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// The prompt style is a hint to sessions using AVAudioSessionModeVoicePrompt to alter the type of
/// prompts they issue in response to other audio activity on the system, such as Siri and phone
/// calls. This property is key-value observable.
@property(readonly) AVAudioSessionPromptStyle promptStyle API_AVAILABLE(ios(13.0), watchos(6.0), tvos(13.0)) API_UNAVAILABLE(macos);

@end // AVAudioSession (Observation)

// -------------------------------------------------------------------------------------------------
#pragma mark-- routing configuration --
// -------------------------------------------------------------------------------------------------
@interface AVAudioSession (RoutingConfiguration)

/*!
	@brief	Get the set of input ports that are available for routing.

	Note that this property only applies to the session's current category and mode. For
    example, if the session's current category is AVAudioSessionCategoryPlayback, there will be
    no available inputs.
 
	On iOS, clients can listen to AVAudioSessionAvailableInputsChangeNotification to
	be notified when this changes.
*/
@property (readonly, nullable) NSArray<AVAudioSessionPortDescription *> *availableInputs API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// A description of the current route, consisting of zero or more input ports and zero or more
/// output ports
@property (readonly) AVAudioSessionRouteDescription *currentRoute
	API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*!
    @brief    Controls whether audio input and output are aggregated. Only valid in combination with
    AVAudioSessionCategoryPlayAndRecord or AVAudioSessionCategoryMultiRoute.
 
    See the AVAudioSessionIOType documentation for a more detailed explanation of why a client may
    want to change the IO type.
*/
- (BOOL)setAggregatedIOPreference:(AVAudioSessionIOType)inIOType
							error:(NSError **)outError API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(tvos, watchos, macos);

/// Set YES to inform the system if the app can supply multichannel audio content.
/// Default value is NO. This property is intended to be used by 'Now Playing' applications.
/// See https://developer.apple.com/documentation/mediaplayer/becoming_a_now_playable_app for more information
/// about what it means to be a 'Now Playing' application. Typically 'Now Playing' applications will also use
/// AVAudioSessionRouteSharingPolicyLongFormAudio or AVAudioSessionRouteSharingPolicyLongFormVideo.
- (BOOL)setSupportsMultichannelContent:(BOOL)inValue error:(NSError **)outError API_AVAILABLE(ios(15.0), watchos(8.0), tvos(15.0)) API_UNAVAILABLE(macos);

@property(readonly) BOOL supportsMultichannelContent API_AVAILABLE(ios(15.0), watchos(8.0), tvos(15.0)) API_UNAVAILABLE(macos);

/*!
    @brief Use this method to opt in or opt out of interruption on route disconnect policy.
 
    As described in the Audio Session Programming Guide, most media playback apps are expected
    to pause playback if the route change reason is AVAudioSessionRouteChangeReasonOldDeviceUnavailable.
 
    Starting in iOS 17, by default Now Playing sessions will be interrupted if they are active
    when a route change occurs because of a disconnect event. All other sessions will not be
    interrupted due to a disconnect event.
*/
- (BOOL) setPrefersInterruptionOnRouteDisconnect:(BOOL)inValue error:(NSError **)outError API_AVAILABLE(ios(17.0), watchos(10.0), tvos(17.0)) API_UNAVAILABLE(macos);

/// Indicates if session will be interrupted on route disconnect.
@property(readonly) BOOL prefersInterruptionOnRouteDisconnect API_AVAILABLE(ios(17.0), watchos(10.0), tvos(17.0)) API_UNAVAILABLE(macos);

@end // interface for AVAudioSession (RoutingConfiguration)

@interface  AVAudioSession (MicrophoneInjection)

/// Set the preferred form of audio injection into another app's input stream
/// See AVAudioSessionMicrophoneInjectionMode for available modes
- (BOOL)setPreferredMicrophoneInjectionMode:(AVAudioSessionMicrophoneInjectionMode)inValue error:(NSError**)outError API_AVAILABLE(ios(18.2), visionos(2.2)) API_UNAVAILABLE(tvos, watchos, macos);
@property(readonly) AVAudioSessionMicrophoneInjectionMode  preferredMicrophoneInjectionMode API_AVAILABLE(ios(18.2), visionos(2.2)) API_UNAVAILABLE(tvos, watchos, macos);

/// Indicates if microphone injection is available.
/// Observe AVAudioSessionMicrophoneInjectionCapabilitiesChangeNotification for changes to this property
@property(readonly) BOOL isMicrophoneInjectionAvailable API_AVAILABLE(ios(18.2), visionos(2.2)) API_UNAVAILABLE(tvos, watchos, macos);

@end

#if TARGET_OS_VISION

@interface AVAudioSession (SpatialPreference)


///Configure the developer's intended spatial experience for this audio session.
- (BOOL)setIntendedSpatialExperience:(AVAudioSessionSpatialExperience)intendedSpatialExperience
                             options:(nullable NSDictionary<AVAudioSessionSpatialExperienceOption, id>*)options
                               error:(NSError**)error NS_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(ios, watchos, tvos, macos);

/// Get the developer's intended spatial experience
@property (readonly, nonatomic) AVAudioSessionSpatialExperience intendedSpatialExperience NS_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(ios, watchos, tvos, macos);

/// Get the developer's intended spatial experience options. May be nil if the
/// experience is NonSpatial.
@property (readonly, nonatomic, nullable) NSDictionary<AVAudioSessionSpatialExperienceOption, id>* intendedSpatialExperienceOptions NS_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(ios, watchos, tvos, macos);

@end // AVAudioSession (SpatialPreference)

@interface AVAudioSession (NowPlayingCandidacy)

/// Get/set whether this session is a now-playing candidate. Now playing
/// candidacy must be exclusive for an audio session to be eligible - that is,
/// if multiple audio sessions from the same application are now-playing
/// candidates, none of them are eligible.
@property(readonly) BOOL isNowPlayingCandidate API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(ios, watchos, tvos, macos);
- (BOOL)setIsNowPlayingCandidate:(BOOL)inValue error:(NSError **)outError API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(ios, watchos, tvos, macos);

@end // AVAudioSession (NowPlayingCandidacy)

#endif // TARGET_OS_VISION

NS_ASSUME_NONNULL_END

// Note: This import comes at the end of the header because it contains content that was
// historically part of AVAudioSession.h and it declares a class category on AVAudioSession.
#import <AVFAudio/AVAudioSessionDeprecated.h>

#endif // AudioSession_AVAudioSession_h
#else
#include <AudioSession/AVAudioSession.h>
#endif
