#if (defined(USE_AVFAUDIO_PUBLIC_HEADERS) && USE_AVFAUDIO_PUBLIC_HEADERS) || !__has_include(<AudioSession/AVAudioSessionTypes.h>)
/*!
	@file		AVAudioSessionTypes.h
	@framework	AudioSession.framework
	@copyright	(c) 2009-2020 Apple Inc. All rights reserved.
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
OS_EXPORT AVAudioSessionCategory const AVAudioSessionCategoryAudioProcessing API_DEPRECATED("No longer supported", ios(3.0, 10.0)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(macos);

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
 signal processing.  Has the side effect of setting AVAudioSessionCategoryOptionAllowBluetooth */
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
 processing for input and/or output audio signals. */
OS_EXPORT AVAudioSessionMode const AVAudioSessionModeMeasurement API_AVAILABLE(ios(5.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*! Engages appropriate output signal processing for movie playback scenarios.  Currently
 only applied during playback over built-in speaker. */
OS_EXPORT AVAudioSessionMode const AVAudioSessionModeMoviePlayback API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*! Only valid with kAudioSessionCategory_PlayAndRecord. Reduces the number of allowable audio
 routes to be only those that are appropriate for video chat applications. May engage appropriate
 system-supplied signal processing.  Has the side effect of setting
 AVAudioSessionCategoryOptionAllowBluetooth and AVAudioSessionCategoryOptionDefaultToSpeaker. */
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

/*!
    @enum        AVAudioSessionCategoryOptions
    @brief        Customization of various aspects of a category's behavior. Use with
                setCategory:mode:options:error:.

    Applications must be prepared for changing category options to fail as behavior may change
    in future releases. If an application changes its category, it should reassert the options,
    since they are not sticky across category changes. Introduced in iOS 6.0 / watchOS 2.0 /
    tvOS 9.0.

    @var AVAudioSessionCategoryOptionMixWithOthers
        Controls whether other active audio apps will be interrupted or mixed with when your app's
        audio session goes active. Details depend on the category.

        AVAudioSessionCategoryPlayAndRecord or AVAudioSessionCategoryMultiRoute:
             MixWithOthers defaults to false, but can be set to true, allowing other applications to
             play in the background while your app has both audio input and output enabled.

        AVAudioSessionCategoryPlayback:
             MixWithOthers defaults to false, but can be set to true, allowing other applications to
             play in the background. Your app will still be able to play regardless of the setting
             of the ringer switch.

        Other categories:
             MixWithOthers defaults to false and cannot be changed.

        MixWithOthers is only valid with AVAudioSessionCategoryPlayAndRecord,
        AVAudioSessionCategoryPlayback, and AVAudioSessionCategoryMultiRoute.

    @var AVAudioSessionCategoryOptionDuckOthers
        Controls whether or not other active audio apps will be ducked when when your app's audio
        session goes active. An example of this is a workout app, which provides periodic updates to
        the user. It reduces the volume of any music currently being played while it provides its
        status.

        Defaults to off. Note that the other audio will be ducked for as long as the current session
        is active. You will need to deactivate your audio session when you want to restore full
        volume playback (un-duck) other sessions.

        Setting this option will also make your session mixable with others
        (AVAudioSessionCategoryOptionMixWithOthers will be set).

        DuckOthers is only valid with AVAudioSessionCategoryAmbient,
        AVAudioSessionCategoryPlayAndRecord, AVAudioSessionCategoryPlayback, and
        AVAudioSessionCategoryMultiRoute.

    @var AVAudioSessionCategoryOptionAllowBluetooth
        Allows an application to change the default behavior of some audio session categories with
        regard to whether Bluetooth Hands-Free Profile (HFP) devices are available for routing. The
        exact behavior depends on the category.

        AVAudioSessionCategoryPlayAndRecord:
            AllowBluetooth defaults to false, but can be set to true, allowing a paired bluetooth
            HFP device to appear as an available route for input, while playing through the
            category-appropriate output.

        AVAudioSessionCategoryRecord:
            AllowBluetooth defaults to false, but can be set to true, allowing a paired Bluetooth
            HFP device to appear as an available route for input

        Other categories:
            AllowBluetooth defaults to false and cannot be changed. Enabling Bluetooth for input in
            these categories is not allowed.

    @var AVAudioSessionCategoryOptionDefaultToSpeaker
        Allows an application to change the default behavior of some audio session categories with
        regard to the audio route. The exact behavior depends on the category.

        AVAudioSessionCategoryPlayAndRecord:
            DefaultToSpeaker will default to false, but can be set to true, routing to Speaker
            (instead of Receiver) when no other audio route is connected.

        Other categories:
            DefaultToSpeaker is always false and cannot be changed.

    @var AVAudioSessionCategoryOptionInterruptSpokenAudioAndMixWithOthers
        When a session with InterruptSpokenAudioAndMixWithOthers set goes active, then if there is
        another playing app whose session mode is AVAudioSessionModeSpokenAudio (for podcast
        playback in the background, for example), then the spoken-audio session will be
        interrupted. A good use of this is for a navigation app that provides prompts to its user:
        it pauses any spoken audio currently being played while it plays the prompt.

        InterruptSpokenAudioAndMixWithOthers defaults to off. Note that the other app's audio will
        be paused for as long as the current session is active. You will need to deactivate your
        audio session to allow the other session to resume playback. Setting this option will also
        make your category mixable with others (AVAudioSessionCategoryOptionMixWithOthers will be
        set). If you want other non-spoken audio apps to duck their audio when your app's session
        goes active, also set AVAudioSessionCategoryOptionDuckOthers.

        Only valid with AVAudioSessionCategoryPlayAndRecord, AVAudioSessionCategoryPlayback, and
        AVAudioSessionCategoryMultiRoute. Introduced in iOS 9.0 / watchOS 2.0 / tvOS 9.0.

    @var AVAudioSessionCategoryOptionAllowBluetoothA2DP
        Allows an application to change the default behavior of some audio session categories with
        regard to whether Bluetooth Advanced Audio Distribution Profile (A2DP) devices are
        available for routing. The exact behavior depends on the category.

        AVAudioSessionCategoryPlayAndRecord:
            AllowBluetoothA2DP defaults to false, but can be set to true, allowing a paired
            Bluetooth A2DP device to appear as an available route for output, while recording
            through the category-appropriate input.

        AVAudioSessionCategoryMultiRoute and AVAudioSessionCategoryRecord:
            AllowBluetoothA2DP is false, and cannot be set to true.

        Other categories:
            AllowBluetoothA2DP is always implicitly true and cannot be changed; Bluetooth A2DP ports
            are always supported in output-only categories.

        Setting both AVAudioSessionCategoryOptionAllowBluetooth and
        AVAudioSessionCategoryOptionAllowBluetoothA2DP is allowed. In cases where a single
        Bluetooth device supports both HFP and A2DP, the HFP ports will be given a higher priority
        for routing. For HFP and A2DP ports on separate hardware devices, the last-in wins rule
        applies.

        Introduced in iOS 10.0 / watchOS 3.0 / tvOS 10.0.

    @var AVAudioSessionCategoryOptionAllowAirPlay
        Allows an application to change the default behavior of some audio session categories with
        with regard to showing AirPlay devices as available routes. This option applies to
        various categories in the same way as AVAudioSessionCategoryOptionAllowBluetoothA2DP;
        see above for details.

        Only valid with AVAudioSessionCategoryPlayAndRecord. Introduced in iOS 10.0 / tvOS 10.0.

    @var AVAudioSessionCategoryOptionOverrideMutedMicrophoneInterruption
        Some devices include a privacy feature that mutes the built-in microphone at a hardware level
        under certain conditions e.g. when the Smart Folio of an iPad is closed. The default behavior is
        to interrupt the session using the built-in microphone when that microphone is muted in hardware.
        This option allows an application to opt out of the default behavior if it is using a category that
        supports both input and output, such as AVAudioSessionCategoryPlayAndRecord, and wants to
        allow its session to stay activated even when the microphone has been muted. The result would be
        that playback continues as normal, and microphone sample buffers would continue to be produced
        but all microphone samples would have a value of zero.

        This may be useful if an application knows that it wants to allow playback to continue and
        recording/monitoring a muted microphone will not lead to a poor user experience. Attempting to use
        this option with a session category that doesn't support the use of audio input will result in an error.

        Note that under the default policy, a session will be interrupted if it is running input at the time when
        the microphone is muted in hardware. Similarly, attempting to start input when the microphone is
        muted will fail.
        Note that this option has no relation to the recordPermission property, which indicates whether or
        not the user has granted permission to use microphone input.
*/
typedef NS_OPTIONS(NSUInteger, AVAudioSessionCategoryOptions) {
    AVAudioSessionCategoryOptionMixWithOthers            = 0x1,
    AVAudioSessionCategoryOptionDuckOthers               = 0x2,
    AVAudioSessionCategoryOptionAllowBluetooth API_UNAVAILABLE(tvos, watchos, macos) = 0x4,
    AVAudioSessionCategoryOptionDefaultToSpeaker API_UNAVAILABLE(tvos, watchos, macos) = 0x8,
    AVAudioSessionCategoryOptionInterruptSpokenAudioAndMixWithOthers API_AVAILABLE(ios(9.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos) = 0x11,
    AVAudioSessionCategoryOptionAllowBluetoothA2DP API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos) = 0x20,
    AVAudioSessionCategoryOptionAllowAirPlay API_AVAILABLE(ios(10.0), tvos(10.0)) API_UNAVAILABLE(watchos, macos) = 0x40,
    AVAudioSessionCategoryOptionOverrideMutedMicrophoneInterruption API_AVAILABLE(ios(14.5), watchos(7.3)) API_UNAVAILABLE(tvos, macos) = 0x80,
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

        Starting in iOS 10, the system will deactivate the audio session of most apps in response to the
        app process being suspended. When the app starts running again, it will receive the notification
        that its session has been deactivated by the system. Note that the notification is necessarily
        delayed in time, due to the fact that the application was suspended at the time the session was
        deactivated by the system and the notification can only be delivered once the app is running
        again.

    @var   AVAudioSessionInterruptionReasonBuiltInMicMuted
        The audio session was interrupted due to the built-in mic being muted e.g. due to an iPad's Smart Folio being closed.

 */
typedef NS_ENUM(NSUInteger, AVAudioSessionInterruptionReason) {
    AVAudioSessionInterruptionReasonDefault         = 0,
    AVAudioSessionInterruptionReasonAppWasSuspended = 1,
    AVAudioSessionInterruptionReasonBuiltInMicMuted = 2
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
	AVAudioSessionRecordPermissionUndetermined = 'undt',
	AVAudioSessionRecordPermissionDenied = 'deny',
	AVAudioSessionRecordPermissionGranted = 'grnt'
};

#endif // AudioSession_AVAudioSessionTypes_h
#else
#include <AudioSession/AVAudioSessionTypes.h>
#endif
