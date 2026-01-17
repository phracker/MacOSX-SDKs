// Copyright © Apple Inc. All rights reserved.

#import <TargetConditionals.h>
#import <Foundation/Foundation.h>

#if !TARGET_OS_WATCH

#import <CoreGraphics/CoreGraphics.h>

#import <GameKit/GKGameCenterViewController.h>

NS_ASSUME_NONNULL_BEGIN

/// This is a class that puts up an access point widget for GameCenterViewController that floats over the game UI.  By default it appears in the top/leading corner (upper left on LTR systems) and shows just the local player avatar in a small circular dot.  If the user taps on this it will present the game center view controller.  If the user is not signed in it will show text offering to sign into GameCenter.

#if TARGET_OS_OSX && !TARGET_OS_MACCATALYST
@class NSWindow;
#else
@class UIWindow;
#endif

@class GKGameActivity;

typedef NS_ENUM(NSInteger, GKAccessPointLocation) {
    GKAccessPointLocationTopLeading,
    GKAccessPointLocationTopTrailing,
    GKAccessPointLocationBottomLeading,
    GKAccessPointLocationBottomTrailing
} NS_SWIFT_NAME(GKAccessPoint.Location) API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), visionos(1.0));

API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface GKAccessPoint : NSObject

@property (nonatomic, class, readonly) GKAccessPoint *shared;

/// set this true to enable access point in your app.  Setting this will cause the access point to appear after the notification banner is presented.  If it already was presented it will appear immediately
@property (nonatomic, assign, getter=isActive) BOOL active;

/// set this on tvOS to put the accessPoint into focused mode
@property (nonatomic, assign, getter=isFocused) BOOL focused API_AVAILABLE(tvos(14.0)) API_UNAVAILABLE(macos, ios);

@property (nonatomic, readonly, getter=isVisible) BOOL visible;     /// observable property that indicates when the access point is visible.
@property (nonatomic, readonly) BOOL isPresentingGameCenter;        /// observable property that becomes true when user taps on the access point and it is showing Game Center UI.  Will become false when it is dismissed

/// Set this property to true if you wish to show the highlights for most recent achievement, current rank on default leaderboard, etc
@property (nonatomic, assign) BOOL showHighlights API_DEPRECATED("No longer supported", ios(14.0,26.0), macos(11.0,26.0), tvos(14.0,26.0), visionos(1.0,26.0));

/// These properties control the placement of the widget
@property (nonatomic, assign) GKAccessPointLocation location;       /// specifies the location on the screen that the developer wishes to place the access point

#if TARGET_OS_OSX && !TARGET_OS_MACCATALYST
/// observable property that contains the current frame needed to display the widget
@property (nonatomic, readonly) NSRect frameInScreenCoordinates;
#else
/// observable property that contains the current frame needed to display the widget
@property (nonatomic, readonly) CGRect frameInScreenCoordinates;
#endif

#if TARGET_OS_OSX && !TARGET_OS_MACCATALYST
/// the following is a platform specific window that you wish to have the access point in.  If not set then a best attempt will be made to choose the main window of the app.
@property (nonatomic, weak, nullable) NSWindow *parentWindow;
#else
/// the following is a platform specific window that you wish to have the access point in.  If not set then a best attempt will be made to choose the main window of the app.
@property (nonatomic, weak, nullable) UIWindow *parentWindow;
#endif

/// this lets the developer trigger the access point as if the user had touched it.  This is useful for games that use controllers or the remote on AppleTV.  the argument lets you specify a specific state (default, profile, achievements, leaderboards) for GameCenterViewController
- (void)triggerAccessPointWithHandler:(void (^)(void))handler NS_SWIFT_NAME(trigger(handler:));
- (void)triggerAccessPointWithState:(GKGameCenterViewControllerState)state
                            handler:(void (^)(void))handler NS_SWIFT_NAME(trigger(state:handler:));
