// Copyright © Apple Inc. All rights reserved.

#import <TargetConditionals.h>
#import <Foundation/Foundation.h>

#if !TARGET_OS_WATCH

@protocol GKTurnBasedMatchmakerViewControllerDelegate;

@class GKMatchmakerViewController, GKTurnBasedMatch, GKMatchRequest;

@protocol GKTurnBasedMatchmakerViewControllerDelegate;

#import <GameKit/GKMatchmakerViewController.h>

#if TARGET_OS_IPHONE

#import <UIKit/UINavigationController.h> // UINavigationController

NS_ASSUME_NONNULL_BEGIN
/// View controller to manage turn-based matches, invite friends and perform automatching. Present modally from the top view controller.
API_AVAILABLE(ios(5.0), macos(10.8), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface GKTurnBasedMatchmakerViewController : UINavigationController
@end
#else
#import <GameKit/GKDialogController.h>
NS_ASSUME_NONNULL_BEGIN
/// View controller to manage turn-based matches, invite friends and perform automatching. Present modally from the top view controller.
API_AVAILABLE(ios(5.0), macos(10.8), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface GKTurnBasedMatchmakerViewController : NSViewController <GKViewController>
@end
#endif

@interface GKTurnBasedMatchmakerViewController ()

@property (nonatomic, nullable, readwrite, weak) id<GKTurnBasedMatchmakerViewControllerDelegate> turnBasedMatchmakerDelegate;
@property (nonatomic, readwrite, assign) BOOL showExistingMatches; /// defaults to YES

/// This controls the mode of matchmaking to support in the UI (all, nearby only, automatch only, invite only). Throws an exception if you can not set to the desired mode (due to restrictions)
@property (nonatomic, assign) GKMatchmakingMode matchmakingMode API_AVAILABLE(ios(15.0), macos(12.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

- (id)initWithMatchRequest:(GKMatchRequest *)request;

@end

API_AVAILABLE(ios(5.0), macos(10.8), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@protocol GKTurnBasedMatchmakerViewControllerDelegate <NSObject>
@required

/// The user has cancelled
- (void)turnBasedMatchmakerViewControllerWasCancelled:(GKTurnBasedMatchmakerViewController *)viewController API_AVAILABLE(ios(5.0), macos(10.8), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Matchmaking has failed with an error
- (void)turnBasedMatchmakerViewController:(GKTurnBasedMatchmakerViewController *)viewController didFailWithError:(NSError *)error API_AVAILABLE(ios(5.0), macos(10.8), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);


@optional

// Deprecated
- (void)turnBasedMatchmakerViewController:(GKTurnBasedMatchmakerViewController *)viewController didFindMatch:(GKTurnBasedMatch *)match API_DEPRECATED_WITH_REPLACEMENT("Use ``GKTurnBasedEventListener`` method ``GKTurnBasedEventListener/player(_:receivedTurnEventFor:didBecomeActive:)`` instead.", ios(5.0,9.0), macos(10.8,10.11), visionos(1.0,1.0)) API_UNAVAILABLE(tvos, watchos);

// Deprectated
- (void)turnBasedMatchmakerViewController:(GKTurnBasedMatchmakerViewController *)viewController playerQuitForMatch:(GKTurnBasedMatch *)match API_DEPRECATED_WITH_REPLACEMENT("Use ``GKTurnBasedEventListener`` method ``GKTurnBasedEventListener/player(_:wantsToQuitMatch:)`` instead.", ios(5.0,9.0), macos(10.8,10.11), visionos(1.0,1.0)) API_UNAVAILABLE(tvos, watchos);

@end

NS_ASSUME_NONNULL_END

#endif
