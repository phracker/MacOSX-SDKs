#if (defined(USE_AVFAUDIO_PUBLIC_HEADERS) && USE_AVFAUDIO_PUBLIC_HEADERS) || !__has_include(<AudioSession/AVAudioSessionTypes.h>)
/*!
	@file		AVAudioSessionTypes.h
	@framework	AudioSession.framework
	@copyright	(c) 2009-2024 Apple Inc. All rights reserved.
*/

#ifndef AudioSession_AVAudioSessionTypes_h
#define AudioSession_AVAudioSessionTypes_h

#import <CoreAudioTypes/CoreAudioTypes.h>
#import <Foundation/Foundation.h>
#import <os/base.h>


#pragma mark -- constants for endpoint and port types --

/// A port describes a specific type of audio input or output device or connector.
typedef NSString *AVAudioSessionPort NS_STRING_ENUM;

/* input port types */
/// Continuity microphone for appletv.
OS_EXPORT AVAudioSessionPort const AVAudioSessionPortContinuityMicrophone API_AVAILABLE(ios(17.0), watchos(10.0), tvos(17.0)) API_UNAVAILABLE(macos);
/// Line level input on a dock connector
OS_EXPORT AVAudioSessionPort const AVAudioSessionPortLineIn      		API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);
/// Built-in microphone on an iOS device
OS_EXPORT AVAudioSessionPort const AVAudioSessionPortBuiltInMic  		API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);
/// Microphone on a wired headset.  Headset refers to an accessory that has headphone outputs paired with a
/// microphone.
OS_EXPORT AVAudioSessionPort const AVAudioSessionPortHeadsetMic		API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* output port types */

/// Line level output on a dock connector
OS_EXPORT AVAudioSessionPort const AVAudioSessionPortLineOut          	API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Headphone or headset output
OS_EXPORT AVAudioSessionPort const AVAudioSessionPortHeadphones       	API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Output on a Bluetooth A2DP device
OS_EXPORT AVAudioSessionPort const AVAudioSessionPortBluetoothA2DP    	API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// The speaker you hold to your ear when on a phone call
OS_EXPORT AVAudioSessionPort const AVAudioSessionPortBuiltInReceiver  	API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Built-in speaker on an iOS device
OS_EXPORT AVAudioSessionPort const AVAudioSessionPortBuiltInSpeaker   	API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Output via High-Definition Multimedia Interface
OS_EXPORT AVAudioSessionPort const AVAudioSessionPortHDMI             	API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Output on a remote Air Play device
OS_EXPORT AVAudioSessionPort const AVAudioSessionPortAirPlay          	API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Output on a Bluetooth Low Energy device
OS_EXPORT AVAudioSessionPort const AVAudioSessionPortBluetoothLE	   	API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* port types that refer to either input or output */

/// Input or output on a Bluetooth Hands-Free Profile device
OS_EXPORT AVAudioSessionPort const AVAudioSessionPortBluetoothHFP 		API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Input or output on a Universal Serial Bus device
OS_EXPORT AVAudioSessionPort const AVAudioSessionPortUSBAudio     		API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Input or output via Car Audio
OS_EXPORT AVAudioSessionPort const AVAudioSessionPortCarAudio     		API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Input or output that does not correspond to real audio hardware
OS_EXPORT AVAudioSessionPort const AVAudioSessionPortVirtual            API_AVAILABLE(ios(14.0), watchos(7.0), tvos(14.0)) API_UNAVAILABLE(macos);

/// Input or output connected via the PCI (Peripheral Component Interconnect) bus
OS_EXPORT AVAudioSessionPort const AVAudioSessionPortPCI                API_AVAILABLE(ios(14.0), watchos(7.0), tvos(14.0)) API_UNAVAILABLE(macos);

/// Input or output connected via FireWire
OS_EXPORT AVAudioSessionPort const AVAudioSessionPortFireWire           API_AVAILABLE(ios(14.0), watchos(7.0), tvos(14.0)) API_UNAVAILABLE(macos);

/// Input or output connected via DisplayPort
OS_EXPORT AVAudioSessionPort const AVAudioSessionPortDisplayPort        API_AVAILABLE(ios(14.0), watchos(7.0), tvos(14.0)) API_UNAVAILABLE(macos);

/// Input or output connected via AVB (Audio Video Bridging)
OS_EXPORT AVAudioSessionPort const AVAudioSessionPortAVB                API_AVAILABLE(ios(14.0), watchos(7.0), tvos(14.0)) API_UNAVAILABLE(macos);

/// Input or output connected via Thunderbolt
OS_EXPORT AVAudioSessionPort const AVAudioSessionPortThunderbolt        API_AVAILABLE(ios(14.0), watchos(7.0), tvos(14.0)) API_UNAVAILABLE(macos);

#pragma mark -- audio session categories --

/// A category defines a broad set of behaviors for a session.
typedef NSString *AVAudioSessionCategory NS_STRING_ENUM;

/*! Use this category for background sounds such as rain, car engine noise, etc.
 Mixes with other music. */