- (void)triggerAccessPointWithAchievementID:(NSString *)achievementID
                                    handler:(void (^ __nullable)(void))handler NS_SWIFT_NAME(trigger(achievementID:handler:)) API_AVAILABLE(ios(18.0), macos(15.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);
- (void)triggerAccessPointWithLeaderboardSetID:(NSString *)leaderboardSetID
                                       handler:(void (^ __nullable)(void))handler NS_SWIFT_NAME(trigger(leaderboardSetID:handler:)) API_AVAILABLE(ios(18.0), macos(15.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);
- (void)triggerAccessPointWithLeaderboardID:(NSString *)leaderboardID
                                playerScope:(GKLeaderboardPlayerScope)playerScope
                                  timeScope:(GKLeaderboardTimeScope)timeScope
                                    handler:(void (^ __nullable)(void))handler NS_SWIFT_NAME(trigger(leaderboardID:playerScope:timeScope:handler:)) API_AVAILABLE(ios(18.0), macos(15.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);
- (void)triggerAccessPointWithPlayer:(GKPlayer *)player
                             handler:(void (^ __nullable)(void))handler NS_SWIFT_NAME(trigger(player:handler:)) API_AVAILABLE(ios(18.0), macos(15.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

/// Displays the view that allows players to engage each other with activities and challenges.
- (void)triggerAccessPointForPlayTogetherWithHandler:(void (^ _Nullable)(void))handler NS_SWIFT_NAME(triggerForPlayTogether(handler:)) NS_SWIFT_ASYNC(1) API_AVAILABLE(ios(26.0), macos(26.0)) API_UNAVAILABLE(tvos, visionos, watchos);

/// Displays the view that allows players to engage each other with challenges.
- (void)triggerAccessPointForChallengesWithHandler:(void (^ _Nullable)(void))handler NS_SWIFT_NAME(triggerForChallenges(handler:)) NS_SWIFT_ASYNC(1) API_AVAILABLE(ios(26.0), macos(26.0)) API_UNAVAILABLE(tvos, visionos, watchos);

/// Displays the challenge creation view for the provided challenge definition ID.
- (void)triggerAccessPointWithChallengeDefinitionID:(NSString *)challengeDefinitionID
                                            handler:(void (^ _Nullable)(void))handler NS_SWIFT_NAME(trigger(challengeDefinitionID:handler:)) NS_SWIFT_ASYNC(2) API_AVAILABLE(ios(26.0), macos(26.0)) API_UNAVAILABLE(tvos, visionos, watchos);

/// Displays the game activity creation view for the provided activity definition ID.
- (void)triggerAccessPointWithGameActivityDefinitionID:(NSString *)gameActivityDefinitionID
                                               handler:(void (^ _Nullable)(void))handler NS_SWIFT_NAME(trigger(gameActivityDefinitionID:handler:)) NS_SWIFT_ASYNC(2) API_AVAILABLE(ios(26.0), macos(26.0)) API_UNAVAILABLE(tvos, visionos, watchos);

/// Displays the game activity view for the provided activity instance.
- (void)triggerAccessPointWithGameActivity:(GKGameActivity *)gameActivity
                                   handler:(void (^ _Nullable)(void))handler NS_SWIFT_NAME(trigger(gameActivity:handler:)) NS_SWIFT_ASYNC(2) API_AVAILABLE(ios(26.0), macos(26.0)) API_UNAVAILABLE(tvos, visionos, watchos);

/// Brings up the invite friends view.
- (void)triggerAccessPointForFriendingWithHandler:(void (^ _Nullable)(void))handler NS_SWIFT_NAME(triggerForFriending(handler:)) NS_SWIFT_ASYNC(1) API_AVAILABLE(ios(26.0), macos(26.0)) API_UNAVAILABLE(tvos, visionos, watchos);

/// Brings up the Arcade dashboard.
- (void)triggerAccessPointForArcadeWithHandler:(void (^ _Nullable)(void))handler NS_SWIFT_NAME(triggerForArcade(handler:)) NS_SWIFT_ASYNC(1) API_AVAILABLE(ios(26.0), macos(26.0)) API_UNAVAILABLE(tvos, visionos, watchos);

@end

NS_ASSUME_NONNULL_END

#endif
