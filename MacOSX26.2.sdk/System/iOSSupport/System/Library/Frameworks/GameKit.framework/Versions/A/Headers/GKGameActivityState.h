// Copyright © Apple Inc. All rights reserved.

#import <TargetConditionals.h>

#if !TARGET_OS_WATCH

#import <Foundation/Foundation.h>
#import <TargetConditionals.h>

/// The state of a game activity.
typedef NS_ENUM(NSUInteger, GKGameActivityState) {
    /// The game activity is initialized but has not started.
    GKGameActivityStateInitialized = 0,
    /// The game activity is active.
    GKGameActivityStateActive = 1,
    /// The game activity is paused.
    GKGameActivityStatePaused = 2,
    /// The game activity has ended. This is a terminal state.
    GKGameActivityStateEnded = 4
} NS_SWIFT_NAME(GKGameActivity.State) API_AVAILABLE(ios(26.0), macos(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

#endif // #if !TARGET_OS_WATCH
