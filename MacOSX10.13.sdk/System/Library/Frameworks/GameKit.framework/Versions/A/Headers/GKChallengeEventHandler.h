//
//  GKChallengeEventHandler.h
//  Game Center
//
//  Copyright 2012-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKChallenge.h>

// GKChallengeEventHandler's delegate must implement the following protocol to be notified of challenge-related events. All of these methods are called on the main thread.
NS_DEPRECATED(10_8, 10_10, 6_0, 7_0, "You should instead implement the GKChallengeListener protocol and register a listener with GKLocalPlayer.") __WATCHOS_PROHIBITED 
@protocol GKChallengeEventHandlerDelegate <NSObject>

@optional

// Called when the user taps a challenge notification banner or the "Play Now" button for a challenge inside Game Center, causing the game to launch. Also called when the user taps a challenge banner inside the game.
- (void)localPlayerDidSelectChallenge:(GKChallenge *)challenge;

// If the method returns YES, a challenge banner (like an achievement or welcome banner -- not a notification center banner) is displayed when a challenge is received in-game for the local player. If NO, then no banner is displayed, and localPlayerDidSelectChallenge: will not be called for that challenge. Default behavior for non-implementing apps is YES.
- (BOOL)shouldShowBannerForLocallyReceivedChallenge:(GKChallenge *)challenge;

// Called when the local player has received a challenge, triggered by a push notification from the server. Received only while the game is running.
- (void)localPlayerDidReceiveChallenge:(GKChallenge *)challenge;

// If the method returns YES, a challenge banner (like an achievement or welcome banner -- not a notification center banner) is displayed. If NO, then no banner is displayed. Default behavior for non-implementing apps is YES.
- (BOOL)shouldShowBannerForLocallyCompletedChallenge:(GKChallenge *)challenge;

// Called when the local player has completed one of their challenges, triggered by a push notification from the server. Received only while the game is running.
- (void)localPlayerDidCompleteChallenge:(GKChallenge *)challenge;

// If the method returns YES, a challenge banner (like an achievement or welcome banner -- not a notification center banner) is displayed. If NO, then no banner is displayed. Default behavior for non-implementing apps is YES.
- (BOOL)shouldShowBannerForRemotelyCompletedChallenge:(GKChallenge *)challenge;

// Called when a non-local player has completed a challenge issued by the local player. Triggered by a push notification from the server. Received when a challenge notification banner is tapped, or while the game is running. 
- (void)remotePlayerDidCompleteChallenge:(GKChallenge *)challenge;

@end

#if !TARGET_OS_WATCH

NS_CLASS_DEPRECATED(10_8, 10_10, 6_0, 7_0, "You should instead implement the GKChallengeListener protocol and register a listener with GKLocalPlayer.") 
// A singleton object responsible for dispatching challenge-related events to its delegate
@interface GKChallengeEventHandler : NSObject

+ (GKChallengeEventHandler *) challengeEventHandler NS_DEPRECATED(10_8, 10_10, 6_0, 7_0);

@property (nonatomic, assign) id<GKChallengeEventHandlerDelegate> delegate NS_DEPRECATED(10_8, 10_10, 6_0, 7_0); // It is not safe to read or write this property on anything other than the main thread
@end
#endif
