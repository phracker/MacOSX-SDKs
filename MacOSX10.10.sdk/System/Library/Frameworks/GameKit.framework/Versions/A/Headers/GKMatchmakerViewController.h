//
//  GKMatchmakerViewController.h
//  Game Center
//
//  Copyright 2010-2015 Apple Inc. All rights reserved.
//

@class GKMatchRequest, GKInvite, GKMatch, GKPlayer;

@protocol GKMatchmakerViewControllerDelegate;

// View controller to invite friends, respond to invites, and perform auto-matching. Present modally from the top view controller.
#if TARGET_OS_IPHONE
NS_CLASS_AVAILABLE(10_8, 4_1)
@interface GKMatchmakerViewController : UINavigationController

#else
#import <GameKit/GKDialogController.h>
NS_CLASS_AVAILABLE(10_8, 4_1)
@interface GKMatchmakerViewController : NSViewController <GKViewController> {
    id _remoteViewController;
    id<GKMatchmakerViewControllerDelegate> _matchmakerDelegateWeak;
    GKMatchRequest *_matchRequest;
    GKInvite *_acceptedInvite;
    GKMatch *_match;
    BOOL _hosted;
    BOOL _finished;
    NSMutableArray *_hostedPlayers;
}

#endif

@property(nonatomic, assign) id<GKMatchmakerViewControllerDelegate>     matchmakerDelegate;
@property(nonatomic, readonly, retain) GKMatchRequest                   *matchRequest;
@property(nonatomic, assign, getter=isHosted) BOOL                      hosted;  // set to YES to receive hosted (eg. not peer-to-peer) match results. Will cause the controller to return an array of players instead of a match.

// Initialize with a matchmaking request, allowing the user to send invites and/or start matchmaking
- (id)initWithMatchRequest:(GKMatchRequest *)request;

// Initialize with an accepted invite, allowing the user to see the status of other invited players and get notified when the game starts
- (id)initWithInvite:(GKInvite *)invite;

// Add additional players (not currently connected) to an existing peer-to-peer match.  
// Apps should elect a single device to do this, otherwise conflicts could arise resulting in unexpected connection errors.
- (void)addPlayersToMatch:(GKMatch *)match NS_AVAILABLE(10_8, 5_0);

// Update the displayed connection status for a remote server-hosted player
- (void)setHostedPlayer:(NSString *)playerID connected:(BOOL)connected NS_DEPRECATED(10_8, 10_10, 5_0, 8_0, "use setHostedPlayer:didConnect:");
- (void)setHostedPlayer:(GKPlayer *)player didConnect:(BOOL)connected NS_AVAILABLE(10_10, 8_0);

#if TARGET_OS_IPHONE
// Deprecated, use setHostedPlayer:connected: instead.
- (void)setHostedPlayerReady:(NSString *)playerID NS_DEPRECATED(NA, NA, 4_1, 5_0);
#endif

// deprecated, set the message on the match request instead
@property(nonatomic, copy) NSString *defaultInvitationMessage NS_DEPRECATED(10_8, 10_10, 5_0, 7_0); // default message to use when inviting friends. Can be edited by the user.

@end

@protocol GKMatchmakerViewControllerDelegate <NSObject>
@required
// The user has cancelled matchmaking
- (void)matchmakerViewControllerWasCancelled:(GKMatchmakerViewController *)viewController NS_AVAILABLE(10_8, 4_1);

// Matchmaking has failed with an error
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFailWithError:(NSError *)error NS_AVAILABLE(10_8, 4_1);

@optional
// A peer-to-peer match has been found, the game should start
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFindMatch:(GKMatch *)match NS_AVAILABLE(10_8, 4_1);

// Players have been found for a server-hosted game, the game should start
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFindHostedPlayers:(NSArray /*<GKPlayer>*/ *)players NS_AVAILABLE(10_10, 8_0);
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFindPlayers:(NSArray /*<NSString>*/ *)playerIDs NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "use matchmakerViewController:didFindHostedPlayers:");

// An invited player has accepted a hosted invite.  Apps should connect through the hosting server and then update the player's connected state (using setConnected:forHostedPlayer:)
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController hostedPlayerDidAccept:(GKPlayer *)player NS_AVAILABLE(10_10, 8_0);
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didReceiveAcceptFromHostedPlayer:(NSString *)playerID NS_DEPRECATED(10_8, 10_10, 5_0, 8_0, "use matchmakerViewController:hostedPlayerDidAccept:");
@end

