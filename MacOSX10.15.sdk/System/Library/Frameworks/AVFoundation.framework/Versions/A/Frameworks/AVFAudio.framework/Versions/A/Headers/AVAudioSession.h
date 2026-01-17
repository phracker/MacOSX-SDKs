/*
	File:  AVAudioSession.h
	
	Framework:  AVFoundation
	
	Copyright © 2009-2018 Apple Inc. All rights reserved.
*/

#ifdef __OBJC2__

#import <Foundation/NSArray.h>
#import <Foundation/NSDate.h> /* for NSTimeInterval */
#import <Foundation/NSObject.h>
#import <CoreAudio/CoreAudioTypes.h>
#import <CoreAudioTypes/AudioSessionTypes.h>
#import <os/availability.h>
#import <os/base.h>

NS_ASSUME_NONNULL_BEGIN

/* This protocol is available with iPhone 3.0 or later */
@protocol AVAudioSessionDelegate;
@class NSError, NSString, NSNumber;
@class AVAudioSessionChannelDescription, AVAudioSessionPortDescription, AVAudioSessionRouteDescription, AVAudioSessionDataSourceDescription;

/*
 Notes on terminology used in this API.
 Some of the property names and class names in AVAudioSession differ from
 the names used in the 'C' language Audio Session API.  In this API, an audio
 "route" is made up of zero or more input "ports" and zero or more ouput "ports".
 If the current audio category does not support inputs, the route will consist purely of
 outputs.  Conversely, if the category does not support output, the route will
 consist purely of inputs.  Categories that support simultaneous input and output
 will have both inputs and outputs in the route.

 A "port" refers to a single input or output within an audio route.  Examples of
 ports include built-in speaker, wired microphone, or Bluetooth A2DP output.
*/

#pragma mark -- enumerations --

/* Category property */
typedef NSString *AVAudioSessionCategory NS_TYPED_ENUM;

/* Mode property */
typedef NSString *AVAudioSessionMode NS_TYPED_ENUM;

/* AVAudioSessionPort */
typedef NSString *AVAudioSessionPort NS_TYPED_ENUM;

/* AVAudioSessionLocation */
typedef NSString *AVAudioSessionLocation NS_TYPED_ENUM;

/* AVAudioSessionOrientation */
typedef NSString *AVAudioSessionOrientation NS_TYPED_ENUM;

/* AVAudioSessionPolarPattern */
typedef NSString *AVAudioSessionPolarPattern NS_TYPED_ENUM;

/* For use with AVAudioSessionInterruptionNotification */
typedef NS_OPTIONS(NSUInteger, AVAudioSessionInterruptionOptions)
{
	AVAudioSessionInterruptionOptionShouldResume = 1
};

/*  options for use when calling setActive:withOptions:error: 
AVAudioSessionSetActiveOptionNotifyOthersOnDeactivation -- 
Notify an interrupted app that the interruption has ended and it may resume playback. Only valid on 
session deactivation. */
typedef NS_OPTIONS(NSUInteger, AVAudioSessionSetActiveOptions)
{
	AVAudioSessionSetActiveOptionNotifyOthersOnDeactivation = 1
};

/*!
 @enum AVAudioSessionActivationOptions values
 @abstract   For use with -activateWithOptions:completionHandler:.
 @discussion Reserved for future use.
 Added in watchOS 5.0.
 */
typedef NS_OPTIONS(NSUInteger, AVAudioSessionActivationOptions)
{
	AVAudioSessionActivationOptionNone	= 0
};

/* values to use for setting overrideOutputAudioPort property
AVAudioSessionPortOverrideNone -- 
No override.  Return audio routing to the default state for the current audio category.
AVAudioSessionPortOverrideSpeaker -- 
Route audio output to speaker.  Use this override with AVAudioSessionCategoryPlayAndRecord, which by 
default routes the output to the receiver. */
typedef NS_ENUM(NSUInteger, AVAudioSessionPortOverride)
{
	AVAudioSessionPortOverrideNone = 0,
	AVAudioSessionPortOverrideSpeaker API_UNAVAILABLE(tvos, watchos, macos) = 'spkr'
};

/* values for AVAudioSessionRouteChangeReasonKey in AVAudioSessionRouteChangeNotification userInfo dictionary
 AVAudioSessionRouteChangeReasonUnknown
	The reason is unknown.
 AVAudioSessionRouteChangeReasonNewDeviceAvailable
	A new device became available (e.g. headphones have been plugged in).
 AVAudioSessionRouteChangeReasonOldDeviceUnavailable
	The old device became unavailable (e.g. headphones have been unplugged).
 AVAudioSessionRouteChangeReasonCategoryChange
	The audio category has changed (e.g. AVAudioSessionCategoryPlayback has been changed to AVAudioSessionCategoryPlayAndRecord).
 AVAudioSessionRouteChangeReasonOverride
	The route has been overridden (e.g. category is AVAudioSessionCategoryPlayAndRecord and the output 
	has been changed from the receiver, which is the default, to the speaker).
 AVAudioSessionRouteChangeReasonWakeFromSleep
	The device woke from sleep.
 AVAudioSessionRouteChangeReasonNoSuitableRouteForCategory
	Returned when there is no route for the current category (for instance, the category is AVAudioSessionCategoryRecord
	but no input device is available).
 AVAudioSessionRouteChangeReasonRouteConfigurationChange
	Indicates that the set of input and/our output ports has not changed, but some aspect of their
	configuration has changed.  For example, a port's selected data source has changed.
*/
typedef NS_ENUM(NSUInteger, AVAudioSessionRouteChangeReason)
{
	AVAudioSessionRouteChangeReasonUnknown = 0,
	AVAudioSessionRouteChangeReasonNewDeviceAvailable = 1,
	AVAudioSessionRouteChangeReasonOldDeviceUnavailable = 2,
	AVAudioSessionRouteChangeReasonCategoryChange = 3,
	AVAudioSessionRouteChangeReasonOverride = 4,
	AVAudioSessionRouteChangeReasonWakeFromSleep = 6,
	AVAudioSessionRouteChangeReasonNoSuitableRouteForCategory = 7,
	AVAudioSessionRouteChangeReasonRouteConfigurationChange = 8 // added in iOS 7
};

