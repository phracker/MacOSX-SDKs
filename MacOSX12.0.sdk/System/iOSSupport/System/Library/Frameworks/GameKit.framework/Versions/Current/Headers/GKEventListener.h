//
//  GKEventListener.h
//  Game Center
//
//  Copyright 2012-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GKPlayer, GKChallenge;

NS_ASSUME_NONNULL_BEGIN
@protocol GKChallengeListener <NSObject>
@optional

/// Called when a player starts the game with the intent of playing a challenge, or intends to play a challenge after selecting it within the in-game Game Center UI.
/// player: The player who selected the challenge
/// challenge: The challenge which was selected
- (void)player:(GKPlayer *)player wantsToPlayChallenge:(GKChallenge *)challenge NS_AVAILABLE(10_10, 7_0) __WATCHOS_PROHIBITED;

/// Called when a player has received a challenge, triggered by a push notification from the server. Received only while the game is running.
/// player: The player who received the challenge
/// challenge: The challenge which was received
- (void)player:(GKPlayer *)player didReceiveChallenge:(GKChallenge *)challenge NS_AVAILABLE(10_10, 7_0) __WATCHOS_PROHIBITED;

/// Called when a player has completed a challenge, triggered while the game is running, or when the user has tapped a challenge notification banner while outside of the game.
/// player: The player who completed the challenge
/// challenge: The challenge which the player completed
/// friendPlayer: The friend who sent the challenge originally
- (void)player:(GKPlayer *)player didCompleteChallenge:(GKChallenge *)challenge issuedByFriend:(GKPlayer *)friendPlayer NS_AVAILABLE(10_10, 7_0) __WATCHOS_PROHIBITED;

/// Called when a player's friend has completed a challenge which the player sent to that friend. Triggered while the game is running, or when the user has tapped a challenge notification banner while outside of the game.
/// player: The player who sent the challenge originally
/// challenge: The challenge which the player created and sent
/// friendPlayer: The friend who completed the challenge
- (void)player:(GKPlayer *)player issuedChallengeWasCompleted:(GKChallenge *)challenge byFriend:(GKPlayer *)friendPlayer NS_AVAILABLE(10_10, 7_0) __WATCHOS_PROHIBITED;

@end
NS_ASSUME_NONNULL_END
