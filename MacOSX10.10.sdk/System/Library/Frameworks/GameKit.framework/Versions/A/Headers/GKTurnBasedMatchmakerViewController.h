//
//  GKTurnBasedMatchmakerViewController.h
//  Game Center
//
//  Copyright 2010-2014 Apple Inc. All rights reserved.
//

@protocol GKTurnBasedMatchmakerViewControllerDelegate;

@class GKMatchmakerViewController, GKTurnBasedMatch, GKMatchRequest;

@protocol GKTurnBasedMatchmakerViewControllerDelegate;

// View controller to manage turn-based matches, invite friends and perform auto-matching. Present modally from the top view controller.
#if TARGET_OS_IPHONE
NS_CLASS_AVAILABLE(10_8, 5_0)
@interface GKTurnBasedMatchmakerViewController : UINavigationController
@end
#else
#import <GameKit/GKDialogController.h>
NS_CLASS_AVAILABLE(10_8, 5_0)
@interface GKTurnBasedMatchmakerViewController : NSViewController <GKViewController> {
    id _remoteViewController;
    id<GKTurnBasedMatchmakerViewControllerDelegate> _turnBasedMatchmakerDelegateWeak;
    GKMatchRequest *_matchRequest;
    BOOL _showExistingMatches;
}
@end
#endif

@interface GKTurnBasedMatchmakerViewController ()

@property (nonatomic, readwrite, assign) id<GKTurnBasedMatchmakerViewControllerDelegate> turnBasedMatchmakerDelegate;
@property (nonatomic, readwrite, assign) BOOL showExistingMatches; // defaults to YES

- (id)initWithMatchRequest:(GKMatchRequest *)request;

@end

@protocol GKTurnBasedMatchmakerViewControllerDelegate <NSObject>
@required

// The user has cancelled
- (void)turnBasedMatchmakerViewControllerWasCancelled:(GKTurnBasedMatchmakerViewController *)viewController NS_AVAILABLE(10_8, 5_0);

// Matchmaking has failed with an error
- (void)turnBasedMatchmakerViewController:(GKTurnBasedMatchmakerViewController *)viewController didFailWithError:(NSError *)error NS_AVAILABLE(10_8, 5_0);

// A turned-based match has been found, the game should start
- (void)turnBasedMatchmakerViewController:(GKTurnBasedMatchmakerViewController *)viewController didFindMatch:(GKTurnBasedMatch *)match NS_AVAILABLE(10_8, 5_0);

// Called when a users chooses to quit a match and that player has the current turn.  The developer should call playerQuitInTurnWithOutcome:nextPlayer:matchData:completionHandler: on the match passing in appropriate values.  They can also update matchOutcome for other players as appropriate.
- (void)turnBasedMatchmakerViewController:(GKTurnBasedMatchmakerViewController *)viewController playerQuitForMatch:(GKTurnBasedMatch *)match NS_AVAILABLE(10_8, 5_0);

@end