/* values for setCategory:withOptions:error:
AVAudioSessionCategoryOptionMixWithOthers -- 
	This allows an application to set whether or not other active audio apps will be interrupted or mixed with
	when your app's audio session goes active. The typical cases are:
	 (1) AVAudioSessionCategoryPlayAndRecord or AVAudioSessionCategoryMultiRoute
		 this will default to false, but can be set to true. This would allow other applications to play in the background
		 while an app had both audio input and output enabled
	 (2) AVAudioSessionCategoryPlayback
		 this will default to false, but can be set to true. This would allow other applications to play in the background,
		 but an app will still be able to play regardless of the setting of the ringer switch
	 (3) Other categories
		 this defaults to false and cannot be changed (that is, the mix with others setting of these categories
		 cannot be overridden. An application must be prepared for setting this property to fail as behaviour 
		 may change in future releases. If an application changes their category, they should reassert the 
		 option (it is not sticky across category changes).
 
AVAudioSessionCategoryOptionDuckOthers -- 
	This allows an application to set whether or not other active audio apps will be ducked when when your app's audio
	session goes active. An example of this is the Nike app, which provides periodic updates to its user (it reduces the
	volume of any music currently being played while it provides its status). This defaults to off. Note that the other
	audio will be ducked for as long as the current session is active. You will need to deactivate your audio
	session when you want full volume playback of the other audio. 
    If your category is AVAudioSessionCategoryPlayback, AVAudioSessionCategoryPlayAndRecord, or 
	AVAudioSessionCategoryMultiRoute, by default the audio session will be non-mixable and non-ducking. 
	Setting this option will also make your category mixable with others (AVAudioSessionCategoryOptionMixWithOthers
	will be set).
 
AVAudioSessionCategoryOptionAllowBluetooth --
	This allows an application to change the default behaviour of some audio session categories with regards to showing
	bluetooth Hands-Free Profile (HFP) devices as available routes. The current category behavior is:
	 (1) AVAudioSessionCategoryPlayAndRecord
		 this will default to false, but can be set to true. This will allow a paired bluetooth HFP device to show up as
		 an available route for input, while playing through the category-appropriate output
	 (2) AVAudioSessionCategoryRecord
		 this will default to false, but can be set to true. This will allow a paired bluetooth HFP device to show up
		 as an available route for input
	 (3) Other categories
		 this defaults to false and cannot be changed (that is, enabling bluetooth for input in these categories is
		 not allowed)
		 An application must be prepared for setting this option to fail as behaviour may change in future releases.
		 If an application changes their category or mode, they should reassert the override (it is not sticky
		 across category and mode changes).
 
AVAudioSessionCategoryOptionDefaultToSpeaker --
	This allows an application to change the default behaviour of some audio session categories with regards to
	the audio route. The current category behavior is:
	 (1) AVAudioSessionCategoryPlayAndRecord category
		 this will default to false, but can be set to true. this will route to Speaker (instead of Receiver)
		 when no other audio route is connected.
	 (2) Other categories
		 this defaults to false and cannot be changed (that is, the default to speaker setting of these
		 categories cannot be overridden
		 An application must be prepared for setting this property to fail as behaviour may change in future releases.
		 If an application changes their category, they should reassert the override (it is not sticky across
		 category and mode changes). 
 
AVAudioSessionCategoryOptionInterruptSpokenAudioAndMixWithOthers --
	If another app's audio session mode is set to AVAudioSessionModeSpokenAudio (podcast playback in the background for example),
	then that other app's audio will be interrupted when the current application's audio session goes active. An example of this
	is a navigation app that provides navigation prompts to its user (it pauses any spoken audio currently being played while it
	plays the prompt). This defaults to off. Note that the other app's audio will be paused for as long as the current session is
	active. You will need to deactivate your audio session to allow the other audio to resume playback.
	Setting this option will also make your category mixable with others (AVAudioSessionCategoryOptionMixWithOthers
	will be set).  If you want other non-spoken audio apps to duck their audio when your app's session goes active, also set
	AVAudioSessionCategoryOptionDuckOthers.
 
AVAudioSessionCategoryOptionAllowBluetoothA2DP --
    This allows an application to change the default behaviour of some audio session categories with regards to showing
	bluetooth Advanced Audio Distribution Profile (A2DP), i.e. stereo Bluetooth, devices as available routes. The current 
	category behavior is:
    (1) AVAudioSessionCategoryPlayAndRecord
    this will default to false, but can be set to true. This will allow a paired bluetooth A2DP device to show up as
    an available route for output, while recording through the category-appropriate input
    (2) AVAudioSessionCategoryMultiRoute and AVAudioSessionCategoryRecord
    this will default to false, and cannot be set to true.
    (3) Other categories
    this defaults to true and cannot be changed (that is, bluetooth A2DP ports are always supported in output-only categories).
    An application must be prepared for setting this option to fail as behaviour may change in future releases.
    If an application changes their category or mode, they should reassert the override (it is not sticky
    across category and mode changes).
	Setting both AVAudioSessionCategoryOptionAllowBluetooth and AVAudioSessionCategoryOptionAllowBluetoothA2DP is allowed. In cases
	where a single Bluetooth device supports both HFP and A2DP, the HFP ports will be given a higher priority for routing. For HFP 
	and A2DP ports on separate hardware devices, the last-in wins rule applies.

 AVAudioSessionCategoryOptionAllowAirPlay --
    This allows an application to change the default behaviour of some audio session categories with regards to showing
	AirPlay devices as available routes. See the documentation of AVAudioSessionCategoryOptionAllowBluetoothA2DP for details on 
    how this option applies to specific categories.
 
 */
typedef NS_OPTIONS(NSUInteger, AVAudioSessionCategoryOptions)
{
	/* MixWithOthers is only valid with AVAudioSessionCategoryPlayAndRecord, AVAudioSessionCategoryPlayback, and  AVAudioSessionCategoryMultiRoute */
	AVAudioSessionCategoryOptionMixWithOthers			= 0x1,
	/* DuckOthers is only valid with AVAudioSessionCategoryAmbient, AVAudioSessionCategoryPlayAndRecord, AVAudioSessionCategoryPlayback, and AVAudioSessionCategoryMultiRoute */
	AVAudioSessionCategoryOptionDuckOthers				= 0x2,
	/* AllowBluetooth is only valid with AVAudioSessionCategoryRecord and AVAudioSessionCategoryPlayAndRecord */
	AVAudioSessionCategoryOptionAllowBluetooth	API_UNAVAILABLE(tvos, watchos, macos) = 0x4,
	/* DefaultToSpeaker is only valid with AVAudioSessionCategoryPlayAndRecord */
	AVAudioSessionCategoryOptionDefaultToSpeaker API_UNAVAILABLE(tvos, watchos, macos) = 0x8,
	/* InterruptSpokenAudioAndMixWithOthers is only valid with AVAudioSessionCategoryPlayAndRecord, AVAudioSessionCategoryPlayback, and AVAudioSessionCategoryMultiRoute */
	AVAudioSessionCategoryOptionInterruptSpokenAudioAndMixWithOthers API_AVAILABLE(ios(9.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos)  = 0x11,
	/* AllowBluetoothA2DP is only valid with AVAudioSessionCategoryPlayAndRecord */
	AVAudioSessionCategoryOptionAllowBluetoothA2DP API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos) = 0x20,
	/* AllowAirPlay is only valid with AVAudioSessionCategoryPlayAndRecord */
	AVAudioSessionCategoryOptionAllowAirPlay API_AVAILABLE(ios(10.0), tvos(10.0)) API_UNAVAILABLE(watchos, macos) = 0x40,
};

typedef NS_ENUM(NSUInteger, AVAudioSessionInterruptionType)
{
	AVAudioSessionInterruptionTypeBegan = 1,  /* the system has interrupted your audio session */
	AVAudioSessionInterruptionTypeEnded = 0,  /* the interruption has ended */
};

