//
//  GKChallengeEventHandler.h
//  GameKit
//
//  Copyright 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKChallenge.h>

// GKChallengeEventHandler's delegate must implement the following protocol to be notified of challenge-related events. All of these methods are called on the main thread.
@protocol GKChallengeEventHandlerDelegate <NSObject>

@optional

// Called when the user clicks a challenge notification banner or the "Play Now" button for a challenge inside Game Center, causing the game to launch. Also called when the user clicks a challenge banner inside the game.
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

// Called when a non-local player has completed a challenge issued by the local player. Triggered by a push notification from the server. Received when a challenge notification banner is clicked, or while the game is running.
- (void)remotePlayerDidCompleteChallenge:(GKChallenge *)challenge;

@end

NS_CLASS_AVAILABLE(10_9, 6_0)
// A singleton object responsible for dispatching challenge-related events to its delegate
@interface GKChallengeEventHandler : NSObject
{
@private
    id _internal1;
    id _internal2;
    id _internal3;
}
+ (GKChallengeEventHandler *) challengeEventHandler;

@property (assign, NS_NONATOMIC_IOSONLY) id<GKChallengeEventHandlerDelegate> delegate; // It is not safe to read or write this property on anything other than the main thread
@end