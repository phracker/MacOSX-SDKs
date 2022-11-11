//
//  GKTurnBasedMatchmakerViewController.h
//  Game Center
//
//  Copyright 2010-2022 Apple Inc. All rights reserved.
//

@protocol GKTurnBasedMatchmakerViewControllerDelegate;

@class GKMatchmakerViewController, GKTurnBasedMatch, GKMatchRequest;

@protocol GKTurnBasedMatchmakerViewControllerDelegate;

#import <Foundation/Foundation.h>
#import <GameKit/GKMatchmakerViewController.h>

/// View controller to manage turn-based matches, invite friends and perform auto-matching. Present modally from the top view controller.
#if TARGET_OS_IPHONE

#import <UIKit/UINavigationController.h> // UINavigationController

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_8, 5_0)
@interface GKTurnBasedMatchmakerViewController : UINavigationController
@end
#else
#import <GameKit/GKDialogController.h>
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_8, 5_0)
@interface GKTurnBasedMatchmakerViewController : NSViewController <GKViewController>
@end
#endif

@interface GKTurnBasedMatchmakerViewController ()

@property (nonatomic, nullable, readwrite, weak) id<GKTurnBasedMatchmakerViewControllerDelegate> turnBasedMatchmakerDelegate;
@property (nonatomic, readwrite, assign) BOOL showExistingMatches; /// defaults to YES

/// This controls the mode of matchmaking to support in the UI (all, nearby only, automatch only, invite only). Throws an exception if you can not set to the desired mode (due to restrictions)
@property (nonatomic, assign) GKMatchmakingMode matchmakingMode API_AVAILABLE(ios(15), macos(12), tvos(15));

- (id)initWithMatchRequest:(GKMatchRequest *)request;

@end

@protocol GKTurnBasedMatchmakerViewControllerDelegate <NSObject>
@required

/// The user has cancelled
- (void)turnBasedMatchmakerViewControllerWasCancelled:(GKTurnBasedMatchmakerViewController *)viewController NS_AVAILABLE(10_8, 5_0);

/// Matchmaking has failed with an error
- (void)turnBasedMatchmakerViewController:(GKTurnBasedMatchmakerViewController *)viewController didFailWithError:(NSError *)error NS_AVAILABLE(10_8, 5_0);


@optional

// Deprecated
- (void)turnBasedMatchmakerViewController:(GKTurnBasedMatchmakerViewController *)viewController didFindMatch:(GKTurnBasedMatch *)match NS_DEPRECATED(10_8, 10_11, 5_0, 9_0, "use GKTurnBasedEventListener player:receivedTurnEventForMatch:didBecomeActive:") ;

// Deprectated
- (void)turnBasedMatchmakerViewController:(GKTurnBasedMatchmakerViewController *)viewController playerQuitForMatch:(GKTurnBasedMatch *)match NS_DEPRECATED(10_8, 10_11, 5_0, 9_0, "use GKTurnBasedEventListener player:wantsToQuitMatch:") ;

@end

NS_ASSUME_NONNULL_END