/* Used in AVAudioSessionSilenceSecondaryAudioHintNotification to indicate whether optional secondary audio muting should begin or end */
typedef NS_ENUM(NSUInteger, AVAudioSessionSilenceSecondaryAudioHintType)
{
	AVAudioSessionSilenceSecondaryAudioHintTypeBegin = 1,  /* the system is indicating that another application's primary audio has started */
	AVAudioSessionSilenceSecondaryAudioHintTypeEnd = 0,    /* the system is indicating that another application's primary audio has stopped */
};

/*!
	@enum AVAudioSessionRecordPermission values
	@abstract   These are the values returned by recordPermission.
	@constant   AVAudioSessionRecordPermissionUndetermined
		The user has not yet been asked for permission.
	@constant   AVAudioSessionRecordPermissionDenied
 		The user has been asked and has denied permission.
	@constant   AVAudioSessionRecordPermissionGranted
 		The user has been asked and has granted permission.

 	Added in iOS 8.0, watchos 4.0.
*/
typedef NS_ENUM(NSUInteger, AVAudioSessionRecordPermission)
{
	AVAudioSessionRecordPermissionUndetermined		= 'undt',
	AVAudioSessionRecordPermissionDenied			= 'deny',
	AVAudioSessionRecordPermissionGranted			= 'grnt'
};

/*
 @enum AVAudioSessionIOType values
	@abstract   Values to be used by setAggregatedIOPreference:error: method.
	@discussion Starting in iOS 10, applications that use AVCaptureSession on iPads and iPhones that
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

	@constant   AVAudioSessionIOTypeNotSpecified
		The default value.  If your app does not use AVCaptureSession or does not have any specific 
		requirement for aggregating input and output audio in the same realtime I/O callback, use this 
		value. Note that if your app does not use AVCaptureSession, it will get aggregated I/O when using 
		AVAudioSessionCategoryPlayAndRecord.

		If your app does utilize AVCaptureSession, use of this value will allow AVCaptureSession to 
		start recording without glitching already running output audio and will allow the system to
		utilize power-saving optimizations.

	@constant	AVAudioSessionIOTypeAggregated
		Use this value if your session uses AVAudioSessionCategoryPlayAndRecord and requires input and
		output audio to be presented in the same realtime I/O callback. For example, if your app will be using
		a RemoteIO with both input and output enabled. 

		Note that your session's preference to use aggregated IO will not be honored if it specifies 
		AVAudioSessionCategoryOptionMixWithOthers AND another app's audio session was already active 
		with non-mixable, non-aggregated input/output.
	
	Added in iOS 10.0. Not applicable on watchos, tvos, macos.
*/
typedef NS_ENUM(NSUInteger, AVAudioSessionIOType)
{
	AVAudioSessionIOTypeNotSpecified = 0,
	AVAudioSessionIOTypeAggregated = 1
};

/*!
	@enum		AVAudioSessionRouteSharingPolicy
	@abstract   Starting in iOS 11, tvOS 11, and watchOS 5, the route sharing policy allows a session
		to specify that its output audio should be routed somewhere other than the default system output,
		when appropriate alternative routes are available.
	@constant	AVAudioSessionRouteSharingPolicyDefault
		Follow normal rules for routing audio output.
	@constant	AVAudioSessionRouteSharingPolicyLongFormAudio
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
	@constant	AVAudioSessionRouteSharingPolicyLongForm
		Deprecated. Replaced by AVAudioSessionRouteSharingPolicyLongFormAudio.
	@constant	AVAudioSessionRouteSharingPolicyIndependent
		Applications should not attempt to set this value directly. On iOS, this value will be set by
		the system in cases where route picker UI is used to direct video to a wireless route.
	@constant	AVAudioSessionRouteSharingPolicyLongFormVideo
		Route output to the shared long-form video output. A session whose primary use case is as a
		movie or other long-form video content player may use this value to play to the same output as
		other long-form video content applications such as the built-in TV (iOS) application. Applications
		that use this policy will also want to also set the AVInitialRouteSharingPolicy key
		in their Info.plist to "LongFormVideo". All applications on the system that use the long-form video
		route sharing policy will have their audio and video routed to the same location (e.g. AppleTV when
		an AirPlay route is selected). Video content not using this route sharing policy will remain local
		to the playback device even when long form video content is being routed to AirPlay.
*/
typedef NS_ENUM(NSUInteger, AVAudioSessionRouteSharingPolicy)
{
	AVAudioSessionRouteSharingPolicyDefault = 0,
	AVAudioSessionRouteSharingPolicyLongFormAudio = 1,
	AVAudioSessionRouteSharingPolicyLongForm API_DEPRECATED_WITH_REPLACEMENT("AVAudioSessionRouteSharingPolicyLongFormAudio", ios(11.0, 13.0), watchos(4.0, 6.0), tvos(11.0, 13.0)) API_UNAVAILABLE(macos) = AVAudioSessionRouteSharingPolicyLongFormAudio,
	AVAudioSessionRouteSharingPolicyIndependent = 2,
	AVAudioSessionRouteSharingPolicyLongFormVideo API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos, macos) = 3,
};


/*!
 @enum AVAudioSessionPromptStyle values
 @abstract
 The prompt style is a hint to sessions that use AVAudioSessionModeVoicePrompt to modify the type of
 prompt they play in response to other audio activity on the system, such as Siri or phone calls.
 Sessions that issue voice prompts are encouraged to pay attention to changes in the prompt style and
 modify their prompts in response. Apple encourages the use of non-verbal prompts when the Short
 style is requested.
 @constant AVAudioSessionPromptStyleNone
 Indicates that another session is actively using microphone input and would be negatively impacted
 by having prompts play at that time. For example if Siri is recognizing speech, having navigation or
 exercise prompts play, could interfere with its ability to accurately recognize the user’s speech.
 Client sessions should refrain from playing any prompts while the prompt style is None.
 @constant AVAudioSessionPromptStyleShort
 Indicates one of three states: Siri is active but not recording, voicemail playback is active, or
 voice call is active. Short, non-verbal versions of prompts should be used.
 @constant AVAudioSessionPromptStyleNormal
 Indicates that normal (long, verbal) versions of prompts may be used.
 */
typedef NS_ENUM(NSUInteger, AVAudioSessionPromptStyle)
{
    AVAudioSessionPromptStyleNone = 'none',
    AVAudioSessionPromptStyleShort = 'shrt',
    AVAudioSessionPromptStyleNormal = 'nrml',
};

