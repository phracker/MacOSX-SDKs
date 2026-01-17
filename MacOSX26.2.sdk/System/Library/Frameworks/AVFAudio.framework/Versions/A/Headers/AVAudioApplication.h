#if (defined(USE_AVFAUDIO_PUBLIC_HEADERS) && USE_AVFAUDIO_PUBLIC_HEADERS) || !__has_include(<AudioSession/AVAudioApplication.h>)
/*!
	@file		AVAudioApplication.h
	@framework	AudioSession.framework
	@copyright	(c) 2009-2024 Apple Inc. All rights reserved.
*/

#ifndef AVAudioApplication_h
#define AVAudioApplication_h

#import <AVFAudio/AVAudioSessionTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*!
	@enum AVAudioApplicationRecordPermission
	@brief	These are the values returned by recordPermission.
	@var	AVAudioApplicationRecordPermissionUndetermined
	The user has not yet been asked for permission.
	@var	AVAudioApplicationRecordPermissionDenied
	The user has been asked and has denied permission.
	@var	AVAudioApplicationRecordPermissionGranted
	The user has been asked and has granted permission.
*/
typedef NS_ENUM(NSInteger, AVAudioApplicationRecordPermission) {
	AVAudioApplicationRecordPermissionUndetermined = 'undt',
	AVAudioApplicationRecordPermissionDenied = 'deny',
	AVAudioApplicationRecordPermissionGranted = 'grnt'
} NS_SWIFT_NAME(AVAudioApplication.recordPermission);

/*!
    @enum AVAudioApplicationMicrophoneInjectionPermission
    @brief    These are the values returned by microphoneInjectionPermission.
    @var    AVAudioApplicationMicrophoneInjectionPermissionServiceDisabled
    The user has disabled this service for all apps.
    @var    AVAudioApplicationMicrophoneInjectionUndetermined
    The user has not yet been asked for permission.
    @var    AVAudioApplicationMicrophoneInjectionPermissionDenied
    The user has been asked and has denied permission.
    @var    AVAudioApplicationMicrophoneInjectionPermissionGranted
    The user has been asked and has granted permission.

    Introduced: ios(18.2) visionos(2.2)
*/
typedef NS_ENUM(NSInteger, AVAudioApplicationMicrophoneInjectionPermission) {
    AVAudioApplicationMicrophoneInjectionPermissionServiceDisabled = 'srds',
    AVAudioApplicationMicrophoneInjectionPermissionUndetermined    = 'undt',
    AVAudioApplicationMicrophoneInjectionPermissionDenied          = 'deny',
    AVAudioApplicationMicrophoneInjectionPermissionGranted         = 'grnt'
} NS_SWIFT_NAME(AVAudioApplication.MicrophoneInjectionPermission);

/*!
	@brief	Notification sent to registered listeners when the application's input is muted
			or unmuted.

	Check the notification's userInfo dictionary for the mute state `AVAudioApplicationMuteStateKey`
	which will have a boolean value 0 for unmuted or value 1 for muted.
	@note this notification will only be dispatched for state changes when there is an active record session (i.e. record or playAndRecord category).
		Setting the `inputMuted` state while the record session is not active is allowed and will be stored, but it will not trigger a notification for the
		state change. When the record session subsequently goes active, the `inputMuted` state will be applied, and this notification will be dispatched
		with the latest input muted state.
*/
OS_EXPORT NSNotificationName const AVAudioApplicationInputMuteStateChangeNotification API_AVAILABLE(ios(17.0), watchos(10.0), tvos(17.0), macos(14.0), visionos(26.0)) NS_SWIFT_NAME(AVAudioApplication.inputMuteStateChangeNotification);

/// Keys for AVAudioApplicationInputMuteStateChangeNotification
/// Value is NSNumber type with boolean value 0 for unmuted or value 1 for muted (samples zeroed out)
OS_EXPORT NSString *const AVAudioApplicationMuteStateKey API_AVAILABLE(ios(17.0), watchos(10.0), tvos(17.0), macos(14.0), visionos(26.0)) NS_SWIFT_NAME(AVAudioApplication.muteStateKey);


/// Class containing methods that relate to an application bundle's audio (i.e. a collection of one or more AVAudioSession instances)
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(17.0), watchos(10.0), tvos(17.0), macos(14.0)) 
@interface AVAudioApplication : NSObject

