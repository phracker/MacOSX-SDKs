#if (defined(USE_AVFAUDIO_PUBLIC_HEADERS) && USE_AVFAUDIO_PUBLIC_HEADERS) || !__has_include(<AudioSession/AVAudioSession.h>)
/*!
	@file		AVAudioSession.h
	@framework	AudioSession.framework
	@copyright	(c) 2009-2020 Apple Inc. All rights reserved.
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


// =================================================================================================
#pragma mark-- iOS/tvOS/watchOS AVAudioSession interface --

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
@property (readonly) AVAudioSessionRecordPermission recordPermission API_AVAILABLE(ios(8.0), watchos(4.0)) API_UNAVAILABLE(macos, tvos);


/*!
 	@brief Checks to see if calling process has permission to record audio.
 
	The 'response' block will be called immediately if permission has already been granted or
	denied.  Otherwise, it presents a dialog to notify the user and allow them to choose, and calls
	the block once the UI has been dismissed.  'granted' indicates whether permission has been
	granted. Note that the block may be called in a different thread context.
*/
- (void)requestRecordPermission:(void (^)(BOOL granted))response API_AVAILABLE(ios(7.0), watchos(4.0)) API_UNAVAILABLE(macos, tvos);

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
    if below property is set to YES then clients will not be interrupted on incoming call notification
    and user will have opportunity to accept or decline the call. If call is declined, the session
    will not be interrupted, but if user accepts the incoming call, the session will be interrupted.
    With  display style set as "Full Screen", below property will have no effect and clients will be
    interrupted by incoming calls. Apps that record audio and/or video and apps that are used for
    music performance are candidates for using this feature.
 */
- (BOOL)setPrefersNoInterruptionsFromSystemAlerts:(BOOL)inValue error:(NSError**)outError API_AVAILABLE(ios(14.5), watchos(7.3), tvos(14.5)) API_UNAVAILABLE(macos);
@property (readonly, nonatomic) BOOL prefersNoInterruptionsFromSystemAlerts API_AVAILABLE(ios(14.5), watchos(7.3), tvos(14.5)) API_UNAVAILABLE(macos);

@end

// -------------------------------------------------------------------------------------------------
#pragma mark-- activation and deactivation --
// -------------------------------------------------------------------------------------------------
@interface AVAudioSession (Activation)

/*!
    @brief  Set the session active or inactive.
 
	Note that activating an audio session is a synchronous (blocking) operation.
	Therefore, we recommend that applications not activate their session from a thread where a long
	blocking operation will be problematic. When deactivating a session, the caller is required to
	first stop or pause all running I/Os (e.g. audio queues, players, recorders, converters,
	remote I/Os, etc.). Starting in iOS 8, if the session has running I/Os at the time that
	deactivation is requested, the session will be deactivated, but the method will return NO and
	populate the NSError with the code property set to AVAudioSessionErrorCodeIsBusy to indicate the
	misuse of the API. Prior to iOS 8, the session would have remained active if it had running I/Os
	at the time of the deactivation request.
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

/// True if input hardware is available.
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

/// The current hardware sample rate
@property (readonly) double sampleRate API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// The current number of hardware input channels. Is key-value observable.
@property (readonly) NSInteger inputNumberOfChannels API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// The current number of hardware output channels. Is key-value observable.
@property (readonly) NSInteger outputNumberOfChannels API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// The current hardware input latency in seconds.
@property (readonly) NSTimeInterval inputLatency API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// The current hardware output latency in seconds.
@property (readonly) NSTimeInterval outputLatency API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// The current hardware IO buffer duration in seconds.
@property (readonly) NSTimeInterval IOBufferDuration API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

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

@end // interface for AVAudioSession (RoutingConfiguration)

#pragma mark-- Names for NSNotifications --

/*!
	@brief	Notification sent to registered listeners when the system has interrupted the audio
			session and when the interruption has ended.

    Check the notification's userInfo dictionary for the interruption type, which is either
    Begin or End. In the case of an end interruption notification, check the userInfo dictionary
    for AVAudioSessionInterruptionOptions that indicate whether audio playback should resume.
    In the case of a begin interruption notification, the reason for the interruption can be found
    within the info dictionary under the key AVAudioSessionInterruptionReasonKey.
*/
OS_EXPORT NSNotificationName const  AVAudioSessionInterruptionNotification API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0));