OS_EXPORT AVAudioSessionCategory const AVAudioSessionCategoryAmbient			API_AVAILABLE(ios(3.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*! Use this category for background sounds.  Other music will stop playing. */
OS_EXPORT AVAudioSessionCategory const AVAudioSessionCategorySoloAmbient		API_AVAILABLE(ios(3.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*! Use this category for music tracks.*/
OS_EXPORT AVAudioSessionCategory const AVAudioSessionCategoryPlayback			API_AVAILABLE(ios(3.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*! Use this category when recording audio. */
OS_EXPORT AVAudioSessionCategory const AVAudioSessionCategoryRecord				API_AVAILABLE(ios(3.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*! Use this category when recording and playing back audio. */
OS_EXPORT AVAudioSessionCategory const AVAudioSessionCategoryPlayAndRecord		API_AVAILABLE(ios(3.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*! Use this category when using a hardware codec or signal processor while
 not playing or recording audio. */
OS_EXPORT AVAudioSessionCategory const AVAudioSessionCategoryAudioProcessing API_DEPRECATED("No longer supported", ios(3.0, 10.0)) API_UNAVAILABLE(watchos, tvos, macos);

/*! Use this category to customize the usage of available audio accessories and built-in audio hardware.
 For example, this category provides an application with the ability to use an available USB output
 and headphone output simultaneously for separate, distinct streams of audio data. Use of
 this category by an application requires a more detailed knowledge of, and interaction with,
 the capabilities of the available audio routes.  May be used for input, output, or both.
 Note that not all output types and output combinations are eligible for multi-route.  Input is limited
 to the last-in input port. Eligible inputs consist of the following:
 AVAudioSessionPortUSBAudio, AVAudioSessionPortHeadsetMic, and AVAudioSessionPortBuiltInMic.
 Eligible outputs consist of the following:
 AVAudioSessionPortUSBAudio, AVAudioSessionPortLineOut, AVAudioSessionPortHeadphones, AVAudioSessionPortHDMI,
 and AVAudioSessionPortBuiltInSpeaker.
 Note that AVAudioSessionPortBuiltInSpeaker is only allowed to be used when there are no other eligible
 outputs connected.  */
OS_EXPORT AVAudioSessionCategory const AVAudioSessionCategoryMultiRoute API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

#pragma mark -- Values for the mode property --

/*!
 @brief      Modes modify the audio category in order to introduce behavior that is tailored to the specific
 use of audio within an application.  Available in iOS 5.0 and greater.
*/
typedef NSString *AVAudioSessionMode NS_STRING_ENUM;

/*! The default mode */
OS_EXPORT AVAudioSessionMode const AVAudioSessionModeDefault API_AVAILABLE(ios(5.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*! Only valid with AVAudioSessionCategoryPlayAndRecord.  Appropriate for Voice over IP
 (VoIP) applications.  Reduces the number of allowable audio routes to be only those
 that are appropriate for VoIP applications and may engage appropriate system-supplied
 signal processing.  Has the side effect of setting AVAudioSessionCategoryOptionAllowBluetoothHFP.
 Using this mode without the VoiceProcessing IO unit or AVAudioEngine with voice processing enabled will result in the following:
- Chat-specific signal processing such as echo cancellation or automatic gain correction will not be loaded
- Dynamic processing on input and output will be disabled resulting in a lower output playback level. */
OS_EXPORT AVAudioSessionMode const AVAudioSessionModeVoiceChat API_AVAILABLE(ios(5.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*! Set by Game Kit on behalf of an application that uses a GKVoiceChat object; valid
 only with the AVAudioSessionCategoryPlayAndRecord category.
 Do not set this mode directly. If you need similar behavior and are not using
 a GKVoiceChat object, use AVAudioSessionModeVoiceChat instead. */
OS_EXPORT AVAudioSessionMode const AVAudioSessionModeGameChat API_AVAILABLE(ios(5.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*! Only valid with AVAudioSessionCategoryPlayAndRecord or AVAudioSessionCategoryRecord.
 Modifies the audio routing options and may engage appropriate system-supplied signal processing. */
OS_EXPORT AVAudioSessionMode const AVAudioSessionModeVideoRecording API_AVAILABLE(ios(5.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*! Appropriate for applications that wish to minimize the effect of system-supplied signal
 processing for input and/or output audio signals.
 This mode disables some dynamics processing on input and output resulting in a lower output playback level. */
OS_EXPORT AVAudioSessionMode const AVAudioSessionModeMeasurement API_AVAILABLE(ios(5.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*! Appropriate for applications playing movie content. Only valid with AVAudioSessionCategoryPlayback.
 Setting this mode engages appropriate output signal processing for movie playback scenarios.
 Content using this mode is eligible for Enhance Dialogue processing on supported routes with capable hardware */
OS_EXPORT AVAudioSessionMode const AVAudioSessionModeMoviePlayback API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*! Only valid with kAudioSessionCategory_PlayAndRecord. Reduces the number of allowable audio
 routes to be only those that are appropriate for video chat applications. May engage appropriate
 system-supplied signal processing.  Has the side effect of setting
 AVAudioSessionCategoryOptionAllowBluetoothHFP and AVAudioSessionCategoryOptionDefaultToSpeaker. 
 Using this mode without the VoiceProcessing IO unit or AVAudioEngine with voice processing enabled will result in the following:
- Chat-specific signal processing such as echo cancellation or automatic gain correction will not be loaded
- Dynamic processing on input and output will be disabled resulting in a lower output playback level. */
OS_EXPORT AVAudioSessionMode const AVAudioSessionModeVideoChat API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*! Appropriate for applications which play spoken audio and wish to be paused (via audio session interruption) rather than ducked
 if another app (such as a navigation app) plays a spoken audio prompt.  Examples of apps that would use this are podcast players and
 audio books.  For more information, see the related category option AVAudioSessionCategoryOptionInterruptSpokenAudioAndMixWithOthers. */
OS_EXPORT AVAudioSessionMode const AVAudioSessionModeSpokenAudio API_AVAILABLE(ios(9.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*! Appropriate for applications which play audio using text to speech. Setting this mode allows for different routing behaviors when
 connected to certain audio devices such as CarPlay. An example of an app that would use this mode is a turn by turn navigation app that
 plays short prompts to the user. Typically, these same types of applications would also configure their session to use
 AVAudioSessionCategoryOptionDuckOthers and AVAudioSessionCategoryOptionInterruptSpokenAudioAndMixWithOthers */
OS_EXPORT AVAudioSessionMode const AVAudioSessionModeVoicePrompt API_AVAILABLE(ios(12.0), watchos(5.0), tvos(12.0)) API_UNAVAILABLE(macos);


/// Appropriate for applications playing short-form video content.
///
/// Only valid with ``AVAudioSessionCategoryPlayback``.
/// Not applicable with ``AVAudioSessionRouteSharingPolicy/AVAudioSessionRouteSharingPolicyLongFormAudio``,
/// or ``AVAudioSessionRouteSharingPolicy/AVAudioSessionRouteSharingPolicyLongFormVideo``.
///
/// When this mode is set:
/// - system will make informed decisions to automatically unmute the output of the media if the user shows intention of unmuting.
/// 	- When auto-unmuted, ``AVAudioSessionUserIntentToUnmuteOutputNotification`` and ``AVAudioSessionOutputMuteStateChangeNotification`` will be sent.
/// - if the session is output muted, system may prevent interrupting other active audio apps.
OS_EXPORT AVAudioSessionMode const AVAudioSessionModeShortFormVideo API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, tvos, visionos, macos);

/// Appropriate for applications that require simultaneous use of built-in microphone/speaker
/// with a secondary audio device that supports both input and output capabilities.
///
/// Only valid with ``AVAudioSessionCategoryMultiRoute``.
///
/// This mode requires ``AVAudioSessionCategoryOptionAllowBluetoothHFP`` to be set
///
/// When this mode is set:
/// - The audio route will always include built-in mic/speaker as the primary route
/// - Supported secondary route types: ``AVAudioSessionPortHeadsetMic``, ``AVAudioSessionPortHeadphones``, ``AVAudioSessionPortBluetoothLE``, ``AVAudioSessionPortBluetoothHFP``
/// - Only routes with both input/output capabilities will be supported
/// - Hardware volume controls will adjust volume for both primary and secondary routes
///   - System may engage appropriate signal processing for output routes
OS_EXPORT AVAudioSessionMode const AVAudioSessionModeDualRoute API_AVAILABLE(ios(26.2)) API_UNAVAILABLE(watchos, tvos, visionos, macos);

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
OS_EXPORT NSNotificationName const  AVAudioSessionInterruptionNotification API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*!
	@brief	Notification sent to registered listeners when an audio route change has occurred.

	Check the notification's userInfo dictionary for the route change reason and for a description
	of the previous audio route.
*/
OS_EXPORT NSNotificationName const  AVAudioSessionRouteChangeNotification API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*!
	@brief	Notification sent to registered listeners if the media server is killed.

	In the event that the server is killed, take appropriate steps to handle requests that come in
	before the server resets.  See Technical Q&A QA1749.
*/
OS_EXPORT NSNotificationName const  AVAudioSessionMediaServicesWereLostNotification API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*!
	@brief	Notification sent to registered listeners when the media server restarts.

	In the event that the server restarts, take appropriate steps to re-initialize any audio objects
	used by your application.  See Technical Q&A QA1749.
*/
OS_EXPORT NSNotificationName const  AVAudioSessionMediaServicesWereResetNotification API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*!
	@brief	Notification sent to registered listeners when they are in the foreground with an active
		audio session and primary audio from other applications starts and stops.

	Check the notification's userInfo dictionary for the notification type, which is either Begin or
	End. Foreground applications may use this notification as a hint to enable or disable audio that
	is secondary to the functionality of the application. For more information, see the related
	property secondaryAudioShouldBeSilencedHint.
*/
OS_EXPORT NSNotificationName const  AVAudioSessionSilenceSecondaryAudioHintNotification API_AVAILABLE(ios(8.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*!
	@brief  Notification sent to registered listeners when spatial playback capabilities are changed due to a
	change in user preference.

	Check the notification's userInfo dictionary for AVAudioSessionSpatialAudioEnabledKey to check if spatial
	audio is enabled.

	Observers of this notification should also observe AVAudioSessionRouteChangeNotification since a route change
	may also result in a change in the ability for the system to play spatial audio. Use
	AVAudioSessionPortDescription's isSpatialAudioEnabled property to check if the current route supports
	spatialized playback.
*/
OS_EXPORT NSNotificationName const  AVAudioSessionSpatialPlaybackCapabilitiesChangedNotification API_AVAILABLE(ios(15.0), watchos(8.0), tvos(15.0)) API_UNAVAILABLE(macos) NS_SWIFT_NAME(AVAudioSession.spatialPlaybackCapabilitiesChangedNotification);

/// Notification sent to registered listeners when the resolved rendering mode changes.
OS_EXPORT NSNotificationName const  AVAudioSessionRenderingModeChangeNotification API_AVAILABLE(ios(17.2), tvos(17.2)) API_UNAVAILABLE(watchos, macos, visionos) NS_SWIFT_NAME(AVAudioSession.renderingModeChangeNotification);

/*!
	 @brief Notification sent to registered listeners when the rendering capabilities change.
 */
OS_EXPORT NSNotificationName const AVAudioSessionRenderingCapabilitiesChangeNotification API_AVAILABLE(ios(17.2), tvos(17.2)) API_UNAVAILABLE(watchos, macos, visionos) NS_SWIFT_NAME(AVAudioSession.renderingCapabilitiesChangeNotification);

/*!
     @brief Notification sent to registered listeners when the system's capability to inject audio into input stream is changed
 
 Check the notification's userInfo dictionary for AVAudioSessionMicrophoneInjectionIsAvailableKey to check if microphone
 injection is available. Use AVAudioSession's isMicrophoneInjectionAvailable property to check if microphone injection is available
 */
OS_EXPORT NSNotificationName const AVAudioSessionMicrophoneInjectionCapabilitiesChangeNotification API_AVAILABLE(ios(18.2), visionos(2.2)) API_UNAVAILABLE(tvos, watchos, macos) NS_SWIFT_NAME(AVAudioSession.microphoneInjectionCapabilitiesChangeNotification);

/// Notification sent to registered listeners when session's output mute state changes.
///
/// The userInfo dictionary will contain the updated output mute value as accessed by ``AVAudioSessionMuteStateKey``
OS_EXPORT NSNotificationName const AVAudioSessionOutputMuteStateChangeNotification API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, tvos, visionos, macos) NS_SWIFT_NAME(AVAudioSession.outputMuteStateChangeNotification);

/// Keys for ``AVAudioSessionOutputMuteStateChangeNotification``
/// Value is `NSNumber` type with boolean value 0 for unmuted or value 1 for muted (samples zeroed out)
OS_EXPORT NSString *const AVAudioSessionMuteStateKey API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, tvos, visionos, macos) NS_SWIFT_NAME(AVAudioSession.muteStateKey);

/// Notification sent to registered listeners when the application's output is muted and user hints to unmute.
OS_EXPORT NSNotificationName const AVAudioSessionUserIntentToUnmuteOutputNotification API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, tvos, visionos, macos) NS_SWIFT_NAME(AVAudioSession.userIntentToUnmuteOutputNotification);

#pragma mark-- Keys for NSNotification userInfo dictionaries --

/// keys for AVAudioSessionSpatialPlaybackCapabilitiesChangedNotification
/// value is an NSNumber whose boolean value indicates if spatial audio enabled.
OS_EXPORT NSString *const AVAudioSessionSpatialAudioEnabledKey API_AVAILABLE(ios(15.0), watchos(8.0), tvos(15.0)) API_UNAVAILABLE(macos);

/// keys for AVAudioSessionInterruptionNotification
/// Value is an NSNumber representing an AVAudioSessionInterruptionType
OS_EXPORT NSString *const AVAudioSessionInterruptionTypeKey API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Only present for end interruption events.  Value is of type AVAudioSessionInterruptionOptions.
OS_EXPORT NSString *const AVAudioSessionInterruptionOptionKey API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

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
OS_EXPORT NSString *const AVAudioSessionRouteChangeReasonKey API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);
/// value is AVAudioSessionRouteDescription *
OS_EXPORT NSString *const AVAudioSessionRouteChangePreviousRouteKey API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// keys for AVAudioSessionSilenceSecondaryAudioHintNotification
/// value is an NSNumber representing an AVAudioSessionSilenceSecondaryAudioHintType
OS_EXPORT NSString *const AVAudioSessionSilenceSecondaryAudioHintTypeKey API_AVAILABLE(ios(8.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// keys for AVAudioSessionRenderingModeChangeNotification
/// Contains a payload of NSInteger representing the new resolved rendering mode
OS_EXPORT NSString *const AVAudioSessionRenderingModeNewRenderingModeKey API_AVAILABLE(ios(17.2), tvos(17.2)) API_UNAVAILABLE(watchos, macos, visionos);

/*!
    Keys for AVAudioSessionMicrophoneInjectionCapabilitiesChangeNotification
*/
/// Indicates if microphone injection is available.
/// Value is an NSNumber whose boolean value indicates if microphone injection is available.
OS_EXPORT NSString *const AVAudioSessionMicrophoneInjectionIsAvailableKey API_AVAILABLE(ios(18.2), visionos(2.2)) API_UNAVAILABLE(tvos, watchos, macos);

/*!
	@brief  Notification sent to registered listeners when there are changes in ``availableInputs``.

	There is no payload (userInfo dictionary) associated with the ``AVAudioSessionAvailableInputsChangeNotification`` notification.
*/
OS_EXPORT NSNotificationName const AVAudioSessionAvailableInputsChangeNotification API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, tvos, visionos, macos)
NS_SWIFT_NAME(AVAudioSession.availableInputsChangeNotification);

#pragma mark-- enumerations --

/*!
    @enum AVAudioSessionActivationOptions
    @brief   For use with activateWithOptions:completionHandler:
    
    Reserved for future use. Added in watchOS 5.0.
*/
typedef NS_OPTIONS(NSUInteger, AVAudioSessionActivationOptions) {
    AVAudioSessionActivationOptionNone    = 0
};

/// For use with overrideOutputAudioPort:error:
typedef NS_ENUM(NSUInteger, AVAudioSessionPortOverride) {
    /// No override.  Return audio routing to the default state for the current audio category.
    AVAudioSessionPortOverrideNone = 0,
    /// Route audio output to speaker.  Use this override with AVAudioSessionCategoryPlayAndRecord,
    /// which by default routes the output to the receiver.
    AVAudioSessionPortOverrideSpeaker API_UNAVAILABLE(tvos, watchos, macos) = 'spkr'
};

/// Values for AVAudioSessionRouteChangeReasonKey in AVAudioSessionRouteChangeNotification's
/// userInfo dictionary
typedef NS_ENUM(NSUInteger, AVAudioSessionRouteChangeReason) {
    /// The reason is unknown.
    AVAudioSessionRouteChangeReasonUnknown = 0,

    /// A new device became available (e.g. headphones have been plugged in).
    AVAudioSessionRouteChangeReasonNewDeviceAvailable = 1,

    /// The old device became unavailable (e.g. headphones have been unplugged).
    AVAudioSessionRouteChangeReasonOldDeviceUnavailable = 2,

    /// The audio category has changed (e.g. AVAudioSessionCategoryPlayback has been changed to
    /// AVAudioSessionCategoryPlayAndRecord).
    AVAudioSessionRouteChangeReasonCategoryChange = 3,

    /// The route has been overridden (e.g. category is AVAudioSessionCategoryPlayAndRecord and
    /// the output has been changed from the receiver, which is the default, to the speaker).
    AVAudioSessionRouteChangeReasonOverride = 4,

    /// The device woke from sleep.
    AVAudioSessionRouteChangeReasonWakeFromSleep = 6,

    /// Returned when there is no route for the current category (for instance, the category is
    /// AVAudioSessionCategoryRecord but no input device is available).
    AVAudioSessionRouteChangeReasonNoSuitableRouteForCategory = 7,

    /// Indicates that the set of input and/our output ports has not changed, but some aspect of
    /// their configuration has changed.  For example, a port's selected data source has changed.
    /// (Introduced in iOS 7.0, watchOS 2.0, tvOS 9.0).
    AVAudioSessionRouteChangeReasonRouteConfigurationChange = 8
};


///		Customization of various aspects of a category's behavior.
///		Use with ``AVAudioSession/setCategory:mode:options:error:``.
///
///    Applications must be prepared for changing category options to fail as behavior may change
///    in future releases. If an application changes its category, it should reassert the options,
///    since they are not sticky across category changes. Introduced in iOS 6.0 / watchOS 2.0 /
///    tvOS 9.0.
typedef NS_OPTIONS(NSUInteger, AVAudioSessionCategoryOptions) {

	///		Controls whether other active audio apps will be interrupted or mixed with when your app's
	///		audio session goes active. Details depend on the category.
	///
	///		- ``AVAudioSessionCategoryPlayAndRecord`` or
	///			``AVAudioSessionCategoryMultiRoute`` with ``AVAudioSessionModeDefault``:
	///			MixWithOthers defaults to false, but can be set to true, allowing other applications to
	///			play in the background while your app has both audio input and output enabled.
	///
	///		- ``AVAudioSessionCategoryPlayback``:
	///			MixWithOthers defaults to false, but can be set to true, allowing other applications to
	///			play in the background. Your app will still be able to play regardless of the setting
	///			of the ringer switch.
	///
	///		- Other categories:
	///			MixWithOthers defaults to false and cannot be changed.
	///
	///		MixWithOthers is only valid with ``AVAudioSessionCategoryPlayAndRecord``,
	///		``AVAudioSessionCategoryPlayback``, and
	///		``AVAudioSessionCategoryMultiRoute`` with ``AVAudioSessionModeDefault``.
    AVAudioSessionCategoryOptionMixWithOthers            = 0x1,

	///		Controls whether or not other active audio apps will be ducked when when your app's audio
	///		session goes active. An example of this is a workout app, which provides periodic updates to
	///		the user. It reduces the volume of any music currently being played while it provides its
	///		status.
	///
	///		Defaults to off. Note that the other audio will be ducked for as long as the current session
	///		is active. You will need to deactivate your audio session when you want to restore full
	///		volume playback (un-duck) other sessions.
	///
	///		Setting this option will also make your session mixable with others
	///		(``AVAudioSessionCategoryOptionMixWithOthers`` will be set).
	///
	///		DuckOthers is only valid with ``AVAudioSessionCategoryAmbient``,
	///		``AVAudioSessionCategoryPlayAndRecord``, ``AVAudioSessionCategoryPlayback``, and
	///		``AVAudioSessionCategoryMultiRoute`` with ``AVAudioSessionModeDefault``.
    AVAudioSessionCategoryOptionDuckOthers               = 0x2,

	/// Deprecated - please see ``AVAudioSessionCategoryOptionAllowBluetoothHFP``
	AVAudioSessionCategoryOptionAllowBluetooth API_DEPRECATED_WITH_REPLACEMENT("AVAudioSessionCategoryOptionAllowBluetoothHFP", ios(1.0, 8.0), watchos(11.0, 11.0), tvos(17.0, 17.0), visionos(1.0, 1.0)) API_UNAVAILABLE(macos) = 0x4,

	///		Allows an application to change the default behavior of some audio session categories with
	///		regard to whether Bluetooth Hands-Free Profile (HFP) devices are available for routing. The
	///		exact behavior depends on the category.
	///
	///		- ``AVAudioSessionCategoryPlayAndRecord``:
	///			AllowBluetoothHFP defaults to false, but can be set to true, allowing a paired bluetooth
	///			HFP device to appear as an available route for input, while playing through the
	///			category-appropriate output.
	///
	///		- ``AVAudioSessionCategoryRecord``:
	///			AllowBluetoothHFP defaults to false, but can be set to true, allowing a paired Bluetooth
	///			HFP device to appear as an available route for input.
	///
	///		- Other categories:
	///			AllowBluetoothHFP defaults to false and cannot be changed. Enabling Bluetooth for input in
	///			these categories is not allowed.
	AVAudioSessionCategoryOptionAllowBluetoothHFP API_AVAILABLE(ios(1.0), watchos(11.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(macos) = 0x4,

	///		Allows an application to change the default behavior of some audio session categories with
	///		regard to the audio route. The exact behavior depends on the category.
	///
	///		- ``AVAudioSessionCategoryPlayAndRecord``:
	///			DefaultToSpeaker will default to false, but can be set to true, routing to Speaker
	///			(instead of Receiver) when no other audio route is connected.
	///
	///		- Other categories:
	///			DefaultToSpeaker is always false and cannot be changed.
	AVAudioSessionCategoryOptionDefaultToSpeaker API_UNAVAILABLE(tvos, watchos, macos) = 0x8,

	///		When a session with InterruptSpokenAudioAndMixWithOthers set goes active, then if there is
	///		another playing app whose session mode is ``AVAudioSessionModeSpokenAudio`` (for podcast
	///		playback in the background, for example), then the spoken-audio session will be
	///		interrupted. A good use of this is for a navigation app that provides prompts to its user:
	///		it pauses any spoken audio currently being played while it plays the prompt.
	///
	///		InterruptSpokenAudioAndMixWithOthers defaults to off. Note that the other app's audio will
	///		be paused for as long as the current session is active. You will need to deactivate your
	///		audio session to allow the other session to resume playback. Setting this option will also
	///		make your category mixable with others (``AVAudioSessionCategoryOptionMixWithOthers``
	///		will be set). If you want other non-spoken audio apps to duck their audio when your app's session
	///		goes active, also set ``AVAudioSessionCategoryOptionDuckOthers``.
	///
	///		Only valid with ``AVAudioSessionCategoryPlayAndRecord``,
	///		``AVAudioSessionCategoryPlayback``, and
	///		``AVAudioSessionCategoryMultiRoute`` with ``AVAudioSessionModeDefault``.
	AVAudioSessionCategoryOptionInterruptSpokenAudioAndMixWithOthers API_AVAILABLE(ios(9.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos) = 0x11,

	///		Allows an application to change the default behavior of some audio session categories with
	///		regard to whether Bluetooth Advanced Audio Distribution Profile (A2DP) devices are
	///		available for routing. The exact behavior depends on the category.
	///
	///		- ``AVAudioSessionCategoryPlayAndRecord``:
	///			AllowBluetoothA2DP defaults to false, but can be set to true, allowing a paired
	///			Bluetooth A2DP device to appear as an available route for output, while recording
	///			through the category-appropriate input.
	///
	///		- ``AVAudioSessionCategoryMultiRoute`` and ``AVAudioSessionCategoryRecord``:
	///			AllowBluetoothA2DP is false, and cannot be set to true.
	///
	///		- Other categories:
	///			AllowBluetoothA2DP is always implicitly true and cannot be changed; Bluetooth A2DP ports
	///			are always supported in output-only categories.
	///
	///		Setting both ``AVAudioSessionCategoryOptionAllowBluetoothHFP``
	///		and ``AVAudioSessionCategoryOptionAllowBluetoothA2DP`` is
	///		allowed. In cases where a single Bluetooth device supports both HFP and A2DP, the HFP
	///		ports will be given a higher priority for routing. For HFP and A2DP ports on separate
	///		hardware devices, the last-in wins rule applies.
	AVAudioSessionCategoryOptionAllowBluetoothA2DP API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos) = 0x20,

	///		Allows an application to change the default behavior of some audio session categories
	///		with regard to showing AirPlay devices as available routes. This option applies to
	///		various categories in the same way as ``AVAudioSessionCategoryOptionAllowBluetoothA2DP``;
	///		see above for details. Only valid with ``AVAudioSessionCategoryPlayAndRecord``.
	AVAudioSessionCategoryOptionAllowAirPlay API_AVAILABLE(ios(10.0), tvos(10.0)) API_UNAVAILABLE(watchos, macos) = 0x40,

	///		Some devices include a privacy feature that mutes the built-in microphone at a hardware level
	///		under certain conditions e.g. when the Smart Folio of an iPad is closed. The default behavior is
	///		to interrupt the session using the built-in microphone when that microphone is muted in hardware.
	///		This option allows an application to opt out of the default behavior if it is using a category that
	///		supports both input and output, such as ``AVAudioSessionCategoryPlayAndRecord``, and wants to
	///		allow its session to stay activated even when the microphone has been muted. The result would be
	///		that playback continues as normal, and microphone sample buffers would continue to be produced
	///		but all microphone samples would have a value of zero.
	///
	///		This may be useful if an application knows that it wants to allow playback to continue and
	///		recording/monitoring a muted microphone will not lead to a poor user experience. Attempting to use
	///		this option with a session category that doesn't support the use of audio input will result in an error.
	///
	///		- Note Under the default policy, a session will be interrupted if it is running input at the time when
	///		the microphone is muted in hardware. Similarly, attempting to start input when the microphone is
	///		muted will fail.
	///		- Note This option has no relation to the recordPermission property, which indicates whether or
	///		not the user has granted permission to use microphone input.
	AVAudioSessionCategoryOptionOverrideMutedMicrophoneInterruption API_AVAILABLE(ios(14.5), watchos(7.3)) API_UNAVAILABLE(tvos, macos) = 0x80,

	/// 	This option should be used if a session prefers to use FarFieldInput when available.
	/// 	This option is only valid with categories that support input -
	/// 	``AVAudioSessionCategoryPlayAndRecord`` and ``AVAudioSessionCategoryRecord``.
	///
	/// 	- This option requires ``AVAudioSessionCategoryOptionAllowBluetoothHFP`` to be set.
	/// 	Otherwise error will be returned.
	///
	///		- Support for this can be queried on input ports via the BluetoothMicrophone interface on a port,
	///		via its member `farFieldCapture.isSupported`.
	///
	///		- Active sessions can see if far-field input is enabled on a bluetooth audio device by querying
	///		the BluetoothMicrophone interface of the input port of the current route for: `farFieldCapture.isEnabled`.
	AVAudioSessionCategoryOptionFarFieldInput API_AVAILABLE(ios(26.2)) API_UNAVAILABLE(watchos, tvos, macos, visionos) = 1 << 18,

	///		When this option is specified with a category that supports both input and output, the session
	///		will enable full-bandwidth audio in both input & output directions, if the Bluetooth route supports
	///		it (e.g. certain AirPods models). It is currently compatible only with mode ``AVAudioSessionModeDefault``.
	///
	///		- Support for this can be queried on input ports via the BluetoothMicrophone interface on a port,
	///			via its member `highQualityRecording.isSupported`.
	///
	///		- Active sessions can see if full-bandwidth Bluetooth audio was successfully enabled by querying
	///		the BluetoothMicrophone interface of the input port of the current route for:
	///		`highQualityRecording.isEnabled`.
	///
	///		- When this option is provided alone, it will be enabled if the route supports it, otherwise the option
	///		will be ignored. This option may be combined with ``AVAudioSessionCategoryOptionAllowBluetoothHFP``,
	///		in which case HFP will be used as a fallback if the route does not support this
	///		``AVAudioSessionCategoryOptionBluetoothHighQualityRecording`` option.
	///
	///		- Note This option may increase input latency when enabled and is therefore not recommended for
	///			real-time communication usage.
	///		- Note Apps using ``AVAudioSessionCategoryOptionBluetoothHighQualityRecording``
	///		may want to consider setting ``AVAudioSession/setPrefersNoInterruptionsFromSystemAlerts:error:``
	///		while recording, to avoid the recording session being interrupted by an incoming call ringtone.
	AVAudioSessionCategoryOptionBluetoothHighQualityRecording API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, tvos, macCatalyst, visionos, macos) = 1 << 19
};

/// Values for AVAudioSessionInterruptionTypeKey in AVAudioSessionInterruptionNotification's
/// userInfo dictionary.
typedef NS_ENUM(NSUInteger, AVAudioSessionInterruptionType) {
    AVAudioSessionInterruptionTypeBegan = 1, ///< the system has interrupted your audio session
    AVAudioSessionInterruptionTypeEnded = 0, ///< the interruption has ended
};

/// Values for AVAudioSessionInterruptionOptionKey in AVAudioSessionInterruptionNotification's
/// userInfo dictionary.
typedef NS_OPTIONS(NSUInteger, AVAudioSessionInterruptionOptions) {
    /// Indicates that you should resume playback now that the interruption has ended.
    AVAudioSessionInterruptionOptionShouldResume = 1
};

/*!
    @enum AVAudioSessionInterruptionReason
    @brief   Values for AVAudioSessionInterruptionReasonKey in AVAudioSessionInterruptionNotification's userInfo dictionary.

    @var   AVAudioSessionInterruptionReasonDefault
        The audio session was interrupted because another session was activated.

    @var   AVAudioSessionInterruptionReasonAppWasSuspended
        The audio session was interrupted due to the app being suspended by the operating sytem.
		Deprecated. Interruption notifications with reason 'wasSuspended' not present from iOS 16 onwards.

    @var   AVAudioSessionInterruptionReasonBuiltInMicMuted
        The audio session was interrupted due to the built-in mic being muted e.g. due to an iPad's Smart Folio being closed.
 
    @var   AVAudioSessionInterruptionReasonRouteDisconnected
        The audio session was interrupted due to route getting disconnected.
 
	@var   AVAudioSessionInterruptionReasonDeviceUnauthenticated
		The audio session was interrupted due to device being doffed or locked.
 
 */
typedef NS_ENUM(NSUInteger, AVAudioSessionInterruptionReason) {
    AVAudioSessionInterruptionReasonDefault         = 0,
    AVAudioSessionInterruptionReasonAppWasSuspended API_DEPRECATED("wasSuspended reason no longer present", ios(14.5, 16.0)) = 1,
    AVAudioSessionInterruptionReasonBuiltInMicMuted = 2,
#if TARGET_OS_VISION
    ///The audio session was interrupted because its UIScene was backgrounded
    AVAudioSessionInterruptionReasonSceneWasBackgrounded = 3,
#endif // TARGET_OS_VISION
    ///The audio session was interrupted because route was disconnected.
    AVAudioSessionInterruptionReasonRouteDisconnected API_AVAILABLE(ios(17.0), watchos(10.0), tvos(17.0)) API_UNAVAILABLE(macos) = 4,
#if TARGET_OS_VISION
	AVAudioSessionInterruptionReasonDeviceUnauthenticated API_UNAVAILABLE(visionos) = 5,
#endif // TARGET_OS_VISION
} NS_SWIFT_NAME(AVAudioSession.InterruptionReason);

///  options for use when calling setActive:withOptions:error:
typedef NS_OPTIONS(NSUInteger, AVAudioSessionSetActiveOptions)
{
    /// Notify an interrupted app that the interruption has ended and it may resume playback. Only
    /// valid on session deactivation.
    AVAudioSessionSetActiveOptionNotifyOthersOnDeactivation = 1
};

/// Values for AVAudioSessionSilenceSecondaryAudioHintTypeKey in
/// AVAudioSessionSilenceSecondaryAudioHintNotification's userInfo dictionary, to indicate whether
/// optional secondary audio muting should begin or end.
typedef NS_ENUM(NSUInteger, AVAudioSessionSilenceSecondaryAudioHintType) {
    /// Another application's primary audio has started.
    AVAudioSessionSilenceSecondaryAudioHintTypeBegin = 1,

    /// Another application's primary audio has stopped.
    AVAudioSessionSilenceSecondaryAudioHintTypeEnd = 0,
};

/*!
	@enum AVAudioSessionIOType
    @brief   Values to be used by setAggregatedIOPreference:error: method.
    
	Starting in iOS 10, applications that use AVCaptureSession on iPads and iPhones that
	support taking Live Photos, will have non-aggregated audio I/O unless the app opts out by
	setting its AVAudioSessionIOType to Aggregated. Non-aggregated audio I/O means that separate
	threads will be used to service audio I/O for input and output directions.

	Note that in cases where the I/O is not aggregated, the sample rate and IO buffer duration
	properties will map to the output audio device. In this scenario, the input and
	output audio hardware may be running at different sample rates and with different IO buffer
	durations. If your app requires input and output audio to be presented in the same realtime
	I/O callback, or requires that input and output audio have the same sample rate or IO buffer
	duration, or if your app requires the ability to set a preferred sample rate or IO buffer duration
	for audio input, set the AVAudioSessionIOType to Aggregated.

	Apps that don't use AVCaptureSession and use AVAudioSessionCategoryPlayAndRecord will continue
	to have aggregated audio I/O, as in previous versions of iOS.

    @var   AVAudioSessionIOTypeNotSpecified
        The default value.  If your app does not use AVCaptureSession or does not have any specific
        requirement for aggregating input and output audio in the same realtime I/O callback, use this
        value. Note that if your app does not use AVCaptureSession, it will get aggregated I/O when using
        AVAudioSessionCategoryPlayAndRecord.

        If your app does utilize AVCaptureSession, use of this value will allow AVCaptureSession to
        start recording without glitching already running output audio and will allow the system to
        utilize power-saving optimizations.

    @var    AVAudioSessionIOTypeAggregated
        Use this value if your session uses AVAudioSessionCategoryPlayAndRecord and requires input and
        output audio to be presented in the same realtime I/O callback. For example, if your app will be using
        a RemoteIO with both input and output enabled.

        Note that your session's preference to use aggregated IO will not be honored if it specifies
        AVAudioSessionCategoryOptionMixWithOthers AND another app's audio session was already active
        with non-mixable, non-aggregated input/output.
 
    Added in iOS 10.0. Not applicable on watchos, tvos, macos.
*/
typedef NS_ENUM(NSUInteger, AVAudioSessionIOType) {
    AVAudioSessionIOTypeNotSpecified = 0,
    AVAudioSessionIOTypeAggregated = 1,
};

/*!
    @enum        AVAudioSessionRouteSharingPolicy
    @brief   Starting in iOS 11, tvOS 11, and watchOS 5, the route sharing policy allows a session
        to specify that its output audio should be routed somewhere other than the default system output,
        when appropriate alternative routes are available.
    @var    AVAudioSessionRouteSharingPolicyDefault
        Follow normal rules for routing audio output.
    @var    AVAudioSessionRouteSharingPolicyLongFormAudio
        Route output to the shared long-form audio output. A session whose primary use case is as a
        music or podcast player may use this value to play to the same output as the built-in Music (iOS),
        Podcasts, or iTunes (macOS) applications. Typically applications that use this policy will also
        want sign up for remote control events as documented in “Event Handling Guide for UIKit Apps”
        and will want to utilize MediaPlayer framework’s MPNowPlayingInfoCenter class. All applications
        on the system that use the long-form audio route sharing policy will have their audio routed to the
        same location.
        Apps running on watchOS using this policy will also be able to play audio in the background,
        as long as an eligible audio route can be activated. Apps running on watchOS using this policy
        must use -activateWithOptions:completionHandler: instead of -setActive:withOptions:error: in
        order to ensure that the user will be given the opportunity to pick an appropriate audio route
        in cases where the system is unable to automatically pick the route.
    @var    AVAudioSessionRouteSharingPolicyLongForm
        Deprecated. Replaced by AVAudioSessionRouteSharingPolicyLongFormAudio.
    @var    AVAudioSessionRouteSharingPolicyIndependent
        Applications should not attempt to set this value directly. On iOS, this value will be set by
        the system in cases where route picker UI is used to direct video to a wireless route.
    @var    AVAudioSessionRouteSharingPolicyLongFormVideo
        Route output to the shared long-form video output. A session whose primary use case is as a
        movie or other long-form video content player may use this value to play to the same output as
        other long-form video content applications such as the built-in TV (iOS) application. Applications
        that use this policy will also want to also set the AVInitialRouteSharingPolicy key
        in their Info.plist to "LongFormVideo". All applications on the system that use the long-form video
        route sharing policy will have their audio and video routed to the same location (e.g. AppleTV when
        an AirPlay route is selected). Video content not using this route sharing policy will remain local
        to the playback device even when long form video content is being routed to AirPlay.
*/
typedef NS_ENUM(NSUInteger, AVAudioSessionRouteSharingPolicy) {
    AVAudioSessionRouteSharingPolicyDefault = 0,
    AVAudioSessionRouteSharingPolicyLongFormAudio = 1,
    AVAudioSessionRouteSharingPolicyLongForm API_DEPRECATED_WITH_REPLACEMENT("AVAudioSessionRouteSharingPolicyLongFormAudio", ios(11.0, 13.0), watchos(4.0, 6.0), tvos(11.0, 13.0)) API_UNAVAILABLE(macos) = AVAudioSessionRouteSharingPolicyLongFormAudio,
    AVAudioSessionRouteSharingPolicyIndependent = 2,
    AVAudioSessionRouteSharingPolicyLongFormVideo API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos, macos) = 3,
};

/*!
     @enum     AVAudioSessionPromptStyle
     @brief
         The prompt style is a hint to sessions that use AVAudioSessionModeVoicePrompt to modify the type of
         prompt they play in response to other audio activity on the system, such as Siri or phone calls.
         Sessions that issue voice prompts are encouraged to pay attention to changes in the prompt style and
         modify their prompts in response. Apple encourages the use of non-verbal prompts when the Short
         style is requested.
     @var AVAudioSessionPromptStyleNone
         Indicates that another session is actively using microphone input and would be negatively impacted
         by having prompts play at that time. For example if Siri is recognizing speech, having navigation or
         exercise prompts play, could interfere with its ability to accurately recognize the user’s speech.
         Client sessions should refrain from playing any prompts while the prompt style is None.
     @var AVAudioSessionPromptStyleShort
         Indicates one of three states: Siri is active but not recording, voicemail playback is active, or
         voice call is active. Short, non-verbal versions of prompts should be used.
     @var AVAudioSessionPromptStyleNormal
         Indicates that normal (long, verbal) versions of prompts may be used.
 */
typedef NS_ENUM(NSUInteger, AVAudioSessionPromptStyle)
{
    AVAudioSessionPromptStyleNone = 'none',
    AVAudioSessionPromptStyleShort = 'shrt',
    AVAudioSessionPromptStyleNormal = 'nrml',
};

/*!
	@enum AVAudioStereoOrientation
	@brief
	Constants indicating stereo input audio orientation, for use with built-in mic input data sources with a stereo polar pattern selected.

	@var AVAudioStereoOrientationNone
	Indicates that audio capture orientation is not applicable (on mono capture, for instance).
	@var AVAudioStereoOrientationPortrait
	Indicates that audio capture should be oriented vertically, Lightning connector on the bottom.
	@var AVAudioStereoOrientationPortraitUpsideDown
	Indicates that audio capture should be oriented vertically, Lightning connector on the top.
	@var AVAudioStereoOrientationLandscapeRight
	Indicates that audio capture should be oriented horizontally, Lightning connector on the right.
	@var AVAudioStereoOrientationLandscapeLeft
	Indicates that audio capture should be oriented horizontally, Lightning connector on the left.
*/
typedef NS_ENUM(NSInteger, AVAudioStereoOrientation) {
    AVAudioStereoOrientationNone               = 0,
    AVAudioStereoOrientationPortrait           = 1,
    AVAudioStereoOrientationPortraitUpsideDown = 2,
    AVAudioStereoOrientationLandscapeRight     = 3,
    AVAudioStereoOrientationLandscapeLeft      = 4,
} NS_SWIFT_NAME(AVAudioSession.StereoOrientation);

/*!
	@enum AVAudioSessionRecordPermission
	@brief	These are the values returned by recordPermission.
	@var	AVAudioSessionRecordPermissionUndetermined
	The user has not yet been asked for permission.
	@var	AVAudioSessionRecordPermissionDenied
	The user has been asked and has denied permission.
	@var	AVAudioSessionRecordPermissionGranted
	The user has been asked and has granted permission.

	Introduced: ios(8.0), watchos(4.0)
*/
typedef NS_ENUM(NSUInteger, AVAudioSessionRecordPermission) {
	AVAudioSessionRecordPermissionUndetermined API_DEPRECATED_WITH_REPLACEMENT("AVAudioApplicationRecordPermissionUndetermined", ios(8.0, 17.0), watchos(4.0, 10.0)) API_UNAVAILABLE(macos, tvos) = 'undt',
	AVAudioSessionRecordPermissionDenied API_DEPRECATED_WITH_REPLACEMENT("AVAudioApplicationRecordPermissionDenied", ios(8.0, 17.0), watchos(4.0, 10.0)) API_UNAVAILABLE(macos, tvos) = 'deny',
	AVAudioSessionRecordPermissionGranted API_DEPRECATED_WITH_REPLACEMENT("AVAudioApplicationRecordPermissionGranted", ios(8.0, 17.0), watchos(4.0, 10.0)) API_UNAVAILABLE(macos, tvos) = 'grnt'
};

/*!
	@enum AVAudioSessionRenderingMode
	@var  AVAudioSessionRenderingModeNotApplicable
	@var  AVAudioSessionRenderingModeMonoStereo
	@var  AVAudioSessionRenderingModeSurround
	@var  AVAudioSessionRenderingModeSpatialAudio
	@var  AVAudioSessionRenderingModeDolbyAudio
	@var  AVAudioSessionRenderingModeDolbyAtmos
*/
typedef NS_ENUM(NSInteger, AVAudioSessionRenderingMode) {
	/// Default Mode when no asset is loaded or playing
	AVAudioSessionRenderingModeNotApplicable           = 0,
 
	/// Default mode for non multi-channel cases
	AVAudioSessionRenderingModeMonoStereo              = 1,
 
	/// Default mode for multi-channel cases that do not fall into the modes below
	AVAudioSessionRenderingModeSurround                = 2,

	/// Fallback mode if provided content is Dolby variant but hardware capabilities don't support it
	AVAudioSessionRenderingModeSpatialAudio            = 3,
	
	/// Dolby Audio mode
	AVAudioSessionRenderingModeDolbyAudio              = 4,
	
	/// Dolby Atmos mode
	AVAudioSessionRenderingModeDolbyAtmos              = 5,
} NS_SWIFT_NAME(AVAudioSession.RenderingMode);

/*!
    @enum AVAudioSessionMicrophoneInjectionMode
    @brief Various modes to inject audio coming from a session to another app’s input stream
 
    Applications can state their intent to mix locally generated audio, which should consist primarily of
    synthesized speech, to another app's input stream. This feature is intended to be used by accessibility apps
    implementing augmentative and alternative communication systems that enable users with disabilities to
    communicate with synthesized speech. When input is muted, microphone injection will also be muted.
 
    @var  AVAudioSessionMicrophoneInjectionModeNone
    @var  AVAudioSessionMicrophoneInjectionModeSpokenAudio
 
*/
typedef NS_ENUM(NSInteger, AVAudioSessionMicrophoneInjectionMode) {
    /// Default state, microphone injection is not preferred
    AVAudioSessionMicrophoneInjectionModeNone = 0,
    
    /// Inject Spoken Audio, like synthesized speech, with microphone audio
    AVAudioSessionMicrophoneInjectionModeSpokenAudio = 1,
} NS_SWIFT_NAME(AVAudioSession.MicrophoneInjectionMode);

#if TARGET_OS_VISION
/*!
 The perceived "size" or "immersivity" of the sound. Use Small for least
 immersive and Large for most immersive.
 */
typedef NS_ENUM(NSInteger, AVAudioSessionSoundStageSize) {
	/// The audio session determines its own sound stage size based on
	/// a handful of factors
	AVAudioSessionSoundStageSizeAutomatic = 0,

	/// A smaller, front-focused sound stage
	AVAudioSessionSoundStageSizeSmall     = 1,

	/// A medium-immersive sound stage
	AVAudioSessionSoundStageSizeMedium    = 2,

	/// A fully-immersive sound stage
	AVAudioSessionSoundStageSizeLarge     = 3,
} NS_SWIFT_NAME(AVAudioSession.SoundStageSize);

/*!
 When the intended spatial experience is HeadTracked, the anchoring strategy
 provides additional information about the reference point for spatialization.
 */
typedef NS_ENUM(NSInteger, AVAudioSessionAnchoringStrategy) {
	/// The audio session determines its own anchoring strategy based on
	/// a handful of factors
	AVAudioSessionAnchoringStrategyAutomatic   = 0,

	/// The session is anchored to the developer-provided scene
	/// identifier (i.e. UIScene.session.persistentIdentifier)
	AVAudioSessionAnchoringStrategyScene       = 1,

	/// The session is anchored to the user's concept of "front"
	/// which the user can move with an intentional gesture.
	AVAudioSessionAnchoringStrategyFront       = 2
} NS_REFINED_FOR_SWIFT;

typedef NS_ENUM(NSInteger, AVAudioSessionSpatialExperience) {
	/// A fully head-tracked spatial experience parameterized by
	/// a sound stage size and anchoring strategy
	AVAudioSessionSpatialExperienceHeadTracked = 0,

	/// An unanchored, non-head-tracked spatial experience parameterized
	/// by a sound stage size
	AVAudioSessionSpatialExperienceFixed       = 1,

	/// An experience that bypasses any system-provided spatialization and
	/// instead mixes the application's sound straight to the output
	AVAudioSessionSpatialExperienceBypassed  = 2,
} NS_REFINED_FOR_SWIFT;

typedef NSString * const AVAudioSessionSpatialExperienceOption NS_TYPED_ENUM NS_REFINED_FOR_SWIFT;

/// Associated value is NSNumber with AVAudioSessionSoundStageSize. Only used if
/// SpatialExperience is HeadTracked or Fixed. If not provided for
/// those SpatialExperiences, the default will be
/// AVAudioSessionSoundStageSizeAutomatic.
OS_EXPORT AVAudioSessionSpatialExperienceOption AVAudioSessionSpatialExperienceOptionSoundStageSize API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(ios, watchos, tvos, macos);

/// Associated value is NSNumber with AVAudioSessionAnchoringStrategy. Only used if
/// SpatialExperience is HeadTracked. If not provided for a head-tracked
/// spatial experience, the default will be
/// AVAudioSessionAnchoringStrategyAutomatic.
OS_EXPORT AVAudioSessionSpatialExperienceOption AVAudioSessionSpatialExperienceOptionAnchoringStrategy API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(ios, watchos, tvos, macos);

/// Associated value is NSString from UIScene.session.persistentIdentifier. Only
/// used if SpatialExperience is HeadTracked and AnchoringStrategy is
/// Scene. If not provided for a scene-anchored spatial experience, the
/// session will fail to set the intended spatial experience and
/// return an error.
OS_EXPORT AVAudioSessionSpatialExperienceOption AVAudioSessionSpatialExperienceOptionSceneIdentifier API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(ios, watchos, tvos, macos);

#endif // TARGET_OS_VISION

#endif // AudioSession_AVAudioSessionTypes_h
#else
#include <AudioSession/AVAudioSessionTypes.h>
#endif
