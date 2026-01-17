/*
 *  GKMatchmakerViewController.h
 *  GameKit
 *
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

@class GKMatchRequest, GKInvite, GKMatch;

@protocol GKMatchmakerViewControllerDelegate;

// View controller to invite friends, respond to invites, and perform auto-matching. Present modally from the top view controller.
#if TARGET_OS_IPHONE
NS_CLASS_AVAILABLE(NA, 4_1)
@interface GKMatchmakerViewController : UINavigationController
@end
#else
#import <GameKit/GKDialogController.h>
NS_CLASS_AVAILABLE(10_8, NA)
@interface GKMatchmakerViewController : NSViewController <GKViewController> {
	id _internal1,_internal2,_internal3,_internal4;
}
@end
#endif

@interface GKMatchmakerViewController ()

@property(assign, NS_NONATOMIC_IOSONLY) id<GKMatchmakerViewControllerDelegate>     matchmakerDelegate;
@property(readonly, retain, NS_NONATOMIC_IOSONLY) GKMatchRequest                   *matchRequest;
@property(assign, getter=isHosted, NS_NONATOMIC_IOSONLY) BOOL                      hosted;  // set to YES to receive hosted (eg. not peer-to-peer) match results. Will cause the controller to return an array of players instead of a match.

// Initialize with a matchmaking request, allowing the user to send invites and/or start matchmaking
- (id)initWithMatchRequest:(GKMatchRequest *)request;

// Initialize with an accepted invite, allowing the user to see the status of other invited players and get notified when the game starts
- (id)initWithInvite:(GKInvite *)invite;

// Add additional players (not currently connected) to an existing peer-to-peer match.  
// Apps should elect a single device to do this, otherwise conflicts could arise resulting in unexpected connection errors.
- (void)addPlayersToMatch:(GKMatch *)match __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);

// Update the displayed connection status for a remote server-hosted player
- (void)setHostedPlayer:(NSString *)playerID connected:(BOOL)connected __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);

#if TARGET_OS_IPHONE
// Deprecated, use setHostedPlayer:connected: instead.
- (void)setHostedPlayerReady:(NSString *)playerID __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_4_1,__IPHONE_5_0);
#endif

// deprecated, set the message on the match request instead
@property(copy, NS_NONATOMIC_IOSONLY) NSString                                     *defaultInvitationMessage __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0); // default message to use when inviting friends. Can be edited by the user.

@end

@protocol GKMatchmakerViewControllerDelegate <NSObject>
@required
// The user has cancelled matchmaking
- (void)matchmakerViewControllerWasCancelled:(GKMatchmakerViewController *)viewController;

// Matchmaking has failed with an error
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFailWithError:(NSError *)error;

@optional
// A peer-to-peer match has been found, the game should start
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFindMatch:(GKMatch *)match;

// Players have been found for a server-hosted game, the game should start
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFindPlayers:(NSArray *)playerIDs;

// An invited player has accepted a hosted invite.  Apps should connect through the hosting server and then update the player's connected state (using setConnected:forHostedPlayer:)
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didReceiveAcceptFromHostedPlayer:(NSString *)playerID __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);
@end