/*!
	@brief	Notification sent to registered listeners when an audio route change has occurred.

	Check the notification's userInfo dictionary for the route change reason and for a description
	of the previous audio route.
*/
OS_EXPORT NSNotificationName const  AVAudioSessionRouteChangeNotification API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0));

/*!
	@brief	Notification sent to registered listeners if the media server is killed.

	In the event that the server is killed, take appropriate steps to handle requests that come in
	before the server resets.  See Technical Q&A QA1749.
*/
OS_EXPORT NSNotificationName const  AVAudioSessionMediaServicesWereLostNotification API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0));

/*!
	@brief	Notification sent to registered listeners when the media server restarts.

	In the event that the server restarts, take appropriate steps to re-initialize any audio objects
	used by your application.  See Technical Q&A QA1749.
*/
OS_EXPORT NSNotificationName const  AVAudioSessionMediaServicesWereResetNotification API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0));

/*!
	@brief	Notification sent to registered listeners when they are in the foreground with an active
		audio session and primary audio from other applications starts and stops.

	Check the notification's userInfo dictionary for the notification type, which is either Begin or
	End. Foreground applications may use this notification as a hint to enable or disable audio that
	is secondary to the functionality of the application. For more information, see the related
	property secondaryAudioShouldBeSilencedHint.
*/
OS_EXPORT NSNotificationName const  AVAudioSessionSilenceSecondaryAudioHintNotification API_AVAILABLE(ios(8.0), watchos(2.0), tvos(9.0));


#pragma mark-- Keys for NSNotification userInfo dictionaries --

/// keys for AVAudioSessionInterruptionNotification
/// Value is an NSNumber representing an AVAudioSessionInterruptionType
OS_EXPORT NSString *const AVAudioSessionInterruptionTypeKey API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0));

/// Only present for end interruption events.  Value is of type AVAudioSessionInterruptionOptions.
OS_EXPORT NSString *const AVAudioSessionInterruptionOptionKey API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0));

/// Only present in begin interruption events. Value is of type AVAudioSessionInterruptionReason.
OS_EXPORT NSString *const AVAudioSessionInterruptionReasonKey API_AVAILABLE(ios(14.5), watchos(7.3)) API_UNAVAILABLE(tvos, macos);

/*!
	Only present in begin interruption events, where the interruption is a direct result of the
	application being suspended by the operating sytem. Value is a boolean NSNumber, where a true
	value indicates that the interruption is the result of the application being suspended, rather
	than being interrupted by another audio session.

	Starting in iOS 10, the system will deactivate the audio session of most apps in response to the
	app process being suspended. When the app starts running again, it will receive the notification
	that its session has been deactivated by the system. Note that the notification is necessarily
	delayed in time, due to the fact that the application was suspended at the time the session was
	deactivated by the system and the notification can only be delivered once the app is running
	again.
*/
OS_EXPORT NSString *const AVAudioSessionInterruptionWasSuspendedKey API_DEPRECATED("No longer supported - see AVAudioSessionInterruptionReasonKey", ios(10.3, 14.5), watchos(3.2, 7.3), tvos(10.3, 14.5));

/// keys for AVAudioSessionRouteChangeNotification
/// value is an NSNumber representing an AVAudioSessionRouteChangeReason
OS_EXPORT NSString *const AVAudioSessionRouteChangeReasonKey API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0));
/// value is AVAudioSessionRouteDescription *
OS_EXPORT NSString *const AVAudioSessionRouteChangePreviousRouteKey API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0));

/// keys for AVAudioSessionSilenceSecondaryAudioHintNotification
/// value is an NSNumber representing an AVAudioSessionSilenceSecondaryAudioHintType
OS_EXPORT NSString *const AVAudioSessionSilenceSecondaryAudioHintTypeKey API_AVAILABLE(ios(8.0), watchos(2.0), tvos(9.0));

NS_ASSUME_NONNULL_END

// Note: This import comes at the end of the header because it contains content that was
// historically part of AVAudioSession.h and it declares a class category on AVAudioSession.
#import <AVFAudio/AVAudioSessionDeprecated.h>

#endif // AudioSession_AVAudioSession_h
#else
#include <AudioSession/AVAudioSession.h>
#endif
