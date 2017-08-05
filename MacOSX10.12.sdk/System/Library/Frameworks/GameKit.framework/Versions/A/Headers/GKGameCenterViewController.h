//
//  GKGameCenterViewController.h
//  Game Center
//
//  Copyright 2012-2016 Apple Inc. All rights reserved.
//

#import <GameKit/GKLeaderboard.h>

@protocol GKGameCenterControllerDelegate;

typedef NS_ENUM(NSInteger, GKGameCenterViewControllerState) {
    GKGameCenterViewControllerStateDefault = -1,
    GKGameCenterViewControllerStateLeaderboards,
    GKGameCenterViewControllerStateAchievements,
    GKGameCenterViewControllerStateChallenges,
};

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#import <GameKit/GKDialogController.h>
#endif

NS_ASSUME_NONNULL_BEGIN
// View controller that provides the standard user interface for leaderboards, achievements, and challenges. Present modally from the top view controller.
#if TARGET_OS_IPHONE
NS_CLASS_AVAILABLE(10_9, 6_0)
@interface GKGameCenterViewController : UINavigationController
@end
#else
NS_CLASS_AVAILABLE(10_9, 6_0)
@interface GKGameCenterViewController : NSViewController  <GKViewController> {
	id _internal1,_internal2,_internal3;
    GKGameCenterViewControllerState _viewState;
    NSString *_leaderboardIdentifier;
    NSString *_leaderboardCategory;
    GKLeaderboardTimeScope _leaderboardTimeScope;
    BOOL _internalFlag;
}
@end
#endif

@interface GKGameCenterViewController ()
@property (assign, nullable, NS_NONATOMIC_IOSONLY)   id<GKGameCenterControllerDelegate>      gameCenterDelegate;
@property (assign, NS_NONATOMIC_IOSONLY)   GKGameCenterViewControllerState         viewState ;


@end

@interface GKGameCenterViewController (Leaderboards)

@property (nonatomic, assign)   GKLeaderboardTimeScope leaderboardTimeScope NS_AVAILABLE(10_8, 4_1) ;
@property (nonatomic, nullable, retain)   NSString *leaderboardIdentifier NS_AVAILABLE(10_10, 7_0) ;

@property (nonatomic, nullable, retain)   NSString *leaderboardCategory    NS_DEPRECATED(10_8, 10_10, 4_1, 7_0, "GKGameCenterViewController's leaderboardCategory property is deprecated. Use leaderboardIdentifier instead.") ;

@end

@protocol GKGameCenterControllerDelegate <NSObject>

- (void)gameCenterViewControllerDidFinish:(GKGameCenterViewController *)gameCenterViewController NS_AVAILABLE(10_9, 6_0);

@end
NS_ASSUME_NONNULL_END
