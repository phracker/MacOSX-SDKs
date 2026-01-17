#if !__has_include(<AVFCore/AVPlaybackCoordinationMedium.h>)
/*
	File: AVPlaybackCoordinationMedium.h
	
	Framework: AVFoundation
	
	Copyright © 2024 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVPlaybackCoordinator.h>

NS_ASSUME_NONNULL_BEGIN

/// The AVPlaybackCoordinationMedium passes states and messages between its connected playback coordinators.
/// 
/// The coordination medium passes states and messages from one playback coordinator to all other connected playback coordinators to enable coordination of rate changes and seeks. Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);
@interface AVPlaybackCoordinationMedium : NSObject

/// Initializes an AVPlaybackCoordinationMedium
- (instancetype)init;

/// All playback coordinators that are connected to the coordination medium.
/// 
/// Returns an array of all the AVPlayerPlaybackCoordinators that are connected to the coordination medium.
/// This coordination is specifically for AVPlayerPlaybackCoordinators, and we exclude AVDelegatingPlaybackCoordinators.
/// AVPlaybackCoordinator properties and methods are individually configurable for each playback coordinator. To ensure correct synchronized behavior across all local playback coordinators, any common AVPlaybackCoordinator properties and methods should be set and called on all playback coordinators in the coordination medium.
/// The properties and methods `otherParticipants`, `setParticipantLimit:forWaitingOutSuspensionsWithReason:`, and `participantLimitForWaitingOutSuspensionsWithReason:` refer specifically to remote participants that are coordinated through a group session rather than through the playback coordination medium. `otherParticipants` only returns participants connected to the same group session. `setParticipantLimit` and `participantLimitForWaitingOutSuspensionsWithReason` affect only policies and behavior with the group session.
@property (nonatomic, readonly) NSArray<AVPlayerPlaybackCoordinator *> *connectedPlaybackCoordinators;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVPlaybackCoordinationMedium.h>
#endif
