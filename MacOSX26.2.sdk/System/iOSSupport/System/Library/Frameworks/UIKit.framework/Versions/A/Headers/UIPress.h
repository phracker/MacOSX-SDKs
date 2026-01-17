#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPress.h>)
//
//  UIPress.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UITouch.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIKey.h>

@class UIGestureRecognizer;
@class UIResponder;
@class UIWindow;

typedef NS_ENUM(NSInteger, UIPressPhase) {
    UIPressPhaseBegan,         // whenever a button press begins.
    UIPressPhaseChanged,       // whenever a button moves.
    UIPressPhaseStationary,    // whenever a buttons was pressed and is still being held down.
    UIPressPhaseEnded,         // whenever a button is released.
    UIPressPhaseCancelled,     // whenever a button press doesn't end but we need to stop tracking.
} API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UIPressType) {
    UIPressTypeUpArrow,
    UIPressTypeDownArrow,
    UIPressTypeLeftArrow,
    UIPressTypeRightArrow,

    UIPressTypeSelect,
    UIPressTypeMenu,
    UIPressTypePlayPause,

    UIPressTypePageUp API_AVAILABLE(tvos(14.3)) API_UNAVAILABLE(ios, watchos) = 30,
    UIPressTypePageDown API_AVAILABLE(tvos(14.3)) API_UNAVAILABLE(ios, watchos) = 31,

    /// Represents a button on a TV remote labeled with 123. When this button is pressed, an app should provide UI to enter a specific channel number if channel
    /// numbers are available. If no channel numbers exist the app should provide UI to toggle channel category filters, search for channels by name or search for
    /// currently airing shows.
    UIPressTypeTVRemoteOneTwoThree API_AVAILABLE(tvos(18.1)) API_UNAVAILABLE(ios, watchos, visionos) = 32,

    /// Represents a button on a TV remote labeled with four colors, analogous to the four separate color buttons found on some TV remotes. When this button is
    /// pressed, an app should perform the appropriate color action or if there are multiple color actions available provide UI to choose the specific color.
    UIPressTypeTVRemoteFourColors API_AVAILABLE(tvos(18.1)) API_UNAVAILABLE(ios, watchos, visionos) = 33,
} API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(watchos);

UIKIT_EXTERN API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(watchos) @interface UIPress : NSObject

@property (nonatomic, readonly) NSTimeInterval   timestamp;
@property (nonatomic, readonly) UIPressPhase     phase;
@property (nonatomic, readonly) UIPressType      type;

@property (nullable, nonatomic, readonly, strong) UIWindow                        *window;
@property (nullable, nonatomic, readonly, strong) UIResponder                     *responder;
@property (nullable, nonatomic, readonly, copy)   NSArray <UIGestureRecognizer *> *gestureRecognizers;

// For analog buttons, returns a value between 0 and 1.  Digital buttons return 0 or 1.
@property (nonatomic, readonly) CGFloat force;

/// For presses that originate from a hardware keyboard, contains a UIKey object describing the key being acted upon.
/// This property is nil if the press did not originate from a hardware keyboard.
@property (nonatomic, nullable, readonly) UIKey *key;

@end

#else
#import <UIKitCore/UIPress.h>
#endif
