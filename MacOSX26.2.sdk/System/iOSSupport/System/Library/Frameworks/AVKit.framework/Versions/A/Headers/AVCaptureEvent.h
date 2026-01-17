/*
	File:  AVCaptureEvent.h
	
	Framework:  AVKit
	
	Copyright © 2022-2023 Apple Inc. All rights reserved.
	
	To report bugs, go to:  http://developer.apple.com/bugreporter/

 */


#import <Foundation/Foundation.h>

#if TARGET_OS_MACCATALYST
#import <AVKit/AVKitDefines.h>
#else
#import <AVKit/AVKitDefines.h>
#endif // TARGET_OS_MACCATALYST

#import <AVKit/AVCaptureEventSound.h>

NS_ASSUME_NONNULL_BEGIN

@class AVCaptureEvent;


// MARK: -

/// An enumeration that describes the phase of a capture event.
typedef NS_ENUM(NSUInteger, AVCaptureEventPhase) {
	/// A phase that indicates the beginning of a capture event.
	AVCaptureEventPhaseBegan,
	/// A phase that indicates the end of a capture event.
	AVCaptureEventPhaseEnded,
	/// A phase that indicates the cancellation of a capture event.
	AVCaptureEventPhaseCancelled,
} API_AVAILABLE(ios(17.2)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(macos, tvos, watchos);


// MARK: -

/// An object that describes a user interaction with a system hardware button.
///
/// Inspect a capture event’s ``phase`` to determine whether the event begins, ends, or is in a canceled state.
API_AVAILABLE(ios(17.2)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(macos, tvos, watchos)
@interface AVCaptureEvent : NSObject

AVKIT_INIT_UNAVAILABLE


/// The current phase of a capture event.
@property (nonatomic, readonly) AVCaptureEventPhase phase;

/*!
 * Plays the specified capture sound through AirPods.
 *
 * - Parameter sound: The capture sound to play for this event.
 * - Returns: A Boolean value that indicates whether the system played the sound.
 *
 * This method has no effect if ``shouldPlaySound`` is `false` or if the event object's lifetime exceeds 15 seconds.
 *
 * > Important: To use AirPods Camera Control, it must be available in your country or region. AirPods Camera Control is not currently available in the European Union.
 */
- (BOOL)playSound:(AVCaptureEventSound *)sound API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(visionos, macCatalyst) API_UNAVAILABLE(macos, tvos, watchos);

/*!
 * A Boolean value that indicates whether you must play a sound manually.
 *
 * This property is `true` only when both of the following conditions are true:
 * 1. A person performs an AirPod stem click.
 * 2. You disable the default capture sound.
 *
 * If this property is `false`, calling ``playSound:`` has no effect. Omitting the sound when expected can significantly impact the user experience.
 *
 * > Important: To use AirPods Camera Control, it must be available in your country or region. AirPods Camera Control is not currently available in the European Union.
 */
@property (nonatomic, readonly) BOOL shouldPlaySound API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(visionos, macCatalyst) API_UNAVAILABLE(macos, tvos, watchos);

@end

NS_ASSUME_NONNULL_END
