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

@class UIGestureRecognizer;
@class UIResponder;
@class UIWindow;

API_AVAILABLE(ios(9.0)) typedef NS_ENUM(NSInteger, UIPressPhase) {
    UIPressPhaseBegan,         // whenever a button press begins.
    UIPressPhaseChanged,       // whenever a button moves.
    UIPressPhaseStationary,    // whenever a buttons was pressed and is still being held down.
    UIPressPhaseEnded,         // whenever a button is releasd.
    UIPressPhaseCancelled,     // whenever a button press doesn't end but we need to stop tracking.
};

API_AVAILABLE(ios(9.0)) typedef NS_ENUM(NSInteger, UIPressType) {
    UIPressTypeUpArrow,
    UIPressTypeDownArrow,
    UIPressTypeLeftArrow,
    UIPressTypeRightArrow,

    UIPressTypeSelect,
    UIPressTypeMenu,
    UIPressTypePlayPause,
};

UIKIT_EXTERN API_AVAILABLE(ios(9.0)) @interface UIPress : NSObject

@property(nonatomic,readonly) NSTimeInterval   timestamp;
@property(nonatomic,readonly) UIPressPhase     phase;
@property(nonatomic,readonly) UIPressType      type;

@property(nullable,nonatomic,readonly,strong) UIWindow                        *window;
@property(nullable,nonatomic,readonly,strong) UIResponder                     *responder;
@property(nullable,nonatomic,readonly,copy)   NSArray <UIGestureRecognizer *> *gestureRecognizers;

// For analog buttons, returns a value between 0 and 1.  Digital buttons return 0 or 1.
@property(nonatomic, readonly) CGFloat force;
@end

#else
#import <UIKitCore/UIPress.h>
#endif
