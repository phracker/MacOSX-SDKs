//
//  GKAccessPoint.h
//  GameCenterUI
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <TargetConditionals.h>

#import <GameKit/GKGameCenterViewController.h>

NS_ASSUME_NONNULL_BEGIN

/// This is a class that puts up an access point widget for GameCenterViewController that floats over the game UI.  By default it appears in the top/leading corner (upper left on LTR systems) and shows just the local player avatar in a small circular dot.  If the user taps on this it will present the game center view controller.  If the user is not signed in it will show text offering to sign into GameCenter.

#if TARGET_OS_OSX && !TARGET_OS_MACCATALYST
@class NSWindow;
#else
@class UIWindow;
#endif

typedef NS_ENUM(NSInteger, GKAccessPointLocation) {
    GKAccessPointLocationTopLeading,
    GKAccessPointLocationTopTrailing,
    GKAccessPointLocationBottomLeading,
    GKAccessPointLocationBottomTrailing
} NS_SWIFT_NAME(GKAccessPoint.Location);

API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface GKAccessPoint : NSObject

@property (nonatomic, class, readonly) GKAccessPoint *shared;

/// set this true to enable access point in your app.  Setting this will cause the access point to appear after the notification banner is presented.  If it already was presented it will appear immediately
@property (nonatomic, assign, getter=isActive) BOOL active;

/// set this on tvOS to put the accessPoint into focused mode
@property (nonatomic, assign, getter=isFocused) BOOL focused API_AVAILABLE(tvos(14.0)) API_UNAVAILABLE(macos, ios);

@property (nonatomic, readonly, getter=isVisible) BOOL visible;     /// observable property that indicates when the access point is visible.
@property (nonatomic, readonly) BOOL isPresentingGameCenter;        /// observable property that becomes true when user taps on the access point and it is showing Game Center UI.  Will become false when it is dismissed

/// Set this property to true if you wish to show the highlights for most recent acheivement, current rank on default leaderboard, etc
@property (nonatomic, assign) BOOL showHighlights;

/// These properties control the placement of the widget
@property (nonatomic, assign) GKAccessPointLocation location;       /// specifies the location on the screen that the developer wishes to place the access point

/// observable property that contains the current frame needed to display the widget
#if TARGET_OS_OSX && !TARGET_OS_MACCATALYST
@property (nonatomic, readonly) NSRect frameInScreenCoordinates;
#else
@property (nonatomic, readonly) CGRect frameInScreenCoordinates;
#endif

/// the following is a platform specific window that you wish to have the access point in.  If not set then a best attempt will be made to choose the main window of the app.
#if TARGET_OS_OSX && !TARGET_OS_MACCATALYST
@property (nonatomic, weak, nullable) NSWindow *parentWindow;
#else
@property (nonatomic, weak, nullable) UIWindow *parentWindow;
#endif

/// this lets the developer trigger the access point as if the user had touched it.  This is useful for games that use controllers or the remote on AppleTV.  the argument lets you specify a specific state (default, profile, acheivements, leaderboards) for GameCenterViewController
- (void)triggerAccessPointWithHandler:(void (^)(void))handler NS_SWIFT_NAME(trigger(handler:));
- (void)triggerAccessPointWithState:(GKGameCenterViewControllerState)state handler:(void (^)(void))handler NS_SWIFT_NAME(trigger(state:handler:));

@end

NS_ASSUME_NONNULL_END