/// Returns the singleton instance
@property (class, readonly) AVAudioApplication *sharedInstance NS_SWIFT_NAME(shared);

/// @see `sharedInstance`
- (instancetype)init NS_UNAVAILABLE;

/// @brief Set the muted/unmuted state of the application's audio input. When set true, inputs
/// (microphone etc.) of all audio clients relating to this application will have their samples zeroed out.
/// @note - this is per-application input muting and doesn't affect the hardware mute state.
- (BOOL)setInputMuted:(BOOL)muted error:(NSError**)outError API_AVAILABLE(ios(17.0), watchos(10.0), tvos(17.0), macos(14.0), visionos(26.0));
/// Get the input muted state - return value is boolean 0 for unmuted or value 1 for muted (input samples zeroed out)
@property(readonly, nonatomic, getter=isInputMuted) BOOL inputMuted API_AVAILABLE(ios(17.0), watchos(10.0), tvos(17.0), macos(14.0), visionos(26.0));


/*!
	@brief  Provide a block that implements your app's input (microphone) muting logic (macOS only). The block will be called
			whenever the input mute state changes, either due to changing the `AVAudioApplication.inputMute` property on
			this API, or due to a Bluetooth audio accessory gesture (certain AirPods / Beats headphones) changing the mute state.

	@param	inputMuteHandler block that will be called upon every input mute state change. If the boolean `inputShouldBeMuted`
			is true, your block should mute all input/microphone samples until the next time the handler is called. Your block should return
			a value of YES if successful, or in exceptional cases return a NO value if the mute action was unsuccesful.
			Since the input mute handling logic should happen a single place, subsequent calls to this method will overwrite any previously
			registered block with the one provided. A nil value may be provided to cancel the block being called, e.g. at end of call lifecycle.

	@note   This is available on macOS only - for all other platforms input muting will be handled internally. It is recommended only to
			perform your input muting logic within this block, and to perform your UI updates for input mute state changes within the handler
			for AVAudioApplicationInputMuteStateChangeNotification. This handler should be set by the process doing the call's audio I/O.
 */
- (BOOL)setInputMuteStateChangeHandler:(BOOL (^_Nullable)(BOOL inputShouldBeMuted))inputMuteHandler error:(NSError**)outError API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos, macCatalyst, visionos);


/// Returns an enum indicating whether the user has granted or denied permission to record, or has
/// not been asked
@property (readonly) AVAudioApplicationRecordPermission recordPermission API_AVAILABLE(ios(17.0), watchos(10.0), tvos(17.0), macos(14.0));

/*!
	@brief Checks to see if calling process has permission to record audio.

	The 'response' block will be called immediately if permission has already been granted or
	denied.  Otherwise, it presents a dialog to notify the user and allow them to choose, and calls
	the block once the UI has been dismissed.  'granted' indicates whether permission has been
	granted. Note that the block may be called in a different thread context.
*/
+ (void)requestRecordPermissionWithCompletionHandler:(void (^)(BOOL granted))response API_AVAILABLE(ios(17.0), watchos(10.0), tvos(17.0), macos(14.0));

/// Returns an enum indicating whether the user has granted or denied permission to inject audio into input,
/// or has not been asked
@property(readonly) AVAudioApplicationMicrophoneInjectionPermission microphoneInjectionPermission API_AVAILABLE(ios(18.2), visionos(2.2)) API_UNAVAILABLE(tvos, watchos, macos);

/*!
    @brief Checks to see if calling process has permission to inject audio to input stream.

    The 'response' block will be called immediately if permission has already been granted or
    denied or if the service is disabled by the user.  Otherwise, it presents a dialog to notify the
    user and allow them to choose, and calls the block once the UI has been dismissed.
    'granted' indicates whether permission has been granted. Note that the block may be
    called in a different thread context.
*/
+ (void)requestMicrophoneInjectionPermissionWithCompletionHandler:(void (^)(AVAudioApplicationMicrophoneInjectionPermission permission))response API_AVAILABLE(ios(18.2), visionos(2.2)) API_UNAVAILABLE(tvos, watchos, macos);

@end

NS_ASSUME_NONNULL_END

#endif /* AVAudioApplication_h */
#else
#include <AudioSession/AVAudioApplication.h>
#endif
