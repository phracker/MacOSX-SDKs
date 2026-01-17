/*
    File:       AVRoutingPlaybackArbiter.h
 
    Framework:  AVRouting
 
    Copyright:  (c) 2025 by Apple Inc., all rights reserved
*/

#import <Foundation/Foundation.h>
#import <AVRouting/AVRoutingDefines.h>

NS_ASSUME_NONNULL_BEGIN

@protocol AVRoutingPlaybackParticipant;

/**
 An object that manages playback routing preferences.

 This object manages instances of ``AVRoutingPlaybackParticipant`` for arbitration of media playback routing priorities and preferences on restricted playback interfaces. The playback routing arbiter is responsible for collecting and applying preferences, such as priorities in non-mixable audio routes and external playback states where the number of allowed players is limited.
 */
API_AVAILABLE(ios(26.0), tvos(26.0)) API_UNAVAILABLE(watchos, visionos, macos)
@interface AVRoutingPlaybackArbiter : NSObject
/**
 Returns the singleton playback arbiter instance.
 */
+ (AVRoutingPlaybackArbiter *)sharedRoutingPlaybackArbiter API_AVAILABLE(ios(26.0), tvos(26.0)) API_UNAVAILABLE(watchos, visionos, macos);

/**
 The participant that has priority to play audio when it's not possible to play multiple audio sources concurrently.
 
 This participant takes precedence over all other participants to play audio in non-mixable audio routes when concurrent audio playback isn't possible, and only a single participant can play audio. The system unmutes this participant's audio, and mutes the audio of all other participants.

 By default, this value is `nil`. When the current preferred participant finishes, the system sets this value to `nil`. If this value is `nil`, the arbiter doesn't impose any priority on the participants, and the participant that's unmuted is based on the existing selection mechanism.
 */

@property (nonatomic, weak, nullable) id<AVRoutingPlaybackParticipant> preferredParticipantForNonMixableAudioRoutes API_AVAILABLE(tvos(26.0)) API_UNAVAILABLE(ios, watchos, visionos, macos);

/**
 The participant that has priority to play on external playback interfaces.
 
 This participant takes precedence over all others to play on external playback interfaces (specifically for AirPlay video and Apple Lightning Digital AV Adapters).
 
 By default, this value is `nil`. When the value is `nil`, the arbiter doesn't impose any priority on the participants, and the participant that is selected to playback externally falls back to the existing selection mechanism.
 */

@property (nonatomic, weak, nullable) id<AVRoutingPlaybackParticipant> preferredParticipantForExternalPlayback API_AVAILABLE(ios(26.0), tvos(26.0)) API_UNAVAILABLE(watchos, visionos, macos);

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new  NS_UNAVAILABLE;

@end

/**
 A protocol for objects that participate in playback routing arbitration.
 
 Classes conform to this protocol if they participate in media playback routing arbitration for managing preferences such as priority on restricted playback routes.
 */
API_AVAILABLE(ios(26.0), tvos(26.0)) API_UNAVAILABLE(watchos, visionos, macos)
@protocol AVRoutingPlaybackParticipant

@end

NS_ASSUME_NONNULL_END
