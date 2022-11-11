//
//  GKMatchmakerViewController.h
//  Game Center
//
//  Copyright 2010-2022 Apple Inc. All rights reserved.
//

@class GKMatchRequest, GKInvite, GKMatch, GKPlayer;

@protocol GKMatchmakerViewControllerDelegate;

typedef NS_ENUM(NSInteger, GKMatchmakingMode) {
    GKMatchmakingModeDefault = 0,
    GKMatchmakingModeNearbyOnly = 1,
    GKMatchmakingModeAutomatchOnly = 2,
    GKMatchmakingModeInviteOnly API_AVAILABLE(ios(15), macos(12), tvos(15)) = 3 ,
};

/// View controller to invite friends, respond to invites, and perform auto-matching. Present modally from the top view controller.
#if TARGET_OS_IPHONE

#import <Foundation/Foundation.h>
#import <UIKit/UINavigationController.h> // UINavigationController

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_8, 4_1)
@interface GKMatchmakerViewController : UINavigationController

#else
#import <GameKit/GKDialogController.h>
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_8, 4_1)
@interface GKMatchmakerViewController : NSViewController <GKViewController>
#endif
@property(nonatomic, nullable, weak) id<GKMatchmakerViewControllerDelegate>     matchmakerDelegate;
@property(nonatomic, readonly, strong) GKMatchRequest                   *matchRequest;
/// set to YES to receive hosted (eg. not peer-to-peer) match results. Will cause the controller to return an array of players instead of a match.
@property(nonatomic, assign, getter=isHosted) BOOL                      hosted;// set to YES to receive hosted (eg. not peer-to-peer) match results. Will cause the controller to return an array of players instead of a match.
/// this controls which mode of matchmaking to support in the UI (all, nearby only, automatch only, invite only).  Throws an exeption if you can not set to the desired mode (due to restrictions)
@property(nonatomic, assign) GKMatchmakingMode                          matchmakingMode;
/// A BOOL value to allow the GKMatchMakerViewController to return control to the game once the minimum number of players are connected.
/// By default the value is NO, and the multiplayer match can only proceed after all players are connected.
/// If the value is set to YES, then once the number of connected players is greater than or equal to minPlayers of the match request, matchmakerViewController:didFindMatch: will be called and the game can get the match instance, and update the game scene accordingly. The remaining players wil continue to connect.
@property(nonatomic, assign) BOOL                                       canStartWithMinimumPlayers API_AVAILABLE(ios(15.0), macos(12.0), tvos(15.0));

/// Initialize with a matchmaking request, allowing the user to send invites and/or start matchmaking
- (nullable id)initWithMatchRequest:(GKMatchRequest *)request;

/// Initialize with an accepted invite, allowing the user to see the status of other invited players and get notified when the game starts
- (nullable id)initWithInvite:(GKInvite *)invite;

/// Add additional players (not currently connected) to an existing peer-to-peer match.
/// Apps should elect a single device to do this, otherwise conflicts could arise resulting in unexpected connection errors.
- (void)addPlayersToMatch:(GKMatch *)match NS_AVAILABLE(10_8, 5_0);

- (void)setHostedPlayer:(GKPlayer *)player didConnect:(BOOL)connected NS_AVAILABLE(10_10, 8_0);

/// deprecated, set the message on the match request instead
@property(nonatomic, nullable, copy) NSString *defaultInvitationMessage NS_DEPRECATED(10_8, 10_10, 5_0, 7_0) ; // default message to use when inviting friends. Can be edited by the user.
@end

@interface GKMatchmakerViewController (Obsoleted)
/*** This method is obsolete. It will never be invoked and its implementation does nothing***/
- (void)setHostedPlayer:(NSString *)playerID connected:(BOOL)connected NS_DEPRECATED(10_8, 10_10, 5_0, 8_0, "This is never invoked and its implementation does nothing, use setHostedPlayer:didConnect:") ;

#if TARGET_OS_IPHONE
/*** This method is obsolete. It will never be invoked and its implementation does nothing***/
- (void)setHostedPlayerReady:(NSString *)playerID NS_DEPRECATED(NA, NA, 4_1, 5_0, "This is never invoked and its implementation does nothing, use setHostedPlayer:connected: instead") ;
#endif
@end

@protocol GKMatchmakerViewControllerDelegate <NSObject>
@required
/// The user has cancelled matchmaking
- (void)matchmakerViewControllerWasCancelled:(GKMatchmakerViewController *)viewController NS_AVAILABLE(10_8, 4_1);

/// Matchmaking has failed with an error
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFailWithError:(NSError *)error NS_AVAILABLE(10_8, 4_1);

@optional
/// A peer-to-peer match has been found, the game should start
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFindMatch:(GKMatch *)match NS_AVAILABLE(10_8, 4_1);

/// Players have been found for a server-hosted game, the game should start
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFindHostedPlayers:(NSArray<GKPlayer *> *)players NS_AVAILABLE(10_10, 8_0);

/// An invited player has accepted a hosted invite.  Apps should connect through the hosting server and then update the player's connected state (using setConnected:forHostedPlayer:)
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController hostedPlayerDidAccept:(GKPlayer *)player NS_AVAILABLE(10_10, 8_0);

/*** These protocol methods are obsoleted. They will never be invoked and their implementation does nothing***/
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFindPlayers:(NSArray<NSString *> *)playerIDs NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "This is never invoked and its implementation does nothing, use matchmakerViewController:didFindHostedPlayers:") ;
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didReceiveAcceptFromHostedPlayer:(NSString *)playerID NS_DEPRECATED(10_8, 10_10, 5_0, 8_0, "This is never invoked and its implementation does nothing, use matchmakerViewController:hostedPlayerDidAccept:") ;
@end
NS_ASSUME_NONNULL_END
