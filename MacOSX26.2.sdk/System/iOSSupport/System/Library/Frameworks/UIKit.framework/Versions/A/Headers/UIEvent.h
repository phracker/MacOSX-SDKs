#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIEvent.h>)
//
//  UIEvent.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UICommand.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIWindow, UIView, UIGestureRecognizer, UITouch;

typedef NS_ENUM(NSInteger, UIEventType) {
    UIEventTypeTouches,
    UIEventTypeMotion,
    UIEventTypeRemoteControl,
    UIEventTypePresses API_AVAILABLE(ios(9.0)),
    UIEventTypeScroll      API_AVAILABLE(ios(13.4), tvos(13.4)) API_UNAVAILABLE(watchos) = 10,
    UIEventTypeHover       API_AVAILABLE(ios(13.4), tvos(13.4)) API_UNAVAILABLE(watchos) = 11,
    UIEventTypeTransform   API_AVAILABLE(ios(13.4), tvos(13.4)) API_UNAVAILABLE(watchos) = 14,
} API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UIEventSubtype) {
    // available in iPhone OS 3.0
    UIEventSubtypeNone                              = 0,
    
    // for UIEventTypeMotion, available in iPhone OS 3.0
    UIEventSubtypeMotionShake                       = 1,
    
    // for UIEventTypeRemoteControl, available in iOS 4.0
    UIEventSubtypeRemoteControlPlay                 = 100,
    UIEventSubtypeRemoteControlPause                = 101,
    UIEventSubtypeRemoteControlStop                 = 102,
    UIEventSubtypeRemoteControlTogglePlayPause      = 103,
    UIEventSubtypeRemoteControlNextTrack            = 104,
    UIEventSubtypeRemoteControlPreviousTrack        = 105,
    UIEventSubtypeRemoteControlBeginSeekingBackward = 106,
    UIEventSubtypeRemoteControlEndSeekingBackward   = 107,
    UIEventSubtypeRemoteControlBeginSeekingForward  = 108,
    UIEventSubtypeRemoteControlEndSeekingForward    = 109,
} API_UNAVAILABLE(watchos);

/// Set of buttons pressed for the current event
/// Raw format of: 1 << (buttonNumber - 1)
/// UIEventButtonMaskPrimary = 1 << 0
typedef NS_OPTIONS(NSInteger, UIEventButtonMask) {
    UIEventButtonMaskPrimary    = 1 << 0,
    UIEventButtonMaskSecondary  = 1 << 1
} NS_SWIFT_NAME(UIEvent.ButtonMask) API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(tvos, watchos);

/// Convenience initializer for a button mask where `buttonNumber` is a one-based index of the button on the input device
/// .button(1) == .primary
/// .button(2) == .secondary
UIKIT_EXTERN UIEventButtonMask UIEventButtonMaskForButtonNumber(NSInteger buttonNumber) NS_SWIFT_NAME(UIEventButtonMask.button(_:)) API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(tvos, watchos);

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIEvent : NSObject

@property(nonatomic,readonly) UIEventType     type API_AVAILABLE(ios(3.0));
@property(nonatomic,readonly) UIEventSubtype  subtype API_AVAILABLE(ios(3.0));

@property(nonatomic,readonly) NSTimeInterval  timestamp;

@property (nonatomic, readonly) UIKeyModifierFlags modifierFlags API_AVAILABLE(ios(13.4), tvos(13.4)) API_UNAVAILABLE(watchos);
@property (nonatomic, readonly) UIEventButtonMask buttonMask API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(tvos, watchos);

@property(nonatomic, readonly, nullable) NSSet <UITouch *> *allTouches;
- (nullable NSSet <UITouch *> *)touchesForWindow:(UIWindow *)window;
- (nullable NSSet <UITouch *> *)touchesForView:(UIView *)view;
- (nullable NSSet <UITouch *> *)touchesForGestureRecognizer:(UIGestureRecognizer *)gesture API_AVAILABLE(ios(3.2));

// An array of auxiliary UITouch’s for the touch events that did not get delivered for a given main touch. This also includes an auxiliary version of the main touch itself.
- (nullable NSArray <UITouch *> *)coalescedTouchesForTouch:(UITouch *)touch API_AVAILABLE(ios(9.0));

// An array of auxiliary UITouch’s for touch events that are predicted to occur for a given main touch. These predictions may not exactly match the real behavior of the touch as it moves, so they should be interpreted as an estimate.
- (nullable NSArray <UITouch *> *)predictedTouchesForTouch:(UITouch *)touch API_AVAILABLE(ios(9.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIEvent.h>
#endif
