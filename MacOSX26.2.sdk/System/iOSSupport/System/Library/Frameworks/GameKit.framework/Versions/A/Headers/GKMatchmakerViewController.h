// Copyright © Apple Inc. All rights reserved.

#import <TargetConditionals.h>
#import <Foundation/Foundation.h>

#if !TARGET_OS_WATCH

@class GKMatchRequest, GKInvite, GKMatch, GKPlayer;

@protocol GKMatchmakerViewControllerDelegate;

typedef NS_ENUM(NSInteger, GKMatchmakingMode) {
    GKMatchmakingModeDefault = 0,
    GKMatchmakingModeNearbyOnly = 1,
    GKMatchmakingModeAutomatchOnly = 2,
    GKMatchmakingModeInviteOnly API_AVAILABLE(ios(15.0), macos(12.0), tvos(15.0), visionos(1.0)) = 3 ,
} API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), visionos(1.0));

/// View controller to invite friends, respond to invites, and perform automatching. Present modally from the top view controller.
#if TARGET_OS_IPHONE

#import <UIKit/UINavigationController.h> // UINavigationController

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(ios(4.1), macos(10.8), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface GKMatchmakerViewController : UINavigationController

#else
#import <GameKit/GKDialogController.h>
NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(ios(4.1), macos(10.8), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface GKMatchmakerViewController : NSViewController <GKViewController>
#endif
@property(nonatomic, nullable, weak) id<GKMatchmakerViewControllerDelegate>     matchmakerDelegate;
@property(nonatomic, readonly, strong) GKMatchRequest                   *matchRequest;
/// set to YES to receive hosted (eg. not peer-to-peer) match results. Will cause the controller to return an array of players instead of a match.
@property(nonatomic, assign, getter=isHosted) BOOL                      hosted;// set to YES to receive hosted (eg. not peer-to-peer) match results. Will cause the controller to return an array of players instead of a match.
/// this controls which mode of matchmaking to support in the UI (all, nearby only, automatch only, invite only).  Throws an exeption if you can not set to the desired mode (due to restrictions)
@property(nonatomic, assign) GKMatchmakingMode                          matchmakingMode API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0));
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
- (void)addPlayersToMatch:(GKMatch *)match API_AVAILABLE(ios(5.0), macos(10.8), tvos(9.0), visionos(1.0));

- (void)setHostedPlayer:(GKPlayer *)player didConnect:(BOOL)connected API_AVAILABLE(ios(8.0), macos(10.10), tvos(9.0), visionos(1.0));

/// deprecated, set the message on the match request instead
@property(nonatomic, nullable, copy) NSString *defaultInvitationMessage API_DEPRECATED("No longer supported.", ios(5.0,7.0), macos(10.8,10.10), visionos(1.0,1.0)) API_UNAVAILABLE(tvos, watchos); // default message to use when inviting friends. Can be edited by the user.
@end

@interface GKMatchmakerViewController (Obsoleted)
/*** This method is obsolete. It will never be invoked and its implementation does nothing***/
- (void)setHostedPlayer:(NSString *)playerID connected:(BOOL)connected API_DEPRECATED_WITH_REPLACEMENT("Use the ``GKMatchmakerViewController/setHostedPlayer(_:didConnect:)`` method instead.", ios(5.0,8.0), macos(10.8,10.10), visionos(1.0,1.0)) API_UNAVAILABLE(tvos, watchos);

/*** This method is obsolete. It will never be invoked and its implementation does nothing***/
- (void)setHostedPlayerReady:(NSString *)playerID API_DEPRECATED_WITH_REPLACEMENT("Use the ``GKMatchmakerViewController/setHostedPlayer(_:connected:)`` method instead.", ios(4.1,5.0), visionos(1.0,1.0)) API_UNAVAILABLE(macos, tvos, watchos);
@end

API_AVAILABLE(ios(4.0), macos(10.8), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@protocol GKMatchmakerViewControllerDelegate <NSObject>
@required
/// The user has cancelled matchmaking
- (void)matchmakerViewControllerWasCancelled:(GKMatchmakerViewController *)viewController API_AVAILABLE(ios(4.1));

/// Matchmaking has failed with an error
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFailWithError:(NSError *)error API_AVAILABLE(ios(4.1));

@optional
/// A peer-to-peer match has been found, the game should start
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFindMatch:(GKMatch *)match API_AVAILABLE(ios(4.1));

/// Players have been found for a server-hosted game, the game should start
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFindHostedPlayers:(NSArray<GKPlayer *> *)players API_AVAILABLE(ios(8.0), macos(10.10));

/// An invited player has accepted a hosted invite.  Apps should connect through the hosting server and then update the player's connected state (using setConnected:forHostedPlayer:)
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController hostedPlayerDidAccept:(GKPlayer *)player API_AVAILABLE(ios(8.0), macos(10.10));

/// The game should provide `GKMatchProperties` for the `GKPlayer` that has been invited.
/// If implemented, this function must call `completionHandler`: failing to do so will hang matchmaking.
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController
  getMatchPropertiesForRecipient:(GKPlayer *)recipient
           withCompletionHandler:(void(^)(GKMatchProperties *recipientProperties))completionHandler API_AVAILABLE(ios(17.2), macos(14.2), tvos(17.2), visionos(1.1));

/*** These protocol methods are obsoleted. They will never be invoked and their implementation does nothing***/
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFindPlayers:(NSArray<NSString *> *)playerIDs API_DEPRECATED_WITH_REPLACEMENT("Use ``GKMatchmakerViewControllerDelegate/matchmakerViewController(_:didFindHostedPlayers:)`` instead.", ios(4.1,8.0), macos(10.8,10.10)) API_UNAVAILABLE(tvos);
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didReceiveAcceptFromHostedPlayer:(NSString *)playerID API_DEPRECATED_WITH_REPLACEMENT("Use ``GKMatchmakerViewControllerDelegate/matchmakerViewController(_:hostedPlayerDidAccept:)`` instead.", ios(5.0,8.0), macos(10.8,10.10)) API_UNAVAILABLE(tvos);
@end
NS_ASSUME_NONNULL_END

#endif
