/*
 *  GKTurnBasedMatchmakerViewController.h
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
#import <GameKit/GameKit.h>

@class GKMatchmakerViewController, GKTurnBasedMatch;

@protocol GKTurnBasedMatchmakerViewControllerDelegate;

// View controller to manage matches, invite friends and perform auto-matching. Present modally from the top view controller.
#if TARGET_OS_IPHONE
NS_CLASS_AVAILABLE(NA, 5_0)
@interface GKTurnBasedMatchmakerViewController : UINavigationController
@end
#else
#import <GameKit/GKDialogController.h>
NS_CLASS_AVAILABLE(10_8, NA)
@interface GKTurnBasedMatchmakerViewController : NSViewController <GKViewController> {
	id _internal1,_internal2,_internal3,_internal4;
}
@end
#endif

@interface GKTurnBasedMatchmakerViewController ()

@property (readwrite, assign, NS_NONATOMIC_IOSONLY) id<GKTurnBasedMatchmakerViewControllerDelegate> turnBasedMatchmakerDelegate;
@property (readwrite, assign, NS_NONATOMIC_IOSONLY) BOOL showExistingMatches; // defaults to YES

// Inherited from GKMatchmakerViewControler
- (id)initWithMatchRequest:(GKMatchRequest *)request;

@end

@protocol GKTurnBasedMatchmakerViewControllerDelegate // <GKMatchmakerViewControllerDelegate>
@required

// The user has cancelled
- (void)turnBasedMatchmakerViewControllerWasCancelled:(GKTurnBasedMatchmakerViewController *)viewController;

// Matchmaking has failed with an error
- (void)turnBasedMatchmakerViewController:(GKTurnBasedMatchmakerViewController *)viewController didFailWithError:(NSError *)error;

// A turned-based match has been found, the game should start
- (void)turnBasedMatchmakerViewController:(GKTurnBasedMatchmakerViewController *)viewController didFindMatch:(GKTurnBasedMatch *)match;

// Called when a users chooses to quit a match and that player has the current turn.  The developer should call playerQuitInTurnWithOutcome:nextPlayer:matchData:completionHandler: on the match passing in appropriate values.  They can also update matchOutcome for other players as appropriate.
- (void)turnBasedMatchmakerViewController:(GKTurnBasedMatchmakerViewController *)viewController playerQuitForMatch:(GKTurnBasedMatch *)match;

@end

