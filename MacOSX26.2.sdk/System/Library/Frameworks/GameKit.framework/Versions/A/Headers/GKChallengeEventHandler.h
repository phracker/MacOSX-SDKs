// Copyright © Apple Inc. All rights reserved.

#import <TargetConditionals.h>
#import <Foundation/Foundation.h>
#import <GameKit/GKChallenge.h>

/// GKChallengeEventHandler's delegate must implement the following protocol to be notified of challenge-related events. All of these methods are called on the main thread.
API_DEPRECATED("You should instead implement the GKChallengeListener protocol and register a listener with GKLocalPlayer.", ios(6.0,7.0), macos(10.8,10.10)) API_UNAVAILABLE(tvos, watchos)
@protocol GKChallengeEventHandlerDelegate <NSObject>

@optional

/// Called when the user taps a challenge notification banner or the "Play Now" button for a challenge inside Game Center, causing the game to launch. Also called when the user taps a challenge banner inside the game.
- (void)localPlayerDidSelectChallenge:(GKChallenge *)challenge;

/// If the method returns YES, a challenge banner (like an achievement or welcome banner -- not a notification center banner) is displayed when a challenge is received in-game for the local player. If NO, then no banner is displayed, and localPlayerDidSelectChallenge: will not be called for that challenge. Default behavior for non-implementing apps is YES.
- (BOOL)shouldShowBannerForLocallyReceivedChallenge:(GKChallenge *)challenge;

/// Called when the local player has received a challenge, triggered by a push notification from the server. Received only while the game is running.
- (void)localPlayerDidReceiveChallenge:(GKChallenge *)challenge;

/// If the method returns YES, a challenge banner (like an achievement or welcome banner -- not a notification center banner) is displayed. If NO, then no banner is displayed. Default behavior for non-implementing apps is YES.
- (BOOL)shouldShowBannerForLocallyCompletedChallenge:(GKChallenge *)challenge;

/// Called when the local player has completed one of their challenges, triggered by a push notification from the server. Received only while the game is running.
- (void)localPlayerDidCompleteChallenge:(GKChallenge *)challenge;

/// If the method returns YES, a challenge banner (like an achievement or welcome banner -- not a notification center banner) is displayed. If NO, then no banner is displayed. Default behavior for non-implementing apps is YES.
- (BOOL)shouldShowBannerForRemotelyCompletedChallenge:(GKChallenge *)challenge;

/// Called when a non-local player has completed a challenge issued by the local player. Triggered by a push notification from the server. Received when a challenge notification banner is tapped, or while the game is running.
- (void)remotePlayerDidCompleteChallenge:(GKChallenge *)challenge;

@end

API_DEPRECATED("You should instead implement the GKChallengeListener protocol and register a listener with GKLocalPlayer.", ios(6.0,7.0), macos(10.8,10.10)) API_UNAVAILABLE(tvos, watchos)
/// A singleton object responsible for dispatching challenge-related events to its delegate
@interface GKChallengeEventHandler : NSObject

+ (GKChallengeEventHandler *) challengeEventHandler API_DEPRECATED("No longer supported.", ios(6.0,7.0), macos(10.8,10.10), visionos(1.0,1.0)) API_UNAVAILABLE(tvos, watchos);

@property (nonatomic, weak) id<GKChallengeEventHandlerDelegate> delegate API_DEPRECATED("No longer supported.", ios(6.0,7.0), macos(10.8,10.10), visionos(1.0,1.0)) API_UNAVAILABLE(tvos, watchos); /// It is not safe to read or write this property on anything other than the main thread
@end
