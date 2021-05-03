#if (defined(USE_AVFAUDIO_PUBLIC_HEADERS) && USE_AVFAUDIO_PUBLIC_HEADERS) || !__has_include(<AudioSession/AVAudioSessionDeprecated.h>)
/*!
	@file		AVAudioSessionDeprecated.h
	@framework	AudioSession.framework
	@copyright	(c) 2009-2020 Apple Inc. All rights reserved.
*/

#ifndef AudioSession_AVAudioSession_Deprecated_h
#define AudioSession_AVAudioSession_Deprecated_h

#import <AVFAudio/AVAudioSessionRoute.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark -- Deprecated API --

/* This protocol is available with iPhone 3.0 or later */
@protocol AVAudioSessionDelegate;

@interface AVAudioSession (AVAudioSessionDeprecated)

/* The delegate property is deprecated. Instead, you should register for the NSNotifications named below. */
/* For example:
 [[NSNotificationCenter defaultCenter] addObserver: myObject
 selector:    @selector(handleInterruption:)
 name:        AVAudioSessionInterruptionNotification
 object:      [AVAudioSession sharedInstance]];
 */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-warning-option"
#pragma clang diagnostic ignored "-Wobjc-property-assign-on-object-type"
@property (assign, nullable) id<AVAudioSessionDelegate> delegate API_DEPRECATED("No longer supported", ios(4.0, 6.0), macCatalyst(14.0, 14.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
#pragma clang diagnostic pop

/* AVAudioSession is a singleton. Use +sharedInstance instead of -init */
- (instancetype)init API_DEPRECATED_WITH_REPLACEMENT("+sharedInstance", ios(3.0, 10.0), macCatalyst(14.0, 14.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED API_UNAVAILABLE(macos);

- (BOOL)setActive:(BOOL)active withFlags:(NSInteger)flags error:(NSError **)outError API_DEPRECATED_WITH_REPLACEMENT("-setActive:withOptions:error:", ios(4.0, 6.0), macCatalyst(14.0, 14.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED API_UNAVAILABLE(macos);

@property (readonly) BOOL inputIsAvailable API_DEPRECATED_WITH_REPLACEMENT("isInputAvailable", ios(3.0, 6.0), macCatalyst(14.0, 14.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED API_UNAVAILABLE(macos); /* is input hardware available or not? */

/* deprecated.  Use the corresponding properties without "Hardware" in their names. */
@property (readonly) double currentHardwareSampleRate API_DEPRECATED_WITH_REPLACEMENT("sampleRate", ios(3.0, 6.0), macCatalyst(14.0, 14.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED API_UNAVAILABLE(macos);
@property (readonly) NSInteger currentHardwareInputNumberOfChannels API_DEPRECATED_WITH_REPLACEMENT("inputNumberOfChannels", ios(3.0, 6.0), macCatalyst(14.0, 14.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED API_UNAVAILABLE(macos);
@property (readonly) NSInteger currentHardwareOutputNumberOfChannels API_DEPRECATED_WITH_REPLACEMENT("outputNumberOfChannels", ios(3.0, 6.0), macCatalyst(14.0, 14.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED API_UNAVAILABLE(macos);
- (BOOL)setPreferredHardwareSampleRate:(double)sampleRate error:(NSError **)outError API_DEPRECATED_WITH_REPLACEMENT("setPreferredSampleRate:error:", ios(3.0, 6.0), macCatalyst(14.0, 14.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED API_UNAVAILABLE(macos);
@property (readonly) double preferredHardwareSampleRate API_DEPRECATED_WITH_REPLACEMENT("preferredSampleRate", ios(3.0, 6.0), macCatalyst(14.0, 14.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED API_UNAVAILABLE(macos);


@end

#pragma mark -- AVAudioSessionDelegate protocol --
/* The AVAudioSessionDelegate protocol is deprecated. Instead you should register for notifications. */
API_DEPRECATED("No longer supported", ios(3.0, 6.0), macCatalyst(14.0, 14.0)) API_UNAVAILABLE(tvos, watchos, macos)
@protocol AVAudioSessionDelegate <NSObject>
@optional

- (void)beginInterruption; /* something has caused your audio session to be interrupted */

/* the interruption is over */
- (void)endInterruptionWithFlags:(NSUInteger)flags API_AVAILABLE(ios(4.0), watchos(2.0), tvos(9.0)); /* Currently the only flag is AVAudioSessionInterruptionFlags_ShouldResume. */

- (void)endInterruption; /* endInterruptionWithFlags: will be called instead if implemented. */

/* notification for input become available or unavailable */
- (void)inputIsAvailableChanged:(BOOL)isInputAvailable;

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

#endif // AudioSession_AVAudioSession_Deprecated_h
#else
#include <AudioSession/AVAudioSessionDeprecated.h>
#endif