#pragma mark -- AVAudioSession interface --
API_AVAILABLE(ios(3.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos) 
@interface AVAudioSession : NSObject {
@private
	void *_impl;
}

/* returns singleton instance */
+ (AVAudioSession *)sharedInstance API_AVAILABLE(ios(3.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Set the session active or inactive. Note that activating an audio session is a synchronous (blocking) operation.
 Therefore, we recommend that applications not activate their session from a thread where a long blocking operation will be problematic.
 When deactivating a session, the caller is required to first stop or pause all running I/Os (e.g. audio queues, players, recorders,
 converters, remote I/Os, etc.). Starting in iOS 8, if the session has running IOs at the time that deactivation is requested,
 the session will be deactivated, but the method will return NO and populate the NSError with the code property set to AVAudioSessionErrorCodeIsBusy
 to indicate the misuse of the API. Prior to iOS 8, the session would have remained active if it had running IOs at the time of the
 deactivation request.
*/
- (BOOL)setActive:(BOOL)active error:(NSError **)outError API_AVAILABLE(ios(3.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);
- (BOOL)setActive:(BOOL)active withOptions:(AVAudioSessionSetActiveOptions)options error:(NSError **)outError API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Asynchronously activate the session. This is relatively time consuming operation. The completion handler will be called when the activation completes or
 if an error occurs while attempting to activate the session. If the session is configured to use AVAudioSessionRouteSharingPolicyLongFormAudio on watchOS, this method
 will also cause a route picker to be presented to the user in cases where an appropriate output route has not already been selected automatically.
 watchOS apps using AVAudioSessionRouteSharingPolicyLongFormAudio should be prepared for this method to fail if no eligible audio route can be activated or if the user
 cancels the route picker view.
 */
- (void)activateWithOptions:(AVAudioSessionActivationOptions)options completionHandler:(void (^)(BOOL activated, NSError * _Nullable error))handler API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios, tvos) API_UNAVAILABLE(macos, macCatalyst);

// Get the list of categories available on the device.  Certain categories may be unavailable on particular devices.  For example,
// AVAudioSessionCategoryRecord will not be available on devices that have no support for audio input.
@property (readonly) NSArray<AVAudioSessionCategory> *availableCategories API_AVAILABLE(ios(9.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* set session category */
- (BOOL)setCategory:(AVAudioSessionCategory)category error:(NSError **)outError API_AVAILABLE(ios(3.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);
/* set session category with options */
- (BOOL)setCategory:(AVAudioSessionCategory)category withOptions:(AVAudioSessionCategoryOptions)options error:(NSError **)outError API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);
/* set session category and mode with options */
- (BOOL)setCategory:(AVAudioSessionCategory)category mode:(AVAudioSessionMode)mode options:(AVAudioSessionCategoryOptions)options error:(NSError **)outError API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/* set session category, mode, routing sharing policy, and options 
 Use of the long-form route sharing policy is only valid in conjunction with a limited set of category, mode, and option values.
 Allowed categories: AVAudioSessionCategoryPlayback
 Allowed modes: AVAudioSessionModeDefault, AVAudioSessionModeMoviePlayback, AVAudioSessionModeSpokenAudio
 Allowed options: None. Options are allowed when changing the routing policy back to Default, however. */
- (BOOL)setCategory:(AVAudioSessionCategory)category mode:(AVAudioSessionMode)mode routeSharingPolicy:(AVAudioSessionRouteSharingPolicy)policy options:(AVAudioSessionCategoryOptions)options error:(NSError **)outError API_AVAILABLE(ios(11.0), tvos(11.0), watchos(5.0)) API_UNAVAILABLE(macos);

/* get session category. Examples: AVAudioSessionCategoryRecord, AVAudioSessionCategoryPlayAndRecord, etc. */
@property (readonly) AVAudioSessionCategory category API_AVAILABLE(ios(3.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* get the current set of AVAudioSessionCategoryOptions */
@property (readonly) AVAudioSessionCategoryOptions categoryOptions API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Get the routing policy. See AVAudioSessionRouteSharingPolicy for a description of the available policies
 See -setCategory:mode:routeSharingPolicy:options:error: method for additional discussion. */
@property (readonly) AVAudioSessionRouteSharingPolicy routeSharingPolicy API_AVAILABLE(ios(11.0), tvos(11.0), watchos(5.0)) API_UNAVAILABLE(macos);

// Modes modify the audio category in order to introduce behavior that is tailored to the specific
// use of audio within an application. Examples:  AVAudioSessionModeVideoRecording, AVAudioSessionModeVoiceChat,
// AVAudioSessionModeMeasurement, etc.

// Get the list of modes available on the device.  Certain modes may be unavailable on particular devices.  For example,
// AVAudioSessionModeVideoRecording will not be available on devices that have no support for recording video.
@property (readonly) NSArray<AVAudioSessionMode> *availableModes API_AVAILABLE(ios(9.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

- (BOOL)setMode:(AVAudioSessionMode)mode error:(NSError **)outError API_AVAILABLE(ios(5.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos); /* set session mode */
@property (readonly) AVAudioSessionMode mode API_AVAILABLE(ios(5.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos); /* get session mode */

/* Returns an enum indicating whether the user has granted or denied permission to record, or has not been asked */
@property (readonly) AVAudioSessionRecordPermission recordPermission API_AVAILABLE(ios(8.0), watchos(4.0)) API_UNAVAILABLE(macos, tvos);

/* Checks to see if calling process has permission to record audio.  The 'response' block will be called
 immediately if permission has already been granted or denied.  Otherwise, it presents a dialog to notify
 the user and allow them to choose, and calls the block once the UI has been dismissed.  'granted'
 indicates whether permission has been granted. Note that the block may be called in a different thread context.
 */
typedef void (^PermissionBlock)(BOOL granted);

- (void)requestRecordPermission:(PermissionBlock)response API_AVAILABLE(ios(7.0), watchos(4.0)) API_UNAVAILABLE(macos, tvos);

- (BOOL)overrideOutputAudioPort:(AVAudioSessionPortOverride)portOverride error:(NSError **)outError API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Will be true when another application is playing audio.
Note: As of iOS 8.0, Apple recommends that most applications use secondaryAudioShouldBeSilencedHint instead of this property.
The otherAudioPlaying property will be true if any other audio (including audio from an app using AVAudioSessionCategoryAmbient)
is playing, whereas the secondaryAudioShouldBeSilencedHint property is more restrictive in its consideration of whether 
primary audio from another application is playing.  
For additional information, see https://developer.apple.com/library/content/qa/qa1882/_index.html
*/
@property (readonly, getter=isOtherAudioPlaying) BOOL otherAudioPlaying API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Will be true when another application with a non-mixable audio session is playing audio.  Applications may use
this property as a hint to silence audio that is secondary to the functionality of the application. For example, a game app
using AVAudioSessionCategoryAmbient may use this property to decide to mute its soundtrack while leaving its sound effects unmuted.
Note: This property is closely related to AVAudioSessionSilenceSecondaryAudioHintNotification.
*/
@property (readonly) BOOL secondaryAudioShouldBeSilencedHint API_AVAILABLE(ios(8.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* A description of the current route, consisting of zero or more input ports and zero or more output ports */
@property (readonly) AVAudioSessionRouteDescription *currentRoute API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Select a preferred input port for audio routing. If the input port is already part of the current audio route, this will have no effect.
   Otherwise, selecting an input port for routing will initiate a route change to use the preferred input port, provided that the application's
   session controls audio routing. Setting a nil value will clear the preference. */
- (BOOL)setPreferredInput:(nullable AVAudioSessionPortDescription *)inPort error:(NSError **)outError API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);
@property (readonly, nullable) AVAudioSessionPortDescription *preferredInput API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos); /* Get the preferred input port.  Will be nil if no preference has been set */

/* Get the set of input ports that are available for routing. Note that this property only applies to the session's current category and mode.
   For example, if the session's current category is AVAudioSessionCategoryPlayback, there will be no available inputs.  */
@property (readonly, nullable) NSArray<AVAudioSessionPortDescription *> *availableInputs API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* The prompt style is a hint to sessions using AVAudioSessionModeVoicePrompt to alter the type of prompts they issue in
 response to other audio activity on the system, such as Siri and phone calls. This property is key-value observable.
 */
@property(readonly) AVAudioSessionPromptStyle promptStyle API_AVAILABLE(ios(13.0), watchos(6.0), tvos(13.0)) API_UNAVAILABLE(macos);

// Set allowHapticsAndSystemSoundsDuringRecording to YES in order to allow system sounds and haptics to play while the session is actively using audio input.
// Default value is NO.
- (BOOL)setAllowHapticsAndSystemSoundsDuringRecording:(BOOL)inValue error:(NSError **)outError API_AVAILABLE(ios(13.0), watchos(6.0), tvos(13.0)) API_UNAVAILABLE(macos);

@property(readonly) BOOL allowHapticsAndSystemSoundsDuringRecording API_AVAILABLE(ios(13.0), watchos(6.0), tvos(13.0)) API_UNAVAILABLE(macos);

@end

/* AVAudioSessionHardwareConfiguration manages the set of properties that reflect the current state of
 audio hardware in the current route.  Applications whose functionality depends on these properties should
 reevaluate them any time the route changes. */
@interface AVAudioSession (AVAudioSessionHardwareConfiguration)

/* Get and set preferred values for hardware properties.  Note: that there are corresponding read-only
 properties that describe the actual values for sample rate, I/O buffer duration, etc. */

/* The preferred hardware sample rate for the session. The actual sample rate may be different. */
- (BOOL)setPreferredSampleRate:(double)sampleRate error:(NSError **)outError API_AVAILABLE(ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);
@property (readonly) double preferredSampleRate API_AVAILABLE(ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/* The preferred hardware IO buffer duration in seconds. The actual IO buffer duration may be different.  */
- (BOOL)setPreferredIOBufferDuration:(NSTimeInterval)duration error:(NSError **)outError API_AVAILABLE(ios(3.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);
@property (readonly) NSTimeInterval preferredIOBufferDuration API_AVAILABLE(ios(3.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/* Sets the number of input channels that the app would prefer for the current route */
- (BOOL)setPreferredInputNumberOfChannels:(NSInteger)count error:(NSError **)outError API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);
@property (readonly) NSInteger preferredInputNumberOfChannels API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/* Sets the number of output channels that the app would prefer for the current route */
- (BOOL)setPreferredOutputNumberOfChannels:(NSInteger)count error:(NSError **)outError API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);
@property (readonly) NSInteger preferredOutputNumberOfChannels API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/* Returns the largest number of audio input channels available for the current route */
@property (readonly) NSInteger maximumInputNumberOfChannels API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Returns the largest number of audio output channels available for the current route */
@property (readonly) NSInteger maximumOutputNumberOfChannels API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* A value defined over the range [0.0, 1.0], with 0.0 corresponding to the lowest analog
gain setting and 1.0 corresponding to the highest analog gain setting.  Attempting to set values
outside of the defined range will result in the value being "clamped" to a valid input.  This is
a global input gain setting that applies to the current input source for the entire system.
When no applications are using the input gain control, the system will restore the default input
gain setting for the input source.  Note that some audio accessories, such as USB devices, may
not have a default value.  This property is only valid if inputGainSettable
is true.  Note: inputGain is key-value observable */
- (BOOL)setInputGain:(float)gain error:(NSError **)outError API_AVAILABLE(ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);
@property (readonly) float inputGain API_AVAILABLE(ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos); /* value in range [0.0, 1.0] */

/* True when audio input gain is available.  Some input ports may not provide the ability to set the
input gain, so check this value before attempting to set input gain. */
@property (readonly, getter=isInputGainSettable) BOOL inputGainSettable API_AVAILABLE(ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/* True if input hardware is available. */
@property (readonly, getter=isInputAvailable) BOOL inputAvailable API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* DataSource methods are for use with routes that support input or output data source selection.
If the attached accessory supports data source selection, the data source properties/methods provide for discovery and 
selection of input and/or output data sources. Note that the properties and methods for data source selection below are
equivalent to the properties and methods on AVAudioSessionPortDescription. The methods below only apply to the currently 
routed ports. */

/* Key-value observable. */
@property (readonly, nullable) NSArray<AVAudioSessionDataSourceDescription *> *inputDataSources API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Get and set the currently selected data source.  Will be nil if no data sources are available.
Setting a nil value will clear the data source preference. */
@property (readonly, nullable) AVAudioSessionDataSourceDescription *inputDataSource API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);
- (BOOL)setInputDataSource:(nullable AVAudioSessionDataSourceDescription *)dataSource error:(NSError **)outError API_AVAILABLE(ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/* Key-value observable. */
@property (readonly, nullable) NSArray<AVAudioSessionDataSourceDescription *> *outputDataSources API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Get and set currently selected data source.  Will be nil if no data sources are available. 
Setting a nil value will clear the data source preference. */
@property (readonly, nullable) AVAudioSessionDataSourceDescription *outputDataSource API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);
- (BOOL)setOutputDataSource:(nullable AVAudioSessionDataSourceDescription *)dataSource error:(NSError **)outError API_AVAILABLE(ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/* Current values for hardware properties.  Note that most of these properties have corresponding methods 
for getting and setting preferred values.  Input- and output-specific properties will generate an error if they are 
queried if the audio session category does not support them.  Each of these will return 0 (or 0.0) if there is an error.  */

/* The current hardware sample rate */
@property (readonly) double sampleRate API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* The current number of hardware input channels. Is key-value observable */
@property (readonly) NSInteger inputNumberOfChannels API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* The current number of hardware output channels. Is key-value observable */
@property (readonly) NSInteger outputNumberOfChannels API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* The current output volume. Is key-value observable */
@property (readonly) float outputVolume API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos); /* value in range [0.0, 1.0] */

/* The current hardware input latency in seconds. */
@property (readonly) NSTimeInterval inputLatency API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* The current hardware output latency in seconds. */
@property (readonly) NSTimeInterval outputLatency API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* The current hardware IO buffer duration in seconds. */
@property (readonly) NSTimeInterval IOBufferDuration API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Set inIOType to AVAudioSessionIOTypeAggregated if your app uses AVAudioSessionCategoryPlayAndRecord
 and requires input and output audio to be presented in the same realtime I/O callback. See the AVAudioSessionIOType
 documentation for more details.
 */
- (BOOL)setAggregatedIOPreference:(AVAudioSessionIOType)inIOType error:(NSError **)outError API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(tvos, watchos, macos);

@end

#pragma mark -- Names for NSNotifications --

/* Registered listeners will be notified when the system has interrupted the audio session and when
 the interruption has ended.  Check the notification's userInfo dictionary for the interruption type -- either begin or end.
 In the case of an end interruption notification, check the userInfo dictionary for AVAudioSessionInterruptionOptions that
 indicate whether audio playback should resume.
 In cases where the interruption is a consequence of the application being suspended, the info dictionary will contain
 AVAudioSessionInterruptionWasSuspendedKey, with the boolean value set to true.
 */
extern NSNotificationName const AVAudioSessionInterruptionNotification API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Registered listeners will be notified when a route change has occurred.  Check the notification's userInfo dictionary for the
 route change reason and for a description of the previous audio route.
 */
extern NSNotificationName const AVAudioSessionRouteChangeNotification API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Registered listeners will be notified if the media server is killed.  In the event that the server is killed,
 take appropriate steps to handle requests that come in before the server resets.  See Technical Q&A QA1749.
 */
extern NSNotificationName const AVAudioSessionMediaServicesWereLostNotification API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Registered listeners will be notified when the media server restarts.  In the event that the server restarts,
 take appropriate steps to re-initialize any audio objects used by your application.  See Technical Q&A QA1749.
 */
extern NSNotificationName const AVAudioSessionMediaServicesWereResetNotification API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Registered listeners that are currently in the foreground and have active audio sessions will be notified 
 when primary audio from other applications starts and stops.  Check the notification's userInfo dictionary 
 for the notification type -- either begin or end.
 Foreground applications may use this notification as a hint to enable or disable audio that is secondary
 to the functionality of the application. For more information, see the related property secondaryAudioShouldBeSilencedHint.
*/
extern NSNotificationName const AVAudioSessionSilenceSecondaryAudioHintNotification API_AVAILABLE(ios(8.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

#pragma mark -- Keys for NSNotification userInfo dictionaries --

/* keys for AVAudioSessionInterruptionNotification */
/* Value is an NSNumber representing an AVAudioSessionInterruptionType */
extern NSString *const AVAudioSessionInterruptionTypeKey API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Only present for end interruption events.  Value is of type AVAudioSessionInterruptionOptions.*/
extern NSString *const AVAudioSessionInterruptionOptionKey API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Only present in begin interruption events, where the interruption is a direct result of the application being suspended
	by the operating sytem. Value is a boolean NSNumber, where a true value indicates that the interruption is the result
	of the application being suspended, rather than being interrupted by another audio session.
	
	Starting in iOS 10, the system will deactivate the audio session of most apps in response to the app process
	being suspended. When the app starts running again, it will receive the notification that its session has been deactivated
	by the system. Note that the notification is necessarily delayed in time, due to the fact that the application was suspended
	at the time the session was deactivated by the system and the notification can only be delivered once the app is running again. */
extern NSString *const AVAudioSessionInterruptionWasSuspendedKey API_AVAILABLE(ios(10.3), watchos(2.3), tvos(10.3)) API_UNAVAILABLE(macos);

/* keys for AVAudioSessionRouteChangeNotification */
/* value is an NSNumber representing an AVAudioSessionRouteChangeReason */
extern NSString *const AVAudioSessionRouteChangeReasonKey API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);
/* value is AVAudioSessionRouteDescription * */
extern NSString *const AVAudioSessionRouteChangePreviousRouteKey API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* keys for AVAudioSessionSilenceSecondaryAudioHintNotification */
/* value is an NSNumber representing an AVAudioSessionSilenceSecondaryAudioHintType */
extern NSString *const AVAudioSessionSilenceSecondaryAudioHintTypeKey API_AVAILABLE(ios(8.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

#pragma mark -- Values for the category property --

/*  Use this category for background sounds such as rain, car engine noise, etc.  
 Mixes with other music. */
extern AVAudioSessionCategory const AVAudioSessionCategoryAmbient API_AVAILABLE(ios(3.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*  Use this category for background sounds.  Other music will stop playing. */
extern AVAudioSessionCategory const AVAudioSessionCategorySoloAmbient API_AVAILABLE(ios(3.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Use this category for music tracks.*/
extern AVAudioSessionCategory const AVAudioSessionCategoryPlayback API_AVAILABLE(ios(3.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*  Use this category when recording audio. */
extern AVAudioSessionCategory const AVAudioSessionCategoryRecord API_AVAILABLE(ios(3.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*  Use this category when recording and playing back audio. */
extern AVAudioSessionCategory const AVAudioSessionCategoryPlayAndRecord API_AVAILABLE(ios(3.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/*  Use this category when using a hardware codec or signal processor while
 not playing or recording audio. */
extern AVAudioSessionCategory const AVAudioSessionCategoryAudioProcessing API_DEPRECATED("No longer supported", ios(3.0, 10.0)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(macos);

/*  Use this category to customize the usage of available audio accessories and built-in audio hardware.
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
extern AVAudioSessionCategory const AVAudioSessionCategoryMultiRoute API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

#pragma mark -- Values for the mode property --

/*!
@abstract      Modes modify the audio category in order to introduce behavior that is tailored to the specific
use of audio within an application.  Available in iOS 5.0 and greater.
 */

/* The default mode */
extern AVAudioSessionMode const AVAudioSessionModeDefault API_AVAILABLE(ios(5.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Only valid with AVAudioSessionCategoryPlayAndRecord.  Appropriate for Voice over IP
(VoIP) applications.  Reduces the number of allowable audio routes to be only those
that are appropriate for VoIP applications and may engage appropriate system-supplied
signal processing.  Has the side effect of setting AVAudioSessionCategoryOptionAllowBluetooth */
extern AVAudioSessionMode const AVAudioSessionModeVoiceChat API_AVAILABLE(ios(5.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Set by Game Kit on behalf of an application that uses a GKVoiceChat object; valid
 only with the AVAudioSessionCategoryPlayAndRecord category.
 Do not set this mode directly. If you need similar behavior and are not using
 a GKVoiceChat object, use AVAudioSessionModeVoiceChat instead. */
extern AVAudioSessionMode const AVAudioSessionModeGameChat API_AVAILABLE(ios(5.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Only valid with AVAudioSessionCategoryPlayAndRecord or AVAudioSessionCategoryRecord.
 Modifies the audio routing options and may engage appropriate system-supplied signal processing. */
extern AVAudioSessionMode const AVAudioSessionModeVideoRecording API_AVAILABLE(ios(5.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Appropriate for applications that wish to minimize the effect of system-supplied signal
processing for input and/or output audio signals. */
extern AVAudioSessionMode const AVAudioSessionModeMeasurement API_AVAILABLE(ios(5.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Engages appropriate output signal processing for movie playback scenarios.  Currently
only applied during playback over built-in speaker. */
extern AVAudioSessionMode const AVAudioSessionModeMoviePlayback API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Only valid with kAudioSessionCategory_PlayAndRecord. Reduces the number of allowable audio
routes to be only those that are appropriate for video chat applications. May engage appropriate
system-supplied signal processing.  Has the side effect of setting
AVAudioSessionCategoryOptionAllowBluetooth and AVAudioSessionCategoryOptionDefaultToSpeaker. */
extern AVAudioSessionMode const AVAudioSessionModeVideoChat API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Appropriate for applications which play spoken audio and wish to be paused (via audio session interruption) rather than ducked
if another app (such as a navigation app) plays a spoken audio prompt.  Examples of apps that would use this are podcast players and
audio books.  For more information, see the related category option AVAudioSessionCategoryOptionInterruptSpokenAudioAndMixWithOthers. */
extern AVAudioSessionMode const AVAudioSessionModeSpokenAudio API_AVAILABLE(ios(9.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Appropriate for applications which play audio using text to speech. Setting this mode allows for different routing behaviors when
connected to certain audio devices such as CarPlay. An example of an app that would use this mode is a turn by turn navigation app that
plays short prompts to the user. Typically, these same types of applications would also configure their session to use
AVAudioSessionCategoryOptionDuckOthers and AVAudioSessionCategoryOptionInterruptSpokenAudioAndMixWithOthers */
extern AVAudioSessionMode const AVAudioSessionModeVoicePrompt API_AVAILABLE(ios(12.0), watchos(5.0), tvos(12.0)) API_UNAVAILABLE(macos);

#pragma mark -- constants for port types --

/* input port types */
extern AVAudioSessionPort const AVAudioSessionPortLineIn       API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos); /* Line level input on a dock connector */
extern AVAudioSessionPort const AVAudioSessionPortBuiltInMic   API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos); /* Built-in microphone on an iOS device */
extern AVAudioSessionPort const AVAudioSessionPortHeadsetMic   API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos); /* Microphone on a wired headset.  Headset refers to an
																				   accessory that has headphone outputs paired with a
																				   microphone. */

/* output port types */
extern AVAudioSessionPort const AVAudioSessionPortLineOut          API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos); /* Line level output on a dock connector */
extern AVAudioSessionPort const AVAudioSessionPortHeadphones       API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos); /* Headphone or headset output */
extern AVAudioSessionPort const AVAudioSessionPortBluetoothA2DP    API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos); /* Output on a Bluetooth A2DP device */
extern AVAudioSessionPort const AVAudioSessionPortBuiltInReceiver  API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos); /* The speaker you hold to your ear when on a phone call */
extern AVAudioSessionPort const AVAudioSessionPortBuiltInSpeaker   API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos); /* Built-in speaker on an iOS device */
extern AVAudioSessionPort const AVAudioSessionPortHDMI             API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos); /* Output via High-Definition Multimedia Interface */
extern AVAudioSessionPort const AVAudioSessionPortAirPlay          API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos); /* Output on a remote Air Play device */
extern AVAudioSessionPort const AVAudioSessionPortBluetoothLE	  API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos); /* Output on a Bluetooth Low Energy device */

/* port types that refer to either input or output */
extern AVAudioSessionPort const AVAudioSessionPortBluetoothHFP API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos); /* Input or output on a Bluetooth Hands-Free Profile device */
extern AVAudioSessionPort const AVAudioSessionPortUSBAudio     API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos); /* Input or output on a Universal Serial Bus device */
extern AVAudioSessionPort const AVAudioSessionPortCarAudio     API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos); /* Input or output via Car Audio */

#pragma mark -- constants for data source locations, orientations, polar patterns, and channel roles --

/* The following represent the location of a data source on an iOS device. */
extern AVAudioSessionLocation const AVAudioSessionLocationUpper					API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);
extern AVAudioSessionLocation const AVAudioSessionLocationLower					API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* The following represent the orientation or directionality of a data source on an iOS device. */
extern AVAudioSessionLocation const AVAudioSessionOrientationTop					API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);
extern AVAudioSessionLocation const AVAudioSessionOrientationBottom				API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);
extern AVAudioSessionLocation const AVAudioSessionOrientationFront				API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);
extern AVAudioSessionLocation const AVAudioSessionOrientationBack				API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);
extern AVAudioSessionLocation const AVAudioSessionOrientationLeft				API_AVAILABLE(ios(8.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);
extern AVAudioSessionLocation const AVAudioSessionOrientationRight				API_AVAILABLE(ios(8.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* The following represent the possible polar patterns for a data source on an iOS device. */
extern AVAudioSessionLocation const AVAudioSessionPolarPatternOmnidirectional	API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);
extern AVAudioSessionLocation const AVAudioSessionPolarPatternCardioid			API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);
extern AVAudioSessionLocation const AVAudioSessionPolarPatternSubcardioid		API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

#pragma mark -- helper class interfaces --

/* 
 AVAudioSessionChannelDescription objects provide information about a port's audio channels.
 AudioQueues, AURemoteIO and AUVoiceIO instances can be assigned to communicate with specific 
 hardware channels by setting an array of <port UID, channel index> pairs.
 */
API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos) 
@interface AVAudioSessionChannelDescription : NSObject {
@private
	void *_impl;
}

@property(readonly) NSString *			channelName API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);
@property(readonly) NSString *			owningPortUID API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);  /* the unique identifier (UID) for the channel's owning port */
@property(readonly) NSUInteger			channelNumber API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);  /* the index of this channel in its owning port's array of channels */
@property(readonly) AudioChannelLabel	channelLabel API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);	/* description of the physical location of this channel.   */

@end

API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos) 
@interface AVAudioSessionPortDescription : NSObject {
@private
	void *_impl;
}

/* Value is one of the AVAudioSessionPort constants declared above. */
@property (readonly) AVAudioSessionPort portType API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* A descriptive name for the port */
@property (readonly) NSString *portName API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* A system-assigned unique identifier for the port */
@property (readonly) NSString *UID API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* This property's value will be true if the associated hardware port has built-in processing for two-way 
 voice communication. Applications that use their own proprietary voice processing algorithms should use 
 this property to decide when to disable processing.  On the other hand, if using Apple's Voice Processing 
 I/O unit (subtype kAudioUnitSubType_VoiceProcessingIO), the system will automatically manage this for the 
 application. In particular, ports of type AVAudioSessionPortBluetoothHFP and AVAudioSessionPortCarAudio
 often have hardware voice processing. */
@property (readonly) BOOL hasHardwareVoiceCallProcessing API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

@property (readonly, nullable) NSArray<AVAudioSessionChannelDescription *> *channels API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Will be nil if there are no selectable data sources. */
@property (readonly, nullable) NSArray<AVAudioSessionDataSourceDescription *> *dataSources API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/* Will be nil if there are no selectable data sources. In all other cases, this
 property reflects the currently selected data source.*/
@property (readonly, nullable) AVAudioSessionDataSourceDescription *selectedDataSource API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/* This property reflects the application's preferred data source for the Port.
 Will be nil if there are no selectable data sources or if no preference has been set.*/
@property (readonly, nullable) AVAudioSessionDataSourceDescription *preferredDataSource API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/* Select the preferred data source for this port. The input dataSource parameter must be one of the dataSources exposed by 
the dataSources property. Setting a nil value will clear the preference.
Note: if the port is part of the active audio route, changing the data source will likely
result in a route reconfiguration.  If the port is not part of the active route, selecting a new data source will
not result in an immediate route reconfiguration.  Use AVAudioSession's setPreferredInput:error: method to activate the port. */
- (BOOL)setPreferredDataSource:(nullable AVAudioSessionDataSourceDescription *)dataSource error:(NSError **)outError API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

@end

API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos) 
@interface AVAudioSessionRouteDescription : NSObject {
@private
	void *_impl;
}

@property (readonly) NSArray<AVAudioSessionPortDescription *> *inputs API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

@property (readonly) NSArray<AVAudioSessionPortDescription *> *outputs API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);
@end

API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos) 
@interface AVAudioSessionDataSourceDescription : NSObject {
@private
	void *_impl;
}

/* system-assigned ID for the data source */
@property (readonly) NSNumber *dataSourceID API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* human-readable name for the data source */
@property (readonly) NSString *dataSourceName API_AVAILABLE(ios(6.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Location and orientation can be used to distinguish between multiple data sources belonging to a single port.  For example, in the case of a port of type AVAudioSessionPortBuiltInMic, one can
   use these properties to differentiate between an upper/front-facing microphone and a lower/bottom-facing microphone. */

/* Describes the general location of a data source. Will be nil for data sources for which the location is not known. */
@property (readonly, nullable) AVAudioSessionLocation location API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Describes the orientation of a data source.  Will be nil for data sources for which the orientation is not known. */
@property (readonly, nullable) AVAudioSessionOrientation orientation API_AVAILABLE(ios(7.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/* Array of one or more AVAudioSessionPolarPatterns describing the supported polar patterns for a data source.  Will be nil for data sources that have no selectable patterns. */
@property (readonly, nullable) NSArray<AVAudioSessionPolarPattern> *supportedPolarPatterns API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/* Describes the currently selected polar pattern.  Will be nil for data sources that have no selectable patterns. */
@property (readonly, nullable) AVAudioSessionPolarPattern selectedPolarPattern API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/* Describes the preferred polar pattern.  Will be nil for data sources that have no selectable patterns or if no preference has been set. */
@property (readonly, nullable) AVAudioSessionPolarPattern preferredPolarPattern API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

/* Select the desired polar pattern from the set of available patterns. Setting a nil value will clear the preference.
   Note: if the owning port and data source are part of the active audio route,
   changing the polar pattern will likely result in a route reconfiguration. If the owning port and data source are not part of the active route,
   selecting a polar pattern will not result in an immediate route reconfiguration.  Use AVAudioSession's setPreferredInput:error: method
   to activate the port. Use setPreferredDataSource:error: to active the data source on the port. */
- (BOOL)setPreferredPolarPattern:(nullable AVAudioSessionPolarPattern)pattern error:(NSError **)outError API_AVAILABLE(ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos, macos);

@end


#pragma mark -- Deprecated API --
@interface AVAudioSession (AVAudioSessionDeprecated)

/* The delegate property is deprecated. Instead, you should register for the NSNotifications named below. */
/* For example:
 [[NSNotificationCenter defaultCenter] addObserver: myObject
 selector:    @selector(handleInterruption:)
 name:        AVAudioSessionInterruptionNotification
 object:      [AVAudioSession sharedInstance]];
 */
@property (assign, nullable) id<AVAudioSessionDelegate> delegate API_DEPRECATED("No longer supported", ios(4.0, 6.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED API_UNAVAILABLE(macos);

/* AVAudioSession is a singleton. Use +sharedInstance instead of -init */
- (instancetype)init API_DEPRECATED_WITH_REPLACEMENT("+sharedInstance", ios(3.0, 10.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED API_UNAVAILABLE(macos, macCatalyst);

- (BOOL)setActive:(BOOL)active withFlags:(NSInteger)flags error:(NSError **)outError API_DEPRECATED_WITH_REPLACEMENT("-setActive:withOptions:error:", ios(4.0, 6.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED API_UNAVAILABLE(macos, macCatalyst);

//isInputAvailable
@property (readonly) BOOL inputIsAvailable API_DEPRECATED_WITH_REPLACEMENT("isInputAvailable", ios(3.0, 6.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED API_UNAVAILABLE(macos, macCatalyst); /* is input hardware available or not? */

/* deprecated.  Use the corresponding properties without "Hardware" in their names. */
@property (readonly) double currentHardwareSampleRate API_DEPRECATED_WITH_REPLACEMENT("sampleRate", ios(3.0, 6.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED API_UNAVAILABLE(macos, macCatalyst);
@property (readonly) NSInteger currentHardwareInputNumberOfChannels API_DEPRECATED_WITH_REPLACEMENT("inputNumberOfChannels", ios(3.0, 6.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED API_UNAVAILABLE(macos, macCatalyst);
@property (readonly) NSInteger currentHardwareOutputNumberOfChannels API_DEPRECATED_WITH_REPLACEMENT("outputNumberOfChannels", ios(3.0, 6.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED API_UNAVAILABLE(macos, macCatalyst);
- (BOOL)setPreferredHardwareSampleRate:(double)sampleRate error:(NSError **)outError API_DEPRECATED_WITH_REPLACEMENT("setPreferredSampleRate:error:", ios(3.0, 6.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED API_UNAVAILABLE(macos,macCatalyst);
@property (readonly) double preferredHardwareSampleRate API_DEPRECATED_WITH_REPLACEMENT("preferredSampleRate", ios(3.0, 6.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED API_UNAVAILABLE(macos, macCatalyst);

@end

#pragma mark -- AVAudioSessionDelegate protocol --
/* The AVAudioSessionDelegate protocol is deprecated. Instead you should register for notifications. */
API_DEPRECATED("No longer supported", ios(3.0, 6.0)) API_UNAVAILABLE(tvos, watchos, macos)
@protocol AVAudioSessionDelegate <NSObject>
@optional

- (void)beginInterruption API_DEPRECATED("No longer supported", ios(3.0, 6.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED API_UNAVAILABLE(macos); /* something has caused your audio session to be interrupted */

/* the interruption is over */
- (void)endInterruptionWithFlags:(NSUInteger)flags API_DEPRECATED("No longer supported", ios(4.0, 6.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED API_UNAVAILABLE(macos); /* Currently the only flag is AVAudioSessionInterruptionFlags_ShouldResume. */

- (void)endInterruption API_DEPRECATED("No longer supported", ios(3.0, 6.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED API_UNAVAILABLE(macos); /* endInterruptionWithFlags: will be called instead if implemented. */

/* notification for input become available or unavailable */
- (void)inputIsAvailableChanged:(BOOL)isInputAvailable API_DEPRECATED("No longer supported", ios(3.0, 6.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED API_UNAVAILABLE(macos);

@end

#pragma mark -- Deprecated enumerations --

/* Deprecated in iOS 6.0.  Use AVAudioSessionInterruptionOptions instead.
 Flags passed to you when endInterruptionWithFlags: is called on the delegate */
enum {
	AVAudioSessionInterruptionFlags_ShouldResume API_DEPRECATED_WITH_REPLACEMENT("AVAudioSessionInterruptionOptions", ios(4.0, 6.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED API_UNAVAILABLE(macos) = 1
};

/* Deprecated in iOS 6.0.  Use AVAudioSessionSetActiveOptions instead.
 flags for use when calling setActive:withFlags:error: */
enum {
	AVAudioSessionSetActiveFlags_NotifyOthersOnDeactivation API_DEPRECATED_WITH_REPLACEMENT("AVAudioSessionSetActiveOptions", ios(4.0, 6.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED API_UNAVAILABLE(macos) = 1
};

NS_ASSUME_NONNULL_END

#elif defined(__OBJC__) && TARGET_OS_OSX
#import <AVFAudio/AVAudioSession_i386.h>
#endif // __OBJC2__
